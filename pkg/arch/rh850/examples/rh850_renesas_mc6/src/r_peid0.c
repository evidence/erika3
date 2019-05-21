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

/*******************************************************************************
 * File Name   : r_peid0.c
 * Device(s)   : RH850/E2x
 * Description : project implementation running on PEID0 (core 0), example
 *             : developed by Evidence (Errico Gudieri, 2018)
 ******************************************************************************/


#include <r_prj.h>
#include <r_synch.h>
#include <stdlib.h>


/*##############################################################################
 # local defines
 ##############################################################################*/

/*******************************************************************************
 * LED and switches on EMBARK EVB
 * Based on configuration of in g_gpio_prj_cfg[] in file r_gpio_cfg.c
 * IMPORTANT: based on order in GPIO project configuration
 *******************************************************************************/
#define PRJ_LED_1       g_port_PrjCfg[2].pin
#define PRJ_LED_7       g_port_PrjCfg[8].pin
#define PRJ_LED_8       g_port_PrjCfg[9].pin


/*##############################################################################
 # local types
 ##############################################################################*/

/*******************************************************************************
 * PE0 locals
 *******************************************************************************/
typedef struct
{
  uint32    task500ms_cnt;
  uint32      taskconc_cnt;
  uint32    background_cnt;
} peid0_state_t;


/*##############################################################################
 # local variables
 ##############################################################################*/

/*******************************************************************************
 * PE0 locals
 *******************************************************************************/
static peid0_state_t g_peid0;


/*##############################################################################
 # API
 ##############################################################################*/

/*******************************************************************************
 * Function Name : R_PEID0_HwInit
 * Description   : project hardware initializations (PLL,...)
 * Arguments     : none
 * Return Value  : none
 * Notice    : for PE0 RAM not initialized, stack initialization should
 *               : be done otherwise ECC errors w/ ERIKA,
 *               : all LRAMs could be or ntialized here
 *******************************************************************************/
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

  /* I/O initialization
     First unlock ports being used (see g_port_PrjCfg)
     - PORT33 pin is used for EVTO
     - PORTs are left unlocked       */
  R_PORT_Unlock((port_lock_t)(PORT_LOCK_P20 | PORT_LOCK_P22 | PORT_LOCK_P24 |
    PORT_LOCK_P33));
  R_PORT_Init(g_port_PrjCfg, g_port_PrjCfgCnt);

  /* Initialize barrier's data structures */
  R_SYNCH_InitBarrier();

  /* register PE0 as running for
   * the core synchronization algorithm */
  R_SYNCH_SetPeActive(((CoreMaskType)1U << OS_CORE_ID_MASTER));

  /* start PE1 */
  StartCore(OS_CORE_ID_1, &status);
  if (status == E_OK)
  {
    /* register PE1 as running for the synchronization algorithm */
    R_SYNCH_SetPeActive(((CoreMaskType)1U << OS_CORE_ID_1));
  }

  /* start PE2 */
  StartCore(OS_CORE_ID_2, &status);
  if (status == E_OK)
  {
    /* register PE2 as running for the synchronization algorithm */
    R_SYNCH_SetPeActive(((CoreMaskType)1U << OS_CORE_ID_2));
  }

  /* start PE3 */
  StartCore(OS_CORE_ID_3, &status);
  if (status == E_OK)
  {
    /* register PE3 as running for the synchronization algorithm */
    R_SYNCH_SetPeActive(((CoreMaskType)1U << OS_CORE_ID_3));
  }

  /* start PE4 */
  StartCore(OS_CORE_ID_4, &status);
  if (status == E_OK) {
    /* register PE4 as running for the synchronization algorithm */
    R_SYNCH_SetPeActive(((CoreMaskType)1U << OS_CORE_ID_4));
  }

  /* start PE5 */
  StartCore(OS_CORE_ID_5, &status);
  if (status == E_OK)
  {
    /* register PE1 as running for the synchronization algorithm */
    R_SYNCH_SetPeActive(((CoreMaskType)1U << OS_CORE_ID_5));
  }

  /* start ERIKA OS */
  StartOS(OSDEFAULTAPPMODE);
}


/******************************************************************************
 * Task Name     : R_PEID0_Task500ms
 * Description   : 500ms, toggle LED if barrier swapped
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PEID0_Task500ms)
{
  static OsEE_bool toogle_led;

  /* task counter */
  g_peid0.task500ms_cnt++;

  if (toogle_led)
  {
    unsigned int  volatile  i;  /* For what i need is good enough */
    unsigned int  const     wait = rand() % 100U;

    /* Add some offset before entering the barrier */
    for (i = 0U; i < wait; ++i);
  }

  toogle_led = R_SYNCH_ManageBarrier();

  if (toogle_led)
  {
    R_PORT_InvertOutLvl(PRJ_LED_1);
  }

  TerminateTask();
}



/******************************************************************************
 * Task Name     : R_PEID0_TaskConcAct
 * Description   : recurrence
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
TASK(R_PEID0_TaskConcAct)
{
  CoreNumType core_num;
  CoreIdType activator = INVALID_CORE_ID;

  /* task counter */
  g_peid0.taskconc_cnt++;

  for (core_num = OS_CORE_ID_1; core_num < OS_CORE_ID_ARR_SIZE; ++core_num)
  {
    /* Wait for valid value */
    while (!R_SYNCH_GetPeValid(core_num));

    /* Invalidate for next loop */
    R_SYNCH_SetPeValid(core_num, OSEE_FALSE);
    if (E_OS_LIMIT != R_SYNCH_GetPeStatus(core_num))
    {
      if (INVALID_CORE_ID != activator)
      {
        /* Unexpected Error: Stop Everything */
        ShutdownOS(E_OS_CORE);
      }
      else
      {
        activator = core_num;
      }
    }
  }

  /* toggle LED based on a PE */
  switch (activator)
  {
    case OS_CORE_ID_1:
      R_PORT_SetOutLvl(PRJ_LED_7, PORT_LOW);
      R_PORT_SetOutLvl(PRJ_LED_8, PORT_LOW);
    break;

    case OS_CORE_ID_2:
      R_PORT_SetOutLvl(PRJ_LED_7, PORT_HIGH);
      R_PORT_SetOutLvl(PRJ_LED_8, PORT_LOW);
    break;

    case OS_CORE_ID_3:
      R_PORT_SetOutLvl(PRJ_LED_7, PORT_LOW);
      R_PORT_SetOutLvl(PRJ_LED_8, PORT_HIGH);
    break;

    case OS_CORE_ID_4:
      R_PORT_SetOutLvl(PRJ_LED_7, PORT_HIGH);
      R_PORT_SetOutLvl(PRJ_LED_8, PORT_HIGH);
    break;

    case OS_CORE_ID_5:
      R_PORT_SetOutLvl(PRJ_LED_7, PORT_HIGH);
      R_PORT_SetOutLvl(PRJ_LED_8, PORT_HIGH);
      R_PORT_InvertOutLvl(PRJ_LED_1);
    break;

    case OS_CORE_ID_0:
    default:
      /* Unexpected Error: Stop Everything */
      ShutdownOS(E_OS_CORE);
    break;
  }

  TerminateTask();
}


/******************************************************************************
 * Function Name : R_PEID0_RunBckgrndHook
 * Description   : background tasks
 * Arguments     : none
 * Return Value  : none
 * Notes         : background hook shares PE0 load with ERIKA Kernel,
 *               : in extremne loads situations (no idle time available) 
 *               : background hook does not tun. Otherwise is it called
 *               : when PE0 is not busy
 *****************************************************************************/
void R_PEID0_RunBckgrndHook(void)
{
  g_peid0.background_cnt++;
}


