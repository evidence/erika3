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
 *  \date   2019
 */

#if (!defined(OSEE_HAL_H))
#define OSEE_HAL_H

/*=============================================================================
                          HAL Types and structures
 ============================================================================*/
#include "ee_cfg.h"
#include "ee_platform_types.h"
#include "ee_compiler.h"
#include "ee_utils.h"
#include <ti/common/sys_common.h>
/* The following are needed for the generation of applcfg.c */
#include "ee_hal_internal_types.h"
#include "ee_ti_awr16xx_internal_types.h"

#if (!defined(__TI_ARM__))
#error Unsupported compiler!
#endif /* !__TI_ARM__ */

#if (defined(MSS_SYS_VCLK))
#if (defined(OSEE_CPU_CLOCK))
#if (MSS_SYS_VCLK != OSEE_CPU_CLOCK)
#error Wrong CPU_CLOCK clock configured the valid value is MSS_SYS_VCLK
#endif
#else
#define OSEE_CPU_CLOCK MSS_SYS_VCLK
#endif  /* OSEE_CPU_CLOCK */
#endif  /* MSS_SYS_VCLK */

/*=============================================================================
    ISR & System Timer Devices Macros & Handler (needed here for applcfg.c)
 ============================================================================*/
/* MSS_RTIA compare interrupt 0 */
#define OSEE_CORTEX_R_DEVICE_RTIC0   (0x2U)
/* MSS_RTIA compare interrupt 1 */
#define OSEE_CORTEX_R_DEVICE_RTIC1   (0x3U)
/* MSS_RTIA compare interrupt 0 */
#define OSEE_CORTEX_R_DEVICE_RTIC2   (0x4U)
/* MSS_RTIA compare interrupt 1 */
#define OSEE_CORTEX_R_DEVICE_RTIC3   (0x5U)

#define OSEE_CORTEX_R_SRC_INVALID    ((OsEE_isr_src_id)-1)
#if (!defined(ISR))
#define ISR(f) void f(void)
#endif /* !ISR */

#if (!defined(ISR1))
#define ISR1(f) void f(void)
#endif /* !ISR1 */

#if (!defined(ISR2))
#define ISR2 ISR
#endif /* !ISR2 */

#if (defined(OSEE_HAS_SYSTEM_TIMER))
extern void osEE_cortex_r_system_timer_handler(void);
#endif /* OSEE_HAS_SYSTEM_TIMER */

/*=============================================================================
                          Macros & Inline Functions
 ============================================================================*/

/* Intrinsics to write co-processors registers:
void __MCR (unsigned int coproc, unsigned int opc1, unsigned int src,
    unsigned int coproc_reg1, unsigned int coproc_reg2, unsigned int opc2);

  MCR coproc, opc1, src, CR<coproc_reg1>, CR<coproc_reg2>, opc2
*/

/* Intrinsic to read co-processors registers:
unsigned int __MRC(unsigned int coproc, unsigned int opc1,
  unsigned int coproc_reg1, unsigned int coproc_reg2, unsigned int opc2);

  MRC coproc, opc1, src, CR<coproc_reg1>, CR<coproc_reg2>, opc2
*/

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
#if 0
/* XXX: Maybe I need a global data structures like {KDB,KCB} for the HAL
        architecture dependent? */
extern OsEE_core_id osEE_cortex_r_vcore_id_offset;
#endif /* 0 */

OSEE_STATIC_INLINE OsEE_core_id osEE_cortex_r_get_vcore_id_raw( void ) {
  /* Multiprocessor Affinity Register (MPIDR) Provides a way to uniquely
     identify individual processors within a multi-processor system. */
  /* ARM DDI 0460D 4.3.6 */
  return (OsEE_core_id)__MRC(15, 0 , 0, 0, 5);
}

OSEE_STATIC_INLINE OsEE_core_id osEE_get_curr_core_id(void) {
  return  osEE_cortex_r_get_vcore_id_raw()
#if 0
    - osEE_cortex_r_vcore_id_offset
#endif /* 0 */
  ;
}

/*==============================================================================
        Utility Macros and Functions for debugging and tracing purposes
 =============================================================================*/

/* asm inline support of TI CGT ARM sucks too much to trust it,
   sadly the following need to become asm function :( */
extern OsEE_addr osEE_get_SP(void);

#endif /* !OSEE_HAL_H */
