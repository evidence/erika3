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

/** \file   ee_hal_internal.h
 *  \brief  HAL internal.
 *
 *  This files contains all HAL Internals for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Michele Pes
 *  \date   2017
 */

#if (!defined(OSEE_HAL_INTERNAL_H))
#define OSEE_HAL_INTERNAL_H


/*==============================================================================
                                  Inclusions
 =============================================================================*/
#include "ee_arch_override.h"
#include "ee_utils.h"
#include "ee_platform_types.h"
#include "ee_hal.h"
#include "ee_hal_internal_types.h"
#include "ee_std_change_context.h"
#include "ee_kernel_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/*==============================================================================
                                  Macros
 =============================================================================*/


/*==============================================================================
                        Interrupt handling utilities
 =============================================================================*/

OSEE_STATIC_INLINE OsEE_bool osEE_hal_is_enabledIRQ( void )
{
  OsEE_reg flags;
  __asm__ volatile("pushf   \n\t");
  __asm__ volatile("pop %0  \n\t" : "=g"(flags));
  return ((OsEE_bool)(flags & 0x200));
}

/* Disable/Enable Interrupts */
OSEE_STATIC_INLINE void osEE_hal_disableIRQ( void )
{
  asm volatile("cli" : : : "memory");
}

OSEE_STATIC_INLINE void osEE_hal_enableIRQ( void )
{
  asm volatile("sti" : : : "memory");
}

/* Suspend/Resume Interrupts */
OSEE_STATIC_INLINE OsEE_reg osEE_hal_suspendIRQ(void)
{
  OsEE_reg flags;
  __asm__ volatile("pushf   \n\t");
  __asm__ volatile("pop %0  \n\t" : "=g"(flags));
  osEE_hal_disableIRQ();
  return flags;
}

OSEE_STATIC_INLINE void osEE_hal_resumeIRQ(OsEE_reg flags)
{
  __asm__ volatile("push %0 \n\t" : : "g"(flags));
  __asm__ volatile("popf    \n\t");
}

OSEE_STATIC_INLINE void osEE_hal_set_ipl(TaskPrio virt_prio) {
  (void)virt_prio; /* IPL not supported, yet */
}

OSEE_STATIC_INLINE OsEE_reg
  osEE_hal_prepare_ipl(OsEE_reg flags, TaskPrio virt_prio)
{
  /* IPL not supported, yet */
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
                          Ready Queue utilities
 =============================================================================*/

#if (defined(OSEE_RQ_MULTIQUEUE))
OSEE_STATIC_INLINE MemSize osEE_hal_get_msb (OsEE_rq_mask mask) {
  MemSize msb;
  MemSize const bits = (MemSize)((sizeof(mask) * CHAR_BIT) - 1U);
  if (mask == 0U) {
    msb = OSEE_RQ_MASK_EMPTY;
  } else if (bits <= 31U) {
    msb = (MemSize)(31 - __builtin_clz(mask));
  } else {
    msb = (MemSize)(63L - __builtin_clzl(mask));
  }
  return msb;
}
#endif /* OSEE_RQ_MULTIQUEUE */

/*==============================================================================
                              Start-up and ISR2
 =============================================================================*/


#if (defined(OSEE_HAS_SYSTEM_TIMER))
extern void osEE_x86_64_system_timer_init(void);
#endif /* OSEE_HAS_SYSTEM_TIMER */

OSEE_STATIC_INLINE FUNC(void, OS_CODE)
  osEE_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
)
{
  osEE_x86_64_int_send_eoi();
  osEE_change_context_from_task_end(p_from, p_to);
}

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_HAL_INTERNAL_H */
