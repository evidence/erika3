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

/** \file	code.cpp
 *  \brief	Main application.
 *
 *  This file contains the code of main application for Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2017
 */

/* ERIKA Enterprise. */
#include "ee.h"

/* Arduino SDK. */
#include "Arduino.h"

/*
 * Pin 13 has an LED connected on most Arduino boards.
 * give it a name:
 */
int led = 13;
int led_val = LOW;

boolean volatile stk_wrong = false;
unsigned int volatile isr_cnt;
OsEE_addr volatile old_sp;

#if (defined(OSEE_API_DYNAMIC))
TaskType TaskL1;
TaskType IsrTimerId;
#endif /* OSEE_API_DYNAMIC */

/*
 * TASK AND ISR2 MUST BE C SYMBOL
 */
extern "C" {

DeclareTask(TaskL1);

void idle_hook(void);

#define	TIMER1_US		1000
#define	TIMER1_ISR_DIVISOR	25

/* Timer1 ISR2 */
ISR2(TimerISR)
{

	Serial.write("ISR\r\n", strlen("ISR\r\n"));

	isr_cnt++;
	if (isr_cnt >= TIMER1_ISR_DIVISOR) {
		isr_cnt = 0;
		ActivateTask(TaskL1);
	}
}

void StartupHook(void)
{
	/* Prepare Timer1 to send notifications every TIMER1_US. */
	OsEE_atmega_startTimer1(TIMER1_US);
}

};	/* extern "C" */

void loop(void)
{
	if ( !stk_wrong ) {
		if (!old_sp) {
			old_sp = osEE_get_SP();
		}
		else if (old_sp != osEE_get_SP()) {
			stk_wrong = true;
			digitalWrite(led, HIGH);
		}
	}
}

void setup(void)
{
	/* initialize the digital pin as an output. */
	pinMode(led, OUTPUT);

	Serial.begin(115200);
}

void idle_hook(void)
{

	loop();
	cli();
	if (serialEventRun) serialEventRun();
	sei();
}

int main(void)
{

	init();

	setup();

#if defined(USBCON)
	USBDevice.attach();
#endif

#if (defined(OSEE_API_DYNAMIC))
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
		&TaskL1,
		OSEE_TASK_TYPE_BASIC,
		TASK_FUNC(TaskL1),
		1U,
		1U,
		1U,
		128
	);

	SetIdleHook(idle_hook);

	SetISR2Source(IsrTimerId, OSEE_AVR8_TIMER1_COMPA_ISR_ID);
#endif /* OSEE_API_DYNAMIC */

	StartOS(OSDEFAULTAPPMODE);

	return 0;
}

