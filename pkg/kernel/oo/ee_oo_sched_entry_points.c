/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 - 2018 Evidence s.r.l.
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
 * < www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
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

/** \file  ee_sched_entry_points.c
 *  \brief  OSEK Kernel Scheduler Entry Points.
 *
 *  This files contains the implementation of all OSEK Kernel Scheduler Entry
 *  Points in Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */

#include "ee_internal.h"

#if (defined(OSEE_HAS_RESOURCES)) || (defined(OSEE_HAS_SPINLOCKS))
static FUNC_P2VAR(OsEE_MDB, OS_APPL_CONST, OS_CODE)
  osEE_release_all_m
(
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST)  p_tdb
)
{
  P2VAR(OsEE_MDB, AUTOMATIC, OS_APPL_CONST)     p_mdb = NULL;
  CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA) p_tcb = p_tdb->p_tcb;

  while ((p_tcb->p_last_m != NULL)
#if (defined(OSEE_HAS_SPINLOCKS))
    && (p_tcb->p_last_m->p_cb->p_owner == p_tdb)
#endif /* OSEE_HAS_SPINLOCKS */
  )
  {
    CONSTP2VAR(OsEE_MCB, AUTOMATIC, OS_APPL_DATA)
      p_last_m_cb = p_tcb->p_last_m->p_cb;
    /* Release the M from the owner */
    p_last_m_cb->p_owner = NULL;
    /* Save the first M not realesed */
    if (p_mdb == NULL) {
      p_mdb = p_tcb->p_last_m;
    }
#if (defined(OSEE_HAS_SPINLOCKS))
    /* Release arch dependent spinlock */
    if (p_tcb->p_last_m->p_spinlock_arch != NULL) {
      osEE_hal_spin_unlock(p_tcb->p_last_m->p_spinlock_arch);
    }
#endif /* OSEE_HAS_SPINLOCKS */

    /* Pop the Resources head */
    p_tcb->p_last_m = p_last_m_cb->p_next;
    /* No need to work on IPL, it will be the normal context restore to handle
       that. */
  }
#if (defined(OSEE_HAS_SPINLOCKS))
  /* Restore last spinlock on CCB */
  if (p_tcb->p_last_m != NULL) {
    CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_CONST)  p_cdb = osEE_get_curr_core();

    p_cdb->p_ccb->p_last_spinlock = p_tcb->p_last_m;
    p_tcb->p_last_m = NULL;
  }
#endif /* OSEE_HAS_SPINLOCKS */

  return p_mdb;
}
#endif /* OSEE_HAS_RESOURCES || OSEE_HAS_SPINLOCKS */

static FUNC(void, OS_CODE)
  osEE_scheduler_task_not_terminated
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_term
)
{
  CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_CONST)
    p_cdb = osEE_get_curr_core();
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)
    p_ccb = p_cdb->p_ccb;

  /* Reset ISR Counters */
/* [SWS_Os_00239] If a task returns from the entry function without making a
    TerminateTask() or ChainTask() call and interrupts are still disabled,
    the Operating System module shall enable them. */
  p_ccb->s_isr_os_cnt  = 0U;
  /* I won't re-enable OS Interrupts since I'm going to enter rescheduling
     critical section */
  if (p_ccb->s_isr_all_cnt > 0U) {
    p_ccb->s_isr_all_cnt = 0U;
    osEE_hal_resumeIRQ(p_ccb->prev_s_isr_all_status);
  }
  if (p_ccb->d_isr_all_cnt > 0U) {
    p_ccb->d_isr_all_cnt = 0U;
    osEE_hal_enableIRQ();
  }

  (void)osEE_begin_primitive();

  osEE_stack_monitoring(p_cdb);

  if (p_to_term->task_type == OSEE_TASK_TYPE_ISR2) {
#if (defined(OSEE_HAS_RESOURCES)) || (defined(OSEE_HAS_SPINLOCKS))
  /* [SWS_Os_00369]: If a Category 2 ISR calls GetResource() and ends (returns)
      without calling the corresponding ReleaseResource(), the Operating System
      module shall perform the ReleaseResource() call and shall call the
      ErrorHook() E_OS_RESOURCE */
    CONSTP2VAR(OsEE_MDB, AUTOMATIC, OS_APPL_CONST)
      p_mdb = osEE_release_all_m(p_to_term);

    if (p_mdb != NULL) {
      osEE_set_service_id(p_ccb, OSId_ISR2Body);
#if (defined(OSEE_HAS_RESOURCES))
#if (defined(OSEE_HAS_SPINLOCKS))
      if (p_mdb->m_type == OSEE_M_RESOURCE) {
        osEE_call_error_hook(p_ccb, E_OS_RESOURCE);
      } else {
        osEE_call_error_hook(p_ccb, E_OS_SPINLOCK);
      }
#else
      osEE_call_error_hook(p_ccb, E_OS_RESOURCE);
#endif /* OSEE_HAS_SPINLOCKS */
#else
      osEE_call_error_hook(p_ccb, E_OS_SPINLOCK);
#endif /* OSEE_HAS_RESOURCES */
    }
#endif /* OSEE_HAS_RESOURCES || OSEE_HAS_SPINLOCKS */
  } else {
    osEE_set_service_id(p_ccb, OSId_TaskBody);
/* [SWS_Os_00069]: If a task returns from its entry function without making a
    TerminateTask() or ChainTask() call AND the error hook is configured,
    the Operating System shall call the ErrorHook() 
    (this is done regardless of whether the task causes other errors,
     e.g. E_OS_RESOURCE) with status E_OS_MISSINGEND before the task leaves
    the RUNNING state. */
    osEE_call_error_hook(p_ccb, E_OS_MISSINGEND);
#if (defined(OSEE_HAS_RESOURCES)) || (defined(OSEE_HAS_SPINLOCKS))
/* [SWS_Os_0070]: If a task returns from the entry function without making a
    TerminateTask() or ChainTask() call and still holds OSEK Resources,
    the Operating System shall release them. */
    (void)osEE_release_all_m(p_to_term);
#endif /* OSEE_HAS_RESOURCES || OSEE_HAS_SPINLOCKS */
  }

  osEE_hal_terminate_activation(&p_to_term->hdb,
    OSEE_KERNEL_TERMINATE_ACTIVATION_CB);
}

FUNC(void, OS_CODE)
  osEE_scheduler_task_wrapper_restore
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb_to
)
{
#if (defined(OSEE_HAS_PRETASKHOOK)) || (defined(OSEE_SCHEDULER_GLOBAL)) ||\
    (defined(OSEE_HAS_CONTEXT)) || (defined(OSEE_HAS_ORTI)) ||\
    (defined(OSEE_HAS_STACK_MONITORING))
  CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA) p_cdb = osEE_get_curr_core();
#endif /* OSEE_HAS_PRETASKHOOK || OSEE_SCHEDULER_GLOBAL || OSEE_HAS_CONTEXT ||
          OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */
#if (defined(OSEE_HAS_PRETASKHOOK)) || (defined(OSEE_SCHEDULER_GLOBAL)) ||\
    (defined(OSEE_HAS_CONTEXT)) || (defined(OSEE_HAS_ORTI))
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb = p_cdb->p_ccb;
#endif /* OSEE_HAS_PRETASKHOOK || OSEE_SCHEDULER_GLOBAL || OSEE_HAS_CONTEXT ||
          OSEE_HAS_ORTI */
#if (defined(OSEE_HAS_STACK_MONITORING))
  osEE_stack_monitoring(p_cdb);
#endif /* OSEE_HAS_STACK_MONITORING */
#if (defined(OSEE_HAS_ORTI))
  if (p_ccb->orti_service_id_valid == OSEE_TRUE) {
/* Reset last bit of service_id to mark OS service exit */
    p_ccb->service_id = (OSServiceIdType)
      (((OsEE_reg)p_ccb->service_id) & (~((OsEE_reg)0x1U)));

    p_ccb->orti_service_id_valid = OSEE_FALSE;
  }

#endif /* OSEE_HAS_ORTI */

  /* Set the TASK status to RUNNING. Before calling PreTaskHook */
  p_tdb_to->p_tcb->status = OSEE_TASK_RUNNING;

  /* Call PreTaskHook only if I'm scheduling a real TASK not an ISR2 or the
   * Idle TASK */
#if (defined(OSEE_HAS_PRETASKHOOK)) || (defined(OSEE_HAS_CONTEXT))
  if (p_tdb_to->task_type <= OSEE_TASK_TYPE_EXTENDED) {
#if (defined(OSEE_HAS_PRETASKHOOK))
    if (p_ccb->p_last_tdb_hook != p_tdb_to) {
      p_ccb->p_last_tdb_hook = p_tdb_to;
      osEE_call_pre_task_hook(p_ccb);
    }
#endif /* OSEE_HAS_PRETASKHOOK */
#if (defined(OSEE_HAS_CONTEXT))
    p_ccb->os_context = OSEE_TASK_CTX;
#endif /* OSEE_HAS_CONTEXT */
  }
#if (defined(OSEE_HAS_CONTEXT))
  else if (p_tdb_to->task_type == OSEE_TASK_TYPE_ISR2) {
    p_ccb->os_context = OSEE_TASK_ISR2_CTX;
  } else {
    p_ccb->os_context = OSEE_IDLE_CTX;
  }
#endif /* OSEE_HAS_CONTEXT */
#endif /* OSEE_HAS_PRETASKHOOK || OSEE_HAS_CONTEXT */

#if (defined(OSEE_SCHEDULER_GLOBAL))
  CONSTP2VAR(OsEE_spin_lock, AUTOMATIC, OS_APPL_DATA)
    p_lock_to_be_released = p_ccb->p_lock_to_be_released;

  osEE_unlock_kernel();

  if (p_lock_to_be_released != NULL) {
    osEE_hal_spin_unlock(p_lock_to_be_released);
    p_ccb->p_lock_to_be_released = NULL;
  }
#endif /* OSEE_SCHEDULER_GLOBAL */

  return;
}

FUNC(void, OS_CODE)
  osEE_scheduler_task_wrapper_run
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb_to
)
{
  CONST(TaskPrio, AUTOMATIC) task_priority = p_tdb_to->p_tcb->current_prio;
  osEE_scheduler_task_wrapper_restore(p_tdb_to);

  if (task_priority < OSEE_ISR_ALL_PRIO) {
    /* Set-up IPL at current TASK level in addition to enable IRQ */
    osEE_hal_set_ipl(task_priority);
    osEE_hal_enableIRQ();
  }
  p_tdb_to->task_func();

  /* Unexpected TASK Function return */
  osEE_scheduler_task_not_terminated(p_tdb_to);
}

FUNC(void, OS_CODE)
  osEE_idle_hook_wrapper
(
  void
)
{
  CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)
    p_cdb = osEE_get_curr_core();
#if (defined(OSEE_HAS_AUTOSTART_TASK))
  /* Schedule Here: Autostart TASKs */
  CONST(OsEE_reg, AUTOMATIC) flags = osEE_begin_primitive();
  (void)osEE_scheduler_task_preemption_point(osEE_get_kernel());
  osEE_end_primitive(flags);
#endif /* !OSEE_STARTOS_RETURN && !OSEE_API_DYNAMIC && !OSEE_HAS_AUTOSTART_TASK */
  while (p_cdb->p_ccb->os_status == OSEE_KERNEL_STARTED) {
#if (defined(OSEE_HAS_IDLEHOOK)) || (defined(OSEE_API_DYNAMIC))
    CONST(TaskFunc, AUTOMATIC) p_idle_hook = p_cdb->p_idle_hook;
    if (p_idle_hook != NULL) {
      p_idle_hook();
    }
#else
    ; /* Empty Endless Loop */
#endif /* OSEE_HAS_IDLEHOOK || OSEE_API_DYNAMIC */
  }
  osEE_idle_task_terminate(p_cdb->p_idle_task);
}
