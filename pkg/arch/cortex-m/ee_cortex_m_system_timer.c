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

/** \file	ee_cortex_m_system_timer.c
 *  \brief	System Timer driver source file.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* ERIKA Enterprise Internals */
#include "ee_internal.h"
#include "ee_cortex_m_systick.h"

#if	(defined(OSEE_SYSTEM_TIMER_DEVICE))
#if (OSEE_SYSTEM_TIMER_DEVICE == OSEE_CORTEX_M_SYSTICK)

#if	(!defined(OSEE_CPU_CLOCK))
#if	(defined(OS_EE_ARCH_CORTEX_M_IMX8))
#define	OSEE_CPU_CLOCK	266666664U
#endif	/* OS_EE_ARCH_CORTEX_M_IMX8 */

#if	(defined(OS_EE_ARCH_CORTEX_M_STM32F4))
#define	OSEE_CPU_CLOCK	16000000U
#endif	/* OS_EE_ARCH_CORTEX_M_STM32F4 */

#if	(defined(OS_EE_ARCH_CORTEX_M_S32K1XX))
#define	OSEE_CPU_CLOCK	48000000U
#endif	/* OS_EE_ARCH_CORTEX_M_S32K1XX */
#endif	/* OSEE_CPU_CLOCK */

/** \brief	System Timer Initialization. */
FUNC(void, OS_CODE) osEE_cortex_m_system_timer_init(void)
{
  osEE_cortex_m_systick_set_period(
    ((OSTICKDURATION / OSEE_KILO) / OSEE_KILO) * (OSEE_CPU_CLOCK / OSEE_KILO)
  );
  osEE_cortex_m_systick_enable_int();
  osEE_cortex_m_systick_start();
}

/** \brief	System Timer Sleep. */
FUNC(void, OS_CODE) osEE_cortex_m_system_timer_sleep(void)
{
  osEE_cortex_m_systick_disable_int();
  osEE_cortex_m_systick_stop();
}

/** \brief	System Timer Wakeup. */
FUNC(void, OS_CODE) osEE_cortex_m_system_timer_wakeup(void)
{
  osEE_cortex_m_systick_enable_int();
  osEE_cortex_m_systick_start();
}

/*
 * System Timer ISR.
 */
ISR2(osEE_cortex_m_system_timer_handler)
{
  OsEE_CDB * p_cdb = osEE_get_curr_core();

  osEE_counter_increment(p_cdb->p_sys_counter_db);
}
#else
#error Unsupported System Timer Device!!!
#endif /* OSEE_SYSTEM_TIMER_DEVICE == OSEE_CORTEX_M_SYSTICK */
#endif /* OSEE_SYSTEM_TIMER_DEVICE */
