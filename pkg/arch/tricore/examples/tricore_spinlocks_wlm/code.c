/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 - 2019 Evidence s.r.l.
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

#define ASSERT_LENGTH 60

#include "ee.h"

/*=============================================================================
                Services Requests Node (SRN) Utility Macros
 ============================================================================*/
#define TC_SRC_BASE                  (0xF0038000U)

#define TC_SRC_REG(off)\
  (*(OsEE_reg volatile *)(TC_SRC_BASE + (off)))

#define TC_SRN_ENABLE                ((OsEE_reg)1U << 10U)
#define TC_SRN_CLEAR_REQUEST         ((OsEE_reg)1U << 25U)
#define TC_SRN_SET_REQUEST           ((OsEE_reg)1U << 26U)
#define TC_SRN_STICKY_CLEAR          ((OsEE_reg)1U << 30U)

#if (!defined(OSEE_TC_2G))
#define GPSR_OFFSET     (0x1000U)
#define GPSR_MAX_CH     (3U)
#else
#define GPSR_OFFSET     (0x0990U)
#define GPSR_MAX_CH     (7U)
#endif /* !OSEE_TC_2G */

#define GPSR_GROUP_OFFSET(g)  (((g) & 0x3U) * 0x20U)

#define GPSR_SRC_OFFSET(g, n)\
  (GPSR_OFFSET + GPSR_GROUP_OFFSET(g) + \
    ((((OsEE_reg)(n) <= GPSR_MAX_CH)?\
        (OsEE_reg)(n):\
        (OsEE_reg)0U) * 0x4U))

/* Rise GPSR group1 interrupt */
static void fire_irq(unsigned int g, unsigned int ch) {
  TC_SRC_REG(GPSR_SRC_OFFSET(g, ch)) |= TC_SRN_SET_REQUEST;
  /* Read the register back, this should assure that the IRQ will raised */
  (void)TC_SRC_REG(GPSR_SRC_OFFSET(g, ch));
}

/* Ack GPSR group1 interrupt */
static void ack_irq(unsigned int g, unsigned int ch)
{
  TC_SRC_REG(GPSR_SRC_OFFSET(g, ch)) |=
    (TC_SRN_CLEAR_REQUEST | TC_SRN_STICKY_CLEAR);
}

#define IRQ_LOW     1U, 0U
#define IRQ_MEDIUM  1U, 1U
#define IRQ_HIGH    1U, 2U
#define IRQ_SLAVE   2U, 0U

StatusType last_error;
unsigned int volatile error_count;

unsigned int volatile task2_hit;
unsigned int volatile task3_hit;

unsigned int volatile low_isr_hit;
unsigned int volatile medium_isr_hit;
unsigned int volatile high_isr_hit;

#if (defined(__TASKING__))
#define API_START_SEC_VAR_CLEARED
#include "Os_MemMap.h"
#endif /* __TASKING__ */
unsigned int volatile task_slave_hit;
unsigned int volatile isr_slave_hit;

/* assertion data */
OSEE_TYPEASSERTVALUE osEE_assertions[ASSERT_LENGTH];

#if (defined(__TASKING__))
#define API_STOP_SEC_VAR_CLEARED
#include "Os_MemMap.h"
#endif /* __TASKING__ */

#if (defined(__TASKING__))
#define API_START_SEC_VAR_INIT
#include "Os_MemMap.h"
#endif /* __TASKING__ */
unsigned int assert_count = OSEE_ASSERT_NIL;
#if (defined(__TASKING__))
#define API_STOP_SEC_VAR_INIT
#include "Os_MemMap.h"
#endif /* __TASKING__ */



static void assert(int test)
{
  register int next_assert;
  GetSpinlock(SpinlockAssert);
  next_assert = (assert_count == OSEE_ASSERT_NIL) ? 1 : assert_count + 1;
  osEE_assert(next_assert, test, OSEE_ASSERT_NIL);
  assert_count = next_assert;
  ReleaseSpinlock(SpinlockAssert);
}

void ErrorHook(StatusType Error)
{
  /* I cache error ID here to check that Error hook is called and that the
     right error is set */

  last_error = Error;
  ++error_count;
}

#if (defined(__TASKING__))
#define OS_CORE0_START_SEC_CODE
#include "Os_MemMap.h"
#endif /* __TASKING__ */

#if (defined(OSEE_EXTENDED_STATUS))
#define EXT_ERROR   (2U)
#else
#define EXT_ERROR   (0U)
#endif /* OSEE_EXTENDED_STATUS */

TASK(Task1)
{
  /* First IRQ stack */
  GetSpinlock(Spinlock2);
  GetResource(ResISRLow);
  ActivateTask(Task2);
  assert(task2_hit == 0U);
  fire_irq(IRQ_LOW);
  assert(low_isr_hit == 0U);
  ReleaseResource(ResISRLow);
  assert(task2_hit == 0U);
  assert(low_isr_hit == 1U);
  assert(medium_isr_hit == 1U);
  assert(high_isr_hit == 1U);
  ReleaseSpinlock(Spinlock2);
  assert(task2_hit == 1U);

  /* Second IRQ stack */
  GetSpinlock(Spinlock3);
  fire_irq(IRQ_LOW);
  assert(low_isr_hit == 1U);
  ReleaseSpinlock(Spinlock3);
  assert(low_isr_hit == 2U);
  assert(medium_isr_hit == 2U);
  assert(high_isr_hit == 2U);

  /* Third IRQ Stack */
  GetSpinlock(Spinlock4);
  fire_irq(IRQ_SLAVE);
  fire_irq(IRQ_LOW);
  fire_irq(IRQ_MEDIUM);
  fire_irq(IRQ_HIGH);
  assert(low_isr_hit == 2U);
  assert(medium_isr_hit == 2U);
  assert(high_isr_hit == 2U);
  assert(task_slave_hit == 0);
  ReleaseSpinlock(Spinlock4);
  assert(low_isr_hit == 3U);
  assert(medium_isr_hit == 3U);
  assert(high_isr_hit == 3U);
  GetSpinlock(Spinlock3);
  assert(task_slave_hit == 1);
  ReleaseSpinlock(Spinlock3);
  assert(task2_hit == 2);
  assert(last_error == E_OS_MISSINGEND);
  assert(error_count == 4U + EXT_ERROR);

  TerminateTask();
}

TASK(Task2)
{
  StatusType s;
  if (task2_hit == 0U) {
    s = GetSpinlock(Spinlock2);
    assert(s == E_OK);

    ActivateTask(Task3);
    assert(task3_hit == 0U);

    ReleaseSpinlock(Spinlock2);
    assert(task3_hit == 1U);
  } else if (task2_hit == 1U) {
    TryToGetSpinlockType Success;
    assert(low_isr_hit == 3U);
    assert(medium_isr_hit == 3U);
    assert(high_isr_hit == 3U);
    TryToGetSpinlock(Spinlock1, &Success);
    assert(Success == TRYTOGETSPINLOCK_SUCCESS);
    ActivateTask(Task3);
    assert(task3_hit == 2U);
    assert(last_error == E_OS_MISSINGEND);
    assert(error_count == 2U + EXT_ERROR);
  }

  ++task2_hit;
  TerminateTask();
  if (task2_hit) {
    assert(last_error == E_OS_SPINLOCK);
    assert(error_count == 3U + EXT_ERROR);
  } else {
    ShutdownAllCores(E_OS_SPINLOCK);
  }
}

TASK(Task3)
{
  if (task3_hit == 0) {
    ++task3_hit;
    TerminateTask();
  } else {
    TryToGetSpinlockType Success;
    assert(task2_hit == 1);
    TryToGetSpinlock(Spinlock2, &Success);
    assert(Success == TRYTOGETSPINLOCK_SUCCESS);
    ++task3_hit;
  }
}

ISR(IsrLow)
{
  ack_irq(IRQ_LOW);

  if (low_isr_hit == 0U) {
    TryToGetSpinlockType Success;
    TryToGetSpinlock(Spinlock3, &Success);
    assert(Success == TRYTOGETSPINLOCK_SUCCESS);
    fire_irq(IRQ_MEDIUM);
    assert(medium_isr_hit == 0U);
    ReleaseSpinlock(Spinlock3);
    assert(medium_isr_hit == 1U);
  } else if (low_isr_hit == 1U) {
    GetSpinlock(Spinlock4);
    fire_irq(IRQ_MEDIUM);
    fire_irq(IRQ_HIGH);
    assert(medium_isr_hit == 1U);
    assert(high_isr_hit == 1U);
  } else if (low_isr_hit == 2U) {
    assert(high_isr_hit == 3U);
    assert(medium_isr_hit == 3U);
  }
  ++low_isr_hit;
}

ISR(IsrMedium)
{
  ack_irq(IRQ_MEDIUM);

  if (medium_isr_hit == 0U) {
    assert(low_isr_hit == 0U);
    GetSpinlock(Spinlock3);
    GetSpinlock(Spinlock4);
    fire_irq(IRQ_HIGH);
    assert(high_isr_hit == 0U);
    fire_irq(IRQ_SLAVE);
    ReleaseSpinlock(Spinlock4);
    assert(high_isr_hit == 1U);
#if (defined(OSEE_EXTENDED_STATUS))
    assert(GetSpinlock(Spinlock1) == E_OS_NESTING_DEADLOCK);
    assert(GetSpinlock(Spinlock2) == E_OS_INTERFERENCE_DEADLOCK);
#endif /* OSEE_EXTENDED_STATUS */
    ReleaseSpinlock(Spinlock3);
  } else if (medium_isr_hit == 1U) {
    assert(low_isr_hit == 2U);
    assert(high_isr_hit == 2U);
    assert(last_error == E_OS_SPINLOCK);
    assert(error_count == 1U + EXT_ERROR);
  } else if (medium_isr_hit == 2U) {
    assert(high_isr_hit == 3U);
    assert(low_isr_hit == 2U);
  }
  ++medium_isr_hit;
}

ISR1(IsrHigh)
{
  ack_irq(IRQ_HIGH);
  /* I cannot call assert here since inside it uses SPINLOCK for mutual
     exclusion with core1 and this is a ISR1 so NO OS calls are allowed. */
  ++high_isr_hit;
}

#if (defined(__TASKING__))
#define OS_CORE0_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* __TASKING__ */

#if (defined(__TASKING__))
#define OS_CORE1_START_SEC_CODE
#include "Os_MemMap.h"
#endif /* __TASKING__ */
TASK(TaskSlave1) {
  if (task_slave_hit == 0U) {
    GetSpinlock(Spinlock3);
    GetSpinlock(Spinlock4);
    ActivateTask(Task2);
    fire_irq(IRQ_SLAVE);
    assert(isr_slave_hit == 2U);
    assert(task2_hit == 1U);
    ++task_slave_hit;
    ReleaseSpinlock(Spinlock4);
    assert(isr_slave_hit == 2U);
    ReleaseSpinlock(Spinlock3);
    assert(isr_slave_hit == 3U);
  } else {
    ++task_slave_hit;
  }

  TerminateTask();
}

ISR(IsrSlave) {
  ack_irq(IRQ_SLAVE);
  if (isr_slave_hit == 1U) {
    ActivateTask(TaskSlave1);
  }
  ++isr_slave_hit;
}
#if (defined(__TASKING__))
#define OS_CORE1_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* __TASKING__ */

void idle_hook(void) {
  ActivateTask(Task1);

  osEE_assert_range(0, 1, assert_count); 
  osEE_assert_last();

  ShutdownAllCores(E_OK);
}

int main(void)
{

  if (GetCoreID() == OS_CORE_ID_MASTER) {
    StatusType s;
    StartCore(OS_CORE_ID_1, &s);
  }

  StartOS(OSDEFAULTAPPMODE);

  return 0;
}
