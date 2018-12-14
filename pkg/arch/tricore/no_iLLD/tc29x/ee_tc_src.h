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


/**
 *
 * This file derives from a modification of the Infineon startup scripts,
 * distributed under the following license:
 *
 * \file ./Src/BaseSw/Infra/Sfr/TC29B/_Reg/IfxSrc_reg.h
 * \brief
 * \copyright Copyright (c) 2014 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC29XB_UM_V1.3.R0
 * Specification: tc29xB_um_v1.3_MCSFR.xml (Revision: UM_V1.3)
 * MAY BE CHANGED BY USER [yes/no]: No
 *
 *                                 IMPORTANT NOTICE
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 */


/** \file   ee_tc_srch.h
 *  \brief  Contains the OSEE_TC_SRC registers offset definition for tc29x.
 *  \author Errico Guidieri
 *  \date   2017
 */
#ifndef OSEE_TC_SRC_H
#define OSEE_TC_SRC_H

/** \brief  24, AGBT Service Request */
#define OSEE_TC_SRC_AGBT_AGBT0_SR         (0x0024U)

/** Alias (User Manual Name) for OSEE_TC_SRC_AGBT_AGBT0_SR.
 * To use register names with standard convention, please use OSEE_TC_SRC_AGBT_AGBT0_SR.
 */
#define OSEE_TC_SRC_AGBT                  (OSEE_TC_SRC_AGBT_AGBT0_SR)

/** \brief  88, ASCLIN Error Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN0_ERR    (0x0088U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN0_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN0_ERR.
 */
#define OSEE_TC_SRC_ASCLIN0ERR            (OSEE_TC_SRC_ASCLIN_ASCLIN0_ERR)

/** \brief  84, ASCLIN Receive Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN0_RX     (0x0084U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN0_RX.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN0_RX.
 */
#define OSEE_TC_SRC_ASCLIN0RX             (OSEE_TC_SRC_ASCLIN_ASCLIN0_RX)

/** \brief  80, ASCLIN Transmit Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN0_TX     (0x0080U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN0_TX.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN0_TX.
 */
#define OSEE_TC_SRC_ASCLIN0TX             (OSEE_TC_SRC_ASCLIN_ASCLIN0_TX)

/** \brief  94, ASCLIN Error Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN1_ERR    (0x0094U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN1_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN1_ERR.
 */
#define OSEE_TC_SRC_ASCLIN1ERR            (OSEE_TC_SRC_ASCLIN_ASCLIN1_ERR)

/** \brief  90, ASCLIN Receive Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN1_RX     (0x0090U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN1_RX.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN1_RX.
 */
#define OSEE_TC_SRC_ASCLIN1RX             (OSEE_TC_SRC_ASCLIN_ASCLIN1_RX)

/** \brief  8C, ASCLIN Transmit Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN1_TX     (0x008CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN1_TX.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN1_TX.
 */
#define OSEE_TC_SRC_ASCLIN1TX             (OSEE_TC_SRC_ASCLIN_ASCLIN1_TX)

/** \brief  A0, ASCLIN Error Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN2_ERR    (0x00A0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN2_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN2_ERR.
 */
#define OSEE_TC_SRC_ASCLIN2ERR            (OSEE_TC_SRC_ASCLIN_ASCLIN2_ERR)

/** \brief  9C, ASCLIN Receive Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN2_RX     (0x009CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN2_RX.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN2_RX.
 */
#define OSEE_TC_SRC_ASCLIN2RX             (OSEE_TC_SRC_ASCLIN_ASCLIN2_RX)

/** \brief  98, ASCLIN Transmit Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN2_TX     (0x0098U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN2_TX.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN2_TX.
 */
#define OSEE_TC_SRC_ASCLIN2TX             (OSEE_TC_SRC_ASCLIN_ASCLIN2_TX)

/** \brief  AC, ASCLIN Error Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN3_ERR    (0x00ACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN3_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN3_ERR.
 */
#define OSEE_TC_SRC_ASCLIN3ERR            (OSEE_TC_SRC_ASCLIN_ASCLIN3_ERR)

/** \brief  A8, ASCLIN Receive Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN3_RX     (0x00A8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN3_RX.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN3_RX.
 */
#define OSEE_TC_SRC_ASCLIN3RX             (OSEE_TC_SRC_ASCLIN_ASCLIN3_RX)

/** \brief  A4, ASCLIN Transmit Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN3_TX     (0x00A4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN3_TX.
 * To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN3_TX.
 */
#define OSEE_TC_SRC_ASCLIN3TX             (OSEE_TC_SRC_ASCLIN_ASCLIN3_TX)

/** \brief  40, Bus Control Unit SPB Service Request */
#define OSEE_TC_SRC_BCU_SPB_SBSRC         (0x0040U)

/** Alias (User Manual Name) for OSEE_TC_SRC_BCU_SPB_SBSRC.
 * To use register names with standard convention, please use OSEE_TC_SRC_BCU_SPB_SBSRC.
 */
#define OSEE_TC_SRC_BCUSPBSBSRC           (OSEE_TC_SRC_BCU_SPB_SBSRC)

/** \brief  900, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT0         (0x0900U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT0.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT0.
 */
#define OSEE_TC_SRC_CANINT0               (OSEE_TC_SRC_CAN_CAN0_INT0)

/** \brief  904, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT1         (0x0904U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT1.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT1.
 */
#define OSEE_TC_SRC_CANINT1               (OSEE_TC_SRC_CAN_CAN0_INT1)

/** \brief  928, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT10        (0x0928U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT10.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT10.
 */
#define OSEE_TC_SRC_CANINT10              (OSEE_TC_SRC_CAN_CAN0_INT10)

/** \brief  92C, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT11        (0x092CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT11.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT11.
 */
#define OSEE_TC_SRC_CANINT11              (OSEE_TC_SRC_CAN_CAN0_INT11)

/** \brief  930, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT12        (0x0930U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT12.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT12.
 */
#define OSEE_TC_SRC_CANINT12              (OSEE_TC_SRC_CAN_CAN0_INT12)

/** \brief  934, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT13        (0x0934U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT13.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT13.
 */
#define OSEE_TC_SRC_CANINT13              (OSEE_TC_SRC_CAN_CAN0_INT13)

/** \brief  938, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT14        (0x0938U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT14.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT14.
 */
#define OSEE_TC_SRC_CANINT14              (OSEE_TC_SRC_CAN_CAN0_INT14)

/** \brief  93C, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT15        (0x093CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT15.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT15.
 */
#define OSEE_TC_SRC_CANINT15              (OSEE_TC_SRC_CAN_CAN0_INT15)

/** \brief  908, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT2         (0x0908U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT2.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT2.
 */
#define OSEE_TC_SRC_CANINT2               (OSEE_TC_SRC_CAN_CAN0_INT2)

/** \brief  90C, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT3         (0x090CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT3.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT3.
 */
#define OSEE_TC_SRC_CANINT3               (OSEE_TC_SRC_CAN_CAN0_INT3)

/** \brief  910, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT4         (0x0910U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT4.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT4.
 */
#define OSEE_TC_SRC_CANINT4               (OSEE_TC_SRC_CAN_CAN0_INT4)

/** \brief  914, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT5         (0x0914U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT5.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT5.
 */
#define OSEE_TC_SRC_CANINT5               (OSEE_TC_SRC_CAN_CAN0_INT5)

/** \brief  918, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT6         (0x0918U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT6.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT6.
 */
#define OSEE_TC_SRC_CANINT6               (OSEE_TC_SRC_CAN_CAN0_INT6)

/** \brief  91C, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT7         (0x091CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT7.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT7.
 */
#define OSEE_TC_SRC_CANINT7               (OSEE_TC_SRC_CAN_CAN0_INT7)

/** \brief  920, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT8         (0x0920U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT8.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT8.
 */
#define OSEE_TC_SRC_CANINT8               (OSEE_TC_SRC_CAN_CAN0_INT8)

/** \brief  924, MULTICAN+ Service Request */
#define OSEE_TC_SRC_CAN_CAN0_INT9         (0x0924U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT9.
 * To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT9.
 */
#define OSEE_TC_SRC_CANINT9               (OSEE_TC_SRC_CAN_CAN0_INT9)

/** \brief  940, MULTICANr+ Service Request */
#define OSEE_TC_SRC_CANR_CANR0_RINT0      (0x0940U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CANR_CANR0_RINT0.
 * To use register names with standard convention, please use OSEE_TC_SRC_CANR_CANR0_RINT0.
 */
#define OSEE_TC_SRC_CANRINT0              (OSEE_TC_SRC_CANR_CANR0_RINT0)

/** \brief  944, MULTICANr+ Service Request */
#define OSEE_TC_SRC_CANR_CANR0_RINT1      (0x0944U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CANR_CANR0_RINT1.
 * To use register names with standard convention, please use OSEE_TC_SRC_CANR_CANR0_RINT1.
 */
#define OSEE_TC_SRC_CANRINT1              (OSEE_TC_SRC_CANR_CANR0_RINT1)

/** \brief  948, MULTICANr+ Service Request */
#define OSEE_TC_SRC_CANR_CANR0_RINT2      (0x0948U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CANR_CANR0_RINT2.
 * To use register names with standard convention, please use OSEE_TC_SRC_CANR_CANR0_RINT2.
 */
#define OSEE_TC_SRC_CANRINT2              (OSEE_TC_SRC_CANR_CANR0_RINT2)

/** \brief  94C, MULTICANr+ Service Request */
#define OSEE_TC_SRC_CANR_CANR0_RINT3      (0x094CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_CANR_CANR0_RINT3.
 * To use register names with standard convention, please use OSEE_TC_SRC_CANR_CANR0_RINT3.
 */
#define OSEE_TC_SRC_CANRINT3              (OSEE_TC_SRC_CANR_CANR0_RINT3)

/** \brief  950, MULTICANr+ Service Request */
#define OSEE_TC_SRC_CANR_CANR0_RINT4      (0x0950U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CANR_CANR0_RINT4.
 * To use register names with standard convention, please use OSEE_TC_SRC_CANR_CANR0_RINT4.
 */
#define OSEE_TC_SRC_CANRINT4              (OSEE_TC_SRC_CANR_CANR0_RINT4)

/** \brief  954, MULTICANr+ Service Request */
#define OSEE_TC_SRC_CANR_CANR0_RINT5      (0x0954U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CANR_CANR0_RINT5.
 * To use register names with standard convention, please use OSEE_TC_SRC_CANR_CANR0_RINT5.
 */
#define OSEE_TC_SRC_CANRINT5              (OSEE_TC_SRC_CANR_CANR0_RINT5)

/** \brief  958, MULTICANr+ Service Request */
#define OSEE_TC_SRC_CANR_CANR0_RINT6      (0x0958U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CANR_CANR0_RINT6.
 * To use register names with standard convention, please use OSEE_TC_SRC_CANR_CANR0_RINT6.
 */
#define OSEE_TC_SRC_CANRINT6              (OSEE_TC_SRC_CANR_CANR0_RINT6)

/** \brief  95C, MULTICANr+ Service Request */
#define OSEE_TC_SRC_CANR_CANR0_RINT7      (0x095CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_CANR_CANR0_RINT7.
 * To use register names with standard convention, please use OSEE_TC_SRC_CANR_CANR0_RINT7.
 */
#define OSEE_TC_SRC_CANRINT7              (OSEE_TC_SRC_CANR_CANR0_RINT7)

/** \brief  420, CCU6 Service Request 0 */
#define OSEE_TC_SRC_CCU6_CCU60_SR0        (0x0420U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU60_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU60_SR0.
 */
#define OSEE_TC_SRC_CCU60SR0              (OSEE_TC_SRC_CCU6_CCU60_SR0)

/** \brief  424, CCU6 Service Request 1 */
#define OSEE_TC_SRC_CCU6_CCU60_SR1        (0x0424U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU60_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU60_SR1.
 */
#define OSEE_TC_SRC_CCU60SR1              (OSEE_TC_SRC_CCU6_CCU60_SR1)

/** \brief  428, CCU6 Service Request 2 */
#define OSEE_TC_SRC_CCU6_CCU60_SR2        (0x0428U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU60_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU60_SR2.
 */
#define OSEE_TC_SRC_CCU60SR2              (OSEE_TC_SRC_CCU6_CCU60_SR2)

/** \brief  42C, CCU6 Service Request 3 */
#define OSEE_TC_SRC_CCU6_CCU60_SR3        (0x042CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU60_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU60_SR3.
 */
#define OSEE_TC_SRC_CCU60SR3              (OSEE_TC_SRC_CCU6_CCU60_SR3)

/** \brief  430, CCU6 Service Request 0 */
#define OSEE_TC_SRC_CCU6_CCU61_SR0        (0x0430U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU61_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU61_SR0.
 */
#define OSEE_TC_SRC_CCU61SR0              (OSEE_TC_SRC_CCU6_CCU61_SR0)

/** \brief  434, CCU6 Service Request 1 */
#define OSEE_TC_SRC_CCU6_CCU61_SR1        (0x0434U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU61_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU61_SR1.
 */
#define OSEE_TC_SRC_CCU61SR1              (OSEE_TC_SRC_CCU6_CCU61_SR1)

/** \brief  438, CCU6 Service Request 2 */
#define OSEE_TC_SRC_CCU6_CCU61_SR2        (0x0438U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU61_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU61_SR2.
 */
#define OSEE_TC_SRC_CCU61SR2              (OSEE_TC_SRC_CCU6_CCU61_SR2)

/** \brief  43C, CCU6 Service Request 3 */
#define OSEE_TC_SRC_CCU6_CCU61_SR3        (0x043CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU61_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU61_SR3.
 */
#define OSEE_TC_SRC_CCU61SR3              (OSEE_TC_SRC_CCU6_CCU61_SR3)

/** \brief  50, Cerberus Service Request */
#define OSEE_TC_SRC_CERBERUS_CERBERUS_SR0 (0x0050U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CERBERUS_CERBERUS_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_CERBERUS_CERBERUS_SR0.
 */
#define OSEE_TC_SRC_CERBERUS0             (OSEE_TC_SRC_CERBERUS_CERBERUS_SR0)

/** \brief  54, Cerberus Service Request */
#define OSEE_TC_SRC_CERBERUS_CERBERUS_SR1 (0x0054U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CERBERUS_CERBERUS_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_CERBERUS_CERBERUS_SR1.
 */
#define OSEE_TC_SRC_CERBERUS1             (OSEE_TC_SRC_CERBERUS_CERBERUS_SR1)

/** \brief  DA8, CIF ISP Service Request */
#define OSEE_TC_SRC_CIF_CIF0_ISP          (0x0DA8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CIF_CIF0_ISP.
 * To use register names with standard convention, please use OSEE_TC_SRC_CIF_CIF0_ISP.
 */
#define OSEE_TC_SRC_CIFISP                (OSEE_TC_SRC_CIF_CIF0_ISP)

/** \brief  DA0, CIF MI Service Request */
#define OSEE_TC_SRC_CIF_CIF0_MI           (0x0DA0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CIF_CIF0_MI.
 * To use register names with standard convention, please use OSEE_TC_SRC_CIF_CIF0_MI.
 */
#define OSEE_TC_SRC_CIFMI                 (OSEE_TC_SRC_CIF_CIF0_MI)

/** \brief  DA4, CIF MI EP Service Request */
#define OSEE_TC_SRC_CIF_CIF0_MIEP         (0x0DA4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CIF_CIF0_MIEP.
 * To use register names with standard convention, please use OSEE_TC_SRC_CIF_CIF0_MIEP.
 */
#define OSEE_TC_SRC_CIFMIEP               (OSEE_TC_SRC_CIF_CIF0_MIEP)

/** \brief  DAC, CIF MJPEG Service Request */
#define OSEE_TC_SRC_CIF_CIF0_MJPEG        (0x0DACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_CIF_CIF0_MJPEG.
 * To use register names with standard convention, please use OSEE_TC_SRC_CIF_CIF0_MJPEG.
 */
#define OSEE_TC_SRC_CIFMJPEG              (OSEE_TC_SRC_CIF_CIF0_MJPEG)

/** \brief  0, CPU Software Breakpoint Service Request */
#define OSEE_TC_SRC_CPU_CPU0_SBSRC        (0x0000U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CPU_CPU0_SBSRC.
 * To use register names with standard convention, please use OSEE_TC_SRC_CPU_CPU0_SBSRC.
 */
#define OSEE_TC_SRC_CPU0SBSRC             (OSEE_TC_SRC_CPU_CPU0_SBSRC)

/** \brief  4, CPU Software Breakpoint Service Request */
#define OSEE_TC_SRC_CPU_CPU1_SBSRC        (0x0004U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CPU_CPU1_SBSRC.
 * To use register names with standard convention, please use OSEE_TC_SRC_CPU_CPU1_SBSRC.
 */
#define OSEE_TC_SRC_CPU1SBSRC             (OSEE_TC_SRC_CPU_CPU1_SBSRC)

/** \brief  8, CPU Software Breakpoint Service Request */
#define OSEE_TC_SRC_CPU_CPU2_SBSRC        (0x0008U)

/** Alias (User Manual Name) for OSEE_TC_SRC_CPU_CPU2_SBSRC.
 * To use register names with standard convention, please use OSEE_TC_SRC_CPU_CPU2_SBSRC.
 */
#define OSEE_TC_SRC_CPU2SBSRC             (OSEE_TC_SRC_CPU_CPU2_SBSRC)

/** \brief  D70, DAM Service Request */
#define OSEE_TC_SRC_DAM_DAM0_SR0          (0x0D70U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DAM_DAM0_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_DAM_DAM0_SR0.
 */
#define OSEE_TC_SRC_DAM0                  (OSEE_TC_SRC_DAM_DAM0_SR0)

/** \brief  D74, DAM Service Request */
#define OSEE_TC_SRC_DAM_DAM0_SR1          (0x0D74U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DAM_DAM0_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_DAM_DAM0_SR1.
 */
#define OSEE_TC_SRC_DAM1                  (OSEE_TC_SRC_DAM_DAM0_SR1)

/** \brief  D78, DAM Service Request */
#define OSEE_TC_SRC_DAM_DAM0_SR2          (0x0D78U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DAM_DAM0_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_DAM_DAM0_SR2.
 */
#define OSEE_TC_SRC_DAM2                  (OSEE_TC_SRC_DAM_DAM0_SR2)

/** \brief  D7C, DAM Service Request */
#define OSEE_TC_SRC_DAM_DAM0_SR3          (0x0D7CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DAM_DAM0_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_DAM_DAM0_SR3.
 */
#define OSEE_TC_SRC_DAM3                  (OSEE_TC_SRC_DAM_DAM0_SR3)

/** \brief  D80, DAM Service Request */
#define OSEE_TC_SRC_DAM_DAM0_SR4          (0x0D80U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DAM_DAM0_SR4.
 * To use register names with standard convention, please use OSEE_TC_SRC_DAM_DAM0_SR4.
 */
#define OSEE_TC_SRC_DAM4                  (OSEE_TC_SRC_DAM_DAM0_SR4)

/** \brief  D84, DAM Service Request */
#define OSEE_TC_SRC_DAM_DAM0_SR5          (0x0D84U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DAM_DAM0_SR5.
 * To use register names with standard convention, please use OSEE_TC_SRC_DAM_DAM0_SR5.
 */
#define OSEE_TC_SRC_DAM5                  (OSEE_TC_SRC_DAM_DAM0_SR5)

/** \brief  500, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH0          (0x0500U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH0.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH0.
 */
#define OSEE_TC_SRC_DMACH0                (OSEE_TC_SRC_DMA_DMA0_CH0)

/** \brief  504, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH1          (0x0504U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH1.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH1.
 */
#define OSEE_TC_SRC_DMACH1                (OSEE_TC_SRC_DMA_DMA0_CH1)

/** \brief  528, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH10         (0x0528U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH10.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH10.
 */
#define OSEE_TC_SRC_DMACH10               (OSEE_TC_SRC_DMA_DMA0_CH10)

/** \brief  690, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH100        (0x0690U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH100.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH100.
 */
#define OSEE_TC_SRC_DMACH100              (OSEE_TC_SRC_DMA_DMA0_CH100)

/** \brief  694, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH101        (0x0694U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH101.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH101.
 */
#define OSEE_TC_SRC_DMACH101              (OSEE_TC_SRC_DMA_DMA0_CH101)

/** \brief  698, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH102        (0x0698U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH102.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH102.
 */
#define OSEE_TC_SRC_DMACH102              (OSEE_TC_SRC_DMA_DMA0_CH102)

/** \brief  69C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH103        (0x069CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH103.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH103.
 */
#define OSEE_TC_SRC_DMACH103              (OSEE_TC_SRC_DMA_DMA0_CH103)

/** \brief  6A0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH104        (0x06A0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH104.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH104.
 */
#define OSEE_TC_SRC_DMACH104              (OSEE_TC_SRC_DMA_DMA0_CH104)

/** \brief  6A4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH105        (0x06A4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH105.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH105.
 */
#define OSEE_TC_SRC_DMACH105              (OSEE_TC_SRC_DMA_DMA0_CH105)

/** \brief  6A8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH106        (0x06A8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH106.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH106.
 */
#define OSEE_TC_SRC_DMACH106              (OSEE_TC_SRC_DMA_DMA0_CH106)

/** \brief  6AC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH107        (0x06ACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH107.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH107.
 */
#define OSEE_TC_SRC_DMACH107              (OSEE_TC_SRC_DMA_DMA0_CH107)

/** \brief  6B0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH108        (0x06B0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH108.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH108.
 */
#define OSEE_TC_SRC_DMACH108              (OSEE_TC_SRC_DMA_DMA0_CH108)

/** \brief  6B4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH109        (0x06B4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH109.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH109.
 */
#define OSEE_TC_SRC_DMACH109              (OSEE_TC_SRC_DMA_DMA0_CH109)

/** \brief  52C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH11         (0x052CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH11.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH11.
 */
#define OSEE_TC_SRC_DMACH11               (OSEE_TC_SRC_DMA_DMA0_CH11)

/** \brief  6B8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH110        (0x06B8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH110.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH110.
 */
#define OSEE_TC_SRC_DMACH110              (OSEE_TC_SRC_DMA_DMA0_CH110)

/** \brief  6BC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH111        (0x06BCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH111.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH111.
 */
#define OSEE_TC_SRC_DMACH111              (OSEE_TC_SRC_DMA_DMA0_CH111)

/** \brief  6C0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH112        (0x06C0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH112.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH112.
 */
#define OSEE_TC_SRC_DMACH112              (OSEE_TC_SRC_DMA_DMA0_CH112)

/** \brief  6C4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH113        (0x06C4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH113.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH113.
 */
#define OSEE_TC_SRC_DMACH113              (OSEE_TC_SRC_DMA_DMA0_CH113)

/** \brief  6C8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH114        (0x06C8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH114.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH114.
 */
#define OSEE_TC_SRC_DMACH114              (OSEE_TC_SRC_DMA_DMA0_CH114)

/** \brief  6CC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH115        (0x06CCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH115.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH115.
 */
#define OSEE_TC_SRC_DMACH115  (OSEE_TC_SRC_DMA_DMA0_CH115)

/** \brief  6D0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH116    (0x06D0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH116.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH116.
 */
#define OSEE_TC_SRC_DMACH116  (OSEE_TC_SRC_DMA_DMA0_CH116)

/** \brief  6D4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH117    (0x06D4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH117.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH117.
 */
#define OSEE_TC_SRC_DMACH117  (OSEE_TC_SRC_DMA_DMA0_CH117)

/** \brief  6D8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH118    (0x06D8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH118.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH118.
 */
#define OSEE_TC_SRC_DMACH118  (OSEE_TC_SRC_DMA_DMA0_CH118)

/** \brief  6DC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH119    (0x06DCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH119.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH119.
 */
#define OSEE_TC_SRC_DMACH119          (OSEE_TC_SRC_DMA_DMA0_CH119)

/** \brief  530, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH12     (0x0530U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH12.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH12.
 */
#define OSEE_TC_SRC_DMACH12           (OSEE_TC_SRC_DMA_DMA0_CH12)

/** \brief  6E0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH120    (0x06E0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH120.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH120.
 */
#define OSEE_TC_SRC_DMACH120  (OSEE_TC_SRC_DMA_DMA0_CH120)

/** \brief  6E4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH121    (0x06E4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH121.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH121.
 */
#define OSEE_TC_SRC_DMACH121  (OSEE_TC_SRC_DMA_DMA0_CH121)

/** \brief  6E8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH122    (0x06E8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH122.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH122.
 */
#define OSEE_TC_SRC_DMACH122  (OSEE_TC_SRC_DMA_DMA0_CH122)

/** \brief  6EC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH123    (0x06ECU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH123.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH123.
 */
#define OSEE_TC_SRC_DMACH123  (OSEE_TC_SRC_DMA_DMA0_CH123)

/** \brief  6F0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH124    (0x06F0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH124.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH124.
 */
#define OSEE_TC_SRC_DMACH124  (OSEE_TC_SRC_DMA_DMA0_CH124)

/** \brief  6F4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH125    (0x06F4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH125.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH125.
 */
#define OSEE_TC_SRC_DMACH125  (OSEE_TC_SRC_DMA_DMA0_CH125)

/** \brief  6F8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH126    (0x06F8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH126.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH126.
 */
#define OSEE_TC_SRC_DMACH126  (OSEE_TC_SRC_DMA_DMA0_CH126)

/** \brief  6FC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH127    (0x06FCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH127.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH127.
 */
#define OSEE_TC_SRC_DMACH127  (OSEE_TC_SRC_DMA_DMA0_CH127)

/** \brief  534, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH13    (0x0534U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH13.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH13.
 */
#define OSEE_TC_SRC_DMACH13 (OSEE_TC_SRC_DMA_DMA0_CH13)

/** \brief  538, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH14    (0x0538U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH14.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH14.
 */
#define OSEE_TC_SRC_DMACH14 (OSEE_TC_SRC_DMA_DMA0_CH14)

/** \brief  53C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH15    (0x053CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH15.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH15.
 */
#define OSEE_TC_SRC_DMACH15 (OSEE_TC_SRC_DMA_DMA0_CH15)

/** \brief  540, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH16    (0x0540U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH16.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH16.
 */
#define OSEE_TC_SRC_DMACH16 (OSEE_TC_SRC_DMA_DMA0_CH16)

/** \brief  544, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH17    (0x0544U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH17.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH17.
 */
#define OSEE_TC_SRC_DMACH17 (OSEE_TC_SRC_DMA_DMA0_CH17)

/** \brief  548, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH18    (0x0548U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH18.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH18.
 */
#define OSEE_TC_SRC_DMACH18 (OSEE_TC_SRC_DMA_DMA0_CH18)

/** \brief  54C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH19    (0x054CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH19.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH19.
 */
#define OSEE_TC_SRC_DMACH19 (OSEE_TC_SRC_DMA_DMA0_CH19)

/** \brief  508, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH2    (0x0508U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH2.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH2.
 */
#define OSEE_TC_SRC_DMACH2  (OSEE_TC_SRC_DMA_DMA0_CH2)

/** \brief  550, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH20    (0x0550U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH20.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH20.
 */
#define OSEE_TC_SRC_DMACH20 (OSEE_TC_SRC_DMA_DMA0_CH20)

/** \brief  554, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH21    (0x0554U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH21.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH21.
 */
#define OSEE_TC_SRC_DMACH21 (OSEE_TC_SRC_DMA_DMA0_CH21)

/** \brief  558, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH22    (0x0558U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH22.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH22.
 */
#define OSEE_TC_SRC_DMACH22 (OSEE_TC_SRC_DMA_DMA0_CH22)

/** \brief  55C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH23    (0x055CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH23.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH23.
 */
#define OSEE_TC_SRC_DMACH23 (OSEE_TC_SRC_DMA_DMA0_CH23)

/** \brief  560, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH24    (0x0560U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH24.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH24.
 */
#define OSEE_TC_SRC_DMACH24 (OSEE_TC_SRC_DMA_DMA0_CH24)

/** \brief  564, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH25    (0x0564U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH25.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH25.
 */
#define OSEE_TC_SRC_DMACH25 (OSEE_TC_SRC_DMA_DMA0_CH25)

/** \brief  568, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH26    (0x0568U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH26.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH26.
 */
#define OSEE_TC_SRC_DMACH26 (OSEE_TC_SRC_DMA_DMA0_CH26)

/** \brief  56C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH27    (0x056CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH27.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH27.
 */
#define OSEE_TC_SRC_DMACH27 (OSEE_TC_SRC_DMA_DMA0_CH27)

/** \brief  570, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH28    (0x0570U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH28.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH28.
 */
#define OSEE_TC_SRC_DMACH28 (OSEE_TC_SRC_DMA_DMA0_CH28)

/** \brief  574, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH29    (0x0574U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH29.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH29.
 */
#define OSEE_TC_SRC_DMACH29 (OSEE_TC_SRC_DMA_DMA0_CH29)

/** \brief  50C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH3    (0x050CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH3.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH3.
 */
#define OSEE_TC_SRC_DMACH3  (OSEE_TC_SRC_DMA_DMA0_CH3)

/** \brief  578, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH30    (0x0578U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH30.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH30.
 */
#define OSEE_TC_SRC_DMACH30 (OSEE_TC_SRC_DMA_DMA0_CH30)

/** \brief  57C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH31    (0x057CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH31.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH31.
 */
#define OSEE_TC_SRC_DMACH31 (OSEE_TC_SRC_DMA_DMA0_CH31)

/** \brief  580, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH32    (0x0580U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH32.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH32.
 */
#define OSEE_TC_SRC_DMACH32 (OSEE_TC_SRC_DMA_DMA0_CH32)

/** \brief  584, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH33    (0x0584U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH33.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH33.
 */
#define OSEE_TC_SRC_DMACH33 (OSEE_TC_SRC_DMA_DMA0_CH33)

/** \brief  588, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH34    (0x0588U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH34.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH34.
 */
#define OSEE_TC_SRC_DMACH34 (OSEE_TC_SRC_DMA_DMA0_CH34)

/** \brief  58C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH35    (0x058CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH35.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH35.
 */
#define OSEE_TC_SRC_DMACH35 (OSEE_TC_SRC_DMA_DMA0_CH35)

/** \brief  590, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH36    (0x0590U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH36.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH36.
 */
#define OSEE_TC_SRC_DMACH36 (OSEE_TC_SRC_DMA_DMA0_CH36)

/** \brief  594, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH37    (0x0594U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH37.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH37.
 */
#define OSEE_TC_SRC_DMACH37 (OSEE_TC_SRC_DMA_DMA0_CH37)

/** \brief  598, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH38    (0x0598U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH38.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH38.
 */
#define OSEE_TC_SRC_DMACH38 (OSEE_TC_SRC_DMA_DMA0_CH38)

/** \brief  59C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH39    (0x059CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH39.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH39.
 */
#define OSEE_TC_SRC_DMACH39 (OSEE_TC_SRC_DMA_DMA0_CH39)

/** \brief  510, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH4    (0x0510U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH4.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH4.
 */
#define OSEE_TC_SRC_DMACH4  (OSEE_TC_SRC_DMA_DMA0_CH4)

/** \brief  5A0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH40    (0x05A0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH40.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH40.
 */
#define OSEE_TC_SRC_DMACH40 (OSEE_TC_SRC_DMA_DMA0_CH40)

/** \brief  5A4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH41    (0x05A4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH41.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH41.
 */
#define OSEE_TC_SRC_DMACH41 (OSEE_TC_SRC_DMA_DMA0_CH41)

/** \brief  5A8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH42    (0x05A8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH42.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH42.
 */
#define OSEE_TC_SRC_DMACH42 (OSEE_TC_SRC_DMA_DMA0_CH42)

/** \brief  5AC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH43    (0x05ACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH43.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH43.
 */
#define OSEE_TC_SRC_DMACH43 (OSEE_TC_SRC_DMA_DMA0_CH43)

/** \brief  5B0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH44    (0x05B0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH44.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH44.
 */
#define OSEE_TC_SRC_DMACH44 (OSEE_TC_SRC_DMA_DMA0_CH44)

/** \brief  5B4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH45    (0x05B4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH45.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH45.
 */
#define OSEE_TC_SRC_DMACH45 (OSEE_TC_SRC_DMA_DMA0_CH45)

/** \brief  5B8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH46    (0x05B8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH46.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH46.
 */
#define OSEE_TC_SRC_DMACH46 (OSEE_TC_SRC_DMA_DMA0_CH46)

/** \brief  5BC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH47    (0x05BCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH47.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH47.
 */
#define OSEE_TC_SRC_DMACH47 (OSEE_TC_SRC_DMA_DMA0_CH47)

/** \brief  5C0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH48    (0x05C0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH48.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH48.
 */
#define OSEE_TC_SRC_DMACH48 (OSEE_TC_SRC_DMA_DMA0_CH48)

/** \brief  5C4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH49    (0x05C4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH49.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH49.
 */
#define OSEE_TC_SRC_DMACH49 (OSEE_TC_SRC_DMA_DMA0_CH49)

/** \brief  514, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH5    (0x0514U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH5.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH5.
 */
#define OSEE_TC_SRC_DMACH5          (OSEE_TC_SRC_DMA_DMA0_CH5)

/** \brief  5C8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH50   (0x05C8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH50.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH50.
 */
#define OSEE_TC_SRC_DMACH50         (OSEE_TC_SRC_DMA_DMA0_CH50)

/** \brief  5CC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH51   (0x05CCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH51.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH51.
 */
#define OSEE_TC_SRC_DMACH51         (OSEE_TC_SRC_DMA_DMA0_CH51)

/** \brief  5D0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH52   (0x05D0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH52.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH52.
 */
#define OSEE_TC_SRC_DMACH52         (OSEE_TC_SRC_DMA_DMA0_CH52)

/** \brief  5D4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH53   (0x05D4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH53.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH53.
 */
#define OSEE_TC_SRC_DMACH53         (OSEE_TC_SRC_DMA_DMA0_CH53)

/** \brief  5D8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH54   (0x05D8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH54.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH54.
 */
#define OSEE_TC_SRC_DMACH54         (OSEE_TC_SRC_DMA_DMA0_CH54)

/** \brief  5DC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH55   (0x05DCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH55.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH55.
 */
#define OSEE_TC_SRC_DMACH55         (OSEE_TC_SRC_DMA_DMA0_CH55)

/** \brief  5E0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH56   (0x05E0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH56.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH56.
 */
#define OSEE_TC_SRC_DMACH56         (OSEE_TC_SRC_DMA_DMA0_CH56)

/** \brief  5E4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH57   (0x05E4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH57.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH57.
 */
#define OSEE_TC_SRC_DMACH57         (OSEE_TC_SRC_DMA_DMA0_CH57)

/** \brief  5E8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH58   (0x05E8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH58.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH58.
 */
#define OSEE_TC_SRC_DMACH58         (OSEE_TC_SRC_DMA_DMA0_CH58)

/** \brief  5EC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH59   (0x05ECU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH59.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH59.
 */
#define OSEE_TC_SRC_DMACH59         (OSEE_TC_SRC_DMA_DMA0_CH59)

/** \brief  518, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH6    (0x0518U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH6.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH6.
 */
#define OSEE_TC_SRC_DMACH6          (OSEE_TC_SRC_DMA_DMA0_CH6)

/** \brief  5F0, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH60   (0x05F0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH60.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH60.
 */
#define OSEE_TC_SRC_DMACH60         (OSEE_TC_SRC_DMA_DMA0_CH60)

/** \brief  5F4, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH61   (0x05F4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH61.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH61.
 */
#define OSEE_TC_SRC_DMACH61         (OSEE_TC_SRC_DMA_DMA0_CH61)

/** \brief  5F8, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH62   (0x05F8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH62.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH62.
 */
#define OSEE_TC_SRC_DMACH62         (OSEE_TC_SRC_DMA_DMA0_CH62)

/** \brief  5FC, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH63   (0x05FCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH63.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH63.
 */
#define OSEE_TC_SRC_DMACH63         (OSEE_TC_SRC_DMA_DMA0_CH63)

/** \brief  600, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH64   (0x0600U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH64.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH64.
 */
#define OSEE_TC_SRC_DMACH64         (OSEE_TC_SRC_DMA_DMA0_CH64)

/** \brief  604, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH65   (0x0604U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH65.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH65.
 */
#define OSEE_TC_SRC_DMACH65         (OSEE_TC_SRC_DMA_DMA0_CH65)

/** \brief  608, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH66   (0x0608U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH66.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH66.
 */
#define OSEE_TC_SRC_DMACH66         (OSEE_TC_SRC_DMA_DMA0_CH66)

/** \brief  60C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH67   (0x060CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH67.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH67.
 */
#define OSEE_TC_SRC_DMACH67         (OSEE_TC_SRC_DMA_DMA0_CH67)

/** \brief  610, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH68   (0x0610U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH68.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH68.
 */
#define OSEE_TC_SRC_DMACH68         (OSEE_TC_SRC_DMA_DMA0_CH68)

/** \brief  614, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH69   (0x0614U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH69.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH69.
 */
#define OSEE_TC_SRC_DMACH69         (OSEE_TC_SRC_DMA_DMA0_CH69)

/** \brief  51C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH7    (0x051CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH7.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH7.
 */
#define OSEE_TC_SRC_DMACH7          (OSEE_TC_SRC_DMA_DMA0_CH7)

/** \brief  618, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH70   (0x0618U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH70.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH70.
 */
#define OSEE_TC_SRC_DMACH70         (OSEE_TC_SRC_DMA_DMA0_CH70)

/** \brief  61C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH71   (0x061CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH71.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH71.
 */
#define OSEE_TC_SRC_DMACH71         (OSEE_TC_SRC_DMA_DMA0_CH71)

/** \brief  620, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH72   (0x0620U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH72.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH72.
 */
#define OSEE_TC_SRC_DMACH72         (OSEE_TC_SRC_DMA_DMA0_CH72)

/** \brief  624, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH73   (0x0624U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH73.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH73.
 */
#define OSEE_TC_SRC_DMACH73         (OSEE_TC_SRC_DMA_DMA0_CH73)

/** \brief  628, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH74   (0x0628U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH74.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH74.
 */
#define OSEE_TC_SRC_DMACH74         (OSEE_TC_SRC_DMA_DMA0_CH74)

/** \brief  62C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH75   (0x062CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH75.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH75.
 */
#define OSEE_TC_SRC_DMACH75         (OSEE_TC_SRC_DMA_DMA0_CH75)

/** \brief  630, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH76   (0x0630U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH76.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH76.
 */
#define OSEE_TC_SRC_DMACH76         (OSEE_TC_SRC_DMA_DMA0_CH76)

/** \brief  634, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH77   (0x0634U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH77.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH77.
 */
#define OSEE_TC_SRC_DMACH77         (OSEE_TC_SRC_DMA_DMA0_CH77)

/** \brief  638, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH78   (0x0638U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH78.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH78.
 */
#define OSEE_TC_SRC_DMACH78         (OSEE_TC_SRC_DMA_DMA0_CH78)

/** \brief  63C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH79   (0x063CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH79.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH79.
 */
#define OSEE_TC_SRC_DMACH79         (OSEE_TC_SRC_DMA_DMA0_CH79)

/** \brief  520, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH8    (0x0520U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH8.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH8.
 */
#define OSEE_TC_SRC_DMACH8          (OSEE_TC_SRC_DMA_DMA0_CH8)

/** \brief  640, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH80   (0x0640U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH80.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH80.
 */
#define OSEE_TC_SRC_DMACH80         (OSEE_TC_SRC_DMA_DMA0_CH80)

/** \brief  644, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH81   (0x0644U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH81.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH81.
 */
#define OSEE_TC_SRC_DMACH81         (OSEE_TC_SRC_DMA_DMA0_CH81)

/** \brief  648, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH82   (0x0648U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH82.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH82.
 */
#define OSEE_TC_SRC_DMACH82         (OSEE_TC_SRC_DMA_DMA0_CH82)

/** \brief  64C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH83   (0x064CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH83.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH83.
 */
#define OSEE_TC_SRC_DMACH83         (OSEE_TC_SRC_DMA_DMA0_CH83)

/** \brief  650, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH84   (0x0650U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH84.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH84.
 */
#define OSEE_TC_SRC_DMACH84         (OSEE_TC_SRC_DMA_DMA0_CH84)

/** \brief  654, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH85   (0x0654U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH85.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH85.
 */
#define OSEE_TC_SRC_DMACH85         (OSEE_TC_SRC_DMA_DMA0_CH85)

/** \brief  658, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH86   (0x0658U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH86.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH86.
 */
#define OSEE_TC_SRC_DMACH86         (OSEE_TC_SRC_DMA_DMA0_CH86)

/** \brief  65C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH87   (0x065CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH87.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH87.
 */
#define OSEE_TC_SRC_DMACH87         (OSEE_TC_SRC_DMA_DMA0_CH87)

/** \brief  660, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH88   (0x0660U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH88.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH88.
 */
#define OSEE_TC_SRC_DMACH88         (OSEE_TC_SRC_DMA_DMA0_CH88)

/** \brief  664, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH89   (0x0664U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH89.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH89.
 */
#define OSEE_TC_SRC_DMACH89         (OSEE_TC_SRC_DMA_DMA0_CH89)

/** \brief  524, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH9    (0x0524U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH9.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH9.
 */
#define OSEE_TC_SRC_DMACH9          (OSEE_TC_SRC_DMA_DMA0_CH9)

/** \brief  668, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH90   (0x0668U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH90.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH90.
 */
#define OSEE_TC_SRC_DMACH90 (OSEE_TC_SRC_DMA_DMA0_CH90)

/** \brief  66C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH91   (0x066CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH91.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH91.
 */
#define OSEE_TC_SRC_DMACH91 (OSEE_TC_SRC_DMA_DMA0_CH91)

/** \brief  670, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH92   (0x0670U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH92.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH92.
 */
#define OSEE_TC_SRC_DMACH92         (OSEE_TC_SRC_DMA_DMA0_CH92)

/** \brief  674, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH93   (0x0674U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH93.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH93.
 */
#define OSEE_TC_SRC_DMACH93         (OSEE_TC_SRC_DMA_DMA0_CH93)

/** \brief  678, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH94   (0x0678U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH94.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH94.
 */
#define OSEE_TC_SRC_DMACH94         (OSEE_TC_SRC_DMA_DMA0_CH94)

/** \brief  67C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH95   (0x067CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH95.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH95.
 */
#define OSEE_TC_SRC_DMACH95         (OSEE_TC_SRC_DMA_DMA0_CH95)

/** \brief  680, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH96   (0x0680U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH96.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH96.
 */
#define OSEE_TC_SRC_DMACH96         (OSEE_TC_SRC_DMA_DMA0_CH96)

/** \brief  684, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH97   (0x0684U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH97.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH97.
 */
#define OSEE_TC_SRC_DMACH97         (OSEE_TC_SRC_DMA_DMA0_CH97)

/** \brief  688, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH98   (0x0688U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH98.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH98.
 */
#define OSEE_TC_SRC_DMACH98         (OSEE_TC_SRC_DMA_DMA0_CH98)

/** \brief  68C, DMA Channel Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH99   (0x068CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH99.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH99.
 */
#define OSEE_TC_SRC_DMACH99         (OSEE_TC_SRC_DMA_DMA0_CH99)

/** \brief  4F0, DMA Error Service Request */
#define OSEE_TC_SRC_DMA_DMA0_ERR    (0x04F0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_ERR.
 */
#define OSEE_TC_SRC_DMAERR          (OSEE_TC_SRC_DMA_DMA0_ERR)

/** \brief  B54, DSADC SRA Service Request */
#define OSEE_TC_SRC_DSADC_DSADC0_SRA  (0x0B54U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC0_SRA.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC0_SRA.
 */
#define OSEE_TC_SRC_DSADCSRA0       (OSEE_TC_SRC_DSADC_DSADC0_SRA)

/** \brief  B50, DSADC SRM Service Request */
#define OSEE_TC_SRC_DSADC_DSADC0_SRM  (0x0B50U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC0_SRM.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC0_SRM.
 */
#define OSEE_TC_SRC_DSADCSRM0       (OSEE_TC_SRC_DSADC_DSADC0_SRM)

/** \brief  B5C, DSADC SRA Service Request */
#define OSEE_TC_SRC_DSADC_DSADC1_SRA  (0x0B5CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC1_SRA.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC1_SRA.
 */
#define OSEE_TC_SRC_DSADCSRA1       (OSEE_TC_SRC_DSADC_DSADC1_SRA)

/** \brief  B58, DSADC SRM Service Request */
#define OSEE_TC_SRC_DSADC_DSADC1_SRM  (0x0B58U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC1_SRM.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC1_SRM.
 */
#define OSEE_TC_SRC_DSADCSRM1       (OSEE_TC_SRC_DSADC_DSADC1_SRM)

/** \brief  B64, DSADC SRA Service Request */
#define OSEE_TC_SRC_DSADC_DSADC2_SRA  (0x0B64U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC2_SRA.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC2_SRA.
 */
#define OSEE_TC_SRC_DSADCSRA2       (OSEE_TC_SRC_DSADC_DSADC2_SRA)

/** \brief  B60, DSADC SRM Service Request */
#define OSEE_TC_SRC_DSADC_DSADC2_SRM  (0x0B60U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC2_SRM.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC2_SRM.
 */
#define OSEE_TC_SRC_DSADCSRM2       (OSEE_TC_SRC_DSADC_DSADC2_SRM)

/** \brief  B6C, DSADC SRA Service Request */
#define OSEE_TC_SRC_DSADC_DSADC3_SRA  (0x0B6CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC3_SRA.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC3_SRA.
 */
#define OSEE_TC_SRC_DSADCSRA3       (OSEE_TC_SRC_DSADC_DSADC3_SRA)

/** \brief  B68, DSADC SRM Service Request */
#define OSEE_TC_SRC_DSADC_DSADC3_SRM  (0x0B68U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC3_SRM.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC3_SRM.
 */
#define OSEE_TC_SRC_DSADCSRM3       (OSEE_TC_SRC_DSADC_DSADC3_SRM)

/** \brief  B74, DSADC SRA Service Request */
#define OSEE_TC_SRC_DSADC_DSADC4_SRA  (0x0B74U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC4_SRA.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC4_SRA.
 */
#define OSEE_TC_SRC_DSADCSRA4       (OSEE_TC_SRC_DSADC_DSADC4_SRA)

/** \brief  B70, DSADC SRM Service Request */
#define OSEE_TC_SRC_DSADC_DSADC4_SRM    (0x0B70U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC4_SRM.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC4_SRM.
 */
#define OSEE_TC_SRC_DSADCSRM4 (OSEE_TC_SRC_DSADC_DSADC4_SRM)

/** \brief  B7C, DSADC SRA Service Request */
#define OSEE_TC_SRC_DSADC_DSADC5_SRA    (0x0B7CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC5_SRA.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC5_SRA.
 */
#define OSEE_TC_SRC_DSADCSRA5 (OSEE_TC_SRC_DSADC_DSADC5_SRA)

/** \brief  B78, DSADC SRM Service Request */
#define OSEE_TC_SRC_DSADC_DSADC5_SRM    (0x0B78U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC5_SRM.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC5_SRM.
 */
#define OSEE_TC_SRC_DSADCSRM5 (OSEE_TC_SRC_DSADC_DSADC5_SRM)

/** \brief  B84, DSADC SRA Service Request */
#define OSEE_TC_SRC_DSADC_DSADC6_SRA    (0x0B84U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC6_SRA.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC6_SRA.
 */
#define OSEE_TC_SRC_DSADCSRA6 (OSEE_TC_SRC_DSADC_DSADC6_SRA)

/** \brief  B80, DSADC SRM Service Request */
#define OSEE_TC_SRC_DSADC_DSADC6_SRM    (0x0B80U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC6_SRM.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC6_SRM.
 */
#define OSEE_TC_SRC_DSADCSRM6 (OSEE_TC_SRC_DSADC_DSADC6_SRM)

/** \brief  B8C, DSADC SRA Service Request */
#define OSEE_TC_SRC_DSADC_DSADC7_SRA    (0x0B8CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC7_SRA.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC7_SRA.
 */
#define OSEE_TC_SRC_DSADCSRA7 (OSEE_TC_SRC_DSADC_DSADC7_SRA)

/** \brief  B88, DSADC SRM Service Request */
#define OSEE_TC_SRC_DSADC_DSADC7_SRM    (0x0B88U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC7_SRM.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC7_SRM.
 */
#define OSEE_TC_SRC_DSADCSRM7 (OSEE_TC_SRC_DSADC_DSADC7_SRM)

/** \brief  B94, DSADC SRA Service Request */
#define OSEE_TC_SRC_DSADC_DSADC8_SRA    (0x0B94U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC8_SRA.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC8_SRA.
 */
#define OSEE_TC_SRC_DSADCSRA8 (OSEE_TC_SRC_DSADC_DSADC8_SRA)

/** \brief  B90, DSADC SRM Service Request */
#define OSEE_TC_SRC_DSADC_DSADC8_SRM    (0x0B90U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC8_SRM.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC8_SRM.
 */
#define OSEE_TC_SRC_DSADCSRM8 (OSEE_TC_SRC_DSADC_DSADC8_SRM)

/** \brief  B9C, DSADC SRA Service Request */
#define OSEE_TC_SRC_DSADC_DSADC9_SRA    (0x0B9CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC9_SRA.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC9_SRA.
 */
#define OSEE_TC_SRC_DSADCSRA9 (OSEE_TC_SRC_DSADC_DSADC9_SRA)

/** \brief  B98, DSADC SRM Service Request */
#define OSEE_TC_SRC_DSADC_DSADC9_SRM    (0x0B98U)

/** Alias (User Manual Name) for OSEE_TC_SRC_DSADC_DSADC9_SRM.
 * To use register names with standard convention, please use OSEE_TC_SRC_DSADC_DSADC9_SRM.
 */
#define OSEE_TC_SRC_DSADCSRM9 (OSEE_TC_SRC_DSADC_DSADC9_SRM)

/** \brief  20, Emulation Memory Service Request */
#define OSEE_TC_SRC_EMEM_EMEM0_SR    (0x0020U)

/** Alias (User Manual Name) for OSEE_TC_SRC_EMEM_EMEM0_SR.
 * To use register names with standard convention, please use OSEE_TC_SRC_EMEM_EMEM0_SR.
 */
#define OSEE_TC_SRC_EMEM  (OSEE_TC_SRC_EMEM_EMEM0_SR)

/** \brief  C04, E-RAY Input Buffer Busy Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_IBUSY    (0x0C04U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_IBUSY.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_IBUSY.
 */
#define OSEE_TC_SRC_ERAY0IBUSY  (OSEE_TC_SRC_ERAY_ERAY0_IBUSY)

/** \brief  BE0, E-RAY  Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_INT0    (0x0BE0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_INT0.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_INT0.
 */
#define OSEE_TC_SRC_ERAY0INT0 (OSEE_TC_SRC_ERAY_ERAY0_INT0)

/** \brief  BE4, E-RAY  Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_INT1    (0x0BE4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_INT1.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_INT1.
 */
#define OSEE_TC_SRC_ERAY0INT1 (OSEE_TC_SRC_ERAY_ERAY0_INT1)

/** \brief  BF8, E-RAY  Message Buffer Status Changed Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_MBSC0    (0x0BF8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_MBSC0.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_MBSC0.
 */
#define OSEE_TC_SRC_ERAY0MBSC0          (OSEE_TC_SRC_ERAY_ERAY0_MBSC0)

/** \brief  BFC, E-RAY  Message Buffer Status Changed Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_MBSC1    (0x0BFCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_MBSC1.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_MBSC1.
 */
#define OSEE_TC_SRC_ERAY0MBSC1          (OSEE_TC_SRC_ERAY_ERAY0_MBSC1)

/** \brief  BF0, E-RAY  New Data Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_NDAT0    (0x0BF0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_NDAT0.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_NDAT0.
 */
#define OSEE_TC_SRC_ERAY0NDAT0          (OSEE_TC_SRC_ERAY_ERAY0_NDAT0)

/** \brief  BF4, E-RAY  New Data Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_NDAT1    (0x0BF4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_NDAT1.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_NDAT1.
 */
#define OSEE_TC_SRC_ERAY0NDAT1          (OSEE_TC_SRC_ERAY_ERAY0_NDAT1)

/** \brief  C00, E-RAY Output Buffer Busy Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_OBUSY    (0x0C00U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_OBUSY.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_OBUSY.
 */
#define OSEE_TC_SRC_ERAY0OBUSY  (OSEE_TC_SRC_ERAY_ERAY0_OBUSY)

/** \brief  BE8, E-RAY  Timer Interrupt Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_TINT0    (0x0BE8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_TINT0.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_TINT0.
 */
#define OSEE_TC_SRC_ERAY0TINT0          (OSEE_TC_SRC_ERAY_ERAY0_TINT0)

/** \brief  BEC, E-RAY  Timer Interrupt Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_TINT1    (0x0BECU)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_TINT1.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_TINT1.
 */
#define OSEE_TC_SRC_ERAY0TINT1          (OSEE_TC_SRC_ERAY_ERAY0_TINT1)

/** \brief  C2C, E-RAY Input Buffer Busy Service Request */
#define OSEE_TC_SRC_ERAY_ERAY1_IBUSY    (0x0C2CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY1_IBUSY.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY1_IBUSY.
 */
#define OSEE_TC_SRC_ERAY1IBUSY  (OSEE_TC_SRC_ERAY_ERAY1_IBUSY)

/** \brief  C08, E-RAY  Service Request */
#define OSEE_TC_SRC_ERAY_ERAY1_INT0    (0x0C08U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY1_INT0.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY1_INT0.
 */
#define OSEE_TC_SRC_ERAY1INT0 (OSEE_TC_SRC_ERAY_ERAY1_INT0)

/** \brief  C0C, E-RAY  Service Request */
#define OSEE_TC_SRC_ERAY_ERAY1_INT1    (0x0C0CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY1_INT1.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY1_INT1.
 */
#define OSEE_TC_SRC_ERAY1INT1 (OSEE_TC_SRC_ERAY_ERAY1_INT1)

/** \brief  C20, E-RAY  Message Buffer Status Changed Service Request */
#define OSEE_TC_SRC_ERAY_ERAY1_MBSC0   (0x0C20U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY1_MBSC0.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY1_MBSC0.
 */
#define OSEE_TC_SRC_ERAY1MBSC0  (OSEE_TC_SRC_ERAY_ERAY1_MBSC0)

/** \brief  C24, E-RAY  Message Buffer Status Changed Service Request */
#define OSEE_TC_SRC_ERAY_ERAY1_MBSC1   (0x0C24U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY1_MBSC1.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY1_MBSC1.
 */
#define OSEE_TC_SRC_ERAY1MBSC1  (OSEE_TC_SRC_ERAY_ERAY1_MBSC1)

/** \brief  C18, E-RAY  New Data Service Request */
#define OSEE_TC_SRC_ERAY_ERAY1_NDAT0   (0x0C18U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY1_NDAT0.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY1_NDAT0.
 */
#define OSEE_TC_SRC_ERAY1NDAT0  (OSEE_TC_SRC_ERAY_ERAY1_NDAT0)

/** \brief  C1C, E-RAY  New Data Service Request */
#define OSEE_TC_SRC_ERAY_ERAY1_NDAT1   (0x0C1CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY1_NDAT1.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY1_NDAT1.
 */
#define OSEE_TC_SRC_ERAY1NDAT1  (OSEE_TC_SRC_ERAY_ERAY1_NDAT1)

/** \brief  C28, E-RAY Output Buffer Busy Service Request */
#define OSEE_TC_SRC_ERAY_ERAY1_OBUSY    (0x0C28U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY1_OBUSY.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY1_OBUSY.
 */
#define OSEE_TC_SRC_ERAY1OBUSY  (OSEE_TC_SRC_ERAY_ERAY1_OBUSY)

/** \brief  C10, E-RAY  Timer Interrupt Service Request */
#define OSEE_TC_SRC_ERAY_ERAY1_TINT0    (0x0C10U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY1_TINT0.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY1_TINT0.
 */
#define OSEE_TC_SRC_ERAY1TINT0  (OSEE_TC_SRC_ERAY_ERAY1_TINT0)

/** \brief  C14, E-RAY  Timer Interrupt Service Request */
#define OSEE_TC_SRC_ERAY_ERAY1_TINT1    (0x0C14U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY1_TINT1.
 * To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY1_TINT1.
 */
#define OSEE_TC_SRC_ERAY1TINT1  (OSEE_TC_SRC_ERAY_ERAY1_TINT1)

/** \brief  8F0, Ethernet Service Request */
#define OSEE_TC_SRC_ETH_ETH0_SR    (0x08F0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_ETH_ETH0_SR.
 * To use register names with standard convention, please use OSEE_TC_SRC_ETH_ETH0_SR.
 */
#define OSEE_TC_SRC_ETH (OSEE_TC_SRC_ETH_ETH0_SR)

/** \brief  4B0, FCE Error Service Request */
#define OSEE_TC_SRC_FCE_FCE0_SR    (0x04B0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_FCE_FCE0_SR.
 * To use register names with standard convention, please use OSEE_TC_SRC_FCE_FCE0_SR.
 */
#define OSEE_TC_SRC_FCE (OSEE_TC_SRC_FCE_FCE0_SR)

/** \brief  FC0, FFT Done Service Request */
#define OSEE_TC_SRC_FFT_FFT0_DONE    (0x0FC0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_FFT_FFT0_DONE.
 * To use register names with standard convention, please use OSEE_TC_SRC_FFT_FFT0_DONE.
 */
#define OSEE_TC_SRC_FFTDONE (OSEE_TC_SRC_FFT_FFT0_DONE)

/** \brief  FC4, FFT Error Service Request */
#define OSEE_TC_SRC_FFT_FFT0_ERR    (0x0FC4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_FFT_FFT0_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_FFT_FFT0_ERR.
 */
#define OSEE_TC_SRC_FFTERR  (OSEE_TC_SRC_FFT_FFT0_ERR)

/** \brief  FC8, FFT Ready For Start Service Request */
#define OSEE_TC_SRC_FFT_FFT0_RFS    (0x0FC8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_FFT_FFT0_RFS.
 * To use register names with standard convention, please use OSEE_TC_SRC_FFT_FFT0_RFS.
 */
#define OSEE_TC_SRC_FFTRFS  (OSEE_TC_SRC_FFT_FFT0_RFS)

/** \brief  1000, General Purpose Service Request 0 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR0  (0x1000U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR0.
 */
#define OSEE_TC_SRC_GPSR00  (OSEE_TC_SRC_GPSR_GPSR0_SR0)

/** \brief  1004, General Purpose Service Request 1 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR1   (0x1004U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR1.
 */
#define OSEE_TC_SRC_GPSR01  (OSEE_TC_SRC_GPSR_GPSR0_SR1)

/** \brief  1008, General Purpose Service Request 2 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR2   (0x1008U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR2.
 */
#define OSEE_TC_SRC_GPSR02  (OSEE_TC_SRC_GPSR_GPSR0_SR2)

/** \brief  100C, General Purpose Service Request 3 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR3   (0x100CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR3.
 */
#define OSEE_TC_SRC_GPSR03  (OSEE_TC_SRC_GPSR_GPSR0_SR3)

/** \brief  1020, General Purpose Service Request 0 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR0  (0x1020U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR0.
 */
#define OSEE_TC_SRC_GPSR10  (OSEE_TC_SRC_GPSR_GPSR1_SR0)

/** \brief  1024, General Purpose Service Request 1 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR1  (0x1024U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR1.
 */
#define OSEE_TC_SRC_GPSR11  (OSEE_TC_SRC_GPSR_GPSR1_SR1)

/** \brief  1028, General Purpose Service Request 2 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR2  (0x1028U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR2.
 */
#define OSEE_TC_SRC_GPSR12  (OSEE_TC_SRC_GPSR_GPSR1_SR2)

/** \brief  102C, General Purpose Service Request 3 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR3  (0x102CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR3.
 */
#define OSEE_TC_SRC_GPSR13  (OSEE_TC_SRC_GPSR_GPSR1_SR3)

/** \brief  1040, General Purpose Service Request 0 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR0  (0x1040U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR0.
 */
#define OSEE_TC_SRC_GPSR20  (OSEE_TC_SRC_GPSR_GPSR2_SR0)

/** \brief  1044, General Purpose Service Request 1 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR1  (0x1044U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR1.
 */
#define OSEE_TC_SRC_GPSR21  (OSEE_TC_SRC_GPSR_GPSR2_SR1)

/** \brief  1048, General Purpose Service Request 2 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR2  (0x1048U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR2.
 */
#define OSEE_TC_SRC_GPSR22  (OSEE_TC_SRC_GPSR_GPSR2_SR2)

/** \brief  104C, General Purpose Service Request 3 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR3  (0x104CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR3.
 */
#define OSEE_TC_SRC_GPSR23  (OSEE_TC_SRC_GPSR_GPSR2_SR3)

/** \brief  460, GPT12 CAPREL Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_CIRQ    (0x0460U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_CIRQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_CIRQ.
 */
#define OSEE_TC_SRC_GPT120CIRQ  (OSEE_TC_SRC_GPT12_GPT120_CIRQ)

/** \brief  464, GPT12 T2 Overflow/Underflow Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_T2    (0x0464U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_T2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_T2.
 */
#define OSEE_TC_SRC_GPT120T2  (OSEE_TC_SRC_GPT12_GPT120_T2)

/** \brief  468, GPT12 T3 Overflow/Underflow Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_T3    (0x0468U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_T3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_T3.
 */
#define OSEE_TC_SRC_GPT120T3  (OSEE_TC_SRC_GPT12_GPT120_T3)

/** \brief  46C, GPT12 T4 Overflow/Underflow Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_T4    (0x046CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_T4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_T4.
 */
#define OSEE_TC_SRC_GPT120T4  (OSEE_TC_SRC_GPT12_GPT120_T4)

/** \brief  470, GPT12 T5 Overflow/Underflow Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_T5    (0x0470U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_T5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_T5.
 */
#define OSEE_TC_SRC_GPT120T5  (OSEE_TC_SRC_GPT12_GPT120_T5)

/** \brief  474, GPT12 T6 Overflow/Underflow Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_T6    (0x0474U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_T6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_T6.
 */
#define OSEE_TC_SRC_GPT120T6  (OSEE_TC_SRC_GPT12_GPT120_T6)

/** \brief  1600, GTM AEI Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_AEIIRQ  (0x1600U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_AEIIRQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_AEIIRQ.
 */
#define OSEE_TC_SRC_GTMAEIIRQ (OSEE_TC_SRC_GTM_GTM0_AEIIRQ)

/** \brief  1604, GTM ARU Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ARUIRQ0  (0x1604U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ARUIRQ0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ARUIRQ0.
 */
#define OSEE_TC_SRC_GTMARUIRQ0  (OSEE_TC_SRC_GTM_GTM0_ARUIRQ0)

/** \brief  1608, GTM ARU Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ARUIRQ1  (0x1608U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ARUIRQ1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ARUIRQ1.
 */
#define OSEE_TC_SRC_GTMARUIRQ1  (OSEE_TC_SRC_GTM_GTM0_ARUIRQ1)

/** \brief  160C, GTM ARU Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ARUIRQ2  (0x160CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ARUIRQ2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ARUIRQ2.
 */
#define OSEE_TC_SRC_GTMARUIRQ2  (OSEE_TC_SRC_GTM_GTM0_ARUIRQ2)

/** \brief  1D80, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM0_0  (0x1D80U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM0_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM0_0.
 */
#define OSEE_TC_SRC_GTMATOM00 (OSEE_TC_SRC_GTM_GTM0_ATOM0_0)

/** \brief  1D84, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM0_1  (0x1D84U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM0_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM0_1.
 */
#define OSEE_TC_SRC_GTMATOM01 (OSEE_TC_SRC_GTM_GTM0_ATOM0_1)

/** \brief  1D88, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM0_2  (0x1D88U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM0_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM0_2.
 */
#define OSEE_TC_SRC_GTMATOM02 (OSEE_TC_SRC_GTM_GTM0_ATOM0_2)

/** \brief  1D8C, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM0_3  (0x1D8CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM0_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM0_3.
 */
#define OSEE_TC_SRC_GTMATOM03 (OSEE_TC_SRC_GTM_GTM0_ATOM0_3)

/** \brief  1D90, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM1_0  (0x1D90U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM1_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM1_0.
 */
#define OSEE_TC_SRC_GTMATOM10 (OSEE_TC_SRC_GTM_GTM0_ATOM1_0)

/** \brief  1D94, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM1_1  (0x1D94U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM1_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM1_1.
 */
#define OSEE_TC_SRC_GTMATOM11 (OSEE_TC_SRC_GTM_GTM0_ATOM1_1)

/** \brief  1D98, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM1_2  (0x1D98U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM1_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM1_2.
 */
#define OSEE_TC_SRC_GTMATOM12 (OSEE_TC_SRC_GTM_GTM0_ATOM1_2)

/** \brief  1D9C, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM1_3  (0x1D9CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM1_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM1_3.
 */
#define OSEE_TC_SRC_GTMATOM13 (OSEE_TC_SRC_GTM_GTM0_ATOM1_3)

/** \brief  1DA0, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM2_0  (0x1DA0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM2_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM2_0.
 */
#define OSEE_TC_SRC_GTMATOM20 (OSEE_TC_SRC_GTM_GTM0_ATOM2_0)

/** \brief  1DA4, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM2_1  (0x1DA4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM2_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM2_1.
 */
#define OSEE_TC_SRC_GTMATOM21 (OSEE_TC_SRC_GTM_GTM0_ATOM2_1)

/** \brief  1DA8, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM2_2  (0x1DA8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM2_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM2_2.
 */
#define OSEE_TC_SRC_GTMATOM22 (OSEE_TC_SRC_GTM_GTM0_ATOM2_2)

/** \brief  1DAC, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM2_3  (0x1DACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM2_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM2_3.
 */
#define OSEE_TC_SRC_GTMATOM23 (OSEE_TC_SRC_GTM_GTM0_ATOM2_3)

/** \brief  1DB0, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM3_0  (0x1DB0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM3_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM3_0.
 */
#define OSEE_TC_SRC_GTMATOM30 (OSEE_TC_SRC_GTM_GTM0_ATOM3_0)

/** \brief  1DB4, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM3_1  (0x1DB4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM3_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM3_1.
 */
#define OSEE_TC_SRC_GTMATOM31 (OSEE_TC_SRC_GTM_GTM0_ATOM3_1)

/** \brief  1DB8, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM3_2  (0x1DB8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM3_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM3_2.
 */
#define OSEE_TC_SRC_GTMATOM32 (OSEE_TC_SRC_GTM_GTM0_ATOM3_2)

/** \brief  1DBC, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM3_3  (0x1DBCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM3_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM3_3.
 */
#define OSEE_TC_SRC_GTMATOM33 (OSEE_TC_SRC_GTM_GTM0_ATOM3_3)

/** \brief  1DC0, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM4_0  (0x1DC0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM4_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM4_0.
 */
#define OSEE_TC_SRC_GTMATOM40 (OSEE_TC_SRC_GTM_GTM0_ATOM4_0)

/** \brief  1DC4, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM4_1  (0x1DC4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM4_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM4_1.
 */
#define OSEE_TC_SRC_GTMATOM41 (OSEE_TC_SRC_GTM_GTM0_ATOM4_1)

/** \brief  1DC8, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM4_2  (0x1DC8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM4_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM4_2.
 */
#define OSEE_TC_SRC_GTMATOM42 (OSEE_TC_SRC_GTM_GTM0_ATOM4_2)

/** \brief  1DCC, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM4_3  (0x1DCCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM4_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM4_3.
 */
#define OSEE_TC_SRC_GTMATOM43 (OSEE_TC_SRC_GTM_GTM0_ATOM4_3)

/** \brief  1DD0, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM5_0  (0x1DD0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM5_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM5_0.
 */
#define OSEE_TC_SRC_GTMATOM50 (OSEE_TC_SRC_GTM_GTM0_ATOM5_0)

/** \brief  1DD4, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM5_1  (0x1DD4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM5_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM5_1.
 */
#define OSEE_TC_SRC_GTMATOM51 (OSEE_TC_SRC_GTM_GTM0_ATOM5_1)

/** \brief  1DD8, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM5_2  (0x1DD8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM5_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM5_2.
 */
#define OSEE_TC_SRC_GTMATOM52 (OSEE_TC_SRC_GTM_GTM0_ATOM5_2)

/** \brief  1DDC, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM5_3  (0x1DDCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM5_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM5_3.
 */
#define OSEE_TC_SRC_GTMATOM53 (OSEE_TC_SRC_GTM_GTM0_ATOM5_3)

/** \brief  1DE0, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM6_0  (0x1DE0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM6_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM6_0.
 */
#define OSEE_TC_SRC_GTMATOM60 (OSEE_TC_SRC_GTM_GTM0_ATOM6_0)

/** \brief  1DE4, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM6_1  (0x1DE4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM6_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM6_1.
 */
#define OSEE_TC_SRC_GTMATOM61 (OSEE_TC_SRC_GTM_GTM0_ATOM6_1)

/** \brief  1DE8, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM6_2  (0x1DE8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM6_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM6_2.
 */
#define OSEE_TC_SRC_GTMATOM62 (OSEE_TC_SRC_GTM_GTM0_ATOM6_2)

/** \brief  1DEC, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM6_3  (0x1DECU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM6_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM6_3.
 */
#define OSEE_TC_SRC_GTMATOM63 (OSEE_TC_SRC_GTM_GTM0_ATOM6_3)

/** \brief  1DF0, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM7_0  (0x1DF0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM7_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM7_0.
 */
#define OSEE_TC_SRC_GTMATOM70 (OSEE_TC_SRC_GTM_GTM0_ATOM7_0)

/** \brief  1DF4, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM7_1  (0x1DF4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM7_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM7_1.
 */
#define OSEE_TC_SRC_GTMATOM71 (OSEE_TC_SRC_GTM_GTM0_ATOM7_1)

/** \brief  1DF8, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM7_2  (0x1DF8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM7_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM7_2.
 */
#define OSEE_TC_SRC_GTMATOM72 (OSEE_TC_SRC_GTM_GTM0_ATOM7_2)

/** \brief  1DFC, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM7_3  (0x1DFCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM7_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM7_3.
 */
#define OSEE_TC_SRC_GTMATOM73 (OSEE_TC_SRC_GTM_GTM0_ATOM7_3)

/** \brief  1E00, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM8_0  (0x1E00U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM8_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM8_0.
 */
#define OSEE_TC_SRC_GTMATOM80 (OSEE_TC_SRC_GTM_GTM0_ATOM8_0)

/** \brief  1E04, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM8_1  (0x1E04U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM8_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM8_1.
 */
#define OSEE_TC_SRC_GTMATOM81 (OSEE_TC_SRC_GTM_GTM0_ATOM8_1)

/** \brief  1E08, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM8_2  (0x1E08U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM8_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM8_2.
 */
#define OSEE_TC_SRC_GTMATOM82 (OSEE_TC_SRC_GTM_GTM0_ATOM8_2)

/** \brief  1E0C, GTM ATOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ATOM8_3  (0x1E0CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ATOM8_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ATOM8_3.
 */
#define OSEE_TC_SRC_GTMATOM83 (OSEE_TC_SRC_GTM_GTM0_ATOM8_3)

/** \brief  1614, GTM BRC Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_BRCIRQ  (0x1614U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_BRCIRQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_BRCIRQ.
 */
#define OSEE_TC_SRC_GTMBRCIRQ (OSEE_TC_SRC_GTM_GTM0_BRCIRQ)

/** \brief  1618, GTM CMP Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_CMPIRQ  (0x1618U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_CMPIRQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_CMPIRQ.
 */
#define OSEE_TC_SRC_GTMCMPIRQ (OSEE_TC_SRC_GTM_GTM0_CMPIRQ)

/** \brief  16A4, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL0  (0x16A4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL0.
 */
#define OSEE_TC_SRC_GTMDPLL0  (OSEE_TC_SRC_GTM_GTM0_DPLL0)

/** \brief  16A8, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL1  (0x16A8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL1.
 */
#define OSEE_TC_SRC_GTMDPLL1  (OSEE_TC_SRC_GTM_GTM0_DPLL1)

/** \brief  16CC, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL10  (0x16CCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL10.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL10.
 */
#define OSEE_TC_SRC_GTMDPLL10 (OSEE_TC_SRC_GTM_GTM0_DPLL10)

/** \brief  16D0, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL11  (0x16D0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL11.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL11.
 */
#define OSEE_TC_SRC_GTMDPLL11 (OSEE_TC_SRC_GTM_GTM0_DPLL11)

/** \brief  16D4, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL12  (0x16D4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL12.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL12.
 */
#define OSEE_TC_SRC_GTMDPLL12 (OSEE_TC_SRC_GTM_GTM0_DPLL12)

/** \brief  16D8, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL13  (0x16D8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL13.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL13.
 */
#define OSEE_TC_SRC_GTMDPLL13 (OSEE_TC_SRC_GTM_GTM0_DPLL13)

/** \brief  16DC, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL14  (0x16DCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL14.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL14.
 */
#define OSEE_TC_SRC_GTMDPLL14 (OSEE_TC_SRC_GTM_GTM0_DPLL14)

/** \brief  16E0, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL15  (0x16E0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL15.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL15.
 */
#define OSEE_TC_SRC_GTMDPLL15 (OSEE_TC_SRC_GTM_GTM0_DPLL15)

/** \brief  16E4, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL16  (0x16E4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL16.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL16.
 */
#define OSEE_TC_SRC_GTMDPLL16 (OSEE_TC_SRC_GTM_GTM0_DPLL16)

/** \brief  16E8, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL17  (0x16E8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL17.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL17.
 */
#define OSEE_TC_SRC_GTMDPLL17 (OSEE_TC_SRC_GTM_GTM0_DPLL17)

/** \brief  16EC, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL18  (0x16ECU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL18.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL18.
 */
#define OSEE_TC_SRC_GTMDPLL18 (OSEE_TC_SRC_GTM_GTM0_DPLL18)

/** \brief  16F0, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL19  (0x16F0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL19.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL19.
 */
#define OSEE_TC_SRC_GTMDPLL19 (OSEE_TC_SRC_GTM_GTM0_DPLL19)

/** \brief  16AC, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL2  (0x16ACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL2.
 */
#define OSEE_TC_SRC_GTMDPLL2  (OSEE_TC_SRC_GTM_GTM0_DPLL2)

/** \brief  16F4, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL20  (0x16F4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL20.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL20.
 */
#define OSEE_TC_SRC_GTMDPLL20 (OSEE_TC_SRC_GTM_GTM0_DPLL20)

/** \brief  16F8, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL21  (0x16F8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL21.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL21.
 */
#define OSEE_TC_SRC_GTMDPLL21 (OSEE_TC_SRC_GTM_GTM0_DPLL21)

/** \brief  16FC, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL22  (0x16FCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL22.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL22.
 */
#define OSEE_TC_SRC_GTMDPLL22 (OSEE_TC_SRC_GTM_GTM0_DPLL22)

/** \brief  1700, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL23  (0x1700U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL23.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL23.
 */
#define OSEE_TC_SRC_GTMDPLL23 (OSEE_TC_SRC_GTM_GTM0_DPLL23)

/** \brief  1704, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL24  (0x1704U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL24.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL24.
 */
#define OSEE_TC_SRC_GTMDPLL24 (OSEE_TC_SRC_GTM_GTM0_DPLL24)

/** \brief  1708, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL25  (0x1708U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL25.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL25.
 */
#define OSEE_TC_SRC_GTMDPLL25 (OSEE_TC_SRC_GTM_GTM0_DPLL25)

/** \brief  170C, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL26  (0x170CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL26.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL26.
 */
#define OSEE_TC_SRC_GTMDPLL26 (OSEE_TC_SRC_GTM_GTM0_DPLL26)

/** \brief  16B0, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL3  (0x16B0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL3.
 */
#define OSEE_TC_SRC_GTMDPLL3  (OSEE_TC_SRC_GTM_GTM0_DPLL3)

/** \brief  16B4, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL4  (0x16B4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL4.
 */
#define OSEE_TC_SRC_GTMDPLL4  (OSEE_TC_SRC_GTM_GTM0_DPLL4)

/** \brief  16B8, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL5  (0x16B8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL5.
 */
#define OSEE_TC_SRC_GTMDPLL5  (OSEE_TC_SRC_GTM_GTM0_DPLL5)

/** \brief  16BC, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL6  (0x16BCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL6.
 */
#define OSEE_TC_SRC_GTMDPLL6  (OSEE_TC_SRC_GTM_GTM0_DPLL6)

/** \brief  16C0, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL7  (0x16C0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL7.
 */
#define OSEE_TC_SRC_GTMDPLL7  (OSEE_TC_SRC_GTM_GTM0_DPLL7)

/** \brief  16C4, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL8  (0x16C4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL8.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL8.
 */
#define OSEE_TC_SRC_GTMDPLL8  (OSEE_TC_SRC_GTM_GTM0_DPLL8)

/** \brief  16C8, GTM DPLL Service Request */
#define OSEE_TC_SRC_GTM_GTM0_DPLL9  (0x16C8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_DPLL9.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_DPLL9.
 */
#define OSEE_TC_SRC_GTMDPLL9  (OSEE_TC_SRC_GTM_GTM0_DPLL9)

/** \brief  1770, GTM Error Service Request */
#define OSEE_TC_SRC_GTM_GTM0_ERR  (0x1770U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_ERR.
 */
#define OSEE_TC_SRC_GTMERR  (OSEE_TC_SRC_GTM_GTM0_ERR)

/** \brief  1980, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS0_0  (0x1980U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS0_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS0_0.
 */
#define OSEE_TC_SRC_GTMMCS00  (OSEE_TC_SRC_GTM_GTM0_MCS0_0)

/** \brief  1984, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS0_1  (0x1984U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS0_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS0_1.
 */
#define OSEE_TC_SRC_GTMMCS01  (OSEE_TC_SRC_GTM_GTM0_MCS0_1)

/** \brief  1988, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS0_2  (0x1988U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS0_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS0_2.
 */
#define OSEE_TC_SRC_GTMMCS02  (OSEE_TC_SRC_GTM_GTM0_MCS0_2)

/** \brief  198C, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS0_3  (0x198CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS0_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS0_3.
 */
#define OSEE_TC_SRC_GTMMCS03  (OSEE_TC_SRC_GTM_GTM0_MCS0_3)

/** \brief  1990, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS0_4  (0x1990U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS0_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS0_4.
 */
#define OSEE_TC_SRC_GTMMCS04  (OSEE_TC_SRC_GTM_GTM0_MCS0_4)

/** \brief  1994, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS0_5  (0x1994U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS0_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS0_5.
 */
#define OSEE_TC_SRC_GTMMCS05  (OSEE_TC_SRC_GTM_GTM0_MCS0_5)

/** \brief  1998, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS0_6  (0x1998U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS0_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS0_6.
 */
#define OSEE_TC_SRC_GTMMCS06  (OSEE_TC_SRC_GTM_GTM0_MCS0_6)

/** \brief  199C, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS0_7  (0x199CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS0_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS0_7.
 */
#define OSEE_TC_SRC_GTMMCS07  (OSEE_TC_SRC_GTM_GTM0_MCS0_7)

/** \brief  19A0, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS1_0  (0x19A0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS1_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS1_0.
 */
#define OSEE_TC_SRC_GTMMCS10  (OSEE_TC_SRC_GTM_GTM0_MCS1_0)

/** \brief  19A4, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS1_1  (0x19A4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS1_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS1_1.
 */
#define OSEE_TC_SRC_GTMMCS11  (OSEE_TC_SRC_GTM_GTM0_MCS1_1)

/** \brief  19A8, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS1_2  (0x19A8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS1_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS1_2.
 */
#define OSEE_TC_SRC_GTMMCS12  (OSEE_TC_SRC_GTM_GTM0_MCS1_2)

/** \brief  19AC, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS1_3  (0x19ACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS1_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS1_3.
 */
#define OSEE_TC_SRC_GTMMCS13  (OSEE_TC_SRC_GTM_GTM0_MCS1_3)

/** \brief  19B0, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS1_4  (0x19B0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS1_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS1_4.
 */
#define OSEE_TC_SRC_GTMMCS14  (OSEE_TC_SRC_GTM_GTM0_MCS1_4)

/** \brief  19B4, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS1_5  (0x19B4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS1_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS1_5.
 */
#define OSEE_TC_SRC_GTMMCS15  (OSEE_TC_SRC_GTM_GTM0_MCS1_5)

/** \brief  19B8, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS1_6  (0x19B8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS1_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS1_6.
 */
#define OSEE_TC_SRC_GTMMCS16  (OSEE_TC_SRC_GTM_GTM0_MCS1_6)

/** \brief  19BC, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS1_7  (0x19BCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS1_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS1_7.
 */
#define OSEE_TC_SRC_GTMMCS17  (OSEE_TC_SRC_GTM_GTM0_MCS1_7)

/** \brief  19C0, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS2_0  (0x19C0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS2_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS2_0.
 */
#define OSEE_TC_SRC_GTMMCS20  (OSEE_TC_SRC_GTM_GTM0_MCS2_0)

/** \brief  19C4, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS2_1  (0x19C4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS2_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS2_1.
 */
#define OSEE_TC_SRC_GTMMCS21  (OSEE_TC_SRC_GTM_GTM0_MCS2_1)

/** \brief  19C8, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS2_2  (0x19C8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS2_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS2_2.
 */
#define OSEE_TC_SRC_GTMMCS22  (OSEE_TC_SRC_GTM_GTM0_MCS2_2)

/** \brief  19CC, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS2_3  (0x19CCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS2_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS2_3.
 */
#define OSEE_TC_SRC_GTMMCS23  (OSEE_TC_SRC_GTM_GTM0_MCS2_3)

/** \brief  19D0, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS2_4  (0x19D0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS2_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS2_4.
 */
#define OSEE_TC_SRC_GTMMCS24  (OSEE_TC_SRC_GTM_GTM0_MCS2_4)

/** \brief  19D4, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS2_5  (0x19D4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS2_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS2_5.
 */
#define OSEE_TC_SRC_GTMMCS25  (OSEE_TC_SRC_GTM_GTM0_MCS2_5)

/** \brief  19D8, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS2_6  (0x19D8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS2_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS2_6.
 */
#define OSEE_TC_SRC_GTMMCS26  (OSEE_TC_SRC_GTM_GTM0_MCS2_6)

/** \brief  19DC, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS2_7  (0x19DCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS2_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS2_7.
 */
#define OSEE_TC_SRC_GTMMCS27  (OSEE_TC_SRC_GTM_GTM0_MCS2_7)

/** \brief  19E0, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS3_0  (0x19E0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS3_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS3_0.
 */
#define OSEE_TC_SRC_GTMMCS30  (OSEE_TC_SRC_GTM_GTM0_MCS3_0)

/** \brief  19E4, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS3_1  (0x19E4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS3_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS3_1.
 */
#define OSEE_TC_SRC_GTMMCS31  (OSEE_TC_SRC_GTM_GTM0_MCS3_1)

/** \brief  19E8, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS3_2  (0x19E8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS3_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS3_2.
 */
#define OSEE_TC_SRC_GTMMCS32  (OSEE_TC_SRC_GTM_GTM0_MCS3_2)

/** \brief  19EC, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS3_3  (0x19ECU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS3_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS3_3.
 */
#define OSEE_TC_SRC_GTMMCS33  (OSEE_TC_SRC_GTM_GTM0_MCS3_3)

/** \brief  19F0, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS3_4  (0x19F0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS3_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS3_4.
 */
#define OSEE_TC_SRC_GTMMCS34  (OSEE_TC_SRC_GTM_GTM0_MCS3_4)

/** \brief  19F4, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS3_5  (0x19F4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS3_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS3_5.
 */
#define OSEE_TC_SRC_GTMMCS35  (OSEE_TC_SRC_GTM_GTM0_MCS3_5)

/** \brief  19F8, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS3_6  (0x19F8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS3_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS3_6.
 */
#define OSEE_TC_SRC_GTMMCS36  (OSEE_TC_SRC_GTM_GTM0_MCS3_6)

/** \brief  19FC, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS3_7  (0x19FCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS3_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS3_7.
 */
#define OSEE_TC_SRC_GTMMCS37  (OSEE_TC_SRC_GTM_GTM0_MCS3_7)

/** \brief  1A00, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS4_0  (0x1A00U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS4_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS4_0.
 */
#define OSEE_TC_SRC_GTMMCS40  (OSEE_TC_SRC_GTM_GTM0_MCS4_0)

/** \brief  1A04, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS4_1  (0x1A04U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS4_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS4_1.
 */
#define OSEE_TC_SRC_GTMMCS41  (OSEE_TC_SRC_GTM_GTM0_MCS4_1)

/** \brief  1A08, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS4_2  (0x1A08U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS4_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS4_2.
 */
#define OSEE_TC_SRC_GTMMCS42  (OSEE_TC_SRC_GTM_GTM0_MCS4_2)

/** \brief  1A0C, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS4_3  (0x1A0CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS4_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS4_3.
 */
#define OSEE_TC_SRC_GTMMCS43  (OSEE_TC_SRC_GTM_GTM0_MCS4_3)

/** \brief  1A10, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS4_4  (0x1A10U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS4_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS4_4.
 */
#define OSEE_TC_SRC_GTMMCS44  (OSEE_TC_SRC_GTM_GTM0_MCS4_4)

/** \brief  1A14, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS4_5  (0x1A14U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS4_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS4_5.
 */
#define OSEE_TC_SRC_GTMMCS45  (OSEE_TC_SRC_GTM_GTM0_MCS4_5)

/** \brief  1A18, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS4_6  (0x1A18U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS4_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS4_6.
 */
#define OSEE_TC_SRC_GTMMCS46  (OSEE_TC_SRC_GTM_GTM0_MCS4_6)

/** \brief  1A1C, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS4_7  (0x1A1CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS4_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS4_7.
 */
#define OSEE_TC_SRC_GTMMCS47  (OSEE_TC_SRC_GTM_GTM0_MCS4_7)

/** \brief  1A20, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS5_0  (0x1A20U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS5_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS5_0.
 */
#define OSEE_TC_SRC_GTMMCS50  (OSEE_TC_SRC_GTM_GTM0_MCS5_0)

/** \brief  1A24, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS5_1  (0x1A24U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS5_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS5_1.
 */
#define OSEE_TC_SRC_GTMMCS51  (OSEE_TC_SRC_GTM_GTM0_MCS5_1)

/** \brief  1A28, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS5_2  (0x1A28U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS5_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS5_2.
 */
#define OSEE_TC_SRC_GTMMCS52  (OSEE_TC_SRC_GTM_GTM0_MCS5_2)

/** \brief  1A2C, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS5_3  (0x1A2CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS5_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS5_3.
 */
#define OSEE_TC_SRC_GTMMCS53  (OSEE_TC_SRC_GTM_GTM0_MCS5_3)

/** \brief  1A30, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS5_4  (0x1A30U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS5_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS5_4.
 */
#define OSEE_TC_SRC_GTMMCS54  (OSEE_TC_SRC_GTM_GTM0_MCS5_4)

/** \brief  1A34, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS5_5  (0x1A34U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS5_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS5_5.
 */
#define OSEE_TC_SRC_GTMMCS55  (OSEE_TC_SRC_GTM_GTM0_MCS5_5)

/** \brief  1A38, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS5_6  (0x1A38U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS5_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS5_6.
 */
#define OSEE_TC_SRC_GTMMCS56  (OSEE_TC_SRC_GTM_GTM0_MCS5_6)

/** \brief  1A3C, GTM MCS Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCS5_7  (0x1A3CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCS5_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCS5_7.
 */
#define OSEE_TC_SRC_GTMMCS57  (OSEE_TC_SRC_GTM_GTM0_MCS5_7)

/** \brief  1F00, GTM Multi Channel Sequencer 0 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW00  (0x1F00U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW00.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW00.
 */
#define OSEE_TC_SRC_GTMMCSW00 (OSEE_TC_SRC_GTM_GTM0_MCSW00)

/** \brief  1F04, GTM Multi Channel Sequencer 0 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW01  (0x1F04U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW01.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW01.
 */
#define OSEE_TC_SRC_GTMMCSW01 (OSEE_TC_SRC_GTM_GTM0_MCSW01)

/** \brief  1F08, GTM Multi Channel Sequencer 0 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW02  (0x1F08U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW02.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW02.
 */
#define OSEE_TC_SRC_GTMMCSW02 (OSEE_TC_SRC_GTM_GTM0_MCSW02)

/** \brief  1F0C, GTM Multi Channel Sequencer 0 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW03  (0x1F0CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW03.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW03.
 */
#define OSEE_TC_SRC_GTMMCSW03 (OSEE_TC_SRC_GTM_GTM0_MCSW03)

/** \brief  1F10, GTM Multi Channel Sequencer 0 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW04  (0x1F10U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW04.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW04.
 */
#define OSEE_TC_SRC_GTMMCSW04 (OSEE_TC_SRC_GTM_GTM0_MCSW04)

/** \brief  1F14, GTM Multi Channel Sequencer 0 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW05  (0x1F14U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW05.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW05.
 */
#define OSEE_TC_SRC_GTMMCSW05 (OSEE_TC_SRC_GTM_GTM0_MCSW05)

/** \brief  1F40, GTM Multi Channel Sequencer 1 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW10  (0x1F40U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW10.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW10.
 */
#define OSEE_TC_SRC_GTMMCSW10 (OSEE_TC_SRC_GTM_GTM0_MCSW10)

/** \brief  1F44, GTM Multi Channel Sequencer 1 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW11  (0x1F44U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW11.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW11.
 */
#define OSEE_TC_SRC_GTMMCSW11 (OSEE_TC_SRC_GTM_GTM0_MCSW11)

/** \brief  1F48, GTM Multi Channel Sequencer 1 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW12  (0x1F48U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW12.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW12.
 */
#define OSEE_TC_SRC_GTMMCSW12 (OSEE_TC_SRC_GTM_GTM0_MCSW12)

/** \brief  1F4C, GTM Multi Channel Sequencer 1 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW13  (0x1F4CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW13.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW13.
 */
#define OSEE_TC_SRC_GTMMCSW13 (OSEE_TC_SRC_GTM_GTM0_MCSW13)

/** \brief  1F50, GTM Multi Channel Sequencer 1 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW14  (0x1F50U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW14.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW14.
 */
#define OSEE_TC_SRC_GTMMCSW14 (OSEE_TC_SRC_GTM_GTM0_MCSW14)

/** \brief  1F54, GTM Multi Channel Sequencer 1 Service Request */
#define OSEE_TC_SRC_GTM_GTM0_MCSW15  (0x1F54U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_MCSW15.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_MCSW15.
 */
#define OSEE_TC_SRC_GTMMCSW15 (OSEE_TC_SRC_GTM_GTM0_MCSW15)

/** \brief  162C, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM0_0  (0x162CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM0_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM0_0.
 */
#define OSEE_TC_SRC_GTMPSM00  (OSEE_TC_SRC_GTM_GTM0_PSM0_0)

/** \brief  1630, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM0_1  (0x1630U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM0_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM0_1.
 */
#define OSEE_TC_SRC_GTMPSM01  (OSEE_TC_SRC_GTM_GTM0_PSM0_1)

/** \brief  1634, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM0_2  (0x1634U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM0_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM0_2.
 */
#define OSEE_TC_SRC_GTMPSM02  (OSEE_TC_SRC_GTM_GTM0_PSM0_2)

/** \brief  1638, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM0_3  (0x1638U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM0_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM0_3.
 */
#define OSEE_TC_SRC_GTMPSM03         (OSEE_TC_SRC_GTM_GTM0_PSM0_3)

/** \brief  163C, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM0_4  (0x163CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM0_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM0_4.
 */
#define OSEE_TC_SRC_GTMPSM04  (OSEE_TC_SRC_GTM_GTM0_PSM0_4)

/** \brief  1640, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM0_5  (0x1640U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM0_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM0_5.
 */
#define OSEE_TC_SRC_GTMPSM05  (OSEE_TC_SRC_GTM_GTM0_PSM0_5)

/** \brief  1644, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM0_6  (0x1644U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM0_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM0_6.
 */
#define OSEE_TC_SRC_GTMPSM06  (OSEE_TC_SRC_GTM_GTM0_PSM0_6)

/** \brief  1648, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM0_7  (0x1648U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM0_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM0_7.
 */
#define OSEE_TC_SRC_GTMPSM07  (OSEE_TC_SRC_GTM_GTM0_PSM0_7)

/** \brief  164C, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM1_0  (0x164CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM1_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM1_0.
 */
#define OSEE_TC_SRC_GTMPSM10  (OSEE_TC_SRC_GTM_GTM0_PSM1_0)

/** \brief  1650, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM1_1  (0x1650U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM1_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM1_1.
 */
#define OSEE_TC_SRC_GTMPSM11  (OSEE_TC_SRC_GTM_GTM0_PSM1_1)

/** \brief  1654, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM1_2  (0x1654U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM1_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM1_2.
 */
#define OSEE_TC_SRC_GTMPSM12  (OSEE_TC_SRC_GTM_GTM0_PSM1_2)

/** \brief  1658, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM1_3  (0x1658U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM1_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM1_3.
 */
#define OSEE_TC_SRC_GTMPSM13  (OSEE_TC_SRC_GTM_GTM0_PSM1_3)

/** \brief  165C, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM1_4  (0x165CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM1_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM1_4.
 */
#define OSEE_TC_SRC_GTMPSM14  (OSEE_TC_SRC_GTM_GTM0_PSM1_4)

/** \brief  1660, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM1_5  (0x1660U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM1_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM1_5.
 */
#define OSEE_TC_SRC_GTMPSM15  (OSEE_TC_SRC_GTM_GTM0_PSM1_5)

/** \brief  1664, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM1_6  (0x1664U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM1_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM1_6.
 */
#define OSEE_TC_SRC_GTMPSM16  (OSEE_TC_SRC_GTM_GTM0_PSM1_6)

/** \brief  1668, GTM PSM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_PSM1_7  (0x1668U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_PSM1_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_PSM1_7.
 */
#define OSEE_TC_SRC_GTMPSM17  (OSEE_TC_SRC_GTM_GTM0_PSM1_7)

/** \brief  161C, GTM SPE Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_SPEIRQ0  (0x161CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_SPEIRQ0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_SPEIRQ0.
 */
#define OSEE_TC_SRC_GTMSPE0IRQ  (OSEE_TC_SRC_GTM_GTM0_SPEIRQ0)

/** \brief  1620, GTM SPE Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_SPEIRQ1  (0x1620U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_SPEIRQ1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_SPEIRQ1.
 */
#define OSEE_TC_SRC_GTMSPE1IRQ  (OSEE_TC_SRC_GTM_GTM0_SPEIRQ1)

/** \brief  1624, GTM SPE Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_SPEIRQ2  (0x1624U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_SPEIRQ2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_SPEIRQ2.
 */
#define OSEE_TC_SRC_GTMSPE2IRQ  (OSEE_TC_SRC_GTM_GTM0_SPEIRQ2)

/** \brief  1628, GTM SPE Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_SPEIRQ3  (0x1628U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_SPEIRQ3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_SPEIRQ3.
 */
#define OSEE_TC_SRC_GTMSPE3IRQ  (OSEE_TC_SRC_GTM_GTM0_SPEIRQ3)

/** \brief  1780, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM0_0  (0x1780U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM0_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM0_0.
 */
#define OSEE_TC_SRC_GTMTIM00  (OSEE_TC_SRC_GTM_GTM0_TIM0_0)

/** \brief  1784, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM0_1  (0x1784U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM0_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM0_1.
 */
#define OSEE_TC_SRC_GTMTIM01  (OSEE_TC_SRC_GTM_GTM0_TIM0_1)

/** \brief  1788, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM0_2  (0x1788U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM0_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM0_2.
 */
#define OSEE_TC_SRC_GTMTIM02  (OSEE_TC_SRC_GTM_GTM0_TIM0_2)

/** \brief  178C, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM0_3  (0x178CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM0_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM0_3.
 */
#define OSEE_TC_SRC_GTMTIM03  (OSEE_TC_SRC_GTM_GTM0_TIM0_3)

/** \brief  1790, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM0_4  (0x1790U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM0_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM0_4.
 */
#define OSEE_TC_SRC_GTMTIM04  (OSEE_TC_SRC_GTM_GTM0_TIM0_4)

/** \brief  1794, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM0_5  (0x1794U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM0_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM0_5.
 */
#define OSEE_TC_SRC_GTMTIM05  (OSEE_TC_SRC_GTM_GTM0_TIM0_5)

/** \brief  1798, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM0_6  (0x1798U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM0_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM0_6.
 */
#define OSEE_TC_SRC_GTMTIM06  (OSEE_TC_SRC_GTM_GTM0_TIM0_6)

/** \brief  179C, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM0_7  (0x179CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM0_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM0_7.
 */
#define OSEE_TC_SRC_GTMTIM07  (OSEE_TC_SRC_GTM_GTM0_TIM0_7)

/** \brief  17A0, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM1_0  (0x17A0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM1_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM1_0.
 */
#define OSEE_TC_SRC_GTMTIM10  (OSEE_TC_SRC_GTM_GTM0_TIM1_0)

/** \brief  17A4, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM1_1  (0x17A4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM1_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM1_1.
 */
#define OSEE_TC_SRC_GTMTIM11  (OSEE_TC_SRC_GTM_GTM0_TIM1_1)

/** \brief  17A8, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM1_2  (0x17A8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM1_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM1_2.
 */
#define OSEE_TC_SRC_GTMTIM12  (OSEE_TC_SRC_GTM_GTM0_TIM1_2)

/** \brief  17AC, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM1_3  (0x17ACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM1_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM1_3.
 */
#define OSEE_TC_SRC_GTMTIM13  (OSEE_TC_SRC_GTM_GTM0_TIM1_3)

/** \brief  17B0, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM1_4  (0x17B0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM1_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM1_4.
 */
#define OSEE_TC_SRC_GTMTIM14  (OSEE_TC_SRC_GTM_GTM0_TIM1_4)

/** \brief  17B4, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM1_5  (0x17B4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM1_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM1_5.
 */
#define OSEE_TC_SRC_GTMTIM15  (OSEE_TC_SRC_GTM_GTM0_TIM1_5)

/** \brief  17B8, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM1_6  (0x17B8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM1_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM1_6.
 */
#define OSEE_TC_SRC_GTMTIM16  (OSEE_TC_SRC_GTM_GTM0_TIM1_6)

/** \brief  17BC, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM1_7  (0x17BCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM1_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM1_7.
 */
#define OSEE_TC_SRC_GTMTIM17  (OSEE_TC_SRC_GTM_GTM0_TIM1_7)

/** \brief  17C0, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM2_0  (0x17C0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM2_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM2_0.
 */
#define OSEE_TC_SRC_GTMTIM20  (OSEE_TC_SRC_GTM_GTM0_TIM2_0)

/** \brief  17C4, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM2_1  (0x17C4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM2_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM2_1.
 */
#define OSEE_TC_SRC_GTMTIM21  (OSEE_TC_SRC_GTM_GTM0_TIM2_1)

/** \brief  17C8, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM2_2  (0x17C8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM2_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM2_2.
 */
#define OSEE_TC_SRC_GTMTIM22  (OSEE_TC_SRC_GTM_GTM0_TIM2_2)

/** \brief  17CC, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM2_3  (0x17CCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM2_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM2_3.
 */
#define OSEE_TC_SRC_GTMTIM23  (OSEE_TC_SRC_GTM_GTM0_TIM2_3)

/** \brief  17D0, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM2_4  (0x17D0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM2_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM2_4.
 */
#define OSEE_TC_SRC_GTMTIM24  (OSEE_TC_SRC_GTM_GTM0_TIM2_4)

/** \brief  17D4, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM2_5  (0x17D4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM2_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM2_5.
 */
#define OSEE_TC_SRC_GTMTIM25  (OSEE_TC_SRC_GTM_GTM0_TIM2_5)

/** \brief  17D8, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM2_6  (0x17D8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM2_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM2_6.
 */
#define OSEE_TC_SRC_GTMTIM26  (OSEE_TC_SRC_GTM_GTM0_TIM2_6)

/** \brief  17DC, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM2_7  (0x17DCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM2_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM2_7.
 */
#define OSEE_TC_SRC_GTMTIM27  (OSEE_TC_SRC_GTM_GTM0_TIM2_7)

/** \brief  17E0, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM3_0  (0x17E0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM3_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM3_0.
 */
#define OSEE_TC_SRC_GTMTIM30  (OSEE_TC_SRC_GTM_GTM0_TIM3_0)

/** \brief  17E4, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM3_1  (0x17E4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM3_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM3_1.
 */
#define OSEE_TC_SRC_GTMTIM31  (OSEE_TC_SRC_GTM_GTM0_TIM3_1)

/** \brief  17E8, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM3_2  (0x17E8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM3_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM3_2.
 */
#define OSEE_TC_SRC_GTMTIM32  (OSEE_TC_SRC_GTM_GTM0_TIM3_2)

/** \brief  17EC, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM3_3  (0x17ECU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM3_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM3_3.
 */
#define OSEE_TC_SRC_GTMTIM33  (OSEE_TC_SRC_GTM_GTM0_TIM3_3)

/** \brief  17F0, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM3_4  (0x17F0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM3_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM3_4.
 */
#define OSEE_TC_SRC_GTMTIM34  (OSEE_TC_SRC_GTM_GTM0_TIM3_4)

/** \brief  17F4, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM3_5  (0x17F4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM3_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM3_5.
 */
#define OSEE_TC_SRC_GTMTIM35  (OSEE_TC_SRC_GTM_GTM0_TIM3_5)

/** \brief  17F8, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM3_6  (0x17F8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM3_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM3_6.
 */
#define OSEE_TC_SRC_GTMTIM36  (OSEE_TC_SRC_GTM_GTM0_TIM3_6)

/** \brief  17FC, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM3_7  (0x17FCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM3_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM3_7.
 */
#define OSEE_TC_SRC_GTMTIM37  (OSEE_TC_SRC_GTM_GTM0_TIM3_7)

/** \brief  1800, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM4_0  (0x1800U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM4_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM4_0.
 */
#define OSEE_TC_SRC_GTMTIM40  (OSEE_TC_SRC_GTM_GTM0_TIM4_0)

/** \brief  1804, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM4_1  (0x1804U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM4_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM4_1.
 */
#define OSEE_TC_SRC_GTMTIM41  (OSEE_TC_SRC_GTM_GTM0_TIM4_1)

/** \brief  1808, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM4_2  (0x1808U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM4_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM4_2.
 */
#define OSEE_TC_SRC_GTMTIM42  (OSEE_TC_SRC_GTM_GTM0_TIM4_2)

/** \brief  180C, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM4_3  (0x180CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM4_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM4_3.
 */
#define OSEE_TC_SRC_GTMTIM43  (OSEE_TC_SRC_GTM_GTM0_TIM4_3)

/** \brief  1810, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM4_4  (0x1810U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM4_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM4_4.
 */
#define OSEE_TC_SRC_GTMTIM44  (OSEE_TC_SRC_GTM_GTM0_TIM4_4)

/** \brief  1814, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM4_5  (0x1814U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM4_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM4_5.
 */
#define OSEE_TC_SRC_GTMTIM45  (OSEE_TC_SRC_GTM_GTM0_TIM4_5)

/** \brief  1818, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM4_6  (0x1818U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM4_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM4_6.
 */
#define OSEE_TC_SRC_GTMTIM46  (OSEE_TC_SRC_GTM_GTM0_TIM4_6)

/** \brief  181C, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM4_7  (0x181CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM4_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM4_7.
 */
#define OSEE_TC_SRC_GTMTIM47  (OSEE_TC_SRC_GTM_GTM0_TIM4_7)

/** \brief  1820, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM5_0  (0x1820U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM5_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM5_0.
 */
#define OSEE_TC_SRC_GTMTIM50  (OSEE_TC_SRC_GTM_GTM0_TIM5_0)

/** \brief  1824, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM5_1  (0x1824U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM5_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM5_1.
 */
#define OSEE_TC_SRC_GTMTIM51  (OSEE_TC_SRC_GTM_GTM0_TIM5_1)

/** \brief  1828, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM5_2  (0x1828U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM5_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM5_2.
 */
#define OSEE_TC_SRC_GTMTIM52  (OSEE_TC_SRC_GTM_GTM0_TIM5_2)

/** \brief  182C, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM5_3  (0x182CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM5_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM5_3.
 */
#define OSEE_TC_SRC_GTMTIM53  (OSEE_TC_SRC_GTM_GTM0_TIM5_3)

/** \brief  1830, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM5_4  (0x1830U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM5_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM5_4.
 */
#define OSEE_TC_SRC_GTMTIM54  (OSEE_TC_SRC_GTM_GTM0_TIM5_4)

/** \brief  1834, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM5_5  (0x1834U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM5_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM5_5.
 */
#define OSEE_TC_SRC_GTMTIM55  (OSEE_TC_SRC_GTM_GTM0_TIM5_5)

/** \brief  1838, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM5_6  (0x1838U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM5_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM5_6.
 */
#define OSEE_TC_SRC_GTMTIM56  (OSEE_TC_SRC_GTM_GTM0_TIM5_6)

/** \brief  183C, GTM TIM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TIM5_7  (0x183CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TIM5_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TIM5_7.
 */
#define OSEE_TC_SRC_GTMTIM57  (OSEE_TC_SRC_GTM_GTM0_TIM5_7)

/** \brief  1B80, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM0_0  (0x1B80U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM0_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM0_0.
 */
#define OSEE_TC_SRC_GTMTOM00  (OSEE_TC_SRC_GTM_GTM0_TOM0_0)

/** \brief  1B84, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM0_1  (0x1B84U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM0_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM0_1.
 */
#define OSEE_TC_SRC_GTMTOM01  (OSEE_TC_SRC_GTM_GTM0_TOM0_1)

/** \brief  1B88, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM0_2  (0x1B88U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM0_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM0_2.
 */
#define OSEE_TC_SRC_GTMTOM02  (OSEE_TC_SRC_GTM_GTM0_TOM0_2)

/** \brief  1B8C, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM0_3  (0x1B8CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM0_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM0_3.
 */
#define OSEE_TC_SRC_GTMTOM03  (OSEE_TC_SRC_GTM_GTM0_TOM0_3)

/** \brief  1B90, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM0_4  (0x1B90U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM0_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM0_4.
 */
#define OSEE_TC_SRC_GTMTOM04  (OSEE_TC_SRC_GTM_GTM0_TOM0_4)

/** \brief  1B94, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM0_5  (0x1B94U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM0_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM0_5.
 */
#define OSEE_TC_SRC_GTMTOM05  (OSEE_TC_SRC_GTM_GTM0_TOM0_5)

/** \brief  1B98, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM0_6  (0x1B98U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM0_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM0_6.
 */
#define OSEE_TC_SRC_GTMTOM06  (OSEE_TC_SRC_GTM_GTM0_TOM0_6)

/** \brief  1B9C, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM0_7  (0x1B9CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM0_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM0_7.
 */
#define OSEE_TC_SRC_GTMTOM07  (OSEE_TC_SRC_GTM_GTM0_TOM0_7)

/** \brief  1BA0, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM1_0  (0x1BA0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM1_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM1_0.
 */
#define OSEE_TC_SRC_GTMTOM10  (OSEE_TC_SRC_GTM_GTM0_TOM1_0)

/** \brief  1BA4, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM1_1  (0x1BA4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM1_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM1_1.
 */
#define OSEE_TC_SRC_GTMTOM11  (OSEE_TC_SRC_GTM_GTM0_TOM1_1)

/** \brief  1BA8, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM1_2  (0x1BA8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM1_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM1_2.
 */
#define OSEE_TC_SRC_GTMTOM12  (OSEE_TC_SRC_GTM_GTM0_TOM1_2)

/** \brief  1BAC, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM1_3  (0x1BACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM1_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM1_3.
 */
#define OSEE_TC_SRC_GTMTOM13  (OSEE_TC_SRC_GTM_GTM0_TOM1_3)

/** \brief  1BB0, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM1_4  (0x1BB0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM1_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM1_4.
 */
#define OSEE_TC_SRC_GTMTOM14  (OSEE_TC_SRC_GTM_GTM0_TOM1_4)

/** \brief  1BB4, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM1_5  (0x1BB4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM1_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM1_5.
 */
#define OSEE_TC_SRC_GTMTOM15  (OSEE_TC_SRC_GTM_GTM0_TOM1_5)

/** \brief  1BB8, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM1_6  (0x1BB8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM1_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM1_6.
 */
#define OSEE_TC_SRC_GTMTOM16  (OSEE_TC_SRC_GTM_GTM0_TOM1_6)

/** \brief  1BBC, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM1_7  (0x1BBCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM1_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM1_7.
 */
#define OSEE_TC_SRC_GTMTOM17  (OSEE_TC_SRC_GTM_GTM0_TOM1_7)

/** \brief  1BC0, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM2_0  (0x1BC0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM2_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM2_0.
 */
#define OSEE_TC_SRC_GTMTOM20  (OSEE_TC_SRC_GTM_GTM0_TOM2_0)

/** \brief  1BC4, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM2_1  (0x1BC4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM2_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM2_1.
 */
#define OSEE_TC_SRC_GTMTOM21  (OSEE_TC_SRC_GTM_GTM0_TOM2_1)

/** \brief  1BC8, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM2_2  (0x1BC8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM2_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM2_2.
 */
#define OSEE_TC_SRC_GTMTOM22  (OSEE_TC_SRC_GTM_GTM0_TOM2_2)

/** \brief  1BCC, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM2_3  (0x1BCCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM2_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM2_3.
 */
#define OSEE_TC_SRC_GTMTOM23  (OSEE_TC_SRC_GTM_GTM0_TOM2_3)

/** \brief  1BD0, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM2_4  (0x1BD0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM2_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM2_4.
 */
#define OSEE_TC_SRC_GTMTOM24  (OSEE_TC_SRC_GTM_GTM0_TOM2_4)

/** \brief  1BD4, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM2_5  (0x1BD4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM2_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM2_5.
 */
#define OSEE_TC_SRC_GTMTOM25  (OSEE_TC_SRC_GTM_GTM0_TOM2_5)

/** \brief  1BD8, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM2_6  (0x1BD8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM2_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM2_6.
 */
#define OSEE_TC_SRC_GTMTOM26  (OSEE_TC_SRC_GTM_GTM0_TOM2_6)

/** \brief  1BDC, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM2_7  (0x1BDCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM2_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM2_7.
 */
#define OSEE_TC_SRC_GTMTOM27  (OSEE_TC_SRC_GTM_GTM0_TOM2_7)

/** \brief  1BE0, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM3_0  (0x1BE0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM3_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM3_0.
 */
#define OSEE_TC_SRC_GTMTOM30  (OSEE_TC_SRC_GTM_GTM0_TOM3_0)

/** \brief  1BE4, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM3_1  (0x1BE4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM3_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM3_1.
 */
#define OSEE_TC_SRC_GTMTOM31  (OSEE_TC_SRC_GTM_GTM0_TOM3_1)

/** \brief  1BE8, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM3_2  (0x1BE8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM3_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM3_2.
 */
#define OSEE_TC_SRC_GTMTOM32  (OSEE_TC_SRC_GTM_GTM0_TOM3_2)

/** \brief  1BEC, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM3_3  (0x1BECU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM3_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM3_3.
 */
#define OSEE_TC_SRC_GTMTOM33  (OSEE_TC_SRC_GTM_GTM0_TOM3_3)

/** \brief  1BF0, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM3_4  (0x1BF0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM3_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM3_4.
 */
#define OSEE_TC_SRC_GTMTOM34  (OSEE_TC_SRC_GTM_GTM0_TOM3_4)

/** \brief  1BF4, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM3_5  (0x1BF4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM3_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM3_5.
 */
#define OSEE_TC_SRC_GTMTOM35  (OSEE_TC_SRC_GTM_GTM0_TOM3_5)

/** \brief  1BF8, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM3_6  (0x1BF8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM3_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM3_6.
 */
#define OSEE_TC_SRC_GTMTOM36  (OSEE_TC_SRC_GTM_GTM0_TOM3_6)

/** \brief  1BFC, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM3_7  (0x1BFCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM3_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM3_7.
 */
#define OSEE_TC_SRC_GTMTOM37  (OSEE_TC_SRC_GTM_GTM0_TOM3_7)

/** \brief  1C00, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM4_0  (0x1C00U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM4_0.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM4_0.
 */
#define OSEE_TC_SRC_GTMTOM40  (OSEE_TC_SRC_GTM_GTM0_TOM4_0)

/** \brief  1C04, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM4_1  (0x1C04U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM4_1.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM4_1.
 */
#define OSEE_TC_SRC_GTMTOM41  (OSEE_TC_SRC_GTM_GTM0_TOM4_1)

/** \brief  1C08, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM4_2  (0x1C08U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM4_2.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM4_2.
 */
#define OSEE_TC_SRC_GTMTOM42  (OSEE_TC_SRC_GTM_GTM0_TOM4_2)

/** \brief  1C0C, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM4_3  (0x1C0CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM4_3.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM4_3.
 */
#define OSEE_TC_SRC_GTMTOM43  (OSEE_TC_SRC_GTM_GTM0_TOM4_3)

/** \brief  1C10, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM4_4  (0x1C10U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM4_4.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM4_4.
 */
#define OSEE_TC_SRC_GTMTOM44  (OSEE_TC_SRC_GTM_GTM0_TOM4_4)

/** \brief  1C14, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM4_5  (0x1C14U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM4_5.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM4_5.
 */
#define OSEE_TC_SRC_GTMTOM45  (OSEE_TC_SRC_GTM_GTM0_TOM4_5)

/** \brief  1C18, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM4_6  (0x1C18U)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM4_6.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM4_6.
 */
#define OSEE_TC_SRC_GTMTOM46  (OSEE_TC_SRC_GTM_GTM0_TOM4_6)

/** \brief  1C1C, GTM TOM Shared Service Request */
#define OSEE_TC_SRC_GTM_GTM0_TOM4_7  (0x1C1CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_GTM_GTM0_TOM4_7.
 * To use register names with standard convention, please use OSEE_TC_SRC_GTM_GTM0_TOM4_7.
 */
#define OSEE_TC_SRC_GTMTOM47  (OSEE_TC_SRC_GTM_GTM0_TOM4_7)

/** \brief  290, HSCT Service Request */
#define OSEE_TC_SRC_HSCT_HSCT0_SR    (0x0290U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSCT_HSCT0_SR.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSCT_HSCT0_SR.
 */
#define OSEE_TC_SRC_HSCT  (OSEE_TC_SRC_HSCT_HSCT0_SR)

/** \brief  CC0, HSM Service Request */
#define OSEE_TC_SRC_HSM_HSM0_HSM0    (0x0CC0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSM_HSM0_HSM0.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSM_HSM0_HSM0.
 */
#define OSEE_TC_SRC_HSM0  (OSEE_TC_SRC_HSM_HSM0_HSM0)

/** \brief  CC4, HSM Service Request */
#define OSEE_TC_SRC_HSM_HSM0_HSM1    (0x0CC4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSM_HSM0_HSM1.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSM_HSM0_HSM1.
 */
#define OSEE_TC_SRC_HSM1  (OSEE_TC_SRC_HSM_HSM0_HSM1)

/** \brief  2E0, Exception Service Request */
#define OSEE_TC_SRC_HSSL_EXI    (0x02E0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_EXI.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_EXI.
 */
#define OSEE_TC_SRC_HSSLEXI (OSEE_TC_SRC_HSSL_EXI)

/** \brief  2A0, Channel OK Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL0_COK    (0x02A0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL0_COK.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL0_COK.
 */
#define OSEE_TC_SRC_HSSLCOK0  (OSEE_TC_SRC_HSSL_HSSL0_COK)

/** \brief  2A8, Channel Error ServiceRequest m */
#define OSEE_TC_SRC_HSSL_HSSL0_ERR    (0x02A8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL0_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL0_ERR.
 */
#define OSEE_TC_SRC_HSSLERR0  (OSEE_TC_SRC_HSSL_HSSL0_ERR)

/** \brief  2A4, Channel Read Data Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL0_RDI    (0x02A4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL0_RDI.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL0_RDI.
 */
#define OSEE_TC_SRC_HSSLRDI0  (OSEE_TC_SRC_HSSL_HSSL0_RDI)

/** \brief  2AC, Channel Trigger Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL0_TRG    (0x02ACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL0_TRG.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL0_TRG.
 */
#define OSEE_TC_SRC_HSSLTRG0  (OSEE_TC_SRC_HSSL_HSSL0_TRG)

/** \brief  2B0, Channel OK Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL1_COK    (0x02B0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL1_COK.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL1_COK.
 */
#define OSEE_TC_SRC_HSSLCOK1  (OSEE_TC_SRC_HSSL_HSSL1_COK)

/** \brief  2B8, Channel Error ServiceRequest m */
#define OSEE_TC_SRC_HSSL_HSSL1_ERR    (0x02B8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL1_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL1_ERR.
 */
#define OSEE_TC_SRC_HSSLERR1  (OSEE_TC_SRC_HSSL_HSSL1_ERR)

/** \brief  2B4, Channel Read Data Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL1_RDI    (0x02B4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL1_RDI.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL1_RDI.
 */
#define OSEE_TC_SRC_HSSLRDI1  (OSEE_TC_SRC_HSSL_HSSL1_RDI)

/** \brief  2BC, Channel Trigger Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL1_TRG    (0x02BCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL1_TRG.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL1_TRG.
 */
#define OSEE_TC_SRC_HSSLTRG1  (OSEE_TC_SRC_HSSL_HSSL1_TRG)

/** \brief  2C0, Channel OK Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL2_COK    (0x02C0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL2_COK.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL2_COK.
 */
#define OSEE_TC_SRC_HSSLCOK2  (OSEE_TC_SRC_HSSL_HSSL2_COK)

/** \brief  2C8, Channel Error ServiceRequest m */
#define OSEE_TC_SRC_HSSL_HSSL2_ERR    (0x02C8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL2_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL2_ERR.
 */
#define OSEE_TC_SRC_HSSLERR2  (OSEE_TC_SRC_HSSL_HSSL2_ERR)

/** \brief  2C4, Channel Read Data Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL2_RDI    (0x02C4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL2_RDI.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL2_RDI.
 */
#define OSEE_TC_SRC_HSSLRDI2  (OSEE_TC_SRC_HSSL_HSSL2_RDI)

/** \brief  2CC, Channel Trigger Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL2_TRG    (0x02CCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL2_TRG.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL2_TRG.
 */
#define OSEE_TC_SRC_HSSLTRG2  (OSEE_TC_SRC_HSSL_HSSL2_TRG)

/** \brief  2D0, Channel OK Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL3_COK    (0x02D0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL3_COK.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL3_COK.
 */
#define OSEE_TC_SRC_HSSLCOK3  (OSEE_TC_SRC_HSSL_HSSL3_COK)

/** \brief  2D8, Channel Error ServiceRequest m */
#define OSEE_TC_SRC_HSSL_HSSL3_ERR    (0x02D8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL3_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL3_ERR.
 */
#define OSEE_TC_SRC_HSSLERR3  (OSEE_TC_SRC_HSSL_HSSL3_ERR)

/** \brief  2D4, Channel Read Data Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL3_RDI    (0x02D4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL3_RDI.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL3_RDI.
 */
#define OSEE_TC_SRC_HSSLRDI3  (OSEE_TC_SRC_HSSL_HSSL3_RDI)

/** \brief  2DC, Channel Trigger Service Request m */
#define OSEE_TC_SRC_HSSL_HSSL3_TRG    (0x02DCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_HSSL_HSSL3_TRG.
 * To use register names with standard convention, please use OSEE_TC_SRC_HSSL_HSSL3_TRG.
 */
#define OSEE_TC_SRC_HSSLTRG3  (OSEE_TC_SRC_HSSL_HSSL3_TRG)

/** \brief  300, I2C Burst Data Transfer Request */
#define OSEE_TC_SRC_I2C_I2C0_BREQ    (0x0300U)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C0_BREQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C0_BREQ.
 */
#define OSEE_TC_SRC_I2C0BREQ  (OSEE_TC_SRC_I2C_I2C0_BREQ)

/** \brief  310, I2C Error Service Request */
#define OSEE_TC_SRC_I2C_I2C0_ERR    (0x0310U)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C0_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C0_ERR.
 */
#define OSEE_TC_SRC_I2C0ERR (OSEE_TC_SRC_I2C_I2C0_ERR)

/** \brief  304, I2C Last Burst Data Transfer Service Request */
#define OSEE_TC_SRC_I2C_I2C0_LBREQ    (0x0304U)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C0_LBREQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C0_LBREQ.
 */
#define OSEE_TC_SRC_I2C0LBREQ (OSEE_TC_SRC_I2C_I2C0_LBREQ)

/** \brief  30C, I2C Last Single Data Transfer Service Request */
#define OSEE_TC_SRC_I2C_I2C0_LSREQ    (0x030CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C0_LSREQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C0_LSREQ.
 */
#define OSEE_TC_SRC_I2C0LSREQ (OSEE_TC_SRC_I2C_I2C0_LSREQ)

/** \brief  314, I2C Kernel Service Request */
#define OSEE_TC_SRC_I2C_I2C0_P    (0x0314U)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C0_P.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C0_P.
 */
#define OSEE_TC_SRC_I2C0P (OSEE_TC_SRC_I2C_I2C0_P)

/** \brief  308, I2C Single Data Transfer Service Request */
#define OSEE_TC_SRC_I2C_I2C0_SREQ    (0x0308U)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C0_SREQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C0_SREQ.
 */
#define OSEE_TC_SRC_I2C0SREQ  (OSEE_TC_SRC_I2C_I2C0_SREQ)

/** \brief  318, I2C Burst Data Transfer Request */
#define OSEE_TC_SRC_I2C_I2C1_BREQ    (0x0318U)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C1_BREQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C1_BREQ.
 */
#define OSEE_TC_SRC_I2C1BREQ  (OSEE_TC_SRC_I2C_I2C1_BREQ)

/** \brief  328, I2C Error Service Request */
#define OSEE_TC_SRC_I2C_I2C1_ERR    (0x0328U)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C1_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C1_ERR.
 */
#define OSEE_TC_SRC_I2C1ERR (OSEE_TC_SRC_I2C_I2C1_ERR)

/** \brief  31C, I2C Last Burst Data Transfer Service Request */
#define OSEE_TC_SRC_I2C_I2C1_LBREQ    (0x031CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C1_LBREQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C1_LBREQ.
 */
#define OSEE_TC_SRC_I2C1LBREQ (OSEE_TC_SRC_I2C_I2C1_LBREQ)

/** \brief  324, I2C Last Single Data Transfer Service Request */
#define OSEE_TC_SRC_I2C_I2C1_LSREQ    (0x0324U)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C1_LSREQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C1_LSREQ.
 */
#define OSEE_TC_SRC_I2C1LSREQ (OSEE_TC_SRC_I2C_I2C1_LSREQ)

/** \brief  32C, I2C Kernel Service Request */
#define OSEE_TC_SRC_I2C_I2C1_P    (0x032CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C1_P.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C1_P.
 */
#define OSEE_TC_SRC_I2C1P (OSEE_TC_SRC_I2C_I2C1_P)

/** \brief  320, I2C Single Data Transfer Service Request */
#define OSEE_TC_SRC_I2C_I2C1_SREQ    (0x0320U)

/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C1_SREQ.
 * To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C1_SREQ.
 */
#define OSEE_TC_SRC_I2C1SREQ  (OSEE_TC_SRC_I2C_I2C1_SREQ)

/** \brief  DE0, LMU Service Request */
#define OSEE_TC_SRC_LMU_LMU0_SR    (0x0DE0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_LMU_LMU0_SR.
 * To use register names with standard convention, please use OSEE_TC_SRC_LMU_LMU0_SR.
 */
#define OSEE_TC_SRC_LMU (OSEE_TC_SRC_LMU_LMU0_SR)

/** \brief  3E0, MSC Service Request 0 */
#define OSEE_TC_SRC_MSC_MSC0_SR0    (0x03E0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC0_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC0_SR0.
 */
#define OSEE_TC_SRC_MSC0SR0 (OSEE_TC_SRC_MSC_MSC0_SR0)

/** \brief  3E4, MSC Service Request 1 */
#define OSEE_TC_SRC_MSC_MSC0_SR1    (0x03E4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC0_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC0_SR1.
 */
#define OSEE_TC_SRC_MSC0SR1 (OSEE_TC_SRC_MSC_MSC0_SR1)

/** \brief  3E8, MSC Service Request 2 */
#define OSEE_TC_SRC_MSC_MSC0_SR2    (0x03E8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC0_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC0_SR2.
 */
#define OSEE_TC_SRC_MSC0SR2 (OSEE_TC_SRC_MSC_MSC0_SR2)

/** \brief  3EC, MSC Service Request 3 */
#define OSEE_TC_SRC_MSC_MSC0_SR3    (0x03ECU)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC0_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC0_SR3.
 */
#define OSEE_TC_SRC_MSC0SR3 (OSEE_TC_SRC_MSC_MSC0_SR3)

/** \brief  3F0, MSC Service Request 4 */
#define OSEE_TC_SRC_MSC_MSC0_SR4    (0x03F0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC0_SR4.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC0_SR4.
 */
#define OSEE_TC_SRC_MSC0SR4 (OSEE_TC_SRC_MSC_MSC0_SR4)

/** \brief  3F4, MSC Service Request 0 */
#define OSEE_TC_SRC_MSC_MSC1_SR0    (0x03F4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC1_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC1_SR0.
 */
#define OSEE_TC_SRC_MSC1SR0 (OSEE_TC_SRC_MSC_MSC1_SR0)

/** \brief  3F8, MSC Service Request 1 */
#define OSEE_TC_SRC_MSC_MSC1_SR1    (0x03F8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC1_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC1_SR1.
 */
#define OSEE_TC_SRC_MSC1SR1 (OSEE_TC_SRC_MSC_MSC1_SR1)

/** \brief  3FC, MSC Service Request 2 */
#define OSEE_TC_SRC_MSC_MSC1_SR2    (0x03FCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC1_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC1_SR2.
 */
#define OSEE_TC_SRC_MSC1SR2 (OSEE_TC_SRC_MSC_MSC1_SR2)

/** \brief  400, MSC Service Request 3 */
#define OSEE_TC_SRC_MSC_MSC1_SR3    (0x0400U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC1_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC1_SR3.
 */
#define OSEE_TC_SRC_MSC1SR3 (OSEE_TC_SRC_MSC_MSC1_SR3)

/** \brief  404, MSC Service Request 4 */
#define OSEE_TC_SRC_MSC_MSC1_SR4    (0x0404U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC1_SR4.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC1_SR4.
 */
#define OSEE_TC_SRC_MSC1SR4 (OSEE_TC_SRC_MSC_MSC1_SR4)

/** \brief  408, MSC Service Request 0 */
#define OSEE_TC_SRC_MSC_MSC2_SR0    (0x0408U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC2_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC2_SR0.
 */
#define OSEE_TC_SRC_MSC2SR0 (OSEE_TC_SRC_MSC_MSC2_SR0)

/** \brief  40C, MSC Service Request 1 */
#define OSEE_TC_SRC_MSC_MSC2_SR1    (0x040CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC2_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC2_SR1.
 */
#define OSEE_TC_SRC_MSC2SR1 (OSEE_TC_SRC_MSC_MSC2_SR1)

/** \brief  410, MSC Service Request 2 */
#define OSEE_TC_SRC_MSC_MSC2_SR2    (0x0410U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC2_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC2_SR2.
 */
#define OSEE_TC_SRC_MSC2SR2 (OSEE_TC_SRC_MSC_MSC2_SR2)

/** \brief  414, MSC Service Request 3 */
#define OSEE_TC_SRC_MSC_MSC2_SR3    (0x0414U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC2_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC2_SR3.
 */
#define OSEE_TC_SRC_MSC2SR3 (OSEE_TC_SRC_MSC_MSC2_SR3)

/** \brief  418, MSC Service Request 4 */
#define OSEE_TC_SRC_MSC_MSC2_SR4    (0x0418U)

/** Alias (User Manual Name) for OSEE_TC_SRC_MSC_MSC2_SR4.
 * To use register names with standard convention, please use OSEE_TC_SRC_MSC_MSC2_SR4.
 */
#define OSEE_TC_SRC_MSC2SR4 (OSEE_TC_SRC_MSC_MSC2_SR4)

/** \brief  C30, PMU  Service Request */
#define OSEE_TC_SRC_PMU_PMU0_SR    (0x0C30U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PMU_PMU0_SR.
 * To use register names with standard convention, please use OSEE_TC_SRC_PMU_PMU0_SR.
 */
#define OSEE_TC_SRC_PMU00 (OSEE_TC_SRC_PMU_PMU0_SR)

/** \brief  C34, PMU  Service Request */
#define OSEE_TC_SRC_PMU_PMU1_SR    (0x0C34U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PMU_PMU1_SR.
 * To use register names with standard convention, please use OSEE_TC_SRC_PMU_PMU1_SR.
 */
#define OSEE_TC_SRC_PMU01 (OSEE_TC_SRC_PMU_PMU1_SR)

/** \brief  D30, PSI5 Service Request */
#define OSEE_TC_SRC_PSI5_PSI50_SR0    (0x0D30U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5_PSI50_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5_PSI50_SR0.
 */
#define OSEE_TC_SRC_PSI50 (OSEE_TC_SRC_PSI5_PSI50_SR0)

/** \brief  D34, PSI5 Service Request */
#define OSEE_TC_SRC_PSI5_PSI50_SR1    (0x0D34U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5_PSI50_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5_PSI50_SR1.
 */
#define OSEE_TC_SRC_PSI51 (OSEE_TC_SRC_PSI5_PSI50_SR1)

/** \brief  D38, PSI5 Service Request */
#define OSEE_TC_SRC_PSI5_PSI50_SR2    (0x0D38U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5_PSI50_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5_PSI50_SR2.
 */
#define OSEE_TC_SRC_PSI52 (OSEE_TC_SRC_PSI5_PSI50_SR2)

/** \brief  D3C, PSI5 Service Request */
#define OSEE_TC_SRC_PSI5_PSI50_SR3    (0x0D3CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5_PSI50_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5_PSI50_SR3.
 */
#define OSEE_TC_SRC_PSI53 (OSEE_TC_SRC_PSI5_PSI50_SR3)

/** \brief  D40, PSI5 Service Request */
#define OSEE_TC_SRC_PSI5_PSI50_SR4    (0x0D40U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5_PSI50_SR4.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5_PSI50_SR4.
 */
#define OSEE_TC_SRC_PSI54 (OSEE_TC_SRC_PSI5_PSI50_SR4)

/** \brief  D44, PSI5 Service Request */
#define OSEE_TC_SRC_PSI5_PSI50_SR5    (0x0D44U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5_PSI50_SR5.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5_PSI50_SR5.
 */
#define OSEE_TC_SRC_PSI55 (OSEE_TC_SRC_PSI5_PSI50_SR5)

/** \brief  D48, PSI5 Service Request */
#define OSEE_TC_SRC_PSI5_PSI50_SR6    (0x0D48U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5_PSI50_SR6.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5_PSI50_SR6.
 */
#define OSEE_TC_SRC_PSI56 (OSEE_TC_SRC_PSI5_PSI50_SR6)

/** \brief  D4C, PSI5 Service Request */
#define OSEE_TC_SRC_PSI5_PSI50_SR7    (0x0D4CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5_PSI50_SR7.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5_PSI50_SR7.
 */
#define OSEE_TC_SRC_PSI57 (OSEE_TC_SRC_PSI5_PSI50_SR7)

/** \brief  DF0, PSI5-S Service Request */
#define OSEE_TC_SRC_PSI5S_PSI5S0_SR0    (0x0DF0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5S_PSI5S0_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5S_PSI5S0_SR0.
 */
#define OSEE_TC_SRC_PSI5S0  (OSEE_TC_SRC_PSI5S_PSI5S0_SR0)

/** \brief  DF4, PSI5-S Service Request */
#define OSEE_TC_SRC_PSI5S_PSI5S0_SR1    (0x0DF4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5S_PSI5S0_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5S_PSI5S0_SR1.
 */
#define OSEE_TC_SRC_PSI5S1  (OSEE_TC_SRC_PSI5S_PSI5S0_SR1)

/** \brief  DF8, PSI5-S Service Request */
#define OSEE_TC_SRC_PSI5S_PSI5S0_SR2    (0x0DF8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5S_PSI5S0_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5S_PSI5S0_SR2.
 */
#define OSEE_TC_SRC_PSI5S2  (OSEE_TC_SRC_PSI5S_PSI5S0_SR2)

/** \brief  DFC, PSI5-S Service Request */
#define OSEE_TC_SRC_PSI5S_PSI5S0_SR3    (0x0DFCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5S_PSI5S0_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5S_PSI5S0_SR3.
 */
#define OSEE_TC_SRC_PSI5S3  (OSEE_TC_SRC_PSI5S_PSI5S0_SR3)

/** \brief  E00, PSI5-S Service Request */
#define OSEE_TC_SRC_PSI5S_PSI5S0_SR4    (0x0E00U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5S_PSI5S0_SR4.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5S_PSI5S0_SR4.
 */
#define OSEE_TC_SRC_PSI5S4  (OSEE_TC_SRC_PSI5S_PSI5S0_SR4)

/** \brief  E04, PSI5-S Service Request */
#define OSEE_TC_SRC_PSI5S_PSI5S0_SR5    (0x0E04U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5S_PSI5S0_SR5.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5S_PSI5S0_SR5.
 */
#define OSEE_TC_SRC_PSI5S5  (OSEE_TC_SRC_PSI5S_PSI5S0_SR5)

/** \brief  E08, PSI5-S Service Request */
#define OSEE_TC_SRC_PSI5S_PSI5S0_SR6    (0x0E08U)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5S_PSI5S0_SR6.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5S_PSI5S0_SR6.
 */
#define OSEE_TC_SRC_PSI5S6  (OSEE_TC_SRC_PSI5S_PSI5S0_SR6)

/** \brief  E0C, PSI5-S Service Request */
#define OSEE_TC_SRC_PSI5S_PSI5S0_SR7    (0x0E0CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_PSI5S_PSI5S0_SR7.
 * To use register names with standard convention, please use OSEE_TC_SRC_PSI5S_PSI5S0_SR7.
 */
#define OSEE_TC_SRC_PSI5S7  (OSEE_TC_SRC_PSI5S_PSI5S0_SR7)

/** \brief  198, QSPI Error Service Request */
#define OSEE_TC_SRC_QSPI_QSPI0_ERR    (0x0198U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI0_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI0_ERR.
 */
#define OSEE_TC_SRC_QSPI0ERR  (OSEE_TC_SRC_QSPI_QSPI0_ERR)

/** \brief  1A0, QSPI High Speed Capture Service Request */
#define OSEE_TC_SRC_QSPI_QSPI0_HC    (0x01A0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI0_HC.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI0_HC.
 */
#define OSEE_TC_SRC_RESERVED10  (OSEE_TC_SRC_QSPI_QSPI0_HC)

/** \brief  19C, QSPI Phase Transition Service Request */
#define OSEE_TC_SRC_QSPI_QSPI0_PT    (0x019CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI0_PT.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI0_PT.
 */
#define OSEE_TC_SRC_QSPI0PT (OSEE_TC_SRC_QSPI_QSPI0_PT)

/** \brief  194, QSPI Receive Service Request */
#define OSEE_TC_SRC_QSPI_QSPI0_RX    (0x0194U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI0_RX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI0_RX.
 */
#define OSEE_TC_SRC_QSPI0RX (OSEE_TC_SRC_QSPI_QSPI0_RX)

/** \brief  190, QSPI Transmit Service Request */
#define OSEE_TC_SRC_QSPI_QSPI0_TX    (0x0190U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI0_TX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI0_TX.
 */
#define OSEE_TC_SRC_QSPI0TX (OSEE_TC_SRC_QSPI_QSPI0_TX)

/** \brief  1A4, QSPI User Defined Service Request */
#define OSEE_TC_SRC_QSPI_QSPI0_U    (0x01A4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI0_U.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI0_U.
 */
#define OSEE_TC_SRC_QSPI0U  (OSEE_TC_SRC_QSPI_QSPI0_U)

/** \brief  1B0, QSPI Error Service Request */
#define OSEE_TC_SRC_QSPI_QSPI1_ERR    (0x01B0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI1_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI1_ERR.
 */
#define OSEE_TC_SRC_QSPI1ERR  (OSEE_TC_SRC_QSPI_QSPI1_ERR)

/** \brief  1B8, QSPI High Speed Capture Service Request */
#define OSEE_TC_SRC_QSPI_QSPI1_HC    (0x01B8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI1_HC.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI1_HC.
 */
#define OSEE_TC_SRC_RESERVED11  (OSEE_TC_SRC_QSPI_QSPI1_HC)

/** \brief  1B4, QSPI Phase Transition Service Request */
#define OSEE_TC_SRC_QSPI_QSPI1_PT    (0x01B4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI1_PT.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI1_PT.
 */
#define OSEE_TC_SRC_QSPI1PT (OSEE_TC_SRC_QSPI_QSPI1_PT)

/** \brief  1AC, QSPI Receive Service Request */
#define OSEE_TC_SRC_QSPI_QSPI1_RX    (0x01ACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI1_RX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI1_RX.
 */
#define OSEE_TC_SRC_QSPI1RX (OSEE_TC_SRC_QSPI_QSPI1_RX)

/** \brief  1A8, QSPI Transmit Service Request */
#define OSEE_TC_SRC_QSPI_QSPI1_TX    (0x01A8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI1_TX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI1_TX.
 */
#define OSEE_TC_SRC_QSPI1TX (OSEE_TC_SRC_QSPI_QSPI1_TX)

/** \brief  1BC, QSPI User Defined Service Request */
#define OSEE_TC_SRC_QSPI_QSPI1_U    (0x01BCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI1_U.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI1_U.
 */
#define OSEE_TC_SRC_QSPI1U  (OSEE_TC_SRC_QSPI_QSPI1_U)

/** \brief  1C8, QSPI Error Service Request */
#define OSEE_TC_SRC_QSPI_QSPI2_ERR    (0x01C8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI2_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI2_ERR.
 */
#define OSEE_TC_SRC_QSPI2ERR  (OSEE_TC_SRC_QSPI_QSPI2_ERR)

/** \brief  1D0, QSPI High Speed Capture Service Request */
#define OSEE_TC_SRC_QSPI_QSPI2_HC    (0x01D0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI2_HC.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI2_HC.
 */
#define OSEE_TC_SRC_QSPI2HC (OSEE_TC_SRC_QSPI_QSPI2_HC)

/** \brief  1CC, QSPI Phase Transition Service Request */
#define OSEE_TC_SRC_QSPI_QSPI2_PT    (0x01CCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI2_PT.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI2_PT.
 */
#define OSEE_TC_SRC_QSPI2PT (OSEE_TC_SRC_QSPI_QSPI2_PT)

/** \brief  1C4, QSPI Receive Service Request */
#define OSEE_TC_SRC_QSPI_QSPI2_RX    (0x01C4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI2_RX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI2_RX.
 */
#define OSEE_TC_SRC_QSPI2RX (OSEE_TC_SRC_QSPI_QSPI2_RX)

/** \brief  1C0, QSPI Transmit Service Request */
#define OSEE_TC_SRC_QSPI_QSPI2_TX    (0x01C0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI2_TX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI2_TX.
 */
#define OSEE_TC_SRC_QSPI2TX (OSEE_TC_SRC_QSPI_QSPI2_TX)

/** \brief  1D4, QSPI User Defined Service Request */
#define OSEE_TC_SRC_QSPI_QSPI2_U    (0x01D4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI2_U.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI2_U.
 */
#define OSEE_TC_SRC_QSPI2U  (OSEE_TC_SRC_QSPI_QSPI2_U)

/** \brief  1E0, QSPI Error Service Request */
#define OSEE_TC_SRC_QSPI_QSPI3_ERR    (0x01E0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI3_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI3_ERR.
 */
#define OSEE_TC_SRC_QSPI3ERR  (OSEE_TC_SRC_QSPI_QSPI3_ERR)

/** \brief  1E8, QSPI High Speed Capture Service Request */
#define OSEE_TC_SRC_QSPI_QSPI3_HC    (0x01E8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI3_HC.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI3_HC.
 */
#define OSEE_TC_SRC_QSPI3HC (OSEE_TC_SRC_QSPI_QSPI3_HC)

/** \brief  1E4, QSPI Phase Transition Service Request */
#define OSEE_TC_SRC_QSPI_QSPI3_PT    (0x01E4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI3_PT.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI3_PT.
 */
#define OSEE_TC_SRC_QSPI3PT (OSEE_TC_SRC_QSPI_QSPI3_PT)

/** \brief  1DC, QSPI Receive Service Request */
#define OSEE_TC_SRC_QSPI_QSPI3_RX    (0x01DCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI3_RX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI3_RX.
 */
#define OSEE_TC_SRC_QSPI3RX (OSEE_TC_SRC_QSPI_QSPI3_RX)

/** \brief  1D8, QSPI Transmit Service Request */
#define OSEE_TC_SRC_QSPI_QSPI3_TX    (0x01D8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI3_TX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI3_TX.
 */
#define OSEE_TC_SRC_QSPI3TX (OSEE_TC_SRC_QSPI_QSPI3_TX)

/** \brief  1EC, QSPI User Defined Service Request */
#define OSEE_TC_SRC_QSPI_QSPI3_U    (0x01ECU)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI3_U.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI3_U.
 */
#define OSEE_TC_SRC_QSPI3U  (OSEE_TC_SRC_QSPI_QSPI3_U)

/** \brief  1F8, QSPI Error Service Request */
#define OSEE_TC_SRC_QSPI_QSPI4_ERR    (0x01F8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI4_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI4_ERR.
 */
#define OSEE_TC_SRC_QSPI4ERR  (OSEE_TC_SRC_QSPI_QSPI4_ERR)

/** \brief  200, QSPI High Speed Capture Service Request */
#define OSEE_TC_SRC_QSPI_QSPI4_HC    (0x0200U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI4_HC.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI4_HC.
 */
#define OSEE_TC_SRC_RESERVED14  (OSEE_TC_SRC_QSPI_QSPI4_HC)

/** \brief  1FC, QSPI Phase Transition Service Request */
#define OSEE_TC_SRC_QSPI_QSPI4_PT    (0x01FCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI4_PT.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI4_PT.
 */
#define OSEE_TC_SRC_QSPI4PT (OSEE_TC_SRC_QSPI_QSPI4_PT)

/** \brief  1F4, QSPI Receive Service Request */
#define OSEE_TC_SRC_QSPI_QSPI4_RX    (0x01F4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI4_RX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI4_RX.
 */
#define OSEE_TC_SRC_QSPI4RX (OSEE_TC_SRC_QSPI_QSPI4_RX)

/** \brief  1F0, QSPI Transmit Service Request */
#define OSEE_TC_SRC_QSPI_QSPI4_TX    (0x01F0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI4_TX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI4_TX.
 */
#define OSEE_TC_SRC_QSPI4TX (OSEE_TC_SRC_QSPI_QSPI4_TX)

/** \brief  204, QSPI User Defined Service Request */
#define OSEE_TC_SRC_QSPI_QSPI4_U    (0x0204U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI4_U.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI4_U.
 */
#define OSEE_TC_SRC_QSPI4U  (OSEE_TC_SRC_QSPI_QSPI4_U)

/** \brief  210, QSPI Error Service Request */
#define OSEE_TC_SRC_QSPI_QSPI5_ERR    (0x0210U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI5_ERR.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI5_ERR.
 */
#define OSEE_TC_SRC_QSPI5ERR  (OSEE_TC_SRC_QSPI_QSPI5_ERR)

/** \brief  218, QSPI High Speed Capture Service Request */
#define OSEE_TC_SRC_QSPI_QSPI5_HC    (0x0218U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI5_HC.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI5_HC.
 */
#define OSEE_TC_SRC_RESERVED15  (OSEE_TC_SRC_QSPI_QSPI5_HC)

/** \brief  214, QSPI Phase Transition Service Request */
#define OSEE_TC_SRC_QSPI_QSPI5_PT    (0x0214U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI5_PT.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI5_PT.
 */
#define OSEE_TC_SRC_QSPI5PT (OSEE_TC_SRC_QSPI_QSPI5_PT)

/** \brief  20C, QSPI Receive Service Request */
#define OSEE_TC_SRC_QSPI_QSPI5_RX    (0x020CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI5_RX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI5_RX.
 */
#define OSEE_TC_SRC_QSPI5RX (OSEE_TC_SRC_QSPI_QSPI5_RX)

/** \brief  208, QSPI Transmit Service Request */
#define OSEE_TC_SRC_QSPI_QSPI5_TX    (0x0208U)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI5_TX.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI5_TX.
 */
#define OSEE_TC_SRC_QSPI5TX (OSEE_TC_SRC_QSPI_QSPI5_TX)

/** \brief  21C, QSPI User Defined Service Request */
#define OSEE_TC_SRC_QSPI_QSPI5_U    (0x021CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI5_U.
 * To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI5_U.
 */
#define OSEE_TC_SRC_QSPI5U  (OSEE_TC_SRC_QSPI_QSPI5_U)

/** \brief  CD0, SCU DTS Busy Service Request */
#define OSEE_TC_SRC_SCU_SCU_DTS    (0x0CD0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SCU_SCU_DTS.
 * To use register names with standard convention, please use OSEE_TC_SRC_SCU_SCU_DTS.
 */
#define OSEE_TC_SRC_SCUDTS  (OSEE_TC_SRC_SCU_SCU_DTS)

/** \brief  CD4, SCU ERU Service Request */
#define OSEE_TC_SRC_SCU_SCU_ERU0    (0x0CD4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SCU_SCU_ERU0.
 * To use register names with standard convention, please use OSEE_TC_SRC_SCU_SCU_ERU0.
 */
#define OSEE_TC_SRC_SCUERU0 (OSEE_TC_SRC_SCU_SCU_ERU0)

/** \brief  CD8, SCU ERU Service Request */
#define OSEE_TC_SRC_SCU_SCU_ERU1    (0x0CD8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SCU_SCU_ERU1.
 * To use register names with standard convention, please use OSEE_TC_SRC_SCU_SCU_ERU1.
 */
#define OSEE_TC_SRC_SCUERU1 (OSEE_TC_SRC_SCU_SCU_ERU1)

/** \brief  CDC, SCU ERU Service Request */
#define OSEE_TC_SRC_SCU_SCU_ERU2    (0x0CDCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_SCU_SCU_ERU2.
 * To use register names with standard convention, please use OSEE_TC_SRC_SCU_SCU_ERU2.
 */
#define OSEE_TC_SRC_SCUERU2 (OSEE_TC_SRC_SCU_SCU_ERU2)

/** \brief  CE0, SCU ERU Service Request */
#define OSEE_TC_SRC_SCU_SCU_ERU3    (0x0CE0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SCU_SCU_ERU3.
 * To use register names with standard convention, please use OSEE_TC_SRC_SCU_SCU_ERU3.
 */
#define OSEE_TC_SRC_SCUERU3 (OSEE_TC_SRC_SCU_SCU_ERU3)

/** \brief  350, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR0    (0x0350U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR0.
 */
#define OSEE_TC_SRC_SENT0 (OSEE_TC_SRC_SENT_SENT0_SR0)

/** \brief  354, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR1    (0x0354U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR1.
 */
#define OSEE_TC_SRC_SENT1 (OSEE_TC_SRC_SENT_SENT0_SR1)

/** \brief  378, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR10    (0x0378U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR10.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR10.
 */
#define OSEE_TC_SRC_SENT10  (OSEE_TC_SRC_SENT_SENT0_SR10)

/** \brief  37C, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR11    (0x037CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR11.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR11.
 */
#define OSEE_TC_SRC_SENT11  (OSEE_TC_SRC_SENT_SENT0_SR11)

/** \brief  380, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR12    (0x0380U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR12.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR12.
 */
#define OSEE_TC_SRC_SENT12  (OSEE_TC_SRC_SENT_SENT0_SR12)

/** \brief  384, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR13    (0x0384U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR13.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR13.
 */
#define OSEE_TC_SRC_SENT13  (OSEE_TC_SRC_SENT_SENT0_SR13)

/** \brief  388, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR14    (0x0388U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR14.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR14.
 */
#define OSEE_TC_SRC_SENT14  (OSEE_TC_SRC_SENT_SENT0_SR14)

/** \brief  358, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR2    (0x0358U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR2.
 */
#define OSEE_TC_SRC_SENT2 (OSEE_TC_SRC_SENT_SENT0_SR2)

/** \brief  35C, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR3    (0x035CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR3.
 */
#define OSEE_TC_SRC_SENT3 (OSEE_TC_SRC_SENT_SENT0_SR3)

/** \brief  360, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR4    (0x0360U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR4.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR4.
 */
#define OSEE_TC_SRC_SENT4 (OSEE_TC_SRC_SENT_SENT0_SR4)

/** \brief  364, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR5    (0x0364U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR5.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR5.
 */
#define OSEE_TC_SRC_SENT5 (OSEE_TC_SRC_SENT_SENT0_SR5)

/** \brief  368, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR6    (0x0368U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR6.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR6.
 */
#define OSEE_TC_SRC_SENT6 (OSEE_TC_SRC_SENT_SENT0_SR6)

/** \brief  36C, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR7    (0x036CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR7.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR7.
 */
#define OSEE_TC_SRC_SENT7 (OSEE_TC_SRC_SENT_SENT0_SR7)

/** \brief  370, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR8    (0x0370U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR8.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR8.
 */
#define OSEE_TC_SRC_SENT8 (OSEE_TC_SRC_SENT_SENT0_SR8)

/** \brief  374, SENT TRIG Service Request */
#define OSEE_TC_SRC_SENT_SENT0_SR9    (0x0374U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SENT_SENT0_SR9.
 * To use register names with standard convention, please use OSEE_TC_SRC_SENT_SENT0_SR9.
 */
#define OSEE_TC_SRC_SENT9 (OSEE_TC_SRC_SENT_SENT0_SR9)

/** \brief  D10, SMU Service Request */
#define OSEE_TC_SRC_SMU_SMU0_SR0    (0x0D10U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SMU_SMU0_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_SMU_SMU0_SR0.
 */
#define OSEE_TC_SRC_SMU0  (OSEE_TC_SRC_SMU_SMU0_SR0)

/** \brief  D14, SMU Service Request */
#define OSEE_TC_SRC_SMU_SMU0_SR1    (0x0D14U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SMU_SMU0_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_SMU_SMU0_SR1.
 */
#define OSEE_TC_SRC_SMU1  (OSEE_TC_SRC_SMU_SMU0_SR1)

/** \brief  D18, SMU Service Request */
#define OSEE_TC_SRC_SMU_SMU0_SR2    (0x0D18U)

/** Alias (User Manual Name) for OSEE_TC_SRC_SMU_SMU0_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_SMU_SMU0_SR2.
 */
#define OSEE_TC_SRC_SMU2  (OSEE_TC_SRC_SMU_SMU0_SR2)

/** \brief  490, System Timer  Service Request 0 */
#define OSEE_TC_SRC_STM_STM0_SR0    (0x0490U)

/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM0_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_STM_STM0_SR0.
 */
#define OSEE_TC_SRC_STM0SR0 (OSEE_TC_SRC_STM_STM0_SR0)

/** \brief  494, System Timer  Service Request 1 */
#define OSEE_TC_SRC_STM_STM0_SR1    (0x0494U)

/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM0_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_STM_STM0_SR1.
 */
#define OSEE_TC_SRC_STM0SR1 (OSEE_TC_SRC_STM_STM0_SR1)

/** \brief  498, System Timer  Service Request 0 */
#define OSEE_TC_SRC_STM_STM1_SR0    (0x0498U)

/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM1_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_STM_STM1_SR0.
 */
#define OSEE_TC_SRC_STM1SR0 (OSEE_TC_SRC_STM_STM1_SR0)

/** \brief  49C, System Timer  Service Request 1 */
#define OSEE_TC_SRC_STM_STM1_SR1    (0x049CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM1_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_STM_STM1_SR1.
 */
#define OSEE_TC_SRC_STM1SR1 (OSEE_TC_SRC_STM_STM1_SR1)

/** \brief  4A0, System Timer  Service Request 0 */
#define OSEE_TC_SRC_STM_STM2_SR0    (0x04A0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM2_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_STM_STM2_SR0.
 */
#define OSEE_TC_SRC_STM2SR0 (OSEE_TC_SRC_STM_STM2_SR0)

/** \brief  4A4, System Timer  Service Request 1 */
#define OSEE_TC_SRC_STM_STM2_SR1    (0x04A4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM2_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_STM_STM2_SR1.
 */
#define OSEE_TC_SRC_STM2SR1 (OSEE_TC_SRC_STM_STM2_SR1)

/** \brief  AA0, VADC Common Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_CG0_SR0    (0x0AA0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG0_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG0_SR0.
 */
#define OSEE_TC_SRC_VADCCG0SR0  (OSEE_TC_SRC_VADC_CG0_SR0)

/** \brief  AA4, VADC Common Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_CG0_SR1    (0x0AA4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG0_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG0_SR1.
 */
#define OSEE_TC_SRC_VADCCG0SR1  (OSEE_TC_SRC_VADC_CG0_SR1)

/** \brief  AA8, VADC Common Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_CG0_SR2    (0x0AA8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG0_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG0_SR2.
 */
#define OSEE_TC_SRC_VADCCG0SR2  (OSEE_TC_SRC_VADC_CG0_SR2)

/** \brief  AAC, VADC Common Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_CG0_SR3    (0x0AACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG0_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG0_SR3.
 */
#define OSEE_TC_SRC_VADCCG0SR3  (OSEE_TC_SRC_VADC_CG0_SR3)

/** \brief  AB0, VADC Common Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_CG1_SR0    (0x0AB0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG1_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG1_SR0.
 */
#define OSEE_TC_SRC_VADCCG1SR0  (OSEE_TC_SRC_VADC_CG1_SR0)

/** \brief  AB4, VADC Common Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_CG1_SR1    (0x0AB4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG1_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG1_SR1.
 */
#define OSEE_TC_SRC_VADCCG1SR1  (OSEE_TC_SRC_VADC_CG1_SR1)

/** \brief  AB8, VADC Common Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_CG1_SR2    (0x0AB8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG1_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG1_SR2.
 */
#define OSEE_TC_SRC_VADCCG1SR2  (OSEE_TC_SRC_VADC_CG1_SR2)

/** \brief  ABC, VADC Common Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_CG1_SR3    (0x0ABCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG1_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG1_SR3.
 */
#define OSEE_TC_SRC_VADCCG1SR3  (OSEE_TC_SRC_VADC_CG1_SR3)

/** \brief  980, VADC Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_G0_SR0    (0x0980U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G0_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G0_SR0.
 */
#define OSEE_TC_SRC_VADCG0SR0 (OSEE_TC_SRC_VADC_G0_SR0)

/** \brief  984, VADC Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_G0_SR1    (0x0984U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G0_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G0_SR1.
 */
#define OSEE_TC_SRC_VADCG0SR1 (OSEE_TC_SRC_VADC_G0_SR1)

/** \brief  988, VADC Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_G0_SR2    (0x0988U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G0_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G0_SR2.
 */
#define OSEE_TC_SRC_VADCG0SR2 (OSEE_TC_SRC_VADC_G0_SR2)

/** \brief  98C, VADC Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_G0_SR3    (0x098CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G0_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G0_SR3.
 */
#define OSEE_TC_SRC_VADCG0SR3 (OSEE_TC_SRC_VADC_G0_SR3)

/** \brief  A20, VADC Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_G10_SR0    (0x0A20U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G10_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G10_SR0.
 */
#define OSEE_TC_SRC_VADCG10SR0  (OSEE_TC_SRC_VADC_G10_SR0)

/** \brief  A24, VADC Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_G10_SR1    (0x0A24U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G10_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G10_SR1.
 */
#define OSEE_TC_SRC_VADCG10SR1  (OSEE_TC_SRC_VADC_G10_SR1)

/** \brief  A28, VADC Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_G10_SR2    (0x0A28U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G10_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G10_SR2.
 */
#define OSEE_TC_SRC_VADCG10SR2  (OSEE_TC_SRC_VADC_G10_SR2)

/** \brief  A2C, VADC Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_G10_SR3    (0x0A2CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G10_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G10_SR3.
 */
#define OSEE_TC_SRC_VADCG10SR3  (OSEE_TC_SRC_VADC_G10_SR3)

/** \brief  990, VADC Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_G1_SR0    (0x0990U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G1_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G1_SR0.
 */
#define OSEE_TC_SRC_VADCG1SR0 (OSEE_TC_SRC_VADC_G1_SR0)

/** \brief  994, VADC Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_G1_SR1    (0x0994U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G1_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G1_SR1.
 */
#define OSEE_TC_SRC_VADCG1SR1 (OSEE_TC_SRC_VADC_G1_SR1)

/** \brief  998, VADC Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_G1_SR2    (0x0998U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G1_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G1_SR2.
 */
#define OSEE_TC_SRC_VADCG1SR2 (OSEE_TC_SRC_VADC_G1_SR2)

/** \brief  99C, VADC Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_G1_SR3    (0x099CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G1_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G1_SR3.
 */
#define OSEE_TC_SRC_VADCG1SR3 (OSEE_TC_SRC_VADC_G1_SR3)

/** \brief  9A0, VADC Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_G2_SR0    (0x09A0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G2_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G2_SR0.
 */
#define OSEE_TC_SRC_VADCG2SR0 (OSEE_TC_SRC_VADC_G2_SR0)

/** \brief  9A4, VADC Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_G2_SR1    (0x09A4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G2_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G2_SR1.
 */
#define OSEE_TC_SRC_VADCG2SR1 (OSEE_TC_SRC_VADC_G2_SR1)

/** \brief  9A8, VADC Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_G2_SR2    (0x09A8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G2_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G2_SR2.
 */
#define OSEE_TC_SRC_VADCG2SR2 (OSEE_TC_SRC_VADC_G2_SR2)

/** \brief  9AC, VADC Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_G2_SR3    (0x09ACU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G2_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G2_SR3.
 */
#define OSEE_TC_SRC_VADCG2SR3 (OSEE_TC_SRC_VADC_G2_SR3)

/** \brief  9B0, VADC Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_G3_SR0    (0x09B0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G3_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G3_SR0.
 */
#define OSEE_TC_SRC_VADCG3SR0 (OSEE_TC_SRC_VADC_G3_SR0)

/** \brief  9B4, VADC Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_G3_SR1    (0x09B4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G3_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G3_SR1.
 */
#define OSEE_TC_SRC_VADCG3SR1 (OSEE_TC_SRC_VADC_G3_SR1)

/** \brief  9B8, VADC Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_G3_SR2    (0x09B8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G3_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G3_SR2.
 */
#define OSEE_TC_SRC_VADCG3SR2 (OSEE_TC_SRC_VADC_G3_SR2)

/** \brief  9BC, VADC Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_G3_SR3    (0x09BCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G3_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G3_SR3.
 */
#define OSEE_TC_SRC_VADCG3SR3 (OSEE_TC_SRC_VADC_G3_SR3)

/** \brief  9C0, VADC Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_G4_SR0    (0x09C0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G4_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G4_SR0.
 */
#define OSEE_TC_SRC_VADCG4SR0 (OSEE_TC_SRC_VADC_G4_SR0)

/** \brief  9C4, VADC Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_G4_SR1    (0x09C4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G4_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G4_SR1.
 */
#define OSEE_TC_SRC_VADCG4SR1 (OSEE_TC_SRC_VADC_G4_SR1)

/** \brief  9C8, VADC Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_G4_SR2    (0x09C8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G4_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G4_SR2.
 */
#define OSEE_TC_SRC_VADCG4SR2 (OSEE_TC_SRC_VADC_G4_SR2)

/** \brief  9CC, VADC Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_G4_SR3    (0x09CCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G4_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G4_SR3.
 */
#define OSEE_TC_SRC_VADCG4SR3 (OSEE_TC_SRC_VADC_G4_SR3)

/** \brief  9D0, VADC Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_G5_SR0    (0x09D0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G5_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G5_SR0.
 */
#define OSEE_TC_SRC_VADCG5SR0 (OSEE_TC_SRC_VADC_G5_SR0)

/** \brief  9D4, VADC Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_G5_SR1    (0x09D4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G5_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G5_SR1.
 */
#define OSEE_TC_SRC_VADCG5SR1 (OSEE_TC_SRC_VADC_G5_SR1)

/** \brief  9D8, VADC Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_G5_SR2    (0x09D8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G5_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G5_SR2.
 */
#define OSEE_TC_SRC_VADCG5SR2 (OSEE_TC_SRC_VADC_G5_SR2)

/** \brief  9DC, VADC Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_G5_SR3    (0x09DCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G5_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G5_SR3.
 */
#define OSEE_TC_SRC_VADCG5SR3 (OSEE_TC_SRC_VADC_G5_SR3)

/** \brief  9E0, VADC Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_G6_SR0    (0x09E0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G6_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G6_SR0.
 */
#define OSEE_TC_SRC_VADCG6SR0 (OSEE_TC_SRC_VADC_G6_SR0)

/** \brief  9E4, VADC Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_G6_SR1    (0x09E4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G6_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G6_SR1.
 */
#define OSEE_TC_SRC_VADCG6SR1 (OSEE_TC_SRC_VADC_G6_SR1)

/** \brief  9E8, VADC Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_G6_SR2    (0x09E8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G6_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G6_SR2.
 */
#define OSEE_TC_SRC_VADCG6SR2 (OSEE_TC_SRC_VADC_G6_SR2)

/** \brief  9EC, VADC Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_G6_SR3    (0x09ECU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G6_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G6_SR3.
 */
#define OSEE_TC_SRC_VADCG6SR3 (OSEE_TC_SRC_VADC_G6_SR3)

/** \brief  9F0, VADC Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_G7_SR0    (0x09F0U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G7_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G7_SR0.
 */
#define OSEE_TC_SRC_VADCG7SR0 (OSEE_TC_SRC_VADC_G7_SR0)

/** \brief  9F4, VADC Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_G7_SR1    (0x09F4U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G7_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G7_SR1.
 */
#define OSEE_TC_SRC_VADCG7SR1 (OSEE_TC_SRC_VADC_G7_SR1)

/** \brief  9F8, VADC Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_G7_SR2    (0x09F8U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G7_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G7_SR2.
 */
#define OSEE_TC_SRC_VADCG7SR2 (OSEE_TC_SRC_VADC_G7_SR2)

/** \brief  9FC, VADC Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_G7_SR3    (0x09FCU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G7_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G7_SR3.
 */
#define OSEE_TC_SRC_VADCG7SR3 (OSEE_TC_SRC_VADC_G7_SR3)

/** \brief  A00, VADC Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_G8_SR0    (0x0A00U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G8_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G8_SR0.
 */
#define OSEE_TC_SRC_VADCG8SR0 (OSEE_TC_SRC_VADC_G8_SR0)

/** \brief  A04, VADC Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_G8_SR1    (0x0A04U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G8_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G8_SR1.
 */
#define OSEE_TC_SRC_VADCG8SR1 (OSEE_TC_SRC_VADC_G8_SR1)

/** \brief  A08, VADC Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_G8_SR2    (0x0A08U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G8_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G8_SR2.
 */
#define OSEE_TC_SRC_VADCG8SR2 (OSEE_TC_SRC_VADC_G8_SR2)

/** \brief  A0C, VADC Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_G8_SR3    (0x0A0CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G8_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G8_SR3.
 */
#define OSEE_TC_SRC_VADCG8SR3 (OSEE_TC_SRC_VADC_G8_SR3)

/** \brief  A10, VADC Group  Service Request 0 */
#define OSEE_TC_SRC_VADC_G9_SR0    (0x0A10U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G9_SR0.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G9_SR0.
 */
#define OSEE_TC_SRC_VADCG9SR0 (OSEE_TC_SRC_VADC_G9_SR0)

/** \brief  A14, VADC Group  Service Request 1 */
#define OSEE_TC_SRC_VADC_G9_SR1    (0x0A14U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G9_SR1.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G9_SR1.
 */
#define OSEE_TC_SRC_VADCG9SR1 (OSEE_TC_SRC_VADC_G9_SR1)

/** \brief  A18, VADC Group  Service Request 2 */
#define OSEE_TC_SRC_VADC_G9_SR2    (0x0A18U)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G9_SR2.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G9_SR2.
 */
#define OSEE_TC_SRC_VADCG9SR2 (OSEE_TC_SRC_VADC_G9_SR2)

/** \brief  A1C, VADC Group  Service Request 3 */
#define OSEE_TC_SRC_VADC_G9_SR3    (0x0A1CU)

/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G9_SR3.
 * To use register names with standard convention, please use OSEE_TC_SRC_VADC_G9_SR3.
 */
#define OSEE_TC_SRC_VADCG9SR3 (OSEE_TC_SRC_VADC_G9_SR3)

/** \brief  48, XBAR_SRI Service Request */
#define OSEE_TC_SRC_XBAR_XBAR_SRC    (0x0048U)

/** Alias (User Manual Name) for OSEE_TC_SRC_XBAR_XBAR_SRC.
 * To use register names with standard convention, please use OSEE_TC_SRC_XBAR_XBAR_SRC.
 */
#define OSEE_TC_SRC_XBARSRC (OSEE_TC_SRC_XBAR_XBAR_SRC)

/******************************************************************************/
/******************************************************************************/
#endif /* OSEE_TC_SRC_H */
