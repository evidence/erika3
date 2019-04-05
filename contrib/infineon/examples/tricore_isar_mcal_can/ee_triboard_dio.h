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

 /** @file    ee_tc2x7_board.h
  *  @brief   Triboard DIO utilities functions
  *  @author  Francesco Bagagli
  *  @date    2019
  *
  *  This utilities assumes that the 8 leds present in the triboard are
  *  configured as DIO with these names:
  *  - DioConf_DioChannel_TRIBOARD_LED1
  *  - DioConf_DioChannel_TRIBOARD_LED2
  *  - DioConf_DioChannel_TRIBOARD_LED3
  *  - DioConf_DioChannel_TRIBOARD_LED4
  *  - DioConf_DioChannel_TRIBOARD_LED5
  *  - DioConf_DioChannel_TRIBOARD_LED6
  *  - DioConf_DioChannel_TRIBOARD_LED7
  *  - DioConf_DioChannel_TRIBOARD_LED8
  *
  */

/* AUTOSAR MCAL. */
#include "Dio.h"

#define  OSEE_TEST_DIO_OUT_1   (DioConf_DioChannel_TRIBOARD_LED1)
#define  OSEE_TEST_DIO_OUT_2   (DioConf_DioChannel_TRIBOARD_LED2)
#define  OSEE_TEST_DIO_OUT_3   (DioConf_DioChannel_TRIBOARD_LED3)
#define  OSEE_TEST_DIO_OUT_4   (DioConf_DioChannel_TRIBOARD_LED4)
#define  OSEE_TEST_DIO_OUT_5   (DioConf_DioChannel_TRIBOARD_LED5)
#define  OSEE_TEST_DIO_OUT_6   (DioConf_DioChannel_TRIBOARD_LED6)
#define  OSEE_TEST_DIO_OUT_7   (DioConf_DioChannel_TRIBOARD_LED7)
#define  OSEE_TEST_DIO_OUT_8   (DioConf_DioChannel_TRIBOARD_LED8)

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE OsEE_test_toggle_dio(
    Dio_ChannelType dio_id
) {
    Dio_ChannelType  value;
    value = Dio_ReadChannel(dio_id);
    if ( value == STD_LOW ) {
        value = STD_HIGH;
    }
    else {
        value = STD_LOW;
    }
    Dio_WriteChannel(dio_id, value);
}
