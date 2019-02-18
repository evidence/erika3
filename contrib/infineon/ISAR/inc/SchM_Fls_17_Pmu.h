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

/** \brief	AUTOSAR BSW FLS Driver Schedule Manager Header File.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */
#ifndef	SCHM_FLS_17_PMU_H
#define	SCHM_FLS_17_PMU_H

/******************************************************************************
 *			Includes					      *
 ******************************************************************************/

#include "Std_Types.h"
#include "McalOsConfig.h"
#include MCAL_OS_HEADER

/******************************************************************************
 *			Global Macro Definitions			      *
 ******************************************************************************/

#define	FLS_EA_INIT		((uint8)0U)
#define	FLS_EA_WRITE		((uint8)1U)
#define	FLS_EA_ERASE		((uint8)2U)
#define	FLS_EA_WRITE_REPAIR	((uint8)3U)
#define	FLS_EA_MAIN		((uint8)4U)

/******************************************************************************
 *			Global Function Definitions			      *
 ******************************************************************************/

/** \brief	SchM_Enter_Fls_17_Pmu_Init() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Fls_17_Pmu_Init(void)
{
  SuspendAllInterrupts();
}

/** \brief	SchM_Exit_Fls_17_Pmu_Init() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Fls_17_Pmu_Init(void)
{
  ResumeAllInterrupts();
}

/** \brief	SchM_Enter_Fls_17_Pmu_Erase() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Fls_17_Pmu_Erase(void)
{
  SuspendAllInterrupts();
}

/** \brief	SchM_Exit_Fls_17_Pmu_Erase() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Fls_17_Pmu_Erase(void)
{
  ResumeAllInterrupts();
}

/** \brief	SchM_Enter_Fls_17_Pmu_Write() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Fls_17_Pmu_Write(void)
{
  SuspendAllInterrupts();
}

/** \brief	SchM_Exit_Fls_17_Pmu_Write() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Fls_17_Pmu_Write(void)
{
  ResumeAllInterrupts();
}

/** \brief	SchM_Enter_Fls_17_Pmu_Main() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Fls_17_Pmu_Main(void)
{
  SuspendAllInterrupts();
}

/** \brief	SchM_Exit_Fls_17_Pmu_Main() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Fls_17_Pmu_Main(void)
{
  ResumeAllInterrupts();
}

/** \brief	SchM_Enter_Fls_17_Pmu_ResumeErase() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Fls_17_Pmu_ResumeErase(void)
{
  SuspendAllInterrupts();
}

/** \brief	SchM_Exit_Fls_17_Pmu_ResumeErase() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE)SchM_Exit_Fls_17_Pmu_ResumeErase(void)
{
  ResumeAllInterrupts();
}

#endif	/* SCHM_FLS_H */
