/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 Evidence s.r.l.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License, version 2, for more details.
 * 
 * You should have received a copy of the GNU General Public License,
 * version 2, along with this program; if not, see
 * <https://www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
 * 
 * This program is distributed to you subject to the following
 * clarifications and special exceptions to the GNU General Public
 * License, version 2.
 * 
 * THIRD PARTIES' MATERIALS
 * 
 * Certain materials included in this library are provided by third
 * parties under licenses other than the GNU General Public License. You
 * may only use, copy, link to, modify and redistribute this library
 * following the terms of license indicated below for third parties'
 * materials.
 * 
 * In case you make modified versions of this library which still include
 * said third parties' materials, you are obligated to grant this special
 * exception.
 * 
 * The complete list of Third party materials allowed with ERIKA
 * Enterprise version 3, together with the terms and conditions of each
 * license, is present in the file THIRDPARTY.TXT in the root of the
 * project.
 * ###*E*### */

/*
 * ee_kernel_k1_global.c
 *
 *  Created on: Jan 22, 2015
 *      Author: e.guidieri
 */
#include "ee_internal.h"

#if (defined(OSEE_HAS_JOBS))

StatusType osEE_k1_activate_job ( OsEE_job_id job_id, mOS_vcore_set_t core_mask,
  CoreIdType requiring_core
#if (defined(OSEE_K1_FULL_PREEMPTION))
  , OsEE_bool preemption_point
#endif /* OSEE_K1_FULL_PREEMPTION */
  )
{
  StatusType         status_type;
  OsEE_reg           i, core_counts;
  TaskType           local_task_attendee[OSEE_K1_CORE_NUMBER];
  OsEE_JOB         * const p_curr_job    = &KCB_WJ.jobs[job_id];
  OsEE_reg           const core_mask_bs  = __k1_cbs(core_mask);

  /* Lock The Core */
  osEE_lock_kernel();

  /* check preconditions */
  for ( i = core_counts = 0U; (i < OSEE_K1_CORE_NUMBER) &&
    (core_counts < core_mask_bs); ++i )
  {
    TaskType task_id  = p_curr_job->task_attendees_id[i];
    if ( task_id != INVALID_TASK ) {
      OsEE_TDB * const p_act = &KDB_WJ.tdb_array[task_id];
      if ( p_act->p_tcb->current_num_of_act < p_act->max_num_of_act ) {
        ++core_counts;
        local_task_attendee[i] = task_id;
      } else {
        local_task_attendee[i] = INVALID_TASK;
      }
    }
  }

  /* If preconditions are full-filled Activate all the job TASks */
  if ( core_counts >= core_mask_bs ) {
    /* Get the Job lock */
    __k1_fspinlock_lock(&p_curr_job->lock);
    p_curr_job->attendee_mask = 0U;
    for ( i = 0U; i < core_mask_bs; ++i ) {
      TaskType task_id = local_task_attendee[i];
      if ( task_id != INVALID_TASK ) {
        OsEE_TDB * const p_act = &KDB_WJ.tdb_array[task_id];

        /* Register the TASK as belonging to the JOB */
        KCB_WJ.tid_to_job[task_id] = p_curr_job;
        p_curr_job->attendee_mask |= OSEE_BIT(OsEE_reg,i);

        /* Prepare TASK */
        if ( p_act->p_tcb->status == OSEE_TASK_SUSPENDED ) {
          p_act->p_tcb->status = OSEE_TASK_READY;
        }
        ++p_act->p_tcb->current_num_of_act;

        osEE_scheduler_rq_insert(&KCB_WJ.kcb.rq,
          osEE_sn_alloc(&KCB_WJ.kcb.p_free_sn), p_act);
      }
    }
    /* Reset the Terminated Task Mask */
    p_curr_job->terminated_task_mask = 0U;

    /* Commit all the changes in memory */
    osEE_k1_wmb();
    /* Release the Job lock */
    __k1_fspinlock_unlock(&p_curr_job->lock);
    status_type = E_OK;
  } else {
    status_type = E_OS_LIMIT;
  }
  /* Unlock the Kernel */
  osEE_unlock_kernel();

  /* Raise an interrupt on all cores if:
   * * The job activation has been successful
   */
  if ( status_type == E_OK ) {
    osEE_hal_signal_broadcast();
  }

  return status_type;
}

StatusType SignalValue (BlockableValueTypeRef BlockableValueRef,
  ValueType Value)
{
  StatusType     status_type;
  if ( BlockableValueRef == NULL ) {
    status_type = E_OS_PARAM_POINTER;
  } else {
    __k1_uint32_t  p_bq_temp;
    OsEE_SN    *   p_blocked_queue;

    __k1_fspinlock_lock(&BlockableValueRef->lock);

    __k1_umem_write32(&BlockableValueRef->value, Value);

    p_bq_temp       = __k1_umem_read32(&BlockableValueRef->blocked_queue);
    p_blocked_queue = (OsEE_SN *)p_bq_temp;

    if ( p_blocked_queue != NULL ) {
      OsEE_bool             cond_result;
      OsEE_wait_cond  const wait_cond =
        __k1_umem_read32(&BlockableValueRef->wait_cond);
      OsEE_reg        const right_value =
        __k1_umem_read32(&BlockableValueRef->right_value);

      status_type = CheckCondition(&cond_result, Value, wait_cond, right_value);

      if ( (status_type == E_OK) && cond_result ) {
        OsEE_bool         is_preemption;
        OsEE_KDB  * const p_kdb = osEE_get_kernel();
        OsEE_CDB  * const p_cdb = osEE_get_curr_core();

        /* Pop from the blocked queue */
        __k1_umem_write32(&BlockableValueRef->blocked_queue,
          (__k1_uint32_t)BlockableValueRef->blocked_queue->p_next);

        /* Release the TASK and (SN) */
        is_preemption = osEE_scheduler_task_unblocked (
          p_kdb, p_cdb, p_blocked_queue);

        __k1_fspinlock_unlock(&BlockableValueRef->lock);

        if ( is_preemption ) {
          osEE_k1_optimized_task_preemption_point();
        }
      } else {
        __k1_fspinlock_unlock(&BlockableValueRef->lock);
      }
    } else {
      __k1_fspinlock_unlock(&BlockableValueRef->lock);
      status_type = E_OK;
    }
  }
  return status_type;
}

//#define OSEE_K1_DISABLE_OPT_PREEMPT
#if (!defined(OSEE_K1_DISABLE_OPT_PREEMPT))
#if (defined(OSEE_RQ_MULTIQUEUE))
void osEE_k1_optimized_task_preemption_point ( void ) {
  OsEE_SN         *       p_rq_first;
  OsEE_rq_mask            rq_msk;
  MemSize                 max_queue;
  OsEE_RQ         *       p_rq;
  OsEE_rq_queue   *       p_rq_queue;

  OsEE_KDB_WJ * const p_kdb  = (OsEE_KDB_WJ *)osEE_get_kernel();
  OsEE_KCB_WJ * const p_kcb  = p_kdb->p_kcb_wj;
  OsEE_CDB    * const p_cdb  = osEE_get_curr_core();
  OsEE_CCB    * const p_ccb  = p_cdb->p_ccb;

  /* Lock the Scheduler */
  __k1_fspinlock_lock(&p_kcb->lock);
  p_rq        = &p_kcb->kcb.rq;
  rq_msk      = __k1_umem_read32(&p_rq->mask);
  max_queue   = osEE_hal_get_msb(rq_msk);
  p_rq_queue  = (max_queue != OSEE_RQ_MASK_EMPTY)?
                  &p_rq->queue[max_queue]:
                  NULL;
  p_rq_first  = (p_rq_queue != NULL)?
                  (OsEE_SN *)__k1_umem_read32(&p_rq_queue->p_head):
                  NULL;

  p_rq_first      = (OsEE_SN *)__k1_umem_read32(&p_kcb->kcb.rq);

  if ( p_rq_first != NULL ) {
    OsEE_TDB  * const p_rq_first_tdb  =
      (OsEE_TDB *)__k1_umem_read32(&p_rq_first->p_tdb);

    OsEE_TCB  * const p_rq_first_tcb  = p_rq_first_tdb->p_tcb;
    OsEE_TDB  * const p_curr          =
      (OsEE_TDB *)__k1_umem_read32(&p_ccb->p_curr);

    TaskPrio    const rq_current_prio =
      __k1_umem_read32(&p_rq_first_tcb->current_prio);

    OsEE_bool   const is_preemption   =
     (rq_current_prio > __k1_umem_read32(&p_curr->p_tcb->current_prio));

    /* If there'is preemption: schedule */
    if ( is_preemption ) {
      OsEE_SN * const  p_stk_sn =
        (OsEE_SN *)__k1_umem_read32(&p_ccb->p_stk_sn);
      OsEE_SN * const  p_rq_tail =
        (OsEE_SN *)__k1_umem_read32(&p_rq_queue->p_tail);

      p_curr->p_tcb->status           = OSEE_TASK_READY_STACKED;

      /* Extract from ready queue */
      if (p_rq_first == p_rq_tail) {
        /* Prio RQ became empty */
        p_rq_queue->p_head = NULL;
        /* N.B. The following evicted for optimization */
        /* p_rq_queue->p_tail = NULL; */
        /* Adjust the Multiqueue Mask */
        p_rq->mask = (rq_msk & (~((OsEE_rq_mask)(1U << max_queue))));
      } else {
        OsEE_SN * const  p_rq_next =
          (OsEE_SN *)__k1_umem_read32(&p_rq_first->p_next);
        p_rq_queue->p_head = p_rq_next;
      }

      /* Set as current */
      p_rq_first->p_next              = NULL;
      p_ccb->p_stk_sn                 = p_rq_first;
      p_ccb->p_curr                   = p_rq_first_tdb;

      p_rq_first_tcb->current_core_id = osEE_get_curr_core_id();

      /* Adjust actual priority with dispatch priority: if needed */
      if ( rq_current_prio < p_rq_first_tdb->dispatch_prio ) {
        p_rq_first_tcb->current_prio = p_rq_first_tdb->dispatch_prio;
      }

      /* Reinsert in RQ */
      if ( p_stk_sn != NULL ) {
        OsEE_TDB  * const p_stk_tdb =
          (OsEE_TDB *)__k1_umem_read32(&p_stk_sn->p_tdb);
        OsEE_TCB      * const p_stk_tcb = p_stk_tdb->p_tcb;
        MemSize         const stk_index =
          (MemSize)__k1_umem_read32(&p_stk_tcb->current_prio);
        OsEE_rq_queue * const p_stk_rq_queue = &p_rq->queue[stk_index];
        OsEE_SN       * const p_stk_rq_head =
          (OsEE_SN *)__k1_umem_read32(&p_stk_rq_queue->p_head);

        if ( p_stk_rq_head == NULL ) {
          OsEE_rq_mask const stk_rq_msk =
            (OsEE_rq_mask)__k1_umem_read32(&p_rq->mask);

          /* Insertion in Empty Prio Queue */
          p_stk_rq_queue->p_head  = p_stk_sn;
          p_stk_rq_queue->p_tail  = p_stk_sn;

          /* Set Multiqueue Mask */
          p_rq->mask = stk_rq_msk | ((OsEE_rq_mask)(1U << stk_index));
        } else {
          p_stk_rq_queue->p_tail  = p_stk_sn;
        }

        osEE_hal_signal_broadcast();
      }

      /* Full memory barrier: commit data in memory + cache invalidation */
      osEE_k1_mb();

      /* YOU HAD NOT TO RELESE THE KERNEL HERE IS A GLOBAL QUEUE NEED TO BE
       * RELEASED AFTER ACTUAL CONTEXT CHANGE */

      osEE_change_context_from_running(p_curr, p_rq_first_tdb);
    } else {
      __k1_fspinlock_unlock(&p_kcb->lock);
    }
  } else {
    __k1_fspinlock_unlock(&p_kcb->lock);
  }
}
#else
void osEE_k1_optimized_task_preemption_point ( void ) {
  OsEE_SN     *       p_rq_first;
  OsEE_KDB_WJ * const p_kdb  = (OsEE_KDB_WJ *)osEE_get_kernel();
  OsEE_KCB_WJ * const p_kcb  = p_kdb->p_kcb_wj;
  OsEE_CDB    * const p_cdb  = osEE_get_curr_core();
  OsEE_CCB    * const p_ccb  = p_cdb->p_ccb;

  /* Lock the Scheduler */
  __k1_fspinlock_lock(&p_kcb->lock);

  p_rq_first      = (OsEE_SN *)__k1_umem_read32(&p_kcb->kcb.rq);

  if ( p_rq_first != NULL ) {
    OsEE_TDB  * const p_rq_first_tdb  =
      (OsEE_TDB *)__k1_umem_read32(&p_rq_first->p_tdb);

    OsEE_TCB  * const p_rq_first_tcb  = p_rq_first_tdb->p_tcb;
    OsEE_TDB  * const p_curr          =
      (OsEE_TDB *)__k1_umem_read32(&p_ccb->p_curr);

    TaskPrio    const rq_current_prio =
      __k1_umem_read32(&p_rq_first_tcb->current_prio);

    OsEE_bool   const is_preemption   =
     (rq_current_prio > __k1_umem_read32(&p_curr->p_tcb->current_prio));

    /* If there'is preemption: schedule */
    if ( is_preemption ) {
      OsEE_SN * const  p_stk_sn =
        (OsEE_SN *)__k1_umem_read32(&p_ccb->p_stk_sn);

      p_curr->p_tcb->status           = OSEE_TASK_READY_STACKED;

      /* Extract from ready queue */
      p_kcb->kcb.rq  = (OsEE_SN *)__k1_umem_read32(&p_rq_first->p_next);

      /* Set as current */
      p_rq_first->p_next              = NULL;
      p_ccb->p_stk_sn                 = p_rq_first;
      p_ccb->p_curr                   = p_rq_first_tdb;

      p_rq_first_tcb->current_core_id = osEE_get_curr_core_id();

      /* Adjust actual priority with dispatch priority: if needed */
      if ( rq_current_prio < p_rq_first_tdb->dispatch_prio ) {
        p_rq_first_tcb->current_prio = p_rq_first_tdb->dispatch_prio;
      }

      /* Reinsert in RQ */
      if ( p_stk_sn != NULL ) {
        (void)osEE_k1_umem_data_priority_insert(&p_kcb->kcb.rq,
            p_stk_sn);
        osEE_hal_signal_broadcast();
      }

      /* Full memory barrier: commit data in memory + cache invalidation */
      osEE_k1_mb();

      /* YOU HAD NOT TO RELESE THE KERNEL HERE IS A GLOBAL QUEUE NEED TO BE
       * RELEASED AFTER ACTUAL CONTEXT CHANGE */

      osEE_change_context_from_running(p_curr, p_rq_first_tdb);
    } else {
      __k1_fspinlock_unlock(&p_kcb->lock);
    }
  } else {
    __k1_fspinlock_unlock(&p_kcb->lock);
  }
}
#endif /* OSEE_RQ_MULTIQUEUE */
#else
void osEE_k1_optimized_task_preemption_point ( void ) {
  /* TODO: Not yet implemented */
  osEE_scheduler_task_preemption_point(osEE_get_kernel(), osEE_get_curr_core());
}
#endif

#endif /* OSEE_HAS_JOBS */
