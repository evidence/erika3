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

/** \file	ee3_s32sdk_osif.c
 *  \brief	ERIKA 3 S32SDK osif implementation.
 *
 *  Based on baremetal implementation.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

#include "ee.h"
#include "osif.h"
#include <stddef.h>

#include "device_registers.h"

#include "devassert.h"

#if defined (USING_OS_FREERTOS)
#error "Wrong OSIF selected. USING_OS_BAREMETAL only supported!"
#endif

#ifndef	OSEE_SYSTEM_TIMER

/** \brief Converts milliseconds to ticks
 *
 *  in this case, one tick = one millisecond
 */
#define MSEC_TO_TICK(msec) (msec)

/* Only include headers for configurations that need them. */
#include "interrupt_manager.h"
#include "clock_manager.h"

static volatile uint32_t s_osif_tick_cnt = 0u;

static inline void osif_Tick(void)
{
	s_osif_tick_cnt++;
}	/* osif_Tick() */

static inline uint32_t osif_GetCurrentTickCount(void)
{
	return s_osif_tick_cnt;
}	/* osif_GetCurrentTickCount() */

void SysTick_Handler(void);

void SysTick_Handler(void)
{
	osif_Tick();
}	/* SysTick_Handler() */

static inline void osif_UpdateTickConfig(void)
{
	uint32_t core_freq = 0u;
	/* Get the correct name of the core clock */
	clock_names_t coreclk = CORE_CLK;
	status_t clk_status = CLOCK_SYS_GetFreq(coreclk, &core_freq);
	DEV_ASSERT(clk_status == STATUS_SUCCESS);
	DEV_ASSERT(core_freq > 0U);
	(void)clk_status;

	S32_SysTick->RVR = S32_SysTick_RVR_RELOAD(core_freq / 1000U);
	S32_SysTick->CSR = (
		S32_SysTick_CSR_ENABLE(1U) | S32_SysTick_CSR_TICKINT(1U)
	);
}	/* osif_UpdateTickConfig() */

static inline void osif_DisableIrqGlobal(void)
{
	INT_SYS_DisableIRQGlobal();
}	/* osif_DisableIrqGlobal() */

static inline void osif_EnableIrqGlobal(void)
{
    INT_SYS_EnableIRQGlobal();
}	/* osif_EnableIrqGlobal() */

#else	/* OSEE_SYSTEM_TIMER */

/** \brief Converts milliseconds to ticks
 *
 *  one tick = OS Tick duration in millisecond */
#define MSEC_TO_TICK(msec) ((msec)/((OSTICKDURATION / OSEE_KILO) / OSEE_KILO))

static inline uint32_t osif_GetCurrentTickCount(void)
{
	TickType	ticks = 0U;
	(void)GetCounterValue(OSEE_SYSTEM_TIMER, &ticks);
	return (uint32_t)ticks;
}	/* osif_GetCurrentTickCount() */

static inline void osif_UpdateTickConfig(void)
{
	/* do not update tick */
}	/* osif_UpdateTickConfig() */

static inline void osif_DisableIrqGlobal(void)
{
	DisableAllInterrupts();
}	/* osif_DisableIrqGlobal() */

static inline void osif_EnableIrqGlobal(void)
{
	EnableAllInterrupts();
}	/* osif_EnableIrqGlobal() */

#endif	/* OSEE_SYSTEM_TIMER */

void OSIF_TimeDelay(const uint32_t delay)
{
	osif_UpdateTickConfig();
	uint32_t start = osif_GetCurrentTickCount();
	uint32_t crt_ticks = osif_GetCurrentTickCount();
	uint32_t delta = crt_ticks - start;
	uint32_t delay_ticks = MSEC_TO_TICK(delay);
	while (delta < delay_ticks)
	{
		crt_ticks = osif_GetCurrentTickCount();
		delta = crt_ticks - start;
	}	/* while (delta < delay_ticks) */
}	/* OSIF_TimeDelay() */

uint32_t OSIF_GetMilliseconds(void)
{
#ifndef	OSEE_SYSTEM_TIMER
	/*
	 * Please make sure the timer is initialized before calling this
	 * function.
	 * For example, calling OSIF_TimeDelay(0) ensures that the timer is
	 * initialized without any other side-effects.
	 * If OSIF_TimeDelay or OSIF_SemaWait functions have been called,
	 * the timer is already initialized.
	 */

	/* This assumes that 1 tick = 1 millisecond */
	return osif_GetCurrentTickCount();
#else	/* OSEE_SYSTEM_TIMER */
	return (
		osif_GetCurrentTickCount() *
		((OSTICKDURATION / OSEE_KILO) / OSEE_KILO)
	);
#endif	/* OSEE_SYSTEM_TIMER */
}	/* OSIF_GetMilliseconds() */

status_t OSIF_MutexLock(const mutex_t * const pMutex, const uint32_t timeout)
{
	(void)pMutex;
	(void)timeout;

	return STATUS_SUCCESS;
}	/* OSIF_MutexLock() */

status_t OSIF_MutexUnlock(const mutex_t * const pMutex)
{
	(void)pMutex;

	return STATUS_SUCCESS;
}	/* OSIF_MutexUnlock() */

status_t OSIF_MutexCreate(mutex_t * const pMutex)
{
	(void)pMutex;

	return STATUS_SUCCESS;
}	/* OSIF_MutexCreate() */

status_t OSIF_MutexDestroy(const mutex_t * const pMutex)
{
	(void)pMutex;

	return STATUS_SUCCESS;
}	/* OSIF_MutexDestroy() */

status_t OSIF_SemaWait(semaphore_t * const pSem, const uint32_t timeout)
{
	DEV_ASSERT(pSem != NULL);

	uint32_t timeoutTicks;
	status_t osif_ret_code = STATUS_SUCCESS;

	osif_UpdateTickConfig();
	/* Convert timeout from milliseconds to ticks. */
	if (timeout == OSIF_WAIT_FOREVER)
	{
		timeoutTicks = OSIF_WAIT_FOREVER;
	}
	else
	{
		timeoutTicks = MSEC_TO_TICK(timeout);
	}

	uint32_t start = osif_GetCurrentTickCount();
	uint32_t end = (uint32_t)(start + timeoutTicks);
	uint32_t max = end - start;
	while (*pSem == 0u)
	{
		uint32_t crt_ticks = osif_GetCurrentTickCount();
		uint32_t delta = crt_ticks - start;
		if ((timeoutTicks != OSIF_WAIT_FOREVER) && (delta > max))
		{
			/* Timeout occured, stop waiting and return fail code */
			osif_ret_code = STATUS_TIMEOUT;
			break;
		}
	}

	if (osif_ret_code == STATUS_SUCCESS)
	{
		osif_DisableIrqGlobal();
		--(*pSem);
		osif_EnableIrqGlobal();
	}

	return osif_ret_code;
}	/* OSIF_SemaWait() */

status_t OSIF_SemaPost(semaphore_t * const pSem)
{
	DEV_ASSERT(pSem != NULL);

	status_t osif_ret_code = STATUS_SUCCESS;
	osif_DisableIrqGlobal();
	if (*pSem != 255u)
	{
		++(*pSem);
	}
	else
	{
		osif_ret_code = STATUS_ERROR;
	}

	osif_EnableIrqGlobal();

	return osif_ret_code;
}	/* OSIF_SemaPost() */

status_t OSIF_SemaCreate(semaphore_t * const pSem, const uint8_t initValue)
{
	DEV_ASSERT(pSem != NULL);
	osif_DisableIrqGlobal();
	*pSem = initValue;
	osif_EnableIrqGlobal();

	return STATUS_SUCCESS;
}	/* OSIF_SemaCreate() */

status_t OSIF_SemaDestroy(const semaphore_t * const pSem)
{
	DEV_ASSERT(pSem != NULL);

	(void)pSem;

	return STATUS_SUCCESS;
}	/* OSIF_SemaDestroy() */
