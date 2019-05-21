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

/** \file   Can.h
 *  \brief  CAN Driver Wrapper Header File.
 *  \author Giuseppe Serano [GS]
 *  \date   2018/10/17
 *  \version    0.01.01
 *
 *  Wrapper Header File for CAN Driver.
 *
 *  One Can module provides access to one CAN Hardware Unit that may consist of
 *  several CAN controllers.
 *
 *  \b [CAN077]
 *
 *  For CAN Hardware Units of different type, different Can modules shall be
 *  implemented.
 *
 *  \b [CAN284]
 *  In case several CAN Hardware Units (of same or different vendor) are
 *  implemented in one ECU the function names, and global variables of the Can
 *  modules shall be implemented such that no two functions with the same name
 *  are generated.
 *
 *  \copyright  Evidence Srl 2018, All rights reserved.
 *          See LICENSE.TXT.
 */

#if (!defined(CAN_H))
#define CAN_H

#define     Can_Init                        Can_17_MCanP_Init
#define     Can_GetVersionInfo              Can_17_MCanP_Can_GetVersionInfo
#define     Can_CheckBaudrate               Can_17_MCanP_Can_CheckBaudrate

#define     Can_ChangeBaudrate              Can_17_MCanP_Can_ChangeBaudrate
#define     Can_SetControllerMode           Can_17_MCanP_SetControllerMode
#define     Can_DisableControllerInterrupts Can_17_MCanP_Can_DisableControllerInterrupts
#define     Can_EnableControllerInterrupts  Can_17_MCanP_Can_EnableControllerInterrupts
#define     Can_CheckWakeup                 Can_17_MCanP_Can_CheckWakeup

#define     Can_Write                       Can_17_MCanP_Write

#define     Can_MainFunction_Write          Can_17_MCanP_MainFunction_Write
#define     Can_MainFunction_Read           Can_17_MCanP_MainFunction_Read
#define     Can_MainFunction_BusOff         Can_17_MCanP_MainFunction_BusOff
#define     Can_MainFunction_Wakeup         Can_17_MCanP_MainFunction_Wakeup
#define     Can_MainFunction_Mode           Can_17_MCanP_MainFunction_Mode

#define     CAN_AR_RELEASE_MAJOR_VERSION    CAN_17_MCANP_AR_RELEASE_MAJOR_VERSION
#define     CAN_AR_RELEASE_MINOR_VERSION    CAN_17_MCANP_AR_RELEASE_MINOR_VERSION

/******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "Can_17_MCanP.h"

/******************************************************************************
 *  END OF FILE: Can.h
 ******************************************************************************/
#endif  /* CAN_H */
