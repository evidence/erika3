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

/** \file	code.c
 *  \brief	Main application.
 *
 *  This file contains the code of main application for Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* ERIKA Enterprise. */
#include "ee.h"

/* HAL */
#include "hal.h"

OsEE_bool volatile stk_wrong = OSEE_FALSE;
uint16_t volatile isr_cnt;
uint32_t volatile idle_cnt;
OsEE_addr volatile old_sp;

#if (defined(OSEE_API_DYNAMIC))
TaskType TaskISR;
TaskType IsrTimerId;
#endif /* OSEE_API_DYNAMIC */

DeclareTask(TaskISR);
void idle_hook(void);

#define	TIMER_PERIOD_MS	1U
#define	TIMER_DELAY_MS	1000U
#define	IDLE_CNT_MAX	100000U

#define	IDLE_STR	(P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA))"Idle\r\n"
#define	IDLE_STR_LEN	6U
#define	ISR_STR		(P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA))"ISR\r\n"
#define	ISR_STR_LEN	5U

/* Timer ISR2 */
ISR2(TimerISR)
{
	DemoHAL_SerialWrite(ISR_STR, ISR_STR_LEN);

	++isr_cnt;
	if (isr_cnt >= TIMER_DELAY_MS) {
		isr_cnt = 0;
		ActivateTask(TaskISR);
	}
	DemoHAL_TimerAck();
}

void StartupHook(void)
{
	DemoHAL_TimerInit(TIMER_PERIOD_MS);
}

void idle_hook(void)
{
	if ( !stk_wrong ) {
		if (!old_sp) {
			old_sp = osEE_get_SP();
		}
		else if (old_sp != osEE_get_SP()) {
			stk_wrong = OSEE_TRUE;
			DemoHAL_LedOn(DEMO_HAL_LED_1);
			for(;;);
		}
	}

	++idle_cnt;
	if (idle_cnt >= IDLE_CNT_MAX) {
		idle_cnt = 0;
		DemoHAL_LedToggle(DEMO_HAL_LED_0);
		DemoHAL_SerialWrite(IDLE_STR, IDLE_STR_LEN);
	}

	DemoHAL_MainFunction();
}

int main(void)
{
	DemoHAL_Init();

#if (defined(OSEE_API_DYNAMIC))
	InitOS();

	CreateTask(
		&IsrTimerId,
		OSEE_TASK_TYPE_ISR2,
		TimerISR,
		1U,
		1U,
		1U,
		OSEE_SYSTEM_STACK
	);
	CreateTask(
		&TaskISR,
		OSEE_TASK_TYPE_BASIC,
		TASK_FUNC(TaskISR),
		1U,
		1U,
		1U,
		512
	);

	SetIdleHook(idle_hook);

	SetISR2Source(IsrTimerId, TIMER_ISR_ID);
#endif /* OSEE_API_DYNAMIC */

	StartOS(OSDEFAULTAPPMODE);

	return 0;

}

