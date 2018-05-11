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

/** \file	code.c
 *  \brief	ISRs.
 *
 *  This file contains the code of the ISRs for Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* ERIKA Enterprise. */
#include "ee.h"

/* HAL */
#include "hal.h"

#define OSEE_BREAK_POINT()  do {                                    \
    DemoHAL_LedOn(DEMO_HAL_LED_1);                                  \
    DisableAllInterrupts();                                         \
    while ( 1U ) {                                                  \
      ;                                                             \
    }                                                               \
  } while ( 0U )

ISR1(OscISR)
{
	OSEE_BREAK_POINT();
}

ISR1(AddrISR)
{
	OSEE_BREAK_POINT();
}

ISR1(SghtISR)
{
	OSEE_BREAK_POINT();
}

ISR1(MathISR)
{
	OSEE_BREAK_POINT();
}

ISR1(DmaISR)
{
	OSEE_BREAK_POINT();
}

ISR1(SoftISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Int0ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Ic1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Oc1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Dma0ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Ic2ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Oc2ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Timer2ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Timer3ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Spi1ErrISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Spi1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Uart1RxISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Uart1TxISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Adc1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Dma1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Nvm1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(SlaveI2C1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(MasterI2C1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Cmp1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(CnISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Int1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Dma2ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Oc3ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Oc4ISR)
{
	OSEE_BREAK_POINT();
}

/*
ISR2(Timer4ISR)
{
	OSEE_BREAK_POINT();
}
*/

ISR2(Timer5ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Int2ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Uart2RxISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Uart2TxISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Spi2ErrISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Spi2ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Can1RxISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Can1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Dma3ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Ic3ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Ic4ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(PsemISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Uart1ErrISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Uart2ErrISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Can1TxISR)
{
	OSEE_BREAK_POINT();
}

ISR2(CtmuISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Pwm1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Pwm2ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Pwm3ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(IcdISR)
{
	OSEE_BREAK_POINT();
}

ISR2(I2c1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Sent1ErrISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Sent1ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Sent2ErrISR)
{
	OSEE_BREAK_POINT();
}

ISR2(Sent2ISR)
{
	OSEE_BREAK_POINT();
}

ISR2(EccsbeISR)
{
	OSEE_BREAK_POINT();
}
