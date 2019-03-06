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
 *  \brief  TriCore HAL not inline
 *
 *  \author Errico Guidieri
 *  \date   2018
 */


#include "ee_internal.h"

#if (defined(OSEE_TC_HAS_ISR1_TO_CONF))
#if (defined(OSEE_SINGLECORE))
OSEE_STATIC_INLINE OsEE_isr1_db * OSEE_ALWAYS_INLINE
  osEE_get_isr1_db(CoreIdType core_id)
{
/* Touch unused parameter */
  (void)core_id;
  return &osEE_isr1_db_instance;
}
#else

OSEE_STATIC_INLINE OsEE_isr1_db * OSEE_ALWAYS_INLINE
  osEE_get_isr1_db(CoreIdType core_id)
{
  OsEE_isr1_db * p_tbr;

  switch (core_id) {
    case OS_CORE_ID_0:
      p_tbr = &osEE_isr1_db_instance_core0;
    break;
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
    case OS_CORE_ID_1:
      p_tbr = &osEE_isr1_db_instance_core1;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
    case OS_CORE_ID_2:
      p_tbr = &osEE_isr1_db_instance_core2;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
    case OS_CORE_ID_3:
      p_tbr = &osEE_isr1_db_instance_core3;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
    case OS_CORE_ID_4:
      p_tbr = &osEE_isr1_db_instance_core4;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
    case OS_CORE_ID_6:
      p_tbr = &osEE_isr1_db_instance_core6;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */
    default:
      p_tbr = NULL; /* This should never happens!!! */
    break;
  }

  return p_tbr;
}
#endif /* OSEE_SINGLECORE */
#endif /* OSEE_TC_HAS_ISR1_TO_CONF */

OsEE_bool osEE_cpu_startos(void)
{
  MemSize i;
  MemSize tdb_size;
  OsEE_KDB * const p_kdb = osEE_get_kernel();
  CoreIdType const curr_core_id = osEE_get_curr_core_id();

#if (!defined(OSEE_SINGLECORE))
  if (curr_core_id == OS_CORE_ID_0) {
#endif /* !OSEE_SINGLECORE */
#if (defined(OSEE_HAS_SYSTEM_TIMER))
    osEE_tc_stm_set_clockpersec();
#endif /* OSEE_HAS_SYSTEM_TIMER */
#if (!defined(OSEE_SINGLECORE))
    osEE_tc_setup_inter_irqs();
}
#endif /* !OSEE_SINGLECORE */

  tdb_size = p_kdb->tdb_array_size - 1U;
  for (i = 0U; i < tdb_size; ++i) {
    /* ISR2 initialization */
    OsEE_TDB  * const p_tdb = (*p_kdb->p_tdb_ptr_array)[i];
#if (!defined(OSEE_SINGLECORE))
    if (p_tdb->orig_core_id == curr_core_id) {
#endif /* !OSEE_SINGLECORE */
      if (p_tdb->task_type == OSEE_TASK_TYPE_ISR2) {
#if (defined(OSEE_HAS_SYSTEM_TIMER))
        if (p_tdb->task_func == &osEE_tricore_system_timer_handler) {
          osEE_tc_initialize_system_timer(p_tdb);
        } else
#endif /* OSEE_HAS_SYSTEM_TIMER */
        if (p_tdb->hdb.isr2_src != OSEE_TC_SRC_INVALID) {
          OsEE_prio const srn_priority_tmp =
            (OsEE_prio)OSEE_TC_SRN_PRIORITY(
              OSEE_ISR2_VIRT_TO_HW_PRIO(p_tdb->ready_prio)
            );
          osEE_tc_conf_src(curr_core_id, p_tdb->hdb.isr2_src,
            srn_priority_tmp);
        } else {
          /* nothing to do, entry invalid */
        }
      }
#if (!defined(OSEE_SINGLECORE))
    }
#endif /* !OSEE_SINGLECORE */
  }
#if (defined(OSEE_TC_HAS_ISR1_TO_CONF))
  {
    OsEE_isr1_db * const p_isr1_db = osEE_get_isr1_db(curr_core_id);
    MemSize isr1_max = p_isr1_db->isr1_num;
 
    for (i = 0U; i  < isr1_max; ++i) {
      if ((*p_isr1_db->p_isr1_src_array)[i].isr1_src != OSEE_TC_SRC_INVALID) {
        OsEE_prio const srn_priority_tmp =
          (OsEE_prio)OSEE_TC_SRN_PRIORITY(
            (*p_isr1_db->p_isr1_src_array)[i].isr_prio
          );
        osEE_tc_conf_src(curr_core_id,
          (*p_isr1_db->p_isr1_src_array)[i].isr1_src, srn_priority_tmp);
          
      }
    }
  }
#endif /* OSEE_TC_HAS_ISR1_TO_CONF */
#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
  {
    OsEE_stack * p_stack;
    OsEE_CDB   * const p_cdb = osEE_get_curr_core();

    /* number of stacks excluded the system stack which is the last one */
    MemSize const stack_number = p_cdb->chdb.stack_num - 1U;
    /* Initialize all TASK stacks */
    for (i = 0U; i < stack_number; ++i) {
      MemSize j;
      /* number of words to write with the fillpattern */
      MemSize const stack_words =
        (*p_cdb->chdb.p_sdb_array)[i].stack_size / sizeof(OsEE_stack);

      p_stack = (OsEE_stack *)(*p_cdb->chdb.p_sdb_array)[i].p_bos;
      for (j = 0U; j <= stack_words; ++j)
      {
        (*p_stack) = OSEE_FILL_PATTERN;
        ++p_stack;
      }
    }
    /* Initialize System Stack */
    {
      OsEE_stack const * const p_curr_sp = osEE_get_SP();
      p_stack = (OsEE_stack *)
        (*p_cdb->chdb.p_sdb_array)[(p_cdb->chdb.stack_num - 1U)].p_bos;

      while (p_stack < p_curr_sp) {
        (*p_stack) = OSEE_FILL_PATTERN;
        ++p_stack;
      }
    }
  }
#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */

  return osEE_std_cpu_startos();
}

#if (defined(OSEE_HAS_STACK_MONITORING))

#if (!defined(OSEE_STACK_WORDS_CHECK))
#define OSEE_STACK_WORDS_CHECK (4U)
#endif /* !OSEE_STACK_WORDS_CHECK */

FUNC(OsEE_bool, OS_CODE) osEE_hal_check_stack_overflow
(
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA) p_cdb
)
{
  OsEE_reg     i;
  OsEE_bool    is_overflow        = OSEE_FALSE;
  OsEE_CCB   * const p_ccb        = p_cdb->p_ccb;
  OsEE_SDB   * const p_sdb        = p_ccb->p_curr->hdb.p_sdb;
  OsEE_stack * const p_end_stack  = (OsEE_stack *)p_sdb->p_bos;
  OsEE_stack * const sp           = osEE_get_SP();

  is_overflow = (sp < p_end_stack) || (sp > (OsEE_stack *)p_sdb->p_sos);

  for (i = 0U; (!is_overflow) && (i < OSEE_STACK_WORDS_CHECK); ++i) {
    is_overflow = (p_end_stack[i] != OSEE_FILL_PATTERN);
  }

  return is_overflow;
}
#endif /* OSEE_HAS_STACK_MONITORING */

#if (defined(__TASKING__))
#if (defined(OSEE_SINGLECORE))
/* Force to include the TRAP handlers symbols in elf file from an
   archive */
#pragma extern osEE_tc_trap_mmu
#pragma extern osEE_tc_trap_protection
#pragma extern osEE_tc_trap_instruction
#pragma extern osEE_tc_trap_context
#pragma extern osEE_tc_trap_bus
#pragma extern osEE_tc_trap_assertion
#pragma extern osEE_tc_trap_system
#pragma extern osEE_tc_trap_nmi

#define OSEE_CORE0_S _
#else
#define OSEE_CORE0_S _core0_
#endif /* OSEE_SINGLECORE */

/* Force to include the INTERRUPT handlers symbols in elf file from an
   archive */
#if (defined(OSEE_TC_CORE0_ISR_MAX_PRIO))
#if (defined(OSEE_TC_CORE0_1_ISR_CAT))
#if (OSEE_TC_CORE0_1_ISR_CAT == 2) || (!defined(OSEE_SINGLECORE))
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 1)
#elif (OSEE_TC_CORE0_1_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 1)
#else
#error Invalid value for OSEE_TC_CORE0_1_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 1)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 1)
#endif /* OSEE_TC_CORE0_1_ISR_CAT */
#if (defined(OSEE_TC_CORE0_2_ISR_CAT))
#if (OSEE_TC_CORE0_2_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 2)
#elif (OSEE_TC_CORE0_2_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 2)
#else
#error Invalid value for OSEE_TC_CORE0_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 2)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 2)
#endif /* OSEE_TC_CORE0_2_ISR_CAT */
#if (defined(OSEE_TC_CORE0_3_ISR_CAT))
#if (OSEE_TC_CORE0_3_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 3)
#elif (OSEE_TC_CORE0_3_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 3)
#else
#error Invalid value for OSEE_TC_CORE0_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 3)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 3)
#endif /* OSEE_TC_CORE0_3_ISR_CAT */
#if (defined(OSEE_TC_CORE0_4_ISR_CAT))
#if (OSEE_TC_CORE0_4_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 4)
#elif (OSEE_TC_CORE0_4_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 4)
#else
#error Invalid value for OSEE_TC_CORE0_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 4)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 4)
#endif /* OSEE_TC_CORE0_4_ISR_CAT */
#if (defined(OSEE_TC_CORE0_5_ISR_CAT))
#if (OSEE_TC_CORE0_5_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 5)
#elif (OSEE_TC_CORE0_5_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 5)
#else
#error Invalid value for OSEE_TC_CORE0_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 5)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 5)
#endif /* OSEE_TC_CORE0_5_ISR_CAT */
#if (defined(OSEE_TC_CORE0_6_ISR_CAT))
#if (OSEE_TC_CORE0_6_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 6)
#elif (OSEE_TC_CORE0_6_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 6)
#else
#error Invalid value for OSEE_TC_CORE0_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 6)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 6)
#endif /* OSEE_TC_CORE0_6_ISR_CAT */
#if (defined(OSEE_TC_CORE0_7_ISR_CAT))
#if (OSEE_TC_CORE0_7_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 7)
#elif (OSEE_TC_CORE0_7_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 7)
#else
#error Invalid value for OSEE_TC_CORE0_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 7)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 7)
#endif /* OSEE_TC_CORE0_7_ISR_CAT */
#if (defined(OSEE_TC_CORE0_8_ISR_CAT))
#if (OSEE_TC_CORE0_8_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 8)
#elif (OSEE_TC_CORE0_8_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 8)
#else
#error Invalid value for OSEE_TC_CORE0_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 8)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 8)
#endif /* OSEE_TC_CORE0_8_ISR_CAT */
#if (defined(OSEE_TC_CORE0_9_ISR_CAT))
#if (OSEE_TC_CORE0_9_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 9)
#elif (OSEE_TC_CORE0_9_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 9)
#else
#error Invalid value for OSEE_TC_CORE0_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 9)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 9)
#endif /* OSEE_TC_CORE0_9_ISR_CAT */
#if (defined(OSEE_TC_CORE0_10_ISR_CAT))
#if (OSEE_TC_CORE0_10_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 10)
#elif (OSEE_TC_CORE0_10_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 10)
#else
#error Invalid value for OSEE_TC_CORE0_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 10)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 10)
#endif /* OSEE_TC_CORE0_10_ISR_CAT */
#if (defined(OSEE_TC_CORE0_11_ISR_CAT))
#if (OSEE_TC_CORE0_11_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 11)
#elif (OSEE_TC_CORE0_11_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 11)
#else
#error Invalid value for OSEE_TC_CORE0_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 11)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 11)
#endif /* OSEE_TC_CORE0_11_ISR_CAT */
#if (defined(OSEE_TC_CORE0_12_ISR_CAT))
#if (OSEE_TC_CORE0_12_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 12)
#elif (OSEE_TC_CORE0_12_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 12)
#else
#error Invalid value for OSEE_TC_CORE0_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 12)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 12)
#endif /* OSEE_TC_CORE0_12_ISR_CAT */
#if (defined(OSEE_TC_CORE0_13_ISR_CAT))
#if (OSEE_TC_CORE0_13_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 13)
#elif (OSEE_TC_CORE0_13_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 13)
#else
#error Invalid value for OSEE_TC_CORE0_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 13)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 13)
#endif /* OSEE_TC_CORE0_13_ISR_CAT */
#if (defined(OSEE_TC_CORE0_14_ISR_CAT))
#if (OSEE_TC_CORE0_14_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 14)
#elif (OSEE_TC_CORE0_14_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 14)
#else
#error Invalid value for OSEE_TC_CORE0_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 14)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 14)
#endif /* OSEE_TC_CORE0_14_ISR_CAT */
#if (defined(OSEE_TC_CORE0_15_ISR_CAT))
#if (OSEE_TC_CORE0_15_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 15)
#elif (OSEE_TC_CORE0_15_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 15)
#else
#error Invalid value for OSEE_TC_CORE0_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 15)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 15)
#endif /* OSEE_TC_CORE0_15_ISR_CAT */
#if (defined(OSEE_TC_CORE0_16_ISR_CAT))
#if (OSEE_TC_CORE0_16_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 16)
#elif (OSEE_TC_CORE0_16_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 16)
#else
#error Invalid value for OSEE_TC_CORE0_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 16)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 16)
#endif /* OSEE_TC_CORE0_16_ISR_CAT */
#if (defined(OSEE_TC_CORE0_17_ISR_CAT))
#if (OSEE_TC_CORE0_17_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 17)
#elif (OSEE_TC_CORE0_17_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 17)
#else
#error Invalid value for OSEE_TC_CORE0_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 17)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 17)
#endif /* OSEE_TC_CORE0_17_ISR_CAT */
#if (defined(OSEE_TC_CORE0_18_ISR_CAT))
#if (OSEE_TC_CORE0_18_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 18)
#elif (OSEE_TC_CORE0_18_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 18)
#else
#error Invalid value for OSEE_TC_CORE0_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 18)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 18)
#endif /* OSEE_TC_CORE0_18_ISR_CAT */
#if (defined(OSEE_TC_CORE0_19_ISR_CAT))
#if (OSEE_TC_CORE0_19_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 19)
#elif (OSEE_TC_CORE0_19_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 19)
#else
#error Invalid value for OSEE_TC_CORE0_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 19)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 19)
#endif /* OSEE_TC_CORE0_19_ISR_CAT */
#if (defined(OSEE_TC_CORE0_20_ISR_CAT))
#if (OSEE_TC_CORE0_20_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 20)
#elif (OSEE_TC_CORE0_20_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 20)
#else
#error Invalid value for OSEE_TC_CORE0_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 20)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 20)
#endif /* OSEE_TC_CORE0_20_ISR_CAT */
#if (defined(OSEE_TC_CORE0_21_ISR_CAT))
#if (OSEE_TC_CORE0_21_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 21)
#elif (OSEE_TC_CORE0_21_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 21)
#else
#error Invalid value for OSEE_TC_CORE0_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 21)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 21)
#endif /* OSEE_TC_CORE0_21_ISR_CAT */
#if (defined(OSEE_TC_CORE0_22_ISR_CAT))
#if (OSEE_TC_CORE0_22_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 22)
#elif (OSEE_TC_CORE0_22_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 22)
#else
#error Invalid value for OSEE_TC_CORE0_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 22)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 22)
#endif /* OSEE_TC_CORE0_22_ISR_CAT */
#if (defined(OSEE_TC_CORE0_23_ISR_CAT))
#if (OSEE_TC_CORE0_23_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 23)
#elif (OSEE_TC_CORE0_23_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 23)
#else
#error Invalid value for OSEE_TC_CORE0_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 23)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 23)
#endif /* OSEE_TC_CORE0_23_ISR_CAT */
#if (defined(OSEE_TC_CORE0_24_ISR_CAT))
#if (OSEE_TC_CORE0_24_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 24)
#elif (OSEE_TC_CORE0_24_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 24)
#else
#error Invalid value for OSEE_TC_CORE0_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 24)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 24)
#endif /* OSEE_TC_CORE0_24_ISR_CAT */
#if (defined(OSEE_TC_CORE0_25_ISR_CAT))
#if (OSEE_TC_CORE0_25_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 25)
#elif (OSEE_TC_CORE0_25_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 25)
#else
#error Invalid value for OSEE_TC_CORE0_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 25)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 25)
#endif /* OSEE_TC_CORE0_25_ISR_CAT */
#if (defined(OSEE_TC_CORE0_26_ISR_CAT))
#if (OSEE_TC_CORE0_26_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 26)
#elif (OSEE_TC_CORE0_26_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 26)
#else
#error Invalid value for OSEE_TC_CORE0_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 26)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 26)
#endif /* OSEE_TC_CORE0_26_ISR_CAT */
#if (defined(OSEE_TC_CORE0_27_ISR_CAT))
#if (OSEE_TC_CORE0_27_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 27)
#elif (OSEE_TC_CORE0_27_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 27)
#else
#error Invalid value for OSEE_TC_CORE0_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 27)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 27)
#endif /* OSEE_TC_CORE0_27_ISR_CAT */
#if (defined(OSEE_TC_CORE0_28_ISR_CAT))
#if (OSEE_TC_CORE0_28_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 28)
#elif (OSEE_TC_CORE0_28_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 28)
#else
#error Invalid value for OSEE_TC_CORE0_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 28)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 28)
#endif /* OSEE_TC_CORE0_28_ISR_CAT */
#if (defined(OSEE_TC_CORE0_29_ISR_CAT))
#if (OSEE_TC_CORE0_29_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 29)
#elif (OSEE_TC_CORE0_29_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 29)
#else
#error Invalid value for OSEE_TC_CORE0_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 29)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 29)
#endif /* OSEE_TC_CORE0_29_ISR_CAT */
#if (defined(OSEE_TC_CORE0_30_ISR_CAT))
#if (OSEE_TC_CORE0_30_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 30)
#elif (OSEE_TC_CORE0_30_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 30)
#else
#error Invalid value for OSEE_TC_CORE0_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 30)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 30)
#endif /* OSEE_TC_CORE0_30_ISR_CAT */
#if (defined(OSEE_TC_CORE0_31_ISR_CAT))
#if (OSEE_TC_CORE0_31_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 31)
#elif (OSEE_TC_CORE0_31_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 31)
#else
#error Invalid value for OSEE_TC_CORE0_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 31)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 31)
#endif /* OSEE_TC_CORE0_31_ISR_CAT */
#if (defined(OSEE_TC_CORE0_32_ISR_CAT))
#if (OSEE_TC_CORE0_32_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 32)
#elif (OSEE_TC_CORE0_32_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 32)
#else
#error Invalid value for OSEE_TC_CORE0_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 32)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 32)
#endif /* OSEE_TC_CORE0_32_ISR_CAT */
#if (defined(OSEE_TC_CORE0_33_ISR_CAT))
#if (OSEE_TC_CORE0_33_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 33)
#elif (OSEE_TC_CORE0_33_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 33)
#else
#error Invalid value for OSEE_TC_CORE0_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 33)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 33)
#endif /* OSEE_TC_CORE0_33_ISR_CAT */
#if (defined(OSEE_TC_CORE0_34_ISR_CAT))
#if (OSEE_TC_CORE0_34_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 34)
#elif (OSEE_TC_CORE0_34_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 34)
#else
#error Invalid value for OSEE_TC_CORE0_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 34)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 34)
#endif /* OSEE_TC_CORE0_34_ISR_CAT */
#if (defined(OSEE_TC_CORE0_35_ISR_CAT))
#if (OSEE_TC_CORE0_35_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 35)
#elif (OSEE_TC_CORE0_35_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 35)
#else
#error Invalid value for OSEE_TC_CORE0_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 35)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 35)
#endif /* OSEE_TC_CORE0_35_ISR_CAT */
#if (defined(OSEE_TC_CORE0_36_ISR_CAT))
#if (OSEE_TC_CORE0_36_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 36)
#elif (OSEE_TC_CORE0_36_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 36)
#else
#error Invalid value for OSEE_TC_CORE0_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 36)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 36)
#endif /* OSEE_TC_CORE0_36_ISR_CAT */
#if (defined(OSEE_TC_CORE0_37_ISR_CAT))
#if (OSEE_TC_CORE0_37_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 37)
#elif (OSEE_TC_CORE0_37_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 37)
#else
#error Invalid value for OSEE_TC_CORE0_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 37)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 37)
#endif /* OSEE_TC_CORE0_37_ISR_CAT */
#if (defined(OSEE_TC_CORE0_38_ISR_CAT))
#if (OSEE_TC_CORE0_38_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 38)
#elif (OSEE_TC_CORE0_38_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 38)
#else
#error Invalid value for OSEE_TC_CORE0_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 38)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 38)
#endif /* OSEE_TC_CORE0_38_ISR_CAT */
#if (defined(OSEE_TC_CORE0_39_ISR_CAT))
#if (OSEE_TC_CORE0_39_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 39)
#elif (OSEE_TC_CORE0_39_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 39)
#else
#error Invalid value for OSEE_TC_CORE0_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 39)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 39)
#endif /* OSEE_TC_CORE0_39_ISR_CAT */
#if (defined(OSEE_TC_CORE0_40_ISR_CAT))
#if (OSEE_TC_CORE0_40_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 40)
#elif (OSEE_TC_CORE0_40_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 40)
#else
#error Invalid value for OSEE_TC_CORE0_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 40)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 40)
#endif /* OSEE_TC_CORE0_40_ISR_CAT */
#if (defined(OSEE_TC_CORE0_41_ISR_CAT))
#if (OSEE_TC_CORE0_41_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 41)
#elif (OSEE_TC_CORE0_41_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 41)
#else
#error Invalid value for OSEE_TC_CORE0_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 41)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 41)
#endif /* OSEE_TC_CORE0_41_ISR_CAT */
#if (defined(OSEE_TC_CORE0_42_ISR_CAT))
#if (OSEE_TC_CORE0_42_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 42)
#elif (OSEE_TC_CORE0_42_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 42)
#else
#error Invalid value for OSEE_TC_CORE0_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 42)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 42)
#endif /* OSEE_TC_CORE0_42_ISR_CAT */
#if (defined(OSEE_TC_CORE0_43_ISR_CAT))
#if (OSEE_TC_CORE0_43_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 43)
#elif (OSEE_TC_CORE0_43_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 43)
#else
#error Invalid value for OSEE_TC_CORE0_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 43)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 43)
#endif /* OSEE_TC_CORE0_43_ISR_CAT */
#if (defined(OSEE_TC_CORE0_44_ISR_CAT))
#if (OSEE_TC_CORE0_44_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 44)
#elif (OSEE_TC_CORE0_44_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 44)
#else
#error Invalid value for OSEE_TC_CORE0_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 44)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 44)
#endif /* OSEE_TC_CORE0_44_ISR_CAT */
#if (defined(OSEE_TC_CORE0_45_ISR_CAT))
#if (OSEE_TC_CORE0_45_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 45)
#elif (OSEE_TC_CORE0_45_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 45)
#else
#error Invalid value for OSEE_TC_CORE0_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 45)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 45)
#endif /* OSEE_TC_CORE0_45_ISR_CAT */
#if (defined(OSEE_TC_CORE0_46_ISR_CAT))
#if (OSEE_TC_CORE0_46_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 46)
#elif (OSEE_TC_CORE0_46_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 46)
#else
#error Invalid value for OSEE_TC_CORE0_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 46)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 46)
#endif /* OSEE_TC_CORE0_46_ISR_CAT */
#if (defined(OSEE_TC_CORE0_47_ISR_CAT))
#if (OSEE_TC_CORE0_47_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 47)
#elif (OSEE_TC_CORE0_47_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 47)
#else
#error Invalid value for OSEE_TC_CORE0_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 47)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 47)
#endif /* OSEE_TC_CORE0_47_ISR_CAT */
#if (defined(OSEE_TC_CORE0_48_ISR_CAT))
#if (OSEE_TC_CORE0_48_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 48)
#elif (OSEE_TC_CORE0_48_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 48)
#else
#error Invalid value for OSEE_TC_CORE0_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 48)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 48)
#endif /* OSEE_TC_CORE0_48_ISR_CAT */
#if (defined(OSEE_TC_CORE0_49_ISR_CAT))
#if (OSEE_TC_CORE0_49_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 49)
#elif (OSEE_TC_CORE0_49_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 49)
#else
#error Invalid value for OSEE_TC_CORE0_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 49)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 49)
#endif /* OSEE_TC_CORE0_49_ISR_CAT */
#if (defined(OSEE_TC_CORE0_50_ISR_CAT))
#if (OSEE_TC_CORE0_50_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 50)
#elif (OSEE_TC_CORE0_50_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 50)
#else
#error Invalid value for OSEE_TC_CORE0_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 50)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 50)
#endif /* OSEE_TC_CORE0_50_ISR_CAT */
#if (defined(OSEE_TC_CORE0_51_ISR_CAT))
#if (OSEE_TC_CORE0_51_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 51)
#elif (OSEE_TC_CORE0_51_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 51)
#else
#error Invalid value for OSEE_TC_CORE0_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 51)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 51)
#endif /* OSEE_TC_CORE0_51_ISR_CAT */
#if (defined(OSEE_TC_CORE0_52_ISR_CAT))
#if (OSEE_TC_CORE0_52_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 52)
#elif (OSEE_TC_CORE0_52_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 52)
#else
#error Invalid value for OSEE_TC_CORE0_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 52)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 52)
#endif /* OSEE_TC_CORE0_52_ISR_CAT */
#if (defined(OSEE_TC_CORE0_53_ISR_CAT))
#if (OSEE_TC_CORE0_53_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 53)
#elif (OSEE_TC_CORE0_53_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 53)
#else
#error Invalid value for OSEE_TC_CORE0_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 53)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 53)
#endif /* OSEE_TC_CORE0_53_ISR_CAT */
#if (defined(OSEE_TC_CORE0_54_ISR_CAT))
#if (OSEE_TC_CORE0_54_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 54)
#elif (OSEE_TC_CORE0_54_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 54)
#else
#error Invalid value for OSEE_TC_CORE0_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 54)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 54)
#endif /* OSEE_TC_CORE0_54_ISR_CAT */
#if (defined(OSEE_TC_CORE0_55_ISR_CAT))
#if (OSEE_TC_CORE0_55_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 55)
#elif (OSEE_TC_CORE0_55_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 55)
#else
#error Invalid value for OSEE_TC_CORE0_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 55)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 55)
#endif /* OSEE_TC_CORE0_55_ISR_CAT */
#if (defined(OSEE_TC_CORE0_56_ISR_CAT))
#if (OSEE_TC_CORE0_56_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 56)
#elif (OSEE_TC_CORE0_56_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 56)
#else
#error Invalid value for OSEE_TC_CORE0_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 56)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 56)
#endif /* OSEE_TC_CORE0_56_ISR_CAT */
#if (defined(OSEE_TC_CORE0_57_ISR_CAT))
#if (OSEE_TC_CORE0_57_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 57)
#elif (OSEE_TC_CORE0_57_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 57)
#else
#error Invalid value for OSEE_TC_CORE0_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 57)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 57)
#endif /* OSEE_TC_CORE0_57_ISR_CAT */
#if (defined(OSEE_TC_CORE0_58_ISR_CAT))
#if (OSEE_TC_CORE0_58_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 58)
#elif (OSEE_TC_CORE0_58_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 58)
#else
#error Invalid value for OSEE_TC_CORE0_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 58)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 58)
#endif /* OSEE_TC_CORE0_58_ISR_CAT */
#if (defined(OSEE_TC_CORE0_59_ISR_CAT))
#if (OSEE_TC_CORE0_59_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 59)
#elif (OSEE_TC_CORE0_59_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 59)
#else
#error Invalid value for OSEE_TC_CORE0_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 59)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 59)
#endif /* OSEE_TC_CORE0_59_ISR_CAT */
#if (defined(OSEE_TC_CORE0_60_ISR_CAT))
#if (OSEE_TC_CORE0_60_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 60)
#elif (OSEE_TC_CORE0_60_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 60)
#else
#error Invalid value for OSEE_TC_CORE0_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 60)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 60)
#endif /* OSEE_TC_CORE0_60_ISR_CAT */
#if (defined(OSEE_TC_CORE0_61_ISR_CAT))
#if (OSEE_TC_CORE0_61_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 61)
#elif (OSEE_TC_CORE0_61_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 61)
#else
#error Invalid value for OSEE_TC_CORE0_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 61)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 61)
#endif /* OSEE_TC_CORE0_61_ISR_CAT */
#if (defined(OSEE_TC_CORE0_62_ISR_CAT))
#if (OSEE_TC_CORE0_62_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 62)
#elif (OSEE_TC_CORE0_62_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 62)
#else
#error Invalid value for OSEE_TC_CORE0_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 62)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 62)
#endif /* OSEE_TC_CORE0_62_ISR_CAT */
#if (defined(OSEE_TC_CORE0_63_ISR_CAT))
#if (OSEE_TC_CORE0_63_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 63)
#elif (OSEE_TC_CORE0_63_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 63)
#else
#error Invalid value for OSEE_TC_CORE0_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 63)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 63)
#endif /* OSEE_TC_CORE0_63_ISR_CAT */
#if (defined(OSEE_TC_CORE0_64_ISR_CAT))
#if (OSEE_TC_CORE0_64_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 64)
#elif (OSEE_TC_CORE0_64_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 64)
#else
#error Invalid value for OSEE_TC_CORE0_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 64)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 64)
#endif /* OSEE_TC_CORE0_64_ISR_CAT */
#if (defined(OSEE_TC_CORE0_65_ISR_CAT))
#if (OSEE_TC_CORE0_65_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 65)
#elif (OSEE_TC_CORE0_65_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 65)
#else
#error Invalid value for OSEE_TC_CORE0_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 65)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 65)
#endif /* OSEE_TC_CORE0_65_ISR_CAT */
#if (defined(OSEE_TC_CORE0_66_ISR_CAT))
#if (OSEE_TC_CORE0_66_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 66)
#elif (OSEE_TC_CORE0_66_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 66)
#else
#error Invalid value for OSEE_TC_CORE0_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 66)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 66)
#endif /* OSEE_TC_CORE0_66_ISR_CAT */
#if (defined(OSEE_TC_CORE0_67_ISR_CAT))
#if (OSEE_TC_CORE0_67_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 67)
#elif (OSEE_TC_CORE0_67_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 67)
#else
#error Invalid value for OSEE_TC_CORE0_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 67)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 67)
#endif /* OSEE_TC_CORE0_67_ISR_CAT */
#if (defined(OSEE_TC_CORE0_68_ISR_CAT))
#if (OSEE_TC_CORE0_68_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 68)
#elif (OSEE_TC_CORE0_68_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 68)
#else
#error Invalid value for OSEE_TC_CORE0_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 68)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 68)
#endif /* OSEE_TC_CORE0_68_ISR_CAT */
#if (defined(OSEE_TC_CORE0_69_ISR_CAT))
#if (OSEE_TC_CORE0_69_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 69)
#elif (OSEE_TC_CORE0_69_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 69)
#else
#error Invalid value for OSEE_TC_CORE0_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 69)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 69)
#endif /* OSEE_TC_CORE0_69_ISR_CAT */
#if (defined(OSEE_TC_CORE0_70_ISR_CAT))
#if (OSEE_TC_CORE0_70_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 70)
#elif (OSEE_TC_CORE0_70_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 70)
#else
#error Invalid value for OSEE_TC_CORE0_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 70)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 70)
#endif /* OSEE_TC_CORE0_70_ISR_CAT */
#if (defined(OSEE_TC_CORE0_71_ISR_CAT))
#if (OSEE_TC_CORE0_71_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 71)
#elif (OSEE_TC_CORE0_71_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 71)
#else
#error Invalid value for OSEE_TC_CORE0_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 71)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 71)
#endif /* OSEE_TC_CORE0_71_ISR_CAT */
#if (defined(OSEE_TC_CORE0_72_ISR_CAT))
#if (OSEE_TC_CORE0_72_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 72)
#elif (OSEE_TC_CORE0_72_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 72)
#else
#error Invalid value for OSEE_TC_CORE0_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 72)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 72)
#endif /* OSEE_TC_CORE0_72_ISR_CAT */
#if (defined(OSEE_TC_CORE0_73_ISR_CAT))
#if (OSEE_TC_CORE0_73_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 73)
#elif (OSEE_TC_CORE0_73_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 73)
#else
#error Invalid value for OSEE_TC_CORE0_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 73)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 73)
#endif /* OSEE_TC_CORE0_73_ISR_CAT */
#if (defined(OSEE_TC_CORE0_74_ISR_CAT))
#if (OSEE_TC_CORE0_74_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 74)
#elif (OSEE_TC_CORE0_74_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 74)
#else
#error Invalid value for OSEE_TC_CORE0_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 74)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 74)
#endif /* OSEE_TC_CORE0_74_ISR_CAT */
#if (defined(OSEE_TC_CORE0_75_ISR_CAT))
#if (OSEE_TC_CORE0_75_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 75)
#elif (OSEE_TC_CORE0_75_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 75)
#else
#error Invalid value for OSEE_TC_CORE0_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 75)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 75)
#endif /* OSEE_TC_CORE0_75_ISR_CAT */
#if (defined(OSEE_TC_CORE0_76_ISR_CAT))
#if (OSEE_TC_CORE0_76_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 76)
#elif (OSEE_TC_CORE0_76_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 76)
#else
#error Invalid value for OSEE_TC_CORE0_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 76)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 76)
#endif /* OSEE_TC_CORE0_76_ISR_CAT */
#if (defined(OSEE_TC_CORE0_77_ISR_CAT))
#if (OSEE_TC_CORE0_77_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 77)
#elif (OSEE_TC_CORE0_77_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 77)
#else
#error Invalid value for OSEE_TC_CORE0_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 77)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 77)
#endif /* OSEE_TC_CORE0_77_ISR_CAT */
#if (defined(OSEE_TC_CORE0_78_ISR_CAT))
#if (OSEE_TC_CORE0_78_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 78)
#elif (OSEE_TC_CORE0_78_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 78)
#else
#error Invalid value for OSEE_TC_CORE0_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 78)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 78)
#endif /* OSEE_TC_CORE0_78_ISR_CAT */
#if (defined(OSEE_TC_CORE0_79_ISR_CAT))
#if (OSEE_TC_CORE0_79_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 79)
#elif (OSEE_TC_CORE0_79_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 79)
#else
#error Invalid value for OSEE_TC_CORE0_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 79)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 79)
#endif /* OSEE_TC_CORE0_79_ISR_CAT */
#if (defined(OSEE_TC_CORE0_80_ISR_CAT))
#if (OSEE_TC_CORE0_80_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 80)
#elif (OSEE_TC_CORE0_80_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 80)
#else
#error Invalid value for OSEE_TC_CORE0_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 80)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 80)
#endif /* OSEE_TC_CORE0_80_ISR_CAT */
#if (defined(OSEE_TC_CORE0_81_ISR_CAT))
#if (OSEE_TC_CORE0_81_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 81)
#elif (OSEE_TC_CORE0_81_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 81)
#else
#error Invalid value for OSEE_TC_CORE0_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 81)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 81)
#endif /* OSEE_TC_CORE0_81_ISR_CAT */
#if (defined(OSEE_TC_CORE0_82_ISR_CAT))
#if (OSEE_TC_CORE0_82_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 82)
#elif (OSEE_TC_CORE0_82_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 82)
#else
#error Invalid value for OSEE_TC_CORE0_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 82)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 82)
#endif /* OSEE_TC_CORE0_82_ISR_CAT */
#if (defined(OSEE_TC_CORE0_83_ISR_CAT))
#if (OSEE_TC_CORE0_83_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 83)
#elif (OSEE_TC_CORE0_83_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 83)
#else
#error Invalid value for OSEE_TC_CORE0_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 83)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 83)
#endif /* OSEE_TC_CORE0_83_ISR_CAT */
#if (defined(OSEE_TC_CORE0_84_ISR_CAT))
#if (OSEE_TC_CORE0_84_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 84)
#elif (OSEE_TC_CORE0_84_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 84)
#else
#error Invalid value for OSEE_TC_CORE0_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 84)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 84)
#endif /* OSEE_TC_CORE0_84_ISR_CAT */
#if (defined(OSEE_TC_CORE0_85_ISR_CAT))
#if (OSEE_TC_CORE0_85_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 85)
#elif (OSEE_TC_CORE0_85_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 85)
#else
#error Invalid value for OSEE_TC_CORE0_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 85)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 85)
#endif /* OSEE_TC_CORE0_85_ISR_CAT */
#if (defined(OSEE_TC_CORE0_86_ISR_CAT))
#if (OSEE_TC_CORE0_86_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 86)
#elif (OSEE_TC_CORE0_86_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 86)
#else
#error Invalid value for OSEE_TC_CORE0_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 86)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 86)
#endif /* OSEE_TC_CORE0_86_ISR_CAT */
#if (defined(OSEE_TC_CORE0_87_ISR_CAT))
#if (OSEE_TC_CORE0_87_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 87)
#elif (OSEE_TC_CORE0_87_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 87)
#else
#error Invalid value for OSEE_TC_CORE0_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 87)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 87)
#endif /* OSEE_TC_CORE0_87_ISR_CAT */
#if (defined(OSEE_TC_CORE0_88_ISR_CAT))
#if (OSEE_TC_CORE0_88_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 88)
#elif (OSEE_TC_CORE0_88_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 88)
#else
#error Invalid value for OSEE_TC_CORE0_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 88)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 88)
#endif /* OSEE_TC_CORE0_88_ISR_CAT */
#if (defined(OSEE_TC_CORE0_89_ISR_CAT))
#if (OSEE_TC_CORE0_89_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 89)
#elif (OSEE_TC_CORE0_89_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 89)
#else
#error Invalid value for OSEE_TC_CORE0_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 89)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 89)
#endif /* OSEE_TC_CORE0_89_ISR_CAT */
#if (defined(OSEE_TC_CORE0_90_ISR_CAT))
#if (OSEE_TC_CORE0_90_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 90)
#elif (OSEE_TC_CORE0_90_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 90)
#else
#error Invalid value for OSEE_TC_CORE0_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 90)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 90)
#endif /* OSEE_TC_CORE0_90_ISR_CAT */
#if (defined(OSEE_TC_CORE0_91_ISR_CAT))
#if (OSEE_TC_CORE0_91_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 91)
#elif (OSEE_TC_CORE0_91_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 91)
#else
#error Invalid value for OSEE_TC_CORE0_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 91)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 91)
#endif /* OSEE_TC_CORE0_91_ISR_CAT */
#if (defined(OSEE_TC_CORE0_92_ISR_CAT))
#if (OSEE_TC_CORE0_92_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 92)
#elif (OSEE_TC_CORE0_92_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 92)
#else
#error Invalid value for OSEE_TC_CORE0_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 92)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 92)
#endif /* OSEE_TC_CORE0_92_ISR_CAT */
#if (defined(OSEE_TC_CORE0_93_ISR_CAT))
#if (OSEE_TC_CORE0_93_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 93)
#elif (OSEE_TC_CORE0_93_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 93)
#else
#error Invalid value for OSEE_TC_CORE0_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 93)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 93)
#endif /* OSEE_TC_CORE0_93_ISR_CAT */
#if (defined(OSEE_TC_CORE0_94_ISR_CAT))
#if (OSEE_TC_CORE0_94_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 94)
#elif (OSEE_TC_CORE0_94_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 94)
#else
#error Invalid value for OSEE_TC_CORE0_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 94)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 94)
#endif /* OSEE_TC_CORE0_94_ISR_CAT */
#if (defined(OSEE_TC_CORE0_95_ISR_CAT))
#if (OSEE_TC_CORE0_95_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 95)
#elif (OSEE_TC_CORE0_95_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 95)
#else
#error Invalid value for OSEE_TC_CORE0_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 95)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 95)
#endif /* OSEE_TC_CORE0_95_ISR_CAT */
#if (defined(OSEE_TC_CORE0_96_ISR_CAT))
#if (OSEE_TC_CORE0_96_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 96)
#elif (OSEE_TC_CORE0_96_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 96)
#else
#error Invalid value for OSEE_TC_CORE0_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 96)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 96)
#endif /* OSEE_TC_CORE0_96_ISR_CAT */
#if (defined(OSEE_TC_CORE0_97_ISR_CAT))
#if (OSEE_TC_CORE0_97_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 97)
#elif (OSEE_TC_CORE0_97_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 97)
#else
#error Invalid value for OSEE_TC_CORE0_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 97)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 97)
#endif /* OSEE_TC_CORE0_97_ISR_CAT */
#if (defined(OSEE_TC_CORE0_98_ISR_CAT))
#if (OSEE_TC_CORE0_98_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 98)
#elif (OSEE_TC_CORE0_98_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 98)
#else
#error Invalid value for OSEE_TC_CORE0_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 98)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 98)
#endif /* OSEE_TC_CORE0_98_ISR_CAT */
#if (defined(OSEE_TC_CORE0_99_ISR_CAT))
#if (OSEE_TC_CORE0_99_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 99)
#elif (OSEE_TC_CORE0_99_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 99)
#else
#error Invalid value for OSEE_TC_CORE0_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 99)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 99)
#endif /* OSEE_TC_CORE0_99_ISR_CAT */
#if (defined(OSEE_TC_CORE0_100_ISR_CAT))
#if (OSEE_TC_CORE0_100_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 100)
#elif (OSEE_TC_CORE0_100_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 100)
#else
#error Invalid value for OSEE_TC_CORE0_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 100)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 100)
#endif /* OSEE_TC_CORE0_100_ISR_CAT */
#if (defined(OSEE_TC_CORE0_101_ISR_CAT))
#if (OSEE_TC_CORE0_101_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 101)
#elif (OSEE_TC_CORE0_101_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 101)
#else
#error Invalid value for OSEE_TC_CORE0_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 101)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 101)
#endif /* OSEE_TC_CORE0_101_ISR_CAT */
#if (defined(OSEE_TC_CORE0_102_ISR_CAT))
#if (OSEE_TC_CORE0_102_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 102)
#elif (OSEE_TC_CORE0_102_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 102)
#else
#error Invalid value for OSEE_TC_CORE0_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 102)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 102)
#endif /* OSEE_TC_CORE0_102_ISR_CAT */
#if (defined(OSEE_TC_CORE0_103_ISR_CAT))
#if (OSEE_TC_CORE0_103_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 103)
#elif (OSEE_TC_CORE0_103_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 103)
#else
#error Invalid value for OSEE_TC_CORE0_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 103)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 103)
#endif /* OSEE_TC_CORE0_103_ISR_CAT */
#if (defined(OSEE_TC_CORE0_104_ISR_CAT))
#if (OSEE_TC_CORE0_104_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 104)
#elif (OSEE_TC_CORE0_104_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 104)
#else
#error Invalid value for OSEE_TC_CORE0_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 104)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 104)
#endif /* OSEE_TC_CORE0_104_ISR_CAT */
#if (defined(OSEE_TC_CORE0_105_ISR_CAT))
#if (OSEE_TC_CORE0_105_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 105)
#elif (OSEE_TC_CORE0_105_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 105)
#else
#error Invalid value for OSEE_TC_CORE0_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 105)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 105)
#endif /* OSEE_TC_CORE0_105_ISR_CAT */
#if (defined(OSEE_TC_CORE0_106_ISR_CAT))
#if (OSEE_TC_CORE0_106_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 106)
#elif (OSEE_TC_CORE0_106_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 106)
#else
#error Invalid value for OSEE_TC_CORE0_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 106)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 106)
#endif /* OSEE_TC_CORE0_106_ISR_CAT */
#if (defined(OSEE_TC_CORE0_107_ISR_CAT))
#if (OSEE_TC_CORE0_107_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 107)
#elif (OSEE_TC_CORE0_107_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 107)
#else
#error Invalid value for OSEE_TC_CORE0_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 107)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 107)
#endif /* OSEE_TC_CORE0_107_ISR_CAT */
#if (defined(OSEE_TC_CORE0_108_ISR_CAT))
#if (OSEE_TC_CORE0_108_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 108)
#elif (OSEE_TC_CORE0_108_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 108)
#else
#error Invalid value for OSEE_TC_CORE0_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 108)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 108)
#endif /* OSEE_TC_CORE0_108_ISR_CAT */
#if (defined(OSEE_TC_CORE0_109_ISR_CAT))
#if (OSEE_TC_CORE0_109_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 109)
#elif (OSEE_TC_CORE0_109_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 109)
#else
#error Invalid value for OSEE_TC_CORE0_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 109)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 109)
#endif /* OSEE_TC_CORE0_109_ISR_CAT */
#if (defined(OSEE_TC_CORE0_110_ISR_CAT))
#if (OSEE_TC_CORE0_110_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 110)
#elif (OSEE_TC_CORE0_110_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 110)
#else
#error Invalid value for OSEE_TC_CORE0_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 110)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 110)
#endif /* OSEE_TC_CORE0_110_ISR_CAT */
#if (defined(OSEE_TC_CORE0_111_ISR_CAT))
#if (OSEE_TC_CORE0_111_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 111)
#elif (OSEE_TC_CORE0_111_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 111)
#else
#error Invalid value for OSEE_TC_CORE0_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 111)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 111)
#endif /* OSEE_TC_CORE0_111_ISR_CAT */
#if (defined(OSEE_TC_CORE0_112_ISR_CAT))
#if (OSEE_TC_CORE0_112_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 112)
#elif (OSEE_TC_CORE0_112_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 112)
#else
#error Invalid value for OSEE_TC_CORE0_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 112)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 112)
#endif /* OSEE_TC_CORE0_112_ISR_CAT */
#if (defined(OSEE_TC_CORE0_113_ISR_CAT))
#if (OSEE_TC_CORE0_113_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 113)
#elif (OSEE_TC_CORE0_113_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 113)
#else
#error Invalid value for OSEE_TC_CORE0_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 113)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 113)
#endif /* OSEE_TC_CORE0_113_ISR_CAT */
#if (defined(OSEE_TC_CORE0_114_ISR_CAT))
#if (OSEE_TC_CORE0_114_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 114)
#elif (OSEE_TC_CORE0_114_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 114)
#else
#error Invalid value for OSEE_TC_CORE0_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 114)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 114)
#endif /* OSEE_TC_CORE0_114_ISR_CAT */
#if (defined(OSEE_TC_CORE0_115_ISR_CAT))
#if (OSEE_TC_CORE0_115_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 115)
#elif (OSEE_TC_CORE0_115_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 115)
#else
#error Invalid value for OSEE_TC_CORE0_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 115)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 115)
#endif /* OSEE_TC_CORE0_115_ISR_CAT */
#if (defined(OSEE_TC_CORE0_116_ISR_CAT))
#if (OSEE_TC_CORE0_116_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 116)
#elif (OSEE_TC_CORE0_116_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 116)
#else
#error Invalid value for OSEE_TC_CORE0_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 116)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 116)
#endif /* OSEE_TC_CORE0_116_ISR_CAT */
#if (defined(OSEE_TC_CORE0_117_ISR_CAT))
#if (OSEE_TC_CORE0_117_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 117)
#elif (OSEE_TC_CORE0_117_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 117)
#else
#error Invalid value for OSEE_TC_CORE0_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 117)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 117)
#endif /* OSEE_TC_CORE0_117_ISR_CAT */
#if (defined(OSEE_TC_CORE0_118_ISR_CAT))
#if (OSEE_TC_CORE0_118_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 118)
#elif (OSEE_TC_CORE0_118_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 118)
#else
#error Invalid value for OSEE_TC_CORE0_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 118)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 118)
#endif /* OSEE_TC_CORE0_118_ISR_CAT */
#if (defined(OSEE_TC_CORE0_119_ISR_CAT))
#if (OSEE_TC_CORE0_119_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 119)
#elif (OSEE_TC_CORE0_119_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 119)
#else
#error Invalid value for OSEE_TC_CORE0_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 119)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 119)
#endif /* OSEE_TC_CORE0_119_ISR_CAT */
#if (defined(OSEE_TC_CORE0_120_ISR_CAT))
#if (OSEE_TC_CORE0_120_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 120)
#elif (OSEE_TC_CORE0_120_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 120)
#else
#error Invalid value for OSEE_TC_CORE0_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 120)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 120)
#endif /* OSEE_TC_CORE0_120_ISR_CAT */
#if (defined(OSEE_TC_CORE0_121_ISR_CAT))
#if (OSEE_TC_CORE0_121_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 121)
#elif (OSEE_TC_CORE0_121_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 121)
#else
#error Invalid value for OSEE_TC_CORE0_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 121)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 121)
#endif /* OSEE_TC_CORE0_121_ISR_CAT */
#if (defined(OSEE_TC_CORE0_122_ISR_CAT))
#if (OSEE_TC_CORE0_122_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 122)
#elif (OSEE_TC_CORE0_122_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 122)
#else
#error Invalid value for OSEE_TC_CORE0_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 122)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 122)
#endif /* OSEE_TC_CORE0_122_ISR_CAT */
#if (defined(OSEE_TC_CORE0_123_ISR_CAT))
#if (OSEE_TC_CORE0_123_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 123)
#elif (OSEE_TC_CORE0_123_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 123)
#else
#error Invalid value for OSEE_TC_CORE0_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 123)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 123)
#endif /* OSEE_TC_CORE0_123_ISR_CAT */
#if (defined(OSEE_TC_CORE0_124_ISR_CAT))
#if (OSEE_TC_CORE0_124_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 124)
#elif (OSEE_TC_CORE0_124_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 124)
#else
#error Invalid value for OSEE_TC_CORE0_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 124)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 124)
#endif /* OSEE_TC_CORE0_124_ISR_CAT */
#if (defined(OSEE_TC_CORE0_125_ISR_CAT))
#if (OSEE_TC_CORE0_125_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 125)
#elif (OSEE_TC_CORE0_125_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 125)
#else
#error Invalid value for OSEE_TC_CORE0_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 125)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 125)
#endif /* OSEE_TC_CORE0_125_ISR_CAT */
#if (defined(OSEE_TC_CORE0_126_ISR_CAT))
#if (OSEE_TC_CORE0_126_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 126)
#elif (OSEE_TC_CORE0_126_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 126)
#else
#error Invalid value for OSEE_TC_CORE0_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 126)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 126)
#endif /* OSEE_TC_CORE0_126_ISR_CAT */
#if (defined(OSEE_TC_CORE0_127_ISR_CAT))
#if (OSEE_TC_CORE0_127_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 127)
#elif (OSEE_TC_CORE0_127_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 127)
#else
#error Invalid value for OSEE_TC_CORE0_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 127)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 127)
#endif /* OSEE_TC_CORE0_127_ISR_CAT */
#if (defined(OSEE_TC_CORE0_128_ISR_CAT))
#if (OSEE_TC_CORE0_128_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 128)
#elif (OSEE_TC_CORE0_128_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 128)
#else
#error Invalid value for OSEE_TC_CORE0_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 128)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 128)
#endif /* OSEE_TC_CORE0_128_ISR_CAT */
#if (defined(OSEE_TC_CORE0_129_ISR_CAT))
#if (OSEE_TC_CORE0_129_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 129)
#elif (OSEE_TC_CORE0_129_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 129)
#else
#error Invalid value for OSEE_TC_CORE0_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 129)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 129)
#endif /* OSEE_TC_CORE0_129_ISR_CAT */
#if (defined(OSEE_TC_CORE0_130_ISR_CAT))
#if (OSEE_TC_CORE0_130_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 130)
#elif (OSEE_TC_CORE0_130_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 130)
#else
#error Invalid value for OSEE_TC_CORE0_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 130)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 130)
#endif /* OSEE_TC_CORE0_130_ISR_CAT */
#if (defined(OSEE_TC_CORE0_131_ISR_CAT))
#if (OSEE_TC_CORE0_131_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 131)
#elif (OSEE_TC_CORE0_131_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 131)
#else
#error Invalid value for OSEE_TC_CORE0_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 131)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 131)
#endif /* OSEE_TC_CORE0_131_ISR_CAT */
#if (defined(OSEE_TC_CORE0_132_ISR_CAT))
#if (OSEE_TC_CORE0_132_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 132)
#elif (OSEE_TC_CORE0_132_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 132)
#else
#error Invalid value for OSEE_TC_CORE0_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 132)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 132)
#endif /* OSEE_TC_CORE0_132_ISR_CAT */
#if (defined(OSEE_TC_CORE0_133_ISR_CAT))
#if (OSEE_TC_CORE0_133_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 133)
#elif (OSEE_TC_CORE0_133_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 133)
#else
#error Invalid value for OSEE_TC_CORE0_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 133)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 133)
#endif /* OSEE_TC_CORE0_133_ISR_CAT */
#if (defined(OSEE_TC_CORE0_134_ISR_CAT))
#if (OSEE_TC_CORE0_134_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 134)
#elif (OSEE_TC_CORE0_134_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 134)
#else
#error Invalid value for OSEE_TC_CORE0_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 134)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 134)
#endif /* OSEE_TC_CORE0_134_ISR_CAT */
#if (defined(OSEE_TC_CORE0_135_ISR_CAT))
#if (OSEE_TC_CORE0_135_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 135)
#elif (OSEE_TC_CORE0_135_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 135)
#else
#error Invalid value for OSEE_TC_CORE0_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 135)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 135)
#endif /* OSEE_TC_CORE0_135_ISR_CAT */
#if (defined(OSEE_TC_CORE0_136_ISR_CAT))
#if (OSEE_TC_CORE0_136_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 136)
#elif (OSEE_TC_CORE0_136_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 136)
#else
#error Invalid value for OSEE_TC_CORE0_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 136)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 136)
#endif /* OSEE_TC_CORE0_136_ISR_CAT */
#if (defined(OSEE_TC_CORE0_137_ISR_CAT))
#if (OSEE_TC_CORE0_137_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 137)
#elif (OSEE_TC_CORE0_137_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 137)
#else
#error Invalid value for OSEE_TC_CORE0_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 137)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 137)
#endif /* OSEE_TC_CORE0_137_ISR_CAT */
#if (defined(OSEE_TC_CORE0_138_ISR_CAT))
#if (OSEE_TC_CORE0_138_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 138)
#elif (OSEE_TC_CORE0_138_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 138)
#else
#error Invalid value for OSEE_TC_CORE0_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 138)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 138)
#endif /* OSEE_TC_CORE0_138_ISR_CAT */
#if (defined(OSEE_TC_CORE0_139_ISR_CAT))
#if (OSEE_TC_CORE0_139_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 139)
#elif (OSEE_TC_CORE0_139_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 139)
#else
#error Invalid value for OSEE_TC_CORE0_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 139)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 139)
#endif /* OSEE_TC_CORE0_139_ISR_CAT */
#if (defined(OSEE_TC_CORE0_140_ISR_CAT))
#if (OSEE_TC_CORE0_140_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 140)
#elif (OSEE_TC_CORE0_140_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 140)
#else
#error Invalid value for OSEE_TC_CORE0_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 140)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 140)
#endif /* OSEE_TC_CORE0_140_ISR_CAT */
#if (defined(OSEE_TC_CORE0_141_ISR_CAT))
#if (OSEE_TC_CORE0_141_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 141)
#elif (OSEE_TC_CORE0_141_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 141)
#else
#error Invalid value for OSEE_TC_CORE0_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 141)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 141)
#endif /* OSEE_TC_CORE0_141_ISR_CAT */
#if (defined(OSEE_TC_CORE0_142_ISR_CAT))
#if (OSEE_TC_CORE0_142_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 142)
#elif (OSEE_TC_CORE0_142_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 142)
#else
#error Invalid value for OSEE_TC_CORE0_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 142)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 142)
#endif /* OSEE_TC_CORE0_142_ISR_CAT */
#if (defined(OSEE_TC_CORE0_143_ISR_CAT))
#if (OSEE_TC_CORE0_143_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 143)
#elif (OSEE_TC_CORE0_143_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 143)
#else
#error Invalid value for OSEE_TC_CORE0_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 143)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 143)
#endif /* OSEE_TC_CORE0_143_ISR_CAT */
#if (defined(OSEE_TC_CORE0_144_ISR_CAT))
#if (OSEE_TC_CORE0_144_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 144)
#elif (OSEE_TC_CORE0_144_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 144)
#else
#error Invalid value for OSEE_TC_CORE0_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 144)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 144)
#endif /* OSEE_TC_CORE0_144_ISR_CAT */
#if (defined(OSEE_TC_CORE0_145_ISR_CAT))
#if (OSEE_TC_CORE0_145_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 145)
#elif (OSEE_TC_CORE0_145_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 145)
#else
#error Invalid value for OSEE_TC_CORE0_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 145)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 145)
#endif /* OSEE_TC_CORE0_145_ISR_CAT */
#if (defined(OSEE_TC_CORE0_146_ISR_CAT))
#if (OSEE_TC_CORE0_146_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 146)
#elif (OSEE_TC_CORE0_146_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 146)
#else
#error Invalid value for OSEE_TC_CORE0_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 146)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 146)
#endif /* OSEE_TC_CORE0_146_ISR_CAT */
#if (defined(OSEE_TC_CORE0_147_ISR_CAT))
#if (OSEE_TC_CORE0_147_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 147)
#elif (OSEE_TC_CORE0_147_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 147)
#else
#error Invalid value for OSEE_TC_CORE0_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 147)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 147)
#endif /* OSEE_TC_CORE0_147_ISR_CAT */
#if (defined(OSEE_TC_CORE0_148_ISR_CAT))
#if (OSEE_TC_CORE0_148_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 148)
#elif (OSEE_TC_CORE0_148_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 148)
#else
#error Invalid value for OSEE_TC_CORE0_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 148)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 148)
#endif /* OSEE_TC_CORE0_148_ISR_CAT */
#if (defined(OSEE_TC_CORE0_149_ISR_CAT))
#if (OSEE_TC_CORE0_149_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 149)
#elif (OSEE_TC_CORE0_149_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 149)
#else
#error Invalid value for OSEE_TC_CORE0_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 149)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 149)
#endif /* OSEE_TC_CORE0_149_ISR_CAT */
#if (defined(OSEE_TC_CORE0_150_ISR_CAT))
#if (OSEE_TC_CORE0_150_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 150)
#elif (OSEE_TC_CORE0_150_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 150)
#else
#error Invalid value for OSEE_TC_CORE0_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 150)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 150)
#endif /* OSEE_TC_CORE0_150_ISR_CAT */
#if (defined(OSEE_TC_CORE0_151_ISR_CAT))
#if (OSEE_TC_CORE0_151_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 151)
#elif (OSEE_TC_CORE0_151_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 151)
#else
#error Invalid value for OSEE_TC_CORE0_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 151)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 151)
#endif /* OSEE_TC_CORE0_151_ISR_CAT */
#if (defined(OSEE_TC_CORE0_152_ISR_CAT))
#if (OSEE_TC_CORE0_152_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 152)
#elif (OSEE_TC_CORE0_152_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 152)
#else
#error Invalid value for OSEE_TC_CORE0_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 152)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 152)
#endif /* OSEE_TC_CORE0_152_ISR_CAT */
#if (defined(OSEE_TC_CORE0_153_ISR_CAT))
#if (OSEE_TC_CORE0_153_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 153)
#elif (OSEE_TC_CORE0_153_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 153)
#else
#error Invalid value for OSEE_TC_CORE0_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 153)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 153)
#endif /* OSEE_TC_CORE0_153_ISR_CAT */
#if (defined(OSEE_TC_CORE0_154_ISR_CAT))
#if (OSEE_TC_CORE0_154_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 154)
#elif (OSEE_TC_CORE0_154_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 154)
#else
#error Invalid value for OSEE_TC_CORE0_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 154)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 154)
#endif /* OSEE_TC_CORE0_154_ISR_CAT */
#if (defined(OSEE_TC_CORE0_155_ISR_CAT))
#if (OSEE_TC_CORE0_155_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 155)
#elif (OSEE_TC_CORE0_155_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 155)
#else
#error Invalid value for OSEE_TC_CORE0_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 155)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 155)
#endif /* OSEE_TC_CORE0_155_ISR_CAT */
#if (defined(OSEE_TC_CORE0_156_ISR_CAT))
#if (OSEE_TC_CORE0_156_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 156)
#elif (OSEE_TC_CORE0_156_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 156)
#else
#error Invalid value for OSEE_TC_CORE0_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 156)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 156)
#endif /* OSEE_TC_CORE0_156_ISR_CAT */
#if (defined(OSEE_TC_CORE0_157_ISR_CAT))
#if (OSEE_TC_CORE0_157_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 157)
#elif (OSEE_TC_CORE0_157_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 157)
#else
#error Invalid value for OSEE_TC_CORE0_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 157)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 157)
#endif /* OSEE_TC_CORE0_157_ISR_CAT */
#if (defined(OSEE_TC_CORE0_158_ISR_CAT))
#if (OSEE_TC_CORE0_158_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 158)
#elif (OSEE_TC_CORE0_158_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 158)
#else
#error Invalid value for OSEE_TC_CORE0_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 158)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 158)
#endif /* OSEE_TC_CORE0_158_ISR_CAT */
#if (defined(OSEE_TC_CORE0_159_ISR_CAT))
#if (OSEE_TC_CORE0_159_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 159)
#elif (OSEE_TC_CORE0_159_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 159)
#else
#error Invalid value for OSEE_TC_CORE0_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 159)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 159)
#endif /* OSEE_TC_CORE0_159_ISR_CAT */
#if (defined(OSEE_TC_CORE0_160_ISR_CAT))
#if (OSEE_TC_CORE0_160_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 160)
#elif (OSEE_TC_CORE0_160_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 160)
#else
#error Invalid value for OSEE_TC_CORE0_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 160)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 160)
#endif /* OSEE_TC_CORE0_160_ISR_CAT */
#if (defined(OSEE_TC_CORE0_161_ISR_CAT))
#if (OSEE_TC_CORE0_161_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 161)
#elif (OSEE_TC_CORE0_161_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 161)
#else
#error Invalid value for OSEE_TC_CORE0_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 161)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 161)
#endif /* OSEE_TC_CORE0_161_ISR_CAT */
#if (defined(OSEE_TC_CORE0_162_ISR_CAT))
#if (OSEE_TC_CORE0_162_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 162)
#elif (OSEE_TC_CORE0_162_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 162)
#else
#error Invalid value for OSEE_TC_CORE0_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 162)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 162)
#endif /* OSEE_TC_CORE0_162_ISR_CAT */
#if (defined(OSEE_TC_CORE0_163_ISR_CAT))
#if (OSEE_TC_CORE0_163_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 163)
#elif (OSEE_TC_CORE0_163_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 163)
#else
#error Invalid value for OSEE_TC_CORE0_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 163)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 163)
#endif /* OSEE_TC_CORE0_163_ISR_CAT */
#if (defined(OSEE_TC_CORE0_164_ISR_CAT))
#if (OSEE_TC_CORE0_164_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 164)
#elif (OSEE_TC_CORE0_164_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 164)
#else
#error Invalid value for OSEE_TC_CORE0_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 164)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 164)
#endif /* OSEE_TC_CORE0_164_ISR_CAT */
#if (defined(OSEE_TC_CORE0_165_ISR_CAT))
#if (OSEE_TC_CORE0_165_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 165)
#elif (OSEE_TC_CORE0_165_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 165)
#else
#error Invalid value for OSEE_TC_CORE0_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 165)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 165)
#endif /* OSEE_TC_CORE0_165_ISR_CAT */
#if (defined(OSEE_TC_CORE0_166_ISR_CAT))
#if (OSEE_TC_CORE0_166_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 166)
#elif (OSEE_TC_CORE0_166_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 166)
#else
#error Invalid value for OSEE_TC_CORE0_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 166)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 166)
#endif /* OSEE_TC_CORE0_166_ISR_CAT */
#if (defined(OSEE_TC_CORE0_167_ISR_CAT))
#if (OSEE_TC_CORE0_167_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 167)
#elif (OSEE_TC_CORE0_167_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 167)
#else
#error Invalid value for OSEE_TC_CORE0_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 167)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 167)
#endif /* OSEE_TC_CORE0_167_ISR_CAT */
#if (defined(OSEE_TC_CORE0_168_ISR_CAT))
#if (OSEE_TC_CORE0_168_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 168)
#elif (OSEE_TC_CORE0_168_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 168)
#else
#error Invalid value for OSEE_TC_CORE0_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 168)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 168)
#endif /* OSEE_TC_CORE0_168_ISR_CAT */
#if (defined(OSEE_TC_CORE0_169_ISR_CAT))
#if (OSEE_TC_CORE0_169_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 169)
#elif (OSEE_TC_CORE0_169_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 169)
#else
#error Invalid value for OSEE_TC_CORE0_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 169)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 169)
#endif /* OSEE_TC_CORE0_169_ISR_CAT */
#if (defined(OSEE_TC_CORE0_170_ISR_CAT))
#if (OSEE_TC_CORE0_170_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 170)
#elif (OSEE_TC_CORE0_170_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 170)
#else
#error Invalid value for OSEE_TC_CORE0_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 170)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 170)
#endif /* OSEE_TC_CORE0_170_ISR_CAT */
#if (defined(OSEE_TC_CORE0_171_ISR_CAT))
#if (OSEE_TC_CORE0_171_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 171)
#elif (OSEE_TC_CORE0_171_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 171)
#else
#error Invalid value for OSEE_TC_CORE0_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 171)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 171)
#endif /* OSEE_TC_CORE0_171_ISR_CAT */
#if (defined(OSEE_TC_CORE0_172_ISR_CAT))
#if (OSEE_TC_CORE0_172_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 172)
#elif (OSEE_TC_CORE0_172_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 172)
#else
#error Invalid value for OSEE_TC_CORE0_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 172)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 172)
#endif /* OSEE_TC_CORE0_172_ISR_CAT */
#if (defined(OSEE_TC_CORE0_173_ISR_CAT))
#if (OSEE_TC_CORE0_173_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 173)
#elif (OSEE_TC_CORE0_173_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 173)
#else
#error Invalid value for OSEE_TC_CORE0_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 173)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 173)
#endif /* OSEE_TC_CORE0_173_ISR_CAT */
#if (defined(OSEE_TC_CORE0_174_ISR_CAT))
#if (OSEE_TC_CORE0_174_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 174)
#elif (OSEE_TC_CORE0_174_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 174)
#else
#error Invalid value for OSEE_TC_CORE0_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 174)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 174)
#endif /* OSEE_TC_CORE0_174_ISR_CAT */
#if (defined(OSEE_TC_CORE0_175_ISR_CAT))
#if (OSEE_TC_CORE0_175_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 175)
#elif (OSEE_TC_CORE0_175_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 175)
#else
#error Invalid value for OSEE_TC_CORE0_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 175)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 175)
#endif /* OSEE_TC_CORE0_175_ISR_CAT */
#if (defined(OSEE_TC_CORE0_176_ISR_CAT))
#if (OSEE_TC_CORE0_176_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 176)
#elif (OSEE_TC_CORE0_176_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 176)
#else
#error Invalid value for OSEE_TC_CORE0_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 176)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 176)
#endif /* OSEE_TC_CORE0_176_ISR_CAT */
#if (defined(OSEE_TC_CORE0_177_ISR_CAT))
#if (OSEE_TC_CORE0_177_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 177)
#elif (OSEE_TC_CORE0_177_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 177)
#else
#error Invalid value for OSEE_TC_CORE0_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 177)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 177)
#endif /* OSEE_TC_CORE0_177_ISR_CAT */
#if (defined(OSEE_TC_CORE0_178_ISR_CAT))
#if (OSEE_TC_CORE0_178_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 178)
#elif (OSEE_TC_CORE0_178_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 178)
#else
#error Invalid value for OSEE_TC_CORE0_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 178)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 178)
#endif /* OSEE_TC_CORE0_178_ISR_CAT */
#if (defined(OSEE_TC_CORE0_179_ISR_CAT))
#if (OSEE_TC_CORE0_179_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 179)
#elif (OSEE_TC_CORE0_179_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 179)
#else
#error Invalid value for OSEE_TC_CORE0_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 179)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 179)
#endif /* OSEE_TC_CORE0_179_ISR_CAT */
#if (defined(OSEE_TC_CORE0_180_ISR_CAT))
#if (OSEE_TC_CORE0_180_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 180)
#elif (OSEE_TC_CORE0_180_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 180)
#else
#error Invalid value for OSEE_TC_CORE0_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 180)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 180)
#endif /* OSEE_TC_CORE0_180_ISR_CAT */
#if (defined(OSEE_TC_CORE0_181_ISR_CAT))
#if (OSEE_TC_CORE0_181_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 181)
#elif (OSEE_TC_CORE0_181_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 181)
#else
#error Invalid value for OSEE_TC_CORE0_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 181)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 181)
#endif /* OSEE_TC_CORE0_181_ISR_CAT */
#if (defined(OSEE_TC_CORE0_182_ISR_CAT))
#if (OSEE_TC_CORE0_182_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 182)
#elif (OSEE_TC_CORE0_182_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 182)
#else
#error Invalid value for OSEE_TC_CORE0_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 182)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 182)
#endif /* OSEE_TC_CORE0_182_ISR_CAT */
#if (defined(OSEE_TC_CORE0_183_ISR_CAT))
#if (OSEE_TC_CORE0_183_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 183)
#elif (OSEE_TC_CORE0_183_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 183)
#else
#error Invalid value for OSEE_TC_CORE0_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 183)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 183)
#endif /* OSEE_TC_CORE0_183_ISR_CAT */
#if (defined(OSEE_TC_CORE0_184_ISR_CAT))
#if (OSEE_TC_CORE0_184_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 184)
#elif (OSEE_TC_CORE0_184_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 184)
#else
#error Invalid value for OSEE_TC_CORE0_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 184)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 184)
#endif /* OSEE_TC_CORE0_184_ISR_CAT */
#if (defined(OSEE_TC_CORE0_185_ISR_CAT))
#if (OSEE_TC_CORE0_185_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 185)
#elif (OSEE_TC_CORE0_185_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 185)
#else
#error Invalid value for OSEE_TC_CORE0_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 185)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 185)
#endif /* OSEE_TC_CORE0_185_ISR_CAT */
#if (defined(OSEE_TC_CORE0_186_ISR_CAT))
#if (OSEE_TC_CORE0_186_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 186)
#elif (OSEE_TC_CORE0_186_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 186)
#else
#error Invalid value for OSEE_TC_CORE0_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 186)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 186)
#endif /* OSEE_TC_CORE0_186_ISR_CAT */
#if (defined(OSEE_TC_CORE0_187_ISR_CAT))
#if (OSEE_TC_CORE0_187_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 187)
#elif (OSEE_TC_CORE0_187_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 187)
#else
#error Invalid value for OSEE_TC_CORE0_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 187)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 187)
#endif /* OSEE_TC_CORE0_187_ISR_CAT */
#if (defined(OSEE_TC_CORE0_188_ISR_CAT))
#if (OSEE_TC_CORE0_188_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 188)
#elif (OSEE_TC_CORE0_188_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 188)
#else
#error Invalid value for OSEE_TC_CORE0_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 188)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 188)
#endif /* OSEE_TC_CORE0_188_ISR_CAT */
#if (defined(OSEE_TC_CORE0_189_ISR_CAT))
#if (OSEE_TC_CORE0_189_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 189)
#elif (OSEE_TC_CORE0_189_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 189)
#else
#error Invalid value for OSEE_TC_CORE0_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 189)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 189)
#endif /* OSEE_TC_CORE0_189_ISR_CAT */
#if (defined(OSEE_TC_CORE0_190_ISR_CAT))
#if (OSEE_TC_CORE0_190_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 190)
#elif (OSEE_TC_CORE0_190_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 190)
#else
#error Invalid value for OSEE_TC_CORE0_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 190)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 190)
#endif /* OSEE_TC_CORE0_190_ISR_CAT */
#if (defined(OSEE_TC_CORE0_191_ISR_CAT))
#if (OSEE_TC_CORE0_191_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 191)
#elif (OSEE_TC_CORE0_191_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 191)
#else
#error Invalid value for OSEE_TC_CORE0_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 191)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 191)
#endif /* OSEE_TC_CORE0_191_ISR_CAT */
#if (defined(OSEE_TC_CORE0_192_ISR_CAT))
#if (OSEE_TC_CORE0_192_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 192)
#elif (OSEE_TC_CORE0_192_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 192)
#else
#error Invalid value for OSEE_TC_CORE0_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 192)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 192)
#endif /* OSEE_TC_CORE0_192_ISR_CAT */
#if (defined(OSEE_TC_CORE0_193_ISR_CAT))
#if (OSEE_TC_CORE0_193_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 193)
#elif (OSEE_TC_CORE0_193_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 193)
#else
#error Invalid value for OSEE_TC_CORE0_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 193)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 193)
#endif /* OSEE_TC_CORE0_193_ISR_CAT */
#if (defined(OSEE_TC_CORE0_194_ISR_CAT))
#if (OSEE_TC_CORE0_194_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 194)
#elif (OSEE_TC_CORE0_194_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 194)
#else
#error Invalid value for OSEE_TC_CORE0_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 194)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 194)
#endif /* OSEE_TC_CORE0_194_ISR_CAT */
#if (defined(OSEE_TC_CORE0_195_ISR_CAT))
#if (OSEE_TC_CORE0_195_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 195)
#elif (OSEE_TC_CORE0_195_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 195)
#else
#error Invalid value for OSEE_TC_CORE0_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 195)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 195)
#endif /* OSEE_TC_CORE0_195_ISR_CAT */
#if (defined(OSEE_TC_CORE0_196_ISR_CAT))
#if (OSEE_TC_CORE0_196_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 196)
#elif (OSEE_TC_CORE0_196_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 196)
#else
#error Invalid value for OSEE_TC_CORE0_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 196)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 196)
#endif /* OSEE_TC_CORE0_196_ISR_CAT */
#if (defined(OSEE_TC_CORE0_197_ISR_CAT))
#if (OSEE_TC_CORE0_197_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 197)
#elif (OSEE_TC_CORE0_197_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 197)
#else
#error Invalid value for OSEE_TC_CORE0_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 197)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 197)
#endif /* OSEE_TC_CORE0_197_ISR_CAT */
#if (defined(OSEE_TC_CORE0_198_ISR_CAT))
#if (OSEE_TC_CORE0_198_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 198)
#elif (OSEE_TC_CORE0_198_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 198)
#else
#error Invalid value for OSEE_TC_CORE0_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 198)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 198)
#endif /* OSEE_TC_CORE0_198_ISR_CAT */
#if (defined(OSEE_TC_CORE0_199_ISR_CAT))
#if (OSEE_TC_CORE0_199_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 199)
#elif (OSEE_TC_CORE0_199_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 199)
#else
#error Invalid value for OSEE_TC_CORE0_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 199)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 199)
#endif /* OSEE_TC_CORE0_199_ISR_CAT */
#if (defined(OSEE_TC_CORE0_200_ISR_CAT))
#if (OSEE_TC_CORE0_200_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 200)
#elif (OSEE_TC_CORE0_200_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 200)
#else
#error Invalid value for OSEE_TC_CORE0_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 200)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 200)
#endif /* OSEE_TC_CORE0_200_ISR_CAT */
#if (defined(OSEE_TC_CORE0_201_ISR_CAT))
#if (OSEE_TC_CORE0_201_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 201)
#elif (OSEE_TC_CORE0_201_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 201)
#else
#error Invalid value for OSEE_TC_CORE0_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 201)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 201)
#endif /* OSEE_TC_CORE0_201_ISR_CAT */
#if (defined(OSEE_TC_CORE0_202_ISR_CAT))
#if (OSEE_TC_CORE0_202_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 202)
#elif (OSEE_TC_CORE0_202_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 202)
#else
#error Invalid value for OSEE_TC_CORE0_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 202)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 202)
#endif /* OSEE_TC_CORE0_202_ISR_CAT */
#if (defined(OSEE_TC_CORE0_203_ISR_CAT))
#if (OSEE_TC_CORE0_203_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 203)
#elif (OSEE_TC_CORE0_203_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 203)
#else
#error Invalid value for OSEE_TC_CORE0_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 203)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 203)
#endif /* OSEE_TC_CORE0_203_ISR_CAT */
#if (defined(OSEE_TC_CORE0_204_ISR_CAT))
#if (OSEE_TC_CORE0_204_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 204)
#elif (OSEE_TC_CORE0_204_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 204)
#else
#error Invalid value for OSEE_TC_CORE0_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 204)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 204)
#endif /* OSEE_TC_CORE0_204_ISR_CAT */
#if (defined(OSEE_TC_CORE0_205_ISR_CAT))
#if (OSEE_TC_CORE0_205_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 205)
#elif (OSEE_TC_CORE0_205_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 205)
#else
#error Invalid value for OSEE_TC_CORE0_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 205)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 205)
#endif /* OSEE_TC_CORE0_205_ISR_CAT */
#if (defined(OSEE_TC_CORE0_206_ISR_CAT))
#if (OSEE_TC_CORE0_206_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 206)
#elif (OSEE_TC_CORE0_206_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 206)
#else
#error Invalid value for OSEE_TC_CORE0_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 206)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 206)
#endif /* OSEE_TC_CORE0_206_ISR_CAT */
#if (defined(OSEE_TC_CORE0_207_ISR_CAT))
#if (OSEE_TC_CORE0_207_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 207)
#elif (OSEE_TC_CORE0_207_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 207)
#else
#error Invalid value for OSEE_TC_CORE0_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 207)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 207)
#endif /* OSEE_TC_CORE0_207_ISR_CAT */
#if (defined(OSEE_TC_CORE0_208_ISR_CAT))
#if (OSEE_TC_CORE0_208_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 208)
#elif (OSEE_TC_CORE0_208_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 208)
#else
#error Invalid value for OSEE_TC_CORE0_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 208)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 208)
#endif /* OSEE_TC_CORE0_208_ISR_CAT */
#if (defined(OSEE_TC_CORE0_209_ISR_CAT))
#if (OSEE_TC_CORE0_209_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 209)
#elif (OSEE_TC_CORE0_209_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 209)
#else
#error Invalid value for OSEE_TC_CORE0_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 209)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 209)
#endif /* OSEE_TC_CORE0_209_ISR_CAT */
#if (defined(OSEE_TC_CORE0_210_ISR_CAT))
#if (OSEE_TC_CORE0_210_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 210)
#elif (OSEE_TC_CORE0_210_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 210)
#else
#error Invalid value for OSEE_TC_CORE0_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 210)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 210)
#endif /* OSEE_TC_CORE0_210_ISR_CAT */
#if (defined(OSEE_TC_CORE0_211_ISR_CAT))
#if (OSEE_TC_CORE0_211_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 211)
#elif (OSEE_TC_CORE0_211_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 211)
#else
#error Invalid value for OSEE_TC_CORE0_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 211)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 211)
#endif /* OSEE_TC_CORE0_211_ISR_CAT */
#if (defined(OSEE_TC_CORE0_212_ISR_CAT))
#if (OSEE_TC_CORE0_212_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 212)
#elif (OSEE_TC_CORE0_212_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 212)
#else
#error Invalid value for OSEE_TC_CORE0_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 212)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 212)
#endif /* OSEE_TC_CORE0_212_ISR_CAT */
#if (defined(OSEE_TC_CORE0_213_ISR_CAT))
#if (OSEE_TC_CORE0_213_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 213)
#elif (OSEE_TC_CORE0_213_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 213)
#else
#error Invalid value for OSEE_TC_CORE0_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 213)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 213)
#endif /* OSEE_TC_CORE0_213_ISR_CAT */
#if (defined(OSEE_TC_CORE0_214_ISR_CAT))
#if (OSEE_TC_CORE0_214_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 214)
#elif (OSEE_TC_CORE0_214_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 214)
#else
#error Invalid value for OSEE_TC_CORE0_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 214)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 214)
#endif /* OSEE_TC_CORE0_214_ISR_CAT */
#if (defined(OSEE_TC_CORE0_215_ISR_CAT))
#if (OSEE_TC_CORE0_215_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 215)
#elif (OSEE_TC_CORE0_215_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 215)
#else
#error Invalid value for OSEE_TC_CORE0_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 215)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 215)
#endif /* OSEE_TC_CORE0_215_ISR_CAT */
#if (defined(OSEE_TC_CORE0_216_ISR_CAT))
#if (OSEE_TC_CORE0_216_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 216)
#elif (OSEE_TC_CORE0_216_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 216)
#else
#error Invalid value for OSEE_TC_CORE0_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 216)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 216)
#endif /* OSEE_TC_CORE0_216_ISR_CAT */
#if (defined(OSEE_TC_CORE0_217_ISR_CAT))
#if (OSEE_TC_CORE0_217_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 217)
#elif (OSEE_TC_CORE0_217_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 217)
#else
#error Invalid value for OSEE_TC_CORE0_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 217)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 217)
#endif /* OSEE_TC_CORE0_217_ISR_CAT */
#if (defined(OSEE_TC_CORE0_218_ISR_CAT))
#if (OSEE_TC_CORE0_218_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 218)
#elif (OSEE_TC_CORE0_218_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 218)
#else
#error Invalid value for OSEE_TC_CORE0_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 218)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 218)
#endif /* OSEE_TC_CORE0_218_ISR_CAT */
#if (defined(OSEE_TC_CORE0_219_ISR_CAT))
#if (OSEE_TC_CORE0_219_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 219)
#elif (OSEE_TC_CORE0_219_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 219)
#else
#error Invalid value for OSEE_TC_CORE0_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 219)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 219)
#endif /* OSEE_TC_CORE0_219_ISR_CAT */
#if (defined(OSEE_TC_CORE0_220_ISR_CAT))
#if (OSEE_TC_CORE0_220_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 220)
#elif (OSEE_TC_CORE0_220_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 220)
#else
#error Invalid value for OSEE_TC_CORE0_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 220)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 220)
#endif /* OSEE_TC_CORE0_220_ISR_CAT */
#if (defined(OSEE_TC_CORE0_221_ISR_CAT))
#if (OSEE_TC_CORE0_221_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 221)
#elif (OSEE_TC_CORE0_221_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 221)
#else
#error Invalid value for OSEE_TC_CORE0_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 221)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 221)
#endif /* OSEE_TC_CORE0_221_ISR_CAT */
#if (defined(OSEE_TC_CORE0_222_ISR_CAT))
#if (OSEE_TC_CORE0_222_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 222)
#elif (OSEE_TC_CORE0_222_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 222)
#else
#error Invalid value for OSEE_TC_CORE0_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 222)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 222)
#endif /* OSEE_TC_CORE0_222_ISR_CAT */
#if (defined(OSEE_TC_CORE0_223_ISR_CAT))
#if (OSEE_TC_CORE0_223_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 223)
#elif (OSEE_TC_CORE0_223_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 223)
#else
#error Invalid value for OSEE_TC_CORE0_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 223)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 223)
#endif /* OSEE_TC_CORE0_223_ISR_CAT */
#if (defined(OSEE_TC_CORE0_224_ISR_CAT))
#if (OSEE_TC_CORE0_224_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 224)
#elif (OSEE_TC_CORE0_224_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 224)
#else
#error Invalid value for OSEE_TC_CORE0_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 224)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 224)
#endif /* OSEE_TC_CORE0_224_ISR_CAT */
#if (defined(OSEE_TC_CORE0_225_ISR_CAT))
#if (OSEE_TC_CORE0_225_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 225)
#elif (OSEE_TC_CORE0_225_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 225)
#else
#error Invalid value for OSEE_TC_CORE0_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 225)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 225)
#endif /* OSEE_TC_CORE0_225_ISR_CAT */
#if (defined(OSEE_TC_CORE0_226_ISR_CAT))
#if (OSEE_TC_CORE0_226_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 226)
#elif (OSEE_TC_CORE0_226_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 226)
#else
#error Invalid value for OSEE_TC_CORE0_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 226)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 226)
#endif /* OSEE_TC_CORE0_226_ISR_CAT */
#if (defined(OSEE_TC_CORE0_227_ISR_CAT))
#if (OSEE_TC_CORE0_227_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 227)
#elif (OSEE_TC_CORE0_227_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 227)
#else
#error Invalid value for OSEE_TC_CORE0_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 227)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 227)
#endif /* OSEE_TC_CORE0_227_ISR_CAT */
#if (defined(OSEE_TC_CORE0_228_ISR_CAT))
#if (OSEE_TC_CORE0_228_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 228)
#elif (OSEE_TC_CORE0_228_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 228)
#else
#error Invalid value for OSEE_TC_CORE0_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 228)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 228)
#endif /* OSEE_TC_CORE0_228_ISR_CAT */
#if (defined(OSEE_TC_CORE0_229_ISR_CAT))
#if (OSEE_TC_CORE0_229_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 229)
#elif (OSEE_TC_CORE0_229_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 229)
#else
#error Invalid value for OSEE_TC_CORE0_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 229)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 229)
#endif /* OSEE_TC_CORE0_229_ISR_CAT */
#if (defined(OSEE_TC_CORE0_230_ISR_CAT))
#if (OSEE_TC_CORE0_230_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 230)
#elif (OSEE_TC_CORE0_230_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 230)
#else
#error Invalid value for OSEE_TC_CORE0_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 230)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 230)
#endif /* OSEE_TC_CORE0_230_ISR_CAT */
#if (defined(OSEE_TC_CORE0_231_ISR_CAT))
#if (OSEE_TC_CORE0_231_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 231)
#elif (OSEE_TC_CORE0_231_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 231)
#else
#error Invalid value for OSEE_TC_CORE0_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 231)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 231)
#endif /* OSEE_TC_CORE0_231_ISR_CAT */
#if (defined(OSEE_TC_CORE0_232_ISR_CAT))
#if (OSEE_TC_CORE0_232_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 232)
#elif (OSEE_TC_CORE0_232_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 232)
#else
#error Invalid value for OSEE_TC_CORE0_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 232)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 232)
#endif /* OSEE_TC_CORE0_232_ISR_CAT */
#if (defined(OSEE_TC_CORE0_233_ISR_CAT))
#if (OSEE_TC_CORE0_233_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 233)
#elif (OSEE_TC_CORE0_233_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 233)
#else
#error Invalid value for OSEE_TC_CORE0_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 233)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 233)
#endif /* OSEE_TC_CORE0_233_ISR_CAT */
#if (defined(OSEE_TC_CORE0_234_ISR_CAT))
#if (OSEE_TC_CORE0_234_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 234)
#elif (OSEE_TC_CORE0_234_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 234)
#else
#error Invalid value for OSEE_TC_CORE0_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 234)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 234)
#endif /* OSEE_TC_CORE0_234_ISR_CAT */
#if (defined(OSEE_TC_CORE0_235_ISR_CAT))
#if (OSEE_TC_CORE0_235_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 235)
#elif (OSEE_TC_CORE0_235_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 235)
#else
#error Invalid value for OSEE_TC_CORE0_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 235)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 235)
#endif /* OSEE_TC_CORE0_235_ISR_CAT */
#if (defined(OSEE_TC_CORE0_236_ISR_CAT))
#if (OSEE_TC_CORE0_236_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 236)
#elif (OSEE_TC_CORE0_236_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 236)
#else
#error Invalid value for OSEE_TC_CORE0_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 236)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 236)
#endif /* OSEE_TC_CORE0_236_ISR_CAT */
#if (defined(OSEE_TC_CORE0_237_ISR_CAT))
#if (OSEE_TC_CORE0_237_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 237)
#elif (OSEE_TC_CORE0_237_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 237)
#else
#error Invalid value for OSEE_TC_CORE0_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 237)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 237)
#endif /* OSEE_TC_CORE0_237_ISR_CAT */
#if (defined(OSEE_TC_CORE0_238_ISR_CAT))
#if (OSEE_TC_CORE0_238_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 238)
#elif (OSEE_TC_CORE0_238_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 238)
#else
#error Invalid value for OSEE_TC_CORE0_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 238)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 238)
#endif /* OSEE_TC_CORE0_238_ISR_CAT */
#if (defined(OSEE_TC_CORE0_239_ISR_CAT))
#if (OSEE_TC_CORE0_239_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 239)
#elif (OSEE_TC_CORE0_239_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 239)
#else
#error Invalid value for OSEE_TC_CORE0_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 239)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 239)
#endif /* OSEE_TC_CORE0_239_ISR_CAT */
#if (defined(OSEE_TC_CORE0_240_ISR_CAT))
#if (OSEE_TC_CORE0_240_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 240)
#elif (OSEE_TC_CORE0_240_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 240)
#else
#error Invalid value for OSEE_TC_CORE0_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 240)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 240)
#endif /* OSEE_TC_CORE0_240_ISR_CAT */
#if (defined(OSEE_TC_CORE0_241_ISR_CAT))
#if (OSEE_TC_CORE0_241_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 241)
#elif (OSEE_TC_CORE0_241_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 241)
#else
#error Invalid value for OSEE_TC_CORE0_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 241)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 241)
#endif /* OSEE_TC_CORE0_241_ISR_CAT */
#if (defined(OSEE_TC_CORE0_242_ISR_CAT))
#if (OSEE_TC_CORE0_242_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 242)
#elif (OSEE_TC_CORE0_242_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 242)
#else
#error Invalid value for OSEE_TC_CORE0_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 242)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 242)
#endif /* OSEE_TC_CORE0_242_ISR_CAT */
#if (defined(OSEE_TC_CORE0_243_ISR_CAT))
#if (OSEE_TC_CORE0_243_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 243)
#elif (OSEE_TC_CORE0_243_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 243)
#else
#error Invalid value for OSEE_TC_CORE0_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 243)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 243)
#endif /* OSEE_TC_CORE0_243_ISR_CAT */
#if (defined(OSEE_TC_CORE0_244_ISR_CAT))
#if (OSEE_TC_CORE0_244_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 244)
#elif (OSEE_TC_CORE0_244_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 244)
#else
#error Invalid value for OSEE_TC_CORE0_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 244)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 244)
#endif /* OSEE_TC_CORE0_244_ISR_CAT */
#if (defined(OSEE_TC_CORE0_245_ISR_CAT))
#if (OSEE_TC_CORE0_245_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 245)
#elif (OSEE_TC_CORE0_245_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 245)
#else
#error Invalid value for OSEE_TC_CORE0_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 245)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 245)
#endif /* OSEE_TC_CORE0_245_ISR_CAT */
#if (defined(OSEE_TC_CORE0_246_ISR_CAT))
#if (OSEE_TC_CORE0_246_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 246)
#elif (OSEE_TC_CORE0_246_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 246)
#else
#error Invalid value for OSEE_TC_CORE0_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 246)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 246)
#endif /* OSEE_TC_CORE0_246_ISR_CAT */
#if (defined(OSEE_TC_CORE0_247_ISR_CAT))
#if (OSEE_TC_CORE0_247_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 247)
#elif (OSEE_TC_CORE0_247_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 247)
#else
#error Invalid value for OSEE_TC_CORE0_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 247)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 247)
#endif /* OSEE_TC_CORE0_247_ISR_CAT */
#if (defined(OSEE_TC_CORE0_248_ISR_CAT))
#if (OSEE_TC_CORE0_248_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 248)
#elif (OSEE_TC_CORE0_248_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 248)
#else
#error Invalid value for OSEE_TC_CORE0_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 248)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 248)
#endif /* OSEE_TC_CORE0_248_ISR_CAT */
#if (defined(OSEE_TC_CORE0_249_ISR_CAT))
#if (OSEE_TC_CORE0_249_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 249)
#elif (OSEE_TC_CORE0_249_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 249)
#else
#error Invalid value for OSEE_TC_CORE0_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 249)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 249)
#endif /* OSEE_TC_CORE0_249_ISR_CAT */
#if (defined(OSEE_TC_CORE0_250_ISR_CAT))
#if (OSEE_TC_CORE0_250_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 250)
#elif (OSEE_TC_CORE0_250_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 250)
#else
#error Invalid value for OSEE_TC_CORE0_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 250)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 250)
#endif /* OSEE_TC_CORE0_250_ISR_CAT */
#if (defined(OSEE_TC_CORE0_251_ISR_CAT))
#if (OSEE_TC_CORE0_251_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 251)
#elif (OSEE_TC_CORE0_251_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 251)
#else
#error Invalid value for OSEE_TC_CORE0_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 251)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 251)
#endif /* OSEE_TC_CORE0_251_ISR_CAT */
#if (defined(OSEE_TC_CORE0_252_ISR_CAT))
#if (OSEE_TC_CORE0_252_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 252)
#elif (OSEE_TC_CORE0_252_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 252)
#else
#error Invalid value for OSEE_TC_CORE0_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 252)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 252)
#endif /* OSEE_TC_CORE0_252_ISR_CAT */
#if (defined(OSEE_TC_CORE0_253_ISR_CAT))
#if (OSEE_TC_CORE0_253_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 253)
#elif (OSEE_TC_CORE0_253_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 253)
#else
#error Invalid value for OSEE_TC_CORE0_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 253)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 253)
#endif /* OSEE_TC_CORE0_253_ISR_CAT */
#if (defined(OSEE_TC_CORE0_254_ISR_CAT))
#if (OSEE_TC_CORE0_254_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 254)
#elif (OSEE_TC_CORE0_254_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 254)
#else
#error Invalid value for OSEE_TC_CORE0_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 254)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 254)
#endif /* OSEE_TC_CORE0_254_ISR_CAT */
#if (defined(OSEE_TC_CORE0_255_ISR_CAT))
#if (OSEE_TC_CORE0_255_ISR_CAT == 2)
OSEE_ISR2_DECLARE(OSEE_CORE0_S, 255)
#elif (OSEE_TC_CORE0_255_ISR_CAT == 1)
OSEE_ISR1_DECLARE(OSEE_CORE0_S, 255)
#else
#error Invalid value for OSEE_TC_CORE0_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 255)
OSEE_DUMMY_ISR(OSEE_CORE0_S, 255)
#endif /* OSEE_TC_CORE0_255_ISR_CAT */
#endif /* OSEE_TC_CORE0_ISR_MAX_PRIO */

#endif /* __TASKING__ */

