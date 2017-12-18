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

/** \file  ee_internal_types.h
 *  \brief  HAL Internal Types.
 *
 *  This files contains all HAL internal types and symbols for specific
 *  Architecture in Erika Enterprise.
 *
*  \note  SHOULD BE raplaced by AUTOSAR Type definition paradigm. \n
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */

#if (!defined(OSEE_HAL_INTERNAL_TYPES_H))
#define OSEE_HAL_INTERNAL_TYPES_H

#include "ee_platform_types.h"

typedef struct OsEE_CTX_tag {
  OsEE_reg              R10;
  OsEE_reg              R11;
  OsEE_stack *          SP; /* $R12 is the Stack Pointer */
  OsEE_reg              R13;
  OsEE_reg              R14;
  OsEE_reg              R15;
  OsEE_reg              R16;
  OsEE_reg              R17;
  OsEE_reg              R18;
  OsEE_reg              R19;
  OsEE_reg              R20;
  OsEE_reg              R21;
  OsEE_reg              R22;
  OsEE_reg              R23;
  OsEE_reg              R24;
  OsEE_reg              R25;
  OsEE_reg              R26;
  OsEE_reg              R27;
  OsEE_reg              R28;
  OsEE_reg              R29;
  OsEE_reg              R30;
  OsEE_reg              R31;
  OsEE_addr             RA;
  OsEE_reg              PS;
  struct OsEE_CTX_tag * p_ctx;
  OsEE_reg              dummy;
} OsEE_CTX __attribute__((aligned (8)));

/* Stack Control Block: contine le informazioni dinamiche relative allo stack */
typedef struct OsEE_SCB_tag {
  OsEE_CTX *    p_tos; /* Saved Context */
} OsEE_SCB;

typedef struct OsEE_SDB_tag {
  OsEE_CTX *    p_bos; /* Base Of Stack */
  OsEE_reg      stack_size;
} OSEE_CONST OsEE_SDB;

typedef struct OsEE_HDB_tag {
  OsEE_SDB  *         p_sdb;
  OsEE_SCB  *         p_scb;
  OsEE_isr_src_id     isr_src;
} OSEE_CONST OsEE_HDB;

#if (defined(OSEE_API_DYNAMIC))
typedef struct OsEE_HPB_tag {
  OsEE_addr     pool_base;
  size_t        residual_mem;
  OsEE_SDB      sdb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
  OsEE_SCB      scb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
} OsEE_HPB;
#endif /* OSEE_API_DYNAMIC */

/* Supported Device Macros */
#define OSEE_K1_BSP_IT_TIMER_0 (0U)
#define OSEE_K1_BSP_IT_TIMER_1 (1U)

#if (defined(OSTICKDURATION))
extern void osEE_kalray_k1_system_timer_handler(void);
#endif /* OSTICKDURATION */

#endif /* !OsEE_HAL_INTERNAL_TYPES_H */
