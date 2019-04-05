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

/** \brief  Infineon AUTOSAR MCAL CAN Interface General Types for ERIKA
 *          Enterprise.
 *
 *  \author Francesco Bagagli
 *  \date   2019
 */
#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/** \brief  definition of CanIf_TrcvWakeupReasonType
 */
typedef uint8 CanIf_TrcvWakeupReasonType;

/** \brief  definition of CanIf_TransceiverModeType
 */
typedef uint8 CanIf_TransceiverModeType;

/** \brief  definition of CanIf_TrcvWakeupModeType
 */
typedef uint8 CanIf_TrcvWakeupModeType;

/** \brief  definition of CanIf_WakeupSourceType
 */
typedef uint8 CanIf_WakeupSourceType;

/** \brief  definition of CanIf_ControllerModeType
 */
typedef uint8 CanIf_ControllerModeType;
/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
#endif /* #ifndef CANIF_TYPES_H */

