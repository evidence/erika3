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

/** \file	ee_hal_internal_types.h
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
/** \brief Context block, storing register values */
typedef struct OsEE_CTX_tag {
  /** This is the pointer to the previous context. In the case of
   *  ERIKA3, every time a context is saved, and a new task is stacked
   *  on top of it, we need to remember the previous context, because
   *  in case of a TerminateTask() we need to unwind the stack and
   *  recover the previous context */
  struct OsEE_CTX_tag * p_ctx;
  OsEE_reg dummy0;                      /**< padding to 8 bytes */
#if (defined(OSEE_CORTEX_MX_FP))
  OsEE_reg control;                     /**< control register for floating point operations */
  OsEE_reg dummy1;                      /**< padding to 8 bytes */
#endif	/* OSEE_CORTEX_MX_FP */
  OsEE_reg psr;		                /**< PSR */
  OsEE_reg r4;		                /**< R4 */
  OsEE_reg r5;		                /**< R5 */
  OsEE_reg r6;		                /**< R6 */
  OsEE_reg r7;		                /**< R7 */
  OsEE_reg r8;		                /**< R8 */
  OsEE_reg r9;		                /**< R9 */
  OsEE_reg r10;		                /**< R10 */
  OsEE_reg r11;		                /**< R11 */
  OsEE_reg r14;		                /**< R14 (LR) */
} OsEE_CTX;

struct OsEE_TDB_tag;

/** Stack Control Block: contains runtime information about the stack */
typedef struct OsEE_SCB_tag {
  OsEE_CTX	* p_tos;	/**< Saved Context */
} OsEE_SCB;

/** Stack Descriptor Block. Contains static information about the stack */
typedef struct OsEE_SDB_tag {
  OsEE_CTX	* p_bos;	  /**< pointer to the base of the stack */
  MemSize	stack_size;   /**< stack size */
} OSEE_CONST OsEE_SDB;

/** HAL (Task) Descriptor block. Contains static information about the 
 *  configuration of a task in the HAL (in particular, information on the 
 *  task stacks and on ISR2 IDs in case of the dynamic API */
typedef struct OsEE_HDB_tag {
  OsEE_SDB		* p_sdb;        /**< pointer to the Stack Descriptor Block */
  OsEE_SCB		* p_scb;        /**< pointer to the Stack Control Block */
#if (defined(OSEE_API_DYNAMIC))
  /** This id stores the physical hardware source to which this ISR2
   *  is linked. It is useful during the setup phase, and afterwards
   *  with the functions EnableInterruptSource() and
   *  DisableInterruptSource() that act on the single source of
   *  interrupts */
  OsEE_isr_src_id	isr2_src;
#endif /* OSEE_API_DYNAMIC */
} OSEE_CONST OsEE_HDB;

#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
/** Core HAL Descriptor block. Contains information related to the core, in
  * particular it contains the stack pointers to the various stacks allocated 
  * on each core. */
typedef struct OsEE_CHDB_tag {
  OsEE_SDB (* p_sdb_array)[];  /**< Pointer to the array of Stack SDB (ram) */
  OsEE_SCB (* p_scb_array)[];  /**< Pointer to the array of Stack SCB /flash */
  size_t   stack_num;          /**< number of stack on this core */
} OSEE_CONST OsEE_CHDB;
#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */

#if	(defined(OSTICKDURATION))
extern FUNC(void, OS_CODE) osEE_cortex_m_system_timer_handler( void );
#endif	/* OSTICKDURATION */

#if (defined(__cplusplus))
}
#endif

#endif	/* !OSEE_HAL_INTERNAL_TYPES_H */
