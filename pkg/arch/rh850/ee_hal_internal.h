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
 *  \author Errico Guidieri
 *  \date   2018
 */

#ifndef OSEE_HAL_INTERNAL_H
#define OSEE_HAL_INTERNAL_H

/*==============================================================================
                                  Inclusions
 =============================================================================*/
#include "ee_cfg.h"
#include "ee_platform_types.h"
#include "ee_utils.h"
#include "ee_compiler.h"
#include "ee_hal.h"
#include "ee_hal_internal_types.h"
#include "ee_std_change_context.h"
#include "ee_kernel_types.h"
#include "ee_get_kernel_and_core.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/*==============================================================================
                          Stack utilities
 =============================================================================*/
__asm volatile static void osEE_set_SP(const OsEE_stack * p_sp)
{
% reg p_sp
  mov p_sp sp
}

/*==============================================================================
                        Interrupt handling utilities
 =============================================================================*/
/* PSW.ID (Interrupt Disabled) is Bit 5 */
#define OSEE_RH850_PSW_ID_BIT OSEE_BIT(OsEE_reg,5U)

OSEE_STATIC_INLINE OsEE_bool OSEE_ALWAYS_INLINE osEE_hal_is_enabledIRQ(void)
{
  return (OSEE_RH850_STSR(OSEE_RH850_PSW) & OSEE_RH850_PSW_ID_BIT) == 0U;
}

/* Disable Interrupts */
__asm volatile static void osEE_hal_disableIRQ(void)
{
  di
}

/* Enable Interrupts */
__asm volatile static void osEE_hal_enableIRQ(void)
{
  ei
}

/* Suspend/Resume Interrupts */
OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE osEE_hal_suspendIRQ(void)
{
  OsEE_reg psw = OSEE_RH850_STSR(OSEE_RH850_PSW);
  if ((psw & OSEE_RH850_PSW_ID_BIT) == 0U) {
    osEE_hal_disableIRQ();
  }
  /* Do not allow reordering around this point */
  OSEE_BARRIER();
  return psw;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_hal_resumeIRQ(OsEE_reg flags)
{
  if ((flags & OSEE_RH850_PSW_ID_BIT) == 0U) {
    /* Do not allow reordering around this point */
    OSEE_BARRIER();
    osEE_hal_enableIRQ();
  }
}

/*==============================================================================
                    HAL For Primitives Atomicity
 =============================================================================*/
OSEE_STATIC_INLINE FUNC(uint8_t, OS_CODE) OSEE_ALWAYS_INLINE
OSEE_ISR2_VIRT_TO_HW_PRIO(TaskPrio virt_prio)
{
  return (uint8_t)(15U - (virt_prio & (~OSEE_ISR2_PRIO_BIT)));
}

#define OSEE_ISR2_MAX_HW_PRIO\
  (OSEE_ISR2_VIRT_TO_HW_PRIO(OSEE_ISR2_MAX_PRIO))

/* Called as _first_ function of a primitive that can be called from within
 * an IRQ and from within a task. */
OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE
  osEE_hal_begin_nested_primitive(void)
{
  /* Only bit [0,4] are valid bits */
  OsEE_reg plmr = (OSEE_RH850_STSR(OSEE_RH850_PLMR) & 0x1FU);

  /* PLM mask follow inverse order: greater PLM values means lower priority
     mask */
  if (plmr > OSEE_ISR2_MAX_HW_PRIO) {
    OSEE_RH850_LDSR(OSEE_RH850_PLMR, OSEE_ISR2_MAX_HW_PRIO);
  /* Note From RH850G4 ISA Manual:
     If registers which control the acceptance of interrupts, are updated,
     interrupts will be accepted with the new register settings if interrupt
     requests are present at the time of executing the subsequent instruction.
   */
  }

  /* Do not allow reordering around this point */
  OSEE_BARRIER();
  return plmr;
}

/* Called as _last_ function of a primitive that can be called from
 * within an IRQ or a task. */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_hal_end_nested_primitive(OsEE_reg flags)
{
  /* Do not allow reordering around this point */
  OSEE_BARRIER();
  OSEE_RH850_LDSR(OSEE_RH850_PLMR, flags);
  /* Note From RH850G4 ISA Manual:
     If registers which control the acceptance of interrupts, are updated,
     interrupts will be accepted with the new register settings if interrupt
     requests are present at the time of executing the subsequent instruction.
   */
}

/* We always use virtual priorities */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_hal_set_ipl(TaskPrio virt_prio)
{
  OsEE_reg plmr = (virt_prio < OSEE_ISR2_PRIO_BIT)?
    (OSEE_ISR_UNMASKED):
    (OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio));

  OSEE_RH850_LDSR(OSEE_RH850_PLMR, plmr);
  /* Note From RH850G4 ISA Manual:
     If registers which control the acceptance of interrupts, are updated,
     interrupts will be accepted with the new register settings if interrupt
     requests are present at the time of executing the subsequent instruction.
   */
  /* Do not allow reordering around this point */
  OSEE_BARRIER();
}

OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE
  osEE_hal_prepare_ipl(OsEE_reg flags, TaskPrio virt_prio)
{
  OsEE_reg plmr;
  /* Touch unused parameter */
  (void)flags;
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    plmr = OSEE_ISR_UNMASKED;
  } else
#if (defined(OSEE_SPINLOCKS_HAS_LOCK_METHOD))
  if (virt_prio == OSEE_ISR_ALL_PRIO) {
    /* I The PSW.ID bit must be set somewhere else, I don't need to do nothing
       here */
    plmr = flags;
  } else
#endif /* OSEE_SPINLOCKS_HAS_LOCK_METHOD */
  {
    plmr = OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio);
  }
  return plmr;
}

#if (defined(OSEE_RQ_MULTIQUEUE))
OSEE_STATIC_INLINE MemSize OSEE_ALWAYS_INLINE
  osEE_hal_get_msb(OsEE_rq_mask mask)
{
#if (OSEE_RQ_PRIO_NUM <= 32U)
  int32_t nbits = 32 - _sch1l(mask);
  return (MemSize)(nbits);
#elif (OSEE_RQ_PRIO_NUM <= 64U)
#error To Be Implemente
#else
#error RH850 ISA cannot handle a bitmask long OSEE_RQ_PRIO_NUM
#endif
}
#endif /* OSEE_RQ_MULTIQUEUE */

/*==============================================================================
                              Start-up and ISR2
 =============================================================================*/
#if (!defined(OSEE_LIB_EMBARK_G4MH))
extern void osEE_rh850_isr2_wrapper(TaskType tid,
  OsEE_rh850_exception_ctx const * p_ei_ctx);
#endif /* !OSEE_LIB_EMBARK_G4MH */

#if (defined(OSEE_HAS_SYSTEM_TIMER))
extern void osEE_rh850_initialize_system_timer(OsEE_TDB * p_tdb);
#endif /* OSEE_HAS_SYSTEM_TIMER */

#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
extern void osEE_rh850_initialize_core_stacks(void);
#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */
#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_HAL_INTERNAL_H */
