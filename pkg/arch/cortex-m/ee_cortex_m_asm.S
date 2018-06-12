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

/******************************************************************************
 *				MACROS
 ******************************************************************************/

/*
 * Macro Save Context: Internally used
 */
	.macro	osEE_hal_save_vcontext_m	p_from_scb

	/* Save working registers of preempted thread on stack */
#if	0
	PUSH	{R4-R7}		/* Store R4, R5, R6, R7 onto stack */
	MOV	R4, R8
	MOV	R5, R9
	MOV	R6, R10
	MOV	R7, R11
	PUSH	{R4-R7}		/* Store R8, R9, R10, R11 onto stack */
	PUSH	{LR}		/* Store link register (return address) */
#else
	PUSH	{R4-R11, LR}
#endif
	MRS	R4, PSR		/* Store xPSR to 8-bytes stack aligment */
	PUSH	{R4}

	/* R5 = p_from_scb->p_tos */
	MOV	R4, \p_from_scb
	LDR	R5, [R4]

	/* Save previous tos on stack */
#if	0
	PUSH	{R5}		/* dummy */
	PUSH	{R5}
#else
	PUSH	{R5, R6}	/* SP + dummy */
#endif

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
#if	0
	POP	{R5}	/* dummy */
	POP	{R5}
#else
	POP	{R5, R6}	/* SP + dummy */
#endif

	/* p_to_scb->p_tos = prev_p_tos */
	STR	R5, [R4]

	/* Now restore the context */
	POP	{R4}		/* Get xPSR from stack */
	LDR	R5, =EPSR_T_BIT	/* R5 = 0x01000000 */
	ORRS	R4, R4, R5	/* R4 = (xPSR OR 0x01000000).
				 * This guarantees that Thumbs bit is set to
				 * avoid an hard_fault exception */
	MSR	XPSR_NZCVQ, R4	/* Restore xPSR register */
#if	0
	POP	{R4}		/* Get link register from stack */
	MOV	LR, R4		/* Restore the link register */
	POP	{R4-R7}		/* Restore R8, R9, R10, R11 from stack */
	MOV	R8, R4
	MOV	R9, R5
	MOV	R10, R6
	MOV	R11, R7
	POP	{R4-R7}		/* Restore R4, R5, R6, R7 from stack */
#else
	POP	{R4-R11, LR}
#endif

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
#ifdef	OS_EE_ARCH_CORTEX_M_M4
	.arch armv7e-m
	.cpu cortex-m4
#endif	/* OS_EE_ARCH_CORTEX_M_M4 */

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
	LDR	R2, [R0]
	/* Unwind SP */
	MSR	MSP, R2
	/*  Jump to kern_callback (that schedule) */
	BX	R1
	/* This is a NORETURN Function */
	.size	osEE_hal_terminate_ctx, .-osEE_hal_terminate_ctx

/******************************************************************************
 *				END
 ******************************************************************************/
 
	.end
