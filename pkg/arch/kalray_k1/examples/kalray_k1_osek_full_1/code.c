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

#include "ee.h"

extern SemType V;

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

#if (defined(OSEE_API_DYNAMIC))
/* Task IDs */
TaskType Task1;
TaskType Task2;
TaskType Task3;
TaskType Task4;
TaskType Task5;
TaskType isr2_clock_id;
#endif /* OSEE_API_DYNAMIC */

#define CLOCK_FREQ         (__bsp_frequency/(_K1_DEFAULT_CLOCK_DIV + 1))
#define CLOCK_RELOAD_1_MS  OSEE_MILLI_TO_TICKS(1, CLOCK_FREQ)

static void configure_clock ( void ) {
#ifndef OSEE_TRACE_KERNEL
  mOS_timer_general_setup();
  mOS_timer_setup_num(0, CLOCK_RELOAD_1_MS, CLOCK_RELOAD_1_MS, OSEE_FALSE);
#endif /*OSEE_TRACE_KERNEL */
}

#ifdef OSEE_TRACE_KERNEL
static void throw_isr ( void )  {
  mppa_tracepoint(erika,THROW_ISR_ENTER);
  __k1_interrupt_set_num_fixed(EE_ISR_ID_TIMER0);
}
#else
#define throw_isr() ((void)0)
#endif /* OSEE_TRACE_KERNEL */

ISR(clock_handler) {
  ++isr2_fired;
  if (!isr2_armed) {
    ActivateTask(Task1);
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
#ifdef OSEE_TRACE_TASK
  mppa_tracepoint(erika,TASK1_ENTER);
#endif /* OSEE_TRACE_TASK */

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
    while (isr2_armed) {
#if (defined(OSEE_TRACE_KERNEL))
      throw_isr()
#endif
      ; /* Wait ISR2 release */
    }
  }

  curr_sp = osEE_get_SP();

  if (task1_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }

  ++task1_ended;

#ifdef OSEE_TRACE_TASK
  mppa_tracepoint(erika,TASK1_EXIT);
#endif /* OSEE_TRACE_TASK */

  TerminateTask();
}

/*
 * TASK 2
 */
TASK(Task2)
{
  OsEE_addr  curr_sp;
#ifdef OSEE_TRACE_TASK
  mppa_tracepoint(erika,TASK2_ENTER);
#endif /* OSEE_TRACE_TASK */

  curr_sp = osEE_get_SP();

  if (task2_sp == NULL) {
    task2_sp = curr_sp;
  } else if ( task2_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }

  ++task2_fired;

#ifdef OSEE_TRACE_TASK
  mppa_tracepoint(erika,TASK2_EXIT);
#endif /* OSEE_TRACE_TASK */
  WaitSem(&V);
#ifdef OSEE_TRACE_TASK
  mppa_tracepoint(erika,TASK2_ENTER);
#endif /* OSEE_TRACE_TASK */

  ActivateTask(Task3);
  task2_ended++;
#ifdef OSEE_TRACE_TASK
  mppa_tracepoint(erika,TASK2_EXIT);
#endif /* OSEE_TRACE_TASK */

  TerminateTask();
}

TASK(Task3) {
  ++task3_fired;
  ActivateTask(Task4);
  ++task3_ended;

  TerminateTask();
}

TASK(Task4) {
  ++task4_fired;
  ActivateTask(Task5);

  TerminateTask();
}

TASK(Task5) {
  if (task5_fired == 0U) {
    /* Configure the clock after the first iteration of TASKs */
    configure_clock();
  }
  ++task5_fired;

  TerminateTask();
}

void idle_hook (void) {
  OsEE_addr curr_sp_after;
  OsEE_addr curr_sp = osEE_get_SP();

  ActivateTask(Task1);

  curr_sp_after = osEE_get_SP();

  if (curr_sp != curr_sp_after) {
    OSEE_BREAK_POINT();
  }

  if (main_sp == 0) {
    main_sp = curr_sp;
  } else if (main_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }
}

/*
 * MAIN TASK
 */
int main(void)
{
#if (defined(OSEE_API_DYNAMIC))
  CreateTask(&Task1, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task1),
      1U, 1U, 1U, 1024);
  CreateTask(&Task2, OSEE_TASK_TYPE_EXTENDED, TASK_FUNC(Task2),
      2U, 2U, 1U, 1024);
  CreateTask(&Task3, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task3),
      1U, 1U, 1U, OSEE_SYSTEM_STACK);
  CreateTask(&isr2_clock_id, OSEE_TASK_TYPE_ISR2, clock_handler,
      1U, 1U, 1U, OSEE_SYSTEM_STACK);
  CreateTask(&Task4, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task4),
      1U, 1U, 1U, OSEE_SYSTEM_STACK);
  CreateTask(&Task5, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task5),
      2U, 2U, 1U, OSEE_SYSTEM_STACK);
  InitSem(&V, 0);

  SetISR2Source(isr2_clock_id, BSP_IT_TIMER_0);

  SetIdleHook(idle_hook);
#endif /* OSEE_API_DYNAMIC */

  StartOS(OSDEFAULTAPPMODE);

  return 0;
}

