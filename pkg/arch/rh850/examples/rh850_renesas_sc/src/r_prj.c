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

/** \file   r_prj.c
 *  \brief  project implementation
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

/*******************************************************************************
 * File Name   : r_prj.c
 * Device(s)   : RH850/E2x
 * Description : project implementation running on PEID0 (core 0), example
 ******************************************************************************/

#include <ee.h>
#include <r_prj.h>


/*##############################################################################
 # local defines
 ##############################################################################*/

/*******************************************************************************
 * task defines
 ******************************************************************************/
#define PRJ_MASK_ARMED		1U
#define OSEE_BREAK_POINT() _halt()


/*##############################################################################
 # local types
 ##############################################################################*/

/*******************************************************************************
 * project status
 ******************************************************************************/
typedef struct
{
	uint32			  background_cnt;
	OsEE_reg volatile task1_fired;
	OsEE_reg volatile task2_fired;
	OsEE_reg volatile task1_ended;
	OsEE_reg volatile task2_ended;
	OsEE_reg volatile task3_fired;
	OsEE_reg volatile task3_ended;
	OsEE_reg volatile task4_fired;
	OsEE_reg volatile task5_fired;
	OsEE_reg volatile isr2_armed;
	OsEE_addr volatile task1_sp;
	OsEE_addr volatile task2_sp;
	OsEE_addr volatile main_sp;

} prj_state_t;


/*##############################################################################
 # local variables (debugger visibility)
 ##############################################################################*/

/*******************************************************************************
 * project status
 ******************************************************************************/
prj_state_t g_prj;


/*##############################################################################
 # API
 ##############################################################################*/

/*******************************************************************************
 * Function Name : R_PEID0_HwInit
 * Description   : project hardware initializations (PLL,...)
 * Arguments     : none
 * Return Value  : none
 * Notice		 : for PE0 RAM not initialized, stack initialization should
 *               : be done otherwise ECC errors w/ ERIKA,
 *               : all LRAMs could be or initialized here
 *******************************************************************************/
void R_PRJ_HwInit(void)
{
  /* PLL gear up */
  R_CLK_SetSysClk();

  /* reset CRAM */
  R_BOOT_ClearRamType(BOOT_RAM_LRAM_NO_STACK);
  R_BOOT_ClearRamType(BOOT_RAM_CRAM);
}


/******************************************************************************
 * Function Name : R_PRJ_SwInit
 * Description   : Project initialization.
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
void R_PRJ_SwInit(void)
{
	/* start ERIKA on PE0 */
	StartOS(OSDEFAULTAPPMODE);
}


/******************************************************************************
 * Function Name : R_PRJ_FreeTask
 * Description   : release of task busy flag
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
void R_PRJ_FreeTask(void)
{
	g_prj.isr2_armed = 0;
}


/******************************************************************************
 * Function Name : R_PRJ_Task5msFirst
 * Description   : 5ms tasks
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PRJ_Task5msFirst)
{
  OsEE_addr curr_sp;

  ++g_prj.task1_fired;

  g_prj.isr2_armed = PRJ_MASK_ARMED;

  curr_sp = osEE_get_SP();

  if (g_prj.task1_sp == 0U)
  {
    g_prj.task1_sp = curr_sp;
  }
  else if (g_prj.task1_sp != curr_sp)
  {
    OSEE_BREAK_POINT();
  }

  ActivateTask(R_PRJ_Task5msSecond);

  PostSem(&V);

  while (g_prj.isr2_armed) {
    ; /* Wait ISR2 release */
  }

  curr_sp = osEE_get_SP();

  if (g_prj.task1_sp != curr_sp)
  {
    OSEE_BREAK_POINT();
  }

  ++g_prj.task1_ended;

  TerminateTask();
}


/******************************************************************************
 * Function Name : R_PRJ_Task5msSecond
 * Description   : 5ms tasks
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PRJ_Task5msSecond)
{
  OsEE_addr  curr_sp;

  curr_sp = osEE_get_SP();

  if (g_prj.task2_sp == NULL)
  {
    g_prj.task2_sp = curr_sp;
  }
  else if (g_prj.task2_sp != curr_sp)
  {
    OSEE_BREAK_POINT();
  }

  ++g_prj.task2_fired;

  WaitSem(&V);

  ActivateTask(R_PRJ_Task5msThird);
  ++g_prj.task2_ended;

  TerminateTask();
}


/******************************************************************************
 * Function Name : R_PRJ_Task5msThird
 * Description   : 5ms tasks
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PRJ_Task5msThird)
{
  ++g_prj.task3_fired;
  ActivateTask(R_PRJ_Task5msFourth);
  ++g_prj.task3_ended;

  TerminateTask();
}


/******************************************************************************
 * Function Name : R_PRJ_Task5msFourth
 * Description   : 5ms tasks
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PRJ_Task5msFourth)
{
  ++g_prj.task4_fired;
  ActivateTask(R_PRJ_Task5msFifth);

  TerminateTask();
}


/******************************************************************************
 * Function Name : R_PRJ_Task5msFifth
 * Description   : 5ms tasks
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PRJ_Task5msFifth)
{
  ++g_prj.task5_fired;

  TerminateTask();
}


/******************************************************************************
 * Function Name : R_PRJ_RunBckgrndHook
 * Description   : background tasks
 * Arguments     : none
 * Return Value  : none
 * Notes         : background hook shares PE0 load with ERIKA Kernel,
 *               : in extremne loads situations (no idle time available)
 *               : background hook does not tun. Otherwise is it called
 *               : when PE0 is not busy
 *****************************************************************************/
void R_PRJ_RunBckgrndHook(void)
{
  OsEE_addr volatile curr_sp = osEE_get_SP();

  /* increment background count */
  g_prj.background_cnt++;

  if (g_prj.main_sp == 0)
  {
    g_prj.main_sp = curr_sp;
  }
  else if (g_prj.main_sp != curr_sp)
  {
    OSEE_BREAK_POINT();
  }
}


