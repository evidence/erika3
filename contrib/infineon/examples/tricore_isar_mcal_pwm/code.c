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

/** \file code.cpp
 *  \brief  Main application.
 *
 *  This file contains the code of main application for Erika Enterprise.
 *
 *  This test use a single led, that must be connected to the board.
 *  Using the breakout board provided with the Infineon Starter Kit, we use a
 *  led connected to the Port 1, pin 7, due to the MCAL configuration
 *
 *  Test output:
 *    ok: led blink at 1Hz, check pwm output to the related pin
 *    not ok: led off (not working)
 *
 *
 *   Power
 *       |
 *     .--------------.
 *     |   Tricore    |
 *     | Starter Kit  |
 *     | TC297 board  |
 *     |  _        _  |
 *     | | |      | | |
 *     | |_|      |_| |
 *     |              |
 *     |  _        _  |   P01.4
 *     | | |      | | |---.
 *     | |_|      |_| |    \
 *     '--------------'     '
 *                  |      _|_
 *                  |       \
 *              Gnd |       /  220 Ohm
 *                  |       \
 *                  |      _/_
 *                  |       |
 *                  |       |
 *                  |      _|_
 *                  .     _\_/_ LED
 *                   \      |
 *                    '-----/
 *
 *  \author Giuseppe Serano, Francesco Bagagli
 *  \date   2018
 */

/* AUTOSAR MCAL. */
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Pwm_17_Gtm.h"

/* ERIKA Enterprise. */
#include "ee.h"

OsEE_bool volatile stk_wrong = OSEE_FALSE;
OsEE_addr volatile old_sp;

/* TASKs */
DeclareTask(Task1);

/* Idle Hook */
extern void idle_hook(void);

/* Counters */
OsEE_reg volatile task1_fired;
OsEE_reg volatile task1_ended;

/* Stack Pointers */
OsEE_addr volatile task1_sp;
OsEE_addr volatile main_sp;

#if (defined(OSEE_API_DYNAMIC))
TaskType Task1;
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

  SetIdleHook(idle_hook);
#endif /* OSEE_API_DYNAMIC */

  Mcu_Init(&Mcu_ConfigRoot[0]);
#if (MCU_INITCHECK_API == STD_ON)
  Mcu_InitCheck(&Mcu_ConfigRoot[0]);
#endif

  /* Clock Initialization */
  Mcu_InitClock(McuConf_McuClockSettingConfig_McuClockSettingConfig_0);
  while (Mcu_GetPllStatus() != MCU_PLL_LOCKED);

  /* Clock Distribution */
  Mcu_DistributePllClock();

  Port_Init(&Port_ConfigRoot[0]);
#if (PORT_INITCHECK_API == STD_ON)
  Port_InitCheck(&Port_ConfigRoot[0]);
#endif
  Dio_Init(&Dio_ConfigRoot[0]);
#if (DIO_INITCHECK_API == STD_ON)
  Dio_InitCheck(&Dio_ConfigRoot[0]);
#endif
  Pwm_17_Gtm_Init(&Pwm_ConfigRoot[0]);
#if (PWM_INITCHECK_API == STD_ON)
  Pwm_17_Gtm_InitCheck(&Pwm_ConfigRoot[0]);
#endif

  StartOS(OSDEFAULTAPPMODE);

  return 0;
}

/*
 * TASK 1
 */
TASK(Task1)
{
  static uint16 pwm_duty_cycle = 0;;

  ++task1_fired;

  Pwm_17_Gtm_SetDutyCycle(Pwm_17_GtmConf_PwmChannel_PwmChannel_0,
                          pwm_duty_cycle);
  if (pwm_duty_cycle < 0x8000U) {
    pwm_duty_cycle += 0x1000U;
  } else {
  pwm_duty_cycle = 0x0U;
  }

  ++task1_ended;

  TerminateTask();
}

