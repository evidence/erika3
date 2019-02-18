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
  *  @brief   Board-dependent part of API
  *  @author  Francesco Bagagli
  *  @date    2019
  */
#ifndef	INCLUDE_EE_TC2X7_BOARD_H__
#define	INCLUDE_EE_TC2X7_BOARD_H__

#include <tc29xb/Ifx_reg.h>

/*  Output - Push-pull General-purpose output */
#define OSEE_TC2YX_OUTPUT_PUSH_PULL_GP	0x10U

/* This file have to be included after all API have been */

enum OsEE_test_port_led_id {
  OSEE_TEST_PORT_NO_LEDS = 0x00,
  OSEE_TEST_PORT_LED_1 = 0x01,
  OSEE_TEST_PORT_ALL_LEDS = 0xFF
};

enum OsEE_test_port_led_status {
  OSEE_TEST_PORT_LED_ON  = 1,
  OSEE_TEST_PORT_LED_OFF = 0
};

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE OsEE_test_port_turn_led(
    enum OsEE_test_port_led_id led_id, enum OsEE_test_port_led_status onoff
) {
  switch(led_id) {
    case OSEE_TEST_PORT_LED_1:
      P01_OUT.B.P7 = (uint8_t)onoff;
    break;
    default:
      P01_OUT.B.P7 = (uint8_t)onoff;
    break;
  }
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
OsEE_test_port_set_leds_mask(uint8_t leds_mask)
{
  P01_OUT.B.P7    =   (((uint32_t)leds_mask &
    (uint32_t)OSEE_TEST_PORT_LED_1) != (uint32_t)1U) ?
    (uint8_t)OSEE_TEST_PORT_LED_ON: (uint8_t)OSEE_TEST_PORT_LED_OFF;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE OsEE_test_port_leds_on( void )
{
  OsEE_test_port_turn_led(OSEE_TEST_PORT_ALL_LEDS,
                          OSEE_TEST_PORT_LED_ON);
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE OsEE_test_port_leds_off( void )
{
  OsEE_test_port_turn_led(OSEE_TEST_PORT_ALL_LEDS,
                          OSEE_TEST_PORT_LED_OFF);
}

#endif	/* INCLUDE_EE_TC2X7_BOARD_H__ */
