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

/** \file  ee_oo_api_extension.c
 *  \brief  OSEK Kernel Extended APIs Implementation.
 *
 *  This files contains the implementation of all OSEK Kernel Extended APIs in
 *  Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */


#include "ee_internal.h"

#if (defined(OSEE_SINGLECORE))
#define OSEE_HAL_SPIN_INIT_LOCK(p_lock) ((void)0)
#define OSEE_HAL_SPIN_LOCK(p_lock)      ((void)0)
#define OSEE_HAL_SPIN_UNLOCK(p_lock)    ((void)0)
#else
#define OSEE_HAL_SPIN_INIT_LOCK(p_lock) osEE_hal_spin_init_lock(p_lock)
#define OSEE_HAL_SPIN_LOCK(p_lock)      osEE_hal_spin_lock(p_lock)
#define OSEE_HAL_SPIN_UNLOCK(p_lock)    osEE_hal_spin_unlock(p_lock)
#endif

#if (defined(OSEE_API_DYNAMIC))
FUNC(void, OS_CODE)
  InitSem
(
  VAR(SemRefType, AUTOMATIC)  pSem,
  VAR(CountType, AUTOMATIC)   count
)
{
  if ( pSem != NULL ) {
    OSEE_HAL_SPIN_INIT_LOCK(&pSem->lock);
    pSem->blocked_queue = NULL;
    pSem->count = count;
  }
}
#endif /* OSEE_API_DYNAMIC */

FUNC(StatusType, OS_CODE)
  WaitSem
(
  VAR(SemRefType, AUTOMATIC) Sem
)
{
  /* Error Value */
  VAR(StatusType, AUTOMATIC)  ev;

  if ( Sem == NULL ) {
    ev = E_OS_PARAM_POINTER;
  } else {
    CONSTP2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA) p_kdb = osEE_get_kernel();
    CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA) p_cdb = osEE_get_curr_core();
    CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_curr = p_cdb->p_ccb->p_curr;
    CONST(OsEE_reg, AUTOMATIC) flags  = osEE_begin_primitive();

    if ( p_curr->task_type != OSEE_TASK_TYPE_EXTENDED ) {
      ev = E_OS_ACCESS;
    } else {
      OSEE_HAL_SPIN_LOCK( &Sem->lock );
      if ( Sem->count != 0U ) {
        --Sem->count;
        OSEE_HAL_SPIN_UNLOCK( &Sem->lock );
      } else {
        P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA) blocked_sn;
        CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
          p_to =  osEE_scheduler_task_block_current(p_kdb, p_cdb, &blocked_sn);

        osEE_sn_priority_insert(&Sem->blocked_queue, blocked_sn, OSEE_FALSE);

#if (defined(OSEE_SCHEDULER_GLOBAL)) && (!defined(OSEE_SINGLECORE))
        p_cdb->p_ccb->p_lock_to_be_released = &Sem->lock;
#else
        OSEE_HAL_SPIN_UNLOCK( &Sem->lock );
#endif /* OSEE_SCHEDULER_GLOBAL && !OSEE_SINGLECORE */

        osEE_change_context_from_running(p_curr, p_to);
      }

      ev = E_OK;
    }
    osEE_end_primitive(flags);
  }
  return ev;
}

FUNC(StatusType, OS_CODE)
  PostSem
(
  VAR(SemRefType, AUTOMATIC) Sem
)
{
  /* Error Value */
  VAR(StatusType, AUTOMATIC)  ev;

  if ( Sem == NULL ) {
    ev = E_OS_PARAM_POINTER;
  } else {
    CONST(OsEE_reg, AUTOMATIC) flags  = osEE_begin_primitive();
    /* check if the post on the semaphore wakes up someone */
    OSEE_HAL_SPIN_LOCK( &Sem->lock );

    if ( Sem->blocked_queue != NULL ) {
      VAR(OsEE_bool, AUTOMATIC)
        is_preemption;
      CONSTP2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)
        p_kdb = osEE_get_kernel();
      CONSTP2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
        p_sn_released = Sem->blocked_queue;
      CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
        p_tdb_released = p_sn_released->p_tdb;
      CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)
        p_cdb = osEE_get_task_curr_core(p_tdb_released);

      /* Remove the head from the blocking queue */
      Sem->blocked_queue = p_sn_released->p_next;

      /* Release the TASK (and the SN) */
      is_preemption = osEE_scheduler_task_unblocked(p_kdb, p_cdb,
        p_sn_released);

      OSEE_HAL_SPIN_UNLOCK(&Sem->lock);

      if ( is_preemption ) {
        (void)osEE_scheduler_task_preemption_point(p_kdb, p_cdb);
      }
    } else {
      ++Sem->count;
      OSEE_HAL_SPIN_UNLOCK( &Sem->lock );
    }
    osEE_end_primitive(flags);
    ev = E_OK;
  }

  return ev;
}
