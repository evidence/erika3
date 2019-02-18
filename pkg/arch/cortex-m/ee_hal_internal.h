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

/*==============================================================================
                                  Inclusions
 =============================================================================*/
#include "ee_arch_override.h"
#include "ee_utils.h"
#include "ee_platform_types.h"
#include "ee_hal.h"
#include "ee_hal_internal_types.h"
#include "ee_kernel_types.h"
#include "ee_std_change_context.h"
#include "ee_cortex_m_irq.h"
#include "ee_cortex_m_irqstub.h"
#include "ee_cortex_m_nvic.h"
#include "ee_cortex_m_system.h"

#if	(defined(OSEE_HAS_SYSTEM_TIMER))
#include "ee_cortex_m_system_timer.h"
#endif	/* OSEE_HAS_SYSTEM_TIMER */

#if (defined(__cplusplus))
extern "C" {
#endif

/*==============================================================================
                                        Macros
 =============================================================================*/

/** \brief	Priority Bit Number. */
#define	OSEE_CORTEX_M_PRIO_BIT_NUM	0x04U

/** \brief	Priority Bit Mask. */
#define	OSEE_CORTEX_M_PRIO_BIT_MASK	0x0FU

/** \brief	Priority Shift Bits. */
#define	OSEE_CORTEX_M_PRIO_SH_BITS	0x04U

#if	(!defined(OSEE_ISR2_MAX_PRIO))
/* 8 priorities left for ISR2 of the 16 available as default */
#define	OSEE_ISR2_MAX_PRIO	(OSEE_ISR2_PRIO_BIT + 7U)
#endif	/* OSEE_ISR2_MAX_PRIO */

#define	OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio)	(			\
	OSEE_ISR_PRI_1 - (((virt_prio) & (~OSEE_ISR2_PRIO_BIT)))	\
)

#define	OSEE_ISR2_MAX_HW_PRIO			\
	OSEE_ISR2_VIRT_TO_HW_PRIO(OSEE_ISR2_MAX_PRIO)

/*==============================================================================
                        Interrupt handling utilities
 =============================================================================*/

/* Disable/Enable Interrupts */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_disableIRQ( void )
{
  OSEE_CLI();
}

OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_enableIRQ( void )
{
  OSEE_SEI();
}

/* Suspend/Resume Interrupts */
OSEE_STATIC_INLINE FUNC(OsEE_reg, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_suspendIRQ ( void )
{
  register OsEE_reg sr;
  OSEE_GET_ISR(sr);
  osEE_hal_disableIRQ();
  return sr;
}

OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_resumeIRQ ( OsEE_reg flags )
{
  OSEE_BARRIER();
  OSEE_SET_ISR(flags);
}

OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_set_ipl(
  VAR(TaskPrio, AUTOMATIC)	virt_prio
)
{
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    OSEE_SET_IPL(OSEE_ISR_UNMASKED << OSEE_CORTEX_M_PRIO_SH_BITS);
  }
  else {
    OSEE_SET_IPL(
      ( OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio) & OSEE_CORTEX_M_PRIO_BIT_MASK )
      << OSEE_CORTEX_M_PRIO_SH_BITS
    );
  }
}

OSEE_STATIC_INLINE FUNC(OsEE_reg, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_prepare_ipl(
  VAR(OsEE_reg, AUTOMATIC)	flags,
  VAR(TaskPrio, AUTOMATIC)	virt_prio
)
{
  OsEE_reg ret_flags;
  /* Touch unused parameter */
  (void)flags;
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    ret_flags = 0U;
  } else {
    ret_flags = (
      OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio) & OSEE_CORTEX_M_PRIO_BIT_MASK
    );
  }
  return ret_flags;
}

#if (defined(OSEE_RQ_MULTIQUEUE))
OSEE_STATIC_INLINE MemSize OSEE_ALWAYS_INLINE
 osEE_hal_get_msb(OsEE_rq_mask mask)
{
  return ((MemSize)31U - (MemSize)OSEE_CLZ(mask));
}
#endif /* OSEE_RQ_MULTIQUEUE */

/*==============================================================================
                    HAL For Primitives Synchronization
 =============================================================================*/

/* Called as _first_ function of a primitive that can be called from within
 * an IRQ and from within a task. */
OSEE_STATIC_INLINE FUNC(OsEE_reg, OS_CODE) OSEE_ALWAYS_INLINE
osEE_hal_begin_nested_primitive( void )
{
  OsEE_reg flags = 0U;
  OSEE_GET_IPL(flags);
  flags >>= OSEE_CORTEX_M_PRIO_SH_BITS;
  if ( (flags == 0x00U) || (flags > OSEE_ISR2_MAX_HW_PRIO) ) {
    OSEE_SET_IPL(OSEE_ISR2_MAX_HW_PRIO << OSEE_CORTEX_M_PRIO_SH_BITS);
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
  OSEE_SET_IPL(flag << OSEE_CORTEX_M_PRIO_SH_BITS);
}

/*==============================================================================
                              Start-up and ISR2
 =============================================================================*/

#define	OSEE_CPU_STARTOS_INLINE	OSEE_STATIC_INLINE

#if	0	/* [GS]: T.B.C. */
#if	(defined(OS_EE_ARCH_CORTEX_M_M4F_FPU))
/* Enable FPU. */
extern FUNC(void, OS_CODE) osEE_hal_cortex_m4f_enable_fpu( void );
#endif	/* OS_EE_ARCH_CORTEX_M_M4F_FPU */
#endif	/* 0 - [GS]: T.B.C. */

#if (defined(OS_EE_LIB_S32_SDK))
/* Original vector table symbol, valid when S32 SDK is configured */
extern OsEE_reg __VECTOR_TABLE;
#endif /* OS_EE_LIB_S32_SDK */

/* Nothing to do. All the initialiazation is done in osEE_os_init */
OSEE_CPU_STARTOS_INLINE FUNC(OsEE_bool, OS_CODE) OSEE_ALWAYS_INLINE
osEE_cpu_startos ( void )
{
  OsEE_bool const cpu_startos_ok  = osEE_std_cpu_startos();
  if (cpu_startos_ok)
  {
#if (defined(OS_EE_LIB_S32_SDK))
    /* Restore original vector table (offset) (VTOR) */
    OSEE_CORTEX_M_NVIC_VTOR = (OsEE_reg)&__VECTOR_TABLE;
#endif /* OS_EE_LIB_S32_SDK */
#if	0	/* [GS]: T.B.C. */
#if	(defined(OS_EE_ARCH_CORTEX_M_M4F_FPU))
    osEE_hal_cortex_m4f_enable_fpu();
#endif	/* OS_EE_ARCH_CORTEX_M_M4F_FPU */
#endif	/* 0 - [GS]: T.B.C. */
#if	(defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
    osEE_cortex_m_stack_init();
#endif	/* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */
    osEE_cortex_m_system_init();
#if	(defined(OSEE_HAS_SYSTEM_TIMER))
    osEE_cortex_m_system_timer_init();
#endif	/* OSEE_HAS_SYSTEM_TIMER */
  }
  return cpu_startos_ok;
}

/* Trigger PendSV. */
extern FUNC(void, OS_CODE) osEE_cortex_m_trigger_pend_sv( void );

/* Pop a context from a stack, without actually calling kernel wrapper. used to
   return from ISR2 with PendSV */
extern FUNC(void, OS_CODE) osEE_cortex_m_restore_ctx
(
	P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)	p_to_tdb,
	P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)	p_to_scb
);

/* Scheduler Entry Point at Task/ISR2 termination. */
extern FUNC(void, OS_CODE) osEE_cortex_m_scheduler_task_end( void );

#if (defined(__cplusplus))
}
#endif

#endif	/* !OSEE_HAL_INTERNAL_H */
