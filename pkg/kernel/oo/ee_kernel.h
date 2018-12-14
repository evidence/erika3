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

/** \file   ee_kernel.h
 *  \brief  OSEK Kernel Internals.
 *
 *  This files contains all OSEK Kernel Internals in Erika Enterprise.
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2016
 */

#ifndef OSEE_KERNEL_H
#define OSEE_KERNEL_H

#include "ee_arch_override.h"
#include "ee_api.h"
#include "ee_scheduler_types.h"
#include "ee_kernel_types.h"
#include "ee_hal_internal.h"
#include "ee_get_kernel_and_core.h"
#include "ee_scheduler.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#if (!defined(OSEE_SINGLECORE))
/* Synchronization callbacks declarations */
#if (defined(OSEE_STARTOS_1ST_SYNC_BARRIER_CB))
extern void OSEE_STARTOS_1ST_SYNC_BARRIER_CB(void);
#else
#define OSEE_STARTOS_1ST_SYNC_BARRIER_CB NULL
#endif /* OSEE_STARTOS_1ST_SYNC_BARRIER_CB */
#if (defined(OSEE_STARTOS_2ND_SYNC_BARRIER_CB))
extern void OSEE_STARTOS_2ND_SYNC_BARRIER_CB(void);
#else
#define OSEE_STARTOS_2ND_SYNC_BARRIER_CB NULL
#endif /* OSEE_STARTOS_2ND_SYNC_BARRIER_CB */
#if (defined(OSEE_SHUTDOWNOS_SYNC_BARRIER_CB))
extern void OSEE_SHUTDOWNOS_SYNC_BARRIER_CB(void);
#else
#define OSEE_SHUTDOWNOS_SYNC_BARRIER_CB NULL
#endif /* OSEE_SHUTDOWNOS_SYNC_BARRIER_CB */
#endif /* !OSEE_SINGLECORE */

FUNC(void, OS_CODE)
  osEE_change_context_from_running
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
);

#if (!defined(OSEE_CPU_STARTOS_INLINE))
#define OSEE_CPU_STARTOS_INLINE
#endif /* !OSEE_CPU_STARTOS_INLINE */

#if (defined(OSEE_API_DYNAMIC))
/* All Core OS initialization */
FUNC(void, OS_CODE_INIT) osEE_os_init(void);
#endif /* OSEE_API_DYNAMIC */

/* For each CORE Arch dependent StartOS procedure */
OSEE_CPU_STARTOS_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_cpu_startos
(
  void
);

#if (defined(OSEE_HAS_ORTI))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_orti_trace_service_entry
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(OSServiceIdType, AUTOMATIC) service_id
)
{
  p_ccb->service_id = (service_id + 1U);
  p_ccb->orti_service_id_valid = OSEE_TRUE;
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_orti_trace_service_exit
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(OSServiceIdType, AUTOMATIC) service_id
)
{
  if (p_ccb->orti_service_id_valid == OSEE_TRUE) {
    p_ccb->service_id            = service_id;
    p_ccb->orti_service_id_valid = OSEE_FALSE;
  }
}
#else
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_orti_trace_service_entry
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(OSServiceIdType, AUTOMATIC)      service_id
)
{
/* Touch unused parameter */
  (void)p_ccb;
  (void)service_id;
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_orti_trace_service_exit
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(OSServiceIdType, AUTOMATIC)      service_id
)
{
/* Touch unused parameter */
  (void)p_ccb;
  (void)service_id;
}
#endif /* OSEE_HAS_ORTI */

FUNC(void, OS_CODE)
  osEE_activate_isr2
(
  VAR(TaskType, AUTOMATIC) isr2_id
);

LOCAL_INLINE FUNC_P2VAR(OsEE_TDB, OS_APPL_DATA, OS_CODE)
  osEE_get_curr_task
(
  void
)
{
  return osEE_get_curr_core()->p_ccb->p_curr ;
}

FUNC(StatusType, OS_CODE)
  osEE_task_activated
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb_act
);

LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_task_is_active
(
  P2CONST(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)  p_tcb
)
{
  return (p_tcb->status > OSEE_TASK_READY);
}

FUNC(void, OS_CODE)
  osEE_task_end
(
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_tdb
);

#if (defined(OSEE_HAS_EVENTS))
FUNC_P2VAR(OsEE_SN, OS_APPL_DATA, OS_CODE)
  osEE_task_event_set_mask
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST)   p_tdb_waking_up,
  VAR(EventMaskType, AUTOMATIC)               Mask,
  P2VAR(StatusType, AUTOMATIC, OS_APPL_DATA)  p_ev
);

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_task_event_reset_mask
(
  P2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)  p_tcb
)
{
  p_tcb->event_mask = 0U;
}
#else
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_task_event_reset_mask
(
  P2CONST(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)  p_tcb
)
{
/* Touch unused parameter */
  (void)p_tcb;
}
#endif /* OSEE_HAS_EVENTS */

#if (!defined(OSEE_SINGLECORE))
LOCAL_INLINE FUNC(CoreIdType, OS_CODE)
  osEE_task_get_curr_core_id
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb
)
{
#if (!defined(OSEE_ALLOW_TASK_MIGRATION))
  return p_tdb->orig_core_id;
#else
  return p_tdb->p_tcb->current_core_id;
#endif /* !OSEE_ALLOW_TASK_MIGRATION */
}
#endif /* !OSEE_SINGLECORE */

LOCAL_INLINE FUNC(OsEE_reg, OS_CODE)
  osEE_begin_primitive
(
  void
)
{
  return osEE_hal_begin_nested_primitive();
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_end_primitive
(
  VAR(OsEE_reg, AUTOMATIC) flags
)
{
  osEE_hal_end_nested_primitive(flags);
}

LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_is_valid_tid
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  VAR(TaskType, AUTOMATIC)                  tid
)
{
#if (defined(OSEE_API_DYNAMIC))
  return (tid < p_kdb->p_kcb->free_task_index);
#else
  return (tid < p_kdb->tdb_array_size);
#endif /* OSEE_API_DYNAMIC */
}

#if (defined(OSEE_HAS_RESOURCES))
LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_is_valid_res_id
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  VAR(ResourceType, AUTOMATIC)              res_id
)
{
#if (defined(OSEE_API_DYNAMIC))
  return (res_id < p_kdb->p_kcb->free_res_index);
#else
  return (res_id < p_kdb->res_array_size);
#endif /* OSEE_API_DYNAMIC */
}
#endif /* OSEE_HAS_RESOURCES */

#if (defined(OSEE_HAS_CHECKS))
LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_check_disableint
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
  return (p_ccb->s_isr_all_cnt > 0U) || (p_ccb->s_isr_os_cnt > 0U) ||
    (p_ccb->d_isr_all_cnt > 0U);
}
#endif /* OSEE_HAS_CHECKS */

#if (defined(OSEE_HAS_STARTUPHOOK)) && (defined(OSEE_HAS_CONTEXT))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_startup_hook
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)    p_ccb
)
{
  VAR(OsEE_os_context, AUTOMATIC) prev_os_ctx = p_ccb->os_context;
  p_ccb->os_context = OSEE_STARTUPHOOK_CTX;

  StartupHook();

  p_ccb->os_context = prev_os_ctx;
}
#elif (defined(OSEE_HAS_STARTUPHOOK))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_startup_hook
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
/* Touch unused parameter */
  ((void)p_ccb);
  StartupHook();
}
#else
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_startup_hook
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
/* Touch unused parameter */
  ((void)p_ccb);

}
#endif /* (OSEE_HAS_STARTUPHOOK && OSEE_HAS_CONTEXT) elif
  OSEE_HAS_STARTUPHOOK */

#if (defined(OSEE_HAS_PRETASKHOOK)) && (defined(OSEE_HAS_CONTEXT))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_pre_task_hook
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
  VAR(OsEE_os_context, AUTOMATIC) prev_os_ctx = p_ccb->os_context;
  p_ccb->os_context = OSEE_PRETASKHOOK_CTX;

  PreTaskHook();

  p_ccb->os_context = prev_os_ctx;
}
#elif (defined(OSEE_HAS_PRETASKHOOK))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_pre_task_hook
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
/* Touch unused parameter */
  (void)p_ccb;
  PreTaskHook();
}
#else
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_pre_task_hook
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
/* Touch unused parameter */
  (void)p_ccb;
}
#endif /* (OSEE_HAS_PRETASKHOOK && OSEE_HAS_CONTEXT) elif
  OSEE_HAS_PRETASKHOOK */

#if (defined(OSEE_HAS_POSTTASKHOOK)) && (defined(OSEE_HAS_CONTEXT))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_post_task_hook
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
  VAR(OsEE_os_context, AUTOMATIC) prev_os_ctx = p_ccb->os_context;
  p_ccb->os_context = OSEE_POSTTASKHOOK_CTX;

  PostTaskHook();

  p_ccb->os_context = prev_os_ctx;
}
#elif (defined(OSEE_HAS_POSTTASKHOOK))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_post_task_hook
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
/* Touch unused parameter */
  (void)p_ccb;
  PostTaskHook();
}
#else
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_post_task_hook
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
/* Touch unused parameter */
  (void)p_ccb;
}
#endif /* (OSEE_HAS_POSTTASKHOOK && OSEE_HAS_CONTEXT) elif
  OSEE_HAS_POSTTASKHOOK */

#if (defined(OSEE_HAS_SHUTDOWNHOOK)) && (defined(OSEE_HAS_CONTEXT))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_shutdown_hook
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)    p_ccb,
  VAR(StatusType, AUTOMATIC)                  Error
)
{
  VAR(OsEE_os_context, AUTOMATIC) prev_os_ctx = p_ccb->os_context;
  p_ccb->os_context = OSEE_SHUTDOWNHOOK_CTX;

  ShutdownHook(Error);
  p_ccb->os_context = prev_os_ctx;
}
#elif (defined(OSEE_HAS_SHUTDOWNHOOK))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_shutdown_hook
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  VAR(StatusType, AUTOMATIC)                  Error
)
{
/* Touch unused parameter */
  ((void)p_ccb);
  ShutdownHook(Error);
}
#else
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_shutdown_hook
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  VAR(StatusType, AUTOMATIC)                  Error
)
{
  ((void)p_ccb);
  ((void)Error);
}
#endif /* OSEE_HAS_SHUTDOWNHOOK */

#if (defined(OSEE_HAS_ERRORHOOK))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_error_hook
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)    p_ccb,
  VAR(StatusType, AUTOMATIC)                  Error
)
{
  VAR(OsEE_os_context, AUTOMATIC) prev_os_ctx = p_ccb->os_context;
  if (prev_os_ctx != OSEE_ERRORHOOK_CTX) {
    p_ccb->os_context = OSEE_ERRORHOOK_CTX;
    p_ccb->last_error = Error;
    ErrorHook(Error);
    p_ccb->os_context = prev_os_ctx;
  }
}
#else
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_error_hook
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  VAR(StatusType, AUTOMATIC)                  Error
)
{
/* Touch unused parameter */
  ((void)p_ccb);
  ((void)Error);
}
#endif /* OSEE_HAS_ERRORHOOK */

#if (defined(OSEE_USEGETSERVICEID)) || (defined(OSEE_USEPARAMETERACCESS))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_service_id
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  VAR(OSServiceIdType, AUTOMATIC)           service_id
)
{
  p_ccb->service_id = service_id;
}
#else
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_service_id
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  VAR(OSServiceIdType, AUTOMATIC)             service_id
)
{
  ((void)p_ccb);
  ((void)service_id);
}
#endif /* OSEE_USEGETSERVICEID || OSEE_USEPARAMETERACCESS */
#if (defined(OSEE_USEPARAMETERACCESS))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param1_num_param
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(ObjectIDType, AUTOMATIC)            num_param
)
{
  p_ccb->api_param1.num_param = num_param;
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param1_p_param
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(OsEE_addr, AUTOMATIC)               p_param
)
{
  p_ccb->api_param1.p_param = p_param;
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param2_num_param
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(ObjectIDType, AUTOMATIC)            num_param
)
{
  p_ccb->api_param2.num_param = num_param;
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param2_p_param
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(OsEE_addr, AUTOMATIC)               p_param
)
{
  p_ccb->api_param2.p_param = p_param;
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param3_num_param
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(ObjectIDType, AUTOMATIC)            num_param
)
{
  p_ccb->api_param3.num_param = num_param;
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param3_p_param
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(OsEE_addr, AUTOMATIC)               p_param
)
{
  p_ccb->api_param3.p_param = p_param;
}
#else /* OSEE_USEPARAMETERACCESS */
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param1_num_param
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(ObjectIDType, AUTOMATIC)              num_param
)
{
  ((void)p_ccb);
  ((void)num_param);
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param1_p_param
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONSTP2CONST(void, AUTOMATIC, OS_APPL_DATA) p_param
)
{
  ((void)p_ccb);
  ((void)p_param);
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param2_num_param
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(ObjectIDType, AUTOMATIC)              num_param
)
{
  ((void)p_ccb);
  ((void)num_param);
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param2_p_param
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONSTP2CONST(void, AUTOMATIC, OS_APPL_DATA) p_param
)
{
  ((void)p_ccb);
  ((void)p_param);
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param3_num_param
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONST(ObjectIDType, AUTOMATIC)              num_param
)
{
  ((void)p_ccb);
  ((void)num_param);
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param3_p_param
(
  P2CONST(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  CONSTP2CONST(void, AUTOMATIC, OS_APPL_DATA) p_param
)
{
  ((void)p_ccb);
  ((void)p_param);
}
#endif /* OSEE_USEPARAMETERACCESS */

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_shutdown_os_extra(void)
{
  /* TODO: Stop Timing Protection definitely if configured */
#if (defined(OSEE_HAS_SPINLOCKS))
  /* [SWS_Os_00620] ShutdownOS shall release all spinlocks which are occupied
      by the calling core. (SRS_Os_80021) */
#endif /* OSEE_HAS_SPINLOCKS */
#if (defined(OSEE_HAS_OSAPPLICATIONS))
  /* [SWS_Os_00586]: During the shutdown, the OS-Application specific
      ShutdownHook shall be called on the core on which the corresponding
      OS-Application is bound. (BSW4080007) */
#endif /* OSEE_HAS_OSAPPLICATIONS */
#if (!defined(OSEE_SINGLECORE))
  {
    CONSTP2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_CONST)
      p_kdb = osEE_lock_and_get_kernel();
    CONSTP2VAR(OsEE_KCB, AUTOMATIC, OS_APPL_DATA)
      p_kcb = p_kdb->p_kcb;

    if (p_kcb->ar_shutdown_all_cores_flag) {
      /* Release the kernel spinlock and synchronize with other core
         participating to shutdown */
      osEE_unlock_kernel();

      /* [OS587]: Before calling the global ShutdownHook, all cores shall be
          synchronized. (BSW4080007) */
      osEE_hal_sync_barrier(p_kdb->p_barrier, &p_kcb->ar_shutdown_mask,
        OSEE_SHUTDOWNOS_SYNC_BARRIER_CB);
    } else {
      /* Remove this core from the waiting mask: this core has already reached
         the barrier/ it's already shutdown */
      p_kcb->ar_shutdown_mask &=
        (~((CoreMaskType)1U << (OsEE_reg)osEE_get_curr_core_id()));
      /* Unlock the kernel and continue */
      osEE_unlock_kernel();
    }
  }
#endif /* !OSEE_SINGLECORE */
}

#if (defined(OSEE_SHUTDOWN_DO_NOT_RETURN_ON_MAIN))

LOCAL_INLINE FUNC(void, OS_CODE_NO_RETURN)
  osEE_shutdown_os
(
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_CONST) p_cdb,
  VAR(StatusType, AUTOMATIC)                Error
)
{
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb = p_cdb->p_ccb;

  p_ccb->os_status = OSEE_KERNEL_SHUTDOWN;
  /* Used to propagate the error to the ShutdownHook */
  p_ccb->last_error = Error;

  osEE_hal_disableIRQ();

  osEE_shutdown_os_extra();
  osEE_call_shutdown_hook(p_ccb, Error);
  for(;;) {
    ; /* Endless Loop */
  }
}
#else /* OSEE_SHUTDOWN_DO_NOT_RETURN_ON_MAIN */

LOCAL_INLINE FUNC(void, OS_CODE_NO_RETURN)
  osEE_shutdown_os
(
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_CONST) p_cdb,
  VAR(StatusType, AUTOMATIC)                Error
)
{
  CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA) p_ccb = p_cdb->p_ccb;
  CONST(OsEE_kernel_status, AUTOMATIC) os_status = p_ccb->os_status;

  p_ccb->os_status = OSEE_KERNEL_SHUTDOWN;
  /* Used to propagate the error to the ShutdownHook */
  p_ccb->last_error = Error;

  if (os_status == OSEE_KERNEL_STARTED) {
    osEE_idle_task_terminate(p_cdb->p_idle_task);
  } else {
    osEE_call_shutdown_hook(p_ccb, Error);
  }
  for (;;) {
    ; /* Endless Loop (entered only if Kernel Not Started) */
  }
}
#endif /* OSEE_SHUTDOWN_DO_NOT_RETURN_ON_MAIN */

#if (defined(OSEE_HAS_COUNTERS))
LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_is_valid_counter_id
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_CONST) p_kdb,
  VAR(CounterType, AUTOMATIC)               counter_id
)
{
#if (defined(OSEE_API_DYNAMIC))
  return (counter_id < p_kdb->p_kcb->free_counter_index);
#else
  return (counter_id < p_kdb->counter_array_size);
#endif /* OSEE_API_DYNAMIC */
}

FUNC(void, OS_CODE)
  osEE_counter_insert_rel_trigger
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_CONST) p_counter_db,
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_CONST) p_trigger_db,
  VAR(TickType, AUTOMATIC)                        delta
);

FUNC(void, OS_CODE)
  osEE_counter_insert_abs_trigger
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_CONST) p_counter_db,
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_CONST) p_trigger_db,
  VAR(TickType, AUTOMATIC)                        when
);

FUNC(void, OS_CODE)
  osEE_counter_cancel_trigger
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_CONST) p_counter_db,
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_CONST) p_trigger_db
);

FUNC(void, OS_CODE)
  osEE_counter_increment
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_CONST) p_counter_db
);


LOCAL_INLINE FUNC(TickType, OS_CODE)
  osEE_counter_eval_when
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_CONST) p_counter_db,
  VAR(TickType, AUTOMATIC)                        delta
)
{
  VAR(TickType, AUTOMATIC) when;
  CONSTP2CONST(OsEE_CounterCB, AUTOMATIC, OS_APPL_DATA)
    p_counter_cb    = p_counter_db->p_counter_cb;
  CONST(TickType, AUTOMATIC)
    maxallowedvalue = p_counter_db->info.maxallowedvalue;
  CONST(TickType, AUTOMATIC)
    value           = p_counter_cb->value;

  if ((maxallowedvalue - delta) >= value) {
    when = value + delta;
  } else {
    when = delta - (maxallowedvalue - value) - 1U;
  }

  return when;
}

LOCAL_INLINE FUNC(TickType, OS_CODE)
  osEE_counter_eval_delta
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_CONST) p_counter_db,
  VAR(TickType, AUTOMATIC)                        when
)
{
  VAR(TickType, AUTOMATIC) delta;
  CONSTP2CONST(OsEE_CounterCB, AUTOMATIC, OS_APPL_DATA)
    p_counter_cb    = p_counter_db->p_counter_cb;
  CONST(TickType, AUTOMATIC)
    maxallowedvalue = p_counter_db->info.maxallowedvalue;
  CONST(TickType, AUTOMATIC)
    value           = p_counter_cb->value;

  if (when > value) {
    delta = when - value;
  } else {
    delta = (maxallowedvalue - value) + when + 1U;
  }

  return delta;
}

#if (defined(OSEE_HAS_ALARMS))
FUNC(StatusType, OS_CODE)
  osEE_alarm_set_rel
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_CONST) p_counter_db,
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_CONST)   p_alarm_db,
  VAR(TickType,   AUTOMATIC)                      increment,
  VAR(TickType,   AUTOMATIC)                      cycle
);

FUNC(StatusType, OS_CODE)
  osEE_alarm_set_abs
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_CONST) p_counter_db,
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_CONST)   p_alarm_db,
  VAR(TickType,   AUTOMATIC)                      start,
  VAR(TickType,   AUTOMATIC)                      cycle
);

FUNC(StatusType, OS_CODE)
  osEE_alarm_cancel
(
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_CONST)   p_alarm_db
);

FUNC(StatusType, OS_CODE)
  osEE_alarm_get
(
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_CONST)   p_alarm_db,
  P2VAR(TickType, AUTOMATIC, OS_APPL_DATA)        p_tick
);

LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_is_valid_alarm_id
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_CONST) p_kdb,
  VAR(AlarmType, AUTOMATIC)                 alarm_id
)
{
#if (defined(OSEE_API_DYNAMIC))
  return (alarm_id < p_kdb->p_kcb->free_alarm_index);
#else
  return (alarm_id < p_kdb->alarm_array_size);
#endif /* OSEE_API_DYNAMIC */
}

LOCAL_INLINE FUNC_P2VAR(OsEE_TriggerDB, OS_APPL_CONST, OS_CODE)
  osEE_alarm_get_trigger_db
(
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_CONST) p_alarm_db
)
{
#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
  return p_alarm_db->p_trigger_db;
#else
  return p_alarm_db;
#endif
}

LOCAL_INLINE FUNC_P2VAR(OsEE_AlarmCB, OS_APPL_DATA, OS_CODE)
  osEE_alarm_get_cb
(
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_CONST) p_alarm_db
)
{
#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
  return p_alarm_db->p_alarm_cb;
#else
  return p_alarm_db->p_trigger_cb;
#endif
}

LOCAL_INLINE FUNC_P2VAR(OsEE_AlarmDB, OS_APPL_CONST, OS_CODE)
  osEE_trigger_get_alarm_db
(
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_CONST) p_trigger_db
)
{
#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
  return p_trigger_db->p_alarm_db;
#else
  return p_trigger_db;
#endif
}

#endif /* OSEE_HAS_ALARMS */

#if (defined(OSEE_HAS_SCHEDULE_TABLES))
FUNC(StatusType, OS_CODE)
  osEE_st_start_rel
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA)  p_counter_db,
  P2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_DATA) p_st_db,
  VAR(TickType,   AUTOMATIC)                      offset
);

FUNC(StatusType, OS_CODE)
  osEE_st_start_abs
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA)  p_counter_db,
  P2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_DATA) p_st_db,
  VAR(TickType,   AUTOMATIC)                      start
);

FUNC(StatusType, OS_CODE)
  osEE_st_stop
(
  P2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_CONST)  p_st_db
);

FUNC(StatusType, OS_CODE)
  osEE_st_syncronize
(
  P2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_CONST)  p_st_db,
  VAR(TickType, AUTOMATIC)                          value
);

LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_is_valid_st_id
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_CONST) p_kdb,
  VAR(ScheduleTableType, AUTOMATIC)         st_id
)
{
#if (defined(OSEE_API_DYNAMIC))
  return (st_id < p_kdb->p_kcb->free_st_index);
#else
  return (st_id < p_kdb->st_array_size);
#endif /* OSEE_API_DYNAMIC */
}

LOCAL_INLINE FUNC_P2VAR(OsEE_TriggerDB, OS_APPL_CONST, OS_CODE)
  osEE_st_get_trigger_db
(
  P2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_CONST) p_st_db
)
{
#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
  return p_st_db->p_trigger_db;
#else
  return p_st_db;
#endif
}

LOCAL_INLINE FUNC_P2VAR(OsEE_SchedTabCB, OS_APPL_DATA, OS_CODE)
  osEE_st_get_cb
(
  P2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_CONST) p_st_db
)
{
#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
  return p_st_db->p_st_cb;
#else
  return p_st_db->p_trigger_cb;
#endif
}

LOCAL_INLINE FUNC_P2VAR(OsEE_SchedTabDB, OS_APPL_CONST, OS_CODE)
  osEE_trigger_get_st_db
(
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_CONST) p_trigger_db
)
{
#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
  return p_trigger_db->p_st_db;
#else
  return p_trigger_db;
#endif
}

#endif /* OSEE_HAS_SCHEDULE_TABLES */
#endif /* OSEE_HAS_COUNTERS */

#if (defined(OSEE_HAS_STACK_MONITORING))
FUNC(void, OS_CODE) osEE_stack_monitoring
(
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_CONST) p_cdb
);
#else
LOCAL_INLINE FUNC(void, OS_CODE) osEE_stack_monitoring
(
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_CONST) p_cdb
)
{
/* Touch unused parameter */
  (void)p_cdb;
}
#endif /* OSEE_HAS_STACK_MONITORING */

#if (defined(OSEE_HAS_SPINLOCKS))
LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_is_valid_spinlock_id
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_CONST) p_kdb,
  VAR(SpinlockIdType, AUTOMATIC)            spinlock_id
)
{
#if (defined(OSEE_API_DYNAMIC))
  return (spinlock_id < p_kdb->p_kcb->free_spinlock_index);
#else
  return (spinlock_id < p_kdb->spinlock_array_size);
#endif /* OSEE_API_DYNAMIC */
}

#if (defined(OSEE_HAS_RESOURCES))
LOCAL_INLINE FUNC_P2VAR(OsEE_SpinlockDB, OS_APPL_CONST, OS_CODE)
  osEE_task_get_last_spinlock_db
(
  CONSTP2CONST(OsEE_TCB, AUTOMATIC, OS_APPL_CONST) p_tcb
)
{
  P2VAR(OsEE_MDB, AUTOMATIC, OS_APPL_CONST) p_mdb = p_tcb->p_last_m;

  while (p_mdb != NULL) {
    if (p_mdb->m_type == OSEE_M_SPINLOCK) {
      /* Found the first spinlock */
      break;
    } else {
      /* p_mdb is a Resource move on the stack */
      p_mdb = p_mdb->p_cb->p_next;
    }
  }

  return p_mdb;
}
#else
LOCAL_INLINE FUNC_P2VAR(OsEE_SpinlockDB, OS_APPL_CONST, OS_CODE)
  osEE_task_get_last_spinlock_db
(
  CONSTP2CONST(OsEE_TCB, AUTOMATIC, OS_APPL_CONST) p_tcb
)
{
  return p_tcb->p_last_m;
}
#endif /* OSEE_HAS_RESOURCES */
#endif /* OSEE_HAS_SPINLOCKS */

#if (defined(OSEE_API_DYNAMIC))
FUNC(StatusType, OS_CODE)
  osEE_create_task
(
  VAR(CoreIdType, AUTOMATIC)        core_id,
  VAR(TaskRefType, AUTOMATIC)       p_task_id,
  VAR(TaskExecutionType, AUTOMATIC) task_type,
  VAR(TaskFunc, AUTOMATIC)          task_func,
  VAR(TaskPrio, AUTOMATIC)          ready_prio,
  VAR(TaskPrio, AUTOMATIC)          dispatch_prio,
  VAR(TaskActivation, AUTOMATIC)    max_num_of_act,
  VAR(MemSize, AUTOMATIC)           stack_size
);
#endif /* OSEE_API_DYNAMIC */

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_KERNEL_H */
