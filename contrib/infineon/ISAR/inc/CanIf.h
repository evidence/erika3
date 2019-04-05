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

/** \brief  Infineon AUTOSAR MCAL CAN Interface Types for ERIKA
 *          Enterprise.
 *
 *  \author Francesco Bagagli
 *  \date   2019
 */
#ifndef CANIF_H
#define CANIF_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "CanIf_Types.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/


/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

#define CANIF_AR_RELEASE_MAJOR_VERSION     (4U)
#define CANIF_AR_RELEASE_MINOR_VERSION     (0U)
#define CANIF_AR_RELEASE_REVISION_VERSION  (2U)


#define CANIF_TRCV_WU_ERROR            ((CanIf_TrcvWakeupReasonType)(0))
#define CANIF_TRCV_WU_NOT_SUPPORTED    ((CanIf_TrcvWakeupReasonType)(1))
#define CANIF_TRCV_WU_BY_BUS           ((CanIf_TrcvWakeupReasonType)(2))
#define CANIF_TRCV_WU_INTERNALLY       ((CanIf_TrcvWakeupReasonType)(3))
#define CANIF_TRCV_WU_RESET            ((CanIf_TrcvWakeupReasonType)(4))
#define CANIF_TRCV_WU_POWER_ON         ((CanIf_TrcvWakeupReasonType)(5))

/* CanTrcv Modes */
#define CANIF_TRCV_MODE_NORMAL         ((CanIf_TransceiverModeType)(0))
#define CANIF_TRCV_MODE_STANDBY        ((CanIf_TransceiverModeType)(1))
#define CANIF_TRCV_MODE_SLEEP          ((CanIf_TransceiverModeType)(2))

#define CANIF_TRCV_WU_ENABLE           ((CanIf_TrcvWakeupModeType)(0))
#define CANIF_TRCV_WU_DISABLE          ((CanIf_TrcvWakeupModeType)(1))
#define CANIF_TRCV_WU_CLEAR            ((CanIf_TrcvWakeupModeType)(2))

#define CANIF_CONTROLLER_WAKEUP        ((CanIf_WakeupSourceType)(0))
#define CANIF_TRANSCEIVER_WAKEUP       ((CanIf_WakeupSourceType)(0))

#define CANIF_CS_UNINIT   ((CanIf_ControllerModeType)0)
#define CANIF_CS_SLEEP    ((CanIf_ControllerModeType)1)
#define CANIF_CS_STARTED  ((CanIf_ControllerModeType)2)
#define CANIF_CS_STOPPED  ((CanIf_ControllerModeType)3)


#define CANTRCV_WU_ERROR            ((CanTrcv_TrcvWakeupReasonType)(0))
#define CANTRCV_WU_NOT_SUPPORTED    ((CanTrcv_TrcvWakeupReasonType)(1))
#define CANTRCV_WU_BY_BUS           ((CanTrcv_TrcvWakeupReasonType)(2))
#define CANTRCV_WU_INTERNALLY       ((CanTrcv_TrcvWakeupReasonType)(3))
#define CANTRCV_WU_RESET            ((CanTrcv_TrcvWakeupReasonType)(4))
#define CANTRCV_WU_POWER_ON         ((CanTrcv_TrcvWakeupReasonType)(5))
#define CANTRCV_WU_BY_PIN           ((CanTrcv_TrcvWakeupReasonType)(6))

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
#endif /*END OF  CANIF_H */


