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

/** \file   ee_avr8_utils.c
 *  \brief  AVR8 Utilities Implementation.
 *
 *  This files contains the implementation of the utilities for AVR8
 *  Architecture available in Erika Enterprise.
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Giuseppe Serano
 *  \author Errico Guidieri
 *  \date   2016
 */
/* ERIKA Enterprise Internals */
#include "ee_internal.h"

/* Write to a CCP-protected 8-bit I/O register.
 *
 * param[in]  addr  Address of the I/O register.
 * param[in]  value Value to be written.
 * return Nothing.
 *
 * note This function is written in assembly because of the timecritial
 *      operation of writing to the registers.
 *
 * not  CCP Register Address: 0x0034U
 *
 * note CCP I/O register signature: 0xD8U
 *
 * note INTERRUPTS MUST BE DISABLED!!!
 */
void osEE_avr8_WriteCCPReg(volatile OsEE_reg * addr, OsEE_reg value)
{
#if 0
  volatile OsEE_reg flags;
#endif /* 0 */
  volatile OsEE_reg *tmp_addr = addr;

#if 0
  flags = osEE_hal_suspendIRQ();
#endif /* 0 */

#if (defined(RAMPZ))
  RAMPZ = 0;
#endif  /* RAMPZ */

  __asm__ __volatile__ (
    "movw r30,  %0" "\n\t"
    "ldi  r16,  %2" "\n\t"
    "out   %3, r16" "\n\t"
    "st     Z,  %1" "\n\t"
    :
    : "r" (tmp_addr), "r" (value), "M" (0xD8U), "i" (0x0034U)
    : "r16", "r30", "r31"
  );

#if 0
  osEE_hal_resumeIRQ(flags);
#endif  /* 0 */
}
