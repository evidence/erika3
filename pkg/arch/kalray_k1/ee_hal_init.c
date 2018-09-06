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

/** \file  ee_hal_init.c
 *  \brief  HAL.
 *
 *  This files contains the HAL implementation for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */

#include "ee_internal.h"
#include <assert.h>

#if (defined(OSEE_API_DYNAMIC))
/* Define Control Blocks in any case */
OsEE_KCB osEE_kcb_var;
OsEE_CCB osEE_ccb_var;

#if (defined(OSEE_HAS_JOBS))
OsEE_KCB_WJ osEE_kcb_wj;
OsEE_KDB_WJ osEE_kdb_wj;
#else
OsEE_TCB    osEE_tcb_array[OSEE_TASK_ARRAY_SIZE + OsNumberOfCores];
OsEE_SN     osEE_sn_array[OSEE_SN_ARRAY_SIZE];
OsEE_TDB    osEE_tdb_array[OSEE_TASK_ARRAY_SIZE + OsNumberOfCores];
OsEE_TDB *  osEE_tdb_ptr_array[OSEE_TASK_ARRAY_SIZE + OsNumberOfCores];

OsEE_KDB osEE_kdb_var;
#if (defined(OSEE_SINGLECORE))
  OsEE_CDB osEE_cdb_var;
#else
  /* TODO */
#endif /* OSEE_SINGLECORE */
#endif /* OSEE_HAS_JOBS */

#define OSEE_STACKS_WORDS OSEE_STACK_WORD_LENGHT(OSEE_STACKS_SIZE)

static OsEE_stack OSEE_STACK_ATTRIB
  ee_task_stacks[OSEE_STACKS_WORDS] =
    {[0 ... (OSEE_STACKS_WORDS - 1U) ] = OSEE_FILL_PATTERN};

/* Stack Descriptor 0 is reserved to System Stack */
OsEE_HPB osEE_pool = {
  .pool_base        = OSEE_STACK_TOS(ee_task_stacks),
  .residual_mem     = OSEE_STACKS_SIZE,
};

/* This handle only the system stack initialization + iirq initialization */
OsEE_bool osEE_cpu_startos ( void ) {
  CoreIdType    const core_id = osEE_get_curr_core_id();
  OsEE_TDB    * const p_tdb   = osEE_get_core(core_id)->p_idle_task;
  OsEE_HDB    * const p_hdb   = &p_tdb->hdb;
  /* System tos will be rewrittern by EE_hal_start_idle_task */
  OsEE_CTX    * const p_tos   = osEE_get_SP();

  /* Il descrittore in posizione 0 descrive lo Stack di sistema (PE) */
  p_hdb->p_sdb->p_bos       = p_tos;
  p_hdb->p_sdb->stack_size  = (MemSize)(-1);
  p_hdb->p_scb->p_tos       = p_tos;

  /* Fill TDB */
  p_tdb->tid              = (OSEE_TASK_ARRAY_SIZE + core_id);
  p_tdb->task_type        = OSEE_TASK_TYPE_IDLE;
  p_tdb->max_num_of_act   = 1U;
#if (!defined(OSEE_SINGLECORE))
  p_tdb->orig_core_id     = core_id;
#endif /* !OSEE_SINGLECORE */

  return OSEE_TRUE;
}

static OsEE_addr osEE_hal_allocate_stack ( MemSize * p_stack_size )
{
  OsEE_addr p_stack;

  /* Grant that the stack size is at least 2 times guard area */
  (*p_stack_size) = ((*p_stack_size) > (OSEE_STACK_GUARD_AREA * 2U))?
    (((*p_stack_size) + (OSEE_STACK_ALIGN_SIZE - 1U)) & OSEE_STACK_ALIGN):
    (OSEE_STACK_GUARD_AREA * 2U);

  if ( osEE_pool.residual_mem >= (*p_stack_size) ) {
    p_stack = (OsEE_stack *)((unsigned char *)osEE_pool.pool_base -
      (ptrdiff_t)(OSEE_STACK_GUARD_AREA));

    osEE_pool.pool_base     -= (ptrdiff_t)(*p_stack_size);
    osEE_pool.residual_mem  -= (*p_stack_size);
  } else {
    p_stack = NULL;
  }
  return p_stack;
}

OsEE_bool osEE_hal_hdb_init ( CoreIdType core_id, OsEE_HDB * p_hdb,
  MemSize stack_size )
{
  OsEE_bool  ret_val;
  if ( stack_size == OSEE_SYSTEM_STACK ) {
     /* Share the core global stack */
     OsEE_HDB * const p_hdb_idle = &osEE_get_core(core_id)->p_idle_task->hdb;
     p_hdb->p_sdb = p_hdb_idle->p_sdb;
     p_hdb->p_scb = p_hdb_idle->p_scb;
     ret_val = OSEE_TRUE;
  } else {
    OsEE_CTX * p_stack = osEE_hal_allocate_stack(&stack_size);
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

#if (defined(OSEE_HAS_JOBS))

void osEE_os_init ( void ) {
  size_t i;
  /* Initialize Kernel Descriptor block */
  osEE_kdb_wj.p_kcb_wj             = &osEE_kcb_wj;
  osEE_kdb_wj.kdb.p_kcb            = &osEE_kcb_wj.kcb;
  osEE_kdb_wj.kdb.p_tdb_ptr_array  = (OsEE_TDB * const (*)[])&osEE_kdb_wj.tdb_ptr_array;
  osEE_kdb_wj.kdb.tdb_array_size   = OSEE_ARRAY_ELEMENT_COUNT(osEE_kdb_wj.tdb_ptr_array);

  osEE_hal_spin_init_lock(&osEE_kcb_wj.kernel_lock);
  osEE_kdb_wj.kdb.p_lock = &osEE_kcb_wj.kernel_lock;

  osEE_hal_spin_init_lock(&osEE_kcb_wj.kernel_barrier.barrier_lock);
  osEE_kdb_wj.kdb.p_barrier = &osEE_kcb_wj.kernel_barrier;

  /* Initialize Core Data Structures */
  for (i = 0U; i < OSEE_K1_CORE_NUMBER; ++i) {
    osEE_kdb_wj.core_descriptors[i].p_ccb = &osEE_kcb_wj.core_ctrls[i];
    osEE_hal_spin_init_lock(&osEE_kcb_wj.core_locks[i]);
    osEE_kdb_wj.core_descriptors[i].p_lock = &osEE_kcb_wj.core_locks[i];

    osEE_kdb_wj.core_descriptors[i].p_idle_task =
      &osEE_kdb_wj.
        tdb_array[osEE_kdb_wj.kdb.tdb_array_size - OSEE_K1_CORE_NUMBER + i];
    osEE_kdb_wj.core_descriptors[i].
      p_idle_task->task_func = osEE_idle_hook_wrapper;
    osEE_kdb_wj.core_descriptors[i].core_id = i;
    osEE_kcb_wj.core_ctrls[i].os_status = OSEE_KERNEL_INITIALIZED;
  }

  /* Initialize the Task Description & Control Blocks (TDB & TCB) */
  for (i = 0U; i < osEE_kdb_wj.kdb.tdb_array_size; ++i) {
    OsEE_TDB * const p_tdb            = &osEE_kdb_wj.tdb_array[i];
    osEE_kdb_wj.tdb_ptr_array[i]           = p_tdb;
    p_tdb->p_tcb                      = &osEE_kcb_wj.tcb_array[i];
    p_tdb->hdb.p_sdb                  = &osEE_pool.sdb_array[i];
    p_tdb->hdb.p_scb                  = &osEE_pool.scb_array[i];
  }

  /* Initialize the Scheduler Nodes (SN) Free Linked List */
  for ( i = 1U; i < OSEE_ARRAY_ELEMENT_COUNT(osEE_kcb_wj.sn_array); ++i ) {
    osEE_kcb_wj.sn_array[(i - 1U)].p_next = &osEE_kcb_wj.sn_array[i];
  }
/* EG: Temporary bypass of StartCore procedure */
  osEE_kcb_wj.kcb.ar_core_mask        = OSEE_CORE_ID_VALID_MASK;
  osEE_kcb_wj.kcb.ar_num_core_started = OsNumberOfCores;

#if (defined(OSEE_SCHEDULER_GLOBAL))
  osEE_kcb_wj.kcb.p_free_sn        = &osEE_kcb_wj.sn_array[0U];
  osEE_kcb_wj.kcb.free_sn_counter  = OSEE_ARRAY_ELEMENT_COUNT(osEE_kcb_wj.sn_array);
#else
  {
    /* XXX: Arbitrary choice to try allocate allocate the same amount of
            Scheduler data for Each core */
    size_t const core_sn_size = OSEE_ARRAY_ELEMENT_COUNT(osEE_kcb_wj.sn_array);
    size_t const per_core_sn_size  = (core_sn_size / OSEE_K1_CORE_NUMBER);
    size_t const sn_offset_modulus = (core_sn_size % OSEE_K1_CORE_NUMBER);

    for ( i = (OSEE_K1_CORE_NUMBER - 1U); i > 0U; --i ) {
      osEE_kcb_wj.core_ctrls[i].p_free_sn =
        &osEE_kcb_wj.sn_array[(i * per_core_sn_size) + sn_offset_modulus];

      /* Initialize The Last element of the array associated to an array */
      osEE_kcb_wj.core_ctrls[i].p_free_sn[per_core_sn_size - 1U].
        p_next = NULL;
      /* Save the per_core_sn_size as free sn counter */
      osEE_kcb_wj.core_ctrls[i].free_sn_counter = per_core_sn_size;
    }
    /* I assign eventual offset to core 0 */
    osEE_kcb_wj.core_ctrls[0].p_free_sn = &osEE_kcb_wj.sn_array[0];
    /* Initialize The Last element of the array associated to an array */
    osEE_kcb_wj.core_ctrls[0].
      p_free_sn[per_core_sn_size - 1U + sn_offset_modulus].p_next = NULL;
    /* Since I assigned the offset to core 0, even the size has to be changed
     * accordingly */
    osEE_kcb_wj.core_ctrls[0].
      free_sn_counter = (per_core_sn_size + sn_offset_modulus);
  }
#endif /* !OSEE_SCHEDULER_GLOBAL */
}
#elif (defined(OSEE_SINGLECORE))

void osEE_os_init (void) {
  size_t i = 0;

  /* Initialize Kernel Descriptor block */
  osEE_kdb_var.p_kcb           = &osEE_kcb_var;
  osEE_kdb_var.p_tdb_ptr_array = (OsEE_TDB * const (*)[])&osEE_tdb_ptr_array;
  osEE_kdb_var.tdb_array_size  = OSEE_ARRAY_ELEMENT_COUNT(osEE_tdb_ptr_array);

  /* Initialize Core Data Structures */
  osEE_cdb_var.p_ccb                   = &osEE_ccb_var;
  osEE_cdb_var.p_idle_task             = &osEE_tdb_array[OSEE_TASK_ARRAY_SIZE];
  osEE_cdb_var.p_idle_task->task_func  = osEE_idle_hook_wrapper;

  /* Initialize the Task Description & Control Blocks (TDB & TCB) */
  for ( i = 0U; i < OSEE_ARRAY_ELEMENT_COUNT(osEE_tdb_array); ++i ) {
    OsEE_TDB * const p_tdb          = &osEE_tdb_array[i];
    osEE_tdb_ptr_array[i]           = p_tdb;
    p_tdb->p_tcb                    = &osEE_tcb_array[i];
    p_tdb->hdb.p_sdb                = &osEE_pool.sdb_array[i];
    p_tdb->hdb.p_scb                = &osEE_pool.scb_array[i];
  }

  /* Initialize the Scheduler Nodes (SN) Free Linked List */
  for ( i = 1U; i < OSEE_ARRAY_ELEMENT_COUNT(osEE_sn_array); ++i ) {
    osEE_sn_array[(i - 1U)].p_next = &osEE_sn_array[i];
  }

  /* TODO configure how partition the SN in between Cores*/

  /* Initialize Core Data Structures */
  osEE_ccb_var.p_free_sn       = &osEE_sn_array[0U];
  osEE_ccb_var.free_sn_counter = OSEE_ARRAY_ELEMENT_COUNT(osEE_sn_array);

  /* Initialize TCBs */
  for (i = 0; i < (osEE_kdb_var.tdb_array_size - 1U); ++i)
  {
    /* ISR2 initialization */
    OsEE_TDB  * const p_tdb = (*osEE_kdb_var.p_tdb_ptr_array)[i];
    OsEE_TCB  * const p_tcb = p_tdb->p_tcb;

    /* Set starting priority for TASKs */
    p_tcb->current_prio = p_tdb->ready_prio;

    if (p_tdb->task_type == OSEE_TASK_TYPE_ISR2) {
      osEE_hal_set_isr2_source(p_tdb, p_tdb->hdb.isr_src);
    }
  }
  osEE_ccb_var.os_status = OSEE_KERNEL_INITIALIZED;
}
#endif /* OSEE_HAS_JOBS */
#endif /* OSEE_API_DYNAMIC */
