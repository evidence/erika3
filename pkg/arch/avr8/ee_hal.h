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

/** \file   ee_hal.h
 *  \brief  HAL support visible to the application.
 *
 *  This files contains all HAL for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \author Errico Guidieri
 *  \author Giuseppe Serano
 *  \date   2016
 */

#if (!defined(OSEE_HAL_H))
#define OSEE_HAL_H

/*==============================================================================
                          HAL Types and structures
 =============================================================================*/
#include "ee_cfg.h"
#include "ee_utils.h"
#include "ee_compiler.h"
#include "ee_platform_types.h"

#if (!defined(OSEE_HAS_SYSTEM_TIMER))
#include "ee_atmega_timer1ctc.h"
#endif	/* !OSEE_HAS_SYSTEM_TIMER */

#if (!defined(__GNUC__))
#error Unsupported compiler!
#endif /* !__GNUC__ */

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
#if 0 /* Software Breakpoint support: temporary disabled */
/* Break point instruction, can be useful even when EE_DEBUG is not defined */
#define OSEE_BREAK_INST(num)  __asm__ volatile ("break " OSEE_S(num) "\n\t;;\n")

#define OSEE_BREAK_POINT_NUM  0x1FFFF /* TODO: Maybe another value have tbd */
#define OSEE_BREAK_POINT()    OSEE_BREAK_INST(OSEE_BREAK_POINT_NUM)
#define OSEE_GLOBAL_LABEL(label)  __asm__(".globl " #label "\n" #label ":")
#endif /* 0 */

/* Context handling functions for Tasking */
OSEE_STATIC_INLINE OsEE_addr osEE_get_SP ( void )
{
  return (OsEE_addr)_SFR_IO16(_SFR_IO_ADDR(SP));
}

OSEE_STATIC_INLINE OsEE_core_id osEE_get_curr_core_id ( void ) {
  return  (OsEE_core_id)0U;
}

#endif /* !OSEE_HAL_H */
