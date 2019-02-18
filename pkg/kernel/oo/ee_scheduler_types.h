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

/** \file   ee_scheduler_types.h
 *  \brief
 *
 *  Contains the types for different scheduler data structures
 *
 *  \author Errico Guidieri
 *  \date   2016
 */

#ifndef OSEE_SCHEDULER_TYPES_H
#define OSEE_SCHEDULER_TYPES_H

#include "ee_cfg.h"
#include "ee_utils.h"
#include "ee_compiler.h"
#include "ee_platform_types.h"
#include "ee_api_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/* Forward OsEE_TDB declaration */
struct OsEE_TDB_tag;

/*==============================================================================
 *                    Scheduler Node (SN) Data Structure
 =============================================================================*/

/**
 *  Scheduler node data structure.
 *  The Scheduler queues are composed by lists of nodes.
 */
typedef struct OsEE_SN_tag {
  /** next pointer for the list of scheduler nodes */
  P2VAR(struct OsEE_SN_tag, TYPEDEF, OS_APPL_DATA)  p_next;
  /** pointer to the task TDB in this scheduler node */
  P2VAR(struct OsEE_TDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA) p_tdb;
} OsEE_SN;

/**
 *  \brief Removes the first node from a node list.
 *  
 *  Removes the first node in a task list. Typically called on the free 
 *  node list.
 *  
 *  \param [in,out] pp_first Pointer to (the pointer to the first node 
 *                  of a queue)
 *  \return Returns a pointer to a node.
 */
LOCAL_INLINE FUNC_P2VAR(OsEE_SN, OS_APPL_DATA, OS_CODE)
  osEE_sn_alloc
(
  P2VAR(OsEE_SN *, AUTOMATIC, OS_APPL_DATA) pp_first
)
{
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA) p_sn_allocated;

  p_sn_allocated          = (*pp_first);
  (*pp_first)              = p_sn_allocated->p_next;
  p_sn_allocated->p_next  = NULL;

  return p_sn_allocated;
}

/**
 *  \brief Inserts a node as the first of a list.
 *  
 *  Inserts a node as the first of a list. Typically called on the free 
 *  node list to "release" a scheduler node.
 *  
 *  \param [in,out] pp_first Pointer to (the pointer to the first node of a 
 *                 queue)
 *  \param [in,out] p_to_free Node to be inserted in the list
 */
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

/**
 *  \brief Ordered insertion in a queue.
 *  
 *  This functon inserts a task inside a task queue, following the order of the
 *  task.
 *  
 *  \param [in,out] pp_first Pointer to (the pointer to the first node of a 
 *                 queue)
 *  \param [in]    p_sn_new Node to be inserted in the list following the 
 *                 priority of its task
 *  \param [in]    as_ready If OSEE_TRUE, use the ready_priority and not the 
 *                 current priority to queue the task. The usage of the ready
 *                 priority is useful when doing global schedulng. In AUTOSAR
 *                 conformance classes, onlt the current priority is used.
 *  
 *  \return The function returns OSEE_TRUE if the head pp_first changed.
 */
FUNC(OsEE_bool, OS_CODE)
  osEE_sn_priority_insert
(
  P2VAR(OsEE_SN *, AUTOMATIC, OS_APPL_DATA) pp_first,
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)   p_sn_new,
  CONST(OsEE_bool, AUTOMATIC)               as_ready
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
 * MemSize (by definition). Can be overridden by porting with a most
 * meaningful value */
#if (!defined(OSEE_RQ_MASK_EMPTY))
#define OSEE_RQ_MASK_EMPTY          ((MemSize)-1)
#endif /* !OSEE_RQ_MASK_EMPTY */

typedef struct {
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA) p_head;
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA) p_tail;
} OsEE_rq_queue;

typedef struct {
  VAR(OsEE_rq_queue, TYPEDEF) queue[OSEE_RQ_PRIO_NUM];
  VAR(OsEE_rq_mask, TYPEDEF)  mask;
} OsEE_RQ;

#else
#if (!defined(OSEE_RQ_LL))
/** in case it is not defined the OSEE_RQ_MULTIQUEUE, define the OSEE_RQ_LL,
 *  which is the linked list implementation.
 */
#define OSEE_RQ_LL
#endif /* !OSEE_RQ_LL */
/** When implemented with a linked list, a ready queue is a list of scheduler 
 *  nodes.
 */
typedef OsEE_SN * OsEE_RQ;
#endif /* RQ Data Structures */


#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_SCHEDULER_TYPES_H */
