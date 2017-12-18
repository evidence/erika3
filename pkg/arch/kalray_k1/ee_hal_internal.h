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
 *  \brief  ISA-dependent internal part of HAL
 *
 *  This files contains all HAL Internals for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */

#if (!defined(OSEE_HAL_INTERNAL_H))
#define OSEE_HAL_INTERNAL_H

/* Used to override default definition of osEE_hal_get_msb,
   in ee_std_change_context.h that is not inlined */
#define OSEE_GET_MSB_INLINE OSEE_STATIC_INLINE

#include "ee_platform_types.h"
#include "ee_compiler.h"
#include "ee_utils.h"
#include "ee_hal.h"
#include "ee_k1_irq.h"
#include "ee_hal_internal_types.h"
#include "ee_kernel_types.h"
#include "ee_std_change_context.h"

/* Used to place ERIKA Stacks in right section for memory protection and ORTI
   Stack filling, and handling stack alignment */
/* #define EE_STACK_ATTRIB EE_COMPILER_ALIGN(EE_STACK_ALIGN_SIZE) \
  EE_COMPILER_SECTION("ee_kernel_stack") */
#define OSEE_STACK_ATTRIB OSEE_COMPILER_ALIGN(OSEE_STACK_ALIGN_SIZE)

OSEE_STATIC_INLINE void osEE_set_SP ( register OsEE_addr reg )
{
  __asm__ volatile ("copy $r12 = %0" OSEE_K1_END_ASM_BUNDLE : : "r"(reg));
}

/* Standard HAL init support */
#define EE_STACK_GUARD_AREA EE_STACK_SCRATCH_AREA_SIZE

/*******************************************************************************
                        Interrupt handling utilities
 ******************************************************************************/
/* Disable/Enable Interrupts */
OSEE_STATIC_INLINE void osEE_hal_disableIRQ( void )
{
  mOS_it_disable();
}

OSEE_STATIC_INLINE void osEE_hal_enableIRQ( void )
{
  mOS_it_enable();
}

#define OSEE_VPS_IE_BIT OSEE_BIT(OsEE_reg,5) /* (1U << ((OsEE_reg)(5))) */

/* Suspend/Resume Interrupts */
OSEE_STATIC_INLINE OsEE_reg osEE_hal_suspendIRQ ( void )
{
  OsEE_core_id const core_id = osEE_get_curr_core_id ();
  OsEE_reg flags = _scoreboard_start.SCB_VCORE.PER_CPU[core_id].SFR_PS.word;

  if ((flags & OSEE_VPS_IE_BIT) != 0) {
    mOS_it_disable();
  }
  return flags;
}

OSEE_STATIC_INLINE void osEE_hal_resumeIRQ ( OsEE_reg flags )
{
  if ((flags & OSEE_VPS_IE_BIT) != 0) {
    mOS_it_enable();
  }
}

/*******************************************************************************
                    HAL For Primitives Synchronization
 ******************************************************************************/

#if (!defined(OSEE_ISR2_MAX_PRIO))
/* 2 priorities left for ISR2 of the 16 available as default */
#define OSEE_ISR2_MAX_PRIO (OSEE_ISR2_PRIO_BIT + 1U)
#endif /* OSEE_ISR2_MAX_PRIO */

#define OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio)\
  (((virt_prio) & (~OSEE_ISR2_PRIO_BIT)) + 1U)

#define OSEE_ISR2_MAX_HW_PRIO\
  OSEE_ISR2_VIRT_TO_HW_PRIO(OSEE_ISR2_MAX_PRIO)

OSEE_STATIC_INLINE void osEE_hal_set_ipl(TaskPrio virt_prio) {
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    mOS_set_it_level(0U);
  } else {
    mOS_set_it_level(OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio) & 0xFU);
  }
}

OSEE_STATIC_INLINE OsEE_reg
  osEE_hal_prepare_ipl(OsEE_reg flags, TaskPrio virt_prio)
{
  OsEE_reg ret_flags;
  /* Touch unused parameter */
  (void)flags;
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    ret_flags = 0U;
  } else {
    ret_flags = (OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio) & 0xFU);
  }
  return ret_flags;
}

/* Called as _first_ function of a primitive that can be called from within
 * an IRQ and from within a task. */
OSEE_STATIC_INLINE OsEE_reg osEE_hal_begin_nested_primitive( void )
{
  OsEE_core_id const core_id = osEE_get_curr_core_id();
  OsEE_reg flags = _scoreboard_start.SCB_VCORE.PER_CPU [core_id].SFR_PS.il;
  if (flags < OSEE_ISR2_MAX_HW_PRIO) {
    mOS_set_it_level(OSEE_ISR2_MAX_HW_PRIO);
  }

  return flags;
}

/* Called as _last_ function of a primitive that can be called from
 * within an IRQ or a task. */
OSEE_STATIC_INLINE void osEE_hal_end_nested_primitive(OsEE_reg flags)
{
  mOS_set_it_level(flags);
}

#if (!defined(OSEE_SINGLECORE))
OSEE_STATIC_INLINE void osEE_hal_signal_broadcast ( void ) {
  bsp_inter_pe_event_notify((mOS_vcore_set_t)(-1),
    BSP_IT_LINE);
}

OSEE_STATIC_INLINE void osEE_hal_signal_core ( CoreIdType core_id )
{
#if (!defined(OSEE_K1_FULL_PREEMPTION))
  bsp_inter_pe_event_notify((mOS_vcore_set_t)(1U << core_id),
    BSP_IT_LINE);
#else
  bsp_inter_pe_interrupt_raise((mOS_vcore_set_t)(1U << core_id),
    BSP_IT_LINE);
#endif /* !OSEE_K1_FULL_PREEMPTION */
}
#endif /* !OSEE_SINGLECORE */

#if (defined(OSEE_RQ_MULTIQUEUE))
OSEE_STATIC_INLINE MemSize osEE_hal_get_msb (OsEE_rq_mask mask) {
  return ((MemSize)31U - ((MemSize)__k1_clz(mask)));
}
#endif /* OSEE_RQ_MULTIQUEUE */

#endif /* OSEE_HAL_INTERNAL_H_ */
