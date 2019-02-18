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
 *  This files contains all HAL internal types and symbols for ARMv7-R
 *  Architecture in Erika Enterprise.
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#if (!defined(OSEE_HAL_INTERNAL_TYPES_H))
#define OSEE_HAL_INTERNAL_TYPES_H

#include "ee_platform_types.h"
#include "ee_api_types.h"

/* Reminder using STM/LDM instructions (in any of its variant,
   push & pop included, GPR with lower ID are stored at lower addresses) */
/* This data structure do not need to have length 8 bytes multiple,
   since AAPCS allows to have the stack not aligned to 8 bytes inside
   a function
   (It has to be be 8 bytes aligned only at function boundaries).
   Stack alignment after an IRQ need to be enforced by code. */
/* AAPCS states that d0-d7 and d16-d31 registers are scratch,
    but only 16 "d" registers are available in ARMv7-R variant */
/* Intra-procedure-call scratch register: r12 */
/* Linker Register: r14 (IRQ mode bank)
    [Value After Interrupt -4 (See ARMv7 ARM)] */
/* Saved Program Status Registers (IRQ mode bank). Done using SRS(FD).
   SPSR is considered to have the highest register ID. */

/* This data structure must have size that is 8 bytes multiple */
typedef struct OsEE_CTX_tag {
  struct OsEE_CTX_tag * p_ctx;
#if (defined(OSEE_CORTEX_R_VFP))
  OsEE_dreg d8;
  OsEE_dreg d9;
  OsEE_dreg d10;
  OsEE_dreg d11;
  OsEE_dreg d12;
  OsEE_dreg d13;
  OsEE_dreg d14;
  OsEE_dreg d15;
#endif /* OSEE_CORTEX_R_VFP */
  OsEE_reg  r4;
  OsEE_reg  r5;
  OsEE_reg  r6;
  OsEE_reg  r7;
  OsEE_reg  r8;
  OsEE_reg  r9;
  OsEE_reg  r10;
  OsEE_reg  r11;
  OsEE_reg  LR_usr; /* Linker Register: r14 (USR bank) */
} OsEE_CTX;

/* Stack Control Block: contine le informazioni dinamiche relative allo stack */
typedef struct {
  OsEE_CTX      * p_tos; /* Saved Context */
} OsEE_SCB;

typedef struct {
  OsEE_CTX   * p_bos; /* Base Of Stack */
  size_t       stack_size;
} OSEE_CONST   OsEE_SDB;

#if (!defined(OSEE_CORTEX_R_HDB_OVERRIDE))
typedef struct {
  OsEE_SDB          * p_sdb;
  OsEE_SCB          * p_scb;
  OsEE_isr_src_id     isr2_src;
} OSEE_CONST OsEE_HDB;
#endif /* OSEE_CORTEX_R_HDB_OVERRIDE */

typedef struct {
  enum {
    OSEE_ISR_TRAP,
    OSEE_ISR_CAT_1,
    OSEE_ISR_CAT_2
  } cat;
  union {
    OsEE_void_cb  p_hnd_func;
    TaskType      tid;
  } hnd;
} OsEE_cortex_r_hnd_type;

#endif /* !OSEE_HAL_INTERNAL_TYPES_H */
