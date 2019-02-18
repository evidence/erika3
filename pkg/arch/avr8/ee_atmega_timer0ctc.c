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
 * Timer 0 in CTC Mode.
 *
 * 2016, Giuseppe Serano
 */

#include "ee_internal.h"

#define	TIMER_0_NO_PRESCALER_MAX_TICKS		   16U
#define	TIMER_0_PRESCALER_8_MAX_TICKS		  128U
#define	TIMER_0_PRESCALER_64_MAX_TICKS		 1024U
#define	TIMER_0_PRESCALER_256_MAX_TICKS		 4096U
#define	TIMER_0_PRESCALER_1024_MAX_TICKS	20480U

/*
 * 0 < microsecondsInterval <= TIMER_0_PRESCALER_1024_MAX_TICKS
 * On 16 MHz Arduino boards, this function has a resolution according to
 * microsecondsInterval.
 * For intervals x where:
 * - x < TIMER_0_NO_PRESCALER_MAX_TICKS   =    16:	0,0625 us
 * - x < TIMER_0_PRESCALER_8_MAX_TICKS    =   128:	0,5    us
 * - x < TIMER_0_PRESCALER_64_MAX_TICKS   =  1024:	3,75   us
 * - x < TIMER_0_PRESCALER_256_MAX_TICKS  =  4096:	16     us
 * - x < TIMER_0_PRESCALER_1024_MAX_TICKS = 20480:	64     us
 */
void OsEE_atmega_startTimer0(uint32_t microsecondsInterval) {
  uint8_t	timer0Prescaler;
  uint16_t	timer0CompareValue;
  TCCR0B = 0;	/* Pause Timer. */
  TCCR0A = 0;
  TCNT0  = 0;
  /*
   * 15.9.2 TCCR0B (page 109)
   * 0 0 0 No clock source (Timer/Counter stopped)
   * 0 0 1 clkIO/1 (No prescaling)
   * 0 1 0 clkIO/8 (From prescaler)
   * 0 1 1 clkIO/64 (From prescaler)
   * 1 0 0 clkIO/256 (From prescaler)
   * 1 0 1 clkIO/1024 (From prescaler)
   */
#if (F_CPU == 16000000L)
  if ( microsecondsInterval < TIMER_0_NO_PRESCALER_MAX_TICKS ) {
    timer0Prescaler = (1 << CS00);
    timer0CompareValue = ((uint16_t)(microsecondsInterval << 4) - 1);
  }
  else if ( microsecondsInterval < TIMER_0_PRESCALER_8_MAX_TICKS ) {
    timer0Prescaler = (1 << CS01);
    timer0CompareValue = ((uint16_t)(microsecondsInterval << 1) - 1);
  }
  else if ( microsecondsInterval < TIMER_0_PRESCALER_64_MAX_TICKS ) {
    timer0Prescaler = (1 << CS01) | (1 << CS00);
    timer0CompareValue = ((uint16_t)(microsecondsInterval >> 2) - 1);
  }
  else if ( microsecondsInterval < TIMER_0_PRESCALER_256_MAX_TICKS ) {
    timer0Prescaler = (1 << CS02);
    timer0CompareValue = ((uint16_t)(microsecondsInterval >> 4) - 1);
  }
  else {	/*  microsecondsInterval < TIMER_0_PRESCALER_1024_MAX_TICKS */
    timer0Prescaler = (1 << CS02) | (1 << CS00);
    timer0CompareValue = ((uint16_t)(microsecondsInterval >> 6) - 1);
  }
#else
  #error("Unsupported CPU frequency")
#endif
  TIFR0  = (1 << OCIE0A);	/* Clear Output Compare A Match Flag. */
  TIMSK0 = (1 << OCIE0A);	/* Output Compare A Match Interrupt Enable */
  OCR0A  = timer0CompareValue;	/* Set Compare A Match Value */
  TCCR0B = (1 << WGM02) | timer0Prescaler;	/* Set CTC Mode and Prescaler. */
}	/* startTimer0() */
