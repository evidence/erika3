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

/** \file   code.c
 *  \brief  Main application.
 *
 *  This file contains the code of main application for Erika Enterprise.
 *
 *  This test use a single led, that must be connected to the board.
 *  Using the breakout board provided with the Infineon Starter Kit, we use a
 *  led connected to the Port 1, pin 7, due to the MCAL configuration
 *
 *  Test output:
 *    ok: led blink at 1Hz
 *    not ok:  led on steady
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
 *     |  _        _  |   P01.7
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
 *  \author Francesco Bagagli
 *  \date   2018
 */

/* AUTOSAR MCAL. */
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Fls_17_Pmu.h"

/*#define OVERRIDE_MCAL_CLOCK*/
#if (defined(OVERRIDE_MCAL_CLOCK))
#include "ee_internal.h"
/* ERIKA Enterprise. */
#else
#include "ee.h"
#endif

OsEE_bool volatile stk_wrong = OSEE_FALSE;
OsEE_addr volatile old_sp;

unsigned int volatile icu_notif_cnt;

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

#define OSEE_BREAK_POINT()                        \
  while ( 1 ) {                                   \
    __asm__ volatile ("debug\n\t" : : : "memory");\
  }

#define  OSEE_TEST_DIO_OUT_0   (DIO_CHANNEL_1_7)

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
  /* Initialization of flash module */
  Fls_17_Pmu_Init(&Fls_17_Pmu_ConfigRoot[0]);
#if (FLS_INITCHECK_API == STD_ON)
  Fls_17_Pmu_InitCheck(&Fls_17_Pmu_ConfigRoot[0]);
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

/****************************** FLS *******************************************/

#define OSEE_FLS_TEST_OFFSET (0U)

typedef enum
{
  OSEE_FLS_TEST_FAILED = 0x0U,
  OSEE_FLS_TEST_PASSED = 0x1U,
} OseeFlsTestStatusType;

typedef enum
{
  OSEE_FLS_TEST_EXECUTED     = 0x0U,
  OSEE_FLS_TEST_NOT_EXECUTED = 0x1U,
} OseeTestExecutedType;

/* Stub definition, to avoid linking problems when used only FLS driver */
void Fee_JobEndNotification(void) {
  ;
}

/* Stub definition, to avoid linking problems when used only FLS driver */
void Fee_JobErrorNotification(void) {
  ;
}

const uint8 Test_ProgData[2 * FLS_PAGE_SIZE] = {
  0x10U, 0x0FU, 0x0EU, 0x0DU, 0x0CU, 0x0B, 0x0AU, 0x09U,
  0x08U, 0x07U, 0x06U, 0x05U, 0x04U, 0x03, 0x02U, 0x01U
};

uint8 Test_ReadData[2 * FLS_PAGE_SIZE];

static OseeFlsTestStatusType  flash_test_result   = OSEE_FLS_TEST_FAILED;
static OseeTestExecutedType   flash_test_executed = OSEE_FLS_TEST_NOT_EXECUTED;

static OseeFlsTestStatusType TestFlash(void) {
  uint8 i;
  OseeFlsTestStatusType test_result = OSEE_FLS_TEST_PASSED;

  /* Erase Flash */
  Fls_17_Pmu_Erase(OSEE_FLS_TEST_OFFSET, FLS_SECTOR_SIZE);
  /* Wait for completion of Erase Job*/
  while(Fls_17_Pmu_GetJobResult() == MEMIF_JOB_PENDING);

  /* Write Flash */
  Fls_17_Pmu_Write( OSEE_FLS_TEST_OFFSET,
                    Test_ProgData,
                    (2*FLS_PAGE_SIZE)
                  );
  /* Wait for completion of Write Job*/
  while(Fls_17_Pmu_GetJobResult() == MEMIF_JOB_PENDING);

  /* Read Flash */
  Fls_17_Pmu_Read( OSEE_FLS_TEST_OFFSET,
                   Test_ReadData,
                   (2*FLS_PAGE_SIZE)
                 );
  /* Wait for completion of Read Job*/
  while(Fls_17_Pmu_GetJobResult() == MEMIF_JOB_PENDING)

  i = 0;
  while ((i < 2*FLS_PAGE_SIZE) && (test_result == OSEE_FLS_TEST_PASSED)) {
    if (Test_ProgData[i] != Test_ReadData[i]) {
      test_result = OSEE_FLS_TEST_FAILED;
    } else {
      i++;
    }
  }

  return test_result;
}

/******************************************************************************/

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

  if (flash_test_executed == OSEE_FLS_TEST_NOT_EXECUTED) {
    flash_test_result = TestFlash();
    flash_test_executed = OSEE_FLS_TEST_EXECUTED;
  }

  if (flash_test_result == OSEE_FLS_TEST_PASSED) {
    if ( led_status == STD_LOW ) {
      led_status = STD_HIGH;
    }
    else {
      led_status = STD_LOW;
    }
    Dio_WriteChannel(OSEE_TEST_DIO_OUT_0, led_status);
  } else {
    /* error always on */
    Dio_WriteChannel(OSEE_TEST_DIO_OUT_0, STD_HIGH);
  }

  ++task1_ended;
  TerminateTask();
}


/*
 * TASK 2
 */
TASK(Task2)
{
  OsEE_addr curr_sp;

  ++task2_fired;

  curr_sp = osEE_get_SP();
  if (task2_sp == 0U) {
    task2_sp = curr_sp;
  } else if (task2_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }

  Fls_17_Pmu_MainFunction();

  ++task2_ended;
  TerminateTask();
}
