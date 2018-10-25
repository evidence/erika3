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

/*=============================================================================
                          HAL Types and structures
 ============================================================================*/
#include "ee_cfg.h"
#include "ee_platform_types.h"
#include "ee_compiler.h"
#include "ee_utils.h"
#include "ee_hal_irq.h"
#include "ee_tc_trapvec.h"

#if (!defined(__GNUC__))
#error Unsupported compiler!
#endif /* !__GNUC__ */

#if (defined(__cplusplus))
extern "C" {
#endif

/*==============================================================================
                            Array Utilities
 =============================================================================*/

/* Fill Pattern Used for Array Monitoring */
#if (!defined(OSEE_FILL_PATTERN))
#define OSEE_FILL_PATTERN (0xA5A5A5A5U)
#endif /* !OSEE_FILL_PATTERN */

/* Use Range Designated Initializers */
#define OSEE_FILL_ARRAY(array) \
  = {[0 ... (sizeof(array)/sizeof(array[0U]) - 1U)] = OSEE_FILL_PATTERN}

/*=============================================================================
                              Compilers Intrinsics
 ============================================================================*/

/* User Space CFSR IDs */
/* CPUn Identification Register TC1.6P */
#define OSEE_CSFR_CPU_ID     (0xFE18U)
/* CPUn Core Identification Register */
#define OSEE_CSFR_CORE_ID    (0xFE1CU)

#if (defined(__GNUC__))
/* Some of the TriCore instructions require an immediate operand.
   If the compiler cannot prove that the respective operand is a compile
   time constant, we get diagnostics like

   warning: asm operand <n> probably doesn't match constraints
   error: impossible constraint in 'asm'.

   We will use Function Macros for these instructions */
#define osEE_tc_get_csfr(reg_id)                              \
  (__extension__({                                            \
    OsEE_reg reg;                                             \
    __asm__ volatile (                                        \
      "mfcr %0, LO:%1" : "=d" (reg) : "i" (reg_id) : "memory" \
    );                                                        \
    reg;                                                      \
  }))

/* Some of the TriCore instructions require an immediate operand.
   We will use Function Macros for these instructions */
  
/* When you write a CSFR you need to force synchronization (isync) to
   avoid side-effects */
#define osEE_tc_set_csfr(reg_id, reg)               \
  __asm__ volatile (                                \
    "mtcr LO:%0, %1\n\t"                            \
    "isync" : : "i" (reg_id), "d" (reg) : "memory"  \
  )

/* Utility to set a GPR with special EABI meaning */
/* Two pre-processor steps to let macros expand */
#define osEE_tc_setareg2(areg, ptr) \
  __asm__ volatile ("mov.aa %%" #areg ", %0": : "a"(ptr): "memory")

#define osEE_tc_setareg(areg, ptr) osEE_tc_setareg2(areg, ptr)

/* Utility to read a GPR with special EABI meaning */
/* Two pre-processor steps to let macros expand */
#define osEE_tc_getareg2(areg, ptr) \
  __asm__ volatile ("mov.aa %0, %%" #areg : "=a"(ptr): : "memory")

#define osEE_tc_getareg(areg, ptr) osEE_tc_getareg2(areg, ptr)

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_debug(void) {
  /* The debug assembler instruction */
  __asm__ volatile ("debug" : : : "memory");
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_dsync(void) {
  /* The dsync assembler instruction */
  __asm__ volatile ("dsync" : : : "memory");
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_isync(void) {
  /* The isync assembler instruction */
  __asm__ volatile ("isync" : : : "memory");
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_svlcx(void) {
  /* The svlcx assembler instruction */
  __asm__ volatile ("svlcx" : : : "memory");
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_rslcx(void) {
  /* The rslcx assembler instruction */
  __asm__ volatile ("rslcx" : : : "memory");
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_rfe(void) {
  /* The rfe assembler instruction */
  __asm__ volatile ("rfe" : : : "memory");
}

OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE osEE_tc_clz(OsEE_reg mask) {
  return (OsEE_reg)__builtin_clz(mask);
}

OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE
  osEE_tc_extru(OsEE_reg reg, OsEE_reg start, uint8_t size)
{
  OsEE_reg res;
  /* The extr.u assembler instruction */
  __asm__ volatile (
    "extr.u %0,%1,%2,%3":
      "=d" (res): "d" (reg), "i" (start), "i" (size): "memory"
  );
  return res;
}

/* Symbols "GOTO" */
#define osEE_tc_jump(f)           __asm__ volatile ("j " OSEE_S(f))

#define osEE_tc_jump_abs(f)       __asm__ volatile ("ja " OSEE_S(f))

#define osEE_tc_indirect_jump(f)  __asm__ volatile ("ji %0"::"a"(f))

#define osEE_tc_jump_and_link(f)  __asm__ volatile ("jli %0"::"a"(f))

/* TODO: for other compilers */
#else
#error Unsupported compiler!
#endif /* __GNUC__ */

/*=============================================================================
                          Macros & Inline Functions
 ============================================================================*/

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_mmio_write8(OsEE_reg addr, uint8_t value)
{
  (*(uint8_t volatile *)addr) = value;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_mmio_write16(OsEE_reg addr, uint16_t value)
{
  (*(uint16_t volatile *)addr) = value;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_mmio_write32(OsEE_reg addr, uint32_t value)
{
  (*(uint32_t volatile *)addr) = value;
}

OSEE_STATIC_INLINE uint8_t OSEE_ALWAYS_INLINE
  osEE_mmio_read8(OsEE_reg addr)
{
  return (*(uint8_t volatile *)addr);
}

OSEE_STATIC_INLINE uint16_t OSEE_ALWAYS_INLINE
  osEE_mmio_read16(OsEE_reg addr)
{
  return (*(uint16_t volatile *)addr);
}

OSEE_STATIC_INLINE uint32_t OSEE_ALWAYS_INLINE
  osEE_mmio_read32(OsEE_reg addr)
{
  return (*(uint32_t volatile *)addr);
}

/*=============================================================================
                            Core IDs Utilities
 ============================================================================*/
OSEE_STATIC_INLINE OsEE_core_id OSEE_ALWAYS_INLINE osEE_get_curr_core_id(void)
{
  return (OsEE_core_id)osEE_tc_get_csfr(OSEE_CSFR_CORE_ID);
}

/*=============================================================================
                 Utility Macros for debugging and tracing purposes
 ============================================================================*/

OSEE_STATIC_INLINE OsEE_stack * OSEE_ALWAYS_INLINE osEE_get_SP(void)
{
  OsEE_stack * sp = NULL;
  /* put the stack pointer in a register in order to return it */
  __asm__ volatile ("mov.aa %0, %%SP" : "=a"(sp));
  return sp;
}

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_HAL_H */
