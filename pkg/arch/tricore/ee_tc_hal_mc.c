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

/** \file   ee_tc_hal.c
 *  \brief  TriCore HAL multi-core (mc) not inline
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

#include "ee_internal.h"

#if (!defined(OSEE_SINGLECORE))
void osEE_hal_sync_barrier(OsEE_barrier * p_bar,
  OsEE_reg const volatile * p_wait_mask, OsEE_kernel_cb p_synch_cb)
{
  CoreMaskType const exit_mask  = (0xFFFFFFFFU ^
    (((CoreMaskType)0x1U << OS_CORE_ID_ARR_SIZE) - 1U));

  OsEE_reg wait_mask, all_exited;

  if ((p_bar != NULL) && (p_wait_mask != NULL)) {
    /* If not all cores have left the previous use of this barrier
       wait for it. */
    while ((p_bar->value & exit_mask) != 0U) {
      if (p_synch_cb != NULL) {
        p_synch_cb();
      }
    }

    /* Set current CPU as entered */
    osEE_tc_imask_ldmst(&p_bar->value, 0x1U,
      (OsEE_reg)osEE_get_curr_core_id(), 1U);

    /* Snapshot of the wait mask */
    wait_mask = (*p_wait_mask);
    while ((p_bar->value & wait_mask) != wait_mask) {
      /* Wait for all other cores/CPUs */
      if (p_synch_cb != NULL) {
        p_synch_cb();
      }
      /* Refresh the snapshot of the wait mask */
      wait_mask = (*p_wait_mask);
    } 

    all_exited = (wait_mask << OS_CORE_ID_ARR_SIZE) | wait_mask;

    /* Set current CPU as exited */
    osEE_tc_imask_ldmst(&p_bar->value, 0x1U,
      ((OsEE_reg)osEE_get_curr_core_id() + (OsEE_reg)OS_CORE_ID_ARR_SIZE), 1U);

    /* Try to reset the barrier */
    (void)osEE_tc_cmpswapw(&p_bar->value, 0U, all_exited);
  }
}

OsEE_CDB * osEE_get_core(CoreIdType core_id) {
  OsEE_CDB * p_cdb;
  switch (core_id) {
    case OS_CORE_ID_0:
      p_cdb = &osEE_cdb_var_core0;
    break;
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
    case OS_CORE_ID_1:
      p_cdb = &osEE_cdb_var_core1;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
    case OS_CORE_ID_2:
      p_cdb = &osEE_cdb_var_core2;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
    case OS_CORE_ID_3:
      p_cdb = &osEE_cdb_var_core3;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
    case OS_CORE_ID_4:
      p_cdb = &osEE_cdb_var_core4;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
    case OS_CORE_ID_6:
      p_cdb = &osEE_cdb_var_core6;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */
    default:
      /* This can happen when we cycle on cores */
      p_cdb = NULL;
    break;
  }

  return p_cdb;
}

void osEE_hal_start_core(CoreIdType core_id) {
  switch (core_id) {
    case OS_CORE_ID_0:
    /* Nothing to do in this case */
    break;
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
    case OS_CORE_ID_1:
      OSEE_TC_CORE_PC(OS_CORE_ID_1).reg = (uint32_t)OSEE_CORE1_START_ADDR;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
    case OS_CORE_ID_2:
      OSEE_TC_CORE_PC(OS_CORE_ID_2).reg = (uint32_t)OSEE_CORE2_START_ADDR;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
    case OS_CORE_ID_3:
      OSEE_TC_CORE_PC(OS_CORE_ID_3).reg = (uint32_t)OSEE_CORE3_START_ADDR;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
    case OS_CORE_ID_4:
      OSEE_TC_CORE_PC(OS_CORE_ID_4).reg = (uint32_t)OSEE_CORE4_START_ADDR;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
    case OS_CORE_ID_6:
      OSEE_TC_CORE_PC(OS_CORE_ID_6).reg = (uint32_t)OSEE_CORE6_START_ADDR;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */
    default:
      /* All possible masks have been handled above */
    break;
  }
  if (core_id != OS_CORE_ID_0) {
#if (!defined(OSEE_TC_2G))
    OSEE_TC_CORE_DBGSR(core_id).bits.halt = OSEE_TC_DBGSR_RESET_HALT;
#else
    OsEE_syscon syscon = OSEE_TC_CORE_SYSCON(core_id);
    if (syscon.bits.bhalt != 0U) {
      syscon.bits.bhalt = 0U;
      OSEE_TC_CORE_SYSCON(core_id) = syscon;
    }
#endif /* !OSEE_TC_2G */
  }
}

#endif /* !OSEE_SINGLECORE */
