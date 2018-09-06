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

/** \file	ee_cortex_m_irqstub.h
 *  \brief	ARM Cortex-M IRQs Internals.
 *
 *  This files contains the internals of the IRQs support for ARM Cortex-M
 *  Architecture available in Erika Enterprise.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

#ifndef OSEE_CORTEX_M_IRQSTUB_H
#define	OSEE_CORTEX_M_IRQSTUB_H

/* Plus I need IRQ handling defines */
#include "ee_cortex_m_irq.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#if	(!defined(OSEE_API_DYNAMIC))

/*
 * ISR Type 1 stub.
 */
FUNC(void, OS_CODE) OSEE_COMPILER_KEEP
osEE_cortex_m_isr1_stub(
  VAR(OsEE_void_cb, AUTOMATIC) f
);

/*
 * ISR Type 2 stub.
 */
FUNC_P2VAR(OsEE_TDB, OS_APPL_CONST, OS_CODE) OSEE_COMPILER_KEEP
osEE_cortex_m_isr2_stub(
  VAR(TaskType, AUTOMATIC) t
);

#else	/* !OSEE_API_DYNAMIC */

/*
 * ISR Type 2 stub.
 */
FUNC(void, OS_CODE) OSEE_COMPILER_KEEP
osEE_cortex_m_isr2_stub(
  VAR(OsEE_isr_src_id, AUTOMATIC) t
);

#endif	/* !OSEE_API_DYNAMIC */

#if (!defined(OSEE_API_DYNAMIC))
/* Define an ISR (category 1) */
#define	OSEE_CORTEX_M_ISR1_DEFINITION(v,f)	\
/* Declare The ISR User handler */		\
extern FUNC(void, OS_CODE) (f)( void );		\
FUNC(void, OS_CODE) (v)( void )			\
{						\
	osEE_cortex_m_isr1_stub(f);		\
}
#endif  /* !OSEE_API_DYNAMIC */

#define OSEE_CORTEX_M_ISR2_DEFINITION(v,t)	\
/* Declare The ISR User handler */		\
FUNC(void, OS_CODE) (v)( void )			\
{						\
	osEE_cortex_m_isr2_stub(t);		\
}

/* Un-Defined ISR */
#define OSEE_CORTEX_M_ISR_NOT_DEFINED(v)	\
/* Define a NAKED ISR handler */		\
FUNC(void, OS_CODE) (v)( void )			\
{						\
	/* Disables IRQ  */			\
	osEE_hal_disableIRQ();			\
	/* Hangs in a infinite loop!!! */	\
	for(;;);			\
}

#if (defined(__cplusplus))
}
#endif

#endif	/* !OSEE_CORTEX_M_IRQSTUB_H */
