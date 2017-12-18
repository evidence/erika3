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

#if (!defined(OSEE_API_OSEK_H))
#define OSEE_API_OSEK_H

#include "ee_hal.h"
#include "ee_api_types.h"

#if (!defined(OSDEFAULTAPPMODE))
#define OSDEFAULTAPPMODE 0U
#endif /* !OSDEFAULTAPPMODE */

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

LOCAL_INLINE FUNC(CoreIdType, OS_CODE)
  GetCoreID
(
  void
)
{
  return  osEE_get_curr_core_id();
}

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

#if (defined(OSEE_USEPARAMETERACCESS))
FUNC(OSServiceIdType, OS_CODE)
  osEE_get_service_id
(
  void
);

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

#define OSErrorGetServiceId() osEE_get_service_id()

#define OSError_ActivateTask_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

#define OSError_ChainTask_TaskID()\
  ((TaskType)osEE_get_api_param1().num_param)

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

#define OSError_SetAbsAlarm_AlarmID()\
  ((AlarmType)osEE_get_api_param1().num_param)
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

#endif /* OSEE_USEPARAMETERACCESS */
#endif /* !OSEE_API_OSEK_H_ */
