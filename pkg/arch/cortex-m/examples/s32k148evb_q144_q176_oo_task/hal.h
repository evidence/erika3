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

#if (defined(__cplusplus))
extern "C" {
#endif

/* Application Code Memory Class */
#define APPL_CODE	TYPEDEF

FUNC(void, APPL_CODE) DemoHAL_Init( void );

FUNC(void, APPL_CODE) DemoHAL_Delay( VAR(MemSize, AUTOMATIC) interval );

FUNC(void, APPL_CODE) DemoHAL_MainFunction( void );

/* Leds HAL */

typedef enum {
	DEMO_HAL_LED_0,
	DEMO_HAL_LED_1,
	DEMO_HAL_LED_2,
	DEMO_HAL_LED_3,
	DEMO_HAL_LED_4,
	DEMO_HAL_LED_5,
	DEMO_HAL_LED_6,
	DEMO_HAL_LED_7,
	DEMO_HAL_LED_NUM
} DemoHAL_Led;

FUNC(void, APPL_CODE) DemoHAL_LedInit( void );

FUNC(void, APPL_CODE) DemoHAL_LedOn( VAR(DemoHAL_Led, AUTOMATIC) led );

FUNC(void, APPL_CODE) DemoHAL_LedOff( VAR(DemoHAL_Led, AUTOMATIC) led );

FUNC(void, APPL_CODE) DemoHAL_LedToggle( VAR(DemoHAL_Led, AUTOMATIC) led );

/* Buttons HAL */

#if	(defined(OSEE_API_DYNAMIC))
#define	BUTTONS_ISR_ID	OSEE_CORTEX_M_PORTC_ISR_ID
#endif	/* OSEE_API_DYNAMIC */

typedef enum {
	DEMO_HAL_BUTTON_0,
	DEMO_HAL_BUTTON_1,
	DEMO_HAL_BUTTON_2,
	DEMO_HAL_BUTTON_3,
	DEMO_HAL_BUTTON_4,
	DEMO_HAL_BUTTON_5,
	DEMO_HAL_BUTTON_6,
	DEMO_HAL_BUTTON_7,
	DEMO_HAL_BUTTON_NUM,
} DemoHAL_Button;

FUNC(void, APPL_CODE) DemoHAL_ButtonInit( void );

FUNC(OsEE_bool, APPL_CODE) DemoHAL_ButtonRead(
	VAR(DemoHAL_Button, AUTOMATIC)	button
);

FUNC(void, APPL_CODE) DemoHAL_ButtonInterruptEnable(
	VAR(DemoHAL_Button, AUTOMATIC)	button
);

FUNC(void, APPL_CODE) DemoHAL_ButtonInterruptDisable(
	VAR(DemoHAL_Button, AUTOMATIC)	button
);

FUNC(void, APPL_CODE) DemoHAL_ButtonInterruptAck(
	VAR(DemoHAL_Button, AUTOMATIC)	button
);

/* Timer HAL */

#if	(defined(OSEE_API_DYNAMIC))
#define	TIMER_ISR_ID	OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_ID
#endif	/* OSEE_API_DYNAMIC */

FUNC(void, APPL_CODE) DemoHAL_TimerInit( VAR(MemSize, AUTOMATIC) period );

FUNC(void, APPL_CODE) DemoHAL_TimerDelay( VAR(MemSize, AUTOMATIC) interval );

FUNC(void, APPL_CODE) DemoHAL_TimerAck( void );

/* Serial HAL */

FUNC(void, APPL_CODE) DemoHAL_SerialInit( void );

FUNC(void, APPL_CODE) DemoHAL_SerialWrite(
	P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA)	buffer,
	VAR(MemSize, AUTOMATIC)				length
);

#if (defined(__cplusplus))
}
#endif
