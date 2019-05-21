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


/******************************************************************************
 * File Name   : r_peid0.c
 * Device(s)   : RH850/E2x
 * Description : project implementation running on PEID0 (core 0), example
 *             : developed by Evidence (Errico Gudieri, 2018)
 *****************************************************************************/

/* ERIKA Enterprise. */
#include "r_prj.h"

/*#############################################################################
 # local defines
 ############################################################################*/

/*#############################################################################
 # local types
 ############################################################################*/

/******************************************************************************
 * PE0 locals
 *****************************************************************************/
typedef struct
{
  uint32    task1s_cnt;
  uint32    taskremote_cnt;
  uint32    background_cnt;
} peid0_state_t;


/*#############################################################################
 # local variables
 ############################################################################*/

/******************************************************************************
 * PE0 locals
 *****************************************************************************/
static peid0_state_t g_peid0;


/*#############################################################################
 # API
 ############################################################################*/

/*******************************************************************************
 * Function Name : R_PEID0_HwInit
 * Description   : project hardware initializations (PLL,...)
 * Arguments     : none
 * Return Value  : none
 * Notice    : for PE0 RAM not initialized, stack initialization should
 *               : be done otherwise ECC errors w/ ERIKA,
 *               : all LRAMs could be or initialized here
 *****************************************************************************/
void R_PEID0_HwInit(void)
{
  /* PLL gear up */
  R_CLK_SetSysClk();

  /* reset CRAM */
  R_BOOT_ClearRamType(BOOT_RAM_LRAM_NO_STACK);
  R_BOOT_ClearRamType(BOOT_RAM_CRAM);
}

/******************************************************************************
 * Function Name : R_PEID0_SwInit
 * Description   : Project initialization.
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
void R_PEID0_SwInit(void)
{
  StatusType    status;


  /* start PE1 */
  StartCore(OS_CORE_ID_1, &status);
  if (status == E_OK)
  {
    /* start ERIKA OS */
    StartOS(OSDEFAULTAPPMODE);
  }
}

/******************************************************************************
 * Task Name     : R_PEID0_Task1s
 * Description   : 1s, Release R_PEID1_Task1 trought a remote event.
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PEID0_Task1s) {
  ++g_peid0.task1s_cnt;
  SetEvent(R_PEID1_Task1, RemoteEvent);
  /* Cleanly terminate the Task */
  TerminateTask();
}

/******************************************************************************
 * Task Name     : R_PEID0_TaskRemote
 * Description   : Task enabled by a remote alarm
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PEID0_TaskRemote)

{
  ++g_peid0.taskremote_cnt;
  /* Cleanly terminate the Task */
  TerminateTask();
}

/******************************************************************************
 * Function Name : R_PEID0_RunBckgrndHook
 * Description   : background tasks
 * Arguments     : none
 * Return Value  : none
 * Notes         : background hook shares PE0 load with ERIKA Kernel,
 *               : in extreme loads situations (no idle time available) 
 *               : background hook does not tun. Otherwise is it called
 *               : when PE0 is not busy
 *****************************************************************************/
void R_PEID0_RunBckgrndHook(void)
{
  ++g_peid0.background_cnt;
}
