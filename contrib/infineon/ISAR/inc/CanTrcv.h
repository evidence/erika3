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

/** \file   CanTrcv.h
 *  \brief  Transceiver Driver Wrapper Header File.
 *  \author Francesco Bagagli
 *  \date   2019/04/01
 *  \version    0.01.01
 *
 *  Wrapper Header File for Infineon TLE 6250GV33 Transceiver Driver.
 *
 *  \b [CanTrcv070]
 *
 *  In case different CAN transceiver hardware chips are used in one ECU,
 *  the function names of the different CAN transceiver drivers must be modified
 *  such that no two functions with the same names are generated.
 *
 *  It is the responsibility of the user to take care that no two functions with
 *  the same names are configured.
 *
 *  The names may be extended with a vendor ID or a type ID. (BSW00347)
 *
 *  \b [CanTrcv064]
 *
 *  The naming convention prescribed by AUTOSAR is applied to all files of the
 *  \c CanTrcv module. (BSW00300)
 *
 *  \copyright  Evidence Srl 2018, All rights reserved.
 *          See LICENSE.TXT.
 */

#if (!defined(CANTRCV_H))
#define CANTRCV_H

#define     CanTrcv_Init    CanTrcv_17_6250GV33_Init
#define     CanTrcv_MainFunction    CanTrcv_17_6250GV33_MainFunction
#define     CanTrcv_SetOpMode       CanTrcv_17_6250GV33_SetOpMode
#define     CanTrcv_GetOpMode       CanTrcv_17_6250GV33_GetOpMode
#define     CanTrcv_GetBusWuReason  CanTrcv_17_6250GV33_GetBusWuReason
#define     CanTrcv_SetWakeupMode   CanTrcv_17_6250GV33_SetWakeupMode


#define     CANTRCV_AR_RELEASE_MAJOR_VERSION    CANTRCV_17_6250GV33_AR_RELEASE_MAJOR_VERSION
#define     CANTRCV_AR_RELEASE_MINOR_VERSION    CANTRCV_17_6250GV33_AR_RELEASE_MINOR_VERSION

/******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "CanTrcv_17_6250GV33.h"

/******************************************************************************
 *  END OF FILE: CanTrcv.h
 ******************************************************************************/
#endif  /* CANTRCV_H */
