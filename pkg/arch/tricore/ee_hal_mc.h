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

/** \file   ee_hal.h
 *  \brief  HAL support visible to the application, for multi-core
 *          applications.
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

#ifndef OSEE_HAL_MC_H
#define OSEE_HAL_MC_H

#include "ee_cfg.h"

#if (!defined(OSEE_SINGLECORE))

#include "ee_platform_types.h"
#include "ee_hal.h"
#if (!defined(OSEE_TRICORE_ILLD))
#include "ee_tc_system.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#if (defined(OSEE_TC_CORE0_1_ISR_CAT)) || (defined(OSEE_TC_CORE0_1_ISR_TID))
#error In multicore environment IRQ priority 1 is already used by ERIKA\
 for Inter Cores Communication.
#else
#define OSEE_TC_CORE0_1_ISR_CAT     2
#define OSEE_TC_CORE0_1_ISR_TID     -1
#if (!OSEE_TC_CORE0_ISR_MAX_PRIO)
#define OSEE_TC_CORE0_ISR_MAX_PRIO  1
#endif /* !OSEE_TC_CORE0_ISR_MAX_PRIO */
#endif /* OSEE_TC_CORE0_1_ISR_CAT || OSEE_TC_CORE0_1_ISR_TID */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
#if (defined(OSEE_TC_CORE1_1_ISR_CAT)) || (defined(OSEE_TC_CORE1_1_ISR_TID))
#error In multicore environment IRQ priority 1 is already used by ERIKA\
 for Inter Cores Communication.
#else
#define OSEE_TC_CORE1_1_ISR_CAT     2
#define OSEE_TC_CORE1_1_ISR_TID     -1
#if (!OSEE_TC_CORE1_ISR_MAX_PRIO)
#define OSEE_TC_CORE1_ISR_MAX_PRIO  1
#endif /* !OSEE_TC_CORE1_ISR_MAX_PRIO */

#endif /* OSEE_TC_CORE1_1_ISR_CAT || OSEE_TC_CORE1_1_ISR_TID */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
#if (defined(OSEE_TC_CORE2_1_ISR_CAT)) || (defined(OSEE_TC_CORE2_1_ISR_TID))
#error In multicore environment IRQ priority 1 is already used by ERIKA\
 for Inter Cores Communication.
#else
#define OSEE_TC_CORE2_1_ISR_CAT     2
#define OSEE_TC_CORE2_1_ISR_TID     -1
#if (!OSEE_TC_CORE2_ISR_MAX_PRIO)
#define OSEE_TC_CORE2_ISR_MAX_PRIO  1
#endif /* !OSEE_TC_CORE2_ISR_MAX_PRIO */

#endif /* OSEE_TC_CORE2_1_ISR_CAT || OSEE_TC_CORE2_1_ISR_TID */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
#if (defined(OSEE_TC_CORE3_1_ISR_CAT)) || (defined(OSEE_TC_CORE3_1_ISR_TID))
#error In multicore environment IRQ priority 1 is already used by ERIKA\
 for Inter Cores Communication.
#else
#define OSEE_TC_CORE3_1_ISR_CAT     2
#define OSEE_TC_CORE3_1_ISR_TID     -1
#if (!OSEE_TC_CORE3_ISR_MAX_PRIO)
#define OSEE_TC_CORE3_ISR_MAX_PRIO  1
#endif /* !OSEE_TC_CORE3_ISR_MAX_PRIO */

#endif /* OSEE_TC_CORE3_1_ISR_CAT || OSEE_TC_CORE3_1_ISR_TID */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
#if (defined(OSEE_TC_CORE4_1_ISR_CAT)) || (defined(OSEE_TC_CORE4_1_ISR_TID))
#error In multicore environment IRQ priority 1 is already used by ERIKA\
 for Inter Cores Communication.
#else
#define OSEE_TC_CORE4_1_ISR_CAT     2
#define OSEE_TC_CORE4_1_ISR_TID     -1
#if (!OSEE_TC_CORE4_ISR_MAX_PRIO)
#define OSEE_TC_CORE4_ISR_MAX_PRIO  1
#endif /* !OSEE_TC_CORE4_ISR_MAX_PRIO */

#endif /* OSEE_TC_CORE4_1_ISR_CAT || OSEE_TC_CORE4_1_ISR_TID */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
#if (defined(OSEE_TC_CORE6_1_ISR_CAT)) || (defined(OSEE_TC_CORE6_1_ISR_TID))
#error In multicore environment IRQ priority 1 is already used by ERIKA\
 for Inter Cores Communication.
#else
#define OSEE_TC_CORE6_1_ISR_CAT     2
#define OSEE_TC_CORE6_1_ISR_TID     -1
#if (!OSEE_TC_CORE6_ISR_MAX_PRIO)
#define OSEE_TC_CORE6_ISR_MAX_PRIO  1
#endif /* !OSEE_TC_CORE6_ISR_MAX_PRIO */

#endif /* OSEE_TC_CORE6_1_ISR_CAT || OSEE_TC_CORE6_1_ISR_TID */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
#if (!defined(OSEE_CORE1_START_ADDR))
void osEE_tc_core1_start(void);
#define OSEE_CORE1_START_ADDR osEE_tc_core1_start
#endif /* !OSEE_CORE1_START_ADDR */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
#if (!defined(OSEE_CORE2_START_ADDR))
void osEE_tc_core2_start(void);
#define OSEE_CORE2_START_ADDR osEE_tc_core2_start
#endif /* !OSEE_CORE2_START_ADDR */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x4U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
#if (!defined(OSEE_CORE3_START_ADDR))
void osEE_tc_core3_start(void);
#define OSEE_CORE3_START_ADDR osEE_tc_core3_start
#endif /* !OSEE_CORE3_START_ADDR */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
#if (!defined(OSEE_CORE4_START_ADDR))
void osEE_tc_core4_start(void);
#define OSEE_CORE4_START_ADDR osEE_tc_core4_start
#endif /* !OSEE_CORE4_START_ADDR */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
#if (!defined(OSEE_CORE6_START_ADDR))
void osEE_tc_core6_start(void);
#define OSEE_CORE6_START_ADDR osEE_tc_core6_start
#endif /* !OSEE_CORE4_START_ADDR */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */
#else
#if (defined(__cplusplus))
extern "C" {
#endif
#endif /* OSEE_TRICORE_ILLD */

#if (defined(__GNUC__))
/* New HighTec GCC versions have built-in support for these functions, so
   I prefer to switch to the them, but I want to maintain hand-coded version
   commented here as reference, so MISRA: deal with it. */
#if 0
OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE osEE_tc_cmpswapw(
  OsEE_reg volatile * const p_var, OsEE_reg new_val, OsEE_reg expected_val
)
{
  /* The following force new_val in da with a even and expected_val in d(a+1) */
  /* __extension__ */ unsigned long long
    e_reg = ((unsigned long long)expected_val << 32U) | new_val;

  /* Register modifier A tell to reference the alternative name of the
     register (e.g. e2). "+d" constraint tell the compiler that the parameter
     is an input-output parameter */
  __asm__ volatile ("cmpswap.w [%1]0, %A0": "+d"(e_reg): "a"(p_var):
                      "memory");

  return (OsEE_reg)e_reg;
}

OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE osEE_tc_swapw(
  OsEE_reg volatile * const p_var, OsEE_reg new_val)
{
  /* I use the following way, instead of "+d" constraint, to tell the compiler
     that new_val is input-output parameter because it is shared between
     TASKING and GNUC compilers */
  __asm__ volatile ("swap.w [%1]0, %0": "=d"(new_val):
                      "a"(p_var), "0"(new_val): "memory");
  return new_val;
}

/** Insert LDMST instruction. Note that all operands must be word-aligned.
 */
OSEE_STATIC_INLINE void osEE_tc_ldmst(OsEE_reg volatile * const p_var,
  OsEE_reg mask, OsEE_reg value)
{
  __asm__ volatile("mov %H2,%1 \n\
                   ldmst [%0]0,%A2" :
                    : "a"(p_var), "d"(mask), "d"((unsigned long long)value)
                    : "memory"
                  );
}

/* Register modifier A tell to reference the alternative name of the
   register (e.g. e2). */
#define osEE_tc_imask_ldmst(address, value, offset, width)  \
  do {                                                      \
    unsigned long long tmp;                                 \
    __asm__ volatile("imask %A0,%1,%2,%3": "=d"(tmp)        \
                      : "d"(value), "d"(offset), "i"(width) \
                      : "memory");                          \
    __asm__ volatile ("ldmst [%0]0,%A1":                    \
                      : "a"(address), "d"(tmp)              \
                      : "memory");                          \
  } while(0)
#else
OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE osEE_tc_cmpswapw(
  OsEE_reg volatile * const p_var, OsEE_reg new_val, OsEE_reg expected_val
)
{
  return __builtin_tricore_cmpswapw((volatile void *)p_var, new_val, expected_val);
}

/** Insert LDMST instruction. Note that all operands must be word-aligned. */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_imask_ldmst(OsEE_reg volatile * const p_var, OsEE_reg value,
    OsEE_reg offset, OsEE_reg width)
{
  __builtin_tricore_ldmst((volatile void *)p_var, value, offset, width);
}
#endif
#else
#error Unsorported compiler!
#endif /* __GNUC__ */

/* Spinlocks Trivial Implementation */

/** @brief Acquire a spin-lock, spin inside if the spin-lock is already busy.
    @param p_lock spin-lock to be acquired. */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_hal_spin_lock(OsEE_spin_lock * p_lock)
{
  while (osEE_tc_cmpswapw(p_lock, 1U, 0U) != 0U) {
    ; /* Wait until you get the spinlock (i.e. write 1 on it)*/
  }
}

/** @brief Release a spin lock
    @param p_lock spin-lock to be released id */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_hal_spin_unlock(OsEE_spin_lock * p_lock)
{
  /* Commit all the changes in memory */
  osEE_tc_dsync();
  (*p_lock) = 0U;
}

/** @brief Try to acquire a spin-lock, immediately exit if it is already busy.
    @param spin_id spin-lock to be acquired id. */
OSEE_STATIC_INLINE OsEE_bool OSEE_ALWAYS_INLINE
  osEE_hal_try_spin_lock(OsEE_spin_lock * p_lock)
{
  OsEE_bool result = (osEE_tc_cmpswapw(p_lock, 1U, 0U) == 0U);
  return (result)? OSEE_TRUE: OSEE_FALSE;
}

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_SINGLECORE */
#endif /* !OSEE_HAL_MC_H */
