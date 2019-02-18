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

/** \file  ee_oo_api_osek.c
 *  \brief  OSEK Kernel APIs Implementation.
 *
 *  This files contains the implementation of some Kernel internal APIs
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date    2018
 */

#include "ee_internal.h"

FUNC(StatusType, OS_CODE) osEE_task_activated
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb_act
)
{
  VAR(StatusType, AUTOMATIC)                    ev;
  CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA) p_tcb_act = p_tdb_act->p_tcb;
#if (!defined(OSEE_SINGLECORE))
#if (!defined(OSEE_SCHEDULER_GLOBAL))
  CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)
    p_cdb = osEE_lock_and_get_core(p_tdb_act->orig_core_id);
#else
  osEE_lock_kernel();
#endif /* !OSEE_SCHEDULER_GLOBAL */
#endif /* !OSEE_SINGLECORE */

  if (p_tcb_act->current_num_of_act < p_tdb_act->max_num_of_act) {
    ++p_tcb_act->current_num_of_act;
    ev = E_OK;
  } else {
    ev = E_OS_LIMIT;
  }

#if (!defined(OSEE_SINGLECORE))
#if (!defined(OSEE_SCHEDULER_GLOBAL))
  osEE_unlock_core(p_cdb);
#else
  osEE_lock_kernel();
#endif /* !OSEE_SCHEDULER_GLOBAL */
#endif /* !OSEE_SINGLECORE */

  return ev;
}

FUNC(void, OS_CODE)
  osEE_task_end
(
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_tdb
)
{
  /* It has to be called already in Multi-Core critical section */
  CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA) p_tcb = p_tdb->p_tcb;

  p_tcb->current_prio = p_tdb->ready_prio;

  --p_tcb->current_num_of_act;

  if (p_tcb->current_num_of_act == 0U) {
    p_tcb->status = OSEE_TASK_SUSPENDED;
  } else {
    p_tcb->status = OSEE_TASK_READY;
  }
}

#if (defined(OSEE_HAS_EVENTS))
FUNC_P2VAR(OsEE_SN, OS_APPL_DATA, OS_CODE)
  osEE_task_event_set_mask
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)    p_tdb_waking_up,
  VAR(EventMaskType, AUTOMATIC)               Mask,
  P2VAR(StatusType, AUTOMATIC, OS_APPL_DATA)  p_ev  
)
{
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
    p_own_sn        = NULL;
  CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)
    p_tcb_waking_up = p_tdb_waking_up->p_tcb;
#if (!defined(OSEE_SINGLECORE))
#if (!defined(OSEE_SCHEDULER_GLOBAL))
  CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)
    p_cdb = osEE_lock_and_get_core(p_tdb_waking_up->orig_core_id);
#else
  osEE_lock_kernel();
#endif /* !OSEE_SCHEDULER_GLOBAL */
#endif /* !OSEE_SINGLECORE */

#if (defined(OSEE_HAS_CHECKS))
  if (p_tdb_waking_up->task_type != OSEE_TASK_TYPE_EXTENDED) {
    *p_ev = E_OS_ACCESS;
  } else
  if (p_tcb_waking_up->status == OSEE_TASK_SUSPENDED) {
    *p_ev = E_OS_STATE;
  } else
#endif /* OSEE_HAS_CHECKS */
  {
    /* Set the event mask only if the task is not suspended */
    p_tcb_waking_up->event_mask |= Mask;

    *p_ev = E_OK;

    if ((p_tcb_waking_up->wait_mask & Mask) != 0U) {
      p_own_sn = p_tcb_waking_up->p_own_sn;

      if (p_own_sn != NULL) {
        p_tcb_waking_up->p_own_sn = NULL;
      }
    }
  }

#if (!defined(OSEE_SINGLECORE))
#if (!defined(OSEE_SCHEDULER_GLOBAL))
  osEE_unlock_core(p_cdb);
#else
  osEE_lock_kernel();
#endif /* !OSEE_SCHEDULER_GLOBAL */
#endif /* !OSEE_SINGLECORE */

  return p_own_sn;
}
#endif /* OSEE_HAS_EVENTS */

#if (defined(OSEE_HAS_STACK_MONITORING))
FUNC(void, OS_CODE) osEE_stack_monitoring
(
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA) p_cdb
)
{
  if (p_cdb->p_ccb->os_status == OSEE_KERNEL_STARTED) {
    if (osEE_hal_check_stack_overflow(p_cdb)) {
#if (defined(OSEE_HAS_PROTECTIONHOOK))
    /* TODO */
#else
    osEE_shutdown_os(p_cdb, E_OS_STACKFAULT);
#endif /*  OSEE_HAS_PROTECTIONHOOK */
    }
  }
}
#endif /* OSEE_HAS_STACK_MONITORING */

FUNC(void, OS_CODE)
  osEE_activate_isr2
(
  VAR(TaskType, AUTOMATIC) isr2_id
)
{
#if (defined(OSEE_HAS_STACK_MONITORING))
  osEE_stack_monitoring(osEE_get_curr_core());
#endif /* OSEE_HAS_STACK_MONITORING */
  {
    CONSTP2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA) p_kdb = osEE_get_kernel();
    CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
      p_act_tdb = (*p_kdb->p_tdb_ptr_array)[isr2_id];

    /* Mark the TASK as Activated */
    ++p_act_tdb->p_tcb->current_num_of_act;

    osEE_scheduler_task_set_running(p_kdb, p_act_tdb, NULL);
  }
}

