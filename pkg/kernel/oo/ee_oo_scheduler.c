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

/** \file   ee_sched_partitioned.c
 *  \brief  OSEK Kernel Partitioned Scheduler.
 *
 *  This files contains the implementation of OSEK Kernel Partitioned Scheduler
 *  in Erika Enterprise.
 *
 *  \note   TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2016
 */

#include "ee_internal.h"

static FUNC(void, OS_CODE)
  osEE_scheduler_stk_next
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb,
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)  p_rq_sn
)
{
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_tdb = p_rq_sn->p_tdb;
  CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA) p_tcb = p_tdb->p_tcb;
  /* Set as current on top of STK */
#if (defined(OSEE_ALLOW_TASK_MIGRATION))
  /* N.B. The Handling of the preempted SN as Stacked or re-inserted in RQ
   * is done by the calling function */
  p_rq_sn->p_next               = NULL;
  p_tcb->current_core_id        = osEE_get_curr_core_id();
#else
  p_rq_sn->p_next               = p_ccb->p_stk_sn;
#endif /* OSEE_ALLOW_TASK_MIGRATION */
  p_ccb->p_stk_sn               = p_rq_sn;
  p_ccb->p_curr                 = p_tdb;

  /* Adjust actual priority with dispatch priority: if needed */
  {
    CONST(TaskPrio, AUTOMATIC)
      dispatch_prio = p_tdb->dispatch_prio;
    if (p_tcb->current_prio < dispatch_prio) {
      p_tcb->current_prio = dispatch_prio;
    }
  }
}

#if (defined(OSEE_RQ_MULTIQUEUE))

OSEE_STATIC_ASSERT((sizeof(OsEE_rq_mask) * CHAR_BIT) >= OSEE_RQ_PRIO_NUM,
    RQ_mask_not_big_enough)

FUNC(OsEE_bool, OS_CODE)
  osEE_scheduler_rq_insert
(
  P2VAR(OsEE_RQ, AUTOMATIC, OS_APPL_DATA)       p_rq,
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)       p_sn_new,
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_tdb_new
)
{
  VAR(OsEE_bool, AUTOMATIC)
    head_changed = OSEE_FALSE;
  CONST(MemSize, AUTOMATIC)
    queue_index = (p_tdb_new->ready_prio - 1U);
  CONSTP2VAR(OsEE_rq_queue, AUTOMATIC, OS_APPL_DATA)
    p_rq_queue = &p_rq->queue[queue_index];

  p_sn_new->p_tdb = p_tdb_new;

  if (p_rq_queue->p_head == NULL) {
    CONST(MemSize, AUTOMATIC) max_queue = osEE_hal_get_msb(p_rq->mask);
    /* Insertion in Empty Prio Queue */
    p_rq_queue->p_head  = p_sn_new;
    p_rq_queue->p_tail  = p_sn_new;

    /* Set Multiqueue Mask */
    p_rq->mask         |= ((OsEE_rq_mask)(1U << queue_index));

    if ((max_queue == OSEE_RQ_MASK_EMPTY) || (max_queue < queue_index)) {
      head_changed = OSEE_TRUE;
    }
  } else {
    /* Append the new SN at priority queue tail */
    p_rq_queue->p_tail->p_next  = p_sn_new;
    p_rq_queue->p_tail          = p_sn_new;
  }

  return head_changed;
}

FUNC_P2VAR(OsEE_preempt, OS_APPL_DATA, OS_CODE)
  osEE_scheduler_core_rq_preempt_stk
(
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_RQ,  AUTOMATIC, OS_APPL_DATA)  p_rq
)
{
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)
    p_ccb = p_cdb->p_ccb;
  CONST(MemSize, AUTOMATIC)
    max_queue = osEE_hal_get_msb(p_rq->mask);
  CONSTP2VAR(OsEE_rq_queue, AUTOMATIC, OS_APPL_DATA)
    p_rq_queue = (max_queue != OSEE_RQ_MASK_EMPTY)?
      &p_rq->queue[max_queue]:
      NULL;
  CONSTP2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
    p_rq_sn  = (p_rq_queue != NULL)?
      p_rq_queue->p_head:
      NULL;
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
    p_ret_sn = p_ccb->p_stk_sn;
  VAR(OsEE_bool, AUTOMATIC)
    is_rq_preemption = OSEE_FALSE;
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
    p_ret_tdb;

  if (p_ret_sn != NULL) {
    p_ret_tdb = p_ret_sn->p_tdb;
    if (p_rq_sn != NULL) {
      CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)
        p_ret_tcb = p_ret_tdb->p_tcb;
      /* Queue Index + 1U is equal to TASK ready (current) priority */
      if (p_ret_tcb->current_prio < (max_queue + 1U))
      {
        /* RQ preempt STK */
        p_ret_tcb->status = OSEE_TASK_READY_STACKED;
        is_rq_preemption  = OSEE_TRUE;
      }
    }
  } else if (p_rq_sn != NULL) {
    /* Only Idle TASK stacked -> RQ preempt STK. */
    /* Don't use p_ccb->p_curr, is not reliable here,
     * It points to the terminated TASK, we are still evaluating
     * the next one. */
    /* Call PostTaskHook before switching active TASK */
    osEE_call_post_task_hook(p_ccb);
    p_ret_tdb                 = p_cdb->p_idle_task;
    p_ret_tdb->p_tcb->status  = OSEE_TASK_READY_STACKED;
    is_rq_preemption          = OSEE_TRUE;
  }

  if (is_rq_preemption) {
    /* Extract from ready queue */
    if (p_rq_queue->p_head == p_rq_queue->p_tail) {
      /* Prio RQ became empty */
      p_rq_queue->p_head = NULL;
      /* N.B. The following evicted for optimization */
      /* p_rq_queue->p_tail = NULL; */
      /* Adjust the Multiqueue Mask */
      p_rq->mask &= (~((OsEE_rq_mask)(1U << max_queue)));
    } else {
      /* Pop the current priority queue head */
      p_rq_queue->p_head = p_rq_queue->p_head->p_next;
    }

    /* Set as current on top of STK */
    osEE_scheduler_stk_next(p_ccb, p_rq_sn);
  } else {
    p_ret_tdb = NULL;
    p_ret_sn  = NULL;
  }

#if (defined(OSEE_ALLOW_TASK_MIGRATION))
  return p_ret_sn;
#else
  return p_ret_tdb;
#endif /* OSEE_ALLOW_TASK_MIGRATION */
}
#else
FUNC(OsEE_bool, OS_CODE)
  osEE_scheduler_rq_insert
(
  P2VAR(OsEE_RQ, AUTOMATIC, OS_APPL_DATA)       p_rq,
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)       p_sn_new,
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_tdb_new
)
{
  p_sn_new->p_tdb = p_tdb_new;

#if (!defined(OSEE_SCHEDULER_GLOBAL))
  return osEE_sn_priority_insert(p_rq, p_sn_new, OSEE_TRUE);
#else
  return osEE_sn_priority_insert(p_rq, p_sn_new, OSEE_FALSE);
#endif /* !OSEE_SCHEDULER_GLOBAL */
}

FUNC_P2VAR(OsEE_preempt, OS_APPL_DATA, OS_CODE)
  osEE_scheduler_core_rq_preempt_stk
(
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_RQ,  AUTOMATIC, OS_APPL_DATA)  p_rq
)
{
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb = p_cdb->p_ccb;
  CONSTP2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)  p_rq_sn  = (*p_rq);
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)       p_ret_sn = p_ccb->p_stk_sn;

  VAR(OsEE_bool, AUTOMATIC)                     is_rq_preemption = OSEE_FALSE;
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)      p_ret_tdb;

  if (p_ret_sn != NULL) {
    p_ret_tdb = p_ret_sn->p_tdb;
    if (p_rq_sn != NULL) {
      CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)
        p_ret_tcb = p_ret_tdb->p_tcb;
      if (p_ret_tcb->current_prio <
        p_rq_sn->p_tdb->p_tcb->current_prio)
      {
        /* RQ preempt STK */
        /* Call PostTaskHook before switching active TASK */
        osEE_call_post_task_hook(p_ccb);

        p_ret_tcb->status = OSEE_TASK_READY_STACKED;
        is_rq_preemption  = OSEE_TRUE;
      }
    }
  } else if (p_rq_sn != NULL) {
    /* Only Idle TASK stacked -> RQ preempt STK. */
    /* Don't use p_ccb->p_curr, is not reliable here,
     * It points to the terminated TASK, we are still evaluating
     * the next one. */
    /* Call PostTaskHook before switching active TASK */
    osEE_call_post_task_hook(p_ccb);
    p_ret_tdb                 = p_cdb->p_idle_task;
    p_ret_tdb->p_tcb->status  = OSEE_TASK_READY_STACKED;
    is_rq_preemption          = OSEE_TRUE;
  }

  if (is_rq_preemption) {
    /* Extract from ready queue */
    (*p_rq)       = p_rq_sn->p_next;

    /* Set as current on top of STK */
    osEE_scheduler_stk_next(p_ccb, p_rq_sn);
  } else {
    p_ret_tdb = NULL;
    p_ret_sn  = NULL;
  }
#if (defined(OSEE_ALLOW_TASK_MIGRATION))
  return p_ret_sn;
#else
  return p_ret_tdb;
#endif /* OSEE_ALLOW_TASK_MIGRATION */
}

#endif /* RQ Functions Selection */

FUNC(OsEE_bool, OS_CODE)
  osEE_sn_priority_insert
(
  P2VAR(OsEE_SN *, AUTOMATIC, OS_APPL_DATA)     pp_first,
  P2VAR(OsEE_SN  , AUTOMATIC, OS_APPL_DATA)     p_sn_new,
  CONST(OsEE_bool, AUTOMATIC)                   hnd_act
)
{
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_tdb_new = p_sn_new->p_tdb;
  CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA) p_tcb_new = p_tdb_new->p_tcb;
  CONST(TaskPrio, AUTOMATIC)                new_task_prio =
    ((hnd_act) && osEE_is_active_task(p_tcb_new))?
      p_tdb_new->ready_prio:
      p_tcb_new->current_prio;
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA) p_prev          = NULL;
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA) p_curr          = (*pp_first);
  VAR(OsEE_bool, AUTOMATIC)               head_changed    = OSEE_FALSE;

  /* Traverse the queue until needed */
  while (p_curr != NULL) {
    VAR(TaskPrio, AUTOMATIC)                      prio_to_check;
    CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_cur_tdb = p_curr->p_tdb;
    CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA) p_cur_tcb = p_cur_tdb->p_tcb;

    if (hnd_act && osEE_is_active_task(p_cur_tcb)) {
      prio_to_check = p_cur_tdb->ready_prio;
    } else {
      prio_to_check = p_cur_tcb->current_prio;
    }

    if (new_task_prio <= prio_to_check)
    {
      p_prev = p_curr;
      p_curr = p_curr->p_next;
    } else {
      break;
    }
  }

  if (p_prev != NULL) {
    p_prev->p_next = p_sn_new;
  } else {
    (*pp_first)   = p_sn_new;
    head_changed  = OSEE_TRUE;
  }

  p_sn_new->p_next = p_curr;

  return head_changed;
}

FUNC_P2VAR(OsEE_SN, OS_APPL_DATA, OS_CODE)
  osEE_scheduler_core_pop_running
(
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_RQ,  AUTOMATIC, OS_APPL_DATA)  p_rq
)
{
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb         = p_cdb->p_ccb;
  CONSTP2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)  p_prev_stk_sn = p_ccb->p_stk_sn;
  CONSTP2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
    p_next_stk_sn = p_prev_stk_sn->p_next;

  /* Pop the current STK SN, if not IDLE TASK. This function MUST not be
   * called inside IDLE TASK. */
  p_ccb->p_stk_sn = p_next_stk_sn;

  /* No need to set Temporary ccb.p_curr, obtaining coherence, since
   * osEE_scheduler_core_rq_preempt_stk won't rely on that.
   * (This memory accesses optimization).
   * Moreover in this way I can call the PostTaskHook with the right value of
   * ccb.p_curr for the GetTaskID.
   * */

  {
    /* Handle if RQ preempt STK (It manipulate the core data structures) */
    CONSTP2VAR(OsEE_preempt, AUTOMATIC, OS_APPL_DATA)
      p_preempt = osEE_scheduler_core_rq_preempt_stk(p_cdb, p_rq);
    CONSTP2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
      p_curr_stk_sn = p_ccb->p_stk_sn;

    /* If not, resume current STK first */
    if (p_preempt == NULL) {
      P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)      p_tdb_stk;

#if (defined(OSEE_HAS_POSTTASKHOOK))
      /* Call PostTaskHook before switching active TASK, if the terminating
         TASK is a real TASK and not an ISR2 */
      if (p_ccb->p_curr->task_type <= OSEE_TASK_TYPE_EXTENDED) {
        osEE_call_post_task_hook(p_ccb);
      }
#endif /* OSEE_HAS_POSTTASKHOOK */

      if ( p_curr_stk_sn != NULL ) {
        /* Resume STK TASK */
        p_tdb_stk = p_curr_stk_sn->p_tdb;
      } else {
        /* Resume IDLE TASK */
        p_tdb_stk = p_cdb->p_idle_task;
      }

      p_ccb->p_curr            = p_tdb_stk;
    }
#if (defined(OSEE_ALLOW_TASK_MIGRATION))
    else if ( p_curr_stk_sn != NULL ) {
      /* Restore the STK data structures. After "preemption in termination"
         (i.e. using Preemption Code corrupt the STK queue) */
      p_curr_stk_sn->p_next = p_next_stk_sn;
    }
#endif /* OSEE_ALLOW_TASK_MIGRATION */
  }

  return p_prev_stk_sn;
}
