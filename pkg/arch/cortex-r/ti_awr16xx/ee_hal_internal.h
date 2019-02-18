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
 *  \author Errico Guidieri
 *  \date   2017
 */

#if (!defined(OSEE_HAL_INTERNAL_H))
#define OSEE_HAL_INTERNAL_H

#include "ee_cfg.h"
#include "ee_platform_types.h"
#include "ee_utils.h"
#include "ee_compiler.h"
#include "ee_hal.h"
#include "ee_hal_internal_types.h"
#include "ee_std_change_context.h"
#include "ee_kernel_types.h"
#include "ee_mmwave_osal_vim.h"

#define OSEE_ARMV7_CPSR_F 0x40
#define OSEE_ARMV7_CPSR_I 0x80

#define OSEE_ARMV7_CPSR_NOT_SET(f,m)  (((f) & (m)) == 0U)
#define OSEE_ARMV7_CPSR_I_NOT_SET(f)\
  OSEE_ARMV7_CPSR_NOT_SET(f,OSEE_ARMV7_CPSR_I)

OSEE_STATIC_INLINE OsEE_bool osEE_hal_is_enabledIRQ(void)
{
  OsEE_reg const flags = _get_CPSR();
  return OSEE_ARMV7_CPSR_I_NOT_SET(flags);
}

/* Disable/Enable Interrupts */
OSEE_STATIC_INLINE void osEE_hal_disableIRQ(void)
{
  _disable_IRQ();
}

OSEE_STATIC_INLINE void osEE_hal_enableIRQ(void)
{
  _enable_IRQ();
}

/* Suspend/Resume Interrupts */
OSEE_STATIC_INLINE OsEE_reg osEE_hal_suspendIRQ(void)
{
  return _disable_interrupts();
}

OSEE_STATIC_INLINE void osEE_hal_resumeIRQ(OsEE_reg flags)
{
  if (OSEE_ARMV7_CPSR_I_NOT_SET(flags)) {
    _enable_interrupts();
  }
}

OSEE_STATIC_INLINE FUNC(uint8_t, OS_CODE) OSEE_ALWAYS_INLINE
OSEE_ISR2_VIRT_TO_HW_PRIO(TaskPrio virt_prio)
{
  return (uint8_t)(OSEE_CORTEX_R_VIM_CHANNELS - 1U) -
    (uint8_t)(virt_prio & (~OSEE_ISR2_PRIO_BIT));
}

#define OSEE_ISR2_MAX_HW_PRIO\
  OSEE_ISR2_VIRT_TO_HW_PRIO(OSEE_ISR2_MAX_PRIO)

/* We always use virtual priorities */
OSEE_STATIC_INLINE void osEE_hal_set_ipl(TaskPrio virt_prio) {
  /* Nothing To Do */
  (void)virt_prio;
}

OSEE_STATIC_INLINE OsEE_reg
  osEE_hal_prepare_ipl(OsEE_reg flags, TaskPrio virt_prio)
{
  (void)virt_prio;
  return flags | OSEE_ARMV7_CPSR_I;
}

#if (defined(OSEE_RQ_MULTIQUEUE))
OSEE_STATIC_INLINE MemSize osEE_hal_get_msb (OsEE_rq_mask mask) {
  return ((MemSize)31U - ((MemSize)__clz((mask)));
}
#endif /* OSEE_RQ_MULTIQUEUE */

/*==============================================================================
                    HAL For Primitives Synchronization
 =============================================================================*/

/* Called as _first_ function of a primitive that can be called from within
 * an IRQ and from within a task. */
OSEE_STATIC_INLINE OsEE_reg osEE_hal_begin_nested_primitive(void)
{
  return osEE_hal_suspendIRQ();
}

/* Called as _last_ function of a primitive that can be called from
 * within an IRQ or a task. */
OSEE_STATIC_INLINE void osEE_hal_end_nested_primitive(OsEE_reg flags)
{
  osEE_hal_resumeIRQ(flags);
}

#if (defined(OSEE_HAS_SYSTEM_TIMER))
extern void osEE_cortex_r_initialize_system_timer(OsEE_TDB * p_tdb);
#endif /* OSEE_HAS_SYSTEM_TIMER */

#endif /* !OSEE_HAL_INTERNAL_H */
