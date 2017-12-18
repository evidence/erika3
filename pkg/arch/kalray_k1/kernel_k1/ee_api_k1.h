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

/*
 * ee_api_k1.h
 *
 *  Created on: Dec 16, 2014
 *      Author: e.guidieri
 */

#if (!defined(OSEE_API_K1_H))
#define OSEE_API_K1_H

#include "ee_cfg.h"

#if (defined(OSEE_HAS_JOBS))

#include "ee_platform_types.h"
#include "ee_k1_vbsp.h"
#include "ee_api_types.h"
#include "ee_hal.h"


typedef uint8_t   OsEE_job_id;
typedef OsEE_addr OsEE_job_param;
typedef void (* OsEE_job_func ) ( OsEE_job_param );
typedef uint8_t   OsEE_job_prio;

typedef mOS_vcore_set_t       CoreMask;
typedef OsEE_job_id           JobType;
typedef JobType *             JobRefType;

typedef OsEE_job_param        JobTaskParam;
typedef OsEE_job_func         JobTaskFunc;

#define INVALID_JOB_ID        ((OsEE_job_id)-1)

typedef enum OsEE_wait_cond_tag {
  VALUE_EQ,
  VALUE_NOT_EQ,
  VALUE_LT,
  VALUE_GT,
  VALUE_LT_OR_EQ,
  VALUE_GT_OR_EQ,
} OsEE_wait_cond;

typedef enum OsEE_block_policy_tag {
  BLOCK_OS,
  BLOCK_IMMEDIATLY,
  BLOCK_NO
} OsEE_block_policy;

typedef OsEE_reg             ValueType;
typedef ValueType *          ValueTypeRef;
typedef OsEE_spin_lock       SpinlockObjType;
typedef SpinlockObjType *    SpinlockObjTypeRef;
typedef OsEE_wait_cond       WaitCondType;
typedef OsEE_block_policy    BlockPolicyType;

typedef struct OsEE_blockable_value_tag {
  SpinlockObjType       lock;
  OsEE_SN *             blocked_queue;
  ValueType             value;
  WaitCondType          wait_cond;
  ValueType             right_value;
} OsEE_blockable_value;
typedef OsEE_bool               BoolType;
typedef BoolType *              BoolTypeRef;
typedef OsEE_blockable_value    BlockableValueType;
typedef BlockableValueType *    BlockableValueTypeRef;

#define OS_SERVICE_ID_K1          OS_SERVICE_ID_DYNAMIC
#define OSServiceId_CreateJob     (OS_SERVICE_ID_K1 + 0U)
#define OSServiceId_ActivateJob   (OS_SERVICE_ID_K1 + 1U)
#define OSServiceId_JoinJob       (OS_SERVICE_ID_K1 + 2U)
#define OSServiceId_SignalValue   (OS_SERVICE_ID_K1 + 3U)

LOCAL_INLINE void SpinInitObj ( SpinlockObjTypeRef SpinlockObjRef ) {
  osEE_hal_spin_init_lock(SpinlockObjRef);
}

LOCAL_INLINE void SpinLockObj ( SpinlockObjTypeRef SpinlockObjRef ) {
  osEE_hal_spin_lock(SpinlockObjRef);
}

LOCAL_INLINE void SpinUnlockObj ( SpinlockObjTypeRef SpinlockObjRef ) {
  osEE_hal_spin_unlock(SpinlockObjRef);
}

LOCAL_INLINE StatusType CheckCondition ( BoolTypeRef CondResultRef,
  ValueType Value, WaitCondType WaitCond, ValueType RightValue )
{
  StatusType status_type = E_OK;
  if ( CondResultRef != NULL ) {
    switch ( WaitCond ) {
      case VALUE_EQ:
        *CondResultRef  = (Value == RightValue);
      break;
      case VALUE_NOT_EQ:
        *CondResultRef  = (Value != RightValue);
      break;
      case VALUE_LT:
        *CondResultRef  = (Value < RightValue);
      break;
      case VALUE_GT:
        *CondResultRef  = (Value > RightValue);
      break;
      case VALUE_LT_OR_EQ:
        *CondResultRef  = (Value <= RightValue);
      break;
      case VALUE_GT_OR_EQ:
        *CondResultRef  = (Value >= RightValue);
      break;
      default:
        *CondResultRef = OSEE_FALSE;
        status_type    = E_OS_NOFUNC;
      break;
    }
  } else {
    status_type = E_OS_PARAM_POINTER;
  }
  return status_type;
}

StatusType CreateJob ( JobRefType JobIdRef, CoreMask JobAttendeeMask,
  TaskPrio JobPrio, JobTaskFunc JobFunc, JobTaskParam JobParam,
  MemSize StackSize );

StatusType ReadyJob ( JobType JobId, CoreMask ActivatedAttendeeMask );

StatusType ActivateJob ( JobType JobId, CoreMask ActivatedAttendeeMask );

StatusType GetJobID ( JobRefType JobIdRef );

StatusType JoinJob ( JobType JobId );

LOCAL_INLINE void InitBlockableValue (BlockableValueTypeRef BlockableValueRef,
  ValueType Value)
{
  if ( BlockableValueRef != NULL ) {
    osEE_hal_spin_init_lock(&BlockableValueRef->lock);
    BlockableValueRef->blocked_queue = NULL;
    BlockableValueRef->value         = Value;
    BlockableValueRef->right_value   = Value;
    BlockableValueRef->wait_cond     = VALUE_EQ;
  }
}

StatusType WaitCondition ( BlockableValueTypeRef BlockableValueRef,
  WaitCondType WaitCond, ValueType RightValue, BlockPolicyType BlockPolicy );

StatusType SignalValue (BlockableValueTypeRef BlockableValueRef,
  ValueType Value);

StatusType CommAndSchedule ( void );

#endif /* OSEE_HAS_JOBS */

#endif /* !OSEE_API_K1_H*/
