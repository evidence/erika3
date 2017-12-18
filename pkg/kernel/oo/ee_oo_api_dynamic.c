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

/** \file  ee_oo_api_dynamic.c
 *  \brief  OSEK Kernel Dynamic APIs Implementation.
 *
 *  This files contains the implementation of all OSEK Kernel Dynamic APIs in
 *  Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */
#include "ee_internal.h"

#if (!defined(OSEE_ISR2_MAX_PRIO))
#define OSEE_ISR2_MAX_PRIO OSEE_ISR2_PRIO_BIT
#endif /* !OSEE_ISR2_MAX_PRIO */

#if (defined(OSEE_API_DYNAMIC))
FUNC(StatusType, OS_CODE)
  osEE_create_task
(
  VAR(CoreIdType, AUTOMATIC)        core_id,
  VAR(TaskRefType, AUTOMATIC)       p_task_id,
  VAR(TaskExecutionType, AUTOMATIC) task_type,
  VAR(TaskFunc, AUTOMATIC)          task_func,
  VAR(TaskPrio, AUTOMATIC)          ready_prio,
  VAR(TaskPrio, AUTOMATIC)          dispatch_prio,
  VAR(TaskActivation, AUTOMATIC)    max_num_of_act,
  VAR(MemSize, AUTOMATIC)           stack_size
)
{
  VAR(StatusType, AUTOMATIC) ev;
  CONSTP2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA) p_kdb = osEE_get_kernel();
  CONSTP2VAR(OsEE_KCB, AUTOMATIC, OS_APPL_DATA) p_kcb = p_kdb->p_kcb;

  /* Adjust Priorities */
  if (task_type == OSEE_TASK_TYPE_ISR2) {
    ready_prio    = (ready_prio - 1U)     | OSEE_ISR2_PRIO_BIT;
    dispatch_prio = (dispatch_prio - 1U)  | OSEE_ISR2_PRIO_BIT;
  } else {
    ready_prio    &= ~OSEE_ISR2_PRIO_BIT;
    dispatch_prio &= ~OSEE_ISR2_PRIO_BIT;
  }

  if ((task_type == OSEE_TASK_TYPE_EXTENDED) &&
      (stack_size == OSEE_SYSTEM_STACK))
  {
    ev = E_OS_STATE;
  } else if (p_kcb->free_task_index >= OSEE_TASK_ARRAY_SIZE) {
    ev = E_OS_SYS_TASK;
  } else if ((ready_prio == 0U) || (ready_prio < dispatch_prio) ||
    (max_num_of_act == 0U) || (dispatch_prio > OSEE_ISR2_MAX_PRIO))
  {
    ev = E_OS_VALUE;
  } else if (!osEE_scheduler_task_reserve_activations(p_kdb,
    osEE_get_core(core_id), max_num_of_act))
  {
    ev = E_OS_SYS_ACT;
  } else {
    P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb;
    /* Try to assign TID */
    CONST(TaskType, AUTOMATIC) tid  = p_kcb->free_task_index;
    /* Get corresponding TDB */
    p_tdb = (*p_kdb->p_tdb_ptr_array)[tid];

    if ( osEE_hal_hdb_init(core_id, &p_tdb->hdb, stack_size) ) {
      CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA) p_tcb = p_tdb->p_tcb;
      /* Alloc TDB and TCB */
      ++p_kcb->free_task_index;

      /* New Task Id */
      (*p_task_id) = tid;

      /* Fill TDB */
      p_tdb->tid              = tid;
      p_tdb->task_type        = task_type;
      p_tdb->task_func        = task_func;
      p_tdb->ready_prio       = ready_prio;
      p_tdb->dispatch_prio    = dispatch_prio;
      p_tdb->max_num_of_act   = max_num_of_act;
#if (!defined(OSEE_SINGLECORE))
      p_tdb->orig_core_id     = core_id;
#endif /* !OSEE_SINGLECORE */

      /* Fill TCB */
      p_tcb->current_prio        = ready_prio;
      p_tcb->status              = OSEE_TASK_SUSPENDED;
      p_tcb->current_num_of_act  = 0U;
#if (defined(OSEE_ALLOW_TASK_MIGRATION))
      p_tcb->current_core_id     = core_id;
#endif /* OSEE_ALLOW_TASK_MIGRATION */

      ev = E_OK;
    } else {
      ev = E_OS_SYS_STACK;
    }
  }
  return ev;
}

FUNC(StatusType, OS_CODE)
  CreateTask
(
  VAR(TaskRefType, AUTOMATIC)       taskIdRef,
  VAR(TaskExecutionType, AUTOMATIC) taskType,
  VAR(TaskFunc, AUTOMATIC)          taskFunc,
  VAR(TaskPrio, AUTOMATIC)          readyPrio,
  VAR(TaskPrio, AUTOMATIC)          dispatchPrio,
  VAR(TaskActivation, AUTOMATIC)    maxNumOfAct,
  VAR(MemSize, AUTOMATIC)           stackSize
)
{
  VAR(StatusType, AUTOMATIC)    ev;
  CONST(CoreIdType, AUTOMATIC)  core_id = osEE_get_curr_core_id();
  CONST(OsEE_reg, AUTOMATIC)    flags   = osEE_begin_primitive();

  osEE_lock_kernel();

  ev =  osEE_create_task(core_id, taskIdRef, taskType, taskFunc, readyPrio,
          dispatchPrio, maxNumOfAct, stackSize);

  osEE_unlock_kernel();
  osEE_end_primitive(flags);

  return ev;
}

FUNC(StatusType, OS_CODE)
  SetISR2Source
(
  VAR(TaskType, AUTOMATIC)  isr_id,
  VAR(ISRSource, AUTOMATIC) source_id
)
{
  VAR(StatusType, AUTOMATIC)                    ret_val;
  CONSTP2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA) p_kdb = osEE_get_kernel();

  if (isr_id >= p_kdb->p_kcb->free_task_index) {
     ret_val = E_OS_ID;
  } else {
    CONST(OsEE_reg, AUTOMATIC) flags  = osEE_begin_primitive();
    osEE_lock_kernel();

    ret_val = osEE_hal_set_isr2_source((*p_kdb->p_tdb_ptr_array)[isr_id],
                source_id);

    osEE_unlock_kernel();
    osEE_end_primitive(flags);
  }
  return ret_val;
}

FUNC(StatusType, OS_CODE)
  SetIdleHook
(
  VAR(TaskFunc, AUTOMATIC)          idleHook
)
{
  VAR(StatusType, AUTOMATIC) ev;
  CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)
    p_cdb = osEE_get_curr_core();

  if ( idleHook == NULL ) {
    ev = E_OS_PARAM_POINTER;
  } else if ( p_cdb->p_ccb->os_status != OSEE_KERNEL_STOPPED ) {
    ev = E_OS_SYS_INIT;
  } else {
    p_cdb->p_idle_hook = idleHook;
    ev = E_OK;
  }

  return ev;
}

#endif /* OSEE_API_DYNAMIC */
