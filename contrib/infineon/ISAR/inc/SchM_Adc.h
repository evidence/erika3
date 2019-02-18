/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2018 Evidence s.r.l.
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

/** \brief	AUTOSAR BSW ADC Driver Schedule Manager Header File.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

#ifndef	SCHM_ADC_H
#define	SCHM_ADC_H

/******************************************************************************
 *			Includes					      *
 ******************************************************************************/

#include "Std_Types.h"
#include "McalOsConfig.h"
#include MCAL_OS_HEADER

/******************************************************************************
 *			Global Function Definitions			      *
 ******************************************************************************/

/** \brief	Adc_StartGroup() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_StartGroup(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_StartGroup() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_StartGroup(void)
{
  ResumeAllInterrupts();
}

/** \brief	Adc_StopGroup() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_StopGroup(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_StopGroup() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_StopGroup(void)
{
  ResumeAllInterrupts();
}

/** \brief	Adc_readGroup() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_ReadGroup(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_readGroup() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_ReadGroup(void)
{
  ResumeAllInterrupts();
}

/** \brief	Adc_EnableHwTrig() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_EnableHwTrig(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_EnableHwTrig() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_EnableHwTrig(void)
{
  ResumeAllInterrupts();
}

/** \brief	Adc_DisableHwTrig() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_DisableHwTrig(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_DisableHwTrig() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_DisableHwTrig(void)
{
  ResumeAllInterrupts();
}

/** \brief	Adc_GetGrpStatus() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_GetGrpStatus(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_GetGrpStatus() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_GetGrpStatus(void)
{
  ResumeAllInterrupts();
}

/** \brief	Adc_GetStreamLastPtr() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_GetStreamLastPtr(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_GetStreamLastPtr() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_GetStreamLastPtr(void)
{
  ResumeAllInterrupts();
}

/** \brief	Adc_ScheduleStart() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_ScheduleStart(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_ScheduleStart() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_ScheduleStart(void)
{
  ResumeAllInterrupts();
}

/** \brief	Adc_ScheduleStop() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_ScheduleStop(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_ScheduleStop() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_ScheduleStop(void)
{
  ResumeAllInterrupts();
}

/** \brief	Adc_ScheduleNext() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_ScheduleNext(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_ScheduleNext() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_ScheduleNext(void)
{
  ResumeAllInterrupts();
}

/** \brief	Adc_PushQueue() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_PushQueue(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_PushQueue() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_PushQueue(void)
{
  ResumeAllInterrupts();
}

/** \brief	Adc_PopQueue() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Adc_PopQueue(void)
{
  SuspendAllInterrupts();
}

/** \brief	Adc_PopQueue() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Adc_PopQueue(void)
{
  ResumeAllInterrupts();
}

#endif	/* SCHM_ADC_H */
