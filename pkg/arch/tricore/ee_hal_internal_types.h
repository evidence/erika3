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

/** \file   ee_internal_types.h
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

/*******************************************************************************
 *  IMPORTANT:
 *  These struct layouts are packet by construction so I don't add 
 *  __attribute__((packed)) because it could harm performances.
 *  Look at:
 *  digitalvampire.org/blog/index.php/2006/07/31/\
 *  why-you-shouldnt-use-__attribute__packed
 ******************************************************************************/

/* Previous Context Information Register */
typedef union OsEE_pcxi_tag {
  OsEE_reg reg;
  struct {
    unsigned int pcxo  :16; /* Previous Context Pointer Offset Address  */
    unsigned int pcxs  :4;  /* Previous Context Pointer Segment Address */
#if (defined(__TC13__)) || (defined(__TC131__))
    unsigned int       :1;  /* In TC 1.3 bit20 is Reserved */
    unsigned int       :1;  /* In TC 1.3 bit21 is Reserved */
#endif /* __TC13__ || __TC131__ */
    unsigned int ul    :1;  /* Upper or Lower Context Tag */
    unsigned int pie   :1;  /* Previous Interrupt Enable */
    unsigned int pcpn  :8;  /* Previous CPU Priority Number */
#if (!defined(__TC13__)) && (!defined(__TC131__))
    unsigned int       :1;  /* In TC 1.6 bit30 is Reserved */
    unsigned int       :1;  /* In TC 1.6 bit31 is Reserved */
#endif /* !__TC13__ && !__TC131__ */
  } bits;
} OsEE_pcxi;

/* Context Save Area Link Word (only PCXS and PCXO are valid) */
typedef OsEE_pcxi OsEE_csa_link;

/* Context Save Area (16 words, upper or lower context). */
typedef struct OsEE_uctx_tag {
  OsEE_reg  psw;
  OsEE_addr a10; /* sp */
  OsEE_addr a11; /* ra */
  OsEE_reg  d8;
  OsEE_reg  d9;
  OsEE_reg  d10;
  OsEE_reg  d11;
  OsEE_addr a12;
  OsEE_addr a13;
  OsEE_addr a14;
  OsEE_addr a15;
  OsEE_reg  d12;
  OsEE_reg  d13;
  OsEE_reg  d14;
  OsEE_reg  d15;
} OsEE_uctx;

typedef struct OsEE_lctx_tag {
  OsEE_addr a11; /* ra */
  OsEE_addr a2;
  OsEE_addr a3;
  OsEE_reg  d0;
  OsEE_reg  d1;
  OsEE_reg  d2;
  OsEE_reg  d3;
  OsEE_addr a4;
  OsEE_addr a5;
  OsEE_addr a6;
  OsEE_addr a7;
  OsEE_reg  d4;
  OsEE_reg  d5;
  OsEE_reg  d6;
  OsEE_reg  d7;
} OsEE_lctx;

typedef union OsEE_csa_ctx_tag {
  OsEE_uctx uctx;
  OsEE_lctx lctx;
} OsEE_csa_ctx;

typedef struct OsEE_csa_tag {
  OsEE_csa_link l_next;
  OsEE_csa_ctx  ctx;
} OsEE_csa;

/* Interrupt control register */
#if (!defined(__TC13__)) && (!defined(__TC131__))
typedef union OsEE_icr_tag {
  OsEE_reg reg;
  struct {
    unsigned int ccpn :8; /* Current CPU Priority Number */
    unsigned int      :7;
    unsigned int ie   :1; /* Interrupt Enable */
    unsigned int pipn :8; /* Pending Interrupt Priority Number */
    unsigned int      :8;
  } bits;
} OsEE_icr;
#else
typedef union OsEE_icr_tag {
  OsEE_reg reg;
  struct {
    unsigned int ccpn     :8; /* Current CPU Priority Number */
    unsigned int ie       :1; /* Interrupt Enable */
    unsigned int          :7;
    unsigned int pipn     :8; /* Pending Interrupt Priority Number */
    unsigned int carbcyc  :2; /* Number of Arbitration Cycles */
    unsigned int conecyc  :1; /* No. of Clks per Arb. Cycle Control */
    unsigned int          :5;
  } bits;
} OsEE_icr;
#endif /* !__TC13__ && !__TC131__ */

typedef struct OsEE_CTX_tag {
  struct OsEE_CTX_tag * p_ctx;  /* Previous ERIKA's Context Pointer */
  OsEE_reg              dummy;  /* Padding Word */
  OsEE_pcxi             pcxi;   /* Previous CSA context */
  OsEE_addr             ra;     /* Return Address (a11) */
} OsEE_CTX;

/* Stack Control Block: contine le informazioni dinamiche relative allo stack */
typedef struct OsEE_SCB_tag {
  OsEE_CTX      * p_tos; /* Saved Context */
} OsEE_SCB;

typedef struct OsEE_SDB_tag {
  OsEE_CTX   * p_bos; /* Bottom Of Stack */
#if (defined(OSEE_HAS_STACK_MONITORING))
  OsEE_CTX   * p_sos; /* Start Of Stack */
#endif /* OSEE_HAS_STACK_MONITORING */
  size_t       stack_size;
} OSEE_CONST   OsEE_SDB;

typedef struct OsEE_HDB_tag {
  OsEE_SDB          * p_sdb;
  OsEE_SCB          * p_scb;
  OsEE_isr_src_id     isr2_src;
} OSEE_CONST OsEE_HDB;

#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
typedef struct OsEE_CHDB_tag {
  OsEE_SDB (* p_sdb_array)[];
  OsEE_SCB (* p_scb_array)[];
  size_t   stack_num;
} OSEE_CONST OsEE_CHDB;
#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */

#if (defined(OSEE_TC_HAS_ISR1_TO_CONF))
  typedef struct OsEE_isr1_src_tag {
    OsEE_isr_src_id     isr1_src;
    OsEE_prio           isr_prio;
  } OSEE_CONST OsEE_isr1_src;

  typedef struct OsEE_isr1_db_tag {
    OsEE_isr1_src (* p_isr1_src_array)[];
    size_t        isr1_num;
  } OSEE_CONST OsEE_isr1_db;
#endif /* OSEE_TC_HAS_ISR1_TO_CONF */

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_HAL_INTERNAL_TYPES_H */
