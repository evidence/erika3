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
 * File Name   : r_peid5.c
 * Device(s)   : RH850/E2x
 * Description : project implementation running on PEID5 (core 5), example
 *             : developed by Evidence (Errico Guidieri, 2018)
 *****************************************************************************/

#include <r_prj.h>
#include <r_synch.h>
#include <diab/copytable.h>


/*#############################################################################
 # local defines
 ############################################################################*/

/******************************************************************************
 * LED and switches on EMBARK EVB
 * Based on configuration of in g_gpio_prj_cfg[] in file r_gpio_cfg.c
 * IMPORTANT: based on order in GPIO project configuration
 *****************************************************************************/
#define PRJ_LED_6       g_port_PrjCfg[7].pin


/*#############################################################################
 # local types
 ############################################################################*/

/******************************************************************************
 * PE5 locals
 *****************************************************************************/
typedef struct
{
  uint32    task500ms_cnt;
  uint32    background_cnt;
} peid5_state_t;


/*#############################################################################
 # local variables
 ############################################################################*/

/******************************************************************************
 * PE5 state (debug visibility)
 *****************************************************************************/
peid5_state_t g_peid5;


/*#############################################################################
 # API
 ############################################################################*/

/******************************************************************************
 * Function Name : R_PEID5_HwInit
 * Description   : project hardware initializations (PLL,...)
 * Arguments     : none
 * Return Value  : none
 * Notice    : RAM is populated with copy table when PE0 invokes crt0
 *               : of WR DIAB (could be different for other compilers)
 *****************************************************************************/
void R_PEID5_HwInit(void)
{

}


/******************************************************************************
 * Function Name : R_PEID5_SwInit
 * Description   : Project initialization.
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
void R_PEID5_SwInit(void)
{
  /* every PE must call StartOS
   * if PE does not set mode then call with DONOTCARE mode */
  StartOS(DONOTCARE);
}


/******************************************************************************
 * Task Name     : R_PEID5_Task500ms
 * Description   : 500ms tasks
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PEID5_Task500ms)
{
  OsEE_bool   toogle_led;
  StatusType  ev;

  /* task counter */
  g_peid5.task500ms_cnt++;

  if (E_OK == R_SYNCH_GetPeStatus(OS_CORE_ID_5))
  {
    /* Emulate a failure to let other cores activate the task */
    ev = E_OS_LIMIT;
  }
  else
  {
    ev = ActivateTask(R_PEID0_TaskConcAct);
  }

  R_SYNCH_SetPeStatus(OS_CORE_ID_5, ev);
  R_SYNCH_SetPeValid(OS_CORE_ID_5, OSEE_TRUE);

  toogle_led = R_SYNCH_ManageBarrier();

  if (toogle_led)
  {
    R_PORT_InvertOutLvl(PRJ_LED_6);
  }

  /* Wait for value valid false */
  while (R_SYNCH_GetPeValid(OS_CORE_ID_5));

  TerminateTask();
}


/******************************************************************************
 * Function Name : R_PEID5_RunBckgrndHook
 * Description   : background hook function
 * Arguments     : none
 * Return Value  : none
 * Notes         : background hook shares PE5 load with ERIKA Kernel,
 *               : in extremne loads situations (no idle time available)
 *               : background hook does not tun. Otherwise is it called
 *               : when PE0 is not busy
 *****************************************************************************/
void R_PEID5_RunBckgrndHook(void)
{
  g_peid5.background_cnt++;
}

