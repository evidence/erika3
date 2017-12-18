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

/** \file  ee_std_hal_init.c
 *  \brief  HAL.
 *
 *  This files contains the HAL implementation for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2017
 */

#include "ee_internal.h"
#include <assert.h>
#include <stdint.h>

#if (defined(OSEE_API_DYNAMIC))

VAR(OsEE_KCB, OS_VAR_CLEARED) KCB;
VAR(OsEE_CCB, OS_VAR_CLEARED) CCB;

VAR(OsEE_KDB, OS_VAR_CLEARED) KDB;
VAR(OsEE_CDB, OS_VAR_CLEARED) CDB;

VAR(OsEE_TDB, OS_VAR_CLEARED) tdb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
VAR(OsEE_TCB, OS_VAR_CLEARED) tcb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
P2VAR(OsEE_TDB, OS_VAR_CLEARED, OS_APPL_DATA)
                          tdb_ptr_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
VAR(OsEE_SN, OS_VAR_CLEARED)  sn_array[OSEE_SN_ARRAY_SIZE];

/* Stacks "space" array */
VAR(OsEE_stack, OS_STACK)
  osEE_task_stacks[OSEE_STACK_WORD_LENGHT(OSEE_STACKS_SIZE)];

typedef struct OsEE_HPB_tag {
  VAR(OsEE_addr, TYPEDEF)     pool_base;
  VAR(size_t, TYPEDEF)        residual_mem;
  VAR(OsEE_SDB, TYPEDEF)      sdb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
  VAR(OsEE_SCB, TYPEDEF)      scb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
} OsEE_HPB;

VAR(OsEE_HPB, OS_VAR_INIT) osEE_pool = {
  OSEE_STACK_TOS(osEE_task_stacks),
  OSEE_STACKS_SIZE,
  {},
  {}
};

static FUNC(OsEE_addr, OS_CODE)
  osEE_hal_allocate_stack
(
  P2VAR(MemSize, AUTOMATIC, OS_APPL_DATA) p_stack_size
)
{
  VAR(OsEE_addr, AUTOMATIC) p_stack;

  /* Grant that the stack size is at least 2 times guard area */
  (*p_stack_size) = ((*p_stack_size) > (OSEE_STACK_GUARD_AREA * 2U))?
    (((*p_stack_size) + (OSEE_STACK_ALIGN_SIZE - 1U)) & OSEE_STACK_ALIGN):
    (OSEE_STACK_GUARD_AREA * 2U);

  if ( osEE_pool.residual_mem >= (*p_stack_size) ) {
    p_stack = OSEE_GET_STACK_POINTER(osEE_pool.pool_base);

    osEE_pool.pool_base =
      OSEE_ADJUST_POOL_BASE(osEE_pool.pool_base, *p_stack_size);

    osEE_pool.residual_mem  -= (*p_stack_size);
  } else {
    p_stack = NULL;
  }
  return p_stack;
}

FUNC(OsEE_bool, OS_CODE)
  osEE_hal_hdb_init
(
  VAR(CoreIdType, AUTOMATIC)                core_id,
  P2VAR(OsEE_HDB, AUTOMATIC, OS_APPL_DATA)  p_hdb,
  VAR(MemSize, AUTOMATIC)                   stack_size
)
{
  VAR(OsEE_bool, AUTOMATIC) ret_val;

  if ( stack_size == OSEE_SYSTEM_STACK ) {
      /* Share the core global stack */
      CONSTP2VAR(OsEE_HDB, AUTOMATIC, OS_APPL_DATA)
        p_hdb_idle = &osEE_get_core(core_id)->p_idle_task->hdb;

      p_hdb->p_sdb = p_hdb_idle->p_sdb;
      p_hdb->p_scb = p_hdb_idle->p_scb;

      ret_val = OSEE_TRUE;
  } else {
    CONSTP2VAR(OsEE_CTX, AUTOMATIC, OS_APPL_DATA) p_stack =
      osEE_hal_allocate_stack(&stack_size);

    if ( p_stack != NULL ) {
      /* The following set the link between TASK and Stack */
      p_hdb->p_sdb->p_bos       = p_stack;
      p_hdb->p_sdb->stack_size  = stack_size;
      p_hdb->p_scb->p_tos       = p_stack;

      ret_val = OSEE_TRUE;
    } else {
      ret_val = OSEE_FALSE;
    }
  }
  return ret_val;
}

FUNC(void, OS_CODE_INIT)
  osEE_os_init ( void )
{
  VAR(size_t, AUTOMATIC) i;

  /* Initialize Kernel Descriptor block */
  KDB.p_kcb           = &KCB;
  KDB.p_tdb_ptr_array = &tdb_ptr_array;
  KDB.tdb_array_size  = OSEE_ARRAY_ELEMENT_COUNT(tdb_ptr_array);
  KDB.p_sn_array      = &sn_array;
  KDB.sn_array_size   = OSEE_ARRAY_ELEMENT_COUNT(sn_array);

  /* Initialize Core Data Structures */
#if (defined(OSEE_SINGLECORE))
  CDB.p_ccb                   = &CCB;
  CDB.p_idle_task             = &tdb_array[OSEE_TASK_ARRAY_SIZE];
  CDB.p_idle_task->task_func  = osEE_idle_hook_wrapper;
#else
  /* TODO */
  /* p_idle_task = (*KDB.tdb_ptr_array)[OSEE_TASK_ARRAY_SIZE + core_id]; */
#endif /* OSEE_SINGLECORE */

  /* Initialize the Task Description & Control Blocks (TDB & TCB) */
  for ( i = 0U; i < OSEE_ARRAY_ELEMENT_COUNT(tdb_array); ++i ) {
    CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_tdb = &tdb_array[i];

    tdb_ptr_array[i]        = p_tdb;
    p_tdb->p_tcb            = &tcb_array[i];
    p_tdb->hdb.p_sdb        = &osEE_pool.sdb_array[i];
    p_tdb->hdb.p_scb        = &osEE_pool.scb_array[i];
  }

  /* Initialize the Scheduler Nodes (SN) Free Linked List */
  for ( i = 1U; i < KDB.sn_array_size; ++i ) {
    (*KDB.p_sn_array)[(i - 1U)].p_next = &(*KDB.p_sn_array)[i];
  }

#if (defined(OSEE_SINGLECORE))
  /* Initialize Core Data Structures */
  CCB.p_free_sn       = &(*KDB.p_sn_array)[0U];
  CCB.free_sn_counter = OSEE_ARRAY_ELEMENT_COUNT(sn_array);
  CCB.os_status       = OSEE_KERNEL_STOPPED;
#else
  /* TODO: configure how partition the SN in between Cores and set the core as
           configured*/
#endif /* OSEE_SINGLECORE */
}

FUNC(OsEE_bool, OS_CODE)
  osEE_std_cpu_startos ( void )
{
  CONST(CoreIdType, AUTOMATIC) core_id = osEE_get_curr_core_id();
  CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)
    p_cdb = osEE_get_core(core_id);
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
    p_tdb = p_cdb->p_idle_task;
  CONSTP2VAR(OsEE_HDB, AUTOMATIC, OS_APPL_DATA) p_hdb = &p_tdb->hdb;

  /* Initialize Idle TASK */
  /* System tos will be rewrittern by EE_hal_start_idle_task */
  CONSTP2VAR(OsEE_CTX, AUTOMATIC, OS_APPL_DATA) p_tos = osEE_get_SP();

  /* Tie Idle TASK with main Stack */
  p_hdb->p_sdb->p_bos       = p_tos;
  p_hdb->p_sdb->stack_size  = (MemSize)(-1);
  p_hdb->p_scb->p_tos       = p_tos;

  /* Fill TDB */
  p_tdb->tid                = (OSEE_TASK_ARRAY_SIZE + core_id);
  p_tdb->task_type          = OSEE_TASK_TYPE_IDLE;
  p_tdb->max_num_of_act     = 1U;
#if (!defined(OSEE_SINGLECORE))
  p_tdb->orig_core_id       = core_id;
#endif /* !OSEE_SINGLECORE */

  return OSEE_TRUE;
}
#endif /* OSEE_API_DYNAMIC */

