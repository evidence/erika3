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

/** \file	code.c
 *  \brief	Main application.
 *
 *  This file contains the code of main application for Erika Enterprise.
 *
 *  \author	Paolo Gai
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* ERIKA Enterprise. */
#include "ee.h"

/* HAL */
#include "hal.h"

#define	HAL_TIMER_MS	1U

#define	HAL_DELAY_MS	25U

#define	IDLE_CNT_MAX	100000U

#define	IDLE_STR	(uint8_t const *)"Idle\r\n"
#define	IDLE_STR_LEN	6U
#define	ISR_STR		(uint8_t const *)"ISR\r\n"
#define	ISR_STR_LEN	5U

#define	WC_STR		(uint8_t const *)"I love EE3!\r\n"
#define	WC_STR_LEN	14U

#define	CNT_STR		(uint8_t const *)"mycounter: "
#define	CNT_STR_LEN	11U

#define	DEC_STR		(uint8_t const *)"Dec\r\n"
#define	DEC_STR_LEN	5U

#define	INC_STR		(uint8_t const *)"Inc\r\n"
#define	INC_STR_LEN	5U

void printchar(char c)
{
  uint8_t volatile ch[2U];
  ch[0U] = c;
  DemoHAL_SerialWrite((uint8_t const *)ch, 1U);
}

uint32_t volatile idle_cnt;
OsEE_addr volatile old_sp;

#if (defined(OSEE_API_DYNAMIC))
TaskType Task1;
TaskType Task2;
TaskType IsrTimerId;
TaskType IsrButtonsId;
#endif /* OSEE_API_DYNAMIC */

/* TASKs */
DeclareTask(Task1);
DeclareTask(Task2);

/* this counter will be printed on the console in ascending 
 * or decreasing order when the button is pressed
 */
volatile int mycounter;

/*
 * This is the Low priority task.
 * When the task runs, it locks a resource for a -long- time, preventing 
 * HighTask to preempt.
 */

TASK(LowTask)
{
  uint8_t j;

  /* Lock the resource */
  GetResource(Resource);

  /* do a long loop, printing the numbers from 0 to 9 */
  DemoHAL_LedOn(DEMO_HAL_LED_0);

  for (j=0U; j<10U; j++) {
    DemoHAL_Delay(2*HAL_DELAY_MS);
    printchar(j +'0');
  }

  DemoHAL_LedOff(DEMO_HAL_LED_0);
  
  /* Release the lock */
  ReleaseResource(Resource);
  
  TerminateTask();
}


/* High Priority Task.
 * This task simply decrements the counter depending on the current 
 * applicationmode, and prints it using printf.
 */
TASK(HighTask)
{
  uint8_t i;
  AppModeType currentmode;
  
  /* get the current application mode */
  currentmode = GetActiveApplicationMode();
  
  GetResource(Resource);

  DemoHAL_LedOn(DEMO_HAL_LED_1);

  for (i=0U; i<10U; i++) {
    DemoHAL_Delay(HAL_DELAY_MS);
  }

  /* decrement or increment the counter depending on the application mode */
  if ( currentmode==ModeIncrement )
    mycounter++;
  else
    mycounter--;
  
  DemoHAL_SerialWrite(CNT_STR, CNT_STR_LEN);
  printchar(((mycounter%1000)/100)+'0');
  printchar(((mycounter%100)/10)+'0');
  printchar((mycounter%10)+'0');

  DemoHAL_LedOff(DEMO_HAL_LED_1);

  ReleaseResource(Resource);

  TerminateTask();
}

/* 
 * This is an ISR Type 2 which is attached to the Timer peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */

volatile int timer_divisor = 0;
ISR2(TimerISR)
{
  timer_divisor++;
  if (timer_divisor==2000) {
    timer_divisor = 0;
    ActivateTask(LowTask);
  }
  DemoHAL_TimerAck();
}

/*
 * Handle button interrupts activates HighTask.
 */
ISR2(ButtonsISR)
{
  DemoHAL_ButtonInterruptAck(DEMO_HAL_BUTTON_0);
  ActivateTask(HighTask);  
}

/* 
 * The StartupHook in this case is used to initialize the Button and timer
 * interrupts
 */
void StartupHook(void)
{
  DemoHAL_TimerInit(HAL_TIMER_MS);
}

void idle_hook ( void ) {

  OsEE_addr volatile curr_sp = osEE_get_SP();

  if ( old_sp == 0U ) {
    old_sp = curr_sp;
  } else if ( old_sp != curr_sp ) {
    DemoHAL_LedOn(DEMO_HAL_LED_1);
    while (1U);
  }

  ++idle_cnt;
  if (idle_cnt >= IDLE_CNT_MAX) {
    idle_cnt = 0U;
    DemoHAL_SerialWrite(IDLE_STR, IDLE_STR_LEN);
  }

  DemoHAL_MainFunction();
}

int main(void)
{
  VAR(AppModeType, AUTOMATIC)	startupmode;
  
  VAR(OsEE_bool, AUTOMATIC)	buttonstatus;

  DemoHAL_Init();

  /* initialize buttons so we can read button 1 value */
  DemoHAL_ButtonInit();

  /* just a nice subliminal welcome message :-) */
  DemoHAL_Delay(HAL_DELAY_MS);

  DemoHAL_SerialWrite(WC_STR, WC_STR_LEN);

  /* read the button status */
  buttonstatus = DemoHAL_ButtonRead(DEMO_HAL_BUTTON_0);

  /* check if the first button is pressed or not */
  if (buttonstatus) {
    /* the button is not pressed */
    startupmode = ModeIncrement;
    DemoHAL_SerialWrite(INC_STR, INC_STR_LEN);
    DemoHAL_LedOff(DEMO_HAL_LED_2);
  }
  else {
    /* the button is pressed */
    startupmode = ModeDecrement;
    mycounter = 1000;
    DemoHAL_SerialWrite(DEC_STR, DEC_STR_LEN);
    DemoHAL_LedOn(DEMO_HAL_LED_2);
  }

#if (defined(OSEE_API_DYNAMIC))
  InitOS();
  
  CreateTask( &Task1, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task1),
      1U, 1U, 1U, 512U );
  CreateTask( &Task2, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task2),
      2U, 2U, 1U, 512U );
  CreateTask( &IsrTimerId, OSEE_TASK_TYPE_ISR2, TimerISR,
      1U, 1U, 1U, OSEE_SYSTEM_STACK );
  CreateTask( &IsrButtonsId, OSEE_TASK_TYPE_ISR2, ButtonsISR,
      1U, 1U, 1U, OSEE_SYSTEM_STACK );

  /* Prio settate a 1 dalla BSP all'avvio */
  SetISR2Source(IsrTimerId, TIMER_ISR_ID);
  SetISR2Source(IsrButtonsId, BUTTONS_ISR_ID);

  SetIdleHook(idle_hook);
#endif /* OSEE_API_DYNAMIC */

  DemoHAL_ButtonInterruptEnable(DEMO_HAL_BUTTON_0);

  StartOS(startupmode);

  return 0;
}
