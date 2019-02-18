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

/** \brief  AUTOSAR BSW DET stub.
 *
 *  \author Francesco Bagagli
 *  \date   2018
 */

#ifndef DET_H
#define DET_H

/******************************************************************************
 *                              Includes                                      *
 ******************************************************************************/

#include "Std_Types.h"

/******************************************************************************
 *                              Global Macros                                 *
 ******************************************************************************/

/* Declaring the Vendor ID */
#define DET_VENDOR_ID                               101U

/* Declaring the module id for DET */
#define DET_MODULE_ID                                15U

/* File version Information to perform the version check */

#define DET_AR_RELEASE_MAJOR_VERSION                  4U
#define DET_AR_RELEASE_MINOR_VERSION                  0U
#define DET_AR_RELEASE_REVISION_VERSION               2U

#define DET_SW_MAJOR_VERSION                          0U
#define DET_SW_MINOR_VERSION                          0U
#define DET_SW_PATCH_VERSION                          1U

/******************************************************************************
 *                              Global Function Declarations                  *
 ******************************************************************************/

/* This function is used to clear the logged errors and the reported
   error count */
extern void Det_Init(void);

/* This function is used to log the reported errors and count the reported
   errors */
extern void Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId);

#if 0  /* Not supported for now */
/* This function is the service for starting after the Det_Init() is called */
extern void Det_Start(void);
#endif

#endif /* #define DET_H */
