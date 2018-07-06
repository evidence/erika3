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

#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "ee_internal.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/******************************************************************************
 * Types
 *****************************************************************************/
typedef enum {
	UART_A = 0,
	UART_B,
	UART_C,
	UART_D,
	MAX_UART_ID
} UART_id_t;

typedef enum{
	UART_BAUD_9600 = 0,
	UART_BAUD_38400,
	UART_BAUD_115200,
	MAX_UART_BAUD 
} UART_baudrate_t;

typedef void (*UART_callback_t)(char);

/******************************************************************************
 * API
 *****************************************************************************/
uint8_t UART_init( UART_id_t id, UART_baudrate_t baudrate);
uint32_t UART_write( UART_id_t id, const void * buffer, uint32_t size);
void UART_set_callback( UART_id_t id, UART_callback_t rx_callback); 

#if (defined(__cplusplus))
}
#endif

#endif /* UART_DRIVER_H*/

