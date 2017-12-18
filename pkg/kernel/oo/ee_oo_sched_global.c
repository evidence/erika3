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

/** \file   ee_sched_global.c
 *  \brief  OSEK Kernel Global Scheduler.
 *
 *  This files contains the implementation of OSEK Kernel Global Scheduler in
 *  Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date    2016
 */

#include "ee_internal.h"

#if (defined(OSEE_SINGLECORE))
#error Having a global scheduler in single core environment is a nonsense
#endif

FUNC(StatusType, OS_CODE)
  osEE_scheduler_task_activated
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb_act,
  CONST(OsEE_bool, AUTOMATIC)               is_preemption_point
)
{
  VAR(StatusType, AUTOMATIC)                    ev;
  CONSTP2VAR(OsEE_KCB, AUTOMATIC, OS_APPL_DATA) p_kcb = p_kdb->p_kcb;
  CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)
    p_tcb_act  = p_tdb_act->p_tcb;

  osEE_lock_kernel();

  if ( p_tcb_act->current_num_of_act <
      p_tdb_act->max_num_of_act )
  {
    CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb = p_cdb->p_ccb;
    CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_curr = p_ccb->p_curr;

    ++p_tcb_act->current_num_of_act;

    if ((is_preemption_point) &&
        (p_curr->p_tcb->current_prio < p_tcb_act->current_prio)
       )
    {
      CONSTP2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
        p_stk_sn = p_ccb->p_stk_sn;
      /* Set the RUNNING Task as READY but Stacked (No more RUNNING) */
      p_curr->p_tcb->status = OSEE_TASK_READY_STACKED;
      if ( p_curr != p_cdb->p_idle_task ) {
        /* Re-insert preempted in RQ */
        (void)osEE_scheduler_rq_insert(&p_kcb->rq, p_stk_sn, p_curr);
        /* Ask to another idle core to take care of it... */
        osEE_hal_signal_broadcast();
      }

      /* Set the activated TASK as current */
      p_ccb->p_stk_sn             = osEE_sn_alloc(&p_kcb->p_free_sn);
      p_ccb->p_curr               = p_tdb_act;

      p_tcb_act->current_core_id  = osEE_get_curr_core_id();
      osEE_event_reset_mask(p_tcb_act);

      osEE_change_context_from_running(p_curr, p_tdb_act);
    } else {
      /* Actually Insert the activated in READY Queue */
      if ( p_tcb_act->status == OSEE_TASK_SUSPENDED ) {
        p_tcb_act->status = OSEE_TASK_READY;
        osEE_event_reset_mask(p_tcb_act);
      }
      (void)osEE_scheduler_rq_insert(&p_kcb->rq,
          osEE_sn_alloc(&p_kcb->p_free_sn), p_tdb_act);
      osEE_unlock_kernel();
      /* Let other idle cores handle it... */
      osEE_hal_signal_broadcast();
    }
    ev = E_OK;
  } else {
    osEE_unlock_kernel();
    ev = E_OS_LIMIT;
  }
  return ev;
}

FUNC_P2VAR(OsEE_TDB, OS_APPL_DATA, OS_CODE)
  osEE_scheduler_task_block_current
(
  P2VAR(OsEE_KDB,  AUTOMATIC, OS_APPL_DATA) p_kdb,
  P2VAR(OsEE_CDB,  AUTOMATIC, OS_APPL_DATA) p_cdb,
  P2VAR(OsEE_SN *, AUTOMATIC, OS_APPL_DATA) p_sn_blocked
)
{
  CONSTP2VAR(OsEE_KCB, AUTOMATIC, OS_APPL_DATA) p_kcb   = p_kdb->p_kcb;
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb   = p_cdb->p_ccb;
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_tdb_blocked  = p_ccb->p_curr;

  osEE_lock_kernel();

  (*p_sn_blocked) = osEE_scheduler_core_pop_running(p_cdb, &p_kcb->rq);

  p_tdb_blocked->p_tcb->status = OSEE_TASK_WAITING;

  /* Kernel Unlocking Postponed */
  return p_ccb->p_curr;
}

FUNC(OsEE_bool, OS_CODE)
  osEE_scheduler_task_unblocked
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_SN,  AUTOMATIC, OS_APPL_DATA)  p_sn_released
)
{
  VAR(OsEE_bool, AUTOMATIC) rq_head_changed;
  VAR(OsEE_bool, AUTOMATIC) is_preemption = OSEE_FALSE;
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
    p_tdb_released = p_sn_released->p_tdb;
  CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)
    p_tcb_released = p_tdb_released->p_tcb;

  osEE_lock_kernel();

  p_tcb_released->status        = OSEE_TASK_READY_STACKED;
  p_tcb_released->current_prio  = p_tdb_released->ready_prio;

  rq_head_changed = osEE_scheduler_rq_insert(&p_kdb->p_kcb->rq,
      p_sn_released, p_tdb_released);

  osEE_unlock_kernel();

  if ( rq_head_changed == OSEE_TRUE ) {
    is_preemption = (p_tdb_released->p_tcb->current_prio >
      p_cdb->p_ccb->p_curr->p_tcb->current_prio);
  }

  /* If the unlocked Task has priority do not signal, the blocking primitive is
     supposed to try a preemption */
  if ( is_preemption == OSEE_FALSE ) {
    osEE_hal_signal_broadcast();
  }
  return is_preemption;
}

FUNC_P2VAR(OsEE_TDB, OS_APPL_DATA, OS_CODE)
  osEE_scheduler_task_terminated
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)    p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)    p_cdb,
  P2VAR(OsEE_TDB *, AUTOMATIC, OS_APPL_DATA)  pp_tdb_from
)
{
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb = p_cdb->p_ccb;
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)      p_tdb_to;

  /* Lock the Scheduler */
  osEE_lock_kernel();
  {
    CONSTP2VAR(OsEE_KCB, AUTOMATIC, OS_APPL_DATA)
      p_kcb = p_kdb->p_kcb;
    CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
      p_tdb_term = p_ccb->p_curr;
    CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)
      p_tcb_term = p_tdb_term->p_tcb;

    /* Prepare the "TDB from" return value */
    (*pp_tdb_from) = p_tdb_term;

    if (p_tcb_term->status == OSEE_TASK_RUNNING) {
      /* Normal Termination */
      CONSTP2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
        p_sn_term = osEE_scheduler_core_pop_running(p_cdb, &p_kcb->rq);

      p_tdb_to = p_ccb->p_curr;

      osEE_task_end(p_tdb_term);
      /* In Normal Termination => SN released */
      osEE_sn_release(&p_kcb->p_free_sn, p_sn_term);
    } else {
      /* Handle ChainTask */
      CONSTP2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
        p_sn_term = p_ccb->p_stk_sn;

      /* Pop the current STK SN, if not IDLE TASK. This function MUST not be
       * called inside IDLE TASK. */
      p_ccb->p_stk_sn = p_sn_term->p_next;
      /* Wait to se p_ccb->p_curr until you are completely sure to what set */

      p_tcb_term->status       = OSEE_TASK_READY;
      p_tcb_term->current_prio = p_tdb_term->ready_prio;
#if (defined(OSEE_HAS_EVENTS))
      /* If this activation is the last of a TASK, a chaining is
       * a transiction from SUSPENDED to READY so I need to reset Events. */
      if (p_tcb_term->current_num_of_act == 1U) {
        osEE_event_reset_mask(p_tcb_term);
      }
#endif /* OSEE_HAS_EVENTS */

      (void)osEE_scheduler_rq_insert(&p_kcb->rq, p_sn_term, p_tdb_term);

      {
        CONSTP2VAR(OsEE_preempt, AUTOMATIC, OS_APPL_DATA)
          p_prev = osEE_scheduler_core_rq_preempt_stk(p_cdb, &p_kcb->rq);

        if (p_prev == NULL) {
          /* Restore Stacked.
           * Not Needed to Check Idle TASK since just reinserted the chained
           * in RQ */
          p_tdb_to                = p_ccb->p_stk_sn->p_tdb;
          p_ccb->p_curr           = p_tdb_to;
        } else {
          p_tdb_to = p_ccb->p_curr;
        }
      }
      /* Chained Termination => SN reused - NO Release */
    }
  }
  /* Do Not Release Yet, wait after the context change */

  return p_tdb_to;
}

FUNC(OsEE_bool, OS_CODE)
  osEE_scheduler_task_preemption_point
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb
)
{
  VAR(OsEE_bool, AUTOMATIC)                     is_preemption;
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)       p_prev_stk_sn;
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb  = p_cdb->p_ccb;
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_prev = p_ccb->p_curr;
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)      p_new;

  /* Lock the Scheduler */
  osEE_lock_kernel();

  p_prev_stk_sn = osEE_scheduler_core_rq_preempt_stk(p_cdb, &p_kdb->p_kcb->rq);

  p_new = p_ccb->p_curr;

  if ( p_prev_stk_sn != NULL ) {
    /* In scheduler global the TDB is reinserted in RQ */
    (void)osEE_scheduler_rq_insert(&p_kdb->p_kcb->rq, p_prev_stk_sn,
        p_prev);
    osEE_hal_signal_broadcast();

    /* Kernel Lock Release Postponed */
    osEE_change_context_from_running(p_prev, p_new);

    is_preemption = OSEE_TRUE;
  } else if (p_new != p_prev) {
    /* Idle Loop preempted: No RQ re-insertion */
    /* Kernel Lock Release Postponed */
    osEE_change_context_from_running(p_prev, p_new);

    is_preemption = OSEE_TRUE;
  } else {
    osEE_unlock_kernel();
    is_preemption = OSEE_FALSE;
  }
  return is_preemption;
}

FUNC(void, OS_CODE)
  osEE_scheduler_task_set_running
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb
)
{
  CONSTP2VAR(OsEE_KCB, AUTOMATIC, OS_APPL_DATA) p_kcb  = p_kdb->p_kcb;
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb  = p_cdb->p_ccb;
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_preempted = p_ccb->p_curr;
  CONSTP2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
    p_preempted_sn = p_ccb->p_stk_sn;

  p_preempted->p_tcb->status    = OSEE_TASK_READY_STACKED;
  p_ccb->p_curr                 = p_tdb;
  p_tdb->p_tcb->current_core_id = osEE_get_curr_core_id();

  osEE_lock_kernel();
  /* Alloc the SN for the new Running TASK */
  p_ccb->p_stk_sn               = osEE_sn_alloc(&p_kcb->p_free_sn);
  p_ccb->p_stk_sn->p_tdb        = p_tdb;

  if ( p_preempted != p_cdb->p_idle_task ) {
    /* Let the other cores try to handle the preempted TASK */
    (void)osEE_scheduler_rq_insert(&p_kcb->rq, p_preempted_sn,
      p_preempted);
    osEE_hal_signal_broadcast();
  }

  osEE_change_context_from_running(p_preempted, p_tdb);
}

#if (defined(OSEE_API_DYNAMIC))
FUNC(OsEE_bool, OS_CODE)
  osEE_scheduler_task_reserve_activations
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  VAR(TaskActivation, AUTOMATIC)            activations
)
{
  VAR(OsEE_bool, AUTOMATIC) reserved;
  CONSTP2VAR(OsEE_KCB, AUTOMATIC, OS_APPL_DATA) p_kcb  = p_kdb->p_kcb;

  /* Touch unused parameters */
  (void)p_cdb;
  /* This function is supposed to be called in a kernel critical section
     already */

  if ( p_kcb->free_sn_counter >= activations ) {
    p_kcb->free_sn_counter -= activations;
    reserved = OSEE_TRUE;
  } else {
    reserved = OSEE_FALSE;
  }

  return reserved;
}
#endif /* OSEE_API_DYNAMIC */
