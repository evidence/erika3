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

#if (!defined(OSEE_HAL_H))
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

/*==============================================================================
                          Macros & Inline Functions
 =============================================================================*/

#define OSEE_ARMV7_MRS(var,reg)   \
  __asm__ volatile("mrs %0, " OSEE_S(reg) "\n\t" : "=&r"(var) : : "memory")

#define OSEE_ARMV7_MSR(var, reg)  \
  __asm__ volatile("msr " OSEE_S(reg) ", %0\n\t" : : "r"(var) : "memory")

#define OSEE_ARMV7_MRC(var, coproc, opcode1, CRn, CRm, opcode2)\
  __asm__ volatile("mrc " OSEE_S(coproc) ", #" OSEE_S(OSEE_EVAL(opcode1))\
    ", %0, "  OSEE_S(CRn) ", " OSEE_S(CRm) ", #" OSEE_S(OSEE_EVAL(opcode2))\
    "\n\t" : "=&r"(var) : : "memory")

#define OSEE_ARMV7_MCR(var, coproc, opcode1, CRn, CRm, opcode2)\
  __asm__ volatile("mcr " OSEE_S(coproc) ", #" OSEE_S(OSEE_EVAL(opcode1))\
    ", %0, "  OSEE_S(CRn) ", " OSEE_S(CRm) ", #" OSEE_S(OSEE_EVAL(opcode2))\
    "\n\t" : : "r"(var) : "memory")

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
extern OsEE_core_id osEE_cortex_r_vcore_id_offset;

OSEE_STATIC_INLINE OsEE_core_id osEE_cortex_r_get_vcore_id_raw( void ) {
  OsEE_core_id vcore_id;
  /* Multiprocessor Affinity Register (MPIDR) Provides a way to uniquely
     identify individual processors within a multi-processor system. */
  /* ARM DDI 0460D 4.3.6 */
  OSEE_ARMV7_MRC(vcore_id, p15, 0 ,c0, c0, 5);
  return OSEE_R_GET(vcore_id, 7:0);
}

OSEE_STATIC_INLINE OsEE_core_id osEE_get_curr_core_id(void) {
  return  osEE_cortex_r_get_vcore_id_raw() - osEE_cortex_r__vcore_id_offset;
}

/*==============================================================================
                 Utility Macros for debugging and tracing purposes
 =============================================================================*/

/* Context handling functions for Tasking */
OSEE_STATIC_INLINE OsEE_addr osEE_get_SP ( void )
{
  OsEE_addr sp;
  __asm__ volatile("mov %0, SP\n\t" : "=&r"(sp));
  return sp;
}

#endif /* !OSEE_HAL_H */
