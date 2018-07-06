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

/** \file   ee_hal.h
 *  \brief  HAL support visible to the application.
 *
 *  This files contains all HAL for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#ifndef OSEE_HAL_H
#define OSEE_HAL_H

/*==============================================================================
                          HAL Types and structures
 =============================================================================*/
#include "ee_cfg.h"
#include "ee_platform_types.h"
#include "ee_compiler.h"
#include "ee_utils.h"

#if (!defined(__GNUC__))
#error Unsupported compiler!
#endif /* !__GNUC__ */

#if (defined(__cplusplus))
extern "C" {
#endif

/*==============================================================================
                          Macros & Inline Functions
 =============================================================================*/

#define OSEE_AARCH64_MRS(var,reg)   \
  __asm__ volatile("mrs %0, " OSEE_S(reg) "\n\t" : "=&r"(var) : : "memory")

#define OSEE_AARCH64_MSR(reg, var)  \
  __asm__ volatile("msr " OSEE_S(reg) ", %0\n\t" : :"r"(var) : "memory")

OSEE_STATIC_INLINE void osEE_mmio_write8(OsEE_reg addr, uint8_t value)
{
  (*(uint8_t volatile *)addr) = value;
}

OSEE_STATIC_INLINE void osEE_mmio_write16(OsEE_reg addr, uint16_t value)
{
  (*(uint16_t volatile *)addr) = value;
}

OSEE_STATIC_INLINE void osEE_mmio_write32(OsEE_reg addr,
  uint32_t value)
{
  (*(uint32_t volatile *)addr) = value;
}

OSEE_STATIC_INLINE uint8_t osEE_mmio_read8(OsEE_reg addr)
{
  return (*(uint8_t volatile *)addr);
}

OSEE_STATIC_INLINE uint16_t osEE_mmio_read16(OsEE_reg addr)
{
  return (*(uint16_t volatile *)addr);
}

OSEE_STATIC_INLINE uint32_t osEE_mmio_read32(OsEE_reg addr) {
  return (*(uint32_t volatile *)addr);
}

/*==============================================================================
                            Core IDs Utilities
 =============================================================================*/
/* XXX: Maybe I need a global data structures like {KDB,KCB} for the HAL
        architecture dependent? */
extern OsEE_core_id osEE_aarch64_vcore_id_offset;

OSEE_STATIC_INLINE OsEE_core_id osEE_aarch64_get_vcore_id_raw(void) {
  OsEE_core_id vcore_id;
  OSEE_AARCH64_MRS(vcore_id,mpidr_el1);
  return vcore_id;
}

OSEE_STATIC_INLINE OsEE_core_id osEE_get_curr_core_id(void) {
  return  osEE_aarch64_get_vcore_id_raw() - osEE_aarch64_vcore_id_offset;
}

/*==============================================================================
                            Array Utilities
 =============================================================================*/

/* Fill Pattern Used for Array Monitoring */
#if (!defined(OSEE_FILL_PATTERN))
#define OSEE_FILL_PATTERN 0xA5A5A5A5U
#endif /* !OSEE_FILL_PATTERN */

/* Use Range Designated Initializers */
#define OSEE_FILL_ARRAY(array) \
  = {[0 ... (sizeof(array)/sizeof(array[0U]) - 1U)] = OSEE_FILL_PATTERN}

/*==============================================================================
                 Utility Macros for debugging and tracing purposes
 =============================================================================*/

/* Context handling functions for Tasking */
OSEE_STATIC_INLINE OsEE_stack * osEE_get_SP(void)
{
  OsEE_stack * sp;
  __asm__ volatile("mov %0, sp\n" : "=&r"(sp));
  return sp;
}

/*==============================================================================
                           Generic Timer Support
 =============================================================================*/
#define OSEE_GTIMER_IRQ (27U)
/* Macro used as System Timer device */
#define OSEE_AARCH64_GTIMER OSEE_GTIMER_IRQ
#if (defined(OSEE_HAS_SYSTEM_TIMER))
extern void osEE_aarch64_system_timer_handler(void);
#endif /* OSEE_HAS_SYSTEM_TIMER */

OSEE_STATIC_INLINE OsEE_reg osEE_aarch64_gtimer_get_freq(void)
{
  OsEE_reg freq;
  OSEE_AARCH64_MRS(freq,cntfrq_el0);
  return freq;
}

OSEE_STATIC_INLINE OsEE_reg osEE_aarch64_gtimer_get_ticks(void)
{
  OsEE_reg ticks;
  OSEE_AARCH64_MRS(ticks,cntpct_el0);
  return ticks;
}

OSEE_STATIC_INLINE OsEE_reg osEE_aarch64_gtimer_ticks_to_ns(OsEE_reg ticks)
{
  return OSEE_TICKS_TO_NANO(ticks, osEE_aarch64_gtimer_get_freq());
}

enum osEE_aarch64_gtimer_mode {
  OSEE_AARCH64_GTIMER_COUNTDOWN = 0U,
  OSEE_AARCH64_GTIMER_UPPERCOUNT
};

OSEE_STATIC_INLINE void osEE_aarch64_gtimer_start(OsEE_reg timeout,
  enum osEE_aarch64_gtimer_mode mode)
{
  if (mode == OSEE_AARCH64_GTIMER_COUNTDOWN) {
    OSEE_AARCH64_MSR(cntv_tval_el0, timeout);
  } else {
    OSEE_AARCH64_MSR(cntv_cval_el0, timeout);
  }
  OSEE_AARCH64_MSR(cntv_ctl_el0, 1U);
}

/*=============================================================================
                                    ISR macros
 ============================================================================*/

/* Macro to declare ISR: always valid */
#define DeclareIsr(f) void f (void)

/* Declare an ISR (category 1) */
#define ISR1(f) void f (void)

/* Define an ISR (category 2). Used only for client code. */
#define ISR2(f) ISR1(f)


#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_HAL_H */
