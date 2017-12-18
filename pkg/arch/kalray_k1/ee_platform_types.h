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

/** \file  ee_platform_types.h
 *  \brief  Platform Types.
 *
 *  This files contains all types and symbols for a specific Architecture in
 *  Erika Enterprise.
 *
*  \note  SHOULD BE raplaced by AUTOSAR Type definition paradigm. \n
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */

#if (!defined(OSEE_PLATFORM_TYPES_H))
#define OSEE_PLATFORM_TYPES_H

#include "ee_cfg.h"

/*******************************************************************************
                                Stack Utilities
 ******************************************************************************/

#define OSEE_STACK_ALIGN_SIZE         8U

#define OSEE_STACK_SCRATCH_AREA_SIZE  16U
#define OSEE_STACK_SCRATCH_AREA_INDEX \
  (OSEE_STACK_SCRATCH_AREA_SIZE/sizeof(OsEE_stack))

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <vbsp.h>
#include "ee_compiler.h"
#include "ee_utils.h"

#if (defined(OSEE_SINGLECORE)) && (!defined(OSEE_USED_CORES))
#define OSEE_USED_CORES (1U)
#elif (!defined(OSEE_USED_CORES))
#define OSEE_USED_CORES OSEE_K1_CORE_NUMBER
#endif /* OSEE_SINGLECORE || !OSEE_USED_CORES */

#if (!defined(OSEE_SINGLECORE)) &&\
  ((defined(OSEE_API_EXTENSION)) && defined(OSEE_API_DYNAMIC))
#define OSEE_HAS_JOBS
#endif /* !EE_SINGLECORE && (EE_API_EXTENSION && EE_API_DYNAMIC) */

#if (!defined(OSEE_BOOL_TYPE))
typedef enum {
  OSEE_FALSE = OSEE_M_FALSE,
  OSEE_TRUE  = OSEE_M_TRUE
} OsEE_bool;
#define OSEE_BOOL_TYPE OsEE_bool
#endif /* !OSEE_BOOL_TYPE */

/* Define HAL types */
typedef void *                OsEE_addr;
typedef uint32_t              OsEE_reg;
typedef uint32_t              OsEE_stack;

typedef uint8_t               OsEE_isr_src_id;
#define OSEE_ISR_SOURCE_TYPE  OsEE_isr_src_id

typedef uint8_t               OsEE_core_id;
#define OSEE_CORE_ID_TYPE     OsEE_core_id

typedef void (* OsEE_void_cb) ( void );

typedef __k1_fspinlock_t      OsEE_spin_lock __attribute__((aligned (8)));
#define OSEE_SPIN_UNLOCKED    _K1_FSPIN_UNLOCKED

#if (defined(OSEE_HAS_JOBS))
typedef uint32_t              OsEE_task_prio;
#define OSEE_TASK_PRIO_TYPE   OsEE_task_prio
#endif /* OSEE_HAS_JOBS */

/* Macro IDs numbers and boot */
#define OSEE_K1_CORE_NUMBER   BSP_NB_PE_MAX
#define OSEE_K1_MAIN_CORE     (0U)

#endif /* !OSEE_PLATFORM_TYPES_H */
