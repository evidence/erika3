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

/**
 * \file	ee_dspic33_pic24_asm.S
 * \brief	DSPIC33/PIC24 Context Switch.
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

	.equ	OS_EE_SPLIM_DELTA,	0x10

/******************************************************************************
 *				MACROS
 ******************************************************************************/

/*
 * Macro SPLIM restore: Internally used
 */
#ifndef	OSEE_API_DYNAMIC
#ifdef	OS_EE_ARCH_DSPIC33_PIC24_DSPIC33_SPLIM
	.macro	_osEE_splim_restore_m		p_to_tdb
	MOV	\p_to_tdb, W8
	MOV	[W8], W9
	MOV	[W9], W8
	SUB	#OS_EE_SPLIM_DELTA, W8
	MOV	W8, SPLIM
	.endm	/* _osEE_splim_restore_m */
#endif	/* OS_EE_ARCH_DSPIC33_PIC24_DSPIC33_SPLIM */
#endif	/* OSEE_API_DYNAMIC */

/*
 * Macro Save Context: Internally used
 */
#ifndef	OS_EE_BUILD_DEBUG
	.macro	_osEE_hal_save_vcontext_m	p_from_scb

	/* Save working registers of preempted thread on stack */
	PUSH.D	W8
	PUSH.D	W10
	PUSH.D	W12
	PUSH	W14

#ifdef	__HAS_DSP__
	PUSH	ACCAL
	PUSH	ACCAH
	PUSH	ACCAU
	PUSH	ACCBL
	PUSH	ACCBH
	PUSH	ACCBU
#endif	/* __HAS_DSP__ */

#ifdef	__HAS_EDS__
	PUSH	DSRPAG
	PUSH	DSWPAG
#else	/* __HAS_EDS__ */
	PUSH	PSVPAG
#endif	/* __HAS_EDS__ */

	PUSH	RCOUNT
	PUSH	DCOUNT
	PUSH	DOSTARTL
	PUSH	DOSTARTH
	PUSH	DOENDL
	PUSH	DOENDH

	PUSH	CORCON

	PUSH	TBLPAG

	/* W9 = p_from_scb->p_tos */
	MOV	\p_from_scb, W8
	MOV	[W8], W9

	/* Save previous tos on stack */
	PUSH	W9

	/* p_from_scb->p_tos = SP */
	MOV	W15, [W8]

	.endm	/* _osEE_hal_save_vcontext_m */

/*
 * Macro Restore Context: Internally used
 */
	.macro	_osEE_hal_restore_vcontext_m	p_to_scb

	/* W9 = p_to_scb->p_tos */
	MOV	\p_to_scb, W8
	MOV	[W8], W9

	/* Restore the SP */
	MOV	W9, W15

	/* Get previous p_tos from stack (prev_p_tos) */
	POP	W9

	/* p_to_scb->p_tos = prev_p_tos */
	MOV	W9, [W8]

	/* Now restore the context */
	POP	TBLPAG

	POP	CORCON

	POP	DOENDH
	POP	DOENDL
	POP	DOSTARTH
	POP	DOSTARTL
	POP	DCOUNT
	POP	RCOUNT

#ifdef	__HAS_EDS__
	POP	DSWPAG
	POP	DSRPAG
#else	/* __HAS_EDS__ */
	POP	PSVPAG
#endif	/* __HAS_EDS__ */

#ifdef	__HAS_DSP__
	POP	ACCBU
	POP	ACCBH
	POP	ACCBL
	POP	ACCAU
	POP	ACCAH
	POP	ACCAL
#endif	/* __HAS_DSP__ */

	POP	W14
	POP.D	W12
	POP.D	W10
	POP.D	W8

	.endm	/* _osEE_hal_restore_vcontext_m */
#endif	/* OS_EE_BUILD_DEBUG */

/******************************************************************************
 *				CODE SECTION
 ******************************************************************************/

	.text

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
	.global	_osEE_hal_save_ctx_and_restore_ctx
	.type	_osEE_hal_save_ctx_and_restore_ctx, @function
_osEE_hal_save_ctx_and_restore_ctx:
	/*
	 * W0 parameter:	OsEE_TDB * p_to_tdb
	 * W1 parameter:	OsEE_SCB * p_to_scb
	 * W2 parameter: 	OsEE_SCB * p_from_scb
	 */
#ifndef	OS_EE_BUILD_DEBUG
	_osEE_hal_save_vcontext_m	W2
#else	/* OS_EE_BUILD_DEBUG */
	/* Save working registers of preempted thread on stack */
	PUSH.D	W8
	PUSH.D	W10
	PUSH.D	W12
	PUSH	W14

#ifdef	__HAS_DSP__
	PUSH	ACCAL
	PUSH	ACCAH
	PUSH	ACCAU
	PUSH	ACCBL
	PUSH	ACCBH
	PUSH	ACCBU
#endif	/* __HAS_DSP__ */

#ifdef	__HAS_EDS__
	PUSH	DSRPAG
	PUSH	DSWPAG
#else	/* __HAS_EDS__ */
	PUSH	PSVPAG
#endif	/* __HAS_EDS__ */

	PUSH	RCOUNT
	PUSH	DCOUNT
	PUSH	DOSTARTL
	PUSH	DOSTARTH
	PUSH	DOENDL
	PUSH	DOENDH

	PUSH	CORCON

	PUSH	TBLPAG

	/* W9 = p_from_scb->p_tos */
	MOV	W2, W8
	MOV	[W8], W9

	/* Save previous tos on stack */
	PUSH	W9

	/* p_from_scb->p_tos = SP */
	MOV	W15, [W8]
#endif	/* OS_EE_BUILD_DEBUG */
	BRA	_osEE_hal_restore_ctx
	.size	_osEE_hal_save_ctx_and_restore_ctx, .-_osEE_hal_save_ctx_and_restore_ctx

/*
FUNC(void, OS_CODE)
	osEE_hal_restore_ctx
(
	P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)	p_to_tdb,
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_to_scb
)
*/
	.align 2
	.global	_osEE_hal_restore_ctx
	.type	_osEE_hal_restore_ctx, @function
_osEE_hal_restore_ctx:
	/*
	 * W0 parameter:	OsEE_TDB * p_to_tdb
	 * W1 parameter:	OsEE_SCB * p_to_scb
	 */

	/* SPLIM RESTORE */
#ifndef	OSEE_API_DYNAMIC
#ifdef	OS_EE_ARCH_DSPIC33_PIC24_DSPIC33_SPLIM
#ifndef	OS_EE_BUILD_DEBUG
	_osEE_splim_restore_m	W0
#else	/* OS_EE_BUILD_DEBUG */
	MOV	W0, W8
	MOV	[W8], W9
	MOV	[W9], W8
	SUB	#OS_EE_SPLIM_DELTA, W8
	MOV	W8, SPLIM
#endif	/* OS_EE_BUILD_DEBUG */
#endif	/* OS_EE_ARCH_DSPIC33_PIC24_DSPIC33_SPLIM */
#endif	/* OSEE_API_DYNAMIC */

#ifndef	OS_EE_BUILD_DEBUG
	_osEE_hal_restore_vcontext_m	W1
#else	/* OS_EE_BUILD_DEBUG */
	/* W9 = p_to_scb->p_tos */
	MOV	W1, W8
	MOV	[W8], W9

	/* Restore the SP */
	MOV	W9, W15

	/* Get previous p_tos from stack (prev_p_tos) */
	POP	W9

	/* p_to_scb->p_tos = prev_p_tos */
	MOV	W9, [W8]

	/* Now restore the context */
	POP	TBLPAG

	POP	CORCON

	POP	DOENDH
	POP	DOENDL
	POP	DOSTARTH
	POP	DOSTARTL
	POP	DCOUNT
	POP	RCOUNT

#ifdef	__HAS_EDS__
	POP	DSWPAG
	POP	DSRPAG
#else	/* __HAS_EDS__ */
	POP	PSVPAG
#endif	/* __HAS_EDS__ */

#ifdef	__HAS_DSP__
	POP	ACCBU
	POP	ACCBH
	POP	ACCBL
	POP	ACCAU
	POP	ACCAH
	POP	ACCAL
#endif	/* __HAS_DSP__ */

	POP	W14
	POP.D	W12
	POP.D	W10
	POP.D	W8
#endif	/* OS_EE_BUILD_DEBUG */
	BRA	_osEE_scheduler_task_wrapper_restore
	.size	_osEE_hal_restore_ctx, .-_osEE_hal_restore_ctx

/*
FUNC(void, OS_CODE)
	osEE_hal_ready2stacked
(
	P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)	p_to_tdb,
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_to_scb
)
*/
	.align 2
	.global	_osEE_hal_ready2stacked
	.type	_osEE_hal_ready2stacked, @function
_osEE_hal_ready2stacked:
	/*
	 * W0 parameter:	OsEE_TDB * p_to_tdb
	 * W1 parameter:	OsEE_SCB * p_to_scb
	 * W2 local:		p_to_scb->p_tos
	 */

	/* SPLIM RESTORE */
#ifndef	OSEE_API_DYNAMIC
#ifdef	OS_EE_ARCH_DSPIC33_PIC24_DSPIC33_SPLIM
#ifndef	OS_EE_BUILD_DEBUG
	_osEE_splim_restore_m	W0
#else	/* OS_EE_BUILD_DEBUG */
	MOV	W0, W8
	MOV	[W8], W9
	MOV	[W9], W8
	SUB	#OS_EE_SPLIM_DELTA, W8
	MOV	W8, SPLIM
#endif	/* OS_EE_BUILD_DEBUG */
#endif	/* OS_EE_ARCH_DSPIC33_PIC24_DSPIC33_SPLIM */
#endif	/* OSEE_API_DYNAMIC */

	MOV	[W1], W2
	/* sp = W2 */
	MOV	W2, W15
	BRA	_osEE_scheduler_task_wrapper_run
	.size	_osEE_hal_ready2stacked, .-_osEE_hal_ready2stacked

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
	.global	_osEE_hal_save_ctx_and_ready2stacked
	.type	_osEE_hal_save_ctx_and_ready2stacked, @function
_osEE_hal_save_ctx_and_ready2stacked:
	/*
	 * W0 parameter:	OsEE_TDB * p_to_tdb
	 * W1 parameter:	OsEE_SCB * p_to_scb
	 * W2 parameter:	OsEE_SCB * p_from_scb
	*/
#ifndef	OS_EE_BUILD_DEBUG
	_osEE_hal_save_vcontext_m	W2
#else	/* OS_EE_BUILD_DEBUG */
	PUSH.D	W8
	PUSH.D	W10
	PUSH.D	W12
	PUSH	W14

#ifdef	__HAS_DSP__
	PUSH	ACCAL
	PUSH	ACCAH
	PUSH	ACCAU
	PUSH	ACCBL
	PUSH	ACCBH
	PUSH	ACCBU
#endif	/* __HAS_DSP__ */

#ifdef	__HAS_EDS__
	PUSH	DSRPAG
	PUSH	DSWPAG
#else	/* __HAS_EDS__ */
	PUSH	PSVPAG
#endif	/* __HAS_EDS__ */

	PUSH	RCOUNT
	PUSH	DCOUNT
	PUSH	DOSTARTL
	PUSH	DOSTARTH
	PUSH	DOENDL
	PUSH	DOENDH

	PUSH	CORCON

	PUSH	TBLPAG

	/* W9 = p_from_scb->p_tos */
	MOV	W2, W8
	MOV	[W8], W9

	/* Save previous tos on stack */
	PUSH	W9

	/* p_from_scb->p_tos = MSP */
	MOV	W15, [W8]
#endif	/* OS_EE_BUILD_DEBUG */
	BRA	_osEE_hal_ready2stacked
	.size	_osEE_hal_save_ctx_and_ready2stacked, .-_osEE_hal_save_ctx_and_ready2stacked

/* 
FUNC(void, OS_CODE_NORETURN)
	osEE_hal_terminate_ctx
(
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_term_scb,
	VAR(OsEE_kernel_callback, AUTOMATIC)		kernel_cb
)
*/
	.align 2
	.global	_osEE_hal_terminate_ctx
	.type	_osEE_hal_terminate_ctx, @function
_osEE_hal_terminate_ctx:
	/*
	 * W0 parameter:	OsEE_SCB * p_term_scb
	 * W1 parameter:	kernel_cb
	 * W2 local:		p_term_scb->p_tos
	 */
	MOV	[W0], W2
	/* Unwind SP */
	MOV	W2, W15
	/*  Jump to kern_callback (that schedule) */
	GOTO	W1
	/* This is a NORETURN Function */
	.size	_osEE_hal_terminate_ctx, .-_osEE_hal_terminate_ctx

/******************************************************************************
 *				END
 ******************************************************************************/
 
	.end
