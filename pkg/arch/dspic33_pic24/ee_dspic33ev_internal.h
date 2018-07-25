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

/** \file	ee_dspic33ev_internal.h
 *  \brief	dsPIC33EV MCU Internal.
 *
 *  This files contains all Internals for Microchip dsPIC33EV MCU in
 *  Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \author	Errico Guidieri
 *  \date	2018
 */
#ifndef OSEE_DSPIC33EV_INTERNAL_H
#define	OSEE_DSPIC33EV_INTERNAL_H

#include "ee_hal.h"
#include "ee_mcu_common_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#define	OSEE_DSPIC33EV_VALIDATE(exp)				\
  if (!(exp)) {							\
    return;							\
  }

#define	OSEE_DSPIC33EV_VALIDATE_IRQ(exp, flags)			\
  if (!(exp)) {							\
    osEE_hal_resumeIRQ(flags);					\
    return;							\
  }

#define	OSEE_DSPIC33EV_VALIDATE_W_RV(exp, rv)			\
  if (!(exp)) {							\
    return (rv);						\
  }

#define	OSEE_DSPIC33EV_VALIDATE_IRQ_W_RV(exp, rv, flags)	\
  if (!(exp)) {							\
    odEE_hal_resumeIRQ(flags);					\
    return (rv);						\
  }

#ifndef	OSEE_DSPIC33_PIC24_SOFT_I_BIT	/* [GS]: Using INTCON2bits.GIE! */

/* Disable/Enable Interrupts */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_disableIRQ( void )
{
  INTCON2bits.GIE = 0U;
}

OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_enableIRQ( void )
{
  INTCON2bits.GIE = 1U;
}

/* Suspend/Resume Interrupts */
OSEE_STATIC_INLINE FUNC(OsEE_reg, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_suspendIRQ ( void )
{
  OsEE_reg gie = INTCON2bits.GIE;
  osEE_hal_disableIRQ();
  return gie;
}

OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_resumeIRQ ( OsEE_reg flags )
{
  INTCON2bits.GIE = (uint8_t)flags;
}

#endif	/* OSEE_DSPIC33_PIC24_SOFT_I_BIT - [GS]: Using INTCON2bits.GIE! */

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_DSPIC33EV_INTERNAL_H */
