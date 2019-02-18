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

/** \brief	Infineon AUTOSAR MCAL Memory Interface Types for ERIKA
 *  		Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */
#ifndef	MEMIF_TYPES_H
#define	MEMIF_TYPES_H

/******************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 ******************************************************************************/

/** \brief	Memory Interface Status Type.
 *
 *  Denotes the current status of the underlying abstraction module and device
 *  drivers.
 *
 *  SWS_MemIf_00064 derived from SRS_BSW_00392.
 */
typedef enum
{
  MEMIF_UNINIT,		/**< The underlying abstraction module or device driver
			 *   has not been initialized (yet)		     */
  MEMIF_IDLE,		/**< The underlying abstraction module or device driver
			 *   is currently idle.				     */
  MEMIF_BUSY,		/**< The underlying abstraction module or device driver
			 *   is currently busy.				     */
  MEMIF_BUSY_INTERNAL	/**< The underlying abstraction module or device driver
			 *   is currently busy.				     */
} MemIf_StatusType;

/** \brief	Memory Interface Job Result Type.
 *
 *  Denotes the result of the last job
 *
 *  SWS_MemIf_00065 derived from SRS_BSW_00392.
 */
typedef enum
{
  MEMIF_JOB_OK,			/**< The job has been finished successfully.  */
  MEMIF_JOB_FAILED,		/**< The job has not been finished successfully.
				 *   					      */
  MEMIF_JOB_PENDING,		/**< The job has not yet benn finished.	      */
  MEMIF_JOB_CANCELED,		/**< The job has been canceled.		      */
  MEMIF_BLOCK_INCONSISTENT,	/**< - The requested block is inconsistent,
				  *    it may contain corrupted data.
				  *  - Block is NOT found.		      */
  MEMIF_BLOCK_INVALID		/**< The requested block has been marked as
				  *  invalid, the requested operation can not be
				  *  performed.				      */
} MemIf_JobResultType;

/** \brief	Memory Interface Mode Type.
 *
 *  Denotes the operation mode of the underlying abstraction modules and device
 *  drivers
 *
 *  SWS_MemIf_00066 derived from SRS_BSW_00392.
 */
typedef enum
{
  MEMIF_MODE_SLOW,	/**< The underlying memory abstraction modules and
			 *   drivers are working in slow mode.		      */
  MEMIF_MODE_FAST	/**< The underlying memory abstraction modules and
			 *   drivers are working in fast mode.		      */
} MemIf_ModeType;

#endif	/* MEMIF_TYPES_H */

