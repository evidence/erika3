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

/** \file	hal.c
 *  \brief	Hardware Abstraction Layer Sources.
 *
 *  This file contains the sources of the HAL for Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

#include "hal.h"
#include "ee_x86_64_tsc.h"

FUNC(void, APPL_CODE) DemoHAL_IdleHook (void )
{
        /* endless loop*/
        while(1) {
                asm volatile("hlt": : : "memory");
        }
}


FUNC(void, APPL_CODE) DemoHAL_DataBarrier ( void ) {}

#define ISRENTRY_ISR2	0x21
#define ISRENTRY_ISR1	0x22
#define ISREXIT_ISR1	0x23
#define ISTENTRY_ISR2	0x24
#define ISTEXIT_ISR2	0x25

/* ISR HAL */

FUNC(void, APPL_CODE) DemoHAL_ISRInit( void ) {}

FUNC(void, APPL_CODE) DemoHAL_ISRTrigger(
	VAR(DemoHAL_ISR, AUTOMATIC) isr
) {
	switch (isr) {
	case DEMO_HAL_ISR_0:
		call_int(ISRENTRY_ISR2);
		break;

	case DEMO_HAL_ISR_1:
		call_int(ISRENTRY_ISR1);
		break;

	case DEMO_HAL_ISR_2:
		call_int(ISREXIT_ISR1);
		break;

	case DEMO_HAL_ISR_3:
		call_int(ISTENTRY_ISR2);
		break;

	case DEMO_HAL_ISR_4:
		call_int(ISTEXIT_ISR2);
		break;

	default:
		break;
	}
}

FUNC(void, APPL_CODE) DemoHAL_ISRDisable( void )
{
	// TODO
}

/* Timer HAL */
FUNC(void, APPL_CODE) DemoHAL_TimerInit( VAR(MemSize, AUTOMATIC) period ) {}

/*! \brief      Return timer value (expressed in ns) */
FUNC(OSEE_TICK_TYPE, APPL_CODE) DemoHAL_TimerGetValue( void ) {
	return osEE_x86_64_tsc_read();
}

/* Serial HAL */

FUNC(void, APPL_CODE) DemoHAL_SerialInit( void ) {}

FUNC(void, APPL_CODE) DemoHAL_SerialWrite(
	P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA)	buffer,
	VAR(MemSize, AUTOMATIC)						length
) { DEMOHAL_PRINTF((char*) buffer);}

