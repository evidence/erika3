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

#define	HAL_DELAY_MS	250U

#define	IDLE_CNT_MAX	100000U

#define	IDLE_STR	(P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA))"Idle\r\n"
#define	IDLE_STR_LEN	6U
#define	ISR_STR		(P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA))"ISR\r\n"
#define	ISR_STR_LEN	5U

#define	WC_STR		(P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA))"I love EE3!\r\n"
#define	WC_STR_LEN	14U

uint32_t volatile idle_cnt;
OsEE_addr volatile old_sp;

/* TASKs */
DeclareTask(Task1);
DeclareTask(Task2);

/* EVENTs */
DeclareEvent(TimerEvent);
DeclareEvent(ButtonEvent);

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged. See also the osek_task example for a full explanation of the
 * function.
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

uint8_t volatile led_status;
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

TASK(Task1)
{
  EventMaskType mask;

  while (OSEE_TRUE) {
    WaitEvent(TimerEvent|ButtonEvent);
    GetEvent(Task1, &mask);

    if (mask & TimerEvent) {
      led_blink(0x01U);
      ClearEvent(TimerEvent);
    }

    if (mask & ButtonEvent) {
      led_blink(0x02U);
      ClearEvent(ButtonEvent);
    }
  }
  TerminateTask();
}

TASK(Task2)
{
  led_blink(0x04U);
  TerminateTask();
}


int myErrorCounter;
void ErrorHook(StatusType Error)
{
  (void)Error;
  myErrorCounter++;
  led_blink(0xFFU);
}

/*
 * Handle button interrupts activates Task2.
 */
ISR2(ButtonsISR)
{
  VAR(OsEE_bool, AUTOMATIC)	buttonstatus;
  
  DemoHAL_SerialWrite(ISR_STR, ISR_STR_LEN);
  
  buttonstatus = DemoHAL_ButtonRead(DEMO_HAL_BUTTON_0);

  /* check if the first button is pressed or not */
  if (buttonstatus) {
    /* the button is not pressed, do nothing */
  }
  else {
    /* the button is pressed */
    /* arm an alarm that will activated Task2 */ 
    SetRelAlarm(AlarmTask2, 1000U, 0U);

    /* set an event to wake up Task1 */
    SetEvent(Task1, ButtonEvent);
  }

  DemoHAL_ButtonInterruptAck(DEMO_HAL_BUTTON_0);
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
}

void idle_hook ( void ) {

  OsEE_addr volatile curr_sp = osEE_get_SP();

  if ( old_sp == 0U ) {
    old_sp = curr_sp;
  } else if ( old_sp != curr_sp ) {
    DemoHAL_LedOn(DEMO_HAL_LED_1);
    for(;;);
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

  DemoHAL_Init();

  StartOS(OSDEFAULTAPPMODE);

  return 0;
}
