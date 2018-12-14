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

/** \file	test.h
 *  \brief	Header for code to run tests.
 *
 *  \author	Errico Guidieri, Claudio Scordino
 *  \date	2018
 */
#ifndef __TEST_H__
#define __TEST_H__

#include "ee.h"

#define PERF_LOOPS  100

/*
 * Each test has right to store its own results into a test structure.
 * All values expressed in ns.
 * Test descriptor:
 * - setup() is called when the execution of the single test begins;
 * - run() is called to execute the test, and is supposed to generate
 *   all the necessary events and to collect stats on them;
 * - cleanup() restores the initial condition.
 */
struct test {
  	const char *test_name;
  	void (*setup)(struct test *data);
  	void (*main)(struct test *data);
  	void (*task1)(struct test *data);
  	void (*task3)(struct test *data);
  	void (*task4)(struct test *data);
  	void (*cleanup)(struct test *data);
	OSEE_TICK_TYPE sum;
  	OSEE_TICK_TYPE max;
  	OSEE_TICK_TYPE min;
};

/* Common code to update the values of the measures. */
static inline void perf_start_measure( void );
static inline void perf_stop_measure(struct test *data, uint32_t n);
static void perf_init(void);
static void perf_finalize(struct test *data);


static struct test alltests[];
static int current;

#define curdata (&alltests[current])

/*
 * NOTE: The two dereferences add a constant offset to the measure: may
 * this be considered too much we should move the measure to the entry of
 * the task itself.
 */
#define perf_run_task(id) do {                  \
  	struct test *test = &alltests[current]; \
  	test->task ## id (test);                      \
} while (0)

#endif /* __TEST_H__ */
