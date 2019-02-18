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
 *  This file contains the code DIO demo.
 *
 *  This test use two leds and a dip switch. One led blink for vitality task,
 *  the other led is turned off at dip switch press.
 *  This is the wiring for the Tricore TC297 Starter Kit
 *
 *         .--------------.
 *         |PWR |         |
 *         |----'         |
 *         |   Tricore    |
 *         | Starter Kit  |
 *         | TC297 board  |
 *         |              |
 *         |---.      .---|
 *         |   |      |   |
 *         |   |      |   |
 *         |___'      |___|
 *         |              |
 *         |---.      .---|----Gnd----------------.
 *         |   |      |   |---------P01.6------.   \
 *         |   |      |   |-------.             \   \
 *         |___'      |___|.       \P22.8        \   \
 *         '--------------' '       \             \   \
 *                          |P01.7   \             \   \
 *                          '         '       Dip   '   \
 *                          |         |       Switch|    \
 *                        __|__     __|__           0 |   \
 *                    Red \   /     \   / Green       |-   \
 *                    Led__\_/__   __\_/__Led       0 |     \
 *                          |         |             |        \
 *                          |         |             .         \
 *                          |         |             |          .
 *                          \         \             |          |
 *                       220/      220/             |          |
 *                       Ohm\      Ohm\             |          |
 *                          /         /             |          |
 *                          |         |             |          |
 *                          '---------'-------------'----------'
 *
 *  \author Francesco Bagagli
 *  \date   2018
 */

/* AUTOSAR MCAL. */
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"

/* ERIKA Enterprise. */
#include "ee.h"

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

#if (defined(OSEE_API_DYNAMIC))
TaskType Task1;
TaskType Task2;
#endif /* OSEE_API_DYNAMIC */

#define  OSEE_TEST_DIO_OUT_0   (DIO_CHANNEL_1_7)

#define  OSEE_TEST_DIO_OUT_1   (DIO_CHANNEL_22_8)

#define  OSEE_TEST_DIO_IN      (DIO_CHANNEL_1_6)


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

  /* Clock Initialization */
  Mcu_InitClock(McuConf_McuClockSettingConfig_McuClockSettingConfig_0);

  while (Mcu_GetPllStatus() != MCU_PLL_LOCKED);

  /* Clock Distribution */
  Mcu_DistributePllClock();

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

  ++task1_ended;

  if ( led_status == STD_LOW ) {
    led_status = STD_HIGH;
  }
  else {
    led_status = STD_LOW;
  }
  Dio_WriteChannel(OSEE_TEST_DIO_OUT_0, led_status);

  TerminateTask();
}


/*
 * TASK 2
 */
TASK(Task2)
{
  OsEE_addr curr_sp;
  Dio_LevelType led_status = STD_LOW;
  Dio_LevelType input_pin = STD_LOW;

  ++task2_fired;

  curr_sp = osEE_get_SP();
  if (task2_sp == 0U) {
    task2_sp = curr_sp;
  } else if (task2_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }

  ++task2_ended;

  input_pin = Dio_ReadChannel(OSEE_TEST_DIO_IN);
  if ( input_pin == STD_LOW) {
    led_status = STD_LOW;
  } else {
    led_status = STD_HIGH;
  }
  Dio_WriteChannel(OSEE_TEST_DIO_OUT_1, led_status);

  TerminateTask();
}
