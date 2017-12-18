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

/** \file  ee_k1_irq.c
 *  \brief  Interrupt Request Handler (based on Kalray BSP support).
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */


/* I need Kernel inclusion for Common Context and Service Protection */
#include "ee_internal.h"

typedef struct {
  enum {
    OSEE_ISR_CAT_1 = 1U,
    OSEE_ISR_CAT_2
  } cat;
  union {
    void (*p_hnd_func) ( void );
    TaskType tid;
  } hnd;
} OsEE_k1_hnd_type;

#if (defined(OSEE_API_DYNAMIC))
OsEE_k1_hnd_type osEE_k1_int_vectors[OSEE_K1_CORE_NUMBER][OSEE_ISR_NUMBER] =
{
  [0 ... (OSEE_K1_CORE_NUMBER - 1U)] =
  {
    [0 ... (OSEE_ISR_NUMBER - 1U)] =
    {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = INVALID_TASK
    }
  }
};

FUNC(StatusType, OS_CODE)
  osEE_hal_set_isr2_source
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb,
  VAR(ISRSource,  AUTOMATIC)                source_id
)
{
  CoreIdType          const core_id = osEE_get_curr_core_id();
  OsEE_k1_hnd_type *  const p_hnd   = &osEE_k1_int_vectors[core_id][source_id];
  /* Adjust the priority as machine priority */
  TaskPrio  const isr2_prio = OSEE_ISR2_VIRT_TO_HW_PRIO(p_tdb->ready_prio);

  p_hnd->cat          = OSEE_ISR_CAT_2;
  p_hnd->hnd.tid      = p_tdb->tid;

  p_tdb->hdb.isr_src  = source_id;

  /* Interrupt Service Routine registration for OS: Unique Handler */
  bsp_register_it(osEE_os_it_handler, source_id);
  mOS_configure_int(source_id, isr2_prio);
  return E_OK;
}
#else

OsEE_k1_hnd_type const
  osEE_k1_int_vectors[OSEE_K1_CORE_NUMBER][OSEE_ISR_NUMBER] =
{
  [0] =
  {
    /* timer0 */
#if (defined(OSEE_K1_CORE0_BSP_IT_TIMER_0_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_TIMER_0_ISR_CAT == 2)
    [BSP_IT_TIMER_0]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_TIMER_0_ISR_TID
    },
#else
    [BSP_IT_TIMER_0]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_TIMER_0_ISR_HND
    },
#endif
#else
    [BSP_IT_TIMER_0]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_TIMER_0_ISR_CAT */

    /* timer1 */
#if (defined(OSEE_K1_CORE0_BSP_IT_TIMER_1_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_TIMER_1_ISR_CAT == 2)
    [BSP_IT_TIMER_1]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_TIMER_1_ISR_TID
    },
#else
    [BSP_IT_TIMER_1]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_TIMER_1_ISR_HND
    },
#endif
#else
    [BSP_IT_TIMER_1]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_TIMER_1_ISR_CAT */

    /* watchdog */
#if (defined(OSEE_K1_CORE0_BSP_IT_WDOG_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_TIMER_1_ISR_CAT == 2)
    [BSP_IT_WDOG]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_WDOG_ISR_TID
    },
#else
    [BSP_IT_WDOG]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_WDOG_ISR_HND
    },
#endif
#else
    [BSP_IT_WDOG]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_WDOG_ISR_CAT */

    /* control noc */
#if (defined(OSEE_K1_CORE0_BSP_IT_CN_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_CN_ISR_CAT == 2)
    [BSP_IT_CN]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_CN_ISR_TID
    },
#else
    [BSP_IT_CN]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_CN_ISR_HND
    },
#endif
#else
    [BSP_IT_CN]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_CN_ISR_CAT */

    /* dnoc rx */
#if (defined(OSEE_K1_CORE0_BSP_IT_RX_ISR_CAT))
#if (OSEE_K1_CORE0__BSP_IT_RX_ISR_CAT == 2)
    [BSP_IT_RX]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_RX_ISR_TID
    },
#else
    [BSP_IT_RX]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_RX_ISR_HND
    },
#endif
#else
    [BSP_IT_RX]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_RX_ISR_CAT */

    /* dma uc */
#if (defined(OSEE_K1_CORE0_BSP_IT_UC_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_UC_ISR_CAT == 2)
    [BSP_IT_UC]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_UC_ISR_TID
    },
#else
    [BSP_IT_UC]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_UC_ISR_HND
    },
#endif
#else
    [BSP_IT_UC]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_UC_ISR_CAT */

    /* noc error */
#if (defined(OSEE_K1_CORE0_BSP_IT_NE_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_NE_ISR_CAT == 2)
    [BSP_IT_NE]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_NE_ISR_TID
    },
#else
    [BSP_IT_NE]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_NE_ISR_HND
    },
#endif
#else
    [BSP_IT_NE]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_NE_ISR_CAT */

    /* watchdog underflow */
#if (defined(OSEE_K1_CORE0_BSP_IT_WDOG_U_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_WDOG_U_ISR_CAT == 2)
    [BSP_IT_WDOG_U]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_WDOG_U_ISR_TID
    },
#else
    [BSP_IT_WDOG_U]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_WDOG_U_ISR_HND
    },
#endif
#else
    [BSP_IT_WDOG_U]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_WDOG_U_ISR_CAT */

    /* remote pe event 0: Reserved as rescheduling IIRQ */

    /* remote pe event 1 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_1_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_1_ISR_CAT == 2)
    [BSP_IT_PE_1]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_1_ISR_TID
    },
#else
    [BSP_IT_PE_1]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_1_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_1]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_1_ISR_CAT */

    /* remote pe event 2 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_2_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_2_ISR_CAT == 2)
    [BSP_IT_PE_2]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_2_ISR_TID
    },
#else
    [BSP_IT_PE_2]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_2_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_2]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_2_ISR_CAT */

    /* remote pe event 3 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_3_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_3_CAT == 2)
    [BSP_IT_PE_3]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_3_ISR_TID
    },
#else
    [BSP_IT_PE_3]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_3_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_3]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_3_ISR_CAT */

    /* remote pe event 4 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_4_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_4_CAT == 2)
    [BSP_IT_PE_4]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_4_ISR_TID
    },
#else
    [BSP_IT_PE_4]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_4_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_4]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_4_ISR_CAT */

    /* remote pe event 5 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_5_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_5_ISR_CAT == 2)
    [BSP_IT_PE_5]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_5_ISR_TID
    },
#else
    [BSP_IT_PE_5]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_5_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_5]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_5_ISR_CAT */

    /* remote pe event 6 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_6_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_6_ISR_CAT == 2)
    [BSP_IT_PE_6]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_6_ISR_TID
    },
#else
    [BSP_IT_PE_6]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_6_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_6]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_6_ISR_CAT */

    /* remote pe event 7 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_7_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_7_ISR_CAT == 2)
    [BSP_IT_PE_7]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_7_ISR_TID
    },
#else
    [BSP_IT_PE_7]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_7_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_7]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_7_ISR_CAT */

    /* remote pe event 8 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_8_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_8_ISR_CAT == 2)
    [BSP_IT_PE_8]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_8_ISR_TID
    },
#else
    [BSP_IT_PE_8]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_8_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_8]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_8_ISR_CAT */

    /* remote pe event 9 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_9_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_9_ISR_CAT == 2)
    [BSP_IT_PE_9]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_9_ISR_TID
    },
#else
    [BSP_IT_PE_9]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_9_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_9]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_9_ISR_CAT */

    /* remote pe event 10 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_10_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_10_ISR_CAT == 2)
    [BSP_IT_PE_10]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_10_ISR_TID
    },
#else
    [BSP_IT_PE_10]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_10_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_10]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_10_ISR_CAT */

    /* remote pe event 11 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_11_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_11_ISR_CAT == 2)
    [BSP_IT_PE_11]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_11_ISR_TID
    },
#else
    [BSP_IT_PE_11]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_11_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_11]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_11_ISR_CAT */

    /* remote pe event 12 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_12_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_12_ISR_CAT == 2)
    [BSP_IT_PE_12]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_12_ISR_TID
    },
#else
    [BSP_IT_PE_12]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_12_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_12]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_12_ISR_CAT */

    /* remote pe event 13 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_13_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_13_ISR_CAT == 2)
    [BSP_IT_PE_13]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_13_ISR_TID
    },
#else
    [BSP_IT_PE_13]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_13_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_13]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_13_ISR_CAT */

    /* remote pe event 14 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_14_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_14_ISR_CAT == 2)
    [BSP_IT_PE_14]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_14_ISR_TID
    },
#else
    [BSP_IT_PE_14]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_14_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_14]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_14_ISR_CAT */

    /* remote pe event 15 */
#if (defined(OSEE_K1_CORE0_BSP_IT_PE_15_ISR_CAT))
#if (OSEE_K1_CORE0_BSP_IT_PE_15_ISR_CAT == 2)
    [BSP_IT_PE_15]  = {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = OSEE_K1_CORE0_BSP_IT_PE_15_ISR_TID
    },
#else
    [BSP_IT_PE_15]  = {
      .cat = OSEE_ISR_CAT_1,
      .hnd.p_hnd_func = OSEE_K1_CORE0_BSP_IT_PE_15_ISR_HND
    },
#endif
#else
    [BSP_IT_PE_15]  = { .cat = OSEE_ISR_CAT_2, .hnd.tid = INVALID_TASK },
#endif /* OSEE_K1_CORE0_BSP_IT_PE_15_ISR_CAT */
  }
  /* TODO Add the configuration for the other (OSEE_K1_CORE_NUMBER - 1U)
   *      cores */
};

#if (defined(OSTICKDURATION))
#if (!defined(OSEE_SYSTEM_TIMER_DEVICE))
#error Unspecified System Timer Device!
#endif /* !OSEE_SYSTEM_TIMER_DEVICE */

#if (OSEE_SYSTEM_TIMER_DEVICE == OSEE_K1_BSP_IT_TIMER_0) ||\
    (OSEE_SYSTEM_TIMER_DEVICE == OSEE_K1_BSP_IT_TIMER_1)
#define OSEE_CLOCK_FREQ\
  (__bsp_frequency/(_K1_DEFAULT_CLOCK_DIV + 1))

#if (!defined(OSEE_KALRAY_K1_SIM_DEC))
#if (defined(OSEE_KALRAY_K1_SIM))
#define OSEE_KALRAY_K1_SIM_DEC (100U)
#else
#define OSEE_KALRAY_K1_SIM_DEC (1U)
#endif /* OSEE_KALRAY_K1_SIM */
#endif /* !OSEE_KALRAY_K1_SIM_DEC */

#define OSEE_TICKDURATION\
  (OSEE_MICRO_TO_TICKS(OSTICKDURATION/OSEE_KILO, OSEE_CLOCK_FREQ)/\
    OSEE_KALRAY_K1_SIM_DEC)

void osEE_kalray_k1_system_timer_handler(void) {
  OsEE_CDB * p_cdb = osEE_get_curr_core();
  osEE_counter_increment(p_cdb->p_sys_counter_db);
}
#else
#error Unsupported System Timer Device: OSEE_SYSTEM_TIMER_DEVICE!
#endif /* OSEE_SYSTEM_TIMER_DEVICE */
#endif /* OSTICKDURATION */

OsEE_bool osEE_cpu_startos ( void ) {
  size_t i;
  OsEE_KDB * const p_kdb = osEE_get_kernel();

  bsp_register_it(osEE_os_it_handler, BSP_IT_TIMER_0);
  bsp_register_it(osEE_os_it_handler, BSP_IT_TIMER_1);
  bsp_register_it(osEE_os_it_handler, BSP_IT_WDOG);
  bsp_register_it(osEE_os_it_handler, BSP_IT_CN);
  bsp_register_it(osEE_os_it_handler, BSP_IT_RX);
  bsp_register_it(osEE_os_it_handler, BSP_IT_UC);
  bsp_register_it(osEE_os_it_handler, BSP_IT_NE);
  bsp_register_it(osEE_os_it_handler, BSP_IT_WDOG_U);
/* From hereunder Virtual IIRQ provided by mOS hypervisor */
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_0);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_1);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_2);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_3);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_4);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_5);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_6);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_7);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_8);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_9);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_10);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_11);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_12);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_13);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_14);
  bsp_register_it(osEE_os_it_handler, BSP_IT_PE_15);

  for (i = 0U; i < (KDB.tdb_array_size - 1U); ++i)
  {
    /* ISR2 initialization */
    OsEE_TDB  * const p_tdb = (*p_kdb->p_tdb_ptr_array)[i];

    if (p_tdb->task_type == OSEE_TASK_TYPE_ISR2) {
      /* Adjust the priority as machine priority */
      OsEE_isr_src_id const source_id = p_tdb->hdb.isr_src;
      TaskPrio  const isr2_prio = OSEE_ISR2_VIRT_TO_HW_PRIO(p_tdb->ready_prio);

      mOS_configure_int(source_id, isr2_prio);
    }
  }

#if (defined(OSTICKDURATION))
  mOS_timer_general_setup();
  mOS_timer_setup_num(OSEE_SYSTEM_TIMER_DEVICE, OSEE_TICKDURATION,
    OSEE_TICKDURATION, OSEE_FALSE);
#endif /* OSTICKDURATION */

  return OSEE_TRUE;
}

#endif /* OSEE_API_DYNAMIC */

/* K1 BSP support handler Overridden */
/* ctx contain pointer to 64 register saved on the stack */
void osEE_os_it_handler ( int ev_src, __k1_vcontext_t *ctx ) {
  CoreIdType const cpu_id = osEE_get_curr_core_id();
#if (!defined(OSEE_SINGLECORE))
  /* Special IIRQ that ask the core to preempt actual TASK */
  if (ev_src >= OSEE_K1_RESCHEDULE_IIRQ)
  {
    osEE_k1_optimized_task_preemption_point();
  } else
#endif /* !OSEE_SINGLECORE */
  {
    OsEE_k1_hnd_type OSEE_CONST *  const p_hnd =
      &osEE_k1_int_vectors[cpu_id][ev_src];

    if (p_hnd->cat == OSEE_ISR_CAT_2) {
      TaskType const tid = p_hnd->hnd.tid;
      if (tid != INVALID_TASK) {
        osEE_activate_isr2(tid);
        /* Since PS is saved and restored in TASK context, when execution will
         * came be back here It will be still in ISR CTX, so we can just let
         * the IRQ wrapper epilogue to restore the previous context status */
      }
    } else {
      void (* const p_hnd_func) (void) = p_hnd->hnd.p_hnd_func;
      if (p_hnd_func != NULL) {
        p_hnd_func();
      }
    }
  }
}

