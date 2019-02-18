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

#if (defined(__TASKING__))

/* Force to include the TRAP handlers symbols in elf file from an
   archive */
#pragma extern osEE_tc_trap_mmu_core0
#pragma extern osEE_tc_trap_protection_core0
#pragma extern osEE_tc_trap_instruction_core0
#pragma extern osEE_tc_trap_context_core0
#pragma extern osEE_tc_trap_bus_core0
#pragma extern osEE_tc_trap_assertion_core0
#pragma extern osEE_tc_trap_system_core0
#pragma extern osEE_tc_trap_nmi_core0

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
#pragma extern osEE_tc_trap_mmu_core1
#pragma extern osEE_tc_trap_protection_core1
#pragma extern osEE_tc_trap_instruction_core1
#pragma extern osEE_tc_trap_context_core1
#pragma extern osEE_tc_trap_bus_core1
#pragma extern osEE_tc_trap_assertion_core1
#pragma extern osEE_tc_trap_system_core1
#pragma extern osEE_tc_trap_nmi_core1
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
#pragma extern osEE_tc_trap_mmu_core2
#pragma extern osEE_tc_trap_protection_core2
#pragma extern osEE_tc_trap_instruction_core2
#pragma extern osEE_tc_trap_context_core2
#pragma extern osEE_tc_trap_bus_core2
#pragma extern osEE_tc_trap_assertion_core2
#pragma extern osEE_tc_trap_system_core2
#pragma extern osEE_tc_trap_nmi_core2
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
#pragma extern osEE_tc_trap_mmu_core3
#pragma extern osEE_tc_trap_protection_core3
#pragma extern osEE_tc_trap_instruction_core3
#pragma extern osEE_tc_trap_context_core3
#pragma extern osEE_tc_trap_bus_core3
#pragma extern osEE_tc_trap_assertion_core3
#pragma extern osEE_tc_trap_system_core3
#pragma extern osEE_tc_trap_nmi_core3
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
#pragma extern osEE_tc_trap_mmu_core4
#pragma extern osEE_tc_trap_protection_core4
#pragma extern osEE_tc_trap_instruction_core4
#pragma extern osEE_tc_trap_context_core4
#pragma extern osEE_tc_trap_bus_core4
#pragma extern osEE_tc_trap_assertion_core4
#pragma extern osEE_tc_trap_system_core4
#pragma extern osEE_tc_trap_nmi_core4
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
#pragma extern osEE_tc_trap_mmu_core5
#pragma extern osEE_tc_trap_protection_core5
#pragma extern osEE_tc_trap_instruction_core5
#pragma extern osEE_tc_trap_context_core5
#pragma extern osEE_tc_trap_bus_core5
#pragma extern osEE_tc_trap_assertion_core5
#pragma extern osEE_tc_trap_system_core5
#pragma extern osEE_tc_trap_nmi_core5
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */

/* Force to include the INTERRUPT handlers symbols in elf file from an
   archive */
#if (defined(OSEE_TC_CORE1_ISR_MAX_PRIO))
OSEE_ISR2_DECLARE(_core1_, 1)
#if (defined(OSEE_TC_CORE1_2_ISR_CAT))
#if (OSEE_TC_CORE1_2_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 2)
#elif (OSEE_TC_CORE1_2_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 2)
#else
#error Invalid value for OSEE_TC_CORE1_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 2)
OSEE_DUMMY_ISR(_core1_, 2)
#endif /* OSEE_TC_CORE1_2_ISR_CAT */
#if (defined(OSEE_TC_CORE1_3_ISR_CAT))
#if (OSEE_TC_CORE1_3_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 3)
#elif (OSEE_TC_CORE1_3_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 3)
#else
#error Invalid value for OSEE_TC_CORE1_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 3)
OSEE_DUMMY_ISR(_core1_, 3)
#endif /* OSEE_TC_CORE1_3_ISR_CAT */
#if (defined(OSEE_TC_CORE1_4_ISR_CAT))
#if (OSEE_TC_CORE1_4_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 4)
#elif (OSEE_TC_CORE1_4_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 4)
#else
#error Invalid value for OSEE_TC_CORE1_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 4)
OSEE_DUMMY_ISR(_core1_, 4)
#endif /* OSEE_TC_CORE1_4_ISR_CAT */
#if (defined(OSEE_TC_CORE1_5_ISR_CAT))
#if (OSEE_TC_CORE1_5_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 5)
#elif (OSEE_TC_CORE1_5_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 5)
#else
#error Invalid value for OSEE_TC_CORE1_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 5)
OSEE_DUMMY_ISR(_core1_, 5)
#endif /* OSEE_TC_CORE1_5_ISR_CAT */
#if (defined(OSEE_TC_CORE1_6_ISR_CAT))
#if (OSEE_TC_CORE1_6_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 6)
#elif (OSEE_TC_CORE1_6_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 6)
#else
#error Invalid value for OSEE_TC_CORE1_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 6)
OSEE_DUMMY_ISR(_core1_, 6)
#endif /* OSEE_TC_CORE1_6_ISR_CAT */
#if (defined(OSEE_TC_CORE1_7_ISR_CAT))
#if (OSEE_TC_CORE1_7_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 7)
#elif (OSEE_TC_CORE1_7_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 7)
#else
#error Invalid value for OSEE_TC_CORE1_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 7)
OSEE_DUMMY_ISR(_core1_, 7)
#endif /* OSEE_TC_CORE1_7_ISR_CAT */
#if (defined(OSEE_TC_CORE1_8_ISR_CAT))
#if (OSEE_TC_CORE1_8_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 8)
#elif (OSEE_TC_CORE1_8_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 8)
#else
#error Invalid value for OSEE_TC_CORE1_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 8)
OSEE_DUMMY_ISR(_core1_, 8)
#endif /* OSEE_TC_CORE1_8_ISR_CAT */
#if (defined(OSEE_TC_CORE1_9_ISR_CAT))
#if (OSEE_TC_CORE1_9_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 9)
#elif (OSEE_TC_CORE1_9_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 9)
#else
#error Invalid value for OSEE_TC_CORE1_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 9)
OSEE_DUMMY_ISR(_core1_, 9)
#endif /* OSEE_TC_CORE1_9_ISR_CAT */
#if (defined(OSEE_TC_CORE1_10_ISR_CAT))
#if (OSEE_TC_CORE1_10_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 10)
#elif (OSEE_TC_CORE1_10_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 10)
#else
#error Invalid value for OSEE_TC_CORE1_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 10)
OSEE_DUMMY_ISR(_core1_, 10)
#endif /* OSEE_TC_CORE1_10_ISR_CAT */
#if (defined(OSEE_TC_CORE1_11_ISR_CAT))
#if (OSEE_TC_CORE1_11_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 11)
#elif (OSEE_TC_CORE1_11_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 11)
#else
#error Invalid value for OSEE_TC_CORE1_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 11)
OSEE_DUMMY_ISR(_core1_, 11)
#endif /* OSEE_TC_CORE1_11_ISR_CAT */
#if (defined(OSEE_TC_CORE1_12_ISR_CAT))
#if (OSEE_TC_CORE1_12_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 12)
#elif (OSEE_TC_CORE1_12_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 12)
#else
#error Invalid value for OSEE_TC_CORE1_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 12)
OSEE_DUMMY_ISR(_core1_, 12)
#endif /* OSEE_TC_CORE1_12_ISR_CAT */
#if (defined(OSEE_TC_CORE1_13_ISR_CAT))
#if (OSEE_TC_CORE1_13_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 13)
#elif (OSEE_TC_CORE1_13_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 13)
#else
#error Invalid value for OSEE_TC_CORE1_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 13)
OSEE_DUMMY_ISR(_core1_, 13)
#endif /* OSEE_TC_CORE1_13_ISR_CAT */
#if (defined(OSEE_TC_CORE1_14_ISR_CAT))
#if (OSEE_TC_CORE1_14_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 14)
#elif (OSEE_TC_CORE1_14_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 14)
#else
#error Invalid value for OSEE_TC_CORE1_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 14)
OSEE_DUMMY_ISR(_core1_, 14)
#endif /* OSEE_TC_CORE1_14_ISR_CAT */
#if (defined(OSEE_TC_CORE1_15_ISR_CAT))
#if (OSEE_TC_CORE1_15_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 15)
#elif (OSEE_TC_CORE1_15_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 15)
#else
#error Invalid value for OSEE_TC_CORE1_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 15)
OSEE_DUMMY_ISR(_core1_, 15)
#endif /* OSEE_TC_CORE1_15_ISR_CAT */
#if (defined(OSEE_TC_CORE1_16_ISR_CAT))
#if (OSEE_TC_CORE1_16_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 16)
#elif (OSEE_TC_CORE1_16_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 16)
#else
#error Invalid value for OSEE_TC_CORE1_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 16)
OSEE_DUMMY_ISR(_core1_, 16)
#endif /* OSEE_TC_CORE1_16_ISR_CAT */
#if (defined(OSEE_TC_CORE1_17_ISR_CAT))
#if (OSEE_TC_CORE1_17_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 17)
#elif (OSEE_TC_CORE1_17_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 17)
#else
#error Invalid value for OSEE_TC_CORE1_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 17)
OSEE_DUMMY_ISR(_core1_, 17)
#endif /* OSEE_TC_CORE1_17_ISR_CAT */
#if (defined(OSEE_TC_CORE1_18_ISR_CAT))
#if (OSEE_TC_CORE1_18_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 18)
#elif (OSEE_TC_CORE1_18_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 18)
#else
#error Invalid value for OSEE_TC_CORE1_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 18)
OSEE_DUMMY_ISR(_core1_, 18)
#endif /* OSEE_TC_CORE1_18_ISR_CAT */
#if (defined(OSEE_TC_CORE1_19_ISR_CAT))
#if (OSEE_TC_CORE1_19_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 19)
#elif (OSEE_TC_CORE1_19_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 19)
#else
#error Invalid value for OSEE_TC_CORE1_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 19)
OSEE_DUMMY_ISR(_core1_, 19)
#endif /* OSEE_TC_CORE1_19_ISR_CAT */
#if (defined(OSEE_TC_CORE1_20_ISR_CAT))
#if (OSEE_TC_CORE1_20_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 20)
#elif (OSEE_TC_CORE1_20_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 20)
#else
#error Invalid value for OSEE_TC_CORE1_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 20)
OSEE_DUMMY_ISR(_core1_, 20)
#endif /* OSEE_TC_CORE1_20_ISR_CAT */
#if (defined(OSEE_TC_CORE1_21_ISR_CAT))
#if (OSEE_TC_CORE1_21_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 21)
#elif (OSEE_TC_CORE1_21_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 21)
#else
#error Invalid value for OSEE_TC_CORE1_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 21)
OSEE_DUMMY_ISR(_core1_, 21)
#endif /* OSEE_TC_CORE1_21_ISR_CAT */
#if (defined(OSEE_TC_CORE1_22_ISR_CAT))
#if (OSEE_TC_CORE1_22_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 22)
#elif (OSEE_TC_CORE1_22_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 22)
#else
#error Invalid value for OSEE_TC_CORE1_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 22)
OSEE_DUMMY_ISR(_core1_, 22)
#endif /* OSEE_TC_CORE1_22_ISR_CAT */
#if (defined(OSEE_TC_CORE1_23_ISR_CAT))
#if (OSEE_TC_CORE1_23_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 23)
#elif (OSEE_TC_CORE1_23_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 23)
#else
#error Invalid value for OSEE_TC_CORE1_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 23)
OSEE_DUMMY_ISR(_core1_, 23)
#endif /* OSEE_TC_CORE1_23_ISR_CAT */
#if (defined(OSEE_TC_CORE1_24_ISR_CAT))
#if (OSEE_TC_CORE1_24_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 24)
#elif (OSEE_TC_CORE1_24_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 24)
#else
#error Invalid value for OSEE_TC_CORE1_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 24)
OSEE_DUMMY_ISR(_core1_, 24)
#endif /* OSEE_TC_CORE1_24_ISR_CAT */
#if (defined(OSEE_TC_CORE1_25_ISR_CAT))
#if (OSEE_TC_CORE1_25_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 25)
#elif (OSEE_TC_CORE1_25_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 25)
#else
#error Invalid value for OSEE_TC_CORE1_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 25)
OSEE_DUMMY_ISR(_core1_, 25)
#endif /* OSEE_TC_CORE1_25_ISR_CAT */
#if (defined(OSEE_TC_CORE1_26_ISR_CAT))
#if (OSEE_TC_CORE1_26_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 26)
#elif (OSEE_TC_CORE1_26_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 26)
#else
#error Invalid value for OSEE_TC_CORE1_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 26)
OSEE_DUMMY_ISR(_core1_, 26)
#endif /* OSEE_TC_CORE1_26_ISR_CAT */
#if (defined(OSEE_TC_CORE1_27_ISR_CAT))
#if (OSEE_TC_CORE1_27_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 27)
#elif (OSEE_TC_CORE1_27_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 27)
#else
#error Invalid value for OSEE_TC_CORE1_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 27)
OSEE_DUMMY_ISR(_core1_, 27)
#endif /* OSEE_TC_CORE1_27_ISR_CAT */
#if (defined(OSEE_TC_CORE1_28_ISR_CAT))
#if (OSEE_TC_CORE1_28_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 28)
#elif (OSEE_TC_CORE1_28_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 28)
#else
#error Invalid value for OSEE_TC_CORE1_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 28)
OSEE_DUMMY_ISR(_core1_, 28)
#endif /* OSEE_TC_CORE1_28_ISR_CAT */
#if (defined(OSEE_TC_CORE1_29_ISR_CAT))
#if (OSEE_TC_CORE1_29_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 29)
#elif (OSEE_TC_CORE1_29_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 29)
#else
#error Invalid value for OSEE_TC_CORE1_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 29)
OSEE_DUMMY_ISR(_core1_, 29)
#endif /* OSEE_TC_CORE1_29_ISR_CAT */
#if (defined(OSEE_TC_CORE1_30_ISR_CAT))
#if (OSEE_TC_CORE1_30_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 30)
#elif (OSEE_TC_CORE1_30_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 30)
#else
#error Invalid value for OSEE_TC_CORE1_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 30)
OSEE_DUMMY_ISR(_core1_, 30)
#endif /* OSEE_TC_CORE1_30_ISR_CAT */
#if (defined(OSEE_TC_CORE1_31_ISR_CAT))
#if (OSEE_TC_CORE1_31_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 31)
#elif (OSEE_TC_CORE1_31_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 31)
#else
#error Invalid value for OSEE_TC_CORE1_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 31)
OSEE_DUMMY_ISR(_core1_, 31)
#endif /* OSEE_TC_CORE1_31_ISR_CAT */
#if (defined(OSEE_TC_CORE1_32_ISR_CAT))
#if (OSEE_TC_CORE1_32_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 32)
#elif (OSEE_TC_CORE1_32_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 32)
#else
#error Invalid value for OSEE_TC_CORE1_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 32)
OSEE_DUMMY_ISR(_core1_, 32)
#endif /* OSEE_TC_CORE1_32_ISR_CAT */
#if (defined(OSEE_TC_CORE1_33_ISR_CAT))
#if (OSEE_TC_CORE1_33_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 33)
#elif (OSEE_TC_CORE1_33_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 33)
#else
#error Invalid value for OSEE_TC_CORE1_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 33)
OSEE_DUMMY_ISR(_core1_, 33)
#endif /* OSEE_TC_CORE1_33_ISR_CAT */
#if (defined(OSEE_TC_CORE1_34_ISR_CAT))
#if (OSEE_TC_CORE1_34_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 34)
#elif (OSEE_TC_CORE1_34_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 34)
#else
#error Invalid value for OSEE_TC_CORE1_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 34)
OSEE_DUMMY_ISR(_core1_, 34)
#endif /* OSEE_TC_CORE1_34_ISR_CAT */
#if (defined(OSEE_TC_CORE1_35_ISR_CAT))
#if (OSEE_TC_CORE1_35_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 35)
#elif (OSEE_TC_CORE1_35_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 35)
#else
#error Invalid value for OSEE_TC_CORE1_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 35)
OSEE_DUMMY_ISR(_core1_, 35)
#endif /* OSEE_TC_CORE1_35_ISR_CAT */
#if (defined(OSEE_TC_CORE1_36_ISR_CAT))
#if (OSEE_TC_CORE1_36_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 36)
#elif (OSEE_TC_CORE1_36_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 36)
#else
#error Invalid value for OSEE_TC_CORE1_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 36)
OSEE_DUMMY_ISR(_core1_, 36)
#endif /* OSEE_TC_CORE1_36_ISR_CAT */
#if (defined(OSEE_TC_CORE1_37_ISR_CAT))
#if (OSEE_TC_CORE1_37_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 37)
#elif (OSEE_TC_CORE1_37_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 37)
#else
#error Invalid value for OSEE_TC_CORE1_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 37)
OSEE_DUMMY_ISR(_core1_, 37)
#endif /* OSEE_TC_CORE1_37_ISR_CAT */
#if (defined(OSEE_TC_CORE1_38_ISR_CAT))
#if (OSEE_TC_CORE1_38_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 38)
#elif (OSEE_TC_CORE1_38_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 38)
#else
#error Invalid value for OSEE_TC_CORE1_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 38)
OSEE_DUMMY_ISR(_core1_, 38)
#endif /* OSEE_TC_CORE1_38_ISR_CAT */
#if (defined(OSEE_TC_CORE1_39_ISR_CAT))
#if (OSEE_TC_CORE1_39_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 39)
#elif (OSEE_TC_CORE1_39_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 39)
#else
#error Invalid value for OSEE_TC_CORE1_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 39)
OSEE_DUMMY_ISR(_core1_, 39)
#endif /* OSEE_TC_CORE1_39_ISR_CAT */
#if (defined(OSEE_TC_CORE1_40_ISR_CAT))
#if (OSEE_TC_CORE1_40_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 40)
#elif (OSEE_TC_CORE1_40_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 40)
#else
#error Invalid value for OSEE_TC_CORE1_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 40)
OSEE_DUMMY_ISR(_core1_, 40)
#endif /* OSEE_TC_CORE1_40_ISR_CAT */
#if (defined(OSEE_TC_CORE1_41_ISR_CAT))
#if (OSEE_TC_CORE1_41_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 41)
#elif (OSEE_TC_CORE1_41_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 41)
#else
#error Invalid value for OSEE_TC_CORE1_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 41)
OSEE_DUMMY_ISR(_core1_, 41)
#endif /* OSEE_TC_CORE1_41_ISR_CAT */
#if (defined(OSEE_TC_CORE1_42_ISR_CAT))
#if (OSEE_TC_CORE1_42_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 42)
#elif (OSEE_TC_CORE1_42_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 42)
#else
#error Invalid value for OSEE_TC_CORE1_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 42)
OSEE_DUMMY_ISR(_core1_, 42)
#endif /* OSEE_TC_CORE1_42_ISR_CAT */
#if (defined(OSEE_TC_CORE1_43_ISR_CAT))
#if (OSEE_TC_CORE1_43_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 43)
#elif (OSEE_TC_CORE1_43_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 43)
#else
#error Invalid value for OSEE_TC_CORE1_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 43)
OSEE_DUMMY_ISR(_core1_, 43)
#endif /* OSEE_TC_CORE1_43_ISR_CAT */
#if (defined(OSEE_TC_CORE1_44_ISR_CAT))
#if (OSEE_TC_CORE1_44_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 44)
#elif (OSEE_TC_CORE1_44_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 44)
#else
#error Invalid value for OSEE_TC_CORE1_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 44)
OSEE_DUMMY_ISR(_core1_, 44)
#endif /* OSEE_TC_CORE1_44_ISR_CAT */
#if (defined(OSEE_TC_CORE1_45_ISR_CAT))
#if (OSEE_TC_CORE1_45_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 45)
#elif (OSEE_TC_CORE1_45_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 45)
#else
#error Invalid value for OSEE_TC_CORE1_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 45)
OSEE_DUMMY_ISR(_core1_, 45)
#endif /* OSEE_TC_CORE1_45_ISR_CAT */
#if (defined(OSEE_TC_CORE1_46_ISR_CAT))
#if (OSEE_TC_CORE1_46_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 46)
#elif (OSEE_TC_CORE1_46_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 46)
#else
#error Invalid value for OSEE_TC_CORE1_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 46)
OSEE_DUMMY_ISR(_core1_, 46)
#endif /* OSEE_TC_CORE1_46_ISR_CAT */
#if (defined(OSEE_TC_CORE1_47_ISR_CAT))
#if (OSEE_TC_CORE1_47_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 47)
#elif (OSEE_TC_CORE1_47_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 47)
#else
#error Invalid value for OSEE_TC_CORE1_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 47)
OSEE_DUMMY_ISR(_core1_, 47)
#endif /* OSEE_TC_CORE1_47_ISR_CAT */
#if (defined(OSEE_TC_CORE1_48_ISR_CAT))
#if (OSEE_TC_CORE1_48_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 48)
#elif (OSEE_TC_CORE1_48_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 48)
#else
#error Invalid value for OSEE_TC_CORE1_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 48)
OSEE_DUMMY_ISR(_core1_, 48)
#endif /* OSEE_TC_CORE1_48_ISR_CAT */
#if (defined(OSEE_TC_CORE1_49_ISR_CAT))
#if (OSEE_TC_CORE1_49_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 49)
#elif (OSEE_TC_CORE1_49_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 49)
#else
#error Invalid value for OSEE_TC_CORE1_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 49)
OSEE_DUMMY_ISR(_core1_, 49)
#endif /* OSEE_TC_CORE1_49_ISR_CAT */
#if (defined(OSEE_TC_CORE1_50_ISR_CAT))
#if (OSEE_TC_CORE1_50_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 50)
#elif (OSEE_TC_CORE1_50_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 50)
#else
#error Invalid value for OSEE_TC_CORE1_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 50)
OSEE_DUMMY_ISR(_core1_, 50)
#endif /* OSEE_TC_CORE1_50_ISR_CAT */
#if (defined(OSEE_TC_CORE1_51_ISR_CAT))
#if (OSEE_TC_CORE1_51_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 51)
#elif (OSEE_TC_CORE1_51_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 51)
#else
#error Invalid value for OSEE_TC_CORE1_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 51)
OSEE_DUMMY_ISR(_core1_, 51)
#endif /* OSEE_TC_CORE1_51_ISR_CAT */
#if (defined(OSEE_TC_CORE1_52_ISR_CAT))
#if (OSEE_TC_CORE1_52_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 52)
#elif (OSEE_TC_CORE1_52_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 52)
#else
#error Invalid value for OSEE_TC_CORE1_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 52)
OSEE_DUMMY_ISR(_core1_, 52)
#endif /* OSEE_TC_CORE1_52_ISR_CAT */
#if (defined(OSEE_TC_CORE1_53_ISR_CAT))
#if (OSEE_TC_CORE1_53_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 53)
#elif (OSEE_TC_CORE1_53_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 53)
#else
#error Invalid value for OSEE_TC_CORE1_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 53)
OSEE_DUMMY_ISR(_core1_, 53)
#endif /* OSEE_TC_CORE1_53_ISR_CAT */
#if (defined(OSEE_TC_CORE1_54_ISR_CAT))
#if (OSEE_TC_CORE1_54_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 54)
#elif (OSEE_TC_CORE1_54_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 54)
#else
#error Invalid value for OSEE_TC_CORE1_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 54)
OSEE_DUMMY_ISR(_core1_, 54)
#endif /* OSEE_TC_CORE1_54_ISR_CAT */
#if (defined(OSEE_TC_CORE1_55_ISR_CAT))
#if (OSEE_TC_CORE1_55_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 55)
#elif (OSEE_TC_CORE1_55_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 55)
#else
#error Invalid value for OSEE_TC_CORE1_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 55)
OSEE_DUMMY_ISR(_core1_, 55)
#endif /* OSEE_TC_CORE1_55_ISR_CAT */
#if (defined(OSEE_TC_CORE1_56_ISR_CAT))
#if (OSEE_TC_CORE1_56_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 56)
#elif (OSEE_TC_CORE1_56_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 56)
#else
#error Invalid value for OSEE_TC_CORE1_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 56)
OSEE_DUMMY_ISR(_core1_, 56)
#endif /* OSEE_TC_CORE1_56_ISR_CAT */
#if (defined(OSEE_TC_CORE1_57_ISR_CAT))
#if (OSEE_TC_CORE1_57_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 57)
#elif (OSEE_TC_CORE1_57_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 57)
#else
#error Invalid value for OSEE_TC_CORE1_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 57)
OSEE_DUMMY_ISR(_core1_, 57)
#endif /* OSEE_TC_CORE1_57_ISR_CAT */
#if (defined(OSEE_TC_CORE1_58_ISR_CAT))
#if (OSEE_TC_CORE1_58_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 58)
#elif (OSEE_TC_CORE1_58_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 58)
#else
#error Invalid value for OSEE_TC_CORE1_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 58)
OSEE_DUMMY_ISR(_core1_, 58)
#endif /* OSEE_TC_CORE1_58_ISR_CAT */
#if (defined(OSEE_TC_CORE1_59_ISR_CAT))
#if (OSEE_TC_CORE1_59_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 59)
#elif (OSEE_TC_CORE1_59_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 59)
#else
#error Invalid value for OSEE_TC_CORE1_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 59)
OSEE_DUMMY_ISR(_core1_, 59)
#endif /* OSEE_TC_CORE1_59_ISR_CAT */
#if (defined(OSEE_TC_CORE1_60_ISR_CAT))
#if (OSEE_TC_CORE1_60_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 60)
#elif (OSEE_TC_CORE1_60_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 60)
#else
#error Invalid value for OSEE_TC_CORE1_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 60)
OSEE_DUMMY_ISR(_core1_, 60)
#endif /* OSEE_TC_CORE1_60_ISR_CAT */
#if (defined(OSEE_TC_CORE1_61_ISR_CAT))
#if (OSEE_TC_CORE1_61_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 61)
#elif (OSEE_TC_CORE1_61_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 61)
#else
#error Invalid value for OSEE_TC_CORE1_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 61)
OSEE_DUMMY_ISR(_core1_, 61)
#endif /* OSEE_TC_CORE1_61_ISR_CAT */
#if (defined(OSEE_TC_CORE1_62_ISR_CAT))
#if (OSEE_TC_CORE1_62_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 62)
#elif (OSEE_TC_CORE1_62_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 62)
#else
#error Invalid value for OSEE_TC_CORE1_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 62)
OSEE_DUMMY_ISR(_core1_, 62)
#endif /* OSEE_TC_CORE1_62_ISR_CAT */
#if (defined(OSEE_TC_CORE1_63_ISR_CAT))
#if (OSEE_TC_CORE1_63_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 63)
#elif (OSEE_TC_CORE1_63_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 63)
#else
#error Invalid value for OSEE_TC_CORE1_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 63)
OSEE_DUMMY_ISR(_core1_, 63)
#endif /* OSEE_TC_CORE1_63_ISR_CAT */
#if (defined(OSEE_TC_CORE1_64_ISR_CAT))
#if (OSEE_TC_CORE1_64_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 64)
#elif (OSEE_TC_CORE1_64_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 64)
#else
#error Invalid value for OSEE_TC_CORE1_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 64)
OSEE_DUMMY_ISR(_core1_, 64)
#endif /* OSEE_TC_CORE1_64_ISR_CAT */
#if (defined(OSEE_TC_CORE1_65_ISR_CAT))
#if (OSEE_TC_CORE1_65_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 65)
#elif (OSEE_TC_CORE1_65_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 65)
#else
#error Invalid value for OSEE_TC_CORE1_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 65)
OSEE_DUMMY_ISR(_core1_, 65)
#endif /* OSEE_TC_CORE1_65_ISR_CAT */
#if (defined(OSEE_TC_CORE1_66_ISR_CAT))
#if (OSEE_TC_CORE1_66_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 66)
#elif (OSEE_TC_CORE1_66_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 66)
#else
#error Invalid value for OSEE_TC_CORE1_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 66)
OSEE_DUMMY_ISR(_core1_, 66)
#endif /* OSEE_TC_CORE1_66_ISR_CAT */
#if (defined(OSEE_TC_CORE1_67_ISR_CAT))
#if (OSEE_TC_CORE1_67_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 67)
#elif (OSEE_TC_CORE1_67_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 67)
#else
#error Invalid value for OSEE_TC_CORE1_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 67)
OSEE_DUMMY_ISR(_core1_, 67)
#endif /* OSEE_TC_CORE1_67_ISR_CAT */
#if (defined(OSEE_TC_CORE1_68_ISR_CAT))
#if (OSEE_TC_CORE1_68_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 68)
#elif (OSEE_TC_CORE1_68_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 68)
#else
#error Invalid value for OSEE_TC_CORE1_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 68)
OSEE_DUMMY_ISR(_core1_, 68)
#endif /* OSEE_TC_CORE1_68_ISR_CAT */
#if (defined(OSEE_TC_CORE1_69_ISR_CAT))
#if (OSEE_TC_CORE1_69_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 69)
#elif (OSEE_TC_CORE1_69_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 69)
#else
#error Invalid value for OSEE_TC_CORE1_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 69)
OSEE_DUMMY_ISR(_core1_, 69)
#endif /* OSEE_TC_CORE1_69_ISR_CAT */
#if (defined(OSEE_TC_CORE1_70_ISR_CAT))
#if (OSEE_TC_CORE1_70_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 70)
#elif (OSEE_TC_CORE1_70_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 70)
#else
#error Invalid value for OSEE_TC_CORE1_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 70)
OSEE_DUMMY_ISR(_core1_, 70)
#endif /* OSEE_TC_CORE1_70_ISR_CAT */
#if (defined(OSEE_TC_CORE1_71_ISR_CAT))
#if (OSEE_TC_CORE1_71_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 71)
#elif (OSEE_TC_CORE1_71_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 71)
#else
#error Invalid value for OSEE_TC_CORE1_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 71)
OSEE_DUMMY_ISR(_core1_, 71)
#endif /* OSEE_TC_CORE1_71_ISR_CAT */
#if (defined(OSEE_TC_CORE1_72_ISR_CAT))
#if (OSEE_TC_CORE1_72_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 72)
#elif (OSEE_TC_CORE1_72_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 72)
#else
#error Invalid value for OSEE_TC_CORE1_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 72)
OSEE_DUMMY_ISR(_core1_, 72)
#endif /* OSEE_TC_CORE1_72_ISR_CAT */
#if (defined(OSEE_TC_CORE1_73_ISR_CAT))
#if (OSEE_TC_CORE1_73_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 73)
#elif (OSEE_TC_CORE1_73_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 73)
#else
#error Invalid value for OSEE_TC_CORE1_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 73)
OSEE_DUMMY_ISR(_core1_, 73)
#endif /* OSEE_TC_CORE1_73_ISR_CAT */
#if (defined(OSEE_TC_CORE1_74_ISR_CAT))
#if (OSEE_TC_CORE1_74_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 74)
#elif (OSEE_TC_CORE1_74_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 74)
#else
#error Invalid value for OSEE_TC_CORE1_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 74)
OSEE_DUMMY_ISR(_core1_, 74)
#endif /* OSEE_TC_CORE1_74_ISR_CAT */
#if (defined(OSEE_TC_CORE1_75_ISR_CAT))
#if (OSEE_TC_CORE1_75_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 75)
#elif (OSEE_TC_CORE1_75_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 75)
#else
#error Invalid value for OSEE_TC_CORE1_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 75)
OSEE_DUMMY_ISR(_core1_, 75)
#endif /* OSEE_TC_CORE1_75_ISR_CAT */
#if (defined(OSEE_TC_CORE1_76_ISR_CAT))
#if (OSEE_TC_CORE1_76_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 76)
#elif (OSEE_TC_CORE1_76_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 76)
#else
#error Invalid value for OSEE_TC_CORE1_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 76)
OSEE_DUMMY_ISR(_core1_, 76)
#endif /* OSEE_TC_CORE1_76_ISR_CAT */
#if (defined(OSEE_TC_CORE1_77_ISR_CAT))
#if (OSEE_TC_CORE1_77_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 77)
#elif (OSEE_TC_CORE1_77_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 77)
#else
#error Invalid value for OSEE_TC_CORE1_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 77)
OSEE_DUMMY_ISR(_core1_, 77)
#endif /* OSEE_TC_CORE1_77_ISR_CAT */
#if (defined(OSEE_TC_CORE1_78_ISR_CAT))
#if (OSEE_TC_CORE1_78_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 78)
#elif (OSEE_TC_CORE1_78_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 78)
#else
#error Invalid value for OSEE_TC_CORE1_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 78)
OSEE_DUMMY_ISR(_core1_, 78)
#endif /* OSEE_TC_CORE1_78_ISR_CAT */
#if (defined(OSEE_TC_CORE1_79_ISR_CAT))
#if (OSEE_TC_CORE1_79_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 79)
#elif (OSEE_TC_CORE1_79_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 79)
#else
#error Invalid value for OSEE_TC_CORE1_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 79)
OSEE_DUMMY_ISR(_core1_, 79)
#endif /* OSEE_TC_CORE1_79_ISR_CAT */
#if (defined(OSEE_TC_CORE1_80_ISR_CAT))
#if (OSEE_TC_CORE1_80_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 80)
#elif (OSEE_TC_CORE1_80_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 80)
#else
#error Invalid value for OSEE_TC_CORE1_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 80)
OSEE_DUMMY_ISR(_core1_, 80)
#endif /* OSEE_TC_CORE1_80_ISR_CAT */
#if (defined(OSEE_TC_CORE1_81_ISR_CAT))
#if (OSEE_TC_CORE1_81_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 81)
#elif (OSEE_TC_CORE1_81_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 81)
#else
#error Invalid value for OSEE_TC_CORE1_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 81)
OSEE_DUMMY_ISR(_core1_, 81)
#endif /* OSEE_TC_CORE1_81_ISR_CAT */
#if (defined(OSEE_TC_CORE1_82_ISR_CAT))
#if (OSEE_TC_CORE1_82_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 82)
#elif (OSEE_TC_CORE1_82_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 82)
#else
#error Invalid value for OSEE_TC_CORE1_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 82)
OSEE_DUMMY_ISR(_core1_, 82)
#endif /* OSEE_TC_CORE1_82_ISR_CAT */
#if (defined(OSEE_TC_CORE1_83_ISR_CAT))
#if (OSEE_TC_CORE1_83_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 83)
#elif (OSEE_TC_CORE1_83_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 83)
#else
#error Invalid value for OSEE_TC_CORE1_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 83)
OSEE_DUMMY_ISR(_core1_, 83)
#endif /* OSEE_TC_CORE1_83_ISR_CAT */
#if (defined(OSEE_TC_CORE1_84_ISR_CAT))
#if (OSEE_TC_CORE1_84_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 84)
#elif (OSEE_TC_CORE1_84_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 84)
#else
#error Invalid value for OSEE_TC_CORE1_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 84)
OSEE_DUMMY_ISR(_core1_, 84)
#endif /* OSEE_TC_CORE1_84_ISR_CAT */
#if (defined(OSEE_TC_CORE1_85_ISR_CAT))
#if (OSEE_TC_CORE1_85_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 85)
#elif (OSEE_TC_CORE1_85_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 85)
#else
#error Invalid value for OSEE_TC_CORE1_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 85)
OSEE_DUMMY_ISR(_core1_, 85)
#endif /* OSEE_TC_CORE1_85_ISR_CAT */
#if (defined(OSEE_TC_CORE1_86_ISR_CAT))
#if (OSEE_TC_CORE1_86_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 86)
#elif (OSEE_TC_CORE1_86_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 86)
#else
#error Invalid value for OSEE_TC_CORE1_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 86)
OSEE_DUMMY_ISR(_core1_, 86)
#endif /* OSEE_TC_CORE1_86_ISR_CAT */
#if (defined(OSEE_TC_CORE1_87_ISR_CAT))
#if (OSEE_TC_CORE1_87_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 87)
#elif (OSEE_TC_CORE1_87_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 87)
#else
#error Invalid value for OSEE_TC_CORE1_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 87)
OSEE_DUMMY_ISR(_core1_, 87)
#endif /* OSEE_TC_CORE1_87_ISR_CAT */
#if (defined(OSEE_TC_CORE1_88_ISR_CAT))
#if (OSEE_TC_CORE1_88_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 88)
#elif (OSEE_TC_CORE1_88_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 88)
#else
#error Invalid value for OSEE_TC_CORE1_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 88)
OSEE_DUMMY_ISR(_core1_, 88)
#endif /* OSEE_TC_CORE1_88_ISR_CAT */
#if (defined(OSEE_TC_CORE1_89_ISR_CAT))
#if (OSEE_TC_CORE1_89_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 89)
#elif (OSEE_TC_CORE1_89_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 89)
#else
#error Invalid value for OSEE_TC_CORE1_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 89)
OSEE_DUMMY_ISR(_core1_, 89)
#endif /* OSEE_TC_CORE1_89_ISR_CAT */
#if (defined(OSEE_TC_CORE1_90_ISR_CAT))
#if (OSEE_TC_CORE1_90_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 90)
#elif (OSEE_TC_CORE1_90_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 90)
#else
#error Invalid value for OSEE_TC_CORE1_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 90)
OSEE_DUMMY_ISR(_core1_, 90)
#endif /* OSEE_TC_CORE1_90_ISR_CAT */
#if (defined(OSEE_TC_CORE1_91_ISR_CAT))
#if (OSEE_TC_CORE1_91_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 91)
#elif (OSEE_TC_CORE1_91_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 91)
#else
#error Invalid value for OSEE_TC_CORE1_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 91)
OSEE_DUMMY_ISR(_core1_, 91)
#endif /* OSEE_TC_CORE1_91_ISR_CAT */
#if (defined(OSEE_TC_CORE1_92_ISR_CAT))
#if (OSEE_TC_CORE1_92_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 92)
#elif (OSEE_TC_CORE1_92_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 92)
#else
#error Invalid value for OSEE_TC_CORE1_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 92)
OSEE_DUMMY_ISR(_core1_, 92)
#endif /* OSEE_TC_CORE1_92_ISR_CAT */
#if (defined(OSEE_TC_CORE1_93_ISR_CAT))
#if (OSEE_TC_CORE1_93_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 93)
#elif (OSEE_TC_CORE1_93_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 93)
#else
#error Invalid value for OSEE_TC_CORE1_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 93)
OSEE_DUMMY_ISR(_core1_, 93)
#endif /* OSEE_TC_CORE1_93_ISR_CAT */
#if (defined(OSEE_TC_CORE1_94_ISR_CAT))
#if (OSEE_TC_CORE1_94_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 94)
#elif (OSEE_TC_CORE1_94_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 94)
#else
#error Invalid value for OSEE_TC_CORE1_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 94)
OSEE_DUMMY_ISR(_core1_, 94)
#endif /* OSEE_TC_CORE1_94_ISR_CAT */
#if (defined(OSEE_TC_CORE1_95_ISR_CAT))
#if (OSEE_TC_CORE1_95_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 95)
#elif (OSEE_TC_CORE1_95_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 95)
#else
#error Invalid value for OSEE_TC_CORE1_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 95)
OSEE_DUMMY_ISR(_core1_, 95)
#endif /* OSEE_TC_CORE1_95_ISR_CAT */
#if (defined(OSEE_TC_CORE1_96_ISR_CAT))
#if (OSEE_TC_CORE1_96_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 96)
#elif (OSEE_TC_CORE1_96_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 96)
#else
#error Invalid value for OSEE_TC_CORE1_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 96)
OSEE_DUMMY_ISR(_core1_, 96)
#endif /* OSEE_TC_CORE1_96_ISR_CAT */
#if (defined(OSEE_TC_CORE1_97_ISR_CAT))
#if (OSEE_TC_CORE1_97_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 97)
#elif (OSEE_TC_CORE1_97_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 97)
#else
#error Invalid value for OSEE_TC_CORE1_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 97)
OSEE_DUMMY_ISR(_core1_, 97)
#endif /* OSEE_TC_CORE1_97_ISR_CAT */
#if (defined(OSEE_TC_CORE1_98_ISR_CAT))
#if (OSEE_TC_CORE1_98_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 98)
#elif (OSEE_TC_CORE1_98_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 98)
#else
#error Invalid value for OSEE_TC_CORE1_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 98)
OSEE_DUMMY_ISR(_core1_, 98)
#endif /* OSEE_TC_CORE1_98_ISR_CAT */
#if (defined(OSEE_TC_CORE1_99_ISR_CAT))
#if (OSEE_TC_CORE1_99_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 99)
#elif (OSEE_TC_CORE1_99_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 99)
#else
#error Invalid value for OSEE_TC_CORE1_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 99)
OSEE_DUMMY_ISR(_core1_, 99)
#endif /* OSEE_TC_CORE1_99_ISR_CAT */
#if (defined(OSEE_TC_CORE1_100_ISR_CAT))
#if (OSEE_TC_CORE1_100_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 100)
#elif (OSEE_TC_CORE1_100_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 100)
#else
#error Invalid value for OSEE_TC_CORE1_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 100)
OSEE_DUMMY_ISR(_core1_, 100)
#endif /* OSEE_TC_CORE1_100_ISR_CAT */
#if (defined(OSEE_TC_CORE1_101_ISR_CAT))
#if (OSEE_TC_CORE1_101_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 101)
#elif (OSEE_TC_CORE1_101_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 101)
#else
#error Invalid value for OSEE_TC_CORE1_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 101)
OSEE_DUMMY_ISR(_core1_, 101)
#endif /* OSEE_TC_CORE1_101_ISR_CAT */
#if (defined(OSEE_TC_CORE1_102_ISR_CAT))
#if (OSEE_TC_CORE1_102_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 102)
#elif (OSEE_TC_CORE1_102_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 102)
#else
#error Invalid value for OSEE_TC_CORE1_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 102)
OSEE_DUMMY_ISR(_core1_, 102)
#endif /* OSEE_TC_CORE1_102_ISR_CAT */
#if (defined(OSEE_TC_CORE1_103_ISR_CAT))
#if (OSEE_TC_CORE1_103_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 103)
#elif (OSEE_TC_CORE1_103_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 103)
#else
#error Invalid value for OSEE_TC_CORE1_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 103)
OSEE_DUMMY_ISR(_core1_, 103)
#endif /* OSEE_TC_CORE1_103_ISR_CAT */
#if (defined(OSEE_TC_CORE1_104_ISR_CAT))
#if (OSEE_TC_CORE1_104_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 104)
#elif (OSEE_TC_CORE1_104_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 104)
#else
#error Invalid value for OSEE_TC_CORE1_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 104)
OSEE_DUMMY_ISR(_core1_, 104)
#endif /* OSEE_TC_CORE1_104_ISR_CAT */
#if (defined(OSEE_TC_CORE1_105_ISR_CAT))
#if (OSEE_TC_CORE1_105_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 105)
#elif (OSEE_TC_CORE1_105_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 105)
#else
#error Invalid value for OSEE_TC_CORE1_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 105)
OSEE_DUMMY_ISR(_core1_, 105)
#endif /* OSEE_TC_CORE1_105_ISR_CAT */
#if (defined(OSEE_TC_CORE1_106_ISR_CAT))
#if (OSEE_TC_CORE1_106_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 106)
#elif (OSEE_TC_CORE1_106_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 106)
#else
#error Invalid value for OSEE_TC_CORE1_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 106)
OSEE_DUMMY_ISR(_core1_, 106)
#endif /* OSEE_TC_CORE1_106_ISR_CAT */
#if (defined(OSEE_TC_CORE1_107_ISR_CAT))
#if (OSEE_TC_CORE1_107_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 107)
#elif (OSEE_TC_CORE1_107_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 107)
#else
#error Invalid value for OSEE_TC_CORE1_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 107)
OSEE_DUMMY_ISR(_core1_, 107)
#endif /* OSEE_TC_CORE1_107_ISR_CAT */
#if (defined(OSEE_TC_CORE1_108_ISR_CAT))
#if (OSEE_TC_CORE1_108_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 108)
#elif (OSEE_TC_CORE1_108_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 108)
#else
#error Invalid value for OSEE_TC_CORE1_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 108)
OSEE_DUMMY_ISR(_core1_, 108)
#endif /* OSEE_TC_CORE1_108_ISR_CAT */
#if (defined(OSEE_TC_CORE1_109_ISR_CAT))
#if (OSEE_TC_CORE1_109_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 109)
#elif (OSEE_TC_CORE1_109_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 109)
#else
#error Invalid value for OSEE_TC_CORE1_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 109)
OSEE_DUMMY_ISR(_core1_, 109)
#endif /* OSEE_TC_CORE1_109_ISR_CAT */
#if (defined(OSEE_TC_CORE1_110_ISR_CAT))
#if (OSEE_TC_CORE1_110_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 110)
#elif (OSEE_TC_CORE1_110_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 110)
#else
#error Invalid value for OSEE_TC_CORE1_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 110)
OSEE_DUMMY_ISR(_core1_, 110)
#endif /* OSEE_TC_CORE1_110_ISR_CAT */
#if (defined(OSEE_TC_CORE1_111_ISR_CAT))
#if (OSEE_TC_CORE1_111_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 111)
#elif (OSEE_TC_CORE1_111_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 111)
#else
#error Invalid value for OSEE_TC_CORE1_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 111)
OSEE_DUMMY_ISR(_core1_, 111)
#endif /* OSEE_TC_CORE1_111_ISR_CAT */
#if (defined(OSEE_TC_CORE1_112_ISR_CAT))
#if (OSEE_TC_CORE1_112_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 112)
#elif (OSEE_TC_CORE1_112_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 112)
#else
#error Invalid value for OSEE_TC_CORE1_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 112)
OSEE_DUMMY_ISR(_core1_, 112)
#endif /* OSEE_TC_CORE1_112_ISR_CAT */
#if (defined(OSEE_TC_CORE1_113_ISR_CAT))
#if (OSEE_TC_CORE1_113_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 113)
#elif (OSEE_TC_CORE1_113_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 113)
#else
#error Invalid value for OSEE_TC_CORE1_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 113)
OSEE_DUMMY_ISR(_core1_, 113)
#endif /* OSEE_TC_CORE1_113_ISR_CAT */
#if (defined(OSEE_TC_CORE1_114_ISR_CAT))
#if (OSEE_TC_CORE1_114_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 114)
#elif (OSEE_TC_CORE1_114_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 114)
#else
#error Invalid value for OSEE_TC_CORE1_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 114)
OSEE_DUMMY_ISR(_core1_, 114)
#endif /* OSEE_TC_CORE1_114_ISR_CAT */
#if (defined(OSEE_TC_CORE1_115_ISR_CAT))
#if (OSEE_TC_CORE1_115_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 115)
#elif (OSEE_TC_CORE1_115_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 115)
#else
#error Invalid value for OSEE_TC_CORE1_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 115)
OSEE_DUMMY_ISR(_core1_, 115)
#endif /* OSEE_TC_CORE1_115_ISR_CAT */
#if (defined(OSEE_TC_CORE1_116_ISR_CAT))
#if (OSEE_TC_CORE1_116_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 116)
#elif (OSEE_TC_CORE1_116_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 116)
#else
#error Invalid value for OSEE_TC_CORE1_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 116)
OSEE_DUMMY_ISR(_core1_, 116)
#endif /* OSEE_TC_CORE1_116_ISR_CAT */
#if (defined(OSEE_TC_CORE1_117_ISR_CAT))
#if (OSEE_TC_CORE1_117_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 117)
#elif (OSEE_TC_CORE1_117_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 117)
#else
#error Invalid value for OSEE_TC_CORE1_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 117)
OSEE_DUMMY_ISR(_core1_, 117)
#endif /* OSEE_TC_CORE1_117_ISR_CAT */
#if (defined(OSEE_TC_CORE1_118_ISR_CAT))
#if (OSEE_TC_CORE1_118_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 118)
#elif (OSEE_TC_CORE1_118_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 118)
#else
#error Invalid value for OSEE_TC_CORE1_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 118)
OSEE_DUMMY_ISR(_core1_, 118)
#endif /* OSEE_TC_CORE1_118_ISR_CAT */
#if (defined(OSEE_TC_CORE1_119_ISR_CAT))
#if (OSEE_TC_CORE1_119_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 119)
#elif (OSEE_TC_CORE1_119_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 119)
#else
#error Invalid value for OSEE_TC_CORE1_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 119)
OSEE_DUMMY_ISR(_core1_, 119)
#endif /* OSEE_TC_CORE1_119_ISR_CAT */
#if (defined(OSEE_TC_CORE1_120_ISR_CAT))
#if (OSEE_TC_CORE1_120_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 120)
#elif (OSEE_TC_CORE1_120_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 120)
#else
#error Invalid value for OSEE_TC_CORE1_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 120)
OSEE_DUMMY_ISR(_core1_, 120)
#endif /* OSEE_TC_CORE1_120_ISR_CAT */
#if (defined(OSEE_TC_CORE1_121_ISR_CAT))
#if (OSEE_TC_CORE1_121_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 121)
#elif (OSEE_TC_CORE1_121_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 121)
#else
#error Invalid value for OSEE_TC_CORE1_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 121)
OSEE_DUMMY_ISR(_core1_, 121)
#endif /* OSEE_TC_CORE1_121_ISR_CAT */
#if (defined(OSEE_TC_CORE1_122_ISR_CAT))
#if (OSEE_TC_CORE1_122_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 122)
#elif (OSEE_TC_CORE1_122_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 122)
#else
#error Invalid value for OSEE_TC_CORE1_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 122)
OSEE_DUMMY_ISR(_core1_, 122)
#endif /* OSEE_TC_CORE1_122_ISR_CAT */
#if (defined(OSEE_TC_CORE1_123_ISR_CAT))
#if (OSEE_TC_CORE1_123_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 123)
#elif (OSEE_TC_CORE1_123_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 123)
#else
#error Invalid value for OSEE_TC_CORE1_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 123)
OSEE_DUMMY_ISR(_core1_, 123)
#endif /* OSEE_TC_CORE1_123_ISR_CAT */
#if (defined(OSEE_TC_CORE1_124_ISR_CAT))
#if (OSEE_TC_CORE1_124_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 124)
#elif (OSEE_TC_CORE1_124_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 124)
#else
#error Invalid value for OSEE_TC_CORE1_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 124)
OSEE_DUMMY_ISR(_core1_, 124)
#endif /* OSEE_TC_CORE1_124_ISR_CAT */
#if (defined(OSEE_TC_CORE1_125_ISR_CAT))
#if (OSEE_TC_CORE1_125_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 125)
#elif (OSEE_TC_CORE1_125_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 125)
#else
#error Invalid value for OSEE_TC_CORE1_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 125)
OSEE_DUMMY_ISR(_core1_, 125)
#endif /* OSEE_TC_CORE1_125_ISR_CAT */
#if (defined(OSEE_TC_CORE1_126_ISR_CAT))
#if (OSEE_TC_CORE1_126_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 126)
#elif (OSEE_TC_CORE1_126_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 126)
#else
#error Invalid value for OSEE_TC_CORE1_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 126)
OSEE_DUMMY_ISR(_core1_, 126)
#endif /* OSEE_TC_CORE1_126_ISR_CAT */
#if (defined(OSEE_TC_CORE1_127_ISR_CAT))
#if (OSEE_TC_CORE1_127_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 127)
#elif (OSEE_TC_CORE1_127_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 127)
#else
#error Invalid value for OSEE_TC_CORE1_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 127)
OSEE_DUMMY_ISR(_core1_, 127)
#endif /* OSEE_TC_CORE1_127_ISR_CAT */
#if (defined(OSEE_TC_CORE1_128_ISR_CAT))
#if (OSEE_TC_CORE1_128_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 128)
#elif (OSEE_TC_CORE1_128_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 128)
#else
#error Invalid value for OSEE_TC_CORE1_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 128)
OSEE_DUMMY_ISR(_core1_, 128)
#endif /* OSEE_TC_CORE1_128_ISR_CAT */
#if (defined(OSEE_TC_CORE1_129_ISR_CAT))
#if (OSEE_TC_CORE1_129_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 129)
#elif (OSEE_TC_CORE1_129_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 129)
#else
#error Invalid value for OSEE_TC_CORE1_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 129)
OSEE_DUMMY_ISR(_core1_, 129)
#endif /* OSEE_TC_CORE1_129_ISR_CAT */
#if (defined(OSEE_TC_CORE1_130_ISR_CAT))
#if (OSEE_TC_CORE1_130_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 130)
#elif (OSEE_TC_CORE1_130_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 130)
#else
#error Invalid value for OSEE_TC_CORE1_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 130)
OSEE_DUMMY_ISR(_core1_, 130)
#endif /* OSEE_TC_CORE1_130_ISR_CAT */
#if (defined(OSEE_TC_CORE1_131_ISR_CAT))
#if (OSEE_TC_CORE1_131_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 131)
#elif (OSEE_TC_CORE1_131_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 131)
#else
#error Invalid value for OSEE_TC_CORE1_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 131)
OSEE_DUMMY_ISR(_core1_, 131)
#endif /* OSEE_TC_CORE1_131_ISR_CAT */
#if (defined(OSEE_TC_CORE1_132_ISR_CAT))
#if (OSEE_TC_CORE1_132_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 132)
#elif (OSEE_TC_CORE1_132_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 132)
#else
#error Invalid value for OSEE_TC_CORE1_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 132)
OSEE_DUMMY_ISR(_core1_, 132)
#endif /* OSEE_TC_CORE1_132_ISR_CAT */
#if (defined(OSEE_TC_CORE1_133_ISR_CAT))
#if (OSEE_TC_CORE1_133_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 133)
#elif (OSEE_TC_CORE1_133_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 133)
#else
#error Invalid value for OSEE_TC_CORE1_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 133)
OSEE_DUMMY_ISR(_core1_, 133)
#endif /* OSEE_TC_CORE1_133_ISR_CAT */
#if (defined(OSEE_TC_CORE1_134_ISR_CAT))
#if (OSEE_TC_CORE1_134_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 134)
#elif (OSEE_TC_CORE1_134_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 134)
#else
#error Invalid value for OSEE_TC_CORE1_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 134)
OSEE_DUMMY_ISR(_core1_, 134)
#endif /* OSEE_TC_CORE1_134_ISR_CAT */
#if (defined(OSEE_TC_CORE1_135_ISR_CAT))
#if (OSEE_TC_CORE1_135_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 135)
#elif (OSEE_TC_CORE1_135_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 135)
#else
#error Invalid value for OSEE_TC_CORE1_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 135)
OSEE_DUMMY_ISR(_core1_, 135)
#endif /* OSEE_TC_CORE1_135_ISR_CAT */
#if (defined(OSEE_TC_CORE1_136_ISR_CAT))
#if (OSEE_TC_CORE1_136_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 136)
#elif (OSEE_TC_CORE1_136_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 136)
#else
#error Invalid value for OSEE_TC_CORE1_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 136)
OSEE_DUMMY_ISR(_core1_, 136)
#endif /* OSEE_TC_CORE1_136_ISR_CAT */
#if (defined(OSEE_TC_CORE1_137_ISR_CAT))
#if (OSEE_TC_CORE1_137_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 137)
#elif (OSEE_TC_CORE1_137_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 137)
#else
#error Invalid value for OSEE_TC_CORE1_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 137)
OSEE_DUMMY_ISR(_core1_, 137)
#endif /* OSEE_TC_CORE1_137_ISR_CAT */
#if (defined(OSEE_TC_CORE1_138_ISR_CAT))
#if (OSEE_TC_CORE1_138_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 138)
#elif (OSEE_TC_CORE1_138_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 138)
#else
#error Invalid value for OSEE_TC_CORE1_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 138)
OSEE_DUMMY_ISR(_core1_, 138)
#endif /* OSEE_TC_CORE1_138_ISR_CAT */
#if (defined(OSEE_TC_CORE1_139_ISR_CAT))
#if (OSEE_TC_CORE1_139_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 139)
#elif (OSEE_TC_CORE1_139_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 139)
#else
#error Invalid value for OSEE_TC_CORE1_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 139)
OSEE_DUMMY_ISR(_core1_, 139)
#endif /* OSEE_TC_CORE1_139_ISR_CAT */
#if (defined(OSEE_TC_CORE1_140_ISR_CAT))
#if (OSEE_TC_CORE1_140_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 140)
#elif (OSEE_TC_CORE1_140_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 140)
#else
#error Invalid value for OSEE_TC_CORE1_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 140)
OSEE_DUMMY_ISR(_core1_, 140)
#endif /* OSEE_TC_CORE1_140_ISR_CAT */
#if (defined(OSEE_TC_CORE1_141_ISR_CAT))
#if (OSEE_TC_CORE1_141_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 141)
#elif (OSEE_TC_CORE1_141_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 141)
#else
#error Invalid value for OSEE_TC_CORE1_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 141)
OSEE_DUMMY_ISR(_core1_, 141)
#endif /* OSEE_TC_CORE1_141_ISR_CAT */
#if (defined(OSEE_TC_CORE1_142_ISR_CAT))
#if (OSEE_TC_CORE1_142_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 142)
#elif (OSEE_TC_CORE1_142_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 142)
#else
#error Invalid value for OSEE_TC_CORE1_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 142)
OSEE_DUMMY_ISR(_core1_, 142)
#endif /* OSEE_TC_CORE1_142_ISR_CAT */
#if (defined(OSEE_TC_CORE1_143_ISR_CAT))
#if (OSEE_TC_CORE1_143_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 143)
#elif (OSEE_TC_CORE1_143_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 143)
#else
#error Invalid value for OSEE_TC_CORE1_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 143)
OSEE_DUMMY_ISR(_core1_, 143)
#endif /* OSEE_TC_CORE1_143_ISR_CAT */
#if (defined(OSEE_TC_CORE1_144_ISR_CAT))
#if (OSEE_TC_CORE1_144_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 144)
#elif (OSEE_TC_CORE1_144_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 144)
#else
#error Invalid value for OSEE_TC_CORE1_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 144)
OSEE_DUMMY_ISR(_core1_, 144)
#endif /* OSEE_TC_CORE1_144_ISR_CAT */
#if (defined(OSEE_TC_CORE1_145_ISR_CAT))
#if (OSEE_TC_CORE1_145_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 145)
#elif (OSEE_TC_CORE1_145_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 145)
#else
#error Invalid value for OSEE_TC_CORE1_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 145)
OSEE_DUMMY_ISR(_core1_, 145)
#endif /* OSEE_TC_CORE1_145_ISR_CAT */
#if (defined(OSEE_TC_CORE1_146_ISR_CAT))
#if (OSEE_TC_CORE1_146_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 146)
#elif (OSEE_TC_CORE1_146_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 146)
#else
#error Invalid value for OSEE_TC_CORE1_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 146)
OSEE_DUMMY_ISR(_core1_, 146)
#endif /* OSEE_TC_CORE1_146_ISR_CAT */
#if (defined(OSEE_TC_CORE1_147_ISR_CAT))
#if (OSEE_TC_CORE1_147_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 147)
#elif (OSEE_TC_CORE1_147_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 147)
#else
#error Invalid value for OSEE_TC_CORE1_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 147)
OSEE_DUMMY_ISR(_core1_, 147)
#endif /* OSEE_TC_CORE1_147_ISR_CAT */
#if (defined(OSEE_TC_CORE1_148_ISR_CAT))
#if (OSEE_TC_CORE1_148_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 148)
#elif (OSEE_TC_CORE1_148_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 148)
#else
#error Invalid value for OSEE_TC_CORE1_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 148)
OSEE_DUMMY_ISR(_core1_, 148)
#endif /* OSEE_TC_CORE1_148_ISR_CAT */
#if (defined(OSEE_TC_CORE1_149_ISR_CAT))
#if (OSEE_TC_CORE1_149_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 149)
#elif (OSEE_TC_CORE1_149_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 149)
#else
#error Invalid value for OSEE_TC_CORE1_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 149)
OSEE_DUMMY_ISR(_core1_, 149)
#endif /* OSEE_TC_CORE1_149_ISR_CAT */
#if (defined(OSEE_TC_CORE1_150_ISR_CAT))
#if (OSEE_TC_CORE1_150_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 150)
#elif (OSEE_TC_CORE1_150_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 150)
#else
#error Invalid value for OSEE_TC_CORE1_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 150)
OSEE_DUMMY_ISR(_core1_, 150)
#endif /* OSEE_TC_CORE1_150_ISR_CAT */
#if (defined(OSEE_TC_CORE1_151_ISR_CAT))
#if (OSEE_TC_CORE1_151_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 151)
#elif (OSEE_TC_CORE1_151_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 151)
#else
#error Invalid value for OSEE_TC_CORE1_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 151)
OSEE_DUMMY_ISR(_core1_, 151)
#endif /* OSEE_TC_CORE1_151_ISR_CAT */
#if (defined(OSEE_TC_CORE1_152_ISR_CAT))
#if (OSEE_TC_CORE1_152_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 152)
#elif (OSEE_TC_CORE1_152_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 152)
#else
#error Invalid value for OSEE_TC_CORE1_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 152)
OSEE_DUMMY_ISR(_core1_, 152)
#endif /* OSEE_TC_CORE1_152_ISR_CAT */
#if (defined(OSEE_TC_CORE1_153_ISR_CAT))
#if (OSEE_TC_CORE1_153_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 153)
#elif (OSEE_TC_CORE1_153_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 153)
#else
#error Invalid value for OSEE_TC_CORE1_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 153)
OSEE_DUMMY_ISR(_core1_, 153)
#endif /* OSEE_TC_CORE1_153_ISR_CAT */
#if (defined(OSEE_TC_CORE1_154_ISR_CAT))
#if (OSEE_TC_CORE1_154_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 154)
#elif (OSEE_TC_CORE1_154_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 154)
#else
#error Invalid value for OSEE_TC_CORE1_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 154)
OSEE_DUMMY_ISR(_core1_, 154)
#endif /* OSEE_TC_CORE1_154_ISR_CAT */
#if (defined(OSEE_TC_CORE1_155_ISR_CAT))
#if (OSEE_TC_CORE1_155_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 155)
#elif (OSEE_TC_CORE1_155_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 155)
#else
#error Invalid value for OSEE_TC_CORE1_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 155)
OSEE_DUMMY_ISR(_core1_, 155)
#endif /* OSEE_TC_CORE1_155_ISR_CAT */
#if (defined(OSEE_TC_CORE1_156_ISR_CAT))
#if (OSEE_TC_CORE1_156_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 156)
#elif (OSEE_TC_CORE1_156_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 156)
#else
#error Invalid value for OSEE_TC_CORE1_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 156)
OSEE_DUMMY_ISR(_core1_, 156)
#endif /* OSEE_TC_CORE1_156_ISR_CAT */
#if (defined(OSEE_TC_CORE1_157_ISR_CAT))
#if (OSEE_TC_CORE1_157_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 157)
#elif (OSEE_TC_CORE1_157_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 157)
#else
#error Invalid value for OSEE_TC_CORE1_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 157)
OSEE_DUMMY_ISR(_core1_, 157)
#endif /* OSEE_TC_CORE1_157_ISR_CAT */
#if (defined(OSEE_TC_CORE1_158_ISR_CAT))
#if (OSEE_TC_CORE1_158_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 158)
#elif (OSEE_TC_CORE1_158_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 158)
#else
#error Invalid value for OSEE_TC_CORE1_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 158)
OSEE_DUMMY_ISR(_core1_, 158)
#endif /* OSEE_TC_CORE1_158_ISR_CAT */
#if (defined(OSEE_TC_CORE1_159_ISR_CAT))
#if (OSEE_TC_CORE1_159_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 159)
#elif (OSEE_TC_CORE1_159_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 159)
#else
#error Invalid value for OSEE_TC_CORE1_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 159)
OSEE_DUMMY_ISR(_core1_, 159)
#endif /* OSEE_TC_CORE1_159_ISR_CAT */
#if (defined(OSEE_TC_CORE1_160_ISR_CAT))
#if (OSEE_TC_CORE1_160_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 160)
#elif (OSEE_TC_CORE1_160_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 160)
#else
#error Invalid value for OSEE_TC_CORE1_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 160)
OSEE_DUMMY_ISR(_core1_, 160)
#endif /* OSEE_TC_CORE1_160_ISR_CAT */
#if (defined(OSEE_TC_CORE1_161_ISR_CAT))
#if (OSEE_TC_CORE1_161_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 161)
#elif (OSEE_TC_CORE1_161_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 161)
#else
#error Invalid value for OSEE_TC_CORE1_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 161)
OSEE_DUMMY_ISR(_core1_, 161)
#endif /* OSEE_TC_CORE1_161_ISR_CAT */
#if (defined(OSEE_TC_CORE1_162_ISR_CAT))
#if (OSEE_TC_CORE1_162_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 162)
#elif (OSEE_TC_CORE1_162_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 162)
#else
#error Invalid value for OSEE_TC_CORE1_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 162)
OSEE_DUMMY_ISR(_core1_, 162)
#endif /* OSEE_TC_CORE1_162_ISR_CAT */
#if (defined(OSEE_TC_CORE1_163_ISR_CAT))
#if (OSEE_TC_CORE1_163_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 163)
#elif (OSEE_TC_CORE1_163_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 163)
#else
#error Invalid value for OSEE_TC_CORE1_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 163)
OSEE_DUMMY_ISR(_core1_, 163)
#endif /* OSEE_TC_CORE1_163_ISR_CAT */
#if (defined(OSEE_TC_CORE1_164_ISR_CAT))
#if (OSEE_TC_CORE1_164_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 164)
#elif (OSEE_TC_CORE1_164_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 164)
#else
#error Invalid value for OSEE_TC_CORE1_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 164)
OSEE_DUMMY_ISR(_core1_, 164)
#endif /* OSEE_TC_CORE1_164_ISR_CAT */
#if (defined(OSEE_TC_CORE1_165_ISR_CAT))
#if (OSEE_TC_CORE1_165_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 165)
#elif (OSEE_TC_CORE1_165_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 165)
#else
#error Invalid value for OSEE_TC_CORE1_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 165)
OSEE_DUMMY_ISR(_core1_, 165)
#endif /* OSEE_TC_CORE1_165_ISR_CAT */
#if (defined(OSEE_TC_CORE1_166_ISR_CAT))
#if (OSEE_TC_CORE1_166_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 166)
#elif (OSEE_TC_CORE1_166_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 166)
#else
#error Invalid value for OSEE_TC_CORE1_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 166)
OSEE_DUMMY_ISR(_core1_, 166)
#endif /* OSEE_TC_CORE1_166_ISR_CAT */
#if (defined(OSEE_TC_CORE1_167_ISR_CAT))
#if (OSEE_TC_CORE1_167_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 167)
#elif (OSEE_TC_CORE1_167_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 167)
#else
#error Invalid value for OSEE_TC_CORE1_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 167)
OSEE_DUMMY_ISR(_core1_, 167)
#endif /* OSEE_TC_CORE1_167_ISR_CAT */
#if (defined(OSEE_TC_CORE1_168_ISR_CAT))
#if (OSEE_TC_CORE1_168_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 168)
#elif (OSEE_TC_CORE1_168_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 168)
#else
#error Invalid value for OSEE_TC_CORE1_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 168)
OSEE_DUMMY_ISR(_core1_, 168)
#endif /* OSEE_TC_CORE1_168_ISR_CAT */
#if (defined(OSEE_TC_CORE1_169_ISR_CAT))
#if (OSEE_TC_CORE1_169_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 169)
#elif (OSEE_TC_CORE1_169_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 169)
#else
#error Invalid value for OSEE_TC_CORE1_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 169)
OSEE_DUMMY_ISR(_core1_, 169)
#endif /* OSEE_TC_CORE1_169_ISR_CAT */
#if (defined(OSEE_TC_CORE1_170_ISR_CAT))
#if (OSEE_TC_CORE1_170_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 170)
#elif (OSEE_TC_CORE1_170_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 170)
#else
#error Invalid value for OSEE_TC_CORE1_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 170)
OSEE_DUMMY_ISR(_core1_, 170)
#endif /* OSEE_TC_CORE1_170_ISR_CAT */
#if (defined(OSEE_TC_CORE1_171_ISR_CAT))
#if (OSEE_TC_CORE1_171_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 171)
#elif (OSEE_TC_CORE1_171_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 171)
#else
#error Invalid value for OSEE_TC_CORE1_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 171)
OSEE_DUMMY_ISR(_core1_, 171)
#endif /* OSEE_TC_CORE1_171_ISR_CAT */
#if (defined(OSEE_TC_CORE1_172_ISR_CAT))
#if (OSEE_TC_CORE1_172_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 172)
#elif (OSEE_TC_CORE1_172_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 172)
#else
#error Invalid value for OSEE_TC_CORE1_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 172)
OSEE_DUMMY_ISR(_core1_, 172)
#endif /* OSEE_TC_CORE1_172_ISR_CAT */
#if (defined(OSEE_TC_CORE1_173_ISR_CAT))
#if (OSEE_TC_CORE1_173_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 173)
#elif (OSEE_TC_CORE1_173_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 173)
#else
#error Invalid value for OSEE_TC_CORE1_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 173)
OSEE_DUMMY_ISR(_core1_, 173)
#endif /* OSEE_TC_CORE1_173_ISR_CAT */
#if (defined(OSEE_TC_CORE1_174_ISR_CAT))
#if (OSEE_TC_CORE1_174_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 174)
#elif (OSEE_TC_CORE1_174_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 174)
#else
#error Invalid value for OSEE_TC_CORE1_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 174)
OSEE_DUMMY_ISR(_core1_, 174)
#endif /* OSEE_TC_CORE1_174_ISR_CAT */
#if (defined(OSEE_TC_CORE1_175_ISR_CAT))
#if (OSEE_TC_CORE1_175_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 175)
#elif (OSEE_TC_CORE1_175_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 175)
#else
#error Invalid value for OSEE_TC_CORE1_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 175)
OSEE_DUMMY_ISR(_core1_, 175)
#endif /* OSEE_TC_CORE1_175_ISR_CAT */
#if (defined(OSEE_TC_CORE1_176_ISR_CAT))
#if (OSEE_TC_CORE1_176_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 176)
#elif (OSEE_TC_CORE1_176_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 176)
#else
#error Invalid value for OSEE_TC_CORE1_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 176)
OSEE_DUMMY_ISR(_core1_, 176)
#endif /* OSEE_TC_CORE1_176_ISR_CAT */
#if (defined(OSEE_TC_CORE1_177_ISR_CAT))
#if (OSEE_TC_CORE1_177_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 177)
#elif (OSEE_TC_CORE1_177_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 177)
#else
#error Invalid value for OSEE_TC_CORE1_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 177)
OSEE_DUMMY_ISR(_core1_, 177)
#endif /* OSEE_TC_CORE1_177_ISR_CAT */
#if (defined(OSEE_TC_CORE1_178_ISR_CAT))
#if (OSEE_TC_CORE1_178_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 178)
#elif (OSEE_TC_CORE1_178_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 178)
#else
#error Invalid value for OSEE_TC_CORE1_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 178)
OSEE_DUMMY_ISR(_core1_, 178)
#endif /* OSEE_TC_CORE1_178_ISR_CAT */
#if (defined(OSEE_TC_CORE1_179_ISR_CAT))
#if (OSEE_TC_CORE1_179_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 179)
#elif (OSEE_TC_CORE1_179_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 179)
#else
#error Invalid value for OSEE_TC_CORE1_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 179)
OSEE_DUMMY_ISR(_core1_, 179)
#endif /* OSEE_TC_CORE1_179_ISR_CAT */
#if (defined(OSEE_TC_CORE1_180_ISR_CAT))
#if (OSEE_TC_CORE1_180_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 180)
#elif (OSEE_TC_CORE1_180_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 180)
#else
#error Invalid value for OSEE_TC_CORE1_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 180)
OSEE_DUMMY_ISR(_core1_, 180)
#endif /* OSEE_TC_CORE1_180_ISR_CAT */
#if (defined(OSEE_TC_CORE1_181_ISR_CAT))
#if (OSEE_TC_CORE1_181_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 181)
#elif (OSEE_TC_CORE1_181_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 181)
#else
#error Invalid value for OSEE_TC_CORE1_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 181)
OSEE_DUMMY_ISR(_core1_, 181)
#endif /* OSEE_TC_CORE1_181_ISR_CAT */
#if (defined(OSEE_TC_CORE1_182_ISR_CAT))
#if (OSEE_TC_CORE1_182_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 182)
#elif (OSEE_TC_CORE1_182_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 182)
#else
#error Invalid value for OSEE_TC_CORE1_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 182)
OSEE_DUMMY_ISR(_core1_, 182)
#endif /* OSEE_TC_CORE1_182_ISR_CAT */
#if (defined(OSEE_TC_CORE1_183_ISR_CAT))
#if (OSEE_TC_CORE1_183_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 183)
#elif (OSEE_TC_CORE1_183_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 183)
#else
#error Invalid value for OSEE_TC_CORE1_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 183)
OSEE_DUMMY_ISR(_core1_, 183)
#endif /* OSEE_TC_CORE1_183_ISR_CAT */
#if (defined(OSEE_TC_CORE1_184_ISR_CAT))
#if (OSEE_TC_CORE1_184_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 184)
#elif (OSEE_TC_CORE1_184_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 184)
#else
#error Invalid value for OSEE_TC_CORE1_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 184)
OSEE_DUMMY_ISR(_core1_, 184)
#endif /* OSEE_TC_CORE1_184_ISR_CAT */
#if (defined(OSEE_TC_CORE1_185_ISR_CAT))
#if (OSEE_TC_CORE1_185_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 185)
#elif (OSEE_TC_CORE1_185_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 185)
#else
#error Invalid value for OSEE_TC_CORE1_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 185)
OSEE_DUMMY_ISR(_core1_, 185)
#endif /* OSEE_TC_CORE1_185_ISR_CAT */
#if (defined(OSEE_TC_CORE1_186_ISR_CAT))
#if (OSEE_TC_CORE1_186_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 186)
#elif (OSEE_TC_CORE1_186_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 186)
#else
#error Invalid value for OSEE_TC_CORE1_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 186)
OSEE_DUMMY_ISR(_core1_, 186)
#endif /* OSEE_TC_CORE1_186_ISR_CAT */
#if (defined(OSEE_TC_CORE1_187_ISR_CAT))
#if (OSEE_TC_CORE1_187_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 187)
#elif (OSEE_TC_CORE1_187_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 187)
#else
#error Invalid value for OSEE_TC_CORE1_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 187)
OSEE_DUMMY_ISR(_core1_, 187)
#endif /* OSEE_TC_CORE1_187_ISR_CAT */
#if (defined(OSEE_TC_CORE1_188_ISR_CAT))
#if (OSEE_TC_CORE1_188_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 188)
#elif (OSEE_TC_CORE1_188_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 188)
#else
#error Invalid value for OSEE_TC_CORE1_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 188)
OSEE_DUMMY_ISR(_core1_, 188)
#endif /* OSEE_TC_CORE1_188_ISR_CAT */
#if (defined(OSEE_TC_CORE1_189_ISR_CAT))
#if (OSEE_TC_CORE1_189_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 189)
#elif (OSEE_TC_CORE1_189_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 189)
#else
#error Invalid value for OSEE_TC_CORE1_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 189)
OSEE_DUMMY_ISR(_core1_, 189)
#endif /* OSEE_TC_CORE1_189_ISR_CAT */
#if (defined(OSEE_TC_CORE1_190_ISR_CAT))
#if (OSEE_TC_CORE1_190_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 190)
#elif (OSEE_TC_CORE1_190_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 190)
#else
#error Invalid value for OSEE_TC_CORE1_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 190)
OSEE_DUMMY_ISR(_core1_, 190)
#endif /* OSEE_TC_CORE1_190_ISR_CAT */
#if (defined(OSEE_TC_CORE1_191_ISR_CAT))
#if (OSEE_TC_CORE1_191_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 191)
#elif (OSEE_TC_CORE1_191_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 191)
#else
#error Invalid value for OSEE_TC_CORE1_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 191)
OSEE_DUMMY_ISR(_core1_, 191)
#endif /* OSEE_TC_CORE1_191_ISR_CAT */
#if (defined(OSEE_TC_CORE1_192_ISR_CAT))
#if (OSEE_TC_CORE1_192_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 192)
#elif (OSEE_TC_CORE1_192_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 192)
#else
#error Invalid value for OSEE_TC_CORE1_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 192)
OSEE_DUMMY_ISR(_core1_, 192)
#endif /* OSEE_TC_CORE1_192_ISR_CAT */
#if (defined(OSEE_TC_CORE1_193_ISR_CAT))
#if (OSEE_TC_CORE1_193_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 193)
#elif (OSEE_TC_CORE1_193_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 193)
#else
#error Invalid value for OSEE_TC_CORE1_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 193)
OSEE_DUMMY_ISR(_core1_, 193)
#endif /* OSEE_TC_CORE1_193_ISR_CAT */
#if (defined(OSEE_TC_CORE1_194_ISR_CAT))
#if (OSEE_TC_CORE1_194_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 194)
#elif (OSEE_TC_CORE1_194_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 194)
#else
#error Invalid value for OSEE_TC_CORE1_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 194)
OSEE_DUMMY_ISR(_core1_, 194)
#endif /* OSEE_TC_CORE1_194_ISR_CAT */
#if (defined(OSEE_TC_CORE1_195_ISR_CAT))
#if (OSEE_TC_CORE1_195_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 195)
#elif (OSEE_TC_CORE1_195_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 195)
#else
#error Invalid value for OSEE_TC_CORE1_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 195)
OSEE_DUMMY_ISR(_core1_, 195)
#endif /* OSEE_TC_CORE1_195_ISR_CAT */
#if (defined(OSEE_TC_CORE1_196_ISR_CAT))
#if (OSEE_TC_CORE1_196_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 196)
#elif (OSEE_TC_CORE1_196_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 196)
#else
#error Invalid value for OSEE_TC_CORE1_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 196)
OSEE_DUMMY_ISR(_core1_, 196)
#endif /* OSEE_TC_CORE1_196_ISR_CAT */
#if (defined(OSEE_TC_CORE1_197_ISR_CAT))
#if (OSEE_TC_CORE1_197_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 197)
#elif (OSEE_TC_CORE1_197_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 197)
#else
#error Invalid value for OSEE_TC_CORE1_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 197)
OSEE_DUMMY_ISR(_core1_, 197)
#endif /* OSEE_TC_CORE1_197_ISR_CAT */
#if (defined(OSEE_TC_CORE1_198_ISR_CAT))
#if (OSEE_TC_CORE1_198_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 198)
#elif (OSEE_TC_CORE1_198_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 198)
#else
#error Invalid value for OSEE_TC_CORE1_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 198)
OSEE_DUMMY_ISR(_core1_, 198)
#endif /* OSEE_TC_CORE1_198_ISR_CAT */
#if (defined(OSEE_TC_CORE1_199_ISR_CAT))
#if (OSEE_TC_CORE1_199_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 199)
#elif (OSEE_TC_CORE1_199_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 199)
#else
#error Invalid value for OSEE_TC_CORE1_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 199)
OSEE_DUMMY_ISR(_core1_, 199)
#endif /* OSEE_TC_CORE1_199_ISR_CAT */
#if (defined(OSEE_TC_CORE1_200_ISR_CAT))
#if (OSEE_TC_CORE1_200_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 200)
#elif (OSEE_TC_CORE1_200_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 200)
#else
#error Invalid value for OSEE_TC_CORE1_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 200)
OSEE_DUMMY_ISR(_core1_, 200)
#endif /* OSEE_TC_CORE1_200_ISR_CAT */
#if (defined(OSEE_TC_CORE1_201_ISR_CAT))
#if (OSEE_TC_CORE1_201_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 201)
#elif (OSEE_TC_CORE1_201_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 201)
#else
#error Invalid value for OSEE_TC_CORE1_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 201)
OSEE_DUMMY_ISR(_core1_, 201)
#endif /* OSEE_TC_CORE1_201_ISR_CAT */
#if (defined(OSEE_TC_CORE1_202_ISR_CAT))
#if (OSEE_TC_CORE1_202_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 202)
#elif (OSEE_TC_CORE1_202_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 202)
#else
#error Invalid value for OSEE_TC_CORE1_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 202)
OSEE_DUMMY_ISR(_core1_, 202)
#endif /* OSEE_TC_CORE1_202_ISR_CAT */
#if (defined(OSEE_TC_CORE1_203_ISR_CAT))
#if (OSEE_TC_CORE1_203_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 203)
#elif (OSEE_TC_CORE1_203_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 203)
#else
#error Invalid value for OSEE_TC_CORE1_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 203)
OSEE_DUMMY_ISR(_core1_, 203)
#endif /* OSEE_TC_CORE1_203_ISR_CAT */
#if (defined(OSEE_TC_CORE1_204_ISR_CAT))
#if (OSEE_TC_CORE1_204_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 204)
#elif (OSEE_TC_CORE1_204_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 204)
#else
#error Invalid value for OSEE_TC_CORE1_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 204)
OSEE_DUMMY_ISR(_core1_, 204)
#endif /* OSEE_TC_CORE1_204_ISR_CAT */
#if (defined(OSEE_TC_CORE1_205_ISR_CAT))
#if (OSEE_TC_CORE1_205_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 205)
#elif (OSEE_TC_CORE1_205_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 205)
#else
#error Invalid value for OSEE_TC_CORE1_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 205)
OSEE_DUMMY_ISR(_core1_, 205)
#endif /* OSEE_TC_CORE1_205_ISR_CAT */
#if (defined(OSEE_TC_CORE1_206_ISR_CAT))
#if (OSEE_TC_CORE1_206_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 206)
#elif (OSEE_TC_CORE1_206_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 206)
#else
#error Invalid value for OSEE_TC_CORE1_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 206)
OSEE_DUMMY_ISR(_core1_, 206)
#endif /* OSEE_TC_CORE1_206_ISR_CAT */
#if (defined(OSEE_TC_CORE1_207_ISR_CAT))
#if (OSEE_TC_CORE1_207_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 207)
#elif (OSEE_TC_CORE1_207_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 207)
#else
#error Invalid value for OSEE_TC_CORE1_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 207)
OSEE_DUMMY_ISR(_core1_, 207)
#endif /* OSEE_TC_CORE1_207_ISR_CAT */
#if (defined(OSEE_TC_CORE1_208_ISR_CAT))
#if (OSEE_TC_CORE1_208_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 208)
#elif (OSEE_TC_CORE1_208_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 208)
#else
#error Invalid value for OSEE_TC_CORE1_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 208)
OSEE_DUMMY_ISR(_core1_, 208)
#endif /* OSEE_TC_CORE1_208_ISR_CAT */
#if (defined(OSEE_TC_CORE1_209_ISR_CAT))
#if (OSEE_TC_CORE1_209_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 209)
#elif (OSEE_TC_CORE1_209_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 209)
#else
#error Invalid value for OSEE_TC_CORE1_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 209)
OSEE_DUMMY_ISR(_core1_, 209)
#endif /* OSEE_TC_CORE1_209_ISR_CAT */
#if (defined(OSEE_TC_CORE1_210_ISR_CAT))
#if (OSEE_TC_CORE1_210_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 210)
#elif (OSEE_TC_CORE1_210_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 210)
#else
#error Invalid value for OSEE_TC_CORE1_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 210)
OSEE_DUMMY_ISR(_core1_, 210)
#endif /* OSEE_TC_CORE1_210_ISR_CAT */
#if (defined(OSEE_TC_CORE1_211_ISR_CAT))
#if (OSEE_TC_CORE1_211_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 211)
#elif (OSEE_TC_CORE1_211_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 211)
#else
#error Invalid value for OSEE_TC_CORE1_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 211)
OSEE_DUMMY_ISR(_core1_, 211)
#endif /* OSEE_TC_CORE1_211_ISR_CAT */
#if (defined(OSEE_TC_CORE1_212_ISR_CAT))
#if (OSEE_TC_CORE1_212_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 212)
#elif (OSEE_TC_CORE1_212_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 212)
#else
#error Invalid value for OSEE_TC_CORE1_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 212)
OSEE_DUMMY_ISR(_core1_, 212)
#endif /* OSEE_TC_CORE1_212_ISR_CAT */
#if (defined(OSEE_TC_CORE1_213_ISR_CAT))
#if (OSEE_TC_CORE1_213_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 213)
#elif (OSEE_TC_CORE1_213_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 213)
#else
#error Invalid value for OSEE_TC_CORE1_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 213)
OSEE_DUMMY_ISR(_core1_, 213)
#endif /* OSEE_TC_CORE1_213_ISR_CAT */
#if (defined(OSEE_TC_CORE1_214_ISR_CAT))
#if (OSEE_TC_CORE1_214_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 214)
#elif (OSEE_TC_CORE1_214_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 214)
#else
#error Invalid value for OSEE_TC_CORE1_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 214)
OSEE_DUMMY_ISR(_core1_, 214)
#endif /* OSEE_TC_CORE1_214_ISR_CAT */
#if (defined(OSEE_TC_CORE1_215_ISR_CAT))
#if (OSEE_TC_CORE1_215_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 215)
#elif (OSEE_TC_CORE1_215_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 215)
#else
#error Invalid value for OSEE_TC_CORE1_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 215)
OSEE_DUMMY_ISR(_core1_, 215)
#endif /* OSEE_TC_CORE1_215_ISR_CAT */
#if (defined(OSEE_TC_CORE1_216_ISR_CAT))
#if (OSEE_TC_CORE1_216_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 216)
#elif (OSEE_TC_CORE1_216_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 216)
#else
#error Invalid value for OSEE_TC_CORE1_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 216)
OSEE_DUMMY_ISR(_core1_, 216)
#endif /* OSEE_TC_CORE1_216_ISR_CAT */
#if (defined(OSEE_TC_CORE1_217_ISR_CAT))
#if (OSEE_TC_CORE1_217_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 217)
#elif (OSEE_TC_CORE1_217_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 217)
#else
#error Invalid value for OSEE_TC_CORE1_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 217)
OSEE_DUMMY_ISR(_core1_, 217)
#endif /* OSEE_TC_CORE1_217_ISR_CAT */
#if (defined(OSEE_TC_CORE1_218_ISR_CAT))
#if (OSEE_TC_CORE1_218_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 218)
#elif (OSEE_TC_CORE1_218_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 218)
#else
#error Invalid value for OSEE_TC_CORE1_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 218)
OSEE_DUMMY_ISR(_core1_, 218)
#endif /* OSEE_TC_CORE1_218_ISR_CAT */
#if (defined(OSEE_TC_CORE1_219_ISR_CAT))
#if (OSEE_TC_CORE1_219_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 219)
#elif (OSEE_TC_CORE1_219_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 219)
#else
#error Invalid value for OSEE_TC_CORE1_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 219)
OSEE_DUMMY_ISR(_core1_, 219)
#endif /* OSEE_TC_CORE1_219_ISR_CAT */
#if (defined(OSEE_TC_CORE1_220_ISR_CAT))
#if (OSEE_TC_CORE1_220_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 220)
#elif (OSEE_TC_CORE1_220_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 220)
#else
#error Invalid value for OSEE_TC_CORE1_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 220)
OSEE_DUMMY_ISR(_core1_, 220)
#endif /* OSEE_TC_CORE1_220_ISR_CAT */
#if (defined(OSEE_TC_CORE1_221_ISR_CAT))
#if (OSEE_TC_CORE1_221_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 221)
#elif (OSEE_TC_CORE1_221_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 221)
#else
#error Invalid value for OSEE_TC_CORE1_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 221)
OSEE_DUMMY_ISR(_core1_, 221)
#endif /* OSEE_TC_CORE1_221_ISR_CAT */
#if (defined(OSEE_TC_CORE1_222_ISR_CAT))
#if (OSEE_TC_CORE1_222_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 222)
#elif (OSEE_TC_CORE1_222_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 222)
#else
#error Invalid value for OSEE_TC_CORE1_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 222)
OSEE_DUMMY_ISR(_core1_, 222)
#endif /* OSEE_TC_CORE1_222_ISR_CAT */
#if (defined(OSEE_TC_CORE1_223_ISR_CAT))
#if (OSEE_TC_CORE1_223_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 223)
#elif (OSEE_TC_CORE1_223_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 223)
#else
#error Invalid value for OSEE_TC_CORE1_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 223)
OSEE_DUMMY_ISR(_core1_, 223)
#endif /* OSEE_TC_CORE1_223_ISR_CAT */
#if (defined(OSEE_TC_CORE1_224_ISR_CAT))
#if (OSEE_TC_CORE1_224_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 224)
#elif (OSEE_TC_CORE1_224_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 224)
#else
#error Invalid value for OSEE_TC_CORE1_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 224)
OSEE_DUMMY_ISR(_core1_, 224)
#endif /* OSEE_TC_CORE1_224_ISR_CAT */
#if (defined(OSEE_TC_CORE1_225_ISR_CAT))
#if (OSEE_TC_CORE1_225_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 225)
#elif (OSEE_TC_CORE1_225_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 225)
#else
#error Invalid value for OSEE_TC_CORE1_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 225)
OSEE_DUMMY_ISR(_core1_, 225)
#endif /* OSEE_TC_CORE1_225_ISR_CAT */
#if (defined(OSEE_TC_CORE1_226_ISR_CAT))
#if (OSEE_TC_CORE1_226_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 226)
#elif (OSEE_TC_CORE1_226_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 226)
#else
#error Invalid value for OSEE_TC_CORE1_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 226)
OSEE_DUMMY_ISR(_core1_, 226)
#endif /* OSEE_TC_CORE1_226_ISR_CAT */
#if (defined(OSEE_TC_CORE1_227_ISR_CAT))
#if (OSEE_TC_CORE1_227_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 227)
#elif (OSEE_TC_CORE1_227_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 227)
#else
#error Invalid value for OSEE_TC_CORE1_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 227)
OSEE_DUMMY_ISR(_core1_, 227)
#endif /* OSEE_TC_CORE1_227_ISR_CAT */
#if (defined(OSEE_TC_CORE1_228_ISR_CAT))
#if (OSEE_TC_CORE1_228_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 228)
#elif (OSEE_TC_CORE1_228_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 228)
#else
#error Invalid value for OSEE_TC_CORE1_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 228)
OSEE_DUMMY_ISR(_core1_, 228)
#endif /* OSEE_TC_CORE1_228_ISR_CAT */
#if (defined(OSEE_TC_CORE1_229_ISR_CAT))
#if (OSEE_TC_CORE1_229_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 229)
#elif (OSEE_TC_CORE1_229_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 229)
#else
#error Invalid value for OSEE_TC_CORE1_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 229)
OSEE_DUMMY_ISR(_core1_, 229)
#endif /* OSEE_TC_CORE1_229_ISR_CAT */
#if (defined(OSEE_TC_CORE1_230_ISR_CAT))
#if (OSEE_TC_CORE1_230_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 230)
#elif (OSEE_TC_CORE1_230_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 230)
#else
#error Invalid value for OSEE_TC_CORE1_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 230)
OSEE_DUMMY_ISR(_core1_, 230)
#endif /* OSEE_TC_CORE1_230_ISR_CAT */
#if (defined(OSEE_TC_CORE1_231_ISR_CAT))
#if (OSEE_TC_CORE1_231_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 231)
#elif (OSEE_TC_CORE1_231_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 231)
#else
#error Invalid value for OSEE_TC_CORE1_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 231)
OSEE_DUMMY_ISR(_core1_, 231)
#endif /* OSEE_TC_CORE1_231_ISR_CAT */
#if (defined(OSEE_TC_CORE1_232_ISR_CAT))
#if (OSEE_TC_CORE1_232_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 232)
#elif (OSEE_TC_CORE1_232_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 232)
#else
#error Invalid value for OSEE_TC_CORE1_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 232)
OSEE_DUMMY_ISR(_core1_, 232)
#endif /* OSEE_TC_CORE1_232_ISR_CAT */
#if (defined(OSEE_TC_CORE1_233_ISR_CAT))
#if (OSEE_TC_CORE1_233_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 233)
#elif (OSEE_TC_CORE1_233_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 233)
#else
#error Invalid value for OSEE_TC_CORE1_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 233)
OSEE_DUMMY_ISR(_core1_, 233)
#endif /* OSEE_TC_CORE1_233_ISR_CAT */
#if (defined(OSEE_TC_CORE1_234_ISR_CAT))
#if (OSEE_TC_CORE1_234_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 234)
#elif (OSEE_TC_CORE1_234_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 234)
#else
#error Invalid value for OSEE_TC_CORE1_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 234)
OSEE_DUMMY_ISR(_core1_, 234)
#endif /* OSEE_TC_CORE1_234_ISR_CAT */
#if (defined(OSEE_TC_CORE1_235_ISR_CAT))
#if (OSEE_TC_CORE1_235_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 235)
#elif (OSEE_TC_CORE1_235_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 235)
#else
#error Invalid value for OSEE_TC_CORE1_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 235)
OSEE_DUMMY_ISR(_core1_, 235)
#endif /* OSEE_TC_CORE1_235_ISR_CAT */
#if (defined(OSEE_TC_CORE1_236_ISR_CAT))
#if (OSEE_TC_CORE1_236_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 236)
#elif (OSEE_TC_CORE1_236_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 236)
#else
#error Invalid value for OSEE_TC_CORE1_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 236)
OSEE_DUMMY_ISR(_core1_, 236)
#endif /* OSEE_TC_CORE1_236_ISR_CAT */
#if (defined(OSEE_TC_CORE1_237_ISR_CAT))
#if (OSEE_TC_CORE1_237_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 237)
#elif (OSEE_TC_CORE1_237_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 237)
#else
#error Invalid value for OSEE_TC_CORE1_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 237)
OSEE_DUMMY_ISR(_core1_, 237)
#endif /* OSEE_TC_CORE1_237_ISR_CAT */
#if (defined(OSEE_TC_CORE1_238_ISR_CAT))
#if (OSEE_TC_CORE1_238_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 238)
#elif (OSEE_TC_CORE1_238_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 238)
#else
#error Invalid value for OSEE_TC_CORE1_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 238)
OSEE_DUMMY_ISR(_core1_, 238)
#endif /* OSEE_TC_CORE1_238_ISR_CAT */
#if (defined(OSEE_TC_CORE1_239_ISR_CAT))
#if (OSEE_TC_CORE1_239_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 239)
#elif (OSEE_TC_CORE1_239_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 239)
#else
#error Invalid value for OSEE_TC_CORE1_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 239)
OSEE_DUMMY_ISR(_core1_, 239)
#endif /* OSEE_TC_CORE1_239_ISR_CAT */
#if (defined(OSEE_TC_CORE1_240_ISR_CAT))
#if (OSEE_TC_CORE1_240_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 240)
#elif (OSEE_TC_CORE1_240_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 240)
#else
#error Invalid value for OSEE_TC_CORE1_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 240)
OSEE_DUMMY_ISR(_core1_, 240)
#endif /* OSEE_TC_CORE1_240_ISR_CAT */
#if (defined(OSEE_TC_CORE1_241_ISR_CAT))
#if (OSEE_TC_CORE1_241_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 241)
#elif (OSEE_TC_CORE1_241_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 241)
#else
#error Invalid value for OSEE_TC_CORE1_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 241)
OSEE_DUMMY_ISR(_core1_, 241)
#endif /* OSEE_TC_CORE1_241_ISR_CAT */
#if (defined(OSEE_TC_CORE1_242_ISR_CAT))
#if (OSEE_TC_CORE1_242_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 242)
#elif (OSEE_TC_CORE1_242_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 242)
#else
#error Invalid value for OSEE_TC_CORE1_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 242)
OSEE_DUMMY_ISR(_core1_, 242)
#endif /* OSEE_TC_CORE1_242_ISR_CAT */
#if (defined(OSEE_TC_CORE1_243_ISR_CAT))
#if (OSEE_TC_CORE1_243_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 243)
#elif (OSEE_TC_CORE1_243_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 243)
#else
#error Invalid value for OSEE_TC_CORE1_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 243)
OSEE_DUMMY_ISR(_core1_, 243)
#endif /* OSEE_TC_CORE1_243_ISR_CAT */
#if (defined(OSEE_TC_CORE1_244_ISR_CAT))
#if (OSEE_TC_CORE1_244_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 244)
#elif (OSEE_TC_CORE1_244_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 244)
#else
#error Invalid value for OSEE_TC_CORE1_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 244)
OSEE_DUMMY_ISR(_core1_, 244)
#endif /* OSEE_TC_CORE1_244_ISR_CAT */
#if (defined(OSEE_TC_CORE1_245_ISR_CAT))
#if (OSEE_TC_CORE1_245_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 245)
#elif (OSEE_TC_CORE1_245_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 245)
#else
#error Invalid value for OSEE_TC_CORE1_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 245)
OSEE_DUMMY_ISR(_core1_, 245)
#endif /* OSEE_TC_CORE1_245_ISR_CAT */
#if (defined(OSEE_TC_CORE1_246_ISR_CAT))
#if (OSEE_TC_CORE1_246_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 246)
#elif (OSEE_TC_CORE1_246_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 246)
#else
#error Invalid value for OSEE_TC_CORE1_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 246)
OSEE_DUMMY_ISR(_core1_, 246)
#endif /* OSEE_TC_CORE1_246_ISR_CAT */
#if (defined(OSEE_TC_CORE1_247_ISR_CAT))
#if (OSEE_TC_CORE1_247_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 247)
#elif (OSEE_TC_CORE1_247_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 247)
#else
#error Invalid value for OSEE_TC_CORE1_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 247)
OSEE_DUMMY_ISR(_core1_, 247)
#endif /* OSEE_TC_CORE1_247_ISR_CAT */
#if (defined(OSEE_TC_CORE1_248_ISR_CAT))
#if (OSEE_TC_CORE1_248_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 248)
#elif (OSEE_TC_CORE1_248_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 248)
#else
#error Invalid value for OSEE_TC_CORE1_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 248)
OSEE_DUMMY_ISR(_core1_, 248)
#endif /* OSEE_TC_CORE1_248_ISR_CAT */
#if (defined(OSEE_TC_CORE1_249_ISR_CAT))
#if (OSEE_TC_CORE1_249_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 249)
#elif (OSEE_TC_CORE1_249_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 249)
#else
#error Invalid value for OSEE_TC_CORE1_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 249)
OSEE_DUMMY_ISR(_core1_, 249)
#endif /* OSEE_TC_CORE1_249_ISR_CAT */
#if (defined(OSEE_TC_CORE1_250_ISR_CAT))
#if (OSEE_TC_CORE1_250_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 250)
#elif (OSEE_TC_CORE1_250_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 250)
#else
#error Invalid value for OSEE_TC_CORE1_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 250)
OSEE_DUMMY_ISR(_core1_, 250)
#endif /* OSEE_TC_CORE1_250_ISR_CAT */
#if (defined(OSEE_TC_CORE1_251_ISR_CAT))
#if (OSEE_TC_CORE1_251_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 251)
#elif (OSEE_TC_CORE1_251_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 251)
#else
#error Invalid value for OSEE_TC_CORE1_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 251)
OSEE_DUMMY_ISR(_core1_, 251)
#endif /* OSEE_TC_CORE1_251_ISR_CAT */
#if (defined(OSEE_TC_CORE1_252_ISR_CAT))
#if (OSEE_TC_CORE1_252_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 252)
#elif (OSEE_TC_CORE1_252_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 252)
#else
#error Invalid value for OSEE_TC_CORE1_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 252)
OSEE_DUMMY_ISR(_core1_, 252)
#endif /* OSEE_TC_CORE1_252_ISR_CAT */
#if (defined(OSEE_TC_CORE1_253_ISR_CAT))
#if (OSEE_TC_CORE1_253_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 253)
#elif (OSEE_TC_CORE1_253_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 253)
#else
#error Invalid value for OSEE_TC_CORE1_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 253)
OSEE_DUMMY_ISR(_core1_, 253)
#endif /* OSEE_TC_CORE1_253_ISR_CAT */
#if (defined(OSEE_TC_CORE1_254_ISR_CAT))
#if (OSEE_TC_CORE1_254_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 254)
#elif (OSEE_TC_CORE1_254_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 254)
#else
#error Invalid value for OSEE_TC_CORE1_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 254)
OSEE_DUMMY_ISR(_core1_, 254)
#endif /* OSEE_TC_CORE1_254_ISR_CAT */
#if (defined(OSEE_TC_CORE1_255_ISR_CAT))
#if (OSEE_TC_CORE1_255_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core1_, 255)
#elif (OSEE_TC_CORE1_255_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core1_, 255)
#else
#error Invalid value for OSEE_TC_CORE1_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 255)
OSEE_DUMMY_ISR(_core1_, 255)
#endif /* OSEE_TC_CORE1_255_ISR_CAT */
#endif /* OSEE_TC_CORE1_ISR_MAX_PRIO */


#if(defined(OSEE_TC_CORE2_ISR_MAX_PRIO))
OSEE_ISR2_DECLARE(_core2_, 1)
#if (defined(OSEE_TC_CORE2_2_ISR_CAT))
#if (OSEE_TC_CORE2_2_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 2)
#elif (OSEE_TC_CORE2_2_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 2)
#else
#error Invalid value for OSEE_TC_CORE2_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 2)
OSEE_DUMMY_ISR(_core2_, 2)
#endif /* OSEE_TC_CORE2_2_ISR_CAT */
#if (defined(OSEE_TC_CORE2_3_ISR_CAT))
#if (OSEE_TC_CORE2_3_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 3)
#elif (OSEE_TC_CORE2_3_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 3)
#else
#error Invalid value for OSEE_TC_CORE2_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 3)
OSEE_DUMMY_ISR(_core2_, 3)
#endif /* OSEE_TC_CORE2_3_ISR_CAT */
#if (defined(OSEE_TC_CORE2_4_ISR_CAT))
#if (OSEE_TC_CORE2_4_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 4)
#elif (OSEE_TC_CORE2_4_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 4)
#else
#error Invalid value for OSEE_TC_CORE2_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 4)
OSEE_DUMMY_ISR(_core2_, 4)
#endif /* OSEE_TC_CORE2_4_ISR_CAT */
#if (defined(OSEE_TC_CORE2_5_ISR_CAT))
#if (OSEE_TC_CORE2_5_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 5)
#elif (OSEE_TC_CORE2_5_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 5)
#else
#error Invalid value for OSEE_TC_CORE2_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 5)
OSEE_DUMMY_ISR(_core2_, 5)
#endif /* OSEE_TC_CORE2_5_ISR_CAT */
#if (defined(OSEE_TC_CORE2_6_ISR_CAT))
#if (OSEE_TC_CORE2_6_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 6)
#elif (OSEE_TC_CORE2_6_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 6)
#else
#error Invalid value for OSEE_TC_CORE2_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 6)
OSEE_DUMMY_ISR(_core2_, 6)
#endif /* OSEE_TC_CORE2_6_ISR_CAT */
#if (defined(OSEE_TC_CORE2_7_ISR_CAT))
#if (OSEE_TC_CORE2_7_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 7)
#elif (OSEE_TC_CORE2_7_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 7)
#else
#error Invalid value for OSEE_TC_CORE2_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 7)
OSEE_DUMMY_ISR(_core2_, 7)
#endif /* OSEE_TC_CORE2_7_ISR_CAT */
#if (defined(OSEE_TC_CORE2_8_ISR_CAT))
#if (OSEE_TC_CORE2_8_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 8)
#elif (OSEE_TC_CORE2_8_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 8)
#else
#error Invalid value for OSEE_TC_CORE2_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 8)
OSEE_DUMMY_ISR(_core2_, 8)
#endif /* OSEE_TC_CORE2_8_ISR_CAT */
#if (defined(OSEE_TC_CORE2_9_ISR_CAT))
#if (OSEE_TC_CORE2_9_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 9)
#elif (OSEE_TC_CORE2_9_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 9)
#else
#error Invalid value for OSEE_TC_CORE2_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 9)
OSEE_DUMMY_ISR(_core2_, 9)
#endif /* OSEE_TC_CORE2_9_ISR_CAT */
#if (defined(OSEE_TC_CORE2_10_ISR_CAT))
#if (OSEE_TC_CORE2_10_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 10)
#elif (OSEE_TC_CORE2_10_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 10)
#else
#error Invalid value for OSEE_TC_CORE2_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 10)
OSEE_DUMMY_ISR(_core2_, 10)
#endif /* OSEE_TC_CORE2_10_ISR_CAT */
#if (defined(OSEE_TC_CORE2_11_ISR_CAT))
#if (OSEE_TC_CORE2_11_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 11)
#elif (OSEE_TC_CORE2_11_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 11)
#else
#error Invalid value for OSEE_TC_CORE2_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 11)
OSEE_DUMMY_ISR(_core2_, 11)
#endif /* OSEE_TC_CORE2_11_ISR_CAT */
#if (defined(OSEE_TC_CORE2_12_ISR_CAT))
#if (OSEE_TC_CORE2_12_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 12)
#elif (OSEE_TC_CORE2_12_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 12)
#else
#error Invalid value for OSEE_TC_CORE2_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 12)
OSEE_DUMMY_ISR(_core2_, 12)
#endif /* OSEE_TC_CORE2_12_ISR_CAT */
#if (defined(OSEE_TC_CORE2_13_ISR_CAT))
#if (OSEE_TC_CORE2_13_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 13)
#elif (OSEE_TC_CORE2_13_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 13)
#else
#error Invalid value for OSEE_TC_CORE2_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 13)
OSEE_DUMMY_ISR(_core2_, 13)
#endif /* OSEE_TC_CORE2_13_ISR_CAT */
#if (defined(OSEE_TC_CORE2_14_ISR_CAT))
#if (OSEE_TC_CORE2_14_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 14)
#elif (OSEE_TC_CORE2_14_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 14)
#else
#error Invalid value for OSEE_TC_CORE2_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 14)
OSEE_DUMMY_ISR(_core2_, 14)
#endif /* OSEE_TC_CORE2_14_ISR_CAT */
#if (defined(OSEE_TC_CORE2_15_ISR_CAT))
#if (OSEE_TC_CORE2_15_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 15)
#elif (OSEE_TC_CORE2_15_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 15)
#else
#error Invalid value for OSEE_TC_CORE2_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 15)
OSEE_DUMMY_ISR(_core2_, 15)
#endif /* OSEE_TC_CORE2_15_ISR_CAT */
#if (defined(OSEE_TC_CORE2_16_ISR_CAT))
#if (OSEE_TC_CORE2_16_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 16)
#elif (OSEE_TC_CORE2_16_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 16)
#else
#error Invalid value for OSEE_TC_CORE2_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 16)
OSEE_DUMMY_ISR(_core2_, 16)
#endif /* OSEE_TC_CORE2_16_ISR_CAT */
#if (defined(OSEE_TC_CORE2_17_ISR_CAT))
#if (OSEE_TC_CORE2_17_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 17)
#elif (OSEE_TC_CORE2_17_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 17)
#else
#error Invalid value for OSEE_TC_CORE2_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 17)
OSEE_DUMMY_ISR(_core2_, 17)
#endif /* OSEE_TC_CORE2_17_ISR_CAT */
#if (defined(OSEE_TC_CORE2_18_ISR_CAT))
#if (OSEE_TC_CORE2_18_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 18)
#elif (OSEE_TC_CORE2_18_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 18)
#else
#error Invalid value for OSEE_TC_CORE2_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 18)
OSEE_DUMMY_ISR(_core2_, 18)
#endif /* OSEE_TC_CORE2_18_ISR_CAT */
#if (defined(OSEE_TC_CORE2_19_ISR_CAT))
#if (OSEE_TC_CORE2_19_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 19)
#elif (OSEE_TC_CORE2_19_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 19)
#else
#error Invalid value for OSEE_TC_CORE2_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 19)
OSEE_DUMMY_ISR(_core2_, 19)
#endif /* OSEE_TC_CORE2_19_ISR_CAT */
#if (defined(OSEE_TC_CORE2_20_ISR_CAT))
#if (OSEE_TC_CORE2_20_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 20)
#elif (OSEE_TC_CORE2_20_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 20)
#else
#error Invalid value for OSEE_TC_CORE2_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 20)
OSEE_DUMMY_ISR(_core2_, 20)
#endif /* OSEE_TC_CORE2_20_ISR_CAT */
#if (defined(OSEE_TC_CORE2_21_ISR_CAT))
#if (OSEE_TC_CORE2_21_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 21)
#elif (OSEE_TC_CORE2_21_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 21)
#else
#error Invalid value for OSEE_TC_CORE2_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 21)
OSEE_DUMMY_ISR(_core2_, 21)
#endif /* OSEE_TC_CORE2_21_ISR_CAT */
#if (defined(OSEE_TC_CORE2_22_ISR_CAT))
#if (OSEE_TC_CORE2_22_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 22)
#elif (OSEE_TC_CORE2_22_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 22)
#else
#error Invalid value for OSEE_TC_CORE2_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 22)
OSEE_DUMMY_ISR(_core2_, 22)
#endif /* OSEE_TC_CORE2_22_ISR_CAT */
#if (defined(OSEE_TC_CORE2_23_ISR_CAT))
#if (OSEE_TC_CORE2_23_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 23)
#elif (OSEE_TC_CORE2_23_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 23)
#else
#error Invalid value for OSEE_TC_CORE2_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 23)
OSEE_DUMMY_ISR(_core2_, 23)
#endif /* OSEE_TC_CORE2_23_ISR_CAT */
#if (defined(OSEE_TC_CORE2_24_ISR_CAT))
#if (OSEE_TC_CORE2_24_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 24)
#elif (OSEE_TC_CORE2_24_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 24)
#else
#error Invalid value for OSEE_TC_CORE2_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 24)
OSEE_DUMMY_ISR(_core2_, 24)
#endif /* OSEE_TC_CORE2_24_ISR_CAT */
#if (defined(OSEE_TC_CORE2_25_ISR_CAT))
#if (OSEE_TC_CORE2_25_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 25)
#elif (OSEE_TC_CORE2_25_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 25)
#else
#error Invalid value for OSEE_TC_CORE2_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 25)
OSEE_DUMMY_ISR(_core2_, 25)
#endif /* OSEE_TC_CORE2_25_ISR_CAT */
#if (defined(OSEE_TC_CORE2_26_ISR_CAT))
#if (OSEE_TC_CORE2_26_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 26)
#elif (OSEE_TC_CORE2_26_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 26)
#else
#error Invalid value for OSEE_TC_CORE2_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 26)
OSEE_DUMMY_ISR(_core2_, 26)
#endif /* OSEE_TC_CORE2_26_ISR_CAT */
#if (defined(OSEE_TC_CORE2_27_ISR_CAT))
#if (OSEE_TC_CORE2_27_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 27)
#elif (OSEE_TC_CORE2_27_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 27)
#else
#error Invalid value for OSEE_TC_CORE2_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 27)
OSEE_DUMMY_ISR(_core2_, 27)
#endif /* OSEE_TC_CORE2_27_ISR_CAT */
#if (defined(OSEE_TC_CORE2_28_ISR_CAT))
#if (OSEE_TC_CORE2_28_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 28)
#elif (OSEE_TC_CORE2_28_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 28)
#else
#error Invalid value for OSEE_TC_CORE2_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 28)
OSEE_DUMMY_ISR(_core2_, 28)
#endif /* OSEE_TC_CORE2_28_ISR_CAT */
#if (defined(OSEE_TC_CORE2_29_ISR_CAT))
#if (OSEE_TC_CORE2_29_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 29)
#elif (OSEE_TC_CORE2_29_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 29)
#else
#error Invalid value for OSEE_TC_CORE2_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 29)
OSEE_DUMMY_ISR(_core2_, 29)
#endif /* OSEE_TC_CORE2_29_ISR_CAT */
#if (defined(OSEE_TC_CORE2_30_ISR_CAT))
#if (OSEE_TC_CORE2_30_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 30)
#elif (OSEE_TC_CORE2_30_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 30)
#else
#error Invalid value for OSEE_TC_CORE2_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 30)
OSEE_DUMMY_ISR(_core2_, 30)
#endif /* OSEE_TC_CORE2_30_ISR_CAT */
#if (defined(OSEE_TC_CORE2_31_ISR_CAT))
#if (OSEE_TC_CORE2_31_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 31)
#elif (OSEE_TC_CORE2_31_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 31)
#else
#error Invalid value for OSEE_TC_CORE2_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 31)
OSEE_DUMMY_ISR(_core2_, 31)
#endif /* OSEE_TC_CORE2_31_ISR_CAT */
#if (defined(OSEE_TC_CORE2_32_ISR_CAT))
#if (OSEE_TC_CORE2_32_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 32)
#elif (OSEE_TC_CORE2_32_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 32)
#else
#error Invalid value for OSEE_TC_CORE2_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 32)
OSEE_DUMMY_ISR(_core2_, 32)
#endif /* OSEE_TC_CORE2_32_ISR_CAT */
#if (defined(OSEE_TC_CORE2_33_ISR_CAT))
#if (OSEE_TC_CORE2_33_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 33)
#elif (OSEE_TC_CORE2_33_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 33)
#else
#error Invalid value for OSEE_TC_CORE2_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 33)
OSEE_DUMMY_ISR(_core2_, 33)
#endif /* OSEE_TC_CORE2_33_ISR_CAT */
#if (defined(OSEE_TC_CORE2_34_ISR_CAT))
#if (OSEE_TC_CORE2_34_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 34)
#elif (OSEE_TC_CORE2_34_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 34)
#else
#error Invalid value for OSEE_TC_CORE2_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 34)
OSEE_DUMMY_ISR(_core2_, 34)
#endif /* OSEE_TC_CORE2_34_ISR_CAT */
#if (defined(OSEE_TC_CORE2_35_ISR_CAT))
#if (OSEE_TC_CORE2_35_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 35)
#elif (OSEE_TC_CORE2_35_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 35)
#else
#error Invalid value for OSEE_TC_CORE2_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 35)
OSEE_DUMMY_ISR(_core2_, 35)
#endif /* OSEE_TC_CORE2_35_ISR_CAT */
#if (defined(OSEE_TC_CORE2_36_ISR_CAT))
#if (OSEE_TC_CORE2_36_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 36)
#elif (OSEE_TC_CORE2_36_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 36)
#else
#error Invalid value for OSEE_TC_CORE2_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 36)
OSEE_DUMMY_ISR(_core2_, 36)
#endif /* OSEE_TC_CORE2_36_ISR_CAT */
#if (defined(OSEE_TC_CORE2_37_ISR_CAT))
#if (OSEE_TC_CORE2_37_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 37)
#elif (OSEE_TC_CORE2_37_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 37)
#else
#error Invalid value for OSEE_TC_CORE2_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 37)
OSEE_DUMMY_ISR(_core2_, 37)
#endif /* OSEE_TC_CORE2_37_ISR_CAT */
#if (defined(OSEE_TC_CORE2_38_ISR_CAT))
#if (OSEE_TC_CORE2_38_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 38)
#elif (OSEE_TC_CORE2_38_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 38)
#else
#error Invalid value for OSEE_TC_CORE2_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 38)
OSEE_DUMMY_ISR(_core2_, 38)
#endif /* OSEE_TC_CORE2_38_ISR_CAT */
#if (defined(OSEE_TC_CORE2_39_ISR_CAT))
#if (OSEE_TC_CORE2_39_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 39)
#elif (OSEE_TC_CORE2_39_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 39)
#else
#error Invalid value for OSEE_TC_CORE2_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 39)
OSEE_DUMMY_ISR(_core2_, 39)
#endif /* OSEE_TC_CORE2_39_ISR_CAT */
#if (defined(OSEE_TC_CORE2_40_ISR_CAT))
#if (OSEE_TC_CORE2_40_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 40)
#elif (OSEE_TC_CORE2_40_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 40)
#else
#error Invalid value for OSEE_TC_CORE2_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 40)
OSEE_DUMMY_ISR(_core2_, 40)
#endif /* OSEE_TC_CORE2_40_ISR_CAT */
#if (defined(OSEE_TC_CORE2_41_ISR_CAT))
#if (OSEE_TC_CORE2_41_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 41)
#elif (OSEE_TC_CORE2_41_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 41)
#else
#error Invalid value for OSEE_TC_CORE2_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 41)
OSEE_DUMMY_ISR(_core2_, 41)
#endif /* OSEE_TC_CORE2_41_ISR_CAT */
#if (defined(OSEE_TC_CORE2_42_ISR_CAT))
#if (OSEE_TC_CORE2_42_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 42)
#elif (OSEE_TC_CORE2_42_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 42)
#else
#error Invalid value for OSEE_TC_CORE2_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 42)
OSEE_DUMMY_ISR(_core2_, 42)
#endif /* OSEE_TC_CORE2_42_ISR_CAT */
#if (defined(OSEE_TC_CORE2_43_ISR_CAT))
#if (OSEE_TC_CORE2_43_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 43)
#elif (OSEE_TC_CORE2_43_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 43)
#else
#error Invalid value for OSEE_TC_CORE2_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 43)
OSEE_DUMMY_ISR(_core2_, 43)
#endif /* OSEE_TC_CORE2_43_ISR_CAT */
#if (defined(OSEE_TC_CORE2_44_ISR_CAT))
#if (OSEE_TC_CORE2_44_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 44)
#elif (OSEE_TC_CORE2_44_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 44)
#else
#error Invalid value for OSEE_TC_CORE2_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 44)
OSEE_DUMMY_ISR(_core2_, 44)
#endif /* OSEE_TC_CORE2_44_ISR_CAT */
#if (defined(OSEE_TC_CORE2_45_ISR_CAT))
#if (OSEE_TC_CORE2_45_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 45)
#elif (OSEE_TC_CORE2_45_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 45)
#else
#error Invalid value for OSEE_TC_CORE2_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 45)
OSEE_DUMMY_ISR(_core2_, 45)
#endif /* OSEE_TC_CORE2_45_ISR_CAT */
#if (defined(OSEE_TC_CORE2_46_ISR_CAT))
#if (OSEE_TC_CORE2_46_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 46)
#elif (OSEE_TC_CORE2_46_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 46)
#else
#error Invalid value for OSEE_TC_CORE2_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 46)
OSEE_DUMMY_ISR(_core2_, 46)
#endif /* OSEE_TC_CORE2_46_ISR_CAT */
#if (defined(OSEE_TC_CORE2_47_ISR_CAT))
#if (OSEE_TC_CORE2_47_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 47)
#elif (OSEE_TC_CORE2_47_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 47)
#else
#error Invalid value for OSEE_TC_CORE2_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 47)
OSEE_DUMMY_ISR(_core2_, 47)
#endif /* OSEE_TC_CORE2_47_ISR_CAT */
#if (defined(OSEE_TC_CORE2_48_ISR_CAT))
#if (OSEE_TC_CORE2_48_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 48)
#elif (OSEE_TC_CORE2_48_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 48)
#else
#error Invalid value for OSEE_TC_CORE2_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 48)
OSEE_DUMMY_ISR(_core2_, 48)
#endif /* OSEE_TC_CORE2_48_ISR_CAT */
#if (defined(OSEE_TC_CORE2_49_ISR_CAT))
#if (OSEE_TC_CORE2_49_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 49)
#elif (OSEE_TC_CORE2_49_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 49)
#else
#error Invalid value for OSEE_TC_CORE2_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 49)
OSEE_DUMMY_ISR(_core2_, 49)
#endif /* OSEE_TC_CORE2_49_ISR_CAT */
#if (defined(OSEE_TC_CORE2_50_ISR_CAT))
#if (OSEE_TC_CORE2_50_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 50)
#elif (OSEE_TC_CORE2_50_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 50)
#else
#error Invalid value for OSEE_TC_CORE2_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 50)
OSEE_DUMMY_ISR(_core2_, 50)
#endif /* OSEE_TC_CORE2_50_ISR_CAT */
#if (defined(OSEE_TC_CORE2_51_ISR_CAT))
#if (OSEE_TC_CORE2_51_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 51)
#elif (OSEE_TC_CORE2_51_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 51)
#else
#error Invalid value for OSEE_TC_CORE2_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 51)
OSEE_DUMMY_ISR(_core2_, 51)
#endif /* OSEE_TC_CORE2_51_ISR_CAT */
#if (defined(OSEE_TC_CORE2_52_ISR_CAT))
#if (OSEE_TC_CORE2_52_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 52)
#elif (OSEE_TC_CORE2_52_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 52)
#else
#error Invalid value for OSEE_TC_CORE2_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 52)
OSEE_DUMMY_ISR(_core2_, 52)
#endif /* OSEE_TC_CORE2_52_ISR_CAT */
#if (defined(OSEE_TC_CORE2_53_ISR_CAT))
#if (OSEE_TC_CORE2_53_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 53)
#elif (OSEE_TC_CORE2_53_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 53)
#else
#error Invalid value for OSEE_TC_CORE2_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 53)
OSEE_DUMMY_ISR(_core2_, 53)
#endif /* OSEE_TC_CORE2_53_ISR_CAT */
#if (defined(OSEE_TC_CORE2_54_ISR_CAT))
#if (OSEE_TC_CORE2_54_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 54)
#elif (OSEE_TC_CORE2_54_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 54)
#else
#error Invalid value for OSEE_TC_CORE2_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 54)
OSEE_DUMMY_ISR(_core2_, 54)
#endif /* OSEE_TC_CORE2_54_ISR_CAT */
#if (defined(OSEE_TC_CORE2_55_ISR_CAT))
#if (OSEE_TC_CORE2_55_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 55)
#elif (OSEE_TC_CORE2_55_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 55)
#else
#error Invalid value for OSEE_TC_CORE2_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 55)
OSEE_DUMMY_ISR(_core2_, 55)
#endif /* OSEE_TC_CORE2_55_ISR_CAT */
#if (defined(OSEE_TC_CORE2_56_ISR_CAT))
#if (OSEE_TC_CORE2_56_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 56)
#elif (OSEE_TC_CORE2_56_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 56)
#else
#error Invalid value for OSEE_TC_CORE2_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 56)
OSEE_DUMMY_ISR(_core2_, 56)
#endif /* OSEE_TC_CORE2_56_ISR_CAT */
#if (defined(OSEE_TC_CORE2_57_ISR_CAT))
#if (OSEE_TC_CORE2_57_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 57)
#elif (OSEE_TC_CORE2_57_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 57)
#else
#error Invalid value for OSEE_TC_CORE2_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 57)
OSEE_DUMMY_ISR(_core2_, 57)
#endif /* OSEE_TC_CORE2_57_ISR_CAT */
#if (defined(OSEE_TC_CORE2_58_ISR_CAT))
#if (OSEE_TC_CORE2_58_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 58)
#elif (OSEE_TC_CORE2_58_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 58)
#else
#error Invalid value for OSEE_TC_CORE2_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 58)
OSEE_DUMMY_ISR(_core2_, 58)
#endif /* OSEE_TC_CORE2_58_ISR_CAT */
#if (defined(OSEE_TC_CORE2_59_ISR_CAT))
#if (OSEE_TC_CORE2_59_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 59)
#elif (OSEE_TC_CORE2_59_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 59)
#else
#error Invalid value for OSEE_TC_CORE2_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 59)
OSEE_DUMMY_ISR(_core2_, 59)
#endif /* OSEE_TC_CORE2_59_ISR_CAT */
#if (defined(OSEE_TC_CORE2_60_ISR_CAT))
#if (OSEE_TC_CORE2_60_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 60)
#elif (OSEE_TC_CORE2_60_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 60)
#else
#error Invalid value for OSEE_TC_CORE2_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 60)
OSEE_DUMMY_ISR(_core2_, 60)
#endif /* OSEE_TC_CORE2_60_ISR_CAT */
#if (defined(OSEE_TC_CORE2_61_ISR_CAT))
#if (OSEE_TC_CORE2_61_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 61)
#elif (OSEE_TC_CORE2_61_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 61)
#else
#error Invalid value for OSEE_TC_CORE2_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 61)
OSEE_DUMMY_ISR(_core2_, 61)
#endif /* OSEE_TC_CORE2_61_ISR_CAT */
#if (defined(OSEE_TC_CORE2_62_ISR_CAT))
#if (OSEE_TC_CORE2_62_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 62)
#elif (OSEE_TC_CORE2_62_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 62)
#else
#error Invalid value for OSEE_TC_CORE2_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 62)
OSEE_DUMMY_ISR(_core2_, 62)
#endif /* OSEE_TC_CORE2_62_ISR_CAT */
#if (defined(OSEE_TC_CORE2_63_ISR_CAT))
#if (OSEE_TC_CORE2_63_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 63)
#elif (OSEE_TC_CORE2_63_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 63)
#else
#error Invalid value for OSEE_TC_CORE2_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 63)
OSEE_DUMMY_ISR(_core2_, 63)
#endif /* OSEE_TC_CORE2_63_ISR_CAT */
#if (defined(OSEE_TC_CORE2_64_ISR_CAT))
#if (OSEE_TC_CORE2_64_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 64)
#elif (OSEE_TC_CORE2_64_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 64)
#else
#error Invalid value for OSEE_TC_CORE2_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 64)
OSEE_DUMMY_ISR(_core2_, 64)
#endif /* OSEE_TC_CORE2_64_ISR_CAT */
#if (defined(OSEE_TC_CORE2_65_ISR_CAT))
#if (OSEE_TC_CORE2_65_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 65)
#elif (OSEE_TC_CORE2_65_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 65)
#else
#error Invalid value for OSEE_TC_CORE2_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 65)
OSEE_DUMMY_ISR(_core2_, 65)
#endif /* OSEE_TC_CORE2_65_ISR_CAT */
#if (defined(OSEE_TC_CORE2_66_ISR_CAT))
#if (OSEE_TC_CORE2_66_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 66)
#elif (OSEE_TC_CORE2_66_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 66)
#else
#error Invalid value for OSEE_TC_CORE2_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 66)
OSEE_DUMMY_ISR(_core2_, 66)
#endif /* OSEE_TC_CORE2_66_ISR_CAT */
#if (defined(OSEE_TC_CORE2_67_ISR_CAT))
#if (OSEE_TC_CORE2_67_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 67)
#elif (OSEE_TC_CORE2_67_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 67)
#else
#error Invalid value for OSEE_TC_CORE2_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 67)
OSEE_DUMMY_ISR(_core2_, 67)
#endif /* OSEE_TC_CORE2_67_ISR_CAT */
#if (defined(OSEE_TC_CORE2_68_ISR_CAT))
#if (OSEE_TC_CORE2_68_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 68)
#elif (OSEE_TC_CORE2_68_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 68)
#else
#error Invalid value for OSEE_TC_CORE2_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 68)
OSEE_DUMMY_ISR(_core2_, 68)
#endif /* OSEE_TC_CORE2_68_ISR_CAT */
#if (defined(OSEE_TC_CORE2_69_ISR_CAT))
#if (OSEE_TC_CORE2_69_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 69)
#elif (OSEE_TC_CORE2_69_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 69)
#else
#error Invalid value for OSEE_TC_CORE2_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 69)
OSEE_DUMMY_ISR(_core2_, 69)
#endif /* OSEE_TC_CORE2_69_ISR_CAT */
#if (defined(OSEE_TC_CORE2_70_ISR_CAT))
#if (OSEE_TC_CORE2_70_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 70)
#elif (OSEE_TC_CORE2_70_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 70)
#else
#error Invalid value for OSEE_TC_CORE2_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 70)
OSEE_DUMMY_ISR(_core2_, 70)
#endif /* OSEE_TC_CORE2_70_ISR_CAT */
#if (defined(OSEE_TC_CORE2_71_ISR_CAT))
#if (OSEE_TC_CORE2_71_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 71)
#elif (OSEE_TC_CORE2_71_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 71)
#else
#error Invalid value for OSEE_TC_CORE2_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 71)
OSEE_DUMMY_ISR(_core2_, 71)
#endif /* OSEE_TC_CORE2_71_ISR_CAT */
#if (defined(OSEE_TC_CORE2_72_ISR_CAT))
#if (OSEE_TC_CORE2_72_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 72)
#elif (OSEE_TC_CORE2_72_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 72)
#else
#error Invalid value for OSEE_TC_CORE2_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 72)
OSEE_DUMMY_ISR(_core2_, 72)
#endif /* OSEE_TC_CORE2_72_ISR_CAT */
#if (defined(OSEE_TC_CORE2_73_ISR_CAT))
#if (OSEE_TC_CORE2_73_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 73)
#elif (OSEE_TC_CORE2_73_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 73)
#else
#error Invalid value for OSEE_TC_CORE2_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 73)
OSEE_DUMMY_ISR(_core2_, 73)
#endif /* OSEE_TC_CORE2_73_ISR_CAT */
#if (defined(OSEE_TC_CORE2_74_ISR_CAT))
#if (OSEE_TC_CORE2_74_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 74)
#elif (OSEE_TC_CORE2_74_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 74)
#else
#error Invalid value for OSEE_TC_CORE2_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 74)
OSEE_DUMMY_ISR(_core2_, 74)
#endif /* OSEE_TC_CORE2_74_ISR_CAT */
#if (defined(OSEE_TC_CORE2_75_ISR_CAT))
#if (OSEE_TC_CORE2_75_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 75)
#elif (OSEE_TC_CORE2_75_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 75)
#else
#error Invalid value for OSEE_TC_CORE2_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 75)
OSEE_DUMMY_ISR(_core2_, 75)
#endif /* OSEE_TC_CORE2_75_ISR_CAT */
#if (defined(OSEE_TC_CORE2_76_ISR_CAT))
#if (OSEE_TC_CORE2_76_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 76)
#elif (OSEE_TC_CORE2_76_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 76)
#else
#error Invalid value for OSEE_TC_CORE2_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 76)
OSEE_DUMMY_ISR(_core2_, 76)
#endif /* OSEE_TC_CORE2_76_ISR_CAT */
#if (defined(OSEE_TC_CORE2_77_ISR_CAT))
#if (OSEE_TC_CORE2_77_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 77)
#elif (OSEE_TC_CORE2_77_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 77)
#else
#error Invalid value for OSEE_TC_CORE2_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 77)
OSEE_DUMMY_ISR(_core2_, 77)
#endif /* OSEE_TC_CORE2_77_ISR_CAT */
#if (defined(OSEE_TC_CORE2_78_ISR_CAT))
#if (OSEE_TC_CORE2_78_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 78)
#elif (OSEE_TC_CORE2_78_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 78)
#else
#error Invalid value for OSEE_TC_CORE2_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 78)
OSEE_DUMMY_ISR(_core2_, 78)
#endif /* OSEE_TC_CORE2_78_ISR_CAT */
#if (defined(OSEE_TC_CORE2_79_ISR_CAT))
#if (OSEE_TC_CORE2_79_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 79)
#elif (OSEE_TC_CORE2_79_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 79)
#else
#error Invalid value for OSEE_TC_CORE2_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 79)
OSEE_DUMMY_ISR(_core2_, 79)
#endif /* OSEE_TC_CORE2_79_ISR_CAT */
#if (defined(OSEE_TC_CORE2_80_ISR_CAT))
#if (OSEE_TC_CORE2_80_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 80)
#elif (OSEE_TC_CORE2_80_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 80)
#else
#error Invalid value for OSEE_TC_CORE2_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 80)
OSEE_DUMMY_ISR(_core2_, 80)
#endif /* OSEE_TC_CORE2_80_ISR_CAT */
#if (defined(OSEE_TC_CORE2_81_ISR_CAT))
#if (OSEE_TC_CORE2_81_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 81)
#elif (OSEE_TC_CORE2_81_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 81)
#else
#error Invalid value for OSEE_TC_CORE2_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 81)
OSEE_DUMMY_ISR(_core2_, 81)
#endif /* OSEE_TC_CORE2_81_ISR_CAT */
#if (defined(OSEE_TC_CORE2_82_ISR_CAT))
#if (OSEE_TC_CORE2_82_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 82)
#elif (OSEE_TC_CORE2_82_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 82)
#else
#error Invalid value for OSEE_TC_CORE2_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 82)
OSEE_DUMMY_ISR(_core2_, 82)
#endif /* OSEE_TC_CORE2_82_ISR_CAT */
#if (defined(OSEE_TC_CORE2_83_ISR_CAT))
#if (OSEE_TC_CORE2_83_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 83)
#elif (OSEE_TC_CORE2_83_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 83)
#else
#error Invalid value for OSEE_TC_CORE2_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 83)
OSEE_DUMMY_ISR(_core2_, 83)
#endif /* OSEE_TC_CORE2_83_ISR_CAT */
#if (defined(OSEE_TC_CORE2_84_ISR_CAT))
#if (OSEE_TC_CORE2_84_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 84)
#elif (OSEE_TC_CORE2_84_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 84)
#else
#error Invalid value for OSEE_TC_CORE2_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 84)
OSEE_DUMMY_ISR(_core2_, 84)
#endif /* OSEE_TC_CORE2_84_ISR_CAT */
#if (defined(OSEE_TC_CORE2_85_ISR_CAT))
#if (OSEE_TC_CORE2_85_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 85)
#elif (OSEE_TC_CORE2_85_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 85)
#else
#error Invalid value for OSEE_TC_CORE2_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 85)
OSEE_DUMMY_ISR(_core2_, 85)
#endif /* OSEE_TC_CORE2_85_ISR_CAT */
#if (defined(OSEE_TC_CORE2_86_ISR_CAT))
#if (OSEE_TC_CORE2_86_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 86)
#elif (OSEE_TC_CORE2_86_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 86)
#else
#error Invalid value for OSEE_TC_CORE2_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 86)
OSEE_DUMMY_ISR(_core2_, 86)
#endif /* OSEE_TC_CORE2_86_ISR_CAT */
#if (defined(OSEE_TC_CORE2_87_ISR_CAT))
#if (OSEE_TC_CORE2_87_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 87)
#elif (OSEE_TC_CORE2_87_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 87)
#else
#error Invalid value for OSEE_TC_CORE2_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 87)
OSEE_DUMMY_ISR(_core2_, 87)
#endif /* OSEE_TC_CORE2_87_ISR_CAT */
#if (defined(OSEE_TC_CORE2_88_ISR_CAT))
#if (OSEE_TC_CORE2_88_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 88)
#elif (OSEE_TC_CORE2_88_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 88)
#else
#error Invalid value for OSEE_TC_CORE2_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 88)
OSEE_DUMMY_ISR(_core2_, 88)
#endif /* OSEE_TC_CORE2_88_ISR_CAT */
#if (defined(OSEE_TC_CORE2_89_ISR_CAT))
#if (OSEE_TC_CORE2_89_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 89)
#elif (OSEE_TC_CORE2_89_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 89)
#else
#error Invalid value for OSEE_TC_CORE2_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 89)
OSEE_DUMMY_ISR(_core2_, 89)
#endif /* OSEE_TC_CORE2_89_ISR_CAT */
#if (defined(OSEE_TC_CORE2_90_ISR_CAT))
#if (OSEE_TC_CORE2_90_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 90)
#elif (OSEE_TC_CORE2_90_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 90)
#else
#error Invalid value for OSEE_TC_CORE2_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 90)
OSEE_DUMMY_ISR(_core2_, 90)
#endif /* OSEE_TC_CORE2_90_ISR_CAT */
#if (defined(OSEE_TC_CORE2_91_ISR_CAT))
#if (OSEE_TC_CORE2_91_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 91)
#elif (OSEE_TC_CORE2_91_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 91)
#else
#error Invalid value for OSEE_TC_CORE2_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 91)
OSEE_DUMMY_ISR(_core2_, 91)
#endif /* OSEE_TC_CORE2_91_ISR_CAT */
#if (defined(OSEE_TC_CORE2_92_ISR_CAT))
#if (OSEE_TC_CORE2_92_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 92)
#elif (OSEE_TC_CORE2_92_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 92)
#else
#error Invalid value for OSEE_TC_CORE2_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 92)
OSEE_DUMMY_ISR(_core2_, 92)
#endif /* OSEE_TC_CORE2_92_ISR_CAT */
#if (defined(OSEE_TC_CORE2_93_ISR_CAT))
#if (OSEE_TC_CORE2_93_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 93)
#elif (OSEE_TC_CORE2_93_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 93)
#else
#error Invalid value for OSEE_TC_CORE2_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 93)
OSEE_DUMMY_ISR(_core2_, 93)
#endif /* OSEE_TC_CORE2_93_ISR_CAT */
#if (defined(OSEE_TC_CORE2_94_ISR_CAT))
#if (OSEE_TC_CORE2_94_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 94)
#elif (OSEE_TC_CORE2_94_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 94)
#else
#error Invalid value for OSEE_TC_CORE2_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 94)
OSEE_DUMMY_ISR(_core2_, 94)
#endif /* OSEE_TC_CORE2_94_ISR_CAT */
#if (defined(OSEE_TC_CORE2_95_ISR_CAT))
#if (OSEE_TC_CORE2_95_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 95)
#elif (OSEE_TC_CORE2_95_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 95)
#else
#error Invalid value for OSEE_TC_CORE2_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 95)
OSEE_DUMMY_ISR(_core2_, 95)
#endif /* OSEE_TC_CORE2_95_ISR_CAT */
#if (defined(OSEE_TC_CORE2_96_ISR_CAT))
#if (OSEE_TC_CORE2_96_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 96)
#elif (OSEE_TC_CORE2_96_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 96)
#else
#error Invalid value for OSEE_TC_CORE2_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 96)
OSEE_DUMMY_ISR(_core2_, 96)
#endif /* OSEE_TC_CORE2_96_ISR_CAT */
#if (defined(OSEE_TC_CORE2_97_ISR_CAT))
#if (OSEE_TC_CORE2_97_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 97)
#elif (OSEE_TC_CORE2_97_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 97)
#else
#error Invalid value for OSEE_TC_CORE2_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 97)
OSEE_DUMMY_ISR(_core2_, 97)
#endif /* OSEE_TC_CORE2_97_ISR_CAT */
#if (defined(OSEE_TC_CORE2_98_ISR_CAT))
#if (OSEE_TC_CORE2_98_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 98)
#elif (OSEE_TC_CORE2_98_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 98)
#else
#error Invalid value for OSEE_TC_CORE2_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 98)
OSEE_DUMMY_ISR(_core2_, 98)
#endif /* OSEE_TC_CORE2_98_ISR_CAT */
#if (defined(OSEE_TC_CORE2_99_ISR_CAT))
#if (OSEE_TC_CORE2_99_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 99)
#elif (OSEE_TC_CORE2_99_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 99)
#else
#error Invalid value for OSEE_TC_CORE2_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 99)
OSEE_DUMMY_ISR(_core2_, 99)
#endif /* OSEE_TC_CORE2_99_ISR_CAT */
#if (defined(OSEE_TC_CORE2_100_ISR_CAT))
#if (OSEE_TC_CORE2_100_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 100)
#elif (OSEE_TC_CORE2_100_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 100)
#else
#error Invalid value for OSEE_TC_CORE2_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 100)
OSEE_DUMMY_ISR(_core2_, 100)
#endif /* OSEE_TC_CORE2_100_ISR_CAT */
#if (defined(OSEE_TC_CORE2_101_ISR_CAT))
#if (OSEE_TC_CORE2_101_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 101)
#elif (OSEE_TC_CORE2_101_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 101)
#else
#error Invalid value for OSEE_TC_CORE2_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 101)
OSEE_DUMMY_ISR(_core2_, 101)
#endif /* OSEE_TC_CORE2_101_ISR_CAT */
#if (defined(OSEE_TC_CORE2_102_ISR_CAT))
#if (OSEE_TC_CORE2_102_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 102)
#elif (OSEE_TC_CORE2_102_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 102)
#else
#error Invalid value for OSEE_TC_CORE2_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 102)
OSEE_DUMMY_ISR(_core2_, 102)
#endif /* OSEE_TC_CORE2_102_ISR_CAT */
#if (defined(OSEE_TC_CORE2_103_ISR_CAT))
#if (OSEE_TC_CORE2_103_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 103)
#elif (OSEE_TC_CORE2_103_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 103)
#else
#error Invalid value for OSEE_TC_CORE2_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 103)
OSEE_DUMMY_ISR(_core2_, 103)
#endif /* OSEE_TC_CORE2_103_ISR_CAT */
#if (defined(OSEE_TC_CORE2_104_ISR_CAT))
#if (OSEE_TC_CORE2_104_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 104)
#elif (OSEE_TC_CORE2_104_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 104)
#else
#error Invalid value for OSEE_TC_CORE2_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 104)
OSEE_DUMMY_ISR(_core2_, 104)
#endif /* OSEE_TC_CORE2_104_ISR_CAT */
#if (defined(OSEE_TC_CORE2_105_ISR_CAT))
#if (OSEE_TC_CORE2_105_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 105)
#elif (OSEE_TC_CORE2_105_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 105)
#else
#error Invalid value for OSEE_TC_CORE2_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 105)
OSEE_DUMMY_ISR(_core2_, 105)
#endif /* OSEE_TC_CORE2_105_ISR_CAT */
#if (defined(OSEE_TC_CORE2_106_ISR_CAT))
#if (OSEE_TC_CORE2_106_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 106)
#elif (OSEE_TC_CORE2_106_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 106)
#else
#error Invalid value for OSEE_TC_CORE2_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 106)
OSEE_DUMMY_ISR(_core2_, 106)
#endif /* OSEE_TC_CORE2_106_ISR_CAT */
#if (defined(OSEE_TC_CORE2_107_ISR_CAT))
#if (OSEE_TC_CORE2_107_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 107)
#elif (OSEE_TC_CORE2_107_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 107)
#else
#error Invalid value for OSEE_TC_CORE2_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 107)
OSEE_DUMMY_ISR(_core2_, 107)
#endif /* OSEE_TC_CORE2_107_ISR_CAT */
#if (defined(OSEE_TC_CORE2_108_ISR_CAT))
#if (OSEE_TC_CORE2_108_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 108)
#elif (OSEE_TC_CORE2_108_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 108)
#else
#error Invalid value for OSEE_TC_CORE2_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 108)
OSEE_DUMMY_ISR(_core2_, 108)
#endif /* OSEE_TC_CORE2_108_ISR_CAT */
#if (defined(OSEE_TC_CORE2_109_ISR_CAT))
#if (OSEE_TC_CORE2_109_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 109)
#elif (OSEE_TC_CORE2_109_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 109)
#else
#error Invalid value for OSEE_TC_CORE2_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 109)
OSEE_DUMMY_ISR(_core2_, 109)
#endif /* OSEE_TC_CORE2_109_ISR_CAT */
#if (defined(OSEE_TC_CORE2_110_ISR_CAT))
#if (OSEE_TC_CORE2_110_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 110)
#elif (OSEE_TC_CORE2_110_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 110)
#else
#error Invalid value for OSEE_TC_CORE2_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 110)
OSEE_DUMMY_ISR(_core2_, 110)
#endif /* OSEE_TC_CORE2_110_ISR_CAT */
#if (defined(OSEE_TC_CORE2_111_ISR_CAT))
#if (OSEE_TC_CORE2_111_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 111)
#elif (OSEE_TC_CORE2_111_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 111)
#else
#error Invalid value for OSEE_TC_CORE2_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 111)
OSEE_DUMMY_ISR(_core2_, 111)
#endif /* OSEE_TC_CORE2_111_ISR_CAT */
#if (defined(OSEE_TC_CORE2_112_ISR_CAT))
#if (OSEE_TC_CORE2_112_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 112)
#elif (OSEE_TC_CORE2_112_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 112)
#else
#error Invalid value for OSEE_TC_CORE2_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 112)
OSEE_DUMMY_ISR(_core2_, 112)
#endif /* OSEE_TC_CORE2_112_ISR_CAT */
#if (defined(OSEE_TC_CORE2_113_ISR_CAT))
#if (OSEE_TC_CORE2_113_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 113)
#elif (OSEE_TC_CORE2_113_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 113)
#else
#error Invalid value for OSEE_TC_CORE2_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 113)
OSEE_DUMMY_ISR(_core2_, 113)
#endif /* OSEE_TC_CORE2_113_ISR_CAT */
#if (defined(OSEE_TC_CORE2_114_ISR_CAT))
#if (OSEE_TC_CORE2_114_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 114)
#elif (OSEE_TC_CORE2_114_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 114)
#else
#error Invalid value for OSEE_TC_CORE2_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 114)
OSEE_DUMMY_ISR(_core2_, 114)
#endif /* OSEE_TC_CORE2_114_ISR_CAT */
#if (defined(OSEE_TC_CORE2_115_ISR_CAT))
#if (OSEE_TC_CORE2_115_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 115)
#elif (OSEE_TC_CORE2_115_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 115)
#else
#error Invalid value for OSEE_TC_CORE2_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 115)
OSEE_DUMMY_ISR(_core2_, 115)
#endif /* OSEE_TC_CORE2_115_ISR_CAT */
#if (defined(OSEE_TC_CORE2_116_ISR_CAT))
#if (OSEE_TC_CORE2_116_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 116)
#elif (OSEE_TC_CORE2_116_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 116)
#else
#error Invalid value for OSEE_TC_CORE2_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 116)
OSEE_DUMMY_ISR(_core2_, 116)
#endif /* OSEE_TC_CORE2_116_ISR_CAT */
#if (defined(OSEE_TC_CORE2_117_ISR_CAT))
#if (OSEE_TC_CORE2_117_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 117)
#elif (OSEE_TC_CORE2_117_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 117)
#else
#error Invalid value for OSEE_TC_CORE2_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 117)
OSEE_DUMMY_ISR(_core2_, 117)
#endif /* OSEE_TC_CORE2_117_ISR_CAT */
#if (defined(OSEE_TC_CORE2_118_ISR_CAT))
#if (OSEE_TC_CORE2_118_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 118)
#elif (OSEE_TC_CORE2_118_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 118)
#else
#error Invalid value for OSEE_TC_CORE2_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 118)
OSEE_DUMMY_ISR(_core2_, 118)
#endif /* OSEE_TC_CORE2_118_ISR_CAT */
#if (defined(OSEE_TC_CORE2_119_ISR_CAT))
#if (OSEE_TC_CORE2_119_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 119)
#elif (OSEE_TC_CORE2_119_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 119)
#else
#error Invalid value for OSEE_TC_CORE2_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 119)
OSEE_DUMMY_ISR(_core2_, 119)
#endif /* OSEE_TC_CORE2_119_ISR_CAT */
#if (defined(OSEE_TC_CORE2_120_ISR_CAT))
#if (OSEE_TC_CORE2_120_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 120)
#elif (OSEE_TC_CORE2_120_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 120)
#else
#error Invalid value for OSEE_TC_CORE2_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 120)
OSEE_DUMMY_ISR(_core2_, 120)
#endif /* OSEE_TC_CORE2_120_ISR_CAT */
#if (defined(OSEE_TC_CORE2_121_ISR_CAT))
#if (OSEE_TC_CORE2_121_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 121)
#elif (OSEE_TC_CORE2_121_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 121)
#else
#error Invalid value for OSEE_TC_CORE2_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 121)
OSEE_DUMMY_ISR(_core2_, 121)
#endif /* OSEE_TC_CORE2_121_ISR_CAT */
#if (defined(OSEE_TC_CORE2_122_ISR_CAT))
#if (OSEE_TC_CORE2_122_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 122)
#elif (OSEE_TC_CORE2_122_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 122)
#else
#error Invalid value for OSEE_TC_CORE2_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 122)
OSEE_DUMMY_ISR(_core2_, 122)
#endif /* OSEE_TC_CORE2_122_ISR_CAT */
#if (defined(OSEE_TC_CORE2_123_ISR_CAT))
#if (OSEE_TC_CORE2_123_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 123)
#elif (OSEE_TC_CORE2_123_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 123)
#else
#error Invalid value for OSEE_TC_CORE2_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 123)
OSEE_DUMMY_ISR(_core2_, 123)
#endif /* OSEE_TC_CORE2_123_ISR_CAT */
#if (defined(OSEE_TC_CORE2_124_ISR_CAT))
#if (OSEE_TC_CORE2_124_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 124)
#elif (OSEE_TC_CORE2_124_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 124)
#else
#error Invalid value for OSEE_TC_CORE2_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 124)
OSEE_DUMMY_ISR(_core2_, 124)
#endif /* OSEE_TC_CORE2_124_ISR_CAT */
#if (defined(OSEE_TC_CORE2_125_ISR_CAT))
#if (OSEE_TC_CORE2_125_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 125)
#elif (OSEE_TC_CORE2_125_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 125)
#else
#error Invalid value for OSEE_TC_CORE2_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 125)
OSEE_DUMMY_ISR(_core2_, 125)
#endif /* OSEE_TC_CORE2_125_ISR_CAT */
#if (defined(OSEE_TC_CORE2_126_ISR_CAT))
#if (OSEE_TC_CORE2_126_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 126)
#elif (OSEE_TC_CORE2_126_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 126)
#else
#error Invalid value for OSEE_TC_CORE2_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 126)
OSEE_DUMMY_ISR(_core2_, 126)
#endif /* OSEE_TC_CORE2_126_ISR_CAT */
#if (defined(OSEE_TC_CORE2_127_ISR_CAT))
#if (OSEE_TC_CORE2_127_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 127)
#elif (OSEE_TC_CORE2_127_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 127)
#else
#error Invalid value for OSEE_TC_CORE2_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 127)
OSEE_DUMMY_ISR(_core2_, 127)
#endif /* OSEE_TC_CORE2_127_ISR_CAT */
#if (defined(OSEE_TC_CORE2_128_ISR_CAT))
#if (OSEE_TC_CORE2_128_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 128)
#elif (OSEE_TC_CORE2_128_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 128)
#else
#error Invalid value for OSEE_TC_CORE2_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 128)
OSEE_DUMMY_ISR(_core2_, 128)
#endif /* OSEE_TC_CORE2_128_ISR_CAT */
#if (defined(OSEE_TC_CORE2_129_ISR_CAT))
#if (OSEE_TC_CORE2_129_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 129)
#elif (OSEE_TC_CORE2_129_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 129)
#else
#error Invalid value for OSEE_TC_CORE2_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 129)
OSEE_DUMMY_ISR(_core2_, 129)
#endif /* OSEE_TC_CORE2_129_ISR_CAT */
#if (defined(OSEE_TC_CORE2_130_ISR_CAT))
#if (OSEE_TC_CORE2_130_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 130)
#elif (OSEE_TC_CORE2_130_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 130)
#else
#error Invalid value for OSEE_TC_CORE2_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 130)
OSEE_DUMMY_ISR(_core2_, 130)
#endif /* OSEE_TC_CORE2_130_ISR_CAT */
#if (defined(OSEE_TC_CORE2_131_ISR_CAT))
#if (OSEE_TC_CORE2_131_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 131)
#elif (OSEE_TC_CORE2_131_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 131)
#else
#error Invalid value for OSEE_TC_CORE2_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 131)
OSEE_DUMMY_ISR(_core2_, 131)
#endif /* OSEE_TC_CORE2_131_ISR_CAT */
#if (defined(OSEE_TC_CORE2_132_ISR_CAT))
#if (OSEE_TC_CORE2_132_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 132)
#elif (OSEE_TC_CORE2_132_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 132)
#else
#error Invalid value for OSEE_TC_CORE2_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 132)
OSEE_DUMMY_ISR(_core2_, 132)
#endif /* OSEE_TC_CORE2_132_ISR_CAT */
#if (defined(OSEE_TC_CORE2_133_ISR_CAT))
#if (OSEE_TC_CORE2_133_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 133)
#elif (OSEE_TC_CORE2_133_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 133)
#else
#error Invalid value for OSEE_TC_CORE2_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 133)
OSEE_DUMMY_ISR(_core2_, 133)
#endif /* OSEE_TC_CORE2_133_ISR_CAT */
#if (defined(OSEE_TC_CORE2_134_ISR_CAT))
#if (OSEE_TC_CORE2_134_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 134)
#elif (OSEE_TC_CORE2_134_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 134)
#else
#error Invalid value for OSEE_TC_CORE2_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 134)
OSEE_DUMMY_ISR(_core2_, 134)
#endif /* OSEE_TC_CORE2_134_ISR_CAT */
#if (defined(OSEE_TC_CORE2_135_ISR_CAT))
#if (OSEE_TC_CORE2_135_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 135)
#elif (OSEE_TC_CORE2_135_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 135)
#else
#error Invalid value for OSEE_TC_CORE2_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 135)
OSEE_DUMMY_ISR(_core2_, 135)
#endif /* OSEE_TC_CORE2_135_ISR_CAT */
#if (defined(OSEE_TC_CORE2_136_ISR_CAT))
#if (OSEE_TC_CORE2_136_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 136)
#elif (OSEE_TC_CORE2_136_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 136)
#else
#error Invalid value for OSEE_TC_CORE2_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 136)
OSEE_DUMMY_ISR(_core2_, 136)
#endif /* OSEE_TC_CORE2_136_ISR_CAT */
#if (defined(OSEE_TC_CORE2_137_ISR_CAT))
#if (OSEE_TC_CORE2_137_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 137)
#elif (OSEE_TC_CORE2_137_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 137)
#else
#error Invalid value for OSEE_TC_CORE2_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 137)
OSEE_DUMMY_ISR(_core2_, 137)
#endif /* OSEE_TC_CORE2_137_ISR_CAT */
#if (defined(OSEE_TC_CORE2_138_ISR_CAT))
#if (OSEE_TC_CORE2_138_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 138)
#elif (OSEE_TC_CORE2_138_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 138)
#else
#error Invalid value for OSEE_TC_CORE2_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 138)
OSEE_DUMMY_ISR(_core2_, 138)
#endif /* OSEE_TC_CORE2_138_ISR_CAT */
#if (defined(OSEE_TC_CORE2_139_ISR_CAT))
#if (OSEE_TC_CORE2_139_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 139)
#elif (OSEE_TC_CORE2_139_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 139)
#else
#error Invalid value for OSEE_TC_CORE2_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 139)
OSEE_DUMMY_ISR(_core2_, 139)
#endif /* OSEE_TC_CORE2_139_ISR_CAT */
#if (defined(OSEE_TC_CORE2_140_ISR_CAT))
#if (OSEE_TC_CORE2_140_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 140)
#elif (OSEE_TC_CORE2_140_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 140)
#else
#error Invalid value for OSEE_TC_CORE2_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 140)
OSEE_DUMMY_ISR(_core2_, 140)
#endif /* OSEE_TC_CORE2_140_ISR_CAT */
#if (defined(OSEE_TC_CORE2_141_ISR_CAT))
#if (OSEE_TC_CORE2_141_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 141)
#elif (OSEE_TC_CORE2_141_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 141)
#else
#error Invalid value for OSEE_TC_CORE2_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 141)
OSEE_DUMMY_ISR(_core2_, 141)
#endif /* OSEE_TC_CORE2_141_ISR_CAT */
#if (defined(OSEE_TC_CORE2_142_ISR_CAT))
#if (OSEE_TC_CORE2_142_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 142)
#elif (OSEE_TC_CORE2_142_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 142)
#else
#error Invalid value for OSEE_TC_CORE2_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 142)
OSEE_DUMMY_ISR(_core2_, 142)
#endif /* OSEE_TC_CORE2_142_ISR_CAT */
#if (defined(OSEE_TC_CORE2_143_ISR_CAT))
#if (OSEE_TC_CORE2_143_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 143)
#elif (OSEE_TC_CORE2_143_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 143)
#else
#error Invalid value for OSEE_TC_CORE2_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 143)
OSEE_DUMMY_ISR(_core2_, 143)
#endif /* OSEE_TC_CORE2_143_ISR_CAT */
#if (defined(OSEE_TC_CORE2_144_ISR_CAT))
#if (OSEE_TC_CORE2_144_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 144)
#elif (OSEE_TC_CORE2_144_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 144)
#else
#error Invalid value for OSEE_TC_CORE2_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 144)
OSEE_DUMMY_ISR(_core2_, 144)
#endif /* OSEE_TC_CORE2_144_ISR_CAT */
#if (defined(OSEE_TC_CORE2_145_ISR_CAT))
#if (OSEE_TC_CORE2_145_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 145)
#elif (OSEE_TC_CORE2_145_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 145)
#else
#error Invalid value for OSEE_TC_CORE2_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 145)
OSEE_DUMMY_ISR(_core2_, 145)
#endif /* OSEE_TC_CORE2_145_ISR_CAT */
#if (defined(OSEE_TC_CORE2_146_ISR_CAT))
#if (OSEE_TC_CORE2_146_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 146)
#elif (OSEE_TC_CORE2_146_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 146)
#else
#error Invalid value for OSEE_TC_CORE2_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 146)
OSEE_DUMMY_ISR(_core2_, 146)
#endif /* OSEE_TC_CORE2_146_ISR_CAT */
#if (defined(OSEE_TC_CORE2_147_ISR_CAT))
#if (OSEE_TC_CORE2_147_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 147)
#elif (OSEE_TC_CORE2_147_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 147)
#else
#error Invalid value for OSEE_TC_CORE2_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 147)
OSEE_DUMMY_ISR(_core2_, 147)
#endif /* OSEE_TC_CORE2_147_ISR_CAT */
#if (defined(OSEE_TC_CORE2_148_ISR_CAT))
#if (OSEE_TC_CORE2_148_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 148)
#elif (OSEE_TC_CORE2_148_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 148)
#else
#error Invalid value for OSEE_TC_CORE2_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 148)
OSEE_DUMMY_ISR(_core2_, 148)
#endif /* OSEE_TC_CORE2_148_ISR_CAT */
#if (defined(OSEE_TC_CORE2_149_ISR_CAT))
#if (OSEE_TC_CORE2_149_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 149)
#elif (OSEE_TC_CORE2_149_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 149)
#else
#error Invalid value for OSEE_TC_CORE2_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 149)
OSEE_DUMMY_ISR(_core2_, 149)
#endif /* OSEE_TC_CORE2_149_ISR_CAT */
#if (defined(OSEE_TC_CORE2_150_ISR_CAT))
#if (OSEE_TC_CORE2_150_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 150)
#elif (OSEE_TC_CORE2_150_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 150)
#else
#error Invalid value for OSEE_TC_CORE2_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 150)
OSEE_DUMMY_ISR(_core2_, 150)
#endif /* OSEE_TC_CORE2_150_ISR_CAT */
#if (defined(OSEE_TC_CORE2_151_ISR_CAT))
#if (OSEE_TC_CORE2_151_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 151)
#elif (OSEE_TC_CORE2_151_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 151)
#else
#error Invalid value for OSEE_TC_CORE2_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 151)
OSEE_DUMMY_ISR(_core2_, 151)
#endif /* OSEE_TC_CORE2_151_ISR_CAT */
#if (defined(OSEE_TC_CORE2_152_ISR_CAT))
#if (OSEE_TC_CORE2_152_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 152)
#elif (OSEE_TC_CORE2_152_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 152)
#else
#error Invalid value for OSEE_TC_CORE2_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 152)
OSEE_DUMMY_ISR(_core2_, 152)
#endif /* OSEE_TC_CORE2_152_ISR_CAT */
#if (defined(OSEE_TC_CORE2_153_ISR_CAT))
#if (OSEE_TC_CORE2_153_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 153)
#elif (OSEE_TC_CORE2_153_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 153)
#else
#error Invalid value for OSEE_TC_CORE2_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 153)
OSEE_DUMMY_ISR(_core2_, 153)
#endif /* OSEE_TC_CORE2_153_ISR_CAT */
#if (defined(OSEE_TC_CORE2_154_ISR_CAT))
#if (OSEE_TC_CORE2_154_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 154)
#elif (OSEE_TC_CORE2_154_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 154)
#else
#error Invalid value for OSEE_TC_CORE2_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 154)
OSEE_DUMMY_ISR(_core2_, 154)
#endif /* OSEE_TC_CORE2_154_ISR_CAT */
#if (defined(OSEE_TC_CORE2_155_ISR_CAT))
#if (OSEE_TC_CORE2_155_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 155)
#elif (OSEE_TC_CORE2_155_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 155)
#else
#error Invalid value for OSEE_TC_CORE2_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 155)
OSEE_DUMMY_ISR(_core2_, 155)
#endif /* OSEE_TC_CORE2_155_ISR_CAT */
#if (defined(OSEE_TC_CORE2_156_ISR_CAT))
#if (OSEE_TC_CORE2_156_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 156)
#elif (OSEE_TC_CORE2_156_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 156)
#else
#error Invalid value for OSEE_TC_CORE2_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 156)
OSEE_DUMMY_ISR(_core2_, 156)
#endif /* OSEE_TC_CORE2_156_ISR_CAT */
#if (defined(OSEE_TC_CORE2_157_ISR_CAT))
#if (OSEE_TC_CORE2_157_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 157)
#elif (OSEE_TC_CORE2_157_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 157)
#else
#error Invalid value for OSEE_TC_CORE2_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 157)
OSEE_DUMMY_ISR(_core2_, 157)
#endif /* OSEE_TC_CORE2_157_ISR_CAT */
#if (defined(OSEE_TC_CORE2_158_ISR_CAT))
#if (OSEE_TC_CORE2_158_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 158)
#elif (OSEE_TC_CORE2_158_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 158)
#else
#error Invalid value for OSEE_TC_CORE2_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 158)
OSEE_DUMMY_ISR(_core2_, 158)
#endif /* OSEE_TC_CORE2_158_ISR_CAT */
#if (defined(OSEE_TC_CORE2_159_ISR_CAT))
#if (OSEE_TC_CORE2_159_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 159)
#elif (OSEE_TC_CORE2_159_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 159)
#else
#error Invalid value for OSEE_TC_CORE2_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 159)
OSEE_DUMMY_ISR(_core2_, 159)
#endif /* OSEE_TC_CORE2_159_ISR_CAT */
#if (defined(OSEE_TC_CORE2_160_ISR_CAT))
#if (OSEE_TC_CORE2_160_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 160)
#elif (OSEE_TC_CORE2_160_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 160)
#else
#error Invalid value for OSEE_TC_CORE2_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 160)
OSEE_DUMMY_ISR(_core2_, 160)
#endif /* OSEE_TC_CORE2_160_ISR_CAT */
#if (defined(OSEE_TC_CORE2_161_ISR_CAT))
#if (OSEE_TC_CORE2_161_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 161)
#elif (OSEE_TC_CORE2_161_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 161)
#else
#error Invalid value for OSEE_TC_CORE2_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 161)
OSEE_DUMMY_ISR(_core2_, 161)
#endif /* OSEE_TC_CORE2_161_ISR_CAT */
#if (defined(OSEE_TC_CORE2_162_ISR_CAT))
#if (OSEE_TC_CORE2_162_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 162)
#elif (OSEE_TC_CORE2_162_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 162)
#else
#error Invalid value for OSEE_TC_CORE2_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 162)
OSEE_DUMMY_ISR(_core2_, 162)
#endif /* OSEE_TC_CORE2_162_ISR_CAT */
#if (defined(OSEE_TC_CORE2_163_ISR_CAT))
#if (OSEE_TC_CORE2_163_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 163)
#elif (OSEE_TC_CORE2_163_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 163)
#else
#error Invalid value for OSEE_TC_CORE2_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 163)
OSEE_DUMMY_ISR(_core2_, 163)
#endif /* OSEE_TC_CORE2_163_ISR_CAT */
#if (defined(OSEE_TC_CORE2_164_ISR_CAT))
#if (OSEE_TC_CORE2_164_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 164)
#elif (OSEE_TC_CORE2_164_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 164)
#else
#error Invalid value for OSEE_TC_CORE2_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 164)
OSEE_DUMMY_ISR(_core2_, 164)
#endif /* OSEE_TC_CORE2_164_ISR_CAT */
#if (defined(OSEE_TC_CORE2_165_ISR_CAT))
#if (OSEE_TC_CORE2_165_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 165)
#elif (OSEE_TC_CORE2_165_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 165)
#else
#error Invalid value for OSEE_TC_CORE2_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 165)
OSEE_DUMMY_ISR(_core2_, 165)
#endif /* OSEE_TC_CORE2_165_ISR_CAT */
#if (defined(OSEE_TC_CORE2_166_ISR_CAT))
#if (OSEE_TC_CORE2_166_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 166)
#elif (OSEE_TC_CORE2_166_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 166)
#else
#error Invalid value for OSEE_TC_CORE2_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 166)
OSEE_DUMMY_ISR(_core2_, 166)
#endif /* OSEE_TC_CORE2_166_ISR_CAT */
#if (defined(OSEE_TC_CORE2_167_ISR_CAT))
#if (OSEE_TC_CORE2_167_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 167)
#elif (OSEE_TC_CORE2_167_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 167)
#else
#error Invalid value for OSEE_TC_CORE2_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 167)
OSEE_DUMMY_ISR(_core2_, 167)
#endif /* OSEE_TC_CORE2_167_ISR_CAT */
#if (defined(OSEE_TC_CORE2_168_ISR_CAT))
#if (OSEE_TC_CORE2_168_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 168)
#elif (OSEE_TC_CORE2_168_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 168)
#else
#error Invalid value for OSEE_TC_CORE2_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 168)
OSEE_DUMMY_ISR(_core2_, 168)
#endif /* OSEE_TC_CORE2_168_ISR_CAT */
#if (defined(OSEE_TC_CORE2_169_ISR_CAT))
#if (OSEE_TC_CORE2_169_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 169)
#elif (OSEE_TC_CORE2_169_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 169)
#else
#error Invalid value for OSEE_TC_CORE2_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 169)
OSEE_DUMMY_ISR(_core2_, 169)
#endif /* OSEE_TC_CORE2_169_ISR_CAT */
#if (defined(OSEE_TC_CORE2_170_ISR_CAT))
#if (OSEE_TC_CORE2_170_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 170)
#elif (OSEE_TC_CORE2_170_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 170)
#else
#error Invalid value for OSEE_TC_CORE2_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 170)
OSEE_DUMMY_ISR(_core2_, 170)
#endif /* OSEE_TC_CORE2_170_ISR_CAT */
#if (defined(OSEE_TC_CORE2_171_ISR_CAT))
#if (OSEE_TC_CORE2_171_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 171)
#elif (OSEE_TC_CORE2_171_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 171)
#else
#error Invalid value for OSEE_TC_CORE2_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 171)
OSEE_DUMMY_ISR(_core2_, 171)
#endif /* OSEE_TC_CORE2_171_ISR_CAT */
#if (defined(OSEE_TC_CORE2_172_ISR_CAT))
#if (OSEE_TC_CORE2_172_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 172)
#elif (OSEE_TC_CORE2_172_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 172)
#else
#error Invalid value for OSEE_TC_CORE2_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 172)
OSEE_DUMMY_ISR(_core2_, 172)
#endif /* OSEE_TC_CORE2_172_ISR_CAT */
#if (defined(OSEE_TC_CORE2_173_ISR_CAT))
#if (OSEE_TC_CORE2_173_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 173)
#elif (OSEE_TC_CORE2_173_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 173)
#else
#error Invalid value for OSEE_TC_CORE2_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 173)
OSEE_DUMMY_ISR(_core2_, 173)
#endif /* OSEE_TC_CORE2_173_ISR_CAT */
#if (defined(OSEE_TC_CORE2_174_ISR_CAT))
#if (OSEE_TC_CORE2_174_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 174)
#elif (OSEE_TC_CORE2_174_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 174)
#else
#error Invalid value for OSEE_TC_CORE2_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 174)
OSEE_DUMMY_ISR(_core2_, 174)
#endif /* OSEE_TC_CORE2_174_ISR_CAT */
#if (defined(OSEE_TC_CORE2_175_ISR_CAT))
#if (OSEE_TC_CORE2_175_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 175)
#elif (OSEE_TC_CORE2_175_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 175)
#else
#error Invalid value for OSEE_TC_CORE2_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 175)
OSEE_DUMMY_ISR(_core2_, 175)
#endif /* OSEE_TC_CORE2_175_ISR_CAT */
#if (defined(OSEE_TC_CORE2_176_ISR_CAT))
#if (OSEE_TC_CORE2_176_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 176)
#elif (OSEE_TC_CORE2_176_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 176)
#else
#error Invalid value for OSEE_TC_CORE2_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 176)
OSEE_DUMMY_ISR(_core2_, 176)
#endif /* OSEE_TC_CORE2_176_ISR_CAT */
#if (defined(OSEE_TC_CORE2_177_ISR_CAT))
#if (OSEE_TC_CORE2_177_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 177)
#elif (OSEE_TC_CORE2_177_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 177)
#else
#error Invalid value for OSEE_TC_CORE2_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 177)
OSEE_DUMMY_ISR(_core2_, 177)
#endif /* OSEE_TC_CORE2_177_ISR_CAT */
#if (defined(OSEE_TC_CORE2_178_ISR_CAT))
#if (OSEE_TC_CORE2_178_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 178)
#elif (OSEE_TC_CORE2_178_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 178)
#else
#error Invalid value for OSEE_TC_CORE2_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 178)
OSEE_DUMMY_ISR(_core2_, 178)
#endif /* OSEE_TC_CORE2_178_ISR_CAT */
#if (defined(OSEE_TC_CORE2_179_ISR_CAT))
#if (OSEE_TC_CORE2_179_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 179)
#elif (OSEE_TC_CORE2_179_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 179)
#else
#error Invalid value for OSEE_TC_CORE2_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 179)
OSEE_DUMMY_ISR(_core2_, 179)
#endif /* OSEE_TC_CORE2_179_ISR_CAT */
#if (defined(OSEE_TC_CORE2_180_ISR_CAT))
#if (OSEE_TC_CORE2_180_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 180)
#elif (OSEE_TC_CORE2_180_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 180)
#else
#error Invalid value for OSEE_TC_CORE2_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 180)
OSEE_DUMMY_ISR(_core2_, 180)
#endif /* OSEE_TC_CORE2_180_ISR_CAT */
#if (defined(OSEE_TC_CORE2_181_ISR_CAT))
#if (OSEE_TC_CORE2_181_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 181)
#elif (OSEE_TC_CORE2_181_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 181)
#else
#error Invalid value for OSEE_TC_CORE2_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 181)
OSEE_DUMMY_ISR(_core2_, 181)
#endif /* OSEE_TC_CORE2_181_ISR_CAT */
#if (defined(OSEE_TC_CORE2_182_ISR_CAT))
#if (OSEE_TC_CORE2_182_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 182)
#elif (OSEE_TC_CORE2_182_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 182)
#else
#error Invalid value for OSEE_TC_CORE2_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 182)
OSEE_DUMMY_ISR(_core2_, 182)
#endif /* OSEE_TC_CORE2_182_ISR_CAT */
#if (defined(OSEE_TC_CORE2_183_ISR_CAT))
#if (OSEE_TC_CORE2_183_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 183)
#elif (OSEE_TC_CORE2_183_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 183)
#else
#error Invalid value for OSEE_TC_CORE2_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 183)
OSEE_DUMMY_ISR(_core2_, 183)
#endif /* OSEE_TC_CORE2_183_ISR_CAT */
#if (defined(OSEE_TC_CORE2_184_ISR_CAT))
#if (OSEE_TC_CORE2_184_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 184)
#elif (OSEE_TC_CORE2_184_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 184)
#else
#error Invalid value for OSEE_TC_CORE2_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 184)
OSEE_DUMMY_ISR(_core2_, 184)
#endif /* OSEE_TC_CORE2_184_ISR_CAT */
#if (defined(OSEE_TC_CORE2_185_ISR_CAT))
#if (OSEE_TC_CORE2_185_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 185)
#elif (OSEE_TC_CORE2_185_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 185)
#else
#error Invalid value for OSEE_TC_CORE2_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 185)
OSEE_DUMMY_ISR(_core2_, 185)
#endif /* OSEE_TC_CORE2_185_ISR_CAT */
#if (defined(OSEE_TC_CORE2_186_ISR_CAT))
#if (OSEE_TC_CORE2_186_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 186)
#elif (OSEE_TC_CORE2_186_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 186)
#else
#error Invalid value for OSEE_TC_CORE2_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 186)
OSEE_DUMMY_ISR(_core2_, 186)
#endif /* OSEE_TC_CORE2_186_ISR_CAT */
#if (defined(OSEE_TC_CORE2_187_ISR_CAT))
#if (OSEE_TC_CORE2_187_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 187)
#elif (OSEE_TC_CORE2_187_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 187)
#else
#error Invalid value for OSEE_TC_CORE2_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 187)
OSEE_DUMMY_ISR(_core2_, 187)
#endif /* OSEE_TC_CORE2_187_ISR_CAT */
#if (defined(OSEE_TC_CORE2_188_ISR_CAT))
#if (OSEE_TC_CORE2_188_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 188)
#elif (OSEE_TC_CORE2_188_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 188)
#else
#error Invalid value for OSEE_TC_CORE2_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 188)
OSEE_DUMMY_ISR(_core2_, 188)
#endif /* OSEE_TC_CORE2_188_ISR_CAT */
#if (defined(OSEE_TC_CORE2_189_ISR_CAT))
#if (OSEE_TC_CORE2_189_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 189)
#elif (OSEE_TC_CORE2_189_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 189)
#else
#error Invalid value for OSEE_TC_CORE2_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 189)
OSEE_DUMMY_ISR(_core2_, 189)
#endif /* OSEE_TC_CORE2_189_ISR_CAT */
#if (defined(OSEE_TC_CORE2_190_ISR_CAT))
#if (OSEE_TC_CORE2_190_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 190)
#elif (OSEE_TC_CORE2_190_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 190)
#else
#error Invalid value for OSEE_TC_CORE2_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 190)
OSEE_DUMMY_ISR(_core2_, 190)
#endif /* OSEE_TC_CORE2_190_ISR_CAT */
#if (defined(OSEE_TC_CORE2_191_ISR_CAT))
#if (OSEE_TC_CORE2_191_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 191)
#elif (OSEE_TC_CORE2_191_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 191)
#else
#error Invalid value for OSEE_TC_CORE2_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 191)
OSEE_DUMMY_ISR(_core2_, 191)
#endif /* OSEE_TC_CORE2_191_ISR_CAT */
#if (defined(OSEE_TC_CORE2_192_ISR_CAT))
#if (OSEE_TC_CORE2_192_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 192)
#elif (OSEE_TC_CORE2_192_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 192)
#else
#error Invalid value for OSEE_TC_CORE2_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 192)
OSEE_DUMMY_ISR(_core2_, 192)
#endif /* OSEE_TC_CORE2_192_ISR_CAT */
#if (defined(OSEE_TC_CORE2_193_ISR_CAT))
#if (OSEE_TC_CORE2_193_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 193)
#elif (OSEE_TC_CORE2_193_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 193)
#else
#error Invalid value for OSEE_TC_CORE2_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 193)
OSEE_DUMMY_ISR(_core2_, 193)
#endif /* OSEE_TC_CORE2_193_ISR_CAT */
#if (defined(OSEE_TC_CORE2_194_ISR_CAT))
#if (OSEE_TC_CORE2_194_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 194)
#elif (OSEE_TC_CORE2_194_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 194)
#else
#error Invalid value for OSEE_TC_CORE2_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 194)
OSEE_DUMMY_ISR(_core2_, 194)
#endif /* OSEE_TC_CORE2_194_ISR_CAT */
#if (defined(OSEE_TC_CORE2_195_ISR_CAT))
#if (OSEE_TC_CORE2_195_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 195)
#elif (OSEE_TC_CORE2_195_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 195)
#else
#error Invalid value for OSEE_TC_CORE2_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 195)
OSEE_DUMMY_ISR(_core2_, 195)
#endif /* OSEE_TC_CORE2_195_ISR_CAT */
#if (defined(OSEE_TC_CORE2_196_ISR_CAT))
#if (OSEE_TC_CORE2_196_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 196)
#elif (OSEE_TC_CORE2_196_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 196)
#else
#error Invalid value for OSEE_TC_CORE2_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 196)
OSEE_DUMMY_ISR(_core2_, 196)
#endif /* OSEE_TC_CORE2_196_ISR_CAT */
#if (defined(OSEE_TC_CORE2_197_ISR_CAT))
#if (OSEE_TC_CORE2_197_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 197)
#elif (OSEE_TC_CORE2_197_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 197)
#else
#error Invalid value for OSEE_TC_CORE2_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 197)
OSEE_DUMMY_ISR(_core2_, 197)
#endif /* OSEE_TC_CORE2_197_ISR_CAT */
#if (defined(OSEE_TC_CORE2_198_ISR_CAT))
#if (OSEE_TC_CORE2_198_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 198)
#elif (OSEE_TC_CORE2_198_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 198)
#else
#error Invalid value for OSEE_TC_CORE2_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 198)
OSEE_DUMMY_ISR(_core2_, 198)
#endif /* OSEE_TC_CORE2_198_ISR_CAT */
#if (defined(OSEE_TC_CORE2_199_ISR_CAT))
#if (OSEE_TC_CORE2_199_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 199)
#elif (OSEE_TC_CORE2_199_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 199)
#else
#error Invalid value for OSEE_TC_CORE2_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 199)
OSEE_DUMMY_ISR(_core2_, 199)
#endif /* OSEE_TC_CORE2_199_ISR_CAT */
#if (defined(OSEE_TC_CORE2_200_ISR_CAT))
#if (OSEE_TC_CORE2_200_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 200)
#elif (OSEE_TC_CORE2_200_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 200)
#else
#error Invalid value for OSEE_TC_CORE2_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 200)
OSEE_DUMMY_ISR(_core2_, 200)
#endif /* OSEE_TC_CORE2_200_ISR_CAT */
#if (defined(OSEE_TC_CORE2_201_ISR_CAT))
#if (OSEE_TC_CORE2_201_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 201)
#elif (OSEE_TC_CORE2_201_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 201)
#else
#error Invalid value for OSEE_TC_CORE2_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 201)
OSEE_DUMMY_ISR(_core2_, 201)
#endif /* OSEE_TC_CORE2_201_ISR_CAT */
#if (defined(OSEE_TC_CORE2_202_ISR_CAT))
#if (OSEE_TC_CORE2_202_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 202)
#elif (OSEE_TC_CORE2_202_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 202)
#else
#error Invalid value for OSEE_TC_CORE2_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 202)
OSEE_DUMMY_ISR(_core2_, 202)
#endif /* OSEE_TC_CORE2_202_ISR_CAT */
#if (defined(OSEE_TC_CORE2_203_ISR_CAT))
#if (OSEE_TC_CORE2_203_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 203)
#elif (OSEE_TC_CORE2_203_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 203)
#else
#error Invalid value for OSEE_TC_CORE2_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 203)
OSEE_DUMMY_ISR(_core2_, 203)
#endif /* OSEE_TC_CORE2_203_ISR_CAT */
#if (defined(OSEE_TC_CORE2_204_ISR_CAT))
#if (OSEE_TC_CORE2_204_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 204)
#elif (OSEE_TC_CORE2_204_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 204)
#else
#error Invalid value for OSEE_TC_CORE2_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 204)
OSEE_DUMMY_ISR(_core2_, 204)
#endif /* OSEE_TC_CORE2_204_ISR_CAT */
#if (defined(OSEE_TC_CORE2_205_ISR_CAT))
#if (OSEE_TC_CORE2_205_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 205)
#elif (OSEE_TC_CORE2_205_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 205)
#else
#error Invalid value for OSEE_TC_CORE2_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 205)
OSEE_DUMMY_ISR(_core2_, 205)
#endif /* OSEE_TC_CORE2_205_ISR_CAT */
#if (defined(OSEE_TC_CORE2_206_ISR_CAT))
#if (OSEE_TC_CORE2_206_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 206)
#elif (OSEE_TC_CORE2_206_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 206)
#else
#error Invalid value for OSEE_TC_CORE2_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 206)
OSEE_DUMMY_ISR(_core2_, 206)
#endif /* OSEE_TC_CORE2_206_ISR_CAT */
#if (defined(OSEE_TC_CORE2_207_ISR_CAT))
#if (OSEE_TC_CORE2_207_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 207)
#elif (OSEE_TC_CORE2_207_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 207)
#else
#error Invalid value for OSEE_TC_CORE2_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 207)
OSEE_DUMMY_ISR(_core2_, 207)
#endif /* OSEE_TC_CORE2_207_ISR_CAT */
#if (defined(OSEE_TC_CORE2_208_ISR_CAT))
#if (OSEE_TC_CORE2_208_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 208)
#elif (OSEE_TC_CORE2_208_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 208)
#else
#error Invalid value for OSEE_TC_CORE2_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 208)
OSEE_DUMMY_ISR(_core2_, 208)
#endif /* OSEE_TC_CORE2_208_ISR_CAT */
#if (defined(OSEE_TC_CORE2_209_ISR_CAT))
#if (OSEE_TC_CORE2_209_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 209)
#elif (OSEE_TC_CORE2_209_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 209)
#else
#error Invalid value for OSEE_TC_CORE2_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 209)
OSEE_DUMMY_ISR(_core2_, 209)
#endif /* OSEE_TC_CORE2_209_ISR_CAT */
#if (defined(OSEE_TC_CORE2_210_ISR_CAT))
#if (OSEE_TC_CORE2_210_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 210)
#elif (OSEE_TC_CORE2_210_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 210)
#else
#error Invalid value for OSEE_TC_CORE2_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 210)
OSEE_DUMMY_ISR(_core2_, 210)
#endif /* OSEE_TC_CORE2_210_ISR_CAT */
#if (defined(OSEE_TC_CORE2_211_ISR_CAT))
#if (OSEE_TC_CORE2_211_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 211)
#elif (OSEE_TC_CORE2_211_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 211)
#else
#error Invalid value for OSEE_TC_CORE2_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 211)
OSEE_DUMMY_ISR(_core2_, 211)
#endif /* OSEE_TC_CORE2_211_ISR_CAT */
#if (defined(OSEE_TC_CORE2_212_ISR_CAT))
#if (OSEE_TC_CORE2_212_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 212)
#elif (OSEE_TC_CORE2_212_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 212)
#else
#error Invalid value for OSEE_TC_CORE2_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 212)
OSEE_DUMMY_ISR(_core2_, 212)
#endif /* OSEE_TC_CORE2_212_ISR_CAT */
#if (defined(OSEE_TC_CORE2_213_ISR_CAT))
#if (OSEE_TC_CORE2_213_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 213)
#elif (OSEE_TC_CORE2_213_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 213)
#else
#error Invalid value for OSEE_TC_CORE2_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 213)
OSEE_DUMMY_ISR(_core2_, 213)
#endif /* OSEE_TC_CORE2_213_ISR_CAT */
#if (defined(OSEE_TC_CORE2_214_ISR_CAT))
#if (OSEE_TC_CORE2_214_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 214)
#elif (OSEE_TC_CORE2_214_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 214)
#else
#error Invalid value for OSEE_TC_CORE2_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 214)
OSEE_DUMMY_ISR(_core2_, 214)
#endif /* OSEE_TC_CORE2_214_ISR_CAT */
#if (defined(OSEE_TC_CORE2_215_ISR_CAT))
#if (OSEE_TC_CORE2_215_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 215)
#elif (OSEE_TC_CORE2_215_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 215)
#else
#error Invalid value for OSEE_TC_CORE2_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 215)
OSEE_DUMMY_ISR(_core2_, 215)
#endif /* OSEE_TC_CORE2_215_ISR_CAT */
#if (defined(OSEE_TC_CORE2_216_ISR_CAT))
#if (OSEE_TC_CORE2_216_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 216)
#elif (OSEE_TC_CORE2_216_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 216)
#else
#error Invalid value for OSEE_TC_CORE2_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 216)
OSEE_DUMMY_ISR(_core2_, 216)
#endif /* OSEE_TC_CORE2_216_ISR_CAT */
#if (defined(OSEE_TC_CORE2_217_ISR_CAT))
#if (OSEE_TC_CORE2_217_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 217)
#elif (OSEE_TC_CORE2_217_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 217)
#else
#error Invalid value for OSEE_TC_CORE2_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 217)
OSEE_DUMMY_ISR(_core2_, 217)
#endif /* OSEE_TC_CORE2_217_ISR_CAT */
#if (defined(OSEE_TC_CORE2_218_ISR_CAT))
#if (OSEE_TC_CORE2_218_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 218)
#elif (OSEE_TC_CORE2_218_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 218)
#else
#error Invalid value for OSEE_TC_CORE2_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 218)
OSEE_DUMMY_ISR(_core2_, 218)
#endif /* OSEE_TC_CORE2_218_ISR_CAT */
#if (defined(OSEE_TC_CORE2_219_ISR_CAT))
#if (OSEE_TC_CORE2_219_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 219)
#elif (OSEE_TC_CORE2_219_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 219)
#else
#error Invalid value for OSEE_TC_CORE2_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 219)
OSEE_DUMMY_ISR(_core2_, 219)
#endif /* OSEE_TC_CORE2_219_ISR_CAT */
#if (defined(OSEE_TC_CORE2_220_ISR_CAT))
#if (OSEE_TC_CORE2_220_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 220)
#elif (OSEE_TC_CORE2_220_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 220)
#else
#error Invalid value for OSEE_TC_CORE2_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 220)
OSEE_DUMMY_ISR(_core2_, 220)
#endif /* OSEE_TC_CORE2_220_ISR_CAT */
#if (defined(OSEE_TC_CORE2_221_ISR_CAT))
#if (OSEE_TC_CORE2_221_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 221)
#elif (OSEE_TC_CORE2_221_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 221)
#else
#error Invalid value for OSEE_TC_CORE2_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 221)
OSEE_DUMMY_ISR(_core2_, 221)
#endif /* OSEE_TC_CORE2_221_ISR_CAT */
#if (defined(OSEE_TC_CORE2_222_ISR_CAT))
#if (OSEE_TC_CORE2_222_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 222)
#elif (OSEE_TC_CORE2_222_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 222)
#else
#error Invalid value for OSEE_TC_CORE2_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 222)
OSEE_DUMMY_ISR(_core2_, 222)
#endif /* OSEE_TC_CORE2_222_ISR_CAT */
#if (defined(OSEE_TC_CORE2_223_ISR_CAT))
#if (OSEE_TC_CORE2_223_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 223)
#elif (OSEE_TC_CORE2_223_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 223)
#else
#error Invalid value for OSEE_TC_CORE2_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 223)
OSEE_DUMMY_ISR(_core2_, 223)
#endif /* OSEE_TC_CORE2_223_ISR_CAT */
#if (defined(OSEE_TC_CORE2_224_ISR_CAT))
#if (OSEE_TC_CORE2_224_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 224)
#elif (OSEE_TC_CORE2_224_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 224)
#else
#error Invalid value for OSEE_TC_CORE2_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 224)
OSEE_DUMMY_ISR(_core2_, 224)
#endif /* OSEE_TC_CORE2_224_ISR_CAT */
#if (defined(OSEE_TC_CORE2_225_ISR_CAT))
#if (OSEE_TC_CORE2_225_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 225)
#elif (OSEE_TC_CORE2_225_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 225)
#else
#error Invalid value for OSEE_TC_CORE2_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 225)
OSEE_DUMMY_ISR(_core2_, 225)
#endif /* OSEE_TC_CORE2_225_ISR_CAT */
#if (defined(OSEE_TC_CORE2_226_ISR_CAT))
#if (OSEE_TC_CORE2_226_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 226)
#elif (OSEE_TC_CORE2_226_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 226)
#else
#error Invalid value for OSEE_TC_CORE2_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 226)
OSEE_DUMMY_ISR(_core2_, 226)
#endif /* OSEE_TC_CORE2_226_ISR_CAT */
#if (defined(OSEE_TC_CORE2_227_ISR_CAT))
#if (OSEE_TC_CORE2_227_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 227)
#elif (OSEE_TC_CORE2_227_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 227)
#else
#error Invalid value for OSEE_TC_CORE2_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 227)
OSEE_DUMMY_ISR(_core2_, 227)
#endif /* OSEE_TC_CORE2_227_ISR_CAT */
#if (defined(OSEE_TC_CORE2_228_ISR_CAT))
#if (OSEE_TC_CORE2_228_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 228)
#elif (OSEE_TC_CORE2_228_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 228)
#else
#error Invalid value for OSEE_TC_CORE2_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 228)
OSEE_DUMMY_ISR(_core2_, 228)
#endif /* OSEE_TC_CORE2_228_ISR_CAT */
#if (defined(OSEE_TC_CORE2_229_ISR_CAT))
#if (OSEE_TC_CORE2_229_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 229)
#elif (OSEE_TC_CORE2_229_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 229)
#else
#error Invalid value for OSEE_TC_CORE2_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 229)
OSEE_DUMMY_ISR(_core2_, 229)
#endif /* OSEE_TC_CORE2_229_ISR_CAT */
#if (defined(OSEE_TC_CORE2_230_ISR_CAT))
#if (OSEE_TC_CORE2_230_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 230)
#elif (OSEE_TC_CORE2_230_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 230)
#else
#error Invalid value for OSEE_TC_CORE2_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 230)
OSEE_DUMMY_ISR(_core2_, 230)
#endif /* OSEE_TC_CORE2_230_ISR_CAT */
#if (defined(OSEE_TC_CORE2_231_ISR_CAT))
#if (OSEE_TC_CORE2_231_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 231)
#elif (OSEE_TC_CORE2_231_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 231)
#else
#error Invalid value for OSEE_TC_CORE2_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 231)
OSEE_DUMMY_ISR(_core2_, 231)
#endif /* OSEE_TC_CORE2_231_ISR_CAT */
#if (defined(OSEE_TC_CORE2_232_ISR_CAT))
#if (OSEE_TC_CORE2_232_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 232)
#elif (OSEE_TC_CORE2_232_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 232)
#else
#error Invalid value for OSEE_TC_CORE2_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 232)
OSEE_DUMMY_ISR(_core2_, 232)
#endif /* OSEE_TC_CORE2_232_ISR_CAT */
#if (defined(OSEE_TC_CORE2_233_ISR_CAT))
#if (OSEE_TC_CORE2_233_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 233)
#elif (OSEE_TC_CORE2_233_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 233)
#else
#error Invalid value for OSEE_TC_CORE2_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 233)
OSEE_DUMMY_ISR(_core2_, 233)
#endif /* OSEE_TC_CORE2_233_ISR_CAT */
#if (defined(OSEE_TC_CORE2_234_ISR_CAT))
#if (OSEE_TC_CORE2_234_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 234)
#elif (OSEE_TC_CORE2_234_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 234)
#else
#error Invalid value for OSEE_TC_CORE2_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 234)
OSEE_DUMMY_ISR(_core2_, 234)
#endif /* OSEE_TC_CORE2_234_ISR_CAT */
#if (defined(OSEE_TC_CORE2_235_ISR_CAT))
#if (OSEE_TC_CORE2_235_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 235)
#elif (OSEE_TC_CORE2_235_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 235)
#else
#error Invalid value for OSEE_TC_CORE2_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 235)
OSEE_DUMMY_ISR(_core2_, 235)
#endif /* OSEE_TC_CORE2_235_ISR_CAT */
#if (defined(OSEE_TC_CORE2_236_ISR_CAT))
#if (OSEE_TC_CORE2_236_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 236)
#elif (OSEE_TC_CORE2_236_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 236)
#else
#error Invalid value for OSEE_TC_CORE2_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 236)
OSEE_DUMMY_ISR(_core2_, 236)
#endif /* OSEE_TC_CORE2_236_ISR_CAT */
#if (defined(OSEE_TC_CORE2_237_ISR_CAT))
#if (OSEE_TC_CORE2_237_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 237)
#elif (OSEE_TC_CORE2_237_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 237)
#else
#error Invalid value for OSEE_TC_CORE2_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 237)
OSEE_DUMMY_ISR(_core2_, 237)
#endif /* OSEE_TC_CORE2_237_ISR_CAT */
#if (defined(OSEE_TC_CORE2_238_ISR_CAT))
#if (OSEE_TC_CORE2_238_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 238)
#elif (OSEE_TC_CORE2_238_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 238)
#else
#error Invalid value for OSEE_TC_CORE2_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 238)
OSEE_DUMMY_ISR(_core2_, 238)
#endif /* OSEE_TC_CORE2_238_ISR_CAT */
#if (defined(OSEE_TC_CORE2_239_ISR_CAT))
#if (OSEE_TC_CORE2_239_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 239)
#elif (OSEE_TC_CORE2_239_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 239)
#else
#error Invalid value for OSEE_TC_CORE2_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 239)
OSEE_DUMMY_ISR(_core2_, 239)
#endif /* OSEE_TC_CORE2_239_ISR_CAT */
#if (defined(OSEE_TC_CORE2_240_ISR_CAT))
#if (OSEE_TC_CORE2_240_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 240)
#elif (OSEE_TC_CORE2_240_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 240)
#else
#error Invalid value for OSEE_TC_CORE2_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 240)
OSEE_DUMMY_ISR(_core2_, 240)
#endif /* OSEE_TC_CORE2_240_ISR_CAT */
#if (defined(OSEE_TC_CORE2_241_ISR_CAT))
#if (OSEE_TC_CORE2_241_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 241)
#elif (OSEE_TC_CORE2_241_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 241)
#else
#error Invalid value for OSEE_TC_CORE2_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 241)
OSEE_DUMMY_ISR(_core2_, 241)
#endif /* OSEE_TC_CORE2_241_ISR_CAT */
#if (defined(OSEE_TC_CORE2_242_ISR_CAT))
#if (OSEE_TC_CORE2_242_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 242)
#elif (OSEE_TC_CORE2_242_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 242)
#else
#error Invalid value for OSEE_TC_CORE2_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 242)
OSEE_DUMMY_ISR(_core2_, 242)
#endif /* OSEE_TC_CORE2_242_ISR_CAT */
#if (defined(OSEE_TC_CORE2_243_ISR_CAT))
#if (OSEE_TC_CORE2_243_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 243)
#elif (OSEE_TC_CORE2_243_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 243)
#else
#error Invalid value for OSEE_TC_CORE2_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 243)
OSEE_DUMMY_ISR(_core2_, 243)
#endif /* OSEE_TC_CORE2_243_ISR_CAT */
#if (defined(OSEE_TC_CORE2_244_ISR_CAT))
#if (OSEE_TC_CORE2_244_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 244)
#elif (OSEE_TC_CORE2_244_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 244)
#else
#error Invalid value for OSEE_TC_CORE2_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 244)
OSEE_DUMMY_ISR(_core2_, 244)
#endif /* OSEE_TC_CORE2_244_ISR_CAT */
#if (defined(OSEE_TC_CORE2_245_ISR_CAT))
#if (OSEE_TC_CORE2_245_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 245)
#elif (OSEE_TC_CORE2_245_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 245)
#else
#error Invalid value for OSEE_TC_CORE2_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 245)
OSEE_DUMMY_ISR(_core2_, 245)
#endif /* OSEE_TC_CORE2_245_ISR_CAT */
#if (defined(OSEE_TC_CORE2_246_ISR_CAT))
#if (OSEE_TC_CORE2_246_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 246)
#elif (OSEE_TC_CORE2_246_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 246)
#else
#error Invalid value for OSEE_TC_CORE2_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 246)
OSEE_DUMMY_ISR(_core2_, 246)
#endif /* OSEE_TC_CORE2_246_ISR_CAT */
#if (defined(OSEE_TC_CORE2_247_ISR_CAT))
#if (OSEE_TC_CORE2_247_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 247)
#elif (OSEE_TC_CORE2_247_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 247)
#else
#error Invalid value for OSEE_TC_CORE2_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 247)
OSEE_DUMMY_ISR(_core2_, 247)
#endif /* OSEE_TC_CORE2_247_ISR_CAT */
#if (defined(OSEE_TC_CORE2_248_ISR_CAT))
#if (OSEE_TC_CORE2_248_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 248)
#elif (OSEE_TC_CORE2_248_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 248)
#else
#error Invalid value for OSEE_TC_CORE2_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 248)
OSEE_DUMMY_ISR(_core2_, 248)
#endif /* OSEE_TC_CORE2_248_ISR_CAT */
#if (defined(OSEE_TC_CORE2_249_ISR_CAT))
#if (OSEE_TC_CORE2_249_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 249)
#elif (OSEE_TC_CORE2_249_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 249)
#else
#error Invalid value for OSEE_TC_CORE2_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 249)
OSEE_DUMMY_ISR(_core2_, 249)
#endif /* OSEE_TC_CORE2_249_ISR_CAT */
#if (defined(OSEE_TC_CORE2_250_ISR_CAT))
#if (OSEE_TC_CORE2_250_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 250)
#elif (OSEE_TC_CORE2_250_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 250)
#else
#error Invalid value for OSEE_TC_CORE2_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 250)
OSEE_DUMMY_ISR(_core2_, 250)
#endif /* OSEE_TC_CORE2_250_ISR_CAT */
#if (defined(OSEE_TC_CORE2_251_ISR_CAT))
#if (OSEE_TC_CORE2_251_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 251)
#elif (OSEE_TC_CORE2_251_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 251)
#else
#error Invalid value for OSEE_TC_CORE2_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 251)
OSEE_DUMMY_ISR(_core2_, 251)
#endif /* OSEE_TC_CORE2_251_ISR_CAT */
#if (defined(OSEE_TC_CORE2_252_ISR_CAT))
#if (OSEE_TC_CORE2_252_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 252)
#elif (OSEE_TC_CORE2_252_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 252)
#else
#error Invalid value for OSEE_TC_CORE2_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 252)
OSEE_DUMMY_ISR(_core2_, 252)
#endif /* OSEE_TC_CORE2_252_ISR_CAT */
#if (defined(OSEE_TC_CORE2_253_ISR_CAT))
#if (OSEE_TC_CORE2_253_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 253)
#elif (OSEE_TC_CORE2_253_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 253)
#else
#error Invalid value for OSEE_TC_CORE2_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 253)
OSEE_DUMMY_ISR(_core2_, 253)
#endif /* OSEE_TC_CORE2_253_ISR_CAT */
#if (defined(OSEE_TC_CORE2_254_ISR_CAT))
#if (OSEE_TC_CORE2_254_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 254)
#elif (OSEE_TC_CORE2_254_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 254)
#else
#error Invalid value for OSEE_TC_CORE2_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 254)
OSEE_DUMMY_ISR(_core2_, 254)
#endif /* OSEE_TC_CORE2_254_ISR_CAT */
#if (defined(OSEE_TC_CORE2_255_ISR_CAT))
#if (OSEE_TC_CORE2_255_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core2_, 255)
#elif (OSEE_TC_CORE2_255_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core2_, 255)
#else
#error Invalid value for OSEE_TC_CORE2_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 255)
OSEE_DUMMY_ISR(_core2_, 255)
#endif /* OSEE_TC_CORE2_255_ISR_CAT */
#endif /* OSEE_TC_CORE2_ISR_MAX_PRIO */


#if(defined(OSEE_TC_CORE3_ISR_MAX_PRIO))
OSEE_ISR2_DECLARE(_core3_, 1)
#if (defined(OSEE_TC_CORE3_2_ISR_CAT))
#if (OSEE_TC_CORE3_2_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 2)
#elif (OSEE_TC_CORE3_2_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 2)
#else
#error Invalid value for OSEE_TC_CORE3_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 2)
OSEE_DUMMY_ISR(_core3_, 2)
#endif /* OSEE_TC_CORE3_2_ISR_CAT */
#if (defined(OSEE_TC_CORE3_3_ISR_CAT))
#if (OSEE_TC_CORE3_3_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 3)
#elif (OSEE_TC_CORE3_3_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 3)
#else
#error Invalid value for OSEE_TC_CORE3_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 3)
OSEE_DUMMY_ISR(_core3_, 3)
#endif /* OSEE_TC_CORE3_3_ISR_CAT */
#if (defined(OSEE_TC_CORE3_4_ISR_CAT))
#if (OSEE_TC_CORE3_4_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 4)
#elif (OSEE_TC_CORE3_4_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 4)
#else
#error Invalid value for OSEE_TC_CORE3_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 4)
OSEE_DUMMY_ISR(_core3_, 4)
#endif /* OSEE_TC_CORE3_4_ISR_CAT */
#if (defined(OSEE_TC_CORE3_5_ISR_CAT))
#if (OSEE_TC_CORE3_5_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 5)
#elif (OSEE_TC_CORE3_5_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 5)
#else
#error Invalid value for OSEE_TC_CORE3_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 5)
OSEE_DUMMY_ISR(_core3_, 5)
#endif /* OSEE_TC_CORE3_5_ISR_CAT */
#if (defined(OSEE_TC_CORE3_6_ISR_CAT))
#if (OSEE_TC_CORE3_6_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 6)
#elif (OSEE_TC_CORE3_6_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 6)
#else
#error Invalid value for OSEE_TC_CORE3_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 6)
OSEE_DUMMY_ISR(_core3_, 6)
#endif /* OSEE_TC_CORE3_6_ISR_CAT */
#if (defined(OSEE_TC_CORE3_7_ISR_CAT))
#if (OSEE_TC_CORE3_7_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 7)
#elif (OSEE_TC_CORE3_7_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 7)
#else
#error Invalid value for OSEE_TC_CORE3_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 7)
OSEE_DUMMY_ISR(_core3_, 7)
#endif /* OSEE_TC_CORE3_7_ISR_CAT */
#if (defined(OSEE_TC_CORE3_8_ISR_CAT))
#if (OSEE_TC_CORE3_8_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 8)
#elif (OSEE_TC_CORE3_8_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 8)
#else
#error Invalid value for OSEE_TC_CORE3_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 8)
OSEE_DUMMY_ISR(_core3_, 8)
#endif /* OSEE_TC_CORE3_8_ISR_CAT */
#if (defined(OSEE_TC_CORE3_9_ISR_CAT))
#if (OSEE_TC_CORE3_9_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 9)
#elif (OSEE_TC_CORE3_9_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 9)
#else
#error Invalid value for OSEE_TC_CORE3_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 9)
OSEE_DUMMY_ISR(_core3_, 9)
#endif /* OSEE_TC_CORE3_9_ISR_CAT */
#if (defined(OSEE_TC_CORE3_10_ISR_CAT))
#if (OSEE_TC_CORE3_10_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 10)
#elif (OSEE_TC_CORE3_10_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 10)
#else
#error Invalid value for OSEE_TC_CORE3_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 10)
OSEE_DUMMY_ISR(_core3_, 10)
#endif /* OSEE_TC_CORE3_10_ISR_CAT */
#if (defined(OSEE_TC_CORE3_11_ISR_CAT))
#if (OSEE_TC_CORE3_11_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 11)
#elif (OSEE_TC_CORE3_11_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 11)
#else
#error Invalid value for OSEE_TC_CORE3_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 11)
OSEE_DUMMY_ISR(_core3_, 11)
#endif /* OSEE_TC_CORE3_11_ISR_CAT */
#if (defined(OSEE_TC_CORE3_12_ISR_CAT))
#if (OSEE_TC_CORE3_12_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 12)
#elif (OSEE_TC_CORE3_12_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 12)
#else
#error Invalid value for OSEE_TC_CORE3_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 12)
OSEE_DUMMY_ISR(_core3_, 12)
#endif /* OSEE_TC_CORE3_12_ISR_CAT */
#if (defined(OSEE_TC_CORE3_13_ISR_CAT))
#if (OSEE_TC_CORE3_13_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 13)
#elif (OSEE_TC_CORE3_13_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 13)
#else
#error Invalid value for OSEE_TC_CORE3_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 13)
OSEE_DUMMY_ISR(_core3_, 13)
#endif /* OSEE_TC_CORE3_13_ISR_CAT */
#if (defined(OSEE_TC_CORE3_14_ISR_CAT))
#if (OSEE_TC_CORE3_14_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 14)
#elif (OSEE_TC_CORE3_14_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 14)
#else
#error Invalid value for OSEE_TC_CORE3_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 14)
OSEE_DUMMY_ISR(_core3_, 14)
#endif /* OSEE_TC_CORE3_14_ISR_CAT */
#if (defined(OSEE_TC_CORE3_15_ISR_CAT))
#if (OSEE_TC_CORE3_15_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 15)
#elif (OSEE_TC_CORE3_15_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 15)
#else
#error Invalid value for OSEE_TC_CORE3_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 15)
OSEE_DUMMY_ISR(_core3_, 15)
#endif /* OSEE_TC_CORE3_15_ISR_CAT */
#if (defined(OSEE_TC_CORE3_16_ISR_CAT))
#if (OSEE_TC_CORE3_16_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 16)
#elif (OSEE_TC_CORE3_16_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 16)
#else
#error Invalid value for OSEE_TC_CORE3_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 16)
OSEE_DUMMY_ISR(_core3_, 16)
#endif /* OSEE_TC_CORE3_16_ISR_CAT */
#if (defined(OSEE_TC_CORE3_17_ISR_CAT))
#if (OSEE_TC_CORE3_17_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 17)
#elif (OSEE_TC_CORE3_17_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 17)
#else
#error Invalid value for OSEE_TC_CORE3_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 17)
OSEE_DUMMY_ISR(_core3_, 17)
#endif /* OSEE_TC_CORE3_17_ISR_CAT */
#if (defined(OSEE_TC_CORE3_18_ISR_CAT))
#if (OSEE_TC_CORE3_18_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 18)
#elif (OSEE_TC_CORE3_18_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 18)
#else
#error Invalid value for OSEE_TC_CORE3_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 18)
OSEE_DUMMY_ISR(_core3_, 18)
#endif /* OSEE_TC_CORE3_18_ISR_CAT */
#if (defined(OSEE_TC_CORE3_19_ISR_CAT))
#if (OSEE_TC_CORE3_19_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 19)
#elif (OSEE_TC_CORE3_19_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 19)
#else
#error Invalid value for OSEE_TC_CORE3_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 19)
OSEE_DUMMY_ISR(_core3_, 19)
#endif /* OSEE_TC_CORE3_19_ISR_CAT */
#if (defined(OSEE_TC_CORE3_20_ISR_CAT))
#if (OSEE_TC_CORE3_20_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 20)
#elif (OSEE_TC_CORE3_20_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 20)
#else
#error Invalid value for OSEE_TC_CORE3_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 20)
OSEE_DUMMY_ISR(_core3_, 20)
#endif /* OSEE_TC_CORE3_20_ISR_CAT */
#if (defined(OSEE_TC_CORE3_21_ISR_CAT))
#if (OSEE_TC_CORE3_21_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 21)
#elif (OSEE_TC_CORE3_21_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 21)
#else
#error Invalid value for OSEE_TC_CORE3_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 21)
OSEE_DUMMY_ISR(_core3_, 21)
#endif /* OSEE_TC_CORE3_21_ISR_CAT */
#if (defined(OSEE_TC_CORE3_22_ISR_CAT))
#if (OSEE_TC_CORE3_22_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 22)
#elif (OSEE_TC_CORE3_22_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 22)
#else
#error Invalid value for OSEE_TC_CORE3_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 22)
OSEE_DUMMY_ISR(_core3_, 22)
#endif /* OSEE_TC_CORE3_22_ISR_CAT */
#if (defined(OSEE_TC_CORE3_23_ISR_CAT))
#if (OSEE_TC_CORE3_23_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 23)
#elif (OSEE_TC_CORE3_23_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 23)
#else
#error Invalid value for OSEE_TC_CORE3_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 23)
OSEE_DUMMY_ISR(_core3_, 23)
#endif /* OSEE_TC_CORE3_23_ISR_CAT */
#if (defined(OSEE_TC_CORE3_24_ISR_CAT))
#if (OSEE_TC_CORE3_24_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 24)
#elif (OSEE_TC_CORE3_24_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 24)
#else
#error Invalid value for OSEE_TC_CORE3_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 24)
OSEE_DUMMY_ISR(_core3_, 24)
#endif /* OSEE_TC_CORE3_24_ISR_CAT */
#if (defined(OSEE_TC_CORE3_25_ISR_CAT))
#if (OSEE_TC_CORE3_25_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 25)
#elif (OSEE_TC_CORE3_25_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 25)
#else
#error Invalid value for OSEE_TC_CORE3_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 25)
OSEE_DUMMY_ISR(_core3_, 25)
#endif /* OSEE_TC_CORE3_25_ISR_CAT */
#if (defined(OSEE_TC_CORE3_26_ISR_CAT))
#if (OSEE_TC_CORE3_26_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 26)
#elif (OSEE_TC_CORE3_26_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 26)
#else
#error Invalid value for OSEE_TC_CORE3_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 26)
OSEE_DUMMY_ISR(_core3_, 26)
#endif /* OSEE_TC_CORE3_26_ISR_CAT */
#if (defined(OSEE_TC_CORE3_27_ISR_CAT))
#if (OSEE_TC_CORE3_27_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 27)
#elif (OSEE_TC_CORE3_27_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 27)
#else
#error Invalid value for OSEE_TC_CORE3_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 27)
OSEE_DUMMY_ISR(_core3_, 27)
#endif /* OSEE_TC_CORE3_27_ISR_CAT */
#if (defined(OSEE_TC_CORE3_28_ISR_CAT))
#if (OSEE_TC_CORE3_28_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 28)
#elif (OSEE_TC_CORE3_28_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 28)
#else
#error Invalid value for OSEE_TC_CORE3_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 28)
OSEE_DUMMY_ISR(_core3_, 28)
#endif /* OSEE_TC_CORE3_28_ISR_CAT */
#if (defined(OSEE_TC_CORE3_29_ISR_CAT))
#if (OSEE_TC_CORE3_29_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 29)
#elif (OSEE_TC_CORE3_29_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 29)
#else
#error Invalid value for OSEE_TC_CORE3_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 29)
OSEE_DUMMY_ISR(_core3_, 29)
#endif /* OSEE_TC_CORE3_29_ISR_CAT */
#if (defined(OSEE_TC_CORE3_30_ISR_CAT))
#if (OSEE_TC_CORE3_30_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 30)
#elif (OSEE_TC_CORE3_30_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 30)
#else
#error Invalid value for OSEE_TC_CORE3_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 30)
OSEE_DUMMY_ISR(_core3_, 30)
#endif /* OSEE_TC_CORE3_30_ISR_CAT */
#if (defined(OSEE_TC_CORE3_31_ISR_CAT))
#if (OSEE_TC_CORE3_31_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 31)
#elif (OSEE_TC_CORE3_31_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 31)
#else
#error Invalid value for OSEE_TC_CORE3_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 31)
OSEE_DUMMY_ISR(_core3_, 31)
#endif /* OSEE_TC_CORE3_31_ISR_CAT */
#if (defined(OSEE_TC_CORE3_32_ISR_CAT))
#if (OSEE_TC_CORE3_32_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 32)
#elif (OSEE_TC_CORE3_32_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 32)
#else
#error Invalid value for OSEE_TC_CORE3_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 32)
OSEE_DUMMY_ISR(_core3_, 32)
#endif /* OSEE_TC_CORE3_32_ISR_CAT */
#if (defined(OSEE_TC_CORE3_33_ISR_CAT))
#if (OSEE_TC_CORE3_33_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 33)
#elif (OSEE_TC_CORE3_33_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 33)
#else
#error Invalid value for OSEE_TC_CORE3_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 33)
OSEE_DUMMY_ISR(_core3_, 33)
#endif /* OSEE_TC_CORE3_33_ISR_CAT */
#if (defined(OSEE_TC_CORE3_34_ISR_CAT))
#if (OSEE_TC_CORE3_34_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 34)
#elif (OSEE_TC_CORE3_34_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 34)
#else
#error Invalid value for OSEE_TC_CORE3_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 34)
OSEE_DUMMY_ISR(_core3_, 34)
#endif /* OSEE_TC_CORE3_34_ISR_CAT */
#if (defined(OSEE_TC_CORE3_35_ISR_CAT))
#if (OSEE_TC_CORE3_35_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 35)
#elif (OSEE_TC_CORE3_35_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 35)
#else
#error Invalid value for OSEE_TC_CORE3_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 35)
OSEE_DUMMY_ISR(_core3_, 35)
#endif /* OSEE_TC_CORE3_35_ISR_CAT */
#if (defined(OSEE_TC_CORE3_36_ISR_CAT))
#if (OSEE_TC_CORE3_36_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 36)
#elif (OSEE_TC_CORE3_36_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 36)
#else
#error Invalid value for OSEE_TC_CORE3_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 36)
OSEE_DUMMY_ISR(_core3_, 36)
#endif /* OSEE_TC_CORE3_36_ISR_CAT */
#if (defined(OSEE_TC_CORE3_37_ISR_CAT))
#if (OSEE_TC_CORE3_37_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 37)
#elif (OSEE_TC_CORE3_37_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 37)
#else
#error Invalid value for OSEE_TC_CORE3_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 37)
OSEE_DUMMY_ISR(_core3_, 37)
#endif /* OSEE_TC_CORE3_37_ISR_CAT */
#if (defined(OSEE_TC_CORE3_38_ISR_CAT))
#if (OSEE_TC_CORE3_38_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 38)
#elif (OSEE_TC_CORE3_38_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 38)
#else
#error Invalid value for OSEE_TC_CORE3_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 38)
OSEE_DUMMY_ISR(_core3_, 38)
#endif /* OSEE_TC_CORE3_38_ISR_CAT */
#if (defined(OSEE_TC_CORE3_39_ISR_CAT))
#if (OSEE_TC_CORE3_39_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 39)
#elif (OSEE_TC_CORE3_39_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 39)
#else
#error Invalid value for OSEE_TC_CORE3_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 39)
OSEE_DUMMY_ISR(_core3_, 39)
#endif /* OSEE_TC_CORE3_39_ISR_CAT */
#if (defined(OSEE_TC_CORE3_40_ISR_CAT))
#if (OSEE_TC_CORE3_40_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 40)
#elif (OSEE_TC_CORE3_40_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 40)
#else
#error Invalid value for OSEE_TC_CORE3_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 40)
OSEE_DUMMY_ISR(_core3_, 40)
#endif /* OSEE_TC_CORE3_40_ISR_CAT */
#if (defined(OSEE_TC_CORE3_41_ISR_CAT))
#if (OSEE_TC_CORE3_41_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 41)
#elif (OSEE_TC_CORE3_41_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 41)
#else
#error Invalid value for OSEE_TC_CORE3_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 41)
OSEE_DUMMY_ISR(_core3_, 41)
#endif /* OSEE_TC_CORE3_41_ISR_CAT */
#if (defined(OSEE_TC_CORE3_42_ISR_CAT))
#if (OSEE_TC_CORE3_42_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 42)
#elif (OSEE_TC_CORE3_42_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 42)
#else
#error Invalid value for OSEE_TC_CORE3_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 42)
OSEE_DUMMY_ISR(_core3_, 42)
#endif /* OSEE_TC_CORE3_42_ISR_CAT */
#if (defined(OSEE_TC_CORE3_43_ISR_CAT))
#if (OSEE_TC_CORE3_43_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 43)
#elif (OSEE_TC_CORE3_43_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 43)
#else
#error Invalid value for OSEE_TC_CORE3_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 43)
OSEE_DUMMY_ISR(_core3_, 43)
#endif /* OSEE_TC_CORE3_43_ISR_CAT */
#if (defined(OSEE_TC_CORE3_44_ISR_CAT))
#if (OSEE_TC_CORE3_44_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 44)
#elif (OSEE_TC_CORE3_44_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 44)
#else
#error Invalid value for OSEE_TC_CORE3_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 44)
OSEE_DUMMY_ISR(_core3_, 44)
#endif /* OSEE_TC_CORE3_44_ISR_CAT */
#if (defined(OSEE_TC_CORE3_45_ISR_CAT))
#if (OSEE_TC_CORE3_45_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 45)
#elif (OSEE_TC_CORE3_45_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 45)
#else
#error Invalid value for OSEE_TC_CORE3_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 45)
OSEE_DUMMY_ISR(_core3_, 45)
#endif /* OSEE_TC_CORE3_45_ISR_CAT */
#if (defined(OSEE_TC_CORE3_46_ISR_CAT))
#if (OSEE_TC_CORE3_46_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 46)
#elif (OSEE_TC_CORE3_46_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 46)
#else
#error Invalid value for OSEE_TC_CORE3_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 46)
OSEE_DUMMY_ISR(_core3_, 46)
#endif /* OSEE_TC_CORE3_46_ISR_CAT */
#if (defined(OSEE_TC_CORE3_47_ISR_CAT))
#if (OSEE_TC_CORE3_47_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 47)
#elif (OSEE_TC_CORE3_47_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 47)
#else
#error Invalid value for OSEE_TC_CORE3_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 47)
OSEE_DUMMY_ISR(_core3_, 47)
#endif /* OSEE_TC_CORE3_47_ISR_CAT */
#if (defined(OSEE_TC_CORE3_48_ISR_CAT))
#if (OSEE_TC_CORE3_48_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 48)
#elif (OSEE_TC_CORE3_48_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 48)
#else
#error Invalid value for OSEE_TC_CORE3_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 48)
OSEE_DUMMY_ISR(_core3_, 48)
#endif /* OSEE_TC_CORE3_48_ISR_CAT */
#if (defined(OSEE_TC_CORE3_49_ISR_CAT))
#if (OSEE_TC_CORE3_49_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 49)
#elif (OSEE_TC_CORE3_49_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 49)
#else
#error Invalid value for OSEE_TC_CORE3_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 49)
OSEE_DUMMY_ISR(_core3_, 49)
#endif /* OSEE_TC_CORE3_49_ISR_CAT */
#if (defined(OSEE_TC_CORE3_50_ISR_CAT))
#if (OSEE_TC_CORE3_50_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 50)
#elif (OSEE_TC_CORE3_50_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 50)
#else
#error Invalid value for OSEE_TC_CORE3_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 50)
OSEE_DUMMY_ISR(_core3_, 50)
#endif /* OSEE_TC_CORE3_50_ISR_CAT */
#if (defined(OSEE_TC_CORE3_51_ISR_CAT))
#if (OSEE_TC_CORE3_51_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 51)
#elif (OSEE_TC_CORE3_51_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 51)
#else
#error Invalid value for OSEE_TC_CORE3_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 51)
OSEE_DUMMY_ISR(_core3_, 51)
#endif /* OSEE_TC_CORE3_51_ISR_CAT */
#if (defined(OSEE_TC_CORE3_52_ISR_CAT))
#if (OSEE_TC_CORE3_52_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 52)
#elif (OSEE_TC_CORE3_52_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 52)
#else
#error Invalid value for OSEE_TC_CORE3_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 52)
OSEE_DUMMY_ISR(_core3_, 52)
#endif /* OSEE_TC_CORE3_52_ISR_CAT */
#if (defined(OSEE_TC_CORE3_53_ISR_CAT))
#if (OSEE_TC_CORE3_53_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 53)
#elif (OSEE_TC_CORE3_53_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 53)
#else
#error Invalid value for OSEE_TC_CORE3_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 53)
OSEE_DUMMY_ISR(_core3_, 53)
#endif /* OSEE_TC_CORE3_53_ISR_CAT */
#if (defined(OSEE_TC_CORE3_54_ISR_CAT))
#if (OSEE_TC_CORE3_54_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 54)
#elif (OSEE_TC_CORE3_54_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 54)
#else
#error Invalid value for OSEE_TC_CORE3_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 54)
OSEE_DUMMY_ISR(_core3_, 54)
#endif /* OSEE_TC_CORE3_54_ISR_CAT */
#if (defined(OSEE_TC_CORE3_55_ISR_CAT))
#if (OSEE_TC_CORE3_55_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 55)
#elif (OSEE_TC_CORE3_55_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 55)
#else
#error Invalid value for OSEE_TC_CORE3_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 55)
OSEE_DUMMY_ISR(_core3_, 55)
#endif /* OSEE_TC_CORE3_55_ISR_CAT */
#if (defined(OSEE_TC_CORE3_56_ISR_CAT))
#if (OSEE_TC_CORE3_56_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 56)
#elif (OSEE_TC_CORE3_56_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 56)
#else
#error Invalid value for OSEE_TC_CORE3_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 56)
OSEE_DUMMY_ISR(_core3_, 56)
#endif /* OSEE_TC_CORE3_56_ISR_CAT */
#if (defined(OSEE_TC_CORE3_57_ISR_CAT))
#if (OSEE_TC_CORE3_57_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 57)
#elif (OSEE_TC_CORE3_57_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 57)
#else
#error Invalid value for OSEE_TC_CORE3_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 57)
OSEE_DUMMY_ISR(_core3_, 57)
#endif /* OSEE_TC_CORE3_57_ISR_CAT */
#if (defined(OSEE_TC_CORE3_58_ISR_CAT))
#if (OSEE_TC_CORE3_58_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 58)
#elif (OSEE_TC_CORE3_58_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 58)
#else
#error Invalid value for OSEE_TC_CORE3_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 58)
OSEE_DUMMY_ISR(_core3_, 58)
#endif /* OSEE_TC_CORE3_58_ISR_CAT */
#if (defined(OSEE_TC_CORE3_59_ISR_CAT))
#if (OSEE_TC_CORE3_59_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 59)
#elif (OSEE_TC_CORE3_59_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 59)
#else
#error Invalid value for OSEE_TC_CORE3_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 59)
OSEE_DUMMY_ISR(_core3_, 59)
#endif /* OSEE_TC_CORE3_59_ISR_CAT */
#if (defined(OSEE_TC_CORE3_60_ISR_CAT))
#if (OSEE_TC_CORE3_60_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 60)
#elif (OSEE_TC_CORE3_60_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 60)
#else
#error Invalid value for OSEE_TC_CORE3_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 60)
OSEE_DUMMY_ISR(_core3_, 60)
#endif /* OSEE_TC_CORE3_60_ISR_CAT */
#if (defined(OSEE_TC_CORE3_61_ISR_CAT))
#if (OSEE_TC_CORE3_61_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 61)
#elif (OSEE_TC_CORE3_61_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 61)
#else
#error Invalid value for OSEE_TC_CORE3_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 61)
OSEE_DUMMY_ISR(_core3_, 61)
#endif /* OSEE_TC_CORE3_61_ISR_CAT */
#if (defined(OSEE_TC_CORE3_62_ISR_CAT))
#if (OSEE_TC_CORE3_62_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 62)
#elif (OSEE_TC_CORE3_62_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 62)
#else
#error Invalid value for OSEE_TC_CORE3_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 62)
OSEE_DUMMY_ISR(_core3_, 62)
#endif /* OSEE_TC_CORE3_62_ISR_CAT */
#if (defined(OSEE_TC_CORE3_63_ISR_CAT))
#if (OSEE_TC_CORE3_63_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 63)
#elif (OSEE_TC_CORE3_63_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 63)
#else
#error Invalid value for OSEE_TC_CORE3_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 63)
OSEE_DUMMY_ISR(_core3_, 63)
#endif /* OSEE_TC_CORE3_63_ISR_CAT */
#if (defined(OSEE_TC_CORE3_64_ISR_CAT))
#if (OSEE_TC_CORE3_64_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 64)
#elif (OSEE_TC_CORE3_64_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 64)
#else
#error Invalid value for OSEE_TC_CORE3_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 64)
OSEE_DUMMY_ISR(_core3_, 64)
#endif /* OSEE_TC_CORE3_64_ISR_CAT */
#if (defined(OSEE_TC_CORE3_65_ISR_CAT))
#if (OSEE_TC_CORE3_65_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 65)
#elif (OSEE_TC_CORE3_65_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 65)
#else
#error Invalid value for OSEE_TC_CORE3_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 65)
OSEE_DUMMY_ISR(_core3_, 65)
#endif /* OSEE_TC_CORE3_65_ISR_CAT */
#if (defined(OSEE_TC_CORE3_66_ISR_CAT))
#if (OSEE_TC_CORE3_66_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 66)
#elif (OSEE_TC_CORE3_66_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 66)
#else
#error Invalid value for OSEE_TC_CORE3_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 66)
OSEE_DUMMY_ISR(_core3_, 66)
#endif /* OSEE_TC_CORE3_66_ISR_CAT */
#if (defined(OSEE_TC_CORE3_67_ISR_CAT))
#if (OSEE_TC_CORE3_67_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 67)
#elif (OSEE_TC_CORE3_67_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 67)
#else
#error Invalid value for OSEE_TC_CORE3_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 67)
OSEE_DUMMY_ISR(_core3_, 67)
#endif /* OSEE_TC_CORE3_67_ISR_CAT */
#if (defined(OSEE_TC_CORE3_68_ISR_CAT))
#if (OSEE_TC_CORE3_68_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 68)
#elif (OSEE_TC_CORE3_68_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 68)
#else
#error Invalid value for OSEE_TC_CORE3_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 68)
OSEE_DUMMY_ISR(_core3_, 68)
#endif /* OSEE_TC_CORE3_68_ISR_CAT */
#if (defined(OSEE_TC_CORE3_69_ISR_CAT))
#if (OSEE_TC_CORE3_69_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 69)
#elif (OSEE_TC_CORE3_69_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 69)
#else
#error Invalid value for OSEE_TC_CORE3_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 69)
OSEE_DUMMY_ISR(_core3_, 69)
#endif /* OSEE_TC_CORE3_69_ISR_CAT */
#if (defined(OSEE_TC_CORE3_70_ISR_CAT))
#if (OSEE_TC_CORE3_70_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 70)
#elif (OSEE_TC_CORE3_70_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 70)
#else
#error Invalid value for OSEE_TC_CORE3_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 70)
OSEE_DUMMY_ISR(_core3_, 70)
#endif /* OSEE_TC_CORE3_70_ISR_CAT */
#if (defined(OSEE_TC_CORE3_71_ISR_CAT))
#if (OSEE_TC_CORE3_71_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 71)
#elif (OSEE_TC_CORE3_71_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 71)
#else
#error Invalid value for OSEE_TC_CORE3_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 71)
OSEE_DUMMY_ISR(_core3_, 71)
#endif /* OSEE_TC_CORE3_71_ISR_CAT */
#if (defined(OSEE_TC_CORE3_72_ISR_CAT))
#if (OSEE_TC_CORE3_72_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 72)
#elif (OSEE_TC_CORE3_72_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 72)
#else
#error Invalid value for OSEE_TC_CORE3_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 72)
OSEE_DUMMY_ISR(_core3_, 72)
#endif /* OSEE_TC_CORE3_72_ISR_CAT */
#if (defined(OSEE_TC_CORE3_73_ISR_CAT))
#if (OSEE_TC_CORE3_73_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 73)
#elif (OSEE_TC_CORE3_73_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 73)
#else
#error Invalid value for OSEE_TC_CORE3_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 73)
OSEE_DUMMY_ISR(_core3_, 73)
#endif /* OSEE_TC_CORE3_73_ISR_CAT */
#if (defined(OSEE_TC_CORE3_74_ISR_CAT))
#if (OSEE_TC_CORE3_74_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 74)
#elif (OSEE_TC_CORE3_74_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 74)
#else
#error Invalid value for OSEE_TC_CORE3_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 74)
OSEE_DUMMY_ISR(_core3_, 74)
#endif /* OSEE_TC_CORE3_74_ISR_CAT */
#if (defined(OSEE_TC_CORE3_75_ISR_CAT))
#if (OSEE_TC_CORE3_75_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 75)
#elif (OSEE_TC_CORE3_75_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 75)
#else
#error Invalid value for OSEE_TC_CORE3_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 75)
OSEE_DUMMY_ISR(_core3_, 75)
#endif /* OSEE_TC_CORE3_75_ISR_CAT */
#if (defined(OSEE_TC_CORE3_76_ISR_CAT))
#if (OSEE_TC_CORE3_76_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 76)
#elif (OSEE_TC_CORE3_76_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 76)
#else
#error Invalid value for OSEE_TC_CORE3_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 76)
OSEE_DUMMY_ISR(_core3_, 76)
#endif /* OSEE_TC_CORE3_76_ISR_CAT */
#if (defined(OSEE_TC_CORE3_77_ISR_CAT))
#if (OSEE_TC_CORE3_77_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 77)
#elif (OSEE_TC_CORE3_77_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 77)
#else
#error Invalid value for OSEE_TC_CORE3_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 77)
OSEE_DUMMY_ISR(_core3_, 77)
#endif /* OSEE_TC_CORE3_77_ISR_CAT */
#if (defined(OSEE_TC_CORE3_78_ISR_CAT))
#if (OSEE_TC_CORE3_78_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 78)
#elif (OSEE_TC_CORE3_78_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 78)
#else
#error Invalid value for OSEE_TC_CORE3_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 78)
OSEE_DUMMY_ISR(_core3_, 78)
#endif /* OSEE_TC_CORE3_78_ISR_CAT */
#if (defined(OSEE_TC_CORE3_79_ISR_CAT))
#if (OSEE_TC_CORE3_79_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 79)
#elif (OSEE_TC_CORE3_79_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 79)
#else
#error Invalid value for OSEE_TC_CORE3_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 79)
OSEE_DUMMY_ISR(_core3_, 79)
#endif /* OSEE_TC_CORE3_79_ISR_CAT */
#if (defined(OSEE_TC_CORE3_80_ISR_CAT))
#if (OSEE_TC_CORE3_80_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 80)
#elif (OSEE_TC_CORE3_80_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 80)
#else
#error Invalid value for OSEE_TC_CORE3_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 80)
OSEE_DUMMY_ISR(_core3_, 80)
#endif /* OSEE_TC_CORE3_80_ISR_CAT */
#if (defined(OSEE_TC_CORE3_81_ISR_CAT))
#if (OSEE_TC_CORE3_81_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 81)
#elif (OSEE_TC_CORE3_81_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 81)
#else
#error Invalid value for OSEE_TC_CORE3_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 81)
OSEE_DUMMY_ISR(_core3_, 81)
#endif /* OSEE_TC_CORE3_81_ISR_CAT */
#if (defined(OSEE_TC_CORE3_82_ISR_CAT))
#if (OSEE_TC_CORE3_82_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 82)
#elif (OSEE_TC_CORE3_82_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 82)
#else
#error Invalid value for OSEE_TC_CORE3_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 82)
OSEE_DUMMY_ISR(_core3_, 82)
#endif /* OSEE_TC_CORE3_82_ISR_CAT */
#if (defined(OSEE_TC_CORE3_83_ISR_CAT))
#if (OSEE_TC_CORE3_83_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 83)
#elif (OSEE_TC_CORE3_83_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 83)
#else
#error Invalid value for OSEE_TC_CORE3_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 83)
OSEE_DUMMY_ISR(_core3_, 83)
#endif /* OSEE_TC_CORE3_83_ISR_CAT */
#if (defined(OSEE_TC_CORE3_84_ISR_CAT))
#if (OSEE_TC_CORE3_84_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 84)
#elif (OSEE_TC_CORE3_84_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 84)
#else
#error Invalid value for OSEE_TC_CORE3_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 84)
OSEE_DUMMY_ISR(_core3_, 84)
#endif /* OSEE_TC_CORE3_84_ISR_CAT */
#if (defined(OSEE_TC_CORE3_85_ISR_CAT))
#if (OSEE_TC_CORE3_85_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 85)
#elif (OSEE_TC_CORE3_85_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 85)
#else
#error Invalid value for OSEE_TC_CORE3_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 85)
OSEE_DUMMY_ISR(_core3_, 85)
#endif /* OSEE_TC_CORE3_85_ISR_CAT */
#if (defined(OSEE_TC_CORE3_86_ISR_CAT))
#if (OSEE_TC_CORE3_86_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 86)
#elif (OSEE_TC_CORE3_86_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 86)
#else
#error Invalid value for OSEE_TC_CORE3_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 86)
OSEE_DUMMY_ISR(_core3_, 86)
#endif /* OSEE_TC_CORE3_86_ISR_CAT */
#if (defined(OSEE_TC_CORE3_87_ISR_CAT))
#if (OSEE_TC_CORE3_87_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 87)
#elif (OSEE_TC_CORE3_87_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 87)
#else
#error Invalid value for OSEE_TC_CORE3_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 87)
OSEE_DUMMY_ISR(_core3_, 87)
#endif /* OSEE_TC_CORE3_87_ISR_CAT */
#if (defined(OSEE_TC_CORE3_88_ISR_CAT))
#if (OSEE_TC_CORE3_88_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 88)
#elif (OSEE_TC_CORE3_88_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 88)
#else
#error Invalid value for OSEE_TC_CORE3_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 88)
OSEE_DUMMY_ISR(_core3_, 88)
#endif /* OSEE_TC_CORE3_88_ISR_CAT */
#if (defined(OSEE_TC_CORE3_89_ISR_CAT))
#if (OSEE_TC_CORE3_89_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 89)
#elif (OSEE_TC_CORE3_89_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 89)
#else
#error Invalid value for OSEE_TC_CORE3_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 89)
OSEE_DUMMY_ISR(_core3_, 89)
#endif /* OSEE_TC_CORE3_89_ISR_CAT */
#if (defined(OSEE_TC_CORE3_90_ISR_CAT))
#if (OSEE_TC_CORE3_90_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 90)
#elif (OSEE_TC_CORE3_90_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 90)
#else
#error Invalid value for OSEE_TC_CORE3_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 90)
OSEE_DUMMY_ISR(_core3_, 90)
#endif /* OSEE_TC_CORE3_90_ISR_CAT */
#if (defined(OSEE_TC_CORE3_91_ISR_CAT))
#if (OSEE_TC_CORE3_91_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 91)
#elif (OSEE_TC_CORE3_91_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 91)
#else
#error Invalid value for OSEE_TC_CORE3_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 91)
OSEE_DUMMY_ISR(_core3_, 91)
#endif /* OSEE_TC_CORE3_91_ISR_CAT */
#if (defined(OSEE_TC_CORE3_92_ISR_CAT))
#if (OSEE_TC_CORE3_92_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 92)
#elif (OSEE_TC_CORE3_92_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 92)
#else
#error Invalid value for OSEE_TC_CORE3_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 92)
OSEE_DUMMY_ISR(_core3_, 92)
#endif /* OSEE_TC_CORE3_92_ISR_CAT */
#if (defined(OSEE_TC_CORE3_93_ISR_CAT))
#if (OSEE_TC_CORE3_93_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 93)
#elif (OSEE_TC_CORE3_93_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 93)
#else
#error Invalid value for OSEE_TC_CORE3_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 93)
OSEE_DUMMY_ISR(_core3_, 93)
#endif /* OSEE_TC_CORE3_93_ISR_CAT */
#if (defined(OSEE_TC_CORE3_94_ISR_CAT))
#if (OSEE_TC_CORE3_94_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 94)
#elif (OSEE_TC_CORE3_94_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 94)
#else
#error Invalid value for OSEE_TC_CORE3_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 94)
OSEE_DUMMY_ISR(_core3_, 94)
#endif /* OSEE_TC_CORE3_94_ISR_CAT */
#if (defined(OSEE_TC_CORE3_95_ISR_CAT))
#if (OSEE_TC_CORE3_95_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 95)
#elif (OSEE_TC_CORE3_95_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 95)
#else
#error Invalid value for OSEE_TC_CORE3_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 95)
OSEE_DUMMY_ISR(_core3_, 95)
#endif /* OSEE_TC_CORE3_95_ISR_CAT */
#if (defined(OSEE_TC_CORE3_96_ISR_CAT))
#if (OSEE_TC_CORE3_96_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 96)
#elif (OSEE_TC_CORE3_96_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 96)
#else
#error Invalid value for OSEE_TC_CORE3_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 96)
OSEE_DUMMY_ISR(_core3_, 96)
#endif /* OSEE_TC_CORE3_96_ISR_CAT */
#if (defined(OSEE_TC_CORE3_97_ISR_CAT))
#if (OSEE_TC_CORE3_97_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 97)
#elif (OSEE_TC_CORE3_97_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 97)
#else
#error Invalid value for OSEE_TC_CORE3_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 97)
OSEE_DUMMY_ISR(_core3_, 97)
#endif /* OSEE_TC_CORE3_97_ISR_CAT */
#if (defined(OSEE_TC_CORE3_98_ISR_CAT))
#if (OSEE_TC_CORE3_98_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 98)
#elif (OSEE_TC_CORE3_98_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 98)
#else
#error Invalid value for OSEE_TC_CORE3_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 98)
OSEE_DUMMY_ISR(_core3_, 98)
#endif /* OSEE_TC_CORE3_98_ISR_CAT */
#if (defined(OSEE_TC_CORE3_99_ISR_CAT))
#if (OSEE_TC_CORE3_99_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 99)
#elif (OSEE_TC_CORE3_99_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 99)
#else
#error Invalid value for OSEE_TC_CORE3_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 99)
OSEE_DUMMY_ISR(_core3_, 99)
#endif /* OSEE_TC_CORE3_99_ISR_CAT */
#if (defined(OSEE_TC_CORE3_100_ISR_CAT))
#if (OSEE_TC_CORE3_100_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 100)
#elif (OSEE_TC_CORE3_100_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 100)
#else
#error Invalid value for OSEE_TC_CORE3_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 100)
OSEE_DUMMY_ISR(_core3_, 100)
#endif /* OSEE_TC_CORE3_100_ISR_CAT */
#if (defined(OSEE_TC_CORE3_101_ISR_CAT))
#if (OSEE_TC_CORE3_101_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 101)
#elif (OSEE_TC_CORE3_101_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 101)
#else
#error Invalid value for OSEE_TC_CORE3_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 101)
OSEE_DUMMY_ISR(_core3_, 101)
#endif /* OSEE_TC_CORE3_101_ISR_CAT */
#if (defined(OSEE_TC_CORE3_102_ISR_CAT))
#if (OSEE_TC_CORE3_102_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 102)
#elif (OSEE_TC_CORE3_102_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 102)
#else
#error Invalid value for OSEE_TC_CORE3_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 102)
OSEE_DUMMY_ISR(_core3_, 102)
#endif /* OSEE_TC_CORE3_102_ISR_CAT */
#if (defined(OSEE_TC_CORE3_103_ISR_CAT))
#if (OSEE_TC_CORE3_103_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 103)
#elif (OSEE_TC_CORE3_103_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 103)
#else
#error Invalid value for OSEE_TC_CORE3_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 103)
OSEE_DUMMY_ISR(_core3_, 103)
#endif /* OSEE_TC_CORE3_103_ISR_CAT */
#if (defined(OSEE_TC_CORE3_104_ISR_CAT))
#if (OSEE_TC_CORE3_104_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 104)
#elif (OSEE_TC_CORE3_104_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 104)
#else
#error Invalid value for OSEE_TC_CORE3_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 104)
OSEE_DUMMY_ISR(_core3_, 104)
#endif /* OSEE_TC_CORE3_104_ISR_CAT */
#if (defined(OSEE_TC_CORE3_105_ISR_CAT))
#if (OSEE_TC_CORE3_105_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 105)
#elif (OSEE_TC_CORE3_105_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 105)
#else
#error Invalid value for OSEE_TC_CORE3_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 105)
OSEE_DUMMY_ISR(_core3_, 105)
#endif /* OSEE_TC_CORE3_105_ISR_CAT */
#if (defined(OSEE_TC_CORE3_106_ISR_CAT))
#if (OSEE_TC_CORE3_106_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 106)
#elif (OSEE_TC_CORE3_106_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 106)
#else
#error Invalid value for OSEE_TC_CORE3_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 106)
OSEE_DUMMY_ISR(_core3_, 106)
#endif /* OSEE_TC_CORE3_106_ISR_CAT */
#if (defined(OSEE_TC_CORE3_107_ISR_CAT))
#if (OSEE_TC_CORE3_107_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 107)
#elif (OSEE_TC_CORE3_107_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 107)
#else
#error Invalid value for OSEE_TC_CORE3_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 107)
OSEE_DUMMY_ISR(_core3_, 107)
#endif /* OSEE_TC_CORE3_107_ISR_CAT */
#if (defined(OSEE_TC_CORE3_108_ISR_CAT))
#if (OSEE_TC_CORE3_108_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 108)
#elif (OSEE_TC_CORE3_108_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 108)
#else
#error Invalid value for OSEE_TC_CORE3_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 108)
OSEE_DUMMY_ISR(_core3_, 108)
#endif /* OSEE_TC_CORE3_108_ISR_CAT */
#if (defined(OSEE_TC_CORE3_109_ISR_CAT))
#if (OSEE_TC_CORE3_109_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 109)
#elif (OSEE_TC_CORE3_109_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 109)
#else
#error Invalid value for OSEE_TC_CORE3_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 109)
OSEE_DUMMY_ISR(_core3_, 109)
#endif /* OSEE_TC_CORE3_109_ISR_CAT */
#if (defined(OSEE_TC_CORE3_110_ISR_CAT))
#if (OSEE_TC_CORE3_110_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 110)
#elif (OSEE_TC_CORE3_110_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 110)
#else
#error Invalid value for OSEE_TC_CORE3_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 110)
OSEE_DUMMY_ISR(_core3_, 110)
#endif /* OSEE_TC_CORE3_110_ISR_CAT */
#if (defined(OSEE_TC_CORE3_111_ISR_CAT))
#if (OSEE_TC_CORE3_111_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 111)
#elif (OSEE_TC_CORE3_111_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 111)
#else
#error Invalid value for OSEE_TC_CORE3_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 111)
OSEE_DUMMY_ISR(_core3_, 111)
#endif /* OSEE_TC_CORE3_111_ISR_CAT */
#if (defined(OSEE_TC_CORE3_112_ISR_CAT))
#if (OSEE_TC_CORE3_112_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 112)
#elif (OSEE_TC_CORE3_112_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 112)
#else
#error Invalid value for OSEE_TC_CORE3_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 112)
OSEE_DUMMY_ISR(_core3_, 112)
#endif /* OSEE_TC_CORE3_112_ISR_CAT */
#if (defined(OSEE_TC_CORE3_113_ISR_CAT))
#if (OSEE_TC_CORE3_113_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 113)
#elif (OSEE_TC_CORE3_113_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 113)
#else
#error Invalid value for OSEE_TC_CORE3_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 113)
OSEE_DUMMY_ISR(_core3_, 113)
#endif /* OSEE_TC_CORE3_113_ISR_CAT */
#if (defined(OSEE_TC_CORE3_114_ISR_CAT))
#if (OSEE_TC_CORE3_114_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 114)
#elif (OSEE_TC_CORE3_114_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 114)
#else
#error Invalid value for OSEE_TC_CORE3_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 114)
OSEE_DUMMY_ISR(_core3_, 114)
#endif /* OSEE_TC_CORE3_114_ISR_CAT */
#if (defined(OSEE_TC_CORE3_115_ISR_CAT))
#if (OSEE_TC_CORE3_115_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 115)
#elif (OSEE_TC_CORE3_115_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 115)
#else
#error Invalid value for OSEE_TC_CORE3_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 115)
OSEE_DUMMY_ISR(_core3_, 115)
#endif /* OSEE_TC_CORE3_115_ISR_CAT */
#if (defined(OSEE_TC_CORE3_116_ISR_CAT))
#if (OSEE_TC_CORE3_116_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 116)
#elif (OSEE_TC_CORE3_116_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 116)
#else
#error Invalid value for OSEE_TC_CORE3_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 116)
OSEE_DUMMY_ISR(_core3_, 116)
#endif /* OSEE_TC_CORE3_116_ISR_CAT */
#if (defined(OSEE_TC_CORE3_117_ISR_CAT))
#if (OSEE_TC_CORE3_117_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 117)
#elif (OSEE_TC_CORE3_117_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 117)
#else
#error Invalid value for OSEE_TC_CORE3_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 117)
OSEE_DUMMY_ISR(_core3_, 117)
#endif /* OSEE_TC_CORE3_117_ISR_CAT */
#if (defined(OSEE_TC_CORE3_118_ISR_CAT))
#if (OSEE_TC_CORE3_118_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 118)
#elif (OSEE_TC_CORE3_118_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 118)
#else
#error Invalid value for OSEE_TC_CORE3_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 118)
OSEE_DUMMY_ISR(_core3_, 118)
#endif /* OSEE_TC_CORE3_118_ISR_CAT */
#if (defined(OSEE_TC_CORE3_119_ISR_CAT))
#if (OSEE_TC_CORE3_119_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 119)
#elif (OSEE_TC_CORE3_119_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 119)
#else
#error Invalid value for OSEE_TC_CORE3_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 119)
OSEE_DUMMY_ISR(_core3_, 119)
#endif /* OSEE_TC_CORE3_119_ISR_CAT */
#if (defined(OSEE_TC_CORE3_120_ISR_CAT))
#if (OSEE_TC_CORE3_120_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 120)
#elif (OSEE_TC_CORE3_120_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 120)
#else
#error Invalid value for OSEE_TC_CORE3_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 120)
OSEE_DUMMY_ISR(_core3_, 120)
#endif /* OSEE_TC_CORE3_120_ISR_CAT */
#if (defined(OSEE_TC_CORE3_121_ISR_CAT))
#if (OSEE_TC_CORE3_121_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 121)
#elif (OSEE_TC_CORE3_121_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 121)
#else
#error Invalid value for OSEE_TC_CORE3_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 121)
OSEE_DUMMY_ISR(_core3_, 121)
#endif /* OSEE_TC_CORE3_121_ISR_CAT */
#if (defined(OSEE_TC_CORE3_122_ISR_CAT))
#if (OSEE_TC_CORE3_122_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 122)
#elif (OSEE_TC_CORE3_122_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 122)
#else
#error Invalid value for OSEE_TC_CORE3_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 122)
OSEE_DUMMY_ISR(_core3_, 122)
#endif /* OSEE_TC_CORE3_122_ISR_CAT */
#if (defined(OSEE_TC_CORE3_123_ISR_CAT))
#if (OSEE_TC_CORE3_123_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 123)
#elif (OSEE_TC_CORE3_123_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 123)
#else
#error Invalid value for OSEE_TC_CORE3_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 123)
OSEE_DUMMY_ISR(_core3_, 123)
#endif /* OSEE_TC_CORE3_123_ISR_CAT */
#if (defined(OSEE_TC_CORE3_124_ISR_CAT))
#if (OSEE_TC_CORE3_124_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 124)
#elif (OSEE_TC_CORE3_124_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 124)
#else
#error Invalid value for OSEE_TC_CORE3_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 124)
OSEE_DUMMY_ISR(_core3_, 124)
#endif /* OSEE_TC_CORE3_124_ISR_CAT */
#if (defined(OSEE_TC_CORE3_125_ISR_CAT))
#if (OSEE_TC_CORE3_125_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 125)
#elif (OSEE_TC_CORE3_125_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 125)
#else
#error Invalid value for OSEE_TC_CORE3_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 125)
OSEE_DUMMY_ISR(_core3_, 125)
#endif /* OSEE_TC_CORE3_125_ISR_CAT */
#if (defined(OSEE_TC_CORE3_126_ISR_CAT))
#if (OSEE_TC_CORE3_126_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 126)
#elif (OSEE_TC_CORE3_126_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 126)
#else
#error Invalid value for OSEE_TC_CORE3_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 126)
OSEE_DUMMY_ISR(_core3_, 126)
#endif /* OSEE_TC_CORE3_126_ISR_CAT */
#if (defined(OSEE_TC_CORE3_127_ISR_CAT))
#if (OSEE_TC_CORE3_127_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 127)
#elif (OSEE_TC_CORE3_127_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 127)
#else
#error Invalid value for OSEE_TC_CORE3_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 127)
OSEE_DUMMY_ISR(_core3_, 127)
#endif /* OSEE_TC_CORE3_127_ISR_CAT */
#if (defined(OSEE_TC_CORE3_128_ISR_CAT))
#if (OSEE_TC_CORE3_128_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 128)
#elif (OSEE_TC_CORE3_128_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 128)
#else
#error Invalid value for OSEE_TC_CORE3_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 128)
OSEE_DUMMY_ISR(_core3_, 128)
#endif /* OSEE_TC_CORE3_128_ISR_CAT */
#if (defined(OSEE_TC_CORE3_129_ISR_CAT))
#if (OSEE_TC_CORE3_129_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 129)
#elif (OSEE_TC_CORE3_129_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 129)
#else
#error Invalid value for OSEE_TC_CORE3_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 129)
OSEE_DUMMY_ISR(_core3_, 129)
#endif /* OSEE_TC_CORE3_129_ISR_CAT */
#if (defined(OSEE_TC_CORE3_130_ISR_CAT))
#if (OSEE_TC_CORE3_130_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 130)
#elif (OSEE_TC_CORE3_130_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 130)
#else
#error Invalid value for OSEE_TC_CORE3_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 130)
OSEE_DUMMY_ISR(_core3_, 130)
#endif /* OSEE_TC_CORE3_130_ISR_CAT */
#if (defined(OSEE_TC_CORE3_131_ISR_CAT))
#if (OSEE_TC_CORE3_131_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 131)
#elif (OSEE_TC_CORE3_131_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 131)
#else
#error Invalid value for OSEE_TC_CORE3_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 131)
OSEE_DUMMY_ISR(_core3_, 131)
#endif /* OSEE_TC_CORE3_131_ISR_CAT */
#if (defined(OSEE_TC_CORE3_132_ISR_CAT))
#if (OSEE_TC_CORE3_132_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 132)
#elif (OSEE_TC_CORE3_132_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 132)
#else
#error Invalid value for OSEE_TC_CORE3_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 132)
OSEE_DUMMY_ISR(_core3_, 132)
#endif /* OSEE_TC_CORE3_132_ISR_CAT */
#if (defined(OSEE_TC_CORE3_133_ISR_CAT))
#if (OSEE_TC_CORE3_133_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 133)
#elif (OSEE_TC_CORE3_133_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 133)
#else
#error Invalid value for OSEE_TC_CORE3_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 133)
OSEE_DUMMY_ISR(_core3_, 133)
#endif /* OSEE_TC_CORE3_133_ISR_CAT */
#if (defined(OSEE_TC_CORE3_134_ISR_CAT))
#if (OSEE_TC_CORE3_134_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 134)
#elif (OSEE_TC_CORE3_134_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 134)
#else
#error Invalid value for OSEE_TC_CORE3_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 134)
OSEE_DUMMY_ISR(_core3_, 134)
#endif /* OSEE_TC_CORE3_134_ISR_CAT */
#if (defined(OSEE_TC_CORE3_135_ISR_CAT))
#if (OSEE_TC_CORE3_135_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 135)
#elif (OSEE_TC_CORE3_135_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 135)
#else
#error Invalid value for OSEE_TC_CORE3_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 135)
OSEE_DUMMY_ISR(_core3_, 135)
#endif /* OSEE_TC_CORE3_135_ISR_CAT */
#if (defined(OSEE_TC_CORE3_136_ISR_CAT))
#if (OSEE_TC_CORE3_136_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 136)
#elif (OSEE_TC_CORE3_136_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 136)
#else
#error Invalid value for OSEE_TC_CORE3_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 136)
OSEE_DUMMY_ISR(_core3_, 136)
#endif /* OSEE_TC_CORE3_136_ISR_CAT */
#if (defined(OSEE_TC_CORE3_137_ISR_CAT))
#if (OSEE_TC_CORE3_137_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 137)
#elif (OSEE_TC_CORE3_137_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 137)
#else
#error Invalid value for OSEE_TC_CORE3_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 137)
OSEE_DUMMY_ISR(_core3_, 137)
#endif /* OSEE_TC_CORE3_137_ISR_CAT */
#if (defined(OSEE_TC_CORE3_138_ISR_CAT))
#if (OSEE_TC_CORE3_138_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 138)
#elif (OSEE_TC_CORE3_138_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 138)
#else
#error Invalid value for OSEE_TC_CORE3_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 138)
OSEE_DUMMY_ISR(_core3_, 138)
#endif /* OSEE_TC_CORE3_138_ISR_CAT */
#if (defined(OSEE_TC_CORE3_139_ISR_CAT))
#if (OSEE_TC_CORE3_139_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 139)
#elif (OSEE_TC_CORE3_139_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 139)
#else
#error Invalid value for OSEE_TC_CORE3_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 139)
OSEE_DUMMY_ISR(_core3_, 139)
#endif /* OSEE_TC_CORE3_139_ISR_CAT */
#if (defined(OSEE_TC_CORE3_140_ISR_CAT))
#if (OSEE_TC_CORE3_140_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 140)
#elif (OSEE_TC_CORE3_140_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 140)
#else
#error Invalid value for OSEE_TC_CORE3_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 140)
OSEE_DUMMY_ISR(_core3_, 140)
#endif /* OSEE_TC_CORE3_140_ISR_CAT */
#if (defined(OSEE_TC_CORE3_141_ISR_CAT))
#if (OSEE_TC_CORE3_141_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 141)
#elif (OSEE_TC_CORE3_141_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 141)
#else
#error Invalid value for OSEE_TC_CORE3_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 141)
OSEE_DUMMY_ISR(_core3_, 141)
#endif /* OSEE_TC_CORE3_141_ISR_CAT */
#if (defined(OSEE_TC_CORE3_142_ISR_CAT))
#if (OSEE_TC_CORE3_142_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 142)
#elif (OSEE_TC_CORE3_142_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 142)
#else
#error Invalid value for OSEE_TC_CORE3_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 142)
OSEE_DUMMY_ISR(_core3_, 142)
#endif /* OSEE_TC_CORE3_142_ISR_CAT */
#if (defined(OSEE_TC_CORE3_143_ISR_CAT))
#if (OSEE_TC_CORE3_143_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 143)
#elif (OSEE_TC_CORE3_143_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 143)
#else
#error Invalid value for OSEE_TC_CORE3_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 143)
OSEE_DUMMY_ISR(_core3_, 143)
#endif /* OSEE_TC_CORE3_143_ISR_CAT */
#if (defined(OSEE_TC_CORE3_144_ISR_CAT))
#if (OSEE_TC_CORE3_144_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 144)
#elif (OSEE_TC_CORE3_144_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 144)
#else
#error Invalid value for OSEE_TC_CORE3_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 144)
OSEE_DUMMY_ISR(_core3_, 144)
#endif /* OSEE_TC_CORE3_144_ISR_CAT */
#if (defined(OSEE_TC_CORE3_145_ISR_CAT))
#if (OSEE_TC_CORE3_145_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 145)
#elif (OSEE_TC_CORE3_145_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 145)
#else
#error Invalid value for OSEE_TC_CORE3_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 145)
OSEE_DUMMY_ISR(_core3_, 145)
#endif /* OSEE_TC_CORE3_145_ISR_CAT */
#if (defined(OSEE_TC_CORE3_146_ISR_CAT))
#if (OSEE_TC_CORE3_146_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 146)
#elif (OSEE_TC_CORE3_146_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 146)
#else
#error Invalid value for OSEE_TC_CORE3_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 146)
OSEE_DUMMY_ISR(_core3_, 146)
#endif /* OSEE_TC_CORE3_146_ISR_CAT */
#if (defined(OSEE_TC_CORE3_147_ISR_CAT))
#if (OSEE_TC_CORE3_147_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 147)
#elif (OSEE_TC_CORE3_147_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 147)
#else
#error Invalid value for OSEE_TC_CORE3_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 147)
OSEE_DUMMY_ISR(_core3_, 147)
#endif /* OSEE_TC_CORE3_147_ISR_CAT */
#if (defined(OSEE_TC_CORE3_148_ISR_CAT))
#if (OSEE_TC_CORE3_148_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 148)
#elif (OSEE_TC_CORE3_148_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 148)
#else
#error Invalid value for OSEE_TC_CORE3_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 148)
OSEE_DUMMY_ISR(_core3_, 148)
#endif /* OSEE_TC_CORE3_148_ISR_CAT */
#if (defined(OSEE_TC_CORE3_149_ISR_CAT))
#if (OSEE_TC_CORE3_149_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 149)
#elif (OSEE_TC_CORE3_149_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 149)
#else
#error Invalid value for OSEE_TC_CORE3_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 149)
OSEE_DUMMY_ISR(_core3_, 149)
#endif /* OSEE_TC_CORE3_149_ISR_CAT */
#if (defined(OSEE_TC_CORE3_150_ISR_CAT))
#if (OSEE_TC_CORE3_150_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 150)
#elif (OSEE_TC_CORE3_150_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 150)
#else
#error Invalid value for OSEE_TC_CORE3_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 150)
OSEE_DUMMY_ISR(_core3_, 150)
#endif /* OSEE_TC_CORE3_150_ISR_CAT */
#if (defined(OSEE_TC_CORE3_151_ISR_CAT))
#if (OSEE_TC_CORE3_151_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 151)
#elif (OSEE_TC_CORE3_151_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 151)
#else
#error Invalid value for OSEE_TC_CORE3_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 151)
OSEE_DUMMY_ISR(_core3_, 151)
#endif /* OSEE_TC_CORE3_151_ISR_CAT */
#if (defined(OSEE_TC_CORE3_152_ISR_CAT))
#if (OSEE_TC_CORE3_152_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 152)
#elif (OSEE_TC_CORE3_152_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 152)
#else
#error Invalid value for OSEE_TC_CORE3_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 152)
OSEE_DUMMY_ISR(_core3_, 152)
#endif /* OSEE_TC_CORE3_152_ISR_CAT */
#if (defined(OSEE_TC_CORE3_153_ISR_CAT))
#if (OSEE_TC_CORE3_153_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 153)
#elif (OSEE_TC_CORE3_153_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 153)
#else
#error Invalid value for OSEE_TC_CORE3_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 153)
OSEE_DUMMY_ISR(_core3_, 153)
#endif /* OSEE_TC_CORE3_153_ISR_CAT */
#if (defined(OSEE_TC_CORE3_154_ISR_CAT))
#if (OSEE_TC_CORE3_154_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 154)
#elif (OSEE_TC_CORE3_154_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 154)
#else
#error Invalid value for OSEE_TC_CORE3_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 154)
OSEE_DUMMY_ISR(_core3_, 154)
#endif /* OSEE_TC_CORE3_154_ISR_CAT */
#if (defined(OSEE_TC_CORE3_155_ISR_CAT))
#if (OSEE_TC_CORE3_155_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 155)
#elif (OSEE_TC_CORE3_155_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 155)
#else
#error Invalid value for OSEE_TC_CORE3_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 155)
OSEE_DUMMY_ISR(_core3_, 155)
#endif /* OSEE_TC_CORE3_155_ISR_CAT */
#if (defined(OSEE_TC_CORE3_156_ISR_CAT))
#if (OSEE_TC_CORE3_156_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 156)
#elif (OSEE_TC_CORE3_156_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 156)
#else
#error Invalid value for OSEE_TC_CORE3_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 156)
OSEE_DUMMY_ISR(_core3_, 156)
#endif /* OSEE_TC_CORE3_156_ISR_CAT */
#if (defined(OSEE_TC_CORE3_157_ISR_CAT))
#if (OSEE_TC_CORE3_157_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 157)
#elif (OSEE_TC_CORE3_157_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 157)
#else
#error Invalid value for OSEE_TC_CORE3_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 157)
OSEE_DUMMY_ISR(_core3_, 157)
#endif /* OSEE_TC_CORE3_157_ISR_CAT */
#if (defined(OSEE_TC_CORE3_158_ISR_CAT))
#if (OSEE_TC_CORE3_158_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 158)
#elif (OSEE_TC_CORE3_158_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 158)
#else
#error Invalid value for OSEE_TC_CORE3_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 158)
OSEE_DUMMY_ISR(_core3_, 158)
#endif /* OSEE_TC_CORE3_158_ISR_CAT */
#if (defined(OSEE_TC_CORE3_159_ISR_CAT))
#if (OSEE_TC_CORE3_159_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 159)
#elif (OSEE_TC_CORE3_159_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 159)
#else
#error Invalid value for OSEE_TC_CORE3_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 159)
OSEE_DUMMY_ISR(_core3_, 159)
#endif /* OSEE_TC_CORE3_159_ISR_CAT */
#if (defined(OSEE_TC_CORE3_160_ISR_CAT))
#if (OSEE_TC_CORE3_160_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 160)
#elif (OSEE_TC_CORE3_160_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 160)
#else
#error Invalid value for OSEE_TC_CORE3_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 160)
OSEE_DUMMY_ISR(_core3_, 160)
#endif /* OSEE_TC_CORE3_160_ISR_CAT */
#if (defined(OSEE_TC_CORE3_161_ISR_CAT))
#if (OSEE_TC_CORE3_161_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 161)
#elif (OSEE_TC_CORE3_161_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 161)
#else
#error Invalid value for OSEE_TC_CORE3_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 161)
OSEE_DUMMY_ISR(_core3_, 161)
#endif /* OSEE_TC_CORE3_161_ISR_CAT */
#if (defined(OSEE_TC_CORE3_162_ISR_CAT))
#if (OSEE_TC_CORE3_162_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 162)
#elif (OSEE_TC_CORE3_162_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 162)
#else
#error Invalid value for OSEE_TC_CORE3_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 162)
OSEE_DUMMY_ISR(_core3_, 162)
#endif /* OSEE_TC_CORE3_162_ISR_CAT */
#if (defined(OSEE_TC_CORE3_163_ISR_CAT))
#if (OSEE_TC_CORE3_163_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 163)
#elif (OSEE_TC_CORE3_163_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 163)
#else
#error Invalid value for OSEE_TC_CORE3_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 163)
OSEE_DUMMY_ISR(_core3_, 163)
#endif /* OSEE_TC_CORE3_163_ISR_CAT */
#if (defined(OSEE_TC_CORE3_164_ISR_CAT))
#if (OSEE_TC_CORE3_164_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 164)
#elif (OSEE_TC_CORE3_164_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 164)
#else
#error Invalid value for OSEE_TC_CORE3_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 164)
OSEE_DUMMY_ISR(_core3_, 164)
#endif /* OSEE_TC_CORE3_164_ISR_CAT */
#if (defined(OSEE_TC_CORE3_165_ISR_CAT))
#if (OSEE_TC_CORE3_165_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 165)
#elif (OSEE_TC_CORE3_165_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 165)
#else
#error Invalid value for OSEE_TC_CORE3_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 165)
OSEE_DUMMY_ISR(_core3_, 165)
#endif /* OSEE_TC_CORE3_165_ISR_CAT */
#if (defined(OSEE_TC_CORE3_166_ISR_CAT))
#if (OSEE_TC_CORE3_166_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 166)
#elif (OSEE_TC_CORE3_166_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 166)
#else
#error Invalid value for OSEE_TC_CORE3_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 166)
OSEE_DUMMY_ISR(_core3_, 166)
#endif /* OSEE_TC_CORE3_166_ISR_CAT */
#if (defined(OSEE_TC_CORE3_167_ISR_CAT))
#if (OSEE_TC_CORE3_167_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 167)
#elif (OSEE_TC_CORE3_167_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 167)
#else
#error Invalid value for OSEE_TC_CORE3_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 167)
OSEE_DUMMY_ISR(_core3_, 167)
#endif /* OSEE_TC_CORE3_167_ISR_CAT */
#if (defined(OSEE_TC_CORE3_168_ISR_CAT))
#if (OSEE_TC_CORE3_168_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 168)
#elif (OSEE_TC_CORE3_168_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 168)
#else
#error Invalid value for OSEE_TC_CORE3_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 168)
OSEE_DUMMY_ISR(_core3_, 168)
#endif /* OSEE_TC_CORE3_168_ISR_CAT */
#if (defined(OSEE_TC_CORE3_169_ISR_CAT))
#if (OSEE_TC_CORE3_169_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 169)
#elif (OSEE_TC_CORE3_169_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 169)
#else
#error Invalid value for OSEE_TC_CORE3_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 169)
OSEE_DUMMY_ISR(_core3_, 169)
#endif /* OSEE_TC_CORE3_169_ISR_CAT */
#if (defined(OSEE_TC_CORE3_170_ISR_CAT))
#if (OSEE_TC_CORE3_170_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 170)
#elif (OSEE_TC_CORE3_170_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 170)
#else
#error Invalid value for OSEE_TC_CORE3_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 170)
OSEE_DUMMY_ISR(_core3_, 170)
#endif /* OSEE_TC_CORE3_170_ISR_CAT */
#if (defined(OSEE_TC_CORE3_171_ISR_CAT))
#if (OSEE_TC_CORE3_171_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 171)
#elif (OSEE_TC_CORE3_171_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 171)
#else
#error Invalid value for OSEE_TC_CORE3_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 171)
OSEE_DUMMY_ISR(_core3_, 171)
#endif /* OSEE_TC_CORE3_171_ISR_CAT */
#if (defined(OSEE_TC_CORE3_172_ISR_CAT))
#if (OSEE_TC_CORE3_172_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 172)
#elif (OSEE_TC_CORE3_172_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 172)
#else
#error Invalid value for OSEE_TC_CORE3_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 172)
OSEE_DUMMY_ISR(_core3_, 172)
#endif /* OSEE_TC_CORE3_172_ISR_CAT */
#if (defined(OSEE_TC_CORE3_173_ISR_CAT))
#if (OSEE_TC_CORE3_173_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 173)
#elif (OSEE_TC_CORE3_173_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 173)
#else
#error Invalid value for OSEE_TC_CORE3_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 173)
OSEE_DUMMY_ISR(_core3_, 173)
#endif /* OSEE_TC_CORE3_173_ISR_CAT */
#if (defined(OSEE_TC_CORE3_174_ISR_CAT))
#if (OSEE_TC_CORE3_174_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 174)
#elif (OSEE_TC_CORE3_174_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 174)
#else
#error Invalid value for OSEE_TC_CORE3_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 174)
OSEE_DUMMY_ISR(_core3_, 174)
#endif /* OSEE_TC_CORE3_174_ISR_CAT */
#if (defined(OSEE_TC_CORE3_175_ISR_CAT))
#if (OSEE_TC_CORE3_175_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 175)
#elif (OSEE_TC_CORE3_175_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 175)
#else
#error Invalid value for OSEE_TC_CORE3_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 175)
OSEE_DUMMY_ISR(_core3_, 175)
#endif /* OSEE_TC_CORE3_175_ISR_CAT */
#if (defined(OSEE_TC_CORE3_176_ISR_CAT))
#if (OSEE_TC_CORE3_176_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 176)
#elif (OSEE_TC_CORE3_176_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 176)
#else
#error Invalid value for OSEE_TC_CORE3_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 176)
OSEE_DUMMY_ISR(_core3_, 176)
#endif /* OSEE_TC_CORE3_176_ISR_CAT */
#if (defined(OSEE_TC_CORE3_177_ISR_CAT))
#if (OSEE_TC_CORE3_177_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 177)
#elif (OSEE_TC_CORE3_177_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 177)
#else
#error Invalid value for OSEE_TC_CORE3_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 177)
OSEE_DUMMY_ISR(_core3_, 177)
#endif /* OSEE_TC_CORE3_177_ISR_CAT */
#if (defined(OSEE_TC_CORE3_178_ISR_CAT))
#if (OSEE_TC_CORE3_178_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 178)
#elif (OSEE_TC_CORE3_178_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 178)
#else
#error Invalid value for OSEE_TC_CORE3_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 178)
OSEE_DUMMY_ISR(_core3_, 178)
#endif /* OSEE_TC_CORE3_178_ISR_CAT */
#if (defined(OSEE_TC_CORE3_179_ISR_CAT))
#if (OSEE_TC_CORE3_179_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 179)
#elif (OSEE_TC_CORE3_179_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 179)
#else
#error Invalid value for OSEE_TC_CORE3_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 179)
OSEE_DUMMY_ISR(_core3_, 179)
#endif /* OSEE_TC_CORE3_179_ISR_CAT */
#if (defined(OSEE_TC_CORE3_180_ISR_CAT))
#if (OSEE_TC_CORE3_180_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 180)
#elif (OSEE_TC_CORE3_180_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 180)
#else
#error Invalid value for OSEE_TC_CORE3_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 180)
OSEE_DUMMY_ISR(_core3_, 180)
#endif /* OSEE_TC_CORE3_180_ISR_CAT */
#if (defined(OSEE_TC_CORE3_181_ISR_CAT))
#if (OSEE_TC_CORE3_181_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 181)
#elif (OSEE_TC_CORE3_181_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 181)
#else
#error Invalid value for OSEE_TC_CORE3_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 181)
OSEE_DUMMY_ISR(_core3_, 181)
#endif /* OSEE_TC_CORE3_181_ISR_CAT */
#if (defined(OSEE_TC_CORE3_182_ISR_CAT))
#if (OSEE_TC_CORE3_182_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 182)
#elif (OSEE_TC_CORE3_182_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 182)
#else
#error Invalid value for OSEE_TC_CORE3_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 182)
OSEE_DUMMY_ISR(_core3_, 182)
#endif /* OSEE_TC_CORE3_182_ISR_CAT */
#if (defined(OSEE_TC_CORE3_183_ISR_CAT))
#if (OSEE_TC_CORE3_183_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 183)
#elif (OSEE_TC_CORE3_183_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 183)
#else
#error Invalid value for OSEE_TC_CORE3_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 183)
OSEE_DUMMY_ISR(_core3_, 183)
#endif /* OSEE_TC_CORE3_183_ISR_CAT */
#if (defined(OSEE_TC_CORE3_184_ISR_CAT))
#if (OSEE_TC_CORE3_184_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 184)
#elif (OSEE_TC_CORE3_184_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 184)
#else
#error Invalid value for OSEE_TC_CORE3_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 184)
OSEE_DUMMY_ISR(_core3_, 184)
#endif /* OSEE_TC_CORE3_184_ISR_CAT */
#if (defined(OSEE_TC_CORE3_185_ISR_CAT))
#if (OSEE_TC_CORE3_185_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 185)
#elif (OSEE_TC_CORE3_185_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 185)
#else
#error Invalid value for OSEE_TC_CORE3_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 185)
OSEE_DUMMY_ISR(_core3_, 185)
#endif /* OSEE_TC_CORE3_185_ISR_CAT */
#if (defined(OSEE_TC_CORE3_186_ISR_CAT))
#if (OSEE_TC_CORE3_186_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 186)
#elif (OSEE_TC_CORE3_186_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 186)
#else
#error Invalid value for OSEE_TC_CORE3_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 186)
OSEE_DUMMY_ISR(_core3_, 186)
#endif /* OSEE_TC_CORE3_186_ISR_CAT */
#if (defined(OSEE_TC_CORE3_187_ISR_CAT))
#if (OSEE_TC_CORE3_187_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 187)
#elif (OSEE_TC_CORE3_187_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 187)
#else
#error Invalid value for OSEE_TC_CORE3_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 187)
OSEE_DUMMY_ISR(_core3_, 187)
#endif /* OSEE_TC_CORE3_187_ISR_CAT */
#if (defined(OSEE_TC_CORE3_188_ISR_CAT))
#if (OSEE_TC_CORE3_188_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 188)
#elif (OSEE_TC_CORE3_188_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 188)
#else
#error Invalid value for OSEE_TC_CORE3_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 188)
OSEE_DUMMY_ISR(_core3_, 188)
#endif /* OSEE_TC_CORE3_188_ISR_CAT */
#if (defined(OSEE_TC_CORE3_189_ISR_CAT))
#if (OSEE_TC_CORE3_189_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 189)
#elif (OSEE_TC_CORE3_189_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 189)
#else
#error Invalid value for OSEE_TC_CORE3_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 189)
OSEE_DUMMY_ISR(_core3_, 189)
#endif /* OSEE_TC_CORE3_189_ISR_CAT */
#if (defined(OSEE_TC_CORE3_190_ISR_CAT))
#if (OSEE_TC_CORE3_190_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 190)
#elif (OSEE_TC_CORE3_190_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 190)
#else
#error Invalid value for OSEE_TC_CORE3_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 190)
OSEE_DUMMY_ISR(_core3_, 190)
#endif /* OSEE_TC_CORE3_190_ISR_CAT */
#if (defined(OSEE_TC_CORE3_191_ISR_CAT))
#if (OSEE_TC_CORE3_191_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 191)
#elif (OSEE_TC_CORE3_191_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 191)
#else
#error Invalid value for OSEE_TC_CORE3_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 191)
OSEE_DUMMY_ISR(_core3_, 191)
#endif /* OSEE_TC_CORE3_191_ISR_CAT */
#if (defined(OSEE_TC_CORE3_192_ISR_CAT))
#if (OSEE_TC_CORE3_192_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 192)
#elif (OSEE_TC_CORE3_192_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 192)
#else
#error Invalid value for OSEE_TC_CORE3_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 192)
OSEE_DUMMY_ISR(_core3_, 192)
#endif /* OSEE_TC_CORE3_192_ISR_CAT */
#if (defined(OSEE_TC_CORE3_193_ISR_CAT))
#if (OSEE_TC_CORE3_193_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 193)
#elif (OSEE_TC_CORE3_193_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 193)
#else
#error Invalid value for OSEE_TC_CORE3_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 193)
OSEE_DUMMY_ISR(_core3_, 193)
#endif /* OSEE_TC_CORE3_193_ISR_CAT */
#if (defined(OSEE_TC_CORE3_194_ISR_CAT))
#if (OSEE_TC_CORE3_194_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 194)
#elif (OSEE_TC_CORE3_194_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 194)
#else
#error Invalid value for OSEE_TC_CORE3_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 194)
OSEE_DUMMY_ISR(_core3_, 194)
#endif /* OSEE_TC_CORE3_194_ISR_CAT */
#if (defined(OSEE_TC_CORE3_195_ISR_CAT))
#if (OSEE_TC_CORE3_195_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 195)
#elif (OSEE_TC_CORE3_195_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 195)
#else
#error Invalid value for OSEE_TC_CORE3_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 195)
OSEE_DUMMY_ISR(_core3_, 195)
#endif /* OSEE_TC_CORE3_195_ISR_CAT */
#if (defined(OSEE_TC_CORE3_196_ISR_CAT))
#if (OSEE_TC_CORE3_196_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 196)
#elif (OSEE_TC_CORE3_196_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 196)
#else
#error Invalid value for OSEE_TC_CORE3_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 196)
OSEE_DUMMY_ISR(_core3_, 196)
#endif /* OSEE_TC_CORE3_196_ISR_CAT */
#if (defined(OSEE_TC_CORE3_197_ISR_CAT))
#if (OSEE_TC_CORE3_197_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 197)
#elif (OSEE_TC_CORE3_197_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 197)
#else
#error Invalid value for OSEE_TC_CORE3_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 197)
OSEE_DUMMY_ISR(_core3_, 197)
#endif /* OSEE_TC_CORE3_197_ISR_CAT */
#if (defined(OSEE_TC_CORE3_198_ISR_CAT))
#if (OSEE_TC_CORE3_198_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 198)
#elif (OSEE_TC_CORE3_198_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 198)
#else
#error Invalid value for OSEE_TC_CORE3_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 198)
OSEE_DUMMY_ISR(_core3_, 198)
#endif /* OSEE_TC_CORE3_198_ISR_CAT */
#if (defined(OSEE_TC_CORE3_199_ISR_CAT))
#if (OSEE_TC_CORE3_199_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 199)
#elif (OSEE_TC_CORE3_199_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 199)
#else
#error Invalid value for OSEE_TC_CORE3_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 199)
OSEE_DUMMY_ISR(_core3_, 199)
#endif /* OSEE_TC_CORE3_199_ISR_CAT */
#if (defined(OSEE_TC_CORE3_200_ISR_CAT))
#if (OSEE_TC_CORE3_200_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 200)
#elif (OSEE_TC_CORE3_200_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 200)
#else
#error Invalid value for OSEE_TC_CORE3_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 200)
OSEE_DUMMY_ISR(_core3_, 200)
#endif /* OSEE_TC_CORE3_200_ISR_CAT */
#if (defined(OSEE_TC_CORE3_201_ISR_CAT))
#if (OSEE_TC_CORE3_201_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 201)
#elif (OSEE_TC_CORE3_201_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 201)
#else
#error Invalid value for OSEE_TC_CORE3_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 201)
OSEE_DUMMY_ISR(_core3_, 201)
#endif /* OSEE_TC_CORE3_201_ISR_CAT */
#if (defined(OSEE_TC_CORE3_202_ISR_CAT))
#if (OSEE_TC_CORE3_202_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 202)
#elif (OSEE_TC_CORE3_202_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 202)
#else
#error Invalid value for OSEE_TC_CORE3_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 202)
OSEE_DUMMY_ISR(_core3_, 202)
#endif /* OSEE_TC_CORE3_202_ISR_CAT */
#if (defined(OSEE_TC_CORE3_203_ISR_CAT))
#if (OSEE_TC_CORE3_203_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 203)
#elif (OSEE_TC_CORE3_203_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 203)
#else
#error Invalid value for OSEE_TC_CORE3_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 203)
OSEE_DUMMY_ISR(_core3_, 203)
#endif /* OSEE_TC_CORE3_203_ISR_CAT */
#if (defined(OSEE_TC_CORE3_204_ISR_CAT))
#if (OSEE_TC_CORE3_204_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 204)
#elif (OSEE_TC_CORE3_204_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 204)
#else
#error Invalid value for OSEE_TC_CORE3_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 204)
OSEE_DUMMY_ISR(_core3_, 204)
#endif /* OSEE_TC_CORE3_204_ISR_CAT */
#if (defined(OSEE_TC_CORE3_205_ISR_CAT))
#if (OSEE_TC_CORE3_205_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 205)
#elif (OSEE_TC_CORE3_205_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 205)
#else
#error Invalid value for OSEE_TC_CORE3_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 205)
OSEE_DUMMY_ISR(_core3_, 205)
#endif /* OSEE_TC_CORE3_205_ISR_CAT */
#if (defined(OSEE_TC_CORE3_206_ISR_CAT))
#if (OSEE_TC_CORE3_206_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 206)
#elif (OSEE_TC_CORE3_206_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 206)
#else
#error Invalid value for OSEE_TC_CORE3_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 206)
OSEE_DUMMY_ISR(_core3_, 206)
#endif /* OSEE_TC_CORE3_206_ISR_CAT */
#if (defined(OSEE_TC_CORE3_207_ISR_CAT))
#if (OSEE_TC_CORE3_207_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 207)
#elif (OSEE_TC_CORE3_207_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 207)
#else
#error Invalid value for OSEE_TC_CORE3_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 207)
OSEE_DUMMY_ISR(_core3_, 207)
#endif /* OSEE_TC_CORE3_207_ISR_CAT */
#if (defined(OSEE_TC_CORE3_208_ISR_CAT))
#if (OSEE_TC_CORE3_208_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 208)
#elif (OSEE_TC_CORE3_208_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 208)
#else
#error Invalid value for OSEE_TC_CORE3_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 208)
OSEE_DUMMY_ISR(_core3_, 208)
#endif /* OSEE_TC_CORE3_208_ISR_CAT */
#if (defined(OSEE_TC_CORE3_209_ISR_CAT))
#if (OSEE_TC_CORE3_209_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 209)
#elif (OSEE_TC_CORE3_209_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 209)
#else
#error Invalid value for OSEE_TC_CORE3_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 209)
OSEE_DUMMY_ISR(_core3_, 209)
#endif /* OSEE_TC_CORE3_209_ISR_CAT */
#if (defined(OSEE_TC_CORE3_210_ISR_CAT))
#if (OSEE_TC_CORE3_210_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 210)
#elif (OSEE_TC_CORE3_210_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 210)
#else
#error Invalid value for OSEE_TC_CORE3_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 210)
OSEE_DUMMY_ISR(_core3_, 210)
#endif /* OSEE_TC_CORE3_210_ISR_CAT */
#if (defined(OSEE_TC_CORE3_211_ISR_CAT))
#if (OSEE_TC_CORE3_211_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 211)
#elif (OSEE_TC_CORE3_211_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 211)
#else
#error Invalid value for OSEE_TC_CORE3_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 211)
OSEE_DUMMY_ISR(_core3_, 211)
#endif /* OSEE_TC_CORE3_211_ISR_CAT */
#if (defined(OSEE_TC_CORE3_212_ISR_CAT))
#if (OSEE_TC_CORE3_212_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 212)
#elif (OSEE_TC_CORE3_212_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 212)
#else
#error Invalid value for OSEE_TC_CORE3_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 212)
OSEE_DUMMY_ISR(_core3_, 212)
#endif /* OSEE_TC_CORE3_212_ISR_CAT */
#if (defined(OSEE_TC_CORE3_213_ISR_CAT))
#if (OSEE_TC_CORE3_213_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 213)
#elif (OSEE_TC_CORE3_213_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 213)
#else
#error Invalid value for OSEE_TC_CORE3_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 213)
OSEE_DUMMY_ISR(_core3_, 213)
#endif /* OSEE_TC_CORE3_213_ISR_CAT */
#if (defined(OSEE_TC_CORE3_214_ISR_CAT))
#if (OSEE_TC_CORE3_214_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 214)
#elif (OSEE_TC_CORE3_214_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 214)
#else
#error Invalid value for OSEE_TC_CORE3_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 214)
OSEE_DUMMY_ISR(_core3_, 214)
#endif /* OSEE_TC_CORE3_214_ISR_CAT */
#if (defined(OSEE_TC_CORE3_215_ISR_CAT))
#if (OSEE_TC_CORE3_215_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 215)
#elif (OSEE_TC_CORE3_215_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 215)
#else
#error Invalid value for OSEE_TC_CORE3_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 215)
OSEE_DUMMY_ISR(_core3_, 215)
#endif /* OSEE_TC_CORE3_215_ISR_CAT */
#if (defined(OSEE_TC_CORE3_216_ISR_CAT))
#if (OSEE_TC_CORE3_216_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 216)
#elif (OSEE_TC_CORE3_216_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 216)
#else
#error Invalid value for OSEE_TC_CORE3_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 216)
OSEE_DUMMY_ISR(_core3_, 216)
#endif /* OSEE_TC_CORE3_216_ISR_CAT */
#if (defined(OSEE_TC_CORE3_217_ISR_CAT))
#if (OSEE_TC_CORE3_217_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 217)
#elif (OSEE_TC_CORE3_217_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 217)
#else
#error Invalid value for OSEE_TC_CORE3_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 217)
OSEE_DUMMY_ISR(_core3_, 217)
#endif /* OSEE_TC_CORE3_217_ISR_CAT */
#if (defined(OSEE_TC_CORE3_218_ISR_CAT))
#if (OSEE_TC_CORE3_218_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 218)
#elif (OSEE_TC_CORE3_218_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 218)
#else
#error Invalid value for OSEE_TC_CORE3_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 218)
OSEE_DUMMY_ISR(_core3_, 218)
#endif /* OSEE_TC_CORE3_218_ISR_CAT */
#if (defined(OSEE_TC_CORE3_219_ISR_CAT))
#if (OSEE_TC_CORE3_219_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 219)
#elif (OSEE_TC_CORE3_219_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 219)
#else
#error Invalid value for OSEE_TC_CORE3_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 219)
OSEE_DUMMY_ISR(_core3_, 219)
#endif /* OSEE_TC_CORE3_219_ISR_CAT */
#if (defined(OSEE_TC_CORE3_220_ISR_CAT))
#if (OSEE_TC_CORE3_220_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 220)
#elif (OSEE_TC_CORE3_220_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 220)
#else
#error Invalid value for OSEE_TC_CORE3_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 220)
OSEE_DUMMY_ISR(_core3_, 220)
#endif /* OSEE_TC_CORE3_220_ISR_CAT */
#if (defined(OSEE_TC_CORE3_221_ISR_CAT))
#if (OSEE_TC_CORE3_221_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 221)
#elif (OSEE_TC_CORE3_221_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 221)
#else
#error Invalid value for OSEE_TC_CORE3_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 221)
OSEE_DUMMY_ISR(_core3_, 221)
#endif /* OSEE_TC_CORE3_221_ISR_CAT */
#if (defined(OSEE_TC_CORE3_222_ISR_CAT))
#if (OSEE_TC_CORE3_222_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 222)
#elif (OSEE_TC_CORE3_222_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 222)
#else
#error Invalid value for OSEE_TC_CORE3_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 222)
OSEE_DUMMY_ISR(_core3_, 222)
#endif /* OSEE_TC_CORE3_222_ISR_CAT */
#if (defined(OSEE_TC_CORE3_223_ISR_CAT))
#if (OSEE_TC_CORE3_223_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 223)
#elif (OSEE_TC_CORE3_223_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 223)
#else
#error Invalid value for OSEE_TC_CORE3_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 223)
OSEE_DUMMY_ISR(_core3_, 223)
#endif /* OSEE_TC_CORE3_223_ISR_CAT */
#if (defined(OSEE_TC_CORE3_224_ISR_CAT))
#if (OSEE_TC_CORE3_224_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 224)
#elif (OSEE_TC_CORE3_224_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 224)
#else
#error Invalid value for OSEE_TC_CORE3_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 224)
OSEE_DUMMY_ISR(_core3_, 224)
#endif /* OSEE_TC_CORE3_224_ISR_CAT */
#if (defined(OSEE_TC_CORE3_225_ISR_CAT))
#if (OSEE_TC_CORE3_225_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 225)
#elif (OSEE_TC_CORE3_225_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 225)
#else
#error Invalid value for OSEE_TC_CORE3_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 225)
OSEE_DUMMY_ISR(_core3_, 225)
#endif /* OSEE_TC_CORE3_225_ISR_CAT */
#if (defined(OSEE_TC_CORE3_226_ISR_CAT))
#if (OSEE_TC_CORE3_226_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 226)
#elif (OSEE_TC_CORE3_226_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 226)
#else
#error Invalid value for OSEE_TC_CORE3_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 226)
OSEE_DUMMY_ISR(_core3_, 226)
#endif /* OSEE_TC_CORE3_226_ISR_CAT */
#if (defined(OSEE_TC_CORE3_227_ISR_CAT))
#if (OSEE_TC_CORE3_227_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 227)
#elif (OSEE_TC_CORE3_227_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 227)
#else
#error Invalid value for OSEE_TC_CORE3_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 227)
OSEE_DUMMY_ISR(_core3_, 227)
#endif /* OSEE_TC_CORE3_227_ISR_CAT */
#if (defined(OSEE_TC_CORE3_228_ISR_CAT))
#if (OSEE_TC_CORE3_228_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 228)
#elif (OSEE_TC_CORE3_228_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 228)
#else
#error Invalid value for OSEE_TC_CORE3_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 228)
OSEE_DUMMY_ISR(_core3_, 228)
#endif /* OSEE_TC_CORE3_228_ISR_CAT */
#if (defined(OSEE_TC_CORE3_229_ISR_CAT))
#if (OSEE_TC_CORE3_229_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 229)
#elif (OSEE_TC_CORE3_229_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 229)
#else
#error Invalid value for OSEE_TC_CORE3_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 229)
OSEE_DUMMY_ISR(_core3_, 229)
#endif /* OSEE_TC_CORE3_229_ISR_CAT */
#if (defined(OSEE_TC_CORE3_230_ISR_CAT))
#if (OSEE_TC_CORE3_230_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 230)
#elif (OSEE_TC_CORE3_230_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 230)
#else
#error Invalid value for OSEE_TC_CORE3_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 230)
OSEE_DUMMY_ISR(_core3_, 230)
#endif /* OSEE_TC_CORE3_230_ISR_CAT */
#if (defined(OSEE_TC_CORE3_231_ISR_CAT))
#if (OSEE_TC_CORE3_231_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 231)
#elif (OSEE_TC_CORE3_231_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 231)
#else
#error Invalid value for OSEE_TC_CORE3_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 231)
OSEE_DUMMY_ISR(_core3_, 231)
#endif /* OSEE_TC_CORE3_231_ISR_CAT */
#if (defined(OSEE_TC_CORE3_232_ISR_CAT))
#if (OSEE_TC_CORE3_232_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 232)
#elif (OSEE_TC_CORE3_232_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 232)
#else
#error Invalid value for OSEE_TC_CORE3_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 232)
OSEE_DUMMY_ISR(_core3_, 232)
#endif /* OSEE_TC_CORE3_232_ISR_CAT */
#if (defined(OSEE_TC_CORE3_233_ISR_CAT))
#if (OSEE_TC_CORE3_233_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 233)
#elif (OSEE_TC_CORE3_233_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 233)
#else
#error Invalid value for OSEE_TC_CORE3_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 233)
OSEE_DUMMY_ISR(_core3_, 233)
#endif /* OSEE_TC_CORE3_233_ISR_CAT */
#if (defined(OSEE_TC_CORE3_234_ISR_CAT))
#if (OSEE_TC_CORE3_234_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 234)
#elif (OSEE_TC_CORE3_234_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 234)
#else
#error Invalid value for OSEE_TC_CORE3_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 234)
OSEE_DUMMY_ISR(_core3_, 234)
#endif /* OSEE_TC_CORE3_234_ISR_CAT */
#if (defined(OSEE_TC_CORE3_235_ISR_CAT))
#if (OSEE_TC_CORE3_235_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 235)
#elif (OSEE_TC_CORE3_235_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 235)
#else
#error Invalid value for OSEE_TC_CORE3_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 235)
OSEE_DUMMY_ISR(_core3_, 235)
#endif /* OSEE_TC_CORE3_235_ISR_CAT */
#if (defined(OSEE_TC_CORE3_236_ISR_CAT))
#if (OSEE_TC_CORE3_236_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 236)
#elif (OSEE_TC_CORE3_236_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 236)
#else
#error Invalid value for OSEE_TC_CORE3_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 236)
OSEE_DUMMY_ISR(_core3_, 236)
#endif /* OSEE_TC_CORE3_236_ISR_CAT */
#if (defined(OSEE_TC_CORE3_237_ISR_CAT))
#if (OSEE_TC_CORE3_237_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 237)
#elif (OSEE_TC_CORE3_237_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 237)
#else
#error Invalid value for OSEE_TC_CORE3_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 237)
OSEE_DUMMY_ISR(_core3_, 237)
#endif /* OSEE_TC_CORE3_237_ISR_CAT */
#if (defined(OSEE_TC_CORE3_238_ISR_CAT))
#if (OSEE_TC_CORE3_238_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 238)
#elif (OSEE_TC_CORE3_238_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 238)
#else
#error Invalid value for OSEE_TC_CORE3_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 238)
OSEE_DUMMY_ISR(_core3_, 238)
#endif /* OSEE_TC_CORE3_238_ISR_CAT */
#if (defined(OSEE_TC_CORE3_239_ISR_CAT))
#if (OSEE_TC_CORE3_239_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 239)
#elif (OSEE_TC_CORE3_239_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 239)
#else
#error Invalid value for OSEE_TC_CORE3_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 239)
OSEE_DUMMY_ISR(_core3_, 239)
#endif /* OSEE_TC_CORE3_239_ISR_CAT */
#if (defined(OSEE_TC_CORE3_240_ISR_CAT))
#if (OSEE_TC_CORE3_240_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 240)
#elif (OSEE_TC_CORE3_240_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 240)
#else
#error Invalid value for OSEE_TC_CORE3_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 240)
OSEE_DUMMY_ISR(_core3_, 240)
#endif /* OSEE_TC_CORE3_240_ISR_CAT */
#if (defined(OSEE_TC_CORE3_241_ISR_CAT))
#if (OSEE_TC_CORE3_241_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 241)
#elif (OSEE_TC_CORE3_241_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 241)
#else
#error Invalid value for OSEE_TC_CORE3_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 241)
OSEE_DUMMY_ISR(_core3_, 241)
#endif /* OSEE_TC_CORE3_241_ISR_CAT */
#if (defined(OSEE_TC_CORE3_242_ISR_CAT))
#if (OSEE_TC_CORE3_242_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 242)
#elif (OSEE_TC_CORE3_242_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 242)
#else
#error Invalid value for OSEE_TC_CORE3_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 242)
OSEE_DUMMY_ISR(_core3_, 242)
#endif /* OSEE_TC_CORE3_242_ISR_CAT */
#if (defined(OSEE_TC_CORE3_243_ISR_CAT))
#if (OSEE_TC_CORE3_243_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 243)
#elif (OSEE_TC_CORE3_243_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 243)
#else
#error Invalid value for OSEE_TC_CORE3_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 243)
OSEE_DUMMY_ISR(_core3_, 243)
#endif /* OSEE_TC_CORE3_243_ISR_CAT */
#if (defined(OSEE_TC_CORE3_244_ISR_CAT))
#if (OSEE_TC_CORE3_244_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 244)
#elif (OSEE_TC_CORE3_244_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 244)
#else
#error Invalid value for OSEE_TC_CORE3_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 244)
OSEE_DUMMY_ISR(_core3_, 244)
#endif /* OSEE_TC_CORE3_244_ISR_CAT */
#if (defined(OSEE_TC_CORE3_245_ISR_CAT))
#if (OSEE_TC_CORE3_245_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 245)
#elif (OSEE_TC_CORE3_245_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 245)
#else
#error Invalid value for OSEE_TC_CORE3_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 245)
OSEE_DUMMY_ISR(_core3_, 245)
#endif /* OSEE_TC_CORE3_245_ISR_CAT */
#if (defined(OSEE_TC_CORE3_246_ISR_CAT))
#if (OSEE_TC_CORE3_246_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 246)
#elif (OSEE_TC_CORE3_246_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 246)
#else
#error Invalid value for OSEE_TC_CORE3_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 246)
OSEE_DUMMY_ISR(_core3_, 246)
#endif /* OSEE_TC_CORE3_246_ISR_CAT */
#if (defined(OSEE_TC_CORE3_247_ISR_CAT))
#if (OSEE_TC_CORE3_247_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 247)
#elif (OSEE_TC_CORE3_247_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 247)
#else
#error Invalid value for OSEE_TC_CORE3_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 247)
OSEE_DUMMY_ISR(_core3_, 247)
#endif /* OSEE_TC_CORE3_247_ISR_CAT */
#if (defined(OSEE_TC_CORE3_248_ISR_CAT))
#if (OSEE_TC_CORE3_248_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 248)
#elif (OSEE_TC_CORE3_248_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 248)
#else
#error Invalid value for OSEE_TC_CORE3_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 248)
OSEE_DUMMY_ISR(_core3_, 248)
#endif /* OSEE_TC_CORE3_248_ISR_CAT */
#if (defined(OSEE_TC_CORE3_249_ISR_CAT))
#if (OSEE_TC_CORE3_249_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 249)
#elif (OSEE_TC_CORE3_249_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 249)
#else
#error Invalid value for OSEE_TC_CORE3_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 249)
OSEE_DUMMY_ISR(_core3_, 249)
#endif /* OSEE_TC_CORE3_249_ISR_CAT */
#if (defined(OSEE_TC_CORE3_250_ISR_CAT))
#if (OSEE_TC_CORE3_250_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 250)
#elif (OSEE_TC_CORE3_250_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 250)
#else
#error Invalid value for OSEE_TC_CORE3_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 250)
OSEE_DUMMY_ISR(_core3_, 250)
#endif /* OSEE_TC_CORE3_250_ISR_CAT */
#if (defined(OSEE_TC_CORE3_251_ISR_CAT))
#if (OSEE_TC_CORE3_251_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 251)
#elif (OSEE_TC_CORE3_251_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 251)
#else
#error Invalid value for OSEE_TC_CORE3_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 251)
OSEE_DUMMY_ISR(_core3_, 251)
#endif /* OSEE_TC_CORE3_251_ISR_CAT */
#if (defined(OSEE_TC_CORE3_252_ISR_CAT))
#if (OSEE_TC_CORE3_252_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 252)
#elif (OSEE_TC_CORE3_252_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 252)
#else
#error Invalid value for OSEE_TC_CORE3_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 252)
OSEE_DUMMY_ISR(_core3_, 252)
#endif /* OSEE_TC_CORE3_252_ISR_CAT */
#if (defined(OSEE_TC_CORE3_253_ISR_CAT))
#if (OSEE_TC_CORE3_253_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 253)
#elif (OSEE_TC_CORE3_253_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 253)
#else
#error Invalid value for OSEE_TC_CORE3_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 253)
OSEE_DUMMY_ISR(_core3_, 253)
#endif /* OSEE_TC_CORE3_253_ISR_CAT */
#if (defined(OSEE_TC_CORE3_254_ISR_CAT))
#if (OSEE_TC_CORE3_254_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 254)
#elif (OSEE_TC_CORE3_254_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 254)
#else
#error Invalid value for OSEE_TC_CORE3_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 254)
OSEE_DUMMY_ISR(_core3_, 254)
#endif /* OSEE_TC_CORE3_254_ISR_CAT */
#if (defined(OSEE_TC_CORE3_255_ISR_CAT))
#if (OSEE_TC_CORE3_255_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core3_, 255)
#elif (OSEE_TC_CORE3_255_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core3_, 255)
#else
#error Invalid value for OSEE_TC_CORE3_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 255)
OSEE_DUMMY_ISR(_core3_, 255)
#endif /* OSEE_TC_CORE3_255_ISR_CAT */
#endif /* OSEE_TC_CORE3_ISR_MAX_PRIO */

#if(defined(OSEE_TC_CORE4_ISR_MAX_PRIO))
OSEE_ISR2_DECLARE(_core4_, 1)
#if (defined(OSEE_TC_CORE4_2_ISR_CAT))
#if (OSEE_TC_CORE4_2_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 2)
#elif (OSEE_TC_CORE4_2_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 2)
#else
#error Invalid value for OSEE_TC_CORE4_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 2)
OSEE_DUMMY_ISR(_core4_, 2)
#endif /* OSEE_TC_CORE4_2_ISR_CAT */
#if (defined(OSEE_TC_CORE4_3_ISR_CAT))
#if (OSEE_TC_CORE4_3_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 3)
#elif (OSEE_TC_CORE4_3_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 3)
#else
#error Invalid value for OSEE_TC_CORE4_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 3)
OSEE_DUMMY_ISR(_core4_, 3)
#endif /* OSEE_TC_CORE4_3_ISR_CAT */
#if (defined(OSEE_TC_CORE4_4_ISR_CAT))
#if (OSEE_TC_CORE4_4_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 4)
#elif (OSEE_TC_CORE4_4_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 4)
#else
#error Invalid value for OSEE_TC_CORE4_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 4)
OSEE_DUMMY_ISR(_core4_, 4)
#endif /* OSEE_TC_CORE4_4_ISR_CAT */
#if (defined(OSEE_TC_CORE4_5_ISR_CAT))
#if (OSEE_TC_CORE4_5_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 5)
#elif (OSEE_TC_CORE4_5_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 5)
#else
#error Invalid value for OSEE_TC_CORE4_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 5)
OSEE_DUMMY_ISR(_core4_, 5)
#endif /* OSEE_TC_CORE4_5_ISR_CAT */
#if (defined(OSEE_TC_CORE4_6_ISR_CAT))
#if (OSEE_TC_CORE4_6_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 6)
#elif (OSEE_TC_CORE4_6_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 6)
#else
#error Invalid value for OSEE_TC_CORE4_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 6)
OSEE_DUMMY_ISR(_core4_, 6)
#endif /* OSEE_TC_CORE4_6_ISR_CAT */
#if (defined(OSEE_TC_CORE4_7_ISR_CAT))
#if (OSEE_TC_CORE4_7_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 7)
#elif (OSEE_TC_CORE4_7_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 7)
#else
#error Invalid value for OSEE_TC_CORE4_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 7)
OSEE_DUMMY_ISR(_core4_, 7)
#endif /* OSEE_TC_CORE4_7_ISR_CAT */
#if (defined(OSEE_TC_CORE4_8_ISR_CAT))
#if (OSEE_TC_CORE4_8_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 8)
#elif (OSEE_TC_CORE4_8_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 8)
#else
#error Invalid value for OSEE_TC_CORE4_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 8)
OSEE_DUMMY_ISR(_core4_, 8)
#endif /* OSEE_TC_CORE4_8_ISR_CAT */
#if (defined(OSEE_TC_CORE4_9_ISR_CAT))
#if (OSEE_TC_CORE4_9_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 9)
#elif (OSEE_TC_CORE4_9_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 9)
#else
#error Invalid value for OSEE_TC_CORE4_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 9)
OSEE_DUMMY_ISR(_core4_, 9)
#endif /* OSEE_TC_CORE4_9_ISR_CAT */
#if (defined(OSEE_TC_CORE4_10_ISR_CAT))
#if (OSEE_TC_CORE4_10_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 10)
#elif (OSEE_TC_CORE4_10_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 10)
#else
#error Invalid value for OSEE_TC_CORE4_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 10)
OSEE_DUMMY_ISR(_core4_, 10)
#endif /* OSEE_TC_CORE4_10_ISR_CAT */
#if (defined(OSEE_TC_CORE4_11_ISR_CAT))
#if (OSEE_TC_CORE4_11_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 11)
#elif (OSEE_TC_CORE4_11_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 11)
#else
#error Invalid value for OSEE_TC_CORE4_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 11)
OSEE_DUMMY_ISR(_core4_, 11)
#endif /* OSEE_TC_CORE4_11_ISR_CAT */
#if (defined(OSEE_TC_CORE4_12_ISR_CAT))
#if (OSEE_TC_CORE4_12_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 12)
#elif (OSEE_TC_CORE4_12_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 12)
#else
#error Invalid value for OSEE_TC_CORE4_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 12)
OSEE_DUMMY_ISR(_core4_, 12)
#endif /* OSEE_TC_CORE4_12_ISR_CAT */
#if (defined(OSEE_TC_CORE4_13_ISR_CAT))
#if (OSEE_TC_CORE4_13_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 13)
#elif (OSEE_TC_CORE4_13_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 13)
#else
#error Invalid value for OSEE_TC_CORE4_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 13)
OSEE_DUMMY_ISR(_core4_, 13)
#endif /* OSEE_TC_CORE4_13_ISR_CAT */
#if (defined(OSEE_TC_CORE4_14_ISR_CAT))
#if (OSEE_TC_CORE4_14_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 14)
#elif (OSEE_TC_CORE4_14_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 14)
#else
#error Invalid value for OSEE_TC_CORE4_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 14)
OSEE_DUMMY_ISR(_core4_, 14)
#endif /* OSEE_TC_CORE4_14_ISR_CAT */
#if (defined(OSEE_TC_CORE4_15_ISR_CAT))
#if (OSEE_TC_CORE4_15_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 15)
#elif (OSEE_TC_CORE4_15_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 15)
#else
#error Invalid value for OSEE_TC_CORE4_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 15)
OSEE_DUMMY_ISR(_core4_, 15)
#endif /* OSEE_TC_CORE4_15_ISR_CAT */
#if (defined(OSEE_TC_CORE4_16_ISR_CAT))
#if (OSEE_TC_CORE4_16_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 16)
#elif (OSEE_TC_CORE4_16_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 16)
#else
#error Invalid value for OSEE_TC_CORE4_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 16)
OSEE_DUMMY_ISR(_core4_, 16)
#endif /* OSEE_TC_CORE4_16_ISR_CAT */
#if (defined(OSEE_TC_CORE4_17_ISR_CAT))
#if (OSEE_TC_CORE4_17_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 17)
#elif (OSEE_TC_CORE4_17_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 17)
#else
#error Invalid value for OSEE_TC_CORE4_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 17)
OSEE_DUMMY_ISR(_core4_, 17)
#endif /* OSEE_TC_CORE4_17_ISR_CAT */
#if (defined(OSEE_TC_CORE4_18_ISR_CAT))
#if (OSEE_TC_CORE4_18_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 18)
#elif (OSEE_TC_CORE4_18_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 18)
#else
#error Invalid value for OSEE_TC_CORE4_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 18)
OSEE_DUMMY_ISR(_core4_, 18)
#endif /* OSEE_TC_CORE4_18_ISR_CAT */
#if (defined(OSEE_TC_CORE4_19_ISR_CAT))
#if (OSEE_TC_CORE4_19_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 19)
#elif (OSEE_TC_CORE4_19_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 19)
#else
#error Invalid value for OSEE_TC_CORE4_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 19)
OSEE_DUMMY_ISR(_core4_, 19)
#endif /* OSEE_TC_CORE4_19_ISR_CAT */
#if (defined(OSEE_TC_CORE4_20_ISR_CAT))
#if (OSEE_TC_CORE4_20_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 20)
#elif (OSEE_TC_CORE4_20_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 20)
#else
#error Invalid value for OSEE_TC_CORE4_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 20)
OSEE_DUMMY_ISR(_core4_, 20)
#endif /* OSEE_TC_CORE4_20_ISR_CAT */
#if (defined(OSEE_TC_CORE4_21_ISR_CAT))
#if (OSEE_TC_CORE4_21_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 21)
#elif (OSEE_TC_CORE4_21_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 21)
#else
#error Invalid value for OSEE_TC_CORE4_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 21)
OSEE_DUMMY_ISR(_core4_, 21)
#endif /* OSEE_TC_CORE4_21_ISR_CAT */
#if (defined(OSEE_TC_CORE4_22_ISR_CAT))
#if (OSEE_TC_CORE4_22_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 22)
#elif (OSEE_TC_CORE4_22_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 22)
#else
#error Invalid value for OSEE_TC_CORE4_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 22)
OSEE_DUMMY_ISR(_core4_, 22)
#endif /* OSEE_TC_CORE4_22_ISR_CAT */
#if (defined(OSEE_TC_CORE4_23_ISR_CAT))
#if (OSEE_TC_CORE4_23_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 23)
#elif (OSEE_TC_CORE4_23_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 23)
#else
#error Invalid value for OSEE_TC_CORE4_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 23)
OSEE_DUMMY_ISR(_core4_, 23)
#endif /* OSEE_TC_CORE4_23_ISR_CAT */
#if (defined(OSEE_TC_CORE4_24_ISR_CAT))
#if (OSEE_TC_CORE4_24_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 24)
#elif (OSEE_TC_CORE4_24_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 24)
#else
#error Invalid value for OSEE_TC_CORE4_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 24)
OSEE_DUMMY_ISR(_core4_, 24)
#endif /* OSEE_TC_CORE4_24_ISR_CAT */
#if (defined(OSEE_TC_CORE4_25_ISR_CAT))
#if (OSEE_TC_CORE4_25_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 25)
#elif (OSEE_TC_CORE4_25_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 25)
#else
#error Invalid value for OSEE_TC_CORE4_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 25)
OSEE_DUMMY_ISR(_core4_, 25)
#endif /* OSEE_TC_CORE4_25_ISR_CAT */
#if (defined(OSEE_TC_CORE4_26_ISR_CAT))
#if (OSEE_TC_CORE4_26_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 26)
#elif (OSEE_TC_CORE4_26_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 26)
#else
#error Invalid value for OSEE_TC_CORE4_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 26)
OSEE_DUMMY_ISR(_core4_, 26)
#endif /* OSEE_TC_CORE4_26_ISR_CAT */
#if (defined(OSEE_TC_CORE4_27_ISR_CAT))
#if (OSEE_TC_CORE4_27_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 27)
#elif (OSEE_TC_CORE4_27_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 27)
#else
#error Invalid value for OSEE_TC_CORE4_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 27)
OSEE_DUMMY_ISR(_core4_, 27)
#endif /* OSEE_TC_CORE4_27_ISR_CAT */
#if (defined(OSEE_TC_CORE4_28_ISR_CAT))
#if (OSEE_TC_CORE4_28_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 28)
#elif (OSEE_TC_CORE4_28_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 28)
#else
#error Invalid value for OSEE_TC_CORE4_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 28)
OSEE_DUMMY_ISR(_core4_, 28)
#endif /* OSEE_TC_CORE4_28_ISR_CAT */
#if (defined(OSEE_TC_CORE4_29_ISR_CAT))
#if (OSEE_TC_CORE4_29_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 29)
#elif (OSEE_TC_CORE4_29_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 29)
#else
#error Invalid value for OSEE_TC_CORE4_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 29)
OSEE_DUMMY_ISR(_core4_, 29)
#endif /* OSEE_TC_CORE4_29_ISR_CAT */
#if (defined(OSEE_TC_CORE4_30_ISR_CAT))
#if (OSEE_TC_CORE4_30_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 30)
#elif (OSEE_TC_CORE4_30_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 30)
#else
#error Invalid value for OSEE_TC_CORE4_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 30)
OSEE_DUMMY_ISR(_core4_, 30)
#endif /* OSEE_TC_CORE4_30_ISR_CAT */
#if (defined(OSEE_TC_CORE4_31_ISR_CAT))
#if (OSEE_TC_CORE4_31_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 31)
#elif (OSEE_TC_CORE4_31_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 31)
#else
#error Invalid value for OSEE_TC_CORE4_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 31)
OSEE_DUMMY_ISR(_core4_, 31)
#endif /* OSEE_TC_CORE4_31_ISR_CAT */
#if (defined(OSEE_TC_CORE4_32_ISR_CAT))
#if (OSEE_TC_CORE4_32_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 32)
#elif (OSEE_TC_CORE4_32_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 32)
#else
#error Invalid value for OSEE_TC_CORE4_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 32)
OSEE_DUMMY_ISR(_core4_, 32)
#endif /* OSEE_TC_CORE4_32_ISR_CAT */
#if (defined(OSEE_TC_CORE4_33_ISR_CAT))
#if (OSEE_TC_CORE4_33_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 33)
#elif (OSEE_TC_CORE4_33_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 33)
#else
#error Invalid value for OSEE_TC_CORE4_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 33)
OSEE_DUMMY_ISR(_core4_, 33)
#endif /* OSEE_TC_CORE4_33_ISR_CAT */
#if (defined(OSEE_TC_CORE4_34_ISR_CAT))
#if (OSEE_TC_CORE4_34_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 34)
#elif (OSEE_TC_CORE4_34_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 34)
#else
#error Invalid value for OSEE_TC_CORE4_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 34)
OSEE_DUMMY_ISR(_core4_, 34)
#endif /* OSEE_TC_CORE4_34_ISR_CAT */
#if (defined(OSEE_TC_CORE4_35_ISR_CAT))
#if (OSEE_TC_CORE4_35_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 35)
#elif (OSEE_TC_CORE4_35_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 35)
#else
#error Invalid value for OSEE_TC_CORE4_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 35)
OSEE_DUMMY_ISR(_core4_, 35)
#endif /* OSEE_TC_CORE4_35_ISR_CAT */
#if (defined(OSEE_TC_CORE4_36_ISR_CAT))
#if (OSEE_TC_CORE4_36_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 36)
#elif (OSEE_TC_CORE4_36_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 36)
#else
#error Invalid value for OSEE_TC_CORE4_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 36)
OSEE_DUMMY_ISR(_core4_, 36)
#endif /* OSEE_TC_CORE4_36_ISR_CAT */
#if (defined(OSEE_TC_CORE4_37_ISR_CAT))
#if (OSEE_TC_CORE4_37_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 37)
#elif (OSEE_TC_CORE4_37_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 37)
#else
#error Invalid value for OSEE_TC_CORE4_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 37)
OSEE_DUMMY_ISR(_core4_, 37)
#endif /* OSEE_TC_CORE4_37_ISR_CAT */
#if (defined(OSEE_TC_CORE4_38_ISR_CAT))
#if (OSEE_TC_CORE4_38_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 38)
#elif (OSEE_TC_CORE4_38_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 38)
#else
#error Invalid value for OSEE_TC_CORE4_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 38)
OSEE_DUMMY_ISR(_core4_, 38)
#endif /* OSEE_TC_CORE4_38_ISR_CAT */
#if (defined(OSEE_TC_CORE4_39_ISR_CAT))
#if (OSEE_TC_CORE4_39_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 39)
#elif (OSEE_TC_CORE4_39_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 39)
#else
#error Invalid value for OSEE_TC_CORE4_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 39)
OSEE_DUMMY_ISR(_core4_, 39)
#endif /* OSEE_TC_CORE4_39_ISR_CAT */
#if (defined(OSEE_TC_CORE4_40_ISR_CAT))
#if (OSEE_TC_CORE4_40_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 40)
#elif (OSEE_TC_CORE4_40_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 40)
#else
#error Invalid value for OSEE_TC_CORE4_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 40)
OSEE_DUMMY_ISR(_core4_, 40)
#endif /* OSEE_TC_CORE4_40_ISR_CAT */
#if (defined(OSEE_TC_CORE4_41_ISR_CAT))
#if (OSEE_TC_CORE4_41_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 41)
#elif (OSEE_TC_CORE4_41_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 41)
#else
#error Invalid value for OSEE_TC_CORE4_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 41)
OSEE_DUMMY_ISR(_core4_, 41)
#endif /* OSEE_TC_CORE4_41_ISR_CAT */
#if (defined(OSEE_TC_CORE4_42_ISR_CAT))
#if (OSEE_TC_CORE4_42_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 42)
#elif (OSEE_TC_CORE4_42_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 42)
#else
#error Invalid value for OSEE_TC_CORE4_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 42)
OSEE_DUMMY_ISR(_core4_, 42)
#endif /* OSEE_TC_CORE4_42_ISR_CAT */
#if (defined(OSEE_TC_CORE4_43_ISR_CAT))
#if (OSEE_TC_CORE4_43_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 43)
#elif (OSEE_TC_CORE4_43_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 43)
#else
#error Invalid value for OSEE_TC_CORE4_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 43)
OSEE_DUMMY_ISR(_core4_, 43)
#endif /* OSEE_TC_CORE4_43_ISR_CAT */
#if (defined(OSEE_TC_CORE4_44_ISR_CAT))
#if (OSEE_TC_CORE4_44_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 44)
#elif (OSEE_TC_CORE4_44_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 44)
#else
#error Invalid value for OSEE_TC_CORE4_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 44)
OSEE_DUMMY_ISR(_core4_, 44)
#endif /* OSEE_TC_CORE4_44_ISR_CAT */
#if (defined(OSEE_TC_CORE4_45_ISR_CAT))
#if (OSEE_TC_CORE4_45_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 45)
#elif (OSEE_TC_CORE4_45_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 45)
#else
#error Invalid value for OSEE_TC_CORE4_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 45)
OSEE_DUMMY_ISR(_core4_, 45)
#endif /* OSEE_TC_CORE4_45_ISR_CAT */
#if (defined(OSEE_TC_CORE4_46_ISR_CAT))
#if (OSEE_TC_CORE4_46_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 46)
#elif (OSEE_TC_CORE4_46_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 46)
#else
#error Invalid value for OSEE_TC_CORE4_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 46)
OSEE_DUMMY_ISR(_core4_, 46)
#endif /* OSEE_TC_CORE4_46_ISR_CAT */
#if (defined(OSEE_TC_CORE4_47_ISR_CAT))
#if (OSEE_TC_CORE4_47_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 47)
#elif (OSEE_TC_CORE4_47_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 47)
#else
#error Invalid value for OSEE_TC_CORE4_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 47)
OSEE_DUMMY_ISR(_core4_, 47)
#endif /* OSEE_TC_CORE4_47_ISR_CAT */
#if (defined(OSEE_TC_CORE4_48_ISR_CAT))
#if (OSEE_TC_CORE4_48_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 48)
#elif (OSEE_TC_CORE4_48_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 48)
#else
#error Invalid value for OSEE_TC_CORE4_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 48)
OSEE_DUMMY_ISR(_core4_, 48)
#endif /* OSEE_TC_CORE4_48_ISR_CAT */
#if (defined(OSEE_TC_CORE4_49_ISR_CAT))
#if (OSEE_TC_CORE4_49_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 49)
#elif (OSEE_TC_CORE4_49_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 49)
#else
#error Invalid value for OSEE_TC_CORE4_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 49)
OSEE_DUMMY_ISR(_core4_, 49)
#endif /* OSEE_TC_CORE4_49_ISR_CAT */
#if (defined(OSEE_TC_CORE4_50_ISR_CAT))
#if (OSEE_TC_CORE4_50_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 50)
#elif (OSEE_TC_CORE4_50_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 50)
#else
#error Invalid value for OSEE_TC_CORE4_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 50)
OSEE_DUMMY_ISR(_core4_, 50)
#endif /* OSEE_TC_CORE4_50_ISR_CAT */
#if (defined(OSEE_TC_CORE4_51_ISR_CAT))
#if (OSEE_TC_CORE4_51_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 51)
#elif (OSEE_TC_CORE4_51_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 51)
#else
#error Invalid value for OSEE_TC_CORE4_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 51)
OSEE_DUMMY_ISR(_core4_, 51)
#endif /* OSEE_TC_CORE4_51_ISR_CAT */
#if (defined(OSEE_TC_CORE4_52_ISR_CAT))
#if (OSEE_TC_CORE4_52_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 52)
#elif (OSEE_TC_CORE4_52_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 52)
#else
#error Invalid value for OSEE_TC_CORE4_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 52)
OSEE_DUMMY_ISR(_core4_, 52)
#endif /* OSEE_TC_CORE4_52_ISR_CAT */
#if (defined(OSEE_TC_CORE4_53_ISR_CAT))
#if (OSEE_TC_CORE4_53_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 53)
#elif (OSEE_TC_CORE4_53_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 53)
#else
#error Invalid value for OSEE_TC_CORE4_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 53)
OSEE_DUMMY_ISR(_core4_, 53)
#endif /* OSEE_TC_CORE4_53_ISR_CAT */
#if (defined(OSEE_TC_CORE4_54_ISR_CAT))
#if (OSEE_TC_CORE4_54_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 54)
#elif (OSEE_TC_CORE4_54_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 54)
#else
#error Invalid value for OSEE_TC_CORE4_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 54)
OSEE_DUMMY_ISR(_core4_, 54)
#endif /* OSEE_TC_CORE4_54_ISR_CAT */
#if (defined(OSEE_TC_CORE4_55_ISR_CAT))
#if (OSEE_TC_CORE4_55_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 55)
#elif (OSEE_TC_CORE4_55_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 55)
#else
#error Invalid value for OSEE_TC_CORE4_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 55)
OSEE_DUMMY_ISR(_core4_, 55)
#endif /* OSEE_TC_CORE4_55_ISR_CAT */
#if (defined(OSEE_TC_CORE4_56_ISR_CAT))
#if (OSEE_TC_CORE4_56_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 56)
#elif (OSEE_TC_CORE4_56_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 56)
#else
#error Invalid value for OSEE_TC_CORE4_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 56)
OSEE_DUMMY_ISR(_core4_, 56)
#endif /* OSEE_TC_CORE4_56_ISR_CAT */
#if (defined(OSEE_TC_CORE4_57_ISR_CAT))
#if (OSEE_TC_CORE4_57_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 57)
#elif (OSEE_TC_CORE4_57_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 57)
#else
#error Invalid value for OSEE_TC_CORE4_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 57)
OSEE_DUMMY_ISR(_core4_, 57)
#endif /* OSEE_TC_CORE4_57_ISR_CAT */
#if (defined(OSEE_TC_CORE4_58_ISR_CAT))
#if (OSEE_TC_CORE4_58_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 58)
#elif (OSEE_TC_CORE4_58_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 58)
#else
#error Invalid value for OSEE_TC_CORE4_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 58)
OSEE_DUMMY_ISR(_core4_, 58)
#endif /* OSEE_TC_CORE4_58_ISR_CAT */
#if (defined(OSEE_TC_CORE4_59_ISR_CAT))
#if (OSEE_TC_CORE4_59_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 59)
#elif (OSEE_TC_CORE4_59_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 59)
#else
#error Invalid value for OSEE_TC_CORE4_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 59)
OSEE_DUMMY_ISR(_core4_, 59)
#endif /* OSEE_TC_CORE4_59_ISR_CAT */
#if (defined(OSEE_TC_CORE4_60_ISR_CAT))
#if (OSEE_TC_CORE4_60_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 60)
#elif (OSEE_TC_CORE4_60_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 60)
#else
#error Invalid value for OSEE_TC_CORE4_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 60)
OSEE_DUMMY_ISR(_core4_, 60)
#endif /* OSEE_TC_CORE4_60_ISR_CAT */
#if (defined(OSEE_TC_CORE4_61_ISR_CAT))
#if (OSEE_TC_CORE4_61_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 61)
#elif (OSEE_TC_CORE4_61_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 61)
#else
#error Invalid value for OSEE_TC_CORE4_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 61)
OSEE_DUMMY_ISR(_core4_, 61)
#endif /* OSEE_TC_CORE4_61_ISR_CAT */
#if (defined(OSEE_TC_CORE4_62_ISR_CAT))
#if (OSEE_TC_CORE4_62_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 62)
#elif (OSEE_TC_CORE4_62_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 62)
#else
#error Invalid value for OSEE_TC_CORE4_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 62)
OSEE_DUMMY_ISR(_core4_, 62)
#endif /* OSEE_TC_CORE4_62_ISR_CAT */
#if (defined(OSEE_TC_CORE4_63_ISR_CAT))
#if (OSEE_TC_CORE4_63_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 63)
#elif (OSEE_TC_CORE4_63_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 63)
#else
#error Invalid value for OSEE_TC_CORE4_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 63)
OSEE_DUMMY_ISR(_core4_, 63)
#endif /* OSEE_TC_CORE4_63_ISR_CAT */
#if (defined(OSEE_TC_CORE4_64_ISR_CAT))
#if (OSEE_TC_CORE4_64_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 64)
#elif (OSEE_TC_CORE4_64_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 64)
#else
#error Invalid value for OSEE_TC_CORE4_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 64)
OSEE_DUMMY_ISR(_core4_, 64)
#endif /* OSEE_TC_CORE4_64_ISR_CAT */
#if (defined(OSEE_TC_CORE4_65_ISR_CAT))
#if (OSEE_TC_CORE4_65_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 65)
#elif (OSEE_TC_CORE4_65_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 65)
#else
#error Invalid value for OSEE_TC_CORE4_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 65)
OSEE_DUMMY_ISR(_core4_, 65)
#endif /* OSEE_TC_CORE4_65_ISR_CAT */
#if (defined(OSEE_TC_CORE4_66_ISR_CAT))
#if (OSEE_TC_CORE4_66_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 66)
#elif (OSEE_TC_CORE4_66_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 66)
#else
#error Invalid value for OSEE_TC_CORE4_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 66)
OSEE_DUMMY_ISR(_core4_, 66)
#endif /* OSEE_TC_CORE4_66_ISR_CAT */
#if (defined(OSEE_TC_CORE4_67_ISR_CAT))
#if (OSEE_TC_CORE4_67_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 67)
#elif (OSEE_TC_CORE4_67_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 67)
#else
#error Invalid value for OSEE_TC_CORE4_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 67)
OSEE_DUMMY_ISR(_core4_, 67)
#endif /* OSEE_TC_CORE4_67_ISR_CAT */
#if (defined(OSEE_TC_CORE4_68_ISR_CAT))
#if (OSEE_TC_CORE4_68_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 68)
#elif (OSEE_TC_CORE4_68_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 68)
#else
#error Invalid value for OSEE_TC_CORE4_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 68)
OSEE_DUMMY_ISR(_core4_, 68)
#endif /* OSEE_TC_CORE4_68_ISR_CAT */
#if (defined(OSEE_TC_CORE4_69_ISR_CAT))
#if (OSEE_TC_CORE4_69_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 69)
#elif (OSEE_TC_CORE4_69_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 69)
#else
#error Invalid value for OSEE_TC_CORE4_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 69)
OSEE_DUMMY_ISR(_core4_, 69)
#endif /* OSEE_TC_CORE4_69_ISR_CAT */
#if (defined(OSEE_TC_CORE4_70_ISR_CAT))
#if (OSEE_TC_CORE4_70_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 70)
#elif (OSEE_TC_CORE4_70_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 70)
#else
#error Invalid value for OSEE_TC_CORE4_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 70)
OSEE_DUMMY_ISR(_core4_, 70)
#endif /* OSEE_TC_CORE4_70_ISR_CAT */
#if (defined(OSEE_TC_CORE4_71_ISR_CAT))
#if (OSEE_TC_CORE4_71_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 71)
#elif (OSEE_TC_CORE4_71_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 71)
#else
#error Invalid value for OSEE_TC_CORE4_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 71)
OSEE_DUMMY_ISR(_core4_, 71)
#endif /* OSEE_TC_CORE4_71_ISR_CAT */
#if (defined(OSEE_TC_CORE4_72_ISR_CAT))
#if (OSEE_TC_CORE4_72_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 72)
#elif (OSEE_TC_CORE4_72_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 72)
#else
#error Invalid value for OSEE_TC_CORE4_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 72)
OSEE_DUMMY_ISR(_core4_, 72)
#endif /* OSEE_TC_CORE4_72_ISR_CAT */
#if (defined(OSEE_TC_CORE4_73_ISR_CAT))
#if (OSEE_TC_CORE4_73_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 73)
#elif (OSEE_TC_CORE4_73_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 73)
#else
#error Invalid value for OSEE_TC_CORE4_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 73)
OSEE_DUMMY_ISR(_core4_, 73)
#endif /* OSEE_TC_CORE4_73_ISR_CAT */
#if (defined(OSEE_TC_CORE4_74_ISR_CAT))
#if (OSEE_TC_CORE4_74_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 74)
#elif (OSEE_TC_CORE4_74_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 74)
#else
#error Invalid value for OSEE_TC_CORE4_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 74)
OSEE_DUMMY_ISR(_core4_, 74)
#endif /* OSEE_TC_CORE4_74_ISR_CAT */
#if (defined(OSEE_TC_CORE4_75_ISR_CAT))
#if (OSEE_TC_CORE4_75_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 75)
#elif (OSEE_TC_CORE4_75_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 75)
#else
#error Invalid value for OSEE_TC_CORE4_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 75)
OSEE_DUMMY_ISR(_core4_, 75)
#endif /* OSEE_TC_CORE4_75_ISR_CAT */
#if (defined(OSEE_TC_CORE4_76_ISR_CAT))
#if (OSEE_TC_CORE4_76_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 76)
#elif (OSEE_TC_CORE4_76_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 76)
#else
#error Invalid value for OSEE_TC_CORE4_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 76)
OSEE_DUMMY_ISR(_core4_, 76)
#endif /* OSEE_TC_CORE4_76_ISR_CAT */
#if (defined(OSEE_TC_CORE4_77_ISR_CAT))
#if (OSEE_TC_CORE4_77_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 77)
#elif (OSEE_TC_CORE4_77_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 77)
#else
#error Invalid value for OSEE_TC_CORE4_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 77)
OSEE_DUMMY_ISR(_core4_, 77)
#endif /* OSEE_TC_CORE4_77_ISR_CAT */
#if (defined(OSEE_TC_CORE4_78_ISR_CAT))
#if (OSEE_TC_CORE4_78_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 78)
#elif (OSEE_TC_CORE4_78_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 78)
#else
#error Invalid value for OSEE_TC_CORE4_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 78)
OSEE_DUMMY_ISR(_core4_, 78)
#endif /* OSEE_TC_CORE4_78_ISR_CAT */
#if (defined(OSEE_TC_CORE4_79_ISR_CAT))
#if (OSEE_TC_CORE4_79_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 79)
#elif (OSEE_TC_CORE4_79_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 79)
#else
#error Invalid value for OSEE_TC_CORE4_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 79)
OSEE_DUMMY_ISR(_core4_, 79)
#endif /* OSEE_TC_CORE4_79_ISR_CAT */
#if (defined(OSEE_TC_CORE4_80_ISR_CAT))
#if (OSEE_TC_CORE4_80_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 80)
#elif (OSEE_TC_CORE4_80_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 80)
#else
#error Invalid value for OSEE_TC_CORE4_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 80)
OSEE_DUMMY_ISR(_core4_, 80)
#endif /* OSEE_TC_CORE4_80_ISR_CAT */
#if (defined(OSEE_TC_CORE4_81_ISR_CAT))
#if (OSEE_TC_CORE4_81_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 81)
#elif (OSEE_TC_CORE4_81_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 81)
#else
#error Invalid value for OSEE_TC_CORE4_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 81)
OSEE_DUMMY_ISR(_core4_, 81)
#endif /* OSEE_TC_CORE4_81_ISR_CAT */
#if (defined(OSEE_TC_CORE4_82_ISR_CAT))
#if (OSEE_TC_CORE4_82_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 82)
#elif (OSEE_TC_CORE4_82_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 82)
#else
#error Invalid value for OSEE_TC_CORE4_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 82)
OSEE_DUMMY_ISR(_core4_, 82)
#endif /* OSEE_TC_CORE4_82_ISR_CAT */
#if (defined(OSEE_TC_CORE4_83_ISR_CAT))
#if (OSEE_TC_CORE4_83_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 83)
#elif (OSEE_TC_CORE4_83_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 83)
#else
#error Invalid value for OSEE_TC_CORE4_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 83)
OSEE_DUMMY_ISR(_core4_, 83)
#endif /* OSEE_TC_CORE4_83_ISR_CAT */
#if (defined(OSEE_TC_CORE4_84_ISR_CAT))
#if (OSEE_TC_CORE4_84_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 84)
#elif (OSEE_TC_CORE4_84_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 84)
#else
#error Invalid value for OSEE_TC_CORE4_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 84)
OSEE_DUMMY_ISR(_core4_, 84)
#endif /* OSEE_TC_CORE4_84_ISR_CAT */
#if (defined(OSEE_TC_CORE4_85_ISR_CAT))
#if (OSEE_TC_CORE4_85_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 85)
#elif (OSEE_TC_CORE4_85_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 85)
#else
#error Invalid value for OSEE_TC_CORE4_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 85)
OSEE_DUMMY_ISR(_core4_, 85)
#endif /* OSEE_TC_CORE4_85_ISR_CAT */
#if (defined(OSEE_TC_CORE4_86_ISR_CAT))
#if (OSEE_TC_CORE4_86_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 86)
#elif (OSEE_TC_CORE4_86_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 86)
#else
#error Invalid value for OSEE_TC_CORE4_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 86)
OSEE_DUMMY_ISR(_core4_, 86)
#endif /* OSEE_TC_CORE4_86_ISR_CAT */
#if (defined(OSEE_TC_CORE4_87_ISR_CAT))
#if (OSEE_TC_CORE4_87_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 87)
#elif (OSEE_TC_CORE4_87_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 87)
#else
#error Invalid value for OSEE_TC_CORE4_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 87)
OSEE_DUMMY_ISR(_core4_, 87)
#endif /* OSEE_TC_CORE4_87_ISR_CAT */
#if (defined(OSEE_TC_CORE4_88_ISR_CAT))
#if (OSEE_TC_CORE4_88_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 88)
#elif (OSEE_TC_CORE4_88_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 88)
#else
#error Invalid value for OSEE_TC_CORE4_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 88)
OSEE_DUMMY_ISR(_core4_, 88)
#endif /* OSEE_TC_CORE4_88_ISR_CAT */
#if (defined(OSEE_TC_CORE4_89_ISR_CAT))
#if (OSEE_TC_CORE4_89_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 89)
#elif (OSEE_TC_CORE4_89_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 89)
#else
#error Invalid value for OSEE_TC_CORE4_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 89)
OSEE_DUMMY_ISR(_core4_, 89)
#endif /* OSEE_TC_CORE4_89_ISR_CAT */
#if (defined(OSEE_TC_CORE4_90_ISR_CAT))
#if (OSEE_TC_CORE4_90_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 90)
#elif (OSEE_TC_CORE4_90_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 90)
#else
#error Invalid value for OSEE_TC_CORE4_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 90)
OSEE_DUMMY_ISR(_core4_, 90)
#endif /* OSEE_TC_CORE4_90_ISR_CAT */
#if (defined(OSEE_TC_CORE4_91_ISR_CAT))
#if (OSEE_TC_CORE4_91_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 91)
#elif (OSEE_TC_CORE4_91_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 91)
#else
#error Invalid value for OSEE_TC_CORE4_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 91)
OSEE_DUMMY_ISR(_core4_, 91)
#endif /* OSEE_TC_CORE4_91_ISR_CAT */
#if (defined(OSEE_TC_CORE4_92_ISR_CAT))
#if (OSEE_TC_CORE4_92_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 92)
#elif (OSEE_TC_CORE4_92_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 92)
#else
#error Invalid value for OSEE_TC_CORE4_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 92)
OSEE_DUMMY_ISR(_core4_, 92)
#endif /* OSEE_TC_CORE4_92_ISR_CAT */
#if (defined(OSEE_TC_CORE4_93_ISR_CAT))
#if (OSEE_TC_CORE4_93_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 93)
#elif (OSEE_TC_CORE4_93_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 93)
#else
#error Invalid value for OSEE_TC_CORE4_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 93)
OSEE_DUMMY_ISR(_core4_, 93)
#endif /* OSEE_TC_CORE4_93_ISR_CAT */
#if (defined(OSEE_TC_CORE4_94_ISR_CAT))
#if (OSEE_TC_CORE4_94_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 94)
#elif (OSEE_TC_CORE4_94_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 94)
#else
#error Invalid value for OSEE_TC_CORE4_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 94)
OSEE_DUMMY_ISR(_core4_, 94)
#endif /* OSEE_TC_CORE4_94_ISR_CAT */
#if (defined(OSEE_TC_CORE4_95_ISR_CAT))
#if (OSEE_TC_CORE4_95_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 95)
#elif (OSEE_TC_CORE4_95_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 95)
#else
#error Invalid value for OSEE_TC_CORE4_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 95)
OSEE_DUMMY_ISR(_core4_, 95)
#endif /* OSEE_TC_CORE4_95_ISR_CAT */
#if (defined(OSEE_TC_CORE4_96_ISR_CAT))
#if (OSEE_TC_CORE4_96_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 96)
#elif (OSEE_TC_CORE4_96_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 96)
#else
#error Invalid value for OSEE_TC_CORE4_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 96)
OSEE_DUMMY_ISR(_core4_, 96)
#endif /* OSEE_TC_CORE4_96_ISR_CAT */
#if (defined(OSEE_TC_CORE4_97_ISR_CAT))
#if (OSEE_TC_CORE4_97_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 97)
#elif (OSEE_TC_CORE4_97_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 97)
#else
#error Invalid value for OSEE_TC_CORE4_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 97)
OSEE_DUMMY_ISR(_core4_, 97)
#endif /* OSEE_TC_CORE4_97_ISR_CAT */
#if (defined(OSEE_TC_CORE4_98_ISR_CAT))
#if (OSEE_TC_CORE4_98_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 98)
#elif (OSEE_TC_CORE4_98_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 98)
#else
#error Invalid value for OSEE_TC_CORE4_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 98)
OSEE_DUMMY_ISR(_core4_, 98)
#endif /* OSEE_TC_CORE4_98_ISR_CAT */
#if (defined(OSEE_TC_CORE4_99_ISR_CAT))
#if (OSEE_TC_CORE4_99_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 99)
#elif (OSEE_TC_CORE4_99_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 99)
#else
#error Invalid value for OSEE_TC_CORE4_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 99)
OSEE_DUMMY_ISR(_core4_, 99)
#endif /* OSEE_TC_CORE4_99_ISR_CAT */
#if (defined(OSEE_TC_CORE4_100_ISR_CAT))
#if (OSEE_TC_CORE4_100_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 100)
#elif (OSEE_TC_CORE4_100_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 100)
#else
#error Invalid value for OSEE_TC_CORE4_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 100)
OSEE_DUMMY_ISR(_core4_, 100)
#endif /* OSEE_TC_CORE4_100_ISR_CAT */
#if (defined(OSEE_TC_CORE4_101_ISR_CAT))
#if (OSEE_TC_CORE4_101_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 101)
#elif (OSEE_TC_CORE4_101_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 101)
#else
#error Invalid value for OSEE_TC_CORE4_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 101)
OSEE_DUMMY_ISR(_core4_, 101)
#endif /* OSEE_TC_CORE4_101_ISR_CAT */
#if (defined(OSEE_TC_CORE4_102_ISR_CAT))
#if (OSEE_TC_CORE4_102_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 102)
#elif (OSEE_TC_CORE4_102_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 102)
#else
#error Invalid value for OSEE_TC_CORE4_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 102)
OSEE_DUMMY_ISR(_core4_, 102)
#endif /* OSEE_TC_CORE4_102_ISR_CAT */
#if (defined(OSEE_TC_CORE4_103_ISR_CAT))
#if (OSEE_TC_CORE4_103_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 103)
#elif (OSEE_TC_CORE4_103_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 103)
#else
#error Invalid value for OSEE_TC_CORE4_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 103)
OSEE_DUMMY_ISR(_core4_, 103)
#endif /* OSEE_TC_CORE4_103_ISR_CAT */
#if (defined(OSEE_TC_CORE4_104_ISR_CAT))
#if (OSEE_TC_CORE4_104_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 104)
#elif (OSEE_TC_CORE4_104_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 104)
#else
#error Invalid value for OSEE_TC_CORE4_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 104)
OSEE_DUMMY_ISR(_core4_, 104)
#endif /* OSEE_TC_CORE4_104_ISR_CAT */
#if (defined(OSEE_TC_CORE4_105_ISR_CAT))
#if (OSEE_TC_CORE4_105_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 105)
#elif (OSEE_TC_CORE4_105_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 105)
#else
#error Invalid value for OSEE_TC_CORE4_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 105)
OSEE_DUMMY_ISR(_core4_, 105)
#endif /* OSEE_TC_CORE4_105_ISR_CAT */
#if (defined(OSEE_TC_CORE4_106_ISR_CAT))
#if (OSEE_TC_CORE4_106_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 106)
#elif (OSEE_TC_CORE4_106_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 106)
#else
#error Invalid value for OSEE_TC_CORE4_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 106)
OSEE_DUMMY_ISR(_core4_, 106)
#endif /* OSEE_TC_CORE4_106_ISR_CAT */
#if (defined(OSEE_TC_CORE4_107_ISR_CAT))
#if (OSEE_TC_CORE4_107_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 107)
#elif (OSEE_TC_CORE4_107_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 107)
#else
#error Invalid value for OSEE_TC_CORE4_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 107)
OSEE_DUMMY_ISR(_core4_, 107)
#endif /* OSEE_TC_CORE4_107_ISR_CAT */
#if (defined(OSEE_TC_CORE4_108_ISR_CAT))
#if (OSEE_TC_CORE4_108_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 108)
#elif (OSEE_TC_CORE4_108_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 108)
#else
#error Invalid value for OSEE_TC_CORE4_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 108)
OSEE_DUMMY_ISR(_core4_, 108)
#endif /* OSEE_TC_CORE4_108_ISR_CAT */
#if (defined(OSEE_TC_CORE4_109_ISR_CAT))
#if (OSEE_TC_CORE4_109_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 109)
#elif (OSEE_TC_CORE4_109_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 109)
#else
#error Invalid value for OSEE_TC_CORE4_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 109)
OSEE_DUMMY_ISR(_core4_, 109)
#endif /* OSEE_TC_CORE4_109_ISR_CAT */
#if (defined(OSEE_TC_CORE4_110_ISR_CAT))
#if (OSEE_TC_CORE4_110_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 110)
#elif (OSEE_TC_CORE4_110_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 110)
#else
#error Invalid value for OSEE_TC_CORE4_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 110)
OSEE_DUMMY_ISR(_core4_, 110)
#endif /* OSEE_TC_CORE4_110_ISR_CAT */
#if (defined(OSEE_TC_CORE4_111_ISR_CAT))
#if (OSEE_TC_CORE4_111_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 111)
#elif (OSEE_TC_CORE4_111_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 111)
#else
#error Invalid value for OSEE_TC_CORE4_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 111)
OSEE_DUMMY_ISR(_core4_, 111)
#endif /* OSEE_TC_CORE4_111_ISR_CAT */
#if (defined(OSEE_TC_CORE4_112_ISR_CAT))
#if (OSEE_TC_CORE4_112_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 112)
#elif (OSEE_TC_CORE4_112_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 112)
#else
#error Invalid value for OSEE_TC_CORE4_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 112)
OSEE_DUMMY_ISR(_core4_, 112)
#endif /* OSEE_TC_CORE4_112_ISR_CAT */
#if (defined(OSEE_TC_CORE4_113_ISR_CAT))
#if (OSEE_TC_CORE4_113_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 113)
#elif (OSEE_TC_CORE4_113_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 113)
#else
#error Invalid value for OSEE_TC_CORE4_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 113)
OSEE_DUMMY_ISR(_core4_, 113)
#endif /* OSEE_TC_CORE4_113_ISR_CAT */
#if (defined(OSEE_TC_CORE4_114_ISR_CAT))
#if (OSEE_TC_CORE4_114_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 114)
#elif (OSEE_TC_CORE4_114_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 114)
#else
#error Invalid value for OSEE_TC_CORE4_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 114)
OSEE_DUMMY_ISR(_core4_, 114)
#endif /* OSEE_TC_CORE4_114_ISR_CAT */
#if (defined(OSEE_TC_CORE4_115_ISR_CAT))
#if (OSEE_TC_CORE4_115_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 115)
#elif (OSEE_TC_CORE4_115_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 115)
#else
#error Invalid value for OSEE_TC_CORE4_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 115)
OSEE_DUMMY_ISR(_core4_, 115)
#endif /* OSEE_TC_CORE4_115_ISR_CAT */
#if (defined(OSEE_TC_CORE4_116_ISR_CAT))
#if (OSEE_TC_CORE4_116_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 116)
#elif (OSEE_TC_CORE4_116_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 116)
#else
#error Invalid value for OSEE_TC_CORE4_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 116)
OSEE_DUMMY_ISR(_core4_, 116)
#endif /* OSEE_TC_CORE4_116_ISR_CAT */
#if (defined(OSEE_TC_CORE4_117_ISR_CAT))
#if (OSEE_TC_CORE4_117_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 117)
#elif (OSEE_TC_CORE4_117_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 117)
#else
#error Invalid value for OSEE_TC_CORE4_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 117)
OSEE_DUMMY_ISR(_core4_, 117)
#endif /* OSEE_TC_CORE4_117_ISR_CAT */
#if (defined(OSEE_TC_CORE4_118_ISR_CAT))
#if (OSEE_TC_CORE4_118_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 118)
#elif (OSEE_TC_CORE4_118_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 118)
#else
#error Invalid value for OSEE_TC_CORE4_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 118)
OSEE_DUMMY_ISR(_core4_, 118)
#endif /* OSEE_TC_CORE4_118_ISR_CAT */
#if (defined(OSEE_TC_CORE4_119_ISR_CAT))
#if (OSEE_TC_CORE4_119_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 119)
#elif (OSEE_TC_CORE4_119_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 119)
#else
#error Invalid value for OSEE_TC_CORE4_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 119)
OSEE_DUMMY_ISR(_core4_, 119)
#endif /* OSEE_TC_CORE4_119_ISR_CAT */
#if (defined(OSEE_TC_CORE4_120_ISR_CAT))
#if (OSEE_TC_CORE4_120_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 120)
#elif (OSEE_TC_CORE4_120_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 120)
#else
#error Invalid value for OSEE_TC_CORE4_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 120)
OSEE_DUMMY_ISR(_core4_, 120)
#endif /* OSEE_TC_CORE4_120_ISR_CAT */
#if (defined(OSEE_TC_CORE4_121_ISR_CAT))
#if (OSEE_TC_CORE4_121_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 121)
#elif (OSEE_TC_CORE4_121_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 121)
#else
#error Invalid value for OSEE_TC_CORE4_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 121)
OSEE_DUMMY_ISR(_core4_, 121)
#endif /* OSEE_TC_CORE4_121_ISR_CAT */
#if (defined(OSEE_TC_CORE4_122_ISR_CAT))
#if (OSEE_TC_CORE4_122_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 122)
#elif (OSEE_TC_CORE4_122_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 122)
#else
#error Invalid value for OSEE_TC_CORE4_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 122)
OSEE_DUMMY_ISR(_core4_, 122)
#endif /* OSEE_TC_CORE4_122_ISR_CAT */
#if (defined(OSEE_TC_CORE4_123_ISR_CAT))
#if (OSEE_TC_CORE4_123_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 123)
#elif (OSEE_TC_CORE4_123_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 123)
#else
#error Invalid value for OSEE_TC_CORE4_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 123)
OSEE_DUMMY_ISR(_core4_, 123)
#endif /* OSEE_TC_CORE4_123_ISR_CAT */
#if (defined(OSEE_TC_CORE4_124_ISR_CAT))
#if (OSEE_TC_CORE4_124_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 124)
#elif (OSEE_TC_CORE4_124_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 124)
#else
#error Invalid value for OSEE_TC_CORE4_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 124)
OSEE_DUMMY_ISR(_core4_, 124)
#endif /* OSEE_TC_CORE4_124_ISR_CAT */
#if (defined(OSEE_TC_CORE4_125_ISR_CAT))
#if (OSEE_TC_CORE4_125_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 125)
#elif (OSEE_TC_CORE4_125_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 125)
#else
#error Invalid value for OSEE_TC_CORE4_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 125)
OSEE_DUMMY_ISR(_core4_, 125)
#endif /* OSEE_TC_CORE4_125_ISR_CAT */
#if (defined(OSEE_TC_CORE4_126_ISR_CAT))
#if (OSEE_TC_CORE4_126_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 126)
#elif (OSEE_TC_CORE4_126_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 126)
#else
#error Invalid value for OSEE_TC_CORE4_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 126)
OSEE_DUMMY_ISR(_core4_, 126)
#endif /* OSEE_TC_CORE4_126_ISR_CAT */
#if (defined(OSEE_TC_CORE4_127_ISR_CAT))
#if (OSEE_TC_CORE4_127_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 127)
#elif (OSEE_TC_CORE4_127_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 127)
#else
#error Invalid value for OSEE_TC_CORE4_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 127)
OSEE_DUMMY_ISR(_core4_, 127)
#endif /* OSEE_TC_CORE4_127_ISR_CAT */
#if (defined(OSEE_TC_CORE4_128_ISR_CAT))
#if (OSEE_TC_CORE4_128_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 128)
#elif (OSEE_TC_CORE4_128_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 128)
#else
#error Invalid value for OSEE_TC_CORE4_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 128)
OSEE_DUMMY_ISR(_core4_, 128)
#endif /* OSEE_TC_CORE4_128_ISR_CAT */
#if (defined(OSEE_TC_CORE4_129_ISR_CAT))
#if (OSEE_TC_CORE4_129_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 129)
#elif (OSEE_TC_CORE4_129_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 129)
#else
#error Invalid value for OSEE_TC_CORE4_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 129)
OSEE_DUMMY_ISR(_core4_, 129)
#endif /* OSEE_TC_CORE4_129_ISR_CAT */
#if (defined(OSEE_TC_CORE4_130_ISR_CAT))
#if (OSEE_TC_CORE4_130_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 130)
#elif (OSEE_TC_CORE4_130_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 130)
#else
#error Invalid value for OSEE_TC_CORE4_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 130)
OSEE_DUMMY_ISR(_core4_, 130)
#endif /* OSEE_TC_CORE4_130_ISR_CAT */
#if (defined(OSEE_TC_CORE4_131_ISR_CAT))
#if (OSEE_TC_CORE4_131_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 131)
#elif (OSEE_TC_CORE4_131_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 131)
#else
#error Invalid value for OSEE_TC_CORE4_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 131)
OSEE_DUMMY_ISR(_core4_, 131)
#endif /* OSEE_TC_CORE4_131_ISR_CAT */
#if (defined(OSEE_TC_CORE4_132_ISR_CAT))
#if (OSEE_TC_CORE4_132_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 132)
#elif (OSEE_TC_CORE4_132_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 132)
#else
#error Invalid value for OSEE_TC_CORE4_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 132)
OSEE_DUMMY_ISR(_core4_, 132)
#endif /* OSEE_TC_CORE4_132_ISR_CAT */
#if (defined(OSEE_TC_CORE4_133_ISR_CAT))
#if (OSEE_TC_CORE4_133_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 133)
#elif (OSEE_TC_CORE4_133_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 133)
#else
#error Invalid value for OSEE_TC_CORE4_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 133)
OSEE_DUMMY_ISR(_core4_, 133)
#endif /* OSEE_TC_CORE4_133_ISR_CAT */
#if (defined(OSEE_TC_CORE4_134_ISR_CAT))
#if (OSEE_TC_CORE4_134_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 134)
#elif (OSEE_TC_CORE4_134_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 134)
#else
#error Invalid value for OSEE_TC_CORE4_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 134)
OSEE_DUMMY_ISR(_core4_, 134)
#endif /* OSEE_TC_CORE4_134_ISR_CAT */
#if (defined(OSEE_TC_CORE4_135_ISR_CAT))
#if (OSEE_TC_CORE4_135_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 135)
#elif (OSEE_TC_CORE4_135_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 135)
#else
#error Invalid value for OSEE_TC_CORE4_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 135)
OSEE_DUMMY_ISR(_core4_, 135)
#endif /* OSEE_TC_CORE4_135_ISR_CAT */
#if (defined(OSEE_TC_CORE4_136_ISR_CAT))
#if (OSEE_TC_CORE4_136_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 136)
#elif (OSEE_TC_CORE4_136_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 136)
#else
#error Invalid value for OSEE_TC_CORE4_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 136)
OSEE_DUMMY_ISR(_core4_, 136)
#endif /* OSEE_TC_CORE4_136_ISR_CAT */
#if (defined(OSEE_TC_CORE4_137_ISR_CAT))
#if (OSEE_TC_CORE4_137_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 137)
#elif (OSEE_TC_CORE4_137_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 137)
#else
#error Invalid value for OSEE_TC_CORE4_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 137)
OSEE_DUMMY_ISR(_core4_, 137)
#endif /* OSEE_TC_CORE4_137_ISR_CAT */
#if (defined(OSEE_TC_CORE4_138_ISR_CAT))
#if (OSEE_TC_CORE4_138_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 138)
#elif (OSEE_TC_CORE4_138_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 138)
#else
#error Invalid value for OSEE_TC_CORE4_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 138)
OSEE_DUMMY_ISR(_core4_, 138)
#endif /* OSEE_TC_CORE4_138_ISR_CAT */
#if (defined(OSEE_TC_CORE4_139_ISR_CAT))
#if (OSEE_TC_CORE4_139_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 139)
#elif (OSEE_TC_CORE4_139_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 139)
#else
#error Invalid value for OSEE_TC_CORE4_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 139)
OSEE_DUMMY_ISR(_core4_, 139)
#endif /* OSEE_TC_CORE4_139_ISR_CAT */
#if (defined(OSEE_TC_CORE4_140_ISR_CAT))
#if (OSEE_TC_CORE4_140_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 140)
#elif (OSEE_TC_CORE4_140_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 140)
#else
#error Invalid value for OSEE_TC_CORE4_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 140)
OSEE_DUMMY_ISR(_core4_, 140)
#endif /* OSEE_TC_CORE4_140_ISR_CAT */
#if (defined(OSEE_TC_CORE4_141_ISR_CAT))
#if (OSEE_TC_CORE4_141_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 141)
#elif (OSEE_TC_CORE4_141_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 141)
#else
#error Invalid value for OSEE_TC_CORE4_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 141)
OSEE_DUMMY_ISR(_core4_, 141)
#endif /* OSEE_TC_CORE4_141_ISR_CAT */
#if (defined(OSEE_TC_CORE4_142_ISR_CAT))
#if (OSEE_TC_CORE4_142_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 142)
#elif (OSEE_TC_CORE4_142_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 142)
#else
#error Invalid value for OSEE_TC_CORE4_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 142)
OSEE_DUMMY_ISR(_core4_, 142)
#endif /* OSEE_TC_CORE4_142_ISR_CAT */
#if (defined(OSEE_TC_CORE4_143_ISR_CAT))
#if (OSEE_TC_CORE4_143_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 143)
#elif (OSEE_TC_CORE4_143_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 143)
#else
#error Invalid value for OSEE_TC_CORE4_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 143)
OSEE_DUMMY_ISR(_core4_, 143)
#endif /* OSEE_TC_CORE4_143_ISR_CAT */
#if (defined(OSEE_TC_CORE4_144_ISR_CAT))
#if (OSEE_TC_CORE4_144_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 144)
#elif (OSEE_TC_CORE4_144_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 144)
#else
#error Invalid value for OSEE_TC_CORE4_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 144)
OSEE_DUMMY_ISR(_core4_, 144)
#endif /* OSEE_TC_CORE4_144_ISR_CAT */
#if (defined(OSEE_TC_CORE4_145_ISR_CAT))
#if (OSEE_TC_CORE4_145_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 145)
#elif (OSEE_TC_CORE4_145_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 145)
#else
#error Invalid value for OSEE_TC_CORE4_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 145)
OSEE_DUMMY_ISR(_core4_, 145)
#endif /* OSEE_TC_CORE4_145_ISR_CAT */
#if (defined(OSEE_TC_CORE4_146_ISR_CAT))
#if (OSEE_TC_CORE4_146_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 146)
#elif (OSEE_TC_CORE4_146_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 146)
#else
#error Invalid value for OSEE_TC_CORE4_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 146)
OSEE_DUMMY_ISR(_core4_, 146)
#endif /* OSEE_TC_CORE4_146_ISR_CAT */
#if (defined(OSEE_TC_CORE4_147_ISR_CAT))
#if (OSEE_TC_CORE4_147_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 147)
#elif (OSEE_TC_CORE4_147_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 147)
#else
#error Invalid value for OSEE_TC_CORE4_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 147)
OSEE_DUMMY_ISR(_core4_, 147)
#endif /* OSEE_TC_CORE4_147_ISR_CAT */
#if (defined(OSEE_TC_CORE4_148_ISR_CAT))
#if (OSEE_TC_CORE4_148_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 148)
#elif (OSEE_TC_CORE4_148_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 148)
#else
#error Invalid value for OSEE_TC_CORE4_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 148)
OSEE_DUMMY_ISR(_core4_, 148)
#endif /* OSEE_TC_CORE4_148_ISR_CAT */
#if (defined(OSEE_TC_CORE4_149_ISR_CAT))
#if (OSEE_TC_CORE4_149_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 149)
#elif (OSEE_TC_CORE4_149_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 149)
#else
#error Invalid value for OSEE_TC_CORE4_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 149)
OSEE_DUMMY_ISR(_core4_, 149)
#endif /* OSEE_TC_CORE4_149_ISR_CAT */
#if (defined(OSEE_TC_CORE4_150_ISR_CAT))
#if (OSEE_TC_CORE4_150_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 150)
#elif (OSEE_TC_CORE4_150_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 150)
#else
#error Invalid value for OSEE_TC_CORE4_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 150)
OSEE_DUMMY_ISR(_core4_, 150)
#endif /* OSEE_TC_CORE4_150_ISR_CAT */
#if (defined(OSEE_TC_CORE4_151_ISR_CAT))
#if (OSEE_TC_CORE4_151_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 151)
#elif (OSEE_TC_CORE4_151_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 151)
#else
#error Invalid value for OSEE_TC_CORE4_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 151)
OSEE_DUMMY_ISR(_core4_, 151)
#endif /* OSEE_TC_CORE4_151_ISR_CAT */
#if (defined(OSEE_TC_CORE4_152_ISR_CAT))
#if (OSEE_TC_CORE4_152_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 152)
#elif (OSEE_TC_CORE4_152_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 152)
#else
#error Invalid value for OSEE_TC_CORE4_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 152)
OSEE_DUMMY_ISR(_core4_, 152)
#endif /* OSEE_TC_CORE4_152_ISR_CAT */
#if (defined(OSEE_TC_CORE4_153_ISR_CAT))
#if (OSEE_TC_CORE4_153_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 153)
#elif (OSEE_TC_CORE4_153_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 153)
#else
#error Invalid value for OSEE_TC_CORE4_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 153)
OSEE_DUMMY_ISR(_core4_, 153)
#endif /* OSEE_TC_CORE4_153_ISR_CAT */
#if (defined(OSEE_TC_CORE4_154_ISR_CAT))
#if (OSEE_TC_CORE4_154_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 154)
#elif (OSEE_TC_CORE4_154_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 154)
#else
#error Invalid value for OSEE_TC_CORE4_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 154)
OSEE_DUMMY_ISR(_core4_, 154)
#endif /* OSEE_TC_CORE4_154_ISR_CAT */
#if (defined(OSEE_TC_CORE4_155_ISR_CAT))
#if (OSEE_TC_CORE4_155_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 155)
#elif (OSEE_TC_CORE4_155_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 155)
#else
#error Invalid value for OSEE_TC_CORE4_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 155)
OSEE_DUMMY_ISR(_core4_, 155)
#endif /* OSEE_TC_CORE4_155_ISR_CAT */
#if (defined(OSEE_TC_CORE4_156_ISR_CAT))
#if (OSEE_TC_CORE4_156_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 156)
#elif (OSEE_TC_CORE4_156_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 156)
#else
#error Invalid value for OSEE_TC_CORE4_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 156)
OSEE_DUMMY_ISR(_core4_, 156)
#endif /* OSEE_TC_CORE4_156_ISR_CAT */
#if (defined(OSEE_TC_CORE4_157_ISR_CAT))
#if (OSEE_TC_CORE4_157_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 157)
#elif (OSEE_TC_CORE4_157_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 157)
#else
#error Invalid value for OSEE_TC_CORE4_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 157)
OSEE_DUMMY_ISR(_core4_, 157)
#endif /* OSEE_TC_CORE4_157_ISR_CAT */
#if (defined(OSEE_TC_CORE4_158_ISR_CAT))
#if (OSEE_TC_CORE4_158_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 158)
#elif (OSEE_TC_CORE4_158_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 158)
#else
#error Invalid value for OSEE_TC_CORE4_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 158)
OSEE_DUMMY_ISR(_core4_, 158)
#endif /* OSEE_TC_CORE4_158_ISR_CAT */
#if (defined(OSEE_TC_CORE4_159_ISR_CAT))
#if (OSEE_TC_CORE4_159_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 159)
#elif (OSEE_TC_CORE4_159_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 159)
#else
#error Invalid value for OSEE_TC_CORE4_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 159)
OSEE_DUMMY_ISR(_core4_, 159)
#endif /* OSEE_TC_CORE4_159_ISR_CAT */
#if (defined(OSEE_TC_CORE4_160_ISR_CAT))
#if (OSEE_TC_CORE4_160_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 160)
#elif (OSEE_TC_CORE4_160_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 160)
#else
#error Invalid value for OSEE_TC_CORE4_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 160)
OSEE_DUMMY_ISR(_core4_, 160)
#endif /* OSEE_TC_CORE4_160_ISR_CAT */
#if (defined(OSEE_TC_CORE4_161_ISR_CAT))
#if (OSEE_TC_CORE4_161_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 161)
#elif (OSEE_TC_CORE4_161_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 161)
#else
#error Invalid value for OSEE_TC_CORE4_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 161)
OSEE_DUMMY_ISR(_core4_, 161)
#endif /* OSEE_TC_CORE4_161_ISR_CAT */
#if (defined(OSEE_TC_CORE4_162_ISR_CAT))
#if (OSEE_TC_CORE4_162_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 162)
#elif (OSEE_TC_CORE4_162_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 162)
#else
#error Invalid value for OSEE_TC_CORE4_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 162)
OSEE_DUMMY_ISR(_core4_, 162)
#endif /* OSEE_TC_CORE4_162_ISR_CAT */
#if (defined(OSEE_TC_CORE4_163_ISR_CAT))
#if (OSEE_TC_CORE4_163_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 163)
#elif (OSEE_TC_CORE4_163_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 163)
#else
#error Invalid value for OSEE_TC_CORE4_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 163)
OSEE_DUMMY_ISR(_core4_, 163)
#endif /* OSEE_TC_CORE4_163_ISR_CAT */
#if (defined(OSEE_TC_CORE4_164_ISR_CAT))
#if (OSEE_TC_CORE4_164_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 164)
#elif (OSEE_TC_CORE4_164_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 164)
#else
#error Invalid value for OSEE_TC_CORE4_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 164)
OSEE_DUMMY_ISR(_core4_, 164)
#endif /* OSEE_TC_CORE4_164_ISR_CAT */
#if (defined(OSEE_TC_CORE4_165_ISR_CAT))
#if (OSEE_TC_CORE4_165_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 165)
#elif (OSEE_TC_CORE4_165_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 165)
#else
#error Invalid value for OSEE_TC_CORE4_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 165)
OSEE_DUMMY_ISR(_core4_, 165)
#endif /* OSEE_TC_CORE4_165_ISR_CAT */
#if (defined(OSEE_TC_CORE4_166_ISR_CAT))
#if (OSEE_TC_CORE4_166_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 166)
#elif (OSEE_TC_CORE4_166_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 166)
#else
#error Invalid value for OSEE_TC_CORE4_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 166)
OSEE_DUMMY_ISR(_core4_, 166)
#endif /* OSEE_TC_CORE4_166_ISR_CAT */
#if (defined(OSEE_TC_CORE4_167_ISR_CAT))
#if (OSEE_TC_CORE4_167_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 167)
#elif (OSEE_TC_CORE4_167_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 167)
#else
#error Invalid value for OSEE_TC_CORE4_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 167)
OSEE_DUMMY_ISR(_core4_, 167)
#endif /* OSEE_TC_CORE4_167_ISR_CAT */
#if (defined(OSEE_TC_CORE4_168_ISR_CAT))
#if (OSEE_TC_CORE4_168_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 168)
#elif (OSEE_TC_CORE4_168_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 168)
#else
#error Invalid value for OSEE_TC_CORE4_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 168)
OSEE_DUMMY_ISR(_core4_, 168)
#endif /* OSEE_TC_CORE4_168_ISR_CAT */
#if (defined(OSEE_TC_CORE4_169_ISR_CAT))
#if (OSEE_TC_CORE4_169_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 169)
#elif (OSEE_TC_CORE4_169_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 169)
#else
#error Invalid value for OSEE_TC_CORE4_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 169)
OSEE_DUMMY_ISR(_core4_, 169)
#endif /* OSEE_TC_CORE4_169_ISR_CAT */
#if (defined(OSEE_TC_CORE4_170_ISR_CAT))
#if (OSEE_TC_CORE4_170_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 170)
#elif (OSEE_TC_CORE4_170_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 170)
#else
#error Invalid value for OSEE_TC_CORE4_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 170)
OSEE_DUMMY_ISR(_core4_, 170)
#endif /* OSEE_TC_CORE4_170_ISR_CAT */
#if (defined(OSEE_TC_CORE4_171_ISR_CAT))
#if (OSEE_TC_CORE4_171_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 171)
#elif (OSEE_TC_CORE4_171_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 171)
#else
#error Invalid value for OSEE_TC_CORE4_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 171)
OSEE_DUMMY_ISR(_core4_, 171)
#endif /* OSEE_TC_CORE4_171_ISR_CAT */
#if (defined(OSEE_TC_CORE4_172_ISR_CAT))
#if (OSEE_TC_CORE4_172_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 172)
#elif (OSEE_TC_CORE4_172_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 172)
#else
#error Invalid value for OSEE_TC_CORE4_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 172)
OSEE_DUMMY_ISR(_core4_, 172)
#endif /* OSEE_TC_CORE4_172_ISR_CAT */
#if (defined(OSEE_TC_CORE4_173_ISR_CAT))
#if (OSEE_TC_CORE4_173_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 173)
#elif (OSEE_TC_CORE4_173_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 173)
#else
#error Invalid value for OSEE_TC_CORE4_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 173)
OSEE_DUMMY_ISR(_core4_, 173)
#endif /* OSEE_TC_CORE4_173_ISR_CAT */
#if (defined(OSEE_TC_CORE4_174_ISR_CAT))
#if (OSEE_TC_CORE4_174_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 174)
#elif (OSEE_TC_CORE4_174_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 174)
#else
#error Invalid value for OSEE_TC_CORE4_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 174)
OSEE_DUMMY_ISR(_core4_, 174)
#endif /* OSEE_TC_CORE4_174_ISR_CAT */
#if (defined(OSEE_TC_CORE4_175_ISR_CAT))
#if (OSEE_TC_CORE4_175_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 175)
#elif (OSEE_TC_CORE4_175_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 175)
#else
#error Invalid value for OSEE_TC_CORE4_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 175)
OSEE_DUMMY_ISR(_core4_, 175)
#endif /* OSEE_TC_CORE4_175_ISR_CAT */
#if (defined(OSEE_TC_CORE4_176_ISR_CAT))
#if (OSEE_TC_CORE4_176_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 176)
#elif (OSEE_TC_CORE4_176_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 176)
#else
#error Invalid value for OSEE_TC_CORE4_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 176)
OSEE_DUMMY_ISR(_core4_, 176)
#endif /* OSEE_TC_CORE4_176_ISR_CAT */
#if (defined(OSEE_TC_CORE4_177_ISR_CAT))
#if (OSEE_TC_CORE4_177_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 177)
#elif (OSEE_TC_CORE4_177_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 177)
#else
#error Invalid value for OSEE_TC_CORE4_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 177)
OSEE_DUMMY_ISR(_core4_, 177)
#endif /* OSEE_TC_CORE4_177_ISR_CAT */
#if (defined(OSEE_TC_CORE4_178_ISR_CAT))
#if (OSEE_TC_CORE4_178_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 178)
#elif (OSEE_TC_CORE4_178_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 178)
#else
#error Invalid value for OSEE_TC_CORE4_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 178)
OSEE_DUMMY_ISR(_core4_, 178)
#endif /* OSEE_TC_CORE4_178_ISR_CAT */
#if (defined(OSEE_TC_CORE4_179_ISR_CAT))
#if (OSEE_TC_CORE4_179_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 179)
#elif (OSEE_TC_CORE4_179_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 179)
#else
#error Invalid value for OSEE_TC_CORE4_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 179)
OSEE_DUMMY_ISR(_core4_, 179)
#endif /* OSEE_TC_CORE4_179_ISR_CAT */
#if (defined(OSEE_TC_CORE4_180_ISR_CAT))
#if (OSEE_TC_CORE4_180_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 180)
#elif (OSEE_TC_CORE4_180_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 180)
#else
#error Invalid value for OSEE_TC_CORE4_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 180)
OSEE_DUMMY_ISR(_core4_, 180)
#endif /* OSEE_TC_CORE4_180_ISR_CAT */
#if (defined(OSEE_TC_CORE4_181_ISR_CAT))
#if (OSEE_TC_CORE4_181_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 181)
#elif (OSEE_TC_CORE4_181_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 181)
#else
#error Invalid value for OSEE_TC_CORE4_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 181)
OSEE_DUMMY_ISR(_core4_, 181)
#endif /* OSEE_TC_CORE4_181_ISR_CAT */
#if (defined(OSEE_TC_CORE4_182_ISR_CAT))
#if (OSEE_TC_CORE4_182_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 182)
#elif (OSEE_TC_CORE4_182_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 182)
#else
#error Invalid value for OSEE_TC_CORE4_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 182)
OSEE_DUMMY_ISR(_core4_, 182)
#endif /* OSEE_TC_CORE4_182_ISR_CAT */
#if (defined(OSEE_TC_CORE4_183_ISR_CAT))
#if (OSEE_TC_CORE4_183_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 183)
#elif (OSEE_TC_CORE4_183_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 183)
#else
#error Invalid value for OSEE_TC_CORE4_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 183)
OSEE_DUMMY_ISR(_core4_, 183)
#endif /* OSEE_TC_CORE4_183_ISR_CAT */
#if (defined(OSEE_TC_CORE4_184_ISR_CAT))
#if (OSEE_TC_CORE4_184_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 184)
#elif (OSEE_TC_CORE4_184_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 184)
#else
#error Invalid value for OSEE_TC_CORE4_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 184)
OSEE_DUMMY_ISR(_core4_, 184)
#endif /* OSEE_TC_CORE4_184_ISR_CAT */
#if (defined(OSEE_TC_CORE4_185_ISR_CAT))
#if (OSEE_TC_CORE4_185_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 185)
#elif (OSEE_TC_CORE4_185_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 185)
#else
#error Invalid value for OSEE_TC_CORE4_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 185)
OSEE_DUMMY_ISR(_core4_, 185)
#endif /* OSEE_TC_CORE4_185_ISR_CAT */
#if (defined(OSEE_TC_CORE4_186_ISR_CAT))
#if (OSEE_TC_CORE4_186_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 186)
#elif (OSEE_TC_CORE4_186_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 186)
#else
#error Invalid value for OSEE_TC_CORE4_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 186)
OSEE_DUMMY_ISR(_core4_, 186)
#endif /* OSEE_TC_CORE4_186_ISR_CAT */
#if (defined(OSEE_TC_CORE4_187_ISR_CAT))
#if (OSEE_TC_CORE4_187_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 187)
#elif (OSEE_TC_CORE4_187_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 187)
#else
#error Invalid value for OSEE_TC_CORE4_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 187)
OSEE_DUMMY_ISR(_core4_, 187)
#endif /* OSEE_TC_CORE4_187_ISR_CAT */
#if (defined(OSEE_TC_CORE4_188_ISR_CAT))
#if (OSEE_TC_CORE4_188_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 188)
#elif (OSEE_TC_CORE4_188_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 188)
#else
#error Invalid value for OSEE_TC_CORE4_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 188)
OSEE_DUMMY_ISR(_core4_, 188)
#endif /* OSEE_TC_CORE4_188_ISR_CAT */
#if (defined(OSEE_TC_CORE4_189_ISR_CAT))
#if (OSEE_TC_CORE4_189_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 189)
#elif (OSEE_TC_CORE4_189_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 189)
#else
#error Invalid value for OSEE_TC_CORE4_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 189)
OSEE_DUMMY_ISR(_core4_, 189)
#endif /* OSEE_TC_CORE4_189_ISR_CAT */
#if (defined(OSEE_TC_CORE4_190_ISR_CAT))
#if (OSEE_TC_CORE4_190_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 190)
#elif (OSEE_TC_CORE4_190_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 190)
#else
#error Invalid value for OSEE_TC_CORE4_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 190)
OSEE_DUMMY_ISR(_core4_, 190)
#endif /* OSEE_TC_CORE4_190_ISR_CAT */
#if (defined(OSEE_TC_CORE4_191_ISR_CAT))
#if (OSEE_TC_CORE4_191_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 191)
#elif (OSEE_TC_CORE4_191_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 191)
#else
#error Invalid value for OSEE_TC_CORE4_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 191)
OSEE_DUMMY_ISR(_core4_, 191)
#endif /* OSEE_TC_CORE4_191_ISR_CAT */
#if (defined(OSEE_TC_CORE4_192_ISR_CAT))
#if (OSEE_TC_CORE4_192_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 192)
#elif (OSEE_TC_CORE4_192_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 192)
#else
#error Invalid value for OSEE_TC_CORE4_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 192)
OSEE_DUMMY_ISR(_core4_, 192)
#endif /* OSEE_TC_CORE4_192_ISR_CAT */
#if (defined(OSEE_TC_CORE4_193_ISR_CAT))
#if (OSEE_TC_CORE4_193_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 193)
#elif (OSEE_TC_CORE4_193_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 193)
#else
#error Invalid value for OSEE_TC_CORE4_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 193)
OSEE_DUMMY_ISR(_core4_, 193)
#endif /* OSEE_TC_CORE4_193_ISR_CAT */
#if (defined(OSEE_TC_CORE4_194_ISR_CAT))
#if (OSEE_TC_CORE4_194_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 194)
#elif (OSEE_TC_CORE4_194_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 194)
#else
#error Invalid value for OSEE_TC_CORE4_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 194)
OSEE_DUMMY_ISR(_core4_, 194)
#endif /* OSEE_TC_CORE4_194_ISR_CAT */
#if (defined(OSEE_TC_CORE4_195_ISR_CAT))
#if (OSEE_TC_CORE4_195_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 195)
#elif (OSEE_TC_CORE4_195_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 195)
#else
#error Invalid value for OSEE_TC_CORE4_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 195)
OSEE_DUMMY_ISR(_core4_, 195)
#endif /* OSEE_TC_CORE4_195_ISR_CAT */
#if (defined(OSEE_TC_CORE4_196_ISR_CAT))
#if (OSEE_TC_CORE4_196_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 196)
#elif (OSEE_TC_CORE4_196_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 196)
#else
#error Invalid value for OSEE_TC_CORE4_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 196)
OSEE_DUMMY_ISR(_core4_, 196)
#endif /* OSEE_TC_CORE4_196_ISR_CAT */
#if (defined(OSEE_TC_CORE4_197_ISR_CAT))
#if (OSEE_TC_CORE4_197_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 197)
#elif (OSEE_TC_CORE4_197_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 197)
#else
#error Invalid value for OSEE_TC_CORE4_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 197)
OSEE_DUMMY_ISR(_core4_, 197)
#endif /* OSEE_TC_CORE4_197_ISR_CAT */
#if (defined(OSEE_TC_CORE4_198_ISR_CAT))
#if (OSEE_TC_CORE4_198_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 198)
#elif (OSEE_TC_CORE4_198_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 198)
#else
#error Invalid value for OSEE_TC_CORE4_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 198)
OSEE_DUMMY_ISR(_core4_, 198)
#endif /* OSEE_TC_CORE4_198_ISR_CAT */
#if (defined(OSEE_TC_CORE4_199_ISR_CAT))
#if (OSEE_TC_CORE4_199_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 199)
#elif (OSEE_TC_CORE4_199_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 199)
#else
#error Invalid value for OSEE_TC_CORE4_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 199)
OSEE_DUMMY_ISR(_core4_, 199)
#endif /* OSEE_TC_CORE4_199_ISR_CAT */
#if (defined(OSEE_TC_CORE4_200_ISR_CAT))
#if (OSEE_TC_CORE4_200_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 200)
#elif (OSEE_TC_CORE4_200_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 200)
#else
#error Invalid value for OSEE_TC_CORE4_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 200)
OSEE_DUMMY_ISR(_core4_, 200)
#endif /* OSEE_TC_CORE4_200_ISR_CAT */
#if (defined(OSEE_TC_CORE4_201_ISR_CAT))
#if (OSEE_TC_CORE4_201_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 201)
#elif (OSEE_TC_CORE4_201_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 201)
#else
#error Invalid value for OSEE_TC_CORE4_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 201)
OSEE_DUMMY_ISR(_core4_, 201)
#endif /* OSEE_TC_CORE4_201_ISR_CAT */
#if (defined(OSEE_TC_CORE4_202_ISR_CAT))
#if (OSEE_TC_CORE4_202_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 202)
#elif (OSEE_TC_CORE4_202_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 202)
#else
#error Invalid value for OSEE_TC_CORE4_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 202)
OSEE_DUMMY_ISR(_core4_, 202)
#endif /* OSEE_TC_CORE4_202_ISR_CAT */
#if (defined(OSEE_TC_CORE4_203_ISR_CAT))
#if (OSEE_TC_CORE4_203_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 203)
#elif (OSEE_TC_CORE4_203_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 203)
#else
#error Invalid value for OSEE_TC_CORE4_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 203)
OSEE_DUMMY_ISR(_core4_, 203)
#endif /* OSEE_TC_CORE4_203_ISR_CAT */
#if (defined(OSEE_TC_CORE4_204_ISR_CAT))
#if (OSEE_TC_CORE4_204_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 204)
#elif (OSEE_TC_CORE4_204_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 204)
#else
#error Invalid value for OSEE_TC_CORE4_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 204)
OSEE_DUMMY_ISR(_core4_, 204)
#endif /* OSEE_TC_CORE4_204_ISR_CAT */
#if (defined(OSEE_TC_CORE4_205_ISR_CAT))
#if (OSEE_TC_CORE4_205_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 205)
#elif (OSEE_TC_CORE4_205_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 205)
#else
#error Invalid value for OSEE_TC_CORE4_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 205)
OSEE_DUMMY_ISR(_core4_, 205)
#endif /* OSEE_TC_CORE4_205_ISR_CAT */
#if (defined(OSEE_TC_CORE4_206_ISR_CAT))
#if (OSEE_TC_CORE4_206_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 206)
#elif (OSEE_TC_CORE4_206_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 206)
#else
#error Invalid value for OSEE_TC_CORE4_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 206)
OSEE_DUMMY_ISR(_core4_, 206)
#endif /* OSEE_TC_CORE4_206_ISR_CAT */
#if (defined(OSEE_TC_CORE4_207_ISR_CAT))
#if (OSEE_TC_CORE4_207_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 207)
#elif (OSEE_TC_CORE4_207_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 207)
#else
#error Invalid value for OSEE_TC_CORE4_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 207)
OSEE_DUMMY_ISR(_core4_, 207)
#endif /* OSEE_TC_CORE4_207_ISR_CAT */
#if (defined(OSEE_TC_CORE4_208_ISR_CAT))
#if (OSEE_TC_CORE4_208_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 208)
#elif (OSEE_TC_CORE4_208_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 208)
#else
#error Invalid value for OSEE_TC_CORE4_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 208)
OSEE_DUMMY_ISR(_core4_, 208)
#endif /* OSEE_TC_CORE4_208_ISR_CAT */
#if (defined(OSEE_TC_CORE4_209_ISR_CAT))
#if (OSEE_TC_CORE4_209_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 209)
#elif (OSEE_TC_CORE4_209_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 209)
#else
#error Invalid value for OSEE_TC_CORE4_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 209)
OSEE_DUMMY_ISR(_core4_, 209)
#endif /* OSEE_TC_CORE4_209_ISR_CAT */
#if (defined(OSEE_TC_CORE4_210_ISR_CAT))
#if (OSEE_TC_CORE4_210_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 210)
#elif (OSEE_TC_CORE4_210_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 210)
#else
#error Invalid value for OSEE_TC_CORE4_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 210)
OSEE_DUMMY_ISR(_core4_, 210)
#endif /* OSEE_TC_CORE4_210_ISR_CAT */
#if (defined(OSEE_TC_CORE4_211_ISR_CAT))
#if (OSEE_TC_CORE4_211_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 211)
#elif (OSEE_TC_CORE4_211_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 211)
#else
#error Invalid value for OSEE_TC_CORE4_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 211)
OSEE_DUMMY_ISR(_core4_, 211)
#endif /* OSEE_TC_CORE4_211_ISR_CAT */
#if (defined(OSEE_TC_CORE4_212_ISR_CAT))
#if (OSEE_TC_CORE4_212_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 212)
#elif (OSEE_TC_CORE4_212_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 212)
#else
#error Invalid value for OSEE_TC_CORE4_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 212)
OSEE_DUMMY_ISR(_core4_, 212)
#endif /* OSEE_TC_CORE4_212_ISR_CAT */
#if (defined(OSEE_TC_CORE4_213_ISR_CAT))
#if (OSEE_TC_CORE4_213_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 213)
#elif (OSEE_TC_CORE4_213_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 213)
#else
#error Invalid value for OSEE_TC_CORE4_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 213)
OSEE_DUMMY_ISR(_core4_, 213)
#endif /* OSEE_TC_CORE4_213_ISR_CAT */
#if (defined(OSEE_TC_CORE4_214_ISR_CAT))
#if (OSEE_TC_CORE4_214_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 214)
#elif (OSEE_TC_CORE4_214_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 214)
#else
#error Invalid value for OSEE_TC_CORE4_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 214)
OSEE_DUMMY_ISR(_core4_, 214)
#endif /* OSEE_TC_CORE4_214_ISR_CAT */
#if (defined(OSEE_TC_CORE4_215_ISR_CAT))
#if (OSEE_TC_CORE4_215_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 215)
#elif (OSEE_TC_CORE4_215_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 215)
#else
#error Invalid value for OSEE_TC_CORE4_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 215)
OSEE_DUMMY_ISR(_core4_, 215)
#endif /* OSEE_TC_CORE4_215_ISR_CAT */
#if (defined(OSEE_TC_CORE4_216_ISR_CAT))
#if (OSEE_TC_CORE4_216_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 216)
#elif (OSEE_TC_CORE4_216_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 216)
#else
#error Invalid value for OSEE_TC_CORE4_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 216)
OSEE_DUMMY_ISR(_core4_, 216)
#endif /* OSEE_TC_CORE4_216_ISR_CAT */
#if (defined(OSEE_TC_CORE4_217_ISR_CAT))
#if (OSEE_TC_CORE4_217_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 217)
#elif (OSEE_TC_CORE4_217_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 217)
#else
#error Invalid value for OSEE_TC_CORE4_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 217)
OSEE_DUMMY_ISR(_core4_, 217)
#endif /* OSEE_TC_CORE4_217_ISR_CAT */
#if (defined(OSEE_TC_CORE4_218_ISR_CAT))
#if (OSEE_TC_CORE4_218_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 218)
#elif (OSEE_TC_CORE4_218_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 218)
#else
#error Invalid value for OSEE_TC_CORE4_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 218)
OSEE_DUMMY_ISR(_core4_, 218)
#endif /* OSEE_TC_CORE4_218_ISR_CAT */
#if (defined(OSEE_TC_CORE4_219_ISR_CAT))
#if (OSEE_TC_CORE4_219_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 219)
#elif (OSEE_TC_CORE4_219_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 219)
#else
#error Invalid value for OSEE_TC_CORE4_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 219)
OSEE_DUMMY_ISR(_core4_, 219)
#endif /* OSEE_TC_CORE4_219_ISR_CAT */
#if (defined(OSEE_TC_CORE4_220_ISR_CAT))
#if (OSEE_TC_CORE4_220_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 220)
#elif (OSEE_TC_CORE4_220_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 220)
#else
#error Invalid value for OSEE_TC_CORE4_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 220)
OSEE_DUMMY_ISR(_core4_, 220)
#endif /* OSEE_TC_CORE4_220_ISR_CAT */
#if (defined(OSEE_TC_CORE4_221_ISR_CAT))
#if (OSEE_TC_CORE4_221_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 221)
#elif (OSEE_TC_CORE4_221_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 221)
#else
#error Invalid value for OSEE_TC_CORE4_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 221)
OSEE_DUMMY_ISR(_core4_, 221)
#endif /* OSEE_TC_CORE4_221_ISR_CAT */
#if (defined(OSEE_TC_CORE4_222_ISR_CAT))
#if (OSEE_TC_CORE4_222_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 222)
#elif (OSEE_TC_CORE4_222_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 222)
#else
#error Invalid value for OSEE_TC_CORE4_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 222)
OSEE_DUMMY_ISR(_core4_, 222)
#endif /* OSEE_TC_CORE4_222_ISR_CAT */
#if (defined(OSEE_TC_CORE4_223_ISR_CAT))
#if (OSEE_TC_CORE4_223_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 223)
#elif (OSEE_TC_CORE4_223_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 223)
#else
#error Invalid value for OSEE_TC_CORE4_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 223)
OSEE_DUMMY_ISR(_core4_, 223)
#endif /* OSEE_TC_CORE4_223_ISR_CAT */
#if (defined(OSEE_TC_CORE4_224_ISR_CAT))
#if (OSEE_TC_CORE4_224_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 224)
#elif (OSEE_TC_CORE4_224_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 224)
#else
#error Invalid value for OSEE_TC_CORE4_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 224)
OSEE_DUMMY_ISR(_core4_, 224)
#endif /* OSEE_TC_CORE4_224_ISR_CAT */
#if (defined(OSEE_TC_CORE4_225_ISR_CAT))
#if (OSEE_TC_CORE4_225_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 225)
#elif (OSEE_TC_CORE4_225_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 225)
#else
#error Invalid value for OSEE_TC_CORE4_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 225)
OSEE_DUMMY_ISR(_core4_, 225)
#endif /* OSEE_TC_CORE4_225_ISR_CAT */
#if (defined(OSEE_TC_CORE4_226_ISR_CAT))
#if (OSEE_TC_CORE4_226_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 226)
#elif (OSEE_TC_CORE4_226_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 226)
#else
#error Invalid value for OSEE_TC_CORE4_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 226)
OSEE_DUMMY_ISR(_core4_, 226)
#endif /* OSEE_TC_CORE4_226_ISR_CAT */
#if (defined(OSEE_TC_CORE4_227_ISR_CAT))
#if (OSEE_TC_CORE4_227_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 227)
#elif (OSEE_TC_CORE4_227_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 227)
#else
#error Invalid value for OSEE_TC_CORE4_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 227)
OSEE_DUMMY_ISR(_core4_, 227)
#endif /* OSEE_TC_CORE4_227_ISR_CAT */
#if (defined(OSEE_TC_CORE4_228_ISR_CAT))
#if (OSEE_TC_CORE4_228_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 228)
#elif (OSEE_TC_CORE4_228_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 228)
#else
#error Invalid value for OSEE_TC_CORE4_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 228)
OSEE_DUMMY_ISR(_core4_, 228)
#endif /* OSEE_TC_CORE4_228_ISR_CAT */
#if (defined(OSEE_TC_CORE4_229_ISR_CAT))
#if (OSEE_TC_CORE4_229_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 229)
#elif (OSEE_TC_CORE4_229_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 229)
#else
#error Invalid value for OSEE_TC_CORE4_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 229)
OSEE_DUMMY_ISR(_core4_, 229)
#endif /* OSEE_TC_CORE4_229_ISR_CAT */
#if (defined(OSEE_TC_CORE4_230_ISR_CAT))
#if (OSEE_TC_CORE4_230_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 230)
#elif (OSEE_TC_CORE4_230_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 230)
#else
#error Invalid value for OSEE_TC_CORE4_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 230)
OSEE_DUMMY_ISR(_core4_, 230)
#endif /* OSEE_TC_CORE4_230_ISR_CAT */
#if (defined(OSEE_TC_CORE4_231_ISR_CAT))
#if (OSEE_TC_CORE4_231_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 231)
#elif (OSEE_TC_CORE4_231_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 231)
#else
#error Invalid value for OSEE_TC_CORE4_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 231)
OSEE_DUMMY_ISR(_core4_, 231)
#endif /* OSEE_TC_CORE4_231_ISR_CAT */
#if (defined(OSEE_TC_CORE4_232_ISR_CAT))
#if (OSEE_TC_CORE4_232_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 232)
#elif (OSEE_TC_CORE4_232_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 232)
#else
#error Invalid value for OSEE_TC_CORE4_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 232)
OSEE_DUMMY_ISR(_core4_, 232)
#endif /* OSEE_TC_CORE4_232_ISR_CAT */
#if (defined(OSEE_TC_CORE4_233_ISR_CAT))
#if (OSEE_TC_CORE4_233_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 233)
#elif (OSEE_TC_CORE4_233_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 233)
#else
#error Invalid value for OSEE_TC_CORE4_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 233)
OSEE_DUMMY_ISR(_core4_, 233)
#endif /* OSEE_TC_CORE4_233_ISR_CAT */
#if (defined(OSEE_TC_CORE4_234_ISR_CAT))
#if (OSEE_TC_CORE4_234_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 234)
#elif (OSEE_TC_CORE4_234_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 234)
#else
#error Invalid value for OSEE_TC_CORE4_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 234)
OSEE_DUMMY_ISR(_core4_, 234)
#endif /* OSEE_TC_CORE4_234_ISR_CAT */
#if (defined(OSEE_TC_CORE4_235_ISR_CAT))
#if (OSEE_TC_CORE4_235_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 235)
#elif (OSEE_TC_CORE4_235_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 235)
#else
#error Invalid value for OSEE_TC_CORE4_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 235)
OSEE_DUMMY_ISR(_core4_, 235)
#endif /* OSEE_TC_CORE4_235_ISR_CAT */
#if (defined(OSEE_TC_CORE4_236_ISR_CAT))
#if (OSEE_TC_CORE4_236_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 236)
#elif (OSEE_TC_CORE4_236_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 236)
#else
#error Invalid value for OSEE_TC_CORE4_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 236)
OSEE_DUMMY_ISR(_core4_, 236)
#endif /* OSEE_TC_CORE4_236_ISR_CAT */
#if (defined(OSEE_TC_CORE4_237_ISR_CAT))
#if (OSEE_TC_CORE4_237_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 237)
#elif (OSEE_TC_CORE4_237_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 237)
#else
#error Invalid value for OSEE_TC_CORE4_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 237)
OSEE_DUMMY_ISR(_core4_, 237)
#endif /* OSEE_TC_CORE4_237_ISR_CAT */
#if (defined(OSEE_TC_CORE4_238_ISR_CAT))
#if (OSEE_TC_CORE4_238_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 238)
#elif (OSEE_TC_CORE4_238_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 238)
#else
#error Invalid value for OSEE_TC_CORE4_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 238)
OSEE_DUMMY_ISR(_core4_, 238)
#endif /* OSEE_TC_CORE4_238_ISR_CAT */
#if (defined(OSEE_TC_CORE4_239_ISR_CAT))
#if (OSEE_TC_CORE4_239_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 239)
#elif (OSEE_TC_CORE4_239_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 239)
#else
#error Invalid value for OSEE_TC_CORE4_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 239)
OSEE_DUMMY_ISR(_core4_, 239)
#endif /* OSEE_TC_CORE4_239_ISR_CAT */
#if (defined(OSEE_TC_CORE4_240_ISR_CAT))
#if (OSEE_TC_CORE4_240_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 240)
#elif (OSEE_TC_CORE4_240_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 240)
#else
#error Invalid value for OSEE_TC_CORE4_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 240)
OSEE_DUMMY_ISR(_core4_, 240)
#endif /* OSEE_TC_CORE4_240_ISR_CAT */
#if (defined(OSEE_TC_CORE4_241_ISR_CAT))
#if (OSEE_TC_CORE4_241_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 241)
#elif (OSEE_TC_CORE4_241_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 241)
#else
#error Invalid value for OSEE_TC_CORE4_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 241)
OSEE_DUMMY_ISR(_core4_, 241)
#endif /* OSEE_TC_CORE4_241_ISR_CAT */
#if (defined(OSEE_TC_CORE4_242_ISR_CAT))
#if (OSEE_TC_CORE4_242_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 242)
#elif (OSEE_TC_CORE4_242_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 242)
#else
#error Invalid value for OSEE_TC_CORE4_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 242)
OSEE_DUMMY_ISR(_core4_, 242)
#endif /* OSEE_TC_CORE4_242_ISR_CAT */
#if (defined(OSEE_TC_CORE4_243_ISR_CAT))
#if (OSEE_TC_CORE4_243_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 243)
#elif (OSEE_TC_CORE4_243_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 243)
#else
#error Invalid value for OSEE_TC_CORE4_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 243)
OSEE_DUMMY_ISR(_core4_, 243)
#endif /* OSEE_TC_CORE4_243_ISR_CAT */
#if (defined(OSEE_TC_CORE4_244_ISR_CAT))
#if (OSEE_TC_CORE4_244_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 244)
#elif (OSEE_TC_CORE4_244_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 244)
#else
#error Invalid value for OSEE_TC_CORE4_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 244)
OSEE_DUMMY_ISR(_core4_, 244)
#endif /* OSEE_TC_CORE4_244_ISR_CAT */
#if (defined(OSEE_TC_CORE4_245_ISR_CAT))
#if (OSEE_TC_CORE4_245_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 245)
#elif (OSEE_TC_CORE4_245_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 245)
#else
#error Invalid value for OSEE_TC_CORE4_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 245)
OSEE_DUMMY_ISR(_core4_, 245)
#endif /* OSEE_TC_CORE4_245_ISR_CAT */
#if (defined(OSEE_TC_CORE4_246_ISR_CAT))
#if (OSEE_TC_CORE4_246_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 246)
#elif (OSEE_TC_CORE4_246_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 246)
#else
#error Invalid value for OSEE_TC_CORE4_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 246)
OSEE_DUMMY_ISR(_core4_, 246)
#endif /* OSEE_TC_CORE4_246_ISR_CAT */
#if (defined(OSEE_TC_CORE4_247_ISR_CAT))
#if (OSEE_TC_CORE4_247_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 247)
#elif (OSEE_TC_CORE4_247_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 247)
#else
#error Invalid value for OSEE_TC_CORE4_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 247)
OSEE_DUMMY_ISR(_core4_, 247)
#endif /* OSEE_TC_CORE4_247_ISR_CAT */
#if (defined(OSEE_TC_CORE4_248_ISR_CAT))
#if (OSEE_TC_CORE4_248_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 248)
#elif (OSEE_TC_CORE4_248_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 248)
#else
#error Invalid value for OSEE_TC_CORE4_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 248)
OSEE_DUMMY_ISR(_core4_, 248)
#endif /* OSEE_TC_CORE4_248_ISR_CAT */
#if (defined(OSEE_TC_CORE4_249_ISR_CAT))
#if (OSEE_TC_CORE4_249_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 249)
#elif (OSEE_TC_CORE4_249_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 249)
#else
#error Invalid value for OSEE_TC_CORE4_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 249)
OSEE_DUMMY_ISR(_core4_, 249)
#endif /* OSEE_TC_CORE4_249_ISR_CAT */
#if (defined(OSEE_TC_CORE4_250_ISR_CAT))
#if (OSEE_TC_CORE4_250_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 250)
#elif (OSEE_TC_CORE4_250_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 250)
#else
#error Invalid value for OSEE_TC_CORE4_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 250)
OSEE_DUMMY_ISR(_core4_, 250)
#endif /* OSEE_TC_CORE4_250_ISR_CAT */
#if (defined(OSEE_TC_CORE4_251_ISR_CAT))
#if (OSEE_TC_CORE4_251_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 251)
#elif (OSEE_TC_CORE4_251_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 251)
#else
#error Invalid value for OSEE_TC_CORE4_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 251)
OSEE_DUMMY_ISR(_core4_, 251)
#endif /* OSEE_TC_CORE4_251_ISR_CAT */
#if (defined(OSEE_TC_CORE4_252_ISR_CAT))
#if (OSEE_TC_CORE4_252_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 252)
#elif (OSEE_TC_CORE4_252_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 252)
#else
#error Invalid value for OSEE_TC_CORE4_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 252)
OSEE_DUMMY_ISR(_core4_, 252)
#endif /* OSEE_TC_CORE4_252_ISR_CAT */
#if (defined(OSEE_TC_CORE4_253_ISR_CAT))
#if (OSEE_TC_CORE4_253_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 253)
#elif (OSEE_TC_CORE4_253_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 253)
#else
#error Invalid value for OSEE_TC_CORE4_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 253)
OSEE_DUMMY_ISR(_core4_, 253)
#endif /* OSEE_TC_CORE4_253_ISR_CAT */
#if (defined(OSEE_TC_CORE4_254_ISR_CAT))
#if (OSEE_TC_CORE4_254_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 254)
#elif (OSEE_TC_CORE4_254_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 254)
#else
#error Invalid value for OSEE_TC_CORE4_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 254)
OSEE_DUMMY_ISR(_core4_, 254)
#endif /* OSEE_TC_CORE4_254_ISR_CAT */
#if (defined(OSEE_TC_CORE4_255_ISR_CAT))
#if (OSEE_TC_CORE4_255_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core4_, 255)
#elif (OSEE_TC_CORE4_255_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core4_, 255)
#else
#error Invalid value for OSEE_TC_CORE4_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 255)
OSEE_DUMMY_ISR(_core4_, 255)
#endif /* OSEE_TC_CORE4_255_ISR_CAT */
#endif /* OSEE_TC_CORE4_ISR_MAX_PRIO */

#if (defined(OSEE_TC_CORE6_ISR_MAX_PRIO))
OSEE_ISR2_DECLARE(_core6_, 1)
#if (defined(OSEE_TC_CORE6_2_ISR_CAT))
#if (OSEE_TC_CORE6_2_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 2)
#elif (OSEE_TC_CORE6_2_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 2)
#else
#error Invalid value for OSEE_TC_CORE6_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 2)
OSEE_DUMMY_ISR(_core6_, 2)
#endif /* OSEE_TC_CORE6_2_ISR_CAT */
#if (defined(OSEE_TC_CORE6_3_ISR_CAT))
#if (OSEE_TC_CORE6_3_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 3)
#elif (OSEE_TC_CORE6_3_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 3)
#else
#error Invalid value for OSEE_TC_CORE6_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 3)
OSEE_DUMMY_ISR(_core6_, 3)
#endif /* OSEE_TC_CORE6_3_ISR_CAT */
#if (defined(OSEE_TC_CORE6_4_ISR_CAT))
#if (OSEE_TC_CORE6_4_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 4)
#elif (OSEE_TC_CORE6_4_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 4)
#else
#error Invalid value for OSEE_TC_CORE6_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 4)
OSEE_DUMMY_ISR(_core6_, 4)
#endif /* OSEE_TC_CORE6_4_ISR_CAT */
#if (defined(OSEE_TC_CORE6_5_ISR_CAT))
#if (OSEE_TC_CORE6_5_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 5)
#elif (OSEE_TC_CORE6_5_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 5)
#else
#error Invalid value for OSEE_TC_CORE6_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 5)
OSEE_DUMMY_ISR(_core6_, 5)
#endif /* OSEE_TC_CORE6_5_ISR_CAT */
#if (defined(OSEE_TC_CORE6_6_ISR_CAT))
#if (OSEE_TC_CORE6_6_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 6)
#elif (OSEE_TC_CORE6_6_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 6)
#else
#error Invalid value for OSEE_TC_CORE6_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 6)
OSEE_DUMMY_ISR(_core6_, 6)
#endif /* OSEE_TC_CORE6_6_ISR_CAT */
#if (defined(OSEE_TC_CORE6_7_ISR_CAT))
#if (OSEE_TC_CORE6_7_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 7)
#elif (OSEE_TC_CORE6_7_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 7)
#else
#error Invalid value for OSEE_TC_CORE6_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 7)
OSEE_DUMMY_ISR(_core6_, 7)
#endif /* OSEE_TC_CORE6_7_ISR_CAT */
#if (defined(OSEE_TC_CORE6_8_ISR_CAT))
#if (OSEE_TC_CORE6_8_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 8)
#elif (OSEE_TC_CORE6_8_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 8)
#else
#error Invalid value for OSEE_TC_CORE6_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 8)
OSEE_DUMMY_ISR(_core6_, 8)
#endif /* OSEE_TC_CORE6_8_ISR_CAT */
#if (defined(OSEE_TC_CORE6_9_ISR_CAT))
#if (OSEE_TC_CORE6_9_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 9)
#elif (OSEE_TC_CORE6_9_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 9)
#else
#error Invalid value for OSEE_TC_CORE6_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 9)
OSEE_DUMMY_ISR(_core6_, 9)
#endif /* OSEE_TC_CORE6_9_ISR_CAT */
#if (defined(OSEE_TC_CORE6_10_ISR_CAT))
#if (OSEE_TC_CORE6_10_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 10)
#elif (OSEE_TC_CORE6_10_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 10)
#else
#error Invalid value for OSEE_TC_CORE6_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 10)
OSEE_DUMMY_ISR(_core6_, 10)
#endif /* OSEE_TC_CORE6_10_ISR_CAT */
#if (defined(OSEE_TC_CORE6_11_ISR_CAT))
#if (OSEE_TC_CORE6_11_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 11)
#elif (OSEE_TC_CORE6_11_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 11)
#else
#error Invalid value for OSEE_TC_CORE6_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 11)
OSEE_DUMMY_ISR(_core6_, 11)
#endif /* OSEE_TC_CORE6_11_ISR_CAT */
#if (defined(OSEE_TC_CORE6_12_ISR_CAT))
#if (OSEE_TC_CORE6_12_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 12)
#elif (OSEE_TC_CORE6_12_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 12)
#else
#error Invalid value for OSEE_TC_CORE6_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 12)
OSEE_DUMMY_ISR(_core6_, 12)
#endif /* OSEE_TC_CORE6_12_ISR_CAT */
#if (defined(OSEE_TC_CORE6_13_ISR_CAT))
#if (OSEE_TC_CORE6_13_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 13)
#elif (OSEE_TC_CORE6_13_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 13)
#else
#error Invalid value for OSEE_TC_CORE6_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 13)
OSEE_DUMMY_ISR(_core6_, 13)
#endif /* OSEE_TC_CORE6_13_ISR_CAT */
#if (defined(OSEE_TC_CORE6_14_ISR_CAT))
#if (OSEE_TC_CORE6_14_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 14)
#elif (OSEE_TC_CORE6_14_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 14)
#else
#error Invalid value for OSEE_TC_CORE6_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 14)
OSEE_DUMMY_ISR(_core6_, 14)
#endif /* OSEE_TC_CORE6_14_ISR_CAT */
#if (defined(OSEE_TC_CORE6_15_ISR_CAT))
#if (OSEE_TC_CORE6_15_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 15)
#elif (OSEE_TC_CORE6_15_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 15)
#else
#error Invalid value for OSEE_TC_CORE6_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 15)
OSEE_DUMMY_ISR(_core6_, 15)
#endif /* OSEE_TC_CORE6_15_ISR_CAT */
#if (defined(OSEE_TC_CORE6_16_ISR_CAT))
#if (OSEE_TC_CORE6_16_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 16)
#elif (OSEE_TC_CORE6_16_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 16)
#else
#error Invalid value for OSEE_TC_CORE6_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 16)
OSEE_DUMMY_ISR(_core6_, 16)
#endif /* OSEE_TC_CORE6_16_ISR_CAT */
#if (defined(OSEE_TC_CORE6_17_ISR_CAT))
#if (OSEE_TC_CORE6_17_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 17)
#elif (OSEE_TC_CORE6_17_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 17)
#else
#error Invalid value for OSEE_TC_CORE6_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 17)
OSEE_DUMMY_ISR(_core6_, 17)
#endif /* OSEE_TC_CORE6_17_ISR_CAT */
#if (defined(OSEE_TC_CORE6_18_ISR_CAT))
#if (OSEE_TC_CORE6_18_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 18)
#elif (OSEE_TC_CORE6_18_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 18)
#else
#error Invalid value for OSEE_TC_CORE6_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 18)
OSEE_DUMMY_ISR(_core6_, 18)
#endif /* OSEE_TC_CORE6_18_ISR_CAT */
#if (defined(OSEE_TC_CORE6_19_ISR_CAT))
#if (OSEE_TC_CORE6_19_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 19)
#elif (OSEE_TC_CORE6_19_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 19)
#else
#error Invalid value for OSEE_TC_CORE6_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 19)
OSEE_DUMMY_ISR(_core6_, 19)
#endif /* OSEE_TC_CORE6_19_ISR_CAT */
#if (defined(OSEE_TC_CORE6_20_ISR_CAT))
#if (OSEE_TC_CORE6_20_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 20)
#elif (OSEE_TC_CORE6_20_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 20)
#else
#error Invalid value for OSEE_TC_CORE6_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 20)
OSEE_DUMMY_ISR(_core6_, 20)
#endif /* OSEE_TC_CORE6_20_ISR_CAT */
#if (defined(OSEE_TC_CORE6_21_ISR_CAT))
#if (OSEE_TC_CORE6_21_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 21)
#elif (OSEE_TC_CORE6_21_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 21)
#else
#error Invalid value for OSEE_TC_CORE6_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 21)
OSEE_DUMMY_ISR(_core6_, 21)
#endif /* OSEE_TC_CORE6_21_ISR_CAT */
#if (defined(OSEE_TC_CORE6_22_ISR_CAT))
#if (OSEE_TC_CORE6_22_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 22)
#elif (OSEE_TC_CORE6_22_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 22)
#else
#error Invalid value for OSEE_TC_CORE6_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 22)
OSEE_DUMMY_ISR(_core6_, 22)
#endif /* OSEE_TC_CORE6_22_ISR_CAT */
#if (defined(OSEE_TC_CORE6_23_ISR_CAT))
#if (OSEE_TC_CORE6_23_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 23)
#elif (OSEE_TC_CORE6_23_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 23)
#else
#error Invalid value for OSEE_TC_CORE6_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 23)
OSEE_DUMMY_ISR(_core6_, 23)
#endif /* OSEE_TC_CORE6_23_ISR_CAT */
#if (defined(OSEE_TC_CORE6_24_ISR_CAT))
#if (OSEE_TC_CORE6_24_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 24)
#elif (OSEE_TC_CORE6_24_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 24)
#else
#error Invalid value for OSEE_TC_CORE6_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 24)
OSEE_DUMMY_ISR(_core6_, 24)
#endif /* OSEE_TC_CORE6_24_ISR_CAT */
#if (defined(OSEE_TC_CORE6_25_ISR_CAT))
#if (OSEE_TC_CORE6_25_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 25)
#elif (OSEE_TC_CORE6_25_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 25)
#else
#error Invalid value for OSEE_TC_CORE6_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 25)
OSEE_DUMMY_ISR(_core6_, 25)
#endif /* OSEE_TC_CORE6_25_ISR_CAT */
#if (defined(OSEE_TC_CORE6_26_ISR_CAT))
#if (OSEE_TC_CORE6_26_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 26)
#elif (OSEE_TC_CORE6_26_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 26)
#else
#error Invalid value for OSEE_TC_CORE6_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 26)
OSEE_DUMMY_ISR(_core6_, 26)
#endif /* OSEE_TC_CORE6_26_ISR_CAT */
#if (defined(OSEE_TC_CORE6_27_ISR_CAT))
#if (OSEE_TC_CORE6_27_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 27)
#elif (OSEE_TC_CORE6_27_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 27)
#else
#error Invalid value for OSEE_TC_CORE6_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 27)
OSEE_DUMMY_ISR(_core6_, 27)
#endif /* OSEE_TC_CORE6_27_ISR_CAT */
#if (defined(OSEE_TC_CORE6_28_ISR_CAT))
#if (OSEE_TC_CORE6_28_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 28)
#elif (OSEE_TC_CORE6_28_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 28)
#else
#error Invalid value for OSEE_TC_CORE6_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 28)
OSEE_DUMMY_ISR(_core6_, 28)
#endif /* OSEE_TC_CORE6_28_ISR_CAT */
#if (defined(OSEE_TC_CORE6_29_ISR_CAT))
#if (OSEE_TC_CORE6_29_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 29)
#elif (OSEE_TC_CORE6_29_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 29)
#else
#error Invalid value for OSEE_TC_CORE6_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 29)
OSEE_DUMMY_ISR(_core6_, 29)
#endif /* OSEE_TC_CORE6_29_ISR_CAT */
#if (defined(OSEE_TC_CORE6_30_ISR_CAT))
#if (OSEE_TC_CORE6_30_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 30)
#elif (OSEE_TC_CORE6_30_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 30)
#else
#error Invalid value for OSEE_TC_CORE6_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 30)
OSEE_DUMMY_ISR(_core6_, 30)
#endif /* OSEE_TC_CORE6_30_ISR_CAT */
#if (defined(OSEE_TC_CORE6_31_ISR_CAT))
#if (OSEE_TC_CORE6_31_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 31)
#elif (OSEE_TC_CORE6_31_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 31)
#else
#error Invalid value for OSEE_TC_CORE6_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 31)
OSEE_DUMMY_ISR(_core6_, 31)
#endif /* OSEE_TC_CORE6_31_ISR_CAT */
#if (defined(OSEE_TC_CORE6_32_ISR_CAT))
#if (OSEE_TC_CORE6_32_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 32)
#elif (OSEE_TC_CORE6_32_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 32)
#else
#error Invalid value for OSEE_TC_CORE6_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 32)
OSEE_DUMMY_ISR(_core6_, 32)
#endif /* OSEE_TC_CORE6_32_ISR_CAT */
#if (defined(OSEE_TC_CORE6_33_ISR_CAT))
#if (OSEE_TC_CORE6_33_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 33)
#elif (OSEE_TC_CORE6_33_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 33)
#else
#error Invalid value for OSEE_TC_CORE6_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 33)
OSEE_DUMMY_ISR(_core6_, 33)
#endif /* OSEE_TC_CORE6_33_ISR_CAT */
#if (defined(OSEE_TC_CORE6_34_ISR_CAT))
#if (OSEE_TC_CORE6_34_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 34)
#elif (OSEE_TC_CORE6_34_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 34)
#else
#error Invalid value for OSEE_TC_CORE6_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 34)
OSEE_DUMMY_ISR(_core6_, 34)
#endif /* OSEE_TC_CORE6_34_ISR_CAT */
#if (defined(OSEE_TC_CORE6_35_ISR_CAT))
#if (OSEE_TC_CORE6_35_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 35)
#elif (OSEE_TC_CORE6_35_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 35)
#else
#error Invalid value for OSEE_TC_CORE6_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 35)
OSEE_DUMMY_ISR(_core6_, 35)
#endif /* OSEE_TC_CORE6_35_ISR_CAT */
#if (defined(OSEE_TC_CORE6_36_ISR_CAT))
#if (OSEE_TC_CORE6_36_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 36)
#elif (OSEE_TC_CORE6_36_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 36)
#else
#error Invalid value for OSEE_TC_CORE6_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 36)
OSEE_DUMMY_ISR(_core6_, 36)
#endif /* OSEE_TC_CORE6_36_ISR_CAT */
#if (defined(OSEE_TC_CORE6_37_ISR_CAT))
#if (OSEE_TC_CORE6_37_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 37)
#elif (OSEE_TC_CORE6_37_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 37)
#else
#error Invalid value for OSEE_TC_CORE6_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 37)
OSEE_DUMMY_ISR(_core6_, 37)
#endif /* OSEE_TC_CORE6_37_ISR_CAT */
#if (defined(OSEE_TC_CORE6_38_ISR_CAT))
#if (OSEE_TC_CORE6_38_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 38)
#elif (OSEE_TC_CORE6_38_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 38)
#else
#error Invalid value for OSEE_TC_CORE6_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 38)
OSEE_DUMMY_ISR(_core6_, 38)
#endif /* OSEE_TC_CORE6_38_ISR_CAT */
#if (defined(OSEE_TC_CORE6_39_ISR_CAT))
#if (OSEE_TC_CORE6_39_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 39)
#elif (OSEE_TC_CORE6_39_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 39)
#else
#error Invalid value for OSEE_TC_CORE6_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 39)
OSEE_DUMMY_ISR(_core6_, 39)
#endif /* OSEE_TC_CORE6_39_ISR_CAT */
#if (defined(OSEE_TC_CORE6_40_ISR_CAT))
#if (OSEE_TC_CORE6_40_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 40)
#elif (OSEE_TC_CORE6_40_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 40)
#else
#error Invalid value for OSEE_TC_CORE6_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 40)
OSEE_DUMMY_ISR(_core6_, 40)
#endif /* OSEE_TC_CORE6_40_ISR_CAT */
#if (defined(OSEE_TC_CORE6_41_ISR_CAT))
#if (OSEE_TC_CORE6_41_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 41)
#elif (OSEE_TC_CORE6_41_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 41)
#else
#error Invalid value for OSEE_TC_CORE6_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 41)
OSEE_DUMMY_ISR(_core6_, 41)
#endif /* OSEE_TC_CORE6_41_ISR_CAT */
#if (defined(OSEE_TC_CORE6_42_ISR_CAT))
#if (OSEE_TC_CORE6_42_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 42)
#elif (OSEE_TC_CORE6_42_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 42)
#else
#error Invalid value for OSEE_TC_CORE6_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 42)
OSEE_DUMMY_ISR(_core6_, 42)
#endif /* OSEE_TC_CORE6_42_ISR_CAT */
#if (defined(OSEE_TC_CORE6_43_ISR_CAT))
#if (OSEE_TC_CORE6_43_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 43)
#elif (OSEE_TC_CORE6_43_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 43)
#else
#error Invalid value for OSEE_TC_CORE6_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 43)
OSEE_DUMMY_ISR(_core6_, 43)
#endif /* OSEE_TC_CORE6_43_ISR_CAT */
#if (defined(OSEE_TC_CORE6_44_ISR_CAT))
#if (OSEE_TC_CORE6_44_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 44)
#elif (OSEE_TC_CORE6_44_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 44)
#else
#error Invalid value for OSEE_TC_CORE6_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 44)
OSEE_DUMMY_ISR(_core6_, 44)
#endif /* OSEE_TC_CORE6_44_ISR_CAT */
#if (defined(OSEE_TC_CORE6_45_ISR_CAT))
#if (OSEE_TC_CORE6_45_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 45)
#elif (OSEE_TC_CORE6_45_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 45)
#else
#error Invalid value for OSEE_TC_CORE6_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 45)
OSEE_DUMMY_ISR(_core6_, 45)
#endif /* OSEE_TC_CORE6_45_ISR_CAT */
#if (defined(OSEE_TC_CORE6_46_ISR_CAT))
#if (OSEE_TC_CORE6_46_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 46)
#elif (OSEE_TC_CORE6_46_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 46)
#else
#error Invalid value for OSEE_TC_CORE6_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 46)
OSEE_DUMMY_ISR(_core6_, 46)
#endif /* OSEE_TC_CORE6_46_ISR_CAT */
#if (defined(OSEE_TC_CORE6_47_ISR_CAT))
#if (OSEE_TC_CORE6_47_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 47)
#elif (OSEE_TC_CORE6_47_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 47)
#else
#error Invalid value for OSEE_TC_CORE6_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 47)
OSEE_DUMMY_ISR(_core6_, 47)
#endif /* OSEE_TC_CORE6_47_ISR_CAT */
#if (defined(OSEE_TC_CORE6_48_ISR_CAT))
#if (OSEE_TC_CORE6_48_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 48)
#elif (OSEE_TC_CORE6_48_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 48)
#else
#error Invalid value for OSEE_TC_CORE6_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 48)
OSEE_DUMMY_ISR(_core6_, 48)
#endif /* OSEE_TC_CORE6_48_ISR_CAT */
#if (defined(OSEE_TC_CORE6_49_ISR_CAT))
#if (OSEE_TC_CORE6_49_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 49)
#elif (OSEE_TC_CORE6_49_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 49)
#else
#error Invalid value for OSEE_TC_CORE6_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 49)
OSEE_DUMMY_ISR(_core6_, 49)
#endif /* OSEE_TC_CORE6_49_ISR_CAT */
#if (defined(OSEE_TC_CORE6_50_ISR_CAT))
#if (OSEE_TC_CORE6_50_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 50)
#elif (OSEE_TC_CORE6_50_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 50)
#else
#error Invalid value for OSEE_TC_CORE6_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 50)
OSEE_DUMMY_ISR(_core6_, 50)
#endif /* OSEE_TC_CORE6_50_ISR_CAT */
#if (defined(OSEE_TC_CORE6_51_ISR_CAT))
#if (OSEE_TC_CORE6_51_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 51)
#elif (OSEE_TC_CORE6_51_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 51)
#else
#error Invalid value for OSEE_TC_CORE6_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 51)
OSEE_DUMMY_ISR(_core6_, 51)
#endif /* OSEE_TC_CORE6_51_ISR_CAT */
#if (defined(OSEE_TC_CORE6_52_ISR_CAT))
#if (OSEE_TC_CORE6_52_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 52)
#elif (OSEE_TC_CORE6_52_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 52)
#else
#error Invalid value for OSEE_TC_CORE6_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 52)
OSEE_DUMMY_ISR(_core6_, 52)
#endif /* OSEE_TC_CORE6_52_ISR_CAT */
#if (defined(OSEE_TC_CORE6_53_ISR_CAT))
#if (OSEE_TC_CORE6_53_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 53)
#elif (OSEE_TC_CORE6_53_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 53)
#else
#error Invalid value for OSEE_TC_CORE6_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 53)
OSEE_DUMMY_ISR(_core6_, 53)
#endif /* OSEE_TC_CORE6_53_ISR_CAT */
#if (defined(OSEE_TC_CORE6_54_ISR_CAT))
#if (OSEE_TC_CORE6_54_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 54)
#elif (OSEE_TC_CORE6_54_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 54)
#else
#error Invalid value for OSEE_TC_CORE6_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 54)
OSEE_DUMMY_ISR(_core6_, 54)
#endif /* OSEE_TC_CORE6_54_ISR_CAT */
#if (defined(OSEE_TC_CORE6_55_ISR_CAT))
#if (OSEE_TC_CORE6_55_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 55)
#elif (OSEE_TC_CORE6_55_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 55)
#else
#error Invalid value for OSEE_TC_CORE6_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 55)
OSEE_DUMMY_ISR(_core6_, 55)
#endif /* OSEE_TC_CORE6_55_ISR_CAT */
#if (defined(OSEE_TC_CORE6_56_ISR_CAT))
#if (OSEE_TC_CORE6_56_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 56)
#elif (OSEE_TC_CORE6_56_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 56)
#else
#error Invalid value for OSEE_TC_CORE6_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 56)
OSEE_DUMMY_ISR(_core6_, 56)
#endif /* OSEE_TC_CORE6_56_ISR_CAT */
#if (defined(OSEE_TC_CORE6_57_ISR_CAT))
#if (OSEE_TC_CORE6_57_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 57)
#elif (OSEE_TC_CORE6_57_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 57)
#else
#error Invalid value for OSEE_TC_CORE6_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 57)
OSEE_DUMMY_ISR(_core6_, 57)
#endif /* OSEE_TC_CORE6_57_ISR_CAT */
#if (defined(OSEE_TC_CORE6_58_ISR_CAT))
#if (OSEE_TC_CORE6_58_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 58)
#elif (OSEE_TC_CORE6_58_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 58)
#else
#error Invalid value for OSEE_TC_CORE6_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 58)
OSEE_DUMMY_ISR(_core6_, 58)
#endif /* OSEE_TC_CORE6_58_ISR_CAT */
#if (defined(OSEE_TC_CORE6_59_ISR_CAT))
#if (OSEE_TC_CORE6_59_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 59)
#elif (OSEE_TC_CORE6_59_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 59)
#else
#error Invalid value for OSEE_TC_CORE6_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 59)
OSEE_DUMMY_ISR(_core6_, 59)
#endif /* OSEE_TC_CORE6_59_ISR_CAT */
#if (defined(OSEE_TC_CORE6_60_ISR_CAT))
#if (OSEE_TC_CORE6_60_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 60)
#elif (OSEE_TC_CORE6_60_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 60)
#else
#error Invalid value for OSEE_TC_CORE6_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 60)
OSEE_DUMMY_ISR(_core6_, 60)
#endif /* OSEE_TC_CORE6_60_ISR_CAT */
#if (defined(OSEE_TC_CORE6_61_ISR_CAT))
#if (OSEE_TC_CORE6_61_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 61)
#elif (OSEE_TC_CORE6_61_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 61)
#else
#error Invalid value for OSEE_TC_CORE6_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 61)
OSEE_DUMMY_ISR(_core6_, 61)
#endif /* OSEE_TC_CORE6_61_ISR_CAT */
#if (defined(OSEE_TC_CORE6_62_ISR_CAT))
#if (OSEE_TC_CORE6_62_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 62)
#elif (OSEE_TC_CORE6_62_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 62)
#else
#error Invalid value for OSEE_TC_CORE6_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 62)
OSEE_DUMMY_ISR(_core6_, 62)
#endif /* OSEE_TC_CORE6_62_ISR_CAT */
#if (defined(OSEE_TC_CORE6_63_ISR_CAT))
#if (OSEE_TC_CORE6_63_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 63)
#elif (OSEE_TC_CORE6_63_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 63)
#else
#error Invalid value for OSEE_TC_CORE6_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 63)
OSEE_DUMMY_ISR(_core6_, 63)
#endif /* OSEE_TC_CORE6_63_ISR_CAT */
#if (defined(OSEE_TC_CORE6_64_ISR_CAT))
#if (OSEE_TC_CORE6_64_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 64)
#elif (OSEE_TC_CORE6_64_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 64)
#else
#error Invalid value for OSEE_TC_CORE6_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 64)
OSEE_DUMMY_ISR(_core6_, 64)
#endif /* OSEE_TC_CORE6_64_ISR_CAT */
#if (defined(OSEE_TC_CORE6_65_ISR_CAT))
#if (OSEE_TC_CORE6_65_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 65)
#elif (OSEE_TC_CORE6_65_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 65)
#else
#error Invalid value for OSEE_TC_CORE6_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 65)
OSEE_DUMMY_ISR(_core6_, 65)
#endif /* OSEE_TC_CORE6_65_ISR_CAT */
#if (defined(OSEE_TC_CORE6_66_ISR_CAT))
#if (OSEE_TC_CORE6_66_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 66)
#elif (OSEE_TC_CORE6_66_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 66)
#else
#error Invalid value for OSEE_TC_CORE6_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 66)
OSEE_DUMMY_ISR(_core6_, 66)
#endif /* OSEE_TC_CORE6_66_ISR_CAT */
#if (defined(OSEE_TC_CORE6_67_ISR_CAT))
#if (OSEE_TC_CORE6_67_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 67)
#elif (OSEE_TC_CORE6_67_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 67)
#else
#error Invalid value for OSEE_TC_CORE6_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 67)
OSEE_DUMMY_ISR(_core6_, 67)
#endif /* OSEE_TC_CORE6_67_ISR_CAT */
#if (defined(OSEE_TC_CORE6_68_ISR_CAT))
#if (OSEE_TC_CORE6_68_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 68)
#elif (OSEE_TC_CORE6_68_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 68)
#else
#error Invalid value for OSEE_TC_CORE6_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 68)
OSEE_DUMMY_ISR(_core6_, 68)
#endif /* OSEE_TC_CORE6_68_ISR_CAT */
#if (defined(OSEE_TC_CORE6_69_ISR_CAT))
#if (OSEE_TC_CORE6_69_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 69)
#elif (OSEE_TC_CORE6_69_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 69)
#else
#error Invalid value for OSEE_TC_CORE6_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 69)
OSEE_DUMMY_ISR(_core6_, 69)
#endif /* OSEE_TC_CORE6_69_ISR_CAT */
#if (defined(OSEE_TC_CORE6_70_ISR_CAT))
#if (OSEE_TC_CORE6_70_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 70)
#elif (OSEE_TC_CORE6_70_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 70)
#else
#error Invalid value for OSEE_TC_CORE6_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 70)
OSEE_DUMMY_ISR(_core6_, 70)
#endif /* OSEE_TC_CORE6_70_ISR_CAT */
#if (defined(OSEE_TC_CORE6_71_ISR_CAT))
#if (OSEE_TC_CORE6_71_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 71)
#elif (OSEE_TC_CORE6_71_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 71)
#else
#error Invalid value for OSEE_TC_CORE6_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 71)
OSEE_DUMMY_ISR(_core6_, 71)
#endif /* OSEE_TC_CORE6_71_ISR_CAT */
#if (defined(OSEE_TC_CORE6_72_ISR_CAT))
#if (OSEE_TC_CORE6_72_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 72)
#elif (OSEE_TC_CORE6_72_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 72)
#else
#error Invalid value for OSEE_TC_CORE6_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 72)
OSEE_DUMMY_ISR(_core6_, 72)
#endif /* OSEE_TC_CORE6_72_ISR_CAT */
#if (defined(OSEE_TC_CORE6_73_ISR_CAT))
#if (OSEE_TC_CORE6_73_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 73)
#elif (OSEE_TC_CORE6_73_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 73)
#else
#error Invalid value for OSEE_TC_CORE6_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 73)
OSEE_DUMMY_ISR(_core6_, 73)
#endif /* OSEE_TC_CORE6_73_ISR_CAT */
#if (defined(OSEE_TC_CORE6_74_ISR_CAT))
#if (OSEE_TC_CORE6_74_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 74)
#elif (OSEE_TC_CORE6_74_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 74)
#else
#error Invalid value for OSEE_TC_CORE6_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 74)
OSEE_DUMMY_ISR(_core6_, 74)
#endif /* OSEE_TC_CORE6_74_ISR_CAT */
#if (defined(OSEE_TC_CORE6_75_ISR_CAT))
#if (OSEE_TC_CORE6_75_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 75)
#elif (OSEE_TC_CORE6_75_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 75)
#else
#error Invalid value for OSEE_TC_CORE6_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 75)
OSEE_DUMMY_ISR(_core6_, 75)
#endif /* OSEE_TC_CORE6_75_ISR_CAT */
#if (defined(OSEE_TC_CORE6_76_ISR_CAT))
#if (OSEE_TC_CORE6_76_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 76)
#elif (OSEE_TC_CORE6_76_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 76)
#else
#error Invalid value for OSEE_TC_CORE6_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 76)
OSEE_DUMMY_ISR(_core6_, 76)
#endif /* OSEE_TC_CORE6_76_ISR_CAT */
#if (defined(OSEE_TC_CORE6_77_ISR_CAT))
#if (OSEE_TC_CORE6_77_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 77)
#elif (OSEE_TC_CORE6_77_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 77)
#else
#error Invalid value for OSEE_TC_CORE6_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 77)
OSEE_DUMMY_ISR(_core6_, 77)
#endif /* OSEE_TC_CORE6_77_ISR_CAT */
#if (defined(OSEE_TC_CORE6_78_ISR_CAT))
#if (OSEE_TC_CORE6_78_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 78)
#elif (OSEE_TC_CORE6_78_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 78)
#else
#error Invalid value for OSEE_TC_CORE6_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 78)
OSEE_DUMMY_ISR(_core6_, 78)
#endif /* OSEE_TC_CORE6_78_ISR_CAT */
#if (defined(OSEE_TC_CORE6_79_ISR_CAT))
#if (OSEE_TC_CORE6_79_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 79)
#elif (OSEE_TC_CORE6_79_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 79)
#else
#error Invalid value for OSEE_TC_CORE6_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 79)
OSEE_DUMMY_ISR(_core6_, 79)
#endif /* OSEE_TC_CORE6_79_ISR_CAT */
#if (defined(OSEE_TC_CORE6_80_ISR_CAT))
#if (OSEE_TC_CORE6_80_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 80)
#elif (OSEE_TC_CORE6_80_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 80)
#else
#error Invalid value for OSEE_TC_CORE6_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 80)
OSEE_DUMMY_ISR(_core6_, 80)
#endif /* OSEE_TC_CORE6_80_ISR_CAT */
#if (defined(OSEE_TC_CORE6_81_ISR_CAT))
#if (OSEE_TC_CORE6_81_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 81)
#elif (OSEE_TC_CORE6_81_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 81)
#else
#error Invalid value for OSEE_TC_CORE6_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 81)
OSEE_DUMMY_ISR(_core6_, 81)
#endif /* OSEE_TC_CORE6_81_ISR_CAT */
#if (defined(OSEE_TC_CORE6_82_ISR_CAT))
#if (OSEE_TC_CORE6_82_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 82)
#elif (OSEE_TC_CORE6_82_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 82)
#else
#error Invalid value for OSEE_TC_CORE6_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 82)
OSEE_DUMMY_ISR(_core6_, 82)
#endif /* OSEE_TC_CORE6_82_ISR_CAT */
#if (defined(OSEE_TC_CORE6_83_ISR_CAT))
#if (OSEE_TC_CORE6_83_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 83)
#elif (OSEE_TC_CORE6_83_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 83)
#else
#error Invalid value for OSEE_TC_CORE6_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 83)
OSEE_DUMMY_ISR(_core6_, 83)
#endif /* OSEE_TC_CORE6_83_ISR_CAT */
#if (defined(OSEE_TC_CORE6_84_ISR_CAT))
#if (OSEE_TC_CORE6_84_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 84)
#elif (OSEE_TC_CORE6_84_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 84)
#else
#error Invalid value for OSEE_TC_CORE6_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 84)
OSEE_DUMMY_ISR(_core6_, 84)
#endif /* OSEE_TC_CORE6_84_ISR_CAT */
#if (defined(OSEE_TC_CORE6_85_ISR_CAT))
#if (OSEE_TC_CORE6_85_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 85)
#elif (OSEE_TC_CORE6_85_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 85)
#else
#error Invalid value for OSEE_TC_CORE6_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 85)
OSEE_DUMMY_ISR(_core6_, 85)
#endif /* OSEE_TC_CORE6_85_ISR_CAT */
#if (defined(OSEE_TC_CORE6_86_ISR_CAT))
#if (OSEE_TC_CORE6_86_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 86)
#elif (OSEE_TC_CORE6_86_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 86)
#else
#error Invalid value for OSEE_TC_CORE6_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 86)
OSEE_DUMMY_ISR(_core6_, 86)
#endif /* OSEE_TC_CORE6_86_ISR_CAT */
#if (defined(OSEE_TC_CORE6_87_ISR_CAT))
#if (OSEE_TC_CORE6_87_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 87)
#elif (OSEE_TC_CORE6_87_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 87)
#else
#error Invalid value for OSEE_TC_CORE6_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 87)
OSEE_DUMMY_ISR(_core6_, 87)
#endif /* OSEE_TC_CORE6_87_ISR_CAT */
#if (defined(OSEE_TC_CORE6_88_ISR_CAT))
#if (OSEE_TC_CORE6_88_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 88)
#elif (OSEE_TC_CORE6_88_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 88)
#else
#error Invalid value for OSEE_TC_CORE6_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 88)
OSEE_DUMMY_ISR(_core6_, 88)
#endif /* OSEE_TC_CORE6_88_ISR_CAT */
#if (defined(OSEE_TC_CORE6_89_ISR_CAT))
#if (OSEE_TC_CORE6_89_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 89)
#elif (OSEE_TC_CORE6_89_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 89)
#else
#error Invalid value for OSEE_TC_CORE6_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 89)
OSEE_DUMMY_ISR(_core6_, 89)
#endif /* OSEE_TC_CORE6_89_ISR_CAT */
#if (defined(OSEE_TC_CORE6_90_ISR_CAT))
#if (OSEE_TC_CORE6_90_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 90)
#elif (OSEE_TC_CORE6_90_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 90)
#else
#error Invalid value for OSEE_TC_CORE6_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 90)
OSEE_DUMMY_ISR(_core6_, 90)
#endif /* OSEE_TC_CORE6_90_ISR_CAT */
#if (defined(OSEE_TC_CORE6_91_ISR_CAT))
#if (OSEE_TC_CORE6_91_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 91)
#elif (OSEE_TC_CORE6_91_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 91)
#else
#error Invalid value for OSEE_TC_CORE6_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 91)
OSEE_DUMMY_ISR(_core6_, 91)
#endif /* OSEE_TC_CORE6_91_ISR_CAT */
#if (defined(OSEE_TC_CORE6_92_ISR_CAT))
#if (OSEE_TC_CORE6_92_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 92)
#elif (OSEE_TC_CORE6_92_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 92)
#else
#error Invalid value for OSEE_TC_CORE6_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 92)
OSEE_DUMMY_ISR(_core6_, 92)
#endif /* OSEE_TC_CORE6_92_ISR_CAT */
#if (defined(OSEE_TC_CORE6_93_ISR_CAT))
#if (OSEE_TC_CORE6_93_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 93)
#elif (OSEE_TC_CORE6_93_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 93)
#else
#error Invalid value for OSEE_TC_CORE6_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 93)
OSEE_DUMMY_ISR(_core6_, 93)
#endif /* OSEE_TC_CORE6_93_ISR_CAT */
#if (defined(OSEE_TC_CORE6_94_ISR_CAT))
#if (OSEE_TC_CORE6_94_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 94)
#elif (OSEE_TC_CORE6_94_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 94)
#else
#error Invalid value for OSEE_TC_CORE6_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 94)
OSEE_DUMMY_ISR(_core6_, 94)
#endif /* OSEE_TC_CORE6_94_ISR_CAT */
#if (defined(OSEE_TC_CORE6_95_ISR_CAT))
#if (OSEE_TC_CORE6_95_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 95)
#elif (OSEE_TC_CORE6_95_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 95)
#else
#error Invalid value for OSEE_TC_CORE6_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 95)
OSEE_DUMMY_ISR(_core6_, 95)
#endif /* OSEE_TC_CORE6_95_ISR_CAT */
#if (defined(OSEE_TC_CORE6_96_ISR_CAT))
#if (OSEE_TC_CORE6_96_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 96)
#elif (OSEE_TC_CORE6_96_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 96)
#else
#error Invalid value for OSEE_TC_CORE6_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 96)
OSEE_DUMMY_ISR(_core6_, 96)
#endif /* OSEE_TC_CORE6_96_ISR_CAT */
#if (defined(OSEE_TC_CORE6_97_ISR_CAT))
#if (OSEE_TC_CORE6_97_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 97)
#elif (OSEE_TC_CORE6_97_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 97)
#else
#error Invalid value for OSEE_TC_CORE6_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 97)
OSEE_DUMMY_ISR(_core6_, 97)
#endif /* OSEE_TC_CORE6_97_ISR_CAT */
#if (defined(OSEE_TC_CORE6_98_ISR_CAT))
#if (OSEE_TC_CORE6_98_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 98)
#elif (OSEE_TC_CORE6_98_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 98)
#else
#error Invalid value for OSEE_TC_CORE6_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 98)
OSEE_DUMMY_ISR(_core6_, 98)
#endif /* OSEE_TC_CORE6_98_ISR_CAT */
#if (defined(OSEE_TC_CORE6_99_ISR_CAT))
#if (OSEE_TC_CORE6_99_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 99)
#elif (OSEE_TC_CORE6_99_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 99)
#else
#error Invalid value for OSEE_TC_CORE6_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 99)
OSEE_DUMMY_ISR(_core6_, 99)
#endif /* OSEE_TC_CORE6_99_ISR_CAT */
#if (defined(OSEE_TC_CORE6_100_ISR_CAT))
#if (OSEE_TC_CORE6_100_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 100)
#elif (OSEE_TC_CORE6_100_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 100)
#else
#error Invalid value for OSEE_TC_CORE6_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 100)
OSEE_DUMMY_ISR(_core6_, 100)
#endif /* OSEE_TC_CORE6_100_ISR_CAT */
#if (defined(OSEE_TC_CORE6_101_ISR_CAT))
#if (OSEE_TC_CORE6_101_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 101)
#elif (OSEE_TC_CORE6_101_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 101)
#else
#error Invalid value for OSEE_TC_CORE6_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 101)
OSEE_DUMMY_ISR(_core6_, 101)
#endif /* OSEE_TC_CORE6_101_ISR_CAT */
#if (defined(OSEE_TC_CORE6_102_ISR_CAT))
#if (OSEE_TC_CORE6_102_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 102)
#elif (OSEE_TC_CORE6_102_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 102)
#else
#error Invalid value for OSEE_TC_CORE6_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 102)
OSEE_DUMMY_ISR(_core6_, 102)
#endif /* OSEE_TC_CORE6_102_ISR_CAT */
#if (defined(OSEE_TC_CORE6_103_ISR_CAT))
#if (OSEE_TC_CORE6_103_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 103)
#elif (OSEE_TC_CORE6_103_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 103)
#else
#error Invalid value for OSEE_TC_CORE6_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 103)
OSEE_DUMMY_ISR(_core6_, 103)
#endif /* OSEE_TC_CORE6_103_ISR_CAT */
#if (defined(OSEE_TC_CORE6_104_ISR_CAT))
#if (OSEE_TC_CORE6_104_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 104)
#elif (OSEE_TC_CORE6_104_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 104)
#else
#error Invalid value for OSEE_TC_CORE6_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 104)
OSEE_DUMMY_ISR(_core6_, 104)
#endif /* OSEE_TC_CORE6_104_ISR_CAT */
#if (defined(OSEE_TC_CORE6_105_ISR_CAT))
#if (OSEE_TC_CORE6_105_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 105)
#elif (OSEE_TC_CORE6_105_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 105)
#else
#error Invalid value for OSEE_TC_CORE6_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 105)
OSEE_DUMMY_ISR(_core6_, 105)
#endif /* OSEE_TC_CORE6_105_ISR_CAT */
#if (defined(OSEE_TC_CORE6_106_ISR_CAT))
#if (OSEE_TC_CORE6_106_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 106)
#elif (OSEE_TC_CORE6_106_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 106)
#else
#error Invalid value for OSEE_TC_CORE6_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 106)
OSEE_DUMMY_ISR(_core6_, 106)
#endif /* OSEE_TC_CORE6_106_ISR_CAT */
#if (defined(OSEE_TC_CORE6_107_ISR_CAT))
#if (OSEE_TC_CORE6_107_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 107)
#elif (OSEE_TC_CORE6_107_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 107)
#else
#error Invalid value for OSEE_TC_CORE6_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 107)
OSEE_DUMMY_ISR(_core6_, 107)
#endif /* OSEE_TC_CORE6_107_ISR_CAT */
#if (defined(OSEE_TC_CORE6_108_ISR_CAT))
#if (OSEE_TC_CORE6_108_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 108)
#elif (OSEE_TC_CORE6_108_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 108)
#else
#error Invalid value for OSEE_TC_CORE6_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 108)
OSEE_DUMMY_ISR(_core6_, 108)
#endif /* OSEE_TC_CORE6_108_ISR_CAT */
#if (defined(OSEE_TC_CORE6_109_ISR_CAT))
#if (OSEE_TC_CORE6_109_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 109)
#elif (OSEE_TC_CORE6_109_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 109)
#else
#error Invalid value for OSEE_TC_CORE6_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 109)
OSEE_DUMMY_ISR(_core6_, 109)
#endif /* OSEE_TC_CORE6_109_ISR_CAT */
#if (defined(OSEE_TC_CORE6_110_ISR_CAT))
#if (OSEE_TC_CORE6_110_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 110)
#elif (OSEE_TC_CORE6_110_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 110)
#else
#error Invalid value for OSEE_TC_CORE6_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 110)
OSEE_DUMMY_ISR(_core6_, 110)
#endif /* OSEE_TC_CORE6_110_ISR_CAT */
#if (defined(OSEE_TC_CORE6_111_ISR_CAT))
#if (OSEE_TC_CORE6_111_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 111)
#elif (OSEE_TC_CORE6_111_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 111)
#else
#error Invalid value for OSEE_TC_CORE6_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 111)
OSEE_DUMMY_ISR(_core6_, 111)
#endif /* OSEE_TC_CORE6_111_ISR_CAT */
#if (defined(OSEE_TC_CORE6_112_ISR_CAT))
#if (OSEE_TC_CORE6_112_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 112)
#elif (OSEE_TC_CORE6_112_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 112)
#else
#error Invalid value for OSEE_TC_CORE6_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 112)
OSEE_DUMMY_ISR(_core6_, 112)
#endif /* OSEE_TC_CORE6_112_ISR_CAT */
#if (defined(OSEE_TC_CORE6_113_ISR_CAT))
#if (OSEE_TC_CORE6_113_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 113)
#elif (OSEE_TC_CORE6_113_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 113)
#else
#error Invalid value for OSEE_TC_CORE6_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 113)
OSEE_DUMMY_ISR(_core6_, 113)
#endif /* OSEE_TC_CORE6_113_ISR_CAT */
#if (defined(OSEE_TC_CORE6_114_ISR_CAT))
#if (OSEE_TC_CORE6_114_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 114)
#elif (OSEE_TC_CORE6_114_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 114)
#else
#error Invalid value for OSEE_TC_CORE6_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 114)
OSEE_DUMMY_ISR(_core6_, 114)
#endif /* OSEE_TC_CORE6_114_ISR_CAT */
#if (defined(OSEE_TC_CORE6_115_ISR_CAT))
#if (OSEE_TC_CORE6_115_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 115)
#elif (OSEE_TC_CORE6_115_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 115)
#else
#error Invalid value for OSEE_TC_CORE6_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 115)
OSEE_DUMMY_ISR(_core6_, 115)
#endif /* OSEE_TC_CORE6_115_ISR_CAT */
#if (defined(OSEE_TC_CORE6_116_ISR_CAT))
#if (OSEE_TC_CORE6_116_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 116)
#elif (OSEE_TC_CORE6_116_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 116)
#else
#error Invalid value for OSEE_TC_CORE6_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 116)
OSEE_DUMMY_ISR(_core6_, 116)
#endif /* OSEE_TC_CORE6_116_ISR_CAT */
#if (defined(OSEE_TC_CORE6_117_ISR_CAT))
#if (OSEE_TC_CORE6_117_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 117)
#elif (OSEE_TC_CORE6_117_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 117)
#else
#error Invalid value for OSEE_TC_CORE6_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 117)
OSEE_DUMMY_ISR(_core6_, 117)
#endif /* OSEE_TC_CORE6_117_ISR_CAT */
#if (defined(OSEE_TC_CORE6_118_ISR_CAT))
#if (OSEE_TC_CORE6_118_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 118)
#elif (OSEE_TC_CORE6_118_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 118)
#else
#error Invalid value for OSEE_TC_CORE6_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 118)
OSEE_DUMMY_ISR(_core6_, 118)
#endif /* OSEE_TC_CORE6_118_ISR_CAT */
#if (defined(OSEE_TC_CORE6_119_ISR_CAT))
#if (OSEE_TC_CORE6_119_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 119)
#elif (OSEE_TC_CORE6_119_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 119)
#else
#error Invalid value for OSEE_TC_CORE6_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 119)
OSEE_DUMMY_ISR(_core6_, 119)
#endif /* OSEE_TC_CORE6_119_ISR_CAT */
#if (defined(OSEE_TC_CORE6_120_ISR_CAT))
#if (OSEE_TC_CORE6_120_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 120)
#elif (OSEE_TC_CORE6_120_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 120)
#else
#error Invalid value for OSEE_TC_CORE6_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 120)
OSEE_DUMMY_ISR(_core6_, 120)
#endif /* OSEE_TC_CORE6_120_ISR_CAT */
#if (defined(OSEE_TC_CORE6_121_ISR_CAT))
#if (OSEE_TC_CORE6_121_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 121)
#elif (OSEE_TC_CORE6_121_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 121)
#else
#error Invalid value for OSEE_TC_CORE6_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 121)
OSEE_DUMMY_ISR(_core6_, 121)
#endif /* OSEE_TC_CORE6_121_ISR_CAT */
#if (defined(OSEE_TC_CORE6_122_ISR_CAT))
#if (OSEE_TC_CORE6_122_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 122)
#elif (OSEE_TC_CORE6_122_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 122)
#else
#error Invalid value for OSEE_TC_CORE6_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 122)
OSEE_DUMMY_ISR(_core6_, 122)
#endif /* OSEE_TC_CORE6_122_ISR_CAT */
#if (defined(OSEE_TC_CORE6_123_ISR_CAT))
#if (OSEE_TC_CORE6_123_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 123)
#elif (OSEE_TC_CORE6_123_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 123)
#else
#error Invalid value for OSEE_TC_CORE6_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 123)
OSEE_DUMMY_ISR(_core6_, 123)
#endif /* OSEE_TC_CORE6_123_ISR_CAT */
#if (defined(OSEE_TC_CORE6_124_ISR_CAT))
#if (OSEE_TC_CORE6_124_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 124)
#elif (OSEE_TC_CORE6_124_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 124)
#else
#error Invalid value for OSEE_TC_CORE6_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 124)
OSEE_DUMMY_ISR(_core6_, 124)
#endif /* OSEE_TC_CORE6_124_ISR_CAT */
#if (defined(OSEE_TC_CORE6_125_ISR_CAT))
#if (OSEE_TC_CORE6_125_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 125)
#elif (OSEE_TC_CORE6_125_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 125)
#else
#error Invalid value for OSEE_TC_CORE6_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 125)
OSEE_DUMMY_ISR(_core6_, 125)
#endif /* OSEE_TC_CORE6_125_ISR_CAT */
#if (defined(OSEE_TC_CORE6_126_ISR_CAT))
#if (OSEE_TC_CORE6_126_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 126)
#elif (OSEE_TC_CORE6_126_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 126)
#else
#error Invalid value for OSEE_TC_CORE6_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 126)
OSEE_DUMMY_ISR(_core6_, 126)
#endif /* OSEE_TC_CORE6_126_ISR_CAT */
#if (defined(OSEE_TC_CORE6_127_ISR_CAT))
#if (OSEE_TC_CORE6_127_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 127)
#elif (OSEE_TC_CORE6_127_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 127)
#else
#error Invalid value for OSEE_TC_CORE6_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 127)
OSEE_DUMMY_ISR(_core6_, 127)
#endif /* OSEE_TC_CORE6_127_ISR_CAT */
#if (defined(OSEE_TC_CORE6_128_ISR_CAT))
#if (OSEE_TC_CORE6_128_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 128)
#elif (OSEE_TC_CORE6_128_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 128)
#else
#error Invalid value for OSEE_TC_CORE6_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 128)
OSEE_DUMMY_ISR(_core6_, 128)
#endif /* OSEE_TC_CORE6_128_ISR_CAT */
#if (defined(OSEE_TC_CORE6_129_ISR_CAT))
#if (OSEE_TC_CORE6_129_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 129)
#elif (OSEE_TC_CORE6_129_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 129)
#else
#error Invalid value for OSEE_TC_CORE6_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 129)
OSEE_DUMMY_ISR(_core6_, 129)
#endif /* OSEE_TC_CORE6_129_ISR_CAT */
#if (defined(OSEE_TC_CORE6_130_ISR_CAT))
#if (OSEE_TC_CORE6_130_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 130)
#elif (OSEE_TC_CORE6_130_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 130)
#else
#error Invalid value for OSEE_TC_CORE6_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 130)
OSEE_DUMMY_ISR(_core6_, 130)
#endif /* OSEE_TC_CORE6_130_ISR_CAT */
#if (defined(OSEE_TC_CORE6_131_ISR_CAT))
#if (OSEE_TC_CORE6_131_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 131)
#elif (OSEE_TC_CORE6_131_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 131)
#else
#error Invalid value for OSEE_TC_CORE6_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 131)
OSEE_DUMMY_ISR(_core6_, 131)
#endif /* OSEE_TC_CORE6_131_ISR_CAT */
#if (defined(OSEE_TC_CORE6_132_ISR_CAT))
#if (OSEE_TC_CORE6_132_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 132)
#elif (OSEE_TC_CORE6_132_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 132)
#else
#error Invalid value for OSEE_TC_CORE6_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 132)
OSEE_DUMMY_ISR(_core6_, 132)
#endif /* OSEE_TC_CORE6_132_ISR_CAT */
#if (defined(OSEE_TC_CORE6_133_ISR_CAT))
#if (OSEE_TC_CORE6_133_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 133)
#elif (OSEE_TC_CORE6_133_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 133)
#else
#error Invalid value for OSEE_TC_CORE6_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 133)
OSEE_DUMMY_ISR(_core6_, 133)
#endif /* OSEE_TC_CORE6_133_ISR_CAT */
#if (defined(OSEE_TC_CORE6_134_ISR_CAT))
#if (OSEE_TC_CORE6_134_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 134)
#elif (OSEE_TC_CORE6_134_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 134)
#else
#error Invalid value for OSEE_TC_CORE6_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 134)
OSEE_DUMMY_ISR(_core6_, 134)
#endif /* OSEE_TC_CORE6_134_ISR_CAT */
#if (defined(OSEE_TC_CORE6_135_ISR_CAT))
#if (OSEE_TC_CORE6_135_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 135)
#elif (OSEE_TC_CORE6_135_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 135)
#else
#error Invalid value for OSEE_TC_CORE6_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 135)
OSEE_DUMMY_ISR(_core6_, 135)
#endif /* OSEE_TC_CORE6_135_ISR_CAT */
#if (defined(OSEE_TC_CORE6_136_ISR_CAT))
#if (OSEE_TC_CORE6_136_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 136)
#elif (OSEE_TC_CORE6_136_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 136)
#else
#error Invalid value for OSEE_TC_CORE6_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 136)
OSEE_DUMMY_ISR(_core6_, 136)
#endif /* OSEE_TC_CORE6_136_ISR_CAT */
#if (defined(OSEE_TC_CORE6_137_ISR_CAT))
#if (OSEE_TC_CORE6_137_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 137)
#elif (OSEE_TC_CORE6_137_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 137)
#else
#error Invalid value for OSEE_TC_CORE6_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 137)
OSEE_DUMMY_ISR(_core6_, 137)
#endif /* OSEE_TC_CORE6_137_ISR_CAT */
#if (defined(OSEE_TC_CORE6_138_ISR_CAT))
#if (OSEE_TC_CORE6_138_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 138)
#elif (OSEE_TC_CORE6_138_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 138)
#else
#error Invalid value for OSEE_TC_CORE6_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 138)
OSEE_DUMMY_ISR(_core6_, 138)
#endif /* OSEE_TC_CORE6_138_ISR_CAT */
#if (defined(OSEE_TC_CORE6_139_ISR_CAT))
#if (OSEE_TC_CORE6_139_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 139)
#elif (OSEE_TC_CORE6_139_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 139)
#else
#error Invalid value for OSEE_TC_CORE6_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 139)
OSEE_DUMMY_ISR(_core6_, 139)
#endif /* OSEE_TC_CORE6_139_ISR_CAT */
#if (defined(OSEE_TC_CORE6_140_ISR_CAT))
#if (OSEE_TC_CORE6_140_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 140)
#elif (OSEE_TC_CORE6_140_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 140)
#else
#error Invalid value for OSEE_TC_CORE6_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 140)
OSEE_DUMMY_ISR(_core6_, 140)
#endif /* OSEE_TC_CORE6_140_ISR_CAT */
#if (defined(OSEE_TC_CORE6_141_ISR_CAT))
#if (OSEE_TC_CORE6_141_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 141)
#elif (OSEE_TC_CORE6_141_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 141)
#else
#error Invalid value for OSEE_TC_CORE6_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 141)
OSEE_DUMMY_ISR(_core6_, 141)
#endif /* OSEE_TC_CORE6_141_ISR_CAT */
#if (defined(OSEE_TC_CORE6_142_ISR_CAT))
#if (OSEE_TC_CORE6_142_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 142)
#elif (OSEE_TC_CORE6_142_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 142)
#else
#error Invalid value for OSEE_TC_CORE6_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 142)
OSEE_DUMMY_ISR(_core6_, 142)
#endif /* OSEE_TC_CORE6_142_ISR_CAT */
#if (defined(OSEE_TC_CORE6_143_ISR_CAT))
#if (OSEE_TC_CORE6_143_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 143)
#elif (OSEE_TC_CORE6_143_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 143)
#else
#error Invalid value for OSEE_TC_CORE6_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 143)
OSEE_DUMMY_ISR(_core6_, 143)
#endif /* OSEE_TC_CORE6_143_ISR_CAT */
#if (defined(OSEE_TC_CORE6_144_ISR_CAT))
#if (OSEE_TC_CORE6_144_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 144)
#elif (OSEE_TC_CORE6_144_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 144)
#else
#error Invalid value for OSEE_TC_CORE6_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 144)
OSEE_DUMMY_ISR(_core6_, 144)
#endif /* OSEE_TC_CORE6_144_ISR_CAT */
#if (defined(OSEE_TC_CORE6_145_ISR_CAT))
#if (OSEE_TC_CORE6_145_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 145)
#elif (OSEE_TC_CORE6_145_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 145)
#else
#error Invalid value for OSEE_TC_CORE6_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 145)
OSEE_DUMMY_ISR(_core6_, 145)
#endif /* OSEE_TC_CORE6_145_ISR_CAT */
#if (defined(OSEE_TC_CORE6_146_ISR_CAT))
#if (OSEE_TC_CORE6_146_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 146)
#elif (OSEE_TC_CORE6_146_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 146)
#else
#error Invalid value for OSEE_TC_CORE6_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 146)
OSEE_DUMMY_ISR(_core6_, 146)
#endif /* OSEE_TC_CORE6_146_ISR_CAT */
#if (defined(OSEE_TC_CORE6_147_ISR_CAT))
#if (OSEE_TC_CORE6_147_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 147)
#elif (OSEE_TC_CORE6_147_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 147)
#else
#error Invalid value for OSEE_TC_CORE6_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 147)
OSEE_DUMMY_ISR(_core6_, 147)
#endif /* OSEE_TC_CORE6_147_ISR_CAT */
#if (defined(OSEE_TC_CORE6_148_ISR_CAT))
#if (OSEE_TC_CORE6_148_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 148)
#elif (OSEE_TC_CORE6_148_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 148)
#else
#error Invalid value for OSEE_TC_CORE6_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 148)
OSEE_DUMMY_ISR(_core6_, 148)
#endif /* OSEE_TC_CORE6_148_ISR_CAT */
#if (defined(OSEE_TC_CORE6_149_ISR_CAT))
#if (OSEE_TC_CORE6_149_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 149)
#elif (OSEE_TC_CORE6_149_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 149)
#else
#error Invalid value for OSEE_TC_CORE6_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 149)
OSEE_DUMMY_ISR(_core6_, 149)
#endif /* OSEE_TC_CORE6_149_ISR_CAT */
#if (defined(OSEE_TC_CORE6_150_ISR_CAT))
#if (OSEE_TC_CORE6_150_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 150)
#elif (OSEE_TC_CORE6_150_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 150)
#else
#error Invalid value for OSEE_TC_CORE6_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 150)
OSEE_DUMMY_ISR(_core6_, 150)
#endif /* OSEE_TC_CORE6_150_ISR_CAT */
#if (defined(OSEE_TC_CORE6_151_ISR_CAT))
#if (OSEE_TC_CORE6_151_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 151)
#elif (OSEE_TC_CORE6_151_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 151)
#else
#error Invalid value for OSEE_TC_CORE6_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 151)
OSEE_DUMMY_ISR(_core6_, 151)
#endif /* OSEE_TC_CORE6_151_ISR_CAT */
#if (defined(OSEE_TC_CORE6_152_ISR_CAT))
#if (OSEE_TC_CORE6_152_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 152)
#elif (OSEE_TC_CORE6_152_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 152)
#else
#error Invalid value for OSEE_TC_CORE6_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 152)
OSEE_DUMMY_ISR(_core6_, 152)
#endif /* OSEE_TC_CORE6_152_ISR_CAT */
#if (defined(OSEE_TC_CORE6_153_ISR_CAT))
#if (OSEE_TC_CORE6_153_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 153)
#elif (OSEE_TC_CORE6_153_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 153)
#else
#error Invalid value for OSEE_TC_CORE6_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 153)
OSEE_DUMMY_ISR(_core6_, 153)
#endif /* OSEE_TC_CORE6_153_ISR_CAT */
#if (defined(OSEE_TC_CORE6_154_ISR_CAT))
#if (OSEE_TC_CORE6_154_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 154)
#elif (OSEE_TC_CORE6_154_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 154)
#else
#error Invalid value for OSEE_TC_CORE6_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 154)
OSEE_DUMMY_ISR(_core6_, 154)
#endif /* OSEE_TC_CORE6_154_ISR_CAT */
#if (defined(OSEE_TC_CORE6_155_ISR_CAT))
#if (OSEE_TC_CORE6_155_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 155)
#elif (OSEE_TC_CORE6_155_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 155)
#else
#error Invalid value for OSEE_TC_CORE6_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 155)
OSEE_DUMMY_ISR(_core6_, 155)
#endif /* OSEE_TC_CORE6_155_ISR_CAT */
#if (defined(OSEE_TC_CORE6_156_ISR_CAT))
#if (OSEE_TC_CORE6_156_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 156)
#elif (OSEE_TC_CORE6_156_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 156)
#else
#error Invalid value for OSEE_TC_CORE6_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 156)
OSEE_DUMMY_ISR(_core6_, 156)
#endif /* OSEE_TC_CORE6_156_ISR_CAT */
#if (defined(OSEE_TC_CORE6_157_ISR_CAT))
#if (OSEE_TC_CORE6_157_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 157)
#elif (OSEE_TC_CORE6_157_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 157)
#else
#error Invalid value for OSEE_TC_CORE6_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 157)
OSEE_DUMMY_ISR(_core6_, 157)
#endif /* OSEE_TC_CORE6_157_ISR_CAT */
#if (defined(OSEE_TC_CORE6_158_ISR_CAT))
#if (OSEE_TC_CORE6_158_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 158)
#elif (OSEE_TC_CORE6_158_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 158)
#else
#error Invalid value for OSEE_TC_CORE6_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 158)
OSEE_DUMMY_ISR(_core6_, 158)
#endif /* OSEE_TC_CORE6_158_ISR_CAT */
#if (defined(OSEE_TC_CORE6_159_ISR_CAT))
#if (OSEE_TC_CORE6_159_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 159)
#elif (OSEE_TC_CORE6_159_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 159)
#else
#error Invalid value for OSEE_TC_CORE6_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 159)
OSEE_DUMMY_ISR(_core6_, 159)
#endif /* OSEE_TC_CORE6_159_ISR_CAT */
#if (defined(OSEE_TC_CORE6_160_ISR_CAT))
#if (OSEE_TC_CORE6_160_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 160)
#elif (OSEE_TC_CORE6_160_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 160)
#else
#error Invalid value for OSEE_TC_CORE6_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 160)
OSEE_DUMMY_ISR(_core6_, 160)
#endif /* OSEE_TC_CORE6_160_ISR_CAT */
#if (defined(OSEE_TC_CORE6_161_ISR_CAT))
#if (OSEE_TC_CORE6_161_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 161)
#elif (OSEE_TC_CORE6_161_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 161)
#else
#error Invalid value for OSEE_TC_CORE6_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 161)
OSEE_DUMMY_ISR(_core6_, 161)
#endif /* OSEE_TC_CORE6_161_ISR_CAT */
#if (defined(OSEE_TC_CORE6_162_ISR_CAT))
#if (OSEE_TC_CORE6_162_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 162)
#elif (OSEE_TC_CORE6_162_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 162)
#else
#error Invalid value for OSEE_TC_CORE6_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 162)
OSEE_DUMMY_ISR(_core6_, 162)
#endif /* OSEE_TC_CORE6_162_ISR_CAT */
#if (defined(OSEE_TC_CORE6_163_ISR_CAT))
#if (OSEE_TC_CORE6_163_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 163)
#elif (OSEE_TC_CORE6_163_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 163)
#else
#error Invalid value for OSEE_TC_CORE6_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 163)
OSEE_DUMMY_ISR(_core6_, 163)
#endif /* OSEE_TC_CORE6_163_ISR_CAT */
#if (defined(OSEE_TC_CORE6_164_ISR_CAT))
#if (OSEE_TC_CORE6_164_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 164)
#elif (OSEE_TC_CORE6_164_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 164)
#else
#error Invalid value for OSEE_TC_CORE6_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 164)
OSEE_DUMMY_ISR(_core6_, 164)
#endif /* OSEE_TC_CORE6_164_ISR_CAT */
#if (defined(OSEE_TC_CORE6_165_ISR_CAT))
#if (OSEE_TC_CORE6_165_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 165)
#elif (OSEE_TC_CORE6_165_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 165)
#else
#error Invalid value for OSEE_TC_CORE6_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 165)
OSEE_DUMMY_ISR(_core6_, 165)
#endif /* OSEE_TC_CORE6_165_ISR_CAT */
#if (defined(OSEE_TC_CORE6_166_ISR_CAT))
#if (OSEE_TC_CORE6_166_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 166)
#elif (OSEE_TC_CORE6_166_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 166)
#else
#error Invalid value for OSEE_TC_CORE6_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 166)
OSEE_DUMMY_ISR(_core6_, 166)
#endif /* OSEE_TC_CORE6_166_ISR_CAT */
#if (defined(OSEE_TC_CORE6_167_ISR_CAT))
#if (OSEE_TC_CORE6_167_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 167)
#elif (OSEE_TC_CORE6_167_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 167)
#else
#error Invalid value for OSEE_TC_CORE6_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 167)
OSEE_DUMMY_ISR(_core6_, 167)
#endif /* OSEE_TC_CORE6_167_ISR_CAT */
#if (defined(OSEE_TC_CORE6_168_ISR_CAT))
#if (OSEE_TC_CORE6_168_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 168)
#elif (OSEE_TC_CORE6_168_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 168)
#else
#error Invalid value for OSEE_TC_CORE6_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 168)
OSEE_DUMMY_ISR(_core6_, 168)
#endif /* OSEE_TC_CORE6_168_ISR_CAT */
#if (defined(OSEE_TC_CORE6_169_ISR_CAT))
#if (OSEE_TC_CORE6_169_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 169)
#elif (OSEE_TC_CORE6_169_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 169)
#else
#error Invalid value for OSEE_TC_CORE6_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 169)
OSEE_DUMMY_ISR(_core6_, 169)
#endif /* OSEE_TC_CORE6_169_ISR_CAT */
#if (defined(OSEE_TC_CORE6_170_ISR_CAT))
#if (OSEE_TC_CORE6_170_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 170)
#elif (OSEE_TC_CORE6_170_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 170)
#else
#error Invalid value for OSEE_TC_CORE6_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 170)
OSEE_DUMMY_ISR(_core6_, 170)
#endif /* OSEE_TC_CORE6_170_ISR_CAT */
#if (defined(OSEE_TC_CORE6_171_ISR_CAT))
#if (OSEE_TC_CORE6_171_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 171)
#elif (OSEE_TC_CORE6_171_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 171)
#else
#error Invalid value for OSEE_TC_CORE6_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 171)
OSEE_DUMMY_ISR(_core6_, 171)
#endif /* OSEE_TC_CORE6_171_ISR_CAT */
#if (defined(OSEE_TC_CORE6_172_ISR_CAT))
#if (OSEE_TC_CORE6_172_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 172)
#elif (OSEE_TC_CORE6_172_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 172)
#else
#error Invalid value for OSEE_TC_CORE6_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 172)
OSEE_DUMMY_ISR(_core6_, 172)
#endif /* OSEE_TC_CORE6_172_ISR_CAT */
#if (defined(OSEE_TC_CORE6_173_ISR_CAT))
#if (OSEE_TC_CORE6_173_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 173)
#elif (OSEE_TC_CORE6_173_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 173)
#else
#error Invalid value for OSEE_TC_CORE6_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 173)
OSEE_DUMMY_ISR(_core6_, 173)
#endif /* OSEE_TC_CORE6_173_ISR_CAT */
#if (defined(OSEE_TC_CORE6_174_ISR_CAT))
#if (OSEE_TC_CORE6_174_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 174)
#elif (OSEE_TC_CORE6_174_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 174)
#else
#error Invalid value for OSEE_TC_CORE6_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 174)
OSEE_DUMMY_ISR(_core6_, 174)
#endif /* OSEE_TC_CORE6_174_ISR_CAT */
#if (defined(OSEE_TC_CORE6_175_ISR_CAT))
#if (OSEE_TC_CORE6_175_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 175)
#elif (OSEE_TC_CORE6_175_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 175)
#else
#error Invalid value for OSEE_TC_CORE6_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 175)
OSEE_DUMMY_ISR(_core6_, 175)
#endif /* OSEE_TC_CORE6_175_ISR_CAT */
#if (defined(OSEE_TC_CORE6_176_ISR_CAT))
#if (OSEE_TC_CORE6_176_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 176)
#elif (OSEE_TC_CORE6_176_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 176)
#else
#error Invalid value for OSEE_TC_CORE6_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 176)
OSEE_DUMMY_ISR(_core6_, 176)
#endif /* OSEE_TC_CORE6_176_ISR_CAT */
#if (defined(OSEE_TC_CORE6_177_ISR_CAT))
#if (OSEE_TC_CORE6_177_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 177)
#elif (OSEE_TC_CORE6_177_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 177)
#else
#error Invalid value for OSEE_TC_CORE6_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 177)
OSEE_DUMMY_ISR(_core6_, 177)
#endif /* OSEE_TC_CORE6_177_ISR_CAT */
#if (defined(OSEE_TC_CORE6_178_ISR_CAT))
#if (OSEE_TC_CORE6_178_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 178)
#elif (OSEE_TC_CORE6_178_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 178)
#else
#error Invalid value for OSEE_TC_CORE6_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 178)
OSEE_DUMMY_ISR(_core6_, 178)
#endif /* OSEE_TC_CORE6_178_ISR_CAT */
#if (defined(OSEE_TC_CORE6_179_ISR_CAT))
#if (OSEE_TC_CORE6_179_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 179)
#elif (OSEE_TC_CORE6_179_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 179)
#else
#error Invalid value for OSEE_TC_CORE6_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 179)
OSEE_DUMMY_ISR(_core6_, 179)
#endif /* OSEE_TC_CORE6_179_ISR_CAT */
#if (defined(OSEE_TC_CORE6_180_ISR_CAT))
#if (OSEE_TC_CORE6_180_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 180)
#elif (OSEE_TC_CORE6_180_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 180)
#else
#error Invalid value for OSEE_TC_CORE6_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 180)
OSEE_DUMMY_ISR(_core6_, 180)
#endif /* OSEE_TC_CORE6_180_ISR_CAT */
#if (defined(OSEE_TC_CORE6_181_ISR_CAT))
#if (OSEE_TC_CORE6_181_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 181)
#elif (OSEE_TC_CORE6_181_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 181)
#else
#error Invalid value for OSEE_TC_CORE6_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 181)
OSEE_DUMMY_ISR(_core6_, 181)
#endif /* OSEE_TC_CORE6_181_ISR_CAT */
#if (defined(OSEE_TC_CORE6_182_ISR_CAT))
#if (OSEE_TC_CORE6_182_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 182)
#elif (OSEE_TC_CORE6_182_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 182)
#else
#error Invalid value for OSEE_TC_CORE6_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 182)
OSEE_DUMMY_ISR(_core6_, 182)
#endif /* OSEE_TC_CORE6_182_ISR_CAT */
#if (defined(OSEE_TC_CORE6_183_ISR_CAT))
#if (OSEE_TC_CORE6_183_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 183)
#elif (OSEE_TC_CORE6_183_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 183)
#else
#error Invalid value for OSEE_TC_CORE6_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 183)
OSEE_DUMMY_ISR(_core6_, 183)
#endif /* OSEE_TC_CORE6_183_ISR_CAT */
#if (defined(OSEE_TC_CORE6_184_ISR_CAT))
#if (OSEE_TC_CORE6_184_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 184)
#elif (OSEE_TC_CORE6_184_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 184)
#else
#error Invalid value for OSEE_TC_CORE6_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 184)
OSEE_DUMMY_ISR(_core6_, 184)
#endif /* OSEE_TC_CORE6_184_ISR_CAT */
#if (defined(OSEE_TC_CORE6_185_ISR_CAT))
#if (OSEE_TC_CORE6_185_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 185)
#elif (OSEE_TC_CORE6_185_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 185)
#else
#error Invalid value for OSEE_TC_CORE6_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 185)
OSEE_DUMMY_ISR(_core6_, 185)
#endif /* OSEE_TC_CORE6_185_ISR_CAT */
#if (defined(OSEE_TC_CORE6_186_ISR_CAT))
#if (OSEE_TC_CORE6_186_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 186)
#elif (OSEE_TC_CORE6_186_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 186)
#else
#error Invalid value for OSEE_TC_CORE6_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 186)
OSEE_DUMMY_ISR(_core6_, 186)
#endif /* OSEE_TC_CORE6_186_ISR_CAT */
#if (defined(OSEE_TC_CORE6_187_ISR_CAT))
#if (OSEE_TC_CORE6_187_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 187)
#elif (OSEE_TC_CORE6_187_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 187)
#else
#error Invalid value for OSEE_TC_CORE6_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 187)
OSEE_DUMMY_ISR(_core6_, 187)
#endif /* OSEE_TC_CORE6_187_ISR_CAT */
#if (defined(OSEE_TC_CORE6_188_ISR_CAT))
#if (OSEE_TC_CORE6_188_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 188)
#elif (OSEE_TC_CORE6_188_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 188)
#else
#error Invalid value for OSEE_TC_CORE6_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 188)
OSEE_DUMMY_ISR(_core6_, 188)
#endif /* OSEE_TC_CORE6_188_ISR_CAT */
#if (defined(OSEE_TC_CORE6_189_ISR_CAT))
#if (OSEE_TC_CORE6_189_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 189)
#elif (OSEE_TC_CORE6_189_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 189)
#else
#error Invalid value for OSEE_TC_CORE6_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 189)
OSEE_DUMMY_ISR(_core6_, 189)
#endif /* OSEE_TC_CORE6_189_ISR_CAT */
#if (defined(OSEE_TC_CORE6_190_ISR_CAT))
#if (OSEE_TC_CORE6_190_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 190)
#elif (OSEE_TC_CORE6_190_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 190)
#else
#error Invalid value for OSEE_TC_CORE6_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 190)
OSEE_DUMMY_ISR(_core6_, 190)
#endif /* OSEE_TC_CORE6_190_ISR_CAT */
#if (defined(OSEE_TC_CORE6_191_ISR_CAT))
#if (OSEE_TC_CORE6_191_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 191)
#elif (OSEE_TC_CORE6_191_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 191)
#else
#error Invalid value for OSEE_TC_CORE6_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 191)
OSEE_DUMMY_ISR(_core6_, 191)
#endif /* OSEE_TC_CORE6_191_ISR_CAT */
#if (defined(OSEE_TC_CORE6_192_ISR_CAT))
#if (OSEE_TC_CORE6_192_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 192)
#elif (OSEE_TC_CORE6_192_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 192)
#else
#error Invalid value for OSEE_TC_CORE6_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 192)
OSEE_DUMMY_ISR(_core6_, 192)
#endif /* OSEE_TC_CORE6_192_ISR_CAT */
#if (defined(OSEE_TC_CORE6_193_ISR_CAT))
#if (OSEE_TC_CORE6_193_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 193)
#elif (OSEE_TC_CORE6_193_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 193)
#else
#error Invalid value for OSEE_TC_CORE6_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 193)
OSEE_DUMMY_ISR(_core6_, 193)
#endif /* OSEE_TC_CORE6_193_ISR_CAT */
#if (defined(OSEE_TC_CORE6_194_ISR_CAT))
#if (OSEE_TC_CORE6_194_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 194)
#elif (OSEE_TC_CORE6_194_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 194)
#else
#error Invalid value for OSEE_TC_CORE6_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 194)
OSEE_DUMMY_ISR(_core6_, 194)
#endif /* OSEE_TC_CORE6_194_ISR_CAT */
#if (defined(OSEE_TC_CORE6_195_ISR_CAT))
#if (OSEE_TC_CORE6_195_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 195)
#elif (OSEE_TC_CORE6_195_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 195)
#else
#error Invalid value for OSEE_TC_CORE6_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 195)
OSEE_DUMMY_ISR(_core6_, 195)
#endif /* OSEE_TC_CORE6_195_ISR_CAT */
#if (defined(OSEE_TC_CORE6_196_ISR_CAT))
#if (OSEE_TC_CORE6_196_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 196)
#elif (OSEE_TC_CORE6_196_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 196)
#else
#error Invalid value for OSEE_TC_CORE6_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 196)
OSEE_DUMMY_ISR(_core6_, 196)
#endif /* OSEE_TC_CORE6_196_ISR_CAT */
#if (defined(OSEE_TC_CORE6_197_ISR_CAT))
#if (OSEE_TC_CORE6_197_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 197)
#elif (OSEE_TC_CORE6_197_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 197)
#else
#error Invalid value for OSEE_TC_CORE6_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 197)
OSEE_DUMMY_ISR(_core6_, 197)
#endif /* OSEE_TC_CORE6_197_ISR_CAT */
#if (defined(OSEE_TC_CORE6_198_ISR_CAT))
#if (OSEE_TC_CORE6_198_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 198)
#elif (OSEE_TC_CORE6_198_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 198)
#else
#error Invalid value for OSEE_TC_CORE6_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 198)
OSEE_DUMMY_ISR(_core6_, 198)
#endif /* OSEE_TC_CORE6_198_ISR_CAT */
#if (defined(OSEE_TC_CORE6_199_ISR_CAT))
#if (OSEE_TC_CORE6_199_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 199)
#elif (OSEE_TC_CORE6_199_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 199)
#else
#error Invalid value for OSEE_TC_CORE6_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 199)
OSEE_DUMMY_ISR(_core6_, 199)
#endif /* OSEE_TC_CORE6_199_ISR_CAT */
#if (defined(OSEE_TC_CORE6_200_ISR_CAT))
#if (OSEE_TC_CORE6_200_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 200)
#elif (OSEE_TC_CORE6_200_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 200)
#else
#error Invalid value for OSEE_TC_CORE6_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 200)
OSEE_DUMMY_ISR(_core6_, 200)
#endif /* OSEE_TC_CORE6_200_ISR_CAT */
#if (defined(OSEE_TC_CORE6_201_ISR_CAT))
#if (OSEE_TC_CORE6_201_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 201)
#elif (OSEE_TC_CORE6_201_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 201)
#else
#error Invalid value for OSEE_TC_CORE6_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 201)
OSEE_DUMMY_ISR(_core6_, 201)
#endif /* OSEE_TC_CORE6_201_ISR_CAT */
#if (defined(OSEE_TC_CORE6_202_ISR_CAT))
#if (OSEE_TC_CORE6_202_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 202)
#elif (OSEE_TC_CORE6_202_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 202)
#else
#error Invalid value for OSEE_TC_CORE6_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 202)
OSEE_DUMMY_ISR(_core6_, 202)
#endif /* OSEE_TC_CORE6_202_ISR_CAT */
#if (defined(OSEE_TC_CORE6_203_ISR_CAT))
#if (OSEE_TC_CORE6_203_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 203)
#elif (OSEE_TC_CORE6_203_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 203)
#else
#error Invalid value for OSEE_TC_CORE6_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 203)
OSEE_DUMMY_ISR(_core6_, 203)
#endif /* OSEE_TC_CORE6_203_ISR_CAT */
#if (defined(OSEE_TC_CORE6_204_ISR_CAT))
#if (OSEE_TC_CORE6_204_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 204)
#elif (OSEE_TC_CORE6_204_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 204)
#else
#error Invalid value for OSEE_TC_CORE6_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 204)
OSEE_DUMMY_ISR(_core6_, 204)
#endif /* OSEE_TC_CORE6_204_ISR_CAT */
#if (defined(OSEE_TC_CORE6_205_ISR_CAT))
#if (OSEE_TC_CORE6_205_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 205)
#elif (OSEE_TC_CORE6_205_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 205)
#else
#error Invalid value for OSEE_TC_CORE6_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 205)
OSEE_DUMMY_ISR(_core6_, 205)
#endif /* OSEE_TC_CORE6_205_ISR_CAT */
#if (defined(OSEE_TC_CORE6_206_ISR_CAT))
#if (OSEE_TC_CORE6_206_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 206)
#elif (OSEE_TC_CORE6_206_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 206)
#else
#error Invalid value for OSEE_TC_CORE6_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 206)
OSEE_DUMMY_ISR(_core6_, 206)
#endif /* OSEE_TC_CORE6_206_ISR_CAT */
#if (defined(OSEE_TC_CORE6_207_ISR_CAT))
#if (OSEE_TC_CORE6_207_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 207)
#elif (OSEE_TC_CORE6_207_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 207)
#else
#error Invalid value for OSEE_TC_CORE6_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 207)
OSEE_DUMMY_ISR(_core6_, 207)
#endif /* OSEE_TC_CORE6_207_ISR_CAT */
#if (defined(OSEE_TC_CORE6_208_ISR_CAT))
#if (OSEE_TC_CORE6_208_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 208)
#elif (OSEE_TC_CORE6_208_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 208)
#else
#error Invalid value for OSEE_TC_CORE6_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 208)
OSEE_DUMMY_ISR(_core6_, 208)
#endif /* OSEE_TC_CORE6_208_ISR_CAT */
#if (defined(OSEE_TC_CORE6_209_ISR_CAT))
#if (OSEE_TC_CORE6_209_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 209)
#elif (OSEE_TC_CORE6_209_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 209)
#else
#error Invalid value for OSEE_TC_CORE6_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 209)
OSEE_DUMMY_ISR(_core6_, 209)
#endif /* OSEE_TC_CORE6_209_ISR_CAT */
#if (defined(OSEE_TC_CORE6_210_ISR_CAT))
#if (OSEE_TC_CORE6_210_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 210)
#elif (OSEE_TC_CORE6_210_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 210)
#else
#error Invalid value for OSEE_TC_CORE6_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 210)
OSEE_DUMMY_ISR(_core6_, 210)
#endif /* OSEE_TC_CORE6_210_ISR_CAT */
#if (defined(OSEE_TC_CORE6_211_ISR_CAT))
#if (OSEE_TC_CORE6_211_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 211)
#elif (OSEE_TC_CORE6_211_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 211)
#else
#error Invalid value for OSEE_TC_CORE6_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 211)
OSEE_DUMMY_ISR(_core6_, 211)
#endif /* OSEE_TC_CORE6_211_ISR_CAT */
#if (defined(OSEE_TC_CORE6_212_ISR_CAT))
#if (OSEE_TC_CORE6_212_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 212)
#elif (OSEE_TC_CORE6_212_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 212)
#else
#error Invalid value for OSEE_TC_CORE6_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 212)
OSEE_DUMMY_ISR(_core6_, 212)
#endif /* OSEE_TC_CORE6_212_ISR_CAT */
#if (defined(OSEE_TC_CORE6_213_ISR_CAT))
#if (OSEE_TC_CORE6_213_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 213)
#elif (OSEE_TC_CORE6_213_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 213)
#else
#error Invalid value for OSEE_TC_CORE6_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 213)
OSEE_DUMMY_ISR(_core6_, 213)
#endif /* OSEE_TC_CORE6_213_ISR_CAT */
#if (defined(OSEE_TC_CORE6_214_ISR_CAT))
#if (OSEE_TC_CORE6_214_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 214)
#elif (OSEE_TC_CORE6_214_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 214)
#else
#error Invalid value for OSEE_TC_CORE6_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 214)
OSEE_DUMMY_ISR(_core6_, 214)
#endif /* OSEE_TC_CORE6_214_ISR_CAT */
#if (defined(OSEE_TC_CORE6_215_ISR_CAT))
#if (OSEE_TC_CORE6_215_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 215)
#elif (OSEE_TC_CORE6_215_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 215)
#else
#error Invalid value for OSEE_TC_CORE6_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 215)
OSEE_DUMMY_ISR(_core6_, 215)
#endif /* OSEE_TC_CORE6_215_ISR_CAT */
#if (defined(OSEE_TC_CORE6_216_ISR_CAT))
#if (OSEE_TC_CORE6_216_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 216)
#elif (OSEE_TC_CORE6_216_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 216)
#else
#error Invalid value for OSEE_TC_CORE6_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 216)
OSEE_DUMMY_ISR(_core6_, 216)
#endif /* OSEE_TC_CORE6_216_ISR_CAT */
#if (defined(OSEE_TC_CORE6_217_ISR_CAT))
#if (OSEE_TC_CORE6_217_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 217)
#elif (OSEE_TC_CORE6_217_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 217)
#else
#error Invalid value for OSEE_TC_CORE6_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 217)
OSEE_DUMMY_ISR(_core6_, 217)
#endif /* OSEE_TC_CORE6_217_ISR_CAT */
#if (defined(OSEE_TC_CORE6_218_ISR_CAT))
#if (OSEE_TC_CORE6_218_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 218)
#elif (OSEE_TC_CORE6_218_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 218)
#else
#error Invalid value for OSEE_TC_CORE6_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 218)
OSEE_DUMMY_ISR(_core6_, 218)
#endif /* OSEE_TC_CORE6_218_ISR_CAT */
#if (defined(OSEE_TC_CORE6_219_ISR_CAT))
#if (OSEE_TC_CORE6_219_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 219)
#elif (OSEE_TC_CORE6_219_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 219)
#else
#error Invalid value for OSEE_TC_CORE6_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 219)
OSEE_DUMMY_ISR(_core6_, 219)
#endif /* OSEE_TC_CORE6_219_ISR_CAT */
#if (defined(OSEE_TC_CORE6_220_ISR_CAT))
#if (OSEE_TC_CORE6_220_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 220)
#elif (OSEE_TC_CORE6_220_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 220)
#else
#error Invalid value for OSEE_TC_CORE6_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 220)
OSEE_DUMMY_ISR(_core6_, 220)
#endif /* OSEE_TC_CORE6_220_ISR_CAT */
#if (defined(OSEE_TC_CORE6_221_ISR_CAT))
#if (OSEE_TC_CORE6_221_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 221)
#elif (OSEE_TC_CORE6_221_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 221)
#else
#error Invalid value for OSEE_TC_CORE6_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 221)
OSEE_DUMMY_ISR(_core6_, 221)
#endif /* OSEE_TC_CORE6_221_ISR_CAT */
#if (defined(OSEE_TC_CORE6_222_ISR_CAT))
#if (OSEE_TC_CORE6_222_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 222)
#elif (OSEE_TC_CORE6_222_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 222)
#else
#error Invalid value for OSEE_TC_CORE6_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 222)
OSEE_DUMMY_ISR(_core6_, 222)
#endif /* OSEE_TC_CORE6_222_ISR_CAT */
#if (defined(OSEE_TC_CORE6_223_ISR_CAT))
#if (OSEE_TC_CORE6_223_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 223)
#elif (OSEE_TC_CORE6_223_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 223)
#else
#error Invalid value for OSEE_TC_CORE6_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 223)
OSEE_DUMMY_ISR(_core6_, 223)
#endif /* OSEE_TC_CORE6_223_ISR_CAT */
#if (defined(OSEE_TC_CORE6_224_ISR_CAT))
#if (OSEE_TC_CORE6_224_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 224)
#elif (OSEE_TC_CORE6_224_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 224)
#else
#error Invalid value for OSEE_TC_CORE6_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 224)
OSEE_DUMMY_ISR(_core6_, 224)
#endif /* OSEE_TC_CORE6_224_ISR_CAT */
#if (defined(OSEE_TC_CORE6_225_ISR_CAT))
#if (OSEE_TC_CORE6_225_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 225)
#elif (OSEE_TC_CORE6_225_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 225)
#else
#error Invalid value for OSEE_TC_CORE6_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 225)
OSEE_DUMMY_ISR(_core6_, 225)
#endif /* OSEE_TC_CORE6_225_ISR_CAT */
#if (defined(OSEE_TC_CORE6_226_ISR_CAT))
#if (OSEE_TC_CORE6_226_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 226)
#elif (OSEE_TC_CORE6_226_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 226)
#else
#error Invalid value for OSEE_TC_CORE6_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 226)
OSEE_DUMMY_ISR(_core6_, 226)
#endif /* OSEE_TC_CORE6_226_ISR_CAT */
#if (defined(OSEE_TC_CORE6_227_ISR_CAT))
#if (OSEE_TC_CORE6_227_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 227)
#elif (OSEE_TC_CORE6_227_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 227)
#else
#error Invalid value for OSEE_TC_CORE6_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 227)
OSEE_DUMMY_ISR(_core6_, 227)
#endif /* OSEE_TC_CORE6_227_ISR_CAT */
#if (defined(OSEE_TC_CORE6_228_ISR_CAT))
#if (OSEE_TC_CORE6_228_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 228)
#elif (OSEE_TC_CORE6_228_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 228)
#else
#error Invalid value for OSEE_TC_CORE6_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 228)
OSEE_DUMMY_ISR(_core6_, 228)
#endif /* OSEE_TC_CORE6_228_ISR_CAT */
#if (defined(OSEE_TC_CORE6_229_ISR_CAT))
#if (OSEE_TC_CORE6_229_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 229)
#elif (OSEE_TC_CORE6_229_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 229)
#else
#error Invalid value for OSEE_TC_CORE6_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 229)
OSEE_DUMMY_ISR(_core6_, 229)
#endif /* OSEE_TC_CORE6_229_ISR_CAT */
#if (defined(OSEE_TC_CORE6_230_ISR_CAT))
#if (OSEE_TC_CORE6_230_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 230)
#elif (OSEE_TC_CORE6_230_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 230)
#else
#error Invalid value for OSEE_TC_CORE6_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 230)
OSEE_DUMMY_ISR(_core6_, 230)
#endif /* OSEE_TC_CORE6_230_ISR_CAT */
#if (defined(OSEE_TC_CORE6_231_ISR_CAT))
#if (OSEE_TC_CORE6_231_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 231)
#elif (OSEE_TC_CORE6_231_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 231)
#else
#error Invalid value for OSEE_TC_CORE6_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 231)
OSEE_DUMMY_ISR(_core6_, 231)
#endif /* OSEE_TC_CORE6_231_ISR_CAT */
#if (defined(OSEE_TC_CORE6_232_ISR_CAT))
#if (OSEE_TC_CORE6_232_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 232)
#elif (OSEE_TC_CORE6_232_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 232)
#else
#error Invalid value for OSEE_TC_CORE6_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 232)
OSEE_DUMMY_ISR(_core6_, 232)
#endif /* OSEE_TC_CORE6_232_ISR_CAT */
#if (defined(OSEE_TC_CORE6_233_ISR_CAT))
#if (OSEE_TC_CORE6_233_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 233)
#elif (OSEE_TC_CORE6_233_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 233)
#else
#error Invalid value for OSEE_TC_CORE6_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 233)
OSEE_DUMMY_ISR(_core6_, 233)
#endif /* OSEE_TC_CORE6_233_ISR_CAT */
#if (defined(OSEE_TC_CORE6_234_ISR_CAT))
#if (OSEE_TC_CORE6_234_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 234)
#elif (OSEE_TC_CORE6_234_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 234)
#else
#error Invalid value for OSEE_TC_CORE6_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 234)
OSEE_DUMMY_ISR(_core6_, 234)
#endif /* OSEE_TC_CORE6_234_ISR_CAT */
#if (defined(OSEE_TC_CORE6_235_ISR_CAT))
#if (OSEE_TC_CORE6_235_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 235)
#elif (OSEE_TC_CORE6_235_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 235)
#else
#error Invalid value for OSEE_TC_CORE6_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 235)
OSEE_DUMMY_ISR(_core6_, 235)
#endif /* OSEE_TC_CORE6_235_ISR_CAT */
#if (defined(OSEE_TC_CORE6_236_ISR_CAT))
#if (OSEE_TC_CORE6_236_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 236)
#elif (OSEE_TC_CORE6_236_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 236)
#else
#error Invalid value for OSEE_TC_CORE6_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 236)
OSEE_DUMMY_ISR(_core6_, 236)
#endif /* OSEE_TC_CORE6_236_ISR_CAT */
#if (defined(OSEE_TC_CORE6_237_ISR_CAT))
#if (OSEE_TC_CORE6_237_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 237)
#elif (OSEE_TC_CORE6_237_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 237)
#else
#error Invalid value for OSEE_TC_CORE6_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 237)
OSEE_DUMMY_ISR(_core6_, 237)
#endif /* OSEE_TC_CORE6_237_ISR_CAT */
#if (defined(OSEE_TC_CORE6_238_ISR_CAT))
#if (OSEE_TC_CORE6_238_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 238)
#elif (OSEE_TC_CORE6_238_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 238)
#else
#error Invalid value for OSEE_TC_CORE6_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 238)
OSEE_DUMMY_ISR(_core6_, 238)
#endif /* OSEE_TC_CORE6_238_ISR_CAT */
#if (defined(OSEE_TC_CORE6_239_ISR_CAT))
#if (OSEE_TC_CORE6_239_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 239)
#elif (OSEE_TC_CORE6_239_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 239)
#else
#error Invalid value for OSEE_TC_CORE6_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 239)
OSEE_DUMMY_ISR(_core6_, 239)
#endif /* OSEE_TC_CORE6_239_ISR_CAT */
#if (defined(OSEE_TC_CORE6_240_ISR_CAT))
#if (OSEE_TC_CORE6_240_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 240)
#elif (OSEE_TC_CORE6_240_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 240)
#else
#error Invalid value for OSEE_TC_CORE6_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 240)
OSEE_DUMMY_ISR(_core6_, 240)
#endif /* OSEE_TC_CORE6_240_ISR_CAT */
#if (defined(OSEE_TC_CORE6_241_ISR_CAT))
#if (OSEE_TC_CORE6_241_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 241)
#elif (OSEE_TC_CORE6_241_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 241)
#else
#error Invalid value for OSEE_TC_CORE6_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 241)
OSEE_DUMMY_ISR(_core6_, 241)
#endif /* OSEE_TC_CORE6_241_ISR_CAT */
#if (defined(OSEE_TC_CORE6_242_ISR_CAT))
#if (OSEE_TC_CORE6_242_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 242)
#elif (OSEE_TC_CORE6_242_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 242)
#else
#error Invalid value for OSEE_TC_CORE6_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 242)
OSEE_DUMMY_ISR(_core6_, 242)
#endif /* OSEE_TC_CORE6_242_ISR_CAT */
#if (defined(OSEE_TC_CORE6_243_ISR_CAT))
#if (OSEE_TC_CORE6_243_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 243)
#elif (OSEE_TC_CORE6_243_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 243)
#else
#error Invalid value for OSEE_TC_CORE6_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 243)
OSEE_DUMMY_ISR(_core6_, 243)
#endif /* OSEE_TC_CORE6_243_ISR_CAT */
#if (defined(OSEE_TC_CORE6_244_ISR_CAT))
#if (OSEE_TC_CORE6_244_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 244)
#elif (OSEE_TC_CORE6_244_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 244)
#else
#error Invalid value for OSEE_TC_CORE6_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 244)
OSEE_DUMMY_ISR(_core6_, 244)
#endif /* OSEE_TC_CORE6_244_ISR_CAT */
#if (defined(OSEE_TC_CORE6_245_ISR_CAT))
#if (OSEE_TC_CORE6_245_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 245)
#elif (OSEE_TC_CORE6_245_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 245)
#else
#error Invalid value for OSEE_TC_CORE6_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 245)
OSEE_DUMMY_ISR(_core6_, 245)
#endif /* OSEE_TC_CORE6_245_ISR_CAT */
#if (defined(OSEE_TC_CORE6_246_ISR_CAT))
#if (OSEE_TC_CORE6_246_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 246)
#elif (OSEE_TC_CORE6_246_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 246)
#else
#error Invalid value for OSEE_TC_CORE6_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 246)
OSEE_DUMMY_ISR(_core6_, 246)
#endif /* OSEE_TC_CORE6_246_ISR_CAT */
#if (defined(OSEE_TC_CORE6_247_ISR_CAT))
#if (OSEE_TC_CORE6_247_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 247)
#elif (OSEE_TC_CORE6_247_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 247)
#else
#error Invalid value for OSEE_TC_CORE6_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 247)
OSEE_DUMMY_ISR(_core6_, 247)
#endif /* OSEE_TC_CORE6_247_ISR_CAT */
#if (defined(OSEE_TC_CORE6_248_ISR_CAT))
#if (OSEE_TC_CORE6_248_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 248)
#elif (OSEE_TC_CORE6_248_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 248)
#else
#error Invalid value for OSEE_TC_CORE6_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 248)
OSEE_DUMMY_ISR(_core6_, 248)
#endif /* OSEE_TC_CORE6_248_ISR_CAT */
#if (defined(OSEE_TC_CORE6_249_ISR_CAT))
#if (OSEE_TC_CORE6_249_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 249)
#elif (OSEE_TC_CORE6_249_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 249)
#else
#error Invalid value for OSEE_TC_CORE6_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 249)
OSEE_DUMMY_ISR(_core6_, 249)
#endif /* OSEE_TC_CORE6_249_ISR_CAT */
#if (defined(OSEE_TC_CORE6_250_ISR_CAT))
#if (OSEE_TC_CORE6_250_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 250)
#elif (OSEE_TC_CORE6_250_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 250)
#else
#error Invalid value for OSEE_TC_CORE6_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 250)
OSEE_DUMMY_ISR(_core6_, 250)
#endif /* OSEE_TC_CORE6_250_ISR_CAT */
#if (defined(OSEE_TC_CORE6_251_ISR_CAT))
#if (OSEE_TC_CORE6_251_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 251)
#elif (OSEE_TC_CORE6_251_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 251)
#else
#error Invalid value for OSEE_TC_CORE6_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 251)
OSEE_DUMMY_ISR(_core6_, 251)
#endif /* OSEE_TC_CORE6_251_ISR_CAT */
#if (defined(OSEE_TC_CORE6_252_ISR_CAT))
#if (OSEE_TC_CORE6_252_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 252)
#elif (OSEE_TC_CORE6_252_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 252)
#else
#error Invalid value for OSEE_TC_CORE6_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 252)
OSEE_DUMMY_ISR(_core6_, 252)
#endif /* OSEE_TC_CORE6_252_ISR_CAT */
#if (defined(OSEE_TC_CORE6_253_ISR_CAT))
#if (OSEE_TC_CORE6_253_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 253)
#elif (OSEE_TC_CORE6_253_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 253)
#else
#error Invalid value for OSEE_TC_CORE6_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 253)
OSEE_DUMMY_ISR(_core6_, 253)
#endif /* OSEE_TC_CORE6_253_ISR_CAT */
#if (defined(OSEE_TC_CORE6_254_ISR_CAT))
#if (OSEE_TC_CORE6_254_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 254)
#elif (OSEE_TC_CORE6_254_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 254)
#else
#error Invalid value for OSEE_TC_CORE6_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 254)
OSEE_DUMMY_ISR(_core6_, 254)
#endif /* OSEE_TC_CORE6_254_ISR_CAT */
#if (defined(OSEE_TC_CORE6_255_ISR_CAT))
#if (OSEE_TC_CORE6_255_ISR_CAT == 2)
OSEE_ISR2_DECLARE(_core6_, 255)
#elif (OSEE_TC_CORE6_255_ISR_CAT == 1)
OSEE_ISR1_DECLARE(_core6_, 255)
#else
#error Invalid value for OSEE_TC_CORE6_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 255)
OSEE_DUMMY_ISR(_core6_, 255)
#endif /* OSEE_TC_CORE6_255_ISR_CAT */
#endif /* OSEE_TC_CORE6_ISR_MAX_PRIO */

#endif /* __TASKING__ */

#endif /* !OSEE_SINGLECORE */
