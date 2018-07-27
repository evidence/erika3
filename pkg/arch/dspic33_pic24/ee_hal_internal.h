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

/** \file	ee_hal_internal.h
 *  \brief	HAL internal.
 *
 *  This files contains all HAL Internals for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Errico Guidieri
 *  \author	Giuseppe Serano
 *  \date	2018
 */

#ifndef OSEE_HAL_INTERNAL_H
#define	OSEE_HAL_INTERNAL_H

#include "ee_utils.h"
#include "ee_platform_types.h"
#include "ee_hal.h"
#include "ee_hal_internal_types.h"
#include "ee_kernel_types.h"
#include "ee_std_change_context.h"
#include "ee_dspic33_pic24_irq.h"
#include "ee_dspic33_pic24_ic.h"
#include "ee_dspic33_pic24_irqstub.h"
#include "ee_dspic33_pic24_system.h"

#if	(defined(OSEE_HAS_SYSTEM_TIMER))
#include "ee_dspic33_pic24_system_timer.h"
#endif	/* OSEE_HAS_SYSTEM_TIMER */

#if	(defined(OS_EE_ARCH_DSPIC33_PIC24_DSPIC33EV))
#include "ee_dspic33ev_internal.h"
#include "ee_dspic33ev_ic.h"
#if	(defined(OSEE_HAS_SYSTEM_TIMER))
#include "ee_dspic33ev_timers.h"
#endif	/* OSEE_HAS_SYSTEM_TIMER */
#else	/* OS_EE_ARCH_DSPIC33_PIC24_DSPIC33EV */
#error NO Valid MCU Selected!!!
#endif	/* OS_EE_ARCH_DSPIC33_PIC24_DSPIC33EV */

#if (defined(__cplusplus))
extern "C" {
#endif

/*==============================================================================
                                        Macros
 =============================================================================*/

/** \brief	Minimum IPL Value. */
#define	OSEE_DSPIC33_PIC24_IPL_MIN	(0x00U)

/** \brief	Maximum IPL Value. */
#define	OSEE_DSPIC33_PIC24_IPL_MAX	(0x07U)

#if	(!defined(OSEE_ISR2_MAX_PRIO))
/* 4 priorities left for ISR2 of the 8 available as default */
#define	OSEE_ISR2_MAX_PRIO	((TaskPrio)(OSEE_ISR2_PRIO_BIT + 3U))
#endif	/* OSEE_ISR2_MAX_PRIO */

/**
 * hardware priority 0 is not consider (tasks are running at hardware priorty 0!)
 * hardware priority 1 is 0xb 1000 0000 which is also OSEE_ISR2_PRIO_BIT
 * hardware priority 2 is 0xb 1000 0001
 * ...
 * hardware priority 7 is 0xb 1000 0110
 */
OSEE_STATIC_INLINE FUNC(TaskPrio, OS_CODE) OSEE_ALWAYS_INLINE
OSEE_ISR2_VIRT_TO_HW_PRIO(uint8_t virt_prio)
{
  return (TaskPrio) (((virt_prio) & (~OSEE_ISR2_PRIO_BIT)) + 1U) ;
}

#define	OSEE_ISR2_MAX_HW_PRIO			\
  (OSEE_ISR2_VIRT_TO_HW_PRIO(OSEE_ISR2_MAX_PRIO))

/*==============================================================================
                        Interrupt handling utilities
 =============================================================================*/

#ifdef	OSEE_DSPIC33_PIC24_SOFT_I_BIT	/* [GS]: Using INTCON2bits.GIE! */

extern VAR(OsEE_reg, OS_VAR_NO_INIT) osEE_dspic33_pic24_internal_ipl;

/* Disable/Enable Interrupts */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_disableIRQ( void )
{
  VAR(OsEE_reg, AUTOMATIC) ipl;
  SET_AND_SAVE_CPU_IPL(ipl, OSEE_DSPIC33_PIC24_IPL_MAX);
  if ( osEE_dspic33_pic24_internal_ipl > ipl )
  {
    osEE_dspic33_pic24_internal_ipl = ipl;
  }
}

OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_enableIRQ( void )
{
  if ( _IPL == OSEE_DSPIC33_PIC24_IPL_MAX ) {
    SET_CPU_IPL(osEE_dspic33_pic24_internal_ipl);
  }
}

/* Suspend/Resume Interrupts */
OSEE_STATIC_INLINE FUNC(OsEE_reg, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_suspendIRQ ( void )
{
  OsEE_reg ipl;
  SET_AND_SAVE_CPU_IPL(ipl, OSEE_DSPIC33_PIC24_IPL_MAX);
  return ipl;
}

OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_resumeIRQ ( OsEE_reg flags )
{
  RESTORE_CPU_IPL(flags);
}

#endif	/* OSEE_DSPIC33_PIC24_SOFT_I_BIT - [GS]: Using INTCON2bits.GIE! */

OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_set_ipl(
  VAR(TaskPrio, AUTOMATIC)	virt_prio
)
{
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    SET_CPU_IPL(OSEE_DSPIC33_PIC24_IPL_MIN);
  }
  else {
    SET_CPU_IPL(((uint8_t)(OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio) & 0x07U)));
  }
}

OSEE_STATIC_INLINE FUNC(OsEE_reg, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_prepare_ipl(
  VAR(OsEE_reg, AUTOMATIC)	flags,
  VAR(TaskPrio, AUTOMATIC)	virt_prio
)
{
  OsEE_reg ret_flags;
  TaskPrio tmp_flags;

  /* Touch unused parameter */
  (void)flags;
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    ret_flags = 0U;
  } else {
    tmp_flags = (OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio) & ((TaskPrio)0xFU));
    ret_flags = tmp_flags;
  }
  return ret_flags;
}

/*==============================================================================
                    HAL For Primitives Synchronization
 =============================================================================*/

/* Called as _first_ function of a primitive that can be called from within
 * an IRQ and from within a task. */
OSEE_STATIC_INLINE FUNC(OsEE_reg, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_begin_nested_primitive( void )
{
  OsEE_reg flags = _IPL;
  if (flags < OSEE_ISR2_MAX_HW_PRIO) {
    SET_CPU_IPL(OSEE_ISR2_MAX_HW_PRIO);
  }
  return flags;
}

/* Called as _last_ function of a primitive that can be called from
 * within an IRQ or a task. */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_end_nested_primitive(
  VAR(OsEE_reg, AUTOMATIC)	flag
)
{
  SET_CPU_IPL(((uint8_t)flag));
}

/*==============================================================================
                              Start-up and ISR2
 =============================================================================*/

#define	OSEE_CPU_STARTOS_INLINE	OSEE_STATIC_INLINE

/* Nothing to do. All the initialiazation is done in osEE_os_init */
OSEE_CPU_STARTOS_INLINE FUNC(OsEE_bool, OS_CODE) OSEE_ALWAYS_INLINE
osEE_cpu_startos ( void )
{
  OsEE_bool const cpu_startos_ok  = osEE_std_cpu_startos();
  if (cpu_startos_ok)
  {
    osEE_dspic33_pic24_system_init();
#if	(defined(OSEE_HAS_SYSTEM_TIMER))
    osEE_dspic33_pic24_system_timer_init();
#endif	/* OSEE_HAS_SYSTEM_TIMER */
  }
  return cpu_startos_ok;
}

OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
)
{
  osEE_change_context_from_task_end(p_from, p_to);
}

#if (defined(__cplusplus))
}
#endif

#endif	/* !OSEE_HAL_INTERNAL_H */
