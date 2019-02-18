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
/** This architecture requires the saving of a context in the CCB 
 *  (Core Control Block)
 */
#define OSEE_HAS_CONTEXT
#endif /* OSEE_HAS_ERRORHOOK || OSEE_HAS_SERVICE_PROTECTION */

#if (defined(OSEE_EXTENDED_STATUS)) || (defined(OSEE_HAS_SERVICE_PROTECTION))
#define OSEE_HAS_CHECKS
#endif /* OSEE_EXTENDED_STATUS || OSEE_HAS_SERVICE_PROTECTION */

/** Kernel Callback */
typedef P2FUNC(void, OS_APPL_DATA, OsEE_kernel_cb) (void);
/** Byte: the smallest type instantiable */
typedef VAR(uint8_t, TYPEDEF) OsEE_byte;
/** Byte: the maximum value for a byte */
/** Byte: the maximum value for a byte */
#define OSEE_MAX_BYTE               ((OsEE_byte)-1)

/*[OS_SWS_088] If an OS-Application makes a service call from the wrong
 * context AND is currently not inside a Category 1 ISR the Operating System
 * module shall not perform the requested action
 * (the service call shall have no effect), and return E_OS_CALLEVEL
 * (see [12], section 13.1) or the "invalid value" of the service.
 * (BSW11009, BSW11013) */
/** OS-Application contexts enum used to implement Autosar OS
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

/**
 *  This enumerate controls the status of the kernel over the application
 *  execution.
 */
typedef enum {
#if (defined(OSEE_API_DYNAMIC))
  OSEE_KERNEL_UNINITIALIZED,   /**< OS not yet initialized */
#endif /* OSEE_API_DYNAMIC */
  OSEE_KERNEL_INITIALIZED,     /**< before OS initialization */
  OSEE_KERNEL_STARTING,        /**< before the call to StartupHook() 
                                    and autostart */
  OSEE_KERNEL_STARTED,         /**< after the call to StartupHook() 
                                    and autostart */
  OSEE_KERNEL_SHUTDOWN         /**< ShutdownOS() called */
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

/**
 *  Mutual exclusion control block. The system needs to track the order in which
 *  Resources and Spin-locks are taken in order to verify they are released in 
 *  LIFO order [SWS_Os_00801]. Also the owner has to be tracked.
 */
typedef struct {
  /** pointer to the next ''mutex'' (the system needs to guarantee the LIFO
   *  order of the semaphore/spin lock allocation) */
  P2VAR(struct OsEE_MDB_tag OSEE_CONST, TYPEDEF, OS_APPL_CONST)
    p_next;
  /** this is the previous task priority when the mutex was locked. */
  VAR(TaskPrio, TYPEDEF)
    prev_prio;
  /** owner of the mutex/spinlock */
  P2VAR(struct OsEE_TDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA)
    p_owner;
} OsEE_MCB;

#if (defined(OSEE_HAS_RESOURCES)) && (defined(OSEE_HAS_SPINLOCKS))
/**
 *  \brief Mutual Exclusion type. 
 *  
 *  The Mutual exclusion type is only present if the application uses both 
 *  Resources and Spin locks, and is used to mark the type of the specific 
 *  object (either a Resource or a Spin Lock). The idea is that when the 
 *  application only has one type of these objects (either only Resources 
 *  or only Spin Locks), the system is optimized reducing the overhead of 
 *  the additional indirection.
 */
typedef enum {
  OSEE_M_RESOURCE,
  OSEE_M_SPINLOCK
} OsEE_m_type;
#endif /* OSEE_HAS_RESOURCES && OSEE_HAS_SPINLOCKS */

/**
 *  \brief Mutual exclusion descriptor block.
 *  
 *  The descriptor block tracks the specific mutual exclusion object, which 
 *  can be either a Resource or a Spin Lock. They are handled together because
 *  they have to be released in LIFO order [SWS_Os_00801].
 */
typedef struct OsEE_MDB_tag {
  /** pointer to the flash descriptor (shortcut to optimize the system access */
  P2VAR(OsEE_MCB, TYPEDEF, OS_APPL_DATA)        p_cb;
#if (defined(OSEE_HAS_SPINLOCKS))
  /** HAL part of the spinlock. a register if the spinlock is hardware,
   *  or a data structure if done in memory */
  P2VAR(OsEE_spin_lock, TYPEDEF, OS_APPL_DATA)  p_spinlock_arch; 
#endif /* OSEE_HAS_SPINLOCKS */
#if (defined(OSEE_HAS_RESOURCES)) || (defined(OSEE_SPINLOCKS_HAS_LOCK_METHOD))
  /** ceiling priority of the resource or of the spinlock (note that
   *  the spinlock may be configured to have its own ceiling. The
   *  virtual priorities in ERIKA3 allows a simple way to obtain the
   *  various levels of priority raising for the spinlocks (e.g.,
   *  OSEE_ISR_ALL_PRIO means that all ISR are blocked) */
  VAR(TaskPrio, TYPEDEF)                        prio;
#endif /* OSEE_HAS_RESOURCES || OSEE_SPINLOCKS_HAS_LOCK_METHOD */
#if (!defined(OSEE_SINGLECORE))
  /** these are the cores that are allowed to use the resource/spinlock */
  VAR(CoreMaskType, TYPEDEF)                    allowed_core_mask;
#endif /* !OSEE_SINGLECORE */
#if (defined(OSEE_HAS_RESOURCES)) && (defined(OSEE_HAS_SPINLOCKS))
  /** type that says whether this data structure is related to a resource or a
   *  spinlock */
  VAR(OsEE_m_type, TYPEDEF)                     m_type;
#endif /* OSEE_HAS_RESOURCES && OSEE_HAS_SPINLOCKS */
} OSEE_CONST OsEE_MDB;

#if (defined(OSEE_HAS_RESOURCES))
typedef OsEE_MCB OsEE_ResourceCB; /**< The Resource Control Block */
typedef OsEE_MDB OsEE_ResourceDB; /**< The Resource Descriptor Block */
#endif /* OSEE_HAS_RESOURCES */

#if (defined(OSEE_HAS_SPINLOCKS))
typedef OsEE_MCB OsEE_SpinlockCB; /**< The Spin Lock Control Block */
typedef OsEE_MDB OsEE_SpinlockDB; /**< The Spin Lock Descriptor Block */
#endif /* OSEE_HAS_SPINLOCKS */
#endif /* OSEE_HAS_RESOURCES || OSEE_HAS_SPINLOCKS */

/**
 *  The Task Control Block. It stores all the information related to the task
 *  that can change at runtime such as: number of pending activation, current
 *  priority, status, wait and event mask, ...
 */
typedef struct {
  /** number of pending activations of the task. When the task is suspended,
   *  the counter is 0. When activated, the counter is incremented.
   *  When the task terminates, the counter is decremented. */
  VAR(TaskActivation, TYPEDEF)                  current_num_of_act;
  /** current task priority. The priority can be raised by the usage
   *  of resources or spin locks following the Immediate Priority
   *  Ceiling Protocol. The current_prio is set to dispatch_priority
   *  when a task is scheduled to implement the Internal resources /
   *  Preemption thresholds handling. */
  VAR(TaskPrio, TYPEDEF)                        current_prio;
  /** Task status */
  VAR(TaskStateType, TYPEDEF)                   status;
#if (defined(OSEE_HAS_RESOURCES)) || (defined(OSEE_HAS_SPINLOCKS))
  /** pointer to the last resource or spinlock taken */
  P2VAR(OsEE_MDB, TYPEDEF, OS_APPL_DATA)        p_last_m;
#endif /* OSEE_HAS_RESOURCES || OSEE_HAS_SPINLOCKS */
#if (defined(OSEE_HAS_EVENTS))
  /** wait mask, used only for extended tasks */
  VAR(EventMaskType, TYPEDEF)                   wait_mask;
  /** event mask, used only for extended tasks */
  VAR(EventMaskType, TYPEDEF)                   event_mask;
  /** Scheduler node. When a task blocks we need a place to temporary
   *  save the associated scheduler node, to be used again when the
   *  task is reallocated again. This avoids a race condition on the
   *  free scheduler node list that happens in the SetEvent when the
   *  task status changes on wakeup. */
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA)         p_own_sn;
#endif /* OSEE_HAS_EVENTS */
#if (defined(OSEE_ALLOW_TASK_MIGRATION))
  /** current core id where the task is currently running */
  VAR(CoreIdType, TYPEDEF)                      current_core_id;
#endif /* OSEE_ALLOW_TASK_MIGRATION */
} OsEE_TCB;

/**
 *  The Task Descriptor Block. It stores all the information related to the 
 *  task that is configured statically, such as: priority, task type, task body
 *  pointer, maximum number of activations, core id, ...
 */
typedef struct OsEE_TDB_tag
{
  /** Hardware dependednt structure for the task (not a pointer!) */
  VAR(OsEE_HDB, TYPEDEF)                  hdb;
  /** pointer to the task control block, containing the RAM information 
   *  about a task */
  P2VAR(OsEE_TCB, TYPEDEF, OS_APPL_DATA)  p_tcb;
  /** Task ID. it is a number, allocated one per task by RT-Druid */
  VAR(TaskType, TYPEDEF)                  tid;
  /** Task Execution type (basic, extended, isr2, ...) */
  VAR(TaskExecutionType, TYPEDEF)         task_type;
  /** Task body function */
  VAR(TaskFunc, TYPEDEF)                  task_func;
  /** Task ready priority (which is a priority specified based on the
   *  PRIORITY OIL field) */
  VAR(TaskPrio, TYPEDEF)                  ready_prio;
  /** Task dispatch priority (which is computed based on the fact the task 
   *  is non preemptive and based to the internal resources used */
  VAR(TaskPrio, TYPEDEF)                  dispatch_prio;
  /** Maximum number of activations, as specified in the OIL file. */
  VAR(TaskActivation, TYPEDEF)            max_num_of_act;
#if (!defined(OSEE_SINGLECORE))
  /** Core ID in which a task is allocated. If the scheduler has
   *  migration, then the core_id in the TCB will change. */
  VAR(CoreIdType, TYPEDEF)                orig_core_id;
#endif /* !OSEE_SINGLECORE */
} OSEE_CONST OsEE_TDB;

/**
 *  This is the generic definition of a task wrapper. A Task wrapper is useful
 *  every time some actions have to be performed before we need to execute the
 *  task. For example, it is useful on some architecture's system timer to 
 *  perform actions on the peripheral registers before calling the ISR2 
 *  (remember that ISR2 and Tasks in ERIKA3 are handled in a similar way)
 */
typedef struct {
  /** a pointer to the task descriptor block to which the wrapper relates to */
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_DATA)  p_tdb;
  /** the real task body function that will be executed by the wrapper. */
  VAR(TaskFunc, TYPEDEF)                  real_task_func;
} OSEE_CONST OsEE_TW;

#if (defined(OSEE_HAS_COUNTERS))
#if (defined(OSEE_HAS_ALARMS)) && (defined(OSEE_HAS_SCHEDULE_TABLES))
/**
 *  If the application contains both Alarms and Schedule Tables, then the 
 *  Trigger queue OsEE_TriggerQ will distinguis among the two types of objects.
 *  If there is only one kind of object, then we use an optimized 
 *  implementation.
 */
#define OSEE_COUNTER_TRIGGER_TYPES
#endif /* OSEE_HAS_ALARMS && OSEE_HAS_SCHEDULE_TABLES */

/* Forward declaration of TriggerDB, needed for CounterCB
 * p_first_trigger and for TriggerCB p_next fields. */
struct OsEE_TriggerDB_tag;

/**
 *  This is the type used for the trigger queue.
 *  
 *  The trigger queue represents a queue of expiry points which could come
 *  either from Alarms or from Schedule Tables. If both (Alarms and Schedule
 *  Tables) are present inside an application, then the trigger queue has two
 *  pointers, one to the Alarm data, one to the Schedule Table data, and only
 *  one of them will be set, implicitly stating the type of object. If only 
 *  one kind of object is present in the Application, then we avoid the 
 *  indirection and the specific item data is put inside the OsEE_TriggerCB and 
 *  inside the OsEE_TriggerDB.
 *  
 *  Also note that the Trigger Queue is a Linked List, but in theory we could
 *  implement any priority queue data structure (Heap for example)
 */
typedef P2VAR(struct OsEE_TriggerDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA)
  OsEE_TriggerQ;

/** Counter Control Block. It stores the reference trigger queue, the counter 
  * value and the prescaler (if configured) */
typedef struct {
  /** the trigger list attached to this counter */ 
  VAR(OsEE_TriggerQ, TYPEDEF) trigger_queue;
  /** the value of the counter */
  VAR(TickType, TYPEDEF)      value;
#if (defined(OSEE_HAS_COUNTER_PRESCALER))
  /** the prescaler of the counter, if configured */
  VAR(TickType, TYPEDEF)      prescaler;
#endif /* OSEE_HAS_COUNTER_PRESCALER */
} OsEE_CounterCB;

#if (defined(OSEE_HAS_COUNTER_HARD))
/** Hardware Counter Descriptor Block. This data structure was defined for 
 *  future usage and has not been used yet in ERIKA3. */
typedef struct OsEE_CounterHardDB {
  /** To be refined in the next versions of ERIKA3 */
  VAR(OsEE_CounterDB, TYPEDEF)  super;
  /** To be refined in the next versions of ERIKA3 */
  VAR(TickType, TYPEDEF)        microsecondspertick;
} OSEE_CONST OsEE_CounterHardDB;
#endif /* OSEE_HAS_COUNTER_HARD */

/** Counter descriptor block. It stores all the data required to configure
 *  a counter: the counter information (software or hardware), alarm time base,
 *  core
 */
typedef struct {
  /** pointer to the counter descriptor block in RAM */
  P2VAR(OsEE_CounterCB, TYPEDEF, OS_APPL_DATA)      p_counter_cb;
#if (defined(OSEE_HAS_COUNTER_HARD))
  /** pointer to the hardware counter descriptor block */
  P2VAR(OsEE_CounterHardDB, TYPEDEF, OS_APPL_CONST) p_counter_hard;
#endif /* OSEE_HAS_COUNTER_HARD */
  /** AlarmBase of the counter */
  VAR(AlarmBaseType, TYPEDEF)                       info;
#if (!defined(OSEE_SINGLECORE))
  /** core where the counter is allocated */
  VAR(CoreIdType, TYPEDEF)                          core_id;
#endif /* OSEE_SINGLECORE */
} OSEE_CONST OsEE_CounterDB;

/** Possible types of notifications for Alarms and Schedule Tables */
typedef enum {
  OSEE_ACTION_TASK,
  OSEE_ACTION_EVENT,
  OSEE_ACTION_COUNTER,
  OSEE_ACTION_CALLBACK
} OsEE_action_type;

/** Parameters of an Alarm/Schedule Table expiration (function callback, 
 *  task, event mask, and counter)
 */
typedef struct {
  /** alarm callback to be called */
  VAR(OsEE_kernel_cb, TYPEDEF)                  f;
  /** task to be activated (or task whose event mask has to be set) */
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_DATA)        p_tdb;
  /** counter to be incremented */
  P2VAR(OsEE_CounterDB, TYPEDEF, OS_APPL_DATA)  p_counter_db;
#if (defined(OSEE_HAS_EVENTS))
  /** event mask to be set on the task */
  VAR(EventMaskType, TYPEDEF)                   mask;
#endif /* OSEE_HAS_EVENTS */
} OsEE_action_param;

/** Notification data structure for Alarms and Schedule Tables. It includes the
 *  Type and its parameters */
typedef struct {
  /** contains the data to be passed to the specific notification type */
  VAR(OsEE_action_param, TYPEDEF)               param;
  /** type of notification */
  VAR(OsEE_action_type, TYPEDEF)                type;
} OSEE_CONST OsEE_action;

#if (defined(OSEE_HAS_SCHEDULE_TABLES))
/** Schedule Table Synchronization strategies symbols */
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

/** to have a more harmonized type name with other OSEK type names. */
typedef OsEE_st_synch_strategy SynchStrategyType;

/** Structures that hold the information related to an expiry point */
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
/** Alarm Control Block. It stores the RAM information about the alarm.
 *  This data structure is present only if both Alarms and Schedule Tables 
 *  are present in the application. Otherwise, the content of this data 
 *  structure is integrated inside the trigger.
 */
typedef struct OsEE_AlarmCB_tag {
  /** the alarm periodic reactivation */
  VAR(TickType, TYPEDEF)                      cycle;
} OsEE_AlarmCB;

/**
 *  Alarm descriptor block. It stores the Flash information about an alarm.
 *  This data structure is present only if both Alarms and Schedule Tables 
 *  are present in the application. Otherwise, the content of this data 
 *  structure is integrated inside the trigger.
 */
typedef struct OsEE_AlarmDB_tag {
  /** pointer to the alarm control block */
  P2VAR(OsEE_AlarmCB, TYPEDEF, OS_APPL_DATA)  p_alarm_cb;
  /** pointer to the trigger descriptor */
  P2VAR(struct OsEE_TriggerDB_tag OSEE_CONST, TYPEDEF, OS_APPL_CONST)
                                              p_trigger_db;
  /** notification action to be implemented once the alarm fires */
  VAR(OsEE_action, TYPEDEF)                   action;
} OSEE_CONST OsEE_AlarmDB;

/**
 * Data structure to store RAM informations needed by schedule tables.
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
 *  \brief This is the trigger status enumerate.
 *
 *  The trigger statuses have been made to consistently handle race conditions 
 *  on the update of Alarms and Schedule Tables.
 *
 *  In particular, in the multicore case we have a potential race condition 
 *  due to the following:
 *  - the handling of the trigger data structure is done in mutual exclusion
 *    using a spin lock.
 *  - the spinlock is released during the handling of the notifications. 
 *    This is done because the time spent in handling notifications may be long
 *    (e.g., a Schedule Table  activating a number of tasks at an expiry point.
 *  - when a core is handling the notifications at an expiry point related to an
 *    Alarm (Schedule Table), with the spin lock unlocked, a CancelAlarm() 
 *    (StopScheduleTable()) could be issued by another core on the same Alarm 
 *    (Schedule Table). Once canceled (stopped), the Alarm (Schedule Table) 
 *    could be restarted again.
 *
 *  Therefore, the status transitions of a trigger will be the following:
 *  - OSEE_TRIGGER_INACTIVE: Initial status, trigger inactive
 *  - OSEE_TRIGGER_ACTIVE: Alarm or Schedule Table started
 *  - OSEE_TRIGGER_EXPIRED: The trigger fired. The status is changed to expired 
 *    before leaving the critical section.
 *  - OSEE_TRIGGER_CANCELED: The status is set to canceled if while the trigger
 *    is expired and the spin lock released a CancelAlarm() or
 *    StopScheduleTable() arrives from another core. At the end of the 
 *    notification handling the status will be set back to OSEE_TRIGGER_INACTIVE
 *  - OSEE_TRIGGER_REENABLED: The status is set to reenabled if a canceled Alarm
 *    or ScheduleTable is reenabled while a core is still handling the actions.
 *    At the end of the notification handling the status will be set to
 *    OSEE_TRIGGER_ACTIVE with the new start time.
 */
typedef enum {
  OSEE_TRIGGER_INACTIVE,
  OSEE_TRIGGER_CANCELED,
  OSEE_TRIGGER_ACTIVE,
  OSEE_TRIGGER_EXPIRED,
  OSEE_TRIGGER_REENABLED
} OsEE_trigger_status;

/**
 *  The Trigger Countrol Block is the element in the trigger queue that records
 *  when the next trigger is going to expire, and what is its status 
 *  (see OsEE_trigger_status).
 *  
 *  The Trigger Control Block contains:
 *  - the content of the Alarm Control Block if only Alarms are present in the
 *    current application.
 *  - the content of the Schedule Table Control block if only Schedule Tables
 *    are present in the current application.
 *  
 *  If both Alarms and Schedule Tables are present, the information above are 
 *  linked through the Trigger Descriptor Block to the Alarm/Schedule Table 
 *  Descriptor Block to the Alarm/Schedule Table control block.
 */
typedef struct {
  /** a pointer to the next trigger, to make a list */
  P2VAR(struct OsEE_TriggerDB_tag OSEE_CONST, TYPEDEF, OS_APPL_DATA)  p_next;
  /** the next expiry point of the trigger (this is the absolute
   *  counter value, not a delta) */
  VAR(TickType, TYPEDEF)                                              when;
  /** status of the trigger */
  VAR(OsEE_trigger_status, TYPEDEF)                                   status;
#if (!defined(OSEE_COUNTER_TRIGGER_TYPES))
#if (defined(OSEE_HAS_ALARMS))
  /** If the application only has alarms, this is the alarm cycle */
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

/**
 *  Trigger Descriptor Block is the elemnt containing the information of Alarms
 *  and Schedule Tables. If both Alarms and Schedule Tables are present in the
 *  Application, the struct has two pointers to the Alarm and to the Schedule
 *  Table Descriptor blocks. Only one of them is different from NULL (this is
 *  implicitly the type of the trigger). If only Alarms or only Schedule Tables
 *  are present, the struct contains the fields of the descriptor block, saving
 *  one indirection.
 */
typedef struct OsEE_TriggerDB_tag {
  /** pointer to the trigger descriptor block */
  P2VAR(OsEE_TriggerCB, TYPEDEF, OS_APPL_DATA)              p_trigger_cb;
  /** pointer to the counter descriptor block (in ram) */
  P2VAR(OsEE_CounterDB, TYPEDEF, OS_APPL_DATA)              p_counter_db;
#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
  /** pointer to the alarm descriptor block. present if both alarms and schedule
   *  table are there. !=0 if the trigger is related to an alarm. */
  P2VAR(struct OsEE_AlarmDB_tag OSEE_CONST, TYPEDEF, OS_APPL_CONST)
                                                            p_alarm_db;
  /** pointer to the schedule table descriptor block. present if both alarms 
   *  and schedule tables are there. !=0 if the trigger is related to a 
   *  schedule table. */
  P2VAR(struct OsEE_SchedTabDB_tag OSEE_CONST, TYPEDEF, OS_APPL_CONST)
                                                            p_st_db;
#elif (defined(OSEE_HAS_ALARMS))
  /** if the application only has alarms, this is the notification action 
   *  of the alarm */
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
/** This trigger type is related to the autostart feature */
typedef enum osEE_autostart_trigger_info_type_tag {
  OSEE_AUTOSTART_ALARM,
  OSEE_AUTOSTART_SCHEDULE_TABLE_ABS,
  OSEE_AUTOSTART_SCHEDULE_TABLE_REL,
  OSEE_AUTOSTART_SCHEDULE_TABLE_SYNCHRON /**< External synchronization */
} osEE_autostart_trigger_info_type;
#endif /* OSEE_HAS_SCHEDULE_TABLES */

/** These are the parameters needed to activate the autostart of an Alarm or of
 *  a Schedule Table. */
typedef struct {
  /** pointer to the trigger descriptor block of the alarm/schedule
   *  table (both autostart are handled with the same data
   *  structure) */
  P2VAR(OsEE_TriggerDB, TYPEDEF, OS_APPL_CONST)   p_trigger_db;
  /** autostart: parameter of the schedule table, or initial offset in case it is an alarm */
  VAR(TickType, TYPEDEF)                          first_tick_parameter;
#if (defined(OSEE_HAS_ALARMS))
  /** autostart: cycle parameter for alarms */
  VAR(TickType, TYPEDEF)                          second_tick_parameter;
#endif /* OSEE_HAS_ALARMS */
#if (defined(OSEE_HAS_SCHEDULE_TABLES))
  /** type of autostart (alarm, schedule table abs, ... ) */	
  VAR(osEE_autostart_trigger_info_type, TYPEDEF)  autostart_type;
#endif /* OSEE_HAS_SCHEDULE_TABLES */
} OSEE_CONST OsEE_autostart_trigger_info;

/** This struct contains an array storing pointers to autostart triggers */
typedef struct {
  /** pointer to the array storing the autostart triggers */
  P2SYM_VAR(OsEE_autostart_trigger_info, OS_APPL_CONST, p_trigger_ptr_array)[];
  /** size of the array storing the autostart triggers */
  VAR(MemSize, TYPEDEF)                                 trigger_array_size;
} OSEE_CONST OsEE_autostart_trigger;
#endif /* OSEE_HAS_AUTOSTART_TRIGGER */
#endif /* OSEE_HAS_COUNTERS */

#if (defined(OSEE_HAS_AUTOSTART_TASK))
/** This structure contains all the information for implementing the autostart
 *  of a task */
typedef struct OsEE_autostart_tdb_tag {
  /** pointer to the array of TDBs to be autostarted */
  P2SYM_CONSTP2VAR(OsEE_TDB, OS_APPL_CONST, p_tdb_ptr_array)[];
  /** size of the array of TDBs to be autostarted */
  VAR(MemSize, TYPEDEF)                     tdb_array_size;
} OSEE_CONST OsEE_autostart_tdb;
#endif /* !OSEE_HAS_AUTOSTART_TASK */

/**
 *  This is the Core Control Block. The struct stores all the information
 *  related to the handling of a core in RAM, such as:
 *  - core running priority
 *  - ready queue
 *  - stacks
 *  - application mode
 *  - interrupt nesting
 *  - ORTI core informations
 */
typedef struct {
  /** current running task or ISR2 on the specific core. note that this is a 
   *  shortcut for the task pointed by the first sn of the p_stk_sn */
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_CONST)         p_curr;
#if (!defined(OSEE_SINGLECORE)) && (defined(OSEE_SCHEDULER_GLOBAL))
  /**
   *  p_lock_to_be released is related to multicore configurations with global 
   *  scheduling. The reason is as follows:
   *  - in multicore configurations, there is a spin-lock protecting the kernel
   *    data structures from concurrent access and modifications by other cores.
   *  - if there is no migration, the lock needs to be taken just up to the end
   *    of the modifications of the data structure.
   *  - if there is migration, the lock needs to be taken a bit more, until the
   *    context of the running task has been correctly saved. This because once
   *    we release the lock, another core could arrive to migrate and schedule
   *    the task we just saved.
   */
  P2VAR(OsEE_spin_lock, TYPEDEF, OS_APPL_DATA)    p_lock_to_be_released;
#endif /* !OSEE_SINGLECORE && OSEE_SCHEDULER_GLOBAL */
#if (!defined(OSEE_SCHEDULER_GLOBAL))
  /** core ready queue (valid only with partitioned scheduling) */
  VAR(OsEE_RQ, TYPEDEF)                           rq;
  /** scheduler node free list. Popped when activating a task */
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA)           p_free_sn;
#if (defined(OSEE_API_DYNAMIC))
  /** Total number of pending activations remaining on the core.
   *  Needed on dynamic API because the task activations are reserved 
   *  dynamically, but the free list is allocated statically.
   */
  VAR(MemSize, TYPEDEF)                           free_sn_counter;
#endif /* OSEE_API_DYNAMIC */
#endif /* !OSEE_SCHEDULER_GLOBAL */
  /** Stack of scheduler nodes.
   *  The idea is that when the scheduler implements a preemption, it keeps
   *  the preempted task in a stack, that therefore contains the list of tasks
   *  which are ready and on the stack.
   *  Note that ISR2 are also inserted in this stack.
   */
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA)           p_stk_sn;
  /** kernel status */
  VAR(OsEE_kernel_status volatile, TYPEDEF)       os_status;
  /** application mode for the core. it is local to the core because in 
   *  multicore systems you can initialize the system with different parameters
   *  on the StartOS(). */
  VAR(AppModeType, TYPEDEF)                       app_mode;
  /** Last error raised by a primitive */
  VAR(StatusType, TYPEDEF)                        last_error;
#if (defined(OSEE_USEGETSERVICEID)) || (defined(OSEE_USEPARAMETERACCESS)) ||\
    (defined(OSEE_HAS_ORTI))
  /** Last kernel primitive executed on the core */
  VAR(OSServiceIdType, TYPEDEF)                   service_id;
#endif /* OSEE_USEGETSERVICEID || OSEE_USEPARAMETERACCESS || OSEE_HAS_ORTI */
#if (defined(OSEE_USEPARAMETERACCESS))
  /** ErrorHook macros - first parameter */
  VAR(OsEE_api_param, TYPEDEF)                    api_param1;
  /** ErrorHook macros - second parameter */
  VAR(OsEE_api_param, TYPEDEF)                    api_param2;
  /** ErrorHook macros - third parameter */
  VAR(OsEE_api_param, TYPEDEF)                    api_param3;
#endif /* OSEE_USEPARAMETERACCESS */
#if (defined(OSEE_HAS_CONTEXT))
  /** The running "item" (task, isr2, hook, ...) context. Nededed to
   *  discriminate what subset of primitives are legal to be executed at a 
   *  given time. The list of permission is noted in the table in section 
   *  \ref api-primitives . This feature is part of the service protection */
  VAR(OsEE_os_context, TYPEDEF)                   os_context;
#endif /* OSEE_HAS_CONTEXT */
#if (defined(OSEE_HAS_PRETASKHOOK))
  /** Needed to distinguish that PreTaskHook HAVE NOT to be called after an
   * ISR2 that terminates without a TASK rescheduling */
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_CONST)         p_last_tdb_hook;
#endif /* OSEE_HAS_PRETASKHOOK */
#if (defined(OSEE_HAS_SPINLOCKS))
  /** last spinlock acquired. needed to avoid the acquisition of spin locks
   *  which are not a successor in the spinlock list [SWS_Os_00661] */
  P2VAR(OsEE_SpinlockDB, TYPEDEF, OS_APPL_CONST)  p_last_spinlock;
#endif /* OSEE_HAS_SPINLOCKS */
  /** Interrupt status saved by SuspendAllInterrupts() */
  VAR(OsEE_reg,  TYPEDEF)                         prev_s_isr_all_status;
  /** Interrupt status saved by SuspendOSInterrupts() */
  VAR(OsEE_reg,  TYPEDEF)                         prev_s_isr_os_status;
  /** Counter of nested SuspendAllInterrupts() */
  VAR(OsEE_byte, TYPEDEF)                         s_isr_all_cnt;
  /** Counter of nested SuspendOSInterrupts() */
  VAR(OsEE_byte, TYPEDEF)                         s_isr_os_cnt;
  /** This flag marks whether, at the end of a task, a DisableAllInterrupts()
   *  was called without a matching call to EnableAllInterrupts() */
  VAR(OsEE_byte, TYPEDEF)                         d_isr_all_cnt; 
#if (defined(OSEE_HAS_ORTI))
  /** The ORTI service ID marks the beginning (enter) and the end (exit) 
   *  of primitives. This is a flag needed to avoid setting the exit of a 
   *  primitive which caused a rescheduling. This avoid, for example, that an
   *  Activatetask/schedule/waitevent/releaseresource/... implementing a 
   *  preemption sets the last primitive to Activatetask at its exit 
   *  if there was a rescheduling */
  VAR(OsEE_bool, TYPEDEF)                         orti_service_id_valid;
#endif /* OSEE_HAS_ORTI */
} OsEE_CCB;

/**
 *  This is the Core Descriptor Block. The struct stores all the information
 *  related to the handling of a core in Flash, such as:
 *  - core id
 *  - pointer to the core control block
 *  - autostart information
 *  - idle hooks
 */
typedef struct {
#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
  /** pointer to the Core HAL Descriptor block (stores info about stacks/...) */
  VAR(OsEE_CHDB, TYPEDEF)                         chdb;
#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */
  /** pointer to the CCB (holds the RAM part of the information of the core) */
  P2VAR(OsEE_CCB, TYPEDEF, OS_APPL_DATA)          p_ccb;
#if (!defined(OSEE_SINGLECORE))
  /** global lock for this core */
  P2VAR(OsEE_spin_lock, TYPEDEF,OS_APPL_DATA)     p_lock;
#endif /* !OSEE_SINGLECORE */
#if (defined(OSEE_HAS_IDLEHOOK)) || (defined(OSEE_API_DYNAMIC))
  /** Idle hook function */
  VAR(TaskFunc, TYPEDEF)                          p_idle_hook;
#endif /* OSEE_HAS_IDLEHOOK || OSEE_API_DYNAMIC */
  /** Idle task TDB */
  P2VAR(OsEE_TDB, TYPEDEF, OS_APPL_CONST)         p_idle_task;
#if (defined(OSEE_HAS_SYSTEM_TIMER))
  /** pointer to the system counter DB. Useful here to avoid calling
   *  IncrementCounter() on the system timer */
  P2VAR(OsEE_CounterDB, TYPEDEF, OS_APPL_CONST)   p_sys_counter_db;
#endif /* OSEE_HAS_SYSTEM_TIMER */
#if (defined(OSEE_HAS_AUTOSTART_TASK))
  /** array of TDB ptrs, stores the tasks subject to autostart on the core */
  P2SYM_VAR(OsEE_autostart_tdb, OS_APPL_CONST,    p_autostart_tdb_array)[];
  /** size of the array p_autostart_tdb_array */
  VAR(MemSize, TYPEDEF)                           autostart_tdb_array_size;
#endif /* OSEE_HAS_AUTOSTART_TASK */
#if (defined(OSEE_HAS_AUTOSTART_TRIGGER))
  /** array of pointers to triggers, stores the triggers subject to autostart */
  P2SYM_VAR(OsEE_autostart_trigger, OS_APPL_CONST, p_autostart_trigger_array)[];
  /** size of the array p_autostart_trigger_array */
  VAR(MemSize, TYPEDEF)                           autostart_trigger_array_size;
#endif /* OSEE_HAS_AUTOSTART_TRIGGER */
#if (!defined(OSEE_SINGLECORE))
  /** ID of the core */
  VAR(CoreIdType, TYPEDEF)                        core_id;
#endif /* !OSEE_SINGLECORE */
} OSEE_CONST OsEE_CDB;

/**
 *  This is the Kernel Control Block. This is the main global data structure, 
 *  which contains overall RAM information for the kernel */
typedef struct {
#if (defined(OSEE_SCHEDULER_GLOBAL))
  /** global ready queue, in case of task migration/global scheduling */
  VAR(OsEE_RQ, TYPEDEF)                   rq;
  /** scheduler node free list. Popped when activating a task */
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA)   p_free_sn;
#if (defined(OSEE_API_DYNAMIC))
  /** Total number of pending activations remaining on the core.
   *  Needed on dynamic API because the task activations are reserved 
   *  dynamically, but the free list is allocated statically.
   */
  VAR(MemSize, TYPEDEF)                   free_sn_counter;
#endif /* OSEE_API_DYNAMIC */
#endif /* OSEE_SCHEDULER_GLOBAL */
#if (defined(OSEE_API_DYNAMIC))
  /** First free ID of the array containing the free pool of
   *  tasks. Note that this index will become a TaskType once a slot
   *  is allocated */
  VAR(MemSize, TYPEDEF)                   free_task_index;
#endif /* OSEE_API_DYNAMIC */
#if (defined(OSEE_HAS_RESOURCES)) && (defined(OSEE_API_DYNAMIC))
  /** First free ID of the array containing the free pool of
   *  resources. Note that this index will become a ResourceType once
   *  a slot is allocated */
  VAR(MemSize, TYPEDEF)                   free_res_index;
#endif /* OSEE_HAS_RESOURCES && OSEE_API_DYNAMIC */
#if (defined(OSEE_HAS_COUNTERS)) && (defined(OSEE_API_DYNAMIC))
  /** First free ID of the array containing the free pool of
   *  counters. Note that this index will become a CounterType once a
   *  slot is allocated */
  VAR(MemSize, TYPEDEF)                   free_counter_index;
#if (defined(OSEE_HAS_ALARMS))
  /** First free ID of the array containing the free pool of
   *  alarms. Note that this index will become an AlarmType once a
   *  slot is allocated */
  VAR(MemSize, TYPEDEF)                   free_alarm_index;
#endif /* OSEE_HAS_ALARMS */
#if (defined(OSEE_HAS_SCHEDULE_TABLES))
  /** First free ID of the array containing the free pool of schedule
   *  tables. Note that this index will become an ScheduleTableType
   *  once a slot is allocated */
  VAR(MemSize, TYPEDEF)                   free_st_index;
#endif /* OSEE_HAS_SCHEDULE_TABLES */
#endif /* OSEE_HAS_COUNTERS && OSEE_API_DYNAMIC */
#if (!defined(OSEE_SINGLECORE))
  /** This is the mask of the cores started with StartCore() and which
   *  will be handled by ERIKA3 */
  VAR(CoreMaskType, TYPEDEF)              ar_core_mask;
  /** This is the mask of the cores started with StartNonAutosarCore()
      which are not under the control of ERIKA3. */
  VAR(CoreMaskType, TYPEDEF)              not_ar_core_mask;
  /** This is the mask to coordinate the distributed shutdown
      initiated with ShutdownAllCores() */
  VAR(CoreMaskType, TYPEDEF)              ar_shutdown_mask;
  /** This is the number of cores that have been started (both AUTOSAR
      and non AUTOSAR) */
  VAR(CoreNumType,  TYPEDEF)              ar_num_core_started;
  /** This is the error parameter value passed to ShutdownAllCores
   *  that must be know to all cores shutting down. */
  VAR(StatusType, TYPEDEF)                ar_shutdown_all_cores_error;
  /** This is a flag that says if the Shutdown procedure has been
   *  initiated. Checked inside the intercore interrupt. */
  VAR(OsEE_bool, TYPEDEF)                 ar_shutdown_all_cores_flag;
#endif /* !OSEE_SINGLECORE */
#if (defined(OSEE_SINGLECORE)) && (!defined(OSEE_API_DYNAMIC))
  /* To not have an empty struct */
  VAR(OsEE_reg, TYPEDEF)                  dummy;
#endif /* OSEE_SINGLECORE && !OSEE_API_DYNAMIC */
} OsEE_KCB;

/**
 *  This is the Kernel descriptor Block. This data structure is the "starting
 *  point" for navigating all the kernel data structures. It contains static
 *  flash information about all the global objects included in the system,
 *  such as:
 *  - cores
 *  - tasks
 *  - resources
 *  - counters
 *  - alarms
 *  - scheduling tables
 *  - spin locks
 *  - barriers
 */
typedef struct {
  /** pointer to the Kernel Control Block (storing RAM information) */
  P2VAR(OsEE_KCB, TYPEDEF, OS_APPL_DATA)            p_kcb;
#if (!defined(OSEE_SINGLECORE))
  /** This is the global kernel lock */
  P2VAR(OsEE_spin_lock, TYPEDEF,OS_APPL_DATA)       p_lock;
  /** This is the global kernel barrier used in startup and
   *  shutdown. It must be a rearming barrier */
  P2VAR(OsEE_barrier, TYPEDEF,OS_APPL_DATA)         p_barrier;
#endif /* !OSEE_SINGLECORE */
  /* EG: No AUTOSAR Compiler Abstraction For Pointer To Array !!!
         ==> I need to invent one */
  /** this is the global list of tasks, including the idle task
   *  (one per core), and all ISR2 */ 
  P2SYM_CONSTP2VAR(OsEE_TDB, OS_APPL_CONST,         p_tdb_ptr_array)
    [/*OSEE_TASK_ARRAY_SIZE + OsNumberOfCores*/];
  /** size of the array pointed by p_tdb_ptr_array */
  VAR(MemSize, TYPEDEF)                             tdb_array_size;
#if (defined(OSEE_ALLOW_TASK_MIGRATION))
  /** array of the schedule nodes */
  P2SYM_VAR(OsEE_SN, OS_APPL_DATA,                  p_sn_array)
    [/*OSEE_SN_ARRAY_SIZE*/];
  /** size of the array pointed by p_sn_array */
  VAR(MemSize, TYPEDEF)                             sn_array_size;
#endif /* OSEE_ALLOW_TASK_MIGRATION */
#if (defined(OSEE_ALLOW_TASK_MIGRATION))
#endif /* OSEE_ALLOW_TASK_MIGRATION */
#if (defined(OSEE_HAS_RESOURCES))
  /** array of the resources */
  P2SYM_CONSTP2VAR(OsEE_ResourceDB, OS_APPL_CONST,  p_res_ptr_array)[];
  /** size of the array pointed by p_res_ptr_array */
  VAR(MemSize, TYPEDEF)                             res_array_size;
#endif /* OSEE_HAS_RESOURCES */
#if (defined(OSEE_HAS_COUNTERS))
  /** array of counters */
  P2SYM_CONSTP2VAR(OsEE_CounterDB, OS_APPL_CONST,   p_counter_ptr_array)[];
  /** size of the array pointed by p_counter_ptr_array */
  VAR(MemSize, TYPEDEF)                             counter_array_size;
#if (defined(OSEE_HAS_ALARMS))
  /** array of alarms */
  P2SYM_CONSTP2VAR(OsEE_AlarmDB, OS_APPL_CONST,     p_alarm_ptr_array)[];
  /** size of the array pointed by p_alarm_ptr_array */
  VAR(MemSize, TYPEDEF)                             alarm_array_size;
#endif /* OSEE_HAS_ALARMS */
#if (defined(OSEE_HAS_SCHEDULE_TABLES))
  /** array of schedule tables */
  P2SYM_CONSTP2VAR(OsEE_SchedTabDB, OS_APPL_CONST,  p_st_ptr_array)[];
  /** size of the array pointed by p_st_ptr_array */
  VAR(MemSize, TYPEDEF)                             st_array_size;
#endif /* OSEE_HAS_SCHEDULE_TABLES */
#endif /* OSEE_HAS_COUNTERS */
#if (defined(OSEE_HAS_SPINLOCKS))
  /** array of spinlocks */
  P2SYM_VAR(OsEE_SpinlockDB, OS_APPL_CONST,         p_spinlock_array)[];
  /** size of the array pointed by p_spinlock_array */
  VAR(MemSize, TYPEDEF)                             spinlock_array_size;
#endif /* OSEE_HAS_SPINLOCKS */
} OSEE_CONST OsEE_KDB;

#if (defined(OSEE_API_EXTENSION))
/** Semaphore Data structure. A counter, a blocked queue, and a spinlock in 
  * case of multicores. */
typedef struct OsEE_sem_tag {
#if (!defined(OSEE_SINGLECORE))
  /** the semaphore has a spinlock to be used in case of multicore systems */
  VAR(OsEE_spin_lock, TYPEDEF)          lock;
#endif /* !OSEE_SINGLECORE */
  /** This is the semaphore blocked queue */
  P2VAR(OsEE_SN, TYPEDEF, OS_APPL_DATA) blocked_queue;
  /** This is the semaphore counter */
  VAR(CountType, TYPEDEF)               count;
} OsEE_sem;

/** A semaphore dtaa structure with a OSEK/VDX naming convention flavour */
typedef struct OsEE_sem_tag SemType;

#endif /* OSEE_API_EXTENSION */

#if (!defined(OSEE_ISR2_INLINE))
/**
 *  \brief Handles the ISR2 termination.
 *  
 *  This function handles the context change at ISR2 termination.
 *  
 *  This is an internal function of the ERIKA3 Hardware Abstraction Layer,
 *  called by the Kernel, provided by each porting in an architecture dependent
 *  way. The typical implementation acknowledges the interrupt controller and 
 *  then calls afterwards the osEE_change_context_from_task_end.
 *  
 *  Note: this include file is not the "best" place to place this function.
 *  ... but is a good point because it is visible to teh HAL implementation.
 *  Likely this  declaration will move soon or later to another
 *  include file.
 *  
 *  \param [in] p_from Current ISR2 in execution
 *  \param [in] p_to   New task to execute
 */
extern FUNC(void, OS_CODE)
  osEE_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
);
#endif /* !OSEE_ISR2_INLINE */

/**
 *  \brief Handles the Task termination.
 *  
 *  This function handles the context change at Task termination.
 *  
 *  This is an internal function of the ERIKA3 Hardware Abstraction Layer,
 *  called by the Kernel, provided by each porting in an architecture dependent
 *  way.
 *  
 *  Note: this include file is not the "best" place to place this function.
 *  ... but is a good point because it is visible to teh HAL implementation.
 *  Likely this  declaration will move soon or later to another
 *  include file.
 *  
 *  \param [in] p_from Current ISR2 in execution
 *  \param [in] p_to   New task to execute
 */
extern FUNC(void, OS_CODE)
  osEE_change_context_from_task_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
);

/**
 *  \brief Task Body of the Idle Task.
 *  
 *  This is the Task Body of the Idle task.
 */
extern FUNC(void, OS_CODE)
  osEE_idle_hook_wrapper
(
  void
);

 /**
 *  \brief Terminate callback definition.
 *  
 *  This is the definition of the callback used to terminate a single task 
 *  activation at the end of the task (typically is the TerminateTask() 
 *  or ChainTask() primitive).
 *  
 *  After the termination of the current activation, the task will go either 
 *  in SUSPENDED state (if it has no more pending activations, or READY in 
 *  case it has pending activations.
 *  
 *  The function is mainly responsible for the stack unwinding at the end of
 *  the task (if needed), and after that the call to the scheduler.
 *  
 *  ''CB'' stands for Callback.
 *  
 *  Note: this include file is not the "best" place to place this function.
 *  ... but is a good point because it is visible to teh HAL implementation.
 *  Likely this declaration will move soon or later to another
 *  include file.
 */
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
