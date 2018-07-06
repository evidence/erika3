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

/** \file	task.c
 *  \brief	Task.
 *
 *  This file contains the code of application task 2 for Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* ERIKA Enterprise. */
#include "ee.h"

/* HAL */
#include "hal.h"

#define	HAL_DELAY_MS	1000U

#define	TASK_STR	(P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA))"Task2\r\n"
#define	TASK_STR_LEN	7U

uint16_t volatile Task2_count;

TASK(Task2)
{
	static OsEE_bool volatile stk_wrong = OSEE_FALSE;
	static OsEE_addr volatile old_sp = 0;

	DemoHAL_SerialWrite(TASK_STR, TASK_STR_LEN);

	DemoHAL_LedOn(DEMO_HAL_LED_3);

	DemoHAL_Delay(HAL_DELAY_MS);

	DemoHAL_LedOff(DEMO_HAL_LED_3);

	DemoHAL_Delay(HAL_DELAY_MS);

	if ( !stk_wrong ) {
		if (!old_sp) {
			old_sp = osEE_get_SP();
		}
		else if (old_sp != osEE_get_SP()) {
			stk_wrong = OSEE_TRUE;
			DemoHAL_LedOn(DEMO_HAL_LED_1);
			while (1U);
		}
	}

	++Task2_count;
	TerminateTask();

};
