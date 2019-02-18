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

/******************************************************************************
 *                              Includes                                      *
 ******************************************************************************/

#include "Det.h"

/******************************************************************************
 *                              Local Data Types                              *
 ******************************************************************************/

/*Defining the structure to store the parameters of Det Report Error function*/

typedef struct
{  /* It will store the ModuleId of the reporting module */
   uint16 ModuleId;

   /* It will store the index based InstanceId of the reporting module */
   uint8 InstanceId;

   /* It will store the ApiId of the reporting function */
   uint8 ApiId;

   /* It will store the ErrorId of the reporting error */
   uint8 ErrorId;

}Det_ErrorType ;

/******************************************************************************
 *                              Local Data                                    *
 ******************************************************************************/

volatile Det_ErrorType Det_Error;

/******************************************************************************
 *                              Global Function Definitions                   *
 ******************************************************************************/

/* Test Stub for Det_ReportError */
void Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId)
{
    Det_Error.ModuleId = ModuleId;
    Det_Error.InstanceId = InstanceId;
    Det_Error.ApiId = ApiId;
    Det_Error.ErrorId = ErrorId;
    for(;;);
}

void Det_Init(void)
{
    Det_Error.ModuleId = 0U;
    Det_Error.InstanceId = 0U;
    Det_Error.ApiId = 0U;
    Det_Error.ErrorId = 0U;
}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/


