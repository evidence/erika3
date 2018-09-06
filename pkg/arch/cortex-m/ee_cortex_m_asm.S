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
 * \file	ee_cortex_m_asm.S
 * \brief	Cortex-M Context Switch.
 *
 * This file contains the functions to save and restore registers for
 * context switch & OSEK TerminateTask().
 *
 * \author	Errico Guidieri
 * \author	Giuseppe Serano
 * \date	2018
 */

#include "ee_oscfg.h"

/******************************************************************************
 *				EQUATES
 ******************************************************************************/
/*
 * Value to set the T-bit in EPSR (always Thumb mode)
 */
#define	EPSR_T_BIT	0x01000000

#if	0	/* [GS]: T.B.C. */
/*
 * CPACR is located at address 0xE000ED88
 */
#define	CPACR		0xE000ED88
#endif	/* 0 - [GS]: T.B.C. */

/*
 * FPCA bits
 */
#define	CONTROL_FPCA_NEG	0xFFFFFFFB

/******************************************************************************
 *				MACROS
 ******************************************************************************/

/*
 * Macro Save Context: Internally used
 */
	.macro	osEE_hal_save_vcontext_m	p_from_scb

	/* Save working registers of preempted thread on stack */
	PUSH	{R4-R11, LR}
	MRS	R4, PSR		/* Store xPSR to 8-bytes stack aligment */
	PUSH	{R4}
#if	defined(OS_EE_ARCH_CORTEX_M_M4F_FPU)
	MRS	R4, CONTROL
	PUSH	{R4-R5}
#endif	/* defined(OS_EE_ARCH_CORTEX_M_M4F_FPU) */

	/* R5 = p_from_scb->p_tos */
	MOV	R4, \p_from_scb
	LDR	R5, [R4]

	/* Save previous tos on stack */
	PUSH	{R5, R6}	/* SP + dummy */

	/* p_from_scb->p_tos = MSP */
	MRS	R5, MSP
	STR	R5, [R4]

	.endm	/* osEE_hal_save_vcontext_m */

/*
 * Macro Restore Context: Internally used
 */
	.macro	osEE_hal_restore_vcontext_m	p_to_scb

	/* R5 = p_to_scb->p_tos */
	MOV	R4, \p_to_scb
	LDR	R5, [R4]

	/* Restore the SP */
	MSR	MSP, R5

	/* Get previous p_tos from stack (prev_p_tos) */
	POP	{R5, R6}	/* SP + dummy */

	/* p_to_scb->p_tos = prev_p_tos */
	STR	R5, [R4]

	/* Now restore the context */
#if	defined(OS_EE_ARCH_CORTEX_M_M4F_FPU)
	POP	{R4-R5}
	MSR	CONTROL, R4
#endif	/* defined(OS_EE_ARCH_CORTEX_M_M4F_FPU) */
	POP	{R4}		/* Get xPSR from stack */
	LDR	R5, =EPSR_T_BIT	/* R5 = 0x01000000 */
	ORRS	R4, R4, R5	/* R4 = (xPSR OR 0x01000000).
				 * This guarantees that Thumbs bit is set to
				 * avoid an hard_fault exception */
	MSR	XPSR_NZCVQ, R4	/* Restore xPSR register */
	POP	{R4-R11, LR}

	.endm	/* osEE_hal_restore_vcontext_m */

/******************************************************************************
 *				STACK SIZE
 ******************************************************************************/

#ifdef	OSEE_SYS_STACK_SIZE_ASM
	.global	__stack_size__
	.set	__stack_size__, OSEE_SYS_STACK_SIZE_ASM
#endif	/* OSEE_SYS_STACK_SIZE_ASM */

/******************************************************************************
 *				CODE SECTION
 ******************************************************************************/

	.text

	/* kernel code is in ARM-mode */
	.syntax unified

	/* Architecture */
	.arch armv7e-m

#if	(						\
	defined(OS_EE_ARCH_CORTEX_M_M4)		||	\
	defined(OS_EE_ARCH_CORTEX_M_M4F)	||	\
	defined(OS_EE_ARCH_CORTEX_M_M4F_FPU)		\
)
	/* CPU */
	.cpu cortex-m4
#endif	/*
	 * OS_EE_ARCH_CORTEX_M_M4	||
	 * OS_EE_ARCH_CORTEX_M_M4F	||
	 * OS_EE_ARCH_CORTEX_M_M4F_FPU
	 */

#if	0	/* [GS]: T.B.C. */
#ifdef	OS_EE_ARCH_CORTEX_M_M4F_FPU
/*
FUNC(void, OS_CODE) osEE_hal_cortex_m4f_enable_fpu(void)
*/
	.align 2
	.global	osEE_hal_cortex_m4f_enable_fpu
	.type	osEE_hal_cortex_m4f_enable_fpu, %function
osEE_hal_cortex_m4f_enable_fpu:
	/* Set CPACR Address */
	LDR.W	R0, =CPACR
	/* Read CPACR */
	LDR	R1, [R0]
	/* Set bits 20-23 to enable CP10 and CP11 coprocessors */
	ORR	R1, R1, (#0xF << 20)
	/* Write back the modified value to the CPACR */
	STR	R1, [R0]
	/* [GS]: Disble other features. */
	/* Return */
	BX	LR
	.size	osEE_hal_cortex_m4f_enable_fpu, .-osEE_hal_cortex_m4f_enable_fpu
#endif	/* OS_EE_ARCH_CORTEX_M_M4F_FPU */
#endif	/* 0 - [GS]: T.B.C. */

/*
FUNC(void, OS_CODE)
	osEE_hal_save_ctx_and_restore_ctx
(
	P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)	p_to_tdb,
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_to_scb,
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_from_scb
)
*/
	.align 2
	.global	osEE_hal_save_ctx_and_restore_ctx
	.type	osEE_hal_save_ctx_and_restore_ctx, %function
osEE_hal_save_ctx_and_restore_ctx:
	/*
	 * R0 parameter:	OsEE_TDB * p_to_tdb
	 * R1 parameter:	OsEE_SCB * p_to_scb
	 * R2 parameter: 	OsEE_SCB * p_from_scb
	 */
	osEE_hal_save_vcontext_m R2
	B	osEE_hal_restore_ctx
	.size	osEE_hal_save_ctx_and_restore_ctx, .-osEE_hal_save_ctx_and_restore_ctx

/*
FUNC(void, OS_CODE)
	osEE_hal_restore_ctx
(
	P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)	p_to_tdb,
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_to_scb
)
*/
	.align 2
	.global	osEE_hal_restore_ctx
	.type	osEE_hal_restore_ctx, %function
osEE_hal_restore_ctx:
	/*
	 * R0 parameter:	OsEE_TDB * p_to_tdb
	 * R1 parameter:	OsEE_SCB * p_to_scb
	 */
	osEE_hal_restore_vcontext_m R1
	B	osEE_scheduler_task_wrapper_restore
	.size	osEE_hal_restore_ctx, .-osEE_hal_restore_ctx

/*
FUNC(void, OS_CODE)
	osEE_hal_ready2stacked
(
	P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)	p_to_tdb,
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_to_scb
)
*/
	.align 2
	.global	osEE_hal_ready2stacked
	.type	osEE_hal_ready2stacked, %function
osEE_hal_ready2stacked:
	/*
	 * R0 parameter:	OsEE_TDB * p_to_tdb
	 * R1 parameter:	OsEE_SCB * p_to_scb
	 * R2 local:		p_to_scb->p_tos
	 */
#if	defined(OS_EE_ARCH_CORTEX_M_M4F_FPU)
	MRS	R4, CONTROL
	LDR	R5, =CONTROL_FPCA_NEG
	ANDS	R4, R4, R5
	MSR	CONTROL, R4
#endif	/* defined(OS_EE_ARCH_CORTEX_M_M4F_FPU) */
	LDR	R2, [R1]
	/* sp = R2 */
	MSR	MSP, R2
	B	osEE_scheduler_task_wrapper_run
	.size	osEE_hal_ready2stacked, .-osEE_hal_ready2stacked

/*
FUNC(void, OS_CODE)
	osEE_hal_save_ctx_and_ready2stacked
(
	P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)	p_to_tdb,
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_to_scb,
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_from_scb
)
*/
	.align 2
	.global	osEE_hal_save_ctx_and_ready2stacked
	.type	osEE_hal_save_ctx_and_ready2stacked, %function
osEE_hal_save_ctx_and_ready2stacked:
	/*
	 * R0 parameter:	OsEE_TDB * p_to_tdb
	 * R1 parameter:	OsEE_SCB * p_to_scb
	 * R2 parameter:	OsEE_SCB * p_from_scb
	*/
	osEE_hal_save_vcontext_m R2
	B	osEE_hal_ready2stacked
	.size	osEE_hal_save_ctx_and_ready2stacked, .-osEE_hal_save_ctx_and_ready2stacked

/* 
FUNC(void, OS_CODE_NORETURN)
	osEE_hal_terminate_ctx
(
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_term_scb,
	VAR(OsEE_kernel_callback, AUTOMATIC)		kernel_cb
)
*/
	.align 2
	.global	osEE_hal_terminate_ctx
	.type	osEE_hal_terminate_ctx, %function
osEE_hal_terminate_ctx:
	/*
	 * R0 parameter:	OsEE_SCB * p_term_scb
	 * R1 parameter:	kernel_cb
	 * R2 local:		p_term_scb->p_tos
	 */
#if	defined(OS_EE_ARCH_CORTEX_M_M4F_FPU)
	MRS	R4, CONTROL
	LDR	R5, =CONTROL_FPCA_NEG
	ANDS	R4, R4, R5
	MSR	CONTROL, R4
#endif	/* defined(OS_EE_ARCH_CORTEX_M_M4F_FPU) */
	LDR	R2, [R0]
	/* Unwind SP */
	MSR	MSP, R2
	/*  Jump to kern_callback (that schedule) */
	BX	R1
	/* This is a NORETURN Function */
	.size	osEE_hal_terminate_ctx, .-osEE_hal_terminate_ctx

/*
FUNC(void, OS_CODE)
	osEE_cortex_m_restore_ctx
(
	P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)	p_to_tdb,
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_to_scb
)
*/
	.align 2
	.global	osEE_cortex_m_restore_ctx
	.type	osEE_cortex_m_restore_ctx, %function
osEE_cortex_m_restore_ctx:
	/*
	 * R0 parameter:	OsEE_TDB * p_to_tdb
	 * R1 parameter:	OsEE_SCB * p_to_scb
	 */
	osEE_hal_restore_vcontext_m R1
	BX	LR
	.size	osEE_cortex_m_restore_ctx, .-osEE_cortex_m_restore_ctx

/******************************************************************************
 *				END
 ******************************************************************************/
 
	.end
