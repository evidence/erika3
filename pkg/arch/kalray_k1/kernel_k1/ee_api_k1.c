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
 * ee_api_k1.c
 *
 *  Created on: Dec 16, 2014
 *      Author: e.guidieri
 */

#include "ee_hal_internal.h"
#include "ee_k1_context.h"
#include "ee_kernel.h"
#include <assert.h>
#include "ee_kernel_k1.h"

#if (defined(OSEE_HAS_JOBS))

extern OsEE_HPB osEE_pool;

StatusType CreateJob ( JobRefType JobIdRef, CoreMask JobAttendeeMask,
  TaskPrio JobPrio, JobTaskFunc JobFunc, JobTaskParam JobParam,
  MemSize StackSize )
{
  StatusType status_type;
  if ( (JobIdRef == NULL) || (JobFunc == NULL) ) {
    status_type = E_OS_PARAM_POINTER;
  } else {
    OsEE_reg  const JobAttendeeCount = __k1_cbs(JobAttendeeMask);
    OsEE_reg  const flags            = osEE_hal_begin_nested_primitive();

    /* Enter in the critical section to create the Job */
    osEE_lock_kernel();

    if ( (KDB_WJ.p_kcb_wj->job_index < OSEE_MAX_NUM_JOB) &&
      (osEE_pool.residual_mem >=
        (JobAttendeeCount * (StackSize + OSEE_STACK_GUARD_AREA))) )
    {
      if ( JobAttendeeMask != 0U ) {
        /* Check if it's possible to create the Job, and lock the cores that
           attends to the job */
        /* Actually Task Core allocation rule is "First found is used" */
        if ( KDB_WJ.kdb.p_kcb->free_task_index <
            (OSEE_TASK_ARRAY_SIZE - JobAttendeeCount) )
        {
          OsEE_reg     i;
          /* Allocate New Job */
          OsEE_JOB *   p_alloc_job;

          (*JobIdRef) = KDB_WJ.p_kcb_wj->job_index++;
          p_alloc_job = &KDB_WJ.p_kcb_wj->jobs[(*JobIdRef)];

          /* Fill the Job */
          p_alloc_job->job_func             = JobFunc;
          p_alloc_job->job_param            = JobParam;
          p_alloc_job->job_prio             = JobPrio;
          p_alloc_job->job_id               = (*JobIdRef);
          /* Init the Job Lock */
          osEE_hal_spin_init_lock(&p_alloc_job->lock);
          /* Check if it will possible to reserve SN for each TASKs */
          status_type = E_OK;
#if (!defined(OSEE_SCHEDULER_GLOBAL))
          for ( i = 0U; i < OSEE_K1_CORE_NUMBER; ++i ) {
            if ( (JobAttendeeMask & OSEE_BIT(CoreMask,i)) != 0 ) {
              OsEE_CDB * const p_cdb = osEE_get_core(i);
              if (p_cdb->p_ccb->free_sn_counter == 0U) {
                status_type = E_OS_LIMIT;
                break;
              }
           }
          }
#else
          if ( KCB_WJ.kcb.free_sn_counter < JobAttendeeCount) {
            status_type = E_OS_LIMIT;
          }
#endif
          if ( status_type == E_OK ) {
            for ( i = 0U; i < OSEE_K1_CORE_NUMBER; ++i ) {
              /* Fill the Job */
              if ( (JobAttendeeMask & OSEE_BIT(CoreMask,i)) != 0 ) {
                TaskType  task_id;
                StatusType const create_status = osEE_create_task (i, &task_id,
                  OSEE_TASK_TYPE_EXTENDED, osEE_job_wrapper, JobPrio,
                    JobPrio, 1U, StackSize );
                if ( create_status == E_OK ) {
                  p_alloc_job->task_attendees_id[i] = task_id;
                  p_alloc_job->attendee_mask |= OSEE_BIT(CoreMask,i);
                } else {
                  /* THIS SHALL NEVER HAPPENS !!! */
                  assert(false);
                }
              } else {
                p_alloc_job->task_attendees_id[i] = INVALID_TASK;
              }
            }
            /* Set the Job as Terminated */
            p_alloc_job->terminated_task_mask = p_alloc_job->attendee_mask;
          }
        } else {
          status_type = E_OS_LIMIT;
        }
      } else {
        status_type = E_OS_NOFUNC;
      }
    } else {
      status_type = E_OS_LIMIT;
    }

    /* Release the Kernel & Commit the changes in memory */
    osEE_unlock_kernel();
    osEE_hal_end_nested_primitive(flags);
  }
  return status_type;
}

StatusType ReadyJob ( JobType JobId, CoreMask JobAttendeeMask ) {
  StatusType status_type;
  if ( JobId < KDB_WJ.p_kcb_wj->job_index ) {
    CoreIdType core_id = osEE_get_curr_core_id();
    /* Activate all the JOB TASKs */
    OsEE_reg   flags = osEE_hal_begin_nested_primitive();

    status_type = osEE_k1_activate_job(JobId, JobAttendeeMask, core_id
#if (defined(OSEE_K1_FULL_PREEMPTION))
      , OSEE_FALSE
#endif /* OSEE_K1_FULL_PREEMPTION */
    );

    osEE_hal_end_nested_primitive(flags);
  } else {
    status_type = E_OS_ID;
  }
  return status_type;
}

StatusType ActivateJob ( JobType JobId, CoreMask JobAttendeeMask ) {
  StatusType status_type;
  if ( JobId < KDB_WJ.p_kcb_wj->job_index ) {
    CoreIdType core_id  = osEE_get_curr_core_id();
    /* Activate all the JOB TASKs */
    OsEE_reg flags      = osEE_hal_begin_nested_primitive();

    status_type = osEE_k1_activate_job(JobId, JobAttendeeMask, core_id
#if (defined(OSEE_K1_FULL_PREEMPTION))
      , OSEE_TRUE
#endif /* OSEE_K1_FULL_PREEMPTION */
    );

    if ( status_type == E_OK ) {
      osEE_k1_optimized_task_preemption_point();
    }
    osEE_hal_end_nested_primitive(flags);
  } else {
    status_type = E_OS_ID;
  }
  return status_type;
}

StatusType JoinJob ( JobType JobId ) {
  StatusType  status_type;
  MemSize     job_index = __k1_umem_read32(&KDB_WJ.p_kcb_wj->job_index);
  if ( JobId < job_index ) {
    OsEE_JOB  * const p_job   = &KDB_WJ.p_kcb_wj->jobs[JobId];
    OsEE_TDB  * const p_curr  = osEE_get_curr_task();
    /* Invalidate the Job line */
    /* __k1_dcache_invalidate_mem_area((uintptr_t)p_JOB, sizeof(*p_JOB)); */
    if ( p_curr->p_tcb->current_prio < p_job->job_prio) {
      while (
        __k1_umem_read32(&p_job->attendee_mask) !=
          __k1_umem_read32(&p_job->terminated_task_mask) )
      {
#if (!defined(OSEE_K1_FULL_PREEMPTION))
        osEE_k1_optimized_task_preemption_point();
#else
        ; /* Nothing TO DO */
#endif /* !OSEE_K1_FULL_PREEMPTION */
      }
      status_type = E_OK;
    } else {
      status_type = E_OS_ACCESS;
    }
  } else {
    status_type = E_OS_ID;
  }
  return status_type;
}

StatusType GetJobID ( JobRefType JobIdRef ) {
  register StatusType ev;

  if ( JobIdRef == NULL ) {
    ev = E_OS_PARAM_POINTER;
  } else {
    OsEE_CDB  * const p_cdb   = osEE_get_curr_core();
    OsEE_TDB  * const p_curr  = p_cdb->p_ccb->p_curr;
    OsEE_JOB  * const p_job   = KCB_WJ.tid_to_job[p_curr->tid];

    if ( p_job != NULL ) {
      (*JobIdRef) = p_job->job_id;
      ev = E_OK;
    } else {
      (*JobIdRef) = INVALID_JOB_ID;
      ev = E_OS_NOFUNC;
    }
  }

  return ev;
}

StatusType CommAndSchedule ( void ) {
#if (defined(OSEE_HAS_COMM_HOOK))
  if ( isPendingOffload() ) {
    if ( osEE_hal_spin_trylock(&comm_lock) ) {
      CommunicationHook();
      osEE_hal_spin_unlock(&comm_lock);
    }
  }
#endif /* OSEE_HAS_COMM_HOOK */

  osEE_k1_optimized_task_preemption_point();

  return E_OK;
}

static StatusType osEE_k1_block_on_value ( OsEE_blockable_value *
  blockable_value_ref, OsEE_wait_cond wait_cond, OsEE_reg right_value )
{
  StatusType        status_type;
  OsEE_KDB  * const p_kdb   = osEE_get_kernel();
  OsEE_CDB  * const p_cdb   = osEE_get_curr_core();
  OsEE_CCB  * const p_ccb   = p_cdb->p_ccb;
  OsEE_TDB  * const p_curr  = p_ccb->p_curr;
  OsEE_reg    const flags   = osEE_hal_begin_nested_primitive();

  if ( p_curr->task_type != OSEE_TASK_TYPE_EXTENDED ) {
    status_type = E_OS_ACCESS;
  } else {
    OsEE_TDB * p_to;

    __k1_fspinlock_lock(&blockable_value_ref->lock);

    if ( blockable_value_ref->blocked_queue == NULL ) {
      BoolType  cond_result;
      ValueType value = __k1_umem_read32(&blockable_value_ref->value);

      status_type = CheckCondition(&cond_result, value, wait_cond, right_value);

      if ( (status_type == E_OK) && (cond_result == OSEE_FALSE) ) {
        blockable_value_ref->right_value = right_value;
        blockable_value_ref->wait_cond   = wait_cond;

        /* Prepare to put the TASK inside the BlockableValue queue...
         * It will be really done in EE_scheduler_task_wrapper calling
         * EE_scheduler_task_saving_available */
        p_to = osEE_scheduler_task_block_current(p_kdb, p_cdb,
          &blockable_value_ref->blocked_queue);

#if (defined(OSEE_SCHEDULER_GLOBAL)) && (!defined(OSEE_SINGLECORE))
        p_ccb->p_lock_to_be_released = &blockable_value_ref->lock;
#else
        osEE_hal_spin_unlock( &blockable_value_ref->lock );
#endif /* OSEE_SCHEDULER_GLOBAL && !OSEE_SINGLECORE */

        osEE_change_context_from_running(p_curr, p_to);
      } else {
        __k1_fspinlock_unlock(&blockable_value_ref->lock);
      }
    } else {
      __k1_fspinlock_unlock(&blockable_value_ref->lock);
      status_type = E_OS_ACCESS;
    }
  }
  osEE_hal_end_nested_primitive(flags);
  return status_type;
}

StatusType WaitCondition ( BlockableValueTypeRef BlockableValueRef,
  WaitCondType WaitCond, ValueType RightValue, BlockPolicyType BlockPolicy)
{
  StatusType     status_type = E_OK;
  ValueType      value;
  OsEE_bool      cond_result;
  if ( BlockableValueRef == NULL ) {
    status_type = E_OS_PARAM_POINTER;
  } else {
    do {
      value       = __k1_umem_read32(&BlockableValueRef->value);
      status_type = CheckCondition (&cond_result, value, WaitCond, RightValue);

      if ( status_type == E_OK ) {
#if (defined(OSEE_HAS_COMM_HOOK))
        if ( isPendingOffload() ) {
          if ( osEE_hal_spin_trylock(&comm_lock) ) {
            CommunicationHook();
            osEE_hal_spin_unlock(&comm_lock);
          }
        }
#endif /* OSEE_HAS_COMM_HOOK */
        if ( cond_result == OSEE_FALSE ) {
          switch ( BlockPolicy ) {
            case BLOCK_OS:
            case BLOCK_IMMEDIATLY:
              status_type = osEE_k1_block_on_value(BlockableValueRef, WaitCond,
                RightValue);
              cond_result = OSEE_TRUE;
              break;
             case BLOCK_NO:
               osEE_k1_optimized_task_preemption_point();
               break;
             default:
               status_type = E_OS_VALUE;
               break;
           }
         }
      } else {
        break;
      }
    } while ( (status_type == E_OK) && (cond_result == OSEE_FALSE) );
  }
  return status_type;
}

void osEE_job_wrapper ( void ) {
  CoreMask          terminated_mask;
  /* C Single inheritance */
  OsEE_CDB  * const p_cdb   = osEE_get_curr_core();
  OsEE_TDB  * const p_curr  = p_cdb->p_ccb->p_curr;
  OsEE_JOB  * const p_job   = KCB_WJ.tid_to_job[p_curr->tid];

  p_job->job_func(p_job->job_param);

  __k1_fspinlock_lock(&p_job->lock);
  terminated_mask = (__k1_umem_read32(&p_job->terminated_task_mask) |
      OSEE_BIT(CoreMask, p_curr->orig_core_id));
  __k1_umem_write32(&p_job->terminated_task_mask, terminated_mask );
  KCB_WJ.tid_to_job[p_curr->tid] = NULL;
  __k1_fspinlock_unlock(&p_job->lock);

  TerminateTask();
}
#endif /* OSEE_HAS_JOBS */
