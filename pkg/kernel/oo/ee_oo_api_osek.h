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

/** \file   ee_oo_api_osek.h
 *  \brief  OSEK Kernel APIs.
 *
 *  This files contains all OSEK Kernel APIs in Erika Enterprise.
 *
 *  \note    TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date    2016
 */

#ifndef OSEE_API_OSEK_H
#define OSEE_API_OSEK_H

#include "ee_hal.h"
#include "ee_api_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#if (!defined(OSDEFAULTAPPMODE))
#define OSDEFAULTAPPMODE ((AppModeType)0U)
#endif /* !OSDEFAULTAPPMODE */
#if (!defined(DONOTCARE))
#define DONOTCARE ((AppModeType)-1)
#endif /* !DONOTCARE */

FUNC(void, OS_CODE)
  DisableAllInterrupts
(
  void
);

FUNC(void, OS_CODE)
  EnableAllInterrupts
(
  void
);

FUNC(void, OS_CODE)
  SuspendAllInterrupts
(
  void
);

FUNC(void, OS_CODE)
  ResumeAllInterrupts
(
  void
);

FUNC(void, OS_CODE)
  SuspendOSInterrupts
(
  void
);

FUNC(void, OS_CODE)
  ResumeOSInterrupts
(
  void
);

FUNC(StatusType, OS_CODE)
  StartOS
(
  VAR(AppModeType, AUTOMATIC) Mode
);

FUNC(AppModeType, OS_CODE)
  GetActiveApplicationMode
(
  void
);

FUNC(StatusType, OS_CODE)
  ActivateTask
(
  VAR(TaskType, AUTOMATIC) TaskID
);

FUNC(StatusType, OS_CODE)
  ChainTask
(
  VAR(TaskType, AUTOMATIC) TaskID
);

FUNC(StatusType, OS_CODE)
  TerminateTask
(
  void
);

FUNC(StatusType, OS_CODE)
  GetTaskID
(
  VAR(TaskRefType, AUTOMATIC) TaskID
);

FUNC(StatusType, OS_CODE)
  GetTaskState
(
  VAR(TaskType, AUTOMATIC)          TaskID,
  VAR(TaskStateRefType, AUTOMATIC)  State
);

FUNC(StatusType, OS_CODE)
  Schedule
(
  void
);

#if (defined(OSEE_HAS_RESOURCES))
FUNC(StatusType, OS_CODE)
  GetResource
(
  VAR(ResourceType, AUTOMATIC) ResID
);

FUNC(StatusType, OS_CODE)
  ReleaseResource
(
  VAR(ResourceType, AUTOMATIC) ResID
);
#endif /* OSEE_HAS_RESOURCES */

FUNC(StatusType, OS_CODE)
  ShutdownOS
(
  VAR(StatusType, AUTOMATIC) Error
);

#if (defined(OSEE_HAS_ALARMS))
FUNC(StatusType, OS_CODE)
  SetRelAlarm
(
  VAR(AlarmType, AUTOMATIC) AlarmID,
  VAR(TickType, AUTOMATIC)  increment,
  VAR(TickType, AUTOMATIC)  cycle
);

FUNC(StatusType, OS_CODE)
  SetAbsAlarm
(
  VAR(AlarmType, AUTOMATIC) AlarmID,
  VAR(TickType, AUTOMATIC)  start,
  VAR(TickType, AUTOMATIC)  cycle
);

FUNC(StatusType, OS_CODE)
  GetAlarm
(
  VAR(AlarmType, AUTOMATIC)   AlarmID,
  VAR(TickRefType, AUTOMATIC) Tick
);

FUNC(StatusType, OS_CODE)
  GetAlarmBase
(
  VAR(AlarmType, AUTOMATIC)         AlarmID,
  VAR(AlarmBaseRefType, AUTOMATIC)  Info
);

FUNC(StatusType, OS_CODE)
  CancelAlarm
(
  VAR(AlarmType, AUTOMATIC) AlarmID
);

#endif /* OSEE_HAS_ALARMS */

#if (defined(OSEE_HAS_EVENTS))
FUNC(StatusType, OS_CODE)
  WaitEvent
(
  VAR(EventMaskType, AUTOMATIC) Mask
);

FUNC(StatusType, OS_CODE)
  SetEvent
(
  VAR(TaskType,      AUTOMATIC) TaskID,
  VAR(EventMaskType, AUTOMATIC) Mask
);

FUNC(StatusType, OS_CODE)
  GetEvent
(
  VAR(TaskType, AUTOMATIC)          TaskID,
  VAR(EventMaskRefType, AUTOMATIC)  Event
);

FUNC(StatusType, OS_CODE)
  ClearEvent
(
  VAR(EventMaskType, AUTOMATIC) Mask
);
#endif /* OSEE_HAS_EVENTS */

#if (defined(OSEE_HAS_ERRORHOOK))
extern FUNC(void, OS_CODE)
  ErrorHook
(
  VAR(StatusType, AUTOMATIC) Error
);
#endif /* OSEE_HAS_ERRORHOOK */

#if (defined(OSEE_HAS_STARTUPHOOK))
extern FUNC(void, OS_CODE) StartupHook(void);
#endif /* OSEE_HAS_STARTUPHOOK */

#if (defined(OSEE_HAS_PRETASKHOOK))
extern FUNC(void, OS_CODE) PreTaskHook(void);
#endif /* OSEE_HAS_PRETASKHOOK */

#if (defined(OSEE_HAS_POSTTASKHOOK))
extern FUNC(void, OS_CODE) PostTaskHook(void);
#endif /* OSEE_HAS_POSTTASKHOOK */

#if (defined(OSEE_HAS_SHUTDOWNHOOK))
extern FUNC(void, OS_CODE)
  ShutdownHook
(
  VAR(StatusType, AUTOMATIC) Error
);
#endif /* OSEE_HAS_SHUTDOWNHOOK */

#if (defined(OSEE_HAS_COUNTERS))
FUNC(StatusType, OS_CODE)
  GetCounterValue
(
  VAR(CounterType, AUTOMATIC) CounterID,
  VAR(TickRefType, AUTOMATIC) Value
);

FUNC(StatusType, OS_CODE)
  GetElapsedValue
(
  VAR(CounterType, AUTOMATIC) CounterID,
  VAR(TickRefType, AUTOMATIC) Value,
  VAR(TickRefType, AUTOMATIC) ElapsedValue
);

FUNC(StatusType, OS_CODE)
  IncrementCounter
(
  VAR(CounterType, AUTOMATIC) CounterID
);
#endif /* OSEE_HAS_COUNTERS */

#if (defined(OSEE_HAS_SCHEDULE_TABLES))
/** 8.4.9 StartScheduleTableRel [SWS_Os_00347]
 *
 *  @brief This service starts the processing of a schedule table at "Offset"
 *    relative to the "Now" value on the underlying counter.
 *
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *
 *  @param ScheduleTableID Schedule table to be started.
 *
 *  @param Offset Number of ticks on the counter before the the schedule table
 *     processing is started
 *
 *  @return StatusType -
 *          E_OK: No Error
 *          E_OS_ID: (only in EXTENDED status): ScheduleTableID not valid.
 *          E_OS_VALUE: (only in EXTENDED status): Offset is greater than
 *            (OsCounterMaxAllowedValue - InitialOffset) or is equal to 0.
 *          E_OS_STATE: Schedule table was already started.
 */
FUNC(StatusType, OS_CODE)
  StartScheduleTableRel
(
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID,
  VAR(TickType, AUTOMATIC)          Offset
);

/** 8.4.10 StartScheduleTableAbs [SWS_Os_00358]
 *
 * @brief This service starts the processing of a schedule table at an absolute
 *  value "Start" on the underlying counter.
 *
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *
 *  @param ScheduleTableID: Schedule table to be started
 *  @param Start: Absolute counter tick value at which the schedule table is
 *    started
 *
 *  @return StatusType
 *    E_OK: No Error
 *    E_OS_ID (only in EXTENDED status): ScheduleTableID not valid.
 *    E_OS_VALUE (only in EXTENDED status): "Start" is greater than
 *      OsCounterMaxAllowedValue
 *    E_OS_STATE: Schedule table was already started Description:
 */
FUNC(StatusType, OS_CODE)
  StartScheduleTableAbs
(
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID,
  VAR(TickType, AUTOMATIC)          Start
);

/** 8.4.11 StopScheduleTable [SWS_Os_00006]
 *
 *  @brief This service cancels the processing of a schedule table immediately
 *    at any point while the schedule table is running.
 *
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *
 *  @param ScheduleTableID: Schedule table to be stopped
 *
 *  @return StatusType
 *    E_OK: No Error
 *    E_OS_ID (only in EXTENDED status): ScheduleTableID not valid.
 *    E_OS_NOFUNC: Schedule table was already stopped.
 */
FUNC(StatusType, OS_CODE)
  StopScheduleTable
(
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID
);

/** 8.4.16 GetScheduleTableStatus [SWS_Os_00227]
 *
 *  @brief This service queries the state of a schedule table (also with respect
 *    to synchronization).
 *
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *
 *  @param ScheduleTableID (in): Schedule table for which status is requested.
 *  @param ScheduleStatus (out): Reference to ScheduleTableStatusType.
 *
 *  @return StatusType:
 *    E_OK: No Error
 *    E_OS_ID (only in EXTENDED status): Invalid ScheduleTableID
 *
 * (SRS_Os_11002)
 */
FUNC(StatusType, OS_CODE)
  GetScheduleTableStatus
(
  VAR(ScheduleTableType, AUTOMATIC)           ScheduleTableID,
  VAR(ScheduleTableStatusRefType, AUTOMATIC)  ScheduleStatus
);

/** 8.4.12 NextScheduleTable [SWS_Os_00191]
 *
 *  @brief This service switches the processing from one schedule table to
 *    another schedule table.
 *
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *
 *  @param ScheduleTableID_From: Currently processed schedule table
 *  @param ScheduleTableID_To: Schedule table that provides its series of
 *    expiry points
 *
 * @return StatusType
 *    E_OK: No error
 *    E_OS_ID (only in EXTENDED status): ScheduleTableID_From or
 *      ScheduleTableID_To not valid.
 *    E_OS_NOFUNC: ScheduleTableID_From not started
 *    E_OS_STATE: ScheduleTableID_To is started or next
 *
 * (SRS_Os_00099)
 */
FUNC(StatusType, OS_CODE)
  NextScheduleTable
(
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID_From,
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID_To
);

/** 8.4.14 SyncScheduleTable [SWS_Os_00199]
 *
 *  @brief This service provides the schedule table with a synchronization
 *    count and start synchronization.
 *
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *
 *  @param ScheduleTableID (in): Schedule table to be synchronized
 *  @param Value (in): The current value of the synchronization counter
 *
 *  @return StatusType:
 *    E_OK: No errors
 *    E_OS_ID (only in EXTENDED status): The ScheduleTableID was not valid or
 *      schedule table can not be synchronized (OsScheduleTblSyncStrategy not
 *      set or OsScheduleTblSyncStrategy = IMPLICIT)
 *    E_OS_VALUE (only in EXETENDED status): The <Value> is out of range.
 *    E_OS_STATE: The state of schedule table <ScheduleTableID> is equal to
 *      SCHEDULETABLE_STOPPED
 * (SRS_Os_11002)
 */
FUNC(StatusType, OS_CODE)
  SyncScheduleTable
(
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID,
  VAR(TickType, AUTOMATIC)          Value
);

/* 8.4.13 StartScheduleTableSynchron [SWS_Os_00201]
 *
 *  @brief This service starts an explicitly synchronized schedule table
 *    synchronously.
 *
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *
 *  @param ScheduleTableID (in): Schedule table to be started
 *
 *  @return StatusType:
 *    E_OK: No Error
 *    E_OS_ID (only in EXTENDED status): ScheduleTableID not valid
 *    E_OS_STATE: Schedule table was already started Description:
 *
 * (SRS_Os_11002)
 */

/*  8.4.15 SetScheduleTableAsync [SWS_Os_00422]
 *
 *  @brief This service stops synchronization of a schedule table.
 *
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *
 *  @param ScheduleTableID (in) Schedule table for which status is requested
 *
 *  @return StatusType:
 *    E_OK: No Error
 *    E_OS_ID (only in EXTENDED status): Invalid ScheduleTableID
 */
#endif /* OSEE_HAS_SCHEDULE_TABLES */

FUNC(ISRType, OS_CODE)
  GetISRID
(
  void
);

#if (!defined(OSEE_SINGLECORE))
LOCAL_INLINE FUNC(CoreIdType, OS_CODE)
  GetCoreID
(
  void
)
{
  /* [SWS_Os_00675] The function GetCoreID shall return the unique logical
      CoreID of the core on which the function is called.
      The mapping of physical cores to logical CoreIDs is implementation
      specific. (SRS_Os_80001) */
  return  osEE_get_curr_core_id();
}

/* FIXME: from specification return value should be uint32 */
FUNC(CoreNumType, OS_CODE)
  GetNumberOfActivatedCores
(
  void
);

FUNC(void, OS_CODE)
  StartCore
(
  VAR(CoreIdType, AUTOMATIC)                  CoreID,
  P2VAR(StatusType, AUTOMATIC, OS_APPL_DATA)  Status
);

FUNC(void, OS_CODE)
  StartNonAutosarCore
(
  VAR(CoreIdType, AUTOMATIC)                  CoreID,
  P2VAR(StatusType, AUTOMATIC, OS_APPL_DATA)  Status
);

FUNC(void, OS_CODE) 
  ShutdownAllCores
(
  VAR(StatusType, AUTOMATIC)  Error
);

#if (defined(OSEE_HAS_SPINLOCKS))
FUNC(StatusType, OS_CODE)
  GetSpinlock
(
  VAR(SpinlockIdType, AUTOMATIC) SpinlockID
);

FUNC(StatusType, OS_CODE)
  ReleaseSpinlock
(
  VAR(SpinlockIdType, AUTOMATIC) SpinlockID
);
FUNC(StatusType, OS_CODE)
  TryToGetSpinlock
(
  VAR(SpinlockIdType, AUTOMATIC)                        SpinlockID,
  P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_APPL_DATA)  Success
);
#endif /* OSEE_HAS_SPINLOCKS */
#endif /* !OSEE_SINGLECORE */

#if (defined(OSEE_USEGETSERVICEID)) || (defined(OSEE_USEPARAMETERACCESS))
FUNC(OSServiceIdType, OS_CODE)
  osEE_get_service_id
(
  void
);

#define OSErrorGetServiceId() osEE_get_service_id()

#endif /* OSEE_USEGETSERVICEID || OSEE_USEPARAMETERACCESS */
#if (defined(OSEE_USEPARAMETERACCESS))
FUNC(OsEE_api_param, OS_CODE)
  osEE_get_api_param1
(
  void
);

FUNC(OsEE_api_param, OS_CODE)
  osEE_get_api_param2
(
  void
);

FUNC(OsEE_api_param, OS_CODE)
  osEE_get_api_param3
(
  void
);

#define OSError_ActivateTask_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

#define OSError_ChainTask_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

#define OSError_GetTaskID_TaskID()\
  ((TaskRefType)osEE_get_api_param1().p_param)

#define OSError_GetTaskState_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

#define OSError_GetTaskState_State()\
  ((TaskRefType)osEE_get_api_param2().p_param)

#define OSError_ShutdownOS_Error()\
  ((StatusType)osEE_get_api_param1().num_param)

#if (defined(OSEE_HAS_RESOURCES))
#define OSError_GetResource_ResID()\
  ((ResourceType)osEE_get_api_param1().num_param)

#define OSError_ReleaseResource_ResID()\
  ((ResourceType)osEE_get_api_param1().num_param)
#endif /* OSEE_HAS_RESOURCES */

#if (defined(OSEE_HAS_ALARMS))
#define OSError_GetAlarm_AlarmID()\
  ((AlarmType)osEE_get_api_param1().num_param)

#define OSError_CancelAlarm_AlarmID()\
  ((AlarmType)osEE_get_api_param1().num_param)

#define OSError_SetRelAlarm_AlarmID()\
  ((AlarmType)osEE_get_api_param1().num_param)

  #define OSError_SetRelAlarm_increment()\
  ((TickType)osEE_get_api_param2().num_param)

#define OSError_SetRelAlarm_cycle()\
  ((TickType)osEE_get_api_param3().num_param)

#define OSError_SetAbsAlarm_AlarmID()\
  ((AlarmType)osEE_get_api_param1().num_param)

#define OSError_SetAbsAlarm_start()\
  ((TickType)osEE_get_api_param2().num_param)

#define OSError_SetAbsAlarm_cycle()\
  ((TickType)osEE_get_api_param3().num_param)

#define OSError_GetAlarmBase_AlarmID()\
  ((AlarmType)osEE_get_api_param1().num_param)

#define OSError_GetAlarmBase_Info()\
  ((AlarmBaseRefType)osEE_get_api_param2().p_param)
#endif /* OSEE_HAS_ALARMS */

#if (defined(OSEE_HAS_EVENTS))
#define OSError_WaitEvent_Mask()\
  ((EventMaskType)osEE_get_api_param1().num_param)

#define OSError_SetEvent_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

#define OSError_SetEvent_Mask()\
  ((EventMaskType)osEE_get_api_param2().num_param)

#define OSError_GetEvent_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

#define OSError_GetEvent_Event()\
  ((EventMaskRefType)osEE_get_api_param2().p_param)

#define OSError_ClearEvent_Mask()\
  ((EventMaskType)osEE_get_api_param1().num_param)
#endif /* OSEE_HAS_EVENTS */

#if (defined(OSEE_HAS_COUNTERS))
#define OSError_GetCounterValue_CounterID()\
  ((CounterType)osEE_get_api_param1().num_param)

#define OSError_GetCounterValue_Value()\
  ((TickRefType)osEE_get_api_param2().p_param)

#define OSError_GetElapsedValue_CounterID()\
  ((CounterType)osEE_get_api_param1().num_param)

#define OSError_GetElapsedValue_Value()\
  ((TickRefType)osEE_get_api_param2().p_param)

#define OSError_GetElapsedValue_ElapsedValue()\
  ((TickRefType)osEE_get_api_param3().p_param)

#define OSError_IncrementCounter_CounterID()\
  ((CounterType)osEE_get_api_param1().num_param)
#endif /* OSEE_HAS_COUNTERS */

#if (defined(OSEE_HAS_SCHEDULE_TABLES))
#define OSError_StartScheduleTableRel_ScheduleTableID()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)

#define OSError_StartScheduleTableRel_Offset()\
  ((TickType)osEE_get_api_param2().num_param)

#define OSError_StartScheduleTableAbs_ScheduleTableID()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)

#define OSError_StartScheduleTableAbs_Start()\
  ((TickType)osEE_get_api_param2().num_param)

#define OSError_StopScheduleTable_ScheduleTableID()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)

#define OSError_GetScheduleTableStatus_ScheduleTableID()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)

#define OSError_GetScheduleTableStatus_ScheduleStatus()\
  ((ScheduleTableStatusRefType)osEE_get_api_param2().p_param)

#define OSError_NextScheduleTable_ScheduleTableID_From()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)
  
#define OSError_NextScheduleTable_ScheduleTableID_To()\
  ((ScheduleTableType)osEE_get_api_param2().num_param)

#define OSError_SyncScheduleTable_ScheduleTableID()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)

#define OSError_SyncScheduleTable_Value()\
  ((TickType)osEE_get_api_param2().num_param)
#endif /* OSEE_HAS_SCHEDULE_TABLES */

#if (defined(OSEE_HAS_SPINLOCKS))
#define OSError_GetSpinlock_SpinlockID()\
  ((SpinlockIdType)osEE_get_api_param1().num_param)

#define OSError_ReleaseSpinlock_SpinlockID()\
  ((SpinlockIdType)osEE_get_api_param1().num_param)

#define OSError_TryToGetSpinlock_SpinlockID()\
  ((SpinlockIdType)osEE_get_api_param1().num_param)

#define OSError_TryToGetSpinlock_Success()\
  ((TryToGetSpinlockType)osEE_get_api_param2().p_param)
#endif /* OSEE_HAS_SPINLOCKS */
#endif /* OSEE_USEPARAMETERACCESS */

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_API_OSEK_H_ */
