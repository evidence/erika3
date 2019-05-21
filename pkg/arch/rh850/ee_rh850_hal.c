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
 *  \brief  RH850 HAL not inline
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

#include "ee_internal.h"

#if (!defined(OSEE_LIB_EMBARK_G4MH))
void osEE_rh850_isr2_wrapper(TaskType tid,
  OsEE_rh850_exception_ctx const * p_ei_ctx)
{
#if (defined(OSEE_DEBUG))
  /* Just for debug */
  static OsEE_rh850_exception_ctx const * volatile osEE_p_ei_ctx;
  /* Save EI CTX for debug */
  osEE_p_ei_ctx = p_ei_ctx;
#else
  /* Touch Unused Parameter */
  (void)p_ei_ctx;
#endif /* OSEE_DEBUG */
#if 0
#if (!defined(OSEE_SINGLECORE))
  if (tid == INVALID_TASK) {
    osEE_rh850_handle_ipir();
  } else
#endif /* !OSEE_SINGLECORE */
#endif /* 0 */
  {
    /* For Now I need Only this */
    osEE_activate_isr2(tid);
    /* I need to disable IRQ here since I'm lowering PLMR, and I don't want to
       allow nesting here before context restoring. Multiple ISR context
       stacking for the same TASK have not to happens for stack bounding. */
    osEE_hal_disableIRQ();
    osEE_hal_end_nested_primitive(OSEE_ISR_UNMASKED);
  }
}
#endif /* !OSEE_LIB_EMBARK_G4MH */

#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
void osEE_rh850_initialize_core_stacks(void) {
  MemSize       i;
  OsEE_stack *  p_stack;
  OsEE_CDB   *  const p_cdb = osEE_get_curr_core();

  /* Number of stacks excluded the system stack which is the last one */
  MemSize const stack_number = p_cdb->chdb.stack_num - 1U;
  /* Initialize all TASK stacks */
  for (i = 0U; i < stack_number; ++i) {
    MemSize j;
    /* number of words to write with the fillpattern */
    MemSize const stack_words =
      (*p_cdb->chdb.p_sdb_array)[i].stack_size / sizeof(OsEE_stack);

    p_stack = (OsEE_stack *)(*p_cdb->chdb.p_sdb_array)[i].p_bos;
    for (j = 0U; j <= stack_words; ++j) {
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

#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */
