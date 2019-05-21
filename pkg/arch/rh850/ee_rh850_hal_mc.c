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

/** \file   ee_rh850_hal.c
 *  \brief  RH850 HAL multi-core (mc) not inline
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

#include "ee_internal.h"

#if (!defined(OSEE_SINGLECORE))
void osEE_hal_sync_barrier(OsEE_barrier * p_barr,
  OsEE_reg const volatile * p_wait_mask, OsEE_kernel_cb p_synch_cb)
{
  CoreMaskType const exit_mask  = (0xFFFFFFFFU ^
    (((CoreMaskType)0x1U << OS_CORE_ID_ARR_SIZE) - 1U));

  OsEE_reg wait_mask, all_exited;

  if ((p_barr != NULL) && (p_wait_mask != NULL)) {
    /* If not all cores have left the previous use of this barrier
       wait for it. */
    while ((p_barr->value & exit_mask) != 0U) {
      if (p_synch_cb != NULL) {
        p_synch_cb();
      }
      _snooze();
    }

    /* Set current CPU as entered */
    osEE_rh850_set_bit_l(&p_barr->value, (OsEE_reg)osEE_get_curr_core_id());

    /* Snapshot of the wait mask */
    wait_mask = (*p_wait_mask);
    while ((p_barr->value & wait_mask) != wait_mask) {
      /* Wait for all other cores/CPUs */
      if (p_synch_cb != NULL) {
        p_synch_cb();
      }
      /* Refresh the snapshot of the wait mask */
      wait_mask = (*p_wait_mask);
      _snooze();
    } 

    all_exited = (wait_mask << OS_CORE_ID_ARR_SIZE) | wait_mask;

    /* Set current CPU as exited */
    osEE_rh850_set_bit_l(&p_barr->value,
      ((OsEE_reg)osEE_get_curr_core_id() + (OsEE_reg)OS_CORE_ID_ARR_SIZE));

    /* Try to reset the barrier */
    (void)osEE_rh850_cmpswapw_l(&p_barr->value, all_exited, 0U);
  }
}

/* As optimization this is directly called by our implementation of EI
   RefTable and by Embark G4MH, this means that the symbol have to be extern
   and "conf" visible */
void osEE_rh850_handle_ipir(void) {
  /* Rise PLMR to handle IPIR preemption point */
  CONST(OsEE_reg, AUTOMATIC) flags = osEE_hal_begin_nested_primitive();
  CONSTP2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_CONST)  p_kdb = osEE_get_kernel();
  CONSTP2CONST(OsEE_KCB, AUTOMATIC, OS_APPL_DATA) p_kcb = p_kdb->p_kcb;

  /* Ack IPIR IIRQ */
  osEE_rh850_ack_signal();

  /* Check for ShutdownAllCores */
  if (p_kcb->ar_shutdown_all_cores_flag) {
    CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_CONST)
      p_curr_cdb = osEE_get_curr_core();
    osEE_shutdown_os(p_curr_cdb, p_kcb->ar_shutdown_all_cores_error);
  } else {
    osEE_rh850_ipir_preemption_point(p_kdb);

    /* I need to disable IRQ here since I'm lowering PLMR, and I don't want to
       allow nesting here before context restoring. Multiple ISR context
       stacking for the same TASK have not to happens for stack bounding. */
    osEE_hal_disableIRQ();
  }

  osEE_hal_end_nested_primitive(flags);
}
#endif /* !OSEE_SINGLECORE */
