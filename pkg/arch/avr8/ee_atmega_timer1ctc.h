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

/** \file	ee_atmega_timer1ctc.h
 *  \brief	Timer 1 in CTC Mode.
 *
 *  Timer 1 is available on ATmega168, ATmega328 and on ATmega2560.
 *
 *  (The page and chapter numbers refer to the ATmega328P documentation).
 *
 *  16.9.2 Clear Timer on Compare Match (CTC) Mode (page 123)
 *  In Clear Timer on Compareor CTC mode (WGM13:0 = 4 or 12), the OCR1A or ICR1
 *  Register are used to manipulate the counter resolution.
 *  In CTC mode the counter is cleared to zero when the counter value (TCNT1)
 *  matches either the OCR1A (WGM13:0 = 4) or the ICR1 (WGM13:0 = 12).
 *  The OCR1A or ICR1 define the top value for the counter, hence also its
 *  resolution.
 *  This mode allows greater control of the compare match output frequency.
 *  It also simplifies the operation of counting external events.
 *  The timing diagram for the CTC mode is shown in Figure 16-6.
 *  The counter value (TCNT1) increases until a compare match occurs with either
 *  OCR1A or ICR1, and then counter (TCNT1) is cleared.
 *  An interrupt can be generated at each time the counter value reaches the TOP
 *  value by either using the OCF1A or ICF1 Flag according to the register used
 *  to define the TOP value.
 *  If the interrupt is enabled, the interrupt handler routine can be used for
 *  updating the TOP value.
 *  However, changing the TOP to a value close to BOTTOM when the counter is
 *  running with none or a low prescaler value must be done with care since the
 *  CTC mode does not have the double buffering feature.
 *  If the new value written to OCR1A or ICR1 is lower than the current value of
 *  TCNT1, the counter will miss the compare match.
 *  The counter will then have to count to its maximum value (0xFFFF) and wrap
 *  around starting at 0x0000 before the compare match can occur.
 *  In many cases this feature is not desirable.
 *  An alternative will then be to use the fast PWM mode using OCR1A for
 *  defining TOP (WGM13:0 = 15) since the OCR1A then will be doublebuffered.
 *  For generating a waveform output in CTC mode, the OC1A output can be set to
 *  toggle its logical level on each compare match by setting the Compare Output
 *  mode bit to toggle mode (COM1A1:0 = 1).
 *  The OC1A value will not be visible on the port pin unless the data direction
 *  for the pin is set to output (DDR_OC1A = 1).
 *  The waveform generated will have a maximum frequency of
 *  fOC1A = fclk_I_O/2 when OCR1A is set to zero (0x0000).
 *  The waveform frequency is defined by the following equation:
 *  fOCnA = fclk_I_O/(2*N*(1+OCRnA))
 *  The Nvariable represents the prescaler factor (1, 8, 64, 256, or 1024).
 *  As for the Normal mode of operation, the TOV1 Flag is set in the same timer
 *  clock cycle that the counter counts from MAX to 0x0000.
 *
 *  \author	Giuseppe Serano
 *  \date	2016
 */

#ifndef	OSEE_ATMEGA_TIMER_1_CTC_H
#define	OSEE_ATMEGA_TIMER_1_CTC_H

#include "ee_platform_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \brief	Timer 1 Start.
 *  \param	microsecondsInterval	Timer 1 Period (us).
 *
 *  Initializes and Start Timer 1 in CTC Mode.
 *
 *  \note	0 < <b>microsecondsInterval</b> < 4194304
 *
 *  \note	On 16 MHz Arduino boards, the Timer has a resolution according
 *  		to <b>microsecondsInterval</b>.
 *  		For intervals x where:
 *  		- x <    4096:	 0.0625 us
 *  		- x <   32768:	 0.5    us
 *  		- x <  262140:	 3.75   us
 *  		- x < 1048576:	16      us
 *  		- x < 4194304:	64      us
 *
 *  \note	Enables Output Compare A Match Interrupt for Timer 1:
 *  		<b>TIMER1_COMPA_vect</b>.
 *
 */
void OsEE_atmega_startTimer1(uint32_t microsecondsInterval);

#ifdef __cplusplus
}
#endif

#endif	/* OSEE_ATMEGA_TIMER_1_CTC_H */
