/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 Evidence s.r.l.
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

/** \file   ee_atmega_internal.h
 *  \brief  ATMEGA MCU Internal.
 *
 *  This files contains all Internals for Atmel ATMEGA MCU in Erika Enterprise.
 *
 *  \author Giuseppe Serano
 *  \author Errico Guidieri
 *  \date   2016
 */
#if (!defined(OSEE_ATMEGA_INTERNAL_H))
#define OSEE_ATMEGA_INTERNAL_H

#include "ee_hal.h"
#include "ee_mcu_common_types.h"

/* I need AVR Interrupt */
#include <avr/interrupt.h>

/* I need AVR Input/Output */
#include <avr/io.h>

/*
 * ISR Priorities.
*/
#define OSEE_ISR_PRI_OFF  0x00U
#define OSEE_ISR_PRI_LOW  0x01U
#define OSEE_ISR_PRI_MED  0x02U
#define OSEE_ISR_PRI_HIGH 0x03U

#define OSEE_ATMEGA_VALIDATE(exp) \
  if (!(exp)) {                   \
    return;                       \
  }

#define OSEE_ATMEGA_VALIDATE_IRQ(exp, flags)  \
  if (!(exp)) {                               \
    osEE_hal_resumeIRQ(flags);                \
    return;                                   \
  }

#define OSEE_ATMEGA_VALIDATE_W_RV(exp, rv)  \
  if (!(exp)) {                             \
    return (rv);                            \
  }

#define OSEE_ATMEGA_VALIDATE_IRQ_W_RV(exp, rv, flags) \
  if (!(exp)) {                                       \
    odEE_hal_resumeIRQ(flags);                        \
    return (rv);                                      \
  }

#define OSEE_LOW_BYTE_SH_BITS 0x08U

OSEE_STATIC_INLINE OsEE_uint16  OSEE_ALWAYS_INLINE
  osEE_ATmega_Reg16Read(OSEE_HWREG_PTR Address)
{
  register OsEE_uint16  ret = OSEE_HWREG(Address++);
  ret |= ((OsEE_uint16)EE_HWREG(Address) << OSEE_LOW_BYTE_SH_BITS);
  return ret;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_ATmega_Reg16Write(OSEE_HWREG_PTR Address, OsEE_uint16 Data)
{
  OSEE_HWREG(Address++) = (OsEE_reg)(Data);
  OSEE_HWREG(Address)   = (OsEE_reg)(Data >> EE_LOW_BYTE_SH_BITS);
}

/* True if we are inside an interrupt handler */
#define osEE_is_inside_hw_ISR_call()  OSEE_FALSE

#endif /* !OSEE_ATMEGA_INTERNAL_H */
