/* ###*B*###
 * Erika Enterprise, version 3
 *
 * Copyright (C) 2017 - 2018 Evidence s.r.l.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of th:we License, or (at
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

/** \file   ee_uart.h
 *  \brief  UART header file.
 *
 *  \author Ida Savino
 *  \date   2018
 */

#if (!defined(OSEE_UART_H))
#define OSEE_UART_H 

#include "ee.h"

#define COM1 (0x03f8)
#define COM2 (0x02f8)
#define COM3 (0x03e8)
#define COM4 (0x02f8)


/* Uart return values */
#define OSEE_UART_NO_ERROR              ( 1)	//Used as positive
#define OSEE_UART_ERR_BAD_PORT		    (-1)
#define OSEE_UART_ERR_BAD_BAUD_VALUE    (-2)
#define OSEE_UART_ERR_TX_NOT_READY      (-3)
#define OSEE_UART_ERR_RX_NOT_READY      (-4)
#define OSEE_UART_ERR_INT_MODE    	    (-5)
#define OSEE_UART_ERR_FRAME		        (-6)
#define OSEE_UART_ERR_PARITY		    (-7)
#define OSEE_UART_ERR_OVERRUN		    (-8)
#define OSEE_UART_ERR_BREAK_CONDITION	(-9)
#define OSEE_UART_ERR_FUNCTION_NULL	    (-10)
#define OSEE_UART_ERR_INT_DISABLED	    (-11)

int8_t OsEE_uart_init(uint16_t port);

int8_t OsEE_uart_write_byte(uint16_t port, uint8_t data);

void OsEE_uart_puts(uint16_t port, char * data);

#endif /* OSEE_UART_H */
