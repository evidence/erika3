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

/** \file   ee_platform_types.h
 *  \brief  Platform Types.
 *
 *  This files contains all types and symbols for a ARMv7-R
 *  Erika Enterprise.
 *
 *  \note COULD BE raplaced by AUTOSAR Type definition paradigm or being the
 *        implementation.
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#ifndef OSEE_PLATFORM_TYPES_H
#define OSEE_PLATFORM_TYPES_H

#include "ee_cfg.h"
#include "ee_arch_override.h"
#include "ee_compiler.h"
#include "ee_utils.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#if (defined(__cplusplus))
extern "C" {
#endif

#if (!defined(OSEE_BOOL_TYPE))
typedef enum {
  OSEE_FALSE = OSEE_M_FALSE,
  OSEE_TRUE  = OSEE_M_TRUE
} OsEE_bool;
#define OSEE_BOOL_TYPE OsEE_bool
#endif /* !OSEE_BOOL_TYPE */

#if (!defined(NULL))
#if (!defined(__cplusplus))
#define NULL ((void *)0)
#else   /* C++ */
#define NULL 0
#endif  /* C++ */
#endif  /* NULL */

/* Define HAL types */
typedef void *                OsEE_addr;
typedef uint32_t              OsEE_reg;
typedef int32_t               OsEE_sreg;
typedef uint32_t              OsEE_stack;

/* [SWS_Os_00583] The number of cores that can be controlled by the AUTOSAR OS
    shall be configured offline. A new configuration item (OsNumberOfCores)
    within the "OsOS" container is used to specify the maximum number of cores
    that are controlled by the AUTOSAR OS.
    If no value for (OsNumberOfCores) has been specified the number of cores
    shall be one. (SRS_Os_80001, SRS_Os_80011) */
/* [SWS_Os_00627]
    An implementation shall define a set of constants OS_CORE_ID_<No>
    of the type CoreIDType with <No> a value from 0 to "OsNumberOfCores - 1".
    (SRS_Os_80001) */
/* [SWS_Os_00628]
    An implementation shall offer a constant OS_CORE_ID_MASTER of the
    type CoreIDType that refers to the master core. (SRS_Os_80001) */
/** @brief ID type for cores */
typedef enum {
  OS_CORE_ID_0 = 0,
  OS_CORE_ID_MASTER = OS_CORE_ID_0,
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
  OS_CORE_ID_1 = 1,
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
  OS_CORE_ID_2 = 2,
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
  OS_CORE_ID_3 = 3,
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
  OS_CORE_ID_4 = 4,
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */
/* Numeric ID 5 is took by HSM core, how lame :(. */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
  OS_CORE_ID_6 = 6,
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */
  OS_CORE_ID_ARR_SIZE
} OsEE_core_id;

#define OSEE_CORE_ID_MAX      ((CoreNumType)OS_CORE_ID_ARR_SIZE - 1U)
#define OSEE_CORE_ID_TYPE     OsEE_core_id

typedef uint8_t               OsEE_prio;
#define OSEE_TASK_PRIO_TYPE   OsEE_prio

typedef uint16_t              OsEE_isr_src_id;
#define OSEE_ISR_SOURCE_TYPE  OsEE_isr_src_id

#define OSEE_TC_SRC_INVALID   ((OsEE_isr_src_id)-1)

#if (!defined(OSEE_SINGLECORE))
/** @brief Type for spinlocks */
typedef OsEE_reg volatile OsEE_spin_lock;

/** @brief Type for inter cpu barriers */
typedef struct {
  OsEE_reg volatile value;
} OsEE_barrier;
#endif /* !OSEE_SINGLECORE */

/* Override default implementation for some Kernel Types */

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_PLATFORM_TYPES_H */
