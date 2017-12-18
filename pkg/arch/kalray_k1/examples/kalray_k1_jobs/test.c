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

/*
 * test_job.c
 *
 *  Created on: Jan 22, 2015
 *      Author: e.guidieri
 */

#define ASSERT_LENGTH 70U
#include "ee_internal.h"
#include <stdio.h>
#include <stdarg.h>

#define JOB_TASK_STACK_SIZE 2048

#define ASSERT_LENGTH 70U
EE_TYPEASSERTVALUE EE_assertions[ASSERT_LENGTH];


#define ASSERT_LENGTH 70U
OsEE_spin_lock     assertions_lock;

int volatile assert_count = EE_ASSERT_NIL;
void test_assert(int test)
{
  register int next_assert;
  osEE_hal_spin_lock(&assertions_lock);
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
  osEE_hal_spin_unlock(&assertions_lock);
}
OsEE_reg dummy_job_param;

#define OSENABLE_PRINTF
#define OSENABLE_LOCKED_PRINTF
#if defined(OSENABLE_PRINTF)
#if defined(OSENABLE_LOCKED_PRINTF)
OsEE_spin_lock    print_lock;

#define locked_printf(fmt, ...)         \
  do {                                  \
     osEE_hal_spin_lock(&print_lock);   \
     printf(fmt, __VA_ARGS__);          \
     osEE_hal_spin_unlock(&print_lock); \
  } while ( 0 )
#else
#define locked_printf printf
#endif /* ENABLE_LOCKED_PRINTF */
#else
#define locked_printf(fmt, ...) ((void)0)
#endif /* ENABLE_PRINTF */

BlockableValueType comm_variables[(OSEE_K1_CORE_NUMBER - 1U)];

typedef struct {
  SpinlockObjType  lock;
  CoreIdType       core_ids[OSEE_K1_CORE_NUMBER];
  ValueType        counter;
} core_stamps_t;
core_stamps_t core_stamps;
core_stamps_t core_stamps_end;

void dummy_job ( JobTaskParam param ) {
  OsEE_TDB * const volatile p_curr    = osEE_get_curr_task();
  volatile unsigned int tid           = p_curr->tid;
  volatile unsigned int orig_core_id  = p_curr->orig_core_id;

  test_assert( &dummy_job_param == param );

  if ( orig_core_id != (OSEE_K1_CORE_NUMBER - 1U) ) {
    BlockableValueTypeRef p_blockable_var = &comm_variables[orig_core_id];
    locked_printf(
      "Before First Wait Task[%p]:\ttid:%u orig_core_id:%u curr_core_id:%u\n---\n",
      p_curr, tid, orig_core_id, (unsigned int)osEE_get_curr_core_id());
    WaitCondition(p_blockable_var, VALUE_EQ, (orig_core_id + 1U),
      BLOCK_IMMEDIATLY);
    test_assert(p_blockable_var->value == (orig_core_id + 1U));
    locked_printf(
      "After First Wait Task[%p]:\ttid:%u orig_core_id:%u curr_core_id:%u\n---\n",
      p_curr, tid, orig_core_id, (unsigned int)osEE_get_curr_core_id());
  }

  SpinLockObj(&core_stamps.lock);
  locked_printf(
    "Before First Signal Task[%p]:\ttid:%u orig_core_id:%u curr_core_id:%u\n---\n",
    p_curr, tid, orig_core_id, (unsigned int)osEE_get_curr_core_id());
  core_stamps.core_ids[core_stamps.counter++] = orig_core_id;
  SpinUnlockObj(&core_stamps.lock);

  if ( orig_core_id != OSEE_K1_MAIN_CORE ) {
    CoreIdType            const to_be_signal_id = (orig_core_id - 1U);
    BlockableValueTypeRef const p_signal_var    = &comm_variables[to_be_signal_id];
    SignalValue(p_signal_var, orig_core_id);
    locked_printf(
      "Before second Wait Task[%p]:\ttid:%u orig_core_id:%u curr_core_id:%u\n---\n",
      p_curr, tid, orig_core_id, (unsigned int)osEE_get_curr_core_id());
    WaitCondition(p_signal_var, VALUE_EQ, to_be_signal_id, BLOCK_IMMEDIATLY);
  }

  SpinLockObj(&core_stamps_end.lock);
  locked_printf(
    "After second Wait Task[%p]:\ttid:%u orig_core_id:%u curr_core_id:%u\n---\n",
     p_curr, tid, orig_core_id, (unsigned int)osEE_get_curr_core_id());
  core_stamps_end.core_ids[core_stamps_end.counter++] = orig_core_id;
  SpinUnlockObj(&core_stamps_end.lock);

  if ( orig_core_id != (OSEE_K1_CORE_NUMBER - 1U) ) {
    locked_printf(
      "Before second Signal Task[%p]:\ttid:%u orig_core_id:%u curr_core_id:%u\n---\n",
       p_curr, tid, orig_core_id, (unsigned int)osEE_get_curr_core_id());
    SignalValue(&comm_variables[orig_core_id], orig_core_id);
  }
}

int main ( void ) {
  StatusType    status_type = E_OK;
  JobType       jobId;
  size_t        i;
  OsEE_stack *  sp;

  osEE_hal_spin_init_lock(&assertions_lock);
  osEE_hal_spin_init_lock(&core_stamps.lock);
  osEE_hal_spin_init_lock(&core_stamps_end.lock);
#if (defined(OSENABLE_LOCKED_PRINTF))
  osEE_hal_spin_init_lock(&print_lock);
#endif

  for ( i = 0U; i < (OSEE_K1_CORE_NUMBER - 1U); ++i ) {
    InitBlockableValue(&comm_variables[i], 0U);
  }
  status_type = CreateJob(&jobId, 0xFFFFU, 1U, dummy_job,
    &dummy_job_param, JOB_TASK_STACK_SIZE );
  test_assert( status_type == E_OK );

  sp = osEE_get_SP();
  status_type = ActivateJob(jobId, 0xFFFFU);

  test_assert( sp == osEE_get_SP() );
  test_assert( status_type == E_OK );

  status_type = JoinJob(jobId);

  test_assert( sp == osEE_get_SP() );

  test_assert( status_type == E_OK );

  {
    osEE_k1_rmb();
    for ( i = 0U; i < (OSEE_K1_CORE_NUMBER - 1U); ++i ) {
      test_assert (core_stamps.core_ids[i] == ((OSEE_K1_CORE_NUMBER - 1U) - i));
      test_assert (core_stamps_end.core_ids[i] == i);
    }
  }

  EE_assert_range(0, 1, assert_count);

  if ( EE_assert_last() == EE_ASSERT_YES ) {
    printf("Job Test -- Passed\n");
  } else {
    printf("Job Test -- FAILED !!!\n");
  }

  /*
  while ( EE_TRUE ) {
    ;
  }
  */
  return 0;
}

