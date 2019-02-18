
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

/** \file   ee_api_types.h
 *  \brief  OSEK Kernel API Types.
 *
 *  This files contains all types and symbols needed by OSEK Kernel APIs
 *  in Erika Enterprise.
 * 
 *  About Type redefinition
 *  =======================
 *   
 *  ERIKA3 supports the same type naming as specified in the AUTOSAR OS.
 *
 * Each type is defined with a default size, that sometimes depends on the 
 * microcontroller word.
 *
 * Moreover, it is possible to redefine the type size by using appropriate
 * defines, like in the example below:
 *
 *     #if (!defined(OSEE_APPMODE_TYPE))
 *     #define OSEE_APPMODE_TYPE                       VAR(uint8_t, TYPEDEF)
 *     #endif
 *     typedef OSEE_APPMODE_TYPE                       AppModeType;
 *
 * In this example, the default type for AppModeType is uint8_t. It can be 
 * redefined by defining OSEE_APPMODE_TYPE prior the inclusion of
 * ee_api_types.h .
 *
 * This allows flexibility in the definition of the size of the various data
 * types.
 *
 *  \author Errico Guidieri
 *  \date   2016
 */

#ifndef OSEE_API_TYPES_H
#define OSEE_API_TYPES_H

#include "ee_platform_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#if (!defined(OSEE_APPMODE_TYPE))
/** \brief Internal type used for Application Modes.
 *  This is the internal type used for Application Modes.
 */
#define OSEE_APPMODE_TYPE                       VAR(uint8_t, TYPEDEF)
#endif /* !OSEE_APPMODE_TYPE */

/** \brief Type used for application modes.
 *  \ingroup primitives-startup
 *  This is the type that stores Application modes. It is an integer value.
 */
typedef OSEE_APPMODE_TYPE                       AppModeType;

/** \brief Value for invalid application modes.
 *  \ingroup primitives-startup
 *  Value for invalid application modes. No application mode will have this 
 *  value.
 */
#define INVALID_APPMODE                         ((AppModeType)-1)

#if (!defined(OSEE_TASK_ID_TYPE))
/** \brief Internal type used for Task IDs.
 *  This is the internal type used for Task IDs.
 */
#define OSEE_TASK_ID_TYPE                       VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_TASK_ID_TYPE */

 /**
 *  \brief Type used for Task IDs.
 *  \ingroup primitives-task
 *  Type used for Task IDs. Typically the size of a word on the microcontroller. 
 *  It is a positive number (except the invalid task 
 *  which is -1). The Task IDs are consistent and do not change in case of
 *  multicore configurations.
 */
typedef OSEE_TASK_ID_TYPE                       TaskType;

 /**
 *  \brief Type used for interrupts type 2.
 *  \ingroup primitives-interrupt
 *  Type used for interrupts type 2. It is a positive number. The ISR2 IDs are
 *  in the same value space as Task IDs (this because ISR2 in ERIKA3 are 
 *  implemented in a way similar to tasks).
 */
typedef OSEE_TASK_ID_TYPE                       ISRType;

/** \brief This is a pointer to a TaskType.
 *  \ingroup primitives-task
 *  This type is a pointer to Task IDs, used as parameter of a primitive.
 */
typedef P2VAR(TaskType, TYPEDEF, OS_APPL_DATA)  TaskRefType;
/** \brief This is the invalid task value.
 *  \ingroup primitives-task
 *  This is the invalid task value. No task can have this task ID. GetTaskID()
 *  executed in the background task (or idle hook) always provides INVALID_TASK.
 */
#define INVALID_TASK                            ((TaskType)-1)
/** \brief This is the invalid ISR2 value.
 *  \ingroup primitives-interrupt
 *  This is the invalid ISR2 value. No real ISR can have this value.
 */
#define INVALID_ISR                             INVALID_TASK


#if (!defined(OSEE_TASK_PRIO_TYPE))
/**
 *  \brief Internal type storing task priorities.
 *  This is the internal type storing task priorities.
 */
#define OSEE_TASK_PRIO_TYPE                     VAR(uint8_t, TYPEDEF)
#endif /* !OSEE_TASK_PRIO_TYPE */

/**
 *  \brief Type storing task priorities.
 *  \ingroup primitives-task
 *
 *  This type is used to store the priority of both Tasks and ISR2s (please
 *  remember that ISR2 are treated like tasks inside ERIKA3).
 * 
 *  TaskPrio is an integer number (usually n bits=8).
 *  
 *  Higher values for higher priorities.
 *
 *  The same variable maps two types of priorities, in two different value 
 *  ranges:
 *  - The task priority
 *  - The ISR2 ''virtual'' priority.
 *  
 *  The ISR2 virtual priority maps the interrupt controller prioriries on top
 *  of the Task priorities. This is done by allocating the two kind of 
 *  priorities into two non-overlapping ranges.
 *
 *  Choosen the dimension 'n' in bit of the type,
 *  the priority space is partitioned in the following way:
 *  
 *  - 0 Idle (Task) Priority,
 *  - 1 .. 2^(n-1) - 1 Tasks priorities. 
 *    (value for n=8, 1..127)
 *  - 2^(n-1) .. 2^n-2 ISR2 virtual priorities
 *    (typically the hardware priority range is smaller than the size of this 
 *    range)
 *    (value for n=8, 128..254)
 *  - 2^n - 1 Special value used to not reenable interrupts
 *    (used for internal interrupts when we want prevent preemption,
 *    like for system timer or for Scheduling Inter Core Interrupts).
 *    (value for n=8, 255)
 *
 *  ISR2 virtual priorities are mapped to hardware priorities by a HAL porting
 *  function in the following way:
 *
 *  Virtual priority 2^(n-1)     == lowest_hardware priority
 *  Virtual priority 2^(n-1) + 1 == second_lowest_harware_priority
 *  ...
 *  and so on. 
 */
typedef OSEE_TASK_PRIO_TYPE                     TaskPrio;

/**
 *  \brief Most significant bit of a priority.
 *  \ingroup primitives-task
 *  This is the most significant bit of a priority
 *  Note that a priority that has this bit to 1 is a "virtual priority" of an 
 *  ISR2.
 */
#define OSEE_ISR2_PRIO_BIT    \
  ( (TaskPrio)1U << ( (sizeof(TaskPrio)*((size_t)CHAR_BIT)) - ((size_t)1U) ) )

/**
 *  \brief Bit mask for all priority bits.
 *  \ingroup primitives-task
 *  Bit mask for all priority bits.
 */
#define OSEE_ISR_ALL_PRIO                       ((TaskPrio)-1)

#if (!defined(OSEE_ISR_SOURCE_TYPE))
/**
 *  \brief Internal type for the interrupt source types.
 *  Interrupt source types.
 */
#define OSEE_ISR_SOURCE_TYPE                    VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_ISR2_SOURCE_TYPE */
/**
 *  \brief This type stores an interrupt source type.
 *  \ingroup primitives-interrupt
 *  This type stores an interrupt source type.
 */
typedef OSEE_ISR_SOURCE_TYPE                    ISRSource;

#if (!defined(OSEE_TASK_ACTIVATION_TYPE))
/**
 *  \brief Internal type to store the number of pending activations.
 *  Type that stores the number of pending activations.
 */
#define OSEE_TASK_ACTIVATION_TYPE               VAR(uint8_t, TYPEDEF)
#endif /* !OSEE_TASK_ACTIVATION_TYPE */
/**
 *  \brief This type stores a number of pending activations.
 *  This type stores a number of pending activations.
 */
typedef OSEE_TASK_ACTIVATION_TYPE               TaskActivation;

#if (!defined(OSEE_CORE_ID_TYPE))
/**
 *  \brief Internal type representing a logical core ID.
 *  Internal type representing a logical core ID.
 */
#define OSEE_CORE_ID_TYPE                       VAR(uint8_t, TYPEDEF)
#endif /* !OSEE_CORE_ID_TYPE */
/**
 *  \brief Type representing a logical core ID.
 *  \ingroup primitives-multicore
 *  This type represents a logical core ID. Depending on the architectures, 
 *  this type can be implemented as an enum.
 */
typedef OSEE_CORE_ID_TYPE                       CoreIdType;

#if (!defined(INVALID_CORE_ID))
/**
 *  \brief Invalid core ID.
 *  \ingroup primitives-multicore
 *  A constant representing an invalid logical core ID.
 */
#define INVALID_CORE_ID                         ((CoreIdType)-1)
#endif /* !INVALID_CORE_ID */

#if (!defined(OSEE_CORE_NUM_TYPE))
/**
 *  \brief Internal type representing a logical core ID.
 *  Internal type representing a logical core ID.
 */
#define OSEE_CORE_NUM_TYPE                      VAR(uint8_t, TYPEDEF)
#endif /* !OSEE_CORE_NUM_TYPE */
/**
 *  \brief Type used to store the total number of cores.
 *  \ingroup primitives-multicore
 *  This type is used to store the total number of cores.
 */
typedef OSEE_CORE_NUM_TYPE                      CoreNumType;

#if (!defined(OSEE_CORE_MASK_TYPE))
/**
 *  \brief Internal type representing a mask of cores.
 *  Internal type representing a mask of cores. It should be big enough to store
 *  one bit for each core of a specific architecture.
 */
#define OSEE_CORE_MASK_TYPE                     VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_CORE_MASK_TYPE */
/**
 *  \brief Type representing a mask of cores.
 *  \ingroup primitives-multicore
 *  This type represents a mask of cores. Each core is represented with a bit
 *  on a bitmask.
 */
typedef OSEE_CORE_MASK_TYPE                     CoreMaskType;

#if (!defined(OSEE_TASK_FUNC_TYPE))
/**
 *  \brief A function pointer.
 *  Internal type representing a function pointer used for callbacks or 
 *  task bodies.
 */
#define OSEE_TASK_FUNC_TYPE(task_func_type_name)\
  P2FUNC(void, TYPEDEF, task_func_type_name)
#endif /* !OSEE_TASK_FUNC_TYPE */
/**
 *  \brief Type representing a function pointer.
 *  This type represents a function pointer, and it is used to store callbacks 
 *  entry points and task bodies in data structures and in the dynamic API.
 */
typedef OSEE_TASK_FUNC_TYPE(TaskFunc) ( void );

/**
 *  \brief Type of the task.
 *  This variable contains the type of tasks in the system, which can be:
 *  - Basic. This is a OSEK/VDX Basic Task.
 *  - Extended. This is a OSEK/VDX Extended Task.
 *  - ISR2. In ERIKA3, ISR2 are handled like special tasks.
 *  - IDLE. The background task executed inside the StartOS(). This includes 
 *    the call to the idle hook.
 */
typedef enum {
  /** \brief Basic Task Type, also known as Run-To-Completion (RTC) TASKs,
             these TASKs cannot call blocking services. */
  OSEE_TASK_TYPE_BASIC,
  /** \brief Extended Task Type, also known as threads. These TASKs own a
             private stack so they can call blocking primitives.*/
  OSEE_TASK_TYPE_EXTENDED,
  /** \brief ISR2 are handled as special kind of TASKs.
             This allow us to share a lot of core for termination and protection
             with other TASKs.*/
  OSEE_TASK_TYPE_ISR2,
  /** \brief Idle Task is a special kind of TASK for Idle Time.
             There's exactly one Idle Task for each core.*/
  OSEE_TASK_TYPE_IDLE
} OsEE_task_type;

/** Synonym of OsEE_task_type, with an OSEK/VDX name structure, mostly used 
  * with dynamic API */
typedef VAR(OsEE_task_type, TYPEDEF)                TaskExecutionType;

/**
 *  \brief These are the task/ISR2 statuses that a task can have during its 
 *         lifetime.
 */
typedef enum {
  /** \brief Status of a TASK that's is not activated yet */
  OSEE_TASK_SUSPENDED,
  /** \brief Task activated and present in raeady, but the current activation
             has not executed yet (never set at OSEE_TASK_RUNNING) */
  OSEE_TASK_READY,
  /** \brief Task activated and present in ready queue,
             but the current activation has already executed for a while.
             Special value to handle Preemption and Unblocking */
  OSEE_TASK_READY_STACKED,
  /** \brief Task blocked in the middle of execution waiting for events */
  OSEE_TASK_WAITING,
  /** \brief Task currently in execution. At most only one task for each core
             can be in this status */
  OSEE_TASK_RUNNING,
  /** \brief Transient status to handle ChainTask service on the same Task */
  OSEE_TASK_CHAINED
} OsEE_task_status;

#define SUSPENDED OSEE_TASK_SUSPENDED /**< OSEK OS SUSPENDED task status */
#define READY     OSEE_TASK_READY     /**< OSEK OS READY task status */
#define WAITING   OSEE_TASK_WAITING   /**< OSEK OS WAITING task status */
#define RUNNING   OSEE_TASK_RUNNING   /**< OSEK OS RUNNING task status */

/**
 *  \brief Task state type.
 *  \ingroup primitives-task
 *  
 *  This is the TaskState type, which is used to store the Task states.
 *  TaskState is returned also by GetTaskState(), with one of the following
 *  values: SUSPENDED, READY, RUNNING, WAITING. The complete list of states 
 *  are defined in the values of OsEE_task_status.
 */
typedef VAR(OsEE_task_status, TYPEDEF)              TaskStateType;
/** Pointer to a TaskSatte */
typedef P2VAR(TaskStateType, TYPEDEF, OS_APPL_DATA) TaskStateRefType;

#if (defined(OSEE_HAS_COUNTERS))
#if (!defined(OSEE_COUNTER_TYPE))
/**
 *  \brief Internal type representing a counter.
 *  Internal type representing a counter.
 */
#define OSEE_COUNTER_TYPE                           VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_COUNTER_TYPE */
/**
 *  \brief Type representing a counter.
 *  \ingroup primitives-alarm
 *  This type represents a counter.
 */
typedef OSEE_COUNTER_TYPE                           CounterType;

#if (!defined(OSEE_TICK_TYPE))
/**
 *  \brief Internal type representing the value of ticks a counter can store.
 *  Internal type representing the value of ticks a counter can store.
 */
#define OSEE_TICK_TYPE                              VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_TICK_TYPE */

/**
 *  \brief Type representing the value of ticks a counter can store.
 *  \ingroup primitives-alarm
 *  This type represents the value of ticks a counter can store.
 */
typedef OSEE_TICK_TYPE                              TickType;
/** \brief This is a pointer to a TickType.
 *  \ingroup primitives-alarm
 *  This type is a pointer to a TickType, used as parameter of a primitive.
 */
typedef P2VAR(TickType, TYPEDEF, OS_APPL_DATA)      TickRefType;

#if (!defined(OSEE_TICK_DELTA_TYPE))
/**
 *  \brief Type used to store tick deviations in Schedule Tables.
 *  This type represents the tick deviations in Schedule Tables.
 */
#define OSEE_TICK_DELTA_TYPE                        VAR(OsEE_sreg, TYPEDEF)
#endif /* !OSEE_TICK_DELTA_TYPE */
/** \brief This is used to store a tick deviation.
 *  This type is used to store tick deviations in Schedule Tables.
 */
typedef OSEE_TICK_DELTA_TYPE                        TickDeltaType;

/**
 *  \brief The AlarmBaseType stores information about a counter.
 *  \ingroup primitives-alarm
 *  This struct is returned by GetAlarmBase() filled with information about the
 *  counter to which an alarm is linked.
 */
typedef VAR(struct, TYPEDEF) {
/** Maximum possible allowed count value in ticks */
  VAR(TickType, TYPEDEF)  maxallowedvalue;
/** Number of hardware ticks required to reach a counter-specific (significant)
    unit. */
  VAR(TickType, TYPEDEF)  ticksperbase;
#if (defined(OSEE_EXTENDED_STATUS))
/** Smallest allowed value for the cycle-parameter of SetRelAlarm/SetAbsAlarm)
    (only for systems with extended status) */
  VAR(TickType, TYPEDEF)  mincycle;
#endif /* OSEE_EXTENDED_STATUS */
} AlarmBaseType;

/** Pointer to an AlarmBase, used as [out] parameter in GetAlarmBase() */
typedef P2VAR(AlarmBaseType, TYPEDEF, OS_APPL_DATA) AlarmBaseRefType;
#endif /* OSEE_HAS_COUNTERS */

#if (defined(OSEE_HAS_ALARMS))
#if (!defined(OSEE_ALARM_ID_TYPE))
/**
 *  \brief Internal type for Alarm IDs.
 *  Internal type used to store an Alarm ID.
 */
#define OSEE_ALARM_ID_TYPE                          VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_ALARM_ID_TYPE */

/**
 *  \brief Type for Alarm IDs.
 *  \ingroup primitives-alarm
 *  Type used to store an Alarm ID.
 */
typedef OSEE_ALARM_ID_TYPE                          AlarmType;

/**
 *  \brief Invalid alarm ID.
 *  \ingroup primitives-alarm
 *  A constant representing an invalid alarm ID.
 */
#define INVALID_ALARM                               ((AlarmType)-1)

/**
 *  \brief Alarm Declaration
 *  \ingroup primitives-alarm
 *
 *  Declares an alarm.
 *
 *  This declaration is currently not mandatory because alarm
 *  identifiers are all declared within the code generated by RT-Druid.
 *
 *  Reference: OSEK OS - ISO 17356-3 - 13.7.2.1
 *  
 *  \param [in] Alarm The alarm to be declared.
 *  \return void
 */
#define DeclareAlarm(Alarm)

/* Alarm Callbacks declarations are handled by RT-Druid.
 * Macro needed by standard */
/**
 *  \brief This macro is used both to declare and to define an alarm callback.
 *  \ingroup primitives-alarm
 *  
 *  This macro is used both to declare and to define an alarm callback.
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.7.5
 *  
 *  \param [in] cbk the callback name
 */
#define ALARMCALLBACK(cbk) void cbk (void)
#endif /* OSEE_HAS_ALARMS */

#if (defined(OSEE_HAS_RESOURCES))
#if (!defined(OSEE_RESOURCE_ID_TYPE))
/**
 *  \brief Internal type for Resource IDs.
 *  Internal type used to store a Resource ID.
 */
#define OSEE_RESOURCE_ID_TYPE                       VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_RESOURCE_ID_TYPE */

/**
 *  \brief Type for Resource IDs.
 *  \ingroup primitives-resource
 *  Type used to store a Resource ID.
 */
typedef OSEE_RESOURCE_ID_TYPE                       ResourceType;

/**
 *  \brief Invalid resource ID.
 *  \ingroup primitives-resource
 *  A constant representing an invalid Resource.
 */
#define INVALID_RESOURCE                            ((ResourceType)-1)

/**
 *  \brief Resource Declaration.
 *  \ingroup primitives-resource
 *
 *  Declares a resource used by Tasks.
 *
 *  This declaration is currently not mandatory because resource
 *  identifiers are all declared within the code generated by RT-Druid.
 *
 *  Reference: OSEK OS - ISO 17356-3 - 13.5.2.1
 *  
 *  \param [in] Res The resource to be declared.
 *  \return void
 */
#define DeclareResource(Res)
#endif /* OSEE_HAS_RESOURCES */

#if (defined(OSEE_HAS_EVENTS))
#if (!defined(OSEE_EVENT_MASK_TYPE))
/**
 *  \brief Internal type representing an event mask.
 *  Internal type representing the value of ticks a counter can store.
 */
#define OSEE_EVENT_MASK_TYPE                        VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_EVENT_MASK_TYPE */

/**
 *  \brief Type representing the value of an event mask.
 *  \ingroup primitives-event
 *  This type represents the value of an event mask. Please note that each
 *  Extended task has a private mask of events reserved for the usage with 
 *  the event primitives. The number of events available depend on the
 *  architecture and it is typically the size of a microcontroller word.
 */
typedef OSEE_EVENT_MASK_TYPE                        EventMaskType;

/**
 *  \brief Pointer to an event mask.
 *  \ingroup primitives-event
 *  This is a pointer to an EventMaskType. it is used as an [out] parametre to 
 *  some of the OSEK primitives.
 */
typedef P2VAR(EventMaskType, TYPEDEF, OS_APPL_DATA) EventMaskRefType;

/**
 *  \brief Event Declaration.
 *  \ingroup primitives-event
 *
 *  Declares an event used by Extended Tasks.
 *
 *  This declaration is currently not mandatory because event
 *  identifiers are all declared within the code generated by RT-Druid.
 *
 *  Reference: OSEK OS - ISO 17356-3 - 13.6.2.1
 *  
 *  \param [in] Event The event to be declared.
 *  \return void
 */
#define DeclareEvent(Event)
#endif /* OSEE_HAS_EVENTS */

#if (defined(OSEE_HAS_SCHEDULE_TABLES))
#if (!defined(OSEE_SCHEDULETABLE_TYPE))
/**
 *  \brief Internal type for Schedule Tables.
 *  Internal type used to store a Schedule Table.
 */
#define OSEE_SCHEDULETABLE_TYPE                     VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_SCHEDULETABLE_TYPE */

/**
 *  \brief Type for Schedule Tables.
 *  \ingroup primitives-resource
 *  Type used to store a Schedule Table.
 */
typedef OSEE_SCHEDULETABLE_TYPE                     ScheduleTableType;

/** The schedule table has not started. */
#define SCHEDULETABLE_STOPPED     (0x00U)
  
/** The schedule table will be started after the end of currently running
    schedule table (schedule table was used in NextScheduleTable() service). */
#define SCHEDULETABLE_NEXT        (0x01U)

/** The schedule table uses explicit synchronization, has been started and is
    waiting for the global time. */
#define SCHEDULETABLE_WAITING     (0x02U)

/** The schedule table is running, but is currently not synchronous to a
    global time source. */
#define SCHEDULETABLE_RUNNING     (0x03U)

/** Used as bit-mask, flag if the schedule table is synchronized */
#define SCHEDULETABLE_SYNCHRONOUS (0x04U)

/** Used as bit-mask, flag if the schedule table shall be not synchronized */
#define SCHEDULETABLE_ASYNC       (0x08U)

/** The schedule table is running and is synchronous to a global time source
    (SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS) */
#define SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS \
        (SCHEDULETABLE_RUNNING | SCHEDULETABLE_SYNCHRONOUS)
  
/** This type describes the status of a schedule. The status can be
 *  one of the following:
 *  - SCHEDULETABLE_STOPPED
 *  - SCHEDULETABLE_NEXT
 *  - SCHEDULETABLE_WAITING
 *  - SCHEDULETABLE_RUNNING
 *  - SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS
 */
typedef VAR(OsEE_reg, TYPEDEF)  ScheduleTableStatusType;

/** This type is a pointer to a ScheduleTableStatusType */
typedef P2VAR(ScheduleTableStatusType, TYPEDEF, OS_APPL_DATA)
  ScheduleTableStatusRefType;

#endif /* OSEE_HAS_SCHEDULE_TABLES */

#if (!defined(OSEE_OBJECT_ID_TYPE))
/**
 *  \brief Internal type for a generic object, used for ErrorHook() macros
 *  This is a generic type for the generic object used for ErrorHook() macros
 */
#define OSEE_OBJECT_ID_TYPE                         VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_OBJECT_ID_TYPE */
/**
 *  \brief Generic Object type used for ErrorHook macros.
 *  Generic Object type used for ErrorHook macros.
 */
typedef OSEE_OBJECT_ID_TYPE                         ObjectIDType;

/**
 *  Invalid value for a generic object used with ErrorHook() macros
 */
#define INVALID_OBJECT_ID                           ((ObjectIDType)-1)

#if (!defined(OSEE_MEM_SIZE_TYPE))
/** Internal type able to store memory sizes. */
#define OSEE_MEM_SIZE_TYPE                          VAR(size_t, TYPEDEF)
#endif /* !OSEE_MEM_SIZE_TYPE */
/** Type able to store memory sizes. */
typedef OSEE_MEM_SIZE_TYPE                          MemSize;

/** Invalid MemSize value. */
#define INVALID_INDEX                               ((MemSize)-1)
/** default ID for the system Stack. */
#define OSEE_SYSTEM_STACK                           ((MemSize)-1)

#if (!defined(STATUSTYPEDEFINED))
#define  STATUSTYPEDEFINED  /**< OSEK compliance */

/**
 * \brief StatusType values.
 * These are all possible StatusType values used in the code.
 */
typedef enum {
  E_OK,                                             /* ((StatusType)0)  */
  E_OS_ACCESS,                                      /* ((StatusType)1)  */
  E_OS_CALLEVEL,                                    /* ((StatusType)2)  */
  E_OS_ID,                                          /* ((StatusType)3)  */
  E_OS_LIMIT,                                       /* ((StatusType)4)  */
  E_OS_NOFUNC,                                      /* ((StatusType)5)  */
  E_OS_RESOURCE,                                    /* ((StatusType)6)  */
  E_OS_STATE,                                       /* ((StatusType)7)  */
  E_OS_VALUE,                                       /* ((StatusType)8)  */
  E_OS_SERVICEID,                                   /* ((StatusType)9)  */
  E_OS_ILLEGAL_ADDRESS,                             /* ((StatusType)10) */
  E_OS_MISSINGEND,                                  /* ((StatusType)11) */
  E_OS_DISABLEDINT,                                 /* ((StatusType)12) */
  E_OS_STACKFAULT,                                  /* ((StatusType)13) */
  E_OS_PARAM_POINTER,                               /* ((StatusType)14) */
  E_OS_PROTECTION_MEMORY,                           /* ((StatusType)15) */
  E_OS_PROTECTION_TIME,                             /* ((StatusType)16) */
  E_OS_PROTECTION_ARRIVAL,                          /* ((StatusType)17) */
  E_OS_PROTECTION_LOCKED,                           /* ((StatusType)18) */
  E_OS_PROTECTION_EXCEPTION,                        /* ((StatusType)19) */
/* Spinlocks Errors */
  E_OS_SPINLOCK,                                    /* ((StatusType)20) */
  E_OS_INTERFERENCE_DEADLOCK,                       /* ((StatusType)21) */
  E_OS_NESTING_DEADLOCK,                            /* ((StatusType)22) */
/* Multicore */
  E_OS_CORE,                                        /* ((StatusType)23) */
/* Implementation specific errors: they must start with E_OS_SYS_ */
/* Error during StartOS */
  E_OS_SYS_INIT,                                    /* ((StatusType)24) */
  E_OS_SYS_SUSPEND_NESTING_LIMIT,                   /* (E_OS_SYS_INIT + 1U) */
/* Error Codes for Dynamic APIs */
  E_OS_SYS_TASK,                                    /* (E_OS_SYS_INIT + 2U) */
  E_OS_SYS_STACK,                                   /* (E_OS_SYS_INIT + 3U) */
  E_OS_SYS_ACT                                      /* (E_OS_SYS_INIT + 4U) */
} OsEE_status_type;

/**
 *  \brief This type stores possible status return values
 */
typedef OsEE_status_type                            StatusType;

#endif  /* !STATUSTYPEDEFINED */

/**
 *  We use a union to hold the a function parameter to be used in the ErrorHook
 *  macros. The union has both a scalar type and a pointer type to hold the
 *  parameter.
 *  
 *  The idea is that the system stores the primitive parameters inside a global
 *  structure before calling ErrorHook. After that, depending on the type of
 *  parameter, the right union member is used to get the right value.
 */
typedef union {
  VAR(ObjectIDType, TYPEDEF)  num_param; /**< numeric parameter */
  VAR(OsEE_addr, TYPEDEF)     p_param;   /**< pointer parameter */
} OsEE_api_param;

/**
 *  \brief System Service unique identifiers
 *  
 *  System Service unique identifiers.
 *  These identifiers and the service id values are specified using the ORTI
 *  conventions:
 *  - Even identifiers are used for the service IDs
 *  - Odd identifiers are used to track the entering inside the service.
 */
typedef enum {
  OSServiceId_ActivateTask                    = (0),
  OSServiceId_TerminateTask                   = (2),
  OSServiceId_ChainTask                       = (4),
  OSServiceId_Schedule                        = (6),
  OSServiceId_GetTaskID                       = (8),
  OSServiceId_GetTaskState                    = (10),
  OSServiceId_DisableAllInterrupts            = (12),
  OSServiceId_EnableAllInterrupts             = (14),
  OSServiceId_SuspendAllInterrupts            = (16),
  OSServiceId_ResumeAllInterrupts             = (18),
  OSServiceId_SuspendOSInterrupts             = (20),
  OSServiceId_ResumeOSInterrupts              = (22),
#if (defined(OSEE_HAS_RESOURCES))
  OSServiceId_GetResource                     = (24),
  OSServiceId_ReleaseResource                 = (26),
#endif /* OSEE_HAS_RESOURCES */
#if (defined(OSEE_HAS_EVENTS))
  OSServiceId_SetEvent                        = (28),
  OSServiceId_ClearEvent                      = (30),
  OSServiceId_GetEvent                        = (32),
  OSServiceId_WaitEvent                       = (34),
#endif /* OSEE_HAS_EVENTS */
#if (defined(OSEE_HAS_ALARMS))
  OSServiceId_GetAlarmBase                    = (36),
  OSServiceId_GetAlarm                        = (38),
  OSServiceId_SetRelAlarm                     = (40),
  OSServiceId_SetAbsAlarm                     = (42),
  OSServiceId_CancelAlarm                     = (44),
#endif /* OSEE_HAS_ALARMS */
#if (defined(OSEE_HAS_COUNTERS))
  OSServiceId_IncrementCounter                = (46),
  OSServiceId_GetCounterValue                 = (48),
  OSServiceId_GetElapsedValue                 = (50),
#endif /* OSEE_HAS_COUNTERS */
#if (defined(OSEE_HAS_SCHEDULE_TABLES))
  OSServiceId_StartScheduleTableRel           = (52),
  OSServiceId_StartScheduleTableAbs           = (54),
  OSServiceId_StopScheduleTable               = (56),
  OSServiceId_GetScheduleTableStatus          = (58),
  OSServiceId_NextScheduleTable               = (60),
  OSServiceId_SyncScheduleTable               = (62),
#endif /* OSEE_HAS_SCHEDULE_TABLES */
#if (defined(OSEE_HAS_SPINLOCKS))
  OSServiceId_GetSpinlock                     = (64),
  OSServiceId_ReleaseSpinlock                 = (66),
  OSServiceId_TryToGetSpinlock                = (68),
#endif /* OSEE_HAS_SPINLOCKS */
  OSServiceId_GetActiveApplicationMode        = (70),
  OSServiceId_ShutdownOS                      = (72),
  OSServiceId_StartOS                         = (74),
#if (!defined(OSEE_SINGLECORE))
  OSServiceId_ShutdownAllCores                = (76),
#endif /* !OSEE_SINGLECORE */
/** Special value to flag an error happened in the Task body
    needed for AR requirement [SWS_Os_00069] */
  OSId_TaskBody                               = (78),
/* Special value to flag an error happened in the ISR2 body
   needed for AS requirement [SWS_Os_00368] */
  OSId_ISR2Body                               = (80),
/* Special value to flag an error happened in a Alarm or Schedule Table
   action */
  OSId_Action                                 = (82),
/* Special value to flag an error happened in a Kernel internal service */
  OSId_Kernel                                 = (84),
  OsId_Invalid                                = (86)
} OsEE_service_id_type;

/** This data type represents the identification of system services. */
typedef OsEE_service_id_type                        OSServiceIdType;


#if (defined(OSEE_HAS_SPINLOCKS))
#if (!defined(OSEE_SPINLOCK_ID_TYPE))
/**
 *  \brief Internal type used to identify a spinlock.
 *  Internal type identifying a spinlock.
 */
#define OSEE_SPINLOCK_ID_TYPE                       VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_SPINLOCK_ID_TYPE */

/**
 *  \brief Type used to identify a spinlock.
 *  Type identifying a spinlock.
 */
typedef OSEE_SPINLOCK_ID_TYPE                       SpinlockIdType;

/**
 *  \brief Type used to indicate if a spinlock has been occupied or not.
 *  \ingroup primitives-multicore
 *  The TryToGetSpinlockType indicates if the spinlock has been occupied or not.
 */
typedef enum {
  TRYTOGETSPINLOCK_NOSUCCESS = 0x0,
  TRYTOGETSPINLOCK_SUCCESS
}                                                   TryToGetSpinlockType;
#endif /* OSEE_HAS_SPINLOCKS */

/*  MISRA-C Deviation. We cannot delegate string concatenation to other
 *  macros, otherwise we will incur in TASK IDs macro expansion that will lead
 *  to compiling errors */

/**
 *  \brief macro used to pass a Task function to dynamic APIs.
 *  This macro is used when using the Dynamic APIs in order to pass a Task
 *  function as parameter (in this way the parameter of the macro is the Task
 *  function name).
 */
#define TASK_FUNC(TaskToBeCreated)    Func##TaskToBeCreated


/**
 *  \brief Task Declaration.
 *  \ingroup primitives-task
 *
 *  Declares a task. It is equivalent of an externa declaration of a task
 *  function defined with the _TASK()_ macro.
 *
 *  This declaration is currently not mandatory because task
 *  identifiers are all declared within the code generated by RT-Druid.
 *
 *  Reference: OSEK OS - ISO 17356-3 - 13.3.2.1
 *  
 *  \param [in] TaskToBeDeclared The task to be declared.
 *  \return void
 */
#define DeclareTask(TaskToBeDeclared) \
        extern FUNC(void, OS_CODE) Func##TaskToBeDeclared ( void )

/**
 *  \brief Task Definition.
 *  \ingroup primitives-task
 *  
 *  This macro is used when defining the body of a task.
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.3.5
 *  
 *  \param [in] TaskToBeDefined This is the task keyword used also in the OIL
 *              file.
 */
#define TASK(TaskToBeDefined) \
        FUNC(void, OS_CODE) Func##TaskToBeDefined ( void )

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_API_TYPES_H */
