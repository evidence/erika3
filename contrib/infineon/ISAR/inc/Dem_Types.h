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

/** \brief	Infineon AUTOSAR MCAL Diagnostic Event Manager Types for ERIKA
 *  		Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

#ifndef	DEM_TYPES_H
#define	DEM_TYPES_H

/******************************************************************************
 *			Global Macro Definitions			      *
 ******************************************************************************/

/** \brief	Diagnostic Event Status Passed
 *
 *  Monitor reports qualified test result passed.
 */
#define	DEM_EVENT_STATUS_PASSED	((Dem_EventStatusType)0x00U)

/** \brief	Diagnostic Event Status Failed
 *
 *  Monitor reports qualified test result failed.
 */
#define	DEM_EVENT_STATUS_FAILED	((Dem_EventStatusType)0x01U)

/******************************************************************************
 *			Global Type Definitions				      *
 ******************************************************************************/

/** \brief	Diagnostic Event Identifier Type.
 *
 *  Identification of an event by assigned EventId.
 *
 *  The EventId is assigned by the Dem.
 *
 *  Internal identifier of a diagnostic event.
 *
 *  Example:
 *  1 refers to monitor x,
 *  2 refers to monitor y, etc
 *
 *  Range:	1..65535
 *  Remark:	0 is not a valid value
 *
 *  This data type is used in both, C-APIs and service interfaces.
 *
 *  SWS_Dem_00925
 */
typedef	uint16	Dem_EventIdType;


/** \brief	Diagnostic Event Status Type.
 *
 *  This type contains all monitor test result values, which can be reported via
 *  <tt>Dem_SetEventStatus()</tt>
 *
 * SWS_Dem_00926
 */
typedef	uint8	Dem_EventStatusType;

#endif	/* DEM_TYPES_H */
