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

#ifndef OSEE_KERNEL_TYPES_H
#define OSEE_KERNEL_TYPES_H

#include "ee_cfg.h"
#include "ee_api_types.h"
#include "ee_oo_api_extension.h"
#include "ee_hal_internal_types.h"
#include "ee_scheduler_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#if (!defined(OSEE_SINGLECORE)) && (defined(OSEE_SCHEDULER_GLOBAL))
#define OSEE_ALLOW_TASK_MIGRATION
#endif /* OSEE_SINGLECORE && OSEE_SCHEDULER_GLOBAL */

#if (defined(OSEE_HAS_ERRORHOOK)) || (defined(OSEE_HAS_SERVICE_PROTECTION))
#define OSEE_HAS_CONTEXT
#endif /* OSEE_HAS_ERRORHOOK || OSEE_HAS_SERVICE_PROTECTION */

#if (defined(OSEE_EXTENDED_STATUS)) || (defined(OSEE_HAS_SERVICE_PROTECTION))
#define OSEE_HAS_CHECKS
#endif /* OSEE_EXTENDED_STATUS || OSEE_HAS_SERVICE_PROTECTION */

/* Kernel Callback */
typedef P2FUNC(void, OS_APPL_DATA, OsEE_kernel_cb) (void);
/* Byte: the smallest type instantiable */
typedef VAR(uint8_t, TYPEDEF) OsEE_byte;
#define OSEE_MAX_BYTE               ((OsEE_byte)-1)

/*[OS_SWS_088] If an OS-Application makes a service call from the wrong
 * context AND is currently not inside a Category 1 ISR the Operating System
 * module shall not perform the requested action
 * (the service call shall have no effect), and return E_OS_CALLEVEL
 * (see [12], section 13.1) or the "invalid value" of the service.
 * (BSW11009, BSW11013) */
/** @typedef OS-Application contexts enum used to implement Autosar OS
 *  OS_SWS_088 requirement. Used in addition to handle not recursive calls at
 *  ErrorHook */
typedef enum {
  OSEE_KERNEL_CTX,
  OSEE_IDLE_CTX,
  OSEE_TASK_CTX,
  OSEE_TASK_ISR2_CTX,
  OSEE_ERRORHOOK_CTX,
  OSEE_PROTECTIONHOOK_CTX,
  OSEE_PRETASKHOOK_CTX,
  OSEE_POSTTASKHOOK_CTX,
  OSEE_STARTUPHOOK_CTX,
  OSEE_SHUTDOWNHOOK_CTX,
  OSEE_ALARMCALLBACK_CTX
} OsEE_os_context;

typedef enum {
#if (defined(OSEE_API_DYNAMIC))
  OSEE_KERNEL_UNINITIALIZED,
#endif /* OSEE_API_DYNAMIC */
  OSEE_KERNEL_INITIALIZED,
  OSEE_KERNEL_STARTING,
  OSEE_KERNEL_STARTED,
  OSEE_KERNEL_SHUTDOWN
} OsEE_kernel_status;

#if (defined(OSEE_HAS_RESOURCES)) || (defined(OSEE_HAS_SPINLOCKS))
  /* [SWS_Os_00801] If Spinlocks and Resources are locked by a Task/ISR they
      have to be unlocked in strict LIFO order. ReleaseResource() shall return
      E_OS_NOFUNC if the unlock order is violated.
      No other functionality shall be performed. (SRS_Os_80021) */
/* Forward declaration of MDB & TDB, needed for MCB p_next and
   p_owner fields. */
#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_SPINLOCKS))
struct OsEE_TDB_tag;
#endif /* OSEE_HAS_ORTI || OSEE_HAS_SPINLOCKS */
struct OsEE_MDB_tag;

typedef struct {
  P2VAR(struct OsEE_MDB_tag OSEE_CONST, TYPEDEF, OS_APPL_CONST)
    p_next;
  VAR(TaskPrio, TYPEDEF)
    prev_prio;
  P2VAR(struct OsEE_TDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA)
    p_owner;
} OsEE_MCB;

#if (defined(OSEE_HAS_RESOURCES)) && (defined(OSEE_HAS_SPINLOCKS))
typedef enum {
  OSEE_M_RESOURCE,
  OSEE_M_SPINLOCK
} OsEE_m_type;
#endif /* OSEE_HAS_RESOURCES && OSEE_HAS_SPINLOCKS */

typedef struct OsEE_MDB_tag {
  P2VAR(OsEE_MCB, TYPEDEF, OS_APPL_DATA)        p_cb;
#if (defined(OSEE_HAS_SPINLOCKS))
  P2VAR(OsEE_spin_lock, TYPEDEF, OS_APPL_DATA)  p_spinlock_arch;
#endif /* OSEE_HAS_SPINLOCKS */
#if (defined(OSEE_HAS_RESOURCES)) || (defined(OSEE_SPINLOCKS_HAS_LOCK_METHOD))
  VAR(TaskPrio, TYPEDEF)                        prio;
#endif /* OSEE_HAS_RESOURCES || OSEE_SPINLOCKS_HAS_LOCK_METHOD */
#if (!defined(OSEE_SINGLECORE))
  VAR(CoreMaskType, TYPEDEF)                    allowed_core_mask;
#endif /* !OSEE_SINGLECORE */
#if (defined(OSEE_HAS_RESOURCES)) && (defined(OSEE_HAS_SPINLOCKS))
  VAR(OsEE_m_type, TYPEDEF)                     m_type;
#endif /* OSEE_HAS_RESOURCES && OSEE_HAS_SPINLOCKS */
} OSEE_CONST OsEE_MDB;

#if (defined(OSEE_HAS_RESOURCES))
typedef OsEE_MCB OsEE_ResourceCB;
typedef OsEE_MDB OsEE_ResourceDB;
#endif /* OSEE_HAS_RESOURCES */

#if (defined(OSEE_HAS_SPINLOCKS))
typedef OsEE_MCB OsEE_SpinlockCB;
typedef OsEE_MDB OsEE_SpinlockDB;
#endif /* OSEE_HAS_SPINLOCKS */
#endif /* OSEE_HAS_RESOURCES || OSEE_HAS_SPINLOCKS */

typedef struct {
  VAR(TaskActivation, TYPEDEF)                  current_num_of_act;
  VAR(TaskPrio, TYPEDEF)                        current_prio;
  VAR(TaskStateType, TYPEDEF)                   status;
#if (defined(OSEE_HAS_RESOURCES)) || (defined(OSEE_HAS_SPINLOCKS))
  P2VAR(OsEE_MDB, TYPEDEF, OS_APPL_DATA)        p_last_m;
#endif /* OSEE_HAS_RESOURCES || OSEE_HAS_SPINLOCKS */
#if (defined(OSEE_HAS_EVENTS))
  VAR(EventMaskType, TYPEDEF)                   wait_mask;
  VAR(EventMaskType, TYPEDEF)                   event_mask;
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA)         p_own_sn;
#endif /* OSEE_HAS_EVENTS */
#if (defined(OSEE_ALLOW_TASK_MIGRATION))
  VAR(CoreIdType, TYPEDEF)                      current_core_id;
#endif /* OSEE_ALLOW_TASK_MIGRATION */
} OsEE_TCB;

typedef struct OsEE_TDB_tag
{
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

typedef struct {
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

typedef struct {
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

typedef struct {
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

typedef struct {
  VAR(OsEE_kernel_cb, TYPEDEF)                  f;
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_DATA)        p_tdb;
  P2VAR(OsEE_CounterDB, TYPEDEF, OS_APPL_DATA)  p_counter_db;
#if (defined(OSEE_HAS_EVENTS))
  VAR(EventMaskType, TYPEDEF)                   mask;
#endif /* OSEE_HAS_EVENTS */
} OsEE_action_param;

typedef struct {
  VAR(OsEE_action_param, TYPEDEF)               param;
  VAR(OsEE_action_type, TYPEDEF)                type;
} OSEE_CONST OsEE_action;

#if (defined(OSEE_HAS_SCHEDULE_TABLES))
/** @typedef Schedule Table Synchronization strategies symbols */
typedef enum {
  /** No support for synchronization. (default) */
  OSEE_SCHEDTABLE_SYNC_NONE,
  /** The counter driving the schedule table is the counter with which
      synchronization is required */
  OSEE_SCHEDTABLE_SYNC_IMPLICIT,
  /** The schedule table is driven by an OS counter but processing needs to be
      synchronized with a different counter which is not an OS counter object.
      Specification of Operating System */
  OSEE_SCHEDTABLE_SYNC_EXPLICIT
} OsEE_st_synch_strategy;

/** @typedef to have a more harmonized type name with other OSEK type names. */
typedef OsEE_st_synch_strategy SynchStrategyType;

/** @typedef Structures that hold the information related to an expiry point */
typedef struct OsEE_st_exipiry_point_tag{
  /** Expiry point offset in its own schedule table */
  VAR(TickType, TYPEDEF)                offset;
  /** Array of the expiry point's actions */
  P2SYM_VAR(OsEE_action, OS_APPL_DATA,  p_action_array)[];
  /** Sizeof array of the expiry point's actions */
  VAR(MemSize, TYPEDEF)                 action_array_size;
  /** Maximum value that can be subtracted from the expiry offset */
  VAR(TickType, TYPEDEF)                max_shorten;
  /** Maximum value that can be added to the expiry point offset */
  VAR(TickType, TYPEDEF)                max_lengthen;
} OSEE_CONST OsEE_st_exipiry_point;
#endif /* OSEE_HAS_SCHEDULE_TABLES */

#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
typedef struct OsEE_AlarmCB_tag {
  VAR(TickType, TYPEDEF)                      cycle;
} OsEE_AlarmCB;

typedef struct OsEE_AlarmDB_tag {
  P2VAR(OsEE_AlarmCB, TYPEDEF, OS_APPL_DATA)  p_alarm_cb;
  P2VAR(struct OsEE_TriggerDB_tag OSEE_CONST, TYPEDEF, OS_APPL_CONST)
                                              p_trigger_db;
  VAR(OsEE_action, TYPEDEF)                   action;
} OSEE_CONST OsEE_AlarmDB;

/**
 * @typedef EE_as_Schedule_Table_RAM_type
 *
 * Data structure to store variable informations about a schedule table.
 */
typedef struct OsEE_SchedTabCB_tag {
  /** ID of next schedule table to be started */
  P2VAR(struct OsEE_SchedTabDB_tag OSEE_CONST, TYPEDEF, OS_APPL_CONST)
                                              p_next_table;
  /** Schedule Table underlying counter Start value */
  VAR(TickType, TYPEDEF)                      start;
  /** Schedule Table current status */
  VAR(ScheduleTableStatusType, TYPEDEF)       st_status;
  /** Expiry point to be processed in the schedule table. I use an index
      instead a pointer to not rely in pointer arithmetic that is no compliant
      with MISRA */
  VAR(MemSize, TYPEDEF)                       position;
  /** Deviation of the schedule table from synchronization */
  VAR(TickDeltaType, TYPEDEF)                 deviation;
} OsEE_SchedTabCB;

/**
 * @typedef OsEE_schedule_table_db
 *
 * This is the data structure used to describe the constant part of a
 * schedule table. */
typedef struct OsEE_SchedTabDB_tag {
  /** Pointer to corresponding Control Block */
  P2VAR(OsEE_SchedTabCB, TYPEDEF, OS_APPL_DATA) p_st_cb;
  /** Pointer to corresponding Schedule Table Trigger */
  P2VAR(struct OsEE_TriggerDB_tag OSEE_CONST, TYPEDEF, OS_APPL_CONST)
                                                p_trigger_db;
  /** Array of the schedule table's expiry points */
  P2SYM_VAR(OsEE_st_exipiry_point, OS_APPL_CONST, p_expiry_point_array)[];
  /** Size of array of the schedule table's expiry point */
  VAR(MemSize, TYPEDEF)                         expiry_point_array_size;
  /** Schedule table synchronization strategy */
  VAR(SynchStrategyType, TYPEDEF)               sync_strategy;
  /** The length of the schedule table in ticks */
  VAR(TickType, TYPEDEF)                        duration;
  /** Minimum deviation from synchronization source to be synchronized */
  VAR(TickDeltaType, TYPEDEF)                   precision;
  /** OSTRUE if the schedule table shall be repeated after the last expiry
      point, FALSE if the schedule table is single-shot */
  VAR(OsEE_bool, TYPEDEF)                       repeated;
#if (defined(OSEE_HAS_OSAPPLICATIONS))
  /** The ID of the application to which this schedule table belong to. */
  VAR(ApplicationType, TYPEDEF)                 ApplID;
#endif /* OSEE_HAS_OSAPPLICATIONS */
} OSEE_CONST OsEE_SchedTabDB;
#endif /* OSEE_COUNTER_TRIGGER_TYPES */

/**
 * I will handle concurrent updates for triggers thanks this status 
 */
typedef enum {
  OSEE_TRIGGER_INACTIVE,
  OSEE_TRIGGER_CANCELED,
  OSEE_TRIGGER_ACTIVE,
  OSEE_TRIGGER_EXPIRED,
  OSEE_TRIGGER_REENABLED
} OsEE_trigger_status;

typedef struct {
  P2VAR(struct OsEE_TriggerDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA)  p_next;
  VAR(TickType, TYPEDEF)                                              when;
  VAR(OsEE_trigger_status, TYPEDEF)                                   status;
#if (!defined(OSEE_COUNTER_TRIGGER_TYPES))
#if (defined(OSEE_HAS_ALARMS))
  VAR(TickType, TYPEDEF)                                              cycle;
#elif (defined(OSEE_HAS_SCHEDULE_TABLES))
  /** ID of next schedule table to be started */
  P2VAR(struct OsEE_TriggerDB_tag OSEE_CONST, TYPEDEF, OS_APPL_CONST)
                                                              p_next_table;
  /** Schedule Table underlying counter Start value */
  VAR(TickType, TYPEDEF)                                      start;
  /** Schedule Table current status */
  VAR(ScheduleTableStatusType, TYPEDEF)                       st_status;
  /** Expiry point to be processed in the schedule table. I use an index
      instead a pointer to not rely in pointer arithmetic that is no compliant
      with MISRA */
  VAR(MemSize, TYPEDEF)                                       position;
  /** Deviation of the schedule table from synchronization */
  VAR(TickDeltaType, TYPEDEF)                                 deviation;
#endif /* OSEE_HAS_ALARMS elif OSEE_HAS_SCHEDULE_TABLES */
#endif /* !OSEE_COUNTER_TRIGGER_TYPES */
} OsEE_TriggerCB;

typedef struct OsEE_TriggerDB_tag {
  P2VAR(OsEE_TriggerCB, TYPEDEF, OS_APPL_DATA)              p_trigger_cb;
  P2VAR(OsEE_CounterDB, TYPEDEF, OS_APPL_DATA)              p_counter_db;
#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
  P2VAR(struct OsEE_AlarmDB_tag OSEE_CONST, TYPEDEF, OS_APPL_CONST)
                                                            p_alarm_db;
  P2VAR(struct OsEE_SchedTabDB_tag OSEE_CONST, TYPEDEF, OS_APPL_CONST)
                                                            p_st_db;
#elif (defined(OSEE_HAS_ALARMS))
  VAR(OsEE_action, TYPEDEF)                                 action;
#elif (defined(OSEE_HAS_SCHEDULE_TABLES))
  /** Array of the schedule table's expiry points */
  P2SYM_VAR(OsEE_st_exipiry_point, OS_APPL_CONST, p_expiry_point_array)[];
  /** Size of array of the schedule table's expiry point */
  VAR(MemSize, TYPEDEF)                         expiry_point_array_size;
  /** Schedule table synchronization strategy */
  VAR(SynchStrategyType, TYPEDEF)               sync_strategy;
  /** The length of the schedule table in ticks */
  VAR(TickType, TYPEDEF)                        duration;
  /** Minimum deviation from synchronization source to be synchronized */
  VAR(TickDeltaType, TYPEDEF)                   precision;
  /** OSEE_TRUE if the schedule table shall be repeated after the last expiry
      point, FALSE if the schedule table is single-shot */
  VAR(OsEE_bool, TYPEDEF)                       repeated;
#if (defined(OSEE_HAS_OSAPPLICATIONS))
  /** The ID of the application to which this schedule table belong to. */
  VAR(ApplicationType, TYPEDEF)                 ApplID;
#endif /* OSEE_HAS_OSAPPLICATIONS */
#endif /* OSEE_COUNTER_TRIGGER_TYPES elif OSEE_HAS_ALARMS elif
          OSEE_HAS_SCHEDULE_TABLES */
} OSEE_CONST OsEE_TriggerDB;

#if (!defined(OSEE_COUNTER_TRIGGER_TYPES))
#if (defined(OSEE_HAS_ALARMS))
typedef OsEE_TriggerCB OsEE_AlarmCB;
typedef OsEE_TriggerDB OsEE_AlarmDB;
#elif (defined(OSEE_HAS_SCHEDULE_TABLES))
typedef OsEE_TriggerCB OsEE_SchedTabCB;
typedef OsEE_TriggerDB OsEE_SchedTabDB;
#endif /* OSEE_HAS_ALARMS elif OSEE_HAS_SCHEDULE_TABLES */
#endif /* !OSEE_COUNTER_TRIGGER_TYPES */

#if (defined(OSEE_HAS_AUTOSTART_TRIGGER))
#if (defined(OSEE_HAS_SCHEDULE_TABLES))
typedef enum osEE_autostart_trigger_info_type_tag {
  OSEE_AUTOSTART_ALARM,
  OSEE_AUTOSTART_SCHEDULE_TABLE_ABS,
  OSEE_AUTOSTART_SCHEDULE_TABLE_REL,
  OSEE_AUTOSTART_SCHEDULE_TABLE_SYNCHRON
} osEE_autostart_trigger_info_type;
#endif /* OSEE_HAS_SCHEDULE_TABLES */

typedef struct {
  P2VAR(OsEE_TriggerDB, TYPEDEF, OS_APPL_CONST)   p_trigger_db;
  VAR(TickType, TYPEDEF)                          first_tick_parameter;
#if (defined(OSEE_HAS_ALARMS))
  VAR(TickType, TYPEDEF)                          second_tick_parameter;
#endif /* OSEE_HAS_ALARMS */
#if (defined(OSEE_HAS_SCHEDULE_TABLES)) 
  VAR(osEE_autostart_trigger_info_type, TYPEDEF)  autostart_type;
#endif /* OSEE_HAS_SCHEDULE_TABLES */
} OSEE_CONST OsEE_autostart_trigger_info;

typedef struct {
  P2SYM_VAR(OsEE_autostart_trigger_info, OS_APPL_CONST, p_trigger_ptr_array)[];
  VAR(MemSize, TYPEDEF)                                 trigger_array_size;
} OSEE_CONST OsEE_autostart_trigger;
#endif /* OSEE_HAS_AUTOSTART_TRIGGER */
#endif /* OSEE_HAS_COUNTERS */

#if (defined(OSEE_HAS_AUTOSTART_TASK))
typedef struct OsEE_autostart_tdb_tag {
  P2SYM_CONSTP2VAR(OsEE_TDB, OS_APPL_CONST, p_tdb_ptr_array)[];
  VAR(MemSize, TYPEDEF)                     tdb_array_size;
} OSEE_CONST OsEE_autostart_tdb;
#endif /* !OSEE_HAS_AUTOSTART_TASK */

typedef struct {
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_CONST)         p_curr;
#if (!defined(OSEE_SINGLECORE)) && (defined(OSEE_SCHEDULER_GLOBAL))
  P2VAR(OsEE_spin_lock, TYPEDEF, OS_APPL_DATA)    p_lock_to_be_released;
#endif /* !OSEE_SINGLECORE && OSEE_SCHEDULER_GLOBAL */
#if (!defined(OSEE_SCHEDULER_GLOBAL))
  VAR(OsEE_RQ, TYPEDEF)                           rq;
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA)           p_free_sn;
#if (defined(OSEE_API_DYNAMIC))
  VAR(MemSize, TYPEDEF)                           free_sn_counter;
#endif /* OSEE_API_DYNAMIC */
#endif /* !OSEE_SCHEDULER_GLOBAL */
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA)           p_stk_sn;
  VAR(OsEE_kernel_status volatile, TYPEDEF)       os_status;
  VAR(AppModeType, TYPEDEF)                       app_mode;
  /* Error Handling variables */
  VAR(StatusType, TYPEDEF)                        last_error;
#if (defined(OSEE_USEGETSERVICEID)) || (defined(OSEE_USEPARAMETERACCESS)) ||\
    (defined(OSEE_HAS_ORTI))
  VAR(OSServiceIdType, TYPEDEF)                   service_id;
#endif /* OSEE_USEGETSERVICEID || OSEE_USEPARAMETERACCESS || OSEE_HAS_ORTI */
#if (defined(OSEE_USEPARAMETERACCESS))
  VAR(OsEE_api_param, TYPEDEF)                    api_param1;
  VAR(OsEE_api_param, TYPEDEF)                    api_param2;
  VAR(OsEE_api_param, TYPEDEF)                    api_param3;
#endif /* OSEE_USEPARAMETERACCESS */
#if (defined(OSEE_HAS_CONTEXT))
  VAR(OsEE_os_context, TYPEDEF)                   os_context;
#endif /* OSEE_HAS_CONTEXT */
#if (defined(OSEE_HAS_PRETASKHOOK))
  /* Needed to distinguish that PreTaskHook HAVE NOT to be called after an
   * ISR2 that terminate without a TASK rescheduling */
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_CONST)         p_last_tdb_hook;
#endif /* OSEE_HAS_PRETASKHOOK */
#if (defined(OSEE_HAS_SPINLOCKS))
  P2VAR(OsEE_SpinlockDB, TYPEDEF, OS_APPL_CONST)  p_last_spinlock;
#endif /* OSEE_HAS_SPINLOCKS */
  VAR(OsEE_reg,  TYPEDEF)                         prev_s_isr_all_status;
  VAR(OsEE_reg,  TYPEDEF)                         prev_s_isr_os_status;
  VAR(OsEE_byte, TYPEDEF)                         s_isr_all_cnt;
  VAR(OsEE_byte, TYPEDEF)                         s_isr_os_cnt;
  VAR(OsEE_byte, TYPEDEF)                         d_isr_all_cnt;
#if (defined(OSEE_HAS_ORTI))
  VAR(OsEE_bool, TYPEDEF)                         orti_service_id_valid;
#endif /* OSEE_HAS_ORTI */
} OsEE_CCB;

typedef struct {
#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
  VAR(OsEE_CHDB, TYPEDEF)                         chdb;
#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */
  P2VAR(OsEE_CCB, TYPEDEF, OS_APPL_DATA)          p_ccb;
#if (!defined(OSEE_SINGLECORE))
  P2VAR(OsEE_spin_lock, TYPEDEF,OS_APPL_DATA)     p_lock;
#endif /* !OSEE_SINGLECORE */
#if (defined(OSEE_HAS_IDLEHOOK)) || (defined(OSEE_API_DYNAMIC))
  VAR(TaskFunc, TYPEDEF)                          p_idle_hook;
#endif /* OSEE_HAS_IDLEHOOK || OSEE_API_DYNAMIC */
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_CONST)         p_idle_task;
#if (defined(OSEE_HAS_SYSTEM_TIMER))
  P2VAR(OsEE_CounterDB, TYPEDEF, OS_APPL_CONST)   p_sys_counter_db;
#endif /* OSEE_HAS_SYSTEM_TIMER */
#if (defined(OSEE_HAS_AUTOSTART_TASK))
  P2SYM_VAR(OsEE_autostart_tdb, OS_APPL_CONST,    p_autostart_tdb_array)[];
  VAR(MemSize, TYPEDEF)                           autostart_tdb_array_size;
#endif /* OSEE_HAS_AUTOSTART_TASK */
#if (defined(OSEE_HAS_AUTOSTART_TRIGGER))
  P2SYM_VAR(OsEE_autostart_trigger, OS_APPL_CONST, p_autostart_trigger_array)[];
  VAR(MemSize, TYPEDEF)                           autostart_trigger_array_size;
#endif /* OSEE_HAS_AUTOSTART_TRIGGER */
#if (!defined(OSEE_SINGLECORE))
  VAR(CoreIdType, TYPEDEF)                        core_id;
#endif /* !OSEE_SINGLECORE */
} OSEE_CONST OsEE_CDB;

typedef struct {
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
#if (defined(OSEE_HAS_SCHEDULE_TABLES))
  VAR(MemSize, TYPEDEF)                   free_st_index;
#endif /* OSEE_HAS_SCHEDULE_TABLES */
#endif /* OSEE_HAS_COUNTERS && OSEE_API_DYNAMIC */
#if (!defined(OSEE_SINGLECORE))
  VAR(CoreMaskType, TYPEDEF)              ar_core_mask;
  VAR(CoreMaskType, TYPEDEF)              not_ar_core_mask;
  VAR(CoreMaskType, TYPEDEF)              ar_shutdown_mask;
  VAR(CoreNumType,  TYPEDEF)              ar_num_core_started;
  VAR(StatusType, TYPEDEF)                ar_shutdown_all_cores_error;
  VAR(OsEE_bool, TYPEDEF)                 ar_shutdown_all_cores_flag;
#endif /* !OSEE_SINGLECORE */
#if (defined(OSEE_SINGLECORE)) && (!defined(OSEE_API_DYNAMIC))
  /* To not have an empty struct */
  VAR(OsEE_reg, TYPEDEF)                  dummy;
#endif /* OSEE_SINGLECORE && !OSEE_API_DYNAMIC */
} OsEE_KCB;

typedef struct {
  P2VAR(OsEE_KCB, TYPEDEF, OS_APPL_DATA)            p_kcb;
#if (!defined(OSEE_SINGLECORE))
  P2VAR(OsEE_spin_lock, TYPEDEF,OS_APPL_DATA)       p_lock;
  P2VAR(OsEE_barrier, TYPEDEF,OS_APPL_DATA)         p_barrier;
#endif /* !OSEE_SINGLECORE */
  /* EG: No AUTOSAR Compiler Abstraction For Pointer To Array !!!
         ==> I need to invent one */
  P2SYM_CONSTP2VAR(OsEE_TDB, OS_APPL_CONST,         p_tdb_ptr_array)
    [/*OSEE_TASK_ARRAY_SIZE + OsNumberOfCores*/];
  VAR(MemSize, TYPEDEF)                             tdb_array_size;
#if (defined(OSEE_ALLOW_TASK_MIGRATION))
  P2SYM_VAR(OsEE_SN, OS_APPL_DATA,                  p_sn_array)
    [/*OSEE_SN_ARRAY_SIZE*/];
  VAR(MemSize, TYPEDEF)                             sn_array_size;
#endif /* OSEE_ALLOW_TASK_MIGRATION */
#if (defined(OSEE_ALLOW_TASK_MIGRATION))
#endif /* OSEE_ALLOW_TASK_MIGRATION */
#if (defined(OSEE_HAS_RESOURCES))
  P2SYM_CONSTP2VAR(OsEE_ResourceDB, OS_APPL_CONST,  p_res_ptr_array)[];
  VAR(MemSize, TYPEDEF)                             res_array_size;
#endif /* OSEE_HAS_RESOURCES */
#if (defined(OSEE_HAS_COUNTERS))
  P2SYM_CONSTP2VAR(OsEE_CounterDB, OS_APPL_CONST,   p_counter_ptr_array)[];
  VAR(MemSize, TYPEDEF)                             counter_array_size;
#if (defined(OSEE_HAS_ALARMS))
  P2SYM_CONSTP2VAR(OsEE_AlarmDB, OS_APPL_CONST,     p_alarm_ptr_array)[];
  VAR(MemSize, TYPEDEF)                             alarm_array_size;
#endif /* OSEE_HAS_ALARMS */
#if (defined(OSEE_HAS_SCHEDULE_TABLES))
  P2SYM_CONSTP2VAR(OsEE_SchedTabDB, OS_APPL_CONST,  p_st_ptr_array)[];
  VAR(MemSize, TYPEDEF)                             st_array_size;
#endif /* OSEE_HAS_SCHEDULE_TABLES */
#endif /* OSEE_HAS_COUNTERS */
#if (defined(OSEE_HAS_SPINLOCKS))
  P2SYM_VAR(OsEE_SpinlockDB, OS_APPL_CONST,         p_spinlock_array)[];
  VAR(MemSize, TYPEDEF)                             spinlock_array_size;
#endif /* OSEE_HAS_SPINLOCKS */
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

/* Definition of default terminate activation "kernel" callback (CB), and
   override declaration handling */
#if (!defined(OSEE_KERNEL_TERMINATE_ACTIVATION_CB))
#define OSEE_KERNEL_TERMINATE_ACTIVATION_CB &osEE_scheduler_task_end
#else
#if (!defined(OSEE_KERNEL_TERMINATE_ACTIVATION_OVERRIDE))
#define OSEE_KERNEL_TERMINATE_ACTIVATION_OVERRIDE
#endif /* !OSEE_KERNEL_TERMINATE_ACTIVATION_OVERRIDE */
#endif /* !OSEE_KERNEL_TERMINATE_ACTIVATION_CB */

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_KERNEL_TYPES_H */
