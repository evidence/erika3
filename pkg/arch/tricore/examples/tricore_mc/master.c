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

/** \file   code.c
 *  \brief  Main application.
 *
 *  This file contains the code of main application for Erika Enterprise.
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

/* ERIKA Enterprise. */
#include "shared.h"

TASK(TaskMaster)

{
  SetEvent(TaskSlave1, RemoteEvent);
  led_blink(OSEE_TRIBOARD_2X5_LED_1);
  /* Cleanly terminate the Task */
  TerminateTask();
}

TASK(TaskCpu0Remote)

{
  led_blink(OSEE_TRIBOARD_2X5_LED_5);
  /* Cleanly terminate the Task */
  TerminateTask();
}

OsEE_reg myErrorCounter;

void ErrorHook(StatusType Error)
{
  (void)Error;

  ++myErrorCounter;
  led_blink(OSEE_TRIBOARD_2X5_ALL_LEDS);
}

void idle_hook_core0(void);
void idle_hook_core0(void)
{
  idle_hook_body();
}

/*
 * MAIN TASK
 */
int main(void)
{
  StatusType       status;
  AppModeType      mode;
  CoreIdType const core_id = GetCoreID();

  if (core_id == OS_CORE_ID_MASTER) {
    /* Init leds */
    osEE_tc2x5_leds_init();

    StartCore(OS_CORE_ID_1, &status);
    StartCore(OS_CORE_ID_2, &status);

    mode = OSDEFAULTAPPMODE;
  } else {

    mode = DONOTCARE;
  }

  StartOS(mode);

  return 0;
}


