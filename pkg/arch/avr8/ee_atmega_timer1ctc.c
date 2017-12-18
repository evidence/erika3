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

/*
 * Timer 1 in CTC Mode.
 *
 * 2016, Giuseppe Serano
 */

#include "ee_internal.h"

#define	TIMER_1_NO_PRESCALER_MAX_TICKS		   4096U
#define	TIMER_1_PRESCALER_8_MAX_TICKS		  32768U
#define	TIMER_1_PRESCALER_64_MAX_TICKS		 262140U
#define	TIMER_1_PRESCALER_256_MAX_TICKS		1048576U
#define	TIMER_1_PRESCALER_1024_MAX_TICKS	4194304U

/*
 * 0 < microsecondsInterval <= TIMER_1_PRESCALER_1024_MAX_TICKS
 * On 16 MHz Arduino boards, this function has a resolution according to
 * microsecondsInterval.
 * For intervals x where:
 * - x < TIMER_1_NO_PRESCALER_MAX_TICKS   =    4096:	0,0625 us
 * - x < TIMER_1_PRESCALER_8_MAX_TICKS    =   32768:	0,5    us
 * - x < TIMER_1_PRESCALER_64_MAX_TICKS   =  262140:	3,75   us
 * - x < TIMER_1_PRESCALER_256_MAX_TICKS  = 1048576:	16     us
 * - x < TIMER_1_PRESCALER_1024_MAX_TICKS = 4194304:	64     us
 */
void OsEE_atmega_startTimer1(uint32_t microsecondsInterval) {
  uint8_t	timer1Prescaler;
  uint16_t	timer1CompareValue;
  TCCR1B = 0;	/* Pause Timer. */
  TCCR1A = 0;
  TCCR1C = 0;
  TCNT1  = 0;
  /*
   * 16.11.2 TCCR1B (page 134)
   * 0 0 0 No clock source (Timer/Counter stopped)
   * 0 0 1 clkIO/1 (No prescaling)
   * 0 1 0 clkIO/8 (From prescaler)
   * 0 1 1 clkIO/64 (From prescaler)
   * 1 0 0 clkIO/256 (From prescaler)
   * 1 0 1 clkIO/1024 (From prescaler)
   */
#if (F_CPU == 16000000L)
  if ( microsecondsInterval < TIMER_1_NO_PRESCALER_MAX_TICKS ) {
    timer1Prescaler = (1 << CS10);
    timer1CompareValue = ((uint16_t)(microsecondsInterval << 4) - 1);
  }
  else if ( microsecondsInterval < TIMER_1_PRESCALER_8_MAX_TICKS ) {
    timer1Prescaler = (1 << CS11);
    timer1CompareValue = ((uint16_t)(microsecondsInterval << 1) - 1);
  }
  else if ( microsecondsInterval < TIMER_1_PRESCALER_64_MAX_TICKS ) {
    timer1Prescaler = (1 << CS11) | (1 << CS10);
    timer1CompareValue = ((uint16_t)(microsecondsInterval >> 2) - 1);
  }
  else if ( microsecondsInterval < TIMER_1_PRESCALER_256_MAX_TICKS ) {
    timer1Prescaler = (1 << CS12);
    timer1CompareValue = ((uint16_t)(microsecondsInterval >> 4) - 1);
  }
  else {	/*  microsecondsInterval < TIMER_1_PRESCALER_1024_MAX_TICKS */
    timer1Prescaler = (1 << CS12) | (1 << CS10);
    timer1CompareValue = ((uint16_t)(microsecondsInterval >> 6) - 1);
  }
#else
  #error("Unsupported CPU frequency")
#endif
  TIFR1  = (1 << OCIE1A);	/* Clear Output Compare A Match Flag. */
  TIMSK1 = (1 << OCIE1A);	/* Output Compare A Match Interrupt Enable */
  OCR1A  = timer1CompareValue;	/* Set Compare A Match Value */
  TCCR1B = (1 << WGM12) | timer1Prescaler;	/* Set CTC Mode and Prescaler. */
}	/* startTimer1() */
