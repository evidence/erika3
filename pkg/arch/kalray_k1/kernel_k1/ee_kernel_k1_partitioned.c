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
 * ee_kernel_k1_partitioned.c
 *
 *  Created on: Jan 22, 2015
 *      Author: e.guidieri
 */
#include "ee_k1_vbsp.h"
#include "ee_hal_internal.h"
#include "ee_kernel.h"
#include <assert.h>
#include "ee_kernel_k1.h"

#if (defined(OSEE_HAS_JOBS))

StatusType osEE_k1_activate_job ( OsEE_job_id job_id, mOS_vcore_set_t core_mask,
  CoreIdType requiring_core
#if (defined(OSEE_K1_FULL_PREEMPTION))
  , OsEE_bool preemption_point
#endif /* OSEE_K1_FULL_PREEMPTION */
  )
{
  StatusType       status_type;
  size_t           i, core_counts;
  mOS_vcore_set_t  signalAttendeeMask = 0U;
  OsEE_reg         core_mask_bs       = __k1_cbs(core_mask);

  struct {
    TaskType  tid;
    OsEE_bool preemption;
  } local_task_attendee[OSEE_K1_CORE_NUMBER] =
    { [0U ... (OSEE_K1_CORE_NUMBER -1U)] = { INVALID_TASK, OSEE_FALSE } };

  OsEE_JOB  * const p_curr_job  = &KCB_WJ.jobs[job_id];

  /* Lock All the Cores that attend to a Job and check preconditions */
  for ( i = core_counts = 0U; i < OSEE_K1_CORE_NUMBER; ++i ) {
    if ( (core_mask & OSEE_BIT(mOS_vcore_set_t, i)) != 0 ) {
      TaskType task_id  = p_curr_job->task_attendees_id[i];
      if ( task_id != INVALID_TASK ) {
        OsEE_TDB *         p_act;
        __k1_fspinlock_lock( &KCB_WJ.core_ctrls[i].lock );

        p_act = &KDB_WJ.tdb_array[task_id];
        if ( p_act->p_tcb->current_num_of_act < p_act->max_num_of_act ) {
          ++core_counts;
          local_task_attendee[i].tid = task_id;
        }
      }
    }
  }

  /* If preconditions are full-filled Activate all the job TASks */
  if ( core_counts >= core_mask_bs ) {
    /* Get the Job lock */
    __k1_fspinlock_lock(&p_curr_job->lock);
    p_curr_job->attendee_mask = 0U;
    for ( i = 0U; (i < OSEE_K1_CORE_NUMBER) && (core_mask_bs > 0U); ++i ) {
      TaskType task_id = local_task_attendee[i].tid;
      if ( task_id != INVALID_TASK ) {
        OsEE_CCB  * const p_ccb = &KCB_WJ.core_ctrls[i].ccb;
        OsEE_TDB  * const p_act = &KDB_WJ.tdb_array[task_id];

        /* Got a TASK*/
        --core_mask_bs;

        /* Register the TASK as belonging to the JOB */
        KCB_WJ.tid_to_job[task_id] = p_curr_job;
        p_curr_job->attendee_mask |= OSEE_BIT(OsEE_reg,i);

        /* Prepare TASK */
        if ( p_act->p_tcb->status == OSEE_TASK_SUSPENDED ) {
          p_act->p_tcb->status = OSEE_TASK_READY;
        }
        ++p_act->p_tcb->current_num_of_act;

        if (
            osEE_scheduler_rq_insert(&p_ccb->rq,
                osEE_sn_alloc(&p_ccb->p_free_sn), p_act)
        ) {
          local_task_attendee[i].preemption =
            (p_ccb->p_curr->p_tcb->current_prio < p_act->p_tcb->current_prio);
        }
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

  /* Free All the Cores that attend to a Job And Notify each attendee core */
  for ( i = 0U; (i < OSEE_K1_CORE_NUMBER) && (core_counts > 0U) ; ++i ) {
    if ( local_task_attendee[i].tid != INVALID_TASK ) {
      --core_counts;
      __k1_fspinlock_unlock( &KCB_WJ.core_ctrls[i].lock );
      /* Raise an interrupt on the receiving core if:
       * * The job activation has been successful
       * * The interrupt receiving core is no the activation requiring core.
       * * The job activation has preempted the actual execution TASK in
       *   receiving core (otherwise the interrupt is just waste of time).
       */
      if ( (status_type == E_OK) && (i != requiring_core) &&
         local_task_attendee[i].preemption )
      {
        signalAttendeeMask |= (1U << i);
      }
    }
  }
  /* Raise an interrupt on the receiving core if:
   * * The job activation has been successful
   * * The interrupt receiving core is no the activation requiring core.
   * * The job activation has preempted the actual execution TASK in
   *   receiving core (otherwise the interrupt is just waste of time).
   */
  if ( status_type == E_OK ) {
#if (!defined(OSEE_K1_FULL_PREEMPTION))
    bsp_inter_pe_event_notify(signalAttendeeMask, BSP_IT_LINE);
#else
    if ( preemption_point ) {
      bsp_inter_pe_interrupt_raise(signalAttendeeMask, BSP_IT_LINE);
    } else {
      bsp_inter_pe_event_notify(signalAttendeeMask, BSP_IT_LINE);
    }
#endif /* !OSEE_K1_FULL_PREEMPTION */
  }

  return status_type;
}

static StatusType osEE_k1_signal_value ( OsEE_blockable_value *
  blockable_value_ref, OsEE_bool * is_preemption_ref )
{
  StatusType     status_type;
  if ( (blockable_value_ref == NULL) || (is_preemption_ref == NULL) ) {
    status_type = E_OS_PARAM_POINTER;
  } else {
    __k1_uint32_t  p_bq_temp;
    OsEE_SN *      blocked_queue;

    p_bq_temp       = __k1_umem_read32(&blockable_value_ref->blocked_queue);
    blocked_queue = (OsEE_SN *)p_bq_temp;

    /* check if the post on the semaphore wakes up someone */
    if ( blocked_queue != NULL ) {
      CoreIdType  const core_id  = blocked_queue->p_tdb->orig_core_id;
      OsEE_CDB *  const p_cdb    = osEE_get_core(core_id);

      /* Pop from the blocked queue */
      __k1_umem_write32(&blockable_value_ref->blocked_queue,
        (__k1_uint32_t)blockable_value_ref->blocked_queue->p_next);

      /* Release the TASK (and the SN) */
      (*is_preemption_ref) = osEE_scheduler_task_unblocked (
        osEE_get_kernel(), p_cdb, blocked_queue);

      if ( (*is_preemption_ref) ) {
        osEE_hal_signal_core(core_id);
      }
      status_type = E_OK;
    } else {
      status_type = E_OS_PARAM_POINTER;
    }
  }
  return status_type;
}

StatusType SignalValue (BlockableValueTypeRef BlockableValueRef,
  ValueType Value)
{
  StatusType     status_type;
  OsEE_bool      is_preemption = OSEE_FALSE;

  if ( BlockableValueRef == NULL ) {
    status_type = E_OS_PARAM_POINTER;
  } else
  {
    __k1_uint32_t  p_bq_temp;
    OsEE_SN    *   p_blocked_queue;
    CoreIdType     orig_core_id;

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
        status_type  = osEE_k1_signal_value(BlockableValueRef, &is_preemption);
      }

      if ( status_type == E_OK ) {
        orig_core_id = p_blocked_queue->p_tdb->orig_core_id;
      } else {
        orig_core_id = ((CoreIdType)-1);
      }
    } else {
      orig_core_id = ((CoreIdType)-1);
      status_type = E_OK;
    }
    __k1_fspinlock_unlock(&BlockableValueRef->lock);

    /* Preemption point */
    if ( is_preemption && (osEE_get_curr_core_id() == orig_core_id) ) {
      osEE_k1_optimized_task_preemption_point();
    }
  }
  return status_type;
}

//#define OSEE_K1_DISABLE_OPT_PREEMPT
#if (!defined(OSEE_K1_DISABLE_OPT_PREEMPT))
#if (defined(OSEE_RQ_MULTIQUEUE))
void osEE_k1_optimized_task_preemption_point ( void )
{
  OsEE_SN         *       p_rq_first;
  OsEE_rq_mask            rq_msk;
  MemSize                 max_queue;
  OsEE_RQ         *       p_rq;
  OsEE_rq_queue   *       p_rq_queue;

  OsEE_CDB        * const p_cdb     = osEE_get_curr_core();
  OsEE_CCB_WL     * const p_ccb     = (OsEE_CCB_WL *)p_cdb->p_ccb;

  /* Lock the Scheduler */
  __k1_fspinlock_lock(&p_ccb->lock);

  p_rq        = &p_ccb->ccb.rq;
  rq_msk      = __k1_umem_read32(&p_rq->mask);
  max_queue   = osEE_hal_get_msb(rq_msk);
  p_rq_queue  = (max_queue != OSEE_RQ_MASK_EMPTY)?
                  &p_rq->queue[max_queue]:
                  NULL;
  p_rq_first  = (p_rq_queue != NULL)?
                  (OsEE_SN *)__k1_umem_read32(&p_rq_queue->p_head):
                  NULL;

  if ( p_rq_first != NULL ) {
    OsEE_TDB * const  p_rq_first_tdb  =
      (OsEE_TDB *)__k1_umem_read32(&p_rq_first->p_tdb);

    OsEE_TCB * const  p_rq_first_tcb  = p_rq_first_tdb->p_tcb;

    OsEE_TDB * const  p_curr          =
      (OsEE_TDB *)__k1_umem_read32(&p_ccb->ccb.p_curr);

    TaskPrio   const  rq_current_prio =
      __k1_umem_read32(&p_rq_first_tcb->current_prio);

    OsEE_bool  const  is_preemption   =
      (rq_current_prio >
        __k1_umem_read32(&p_curr->p_tcb->current_prio));

    /* If there'is preemption: schedule */
    if ( is_preemption ) {
      OsEE_SN * const  p_stk_sn =
        (OsEE_SN *)__k1_umem_read32(&p_ccb->ccb.p_stk_sn);
      OsEE_SN * const  p_rq_tail =
        (OsEE_SN *)__k1_umem_read32(&p_rq_queue->p_tail);

      p_curr->p_tcb->status              = OSEE_TASK_READY_STACKED;

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

      /* Set as current. In partitioned scheduler the TASK are stacked */
      p_rq_first->p_next                 = p_stk_sn;
      p_ccb->ccb.p_stk_sn                = p_rq_first;
      p_ccb->ccb.p_curr                  = p_rq_first_tdb;

      /* Adjust actual priority with dispatch priority: if needed */
      if ( rq_current_prio < p_rq_first_tdb->dispatch_prio ) {
        p_rq_first_tcb->current_prio = p_rq_first_tdb->dispatch_prio;
      }

      /* Full memory barrier: commit data in memory + cache invalidation */
      osEE_k1_mb();
      __k1_fspinlock_unlock(&p_ccb->lock);

      osEE_change_context_from_running(p_curr, p_rq_first_tdb);
    } else {
      __k1_fspinlock_unlock(&p_ccb->lock);
    }
  } else {
    __k1_fspinlock_unlock(&p_ccb->lock);
  }
}
#else
void osEE_k1_optimized_task_preemption_point ( void )
{
  OsEE_SN         *        p_rq_first;
  OsEE_CDB        * const  p_cdb  = osEE_get_curr_core();
  OsEE_CCB_WL     * const  p_ccb  = (OsEE_CCB_WL *)p_cdb->p_ccb;

  /* Lock the Scheduler */
  __k1_fspinlock_lock(&p_ccb->lock);

  p_rq_first      = (OsEE_SN *)__k1_umem_read32(&p_ccb->ccb.rq);

  if ( p_rq_first != NULL ) {
    OsEE_TDB * const  p_rq_first_tdb  =
      (OsEE_TDB *)__k1_umem_read32(&p_rq_first->p_tdb);

    OsEE_TCB * const  p_rq_first_tcb  = p_rq_first_tdb->p_tcb;

    OsEE_TDB * const  p_curr          =
      (OsEE_TDB *)__k1_umem_read32(&p_ccb->ccb.p_curr);

    TaskPrio   const  rq_current_prio =
      __k1_umem_read32(&p_rq_first_tcb->current_prio);

    OsEE_bool  const  is_preemption   =
      (rq_current_prio >
        __k1_umem_read32(&p_curr->p_tcb->current_prio));

    /* If there'is preemption: schedule */
    if ( is_preemption ) {
      OsEE_SN * const  p_stk_sn =
        (OsEE_SN *)__k1_umem_read32(&p_ccb->ccb.p_stk_sn);

      p_curr->p_tcb->status              = OSEE_TASK_READY_STACKED;

      /* Extract from ready queue */
      p_ccb->ccb.rq  = (OsEE_SN *)__k1_umem_read32(&p_rq_first->p_next);

      /* Set as current. In partitioned scheduler the TASK are stacked */
      p_rq_first->p_next                 = p_stk_sn;
      p_ccb->ccb.p_stk_sn                = p_rq_first;
      p_ccb->ccb.p_curr                  = p_rq_first_tdb;

      /* Adjust actual priority with dispatch priority: if needed */
      if ( rq_current_prio < p_rq_first_tdb->dispatch_prio ) {
        p_rq_first_tcb->current_prio = p_rq_first_tdb->dispatch_prio;
      }

      /* Full memory barrier: commit data in memory + cache invalidation */
      osEE_k1_mb();
      __k1_fspinlock_unlock(&p_ccb->lock);

      osEE_change_context_from_running(p_curr, p_rq_first_tdb);
    } else {
      __k1_fspinlock_unlock(&p_ccb->lock);
    }
  } else {
    __k1_fspinlock_unlock(&p_ccb->lock);
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
