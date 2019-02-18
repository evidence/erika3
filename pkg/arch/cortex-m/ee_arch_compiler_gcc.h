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

/** \file   ee_arch_compiler_gcc.h
 *  \brief  ARM GNU GCC Compilers Definitions.
 *
 *  This file contains all the common compiler-dependent architectural
 *  definitions for ARM GNU GCC Compiler.
 *
 *  \note This file \b MUST contain only \c defines, because it is also
 *        included by the \c .S files. \n
 *
 *  \note   TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \author Giuseppe Serano
 *  \date   2018
 */

/*
 * Compiler dependent interface
 */
#ifndef OSEE_ARCH_COMPILER_GCC_H
#define OSEE_ARCH_COMPILER_GCC_H

/*
 * Compiler dependent interface
 */
#include "ee_cfg.h"
/* compiler.h is the "mother" include file and does not need to be included here */
#include "ee_utils.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/** \brief Function to be executed at startup.
 *
 *  Function to be executed at startup.
 */
#define	OSEE_INIT			__attribute__((constructor))

/** \brief Returns from a function.
 *
 *  Returns from a function. This should be the last command executed before
 *  leaving a function defined with the EE_NAKED attribute.
 *
 *  This macro actually compiles into a single line of assembly, so there is
 *   no function call overhead.
 */
#define	OSEE_RETURN()			__asm__ volatile("ret" ::)

/** \brief Function is created with no prologue or epilogue.
 *
 *  The function is created with no prologue or epilogue code.
 *
 *  The user code is responsible for preservation of the machine state including
 *  the SREG register, as well as placing a EE_return() at the end of the
 *  function.
 *
 *   Use this attribute in the attributes parameter of the function.
 */
#define	OSEE_NAKED			__attribute__((naked))

/** \brief Stack Pointer Register retrieval.
 *
 *  Stack Pointer Register retrieval.
 */
#define	OSEE_GET_SP(SP)		\
	__asm__ volatile("mov %0, sp" : "=r" (SP))

/** \brief Clear Interrupts.
 *
 *  Clear Interrupts.
 */
#define OSEE_CLI()			__asm__ volatile("cpsid i" ::)

/** \brief Enable Interrupts.
 *
 *  Enable Interrupts.
 */
#define OSEE_SEI()			__asm__ volatile("cpsie i" ::)

/** \brief	Read the interrupt status register.
 *
 *  Interrupts Status Register retrieval.
 */
#define	OSEE_GET_ISR(SR)		\
	__asm__ volatile("mrs %0, primask" : "=r" (SR))

/** \brief	Set the interrupt status register
 *
 *  Interrupts Status Register set-up.
 */
#define	OSEE_SET_ISR(SR)		\
	__asm__ volatile("msr primask, %0" :: "r" (SR))

/** \brief  Read the Interrupt priority Level register.
 *
 *  Interrupts Priority Level retrieval.
 */
#define	OSEE_GET_IPL(SR)		\
	__asm__ volatile("mrs %0, basepri" : "=r" (SR))

/** \brief  Set the Interrupt priority level register.
 *
 *  Interrupts Priority Level set-up.
 */
#define	OSEE_SET_IPL(SR)		\
	__asm__ volatile("msr basepri, %0" :: "r" (SR))


/** \brief	CLZ instruction, if available.
 *
 *  CLZ Instruction. This returns the count leading zeroes of the input word.
 */
#define	OSEE_CLZ(MASK)		\
	__builtin_clz(MASK)

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_ARCH_COMPILER_GCC_H */
