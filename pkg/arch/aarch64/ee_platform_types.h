/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2017 Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * See LICENSE file.
 * ###*E*### */

/** \file   ee_platform_types.h
 *  \brief  Platform Types.
 *
 *  This files contains all types and symbols for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \note COULD BE raplaced by AUTOSAR Type definition paradigm or being the
 *        implementation.
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#if (!defined(OSEE_PLATFORM_TYPES_H))
#define OSEE_PLATFORM_TYPES_H

#include "ee_cfg.h"

#define OSEE_STACK_ALIGN_SIZE         (16U)

#include "ee_compiler.h"
#include "ee_utils.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#if (defined(OSEE_AARCH64_SOC))
#include "ee_aarch64_gic.h"
#endif /* OSEE_AARCH64_SOC */

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
typedef uint64_t              OsEE_reg;
typedef uint64_t              OsEE_stack;

typedef uint8_t               OsEE_core_id;
#define OSEE_CORE_ID_TYPE     OsEE_core_id

#if (defined(OSEE_GIC_ISR_NUM)) && (OSEE_GIC_ISR_NUM > 256)
typedef uint16_t              OsEE_isr_src_id;
#else
typedef uint8_t               OsEE_isr_src_id;
#endif /* OSEE_GIC_ISR_NUM > 256 */
#define OSEE_ISR_SOURCE_TYPE  OsEE_isr_src_id

//typedef uint16_t              OsEE_task_prio;
//#define OSEE_TASK_PRIO_TYPE   OsEE_task_prio

typedef void (* OsEE_void_cb) ( void );

typedef uint8_t               OsEE_isr_prio;

/* Override default implementation for some Kernel Types */
//typedef size_t                OsEE_mem_size;
//#define OSEE_MEM_SIZE_TYPE    OsEE_mem_size

#endif /* !OSEE_PLATFORM_TYPES_H */
