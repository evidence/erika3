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
 *  \author	Paolo Gai
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* ERIKA Enterprise. */
#include "ee.h"

/* HAL */
#include "hal.h"

#define	HAL_TIMER_MS	1U

#define	HAL_DELAY_MS	250U

#define	IDLE_CNT_MAX	100000U

#define	IDLE_STR	(uint8_t const *)"Idle\r\n"
#define	IDLE_STR_LEN	6U
#define	ISR_STR		(uint8_t const *)"ISR\r\n"
#define	ISR_STR_LEN	5U

#define	WC_STR		(uint8_t const *)"I love EE3!\r\n"
#define	WC_STR_LEN	14U

#define	TMR_STR		(uint8_t const *)"\r\nTmr: "
#define	TMR_STR_LEN	7U

#define	BTN_STR		(uint8_t const *)"\r\nBtn: "
#define	BTN_STR_LEN	7U

#define	TASK1_STR	(uint8_t const *)"\r\nTask1: "
#define	TASK1_STR_LEN	9U

#define	TASK2_STR	(uint8_t const *)"\r\nTask2: "
#define	TASK2_STR_LEN	9U

/* A few counters incremented at each event
 * (alarm, button press or task activation...)
 */
volatile uint16_t timer_fired;
volatile uint16_t button_fired;
volatile uint16_t task1_fired;
volatile uint16_t task2_fired;

/* prints a report
 * Note: after the first printf in main(), only one task uses printf
 * In this way we avoid raceconditions in the usage of stdout.
 */
void printchar(char c)
{
  uint8_t volatile ch[2U];
  ch[0U] = c;
  DemoHAL_SerialWrite((uint8_t const *)ch, 1U);
}

void print_report(void) {
  DemoHAL_SerialWrite(TMR_STR, TMR_STR_LEN);
  printchar(((timer_fired%1000)/100)+'0');
  printchar(((timer_fired%100)/10)+'0');
  printchar((timer_fired%10)+'0');

  DemoHAL_SerialWrite(TASK1_STR, TASK1_STR_LEN);
  printchar(((task1_fired%1000)/100)+'0');
  printchar(((task1_fired%100)/10)+'0');
  printchar((task1_fired%10)+'0');

  DemoHAL_SerialWrite(BTN_STR, BTN_STR_LEN);
  printchar(((button_fired%1000)/100)+'0');
  printchar(((button_fired%100)/10)+'0');
  printchar((button_fired%10)+'0');

  DemoHAL_SerialWrite(TASK2_STR, TASK2_STR_LEN);
  printchar(((task2_fired%1000)/100)+'0');
  printchar(((task2_fired%100)/10)+'0');
  printchar((task2_fired%10)+'0');
}

/* Let's remember the led status! 
 * Mutual exclusion on this variable is not included in the demo to make it
 * not too complicated; in general shared variables should be protected using
 * GetResource/ReleaseResource calls
 */
volatile uint8_t led_status;

uint32_t volatile idle_cnt;
OsEE_addr volatile old_sp;

#if (defined(OSEE_API_DYNAMIC))
TaskType Task1;
TaskType Task2;
TaskType IsrTimerId;
TaskType IsrButtonsId;
#endif /* OSEE_API_DYNAMIC */

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged
 * 
 * Note: led_blink is called both from Task1 and Task2. To avoid race 
 * conditions, we forced the atomicity of the led manipulation using IRQ
 * enabling/disabling. We did not use Resources in this case because the 
 * critical section is -really- small. An example of critical section using 
 * resources can be found in the osek_resource example.
 */
void leds(uint8_t theled)
{
  DemoHAL_Led led;
  for ( led = DEMO_HAL_LED_0; led < DEMO_HAL_LED_NUM; led++)
  {
    if ( (theled & 0x01U) != 0x0U ) {
      DemoHAL_LedOn(led);
    }
    else {
      DemoHAL_LedOff(led);
    }
    theled >>= 0x01U;
  }
}

void led_blink(uint8_t theled)
{
  DisableAllInterrupts();
  led_status |= theled;
  leds(led_status);
  EnableAllInterrupts();

  DemoHAL_Delay(HAL_DELAY_MS);

  DisableAllInterrupts();
  led_status &= ~theled;
  leds(led_status);
  EnableAllInterrupts();
}

/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  task1_fired++;
  
  /* First half of the christmas tree */
  led_blink(0x01U);
  led_blink(0x02U);
  led_blink(0x04U);
  
  /* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
#ifdef MYSCHEDULE
  Schedule();
#endif

  /* Second half of the christmas tree */
  led_blink(0x08U);
  led_blink(0x10U);
  led_blink(0x20U);
  
  TerminateTask();
}


/* Task2: Print the counters on the UART */
TASK(Task2)
{
  static uint8_t which_led = 0U;
  /* count the number of Task2 activations */
  task2_fired++;

  /* let blink leds 6 or 7 */
  if (which_led) {
    led_blink(0x80U);
    which_led = 0U;
  }
  else {
    led_blink(0x40U);
    which_led = 1U;
  }

  /* prints a report
   * Note: after the first printf in main(), then only this task uses printf
   * In this way we avoid raceconditions in the usage of stdout.
   */
  
  
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

  /* just a nice subliminal welcome message :-) */
  DemoHAL_Delay(HAL_DELAY_MS);

  DemoHAL_SerialWrite(WC_STR, WC_STR_LEN);

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
