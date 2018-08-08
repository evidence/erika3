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

/** \file	hal.h
 *  \brief	Hardware Abstraction Layer header.
 *
 *  This file contains the header of the HAL for Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* ERIKA Enterprise. */
#include "ee.h"

/*Include shared modules, which are used for whole project*/
#include "device_registers.h"
#include "clock_manager.h"
#include "interrupt_manager.h"
#include "pins_driver.h"
#include "edma_driver.h"
#include "lpuart_driver.h"
#include "system_S32K144.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/* Application Code Memory Class */
#define APPL_CODE	TYPEDEF

FUNC(void, APPL_CODE) DemoHAL_Init( void );

FUNC(void, APPL_CODE) DemoHAL_Delay( VAR(MemSize, AUTOMATIC) interval );

FUNC(void, APPL_CODE) DemoHAL_MainFunction( void );

/* Serial HAL */

FUNC(void, APPL_CODE) DemoHAL_SerialInit( void );

FUNC(void, APPL_CODE) DemoHAL_SerialWrite(
  P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA) buffer,
  VAR(MemSize, AUTOMATIC)                   length
);

FUNC(void, APPL_CODE) DemoHAL_SerialWrite_Async(
  P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA) buffer,
  VAR(MemSize, AUTOMATIC)                   length
);

FUNC(status_t, APPL_CODE) DemoHAL_SerialWrite_Status(
  void
);

FUNC(void, APPL_CODE) DemoHAL_SerialRead(
  P2VAR(uint8_t, AUTOMATIC, OS_APPL_DATA) buffer,
  VAR(MemSize, AUTOMATIC)                 length
);

FUNC(void, APPL_CODE) DemoHAL_SerialISRHandler(
  void
);


#if (defined(__cplusplus))
}
#endif
