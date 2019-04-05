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
 *  .--------------.                  .----------.
 *  |PWR |         |CAN_H - CAN0 pin 4|          |
 *  |----'         |----------------->|          |
 *  |   Tricore    |                  | CAN BUS  |
 *  | Starter Kit  |CAN_L - CAN0 pin 3|          |
 *  | TC277 board  |----------------->|          |
 *  |              |                  '----------'
 *  |---.      .---|
 *  |   |      |   |
 *  |   |      |   |
 *  |___'      |___|
 *  |              |
 *  |---.      .---|
 *  |   |      |   |
 *  |   |      |   |
 *  |___'      |___|
 *  '--------------'
 *
 *  \author Francesco Bagagli
 *  \date   2018
 */

/* AUTOSAR MCAL. */
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Can_17_MCanP.h"
#include "ee_triboard_dio.h"
#include "CanIf_Cbk.h"

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

#define  OSEE_TEST_CAN_HWH_TX  (\
              Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Tx_UDSresp_BCCM2F0)

/* Macro to set MSB for Extended messages */
#define CAN_EXTENDED_MSB_SET  (0x80000000U)

#define  OSEE_TEST_CAN_ID_TX  (0x18DAF06DU | CAN_EXTENDED_MSB_SET)

#define  OSEE_TEST_NUMBER_OF_CAN_MESSAGES   (2)

/* Data used for transmission by Controller 0 */
uint8 tx_data_1[OSEE_TEST_NUMBER_OF_CAN_MESSAGES][8] = {
  {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 },
  {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18 }
};

/* PDU info used by Controller 0 */
Can_PduType PduInfo_1[] = {
  {OSEE_TEST_CAN_TX_PDU_ID_1, 8, OSEE_TEST_CAN_ID_TX, tx_data_1[0] },
  {OSEE_TEST_CAN_TX_PDU_ID_2, 8, OSEE_TEST_CAN_ID_TX, tx_data_1[1] }
};

typedef enum {
  OSEE_CAN_MODE_INITIALIZED,
  OSEE_CAN_MODE_NOT_INITIALIZED
} OseeCanStatusType;

OseeCanStatusType can_init = OSEE_CAN_MODE_NOT_INITIALIZED;

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
  Can_17_MCanP_Init(&Can_17_MCanP_ConfigRoot[0]);

  /* Clock Initialization */
  Mcu_InitClock(McuConf_McuClockSettingConfig_McuClockSettingConfig_0);

  while (Mcu_GetPllStatus() != MCU_PLL_LOCKED);

  /* Clock Distribution */
  Mcu_DistributePllClock();

  /* led init */
  Dio_WriteChannel(OSEE_TEST_DIO_OUT_1, STD_HIGH);
  Dio_WriteChannel(OSEE_TEST_DIO_OUT_2, STD_HIGH);
  Dio_WriteChannel(OSEE_TEST_DIO_OUT_3, STD_HIGH);
  Dio_WriteChannel(OSEE_TEST_DIO_OUT_4, STD_HIGH);
  Dio_WriteChannel(OSEE_TEST_DIO_OUT_5, STD_HIGH);
  Dio_WriteChannel(OSEE_TEST_DIO_OUT_6, STD_HIGH);
  Dio_WriteChannel(OSEE_TEST_DIO_OUT_7, STD_HIGH);
  Dio_WriteChannel(OSEE_TEST_DIO_OUT_8, STD_HIGH);

  StartOS(OSDEFAULTAPPMODE);

  return 0;
}

/*
 * TASK 1: main function
 */
TASK(Task1)
{
  Can_ReturnType can_ret;

  ++task1_fired;

/*  if ( led_status == STD_LOW ) {
    led_status = STD_HIGH;
  }
  else {
    led_status = STD_LOW;
  }*/
  OsEE_test_toggle_dio(OSEE_TEST_DIO_OUT_1);

  if (can_init == OSEE_CAN_MODE_NOT_INITIALIZED) {
    can_init = OSEE_CAN_MODE_INITIALIZED;
    can_ret = Can_17_MCanP_SetControllerMode(
                                 Can_17_MCanPConf_CanController_CanController_0,
                                 CAN_T_START);
    Can_17_MCanP_EnableControllerInterrupts(
                                Can_17_MCanPConf_CanController_CanController_0);
    if (can_ret != CAN_OK) {
      for(;;);
    }
  }

  Can_17_MCanP_MainFunction_Write();
  Can_17_MCanP_MainFunction_Read();
  Can_17_MCanP_MainFunction_Mode();

  ++task1_ended;
  TerminateTask();
}


/*
 * TASK 2: periodic sender
 */
TASK(Task2)
{
  static uint8 msg_id;
  Can_ReturnType can_ret = CAN_OK;

  ++task2_fired;

  msg_id = (msg_id + 1) % OSEE_TEST_NUMBER_OF_CAN_MESSAGES;
  can_ret = Can_17_MCanP_Write(OSEE_TEST_CAN_HWH_TX, &PduInfo_1[msg_id]);
  if (can_ret != CAN_OK) {
    for(;;);
  }
  OsEE_test_toggle_dio(OSEE_TEST_DIO_OUT_2);

  ++task2_ended;
  TerminateTask();
}
