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

/** \file   ee_scheduler_types.h
 *  \brief
 *
 *  Contains the types for different scheduler data structures
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2016
 */

#if (!defined(OSEE_SCHEDULER_TYPES_H))
#define OSEE_SCHEDULER_TYPES_H

#include "ee_cfg.h"
#include "ee_utils.h"
#include "ee_compiler.h"
#include "ee_platform_types.h"
#include "ee_api_types.h"

/* Forward OsEE_TDB declaration */
struct OsEE_TDB_tag;

/*==============================================================================
 *                    Scheduler Node (SN) Data Structure
 =============================================================================*/

typedef struct OsEE_SN_tag {
  P2VAR(struct OsEE_SN_tag, TYPEDEF, OS_APPL_DATA)  p_next;
  P2VAR(struct OsEE_TDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA) p_tdb;
} OsEE_SN;

LOCAL_INLINE FUNC_P2VAR(OsEE_SN, OS_APPL_DATA, OS_CODE)
  osEE_sn_alloc
(
  P2VAR(OsEE_SN *, AUTOMATIC, OS_APPL_DATA) pp_fist
)
{
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA) p_sn_allocated;

  p_sn_allocated          = (*pp_fist);
  (*pp_fist)              = p_sn_allocated->p_next;
  p_sn_allocated->p_next  = NULL;

  return p_sn_allocated;
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_sn_release
(
  P2VAR(OsEE_SN *, AUTOMATIC, OS_APPL_DATA) pp_first,
  P2VAR(OsEE_SN  , AUTOMATIC, OS_APPL_DATA) p_to_free
)
{
  p_to_free->p_next = (*pp_first);
  (*pp_first)       = p_to_free;
}

FUNC(OsEE_bool, OS_CODE)
  osEE_sn_priority_insert
(
  P2VAR(OsEE_SN *, AUTOMATIC, OS_APPL_DATA) pp_first,
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)   p_sn_new,
  CONST(OsEE_bool, AUTOMATIC)               hnd_act
);

/*==============================================================================
 *                     Ready Queue (RQ) Data Structure
 =============================================================================*/
#if (defined(OSEE_RQ_MULTIQUEUE))

#if (!defined(OSEE_RQ_MASK_TYPE))
#if (defined(OSEE_RQ_PRIO_NUM))
#if (OSEE_RQ_PRIO_NUM <= 8U)
#define OSEE_RQ_MASK_TYPE           VAR(uint8_t, TYPEDEF)
#elif (OSEE_RQ_PRIO_NUM <= 16U)
#define OSEE_RQ_MASK_TYPE           VAR(uint16_t, TYPEDEF)
#elif (OSEE_RQ_PRIO_NUM <= 32U)
#define OSEE_RQ_MASK_TYPE           VAR(uint32_t, TYPEDEF)
#elif (OSEE_RQ_PRIO_NUM <= 64U) && (!defined(__STRICT_ANSI__))
#define OSEE_RQ_MASK_TYPE           VAR(uint64_t, TYPEDEF)
#else
#error The OS cannot handle OSEE_RQ_PRIO_NUM priorities
#endif /* All OSEE_RQ_PRIO_NUMs */
#else   /* OSEE_RQ_PRIO_NUM */
#define OSEE_RQ_PRIO_NUM            (sizeof(OsEE_reg) * CHAR_BIT)
#define OSEE_RQ_MASK_TYPE           VAR(OsEE_reg, TYPEDEF)
#endif  /* OSEE_RQ_PRIO_NUM */
#elif (defined(OSEE_RQ_PRIO_NUM)) /* && OSEE_RQ_MASK_TYPE */
OSEE_STATIC_ASSERT(
  (sizeof(OSEE_RQ_MASK_TYPE) * CHAR_BIT) >= OSEE_RQ_PRIO_NUM,
  given_RQ_mask_type_not_big_enough
)
#else /* !OSEE_RQ_MASK_TYPE && !OSEE_RQ_PRIO_NUM */
#define OSEE_RQ_PRIO_NUM            (sizeof(OSEE_RQ_MASK_TYPE) * CHAR_BIT)
#endif /* !OSEE_RQ_MASK_TYPE */

typedef OSEE_RQ_MASK_TYPE           OsEE_rq_mask;
/* The following Macro is used against the result of osEE_hal_get_msb
 * that return an integer value that can be safely used as array index so a
 * MemSize (by definition). */
#define OSEE_RQ_MASK_EMPTY          ((MemSize)-1)

typedef struct OsEE_rq_queue_tag {
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA) p_head;
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA) p_tail;
} OsEE_rq_queue;

typedef struct OsEE_RQ_tag {
  VAR(OsEE_rq_queue, TYPEDEF) queue[OSEE_RQ_PRIO_NUM];
  VAR(OsEE_rq_mask, TYPEDEF)  mask;
} OsEE_RQ;

#else
#if (!defined(OSEE_RQ_LL))
#define OSEE_RQ_LL
#endif /* !OSEE_RQ_LL */
typedef OsEE_SN * OsEE_RQ;
#endif /* RQ Data Structures */
#endif /* !OSEE_SCHEDULER_TYPES_H */
