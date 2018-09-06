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

/*
 * \file	ee_cortex_m_irq_asm.S
 * \brief	Functions ISR context switch for ARM Cortex-M.
 * \author	Giuseppe Serano
 * \date	2018
 */

#include "ee_cfg.h"

/******************************************************************************
 *			MACROS
 ******************************************************************************/

/* 
 * Interrupt control status register address.
 */
#define	NVIC_INT_CTRL	0xE000ED04

/*
 * System priority register 2 address (SVCall 11)
 */
#define	NVIC_SHPR2	0xE000ED1C

/*
 * System priority register 3 address (PendSV 14)
 */
#define	NVIC_SHPR3	0xE000ED20

/*
 * PendSV priority OR-value (Lowest)
 */
#define	NVIC_PENDSV_PRI	0x00FF0000

/*
 * SVCall priority AND-value (Highest)
 */
#define	NVIC_SVCALL_PRI	0x00FFFFFF

/*
 * Value to trigger PendSV exception
 */
#define	NVIC_PENDSVSET	0x10000000

/*
 * Value to acknowledge PendSV exception
 */
#define	NVIC_PENDSVCLR	0x08000000

/*
 * Value to set the T-bit in EPSR (always Thumb mode)
 */
#define	EPSR_T_BIT_VAL	0x01000000

/*
 * Exception return: No-FPU, Thread-Mode, MSP.
 */
#define	EXC_RETURN	0xFFFFFFF9

/******************************************************************************
 *			EXTERNAL SYMBOLS
 ******************************************************************************/

	/*
	 * FUNC(void, OS_CODE)
	 * osEE_cortex_m_change_context_from_task_end( void )
	 */
	.extern	osEE_cortex_m_change_context_from_task_end

/******************************************************************************
 *			CODE SECTION
 ******************************************************************************/
	.text

	/* kernel code is in ARM-mode */
	.syntax unified
#ifdef	OS_EE_ARCH_CORTEX_M_M4
	.arch armv7e-m
	.cpu cortex-m4
#endif	/* OS_EE_ARCH_CORTEX_M_M4 */

/*
 * FUNC(void, OS_CODE) osEE_set_switch_context_pri(void)
 */
	.align 2
	.global	osEE_set_switch_context_pri
	.type	osEE_set_switch_context_pri, #function
osEE_set_switch_context_pri:

	/* Set PendSV priority to the minumum one */
	LDR	R0, =NVIC_SHPR3
	LDR	R1, =NVIC_PENDSV_PRI
	LDR	R2, [R0]
	ORRS	R2, R2, R1
	STR	R2, [R0]

	/* SVCall priority to the maximum one */
	LDR	R0, =NVIC_SHPR2
	LDR	R1, =NVIC_SVCALL_PRI
	LDR	R2, [R0]
	ANDS	R2, R2, R1
	STR	R2, [R0]

	BX	LR

	.size	osEE_set_switch_context_pri, . - osEE_set_switch_context_pri

/*
 * FUNC(void, OS_CODE) osEE_cortex_m_trigger_pend_sv(void)
 */
	.align 2
	.global	osEE_cortex_m_trigger_pend_sv
	.type	osEE_cortex_m_trigger_pend_sv, %function
osEE_cortex_m_trigger_pend_sv:

	/* 
	 * Trigger the PendSV exception (causes context switch)
	 */
	LDR	R0, =NVIC_INT_CTRL
	LDR	R1, =NVIC_PENDSVSET
	STR	R1, [R0]

	BX	LR

	.size	osEE_cortex_m_trigger_pend_sv, . - osEE_cortex_m_trigger_pend_sv

/*
 * FUNC(void, OS_CODE) PendSV_Handler(void)
 */
	.align 2
	.global	PendSV_Handler
	.type	PendSV_Handler, %function
PendSV_Handler:

	/* Disable interrupts (set PRIMASK) */
#if	1	/* [GS]: To Be Checked. */
	CPSID	I
#endif

	/* Clear the PendSV exception (preventing 2nd triggering) */
	LDR	R2, =NVIC_INT_CTRL
	LDR	R1, =NVIC_PENDSVCLR
	STR	R1, [R2]

#if	defined(OS_EE_ARCH_CORTEX_M_M4F_FPU)
	/* Save Link Register. */
	PUSH	{R0, LR}
#endif	/* defined(OS_EE_ARCH_CORTEX_M_M4F_FPU) */

	/*
	 * Build a stack frame to jump into the
	 * EE_std_change_context(EE_TID) at the
	 * end of PendSV_Handler.
	 */

	/* R3 = 0x01000000 (xPSR) */
	LDR	R3, =EPSR_T_BIT_VAL

	/* R2 = osEE_cortex_m_change_context_from_task_end (PC) */
	LDR	R2, =osEE_cortex_m_change_context_from_task_end

	/* R1 = osEE_cortex_m_thread_end (LR) */
	LDR	R1, =osEE_cortex_m_thread_end

	/*
	 * |xPSR|-> xPSR AND 0xFFFFFE0
	 * | PC |-> osEE_cortex_m_change_context_from_task_end
	 * | LR |-> osEE_cortex_m_thread_end
	 * | R12|
	 */
	PUSH	{R0-R3}

	/*
	 * | R3 |
	 * | R2 |
	 * | R1 |
	 * | R0 |
	 */
	PUSH	{R0-R3}

	/*
	 * Fake IRQ handler frame on top of PendSV frame:
	 * |xPSR|-> xPSR AND 0xFFFFFE0
	 * | PC |-> osEE_cortex_m_change_context_from_task_end
	 * | LR |-> osEE_cortex_m_thread_end
	 * | R12|
	 * | R3 |
	 * | R2 |
	 * | R1 |
	 * | R0 | <- MSP
	 */

	/*
	 * R0 = EXC_RETURN -> Return to Thread mode.
	 *		   -> Exception return gets state from MSP.
	 *		   -> Execution uses MSP after return.
	 */
	LDR	LR, =EXC_RETURN

	BX	LR		/* EXC_RETURN. */

	.size	PendSV_Handler, . - PendSV_Handler

/*
 * FUNC(void, OS_CODE) osEE_cortex_m_thread_end(void)
 */
	.align 2
	.global	osEE_cortex_m_thread_end
	.type	osEE_cortex_m_thread_end, %function
osEE_cortex_m_thread_end:
/*
 * NOTE:	If SVC is executed when PRIMASK is set to 1,
 * 		HardFault Exception will occur.
 * 		To solve this, instead of using PRIMASK to mask interrupts,
 * 		use BASEPRI to mask particular interrupts.
 */

	/* Enable interrupts (clear PRIMASK) */
	CPSIE	I

	/* SVCall exception to remove Original PendSV stack-frame. */
	SVC	#0

	.size	osEE_cortex_m_thread_end, . - osEE_cortex_m_thread_end

/*
 * FUNC(void, OS_CODE) SVC_Handler(void)
 */
	.align 2
	.global	SVC_Handler
	.type	SVC_Handler, %function
SVC_Handler:

	/* Remove SVCall Stack-Frame. */
	ADD	SP, SP, #(8*4)

#if	defined(OS_EE_ARCH_CORTEX_M_M4F_FPU)
	/* Retrieves original Link Register. */
	POP	{R0, LR}
#endif	/* defined(OS_EE_ARCH_CORTEX_M_M4F_FPU) */

	BX	LR		/* EXC_RETURN. */

	.size	SVC_Handler, . - SVC_Handler

/******************************************************************************
 *			END
 ******************************************************************************/

	.end
