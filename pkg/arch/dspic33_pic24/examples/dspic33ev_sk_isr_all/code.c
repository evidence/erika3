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

#include <stdio.h>
#include <string.h>

OsEE_bool volatile stk_wrong = OSEE_M_FALSE;
uint32_t volatile idle_cnt;
OsEE_addr volatile old_sp;

/* TASKs */
DeclareTask(Task1);
DeclareTask(Task2);
DeclareIsr1(stack_handler);

/* Idle Hook */
extern void idle_hook ( void );
extern void free_task1 (void);

/* Counters */
OsEE_reg volatile task1_fired;
OsEE_reg volatile task2_fired;
OsEE_reg volatile task1_ended;
OsEE_reg volatile task2_ended;
OsEE_reg volatile isr1_fired;
OsEE_reg volatile isr2_fired;
OsEE_reg volatile isr2_armed;

/* Stack Pointers */
OsEE_addr volatile task1_sp;
OsEE_addr volatile task2_sp;
OsEE_addr volatile main_sp;

extern SemType V;

#define	VECT_SIZE	100U

#define	TIMER_PERIOD_MS	1U
#define	ISR_DIVISOR	1000U
#define	IDLE_CNT_MAX	100000U

#define	IDLE_STR	(P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA))"Idle\r\n"
#define	IDLE_STR_LEN	6U
#define	ISR_STR		(P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA))"ISR\r\n"
#define	ISR_STR_LEN	5U

void StartupHook(void)
{

}

void serial_print(char const * msg) {
  SuspendAllInterrupts();
  DemoHAL_SerialWrite(
    (P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA))msg, strlen(msg)
  );
  ResumeAllInterrupts();
}

void print_sp(TaskType tid, OsEE_addr sp) {
  static char msg[] = "TASK n SP<0xXXXX>\r\n  ";
  SuspendAllInterrupts();
  sprintf(msg, "TASK %d SP<%p>\r\n", tid, sp);
  ResumeAllInterrupts();
  serial_print(msg);
}

#define OSEE_BREAK_POINT()  do {                                    \
    DemoHAL_LedOn(DEMO_HAL_LED_1);                                  \
    DisableAllInterrupts();                                         \
    serial_print("Test Failed!!!, line:" OSEE_S(__LINE__) " \r\n"); \
    while ( 1U ) {                                                  \
      ;                                                             \
    }                                                               \
  } while ( 0U )

void free_task1(void) {
  DemoHAL_LedToggle(DEMO_HAL_LED_2);
  isr2_armed  = 0U;
}

void idle_hook ( void ) {

  OsEE_addr volatile curr_sp = osEE_get_SP();

  if ( main_sp == 0U ) {
    main_sp = curr_sp;
  } else if ( main_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }

  ++idle_cnt;
  if (idle_cnt >= IDLE_CNT_MAX) {
    idle_cnt = 0U;
    DemoHAL_LedToggle(DEMO_HAL_LED_0);
    DemoHAL_SerialWrite(IDLE_STR, IDLE_STR_LEN);
  }

  DemoHAL_MainFunction();
}

ISR1(StackISR)
{
	isr1_fired++;
	OSEE_BREAK_POINT();
}

int main(void)
{
  DemoHAL_Init();

  StartOS(OSDEFAULTAPPMODE);

  return 0;
}

/*
 * TASK 1
 */
TASK(Task1)
{
  OsEE_addr curr_sp;

  serial_print("TASK1\r\n");

  task1_fired++;

  isr2_armed = 1U;

  curr_sp = osEE_get_SP();
  if ( task1_sp == 0U ) {
    task1_sp = curr_sp;
  } else if ( task1_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }

  ActivateTask(Task2);

  PostSem(&V);

  while (isr2_armed) {
    ; /* Wait ISR2 release */
  }
  serial_print("Release TASK1\r\n");

  curr_sp = osEE_get_SP();
  if ( task1_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }

  task1_ended++;
}


void recursiveFunc(void)
{
	volatile uint8_t v[VECT_SIZE];
	volatile uint8_t i;

	for (i=0U; i<VECT_SIZE; i++)
	{
		v[i] = 0U;
	}
	recursiveFunc();
}

/*
 * TASK 2
 */
TASK(Task2)
{
  OsEE_addr  curr_sp;
  serial_print("TASK2\r\n");
  curr_sp = osEE_get_SP();
  if ( task2_sp == 0U ) {
    task2_sp = curr_sp;
  } else if ( task2_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }

  task2_fired++;

  WaitSem(&V);

  DemoHAL_LedToggle(DEMO_HAL_LED_3);

  recursiveFunc();
  task2_ended++;
}

