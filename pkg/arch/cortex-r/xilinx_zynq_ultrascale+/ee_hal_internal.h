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
#include "ee_hal_irq.h"

/*==============================================================================
                        Interrupt handling utilities
 =============================================================================*/

/* The Interrupt Controller uses a certain ammount of the 8 available bits to
   handle interrupt priorities. These bits are always the most significats of
   the priority byte. So if the GIC handle 32 priorities, it uses the 5 msb.
   This meand that the logic virtual ISR priority value have to be left-shifted
   of 3 positions. */
#if (!defined(OSEE_ARMV7_GIC_PRIO_SHIFT))
#define OSEE_ARMV7_GIC_PRIO_SHIFT (0x3U)
#endif /* OSEE_ARMV7_GIC_PRIO_SHIFT */

#define OSEE_ARMV7_GIC_PRIO_UNUSED_MASK  OSEE_ONES(OSEE_ARMV7_GIC_PRIO_SHIFT)

/* Number of different priorities handled by the GIC */
#define OSEE_ARMV7_GIC_MAX_NUM_PRIO\
  ((TaskPrio)0xFFU /(OSEE_BIT(TaskPrio,OSEE_ARMV7_GIC_PRIO_SHIFT)))

#define OSEE_ARMV7_GIC_RUNNING_PRIO_IDLE (0xFFU)

/* Is the maximun numerical value that the field prio can have, but correspond
   to the minimun priority. Not need to turn off the not implemented bit.
   It's granted by GIC specification to work. */
#define OSEE_ARMV7_GIC_PRIO_UNMASKED\
  (OSEE_ARMV7_GIC_RUNNING_PRIO_IDLE /* ^ OSEE_ARMV7_GIC_PRIO_UNUSED_MASK*/)

/* Interrupt controller access addresses. */
/* Priority Mask */
#define OSEE_ARMV7_GIC_ICCPMR_OFFSET  (0x04U)
/* Binary Point */
#define OSEE_ARMV7_GIC_ICCBPR_OFFSET  (0x08U)
/* Interrupt Acknowledge */
#define OSEE_ARMV7_GIC_ICCIAR_OFFSET  (0x0CU)
/* End Of Interrupt */
#define OSEE_ARMV7_GIC_EOIR_OFFSET    (0x10U)
/* Running Priority Offset */
#define OSEE_ARMV7_GIC_ICCRPR_OFFSET  (0x14U)

/* Per CPU banked registers offset from GICD base */
#define OSEE_ARMV7_GIC_CPU_OFFSET (0x1000U)

/* Base Address for per CPU banked GIC registers */
#define OSEE_ARMV7_GIC_CPU_ADDR\
  (XPAR_SCUGIC_0_DIST_BASEADDR + OSEE_ARMV7_GIC_CPU_OFFSET)

/* Priority Mask Address */
#define OSEE_ARMV7_GIC_ICCPMR_ADDR\
  (OSEE_ARMV7_GIC_CPU_ADDR + OSEE_ARMV7_GIC_ICCPMR_OFFSET)

/* Binary Point Address */
#define OSEE_ARMV7_GIC_ICCBPR_ADDR\
  (OSEE_ARMV7_GIC_CPU_ADDR + OSEE_ARMV7_GIC_ICCBPR_OFFSET)

/* Interrupt Acknowledge Address */
#define OSEE_ARMV7_GIC_ICCIAR_ADDR\
  (OSEE_ARMV7_GIC_CPU_ADDR + OSEE_ARMV7_GIC_ICCIAR_OFFSET)

/* End Of Interrupt Address */
#define OSEE_ARMV7_GIC_EOIR_ADDR\
  (OSEE_ARMV7_GIC_CPU_ADDR + OSEE_ARMV7_GIC_EOIR_OFFSET)

/* Running Priority Address */
#define OSEE_ARMV7_GIC_ICCRPR_ADDR\
  (OSEE_ARMV7_GIC_CPU_ADDR + OSEE_ARMV7_GIC_ICCRPR_OFFSET)

/* Priority Mask Register */
#define OSEE_ARMV7_GIC_ICCPMR\
  (*((uint8_t volatile *)OSEE_ARMV7_GIC_ICCPMR_ADDR))

/* Binary Point Register */
#define OSEE_ARMV7_GIC_ICCBPR\
  (*((uint32_t const volatile *)OSEE_ARMV7_GIC_ICCBPR_ADDR))

/* End Of Interrupt Register */
#define OSEE_ARMV7_GIC_EOIR\
  (*((uint32_t volatile *)OSEE_ARMV7_GIC_EOIR_ADDR))

/* Running Priority Register */
#define OSEE_ARMV7_GIC_ICCRPR\
  (*((uint8_t const volatile *)OSEE_ARMV7_GIC_ICCRPR_ADDR))

#define OSEE_ARMV7_CPSR_F 0x40
#define OSEE_ARMV7_CPSR_I 0x80

#define OSEE_ARMV7_CPSR_C_NOT_SET(f,m)  (((f) & (m)) == 0U)
#define OSEE_ARMV7_CPSR_I_NOT_SET(f)\
  OSEE_ARMV7_CPSR_C_NOT_SET(f,OSEE_ARMV7_CPSR_I)

OSEE_STATIC_INLINE OsEE_bool osEE_hal_is_enabledIRQ( void )
{
  OsEE_reg flags;
  OSEE_ARMV7_MRS(flags,CPSR);
  return OSEE_ARMV7_CPSR_I_NOT_SET(flags);
}

/* Disable/Enable Interrupts */
OSEE_STATIC_INLINE void osEE_hal_disableIRQ( void )
{
  __asm__ volatile("cpsid if\n\t");
}

OSEE_STATIC_INLINE void osEE_hal_enableIRQ( void )
{
  __asm__ volatile("cpsie if\n\t");
}

/* Suspend/Resume Interrupts */
OSEE_STATIC_INLINE OsEE_reg osEE_hal_suspendIRQ(void)
{
  OsEE_reg flags;
  OSEE_ARMV7_MRS(flags,CPSR);
  osEE_hal_disableIRQ();
  return flags;
}

OSEE_STATIC_INLINE void osEE_hal_resumeIRQ(OsEE_reg flags)
{
  if (OSEE_ARMV7_CPSR_I_NOT_SET(flags)) {
    osEE_hal_enableIRQ();
  }
}

#define OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio)\
  ((TaskPrio)((OSEE_ARMV7_GIC_MAX_NUM_PRIO -\
    (((virt_prio) & (~OSEE_ISR2_PRIO_BIT)) + 1U)) <<\
      OSEE_ARMV7_GIC_PRIO_SHIFT))

#define OSEE_ISR2_MAX_HW_PRIO\
  OSEE_ISR2_VIRT_TO_HW_PRIO(OSEE_ISR2_MAX_PRIO)

/* We always use virtual priorities */
OSEE_STATIC_INLINE void osEE_hal_set_ipl(TaskPrio virt_prio) {
#if (defined(OSEE_ARMV7_GIC_REQUIRE_CS))
  OsEE_reg flags = osEE_hal_suspendIRQ();
#endif /* OSEE_ARMV7_GIC_REQUIRE_CS */
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    OSEE_ARMV7_GIC_ICCPMR = OSEE_ARMV7_GIC_PRIO_UNMASKED;
  } else {
    OSEE_ARMV7_GIC_ICCPMR = OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio);
  }
#if (defined(OSEE_ARMV7_GIC_REQUIRE_CS))
  osEE_hal_resumeIRQ(flags);
#endif /* OSEE_ARMV7_GIC_REQUIRE_CS */
}

OSEE_STATIC_INLINE OsEE_reg
  osEE_hal_prepare_ipl(OsEE_reg flags, TaskPrio virt_prio)
{
  OsEE_reg ret_flags;
  /* Touch unused parameter */
  (void)flags;
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    ret_flags = OSEE_ARMV7_GIC_PRIO_UNMASKED;
  } else {
    ret_flags = OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio);
  }
  return ret_flags;
}

#if (defined(OSEE_RQ_MULTIQUEUE))
OSEE_STATIC_INLINE MemSize osEE_hal_get_msb (OsEE_rq_mask mask) {
  return ((MemSize)31U - ((MemSize)__builtin_clz((mask)));
}
#endif /* OSEE_RQ_MULTIQUEUE */

/*==============================================================================
                    HAL For Primitives Synchronization
 =============================================================================*/

/* Called as _first_ function of a primitive that can be called from within
 * an IRQ and from within a task. */
OSEE_STATIC_INLINE OsEE_reg osEE_hal_begin_nested_primitive(void)
{
  OsEE_reg const flags = OSEE_ARMV7_GIC_ICCPMR;
  if (flags > OSEE_ISR2_MAX_HW_PRIO) {
    OSEE_ARMV7_GIC_ICCPMR = OSEE_ISR2_MAX_HW_PRIO;
  }
  return flags;
}

/* Called as _last_ function of a primitive that can be called from
 * within an IRQ or a task. */
OSEE_STATIC_INLINE void osEE_hal_end_nested_primitive(OsEE_reg flags)
{
  OSEE_ARMV7_GIC_ICCPMR = ((TaskPrio)flags);
}

/*==============================================================================
                              Start-up and ISR2
 =============================================================================*/
/* Start-Up function (C Part) */
extern void osEE_cortex_r_c_start(void);

#endif /* !OSEE_HAL_INTERNAL_H */
