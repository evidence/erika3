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

#define	HAL_TIMER_MS	     1U

#define	HAL_DELAY_MS	   200U
#define	HAL_SMALLDELAY_MS	25U

/* TASKs */
DeclareTask(Task1);
DeclareTask(Task2);

/* this counter will be printed on the console in ascending 
 * or decreasing order when the button is pressed
 */
volatile int mycounter;

void led_blink(uint8_t theled)
{
  DisableAllInterrupts();
  DemoHAL_LedOn(theled);
  EnableAllInterrupts();

  DemoHAL_Delay(HAL_DELAY_MS);

  DisableAllInterrupts();
  DemoHAL_LedOff(theled);
  EnableAllInterrupts();

  DemoHAL_Delay(HAL_SMALLDELAY_MS);
}


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

  /* do a long loop, blinking for some time */
  for (j=0U; j<6U; j++) {
	led_blink(DEMO_HAL_LED_0);
  }

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

  led_blink(DEMO_HAL_LED_1);

  /* decrement or increment the counter depending on the application mode */
  if ( currentmode==ModeIncrement )
    mycounter++;
  else
    mycounter--;
  
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
  if (timer_divisor==4000) {
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

  /* read the button status */
  buttonstatus = DemoHAL_ButtonRead(DEMO_HAL_BUTTON_0);

  /* check if the first button is pressed or not */
  if (buttonstatus) {
    /* the button is not pressed */
    startupmode = ModeIncrement;
    DemoHAL_LedOff(DEMO_HAL_LED_2);
  }
  else {
    /* the button is pressed */
    startupmode = ModeDecrement;
    mycounter = 1000;
    DemoHAL_LedOn(DEMO_HAL_LED_2);
  }

  DemoHAL_ButtonInterruptEnable(DEMO_HAL_BUTTON_0);

  StartOS(startupmode);

  return 0;
}
