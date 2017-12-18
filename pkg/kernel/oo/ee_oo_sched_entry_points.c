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

static FUNC(void, OS_CODE)
  osEE_scheduler_task_not_terminated
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_term
)
{
  (void)osEE_begin_primitive();

  osEE_hal_terminate_activation(&p_to_term->hdb,
    OSEE_KERNEL_TERMINATE_ACTIVATION_CB);
}

#if (!defined(OSEE_KERNEL_TERMINATE_ACTIVATION_OVERRIDE))
FUNC(void, OS_CODE)
  osEE_scheduler_task_end
(
  void
)
{
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to;
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_from;

  p_to = osEE_scheduler_task_terminated(osEE_get_kernel(), osEE_get_curr_core(),
           &p_from);

  if (p_from->task_type != OSEE_TASK_TYPE_ISR2) {
    osEE_change_context_from_task_end(p_from, p_to);
  } else {
    osEE_change_context_from_isr2_end(p_from, p_to);
  }
}
#endif /* !OSEE_KERNEL_TERMINATE_ACTIVATION_OVERRIDE */

FUNC(void, OS_CODE)
  osEE_scheduler_task_wrapper_restore
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb_to
)
{
#if (defined(OSEE_HAS_PRETASKHOOK)) || (defined(OSEE_SCHEDULER_GLOBAL)) ||\
    (defined(OSEE_HAS_CONTEXT))
  CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA) p_cdb = osEE_get_curr_core();
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb = p_cdb->p_ccb;
#endif /* OSEE_HAS_PRETASKHOOK || OSEE_SCHEDULER_GLOBAL || OSEE_HAS_CONTEXT */

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
#else
/* Touch unused parameter */
(void)p_tdb_to;
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
  CONST(TaskPrio, AUTOMATIC) task_prio = p_tdb_to->p_tcb->current_prio;
  osEE_scheduler_task_wrapper_restore(p_tdb_to);

  if (task_prio < OSEE_ISR_ALL_PRIO) {
    /* Set-up IPL at current TASK level in addition to enable IRQ */
    osEE_hal_set_ipl(task_prio);
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
  (void)osEE_scheduler_task_preemption_point(osEE_get_kernel(), p_cdb);
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
