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
        OsEE_reg const srn_priority_tmp =
          OSEE_TC_SRN_PRIORITY((*p_isr1_db->p_isr1_src_array)[i].isr_prio);
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

