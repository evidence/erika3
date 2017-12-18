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
 *  This files contains the implementation of the System Timer for ATMEGA
 *  AVR8 Derivative.
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2017
 */
/* ERIKA Enterprise Internals */
#include "ee_internal.h"

#define OSEE_AVR8_TIMER1_COMPA  (0U)
#define OSEE_AVR8_TIMER1_COMPB  (1U)

#if (defined(OSEE_SYSTEM_TIMER_DEVICE))
#if (OSEE_SYSTEM_TIMER_DEVICE == OSEE_AVR8_TIMER1_COMPA)

void osEE_avr8_system_timer_init(void) {
  OsEE_atmega_startTimer1(OSTICKDURATION / OSEE_KILO);
}

ISR2(osEE_avr8_system_timer_handler) {
  OsEE_CDB * p_cdb = osEE_get_curr_core();
  osEE_counter_increment(p_cdb->p_sys_counter_db);
}
#else
#error Unsupported System Timer Device: OSEE_SYSTEM_TIMER_DEVICE!
#endif /* OSEE_SYSTEM_TIMER_DEVICE == OSEE_AVR8_TIMER1_COMPA */
#endif /* OSEE_SYSTEM_TIMER_DEVICE */
