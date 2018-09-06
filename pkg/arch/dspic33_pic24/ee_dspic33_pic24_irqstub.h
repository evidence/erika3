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

/** \file	ee_dspic33_pic24_irqstub.h
 *  \brief	Microchip DSPIC33_PIC24 IRQs Internals.
 *
 *  This files contains the internals of the IRQs support for Microchip
 *  DSPIC33/PIC24 Architecture available in Erika Enterprise.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

#ifndef OSEE_DSPIC33_PIC24_IRQSTUB_H
#define	OSEE_DSPIC33_PIC24_IRQSTUB_H

#include "ee_dspic33_pic24_irq.h"

/* needed for the osEE_hal_disableIRQ */
#if (defined(OS_EE_ARCH_DSPIC33_PIC24_DSPIC33EV))
#include "ee_dspic33ev_internal.h"
#endif	/* OS_EE_ARCH_DSPIC33_PIC24_DSPIC33EV */


#if (defined(__cplusplus))
extern "C" {
#endif

#if	(!defined(OSEE_API_DYNAMIC))
/*
 * ISR Type 1 stub.
 */
FUNC(void, OS_CODE) OSEE_COMPILER_KEEP
osEE_dspic33_pic24_isr1_stub(
  VAR(OsEE_void_cb, AUTOMATIC) f
);

/*
 * ISR Type 2 stub.
 */
FUNC(void, OS_CODE) OSEE_COMPILER_KEEP
osEE_dspic33_pic24_isr2_stub(
  VAR(TaskType, AUTOMATIC) t
);
#else /* !OSEE_API_DYNAMIC */

/*
 * ISR Type 2 stub.
 */
FUNC(void, OS_CODE) OSEE_COMPILER_KEEP
osEE_dspic33_pic24_isr2_stub(
  VAR(OsEE_isr_src_id, AUTOMATIC) t
);

#endif	/* !OSEE_API_DYNAMIC */

#if	0	/* [GS]: MISRA */
/*
 * ISR pre-stub.
 */
#define	OSEE_DSPIC33_PIC24_ISR_PRESTUB()	\
osEE_hal_disableIRQ();				\
do {						\
	__asm__ volatile("PUSH.D W0");		\
	__asm__ volatile("PUSH.D W2");		\
	__asm__ volatile("MOV _SRbits, w0");	\
	__asm__ volatile("PUSH W0");		\
} while(OSEE_FALSE)
#else	/* 0 - [GS]: MISRA */
/*
 * Save IRQ Context
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_saveIrqCtx( void )
{
	__asm__ volatile("PUSH.D W0");
	__asm__ volatile("PUSH.D W2");
	__asm__ volatile("MOV _SRbits, w0");
	__asm__ volatile("PUSH W0");
}

/*
 * ISR pre-stub.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
OSEE_DSPIC33_PIC24_ISR_PRESTUB( void )
{
	osEE_hal_disableIRQ();
	osEE_hal_saveIrqCtx();
}

#endif	/* 0 - [GS]: MISRA */

#if	0	/* [GS]: MISRA */
/*
 * ISR post-stub.
 */
#define	OSEE_DSPIC33_PIC24_ISR_POSTSTUB()	\
do {						\
	__asm__ volatile("POP W0");		\
	__asm__ volatile("MOV W0, _SRbits");	\
	__asm__ volatile("POP.D W2");		\
	__asm__ volatile("POP.D W0");		\
} while(OSEE_FALSE)
#else	/* 0 - [GS]: MISRA */
/*
 * Restore IRQ Context
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_restoreIrqCtx( void )
{
	__asm__ volatile("POP W0");
	__asm__ volatile("MOV W0, _SRbits");
	__asm__ volatile("POP.D W2");
	__asm__ volatile("POP.D W0");
}

/*
 * ISR post-stub.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
OSEE_DSPIC33_PIC24_ISR_POSTSTUB( void )
{
  osEE_hal_restoreIrqCtx();
}

#endif	/* 0 - [GS]: MISRA */

/* Un-Defined ISR */
#define OSEE_DSPIC33_PIC24_ISR_NOT_DEFINED(v)		\
/* Define a NAKED ISR handler */			\
FUNC(void, OS_CODE) OSEE_ISR_NO_AUTO_PSV (v)(void)	\
{							\
	/* Disables IRQ  */				\
	osEE_hal_disableIRQ();				\
	/* Hangs in a infinite loop!!! */		\
	for(;;) {}					\
}

#if (defined(__cplusplus))
}
#endif

#endif	/* !OSEE_DSPIC33_PIC24_IRQSTUB_H */
