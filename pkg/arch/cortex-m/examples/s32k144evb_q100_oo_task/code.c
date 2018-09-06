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

/* A few counters incremented at each event
 * (alarm, button press or task activation...)
 */
volatile uint16_t timer_fired;
volatile uint16_t button_fired;
volatile uint16_t task1_fired;
volatile uint16_t task2_fired;

#if (defined(OSEE_API_DYNAMIC))
TaskType Task1;
TaskType Task2;
TaskType IsrTimerId;
TaskType IsrButtonsId;
#endif /* OSEE_API_DYNAMIC */

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

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

/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  task1_fired++;
  
  /* First half of the christmas tree */
  led_blink(DEMO_HAL_LED_0);
  led_blink(DEMO_HAL_LED_0);
  led_blink(DEMO_HAL_LED_0);
  
  /* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
#ifdef MYSCHEDULE
  Schedule();
#endif

  /* Second half of the christmas tree */
  led_blink(DEMO_HAL_LED_1);
  led_blink(DEMO_HAL_LED_1);
  led_blink(DEMO_HAL_LED_1);
  
  TerminateTask();
}


/* Task2: Print the counters on the UART */
TASK(Task2)
{
  /* count the number of Task2 activations */
  task2_fired++;

  led_blink(DEMO_HAL_LED_2);
  
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
    timer_fired++;
    ActivateTask(Task1);
  }
  DemoHAL_TimerAck();
}

/*
 * Handle button interrupts activates Task2.
 */
ISR2(ButtonsISR)
{
  /* count the number of button presses */
  button_fired++;
  DemoHAL_ButtonInterruptAck(DEMO_HAL_BUTTON_0);
  ActivateTask(Task2);  
}

/* 
 * The StartupHook in this case is used to initialize the Button and timer
 * interrupts
 */
void StartupHook(void)
{
  DemoHAL_ButtonInit();
  DemoHAL_ButtonInterruptEnable(DEMO_HAL_BUTTON_0);
  DemoHAL_TimerInit(HAL_TIMER_MS);
}

void idle_hook ( void ) {
  DemoHAL_MainFunction();
}

int main()
{ 
  DemoHAL_Init();

#if (defined(OSEE_API_DYNAMIC))
  InitOS();
  
  CreateTask( &Task1, OSEE_TASK_TYPE_EXTENDED, TASK_FUNC(Task1),
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

  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);
  
  return 0;
}
