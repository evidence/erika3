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

/** \file   ee_hal_internal_types.h
 *  \brief  HAL Internal Types.
 *
 *  This files contains all HAL internal types and symbols for ARMv7-R
 *  Architecture in Erika Enterprise.
 *
 *  \note COULD BE raplaced by AUTOSAR Type definition paradigm or being the
 *        implementation
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#ifndef OSEE_HAL_INTERNAL_TYPES_H
#define OSEE_HAL_INTERNAL_TYPES_H

#include "ee_platform_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/*=============================================================================
              Core Special Function Registers Data Structures
 ============================================================================*/

/*******************************************************************************
 *  IMPORTANT:
 *  These struct layouts are packet by construction so I don't add 
 *  __attribute__((packed)) because it could harm performances.
 *  Look at:
 *  digitalvampire.org/blog/index.php/2006/07/31/\
 *  why-you-shouldnt-use-__attribute__packed
 ******************************************************************************/

/** Program Status Word */
typedef union {
  OsEE_reg reg;             /**< The register of the program status word */

  /** 
   * Consists of two variable width subfields.
   *
   * The first subfield consists of a string of zero or more initial 1
   * bits, terminated by the first 0 bit.
   *
   * The remaining bits form the second subfield(CDC.COUNT) which
   * constitutes the call depth count value.
   *
   * The count value is incremented on each Call and is decremented on
   * a Return.
   */
struct {
    unsigned int cdc    :7; /**< Call Depth Counter */
    unsigned int cde    :1; /**< Call Depth Count Enabled */
    unsigned int gw     :1; /**< Global Address Register Write Permission */
    unsigned int is     :1; /**< Interrupt Stack Control */
    unsigned int io     :2; /**< Access Privilege Level Ctrl (I/O Privilege) */
    unsigned int prs    :2; /**< Protection Register Set bits[0:1] */
    unsigned int s      :1; /**< Safety Task Identifier */
    unsigned int prs2   :1; /**< Protection Register Set bit[2] (AURIX Gen2) */
    unsigned int        :8;
/* User Status Bits */
    unsigned int        :3;
    unsigned int sav    :1; /**< Sticky Advance Overflow */
    unsigned int av     :1; /**< Advance Overflow */
    unsigned int sv     :1; /**< Sticky Overflow */
    unsigned int v      :1; /**< Overflow */
    unsigned int c      :1; /**< Carry */
  } bits;
} OsEE_psw;

/** Previous Context Information Register */
typedef union {
  OsEE_reg reg;             /**< the whole register */
  struct {
    unsigned int pcxo  :16; /**< Previous Context Pointer Offset Address  */
    unsigned int pcxs  :4;  /**< Previous Context Pointer Segment Address */
#if (defined(__TC13__)) || (defined(__TC131__))
    unsigned int       :1;  /**< In TC 1.3 bit20 is Reserved */
    unsigned int       :1;  /**< In TC 1.3 bit21 is Reserved */
#endif /* __TC13__ || __TC131__ */
    unsigned int ul    :1;  /**< Upper or Lower Context Tag */
    unsigned int pie   :1;  /**< Previous Interrupt Enable */
    unsigned int pcpn  :8;  /**< Previous CPU Priority Number */
#if (!defined(__TC13__)) && (!defined(__TC131__))
    unsigned int       :1;  /**< In TC 1.6 bit30 is Reserved */
    unsigned int       :1;  /**< In TC 1.6 bit31 is Reserved */
#endif /* !__TC13__ && !__TC131__ */
  } bits;                   /**< The register split in its bits */
} OsEE_pcxi;

/** Context Save Area Link Word (only PCXS and PCXO are valid) */
typedef OsEE_pcxi OsEE_csa_link;

/** Context Save Area (16 words, upper context). */
typedef struct {
  OsEE_reg  psw; /**< psw */
  OsEE_addr a10; /**< sp */
  OsEE_addr a11; /**< ra */
  OsEE_reg  d8;  /**< d8 */
  OsEE_reg  d9;  /**< d9 */
  OsEE_reg  d10; /**< d10 */
  OsEE_reg  d11; /**< d11 */
  OsEE_addr a12; /**< a12 */
  OsEE_addr a13; /**< a13 */
  OsEE_addr a14; /**< a14 */
  OsEE_addr a15; /**< a15 */
  OsEE_reg  d12; /**< d12 */
  OsEE_reg  d13; /**< d13 */
  OsEE_reg  d14; /**< d14 */
  OsEE_reg  d15; /**< d15 */
} OsEE_uctx;

/** Context Save Area (16 words, lower context). */
typedef struct {
  OsEE_addr a11; /**< ra */
  OsEE_addr a2;  /**< a2 */
  OsEE_addr a3;  /**< a3 */
  OsEE_reg  d0;  /**< d0 */
  OsEE_reg  d1;  /**< d1 */
  OsEE_reg  d2;  /**< d2 */
  OsEE_reg  d3;  /**< d3 */
  OsEE_addr a4;  /**< a4 */
  OsEE_addr a5;  /**< a5 */
  OsEE_addr a6;  /**< a6 */
  OsEE_addr a7;  /**< a7 */
  OsEE_reg  d4;  /**< d4 */
  OsEE_reg  d5;  /**< d5 */
  OsEE_reg  d6;  /**< d6 */
  OsEE_reg  d7;  /**< d7 */
} OsEE_lctx;

/** The CSA context is either a upper or a lowe context */
typedef union {
  OsEE_uctx uctx; /**< the CSA can be a upper context */
  OsEE_lctx lctx; /**< the CSA can be a lower context */
} OsEE_csa_ctx;

/** The CSA is a CSA context plus a link to the next CSA  in the list */
typedef struct {
  OsEE_csa_link l_next; /**< link to the next CSA in the list */
  OsEE_csa_ctx  ctx;    /**< CSA context */
} OsEE_csa;

/** Interrupt control register */
#if (!defined(__TC13__)) && (!defined(__TC131__))
typedef union {
  OsEE_reg reg;           /**< the whole register */
  struct {
    unsigned int ccpn :8; /**< Current CPU Priority Number */
    unsigned int      :7;
    unsigned int ie   :1; /**< Interrupt Enable */
    unsigned int pipn :8; /**< Pending Interrupt Priority Number */
    unsigned int      :8;
  } bits;                 /**< The register split in its bits */
} OsEE_icr;
#else
typedef union {
  OsEE_reg reg;               /**< the whole register */
  struct {
    unsigned int ccpn     :8; /**< Current CPU Priority Number */
    unsigned int ie       :1; /**< Interrupt Enable */
    unsigned int          :7;
    unsigned int pipn     :8; /**< Pending Interrupt Priority Number */
    unsigned int carbcyc  :2; /**< Number of Arbitration Cycles */
    unsigned int conecyc  :1; /**< No. of Clks per Arb. Cycle Control */
    unsigned int          :5;
  } bits;                     /**< The register split in its bits */
} OsEE_icr;
#endif /* !__TC13__ && !__TC131__ */

/** Syscon Register */
typedef union {
  OsEE_reg reg;               /**< the whole register */
  struct {
    unsigned int fcdsf    :1; /**< rwh Free Context List Depleted Sticky Flag */
    unsigned int proten   :1; /**< rw  Memory Protection Enable */
    unsigned int tpreten  :1; /***< rw  Temporal Protection Enable */
    unsigned int is       :1; /**< State of PSW.S bit in interrupt handler */
    unsigned int ts       :1; /**< State of PSW.S bit in trap handler */
    unsigned int          :3;
    unsigned int esdis    :1; /**< Emulator Space Disable (AURIX Gen2) */
    unsigned int          :7;
    unsigned int u1_ied   :1; /**< User-1 Instruction execution disable. (G2) */
    unsigned int u1_ios   :1; /**< User-1 Peripheral access as super. (G2) */
    unsigned int          :6;
    unsigned int bhalt    :1; /**< Boot halt status and release (AURIX Gen2) */
    unsigned int          :7;
  } bits;                     /**< The register split in its bits */
} OsEE_syscon;

/*=============================================================================
                          Context Data Structures
 ============================================================================*/
/** This is the context type for Tricore, which stores the pointer to
 *  the previous context (used for the TerminateTask()), the pointer
 *  to the PCXI context, and the return address. Please note that the
 *  stack pointer is implicitly saved in the Tricore context. The
 *  p_ctx context is also as well allocated on the stack and it is de
 *  facto a pointer to the stack.
 */
typedef struct OsEE_CTX_tag {
  struct OsEE_CTX_tag * p_ctx;  /**< Previous Context Pointer */
  OsEE_reg              dummy;  /**< Padding Word to guarantee 8 bytes align */
  OsEE_pcxi             pcxi;   /**< Previous CSA context */
  OsEE_addr             ra;     /**< Return Address (a11) */
} OsEE_CTX;

/** Stack Control Block: contains dynamic stack status */
typedef struct {
  OsEE_CTX      * p_tos; /**< Saved Context */
} OsEE_SCB;

/** Stack descriptor Block: contains the stack size end addresses */
typedef struct {
  OsEE_CTX   * p_bos;      /**< Bottom Of Stack */
#if (defined(OSEE_HAS_STACK_MONITORING))
  OsEE_CTX   * p_sos;      /**< Start Of Stack */
#endif /* OSEE_HAS_STACK_MONITORING */
  size_t       stack_size; /**< Stack Size */
} OSEE_CONST   OsEE_SDB;

/** HAL Descriptor Block: Contains the architecture dependent part of the 
 *  Task Description Block (TDB)
 */
typedef struct {
  OsEE_SDB          * p_sdb;     /**< Pointer to the Task SDB */
  OsEE_SCB          * p_scb;     /**< Pointer to the Task SCB */
  OsEE_isr_src_id     isr2_src;  /**< Interrupt source (in case it is an ISR2),
                                      or OSEE_TC_SRC_INVALID in case it is a 
                                      Task */
} OSEE_CONST OsEE_HDB;

#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
/** Core HAL Descriptor Block: stores the list of stacks to be used in case of
 *  Stack Monitoring or in case of ORTI support */
typedef struct {
  OsEE_SDB (* p_sdb_array)[];  /**< Array of SDB for this core */
  OsEE_SCB (* p_scb_array)[];  /**< Array of SCB for this core */
  size_t   stack_num;          /**< Number of stacks allocated for this core */
} OSEE_CONST OsEE_CHDB;
#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */

#if (defined(OSEE_TC_HAS_ISR1_TO_CONF))
/** This is a single ISR1 entry. Needed when we have to program the IRQ Table
 *  after the StartOS()
 */
typedef struct {
  OsEE_isr_src_id     isr1_src; /**< Interrupt Type 1 source */
  OsEE_prio           isr_prio; /**< Interrupt Priority */
} OSEE_CONST OsEE_isr1_src;

/** This is a single ISR1 entry. Needed when we have to program the IRQ Table
 *  after the StartOS()
 */
typedef struct OsEE_isr1_db_tag {
  OsEE_isr1_src (* p_isr1_src_array)[]; /**< Array of ISR1 sources */
  size_t        isr1_num;               /**< Number of ISR Type configured in 
                                             the OIL file */
} OSEE_CONST OsEE_isr1_db;
#endif /* OSEE_TC_HAS_ISR1_TO_CONF */

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_HAL_INTERNAL_TYPES_H */
