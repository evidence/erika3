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

/** \file	hal.c
 *  \brief	Hardware Abstraction Layer Sources.
 *
 *  This file contains the sources of the HAL for Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* Header */
#include "hal.h"

/* Reserve RAM Memory for Debugger Support. */
uint8_t OSEE_COMPILER_KEEP _ICD2RAM;

/* Pragmas for Configuration Fuse Registers */

/*
 * Startup directly into XT + PLL
 * OSC2 Pin Function: OSC2 is Clock Output
 * Primary Oscillator Mode: XT Crystal
 */
#pragma config FNOSC = PRIPLL
#pragma config POSCMD = XT
#pragma config OSCIOFNC = OFF
#pragma config FCKSM = CSDCMD
/* Watchdog Timer Enabled/disabled by user software */
#pragma config FWDTEN = OFF
/* PGD3 for external PK3/ICD3/RealIce, use PGD2 for PKOB */
#pragma config ICS = PGD2
/* no brownout detect */
#pragma config BOREN0 = OFF
/* no deadman timer  <<< *** New feature, important to DISABLE */
#pragma config DMTEN = DISABLE

FUNC(void, APPL_CODE) DemoHAL_Init( void )
{
	DemoHAL_LedInit();
	DemoHAL_SerialInit();
}

static FUNC(void, APPL_CODE) DemoHAL_Delayus( VAR(MemSize, AUTOMATIC) interval )
{
	VAR(MemSize, AUTOMATIC)	i;
	for (i = 0; i < interval; i++)
	{
		__asm__ volatile ("repeat #39");
		__asm__ volatile ("nop");
	}
}

#define	HAL_DELAYUS_INTERVAL	1000U

FUNC(void, APPL_CODE) DemoHAL_Delay( VAR(MemSize, AUTOMATIC) interval )
{
	VAR(MemSize, AUTOMATIC) i;
	for (i = 0; i < interval; i++)
	{
		DemoHAL_Delayus(HAL_DELAYUS_INTERVAL);
	}
}

FUNC(void, APPL_CODE) DemoHAL_MainFunction( void )
{

}

/* Leds HAL */
#define	LED1		_LATC4
#define	TRISLED1	_TRISC4
#define	LED2		_LATC5
#define	TRISLED2	_TRISC5
#define	LED3		_LATC6
#define	TRISLED3	_TRISC6

FUNC(void, APPL_CODE) DemoHAL_LedInit( void )
{
	/* initialize LEDs to all off */
	TRISLED1 = 0U;
	TRISLED2 = 0U;
	TRISLED3 = 0U;
	LED1 = 0U;
	LED2 = 0U;
	LED3 = 0U;
}

FUNC(void, APPL_CODE) DemoHAL_LedOn( VAR(DemoHAL_Led, AUTOMATIC) led )
{
	switch (led) {
	case DEMO_HAL_LED_0:
		LED1 = 1U;
		break;
	case DEMO_HAL_LED_1:
		LED2 = 1U;
		break;
	case DEMO_HAL_LED_2:
		break;
	case DEMO_HAL_LED_3:
		LED3 = 1U;
		break;
	case DEMO_HAL_LED_4:
	case DEMO_HAL_LED_5:
	case DEMO_HAL_LED_6:
	case DEMO_HAL_LED_7:
	default:
		break;
	}
}

FUNC(void, APPL_CODE) DemoHAL_LedOff( VAR(DemoHAL_Led, AUTOMATIC) led )
{
	switch (led) {
	case DEMO_HAL_LED_0:
		LED1 = 0U;
		break;
	case DEMO_HAL_LED_1:
		LED2 = 0U;
		break;
	case DEMO_HAL_LED_2:
		break;
	case DEMO_HAL_LED_3:
		LED3 = 0U;
		break;
	case DEMO_HAL_LED_4:
	case DEMO_HAL_LED_5:
	case DEMO_HAL_LED_6:
	case DEMO_HAL_LED_7:
	default:
		break;
	}
}

FUNC(void, APPL_CODE) DemoHAL_LedToggle( VAR(DemoHAL_Led, AUTOMATIC) led )
{
	switch (led) {
	case DEMO_HAL_LED_0:
		if ( LED1 == 1U )
		{
			LED1 = 0U;
		}
		else
		{
			LED1 = 1U;
		}
		break;
	case DEMO_HAL_LED_1:
		if ( LED2 == 1U )
		{
			LED2 = 0U;
		}
		else
		{
			LED2 = 1U;
		}
		break;
	case DEMO_HAL_LED_2:
		break;
	case DEMO_HAL_LED_3:
		if ( LED3 == 1U )
		{
			LED3 = 0U;
		}
		else
		{
			LED3 = 1U;
		}
		break;
	case DEMO_HAL_LED_4:
	case DEMO_HAL_LED_5:
	case DEMO_HAL_LED_6:
	case DEMO_HAL_LED_7:
	default:
		break;
	}
}

#define	DEMO_HAL_TIMER_MAX_PERIOD	0xFFFFUL

/* Timer HAL */
FUNC(void, APPL_CODE) DemoHAL_TimerInit( VAR(MemSize, AUTOMATIC) period )
{
	VAR(uint32_t, AUTOMATIC) u32_period = OSEE_MILLI_TO_TICKS(
		((uint32_t)period), OSEE_CPU_CLOCK
	);
	VAR(uint8_t, AUTOMATIC) u8_prescaler = 0U;

	if ( u32_period > DEMO_HAL_TIMER_MAX_PERIOD ) {
		u32_period >>= 0x03U;
		u8_prescaler++;
		if ( u32_period > DEMO_HAL_TIMER_MAX_PERIOD ) {
			u32_period >>= 0x03U;
			u8_prescaler++;
			if ( u32_period > DEMO_HAL_TIMER_MAX_PERIOD ) {
				u32_period >>= 0x02U;
				u8_prescaler++;
				if ( u32_period > DEMO_HAL_TIMER_MAX_PERIOD ) {
					u32_period = DEMO_HAL_TIMER_MAX_PERIOD;
				}
			}
		}
	}
  
	T3CONbits.TON = 0;	/* Disable Timer1 */
	T3CONbits.TCS = 0;	/* Select internal instruction cycle clock */
	T3CONbits.TGATE = 0;	/* Disable Gated Timer mode */
	T3CONbits.TCKPS = u8_prescaler;	/* Select Prescaler */
	PR3 = (uint16_t)u32_period;	/* Load the period value */
	T3CONbits.TON = 1;	/* Enable Timer1 */
}

FUNC(void, APPL_CODE) DemoHAL_TimerDelay( VAR(MemSize, AUTOMATIC) interval )
{
  (void)interval;
}

FUNC(void, APPL_CODE) DemoHAL_TimerAck( void ) { }

/* Serial HAL */

FUNC(void, APPL_CODE) DemoHAL_SerialInit( void )
{

}

FUNC(void, APPL_CODE) DemoHAL_SerialWrite(
	P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA)	buffer,
	VAR(MemSize, AUTOMATIC)				length
) {
	(void)buffer;
	(void)length;
}
