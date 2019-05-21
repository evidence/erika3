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

/** \file   slave1.c
 *  \brief  peid1 application
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

#include "r_prj.h"

#if 0
#include <diab/copytable.h>

/* This #pragma is a MUST otherwise the linker won't generate the reference of
   the following symbols with the linker internally generated symbols */
#pragma weak WR_CPU1_CT
extern struct copytable WR_CPU1_CT[];
#pragma weak WR_CPU1_CT__END__
extern struct copytable WR_CPU1_CT__END__[];
#endif /* 0 */

/*#############################################################################
 # local defines
 ############################################################################*/

/*#############################################################################
 # local types
 ############################################################################*/

/******************************************************************************
 * PE1 overall state
 *****************************************************************************/
typedef struct
{
  uint32    task1_cnt;
  uint32    task2_cnt;
  uint32    background_cnt;
  OsEE_bool stop_task1;
} peid1_state_t;

/*#############################################################################
 # local variables
 ############################################################################*/

/******************************************************************************
 * PE1 state
 *****************************************************************************/
peid1_state_t g_peid1;


/*#############################################################################
 # API
 ############################################################################*/

/******************************************************************************
 * Function Name : R_PEID1_HwInit
 * Description   : project hardware initializations (PLL,...)
 * Arguments     : none
 * Return Value  : none
 * Notice        : RAM is populated with copy table when PE0 invokes crt0
 *               : of WR DIAB (could be different for other compilers)
 *****************************************************************************/
void R_PEID1_HwInit(void)
{
#if 0
  /* Local RAM in zeroed by Embark boot code so I need to reinitialize
     Local RAM data */
  __copy_multiple(WR_CPU1_CT, WR_CPU1_CT__END__);
#endif /* 0 */
}


/******************************************************************************
 * Function Name : R_PEID1_SwInit
 * Description   : Project initialization.
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
void R_PEID1_SwInit(void)
{
  /* every PE must call StartOS
   * if PE does not set mode then call with DONOTCARE mode */
  StartOS(DONOTCARE);
}

/******************************************************************************
 * Task Name     : R_PEID1_Task1
 * Description   : Extended Task enabled by a remote event
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PEID1_Task1)
{
  while (!g_peid1.stop_task1) {
    ++g_peid1.task1_cnt;
    WaitEvent(RemoteEvent);
    ActivateTask(R_PEID1_Task2);
    ClearEvent(RemoteEvent);
  }
  TerminateTask();
}

/******************************************************************************
 * Task Name     : R_PEID1_Task2
 * Description   : It just set an alarm to enable remotely a Task in PE0
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PEID1_Task2)
{
  ++g_peid1.task2_cnt;
  SetRelAlarm(AlarmSlave2RemoteCPU0, 50, 0);
  TerminateTask();
}

/******************************************************************************
 * Function Name : R_PEID1_RunBckgrndHook
 * Description   : background tasks
 * Arguments     : none
 * Return Value  : none
 * Notes         : background hook shares PE1 load with ERIKA Kernel,
 *               : in extremne loads situations (no idle time available)
 *               : background hook does not tun. Otherwise is it called
 *               : when PE0 is not busy
 *****************************************************************************/
void R_PEID1_RunBckgrndHook(void)
{
  static OsEE_addr  idle_sp;
  OsEE_addr         curr_sp;

  curr_sp = osEE_get_SP();

  if (idle_sp == NULL) {
    idle_sp = curr_sp;
  } else if (idle_sp != curr_sp) {
    _halt();
  }

  ++g_peid1.background_cnt;
}
