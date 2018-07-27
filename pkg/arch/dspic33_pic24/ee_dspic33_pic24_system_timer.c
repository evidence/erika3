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

/** \file	ee_dspic33_pic24_system_timer.c
 *  \brief	System Timer driver source file.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* ERIKA Enterprise Internals */
#include "ee_internal.h"

#if	(defined(OSEE_SYSTEM_TIMER_DEVICE))

#define	OSEE_DSPIC33_PIC24_T1	0x01U
#define	OSEE_DSPIC33_PIC24_T2	0x02U
#define	OSEE_DSPIC33_PIC24_T3	0x03U
#define	OSEE_DSPIC33_PIC24_T4	0x04U
#define	OSEE_DSPIC33_PIC24_T5	0x05U

#if	(OSEE_SYSTEM_TIMER_DEVICE == OSEE_DSPIC33_PIC24_T1)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_CHANNEL	OSEE_T1
#elif	(OSEE_SYSTEM_TIMER_DEVICE == OSEE_DSPIC33_PIC24_T2)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_CHANNEL	OSEE_T2
#elif	(OSEE_SYSTEM_TIMER_DEVICE == OSEE_DSPIC33_PIC24_T3)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_CHANNEL	OSEE_T3
#elif	(OSEE_SYSTEM_TIMER_DEVICE == OSEE_DSPIC33_PIC24_T4)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_CHANNEL	OSEE_T4
#elif	(OSEE_SYSTEM_TIMER_DEVICE == OSEE_DSPIC33_PIC24_T5)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_CHANNEL	OSEE_T5
#else
#error Unsupported System Timer Device: OSEE_SYSTEM_TIMER_DEVICE!
#endif	/* OSEE_SYSTEM_TIMER_DEVICE */

#if	(							\
	OSEE_MICRO_TO_TICKS(					\
		(OSTICKDURATION/OSEE_KILO), OSEE_CPU_CLOCK	\
	) < OSEE_TIMERS_MAX_PERIOD				\
)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PERIOD		(	\
	OSEE_MICRO_TO_TICKS(					\
		(OSTICKDURATION/OSEE_KILO), OSEE_CPU_CLOCK	\
	) - 1U							\
)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PRESCALER	OSEE_TIMER_PS_1
#elif	(							\
	(OSEE_MICRO_TO_TICKS(					\
		(OSTICKDURATION/OSEE_KILO), OSEE_CPU_CLOCK	\
	)/8) <  OSEE_TIMERS_MAX_PERIOD				\
)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PERIOD		(	\
	(OSEE_MICRO_TO_TICKS(					\
		(OSTICKDURATION/OSEE_KILO), OSEE_CPU_CLOCK	\
	)/8) - 1 U						\
)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PRESCALER	OSEE_TIMER_PS_8
#elif	(							\
	(OSEE_MICRO_TO_TICKS(					\
		(OSTICKDURATION/OSEE_KILO), OSEE_CPU_CLOCK	\
	)/64) < OSEE_TIMERS_MAX_PERIOD				\
)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PERIOD		(	\
	(OSEE_MICRO_TO_TICKS(					\
		(OSTICKDURATION/OSEE_KILO), OSEE_CPU_CLOCK	\
	)/64) - 1U						\
)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PRESCALER	OSEE_TIMER_PS_64
#elif	(							\
	(OSEE_MICRO_TO_TICKS(					\
		(OSTICKDURATION/OSEE_KILO), OSEE_CPU_CLOCK	\
	)/256) < OSEE_TIMERS_MAX_PERIOD				\
)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PERIOD		(	\
	(OSEE_MICRO_TO_TICKS(					\
		(OSTICKDURATION/OSEE_KILO), OSEE_CPU_CLOCK	\
	)/256) - 1U						\
)
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PRESCALER	OSEE_TIMER_PS_256
#else
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PERIOD		OSEE_TIMERS_MAX_PERIOD
#define	OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PRESCALER	OSEE_TIMER_PS_256
#endif

/** \brief	System Timer Initialization. */
FUNC(void, OS_CODE) osEE_dspic33_pic24_system_timer_init(void)
{
  osEE_timer_init(
    OSEE_DSPIC33_PIC24_SYSTEM_TIMER_CHANNEL,
    OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PRESCALER,
    (OsEE_reg)OSEE_DSPIC33_PIC24_SYSTEM_TIMER_PERIOD
  );

  osEE_timer_start(OSEE_DSPIC33_PIC24_SYSTEM_TIMER_CHANNEL);

}

/* These two functions are in preparation for the low-poer mode support */
#if 0
/** \brief	System Timer Sleep. */
FUNC(void, OS_CODE) osEE_dspic33_pic24_system_timer_sleep(void)
{
  osEE_timer_stop(OSEE_DSPIC33_PIC24_SYSTEM_TIMER_CHANNEL);
}

/** \brief	System Timer Wakeup. */
FUNC(void, OS_CODE) osEE_dspic33_pic24_system_timer_wakeup(void)
{
  osEE_timer_start(OSEE_DSPIC33_PIC24_SYSTEM_TIMER_CHANNEL);
}
#endif

/*
 * System Timer ISR.
 */
ISR2(osEE_dspic33_pic24_system_timer_handler)
{
  OsEE_CDB * p_cdb = osEE_get_curr_core();

  osEE_counter_increment(p_cdb->p_sys_counter_db);
}

#endif /* OSEE_SYSTEM_TIMER_DEVICE */
