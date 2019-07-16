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
 *  \author Giuseppe Serano
 *  \date   2019
 */
#ifndef CAN_CFG_H
#define CAN_CFG_H

/* Required by Can_GeneralTypes.h of COMASSO 4.0.2.6! */
#define CAN_HW_HANDLE_TYPE  Can_HwHandleType

/** \brief CAN ID Type.
 *
 * \b [CAN416] Required by Can_GeneralTypes.h of COMASSO 4.0.2.6!
 *
 * Represents the Identifier of an L-PDU.
 *
 * \note For extended IDs the most significant bit is set.
 *
 * Range:    \c Standard 0..0x7FF
 * \c Extended   0..0xFFFFFFFF
 */
typedef VAR(uint32, TYPEDEF)    Can_IdType;

/** \brief CAN Hardware Handle Type.
 *
 * \b [CAN429] Required by Can_GeneralTypes.h of COMASSO 4.0.2.6!
 *
 * Represents the hardware object handles of a CAN hardware unit.
 *
 * \note For CAN hardware units with more than 255 HW objects use
 * extended range.
 *
 * Range:    \c Standard 0..0x0FF
 * \c Extended   0..0xFFFFFFFF
 */
typedef VAR(uint16, TYPEDEF) Can_HwHandleType;

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Can_17_MCanP_Cfg.h"


/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/


/* Remapping of Hardware objects names from ISAR-MCAL and COMASSO */

#define	CanHO_L_Pdu_Tx_0_TEST		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Tx_0_TEST

#define	CanHO_L_Pdu_Tx_1_TEST		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Tx_1_TEST

#define	CanHO_L_Pdu_Tx_UDS_Resp_0 	\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Tx_UDS_Resp_0

#define	CanHO_L_Pdu_Tx_UDS_Resp_1	\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Tx_UDS_Resp_1

#define	CanHO_L_Pdu_Tx_NM		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Tx_NM

#define	CanHO_L_Pdu_Tx_XCP_Resp		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Tx_XCP_Resp

#define	CanHO_L_Pdu_Tx_2_TEST		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Tx_2_TEST

#define	CanHO_L_Pdu_Tx_3_TEST		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Tx_3_TEST

#define	CanHO_L_Pdu_Tx_4_TEST		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Tx_4_TEST

#define	CanHO_L_Pdu_Rx_0_TEST		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Rx_0_TEST

#define	CanHO_L_Pdu_Rx_1_TEST		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Rx_1_TEST

#define	CanHO_L_Pdu_Rx_2_TEST		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Rx_2_TEST

#define	CanHO_L_Pdu_Rx_UDS_Req_0	\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Rx_UDS_Req_0

#define	CanHO_L_Pdu_Rx_UDS_Req_1	\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Rx_UDS_Req_1

#define	CanHO_L_Pdu_Rx_UDS_Req_0_FCN	\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Rx_UDS_Req_0_FCN

#define	CanHO_L_Pdu_Rx_UDS_Req_2	\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Rx_UDS_Req_2

#define	CanHO_L_Pdu_Rx_XCP_Req		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Rx_XCP_Req

#define	CanHO_L_Pdu_Rx_NM		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Rx_NM

#define	CanHO_L_Pdu_Rx_3_TEST		\
	Can_17_MCanPConf_CanHardwareObject_CanHO_L_Pdu_Rx_3_TEST

#endif /*END OF  CANIF_H */


