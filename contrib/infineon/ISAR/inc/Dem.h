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

/** \brief	Infineon AUTOSAR MCAL Diagnostic Event Manager Stub for ERIKA
 *  		Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */
#ifndef	DEM_H
#define	DEM_H

/******************************************************************************
 *			Includes					      *
 ******************************************************************************/
#include "Std_Types.h" 
#include "Dem_Types.h"
#include "Dem_PBcfg.h"

/******************************************************************************
 *			Global Macro Definitions			      *
 ******************************************************************************/
#define	DEM_AR_RELEASE_MAJOR_VERSION	(4U)
#define	DEM_AR_RELEASE_MINOR_VERSION	(0U)
#define	DEM_AR_RELEASE_REVISION_VERSION	(2U)

/******************************************************************************
 *			Global Function Declarations			      *
 ******************************************************************************/

/** \brief	Diagnostic Error Status Reporting.
 *  \param[in]	EventId		Identification of an event by assigned Event ID.
 *  \param[in]	EventStatus	Monitor test result.
 *  \return	Nothing.
 *
 *  Queues the reported events from the BSW modules (API is only used by BSW
 *  modules). The interface has an asynchronous behavior, because the processing
 *  of the event is done within the Dem main function.
 *
 *  Service ID:	0x0F
 *
 *  Sync/Async:	Asynchronous
 *  Reentrancy:	Reentrant
 *
 *  Dem206
 */
LOCAL_INLINE FUNC(void, OS_CODE)
Dem_ReportErrorStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{
#if	0	/* [GS]: T.B.C. */
  print_f("\n DEM OCCURED \n");
  print_f("EventId:%d", EventId);
  /* this line is provided to remove unused param warning in GNU */
  UNUSED_PARAMETER(EventStatus)
#else	/* 0 - [GS]: T.B.C. */
  (void)EventId;
  (void)EventStatus;
#endif	/* 0 - [GS]: T.B.C. */
}

#endif
