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

#include "ee.h"

unsigned int entry_mask;

TASK(TaskMaster) {
  ActivateTask(TaskSlave1);

  SuspendOSInterrupts();
  GetSpinlock(spinlock_1);
  GetSpinlock(spinlock_2);

  /* Here at least TaskSlave2 should have been ran, since is in autostart
     and cores are synchronized inside StartOs before scheduling */
  if (entry_mask == 0U)
    for(;;);

  /* I use sum instead of or to check multiple entrance in critical section */
  entry_mask += (1U << GetCoreID());

  ReleaseSpinlock(spinlock_2);
  ReleaseSpinlock(spinlock_1);
  ResumeOSInterrupts();

  ShutdownAllCores(E_OK);
};

TASK(TaskSlave1) {
  SuspendOSInterrupts();
  GetSpinlock(spinlock_1);

  /* I use sum instead of or to check multiple entrance in critical section */
  entry_mask += (1U << GetCoreID());

  ReleaseSpinlock(spinlock_1);
  ResumeOSInterrupts();

  TerminateTask();
};

TASK(TaskSlave2) {
  SuspendOSInterrupts();
  GetSpinlock(spinlock_2);

  /* I use sum instead of or to check multiple entrance in critical section */
  entry_mask += (1U << GetCoreID());

  ReleaseSpinlock(spinlock_2);
  ResumeOSInterrupts();

  TerminateTask();
};

int main(void) {
  if (GetCoreID() == OS_CORE_ID_MASTER) {
    StatusType status;

  /* Enable and assign entry (priority) in INTTAB TOS is cpu0 */
  /* SRC_GPSR01.U = EE_TC2YX_SRN_ENABLE | EE_TC2YX_SRN_PRIORITY(
      EE_ISR2_ID_isr_spin); done inside the kernel */
    StartCore(OS_CORE_ID_3, &status);
    StartCore(OS_CORE_ID_4, &status);

    StartOS(DONOTCARE);
  }

  StartOS(OSDEFAULTAPPMODE);

  return 0;
}
