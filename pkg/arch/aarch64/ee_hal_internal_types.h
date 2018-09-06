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

#ifndef OSEE_HAL_INTERNAL_TYPES_H
#define OSEE_HAL_INTERNAL_TYPES_H

#include "ee_platform_types.h"
#include "ee_api_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

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

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_HAL_INTERNAL_TYPES_H */
