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

/** \file	code.cpp
 *  \brief	Main application.
 *
 *  This file contains the code of main application for Erika Enterprise.
 *
 *  \author	Errico Guidieri
 *  \date  	2017
 */

/* ERIKA Enterprise. */
#include "ee.h"

#include "ee_tc2x5_board.h"

extern SemType V;

/* TASKs */
DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(Task3);
DeclareTask(Task4);
DeclareTask(Task5);
extern void clock_handler(void);
extern void idle_hook(void);

/* Counters */
OsEE_reg volatile task1_fired;
OsEE_reg volatile task2_fired;
OsEE_reg volatile task1_ended;
OsEE_reg volatile task2_ended;
OsEE_reg volatile task3_fired;
OsEE_reg volatile task3_ended;
OsEE_reg volatile task4_fired;
OsEE_reg volatile task5_fired;
OsEE_reg volatile isr2_fired;
OsEE_reg volatile isr2_armed;

/* Stack Pointers */
OsEE_addr volatile task1_sp;
OsEE_addr volatile task2_sp;
OsEE_addr volatile main_sp;

#define OSEE_BREAK_POINT()                        \
  while ( 1 ) {                                   \
    __asm__ volatile ("debug\n\t" : : : "memory");\
  }

ISR(clock_handler) {
  enum OsEE_tc2x5_led_status stat = OSEE_TRIBOARD_2X5_LED_OFF;

  osEE_tc_stm_set_sr0_next_match(1000U);

  ++isr2_fired;

  if (!isr2_armed) {
    ActivateTask(Task1);
    if ( stat == OSEE_TRIBOARD_2X5_LED_OFF ) {
      stat = OSEE_TRIBOARD_2X5_LED_ON;
    }
    else {
      stat = OSEE_TRIBOARD_2X5_LED_OFF;
    }
    osEE_tc2x5_turn_led(OSEE_TRIBOARD_2X5_LED_2, stat);
  } else {
    isr2_armed = 0U;
  }
}

/*
 * TASK 1
 */
TASK(Task1)
{
  OsEE_addr curr_sp;
  static enum OsEE_tc2x5_led_status stat = OSEE_TRIBOARD_2X5_LED_OFF;

  ++task1_fired;

  if (task1_fired != 1U) {
    isr2_armed = 1U;
  }

  curr_sp = osEE_get_SP();
  if (task1_sp == 0U) {
    task1_sp = curr_sp;
  } else if (task1_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }

  ActivateTask(Task2);

  PostSem(&V);

  if (task1_fired != 1U) {
#if	0
    while (isr2_armed) {
      ; /* Wait ISR2 release */
    }
#endif
  }

  curr_sp = osEE_get_SP();

  if (task1_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }

  ++task1_ended;

  if ( stat == OSEE_TRIBOARD_2X5_LED_OFF ) {
    stat = OSEE_TRIBOARD_2X5_LED_ON;
  }
  else {
    stat = OSEE_TRIBOARD_2X5_LED_OFF;
  }
  osEE_tc2x5_turn_led(OSEE_TRIBOARD_2X5_LED_3, stat);

  TerminateTask();
}

/*
 * TASK 2
 */
TASK(Task2)
{
  OsEE_addr  curr_sp;
  static enum OsEE_tc2x5_led_status stat = OSEE_TRIBOARD_2X5_LED_OFF;

  curr_sp = osEE_get_SP();

  if (task2_sp == NULL) {
    task2_sp = curr_sp;
  } else if ( task2_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }

  ++task2_fired;

  WaitSem(&V);

  ActivateTask(Task3);
  task2_ended++;

  if ( stat == OSEE_TRIBOARD_2X5_LED_OFF ) {
    stat = OSEE_TRIBOARD_2X5_LED_ON;
  }
  else {
    stat = OSEE_TRIBOARD_2X5_LED_OFF;
  }
  osEE_tc2x5_turn_led(OSEE_TRIBOARD_2X5_LED_4, stat);

  TerminateTask();
}

TASK(Task3) {
  static enum OsEE_tc2x5_led_status stat = OSEE_TRIBOARD_2X5_LED_OFF;

  ++task3_fired;
  ActivateTask(Task4);
  ++task3_ended;

  if ( stat == OSEE_TRIBOARD_2X5_LED_OFF ) {
    stat = OSEE_TRIBOARD_2X5_LED_ON;
  }
  else {
    stat = OSEE_TRIBOARD_2X5_LED_OFF;
  }
  osEE_tc2x5_turn_led(OSEE_TRIBOARD_2X5_LED_5, stat);

  TerminateTask();
}

TASK(Task4) {
  static enum OsEE_tc2x5_led_status stat = OSEE_TRIBOARD_2X5_LED_OFF;

  ++task4_fired;
  ActivateTask(Task5);

  if ( stat == OSEE_TRIBOARD_2X5_LED_OFF ) {
    stat = OSEE_TRIBOARD_2X5_LED_ON;
  }
  else {
    stat = OSEE_TRIBOARD_2X5_LED_OFF;
  }
  osEE_tc2x5_turn_led(OSEE_TRIBOARD_2X5_LED_6, stat);

  TerminateTask();
}

TASK(Task5) {
  static enum OsEE_tc2x5_led_status stat = OSEE_TRIBOARD_2X5_LED_OFF;

  if (task5_fired == 0U) {
    /* Configure the clock after the first iteration of TASKs */
    /* TODO */
  }
  ++task5_fired;

  if ( stat == OSEE_TRIBOARD_2X5_LED_OFF ) {
    stat = OSEE_TRIBOARD_2X5_LED_ON;
  }
  else {
    stat = OSEE_TRIBOARD_2X5_LED_OFF;
  }
  osEE_tc2x5_turn_led(OSEE_TRIBOARD_2X5_LED_6, stat);

  TerminateTask();
}

void idle_hook (void) {
  static uint32_t cnt = 0U;
  static enum OsEE_tc2x5_led_status stat = OSEE_TRIBOARD_2X5_LED_ON;
  OsEE_addr curr_sp;

#if (defined(OSEE_DEBUG))
  osEE_tc_stm_ocds_suspend_control(0U);
#endif /* OSEE_DEBUG */
  osEE_tc_stm_set_clockpersec();
  osEE_tc_stm_set_sr0(1000U, 1U);

  /* Forever loop: So I can check TASKs stacks */
  for (;;)
  {
    curr_sp = osEE_get_SP();

    if (main_sp == NULL) {
      main_sp = curr_sp;
    } else if (main_sp != curr_sp) {
      OSEE_BREAK_POINT();
    }

    if (++cnt > 1000000U) {
      cnt = 0U;
      if (stat == OSEE_TRIBOARD_2X5_LED_OFF) {
        stat = OSEE_TRIBOARD_2X5_LED_ON;
      }
      else {
        stat = OSEE_TRIBOARD_2X5_LED_OFF;
      }
      osEE_tc2x5_turn_led(OSEE_TRIBOARD_2X5_LED_1, stat);
    }
  }

  OSEE_BREAK_POINT();
}

/*
 * MAIN TASK
 */
int main(void)
{
  osEE_tc2x5_leds_init();

  StartOS(OSDEFAULTAPPMODE);

  return 0;
}

