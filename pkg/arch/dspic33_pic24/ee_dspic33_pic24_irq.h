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

/** \file	ee_dspic33_pic24_irq.h
 *  \brief	Microchip DSPIC33/PIC24 IRQs.
 *
 *  This files contains the interfaces of the IRQs support for Microchip dsPIC33
 *  Architecture available in Erika Enterprise.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */
#ifndef OSEE_DSPIC33_PIC24_IRQ_H
#define	OSEE_DSPIC33_PIC24_IRQ_H

/* I need base API */
#include "ee_compiler.h"

#include "ee_mcu_irq.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/** \brief	ISR priority level defines
 *
 *  The value of thess macros can be used in assembly inline templates,
 *  so no parentheses nor unsigned specifiers is allowed
 */
#define	OSEE_ISR_UNMASKED	0U
#define	OSEE_ISR_PRI_1		1U
#define	OSEE_ISR_PRI_2		2U
#define	OSEE_ISR_PRI_3		3U
#define	OSEE_ISR_PRI_4		4U
#define	OSEE_ISR_PRI_5		5U
#define	OSEE_ISR_PRI_6		6U
#define	OSEE_ISR_PRI_7		7U

/* Macro to declare ISR1: always valid */
#define	DeclareIsr1(f)	FUNC(void, OS_CODE) f ( void )

/* Macro to define ISR1: always valid */
#define	ISR1(f)		FUNC(void, OS_CODE) OSEE_COMPILER_KEEP f ( void )

/* Macro to declare ISR2: always valid */
#define	DeclareIsr2(f)	FUNC(void, OS_CODE) f ( void )

/* Macro to define ISR2: always valid */
#define	ISR2(f)		FUNC(void, OS_CODE) OSEE_COMPILER_KEEP f ( void )

/* Macro to declare ISR: always valid */
#define	DeclareIsr(f)	FUNC(void, OS_CODE) f ( void )

/* Macro to define ISR: always valid */
#define	ISR(f)		FUNC(void, OS_CODE) OSEE_COMPILER_KEEP f ( void )

#if (defined(__cplusplus))
}
#endif

#endif	/* !OSEE_DSPIC33_PIC24_IRQ_H */
