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

/** \brief  Infineon AUTOSAR MCAL CAN Callbacks
 *
 *  \author Francesco Bagagli
 *  \date   2019
 */

#ifndef CANIF_CBK_H
#define CANIF_CBK_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#include "ComStack_Types.h"
#include "CanIf.h"
#include "Can_17_MCanP.h"

/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/

#define OSEE_TEST_CAN_TX_PDU_ID_1   (1U)
#define OSEE_TEST_CAN_TX_PDU_ID_2   (2U)

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

extern void CanIf_RxIndication(Can_HwHandleType Hrh,
                               Can_IdType CanId,
                               uint8 CanDlc,
                               const uint8 *CanSduPtr);

extern void CanIf_TxConfirmation(PduIdType CanTxPduId);

extern void CanIf_ControllerBusOff(uint8 ControllerId);

extern void CanIf_ControllerModeIndication(uint8 ControllerId,
                                    CanIf_ControllerModeType ControllerMode);

extern boolean Appl_LPduRxCalloutFunction(Can_HwHandleType Hrh,
                                          Can_IdType CanId,
                                          uint8 CanDlc,
                                          const uint8 *CanSduPtr);

#if (CANIF_AR_RELEASE_MAJOR_VERSION ==(4U))
extern void CanIf_TrcvModeIndication(uint8 Transceiver,
                                     CanTrcv_TrcvModeType OpMode );

void CanIf_CheckTrcvWakeFlagIndication(uint8 Transceiver);
#endif
#endif /*END OF CANIF_CBK_H */
