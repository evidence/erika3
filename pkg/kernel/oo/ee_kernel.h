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

#if (!defined(OSEE_KERNEL_H))
#define OSEE_KERNEL_H

#include "ee_api.h"
#include "ee_scheduler_types.h"
#include "ee_kernel_types.h"
#include "ee_hal_internal.h"
#include "ee_get_kernel_and_core.h"
#include "ee_scheduler.h"

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
/* All Core OS initialization: It SHALL be called in start-up code */
FUNC(void, OS_CODE_INIT) osEE_os_init ( void );
#endif /* OSEE_API_DYNAMIC */

/* For each CORE Arch dependent StartOS procedure */
OSEE_CPU_STARTOS_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_cpu_startos
(
  void
);

LOCAL_INLINE FUNC_P2VAR(OsEE_TDB, OS_APPL_DATA, OS_CODE)
  osEE_get_curr_task
(
  void
)
{
  return osEE_get_curr_core()->p_ccb->p_curr ;
}

LOCAL_INLINE FUNC_P2VAR(OsEE_CDB, OS_APPL_DATA, OS_CODE)
  osEE_get_task_curr_core
(
  P2VAR(OsEE_TDB, OS_APPL_DATA, OS_CODE) p_tdb
)
{
#if (defined(OSEE_SINGLECORE))
  ((void)p_tdb);
  return osEE_get_curr_core();
#elif (defined(OSEE_ALLOW_TASK_MIGRATION))
  return osEE_get_core(p_tdb->p_tcb->current_core_id);
#else
  return osEE_get_core(p_tdb->orig_core_id);
#endif
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_task_end
(
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_tdb
)
{
  CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA) p_tcb = p_tdb->p_tcb;

  p_tcb->current_prio = p_tdb->ready_prio;

  --p_tcb->current_num_of_act;

  if (p_tcb->current_num_of_act == 0U) {
    p_tcb->status = OSEE_TASK_SUSPENDED;
  } else {
    p_tcb->status = OSEE_TASK_READY;
  }
}

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

LOCAL_INLINE FUNC(StatusType, OS_CODE)
  osEE_activate_isr2
(
  VAR(TaskType, AUTOMATIC) isr2_id
)
{
  VAR(StatusType, AUTOMATIC) ret_val  = E_OK;
  CONSTP2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA) p_kdb = osEE_get_kernel();
  CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA) p_cdb = osEE_get_curr_core();
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
    p_act_tdb = (*p_kdb->p_tdb_ptr_array)[isr2_id];

  /* Mark the TASK as Activated */
  ++p_act_tdb->p_tcb->current_num_of_act;

  osEE_scheduler_task_set_running(p_kdb, p_cdb, p_act_tdb);

  return ret_val;
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
  /* return (tid < p_kdb->tdb_array_size - OSEE_USED_CORES); */
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

LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_is_active_task
(
  P2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)  p_tcb
)
{
  return (p_tcb->status > OSEE_TASK_READY);
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_event_reset_mask
(
  P2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)  p_tcb
)
{
#if (defined(OSEE_HAS_EVENTS))
  p_tcb->event_mask = 0U;
#else
  (void)p_tcb;
#endif /* OSEE_HAS_EVENTS */
}

#if (defined(OSEE_HAS_CHECKS))
LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_check_disableint
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
  return (p_ccb->s_isr_all_cnt > 0U) || (p_ccb->s_isr_os_cnt > 0U) ||
    (p_ccb->d_isr_all_cnt > 0U);
}
#endif /* OSEE_HAS_CHECKS */

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_startup_hook
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
#if (defined(OSEE_HAS_STARTUPHOOK))
#if (defined(OSEE_HAS_CONTEXT))
  VAR(OsEE_os_context, AUTOMATIC) prev_os_ctx = p_ccb->os_context;
  p_ccb->os_context = OSEE_STARTUPHOOK_CTX;
#else
  /* Touch unused parameter */
  ((void)p_ccb);
#endif /* OSEE_HAS_CONTEXT */
  StartupHook();
#if (defined(OSEE_HAS_CONTEXT))
  p_ccb->os_context = prev_os_ctx;
#endif /* OSEE_HAS_CONTEXT */
#else
  /* Touch unused parameter */
  ((void)p_ccb);
#endif /* OSEE_HAS_STARTUPHOOK */
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_pre_task_hook
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
#if (defined(OSEE_HAS_PRETASKHOOK))
#if (defined(OSEE_HAS_CONTEXT))
  VAR(OsEE_os_context, AUTOMATIC) prev_os_ctx = p_ccb->os_context;
  p_ccb->os_context = OSEE_PRETASKHOOK_CTX;
#endif /* OSEE_HAS_CONTEXT */
  PreTaskHook();
#if (defined(OSEE_HAS_CONTEXT))
  p_ccb->os_context = prev_os_ctx;
#endif /* OSEE_HAS_CONTEXT */
#else
  ((void)p_ccb);
#endif /* OSEE_HAS_PRETASKHOOK */
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_post_task_hook
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb
)
{
#if (defined(OSEE_HAS_POSTTASKHOOK))
#if (defined(OSEE_HAS_CONTEXT))
  VAR(OsEE_os_context, AUTOMATIC) prev_os_ctx = p_ccb->os_context;
  p_ccb->os_context = OSEE_POSTTASKHOOK_CTX;
#endif /* OSEE_HAS_CONTEXT */
  PostTaskHook();
#if (defined(OSEE_HAS_CONTEXT))
  p_ccb->os_context = prev_os_ctx;
#endif /* OSEE_HAS_CONTEXT */
#else
  ((void)p_ccb);
#endif /* OSEE_HAS_POSTTASKHOOK */
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_shutdown_hook
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  VAR(StatusType, AUTOMATIC)                Error
)
{
#if (defined(OSEE_HAS_SHUTDOWNHOOK))
#if (defined(OSEE_HAS_CONTEXT))
  VAR(OsEE_os_context, AUTOMATIC) prev_os_ctx = p_ccb->os_context;
  p_ccb->os_context = OSEE_SHUTDOWNHOOK_CTX;
#endif /* OSEE_HAS_CONTEXT */
  ShutdownHook(Error);
#if (defined(OSEE_HAS_CONTEXT))
  p_ccb->os_context = prev_os_ctx;
#endif /* OSEE_HAS_CONTEXT */
#else
  ((void)p_ccb);
  ((void)Error);
#endif /* OSEE_HAS_SHUTDOWNHOOK */
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_call_error_hook
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  VAR(StatusType, AUTOMATIC)                Error
)
{
#if (defined(OSEE_HAS_ERRORHOOK))
  VAR(OsEE_os_context, AUTOMATIC) prev_os_ctx = p_ccb->os_context;
  if (prev_os_ctx != OSEE_ERRORHOOK_CTX) {
    p_ccb->os_context = OSEE_ERRORHOOK_CTX;
    p_ccb->last_error = Error;
    ErrorHook(Error);
    p_ccb->os_context = prev_os_ctx;
  }
#else
  ((void)p_ccb);
  ((void)Error);
#endif /* OSEE_HAS_ERRORHOOK */
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_service_id
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  VAR(OSServiceIdType, AUTOMATIC)           service_id
)
{
#if (defined(OSEE_USEPARAMETERACCESS))
  p_ccb->service_id = service_id;
#else
  ((void)p_ccb);
  ((void)service_id);
#endif /* OSEE_USEPARAMETERACCESS */
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param1
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  VAR(OsEE_api_param, AUTOMATIC)            api_param
)
{
#if (defined(OSEE_USEPARAMETERACCESS))
  p_ccb->api_param1 = api_param;
#else
  ((void)p_ccb);
  ((void)api_param);
#endif /* OSEE_USEPARAMETERACCESS && */
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param2
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  VAR(OsEE_api_param, AUTOMATIC)            api_param
)
{
#if (defined(OSEE_USEPARAMETERACCESS))
  p_ccb->api_param2 = api_param;
#else
  ((void)p_ccb);
  ((void)api_param);
#endif /* OSEE_USEPARAMETERACCESS && */
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_set_api_param3
(
  P2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)  p_ccb,
  VAR(OsEE_api_param, AUTOMATIC)            api_param
)
{
#if (defined(OSEE_USEPARAMETERACCESS))
  p_ccb->api_param3 = api_param;
#else
  ((void)p_ccb);
  ((void)api_param);
#endif /* OSEE_USEPARAMETERACCESS && */
}

#if (defined(OSEE_HAS_COUNTERS))
FUNC(void, OS_CODE)
  osEE_counter_insert_rel_trigger
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA) p_counter_db,
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA) p_trigger_db,
  VAR(TickType, AUTOMATIC)                       delta
);

FUNC(void, OS_CODE)
  osEE_counter_insert_abs_trigger
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA) p_counter_cb,
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA) p_trigger_db,
  VAR(TickType, AUTOMATIC)                       when
);

FUNC(void, OS_CODE)
  osEE_counter_cancel_trigger
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA) p_counter_db,
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA) p_trigger_db
);

FUNC(void, OS_CODE)
  osEE_counter_increment
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA) p_counter_db
);


LOCAL_INLINE FUNC(TickType, OS_CODE)
  osEE_counter_eval_when
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA) p_counter_db,
  VAR(TickType, AUTOMATIC)                       delta
)
{
  VAR(TickType, AUTOMATIC) when;
  CONSTP2VAR(OsEE_CounterCB, AUTOMATIC, OS_APPL_DATA)
    p_counter_cb    = p_counter_db->p_counter_cb;
  CONST(TickType, AUTOMATIC)
    maxallowedvalue = p_counter_db->info.maxallowedvalue;
  CONST(TickType, AUTOMATIC)
    value           = p_counter_cb->value;

  if (maxallowedvalue - delta >= value) {
    when = value + delta;
  } else {
    when = delta - (maxallowedvalue - value) - 1U;
  }

  return when;
}

LOCAL_INLINE FUNC(TickType, OS_CODE)
  osEE_counter_eval_delta
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA) p_counter_db,
  VAR(TickType, AUTOMATIC)                       when
)
{
  VAR(TickType, AUTOMATIC) delta;
  CONSTP2VAR(OsEE_CounterCB, AUTOMATIC, OS_APPL_DATA)
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
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA)  p_counter_db,
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_DATA)    p_alarm_db,
  VAR(TickType,   AUTOMATIC)                      increment,
  VAR(TickType,   AUTOMATIC)                      cycle
);

FUNC(StatusType, OS_CODE)
  osEE_alarm_set_abs
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA)  p_counter_db,
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_DATA)    p_alarm_db,
  VAR(TickType,   AUTOMATIC)                      start,
  VAR(TickType,   AUTOMATIC)                      cycle
);

FUNC(StatusType, OS_CODE)
  osEE_alarm_cancel
(
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_DATA)    p_alarm_db
);

FUNC(StatusType, OS_CODE)
  osEE_alarm_get
(
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_DATA)    p_alarm_db,
  P2VAR(TickType, AUTOMATIC, OS_APPL_DATA)        p_tick
);

LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_is_valid_alarm_id
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  VAR(AlarmType, AUTOMATIC)                 alarm_id
)
{
#if (defined(OSEE_API_DYNAMIC))
  return (alarm_id < p_kdb->p_kcb->free_alarm_index);
#else
  return (alarm_id < p_kdb->alarm_array_size);
#endif /* OSEE_API_DYNAMIC */
}

LOCAL_INLINE FUNC_P2VAR(OsEE_TriggerDB, OS_APPL_DATA, OS_CODE)
  osEE_alarm_get_trigger_db
(
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_DATA) p_alarm_db
)
{
#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
  return &p_alarm_db->super;
#else
  return p_alarm_db;
#endif
}

LOCAL_INLINE FUNC_P2VAR(OsEE_AlarmCB, OS_APPL_DATA, OS_CODE)
  osEE_alarm_get_cb
(
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_DATA) p_alarm_db
)
{
  return (P2VAR(OsEE_AlarmCB, AUTOMATIC, OS_APPL_DATA))
    (osEE_alarm_get_trigger_db(p_alarm_db)->p_trigger_cb);
}

#endif /* OSEE_HAS_ALARMS */
#endif /* OSEE_HAS_COUNTERS */

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

#endif /* !OSEE_KERNEL_H */
