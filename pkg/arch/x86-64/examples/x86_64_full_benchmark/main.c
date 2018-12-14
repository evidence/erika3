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
 *  \brief	Tasks for benchmark.
 *
 *  \author	Errico Guidieri
 *  \date	2018
 */

/*********************************
 * Generic OS Benchmark - TESTS
 **********************************/

#include "ee.h"
#include "test.h"
#include "hal.h"

/* Supported tests: */
#include "tests/act.h"
#include "tests/actl.h"
#include "tests/intdisable.h"
#include "tests/intenable.h"
#include "tests/isr2entry.h"
#include "tests/isrentry.h"
#include "tests/isrexit.h"
#include "tests/istentry.h"
#include "tests/istexit.h"
#include "tests/terml.h"

static volatile OSEE_TICK_TYPE start_time;

static inline void perf_start_measure( void )
{
  	start_time = DemoHAL_TimerGetValue();
  	OSEE_BARRIER();
}

/* Common code to update the values of the measures. */
static inline void perf_stop_measure(struct test *data, uint32_t n)
{
  	const OSEE_TICK_TYPE end_time = DemoHAL_TimerGetValue();
  	DemoHAL_DataBarrier();
	if (end_time < start_time) {
		DEMOHAL_PRINTF("ERROR: wrap around detected!\n");
	} else {
		OSEE_TICK_TYPE sample = end_time - start_time;
		data->sum += sample;

  		if(sample > data->max) {
    			data->max = sample;
  		}

  		if((sample < data->min) || (data->min == 0U)) {
    			data->min = sample;
  		}
	}
}

#define PERF_ENABLE(name)  { 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0},
static struct test alltests[] = {
#include "tests_list.h"
	{ 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0}
};
#undef PERF_ENABLE

#define PERF_ENABLE(name) {               \
  	alltests[i].setup = name ## _setup;     \
  	alltests[i].main = name ## _main;       \
  	alltests[i].task1 = name ## _task1;     \
  	alltests[i].task3 = name ## _task3;     \
  	alltests[i].task4 = name ## _task4;     \
  	alltests[i].cleanup = name ## _cleanup; \
	alltests[i].sum = 0U;                   \
  	alltests[i].max  = 0U;                   \
  	alltests[i].min  = 0U;                   \
  	alltests[i].test_name  = #name;          \
  	i++; }

volatile unsigned alltest_size;

static void perf_init(void)
{
  	int i = 0;

#include "tests_list.h"
  	/* just to be sure to end the test suite */
  	alltests[i].main = 0;
  	alltest_size = i;
}
#undef PERF_ENABLE

/* Common code to run the tests, to be used in code.c */
static void perf_run_all(void)
{
  	struct test *tst;

  	current = 0;
  	tst = &alltests[0];

  	do {
    		tst->setup(tst);
    		tst->main(tst);
    		tst->cleanup(tst);

    		tst = &alltests[++current];
  	} while (tst->main);
}

void perf_finalize(struct test *data)
{
	/*
 	 * Put here any code that must be executed by all tests
	 *  once the test is finished.
	 */
}


static void perf_final_results ( void )
{
	/*
 	 * Put here any code to be executed once the test suite
	 * has finished execution (e.g. to normalize data).
	 */
  	int i = 0;
	for (i = 0; i < alltest_size; ++i) {
		DEMOHAL_PRINTF("%s:\t\t Min = %lu\t\t Avg = %lu\t\t Max = %lu\n",
			alltests[i].test_name,
			alltests[i].min,
			alltests[i].sum/PERF_LOOPS,
			alltests[i].max);
	}
}

ISR2(isrentry_isr2)
{
  	static int i = 0;

  	perf_stop_measure(curdata, ++i);
}

ISR2(istentry_isr2)
{
  	ActivateTask(Task3);
  	perf_start_measure();
}

ISR2(istexit_isr2)
{
  	ActivateTask(Task3);
}

ISR1(isrentry_isr1)
{
  	static int i = 0;

  	perf_stop_measure(curdata, ++i);
}

ISR1(isrexit_isr1)
{
  	perf_start_measure();
}


TASK(Task1)
{
  	perf_run_task(1);
  	TerminateTask();
}

TASK(Task3)
{
  	perf_run_task(3);
  	TerminateTask();
}

TASK(Task4)
{
  	perf_run_task(4);
  	TerminateTask();
}

TASK(MainTask)
{
	DemoHAL_ISRInit();
	DemoHAL_TimerInit(1U);
  	perf_init();
  	perf_run_all();
  	perf_final_results();
}


int main( void )
{
	// Temporary fix for ISR1s in x86 until the code generator will
	// properly handle this.
	set_interrupt_handler(0x22, isrentry_isr1);
	set_interrupt_handler(0x23, isrexit_isr1);

  	StartOS(OSDEFAULTAPPMODE);
  	return 0;
}
