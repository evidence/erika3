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

/** \file   ee_api_types.h
 *  \brief  OSEK Kernel API Types.
 *
 *  This files contains all types and symbols needed by OSEK Kernel APIs
 *  in Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2016
 */

#if (!defined(OSEE_API_TYPES_H))
#define OSEE_API_TYPES_H

#include "ee_platform_types.h"

/* OSEK Style typedefs */
#if (!defined(OSEE_APPMODE_TYPE))
#define OSEE_APPMODE_TYPE                       VAR(unsigned char, TYPEDEF)
#endif /* !OSEE_APPMODE_TYPE */
typedef OSEE_APPMODE_TYPE                       AppModeType;
#define INVALID_APPMODE                         ((AppModeType)-1)

#if (!defined(OSEE_TASK_ID_TYPE))
#define OSEE_TASK_ID_TYPE                       VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_TASK_ID_TYPE */
typedef OSEE_TASK_ID_TYPE                       TaskType;
typedef OSEE_TASK_ID_TYPE                       ISRType;

typedef P2VAR(TaskType, TYPEDEF, OS_APPL_DATA)  TaskRefType;
#define INVALID_TASK                            ((TaskType)-1)
#define INVALID_ISR                             INVALID_TASK

#if (!defined(OSEE_TASK_PRIO_TYPE))
#define OSEE_TASK_PRIO_TYPE                     VAR(unsigned char, TYPEDEF)
#endif /* !OSEE_TASK_PRIO_TYPE */

/**
  It represent the priority of TASK and virtual priority for ISR2.
  The priority is an integer number with higher values for higher priorities.
  Choosen the dimension 'n' in bit of the type (usually n=8),
  the priority space is partitioned in the following way:
  0 Idle (Task) Priority,
  1 .. 2^(n-1) - 1 Tasks priorities
  2^(n-1) .. 2^n-2 ISR2 virtual priorities
    (not all this space need to correspond to an hardware priority)
  2^n - 1 Special value used to not reenable interrupts
    (used for internal interrupts when we want prevent preemption,
     like for system timer or for Scheduling Inter Core Interrupts).

  Using priorities in this way we are able to make coesist in the same data
  structures ISR2 and TASK out of the box.

  ISR2 virtual priorities are mapped to hardware priorities by a hal porting
  function in the following way:

  Virtual priority 2^(n-1) == lowest_hardware priority
  2^(n-1) + 1 == second_lowest_harware_priority
  ...
  and so on. */
typedef OSEE_TASK_PRIO_TYPE                     TaskPrio;
#define OSEE_ISR2_PRIO_BIT                 ((TaskPrio)(~(((TaskPrio)-1) >> 1U)))
#define OSEE_ISR_ALL_PRIO                       ((TaskPrio)-1)

#if (!defined(OSEE_ISR_SOURCE_TYPE))
#define OSEE_ISR_SOURCE_TYPE                    VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_ISR2_SOURCE_TYPE */
typedef OSEE_ISR_SOURCE_TYPE                    ISRSource;

#if (!defined(OSEE_TASK_ACTIVATION_TYPE))
#define OSEE_TASK_ACTIVATION_TYPE               VAR(unsigned char, TYPEDEF)
#endif /* !OSEE_TASK_ACTIVATION_TYPE */
typedef OSEE_TASK_ACTIVATION_TYPE               TaskActivation;

#if (!defined(OSEE_CORE_ID_TYPE))
#define OSEE_CORE_ID_TYPE                       VAR(unsigned char, TYPEDEF)
#endif /* !OSEE_CORE_ID_TYPE */
typedef OSEE_CORE_ID_TYPE                       CoreIdType;

#define INVALID_CORE_ID                         ((CoreIdType)-1)

#if (!defined(OSEE_CORE_MASK_TYPE))
#define OSEE_CORE_MASK_TYPE                     VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_CORE_MASK_TYPE */
typedef OSEE_CORE_MASK_TYPE                     CoreMaskType;

#if (!defined(OSEE_TASK_FUNC_TYPE))
#define OSEE_TASK_FUNC_TYPE(task_func_type_name)\
  P2FUNC(void, TYPEDEF, task_func_type_name)
#endif /* !OSEE_TASK_FUNC_TYPE */
typedef OSEE_TASK_FUNC_TYPE(TaskFunc) ( void );

/**
 * \brief TASK types enumeration
 */
typedef enum OsEE_task_type_tag {
  /** \brief Basic Task Type, also known as Run-To-Completition (RTC) TASKs,
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

typedef VAR(OsEE_task_type, TYPEDEF)                TaskExecutionType;

typedef enum OsEE_task_status_tag {
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

#define SUSPENDED OSEE_TASK_SUSPENDED
#define READY     OSEE_TASK_READY
#define WAITING   OSEE_TASK_WAITING
#define RUNNING   OSEE_TASK_RUNNING

typedef VAR(OsEE_task_status, TYPEDEF)              TaskStateType;
typedef P2VAR(TaskStateType, TYPEDEF, OS_APPL_DATA) TaskStateRefType;

#if (defined(OSEE_HAS_COUNTERS))
#if (!defined(OSEE_COUNTER_TYPE))
#define OSEE_COUNTER_TYPE                           VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_COUNTER_TYPE */
typedef OSEE_COUNTER_TYPE                           CounterType;

#if (!defined(OSEE_TICK_TYPE))
#define OSEE_TICK_TYPE                              VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_TICK_TYPE */

typedef OSEE_TICK_TYPE                              TickType;
typedef P2VAR(TickType, TYPEDEF, OS_APPL_DATA)      TickRefType;
#endif /* OSEE_HAS_COUNTERS */

#if (defined(OSEE_HAS_ALARMS))
#if (!defined(OSEE_ALARM_ID_TYPE))
#define OSEE_ALARM_ID_TYPE                          VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_ALARM_ID_TYPE */

typedef OSEE_ALARM_ID_TYPE                          AlarmType;

#define INVALID_ALARM                               ((AlarmType)-1)

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

typedef P2VAR(AlarmBaseType, TYPEDEF, OS_APPL_DATA) AlarmBaseRefType;

/* Alarm declarations are handled by RT-Druid. Macro needed by standard */
#define DeclareAlarm(Alarm)
/* Alarm Callbacks declarations are handled by RT-Druid.
 * Macro needed by standard */
#define ALARMCALLBACK(cbk) void cbk (void)
#endif /* OSEE_HAS_ALARMS */

#if (defined(OSEE_HAS_RESOURCES))
#if (!defined(OSEE_RESOURCE_ID_TYPE))
#define OSEE_RESOURCE_ID_TYPE                       VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_RESOURCE_ID_TYPE */

typedef OSEE_RESOURCE_ID_TYPE                       ResourceType;

#define INVALID_RESOURCE                            ((ResourceType)-1)

/* Resource declarations are handled by RT-Druid. Macro needed by standard */
#define DeclareResource(Res)
#endif /* OSEE_HAS_RESOURCES */

#if (defined(OSEE_HAS_EVENTS))
#if (!defined(OSEE_EVENT_MASK_TYPE))
#define OSEE_EVENT_MASK_TYPE                        VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_EVENT_MASK_TYPE */

typedef OSEE_EVENT_MASK_TYPE                        EventMaskType;

typedef P2VAR(EventMaskType, TYPEDEF, OS_APPL_DATA) EventMaskRefType;

/* Event declaration handled by RT-Druid. Macro Needed because required by the
 * standard */
#define DeclareEvent(Event)
#endif /* OSEE_HAS_EVENTS */

#if (!defined(OSEE_OBJECT_ID_TYPE))
#define OSEE_OBJECT_ID_TYPE                         VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_OBJECT_ID_TYPE */

typedef OSEE_OBJECT_ID_TYPE                         ObjectIDType;

#define INVALID_OBJECT_ID                           ((ObjectIDType)-1)

#if (!defined(OSEE_MEM_SIZE_TYPE))
#define OSEE_MEM_SIZE_TYPE                          VAR(size_t, TYPEDEF)
#endif /* !OSEE_MEM_SIZE_TYPE */
typedef OSEE_MEM_SIZE_TYPE                          MemSize;

#define INVALID_INDEX                               ((MemSize)-1)
#define OSEE_SYSTEM_STACK                           ((MemSize)-1)

#if (!defined(STATUSTYPEDEFINED))
#define  STATUSTYPEDEFINED  /**< OSEK compliance */

typedef enum OsEE_status_type_tag {
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
/* Error Codes for Dynamic APIs */
  E_OS_SYS_TASK,                                    /* (E_OS_SYS_INIT + 1U) */
  E_OS_SYS_STACK,                                   /* (E_OS_SYS_INIT + 2U) */
  E_OS_SYS_ACT                                      /* (E_OS_SYS_INIT + 3U) */
} OsEE_status_type;

typedef OsEE_status_type                            StatusType;

#endif  /* !STATUSTYPEDEFINED */

/* TODO: A union is needed to hold the generic opaque function parameter,
 *       moreover in addition to the deviation for the union, probably MISRA
 *       will require something more "types aware" but actually this is just
 *       fine. */
typedef union OsEE_api_param_tag {
  VAR(ObjectIDType, TYPEDEF)  num_param;
  VAR(OsEE_addr, TYPEDEF)     p_param;
} OsEE_api_param;

/* System Service unique identifiers
 * N.B. These identifiers and the service id variable will be used ORTI
 *      too, so I'll use only even identifiers for the service IDs
 *      (leaving the odd values for the ORTI service terminated event tracing).
 */
typedef enum OsEE_service_id_type_tag {
  OSServiceId_ActivateTask,                         /*  (0) */
  OSServiceId_ActivateTask_Entry,                   /*  (1) */
  OSServiceId_TerminateTask,                        /*  (2) */
  OSServiceId_TerminateTask_Entry,                  /*  (3) */
  OSServiceId_ChainTask,                            /*  (4) */
  OSServiceId_ChainTask_Entry,                      /*  (5) */
  OSServiceId_Schedule,                             /*  (6) */
  OSServiceId_Schedule_Entry,                       /*  (7) */
  OSServiceId_GetTaskID,                            /*  (8) */
  OSServiceId_GetTaskID_Entry,                      /*  (9) */
  OSServiceId_GetTaskState,                         /* (10) */
  OSServiceId_GetTaskState_Entry,                   /* (11) */
  OSServiceId_DisableAllInterrupts,                 /* (12) */
  OSServiceId_DisableAllInterrupts_Entry,           /* (13) */
  OSServiceId_EnableAllInterrupts,                  /* (14) */
  OSServiceId_EnableAllInterrupts_Entry,            /* (15) */
  OSServiceId_SuspendAllInterrupts,                 /* (16) */
  OSServiceId_SuspendAllInterrupts_Entry,           /* (17) */
  OSServiceId_ResumeAllInterrupts,                  /* (18) */
  OSServiceId_ResumeAllInterrupts_Entry,            /* (19) */
  OSServiceId_SuspendOSInterrupts,                  /* (20) */
  OSServiceId_SuspendOSInterrupts_Entry,            /* (21) */
  OSServiceId_ResumeOSInterrupts,                   /* (22) */
  OSServiceId_ResumeOSInterrupts_Entry,             /* (23) */
#if (defined(OSEE_HAS_RESOURCES))
  OSServiceId_GetResource,                          /* (24) */
  OSServiceId_GetResource_Entry,                    /* (25) */
  OSServiceId_ReleaseResource,                      /* (26) */
  OSServiceId_ReleaseResource_Entry,                /* (27) */
#endif /* OSEE_HAS_RESOURCES */
#if (defined(OSEE_HAS_EVENTS))
  OSServiceId_SetEvent,                             /* (28) */
  OSServiceId_SetEvent_Entry,                       /* (29) */
  OSServiceId_ClearEvent,                           /* (30) */
  OSServiceId_ClearEvent_Entry,                     /* (31) */
  OSServiceId_GetEvent,                             /* (32) */
  OSServiceId_GetEvent_Entry,                       /* (33) */
  OSServiceId_WaitEvent,                            /* (34) */
  OSServiceId_WaitEvent_Entry,                      /* (35) */
#endif /* OSEE_HAS_EVENTS */
#if (defined(OSEE_HAS_ALARMS))
  OSServiceId_GetAlarmBase,                         /* (36) */
  OSServiceId_GetAlarmBase_Entry,                   /* (37) */
  OSServiceId_GetAlarm,                             /* (38) */
  OSServiceId_GetAlarm_Entry,                       /* (39) */
  OSServiceId_SetRelAlarm,                          /* (40) */
  OSServiceId_SetRelAlarm_Entry,                    /* (41) */
  OSServiceId_SetAbsAlarm,                          /* (42) */
  OSServiceId_SetAbsAlarm_Entry,                    /* (43) */
  OSServiceId_CancelAlarm,                          /* (44) */
  OSServiceId_CancelAlarm_Entry,                    /* (45) */
#endif /* OSEE_HAS_ALARMS */
#if (defined(OSEE_HAS_COUNTERS))
  OSServiceId_IncrementCounter,                     /* (46) */
  OSServiceId_IncrementCounter_Entry,               /* (47) */
  OSServiceId_GetCounterValue,                      /* (48) */
  OSServiceId_GetCounterValue_Entry,                /* (49) */
  OSServiceId_GetElapsedValue,                      /* (50) */
  OSServiceId_GetElapsedValue_Entry,                /* (51) */
#endif /* OSEE_HAS_COUNTERS */
  OSServiceId_GetActiveApplicationMode,             /* (52) */
  OSServiceId_GetActiveApplicationMode_Entry,       /* (53) */
  OSServiceId_ShutdownOS,                           /* (54) */
  OSServiceId_ShutdownOS_Entry,                     /* (55) */
  OSServiceId_StartOS,                              /* (56) */
  OSServiceId_StartOS_Entry,                        /* (57) */
/** Special value to flag an error happened in the Task body
    needed for AR requirement [SWS_Os_00069] */
  OSId_TaskBody,                                    /* (58) */
/* Not needed, only added to not explicitly assign the value to the
 * next label */
  OSId_TaskBody_Entry,                              /* (59) */
/* Special value to flag an error happened in the ISR2 body
   needed for AS requirement [SWS_Os_00368] */
  OSId_ISR2Body,                                    /* (60) */
/* As above */
  OSId_ISR2Body_Entry,                              /* (61) */
/* Special value to flag an error happened in a Alarm or Schedule Table
   action */
  OSId_Action,                                      /* (62) */
  OSId_Action_Entry,                                /* (63) */
/* Special value to flag an error happened in a Kernel internal service */
  OSId_Kernel,                                      /* (64) */
  OsId_Invalid  = (-1)
} OsEE_service_id_type;

/** @typedef This data type represents the identification of system services. */
typedef OsEE_service_id_type                        OSServiceIdType;

/*  MISRA-C Deviation. We cannot delegate string concatenation to other
 *  macros, otherwise we will incur in TASK IDs macro expansion that will lead
 *  to compiling errors */
#define TASK_FUNC(Task)   Func##Task
#define DeclareTask(Task) extern FUNC(void, OS_CODE) Func##Task ( void )
#define TASK(Task)               FUNC(void, OS_CODE) Func##Task ( void )

#endif /* !OSEE_API_TYPES_H */
