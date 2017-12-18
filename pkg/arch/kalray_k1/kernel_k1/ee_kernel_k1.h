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
 * ee_kernel_k1.h
 *
 *  Created on: Jan 22, 2015
 *      Author: e.guidieri
 */

#if (!defined(OSEE_KERNEL_K1_H))
#define OSEE_KERNEL_K1_H

#include "ee_cfg.h"

#if (!defined(OSEE_SINGLECORE))

#include "ee_platform_types.h"
#include "ee_k1_vbsp.h"
#include "ee_api_types.h"
#include "ee_api.h"
#include "ee_api_k1.h"
#include "ee_kernel_types.h"

/* For the following structures I use C single inheritance idiom */
typedef struct OsEE_CCB_WL_tag {
  OsEE_CCB        ccb;
  OsEE_spin_lock  lock;
} OsEE_CCB_WL;

#if (defined(OSEE_HAS_JOBS))

typedef struct OsEE_JOB_tag {
  OsEE_spin_lock  lock;
  TaskType        task_attendees_id[OSEE_K1_CORE_NUMBER];
  OsEE_job_func   job_func;
  OsEE_job_param  job_param;
  OsEE_job_prio   job_prio;
  OsEE_job_id     job_id;
  OsEE_reg        attendee_mask;
  OsEE_reg        terminated_task_mask;
} OsEE_JOB;

typedef struct OsEE_KCB_WJ_tag {
  OsEE_KCB        kcb;
  OsEE_spin_lock  lock;
  OsEE_CCB_WL     core_ctrls[OSEE_K1_CORE_NUMBER];
  OsEE_JOB        jobs[OSEE_MAX_NUM_JOB];
  OsEE_JOB  *     tid_to_job[OSEE_TASK_ARRAY_SIZE];
  MemSize         job_index;
  OsEE_TCB        tcb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
  OsEE_SN         sn_array[OSEE_SN_ARRAY_SIZE];
} __attribute__ ((aligned(_K1_DCACHE_LINE_SIZE))) OsEE_KCB_WJ;

typedef struct OsEE_KDB_WJ_tag {
  OsEE_KDB        kdb;
  OsEE_KCB_WJ *   p_kcb_wj;
  OsEE_CDB        core_descriptors[OSEE_K1_CORE_NUMBER];
  OsEE_TDB        tdb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
  OsEE_TDB *      tdb_ptr_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
} OSEE_CONST OsEE_KDB_WJ;

extern OsEE_KCB_WJ KCB_WJ;
extern OsEE_KDB_WJ KDB_WJ;

#define INVALID_PARAM ((uintptr_t)-1)

void osEE_job_wrapper ( void );

StatusType osEE_k1_activate_job ( OsEE_job_id job_id, mOS_vcore_set_t core_mask,
  CoreIdType requiring_core
#if (defined(OSEE_K1_FULL_PREEMPTION))
  , OsEE_bool preemption_point
#endif /* OSEE_K1_FULL_PREEMPTION */
  );

#if (defined(OSEE_HAS_COMM_HOOK))
extern int isPendingOffload ( void );
extern void CommunicationHook ( void );
extern OsEE_spin_lock comm_lock;
#endif

void osEE_k1_optimized_task_preemption_point ( void );

static OsEE_bool osEE_k1_umem_data_priority_insert ( OsEE_SN ** p_head,
  OsEE_SN * p_sn_new)
{
  OsEE_bool   head_changed  = OSEE_FALSE;
  OsEE_SN  *  p_prev        = NULL;
  OsEE_SN  *  p_curr        = (OsEE_SN *)__k1_umem_read32(p_head);
  OsEE_TDB *  p_curr_tdb    = (OsEE_TDB *)__k1_umem_read32(&p_curr->p_tdb);
  OsEE_TDB *  p_tdb_new     = (OsEE_TDB *)__k1_umem_read32(&p_sn_new->p_tdb);

  TaskPrio  const  new_task_prio =
    (TaskPrio)__k1_umem_read32(&p_tdb_new->p_tcb->current_prio);

  /* Traverse the queue until needed */
  while ( (p_curr != NULL) &&
    (new_task_prio <= __k1_umem_read32(&p_curr_tdb->p_tcb->current_prio)) )
  {
    p_prev     = p_curr;
    p_curr     = (OsEE_SN *)__k1_umem_read32(&p_curr->p_next);
    p_curr_tdb = (OsEE_TDB *)__k1_umem_read32(&p_curr->p_tdb);
  };

  if ( p_prev != NULL ) {
    p_prev->p_next = p_sn_new;
  } else {
    (*p_head)     = p_sn_new;
    head_changed  = OSEE_TRUE;
  }

  p_sn_new->p_next = p_curr;

  /* Commit all the changes in memory */
  osEE_k1_wmb();
  return head_changed;
}
#else
/* For the following structures I use C single inheritance idiom */
typedef struct OsEE_KCB_WL_tag {
  OsEE_KCB          kcb;
  OsEE_spin_lock    lock;
  OsEE_CCB_WL       core_ctrls[OSEE_K1_CORE_NUMBER];
} /* __attribute__ ((aligned(_K1_DCACHE_LINE_SIZE))) */ OsEE_KCB_WL;

/* For the following structures I use C single inheritance idiom */
typedef struct OsEE_KDB_WL_tag {
  OsEE_KDB          kdb;
  OsEE_KCB_WL *     p_kcb_wl;
  OsEE_CDB          core_descriptors[OSEE_K1_CORE_NUMBER];
} /* __attribute__ ((aligned(_K1_DCACHE_LINE_SIZE))) */ OSEE_CONST OsEE_KDB_WL;

extern OsEE_KDB_WL KDB_WL;
extern OsEE_KCB_WL KCB_WL;

#endif /* OSEE_HAS_JOBS */
#endif /* !OSEE_SINGLECORE */
#endif /* OSEE_KERNEL_K1_H */
