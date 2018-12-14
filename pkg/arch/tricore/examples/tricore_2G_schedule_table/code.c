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

/*
 * Copyright (C) 2002-2013 Errico Guidieri
 */

#include "ee.h"

unsigned int volatile task_counter;

void ErrorHook ( StatusType Error ) {
  (void)Error;
  for (;;) {
    ;
  }
}

TASK(Task1)
{
  NextScheduleTable(SchedTab1, SchedTab2);

  /* Wait all the activation of TASK 2 */
  /* 1 for ST1 + 2 for ST2 + 5 for ST3 on Core2 */
  /* Last expiry point from ST3 will release this TASK */
  while (task_counter < 8U) {
    EventMaskType mask;

    WaitEvent(Event1);
    GetEvent(Task1,&mask);
    if (mask & Event2) {
      ClearEvent(Event1 | Event2);
    } else {
      ClearEvent(Event1);
    }
  }

  ShutdownAllCores(E_OK);
  /* This won't be never reached */
  TerminateTask();
}

TASK(Task2)
{
  ++task_counter;
  TerminateTask();
}

#if (defined(OSEE_CORE_ID_VALID_MASK))
#if   (OSEE_CORE_ID_VALID_MASK & 0x02U)
#define SLAVE_CORE  OS_CORE_ID_1
#elif (OSEE_CORE_ID_VALID_MASK & 0x04U)
#define SLAVE_CORE  OS_CORE_ID_2
#elif (OSEE_CORE_ID_VALID_MASK & 0x08U)
#define SLAVE_CORE  OS_CORE_ID_3
#elif (OSEE_CORE_ID_VALID_MASK & 0x10U)
#define SLAVE_CORE  OS_CORE_ID_4
#elif (OSEE_CORE_ID_VALID_MASK & 0x40U)
#define SLAVE_CORE  OS_CORE_ID_6
#else
#error Invalid Slave Core ID
#endif
#endif /* OSEE_CORE_ID_VALID_MASK */

/* MAIN */
int main( void )
{
  if (GetCoreID() == OS_CORE_ID_MASTER) {
    StatusType ev;

    StartCore(SLAVE_CORE, &ev);
    if (ev != E_OK) {
      for(;;);
    }
  }

  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
