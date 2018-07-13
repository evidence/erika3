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

/** \file	ee_dspic33ev_timers.h
 *  \brief	Timers driver header file.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

#ifndef	OSEE_DSPIC33EV_TIMERS_H
#define	OSEE_DSPIC33EV_TIMERS_H

#include "ee.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#define	OSEE_TIMERS_MAX_PERIOD	0xFFFFUL

/** Timer Prescalers */
typedef enum {
  OSEE_TIMER_PS_1   = 0U,
  OSEE_TIMER_PS_8   = 1U,
  OSEE_TIMER_PS_64  = 2U,
  OSEE_TIMER_PS_256 = 3U
} OsEE_Timer_Prescaler;

/** Timer Chs **/
typedef enum {
  OSEE_T1,
  OSEE_T2,
  OSEE_T3,
  OSEE_T4,
  OSEE_T5
} OsEE_Timer_Channel;

/** \brief	Timer Initialization.
 *  \param	channel		Timer Channel.
 *  \param	prescaler	Timer Prescaler.
 *  \param	period		Timer Period.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_timer_init(
  VAR(OsEE_Timer_Channel, AUTOMATIC)	channel,
  VAR(OsEE_Timer_Prescaler, AUTOMATIC)	prescaler,
  VAR(OsEE_reg, AUTOMATIC)		period
)
{
  switch (channel)
  {
    case OSEE_T1:
      T1CONbits.TON = 0U;		/* Disable Timer		  */
      T1CONbits.TCS = 0U;		/* Select internal clock (Fosc/2) */
      T1CONbits.TGATE = 0U;		/* Disable Gated Timer mode	  */
      T1CONbits.TCKPS = prescaler;	/* Load the prescaler		  */
      PR1 = period;			/* Load the period value	  */
      TMR1 = 0U;			/* Clear Timer Counter.		  */
      break;
    case OSEE_T2:
      T2CONbits.TON = 0U;		/* Disable Timer		  */
      T2CONbits.TCS = 0U;		/* Select internal clock (Fosc/2) */
      T2CONbits.TGATE = 0U;		/* Disable Gated Timer mode	  */
      T2CONbits.TCKPS = prescaler;	/* Load the prescaler		  */
      PR2 = period;			/* Load the period value	  */
      TMR2 = 0U;			/* Clear Timer Counter.		  */
      break;
    case OSEE_T3:
      T3CONbits.TON = 0U;		/* Disable Timer		  */
      T3CONbits.TCS = 0U;		/* Select internal clock (Fosc/2) */
      T3CONbits.TGATE = 0U;		/* Disable Gated Timer mode	  */
      T3CONbits.TCKPS = prescaler;	/* Load the prescaler		  */
      PR3 = period;			/* Load the period value	  */
      TMR3 = 0U;			/* Clear Timer Counter.		  */
      break;
    case OSEE_T4:
      T4CONbits.TON = 0U;		/* Disable Timer		  */
      T4CONbits.TCS = 0U;		/* Select internal clock (Fosc/2) */
      T4CONbits.TGATE = 0U;		/* Disable Gated Timer mode	  */
      T4CONbits.TCKPS = prescaler;	/* Load the prescaler		  */
      PR4 = period;			/* Load the period value	  */
      TMR4 = 0U;			/* Clear Timer Counter.		  */
      break;
    case OSEE_T5:
      T5CONbits.TON = 0U;		/* Disable Timer		  */
      T5CONbits.TCS = 0U;		/* Select internal clock (Fosc/2) */
      T5CONbits.TGATE = 0U;		/* Disable Gated Timer mode	  */
      T5CONbits.TCKPS = prescaler;	/* Load the prescaler		  */
      PR5 = period;			/* Load the period value	  */
      TMR5 = 0U;			/* Clear Timer Counter.		  */
      break;
    default:                            /* no other timer on this MCU     */
      break;
  }
}

/** \brief	Start a timer.
 *  \param	channel	Timer Channel.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_timer_start(
  VAR(OsEE_Timer_Channel, AUTOMATIC)	channel
)
{
  switch (channel)
  {
    case OSEE_T1:
      T1CONbits.TON = 1U;
      break;
    case OSEE_T2:
      T2CONbits.TON = 1U;
      break;
    case OSEE_T3:
      T3CONbits.TON = 1U;
      break;
    case OSEE_T4:
      T4CONbits.TON = 1U;
      break;
    case OSEE_T5:
      T5CONbits.TON = 1U;
      break;
    default:                            /* no other timer on this MCU     */
      break;
  }
}

/** \brief	Stop a timer
 *  \param	channel	Timer Channel.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_timer_stop(
  VAR(OsEE_Timer_Channel, AUTOMATIC)	channel
)
{
  switch (channel)
  {
    case OSEE_T1:
      T1CONbits.TON = 0U;
      break;
    case OSEE_T2:
      T2CONbits.TON = 0U;
      break;
    case OSEE_T3:
      T3CONbits.TON = 0U;
      break;
    case OSEE_T4:
      T4CONbits.TON = 0U;
      break;
    case OSEE_T5:
      T5CONbits.TON = 0U;
      break;
    default:                            /* no other timer on this MCU     */
      break;
  }
}

/** \brief	Timer Counter Retrieval
 *  \param	channel	Timer Channel.
 *  \return	Timer Counter to Retrieve.
 */
OSEE_STATIC_INLINE FUNC(OsEE_reg, OS_CODE) OSEE_ALWAYS_INLINE
osEE_timer_get_counter(
  VAR(OsEE_Timer_Channel, AUTOMATIC)	channel
)
{
  OsEE_reg	cnt;
  switch (channel)
  {
    case OSEE_T1:
      cnt = TMR1;
      break;
    case OSEE_T2:
      cnt = TMR2;
      break;
    case OSEE_T3:
      cnt = TMR3;
      break;
    case OSEE_T4:
      cnt = TMR4;
      break;
    case OSEE_T5:
      cnt = TMR5;
      break;
    default:                            /* no other timer on this MCU     */
      break;
  }
  return cnt;
}

/** \brief	Acknowledge a timer IRQ.
 *  \param	channel	Timer Channel.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_timer_irq_ack(
  VAR(OsEE_Timer_Channel, AUTOMATIC)	channel
)
{
  switch (channel)
  {
    case OSEE_T1:
      IFS0bits.T1IF = 0U;
      break;
    case OSEE_T2:
      IFS0bits.T2IF = 0U;
      break;
    case OSEE_T3:
      IFS0bits.T3IF = 0U;
      break;
    case OSEE_T4:
      IFS1bits.T4IF = 0U;
      break;
    case OSEE_T5:
      IFS1bits.T5IF = 0U;
      break;
    default:                            /* no other timer on this MCU     */
      break;
  }
}

#if (defined(__cplusplus))
}
#endif

#endif /* OSEE_DSPIC33EV_TIMERS_H */

