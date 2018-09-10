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

#if (!defined(OSEE_HAL_MC_INTERNAL_H))
#define OSEE_HAL_MC_INTERNAL_H

#include "ee_cfg.h"

#if (!defined(OSEE_SINGLECORE))

#include "ee_hal_mc.h"
#include "ee_kernel_types.h"

void osEE_hal_sync_barrier(OsEE_barrier * p_bar,
  OsEE_reg volatile * p_wait_mask, OsEE_kernel_cb p_synch_cb);

/** \brief  Program Counter */
typedef struct OsEE_tc_CPU_PC_bits_tag
{
/**< \brief \internal Reserved */
  unsigned      : 1;
/**< \brief [31:1] Program Counter (r) */
  unsigned  pc  : 31;
} OsEE_tc_CPU_PC_bits;

/** \brief Program Counter Register */
typedef union OsEE_tc_CPU_PC_tag
{
/** \brief Unsigned access */
  OsEE_reg            reg;
/** \brief Bitfield access */
  OsEE_tc_CPU_PC_bits bits;
} OsEE_tc_CPU_PC;

#define OSEE_TC_CPU1_PC   (*(OsEE_tc_CPU_PC volatile *)0xF883FE08U)
#define OSEE_TC_CPU2_PC   (*(OsEE_tc_CPU_PC volatile *)0xF885FE08U)

/** \\brief  Debug Status Register */
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
typedef union OsEE_tc_CPU_DBGSR_tag
{
/** \brief Unsigned access */
  OsEE_reg               reg;
/** \brief Bitfield access */
  OsEE_tc_CPU_DBGSR_bits bits;
} OsEE_tc_CPU_DBGSR;

#define OSEE_TC_CPU1_DBGSR (*(OsEE_tc_CPU_DBGSR volatile *)0xF883FD00U)
#define OSEE_TC_CPU2_DBGSR (*(OsEE_tc_CPU_DBGSR volatile *)0xF885FD00U)

/* Value that have to be write to DBGSR to put the Core on RUN at reset time */
#define OSEE_RESET_DBGSR_HALT (2U)
/** @brief start the core represented by id parameter from the statically
           configured start-up address */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_hal_start_core(
  CoreIdType core_id)
{
  switch (core_id) {
    case OS_CORE_ID_0:
    /* Nothing to do in this case */
    break;
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x2U)
    case OS_CORE_ID_1:
      OSEE_TC_CPU1_PC.reg           = (uint32_t)OSEE_CORE1_START_ADDR;
      OSEE_TC_CPU1_DBGSR.bits.halt  = OSEE_RESET_DBGSR_HALT;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x2U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x4U)
    case OS_CORE_ID_2:
      OSEE_TC_CPU2_PC.reg           = (uint32_t)OSEE_CORE2_START_ADDR;
      OSEE_TC_CPU2_DBGSR.bits.halt  = OSEE_RESET_DBGSR_HALT;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x4U */
    default:
    break;
  }
}

/*******************************************************************************
                            Multicore CPU Signal
 ******************************************************************************/

/******************************************************************************
          General Purpose Software Request (GPSR) [Software Interrupts]
 *****************************************************************************/

#define OSEE_TC_GPSR_BASE             (0xF0039000u)

#define OSEE_TC_GPSR_GROUP_OFFSET(g)  (((g) & 0x3U) * 0x20U)

#define OSEE_TC_GPSR_ADDR_SR(g, n)\
  (OSEE_TC_GPSR_BASE + OSEE_TC_GPSR_GROUP_OFFSET(g) + \
    ((((OsEE_reg)n <= 2U)? (OsEE_reg)n: (OsEE_reg)0U) * 0x4U))

#define OSEE_TC_GPSR_SRC(c, n)\
  (*(OsEE_reg volatile *)OSEE_TC_GPSR_ADDR_SR(c, n))

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
  OSEE_TC_GPSR_SRC(OSEE_TC_GPSR_G, 0U) =  OSEE_TC_SRN_ENABLE |
    OSEE_TC_SRN_TYPE_OF_SERVICE(OS_CORE_ID_0) | OSEE_TC_SRN_PRIORITY(1U);
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x2U)
  OSEE_TC_GPSR_SRC(OSEE_TC_GPSR_G, 1U) =  OSEE_TC_SRN_ENABLE |
    OSEE_TC_SRN_TYPE_OF_SERVICE(OS_CORE_ID_1) | OSEE_TC_SRN_PRIORITY(1U);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x2U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x4U)
  OSEE_TC_GPSR_SRC(OSEE_TC_GPSR_G, 2U) =  OSEE_TC_SRN_ENABLE |
    OSEE_TC_SRN_TYPE_OF_SERVICE(OS_CORE_ID_2) | OSEE_TC_SRN_PRIORITY(1U);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x4U */
}

/* Signal the core "cpu" (0/1/2) by sending an IIRQ. */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_hal_signal_core(CoreIdType core_id)
{
  if (core_id == OS_CORE_ID_0) {
    OSEE_TC_GPSR_SRC(OSEE_TC_GPSR_G, 0U) |= OSEE_TC_SRN_SET_REQUEST;
  } else
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x2U)
  if (core_id == OS_CORE_ID_1) {
    OSEE_TC_GPSR_SRC(OSEE_TC_GPSR_G, 1U) |= OSEE_TC_SRN_SET_REQUEST;
  } else
#endif /* OSEE_CORE_ID_VALID_MASK & 0x2U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x4U)
  if (core_id == OS_CORE_ID_2) {
    OSEE_TC_GPSR_SRC(OSEE_TC_GPSR_G, 2U) |= OSEE_TC_SRN_SET_REQUEST;
  } else
#endif /* OSEE_CORE_ID_VALID_MASK & 0x4U */
  {
    /* Empty else statement to comply with MISRA 14.10 */
  }
}

/* Acknowledge the signal received by the core "cpu" (0/1/2) */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_ack_signal(void)
{
  CoreIdType core_id = osEE_get_curr_core_id();
  if (core_id == OS_CORE_ID_0) {
    OSEE_TC_GPSR_SRC(OSEE_TC_GPSR_G, 0U) |= OSEE_TC_SRN_CLEAR_REQUEST;
  } else
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x2U)
  if (core_id == OS_CORE_ID_1) {
    OSEE_TC_GPSR_SRC(OSEE_TC_GPSR_G, 1U) |= OSEE_TC_SRN_CLEAR_REQUEST;
  } else
#endif /* OSEE_CORE_ID_VALID_MASK & 0x2U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x4U)
  if (core_id == OS_CORE_ID_2) {
    OSEE_TC_GPSR_SRC(OSEE_TC_GPSR_G, 2U) |= OSEE_TC_SRN_CLEAR_REQUEST;
  } else
#endif /* OSEE_CORE_ID_VALID_MASK & 0x4U */
  {
    /* Empty else statement to comply with MISRA 14.10 */
  }
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

#endif /* !OSEE_SINGLECORE */
#endif /* !OSEE_HAL_MC_INTERNAL_H */
