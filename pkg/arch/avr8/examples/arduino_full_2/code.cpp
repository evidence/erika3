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
 *  \author	Errico Guidieri
 *  \date  	2017
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

/*
 * TASK AND ISR2 MUST BE C SYMBOL
 */
extern "C" {

/* TASKs */
DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(Task3);
DeclareTask(Task4);
DeclareTask(Task5);
DeclareIsr2(clock_handler);

/* Idle Hook */
extern void idle_hook ( void );
extern void free_task1 (void);

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
OsEE_addr volatile task3_sp;
OsEE_addr volatile task4_sp;
OsEE_addr volatile task5_sp;
OsEE_addr volatile main_sp;

#if (defined(OSEE_API_DYNAMIC))
TaskType Task1;
TaskType Task2;
TaskType Task3;
TaskType Task4;
TaskType Task5;
TaskType isr2_clock_id;
#endif /* OSEE_API_DYNAMIC */

extern SemType V;

void StartupHook(void)
{

}

} /* extern "C" */

void serial_print(char const * msg) {
  cli();
  Serial.write(msg, strlen(msg));
/*  if (serialEventRun) {
    serialEventRun();
  } */
  sei();
}

#if 0
void print_sp(TaskType tid, OsEE_addr sp) {
  static char msg[] = "TASK n SP<0xXXXX>\r\n  ";
  cli();
  sprintf(msg, "TASK %d SP<%p>\r\n", tid, sp);
  sei();
  serial_print(msg);
}
#endif

#define OSEE_BREAK_POINT()  do {                                    \
    digitalWrite(led, HIGH);                                        \
    cli();                                                          \
    serial_print("Test Failed!!!, line:" OSEE_S(__LINE__) " \r\n"); \
    while ( 1 ) {                                                   \
      if (serialEventRun) serialEventRun();                         \
    }                                                               \
  } while ( 0 )

void setup(void)
{
  /* initialize the digital pin as an output. */
  pinMode(led, OUTPUT);

  Serial.begin(115200);
}

void free_task1(void) {
  led_val = (led_val == LOW)? HIGH: LOW;
  digitalWrite(led, led_val);
  isr2_armed  = 0;
}

void idle_hook ( void ) {
  uint32_t counter = 0;
  OsEE_addr volatile curr_sp = osEE_get_SP();

  if ( main_sp == 0 ) {
    main_sp = curr_sp;
  } else if ( main_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }

  cli();
  if (serialEventRun) {
    serialEventRun();
  }
  sei();
  counter++;

}

int main(void)
{
  init();

  setup();

#if defined(USBCON)
  USBDevice.attach();
#endif

#if (defined(OSEE_API_DYNAMIC))
  CreateTask( &Task1, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task1),
      1U, 1U, 1U, 128 );
  CreateTask( &Task2, OSEE_TASK_TYPE_EXTENDED, TASK_FUNC(Task2),
      2U, 2U, 1U, 128 );
  CreateTask( &Task3, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task3),
      1U, 1U, 1U, OSEE_SYSTEM_STACK );
  CreateTask( &isr2_clock_id, OSEE_TASK_TYPE_ISR2, clock_handler,
      1U, 1U, 1U, OSEE_SYSTEM_STACK );
  CreateTask( &Task4, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task4),
      1U, 1U, 1U, OSEE_SYSTEM_STACK );
  CreateTask( &Task5, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task5),
      2U, 2U, 1U, OSEE_SYSTEM_STACK );

  /* Prio settate a 1 dalla BSP all'avvio */
  SetISR2Source(isr2_clock_id, OSEE_AVR8_TIMER1_COMPA_ISR_ID);

  InitSem(&V, 0);

  SetIdleHook(idle_hook);
#endif /* OSEE_API_DYNAMIC */

  StartOS(OSDEFAULTAPPMODE);

  return 0;
}

/*
 * TASK 1
 */
TASK(Task1)
{
  OsEE_addr curr_sp;

  serial_print("1\r\n");

  task1_fired++;

  isr2_armed = 1U;

  curr_sp = osEE_get_SP();
  if ( task1_sp == 0 ) {
    task1_sp = curr_sp;
  } else if ( task1_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }

  ActivateTask(Task2);

  PostSem(&V);

  while (isr2_armed) {
    ; /* Wait ISR2 release */
  }
  serial_print("R1\r\n");

  curr_sp = osEE_get_SP();
  if ( task1_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }

  task1_ended++;
}

/*
 * TASK 2
 */
TASK(Task2)
{
  OsEE_addr  curr_sp;
  serial_print("2\r\n");
  curr_sp = osEE_get_SP();
  if ( task2_sp == 0 ) {
    task2_sp = curr_sp;
  } else if ( task2_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }

  task2_fired++;

  WaitSem(&V);

  ActivateTask(Task3);
  task2_ended++;
}

TASK(Task3) {
  serial_print("3\r\n");

  ++task3_fired;

  ActivateTask(Task4);

  ++task3_ended;
}

TASK(Task4) {
  serial_print("4\r\n");

  ++task4_fired;
  ActivateTask(Task5);

}

TASK(Task5) {
  serial_print("5\r\n");

  ++task5_fired;
}

