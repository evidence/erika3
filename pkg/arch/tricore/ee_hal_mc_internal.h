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

/** \file   ee_hal.h
 *  \brief  HAL support visible to the application, for multi-core
 *          applications.
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

#ifndef OSEE_HAL_MC_INTERNAL_H
#define OSEE_HAL_MC_INTERNAL_H

#include "ee_cfg.h"

#if (!defined(OSEE_SINGLECORE))

#include "ee_hal_mc.h"
#include "ee_kernel_types.h"
#include "ee_hal_internal.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#define OSEE_TC_SFR_BASE              ((OsEE_reg)0xF8800000U)
#define OSEE_TC_CFSR_BASE             ((OsEE_reg)0xF8810000U)
#define OSEE_TC_XFSR_CORE_OFFSET(c)   ((OsEE_reg)(c) * 0x20000U)
#define OSEE_TC_CFSR_ADDR(c,offset)\
  (OSEE_TC_CFSR_BASE + OSEE_TC_XFSR_CORE_OFFSET(c) +\
    (((OsEE_reg)(offset)) & 0xFFFFU))

#define OSEE_TC_CFSR_TASK_ASI   (0x8004U)
#define OSEE_TC_CFSR_PCXI       (0xFE00U)
#define OSEE_TC_CFSR_PSW        (0xFE04U)
#define OSEE_TC_CFSR_PC         (0xFE08U)
#define OSEE_TC_CFSR_SYSCON     (0xFE14U)
#define OSEE_TC_CFSR_DBGSR      (0xFD00U)

#define OSEE_TC_CORE_SYSCON(c)\
  (*(OsEE_syscon volatile *)OSEE_TC_CFSR_ADDR((c),OSEE_TC_CFSR_SYSCON))

void osEE_hal_sync_barrier(OsEE_barrier * p_bar,
  OsEE_reg const volatile * p_wait_mask, OsEE_kernel_cb p_synch_cb);

/** \brief  Program Counter */
typedef struct OsEE_tc_CPU_PC_bits_tag
{
/**< \brief \internal Reserved */
  unsigned      : 1;
/**< \brief [31:1] Program Counter (r) */
  unsigned  pc  : 31;
} OsEE_tc_CPU_PC_bits;

/** \brief Program Counter Register */
typedef union
{
/** \brief Unsigned access */
  OsEE_reg            reg;
/** \brief Bitfield access */
  OsEE_tc_CPU_PC_bits bits;
} OsEE_tc_CPU_PC;

#define OSEE_TC_CORE_PC(c)\
  (*(OsEE_tc_CPU_PC volatile *)OSEE_TC_CFSR_ADDR((c),OSEE_TC_CFSR_PC))

#if (!defined(OSEE_TC_2G))
/** \brief  Debug Status Register */
typedef struct OsEE_tc_CPU_DBGSR_bits_tag
{
/**< \brief [0:0] Debug Enable (rh) */
  unsigned de       : 1;
/**< \brief [2:1] CPU Halt Request / Status Field (rwh) */
  unsigned halt     : 2;
/**< \brief [3:3] Suspend-in Halt (rh) */
  unsigned sih      : 1;
/**< \brief [4:4] Current State of the Core Suspend-Out Signal (rwh) */
  unsigned susp     : 1;
/**< \brief \internal Reserved */
  unsigned          : 1;
/**< \brief [6:6] Previous State of Core Suspend-Out Signal (rh) */
  unsigned prevsusp : 1;
/**< \brief [7:7] Posted Event (rwh) */
  unsigned pevt     : 1;
/**< \brief [12:8] Event Source (rh) */
  unsigned evtsrc   : 5;
/**< \brief \internal Reserved */
  unsigned          : 19;
} OsEE_tc_CPU_DBGSR_bits;

/** \brief Debug Status Register */
typedef union
{
/** \brief Unsigned access */
  OsEE_reg               reg;
/** \brief Bitfield access */
  OsEE_tc_CPU_DBGSR_bits bits;
} OsEE_tc_CPU_DBGSR;

#define OSEE_TC_CORE_DBGSR(c)\
  (*(OsEE_tc_CPU_DBGSR volatile *)OSEE_TC_CFSR_ADDR((c),OSEE_TC_CFSR_DBGSR))
/* Value that have to be written to DBGSR to put the Core on RUN */
#define OSEE_TC_DBGSR_RESET_HALT (2U)
#endif /* !OSEE_TC_2G */

/** \brief start the core represented by id parameter from the statically
           configured start-up address */
extern void osEE_hal_start_core(CoreIdType core_id);

/******************************************************************************
                            Multicore CPU Signal
 *****************************************************************************/

/******************************************************************************
          General Purpose Software Request (GPSR) [Software Interrupts]
 *****************************************************************************/

#if (!defined(OSEE_TC_2G))
#define OSEE_TC_GPSR_OFFSET     (0x1000U)
#define OSEE_TC_GPSR_MAX_CH     (2U)
#else
#define OSEE_TC_GPSR_OFFSET     (0x0990U)
#define OSEE_TC_GPSR_MAX_CH     (7U)
#endif /* !OSEE_TC_2G */

#define OSEE_TC_GPSR_GROUP_OFFSET(g)  (((g) & 0x3U) * 0x20U)

#define OSEE_TC_GPSR_SRC_OFFSET(g, n)\
  (OSEE_TC_GPSR_OFFSET + OSEE_TC_GPSR_GROUP_OFFSET(g) + \
    ((((OsEE_reg)(n) <= OSEE_TC_GPSR_MAX_CH)?\
        (OsEE_reg)(n):\
        (OsEE_reg)0U) * 0x4U))

/* Software Interrupts Broadcast (Only the bits[0:3] can be set. It makes sense
   using these registers with 0x7U or 0xFU as mask to broadcast a request to
   multiple service nodes of a group */
#define OSEE_TC_INT_SRB0  (*(OsEE_reg volatile *)0xF0037010U)
#define OSEE_TC_INT_SRB1  (*(OsEE_reg volatile *)0xF0037014U)
#define OSEE_TC_INT_SRB2  (*(OsEE_reg volatile *)0xF0037018U)

#if (!defined(OSEE_TC_GPSR_G))
#define OSEE_TC_GPSR_G (0x0U)
#endif /* OSEE_TC_GPSR_G */

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_setup_inter_irqs(void)
{
  /*  Assign TOS (Type of Service Control:Read CPU) enable and assign
      entry(priority) in INTTAB. (Priority is statically chosen as the smallest
      possible. RT-Druid MUST ensure that no other ISR will be generated with
      this priority) */
  osEE_tc_conf_src(OS_CORE_ID_0,
    OSEE_TC_GPSR_SRC_OFFSET(OSEE_TC_GPSR_G, 0U), 1U);
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
  osEE_tc_conf_src(OS_CORE_ID_1,
    OSEE_TC_GPSR_SRC_OFFSET(OSEE_TC_GPSR_G, 1U), 1U);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
  osEE_tc_conf_src(OS_CORE_ID_2,
    OSEE_TC_GPSR_SRC_OFFSET(OSEE_TC_GPSR_G, 2U), 1U);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
  osEE_tc_conf_src(OS_CORE_ID_3,
    OSEE_TC_GPSR_SRC_OFFSET(OSEE_TC_GPSR_G, 3U), 1U);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
  osEE_tc_conf_src(OS_CORE_ID_4,
    OSEE_TC_GPSR_SRC_OFFSET(OSEE_TC_GPSR_G, 4U), 1U);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
  osEE_tc_conf_src(OS_CORE_ID_6,
    OSEE_TC_GPSR_SRC_OFFSET(OSEE_TC_GPSR_G, 6U), 1U);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */
}

/* Signal the core "cpu" (0/1/2/3/4/6) by sending an IIRQ. */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_hal_signal_core(CoreIdType core_id)
{

  OSEE_TC_SRC_REG(OSEE_TC_GPSR_SRC_OFFSET(OSEE_TC_GPSR_G, core_id)) |=
    OSEE_TC_SRN_SET_REQUEST;
}

/* Acknowledge the signal received by the core "cpu" (0/1/2/3/4/6) */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_ack_signal(void)
{
  CoreIdType core_id = osEE_get_curr_core_id();

  OSEE_TC_SRC_REG(OSEE_TC_GPSR_SRC_OFFSET(OSEE_TC_GPSR_G, core_id)) |=
    (OSEE_TC_SRN_CLEAR_REQUEST | OSEE_TC_SRN_STICKY_CLEAR);
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_hal_signal_broadcast(void)
{
#if (defined(OSEE_TC_GPSR_G))
#if (OSEE_TC_GPSR_G == 0x0U)
OSEE_TC_INT_SRB0 = OSEE_CORE_ID_VALID_MASK;
#elif (OSEE_TC_GPSR_G == 0x1U)
OSEE_TC_INT_SRB1 = OSEE_CORE_ID_VALID_MASK;
#elif (OSEE_TC_GPSR_G == 0x2U)
OSEE_TC_INT_SRB2 = OSEE_CORE_ID_VALID_MASK;
#endif
#endif /* OSEE_TC_GPSR_G */
}

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_SINGLECORE */
#endif /* !OSEE_HAL_MC_INTERNAL_H */
