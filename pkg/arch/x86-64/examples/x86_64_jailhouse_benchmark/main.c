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

#include <stdio.h>
#include <string.h>
#include <inmate.h>
#include "ee.h"
#include "hal.h"

#define ee_print(...) printk(__VA_ARGS__)

DeclareTask(Task1);
DeclareTask(Task2);

OSEE_TICK_TYPE task_t2, isr_t2;


/* First task */
TASK(Task1)
{
	static OSEE_TICK_TYPE task_act_min = 1000000;
	static OSEE_TICK_TYPE task_act_max = 0;
	static OSEE_TICK_TYPE task_exit_min = 1000000;
	static OSEE_TICK_TYPE task_exit_max = 0;
	static OSEE_TICK_TYPE isr_act_min = 1000000;
	static OSEE_TICK_TYPE isr_act_max = 0;
	static OSEE_TICK_TYPE isr_exit_min = 1000000;
	static OSEE_TICK_TYPE isr_exit_max = 0;

	OSEE_TICK_TYPE task_t1, task_t3, isr_t1, isr_t3;

	task_t1 = DemoHAL_TimerGetValue();
	ActivateTask(Task2);
	task_t3 = DemoHAL_TimerGetValue();

	isr_t1 = DemoHAL_TimerGetValue();
	DemoHAL_ISRTrigger(DEMO_HAL_ISR_0);
	isr_t3 = DemoHAL_TimerGetValue();


	if (task_t2 > task_t1) {
		OSEE_TICK_TYPE task_act = task_t2 - task_t1;
		if (task_act < task_act_min)
			task_act_min = task_act;
		if (task_act > task_act_max)
			task_act_max = task_act;
		ee_print("Task act. time (ns):\tMin=%lu\tCurrent=%lu\tMax=%lu\n",
				task_act_min, task_act, task_act_max);
	}

	if (task_t3 > task_t2) {
		OSEE_TICK_TYPE task_exit = task_t3 - task_t2;
		if (task_exit < task_exit_min)
			task_exit_min = task_exit;
		if (task_exit > task_exit_max)
			task_exit_max = task_exit;
		ee_print("Task exit time (ns):\tMin=%lu\tCurrent=%lu\tMax=%lu\n",
				task_exit_min, task_exit, task_exit_max);
	}

	if (isr_t2 > isr_t1) {
		OSEE_TICK_TYPE isr_act = isr_t2 - isr_t1;
		if (isr_act < isr_act_min)
			isr_act_min = isr_act;
		if (isr_act > isr_act_max)
			isr_act_max = isr_act;
		ee_print("ISR call time (ns):\tMin=%lu\tCurrent=%lu\tMax=%lu\n",
				isr_act_min, isr_act, isr_act_max);
	}

	if (isr_t3 > isr_t2) {
		OSEE_TICK_TYPE isr_exit = isr_t3 - isr_t2;
		if (isr_exit < isr_exit_min)
			isr_exit_min = isr_exit;
		if (isr_exit > isr_exit_max)
			isr_exit_max = isr_exit;
		ee_print("ISR exit time (ns):\tMin=%lu\tCurrent=%lu\tMax=%lu\n",
				isr_exit_min, isr_exit, isr_exit_max);
	}

	TerminateTask();
}


/* Activated task */
TASK(Task2)
{
	task_t2 = DemoHAL_TimerGetValue();
	TerminateTask();
}


void isr_handler(void)
{
	isr_t2 = DemoHAL_TimerGetValue();
}


/******************************************************************************
 *  Main
 *****************************************************************************/
void idle_hook(void);

void idle_hook(void)
{
	ee_print("Starting communication over UART\n");

	/* endless loop*/
	while(1) {
		asm volatile("hlt": : : "memory");
	}
}




int main(void)
{
	ee_print("Starting OS...\n");
	StartOS(OSDEFAULTAPPMODE);
	return 0;
}
