/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 Evidence s.r.l.
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

/** \file    board.h
 *  \brief   VBOX 3610 GPIO library.
 *  \details This file contains routines for VBOX 3610 GPIO pins handling and
 *           watchdog management.
 *  \warning The watchdog APIs are not tested.
 *  \author  Michele Pes
 *  \date    2017
 */

#include <inmate.h>
#include "ee_internal.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#define GPIO_PORT_COMMAND           0xA35U
#define GPIO_PORT_DATA              0xA36U

#define GPIO_COMMAND_READ_ALL       0xA2U
#define GPIO_COMMAND_READ_IGNITION  0xF2U
#define GPIO_COMMAND_WRITE_ALL      0xA1U

#define GPIO_PIN_0                  0x0U
#define GPIO_PIN_1                  0x1U
#define GPIO_PIN_2                  0x2U
#define GPIO_PIN_3                  0x3U
#define GPIO_PIN_4                  0x4U
#define GPIO_PIN_5                  0x5U
#define GPIO_PIN_6                  0x6U
#define GPIO_PIN_7                  0x7U

#define GPIO_PIN_0_MASK             0x1U
#define GPIO_PIN_1_MASK             0x2U
#define GPIO_PIN_2_MASK             0x4U
#define GPIO_PIN_3_MASK             0x8U
#define GPIO_PIN_4_MASK             0x10U
#define GPIO_PIN_5_MASK             0x20U
#define GPIO_PIN_6_MASK             0x40U
#define GPIO_PIN_7_MASK             0x80U

#define GPIO_PIN_INPUT_0            GPIO_PIN_0
#define GPIO_PIN_INPUT_1            GPIO_PIN_1
#define GPIO_PIN_INPUT_2            GPIO_PIN_2
#define GPIO_PIN_INPUT_3            GPIO_PIN_3
#define GPIO_PIN_OUTPUT_0           GPIO_PIN_4
#define GPIO_PIN_OUTPUT_1           GPIO_PIN_5
#define GPIO_PIN_OUTPUT_2           GPIO_PIN_6
#define GPIO_PIN_OUTPUT_3           GPIO_PIN_7

#define GPIO_PIN_IGNITION           GPIO_PIN_INPUT_3

#define WATCHDOG_PORT_DATA          0xA16U
#define WATCHDOG_PORT_COMMAND       0xA15U
#define WATCHDOG_PORT_PME           0xA1AU
#define WATCHDOG_VALUE_ENABLE       0x20U
#define WATCHDOG_VALUE_PME_ENABLE   0x40U
#define WATCHDOG_VALUE_DISABLE      0x0U
#define WATCHDOG_TIME_SECONDS       0x0U
#define WATCHDOG_TIME_MINUTES       0x1U


/** Return all I/O flags. */
OSEE_STATIC_INLINE u8 gpio_get_pins(void) {
    outb(GPIO_COMMAND_READ_ALL, GPIO_PORT_COMMAND);
    return inb(GPIO_PORT_DATA);
}

/** Write \b all I/O flags. */
OSEE_STATIC_INLINE void gpio_set_pins(u8 value) {
    outb(GPIO_COMMAND_WRITE_ALL, GPIO_PORT_COMMAND);
    outb(value, GPIO_PORT_DATA);
}

/**
 * \brief Read pin pin from flags.
 * \param[in] pin The pin \b index, [0-7].
 * \return The bit status, 0 or 1.
 * \note It is recommended to use GPIO_PIN_X or GPIO_PIN_INPUT/OUTPUT_X macros.
 */
OSEE_STATIC_INLINE u8 gpio_get_pin(u8 pin) {
    return (gpio_get_pins() >> pin) & 1;
}

/** Return ignition status, 0 or 1. */
OSEE_STATIC_INLINE u8 gpio_get_ignition(void) {
    outb(GPIO_COMMAND_READ_IGNITION, GPIO_PORT_COMMAND);
    return (gpio_get_pins() >> GPIO_PIN_IGNITION) & 1;
}

/**
 * \brief Write the value value to pin pin.
 * \param[in] pin The pin \b index, [0-7].
 * \param[in] value The value of the pin to write, must be 0 or 1.
 * \note It is recommended to use GPIO_PIN_X or GPIO_PIN_INPUT/OUTPUT_X macros.
 */
OSEE_STATIC_INLINE void gpio_set_pin(u8 pin, u8 value) {
    u8 pins = gpio_get_pins();
    pins &= ~(1 << pin);
    pins |= ((value & 1) << pin);
    gpio_set_pins(pins);
}

/**
 * \brief Toggle the pin bit.
 * \param[in] pin The pin \b index, [0-7].
 * \note It is recommended to use GPIO_PIN_X or GPIO_PIN_INPUT/OUTPUT_X macros.
 */
OSEE_STATIC_INLINE void gpio_toggle_pin(u8 pin) {
    gpio_set_pins(gpio_get_pins() ^ (1 << pin));
}

/**
 * \brief Toggle flags with mask mask.
 * \param[in] mask The mask to xor old flags value with.
 */
OSEE_STATIC_INLINE void gpio_toggle_pins(u8 mask) {
    gpio_set_pins(gpio_get_pins() ^ mask);
}

/**
 * \brief Start watchdog with specified period
 * \param[in] value The value, in seconds or minute
 * \param[in] is_minute This must be 0 for seconds, 1 for minutes. It is
 *            recommended to use WATCHDOG_TIME_X macros.
 */
OSEE_STATIC_INLINE void vbox_start_watchdog(u8 value, u8 is_minute) {
    outb(value, WATCHDOG_PORT_DATA);
    outb(WATCHDOG_VALUE_ENABLE | ((is_minute & 1) << 3), WATCHDOG_PORT_COMMAND);
    /*outb(WATCHDOG_VALUE_PME_ENABLE, WATCHDOG_PORT_PME);*/
}

/** Stop the watchdog */
OSEE_STATIC_INLINE void vbox_stop_watchdog(void) {
    outb(WATCHDOG_VALUE_DISABLE, WATCHDOG_PORT_COMMAND);
}

/**
 * \brief Reset the watchdog
 * \note To be used when watchdog is active
 * \note Restart the watchdog with previuous values
 * \warning To be called after vbox_start_watchdog has been called
 */
OSEE_STATIC_INLINE void vbox_reset_watchdog(void) {
    vbox_stop_watchdog();
    vbox_start_watchdog(inb(WATCHDOG_PORT_DATA), /* old values */
                        (inb(WATCHDOG_PORT_COMMAND) >> 3) & 1);
}

#if (defined(__cplusplus))
}
#endif
