/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 Evidence s.r.l.
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

/** \file   ee_hal_internal.h
 *  \brief  HAL internal.
 *
 *  This files contains all HAL Internals for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \author Giuseppe Serano
 *  \date   2016
 */

#if (!defined(OSEE_HAL_INTERNAL_H))
#define OSEE_HAL_INTERNAL_H

#include "ee_platform_types.h"
#include "ee_utils.h"
#include "ee_hal.h"
#include "ee_avr8_irq.h"
#include "ee_hal_internal_types.h"
#include "ee_kernel_types.h"
#include "ee_std_change_context.h"

#if (defined(OSEE_HAS_SYSTEM_TIMER))
#include "ee_atmega_timer1ctc.h"
#endif	/* OSEE_HAS_SYSTEM_TIMER */

/*==============================================================================
                                        Macros
 =============================================================================*/

/*
 * Provide global symbol and declare an assembly label.
 */
#define OSEE_AVR8_PROVIDE_SYM(symbol) \
  __asm__ __volatile__(               \
    ".global " OSEE_S(symbol) "\n"    \
    OSEE_S(symbol) ":\n" ::           \
  )

/*
 * Access a global symbol.
 */
#define OSEE_AVR8_REQUEST_SYM(symbol)   \
  __asm__ __volatile__(                 \
    ".global " OSEE_S(symbol)           \
    "\n ldi r30, lo8(" OSEE_S(symbol)   \
    ")\n" ::                            \
  )

/*==============================================================================
                        Interrupt handling utilities
 =============================================================================*/

/* Disable/Enable Interrupts */
OSEE_STATIC_INLINE void osEE_hal_disableIRQ( void )
{
  cli();
}

OSEE_STATIC_INLINE void osEE_hal_enableIRQ( void )
{
  sei();
}

/* Suspend/Resume Interrupts */
OSEE_STATIC_INLINE OsEE_reg osEE_hal_suspendIRQ ( void )
{
  register OsEE_reg sr = SREG;
  osEE_hal_disableIRQ();
  return sr;
}

OSEE_STATIC_INLINE void osEE_hal_resumeIRQ ( OsEE_reg flags )
{
  OSEE_BARRIER();
  SREG = flags;
}

OSEE_STATIC_INLINE void osEE_hal_set_ipl(TaskPrio virt_prio) {
  (void)virt_prio; /* No IPL support for AVR8 arch */
}

OSEE_STATIC_INLINE OsEE_reg
  osEE_hal_prepare_ipl(OsEE_reg flags, TaskPrio virt_prio)
{
  /* No IPL support for AVR8 arch */
  (void)virt_prio;
  return flags;
}

/*==============================================================================
                    HAL For Primitives Synchronization
 =============================================================================*/

/* Called as _first_ function of a primitive that can be called from within
 * an IRQ and from within a task. */
OSEE_STATIC_INLINE OsEE_reg osEE_hal_begin_nested_primitive( void )
{
  return osEE_hal_suspendIRQ();
}

/* Called as _last_ function of a primitive that can be called from
 * within an IRQ or a task. */
OSEE_STATIC_INLINE void osEE_hal_end_nested_primitive( OsEE_reg flag )
{
  osEE_hal_resumeIRQ(flag);
}

/*==============================================================================
                              Start-up and ISR2
 =============================================================================*/

extern void osEE_atmega_intvect(void);

#if (defined(OSTICKDURATION))
extern void osEE_avr8_system_timer_init(void);
#endif /* OSTICKDURATION */

#define OSEE_CPU_STARTOS_INLINE OSEE_STATIC_INLINE

/* Nothing to do. All the initialiazation is done in osEE_os_init */
OSEE_CPU_STARTOS_INLINE OsEE_bool osEE_cpu_startos ( void )
{
  /* Interrupt Vector Table Recall. */
  OsEE_void_cb volatile ivt             =  &osEE_atmega_intvect;
  OsEE_bool    const    cpu_startos_ok  = osEE_std_cpu_startos();
#if (defined(OSTICKDURATION))
  if (cpu_startos_ok) {
    osEE_avr8_system_timer_init();
  }
#endif /* OSTICKDURATION */
  return cpu_startos_ok;
}

OSEE_STATIC_INLINE FUNC(void, OS_CODE)
  osEE_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
)
{
  osEE_change_context_from_task_end(p_from, p_to);
}
#endif /* !OSEE_HAL_INTERNAL_H */
