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

/** \file   ee_kernel_types.h
 *  \brief  OSEK Kernel Internal Types.
 *
 *  This files contains all internal types and symbols for OSEK Kernel support
 *  in Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date   2016
 */

#if (!defined(OSEE_KERNEL_TYPES_H))
#define OSEE_KERNEL_TYPES_H

#include "ee_cfg.h"
#include "ee_api_types.h"
#include "ee_oo_api_extension.h"
#include "ee_hal_internal_types.h"
#include "ee_scheduler_types.h"

#if (!defined(OSEE_SINGLECORE)) && (defined(OSEE_SCHEDULER_GLOBAL))
#define OSEE_ALLOW_TASK_MIGRATION
#endif /* OSEE_SINGLECORE && OSEE_SCHEDULER_GLOBAL */

#if (defined(OSEE_HAS_RESOURCES)) || (defined(OSEE_HAS_SPINLOCKS))
#define OSEE_HAS_MUTEX
#endif /* OSEE_HAS_RESOURCES || OSEE_HAS_SPINLOCKS */

#if (defined(OSEE_HAS_ERRORHOOK)) || (defined(OSEE_HAS_SERVICE_PROTECTION))
#define OSEE_HAS_CONTEXT
#endif /* OSEE_HAS_ERRORHOOK || OSEE_HAS_SERVICE_PROTECTION */

#if (defined(OSEE_EXTENDED_STATUS)) || (defined(OSEE_HAS_SERVICE_PROTECTION))
#define OSEE_HAS_CHECKS
#endif /* OSEE_EXTENDED_STATUS || OSEE_HAS_SERVICE_PROTECTION */

/* Kernel Callback */
typedef P2FUNC(void, OS_APPL_DATA, OsEE_kernel_cb) (void);
/* Byte: the smallest type instantiable */
typedef VAR(unsigned char, TYPEDEF) OsEE_byte;
#define OSEE_MAX_BYTE               ((OsEE_byte)-1)

#if (!defined(OSEE_CORE_MASK_TYPE))
#define OSEE_CORE_MASK_TYPE                       VAR(unsigned char, TYPEDEF)
#endif /* !OSEE_CORE_MASK_TYPE */
typedef OSEE_CORE_MASK_TYPE                       CoreMaskType;

/*[OS_SWS_088] If an OS-Application makes a service call from the wrong
 * context AND is currently not inside a Category 1 ISR the Operating System
 * module shall not perform the requested action
 * (the service call shall have no effect), and return E_OS_CALLEVEL
 * (see [12], section 13.1) or the "invalid value" of the service.
 * (BSW11009, BSW11013) */
/** @typedef OS-Application contexts enum used to implement Autosar OS
 *  OS_SWS_088 requirement. Used in addition to handle not recursive calls at
 *  ErrorHook */
typedef enum OsEE_os_context_tag{
  OSEE_KERNEL_CTX,
  OSEE_TASK_CTX,
  OSEE_TASK_ISR2_CTX,
  OSEE_ERRORHOOK_CTX,
  OSEE_PROTECTIONHOOK_CTX,
  OSEE_PRETASKHOOK_CTX,
  OSEE_POSTTASKHOOK_CTX,
  OSEE_STARTUPHOOK_CTX,
  OSEE_SHUTDOWNHOOK_CTX,
  OSEE_ALARMCALLBACK_CTX,
  OSEE_IDLE_CTX
} OsEE_os_context;

typedef enum {
#if (defined(OSEE_API_DYNAMIC))
  OSEE_KERNEL_UNITIALIZED,
#endif /* OSEE_API_DYNAMIC */
  OSEE_KERNEL_STOPPED,
  OSEE_KERNEL_STARTING,
  OSEE_KERNEL_STARTED,
  OSEE_KERNEL_SHUTDOWN
} OsEE_kernel_status;

#if (defined(OSEE_HAS_MUTEX))
/* Forward declaration of MDB, needed for MCB p_next field. */
struct OsEE_MDB_tag;

typedef struct OsEE_MCB_tag {
  P2VAR(struct OsEE_MDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA)  p_next;
  VAR(TaskPrio, TYPEDEF)                                        prev_prio;
#if (defined(OSEE_HAS_CHECKS))
  VAR(OsEE_bool, TYPEDEF)                                       locked;
#endif /* OSEE_HAS_CHECKS */
#if (!defined(OSEE_SINGLECORE))
  VAR(TaskType, TYPEDEF)                                        mtx_owner;
#endif /* !OSEE_SINGLECORE */
} OsEE_MCB;

#if (!defined(OSEE_SINGLECORE))
typedef enum {
  OSEE_MUTEX_RESOURCE,
  OSEE_MUTEX_SPINLOCK
} OsEE_mutex_type;
#endif /* !OSEE_SINGLECORE */

typedef struct OsEE_MDB_tag {
  P2VAR(OsEE_MCB, TYPEDEF, OS_APPL_DATA)        p_mcb;
  VAR(TaskPrio, TYPEDEF)                        mtx_prio;
#if (!defined(OSEE_SINGLECORE))
  P2VAR(OsEE_spin_lock, TYPEDEF, OS_APPL_DATA)  p_lock;
  VAR(OsEE_mutex_type, TYPEDEF)                 mtx_type;
  VAR(CoreMaskType, TYPEDEF)                    core_mask;
#endif /* !OSEE_SINGLECORE */
} OSEE_CONST OsEE_MDB;
#endif /* OSEE_HAS_MUTEX */

typedef struct OsEE_TCB_tag {
  VAR(TaskActivation, TYPEDEF)              current_num_of_act;
  VAR(TaskPrio, TYPEDEF)                    current_prio;
  VAR(TaskStateType, TYPEDEF)               status;
#if (defined(OSEE_HAS_MUTEX))
  P2VAR(OsEE_MDB, TYPEDEF, OS_APPL_DATA)    p_first_mtx;
#endif /* OSEE_HAS_MUTEX */
#if (defined(OSEE_HAS_EVENTS))
  VAR(EventMaskType, TYPEDEF)               wait_mask;
  VAR(EventMaskType, TYPEDEF)               event_mask;
#endif /* OSEE_HAS_EVENTS */
#if (defined(OSEE_ALLOW_TASK_MIGRATION))
  VAR(CoreIdType, TYPEDEF)                  current_core_id;
#endif /* OSEE_ALLOW_TASK_MIGRATION */
} OsEE_TCB;

typedef struct OsEE_TDB_tag {
  VAR(OsEE_HDB, TYPEDEF)                  hdb;
  P2VAR(OsEE_TCB, TYPEDEF, OS_APPL_DATA)  p_tcb;
  VAR(TaskType, TYPEDEF)                  tid;
  VAR(TaskExecutionType, TYPEDEF)         task_type;
  VAR(TaskFunc, TYPEDEF)                  task_func;
  VAR(TaskPrio, TYPEDEF)                  ready_prio;
  VAR(TaskPrio, TYPEDEF)                  dispatch_prio;
  VAR(TaskActivation, TYPEDEF)            max_num_of_act;
#if (!defined(OSEE_SINGLECORE))
  VAR(CoreIdType, TYPEDEF)                orig_core_id;
#endif /* !OSEE_SINGLECORE */
} OSEE_CONST OsEE_TDB;

typedef struct OsEE_TW_tag {
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_DATA)  p_tdb;
  VAR(TaskFunc, TYPEDEF)                  real_task_func;
} OSEE_CONST OsEE_TW;

#if (defined(OSEE_HAS_COUNTERS))
#if (defined(OSEE_HAS_ALARMS)) && (defined(OSEE_HAS_SCHEDULE_TABLES))
#define OSEE_COUNTER_TRIGGER_TYPES
#endif /* OSEE_HAS_ALARMS && OSEE_HAS_SCHEDULE_TABLES */

/* Forward declaration of TriggerDB, needed for CounterCB
 * p_first_trigger and for TriggerCB p_next fields. */
struct OsEE_TriggerDB_tag;

/* XXX: Actually the Trigger Queue is Linked List, but in theory we could
        implement any priority queue data structure (Heap for example) */
typedef P2VAR(struct OsEE_TriggerDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA)
  OsEE_TriggerQ;

typedef struct OsEE_CounterCB_tag {
  VAR(OsEE_TriggerQ, TYPEDEF) trigger_queue;
  VAR(TickType, TYPEDEF)      value;
#if (defined(OSEE_HAS_COUNTER_PRESCALER))
  VAR(TickType, TYPEDEF)      prescaler;
#endif /* OSEE_HAS_COUNTER_PRESCALER */
} OsEE_CounterCB;

#if (defined(OSEE_HAS_COUNTER_HARD))
typedef struct OsEE_CounterHardDB {
  VAR(OsEE_CounterDB, TYPEDEF)  super;
  VAR(TickType, TYPEDEF)        microsecondspertick;
} OSEE_CONST OsEE_CounterHardDB;
#endif /* OSEE_HAS_COUNTER_HARD */

typedef struct OsEE_CounterDB_tag {
  P2VAR(OsEE_CounterCB, TYPEDEF, OS_APPL_DATA)      p_counter_cb;
#if (defined(OSEE_HAS_COUNTER_HARD))
  P2VAR(OsEE_CounterHardDB, TYPEDEF, OS_APPL_CONST) p_counter_hard;
#endif /* OSEE_HAS_COUNTER_HARD */
  VAR(AlarmBaseType, TYPEDEF)                       info;
#if (!defined(OSEE_SINGLECORE))
  VAR(CoreIdType, TYPEDEF)                          core_id;
#endif /* OSEE_SINGLECORE */
} OSEE_CONST OsEE_CounterDB;

typedef enum {
  OSEE_ACTION_TASK,
  OSEE_ACTION_EVENT,
  OSEE_ACTION_COUNTER,
  OSEE_ACTION_CALLBACK
} OsEE_action_type;

typedef struct OsEE_action_param {
  VAR(OsEE_kernel_cb, TYPEDEF)                  f;
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_DATA)        p_tdb;
  P2VAR(OsEE_CounterDB, TYPEDEF, OS_APPL_DATA)  p_counter_db;
#if (defined(OSEE_HAS_EVENTS))
  VAR(EventMaskType, TYPEDEF)                   mask;
#endif /* OSEE_HAS_EVENTS */
} OsEE_action_param;

typedef struct OsEE_action_tag {
  VAR(OsEE_action_param, TYPEDEF)               param;
  VAR(OsEE_action_type, TYPEDEF)                type;
} OsEE_action;

#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
typedef enum {
  OSEE_TRIGGER_ALARM,
  OSEE_TRIGGER_SCHEDULE_TABLE
} OsEE_trigger_type;
#endif /* OSEE_COUNTER_TRIGGER_TYPES */

typedef struct OsEE_TriggerCB_tag {
  P2VAR(struct OsEE_TriggerDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA)  p_next;
  VAR(TickType, TYPEDEF)                                              when;
  VAR(OsEE_bool, TYPEDEF)                                             active;
#if (!defined(OSEE_COUNTER_TRIGGER_TYPES))
#if (defined(OSEE_HAS_ALARMS))
  VAR(TickType, TYPEDEF)                                              cycle;
#elif (defined(OSEE_HAS_SCHEDULE_TABLES))
/* TODO */
#endif /* OSEE_HAS_ALARMS || OSEE_HAS_SCHEDULE_TABLES */
#endif /* !OSEE_COUNTER_TRIGGER_TYPES */
} OsEE_TriggerCB;

typedef struct OsEE_TriggerDB_tag {
  P2VAR(OsEE_TriggerCB, TYPEDEF, OS_APPL_DATA)  p_trigger_cb;
  P2VAR(OsEE_CounterDB, TYPEDEF, OS_APPL_DATA)  p_counter_db;
#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
  VAR(OsEE_trigger_type, TYPEDEF)               type;
#elif (defined(OSEE_HAS_ALARMS))
  VAR(OsEE_action, TYPEDEF)                     action;
#elif (defined(OSEE_HAS_SCHEDULE_TABLES))
  /* TODO */
#endif /* OSEE_COUNTER_TRIGGER_TYPES */
} OSEE_CONST OsEE_TriggerDB;

#if (defined(OSEE_HAS_AUTOSTART_TRIGGER))
typedef struct OsEE_autostart_trigger_info_tag {
  P2VAR(OsEE_TriggerDB, OS_APPL_DATA, TYPEDEF)  p_trigger_db;
  VAR(TickType, TYPEDEF)                        increment;
  VAR(TickType, TYPEDEF)                        cycle;
} OSEE_CONST OsEE_autostart_trigger_info;

typedef struct OsEE_autostart_trigger_tag {
  P2SYM_VAR(OsEE_autostart_trigger_info, OS_APPL_DATA,  p_trigger_ptr_array)[];
  VAR(MemSize, TYPEDEF)                                 trigger_array_size;
} OSEE_CONST OsEE_autostart_trigger;
#endif /* OSEE_HAS_AUTOSTART_TRIGGER */

#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
typedef struct OsEE_AlarmCB_tag {
  VAR(OsEE_TriggerCB, TYPEDEF)                  super;
  VAR(TickType, TYPEDEF)                        cycle;
} OsEE_AlarmCB;

typedef struct OsEE_AlarmDB_tag {
  VAR(OsEE_TriggerDB, TYPEDEF)                  super;
  VAR(OsEE_action, TYPEDEF)                     action;
} OsEE_AlarmDB;
#elif (defined(OSEE_HAS_ALARMS))
typedef OsEE_TriggerCB OsEE_AlarmCB;
typedef OsEE_TriggerDB OsEE_AlarmDB;
#elif (defined(OSEE_HAS_SCHEDULE_TABLES))
/* TODO Schedule Tables */
#endif /* OSEE_COUNTER_TRIGGER_TYPES */
#endif /* OSEE_HAS_COUNTERS */

#if (defined(OSEE_HAS_AUTOSTART_TASK))
typedef struct OsEE_autostart_tdb_tag {
  P2SYM_CONSTP2VAR(OsEE_TDB, OS_APPL_DATA,  p_tdb_ptr_array)[];
  VAR(MemSize, TYPEDEF)                     tdb_array_size;
} OSEE_CONST OsEE_autostart_tdb;
#endif /* !OSEE_HAS_AUTOSTART_TASK */

typedef struct OsEE_CCB_tag {
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_DATA)        p_curr;
#if (!defined(OSEE_SINGLECORE)) && (defined(OSEE_SCHEDULER_GLOBAL))
  P2VAR(OsEE_spin_lock, TYPEDEF, OS_APPL_DATA)  p_lock_to_be_released;
#endif /* !OSEE_SINGLECORE && OSEE_SCHEDULER_GLOBAL */
#if (!defined(OSEE_SCHEDULER_GLOBAL))
  VAR(OsEE_RQ, TYPEDEF)                         rq;
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA)         p_free_sn;
#if (defined(OSEE_API_DYNAMIC))
  VAR(MemSize, TYPEDEF)                         free_sn_counter;
#endif /* OSEE_API_DYNAMIC */
#endif /* !OSEE_SCHEDULER_GLOBAL */
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA)         p_stk_sn;
  VAR(OsEE_kernel_status, TYPEDEF)              os_status;
  VAR(AppModeType, TYPEDEF)                     app_mode;
  /* Error Handling variables */
  VAR(StatusType, TYPEDEF)                      last_error;
#if (defined(OSEE_USEPARAMETERACCESS)) || (defined(OSEE_HAS_ORTI))
  VAR(OSServiceIdType, TYPEDEF)                 service_id;
#endif /*OSEE_USEPARAMETERACCESS || OSEE_HAS_ORTI */
#if (defined(OSEE_USEPARAMETERACCESS))
  VAR(OsEE_api_param, TYPEDEF)                  api_param1;
  VAR(OsEE_api_param, TYPEDEF)                  api_param2;
  VAR(OsEE_api_param, TYPEDEF)                  api_param3;
#endif /* OSEE_USEPARAMETERACCESS */
#if (defined(OSEE_HAS_CONTEXT))
  VAR(OsEE_os_context, TYPEDEF)                 os_context;
#endif /* OSEE_HAS_CONTEXT */
#if (defined(OSEE_HAS_PRETASKHOOK))
  /* Needed to distinguish that PreTaskHook HAVE NOT to be called after an
   * ISR2 that terminate without a TASK rescheduling */
  P2VAR(OsEE_TDB, OS_APPL_DATA, TYPEDEF)        p_last_tdb_hook;
#endif /* OSEE_HAS_PRETASKHOOK */
  VAR(OsEE_reg,  TYPEDEF)                       prev_s_isr_all_status;
  VAR(OsEE_reg,  TYPEDEF)                       prev_s_isr_os_status;
  VAR(OsEE_byte, TYPEDEF)                       s_isr_all_cnt;
  VAR(OsEE_byte, TYPEDEF)                       s_isr_os_cnt;
  VAR(OsEE_byte, TYPEDEF)                       d_isr_all_cnt;
} OsEE_CCB;

typedef struct OsEE_CDB_tag {
  P2VAR(OsEE_CCB, TYPEDEF, OS_APPL_DATA)        p_ccb;
#if (defined(OSEE_HAS_IDLEHOOK)) || (defined(OSEE_API_DYNAMIC))
  VAR(TaskFunc, TYPEDEF)                        p_idle_hook;
#endif /* OSEE_HAS_IDLEHOOK || OSEE_API_DYNAMIC */
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_DATA)        p_idle_task;
#if (defined(OSTICKDURATION))
  P2VAR(OsEE_CounterDB, TYPEDEF, OS_APPL_DATA)  p_sys_counter_db;
#endif /*  */
#if (defined(OSEE_HAS_AUTOSTART_TASK))
  P2SYM_VAR(OsEE_autostart_tdb, OS_APPL_DATA,   p_autostart_tdb_array)[];
  VAR(MemSize, TYPEDEF)                         autostart_tdb_array_size;
#endif /* OSEE_HAS_AUTOSTART_TASK */
#if (defined(OSEE_HAS_AUTOSTART_TRIGGER))
  P2SYM_VAR(OsEE_autostart_trigger, OS_APPL_DATA, p_autostart_trigger_array)[];
  VAR(MemSize, TYPEDEF)                         autostart_trigger_array_size;
#endif /* OSEE_HAS_AUTOSTART_TRIGGER */
#if (!defined(OSEE_SINGLECORE))
  VAR(CoreIdType, TYPEDEF)                      core_id;
#endif /* !OSEE_SINGLECORE */
} OSEE_CONST OsEE_CDB;

typedef struct OsEE_KCB_tag {
#if (defined(OSEE_SCHEDULER_GLOBAL))
  VAR(OsEE_RQ, TYPEDEF)                   rq;
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA)   p_free_sn;
#if (defined(OSEE_API_DYNAMIC))
  VAR(MemSize, TYPEDEF)                   free_sn_counter;
#endif /* OSEE_API_DYNAMIC */
#endif /* OSEE_SCHEDULER_GLOBAL */
#if (defined(OSEE_API_DYNAMIC))
  VAR(MemSize, TYPEDEF)                   free_task_index;
#endif /* OSEE_API_DYNAMIC */
#if (defined(OSEE_HAS_RESOURCES)) && (defined(OSEE_API_DYNAMIC))
  VAR(MemSize, TYPEDEF)                   free_res_index;
#endif /* OSEE_HAS_RESOURCES && OSEE_API_DYNAMIC */
#if (defined(OSEE_HAS_COUNTERS)) && (defined(OSEE_API_DYNAMIC))
  VAR(MemSize, TYPEDEF)                   free_counter_index;
#if (defined(OSEE_HAS_ALARMS))
  VAR(MemSize, TYPEDEF)                   free_alarm_index;
#endif /* OSEE_HAS_ALARMS */
#endif /* OSEE_HAS_COUNTERS && OSEE_API_DYNAMIC */
#if (!defined(OSEE_SCHEDULER_GLOBAL)) && (!defined(OSEE_API_DYNAMIC))
  /* To not have an empty struct */
  VAR(OsEE_reg, TYPEDEF)                  dummy;
#endif /* !OSEE_SCHEDULER_GLOBAL && !OSEE_API_DYNAMIC */
} OsEE_KCB;

typedef struct OsEE_KDB_tag {
  P2VAR(OsEE_KCB, TYPEDEF, OS_APPL_DATA)          p_kcb;
  /* EG: No AUTOSAR Compiler Abstraction For Pointer To Array !!!
         ==> I need to invent one */
  P2SYM_CONSTP2VAR(OsEE_TDB, OS_APPL_DATA,        p_tdb_ptr_array)
    [/*OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES*/];
  P2SYM_VAR(OsEE_SN, OS_APPL_DATA,                p_sn_array)
    [/*OSEE_SN_ARRAY_SIZE*/];
  VAR(MemSize, TYPEDEF)                           tdb_array_size;
  VAR(MemSize, TYPEDEF)                           sn_array_size;
#if (defined(OSEE_HAS_RESOURCES))
  P2SYM_CONSTP2VAR(OsEE_MDB, OS_APPL_DATA,        p_res_ptr_array)[];
  VAR(MemSize, TYPEDEF)                           res_array_size;
#endif /* OSEE_HAS_RESOURCES */
#if (defined(OSEE_HAS_COUNTERS))
  P2SYM_CONSTP2VAR(OsEE_CounterDB, OS_APPL_DATA,  p_counter_ptr_array)[];
  VAR(MemSize, TYPEDEF)                           counter_array_size;
#if (defined(OSEE_HAS_ALARMS))
  P2SYM_CONSTP2VAR(OsEE_AlarmDB, OS_APPL_DATA,    p_alarm_ptr_array)[];
  VAR(MemSize, TYPEDEF)                           alarm_array_size;
#endif /* OSEE_HAS_ALARMS */
#if (defined(OSEE_HAS_SCHEDULE_TABLES))
  /* TODO: Schedule Tables */
#endif /* OSEE_HAS_SCHEDULE_TABLES */
#endif /* OSEE_HAS_COUNTERS */
} OSEE_CONST OsEE_KDB;

#if (defined(OSEE_API_EXTENSION))
typedef struct OsEE_sem_tag {
#if (!defined(OSEE_SINGLECORE))
  VAR(OsEE_spin_lock, TYPEDEF)          lock;
#endif /* !OSEE_SINGLECORE */
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA) blocked_queue;
  VAR(CountType, TYPEDEF)               count;
} OsEE_sem;

typedef struct OsEE_sem_tag SemType;

#endif /* OSEE_API_EXTENSION */

/* No portable Context Handling Function: has to be declared here to be
   visible in any HAL internal implementation. */
#if (!defined(OSEE_ISR2_INLINE))
extern FUNC(void, OS_CODE)
  osEE_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
);
#endif /* !OSEE_ISR2_INLINE */

/* Typical implementation of osEE_change_context_from_isr2_end is an inline
 * that acknowledge Interrupt Controller and call of the following */
extern FUNC(void, OS_CODE)
  osEE_change_context_from_task_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
);

extern FUNC(void, OS_CODE)
  osEE_idle_hook_wrapper
(
  void
);

#if (!defined(OSEE_KERNEL_TERMINATE_ACTIVATION_CB))
#define OSEE_KERNEL_TERMINATE_ACTIVATION_CB &osEE_scheduler_task_end
#else
#define OSEE_KERNEL_TERMINATE_ACTIVATION_OVERRIDE
#endif

#endif /* !OSEE_KERNEL_TYPES_H */
