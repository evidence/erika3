/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2017 Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * See LICENSE file.
 * ###*E*### */

/** \file   ee_internal_types.h
 *  \brief  HAL Internal Types.
 *
 *  This files contains all HAL internal types and symbols for specific
 *  Architecture in Erika Enterprise.
 *
 *  \note COULD BE raplaced by AUTOSAR Type definition paradigm or being the
 *        implementation
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#if (!defined(OSEE_HAL_INTERNAL_TYPES_H))
#define OSEE_HAL_INTERNAL_TYPES_H

#include "ee_platform_types.h"
#include "ee_api_types.h"

typedef struct OsEE_ISR_CTX_tag {
  OsEE_reg x0;
  OsEE_reg x1;
  OsEE_reg x2;
  OsEE_reg x3;
  OsEE_reg x4;
  OsEE_reg x5;
  OsEE_reg x6;
  OsEE_reg x7;
  OsEE_reg x8;
  OsEE_reg x9;
  OsEE_reg x10;
  OsEE_reg x11;
  OsEE_reg x12;
  OsEE_reg x13;
  OsEE_reg x14;
  OsEE_reg x15;
  OsEE_reg x16;
  OsEE_reg x17;
  OsEE_reg x18;
  OsEE_reg x30_lr;
  OsEE_reg elr_el1;
  OsEE_reg spsr_el1;
} OsEE_ISR_CTX;


typedef struct OsEE_CTX_tag {
  OsEE_reg x19;
  OsEE_reg x20;
  OsEE_reg x21;
  OsEE_reg x22;
  OsEE_reg x23;
  OsEE_reg x24;
  OsEE_reg x25;
  OsEE_reg x26;
  OsEE_reg x27;
  OsEE_reg x28;
  OsEE_reg x29_fp;
  OsEE_reg x30_lr;
  OsEE_reg daif;
  OsEE_reg flags;
  struct OsEE_CTX_tag * p_ctx;
} OsEE_CTX;

/* Stack Control Block: contine le informazioni dinamiche relative allo stack */
typedef struct OsEE_SCB_tag {
  OsEE_CTX      * p_tos; /* Saved Context */
} OsEE_SCB;

typedef struct OsEE_SDB_tag {
  OsEE_CTX   * p_bos; /* Base Of Stack */
  size_t       stack_size;
} OSEE_CONST   OsEE_SDB;

typedef struct OsEE_HDB_tag {
  OsEE_SDB          * p_sdb;
  OsEE_SCB          * p_scb;
  OsEE_isr_src_id     isr2_src;
 } OSEE_CONST OsEE_HDB;

typedef struct {
  enum {
    OSEE_ISR_CAT_INVALID = 0U,
    OSEE_ISR_CAT_1,
    OSEE_ISR_CAT_2
  } cat;
  union {
    void (*p_hnd_func) (void);
    TaskType tid;
  } hnd;
} OsEE_aarch64_hnd_type;

/* Used to override default definition of osEE_hal_change_context_from_isr2,
   in ee_std_change_context.h that is not inlined */
#define OSEE_ISR2_INLINE OSEE_STATIC_INLINE

#endif /* !OSEE_HAL_INTERNAL_TYPES_H */
