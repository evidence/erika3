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
/**
 *  \brief Default Application Mode.
 *  \ingroup primitives-startup
 *  
 *  Default Application Mode. Always a valid parameter for StartOS()
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.8.3
 */
#define OSDEFAULTAPPMODE ((AppModeType)0U)
#endif /* !OSDEFAULTAPPMODE */
#if (!defined(DONOTCARE))
/**
 *  \brief Do Not Care Application Mode.
 *  \ingroup primitives-startup
 *  
 *  Do Not Care Application Mode. Inherits the startup mode from other cores.
 *  
 *  Reference: AUTOSAR OS - [SWS_Os_91007]
 */
#define DONOTCARE ((AppModeType)-1)
#endif /* !DONOTCARE */

/**
 *  \brief Disables all interrupts.
 *  \ingroup primitives-interrupt
 *  
 *  DisableAllInterrupts() and EnableAllInterrupts() are
 *  used to implement critical sections with interrupt disabled.
 *
 *  This primitive disables all the interrupts sources in the system,
 *  and saves the interrupt state that will be restored by a call to
 *  EnableAllInterrupts().
 *
 *  The primitive may be called from an ISR category 1 and category 2
 *  and from the task level, but not from hook routines. No primitives
 *  can be called within critical sections surrounded by
 *  DisableAllInterrupts() and EnableAllInterrupts().
 *
 *  Critical sections using DisableAllInterrupts() and 
 *  EnableAllInterrupts() cannot be nested.  If you need nested
 *  critical sections, please use SuspendOSInterrupts() /
 *  ResumeOSInterrupts() or SuspendAllInterrupts() /
 *  ResumeAllInterrupts().
 *  
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.4.2.2
 */
FUNC(void, OS_CODE)
  DisableAllInterrupts
(
  void
);

/**
 *  \brief Enables all interrupts.
 *  \ingroup primitives-interrupt
 *  
 *  DisableAllInterrupts() and EnableAllInterrupts() are
 *  used to implement critical sections with interrupt disabled.
 *
 *  This primitive restores the state saved by
 *  DisableAllInterrupts(), enabling the recognition of interrupts.
 *   
 *  The primitive may be called from an ISR category 1 and category 2
 *  and from the task level, but not from hook routines.  No primitives
 *  can be called inside critical sections surrounded by
 *  DisableAllInterrupts() and EnableAllInterrupts().
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.4.2.1
 */
FUNC(void, OS_CODE)
  EnableAllInterrupts
(
  void
);

/**
 *  \brief Disables interrupt, saving the current status.
 *  \ingroup primitives-interrupt
 *  
 *  SuspendAllInterrupts() and ResumeAllInterrupts() are
 *  used to implement critical sections with interrupt disabled, with
 *  nesting support.
 *
 *  This primitive disables all the interrupts sources in the system,
 *  and saves the interrupt state that will be restored by a call to
 *  ResumeAllInterrupts().
 *   
 *  The service may be called from an ISR category 1 and category 2,
 *  from alarm-callbacks and from the task level, but not from all
 *  hook routines.
 *
 *  No primitive calls beside SuspendAllInterrupts() /
 *  ResumeAllInterrupts() pairs and
 *  SuspendOSInterrupts() / ResumeOSInterrupts() pairs
 *  are allowed within this critical section.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.4.2.4
 */
FUNC(void, OS_CODE)
  SuspendAllInterrupts
(
  void
);

/**
 *  \brief Resumes the interrupt status saved with SuspendAllInterrupts().
 *  \ingroup primitives-interrupt
 *  
 *  SuspendAllInterrupts() and ResumeAllInterrupts() are
 *  used to implement critical sections with interrupt disabled, with
 *  nesting support.
 *
 *  This primitive restores the state saved by
 *  SuspendAllInterrupts(), enabling the recognition of
 *  interrupts if it is the last call in a series of nested calls of
 *  SuspendAllInterrupts() / ResumeAllInterrupts() and
 *  SuspendOSInterrupts() / ResumeOSInterrupts() pairs.
 *
 *  This primitive may be called from an ISR category 1 and category
 *  2, from alarm-callbacks and from the task level, but not from all
 *  hook routines.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.4.2.3
 */
FUNC(void, OS_CODE)
  ResumeAllInterrupts
(
  void
);

/**
 *  \brief Disables ISR2 interrupt, saving the current status.
 *  \ingroup primitives-interrupt
 *  
 *  SuspendOSInterrupts() and ResumeOSInterrupts() are
 *  used to implement critical sections with interrupt category 2
 *  disabled, with nesting support.
 *
 *  This primitive disables all the interrupts sources of category 2
 *  in the system, and saves the interrupt state that will be restored
 *  by a call to ResumeOSInterrupts().
 *   
 *  The service may be called from an ISR category 1 and category 2,
 *  and from the task level.
 *
 *  No primitive calls beside SuspendAllInterrupts() /
 *  ResumeAllInterrupts() pairs and
 *  SuspendOSInterrupts() / ResumeOSInterrupts() pairs
 *  are allowed within this critical section.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.4.2.6
 */
FUNC(void, OS_CODE)
  SuspendOSInterrupts
(
  void
);

/**
 *  \brief Resumes the interrupt status saved with SuspendOSInterrupts().
 *  \ingroup primitives-interrupt
 *  
 *  SuspendOSInterrupts() and ResumeOSInterrupts() are
 *  used to implement critical sections with interrupt category 2
 *  disabled, with nesting support.
 *
 *  This primitive restores the state saved by
 *  SuspendOSInterrupts(), enabling the recognition of
 *  interrupts if it is the last call in a series of nested calls of
 *  SuspendAllInterrupts() / ResumeAllInterrupts() and
 *  SuspendOSInterrupts() / ResumeOSInterrupts() pairs.
 *
 *  The primitive may be called from an ISR category 1 and category 2
 *  and from the task level, but not from hook routines.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.4.2.5
 */
FUNC(void, OS_CODE)
  ResumeOSInterrupts
(
  void
);

/**
 *  \brief Operating system startup routine.
 *  \ingroup primitives-startup
 *  
 *  The user can call this system service to start the operating
 *  system in a specific Application mode. Only allowed outside of the
 *  operating system, at startup. The function calls in order the
 *  StartupHook(), then it activates the tasks and set the
 *  alarms _AUTOSTART_ set as _TRUE_ inside the OIL
 *  configuration file. After that, the system is rescheduled and the
 *  highest priority ready task is executed.
 *  
 *  The StartOS() primitive by default never returns to the caller.
 *  
 *  If specified in the OIL file, the idle loop hook will be called 
 *  inside the StartOS().
 *  
 *  On multicore systems, the StartOS() have to be called by each core,
 *  as specified by the AUTOSAR OS standard.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.8.2.2
 *
 *  \param [in] Mode The startup application mode.
 *  \return The function returns a StatusType.
 *          - E_OK (Extended) No error.
 *          - E_OS_SYS_INIT (Extended) Error during initialization.
 */
FUNC(StatusType, OS_CODE)
  StartOS
(
  VAR(AppModeType, AUTOMATIC) Mode
);

/**
 *  \brief Abort the overall system.
 *  \ingroup primitives-startup
 *  
 *  The user can call this system service to abort the overall system
 *  (e.g. emergency off). 
 *
 *  If a ShutdownHook() is configured the hook routine
 *  ShutdownHook() is always called (with _Error_ as
 *  argument) before shutting down the operating system.
 *  
 *  The Operating system shutdown is currently implemented as a forever
 *  loop with interrupt disabled.
 *
 *  In case of multicore devices, the ShutdownHook takes care of multicore
 *  synchronization and multicore shutdown as specified by the AUTOSAR OS
 *  standard.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.8.2.3
 *
 *  \param [in] Error The identifier of the error which occurred.
 *  \return The function does not return.
 */
FUNC(StatusType, OS_CODE)
  ShutdownOS
(
  VAR(StatusType, AUTOMATIC) Error
);


/**
 *  \brief Reads the current application mode.
 *  \ingroup primitives-startup
 *  
 *  The function returns the current Application Mode, that has been
 *  set up by StartOS() at system startup.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.8.2.1
 *  
 *  \return The function returns the current application mode.
 */
FUNC(AppModeType, OS_CODE)
  GetActiveApplicationMode
(
  void
);


/** 
 *  \brief This primitive activates a task TaskID.
 *  \ingroup primitives-task
 *  
 *  This primitive activates a task TaskID, putting it in the
 *  READY state, or in the RUNNING state if the
 *  scheduler finds that the activated task should become the running
 *  task.
 *
 *  Once activated, the task will run for an instance, starting from
 *  its first instruction. For the BCC2 and ECC2 Conformance classes,
 *  pending activations can be stored if the task has been configured
 *  with a number of activations greater than 1 within the OIL
 *  configuration file.
 *
 *  The function can be called from the Background task (typically,
 *  the main() function).
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.3.3.1
 *
 *  @param [in] TaskID Task to be activated.
 *
 *  @return The function returns a StatusType
 *          - E_OK: No error.
 *          - E_OS_LIMIT: Too many pending activations of TaskID.
 *          - E_OS_ID: (Extended) TaskID is invalid.
 */
FUNC(StatusType, OS_CODE)
  ActivateTask
(
  VAR(TaskType, AUTOMATIC) TaskID
);

/**
 *  \brief Terminates the calling task, and atomically activates 
 *  the TaskID passed as parameter.
 *  \ingroup primitives-task
 *  
 *  This primitive is similar to TerminateTask, with the
 *  differences listed below.
 *  
 *  After the calling task is terminated, TaskID is activated again.
 *  
 *  If TaskID is the calling task ID, then the calling task is
 *  terminated, the Internal Resource is unlocked, and then the
 *  calling task is put again in the ready queue to be scheduled. The
 *  Internal Resource will be locked again when the task will be again
 *  selected for scheduling.
 *
 *  When called successfully, ChainTask does not return to the
 *  caller. In case of error the primitive returns, and the returned
 *  error value can be evaluated by the application.
 *  
 *  When an extended task is transferred from suspended state into
 *  ready state all its events are cleared.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.3.3.3
 *  
 *  \param [in] TaskID The task to activate
 *  
 *  \return The function returns a StatusType
 *          - No return: If the call is successful.
 *          - E_OS_LIMIT: Too many task activations of TaskID. The
 *            Task activation in this case is ignored.
 *          - E_OS_ID: (Extended) Task TaskID is invalid.
 *          - E_OS_RESOURCE: (Extended) Calling task still occupies
 *            resources.
 *          - E_OS_CALLEVEL: (Extended) Call at interrupt level.
 */
FUNC(StatusType, OS_CODE)
  ChainTask
(
  VAR(TaskType, AUTOMATIC) TaskID
);

/**
 *  \brief Terminates the calling task.
 *  \ingroup primitives-task
 *  
 *  This primitive terminates the calling task. The function can be
 *  called from any function nesting: the stack space used by the task
 *  is also freed. The calling task should not have any Resource
 *  locked when this primitive is called (apart an Internal Resource
 *  that is automatically released with this call).
 *
 *  After the call, the calling task is set in the SUSPENDED
 *  state, and it can be reactivated again using
 *  ActivateTask, ChainTask, or using Alarm
 *  notifications.
 *
 *  All the tasks must terminate with a call to TerminateTask or
 *  ChainTask. If not present, TerminateTask will be called automatically.
 *
 *  With Standard Status, the primitive never returns. With Extended
 *  Status, the primitive may return in case of errors.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.3.3.2
 *  
 *  \return The function returns a StatusType
 *          - No return: If the call is successful.
 *          - E_OS_RESOURCE: (Extended) The task still occupies resources.
 *          - E_OS_CALLEVEL: (Extended) The function was called at 
 *            interrupt level.
 */
FUNC(StatusType, OS_CODE)
  TerminateTask
(
  void
);

/**
 *  \brief Returns the Task ID of the running task.
 *  \ingroup primitives-task
 *  
 *  The function returns the Task ID of the running task. If no task is
 *  running, INVALID_TASK is returned.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.3.3.5
 * 
 *  \param [out] TaskID The Task ID of the running task
 *  
 *  \return The function always returns a StatusType of value E_OK.
 */
FUNC(StatusType, OS_CODE)
  GetTaskID
(
  VAR(TaskRefType, AUTOMATIC) TaskID
);

/**
 *  \brief This primitive returns the state of a given task.
 *  \ingroup primitives-task
 *  
 *  This primitive returns the state of a given task. Possible states
 *  are listed in the definition of the TaskStateType. 
 *
 *  If the task TaskID supports pending activation, and the
 *  task has been activated more than once, the results refer to the
 *  state of its oldest activation.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.3.3.6
 * 
 *  \param [in] TaskID The task for which we want to read the state.
 *  \param [out] State The task state of TaskID.
 *  \return The function returns a StatusType.
 *          - E_OK: (Extended) No error.
 *          - E_OS_ID: (Extended) Task TaskID is invalid.
 */
FUNC(StatusType, OS_CODE)
  GetTaskState
(
  VAR(TaskType, AUTOMATIC)          TaskID,
  VAR(TaskStateRefType, AUTOMATIC)  State
);

/**
 *  \brief A rescheduling point typically used in non-preemptive tasks.
 *  \ingroup primitives-task
 *  
 *  This primitive can be used as a rescheduling point for tasks that
 *  have Internal Resources and for non preemptive tasks (Non
 *  preemptive tasks can be seen as tasks with an Internal Resource with the
 *  highest priority ceiling available assigned.).
 *
 *  When this primitive is called, the task releases its Internal
 *  Resource, and checks if there are higher priority tasks that have
 *  to preempt (In that case, a preemption is implemented). When the
 *  primitive returns, the task will reacquire its internal resource.
 *  
 *  The primitive does nothing if the calling task has no internal
 *  resource assigned.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.3.3.4
 * 
 *  \return The function returns a StatusType.
 *          - E_OK: No error.
 * 	        - E_OS_CALLEVEL: (Extended) The primitive was called at interrupt
 *            level.
 *          - E_OS_RESOURCE: (Extended) The calling task occupies resources.
 */
FUNC(StatusType, OS_CODE)
  Schedule
(
  void
);

/*! @} */



#if (defined(OSEE_HAS_RESOURCES))
	
/**
 *  \brief Locks a shared resource.
 *  \ingroup primitives-resource
 *  
 *  This primitive can be used to implement a critical section guarded
 *  by Resource ResID. The critical section will end with the
 *  call to ReleaseResource().
 *
 *  Nesting between critical sections guarded by different resources
 *  is allowed.
 *
 *  Calls to TerminateTask(), ChainTask(),
 *  Schedule(), and WaitEvent() are not allowed inside
 *  the critical section.
 *
 *  Resources may be called on ISR level as well (see ISO17356-3 8.7).
 *  
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.5.3.1
 * 
 *  \param [in] ResID The resource to lock.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_ID (Extended) Resource ResID is invalid.
 *          - E_OS_ACCESS (Extended) Attempt to get a resource which is
 *            already occupied by any task or ISR, or the statically assigned
 *            priority of the calling task or interrupt routine is higher than
 *            the calculated ceiling priority.
 *  
 */
FUNC(StatusType, OS_CODE)
  GetResource
(
  VAR(ResourceType, AUTOMATIC) ResID
);

/**
 *  \brief Releases a resource previously locked with GetResource.
 *  \ingroup primitives-resource
 *  
 *  ReleaseResource() is used to release a resource locked using
 *  GetResource(), closing a critical section.
 *  
 *  For information on nested critical sections, see GetResource().
 *  The service may be called from an ISR and from task level.
 *  
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.5.3.2
 * 
 *  \param [in] ResID The resource to lock.
 *  \return The function returns a StatusType.
 *          - E_OK No error
 *          - E_OS_ID (Extended) ResID is an invalid identifier
 *          - E_OS_NOFUNC (Extended) Attempt to release a resource which
 *            is not occupied by any task or ISR, or another resource shall be
 *            released before.
 *          - E_OS_ACCESS (Extended) Attempt to release a resource which
 *            has a lower ceiling priority than the statically assigned
 *            priority of the calling task or interrupt routine.
 */
FUNC(StatusType, OS_CODE)
  ReleaseResource
(
  VAR(ResourceType, AUTOMATIC) ResID
);
#endif /* OSEE_HAS_RESOURCES */

#if (defined(OSEE_HAS_ALARMS))
/**
 *  \brief Arm the alarm based on a relative counter value.
 *  \ingroup primitives-alarm
 *  
 *  After _increment_ ticks have elapsed, the _AlarmID_
 *  notification is executed.
 *  
 *  If the relative value _increment_ is very small, the alarm may
 *  expire, and the notification can be executed before the system
 *  service returns to the user.  If _cycle_ is unequal zero, the
 *  alarm element is logged on again immediately after expiry with the
 *  relative value _cycle_.
 *  
 *  The alarm _AlarmID_ must not already be in use.  To change
 *  values of alarms already in use the alarm shall be canceled
 *  first.
 *  
 *  If the alarm is already in use, this call will be ignored and the
 *  error E_OS_STATE is returned.  Allowed on task level and
 *  in ISR, but not in hook routines.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.7.3.3
 * 
 *  \param [in] AlarmID Alarm identifier.
 *  \param [in] increment Relative value in ticks representing the offset
 *              with respect to the current time of the first alarm expiration.
 *  \param [in] cycle Cycle value in case of cyclic alarm. In case of
 *              single alarms, this parameter must be set to 0.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_STATE Alarm is already in use.
 *          - E_OS_ID (Extended) reference AlarmID is invalid.
 *          - E_OS_VALUE Value of _increment_ equal to 0.
 *          - E_OS_VALUE (Extended) Value of _increment_ outside of
 *            the admissible limits, or value of _cycle_ unequal to 0 and
 *            outside of the admissible counter limits.
 */
FUNC(StatusType, OS_CODE)
  SetRelAlarm
(
  VAR(AlarmType, AUTOMATIC) AlarmID,
  VAR(TickType, AUTOMATIC)  increment,
  VAR(TickType, AUTOMATIC)  cycle
);

/**
 *  \brief Arm the alarm based on a absolute counter value.
 *  \ingroup primitives-alarm
 *  
 *  The primitive occupies the alarm _AlarmID_ element. When
 *  _start_ ticks are reached, the _AlarmID_ notification is
 *  executed.
 *  
 *  If the absolute value _start_ is equal to the actual counter
 *  value, the alarm not expire immediately but will expire the next
 *  time the counter will reach the _start_ value.
 *  
 *  If _cycle_ is unequal zero, the alarm element is logged on
 *  again immediately after expiry with the relative value _cycle_.
 *  
 *  The alarm _AlarmID_ shall not already be in use.  To change
 *  values of alarms already in use the alarm shall be canceled
 *  first.  If the alarm is already in use, this call will be ignored
 *  and the error E_OS_STATE is returned.  Allowed on task
 *  level and in ISR, but not in hook routines.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.7.3.4
 * 
 *  \param [in] AlarmID Alarm identifier.
 *  \param [in] start Absolute value in ticks representing the absolute offset
 *              of the first alarm expiration.
 *  \param [in] cycle Cycle value in case of cyclic alarm. In case of
 *              single alarms, this parameter must be set to 0.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_STATE Alarm is already in use.
 *          - E_OS_ID (Extended) reference AlarmID is invalid.
 *          - E_OS_VALUE (Extended) Value of _increment_ outside of
 *            the admissible limits, or value of _cycle_ unequal to 0 and
 *            outside of the admissible counter limits.
 */
FUNC(StatusType, OS_CODE)
  SetAbsAlarm
(
  VAR(AlarmType, AUTOMATIC) AlarmID,
  VAR(TickType, AUTOMATIC)  start,
  VAR(TickType, AUTOMATIC)  cycle
);

/**
 *  \brief Returns relative tick value before alarm expiration.
 *  \ingroup primitives-alarm
 *  
 *  The system service GetAlarm() returns the relative value in ticks
 *  before the alarm AlarmID expires. If AlarmID is not in
 *  use, Tick has an undefined value. Allowed on task level, ISR,
 *  and in several hook routines.
 *  
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.7.3.2
 * 
 *  \param [in] AlarmID Alarm identifier.
 *  \param [out] Tick Relative value in ticks before the alarm expires.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_NOFUNC AlarmID is not used.
 *          - E_OS_ID (Extended) Reference AlarmID is invalid.
 */
FUNC(StatusType, OS_CODE)
  GetAlarm
(
  VAR(AlarmType, AUTOMATIC)   AlarmID,
  VAR(TickRefType, AUTOMATIC) Tick
);

/**
 *  \brief Returns the alarm base characteristics.
 *  \ingroup primitives-alarm
 *  
 *  Returns the alarm base characteristics. The return value Info
 *  is a structure in which the information of data type
 *  AlarmBaseType is stored.
 *  
 *  Allowed on task level, ISR, and in several hook routines.
 *  
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.7.3.1
 * 
 *  \param [in] AlarmID Alarm identifier.
 *  \param [out] Info Reference to the structure containing the constants
 *               that define the alarm base.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_ID (Extended) Reference AlarmID is invalid.
 */
FUNC(StatusType, OS_CODE)
  GetAlarmBase
(
  VAR(AlarmType, AUTOMATIC)         AlarmID,
  VAR(AlarmBaseRefType, AUTOMATIC)  Info
);


/**
 *  \brief Cancels an active alarm.
 *  \ingroup primitives-alarm
 *  
 *  The primitive cancels the alarm _AlarmID_. Allowed on task
 *  level and in ISR, but not in hook routines.
 *  
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.7.3.5
 * 
 *  \param [in] AlarmID Alarm identifier.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_NOFUNC AlarmID not in use.
 *          - E_OS_ID (Extended) Reference AlarmID is invalid.
 */
FUNC(StatusType, OS_CODE)
  CancelAlarm
(
  VAR(AlarmType, AUTOMATIC) AlarmID
);

#endif /* OSEE_HAS_ALARMS */

#if (defined(OSEE_HAS_EVENTS))
	
/**
 *  \brief The calling task waits for one of the events in the Mask.
 *  \ingroup primitives-event
 *  
 *  The calling task blocks if none of the events specified in
 *  Mask are set.
 *  
 *  If the calling task blocks, the system is reschedule, and the
 *  Internal resource of the task is released. This service shall only
 *  be called from the extended task owning the events.
 *  
 *  Conformance Classes: ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.6.3.4
 * 
 *  \param [in] Mask Mask of the event waited for.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_ACCESS (Extended) Task TaskID is not an extended task.
 *          - E_OS_RESOURCE (Extended) Calling task occupies resources.
 *          - E_OS_CALLLEVEL (Extended) Call at interrupt level.
 */
FUNC(StatusType, OS_CODE)
  WaitEvent
(
  VAR(EventMaskType, AUTOMATIC) Mask
);

/**
 *  \brief Set an event mask on an extended task.
 *  \ingroup primitives-event
 *  
 *  The events of task TaskID are set according to the event mask
 *  Mask. The call to SetEvent() may cause TaskID to
 *  wakeup from a WaitEvent() primitive. Any events not set in
 *  the event mask remain unchanged.  The service may be called from
 *  an interrupt service routine and from the task level, but not from
 *  hook routines.
 *  
 *  The function can be called from the idle hook.
 *  
 *  Conformance Classes: ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.6.3.1
 * 
 *  \param [in] TaskID The extended task on which we will set the event mask.
 *  \param [in] Mask The mask of the extended task.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_ID (Extended) Reference TaskID is invalid.
 *          - E_OS_ACCESS (Extended) Task TaskID is not an extended task.
 *          - E_OS_STATE (Extended) Events can not be set as the
 *            referenced task is in the SUSPENDED state.
 */
FUNC(StatusType, OS_CODE)
  SetEvent
(
  VAR(TaskType,      AUTOMATIC) TaskID,
  VAR(EventMaskType, AUTOMATIC) Mask
);


/**
 *  \brief returns the current event mask of an extended task.
 *  \ingroup primitives-event
 *  
 *  This primitive returns the current state of all event bits of the
 *  task TaskID.  The service may be called from interrupt
 *  service routines, task level and some hook routines.  The current
 *  status of the event mask of task TaskID is copied to
 *  Event.  The referenced task shall be an extended task.
 *
 *  Conformance Classes: ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.6.3.3
 * 
 *  \param [in] TaskID The extended task whose mask is to be returned.
 *  \param [out] Event The mask of the extended task.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_ID (Extended) Reference TaskID is invalid.
 *          - E_OS_ACCESS (Extended) Task TaskID is not an extended task.
 *          - E_OS_STATE (Extended) Events can not be read as the
 *            referenced task is in the SUSPENDED state.
 */
FUNC(StatusType, OS_CODE)
  GetEvent
(
  VAR(TaskType, AUTOMATIC)          TaskID,
  VAR(EventMaskRefType, AUTOMATIC)  Event
);

/**
 *  \brief Clears the events of the calling task.
 *  \ingroup primitives-event
 *  
 *  ClearEvent() clears the events Mask of the calling task.
 *  
 *  This system call is restricted to extended tasks which own the event.
 *
 *  Conformance Classes: ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.6.3.2
 * 
 *  \param [in] Mask Event Mask to be cleared.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_ACCESS (Extended) The service has been invoked by a
 *            non-extended task.
 *          - E_OS_CALLEVEL (Extended) The service has been invoked at
 *            the interrupt level.
 */
FUNC(StatusType, OS_CODE)
  ClearEvent
(
  VAR(EventMaskType, AUTOMATIC) Mask
);
#endif /* OSEE_HAS_EVENTS */

#if (defined(OSEE_HAS_ERRORHOOK))
/**
 *  \brief Hook called when there is an error inside a primitive.
 *  \ingroup primitives-hook
 *  
 *  When configured in the OIL File, the system calls this callback
 *  every time the return value of a function is different from
 *  _E_OK_. The application can then get additional informations
 *  using the OSErrorGetServiceId() macro, that returns the
 *  function that is generating the Error. Once the function that
 *  generated the error is known, the application can also access the
 *  parameters that generated the error using the _OSError_XXX_YYY()_
 *  macros, where _XXX_ is the name of the function, and _YYY_
 *  is the name of the parameter passed to the function.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.9.2.1
 * 
 *  \param [in] Error The error which triggered the call.
 */
FUNC(void, OS_CODE)
  ErrorHook
(
  VAR(StatusType, AUTOMATIC) Error
);
#endif /* OSEE_HAS_ERRORHOOK */

#if (defined(OSEE_HAS_STARTUPHOOK))
/**
 *  \brief Called inside StartOS().
 *  \ingroup primitives-hook
 *  
 *  When configured in the OIL File, this hook function is called
 *  inside StartOS(). Inside this callback, the Application can
 *  call the Operating System-related functions ActivateTask(),
 *  SetRelAlarm(), and SetAbsAlarm(). Please note that the
 *  simplest way to activate a task or set an alarm at startup is to
 *  specify their initial activation/setting inside the OIL File.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.9.2.4
 *  
 */
FUNC(void, OS_CODE)
  StartupHook(void);
#endif /* OSEE_HAS_STARTUPHOOK */

#if (defined(OSEE_HAS_PRETASKHOOK))
/**
 *  \brief Called everytime a task becomes running.
 *  \ingroup primitives-hook
 *  
 *  When configured in the OIL File, this hook function is called
 *  every time a task becomes the RUNNING task due to the call
 *  of other functions, or due to the preemption done by
 *  interrupts. The ID of the task which has just become the
 *  RUNNING task can be read using the GetTaskID()
 *  function.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.9.2.2
 */
FUNC(void, OS_CODE)
  PreTaskHook(void);
#endif /* OSEE_HAS_PRETASKHOOK */

#if (defined(OSEE_HAS_POSTTASKHOOK))
/**
 *  \brief Called everytime a task is no more the running task.
 *  \ingroup primitives-hook
 *  
 *  When configured in the OIL File, this hook function is called
 *  every time a task is no more the RUNNING task due to the
 *  call of other functions, or due to the preemption done by
 *  interrupts. The ID of the task which has just finished to be the
 *  RUNNING task can be read using the GetTaskID()
 *  function.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.9.2.3
 */
FUNC(void, OS_CODE)
  PostTaskHook(void);
#endif /* OSEE_HAS_POSTTASKHOOK */

#if (defined(OSEE_HAS_SHUTDOWNHOOK))
/**
 *  \brief Hook called inside ShutdownOS().
 *  \ingroup primitives-hook
 *  
 *  When configured in the OIL File, this hook function is called
 *  inside ShutdownOS(). Inside this callback, the Application
 *  can implement application dependent shutdown functions.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: OSEK OS - ISO 17356-3 - 13.9.2.5
 *  
 *  \param [in] Error this is the Error condition originally passed to
 *              ShutdownOS().
 */
FUNC(void, OS_CODE)
  ShutdownHook
(
  VAR(StatusType, AUTOMATIC) Error
);
#endif /* OSEE_HAS_SHUTDOWNHOOK */

#if (defined(OSEE_HAS_COUNTERS))

/**
 *  \brief Reads a counter value.
 *  \ingroup primitives-alarm
 *  
 *  This service reads the current count value of a counter returning 
 *  or the software ticks.
 *
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: AUTOSAR OS - SWS_Os_00383
 * 
 *  \param [in] CounterID The counter whose tick value should be read.
 *  \param [out] Value The value read from the Counter
 *  \return The function returns a StatusType.
 *          - E_OK No Error.
 *          - E_OS_ID (Extended) Reference CounterID is invalid.
 */	
FUNC(StatusType, OS_CODE)
  GetCounterValue
(
  VAR(CounterType, AUTOMATIC) CounterID,
  VAR(TickRefType, AUTOMATIC) Value
);

/**
 *  \brief Gets the number of ticks since the last read.
 *  \ingroup primitives-alarm
 *  
 *  This service gets the number of ticks between the current tick value and a
 *  previously read tick value.
 *  If the timer already passed the _Value_ value a second (or multiple) time,
 *  the result returned is wrong.
 *  The reason is that the service can not detect such a relative overflow.
 *	
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: AUTOSAR OS - SWS_Os_00392
 * 
 *  \param [in] CounterID The Counter which tick value should be read.
 *  \param [out] Value Contains the previously read tick value the counter.
 *  \param [out] ElapsedValue Will contains the difference to the previous 
 *               value.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_ID (Extended) Reference CounterID is invalid.
 *          - E_OS_VALUE (Extended) The given Value is invalid.
 */
FUNC(StatusType, OS_CODE)
  GetElapsedValue
(
  VAR(CounterType, AUTOMATIC) CounterID,
  VAR(TickRefType, AUTOMATIC) Value,
  VAR(TickRefType, AUTOMATIC) ElapsedValue
);

/**
 *  \brief Increment a software counter.
 *  \ingroup primitives-alarm
 *  
 *  This function receives a counter identifier as parameter, and it
 *  increments it by 1. This function is typically called inside an
 *  ISR type 2 or inside a task to notify that the trigger the counter
 *  is counting has happened.
 *  
 *  The function also implements the notification of expired alarms,
 *  that is implemented, depending on the alarm configuration, as:
 *  
 *  - an alarm callback function;
 *  - a task activation;
 *  - an event mask set on an extended task.
 *  
 *  The function is atomic, and a reschedule will happen at the end if
 *  the primitive is called at task level. If called at ISR level, the
 *  reschedule will happen at the end of the outermost nested IRQ.
 * 
 *  Conformance Classes: BCC1, BCC2, ECC1, ECC2
 *  
 *  Reference: AUTOSAR OS SWS_Os_00301
 * 
 *  \param [in] CounterID The counter.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_ID (Extended) CounterID is invalid or counter
 *            is implemented in hardware and can not be incremented by
 *            software.
 */
FUNC(StatusType, OS_CODE)
  IncrementCounter
(
  VAR(CounterType, AUTOMATIC) CounterID
);
#endif /* OSEE_HAS_COUNTERS */

#if (defined(OSEE_HAS_SCHEDULE_TABLES))
/**
 *  \brief Starts a Schedule Table with a relative offset.
 *  \ingroup primitives-schtable 
 *
 *  This service starts the processing of a schedule table at "Offset"
 *  relative to the "Now" value on the underlying counter.
 *  
 *  Sync/Async: Synchronous
 *  
 *  Reentrancy: Reentrant
 *
 *  Reference: AUTOSAR OS 8.4.9 StartScheduleTableRel [SWS_Os_00347]
 *  
 *  \param [in] ScheduleTableID Schedule table to be started.
 *  \param [in] Offset Number of ticks on the counter before the the schedule
 *              table processing is started
 *
 *  \return The function returns a StatusType.
 *          - E_OK No Error.
 *          - E_OS_ID (Extended) ScheduleTableID not valid.
 *          - E_OS_VALUE (Extended) Offset is greater than
 *            (OsCounterMaxAllowedValue - InitialOffset) or is equal to 0.
 *          - E_OS_STATE Schedule table was already started.
 */
FUNC(StatusType, OS_CODE)
  StartScheduleTableRel
(
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID,
  VAR(TickType, AUTOMATIC)          Offset
);

/**
 *  \brief Starts a Schedule Table at an absolute counter value.
 *  \ingroup primitives-schtable 
 *
 *  This service starts the processing of a schedule table at an absolute
 *  value "Start" on the underlying counter.
 *  
 *  Sync/Async: Synchronous
 *  
 *  Reentrancy: Reentrant
 *
 *  Reference: AUTOSAR OS 8.4.10 StartScheduleTableAbs [SWS_Os_00358]
 *  
 *  \param [in] ScheduleTableID: Schedule table to be started
 *  \param [in] Start: Absolute counter tick value at which the schedule table
 *              is started
 *
 *  \return The function returns a StatusType.
 *          - E_OK No Error.
 *          - E_OS_ID (Extended) ScheduleTableID not valid.
 *          - E_OS_VALUE (Extended) "Start" is greater than
 *            OsCounterMaxAllowedValue.
 *          - E_OS_STATE Schedule table was already started.
 */
FUNC(StatusType, OS_CODE)
  StartScheduleTableAbs
(
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID,
  VAR(TickType, AUTOMATIC)          Start
);

/** 
 *  \brief Stops a Schedule Table.
 *  \ingroup primitives-schtable 
 *
 *  This service cancels the processing of a schedule table immediately
 *  at any point while the schedule table is running.
 *  
 *  Sync/Async: Synchronous
 *  
 *  Reentrancy: Reentrant
 *
 *  Reference: AUTOSAR OS 8.4.11 StopScheduleTable [SWS_Os_00006]
 *  
 *  \param [in] ScheduleTableID: Schedule table to be stopped
 *
 *  \return The function returns a StatusType.
 *          - E_OK No Error
 *          - E_OS_ID (Extended) ScheduleTableID not valid.
 *          - E_OS_NOFUNC Schedule table was already stopped.
 */
FUNC(StatusType, OS_CODE)
  StopScheduleTable
(
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID
);

/**
 *  \brief Queries the state of a schedule table.
 *  \ingroup primitives-schtable 
 *
 *  This service queries the state of a schedule table (also with respect
 *  to synchronization).
 *  
 *  Sync/Async: Synchronous
 *  
 *  Reentrancy: Reentrant
 *
 *  Reference: AUTOSAR OS 8.4.16 GetScheduleTableStatus [SWS_Os_00227] 
 *             (SRS_Os_11002)
 *  
 *  \param [in] ScheduleTableID Schedule table for which status is requested.
 *  \param [out] ScheduleStatus: Reference to ScheduleTableStatusType.
 *
 *  \return The function returns a StatusType.
 *          - E_OK No Error
 *          - E_OS_ID (Extended) Invalid ScheduleTableID
 */
FUNC(StatusType, OS_CODE)
  GetScheduleTableStatus
(
  VAR(ScheduleTableType, AUTOMATIC)           ScheduleTableID,
  VAR(ScheduleTableStatusRefType, AUTOMATIC)  ScheduleStatus
);

/**
 *  \brief Switches to another Schedule table.
 *  \ingroup primitives-schtable 
 *
 *  This service switches the processing from one schedule table to
 *  another schedule table
 *  
 *  Sync/Async: Synchronous
 *  
 *  Reentrancy: Reentrant
 *
 *  Reference: AUTOSAR OS 8.4.12 NextScheduleTable [SWS_Os_00191] (SRS_Os_00099)
 *
 *  \param [in] ScheduleTableID_From Currently processed schedule table
 *  \param [in] ScheduleTableID_To Schedule table that provides its series of
 *    expiry points
 *
 * \return The function returns a StatusType.
 *         - E_OK No error
 *         - E_OS_ID (Extended) ScheduleTableID_From or
 *           ScheduleTableID_To not valid.
 *         - E_OS_NOFUNC ScheduleTableID_From not started
 *         - E_OS_STATE ScheduleTableID_To is started or next
 */
FUNC(StatusType, OS_CODE)
  NextScheduleTable
(
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID_From,
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID_To
);

/**
 *  \brief Starts synchronization of a Schedule Table.
 *  \ingroup primitives-schtable 
 *
 *  This service provides the schedule table with a synchronization
 *  count and start synchronization.
 *  
 *  Sync/Async: Synchronous
 *  
 *  Reentrancy: Reentrant
 *
 *  Reference: AUTOSAR OS 8.4.14 SyncScheduleTable [SWS_Os_00199] (SRS_Os_11002)
 *  
 *  \param [in] ScheduleTableID Schedule table to be synchronized
 *  \param [in] Value The current value of the synchronization counter
 *
 *  \return The function returns a StatusType.
 *          - E_OK No errors
 *          - E_OS_ID (Extended) The ScheduleTableID was not valid or
 *            schedule table can not be synchronized (OsScheduleTblSyncStrategy
 *            not set or OsScheduleTblSyncStrategy = IMPLICIT)
 *          - E_OS_VALUE (Extended) The ''Value'' is out of range.
 *          - E_OS_STATE The state of schedule table ''ScheduleTableID'' is equal
 *            to SCHEDULETABLE_STOPPED
 */
FUNC(StatusType, OS_CODE)
  SyncScheduleTable
(
  VAR(ScheduleTableType, AUTOMATIC) ScheduleTableID,
  VAR(TickType, AUTOMATIC)          Value
);


/*  (not yet supported)
 *  \brief This service starts an explicitly synchronized schedule table
 *    synchronously.
 *  \ingroup primitives-schtable 
 *
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *
 *  Reference: AUTOSAR OS 8.4.13 StartScheduleTableSynchron [SWS_Os_00201]
 *             (SRS_Os_11002)
 *  
 *  \param [in] ScheduleTableID Schedule table to be started
 *
 *  \return This function returns a StatusType.
 *          - E_OK No Error
 *          - E_OS_ID (Extended) ScheduleTableID not valid
 *          - E_OS_STATE Schedule table was already started Description:
 */

/*  (not yet supported)
 *  \brief This service stops synchronization of a schedule table.
 *  \ingroup primitives-schtable 
 *
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *
 *  Reference: AUTOSAR OS 8.4.15 SetScheduleTableAsync [SWS_Os_00422]
 *
 *  \param [in] ScheduleTableID Schedule table for which status is requested
 *
 *  \return This function returns a StatusType.
 *          - E_OK No Error
 *          - E_OS_ID (Extended) Invalid ScheduleTableID
 */
#endif /* OSEE_HAS_SCHEDULE_TABLES */


/**
 *  \brief Gets the ID of the running ISR
 *  \ingroup primitives-interrupt
 *  
 *  If called inside an ISR2, it returns the ID of the current executing ISR.
 *  
 *  Reference: AUTOSAR OS 8.4.3 GetISRID [SWS_Os_00511]
 *  
 *  \return This function returns a ISRType which is the current executing ISR
 *          or INVALID_ISR if called outside an ISR Routine (or Hooks called 
 *          inside an ISR2 routine).
 */
 FUNC(ISRType, OS_CODE)
  GetISRID
(
  void
);

#if (!defined(OSEE_SINGLECORE))
/**
 *  \brief Gets the ID of the running core
 *  \ingroup primitives-multicore
 *  
 *  This function returns the logical core on which the function is being called
 *  
 *  Reference: AUTOSAR OS 8.4.24 GetCoreID [SWS_Os_00674]
 *  
 *  \return This function returns a CoreIdType which is the current core where
 *          the function is being called.
 */
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

/**
 *  \brief Returns the number of cores.
 *  \ingroup primitives-multicore
 *  
 *  This function returns the number of cores of the configuration.
 *  
 *  Please note that the returned type is CoreNumType and not uint32 as in 
 *  the AUTOSAR OS specification.
 *  
 *  Reference: AUTOSAR OS 8.4.23 GetNumberOfActivatedCores [SWS_Os_00672]
 *  
 *  \return This function returns a CoreIdType which is the current core where
 *          the function is being called.
 */
/* FIXME: from specification return value should be uint32 */
FUNC(CoreNumType, OS_CODE)
  GetNumberOfActivatedCores
(
  void
);

/**
 *  \brief Starts the core specified as parameter.
 *  \ingroup primitives-multicore
 *  
 *  This function starts the core specified as parameter.
 *  
 *  The function shall be called before StartOS. the activated core must 
 *  call StartOS() once activated.
 *  
 *  Reference: AUTOSAR OS 8.4.25 StartCore [SWS_Os_00676]
 *  
 *  \param [in] CoreID The core to be activated
 *  \param [out] Status The status returned by the function:
 *                      - E_OK No Error
 *                      - E_OS_ID  Core ID is invalid
 *                      - E_OS_ACCESS The function was called after starting 
 *                                    the OS.
 *                      - E_OS_STATE The Core is already activated.
 */
 FUNC(void, OS_CODE)
  StartCore
(
  VAR(CoreIdType, AUTOMATIC)                  CoreID,
  P2VAR(StatusType, AUTOMATIC, OS_APPL_DATA)  Status
);


/**
 *  \brief Starts the core specified as parameter.
 *  \ingroup primitives-multicore
 *  
 *  This function starts the core specified as parameter.
 *  
 *  It is allowed to call the function after StartOS(). the activated core must 
 *  call StartOS() once activated.
 *  
 *  Reference: AUTOSAR OS 8.4.26 StartNonAutosarCore [SWS_Os_00682]
 *  
 *  \param [in] CoreID The core to be activated
 *  \param [out] Status The status returned by the function:
 *                      - E_OK No Error
 *                      - E_OS_ID  Core ID is invalid
 *                      - E_OS_STATE The Core is already activated.
 */
FUNC(void, OS_CODE)
  StartNonAutosarCore
(
  VAR(CoreIdType, AUTOMATIC)                  CoreID,
  P2VAR(StatusType, AUTOMATIC, OS_APPL_DATA)  Status
);


/**
 *  \brief Shut down all cores.
 *  \ingroup primitives-multicore
 *  
 *  This function shut down the calling core. it never returns. it also forces 
 *  all other cores to shut down.
 *  
 *  Reference: AUTOSAR OS 8.4.30 ShutdownAllCores [SWS_Os_00713]
 *  
 *  \param [in] Error The error to be passed to the ShutdownHook()
 */
FUNC(void, OS_CODE) 
  ShutdownAllCores
(
  VAR(StatusType, AUTOMATIC)  Error
);

#if (defined(OSEE_HAS_SPINLOCKS))
/**
 *  \brief Lock a spin-lock variable.
 *  \ingroup primitives-multicore
 *  
 *  This function locks a spin-lock (which is an active wait used to implement
 *  mutual exclusions on multicores). The primitive does not implementa a 
 *  preemption.
 *  
 *  Reference: AUTOSAR OS 8.4.27 StartNonAutosarCore [SWS_Os_00686]
 *  
 *  \param [in] SpinlockID The spin lock to be locked
 *  
 *  \return The function returns a StatusType.
 *          - E_OK No Error
 *          - E_OS_ID (Extended) The spin lock is invalid
 *          - E_OS_INTERFERENCE_DEADLOCK (Extended) Lock already taken on the 
 *            same core.
 *          - E_OS_NESTING_DEADLOCK (Extended) another Task on the same core 
 *            is taking another spinlock
 *          - E_OS_ACCESS (Extended) The spin lock cannot be accessed
 */
FUNC(StatusType, OS_CODE)
  GetSpinlock
(
  VAR(SpinlockIdType, AUTOMATIC) SpinlockID
);

/**
 *  \brief Releases a spin-lock variable.
 *  \ingroup primitives-multicore
 *  
 *  This function releases a spin-lock which was previously locked.
 *  
 *  All spin locks must be released before terminating or before calling
 *  WaitEvent().
 *  
 *  Reference: AUTOSAR OS 8.4.28 ReleaseSpinlock [SWS_Os_00695]
 *  
 *  \param [in] SpinlockID The spin lock to be locked
 *  
 *  \return The function returns a StatusType.
 *          - E_OK No Error.
 *          - E_OS_ID (Extended) The spin lock is invalid.
 *          - E_OS_STATE (Extended) The spin lock is not occupied by the calling
 *            task.
 *          - E_OS_ACCESS (Extended) The spin lock cannot be accessed.
 *          - E_OS_NOFUNC (Extended) Another spinlock has to be released before.
 */
FUNC(StatusType, OS_CODE)
  ReleaseSpinlock
(
  VAR(SpinlockIdType, AUTOMATIC) SpinlockID
);


/**
 *  \brief Lock a spin-lock variable, without active waiting.
 *  \ingroup primitives-multicore
 *  
 *  This function locks a spin-lock in a similar way to GetSpinlock(), but it 
 *  does it without an active loop. The result of the first check is returned
 *  in the Success parameter.
 *  
 *  Reference: AUTOSAR OS 8.4.29 TryToGetSpinlock [SWS_Os_00703]
 *  
 *  \param [in] SpinlockID The spin lock to be locked
 *  \param [out] Success The result of the trylock operation
 *  
 *  \return The function returns a StatusType.
 *          - E_OK No Error
 *          - E_OS_ID (Extended) The spin lock is invalid
 *          - E_OS_INTERFERENCE_DEADLOCK (Extended) Lock already taken on the 
 *            same core.
 *          - E_OS_NESTING_DEADLOCK (Extended) another Task on the same core 
 *            is taking another spinlock
 *          - E_OS_ACCESS (Extended) The spin lock cannot be accessed
 */
 FUNC(StatusType, OS_CODE)
  TryToGetSpinlock
(
  VAR(SpinlockIdType, AUTOMATIC)                        SpinlockID,
  P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_APPL_DATA)  Success
);
#endif /* OSEE_HAS_SPINLOCKS */
#endif /* !OSEE_SINGLECORE */

#if (defined(OSEE_USEGETSERVICEID)) || (defined(OSEE_USEPARAMETERACCESS))

/**
 *  \brief Used internally to get the current service ID. Not to be called 
 *         directly in user code.
 *  \ingroup primitives-hook
 *  \return The function returns the last primitive called in the current core.
 */
FUNC(OSServiceIdType, OS_CODE)
  osEE_get_service_id
(
  void
);

/**
 *  \brief Used to get the current service ID.
 *  \ingroup primitives-hook
 *  \return The function returns the last primitive called in the current core.
 */
#define OSErrorGetServiceId() osEE_get_service_id()

#endif /* OSEE_USEGETSERVICEID || OSEE_USEPARAMETERACCESS */
#if (defined(OSEE_USEPARAMETERACCESS))
/**
 *  \brief Used internally to implement the ErrorHook() macros. Not to be called
 *         directly in user code.
 *  \ingroup primitives-hook
 *  \return The function returns a OsEE_api_param, which is a union containing
 *          the first parameter value.
 */
FUNC(OsEE_api_param, OS_CODE)
  osEE_get_api_param1
(
  void
);

/**
 *  \brief Used internally to implement the ErrorHook() macros. Not to be called
 *         directly in user code.
 *  \ingroup primitives-hook
 *  \return The function returns a OsEE_api_param, which is a union containing 
 *          the second parameter value.
 */
FUNC(OsEE_api_param, OS_CODE)
  osEE_get_api_param2
(
  void
);

/**
 *  \brief Used internally to implement the ErrorHook() macros. Not to be called
 *         directly in user code.
 *  \ingroup primitives-hook
 *  \return The function returns a OsEE_api_param, which is a union containing
 *          the third parameter value.
*/
FUNC(OsEE_api_param, OS_CODE)
  osEE_get_api_param3
(
  void
);

/**
 *  \brief This macro returns the TaskID parameter passed to ActivateTask().
 *  \ingroup primitives-hook
 */
#define OSError_ActivateTask_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the TaskID parameter passed to ChainTask().
 *  \ingroup primitives-hook
 */
#define OSError_ChainTask_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the TaskID parameter passed to GetTaskID().
 *  \ingroup primitives-hook
 */
#define OSError_GetTaskID_TaskID()\
  ((TaskRefType)osEE_get_api_param1().p_param)

/**
 *  \brief This macro returns the TaskID parameter passed to GetTaskState().
 *  \ingroup primitives-hook
 */
#define OSError_GetTaskState_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the State parameter passed to GetTaskState().
 *  \ingroup primitives-hook
 */
#define OSError_GetTaskState_State()\
  ((TaskRefType)osEE_get_api_param2().p_param)

/**
 *  \brief This macro returns the Error parameter passed to ShutdownOS().
 *  \ingroup primitives-hook
 */
#define OSError_ShutdownOS_Error()\
  ((StatusType)osEE_get_api_param1().num_param)

#if (defined(OSEE_HAS_RESOURCES))
/**
 *  \brief This macro returns the ResID parameter passed to GetResource().
 *  \ingroup primitives-hook
 */
#define OSError_GetResource_ResID()\
  ((ResourceType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the ResID parameter passed to ReleaseResource().
 *  \ingroup primitives-hook
 */
#define OSError_ReleaseResource_ResID()\
  ((ResourceType)osEE_get_api_param1().num_param)
#endif /* OSEE_HAS_RESOURCES */

#if (defined(OSEE_HAS_ALARMS))
/**
 *  \brief This macro returns the AlarmID parameter passed to GetAlarm().
 *  \ingroup primitives-hook
 */
#define OSError_GetAlarm_AlarmID()\
  ((AlarmType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the AlarmID parameter passed to GetAlarm().
 *  \ingroup primitives-hook
 */
#define OSError_CancelAlarm_AlarmID()\
  ((AlarmType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the AlarmID parameter passed to SetRelAlarm().
 *  \ingroup primitives-hook
 */
#define OSError_SetRelAlarm_AlarmID()\
  ((AlarmType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the increment parameter passed to SetRelAlarm().
 *  \ingroup primitives-hook
 */
#define OSError_SetRelAlarm_increment()\
  ((TickType)osEE_get_api_param2().num_param)

/**
 *  \brief This macro returns the cycle parameter passed to SetRelAlarm().
 *  \ingroup primitives-hook
 */
#define OSError_SetRelAlarm_cycle()\
  ((TickType)osEE_get_api_param3().num_param)

/**
 *  \brief This macro returns the AlarmID parameter passed to SetAbsAlarm().
 *  \ingroup primitives-hook
 */
#define OSError_SetAbsAlarm_AlarmID()\
  ((AlarmType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the start parameter passed to SetAbsAlarm().
 *  \ingroup primitives-hook
 */
#define OSError_SetAbsAlarm_start()\
  ((TickType)osEE_get_api_param2().num_param)

/**
 *  \brief This macro returns the cycle parameter passed to SetAbsAlarm().
 *  \ingroup primitives-hook
 */
#define OSError_SetAbsAlarm_cycle()\
  ((TickType)osEE_get_api_param3().num_param)

/**
 *  \brief This macro returns the AlarmID parameter passed to GetAlarmBase().
 *  \ingroup primitives-hook
 */
#define OSError_GetAlarmBase_AlarmID()\
  ((AlarmType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the Info parameter passed to GetAlarmBase().
 *  \ingroup primitives-hook
 */
#define OSError_GetAlarmBase_Info()\
  ((AlarmBaseRefType)osEE_get_api_param2().p_param)
#endif /* OSEE_HAS_ALARMS */

#if (defined(OSEE_HAS_EVENTS))
/**
 *  \brief This macro returns the Mask parameter passed to WaitEvent().
 *  \ingroup primitives-hook
 */
#define OSError_WaitEvent_Mask()\
  ((EventMaskType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the TaskID parameter passed to SetEvent().
 *  \ingroup primitives-hook
 */
#define OSError_SetEvent_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the Mask parameter passed to SetEvent().
 *  \ingroup primitives-hook
 */
#define OSError_SetEvent_Mask()\
  ((EventMaskType)osEE_get_api_param2().num_param)

/**
 *  \brief This macro returns the TaskID parameter passed to GetEvent().
 *  \ingroup primitives-hook
 */
#define OSError_GetEvent_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the Event parameter passed to GetEvent().
 *  \ingroup primitives-hook
 */
#define OSError_GetEvent_Event()\
  ((EventMaskRefType)osEE_get_api_param2().p_param)

/**
 *  \brief This macro returns the Mask parameter passed to ClearEvent().
 *  \ingroup primitives-hook
 */
#define OSError_ClearEvent_Mask()\
  ((EventMaskType)osEE_get_api_param1().num_param)
#endif /* OSEE_HAS_EVENTS */

#if (defined(OSEE_HAS_COUNTERS))
/**
 *  \brief This macro returns the CounterID parameter passed to 
 *         GetCounterValue().
 *  \ingroup primitives-hook
 */
#define OSError_GetCounterValue_CounterID()\
  ((CounterType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the Value parameter passed to GetCounterValue().
 *  \ingroup primitives-hook
 */
#define OSError_GetCounterValue_Value()\
  ((TickRefType)osEE_get_api_param2().p_param)

/**
 *  \brief This macro returns the CounterID parameter passed to 
 *         GetElapsedValue().
 *  \ingroup primitives-hook
 */
#define OSError_GetElapsedValue_CounterID()\
  ((CounterType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the Value parameter passed to GetElapsedValue().
 *  \ingroup primitives-hook
 */
#define OSError_GetElapsedValue_Value()\
  ((TickRefType)osEE_get_api_param2().p_param)

/**
 *  \brief This macro returns the ElapsedValue parameter passed to 
 *         GetElapsedValue().
 *  \ingroup primitives-hook
 */
#define OSError_GetElapsedValue_ElapsedValue()\
  ((TickRefType)osEE_get_api_param3().p_param)

/**
 *  \brief This macro returns the CounterID parameter passed to 
 *         IncrementCounter().
 *  \ingroup primitives-hook
 */
#define OSError_IncrementCounter_CounterID()\
  ((CounterType)osEE_get_api_param1().num_param)
#endif /* OSEE_HAS_COUNTERS */

#if (defined(OSEE_HAS_SCHEDULE_TABLES))
/**
 *  \brief This macro returns the ScheduleTableID parameter passed to 
 *         StartScheduleTableRel().
 *  \ingroup primitives-hook
 */
#define OSError_StartScheduleTableRel_ScheduleTableID()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the Offset parameter passed to 
 *         StartScheduleTableRel().
 *  \ingroup primitives-hook
 */
#define OSError_StartScheduleTableRel_Offset()\
  ((TickType)osEE_get_api_param2().num_param)

/**
 *  \brief This macro returns the ScheduleTableID parameter passed to 
 *         StartScheduleTableAbs().
 *  \ingroup primitives-hook
 */
#define OSError_StartScheduleTableAbs_ScheduleTableID()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the Start parameter passed to 
 *         StartScheduleTableAbs().
 *  \ingroup primitives-hook
 */
#define OSError_StartScheduleTableAbs_Start()\
  ((TickType)osEE_get_api_param2().num_param)

/**
 *  \brief This macro returns the ScheduleTableID parameter passed to 
 *         StopScheduleTable().
 *  \ingroup primitives-hook
 */
#define OSError_StopScheduleTable_ScheduleTableID()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the ScheduleTableID parameter passed to 
 *         GetScheduleTableStatus().
 *  \ingroup primitives-hook
 */
#define OSError_GetScheduleTableStatus_ScheduleTableID()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the ScheduleStatus parameter passed to 
 *         GetScheduleTableStatus().
 *  \ingroup primitives-hook
 */
#define OSError_GetScheduleTableStatus_ScheduleStatus()\
  ((ScheduleTableStatusRefType)osEE_get_api_param2().p_param)

/**
 *  \brief This macro returns the From parameter passed to NextScheduleTable().
 *  \ingroup primitives-hook
 */
#define OSError_NextScheduleTable_ScheduleTableID_From()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)
  
/**
 *  \brief This macro returns the To parameter passed to NextScheduleTable().
 *  \ingroup primitives-hook
 */
#define OSError_NextScheduleTable_ScheduleTableID_To()\
  ((ScheduleTableType)osEE_get_api_param2().num_param)

/**
 *  \brief This macro returns the ScheduleTableID parameter passed to 
 *         SyncScheduleTable().
 *  \ingroup primitives-hook
 */
#define OSError_SyncScheduleTable_ScheduleTableID()\
  ((ScheduleTableType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the Value parameter passed to SyncScheduleTable().
 *  \ingroup primitives-hook
 */
#define OSError_SyncScheduleTable_Value()\
  ((TickType)osEE_get_api_param2().num_param)
#endif /* OSEE_HAS_SCHEDULE_TABLES */

#if (defined(OSEE_HAS_SPINLOCKS))
/**
 *  \brief This macro returns the SpinlockID parameter passed to GetSpinlock().
 *  \ingroup primitives-hook
 */
#define OSError_GetSpinlock_SpinlockID()\
  ((SpinlockIdType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the SpinlockID parameter passed to 
 *         ReleaseSpinlock().
 *  \ingroup primitives-hook
 */
#define OSError_ReleaseSpinlock_SpinlockID()\
  ((SpinlockIdType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the SpinlockID parameter passed to 
 *         TryToGetSpinlock().
 *  \ingroup primitives-hook
 */
#define OSError_TryToGetSpinlock_SpinlockID()\
  ((SpinlockIdType)osEE_get_api_param1().num_param)

/**
 *  \brief This macro returns the Success parameter passed to 
 *         TryToGetSpinlock().
 *  \ingroup primitives-hook
 */
#define OSError_TryToGetSpinlock_Success()\
  ((TryToGetSpinlockType)osEE_get_api_param2().p_param)
#endif /* OSEE_HAS_SPINLOCKS */
#endif /* OSEE_USEPARAMETERACCESS */

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_API_OSEK_H_ */
