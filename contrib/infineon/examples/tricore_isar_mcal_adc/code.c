/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2018 Evidence s.r.l.
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

/** \file code.c
 *  \brief  Main application.
 *
 *  This file contains the code of main application for Erika Enterprise.
 *  This is the wiring for the Tricore TC297 Starter Kit
 *
 *                  .--------------.
 *                  |PWR |         |
 *                  |----'         |
 *                  |   Tricore    |
 *                  | Starter Kit  |
 *                  | TC297 board  |
 *                  |              |
 *      VAREF1      |---.      .---|
 *     .------------|   |      |   |
 *    '             |   |      |   |
 *    \            /|___'      |___|
 *    /1KOhm      / |              |
 *    \          /  |---.      .---|
 *    /   SAR3.0/   |   |      |   |
 *    ---------'    |   |      |   |
 *    |             |___'      |___|
 *    \             '--------------'
 *    /<---                   // | \P34.1
 *    \Potentiometer         //  |  \
 *    /            .--------'/   '   '
 *    |           /         /   /    |
 *  __|__        /   .-----'   /     |
 *   ___   P01.7/    |P22.8   /      |
 *    _        /     |       .P22.9  |
 *            /      |       |       |
 *           '       |       |       |
 *           |       |       |       |
 *         __|__   __|__   __|__   __|__
 *         \   /   \   /   \   /   \   /
 *        __\_/__ __\_/__ __\_/__ __\_/__
 *          Red    Green   Yellow   Red
 *           |       |       |       |
 *           |       |       |       |
 *           \       \       \       \
 *        220/       /       /       /
 *        Ohm\       \       \       \
 *           /       /       /       /
 *           |       |       |       |
 *           -------------------------
 *                    __|__
 *                     ___
 *                      _
 *
 *
 * Test result:
 *   ok: led blink + potentiometer could turn on/off 3 leds
 *
 *  \author Giuseppe Serano, Francesco Bagagli
 *  \date   2018
 */

/* AUTOSAR MCAL. */
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Adc.h"

/*#define OVERRIDE_MCAL_CLOCK*/
#if (defined(OVERRIDE_MCAL_CLOCK))
#include "ee_internal.h"
/* ERIKA Enterprise. */
#else
#include "ee.h"
#endif

OsEE_bool volatile stk_wrong = OSEE_FALSE;
OsEE_addr volatile old_sp;

/* TASKs */
DeclareTask(Task1);
DeclareTask(Task2);

/* Idle Hook */
extern void idle_hook(void);

/* Counters */
OsEE_reg volatile task1_fired;
OsEE_reg volatile task1_ended;
OsEE_reg volatile task2_fired;
OsEE_reg volatile task2_ended;

/* Stack Pointers */
OsEE_addr volatile task1_sp;
OsEE_addr volatile task2_sp;
OsEE_addr volatile main_sp;


#define  OSEE_TEST_DIO_OUT_0   (DIO_CHANNEL_1_7)
#define  OSEE_TEST_DIO_OUT_1   (DIO_CHANNEL_22_8)
#define  OSEE_TEST_DIO_OUT_2   (DIO_CHANNEL_22_9)
#define  OSEE_TEST_DIO_OUT_3   (DIO_CHANNEL_34_1)


/*** Adc ***/
/* Maximum number of channels in a group can be 16 */
#define OSEE_TEST_ADC_MAX_GRP_CHANNEL   (16)
Adc_ValueGroupType  adc_buffer[OSEE_TEST_ADC_MAX_GRP_CHANNEL];
#define OSEE_TEST_ADC_GROUP_TEST  (AdcConf_AdcGroup_AdcGroup_003)
#define OSEE_TEST_T1       (1024/4)
#define OSEE_TEST_T2       (1024/2)
#define OSEE_TEST_T3   ((1024*3)/4)

#if (defined(OSEE_API_DYNAMIC))
TaskType Task1;
TaskType Task2;
#endif /* OSEE_API_DYNAMIC */

#define OSEE_BREAK_POINT()                        \
  while ( 1 ) {                                   \
    __asm__ volatile ("debug\n\t" : : : "memory");\
  }

void Mcal_SafeErrorHandler (uint32 Error)
{
  (void)Error;
  while(1);
}

void idle_hook ( void ) {
  OsEE_addr volatile curr_sp = osEE_get_SP();

  if (main_sp == 0) {
    main_sp = curr_sp;
  } else if (main_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }
}

int main(void)
{
#if (defined(OSEE_API_DYNAMIC))
  CreateTask( &Task1, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task1),
      1U, 1U, 1U, 128 );
  CreateTask( &Task2, OSEE_TASK_TYPE_BASIC, TASK_FUNC(Task2),
      1U, 1U, 1U, 128 );

  SetIdleHook(idle_hook);
#endif /* OSEE_API_DYNAMIC */

  Mcu_Init(&Mcu_ConfigRoot[0]);
#if (MCU_INITCHECK_API == STD_ON)
  Mcu_InitCheck(&Mcu_ConfigRoot[0]);
#endif
  Port_Init(&Port_ConfigRoot[0]);
#if (PORT_INITCHECK_API == STD_ON)
  Port_InitCheck(&Port_ConfigRoot[0]);
#endif
  Dio_Init(&Dio_ConfigRoot[0]);
#if (DIO_INITCHECK_API == STD_ON)
  Dio_InitCheck(&Dio_ConfigRoot[0]);
#endif
  Adc_Init(&Adc_ConfigRoot[0]);
  Adc_SetupResultBuffer(OSEE_TEST_ADC_GROUP_TEST, adc_buffer);
#if (ADC_INITCHECK_API == STD_ON)
  Adc_InitCheck(&Adc_ConfigRoot[0]);
#endif

  /* Clock Initialization */
  Mcu_InitClock(McuConf_McuClockSettingConfig_McuClockSettingConfig_0);

  while (Mcu_GetPllStatus() != MCU_PLL_LOCKED);

  /* Clock Distribution */
  Mcu_DistributePllClock();

#if (defined(OVERRIDE_MCAL_CLOCK))
  /* Disable SAFETY ENDINIT Protection */
  {
    uint16_t const safety_wdt_pw  = osEE_tc_get_safety_wdt_pw();
    osEE_tc_clear_safety_endinit(safety_wdt_pw);
  /*===================== Configure CCU Clock Control =========================*/
    osEE_tc_conf_clock_ctrl();
  /*===================== Configure Oscillator Control ========================*/
    osEE_tc_conf_osc_ctrl();
  /*============================ Configure PLL ================================*/
    osEE_tc_set_pll_fsource(300000000);
  /* Re-enable SAFETY ENDINIT Protection */
    osEE_tc_set_safety_endinit(safety_wdt_pw);
  }
#endif

  StartOS(OSDEFAULTAPPMODE);

  return 0;
}

/*
 * TASK 1
 */
TASK(Task1)
{
  OsEE_addr curr_sp;
  static Dio_LevelType led_status = STD_LOW;

  ++task1_fired;

  curr_sp = osEE_get_SP();
  if (task1_sp == 0U) {
    task1_sp = curr_sp;
  } else if (task1_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }

  if ( led_status == STD_LOW ) {
    led_status = STD_HIGH;
  }
  else {
    led_status = STD_LOW;
  }
  Dio_WriteChannel(OSEE_TEST_DIO_OUT_0, led_status);

  ++task1_ended;

  TerminateTask();
}

/*
 * TASK 1
 */
TASK(Task2)
{
  OsEE_addr curr_sp;

  /*Adc_ValueGroupType  Adc_GrpReadBuff;*/
  /*Std_ReturnType  AdcReadStatus;*/
  volatile Adc_StatusType      Adc_Status;
  Std_ReturnType      Std_Return;
  Dio_LevelType       led1 = STD_LOW;
  Dio_LevelType       led2 = STD_LOW;
  Dio_LevelType       led3 = STD_LOW;
  Adc_ValueGroupType  data[OSEE_TEST_ADC_MAX_GRP_CHANNEL];

  ++task2_fired;

  curr_sp = osEE_get_SP();
  if (task2_sp == 0U) {
    task2_sp = curr_sp;
  } else if (task2_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }

  Adc_StartGroupConversion(OSEE_TEST_ADC_GROUP_TEST);

  Adc_Status = ADC_BUSY;
  while (Adc_Status == ADC_BUSY) {
    Adc_Status = Adc_GetGroupStatus(OSEE_TEST_ADC_GROUP_TEST);
  }

  if (Adc_Status == ADC_STREAM_COMPLETED) {
    Std_Return = Adc_ReadGroup(OSEE_TEST_ADC_GROUP_TEST,
                               data);
  } else {
    Mcal_SafeErrorHandler(3);
  }

  if (Std_Return == E_OK) {
    led1 = STD_LOW;
    led2 = STD_LOW;
    led3 = STD_LOW;
    if (data[0] >= OSEE_TEST_T1) {
      led1 = STD_ON;
    }
    if (data[0] >= OSEE_TEST_T2) {
      led2 = STD_ON;
    }
    if (data[0] >= OSEE_TEST_T3) {
      led3 = STD_ON;
    }
    Dio_WriteChannel(OSEE_TEST_DIO_OUT_1, led1);
    Dio_WriteChannel(OSEE_TEST_DIO_OUT_2, led2);
    Dio_WriteChannel(OSEE_TEST_DIO_OUT_3, led3);
  }

  ++task2_ended;

  TerminateTask();
}
