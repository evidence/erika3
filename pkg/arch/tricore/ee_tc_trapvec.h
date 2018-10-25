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
 
 /**
    \file   ee_tc_trapvec.h
    \brief  TriCore trap handlers vector header.
    \author Errico Guidieri
    \date   2017
  */
#ifndef OSEE_TC_TRAPVEC_H
#define OSEE_TC_TRAPVEC_H

#include "ee_cfg.h"

/* Use this symbol to switch off ERIKA Trap Handling */
#if (!defined(OSEE_TC_TRAP_HANDLING_OFF))

#include "ee_platform_types.h"
#include "ee_compiler.h"
#include "ee_utils.h"

/** \brief Macros for Trap Classes */
#define OSEE_CLASS_TRAPMMU    (0U)
#define OSEE_CLASS_TRAPPROT   (1U)
#define OSEE_CLASS_TRAPINST   (2U)
#define OSEE_CLASS_TRAPCONT   (3U)
#define OSEE_CLASS_TRAPBUS    (4U)
#define OSEE_CLASS_TRAPASS    (5U)
#define OSEE_CLASS_TRAPSYS    (6U)
#define OSEE_CLASS_TRAPNMI    (7U)

/** \brief  Macros for MMU Class Trap Numbers:
 *  TIN Name Sync/Async  H/S      Description
 *  0   VAF  Synchronous Hardware Virtual Address Fill
 *  1   VAP  Synchronous Hardware Virtual Address Protection
 */
#define OSEE_TRAPMMU_VAF      (0U)
#define OSEE_TRAPMMU_VAP      (1U)

/** \brief  Macros for Protection Class Trap Numbers:
 *  TIN Name Sync/Async  H/S      Description
 *  1   PRIV Synchronous Hardware Privileged Instruction
 *  2   MPR  Synchronous Hardware Memory Protection: Read Access
 *  3   MPW  Synchronous Hardware Memory Protection: Write Access
 *  4   MPX  Synchronous Hardware Memory Protection: Execution Access
 *  5   MPP  Synchronous Hardware Memory Protection: Peripheral Access
 *  6   MPN  Synchronous Hardware Memory Protection: Null Address
 *  7   GRWP Synchronous Hardware Global Register Write Protection
 */
#define OSEE_TRAPPROT_PRIV    (1U)
#define OSEE_TRAPPROT_MPR     (2U)
#define OSEE_TRAPPROT_MPW     (3U)
#define OSEE_TRAPPROT_MPX     (4U)
#define OSEE_TRAPPROT_MPP     (5U)
#define OSEE_TRAPPROT_MPN     (6U)
#define OSEE_TRAPPROT_GRWP    (7U)

/** \brief  Macros for Instructions Class Trap Numbers:
 *  TIN Name Sync/Async  H/S      Description
 *  1   IOPC Synchronous Hardware Illegal Opcode
 *  2   UOPC Synchronous Hardware Unimplemented Opcode
 *  3   OPD  Synchronous Hardware Invalid operand specification
 *  4   ALN  Synchronous Hardware Data address alignment error
 *  5   MEM  Synchronous Hardware Invalid local memory address
 */
#define OSEE_TRAPINST_IOPC    (1U)
#define OSEE_TRAPINST_UOPC    (2U)
#define OSEE_TRAPINST_OPD     (3U)
#define OSEE_TRAPINST_ALN     (4U)
#define OSEE_TRAPINST_MEM     (5U)

/** \brief  Macros for Context Class Trap Numbers:
 *  TIN Name Sync/Async  H/S      Description
 *  1   FCD  Synchronous Hardware Free context list depleted
 *  2   CDO  Synchronous Hardware Call depth overflow
 *  3   CDU  Synchronous Hardware Call depth underflow
 *  4   FCU  Synchronous Hardware Free context list underflow
 *  5   CSU  Synchronous Hardware Call stack underflow
 *  6   CTYP Synchronous Hardware Context type error
 *  7   NEST Synchronous Hardware Nesting error
 */
#define EE_TRAPCONT_FCD       (1U)
#define EE_TRAPCONT_CDO       (2U)
#define EE_TRAPCONT_CDU       (3U)
#define EE_TRAPCONT_FCU       (4U)
#define EE_TRAPCONT_CSU       (5U)
#define EE_TRAPCONT_CTYP      (6U)
#define EE_TRAPCONT_NEST      (7U)

/** \brief  Macros for System Bus and Peripheral Errors Class Trap Numbers:
 *  TIN Name Sync/Async   H/S      Description
 *  1   PSE  Synchronous  Hardware Program fetch bus error
 *  2   DSE  Synchronous  Hardware Data access bus error
 *  3   DAE  Asynchronous Hardware Data access bus error
 *  4   CAE  Asynchronous Hardware Coprocessor Trap Asynchronous (TriCore 1.6)
 *  5   PIE  Synchronous  Hardware Program Memory Integrity Error.
 *  6   DIE  Asynchronous Hardware Data Memory Integrity Error (TriCore 1.6)
 *  7   TAE  Asynchronous Hardware Temporal Asynchronous Error
 */
#define OSEE_TRAPBUS_PSE      (1U)
#define OSEE_TRAPBUS_DSE      (2U)
#define OSEE_TRAPBUS_DAE      (3U)
#define OSEE_TRAPBUS_CAE      (4U)
#define OSEE_TRAPBUS_PIE      (5U)
#define OSEE_TRAPBUS_DIE      (6U)
#define OSEE_TRAPBUS_TAE      (7U)

/** \brief  Macros for Assertions Class Trap Numbers:
 *  TIN Name Sync/Async  H/S      Description
 *  1   OVF  Synchronous Software Arithmetic overflow
 *  2   SOVF Synchronous Software Sticky arithmetic overflow
 */
#define OSEE_TRAPASS_OVF      (1U)
#define OSEE_TRAPASS_SOVF     (2U)

/** \brief N° Macros for System Call Trap Numbers 
 *  TIN Name Sync/Async  H/S      Description
 *  n   SYS  Synchronous Software System call
 * (n=8-bit unsigned immediate constant int the SYSCALL instruction) *
 */

/** \brief  Macros for Non-Maskable Interrupt Class Trap Numbers:
 *  TIN Name Sync/Async   H/S      Description
 *  0   NMI  Asynchronous Hardware Non-maskable interrupt
 */
#define OSEE_TRAPNMI_NMI      (0U)

/* Trap handler declaration */
#if (defined(__GNUC__))
#define TRAP(class,f) \
  void  __attribute__((interrupt_handler, used)) f (EE_TIN tin)
#else
#error Unsupported compiler!
#endif

#if (defined(OSEE_MEMORY_PROTECTION)) && (defined(OSEE_TC_TRAP_SYS_TRAP))
/* In memory protected environment system call TRAP is handled by Kernel code */
#error In memory protected environment system call MUST be handled by the\
 Kernel
#endif /* OSEE_MEMORY_PROTECTION && OSEE_TC_TRAP_SYS_TRAP */

/* Trap Identification Number */
typedef uint8_t OsEE_tc_tin;

/* Type pointing to an Trap Handler */
typedef void (* OsEE_tc_trap_handler)(OsEE_tc_tin par);

#if (defined(__GNUC__))
OSEE_STATIC_INLINE OsEE_tc_tin osEE_tc_get_tin(void)
{
  OsEE_tc_tin tin;
  /* Register d15 holds the Trap Id Nr inside a Trap handler */
  __asm__ volatile("mov  %0,%%d15": "=d"(tin) : : "memory");
  return tin;
}

#endif /* __GNUC__ */

#endif /* OSEE_TC_TRAP_HANDLING_OFF */
#endif /* OSEE_TC_TRAPVEC_H */
