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

/** \file   code.c
 *  \brief  Full Test application.
 *
 *  This file contains the code of main application for Erika Enterprise.
 *
 *  \author Errico Gudieri
 *  \date   2017
 */
#include <mach.h>
#include "ee_internal.h"
#include "ee_assert.h"
#include <inmate.h>

/*
 * TASK AND ISR2 MUST BE C SYMBOL
 */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK1_POST,
  EE_ASSERT_TASK2_ENDED,
  EE_ASSERT_TASK1_ENDED,
  EE_ASSERT_TASK3_NOT_FIRED,
  EE_ASSERT_TASK3_FIRED,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(Task3);
DeclareTask(Task4);
DeclareTask(Task5);

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

/* Task IDs */
TaskType task1_id;
TaskType task2_id;
TaskType task3_id;
TaskType task4_id;
TaskType task5_id;
TaskType isr2_clock_id;

/* This semaphore is initialized inside the Background Task */
extern SemType V;

#define OSEE_BREAK_POINT()  do {                            \
    printk("Test Failed!!!, line:" OSEE_S(__LINE__) "\n");  \
  } while ( 0 )


#define BEATS_PER_SEC		10

static u64 ticks_per_beat;
static volatile u64 expected_ticks;

void clock_handler(void);
void clock_handler(void) {
  static u64 min_delta = ~0ULL, max_delta = 0;
  u64 delta;


  delta = osEE_aarch64_gtimer_get_ticks() - expected_ticks;
  if (delta < min_delta) {
    min_delta = delta;
  }
  if (delta > max_delta) {
    max_delta = delta;
  }

  printk("ISR | Timer fired, jitter: %6ld ns, min: %6ld ns, max: %6ld ns\n",
         (long)timer_ticks_to_ns(delta),
         (long)timer_ticks_to_ns(min_delta),
         (long)timer_ticks_to_ns(max_delta));

  ++isr2_fired;

  if ( !isr2_armed  ) {
    printk("ISR   | Before | Activate TASK1\n");
    ActivateTask(task1_id);
    printk("ISR   | After  | TASK1 activation\n");

  } else {
    isr2_armed = 0U;
  }

  expected_ticks = osEE_aarch64_gtimer_get_ticks() + ticks_per_beat;
  osEE_aarch64_gtimer_start(ticks_per_beat, OSEE_AARCH64_GTIMER_COUNTDOWN);
  return;
}

void idle_hook(void);
void idle_hook(void) {
  OsEE_addr volatile curr_sp, curr_sp_after;

  printk("MAIN | After  | We are in Idle LOOP\n");
  printk("MAIN | After  | Interrupt Enabled? (0=No)<%d>, PMR:<%x>",
    osEE_hal_is_enabledIRQ(), osEE_gicc_read_pmr());

  EE_assert(EE_ASSERT_INIT, OSEE_TRUE, EE_ASSERT_NIL);

  curr_sp = osEE_get_SP();
  printk("MAIN | BEFORE | TASK1 Activation Stack Pointer:<%p>\n", curr_sp);
  printk("MAIN | BEFORE | main SCB TOS:<%p>\n", osEE_get_curr_task()->hdb.p_scb->p_tos);
  ActivateTask(task1_id);
  curr_sp_after = osEE_get_SP();
  printk("MAIN | AFTER | TASK1 Returned Stack Pointer:<%p>\n", curr_sp_after);
  printk("MAIN | AFTER | main SCB TOS:<%p>\n", osEE_get_curr_task()->hdb.p_scb->p_tos);

  if ( curr_sp != curr_sp_after ) {
    OSEE_BREAK_POINT();
  }

  EE_assert(
    EE_ASSERT_TASKS_ENDED,
    task1_ended && task2_ended && task3_ended,
    EE_ASSERT_TASK3_FIRED
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASKS_ENDED);
  result = EE_assert_last();

  if (result == EE_ASSERT_YES) {
    printk("MAIN | TEST SUCCESS!!!\n");
  } else {
    printk("MAIN | TEST FAILED!!!\n");
  }

  /* Enable generate periodic TASK activation */
  printk("MAIN | Initializing the timer...\n");
  ticks_per_beat = osEE_aarch64_gtimer_get_freq();
  printk("gtimer freq: %ld   BEATS_PER_SEC=%ld\n", ticks_per_beat, BEATS_PER_SEC);
  ticks_per_beat /= BEATS_PER_SEC;
  expected_ticks = osEE_aarch64_gtimer_get_ticks() + ticks_per_beat;

  osEE_aarch64_gtimer_start(ticks_per_beat, OSEE_AARCH64_GTIMER_COUNTDOWN);

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {
    curr_sp = osEE_get_SP();
    if ( curr_sp != curr_sp_after ) {
      OSEE_BREAK_POINT();
    }

    if (main_sp == 0) {
      main_sp = curr_sp;
    } else if (main_sp != curr_sp) {
      OSEE_BREAK_POINT();
    }
    printk("MAIN | Before | WFI: Interrupt Enabled? (0=No)<%d>, PMR:<%x>\n",
      osEE_hal_is_enabledIRQ(), osEE_gicc_read_pmr());
    __asm__ volatile ("wfi" : : : "memory");
    printk("MAIN | After  | Retuned from ISR. Interrupt Enabled? (0=No)<%d>, PMR:<%x>\n",
      osEE_hal_is_enabledIRQ(), osEE_gicc_read_pmr());
  }
}

int main(void)
{
#if (defined(OSEE_API_DYNAMIC))
  StatusType s = E_OK;

  s |= CreateTask( &task1_id, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task1),
      1U, 1U, 1U, 1024 );
  s |= CreateTask( &task2_id, OSEE_TASK_TYPE_EXTENDED, TASK_FUNC(Task2),
      2U, 2U, 1U, 1024 );
  s |= CreateTask( &isr2_clock_id, OSEE_TASK_TYPE_ISR2, clock_handler,
      1U, 1U, 1U, OSEE_SYSTEM_STACK );
  s |= CreateTask( &task3_id, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task3),
      1U, 1U, 1U, OSEE_SYSTEM_STACK );
  s |= CreateTask( &task4_id, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task4),
      1U, 1U, 1U, OSEE_SYSTEM_STACK );
  s |= CreateTask( &task5_id, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task5),
      2U, 2U, 1U, OSEE_SYSTEM_STACK );

  printk("All TASKs created with result (0 is OK):%d\n", s);

  /* Tie ISR2 With IRQ */
  s = SetISR2Source(isr2_clock_id, OSEE_GTIMER_IRQ);

  printk ("ISRs created and tied with TIMER_IRQ. "
          "TIMER IRQ Is Enabled:<%d><%x>; Priority:<%d><%x>; IGROUP:<%d> "
          "after SetISR2Source, Result (0 is OK):%d\n",
          osEE_gic_v2_is_enabled_irq(OSEE_GTIMER_IRQ),
          osEE_gic_v2_read_isenabler(OSEE_GTIMER_IRQ),
          osEE_gic_v2_read_virt_prio_isr(OSEE_GTIMER_IRQ),
          osEE_gic_v2_read_hw_prio_isr(OSEE_GTIMER_IRQ),
          osEE_gicd_get_igroupr(OSEE_GTIMER_IRQ),
          s
  );

  /* Initialization of the second semaphore of the example;
   * the first semaphore is initialized inside the definition */
  InitSem(&V, 0);
#endif /* OSEE_API_DYNAMIC */

  printk("MAIN | Before | Call StartOS\n");
  printk("MAIN | Before | Interrupt Enabled? (0=No)<%d>, PMR:<%x>\n",
    osEE_hal_is_enabledIRQ(), osEE_gicc_read_pmr());
  StartOS(OSDEFAULTAPPMODE);

  printk("MAIN | Returned from application main\n");
  return 0;
}


/*
 * TASK 1
 */
TASK(Task1)
{
  OsEE_addr curr_sp;

  printk("TASK1\n");

  task1_fired++;
  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_FIRED, OSEE_TRUE, EE_ASSERT_INIT);
  } else {
    isr2_armed = 1U;
  }

  curr_sp = osEE_get_SP();
  if ( task1_sp == 0 ) {
    task1_sp = curr_sp;
  } else if ( task1_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }
  printk("TASK1 | Before | SCB TOS:<%p>\n", osEE_get_curr_task()->hdb.p_scb->p_tos);
  printk("TASK1 | Before | Stack Pointer:<%p>\n", osEE_get_SP());
  printk("TASK1 | Before | TASK2 Activation\n");
  ActivateTask(task2_id);
  printk("TASK1 | After  | Resuming from preemption\n");
  printk("TASK1 | After  | SCB TOS:<%p>\n", osEE_get_curr_task()->hdb.p_scb->p_tos);
  printk("TASK1 | After  | Stack Pointer:<%p>\n", osEE_get_SP());

  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_POST, OSEE_TRUE, EE_ASSERT_TASK2_FIRED);
  }

  printk("TASK1 | Before | Post Semaphore for TASK2\n");
  PostSem(&V);
  printk("TASK1 | After  | Resuming from preemption\n");
  printk("TASK1 | After  | SCB TOS:<%p>\n", osEE_get_curr_task()->hdb.p_scb->p_tos);
  printk("TASK1 | After  | Stack Pointer:<%p>\n", osEE_get_SP());

  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_ENDED, OSEE_TRUE, EE_ASSERT_TASK2_ENDED);
    EE_assert(EE_ASSERT_TASK3_NOT_FIRED, task3_fired == 0, EE_ASSERT_TASK1_ENDED);
  } else {
    printk("TASK1 | Before | Wait for release from ISR\n");
    printk("TASK1 | Before | Interrupt Enabled? (0=No)<%d>\n, PMR:<%x>\n",
      osEE_hal_is_enabledIRQ(), osEE_gicc_read_pmr());
    while ( isr2_armed ) {
      ; /* Wait ISR2 release */
    }
    printk("TASK1 | After  | Released by ISR\n");
  }
  curr_sp = osEE_get_SP();
  if ( task1_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }
  task1_ended++;
  TerminateTask();
}

/*
 * TASK 2
 */
TASK(Task2)
{
  OsEE_addr  curr_sp;
  printk("TASK2\n");

  curr_sp = osEE_get_SP();
  if ( task2_sp == 0 ) {
    task2_sp = curr_sp;
  } else if ( task2_sp != curr_sp ) {
    OSEE_BREAK_POINT();
  }

  task2_fired++;
  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_FIRED, OSEE_TRUE, EE_ASSERT_TASK1_FIRED);
  }

  printk("TASK2 | Before | SCB TOS:<%p>\n", osEE_get_curr_task()->hdb.p_scb->p_tos);
  printk("TASK2 | Before | Stack Pointer:<%p>\n", osEE_get_SP());
  printk("TASK2 | Before | Wait on Semaphore\n");
  WaitSem(&V);
  printk("TASK2 | After  | Resuming From Wait\n");
  printk("TASK2 | After  | SCB TOS:<%p>\n", osEE_get_curr_task()->hdb.p_scb->p_tos);
  printk("TASK2 | After  | Stack Pointer:<%p>\n", osEE_get_SP());

  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_ENDED, OSEE_TRUE, EE_ASSERT_TASK1_POST);
  }
  printk("TASK2 | Before | Activating TASK3\n");
  ActivateTask(task3_id);
  task2_ended++;
  printk("TASK2 Terminated\n");
}

TASK(Task3) {
  OsEE_addr  curr_sp;
  printk("TASK3\n");
  curr_sp = osEE_get_SP();
  if ( task3_fired > 1 ) {
    if ( task3_sp == 0 ) {
      task3_sp = curr_sp;
    } else if ( task3_sp != curr_sp ) {
      OSEE_BREAK_POINT();
    }
  }
  ++task3_fired;
  printk("TASK3 | Before | Activating TASK4\n");
  printk("TASK3 | Before | SCB TOS:<%p>\n", osEE_get_curr_task()->hdb.p_scb->p_tos);
  printk("TASK3 | Before | Stack Pointer:<%p>\n", osEE_get_SP());
  ActivateTask(task4_id);
  if (task3_fired == 1) {
    EE_assert(EE_ASSERT_TASK3_FIRED, OSEE_TRUE, EE_ASSERT_TASK3_NOT_FIRED);
  }
  ++task3_ended;
  printk("TASK3 Termination\n");
}

TASK(Task4) {
  OsEE_addr  curr_sp;
  printk("TASK4\n");
  curr_sp = osEE_get_SP();
  if ( task4_fired > 1 ) {
    if ( task4_sp == 0 ) {
      task4_sp = curr_sp;
    } else if ( task4_sp != curr_sp ) {
      OSEE_BREAK_POINT();
    }
  }
  ++task4_fired;
  printk("TASK4 | Before | Activating TASK5\n");
  printk("TASK4 | Before | SCB TOS:<%p>\n", osEE_get_curr_task()->hdb.p_scb->p_tos);
  printk("TASK4 | Before | Stack Pointer:<%p>\n", osEE_get_SP());
  ActivateTask(task5_id);
  printk("TASK4 | After  | Resuming After Preemption\n");
  printk("TASK4 | After  | SCB TOS:<%p>\n", osEE_get_curr_task()->hdb.p_scb->p_tos);
  printk("TASK4 | After  | Stack Pointer:<%p>\n", osEE_get_SP());
  if ( task4_fired > 1 ) {
    curr_sp = osEE_get_SP();
    if ( task4_sp != curr_sp ) {
      OSEE_BREAK_POINT();
    }
  }
  printk("TASK4 Termination\n");
}

TASK(Task5) {
  OsEE_addr  curr_sp;
  printk("TASK5\n");
  curr_sp = osEE_get_SP();
  printk("TASK5 SCB TOS:<%p>\n", osEE_get_curr_task()->hdb.p_scb->p_tos);
  printk("TASK5 Stack Pointer:<%p>\n", osEE_get_SP());
  if ( task5_fired > 1 ) {
    if ( task5_sp == 0 ) {
      task5_sp = curr_sp;
    } else if ( task5_sp != curr_sp ) {
      OSEE_BREAK_POINT();
    }
  }
  ++task5_fired;
  printk("TASK5 Termination\n");
}

