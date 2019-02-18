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

/** \brief	AUTOSAR BSW PWM Driver Schedule Manager Header File.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */
#ifndef	SCHM_SPI_H
#define	SCHM_SPI_H

/******************************************************************************
 *			Includes					      *
 ******************************************************************************/

#include "Std_Types.h"
#include "McalOsConfig.h"
#include MCAL_OS_HEADER

/******************************************************************************
 *			Global Function Definitions			      *
 ******************************************************************************/

/** \brief	Spi_WriteIB() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Spi_WriteIB(void)
{
  SuspendAllInterrupts();
}

/** \brief	Pwm_WriteIB() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Spi_WriteIB(void)
{
  ResumeAllInterrupts();
}

/** \brief	Spi_AsyncTransmit() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Spi_AsyncTransmit(void)
{
  SuspendAllInterrupts();
}

/** \brief	Spi_AsyncTransmit() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Spi_AsyncTransmit(void)
{
  ResumeAllInterrupts();
}

/** \brief	Spi_GetSequenceResult() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Spi_GetSequenceResult(void)
{
  SuspendAllInterrupts();
}

/** \brief	Spi_GetSequenceResult() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Spi_GetSequenceResult(void)
{
  ResumeAllInterrupts();
}

/** \brief	Spi_Cancel() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Spi_Cancel(void)
{
  SuspendAllInterrupts();
}

/** \brief	Spi_Cancel() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Spi_Cancel(void)
{
  ResumeAllInterrupts();
}

/** \brief	Spi_Init() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Spi_Init(void)
{
  SuspendAllInterrupts();
}

/** \brief	Spi_Init() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Spi_Init(void)
{
  ResumeAllInterrupts();
}

/** \brief	Spi_DeInit() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Spi_DeInit(void)
{
  SuspendAllInterrupts();
}

/** \brief	Spi_DeInit() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Spi_DeInit(void)
{
  ResumeAllInterrupts();
}

/** \brief	Spi_SyncTransmit() exclusive area entering.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Enter_Spi_SyncTransmit(void)
{
  SuspendAllInterrupts();
}

/** \brief	Spi_SyncTransmit() exclusive area exiting.
 *  \return	Nothing.
 *
 *  \note	Synchronous.
 *  \note	Non - Reentrant
 **/
LOCAL_INLINE FUNC(void, OS_CODE) SchM_Exit_Spi_SyncTransmit(void)
{
  ResumeAllInterrupts();
}

#endif	/* SCHM_SPI_H */
