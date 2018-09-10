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

 /** @file	ee_tc2x5_board.h
  *  @brief	Board-dependent part of API
  *  @author	Errico Guidieri
  *  @author	Giuseppe Serano
  *  @date	2017
  */
#ifndef	INCLUDE_EE_TC2X5_BOARD_H__
#define	INCLUDE_EE_TC2X5_BOARD_H__

#include <tc27xc/Ifx_reg.h>

/*  Output - Push-pull General-purpose output */
#define OSEE_TC2YX_OUTPUT_PUSH_PULL_GP	0x10U

/* This file have to be included after all API have been */

/* TriBoard 2x5 default clock frequency (20MHz) */
#define OSEE_TRIBOARD_2X5_FOSC	20000000U
/* Interface Board Oscillator Frequency Define */
#define OSEE_TC2YX_BOARD_FOSC	OSEE_TRIBOARD_2X5_FOSC
/* Interface Board Oscillator Frequency Define */
#define OSEE_TC27X_BOARD_FOSC	OSEE_TRIBOARD_2X5_FOSC

enum OsEE_tc2x5_led_id {
  OSEE_TRIBOARD_2X5_NO_LEDS = 0x00,
  OSEE_TRIBOARD_2X5_LED_1 = 0x01,
  OSEE_TRIBOARD_2X5_LED_2 = 0x02,
  OSEE_TRIBOARD_2X5_LED_3 = 0x04,
  OSEE_TRIBOARD_2X5_LED_4 = 0x08,
  OSEE_TRIBOARD_2X5_LED_5 = 0x10,
  OSEE_TRIBOARD_2X5_LED_6 = 0x20,
  OSEE_TRIBOARD_2X5_LED_7 = 0x40,
  OSEE_TRIBOARD_2X5_LED_8 = 0x80,
  OSEE_TRIBOARD_2X5_ALL_LEDS = 0xFF
};

/*  User LEDs are in pull down configuration so the logic is
    inverted respect pin output value */
enum OsEE_tc2x5_led_status {
  OSEE_TRIBOARD_2X5_LED_ON  = 0,
  OSEE_TRIBOARD_2X5_LED_OFF = 1
};

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc2x5_turn_led(
    enum OsEE_tc2x5_led_id led_id, enum OsEE_tc2x5_led_status onoff
) {
  switch(led_id) {
    case OSEE_TRIBOARD_2X5_LED_8:
      P33_OUT.B.P13 = (uint8_t)onoff;
    break;
    case OSEE_TRIBOARD_2X5_LED_7:
      P33_OUT.B.P12 = (uint8_t)onoff;
    break;
    case OSEE_TRIBOARD_2X5_LED_6:
      P33_OUT.B.P11 = (uint8_t)onoff;
    break;
    case OSEE_TRIBOARD_2X5_LED_5:
      P33_OUT.B.P10 = (uint8_t)onoff;
    break;
    case OSEE_TRIBOARD_2X5_LED_4:
      P33_OUT.B.P9 = (uint8_t)onoff;
    break;
    case OSEE_TRIBOARD_2X5_LED_3:
      P33_OUT.B.P8 = (uint8_t)onoff;
    break;
    case OSEE_TRIBOARD_2X5_LED_2:
      P33_OUT.B.P7 = (uint8_t)onoff;
    break;
    case OSEE_TRIBOARD_2X5_LED_1:
      P33_OUT.B.P6 = (uint8_t)onoff;
    break;
    default:
      P33_OUT.B.P13 = (uint8_t)onoff;
      P33_OUT.B.P12 = (uint8_t)onoff;
      P33_OUT.B.P11 = (uint8_t)onoff;
      P33_OUT.B.P10 = (uint8_t)onoff;
      P33_OUT.B.P9 = (uint8_t)onoff;
      P33_OUT.B.P8 = (uint8_t)onoff;
      P33_OUT.B.P7 = (uint8_t)onoff;
      P33_OUT.B.P6 = (uint8_t)onoff;
    break;
  }
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc2x5_set_leds_mask(uint8_t leds_mask)
{
  P33_OUT.B.P13   =   (((uint32_t)leds_mask &
    (uint32_t)OSEE_TRIBOARD_2X5_LED_8) != (uint32_t)0U) ?
    (uint8_t)OSEE_TRIBOARD_2X5_LED_ON: (uint8_t)OSEE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P12   =   (((uint32_t)leds_mask &
    (uint32_t)OSEE_TRIBOARD_2X5_LED_7) != (uint32_t)0U) ?
    (uint8_t)OSEE_TRIBOARD_2X5_LED_ON: (uint8_t)OSEE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P11   =   (((uint32_t)leds_mask &
    (uint32_t)OSEE_TRIBOARD_2X5_LED_6) != (uint32_t)0U) ?
    (uint8_t)OSEE_TRIBOARD_2X5_LED_ON: (uint8_t)OSEE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P10   =   (((uint32_t)leds_mask &
    (uint32_t)OSEE_TRIBOARD_2X5_LED_5) != (uint32_t)0U) ?
    (uint8_t)OSEE_TRIBOARD_2X5_LED_ON: (uint8_t)OSEE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P9    =   (((uint32_t)leds_mask &
    (uint32_t)OSEE_TRIBOARD_2X5_LED_4) != (uint32_t)0U) ?
    (uint8_t)OSEE_TRIBOARD_2X5_LED_ON: (uint8_t)OSEE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P8    =   (((uint32_t)leds_mask &
    (uint32_t)OSEE_TRIBOARD_2X5_LED_3) != (uint32_t)0U) ?
    (uint8_t)OSEE_TRIBOARD_2X5_LED_ON: (uint8_t)OSEE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P7    =   (((uint32_t)leds_mask &
    (uint32_t)OSEE_TRIBOARD_2X5_LED_2) != (uint32_t)0U) ?
    (uint8_t)OSEE_TRIBOARD_2X5_LED_ON: (uint8_t)OSEE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P6    =   (((uint32_t)leds_mask &
    (uint32_t)OSEE_TRIBOARD_2X5_LED_1) != (uint32_t)0U) ?
    (uint8_t)OSEE_TRIBOARD_2X5_LED_ON: (uint8_t)OSEE_TRIBOARD_2X5_LED_OFF;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc2x5_leds_on( void )
{
  osEE_tc2x5_turn_led(OSEE_TRIBOARD_2X5_ALL_LEDS, OSEE_TRIBOARD_2X5_LED_ON);
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc2x5_leds_off( void )
{
  osEE_tc2x5_turn_led(OSEE_TRIBOARD_2X5_ALL_LEDS, OSEE_TRIBOARD_2X5_LED_OFF);
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc2x5_leds_init( void )
{
  osEE_tc2x5_leds_off();

  P33_IOCR12.B.PC13  =   OSEE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR12.B.PC12  =   OSEE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR8.B.PC11   =   OSEE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR8.B.PC10   =   OSEE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR8.B.PC9    =   OSEE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR8.B.PC8    =   OSEE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR4.B.PC7    =   OSEE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR4.B.PC6    =   OSEE_TC2YX_OUTPUT_PUSH_PULL_GP;
}

#if	0	/* [GS]: Button not supported for now! */

/* Infineon TriBoard-TC2X5_V2.0 come without buttons, but RESET button.
   We put a flying button connected with signal REQ1 <-> pin P15.8 on
   pin 71 of PERIPHERALS (Xx02,Xx02) connector.

   Pin P15.8 is a valid input for the ESR5 (External Service Requests 5),
   that can be configured with EICR2.EIS1 (External Input Channel Register 1,
   External Input Selection 1 (the rule is EICRx.EISy -> ESR(2x + y) with
   x [0..3] and y [0,1]).

   The param intvec is used to configure the level of interrupt vector that
   will serve the request.
*/

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc2x5_button_irq_init( EE_TYPEISR2PRIO intvec )
{
  /*  On reset all IOCR (input/output configuration register) configure port
      as input connected to pull-up, that is what we need, so we wont change
      it, but if the internal pull-up will have problem with button pull-up
      I have just to enable the following line */
  /* P15_IOCR8.PC8 = EE_TC2YX_INPUT_TRISTATE; */

  /* P15.8 is input selection 0 so I don't need to configure EIS */
  /* SCU_EICR2.B.EIS1 = 0U; */

  /*  The button will shortcut the pin with GND when pressed ->
      we will use the falling edge to generate the interrupt */
  SCU_EICR2.B.FEN1    = 1U;
  SCU_EICR2.B.EIEN1   = 1U;

  /* Configure OGU0 to respond on triggers (no pattern matching) */
  SCU_IGCR0.B.IGP0 = 1U;

  /* I will use OGU0 (Output Gate-in Unit 0) -> SRC_SCUERU0
   *  [0..7] SRPN = INTERRUPT_NR
   *  [10] Service Request enable
   *  [11..12] Type Of Service (means which CPU will handle it)
   */
  SRC_SCUERU0.U = EE_TC2YX_SRN_TYPE_OF_SERVICE(EE_CURRENTCPU) |
    EE_TC2YX_SRN_ENABLE | EE_TC2YX_SRN_PRIORITY(intvec);
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc2x5_button_irq_clear_request( void )
{
  /* Clear the request */
  SCU_FMR.B.FC5       = 1U;
}

OSEE_STATIC_INLINE EE_BIT OSEE_ALWAYS_INLINE
  osEE_tc2x5_read_button( void )
{
  return P15_IN.B.P8;
}

#endif	/* 0 - [GS]: Button not supported for now! */

#endif	/* INCLUDE_EE_TC2X5_BOARD_H__ */
