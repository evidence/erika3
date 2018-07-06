/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2018 Evidence s.r.l.
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

/** \file	ee_internal_types.h
 *  \brief	HAL Internal Types.
 *
 *  This files contains all HAL internal types and symbols for specific
 *  Architecture in Erika Enterprise.
 *
 *  \note	COULD BE raplaced by AUTOSAR Type definition paradigm or being
 *  		the implementation
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Errico Guidieri
 *  \author	Giuseppe Serano
 *  \date	2018
 */

#ifndef OSEE_HAL_INTERNAL_TYPES_H
#define	OSEE_HAL_INTERNAL_TYPES_H

#include "ee_platform_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/* R0-R3 and R12 are scratch registers, R13 ->(MSP), R14 ->(LR), R15 -> (PC) */
typedef struct OsEE_CTX_tag {
  struct OsEE_CTX_tag * p_ctx;
  OsEE_reg dummy;
#if (defined(OSEE_CORTEX_MX_FP))
  /* [GS]: T.B.D. */
#endif	/* OSEE_CORTEX_MX_FP */
  OsEE_reg psr;		/* PSR */
#if	0
  OsEE_reg r14;		/* LR */
  OsEE_reg r11;
  OsEE_reg r10;
  OsEE_reg r9;
  OsEE_reg r8;
  OsEE_reg r7;
  OsEE_reg r6;
  OsEE_reg r5;
  OsEE_reg r4;
#else
  OsEE_reg r4;
  OsEE_reg r5;
  OsEE_reg r6;
  OsEE_reg r7;
  OsEE_reg r8;
  OsEE_reg r9;
  OsEE_reg r10;
  OsEE_reg r11;
  OsEE_reg r14;		/* LR */
#endif
} OsEE_CTX;

struct OsEE_TDB_tag;

/** @brief	Switch-Context Control Block. */
typedef struct OsEE_SCCB_tag {
#if	0
  OsEE_TDB	* p_from;
  OsEE_TDB	* p_to
#else
  P2VAR(struct OsEE_TDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA)	p_from;
  P2VAR(struct OsEE_TDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA)	p_to;
#endif
} OsEE_SCCB;

/* Stack Control Block: contine le informazioni dinamiche relative allo stack */
typedef struct OsEE_SCB_tag {
  OsEE_CTX	* p_tos;	/* Saved Context */
} OsEE_SCB;

typedef struct OsEE_SDB_tag {
  OsEE_CTX	* p_bos;	/* Base Of Stack */
  MemSize	stack_size;
} OSEE_CONST OsEE_SDB;

typedef struct OsEE_HDB_tag {
  OsEE_SDB		* p_sdb;
  OsEE_SCB		* p_scb;
#if (defined(OSEE_API_DYNAMIC))
  OsEE_isr_src_id	isr2_src;
#endif /* OSEE_API_DYNAMIC */
} OSEE_CONST OsEE_HDB;

#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
typedef struct OsEE_CHDB_tag {
  OsEE_SDB (* p_sdb_array)[];
  OsEE_SCB (* p_scb_array)[];
  size_t   stack_num;
} OSEE_CONST OsEE_CHDB;
#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */

/*
 * Used to override default definition of osEE_change_context_from_isr2,
 * in ee_kernel_types.h, that is not inlined
 */
#define	OSEE_ISR2_INLINE	OSEE_STATIC_INLINE

#if	(defined(OSTICKDURATION))
extern FUNC(void, OS_CODE) osEE_cortex_m_system_timer_handler( void );
#endif	/* OSTICKDURATION */

#if	1	/* [GS]: New Context-Switch using PendSV. */
/*
 * Used to override default definition of osEE_scheduler_task_end,
 * in ee_std_change_context.c, that is not inlined
 */
#define	OSEE_KERNEL_TERMINATE_ACTIVATION_OVERRIDE

/* Override Terminate Activation Kernel Callback (CB). */
#define OSEE_KERNEL_TERMINATE_ACTIVATION_CB osEE_cortex_m_scheduler_task_end
#endif	/* 1 - [GS]: New Context-Switch using PendSV. */

#if (defined(__cplusplus))
}
#endif

#endif	/* !OSEE_HAL_INTERNAL_TYPES_H */
