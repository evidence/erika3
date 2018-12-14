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
 * \file ./Src/BaseSw/Infra/Sfr/TC35A/_Reg/IfxSrc_reg.h
 * \brief
 * \copyright Copyright (c) 2014 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC35XA_TS_V2.6.0.R0
 * Specification: TC3xx Target Specification.V2.6.0
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
 *  \date   2018
 */
#ifndef OSEE_TC_SRC_H
#define OSEE_TC_SRC_H

/** \brief 0, CPU0 Software Breakpoint Service Request */
#define OSEE_TC_SRC_CPU_CPU0_SB (0x0000U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CPU_CPU0_SB.
* To use register names with standard convention, please use OSEE_TC_SRC_CPU_CPU0_SB.
*/
#define OSEE_TC_SRC_CPU0SB (OSEE_TC_SRC_CPU_CPU0_SB)

/** \brief 4, CPU1 Software Breakpoint Service Request */
#define OSEE_TC_SRC_CPU_CPU1_SB (0x0004U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CPU_CPU1_SB.
* To use register names with standard convention, please use OSEE_TC_SRC_CPU_CPU1_SB.
*/
#define OSEE_TC_SRC_CPU1SB (OSEE_TC_SRC_CPU_CPU1_SB)

/** \brief 8, CPU2 Software Breakpoint Service Request */
#define OSEE_TC_SRC_CPU_CPU2_SB (0x0008U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CPU_CPU2_SB.
* To use register names with standard convention, please use OSEE_TC_SRC_CPU_CPU2_SB.
*/
#define OSEE_TC_SRC_CPU2SB (OSEE_TC_SRC_CPU_CPU2_SB)

/** \brief 20, SBCU Service Request (SPB Bus Control Unit) */
#define OSEE_TC_SRC_SBCU (0x0020U)
/** Alias (User Manual Name) for OSEE_TC_SRC_SBCU.
* To use register names with standard convention, please use OSEE_TC_SRC_SBCU.
*/
#define OSEE_TC_SRC_BCUSPB (OSEE_TC_SRC_SBCU)

/** \brief 24, EBCU Service Request (BBB Bus Control Unit, on ED and ADAS devices only) */
#define OSEE_TC_SRC_EBCU (0x0024U)
/** Alias (User Manual Name) for OSEE_TC_SRC_EBCU.
* To use register names with standard convention, please use OSEE_TC_SRC_EBCU.
*/
#define OSEE_TC_SRC_BCUBBB (OSEE_TC_SRC_EBCU)

/** \brief 2C, AGBT Service Request (on ED devices only) */
#define OSEE_TC_SRC_AGBT_AGBT0_SR (0x002CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_AGBT_AGBT0_SR.
* To use register names with standard convention, please use OSEE_TC_SRC_AGBT_AGBT0_SR.
*/
#define OSEE_TC_SRC_AGBT (OSEE_TC_SRC_AGBT_AGBT0_SR)

/** \brief 30, SRI Domain 0 Service Request */
#define OSEE_TC_SRC_XBAR0 (0x0030U)

/** \brief 40, Cerberus Service Request 0 */
#define OSEE_TC_SRC_CERBERUS_CERBERUS_SR0 (0x0040U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CERBERUS_CERBERUS_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_CERBERUS_CERBERUS_SR0.
*/
#define OSEE_TC_SRC_CERBERUS0 (OSEE_TC_SRC_CERBERUS_CERBERUS_SR0)

/** \brief 44, Cerberus Service Request 1 */
#define OSEE_TC_SRC_CERBERUS_CERBERUS_SR1 (0x0044U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CERBERUS_CERBERUS_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_CERBERUS_CERBERUS_SR1.
*/
#define OSEE_TC_SRC_CERBERUS1 (OSEE_TC_SRC_CERBERUS_CERBERUS_SR1)

/** \brief 50, ASCLIN0 Transmit Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN0_TX (0x0050U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN0_TX.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN0_TX.
*/
#define OSEE_TC_SRC_ASCLIN0TX (OSEE_TC_SRC_ASCLIN_ASCLIN0_TX)

/** \brief 54, ASCLIN0 Receive Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN0_RX (0x0054U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN0_RX.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN0_RX.
*/
#define OSEE_TC_SRC_ASCLIN0RX (OSEE_TC_SRC_ASCLIN_ASCLIN0_RX)

/** \brief 58, ASCLIN0 Error Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN0_ERR (0x0058U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN0_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN0_ERR.
*/
#define OSEE_TC_SRC_ASCLIN0ERR (OSEE_TC_SRC_ASCLIN_ASCLIN0_ERR)

/** \brief 5C, ASCLIN1 Transmit Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN1_TX (0x005CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN1_TX.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN1_TX.
*/
#define OSEE_TC_SRC_ASCLIN1TX (OSEE_TC_SRC_ASCLIN_ASCLIN1_TX)

/** \brief 60, ASCLIN1 Receive Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN1_RX (0x0060U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN1_RX.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN1_RX.
*/
#define OSEE_TC_SRC_ASCLIN1RX (OSEE_TC_SRC_ASCLIN_ASCLIN1_RX)

/** \brief 64, ASCLIN1 Error Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN1_ERR (0x0064U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN1_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN1_ERR.
*/
#define OSEE_TC_SRC_ASCLIN1ERR (OSEE_TC_SRC_ASCLIN_ASCLIN1_ERR)

/** \brief 68, ASCLIN2 Transmit Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN2_TX (0x0068U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN2_TX.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN2_TX.
*/
#define OSEE_TC_SRC_ASCLIN2TX (OSEE_TC_SRC_ASCLIN_ASCLIN2_TX)

/** \brief 6C, ASCLIN2 Receive Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN2_RX (0x006CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN2_RX.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN2_RX.
*/
#define OSEE_TC_SRC_ASCLIN2RX (OSEE_TC_SRC_ASCLIN_ASCLIN2_RX)

/** \brief 70, ASCLIN2 Error Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN2_ERR (0x0070U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN2_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN2_ERR.
*/
#define OSEE_TC_SRC_ASCLIN2ERR (OSEE_TC_SRC_ASCLIN_ASCLIN2_ERR)

/** \brief 74, ASCLIN3 Transmit Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN3_TX (0x0074U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN3_TX.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN3_TX.
*/
#define OSEE_TC_SRC_ASCLIN3TX (OSEE_TC_SRC_ASCLIN_ASCLIN3_TX)

/** \brief 78, ASCLIN3 Receive Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN3_RX (0x0078U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN3_RX.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN3_RX.
*/
#define OSEE_TC_SRC_ASCLIN3RX (OSEE_TC_SRC_ASCLIN_ASCLIN3_RX)

/** \brief 7C, ASCLIN3 Error Service Request */
#define OSEE_TC_SRC_ASCLIN_ASCLIN3_ERR (0x007CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_ASCLIN_ASCLIN3_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_ASCLIN_ASCLIN3_ERR.
*/
#define OSEE_TC_SRC_ASCLIN3ERR (OSEE_TC_SRC_ASCLIN_ASCLIN3_ERR)

/** \brief EC, MTU Done Service Request */
#define OSEE_TC_SRC_MTUDONE (0x00ECU)

/** \brief F0, QSPI0 Transmit Service Request */
#define OSEE_TC_SRC_QSPI_QSPI0_TX (0x00F0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI0_TX.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI0_TX.
*/
#define OSEE_TC_SRC_QSPI0TX (OSEE_TC_SRC_QSPI_QSPI0_TX)

/** \brief F4, QSPI0 Receive Service Request */
#define OSEE_TC_SRC_QSPI_QSPI0_RX (0x00F4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI0_RX.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI0_RX.
*/
#define OSEE_TC_SRC_QSPI0RX (OSEE_TC_SRC_QSPI_QSPI0_RX)

/** \brief F8, QSPI0 Error Service Request */
#define OSEE_TC_SRC_QSPI_QSPI0_ERR (0x00F8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI0_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI0_ERR.
*/
#define OSEE_TC_SRC_QSPI0ERR (OSEE_TC_SRC_QSPI_QSPI0_ERR)

/** \brief FC, QSPI0 Phase Transition Service Request */
#define OSEE_TC_SRC_QSPI_QSPI0_PT (0x00FCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI0_PT.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI0_PT.
*/
#define OSEE_TC_SRC_QSPI0PT (OSEE_TC_SRC_QSPI_QSPI0_PT)

/** \brief 100, QSPI0 User Defined Service Request */
#define OSEE_TC_SRC_QSPI_QSPI0_U (0x0100U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI0_U.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI0_U.
*/
#define OSEE_TC_SRC_QSPI0U (OSEE_TC_SRC_QSPI_QSPI0_U)

/** \brief 104, QSPI1 Transmit Service Request */
#define OSEE_TC_SRC_QSPI_QSPI1_TX (0x0104U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI1_TX.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI1_TX.
*/
#define OSEE_TC_SRC_QSPI1TX (OSEE_TC_SRC_QSPI_QSPI1_TX)

/** \brief 108, QSPI1 Receive Service Request */
#define OSEE_TC_SRC_QSPI_QSPI1_RX (0x0108U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI1_RX.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI1_RX.
*/
#define OSEE_TC_SRC_QSPI1RX (OSEE_TC_SRC_QSPI_QSPI1_RX)

/** \brief 10C, QSPI1 Error Service Request */
#define OSEE_TC_SRC_QSPI_QSPI1_ERR (0x010CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI1_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI1_ERR.
*/
#define OSEE_TC_SRC_QSPI1ERR (OSEE_TC_SRC_QSPI_QSPI1_ERR)

/** \brief 110, QSPI1 Phase Transition Service Request */
#define OSEE_TC_SRC_QSPI_QSPI1_PT (0x0110U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI1_PT.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI1_PT.
*/
#define OSEE_TC_SRC_QSPI1PT (OSEE_TC_SRC_QSPI_QSPI1_PT)

/** \brief 114, QSPI1 User Defined Service Request */
#define OSEE_TC_SRC_QSPI_QSPI1_U (0x0114U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI1_U.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI1_U.
*/
#define OSEE_TC_SRC_QSPI1U (OSEE_TC_SRC_QSPI_QSPI1_U)

/** \brief 118, QSPI2 Transmit Service Request */
#define OSEE_TC_SRC_QSPI_QSPI2_TX (0x0118U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI2_TX.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI2_TX.
*/
#define OSEE_TC_SRC_QSPI2TX (OSEE_TC_SRC_QSPI_QSPI2_TX)

/** \brief 11C, QSPI2 Receive Service Request */
#define OSEE_TC_SRC_QSPI_QSPI2_RX (0x011CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI2_RX.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI2_RX.
*/
#define OSEE_TC_SRC_QSPI2RX (OSEE_TC_SRC_QSPI_QSPI2_RX)

/** \brief 120, QSPI2 Error Service Request */
#define OSEE_TC_SRC_QSPI_QSPI2_ERR (0x0120U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI2_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI2_ERR.
*/
#define OSEE_TC_SRC_QSPI2ERR (OSEE_TC_SRC_QSPI_QSPI2_ERR)

/** \brief 124, QSPI2 Phase Transition Service Request */
#define OSEE_TC_SRC_QSPI_QSPI2_PT (0x0124U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI2_PT.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI2_PT.
*/
#define OSEE_TC_SRC_QSPI2PT (OSEE_TC_SRC_QSPI_QSPI2_PT)

/** \brief 128, QSPI2 User Defined Service Request */
#define OSEE_TC_SRC_QSPI_QSPI2_U (0x0128U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI2_U.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI2_U.
*/
#define OSEE_TC_SRC_QSPI2U (OSEE_TC_SRC_QSPI_QSPI2_U)

/** \brief 12C, QSPI3 Transmit Service Request */
#define OSEE_TC_SRC_QSPI_QSPI3_TX (0x012CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI3_TX.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI3_TX.
*/
#define OSEE_TC_SRC_QSPI3TX (OSEE_TC_SRC_QSPI_QSPI3_TX)

/** \brief 130, QSPI3 Receive Service Request */
#define OSEE_TC_SRC_QSPI_QSPI3_RX (0x0130U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI3_RX.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI3_RX.
*/
#define OSEE_TC_SRC_QSPI3RX (OSEE_TC_SRC_QSPI_QSPI3_RX)

/** \brief 134, QSPI3 Error Service Request */
#define OSEE_TC_SRC_QSPI_QSPI3_ERR (0x0134U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI3_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI3_ERR.
*/
#define OSEE_TC_SRC_QSPI3ERR (OSEE_TC_SRC_QSPI_QSPI3_ERR)

/** \brief 138, QSPI3 Phase Transition Service Request */
#define OSEE_TC_SRC_QSPI_QSPI3_PT (0x0138U)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI3_PT.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI3_PT.
*/
#define OSEE_TC_SRC_QSPI3PT (OSEE_TC_SRC_QSPI_QSPI3_PT)

/** \brief 13C, QSPI3 User Defined Service Request */
#define OSEE_TC_SRC_QSPI_QSPI3_U (0x013CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_QSPI_QSPI3_U.
* To use register names with standard convention, please use OSEE_TC_SRC_QSPI_QSPI3_U.
*/
#define OSEE_TC_SRC_QSPI3U (OSEE_TC_SRC_QSPI_QSPI3_U)

/** \brief 178, QSPI2 High Speed Capture Service Request */
#define OSEE_TC_SRC_QSPI2HC (0x0178U)

/** \brief 17C, QSPI3 High Speed Capture Service Request */
#define OSEE_TC_SRC_QSPI3HC (0x017CU)

/** \brief 220, I2C0 Data Transfer Request */
#define OSEE_TC_SRC_I2C_I2C0_DTR (0x0220U)
/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C0_DTR.
* To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C0_DTR.
*/
#define OSEE_TC_SRC_I2C0DTR (OSEE_TC_SRC_I2C_I2C0_DTR)

/** \brief 224, I2C0 Error Service Request */
#define OSEE_TC_SRC_I2C_I2C0_ERR (0x0224U)
/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C0_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C0_ERR.
*/
#define OSEE_TC_SRC_I2C0ERR (OSEE_TC_SRC_I2C_I2C0_ERR)

/** \brief 228, I2C0 Protocol Service Request */
#define OSEE_TC_SRC_I2C_I2C0_P (0x0228U)
/** Alias (User Manual Name) for OSEE_TC_SRC_I2C_I2C0_P.
* To use register names with standard convention, please use OSEE_TC_SRC_I2C_I2C0_P.
*/
#define OSEE_TC_SRC_I2C0P (OSEE_TC_SRC_I2C_I2C0_P)

/** \brief 2C0, CCU0 Service Request 0 */
#define OSEE_TC_SRC_CCU6_CCU0_SR0 (0x02C0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU0_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU0_SR0.
*/
#define OSEE_TC_SRC_CCU60SR0 (OSEE_TC_SRC_CCU6_CCU0_SR0)

/** \brief 2C4, CCU0 Service Request 1 */
#define OSEE_TC_SRC_CCU6_CCU0_SR1 (0x02C4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU0_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU0_SR1.
*/
#define OSEE_TC_SRC_CCU60SR1 (OSEE_TC_SRC_CCU6_CCU0_SR1)

/** \brief 2C8, CCU0 Service Request 2 */
#define OSEE_TC_SRC_CCU6_CCU0_SR2 (0x02C8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU0_SR2.
* To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU0_SR2.
*/
#define OSEE_TC_SRC_CCU60SR2 (OSEE_TC_SRC_CCU6_CCU0_SR2)

/** \brief 2CC, CCU0 Service Request 3 */
#define OSEE_TC_SRC_CCU6_CCU0_SR3 (0x02CCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU0_SR3.
* To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU0_SR3.
*/
#define OSEE_TC_SRC_CCU60SR3 (OSEE_TC_SRC_CCU6_CCU0_SR3)

/** \brief 2D0, CCU1 Service Request 0 */
#define OSEE_TC_SRC_CCU6_CCU1_SR0 (0x02D0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU1_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU1_SR0.
*/
#define OSEE_TC_SRC_CCU61SR0 (OSEE_TC_SRC_CCU6_CCU1_SR0)

/** \brief 2D4, CCU1 Service Request 1 */
#define OSEE_TC_SRC_CCU6_CCU1_SR1 (0x02D4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU1_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU1_SR1.
*/
#define OSEE_TC_SRC_CCU61SR1 (OSEE_TC_SRC_CCU6_CCU1_SR1)

/** \brief 2D8, CCU1 Service Request 2 */
#define OSEE_TC_SRC_CCU6_CCU1_SR2 (0x02D8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU1_SR2.
* To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU1_SR2.
*/
#define OSEE_TC_SRC_CCU61SR2 (OSEE_TC_SRC_CCU6_CCU1_SR2)

/** \brief 2DC, CCU1 Service Request 3 */
#define OSEE_TC_SRC_CCU6_CCU1_SR3 (0x02DCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_CCU6_CCU1_SR3.
* To use register names with standard convention, please use OSEE_TC_SRC_CCU6_CCU1_SR3.
*/
#define OSEE_TC_SRC_CCU61SR3 (OSEE_TC_SRC_CCU6_CCU1_SR3)

/** \brief 2E0, GPT120 CAPREL Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_CIRQ (0x02E0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_CIRQ.
* To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_CIRQ.
*/
#define OSEE_TC_SRC_GPT120CIRQ (OSEE_TC_SRC_GPT12_GPT120_CIRQ)

/** \brief 2E4, GPT120 Timer 2 Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_T2 (0x02E4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_T2.
* To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_T2.
*/
#define OSEE_TC_SRC_GPT120T2 (OSEE_TC_SRC_GPT12_GPT120_T2)

/** \brief 2E8, GPT120 Timer 3 Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_T3 (0x02E8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_T3.
* To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_T3.
*/
#define OSEE_TC_SRC_GPT120T3 (OSEE_TC_SRC_GPT12_GPT120_T3)

/** \brief 2EC, GPT120 Timer 4 Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_T4 (0x02ECU)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_T4.
* To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_T4.
*/
#define OSEE_TC_SRC_GPT120T4 (OSEE_TC_SRC_GPT12_GPT120_T4)

/** \brief 2F0, GPT120 Timer 5 Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_T5 (0x02F0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_T5.
* To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_T5.
*/
#define OSEE_TC_SRC_GPT120T5 (OSEE_TC_SRC_GPT12_GPT120_T5)

/** \brief 2F4, GPT120 Timer 6 Service Request */
#define OSEE_TC_SRC_GPT12_GPT120_T6 (0x02F4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPT12_GPT120_T6.
* To use register names with standard convention, please use OSEE_TC_SRC_GPT12_GPT120_T6.
*/
#define OSEE_TC_SRC_GPT120T6 (OSEE_TC_SRC_GPT12_GPT120_T6)

/** \brief 300, System Timer 0 Service Request 0 */
#define OSEE_TC_SRC_STM_STM0_SR0 (0x0300U)
/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM0_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_STM_STM0_SR0.
*/
#define OSEE_TC_SRC_STM0SR0 (OSEE_TC_SRC_STM_STM0_SR0)

/** \brief 304, System Timer 0 Service Request 1 */
#define OSEE_TC_SRC_STM_STM0_SR1 (0x0304U)
/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM0_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_STM_STM0_SR1.
*/
#define OSEE_TC_SRC_STM0SR1 (OSEE_TC_SRC_STM_STM0_SR1)

/** \brief 308, System Timer 1 Service Request 0 */
#define OSEE_TC_SRC_STM_STM1_SR0 (0x0308U)
/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM1_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_STM_STM1_SR0.
*/
#define OSEE_TC_SRC_STM1SR0 (OSEE_TC_SRC_STM_STM1_SR0)

/** \brief 30C, System Timer 1 Service Request 1 */
#define OSEE_TC_SRC_STM_STM1_SR1 (0x030CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM1_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_STM_STM1_SR1.
*/
#define OSEE_TC_SRC_STM1SR1 (OSEE_TC_SRC_STM_STM1_SR1)

/** \brief 310, System Timer 2 Service Request 0 */
#define OSEE_TC_SRC_STM_STM2_SR0 (0x0310U)
/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM2_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_STM_STM2_SR0.
*/
#define OSEE_TC_SRC_STM2SR0 (OSEE_TC_SRC_STM_STM2_SR0)

/** \brief 314, System Timer 2 Service Request 1 */
#define OSEE_TC_SRC_STM_STM2_SR1 (0x0314U)
/** Alias (User Manual Name) for OSEE_TC_SRC_STM_STM2_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_STM_STM2_SR1.
*/
#define OSEE_TC_SRC_STM2SR1 (OSEE_TC_SRC_STM_STM2_SR1)

/** \brief 330, FCE0 Error Service Request */
#define OSEE_TC_SRC_FCE_FCE0_SR (0x0330U)
/** Alias (User Manual Name) for OSEE_TC_SRC_FCE_FCE0_SR.
* To use register names with standard convention, please use OSEE_TC_SRC_FCE_FCE0_SR.
*/
#define OSEE_TC_SRC_FCE0 (OSEE_TC_SRC_FCE_FCE0_SR)

/** \brief 340, DMA Error Service Request 0 */
#define OSEE_TC_SRC_DMA_DMA0_ERR0 (0x0340U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_ERR0.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_ERR0.
*/
#define OSEE_TC_SRC_DMAERR0 (OSEE_TC_SRC_DMA_DMA0_ERR0)

/** \brief 344, DMA Error Service Request 1 */
#define OSEE_TC_SRC_DMA_DMA0_ERR1 (0x0344U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_ERR1.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_ERR1.
*/
#define OSEE_TC_SRC_DMAERR1 (OSEE_TC_SRC_DMA_DMA0_ERR1)

/** \brief 348, DMA Error Service Request 2 */
#define OSEE_TC_SRC_DMA_DMA0_ERR2 (0x0348U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_ERR2.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_ERR2.
*/
#define OSEE_TC_SRC_DMAERR2 (OSEE_TC_SRC_DMA_DMA0_ERR2)

/** \brief 34C, DMA Error Service Request 3 */
#define OSEE_TC_SRC_DMA_DMA0_ERR3 (0x034CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_ERR3.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_ERR3.
*/
#define OSEE_TC_SRC_DMAERR3 (OSEE_TC_SRC_DMA_DMA0_ERR3)

/** \brief 370, DMA Channel  0 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH0 (0x0370U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH0.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH0.
*/
#define OSEE_TC_SRC_DMACH0 (OSEE_TC_SRC_DMA_DMA0_CH0)

/** \brief 374, DMA Channel  1 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH1 (0x0374U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH1.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH1.
*/
#define OSEE_TC_SRC_DMACH1 (OSEE_TC_SRC_DMA_DMA0_CH1)

/** \brief 378, DMA Channel  2 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH2 (0x0378U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH2.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH2.
*/
#define OSEE_TC_SRC_DMACH2 (OSEE_TC_SRC_DMA_DMA0_CH2)

/** \brief 37C, DMA Channel  3 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH3 (0x037CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH3.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH3.
*/
#define OSEE_TC_SRC_DMACH3 (OSEE_TC_SRC_DMA_DMA0_CH3)

/** \brief 380, DMA Channel  4 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH4 (0x0380U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH4.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH4.
*/
#define OSEE_TC_SRC_DMACH4 (OSEE_TC_SRC_DMA_DMA0_CH4)

/** \brief 384, DMA Channel  5 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH5 (0x0384U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH5.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH5.
*/
#define OSEE_TC_SRC_DMACH5 (OSEE_TC_SRC_DMA_DMA0_CH5)

/** \brief 388, DMA Channel  6 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH6 (0x0388U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH6.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH6.
*/
#define OSEE_TC_SRC_DMACH6 (OSEE_TC_SRC_DMA_DMA0_CH6)

/** \brief 38C, DMA Channel  7 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH7 (0x038CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH7.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH7.
*/
#define OSEE_TC_SRC_DMACH7 (OSEE_TC_SRC_DMA_DMA0_CH7)

/** \brief 390, DMA Channel  8 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH8 (0x0390U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH8.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH8.
*/
#define OSEE_TC_SRC_DMACH8 (OSEE_TC_SRC_DMA_DMA0_CH8)

/** \brief 394, DMA Channel  9 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH9 (0x0394U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH9.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH9.
*/
#define OSEE_TC_SRC_DMACH9 (OSEE_TC_SRC_DMA_DMA0_CH9)

/** \brief 398, DMA Channel  10 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH10 (0x0398U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH10.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH10.
*/
#define OSEE_TC_SRC_DMACH10 (OSEE_TC_SRC_DMA_DMA0_CH10)

/** \brief 39C, DMA Channel  11 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH11 (0x039CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH11.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH11.
*/
#define OSEE_TC_SRC_DMACH11 (OSEE_TC_SRC_DMA_DMA0_CH11)

/** \brief 3A0, DMA Channel  12 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH12 (0x03A0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH12.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH12.
*/
#define OSEE_TC_SRC_DMACH12 (OSEE_TC_SRC_DMA_DMA0_CH12)

/** \brief 3A4, DMA Channel  13 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH13 (0x03A4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH13.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH13.
*/
#define OSEE_TC_SRC_DMACH13 (OSEE_TC_SRC_DMA_DMA0_CH13)

/** \brief 3A8, DMA Channel  14 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH14 (0x03A8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH14.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH14.
*/
#define OSEE_TC_SRC_DMACH14 (OSEE_TC_SRC_DMA_DMA0_CH14)

/** \brief 3AC, DMA Channel  15 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH15 (0x03ACU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH15.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH15.
*/
#define OSEE_TC_SRC_DMACH15 (OSEE_TC_SRC_DMA_DMA0_CH15)

/** \brief 3B0, DMA Channel  16 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH16 (0x03B0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH16.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH16.
*/
#define OSEE_TC_SRC_DMACH16 (OSEE_TC_SRC_DMA_DMA0_CH16)

/** \brief 3B4, DMA Channel  17 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH17 (0x03B4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH17.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH17.
*/
#define OSEE_TC_SRC_DMACH17 (OSEE_TC_SRC_DMA_DMA0_CH17)

/** \brief 3B8, DMA Channel  18 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH18 (0x03B8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH18.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH18.
*/
#define OSEE_TC_SRC_DMACH18 (OSEE_TC_SRC_DMA_DMA0_CH18)

/** \brief 3BC, DMA Channel  19 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH19 (0x03BCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH19.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH19.
*/
#define OSEE_TC_SRC_DMACH19 (OSEE_TC_SRC_DMA_DMA0_CH19)

/** \brief 3C0, DMA Channel  20 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH20 (0x03C0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH20.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH20.
*/
#define OSEE_TC_SRC_DMACH20 (OSEE_TC_SRC_DMA_DMA0_CH20)

/** \brief 3C4, DMA Channel  21 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH21 (0x03C4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH21.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH21.
*/
#define OSEE_TC_SRC_DMACH21 (OSEE_TC_SRC_DMA_DMA0_CH21)

/** \brief 3C8, DMA Channel  22 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH22 (0x03C8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH22.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH22.
*/
#define OSEE_TC_SRC_DMACH22 (OSEE_TC_SRC_DMA_DMA0_CH22)

/** \brief 3CC, DMA Channel  23 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH23 (0x03CCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH23.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH23.
*/
#define OSEE_TC_SRC_DMACH23 (OSEE_TC_SRC_DMA_DMA0_CH23)

/** \brief 3D0, DMA Channel  24 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH24 (0x03D0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH24.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH24.
*/
#define OSEE_TC_SRC_DMACH24 (OSEE_TC_SRC_DMA_DMA0_CH24)

/** \brief 3D4, DMA Channel  25 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH25 (0x03D4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH25.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH25.
*/
#define OSEE_TC_SRC_DMACH25 (OSEE_TC_SRC_DMA_DMA0_CH25)

/** \brief 3D8, DMA Channel  26 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH26 (0x03D8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH26.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH26.
*/
#define OSEE_TC_SRC_DMACH26 (OSEE_TC_SRC_DMA_DMA0_CH26)

/** \brief 3DC, DMA Channel  27 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH27 (0x03DCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH27.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH27.
*/
#define OSEE_TC_SRC_DMACH27 (OSEE_TC_SRC_DMA_DMA0_CH27)

/** \brief 3E0, DMA Channel  28 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH28 (0x03E0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH28.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH28.
*/
#define OSEE_TC_SRC_DMACH28 (OSEE_TC_SRC_DMA_DMA0_CH28)

/** \brief 3E4, DMA Channel  29 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH29 (0x03E4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH29.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH29.
*/
#define OSEE_TC_SRC_DMACH29 (OSEE_TC_SRC_DMA_DMA0_CH29)

/** \brief 3E8, DMA Channel  30 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH30 (0x03E8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH30.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH30.
*/
#define OSEE_TC_SRC_DMACH30 (OSEE_TC_SRC_DMA_DMA0_CH30)

/** \brief 3EC, DMA Channel  31 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH31 (0x03ECU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH31.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH31.
*/
#define OSEE_TC_SRC_DMACH31 (OSEE_TC_SRC_DMA_DMA0_CH31)

/** \brief 3F0, DMA Channel  32 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH32 (0x03F0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH32.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH32.
*/
#define OSEE_TC_SRC_DMACH32 (OSEE_TC_SRC_DMA_DMA0_CH32)

/** \brief 3F4, DMA Channel  33 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH33 (0x03F4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH33.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH33.
*/
#define OSEE_TC_SRC_DMACH33 (OSEE_TC_SRC_DMA_DMA0_CH33)

/** \brief 3F8, DMA Channel  34 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH34 (0x03F8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH34.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH34.
*/
#define OSEE_TC_SRC_DMACH34 (OSEE_TC_SRC_DMA_DMA0_CH34)

/** \brief 3FC, DMA Channel  35 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH35 (0x03FCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH35.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH35.
*/
#define OSEE_TC_SRC_DMACH35 (OSEE_TC_SRC_DMA_DMA0_CH35)

/** \brief 400, DMA Channel  36 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH36 (0x0400U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH36.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH36.
*/
#define OSEE_TC_SRC_DMACH36 (OSEE_TC_SRC_DMA_DMA0_CH36)

/** \brief 404, DMA Channel  37 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH37 (0x0404U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH37.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH37.
*/
#define OSEE_TC_SRC_DMACH37 (OSEE_TC_SRC_DMA_DMA0_CH37)

/** \brief 408, DMA Channel  38 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH38 (0x0408U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH38.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH38.
*/
#define OSEE_TC_SRC_DMACH38 (OSEE_TC_SRC_DMA_DMA0_CH38)

/** \brief 40C, DMA Channel  39 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH39 (0x040CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH39.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH39.
*/
#define OSEE_TC_SRC_DMACH39 (OSEE_TC_SRC_DMA_DMA0_CH39)

/** \brief 410, DMA Channel  40 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH40 (0x0410U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH40.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH40.
*/
#define OSEE_TC_SRC_DMACH40 (OSEE_TC_SRC_DMA_DMA0_CH40)

/** \brief 414, DMA Channel  41 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH41 (0x0414U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH41.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH41.
*/
#define OSEE_TC_SRC_DMACH41 (OSEE_TC_SRC_DMA_DMA0_CH41)

/** \brief 418, DMA Channel  42 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH42 (0x0418U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH42.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH42.
*/
#define OSEE_TC_SRC_DMACH42 (OSEE_TC_SRC_DMA_DMA0_CH42)

/** \brief 41C, DMA Channel  43 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH43 (0x041CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH43.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH43.
*/
#define OSEE_TC_SRC_DMACH43 (OSEE_TC_SRC_DMA_DMA0_CH43)

/** \brief 420, DMA Channel  44 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH44 (0x0420U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH44.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH44.
*/
#define OSEE_TC_SRC_DMACH44 (OSEE_TC_SRC_DMA_DMA0_CH44)

/** \brief 424, DMA Channel  45 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH45 (0x0424U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH45.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH45.
*/
#define OSEE_TC_SRC_DMACH45 (OSEE_TC_SRC_DMA_DMA0_CH45)

/** \brief 428, DMA Channel  46 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH46 (0x0428U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH46.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH46.
*/
#define OSEE_TC_SRC_DMACH46 (OSEE_TC_SRC_DMA_DMA0_CH46)

/** \brief 42C, DMA Channel  47 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH47 (0x042CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH47.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH47.
*/
#define OSEE_TC_SRC_DMACH47 (OSEE_TC_SRC_DMA_DMA0_CH47)

/** \brief 430, DMA Channel  48 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH48 (0x0430U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH48.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH48.
*/
#define OSEE_TC_SRC_DMACH48 (OSEE_TC_SRC_DMA_DMA0_CH48)

/** \brief 434, DMA Channel  49 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH49 (0x0434U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH49.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH49.
*/
#define OSEE_TC_SRC_DMACH49 (OSEE_TC_SRC_DMA_DMA0_CH49)

/** \brief 438, DMA Channel  50 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH50 (0x0438U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH50.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH50.
*/
#define OSEE_TC_SRC_DMACH50 (OSEE_TC_SRC_DMA_DMA0_CH50)

/** \brief 43C, DMA Channel  51 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH51 (0x043CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH51.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH51.
*/
#define OSEE_TC_SRC_DMACH51 (OSEE_TC_SRC_DMA_DMA0_CH51)

/** \brief 440, DMA Channel  52 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH52 (0x0440U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH52.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH52.
*/
#define OSEE_TC_SRC_DMACH52 (OSEE_TC_SRC_DMA_DMA0_CH52)

/** \brief 444, DMA Channel  53 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH53 (0x0444U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH53.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH53.
*/
#define OSEE_TC_SRC_DMACH53 (OSEE_TC_SRC_DMA_DMA0_CH53)

/** \brief 448, DMA Channel  54 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH54 (0x0448U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH54.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH54.
*/
#define OSEE_TC_SRC_DMACH54 (OSEE_TC_SRC_DMA_DMA0_CH54)

/** \brief 44C, DMA Channel  55 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH55 (0x044CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH55.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH55.
*/
#define OSEE_TC_SRC_DMACH55 (OSEE_TC_SRC_DMA_DMA0_CH55)

/** \brief 450, DMA Channel  56 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH56 (0x0450U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH56.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH56.
*/
#define OSEE_TC_SRC_DMACH56 (OSEE_TC_SRC_DMA_DMA0_CH56)

/** \brief 454, DMA Channel  57 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH57 (0x0454U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH57.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH57.
*/
#define OSEE_TC_SRC_DMACH57 (OSEE_TC_SRC_DMA_DMA0_CH57)

/** \brief 458, DMA Channel  58 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH58 (0x0458U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH58.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH58.
*/
#define OSEE_TC_SRC_DMACH58 (OSEE_TC_SRC_DMA_DMA0_CH58)

/** \brief 45C, DMA Channel  59 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH59 (0x045CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH59.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH59.
*/
#define OSEE_TC_SRC_DMACH59 (OSEE_TC_SRC_DMA_DMA0_CH59)

/** \brief 460, DMA Channel  60 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH60 (0x0460U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH60.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH60.
*/
#define OSEE_TC_SRC_DMACH60 (OSEE_TC_SRC_DMA_DMA0_CH60)

/** \brief 464, DMA Channel  61 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH61 (0x0464U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH61.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH61.
*/
#define OSEE_TC_SRC_DMACH61 (OSEE_TC_SRC_DMA_DMA0_CH61)

/** \brief 468, DMA Channel  62 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH62 (0x0468U)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH62.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH62.
*/
#define OSEE_TC_SRC_DMACH62 (OSEE_TC_SRC_DMA_DMA0_CH62)

/** \brief 46C, DMA Channel  63 Service Request */
#define OSEE_TC_SRC_DMA_DMA0_CH63 (0x046CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_DMA_DMA0_CH63.
* To use register names with standard convention, please use OSEE_TC_SRC_DMA_DMA0_CH63.
*/
#define OSEE_TC_SRC_DMACH63 (OSEE_TC_SRC_DMA_DMA0_CH63)

/** \brief 580, GETH Service Request 0 */
#define OSEE_TC_SRC_GETH_GETH0_SR0 (0x0580U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GETH_GETH0_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_GETH_GETH0_SR0.
*/
#define OSEE_TC_SRC_GETH0 (OSEE_TC_SRC_GETH_GETH0_SR0)

/** \brief 584, GETH Service Request 1 */
#define OSEE_TC_SRC_GETH_GETH0_SR1 (0x0584U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GETH_GETH0_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_GETH_GETH0_SR1.
*/
#define OSEE_TC_SRC_GETH1 (OSEE_TC_SRC_GETH_GETH0_SR1)

/** \brief 588, GETH Service Request 2 */
#define OSEE_TC_SRC_GETH_GETH0_SR2 (0x0588U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GETH_GETH0_SR2.
* To use register names with standard convention, please use OSEE_TC_SRC_GETH_GETH0_SR2.
*/
#define OSEE_TC_SRC_GETH2 (OSEE_TC_SRC_GETH_GETH0_SR2)

/** \brief 58C, GETH Service Request 3 */
#define OSEE_TC_SRC_GETH_GETH0_SR3 (0x058CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_GETH_GETH0_SR3.
* To use register names with standard convention, please use OSEE_TC_SRC_GETH_GETH0_SR3.
*/
#define OSEE_TC_SRC_GETH3 (OSEE_TC_SRC_GETH_GETH0_SR3)

/** \brief 590, GETH Service Request 4 */
#define OSEE_TC_SRC_GETH_GETH0_SR4 (0x0590U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GETH_GETH0_SR4.
* To use register names with standard convention, please use OSEE_TC_SRC_GETH_GETH0_SR4.
*/
#define OSEE_TC_SRC_GETH4 (OSEE_TC_SRC_GETH_GETH0_SR4)

/** \brief 594, GETH Service Request 5 */
#define OSEE_TC_SRC_GETH_GETH0_SR5 (0x0594U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GETH_GETH0_SR5.
* To use register names with standard convention, please use OSEE_TC_SRC_GETH_GETH0_SR5.
*/
#define OSEE_TC_SRC_GETH5 (OSEE_TC_SRC_GETH_GETH0_SR5)

/** \brief 598, GETH Service Request 6 */
#define OSEE_TC_SRC_GETH_GETH0_SR6 (0x0598U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GETH_GETH0_SR6.
* To use register names with standard convention, please use OSEE_TC_SRC_GETH_GETH0_SR6.
*/
#define OSEE_TC_SRC_GETH6 (OSEE_TC_SRC_GETH_GETH0_SR6)

/** \brief 59C, GETH Service Request 7 */
#define OSEE_TC_SRC_GETH_GETH0_SR7 (0x059CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_GETH_GETH0_SR7.
* To use register names with standard convention, please use OSEE_TC_SRC_GETH_GETH0_SR7.
*/
#define OSEE_TC_SRC_GETH7 (OSEE_TC_SRC_GETH_GETH0_SR7)

/** \brief 5A0, GETH Service Request 8 */
#define OSEE_TC_SRC_GETH_GETH0_SR8 (0x05A0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GETH_GETH0_SR8.
* To use register names with standard convention, please use OSEE_TC_SRC_GETH_GETH0_SR8.
*/
#define OSEE_TC_SRC_GETH8 (OSEE_TC_SRC_GETH_GETH0_SR8)

/** \brief 5A4, GETH Service Request 9 */
#define OSEE_TC_SRC_GETH_GETH0_SR9 (0x05A4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GETH_GETH0_SR9.
* To use register names with standard convention, please use OSEE_TC_SRC_GETH_GETH0_SR9.
*/
#define OSEE_TC_SRC_GETH9 (OSEE_TC_SRC_GETH_GETH0_SR9)

/** \brief 5B0, CAN0 Service Request 0 */
#define OSEE_TC_SRC_CAN_CAN0_INT0 (0x05B0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT0.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT0.
*/
#define OSEE_TC_SRC_CAN0INT0 (OSEE_TC_SRC_CAN_CAN0_INT0)

/** \brief 5B4, CAN0 Service Request 1 */
#define OSEE_TC_SRC_CAN_CAN0_INT1 (0x05B4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT1.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT1.
*/
#define OSEE_TC_SRC_CAN0INT1 (OSEE_TC_SRC_CAN_CAN0_INT1)

/** \brief 5B8, CAN0 Service Request 2 */
#define OSEE_TC_SRC_CAN_CAN0_INT2 (0x05B8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT2.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT2.
*/
#define OSEE_TC_SRC_CAN0INT2 (OSEE_TC_SRC_CAN_CAN0_INT2)

/** \brief 5BC, CAN0 Service Request 3 */
#define OSEE_TC_SRC_CAN_CAN0_INT3 (0x05BCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT3.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT3.
*/
#define OSEE_TC_SRC_CAN0INT3 (OSEE_TC_SRC_CAN_CAN0_INT3)

/** \brief 5C0, CAN0 Service Request 4 */
#define OSEE_TC_SRC_CAN_CAN0_INT4 (0x05C0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT4.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT4.
*/
#define OSEE_TC_SRC_CAN0INT4 (OSEE_TC_SRC_CAN_CAN0_INT4)

/** \brief 5C4, CAN0 Service Request 5 */
#define OSEE_TC_SRC_CAN_CAN0_INT5 (0x05C4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT5.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT5.
*/
#define OSEE_TC_SRC_CAN0INT5 (OSEE_TC_SRC_CAN_CAN0_INT5)

/** \brief 5C8, CAN0 Service Request 6 */
#define OSEE_TC_SRC_CAN_CAN0_INT6 (0x05C8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT6.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT6.
*/
#define OSEE_TC_SRC_CAN0INT6 (OSEE_TC_SRC_CAN_CAN0_INT6)

/** \brief 5CC, CAN0 Service Request 7 */
#define OSEE_TC_SRC_CAN_CAN0_INT7 (0x05CCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT7.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT7.
*/
#define OSEE_TC_SRC_CAN0INT7 (OSEE_TC_SRC_CAN_CAN0_INT7)

/** \brief 5D0, CAN0 Service Request 8 */
#define OSEE_TC_SRC_CAN_CAN0_INT8 (0x05D0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT8.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT8.
*/
#define OSEE_TC_SRC_CAN0INT8 (OSEE_TC_SRC_CAN_CAN0_INT8)

/** \brief 5D4, CAN0 Service Request 9 */
#define OSEE_TC_SRC_CAN_CAN0_INT9 (0x05D4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT9.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT9.
*/
#define OSEE_TC_SRC_CAN0INT9 (OSEE_TC_SRC_CAN_CAN0_INT9)

/** \brief 5D8, CAN0 Service Request 10 */
#define OSEE_TC_SRC_CAN_CAN0_INT10 (0x05D8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT10.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT10.
*/
#define OSEE_TC_SRC_CAN0INT10 (OSEE_TC_SRC_CAN_CAN0_INT10)

/** \brief 5DC, CAN0 Service Request 11 */
#define OSEE_TC_SRC_CAN_CAN0_INT11 (0x05DCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT11.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT11.
*/
#define OSEE_TC_SRC_CAN0INT11 (OSEE_TC_SRC_CAN_CAN0_INT11)

/** \brief 5E0, CAN0 Service Request 12 */
#define OSEE_TC_SRC_CAN_CAN0_INT12 (0x05E0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT12.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT12.
*/
#define OSEE_TC_SRC_CAN0INT12 (OSEE_TC_SRC_CAN_CAN0_INT12)

/** \brief 5E4, CAN0 Service Request 13 */
#define OSEE_TC_SRC_CAN_CAN0_INT13 (0x05E4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT13.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT13.
*/
#define OSEE_TC_SRC_CAN0INT13 (OSEE_TC_SRC_CAN_CAN0_INT13)

/** \brief 5E8, CAN0 Service Request 14 */
#define OSEE_TC_SRC_CAN_CAN0_INT14 (0x05E8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT14.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT14.
*/
#define OSEE_TC_SRC_CAN0INT14 (OSEE_TC_SRC_CAN_CAN0_INT14)

/** \brief 5EC, CAN0 Service Request 15 */
#define OSEE_TC_SRC_CAN_CAN0_INT15 (0x05ECU)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN0_INT15.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN0_INT15.
*/
#define OSEE_TC_SRC_CAN0INT15 (OSEE_TC_SRC_CAN_CAN0_INT15)

/** \brief 5F0, CAN1 Service Request 0 */
#define OSEE_TC_SRC_CAN_CAN1_INT0 (0x05F0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT0.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT0.
*/
#define OSEE_TC_SRC_CAN1INT0 (OSEE_TC_SRC_CAN_CAN1_INT0)

/** \brief 5F4, CAN1 Service Request 1 */
#define OSEE_TC_SRC_CAN_CAN1_INT1 (0x05F4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT1.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT1.
*/
#define OSEE_TC_SRC_CAN1INT1 (OSEE_TC_SRC_CAN_CAN1_INT1)

/** \brief 5F8, CAN1 Service Request 2 */
#define OSEE_TC_SRC_CAN_CAN1_INT2 (0x05F8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT2.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT2.
*/
#define OSEE_TC_SRC_CAN1INT2 (OSEE_TC_SRC_CAN_CAN1_INT2)

/** \brief 5FC, CAN1 Service Request 3 */
#define OSEE_TC_SRC_CAN_CAN1_INT3 (0x05FCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT3.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT3.
*/
#define OSEE_TC_SRC_CAN1INT3 (OSEE_TC_SRC_CAN_CAN1_INT3)

/** \brief 600, CAN1 Service Request 4 */
#define OSEE_TC_SRC_CAN_CAN1_INT4 (0x0600U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT4.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT4.
*/
#define OSEE_TC_SRC_CAN1INT4 (OSEE_TC_SRC_CAN_CAN1_INT4)

/** \brief 604, CAN1 Service Request 5 */
#define OSEE_TC_SRC_CAN_CAN1_INT5 (0x0604U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT5.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT5.
*/
#define OSEE_TC_SRC_CAN1INT5 (OSEE_TC_SRC_CAN_CAN1_INT5)

/** \brief 608, CAN1 Service Request 6 */
#define OSEE_TC_SRC_CAN_CAN1_INT6 (0x0608U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT6.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT6.
*/
#define OSEE_TC_SRC_CAN1INT6 (OSEE_TC_SRC_CAN_CAN1_INT6)

/** \brief 60C, CAN1 Service Request 7 */
#define OSEE_TC_SRC_CAN_CAN1_INT7 (0x060CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT7.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT7.
*/
#define OSEE_TC_SRC_CAN1INT7 (OSEE_TC_SRC_CAN_CAN1_INT7)

/** \brief 610, CAN1 Service Request 8 */
#define OSEE_TC_SRC_CAN_CAN1_INT8 (0x0610U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT8.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT8.
*/
#define OSEE_TC_SRC_CAN1INT8 (OSEE_TC_SRC_CAN_CAN1_INT8)

/** \brief 614, CAN1 Service Request 9 */
#define OSEE_TC_SRC_CAN_CAN1_INT9 (0x0614U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT9.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT9.
*/
#define OSEE_TC_SRC_CAN1INT9 (OSEE_TC_SRC_CAN_CAN1_INT9)

/** \brief 618, CAN1 Service Request 10 */
#define OSEE_TC_SRC_CAN_CAN1_INT10 (0x0618U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT10.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT10.
*/
#define OSEE_TC_SRC_CAN1INT10 (OSEE_TC_SRC_CAN_CAN1_INT10)

/** \brief 61C, CAN1 Service Request 11 */
#define OSEE_TC_SRC_CAN_CAN1_INT11 (0x061CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT11.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT11.
*/
#define OSEE_TC_SRC_CAN1INT11 (OSEE_TC_SRC_CAN_CAN1_INT11)

/** \brief 620, CAN1 Service Request 12 */
#define OSEE_TC_SRC_CAN_CAN1_INT12 (0x0620U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT12.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT12.
*/
#define OSEE_TC_SRC_CAN1INT12 (OSEE_TC_SRC_CAN_CAN1_INT12)

/** \brief 624, CAN1 Service Request 13 */
#define OSEE_TC_SRC_CAN_CAN1_INT13 (0x0624U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT13.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT13.
*/
#define OSEE_TC_SRC_CAN1INT13 (OSEE_TC_SRC_CAN_CAN1_INT13)

/** \brief 628, CAN1 Service Request 14 */
#define OSEE_TC_SRC_CAN_CAN1_INT14 (0x0628U)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT14.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT14.
*/
#define OSEE_TC_SRC_CAN1INT14 (OSEE_TC_SRC_CAN_CAN1_INT14)

/** \brief 62C, CAN1 Service Request 15 */
#define OSEE_TC_SRC_CAN_CAN1_INT15 (0x062CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_CAN_CAN1_INT15.
* To use register names with standard convention, please use OSEE_TC_SRC_CAN_CAN1_INT15.
*/
#define OSEE_TC_SRC_CAN1INT15 (OSEE_TC_SRC_CAN_CAN1_INT15)

/** \brief 670, EVADC Group 0 Service Request 0 */
#define OSEE_TC_SRC_VADC_G0_SR0 (0x0670U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G0_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_G0_SR0.
*/
#define OSEE_TC_SRC_VADCG0SR0 (OSEE_TC_SRC_VADC_G0_SR0)

/** \brief 674, EVADC Group 0 Service Request 1 */
#define OSEE_TC_SRC_VADC_G0_SR1 (0x0674U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G0_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_G0_SR1.
*/
#define OSEE_TC_SRC_VADCG0SR1 (OSEE_TC_SRC_VADC_G0_SR1)

/** \brief 678, EVADC Group 0 Service Request 2 */
#define OSEE_TC_SRC_VADC_G0_SR2 (0x0678U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G0_SR2.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_G0_SR2.
*/
#define OSEE_TC_SRC_VADCG0SR2 (OSEE_TC_SRC_VADC_G0_SR2)

/** \brief 67C, EVADC Group 0 Service Request 3 */
#define OSEE_TC_SRC_VADC_G0_SR3 (0x067CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G0_SR3.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_G0_SR3.
*/
#define OSEE_TC_SRC_VADCG0SR3 (OSEE_TC_SRC_VADC_G0_SR3)

/** \brief 680, EVADC Group 1 Service Request 0 */
#define OSEE_TC_SRC_VADC_G1_SR0 (0x0680U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G1_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_G1_SR0.
*/
#define OSEE_TC_SRC_VADCG1SR0 (OSEE_TC_SRC_VADC_G1_SR0)

/** \brief 684, EVADC Group 1 Service Request 1 */
#define OSEE_TC_SRC_VADC_G1_SR1 (0x0684U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G1_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_G1_SR1.
*/
#define OSEE_TC_SRC_VADCG1SR1 (OSEE_TC_SRC_VADC_G1_SR1)

/** \brief 688, EVADC Group 1 Service Request 2 */
#define OSEE_TC_SRC_VADC_G1_SR2 (0x0688U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G1_SR2.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_G1_SR2.
*/
#define OSEE_TC_SRC_VADCG1SR2 (OSEE_TC_SRC_VADC_G1_SR2)

/** \brief 68C, EVADC Group 1 Service Request 3 */
#define OSEE_TC_SRC_VADC_G1_SR3 (0x068CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_G1_SR3.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_G1_SR3.
*/
#define OSEE_TC_SRC_VADCG1SR3 (OSEE_TC_SRC_VADC_G1_SR3)

/** \brief 750, EVADC Common Group 0 Service Request 0 */
#define OSEE_TC_SRC_VADC_CG0_SR0 (0x0750U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG0_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG0_SR0.
*/
#define OSEE_TC_SRC_VADCCG0SR0 (OSEE_TC_SRC_VADC_CG0_SR0)

/** \brief 754, EVADC Common Group 0 Service Request 1 */
#define OSEE_TC_SRC_VADC_CG0_SR1 (0x0754U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG0_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG0_SR1.
*/
#define OSEE_TC_SRC_VADCCG0SR1 (OSEE_TC_SRC_VADC_CG0_SR1)

/** \brief 758, EVADC Common Group 0 Service Request 2 */
#define OSEE_TC_SRC_VADC_CG0_SR2 (0x0758U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG0_SR2.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG0_SR2.
*/
#define OSEE_TC_SRC_VADCCG0SR2 (OSEE_TC_SRC_VADC_CG0_SR2)

/** \brief 75C, EVADC Common Group 0 Service Request 3 */
#define OSEE_TC_SRC_VADC_CG0_SR3 (0x075CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG0_SR3.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG0_SR3.
*/
#define OSEE_TC_SRC_VADCCG0SR3 (OSEE_TC_SRC_VADC_CG0_SR3)

/** \brief 760, EVADC Common Group 1 Service Request 0 */
#define OSEE_TC_SRC_VADC_CG1_SR0 (0x0760U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG1_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG1_SR0.
*/
#define OSEE_TC_SRC_VADCCG1SR0 (OSEE_TC_SRC_VADC_CG1_SR0)

/** \brief 764, EVADC Common Group 1 Service Request 1 */
#define OSEE_TC_SRC_VADC_CG1_SR1 (0x0764U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG1_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG1_SR1.
*/
#define OSEE_TC_SRC_VADCCG1SR1 (OSEE_TC_SRC_VADC_CG1_SR1)

/** \brief 768, EVADC Common Group 1 Service Request 2 */
#define OSEE_TC_SRC_VADC_CG1_SR2 (0x0768U)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG1_SR2.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG1_SR2.
*/
#define OSEE_TC_SRC_VADCCG1SR2 (OSEE_TC_SRC_VADC_CG1_SR2)

/** \brief 76C, EVADC Common Group 1 Service Request 3 */
#define OSEE_TC_SRC_VADC_CG1_SR3 (0x076CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_VADC_CG1_SR3.
* To use register names with standard convention, please use OSEE_TC_SRC_VADC_CG1_SR3.
*/
#define OSEE_TC_SRC_VADCCG1SR3 (OSEE_TC_SRC_VADC_CG1_SR3)

/** \brief 800, E-RAY 0 Service Request 0 */
#define OSEE_TC_SRC_ERAY_ERAY0_INT0 (0x0800U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_INT0.
* To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_INT0.
*/
#define OSEE_TC_SRC_ERAY0INT0 (OSEE_TC_SRC_ERAY_ERAY0_INT0)

/** \brief 804, E-RAY 0 Service Request 1 */
#define OSEE_TC_SRC_ERAY_ERAY0_INT1 (0x0804U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_INT1.
* To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_INT1.
*/
#define OSEE_TC_SRC_ERAY0INT1 (OSEE_TC_SRC_ERAY_ERAY0_INT1)

/** \brief 808, E-RAY 0 Timer Interrupt 0 Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_TINT0 (0x0808U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_TINT0.
* To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_TINT0.
*/
#define OSEE_TC_SRC_ERAY0TINT0 (OSEE_TC_SRC_ERAY_ERAY0_TINT0)

/** \brief 80C, E-RAY 0 Timer Interrupt 1 Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_TINT1 (0x080CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_TINT1.
* To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_TINT1.
*/
#define OSEE_TC_SRC_ERAY0TINT1 (OSEE_TC_SRC_ERAY_ERAY0_TINT1)

/** \brief 810, E-RAY 0 New Data 0 Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_NDAT0 (0x0810U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_NDAT0.
* To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_NDAT0.
*/
#define OSEE_TC_SRC_ERAY0NDAT0 (OSEE_TC_SRC_ERAY_ERAY0_NDAT0)

/** \brief 814, E-RAY 0 New Data 1 Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_NDAT1 (0x0814U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_NDAT1.
* To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_NDAT1.
*/
#define OSEE_TC_SRC_ERAY0NDAT1 (OSEE_TC_SRC_ERAY_ERAY0_NDAT1)

/** \brief 818, E-RAY 0 Message Buffer Status Changed 0 Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_MBSC0 (0x0818U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_MBSC0.
* To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_MBSC0.
*/
#define OSEE_TC_SRC_ERAY0MBSC0 (OSEE_TC_SRC_ERAY_ERAY0_MBSC0)

/** \brief 81C, E-RAY 0 Message Buffer Status Changed 1 Service Request */
#define OSEE_TC_SRC_ERAY_ERAY0_MBSC1 (0x081CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_MBSC1.
* To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_MBSC1.
*/
#define OSEE_TC_SRC_ERAY0MBSC1 (OSEE_TC_SRC_ERAY_ERAY0_MBSC1)

/** \brief 820, E-RAY 0 Output Buffer Busy */
#define OSEE_TC_SRC_ERAY_ERAY0_OBUSY (0x0820U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_OBUSY.
* To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_OBUSY.
*/
#define OSEE_TC_SRC_ERAY0OBUSY (OSEE_TC_SRC_ERAY_ERAY0_OBUSY)

/** \brief 824, E-RAY 0 Input Buffer Busy */
#define OSEE_TC_SRC_ERAY_ERAY0_IBUSY (0x0824U)
/** Alias (User Manual Name) for OSEE_TC_SRC_ERAY_ERAY0_IBUSY.
* To use register names with standard convention, please use OSEE_TC_SRC_ERAY_ERAY0_IBUSY.
*/
#define OSEE_TC_SRC_ERAY0IBUSY (OSEE_TC_SRC_ERAY_ERAY0_IBUSY)

/** \brief 860, DMU Host Service Request */
#define OSEE_TC_SRC_DMUHOST (0x0860U)

/** \brief 864, DMU FSI Service Request */
#define OSEE_TC_SRC_DMUFSI (0x0864U)

/** \brief 870, HSM Service Request 0 */
#define OSEE_TC_SRC_HSM_HSM0_HSM0 (0x0870U)
/** Alias (User Manual Name) for OSEE_TC_SRC_HSM_HSM0_HSM0.
* To use register names with standard convention, please use OSEE_TC_SRC_HSM_HSM0_HSM0.
*/
#define OSEE_TC_SRC_HSM0 (OSEE_TC_SRC_HSM_HSM0_HSM0)

/** \brief 874, HSM Service Request 1 */
#define OSEE_TC_SRC_HSM_HSM0_HSM1 (0x0874U)
/** Alias (User Manual Name) for OSEE_TC_SRC_HSM_HSM0_HSM1.
* To use register names with standard convention, please use OSEE_TC_SRC_HSM_HSM0_HSM1.
*/
#define OSEE_TC_SRC_HSM1 (OSEE_TC_SRC_HSM_HSM0_HSM1)

/** \brief 880, SCU ERU Service Request 0 */
#define OSEE_TC_SRC_SCU_SCUERU0 (0x0880U)
/** Alias (User Manual Name) for OSEE_TC_SRC_SCU_SCUERU0.
* To use register names with standard convention, please use OSEE_TC_SRC_SCU_SCUERU0.
*/
#define OSEE_TC_SRC_SCUERU0 (OSEE_TC_SRC_SCU_SCUERU0)

/** \brief 884, SCU ERU Service Request 1 */
#define OSEE_TC_SRC_SCU_SCUERU1 (0x0884U)
/** Alias (User Manual Name) for OSEE_TC_SRC_SCU_SCUERU1.
* To use register names with standard convention, please use OSEE_TC_SRC_SCU_SCUERU1.
*/
#define OSEE_TC_SRC_SCUERU1 (OSEE_TC_SRC_SCU_SCUERU1)

/** \brief 888, SCU ERU Service Request 2 */
#define OSEE_TC_SRC_SCU_SCUERU2 (0x0888U)
/** Alias (User Manual Name) for OSEE_TC_SRC_SCU_SCUERU2.
* To use register names with standard convention, please use OSEE_TC_SRC_SCU_SCUERU2.
*/
#define OSEE_TC_SRC_SCUERU2 (OSEE_TC_SRC_SCU_SCUERU2)

/** \brief 88C, SCU ERU Service Request 3 */
#define OSEE_TC_SRC_SCU_SCUERU3 (0x088CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_SCU_SCUERU3.
* To use register names with standard convention, please use OSEE_TC_SRC_SCU_SCUERU3.
*/
#define OSEE_TC_SRC_SCUERU3 (OSEE_TC_SRC_SCU_SCUERU3)

/** \brief 8AC, PMS DTS Service Request */
#define OSEE_TC_SRC_PMSDTS (0x08ACU)

/** \brief 8B0, Power Management System Service Request 0 */
#define OSEE_TC_SRC_PMS_PMS0_SR (0x08B0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_PMS_PMS0_SR.
* To use register names with standard convention, please use OSEE_TC_SRC_PMS_PMS0_SR.
*/
#define OSEE_TC_SRC_PMS0 (OSEE_TC_SRC_PMS_PMS0_SR)

/** \brief 8B4, Power Management System Service Request 1 */
#define OSEE_TC_SRC_PMS_PMS1_SR (0x08B4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_PMS_PMS1_SR.
* To use register names with standard convention, please use OSEE_TC_SRC_PMS_PMS1_SR.
*/
#define OSEE_TC_SRC_PMS1 (OSEE_TC_SRC_PMS_PMS1_SR)

/** \brief 8B8, Power Management System Service Request 2 */
#define OSEE_TC_SRC_PMS_PMS2_SR (0x08B8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_PMS_PMS2_SR.
* To use register names with standard convention, please use OSEE_TC_SRC_PMS_PMS2_SR.
*/
#define OSEE_TC_SRC_PMS2 (OSEE_TC_SRC_PMS_PMS2_SR)

/** \brief 8BC, Power Management System Service Request 3 */
#define OSEE_TC_SRC_PMS_PMS3_SR (0x08BCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_PMS_PMS3_SR.
* To use register names with standard convention, please use OSEE_TC_SRC_PMS_PMS3_SR.
*/
#define OSEE_TC_SRC_PMS3 (OSEE_TC_SRC_PMS_PMS3_SR)

/** \brief 8C0, Stand By Controller Service Request */
#define OSEE_TC_SRC_SCR (0x08C0U)

/** \brief 8D0, SMU Service Request 0 */
#define OSEE_TC_SRC_SMU_SMU0_SR0 (0x08D0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_SMU_SMU0_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_SMU_SMU0_SR0.
*/
#define OSEE_TC_SRC_SMU0 (OSEE_TC_SRC_SMU_SMU0_SR0)

/** \brief 8D4, SMU Service Request 1 */
#define OSEE_TC_SRC_SMU_SMU0_SR1 (0x08D4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_SMU_SMU0_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_SMU_SMU0_SR1.
*/
#define OSEE_TC_SRC_SMU1 (OSEE_TC_SRC_SMU_SMU0_SR1)

/** \brief 8D8, SMU Service Request 2 */
#define OSEE_TC_SRC_SMU_SMU0_SR2 (0x08D8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_SMU_SMU0_SR2.
* To use register names with standard convention, please use OSEE_TC_SRC_SMU_SMU0_SR2.
*/
#define OSEE_TC_SRC_SMU2 (OSEE_TC_SRC_SMU_SMU0_SR2)

/** \brief 900, HSPDM0 Buffer Service Request */
#define OSEE_TC_SRC_HSPDM_HSPDM0_BFR (0x0900U)
/** Alias (User Manual Name) for OSEE_TC_SRC_HSPDM_HSPDM0_BFR.
* To use register names with standard convention, please use OSEE_TC_SRC_HSPDM_HSPDM0_BFR.
*/
#define OSEE_TC_SRC_HSPDM0BFR (OSEE_TC_SRC_HSPDM_HSPDM0_BFR)

/** \brief 904, HSPDM0 RAMP Events  Service Request */
#define OSEE_TC_SRC_HSPDM_HSPDM0_RAMP (0x0904U)
/** Alias (User Manual Name) for OSEE_TC_SRC_HSPDM_HSPDM0_RAMP.
* To use register names with standard convention, please use OSEE_TC_SRC_HSPDM_HSPDM0_RAMP.
*/
#define OSEE_TC_SRC_HSPDM0RAMP (OSEE_TC_SRC_HSPDM_HSPDM0_RAMP)

/** \brief 908, HSPDM0 Error / RAM Overflow Service Request */
#define OSEE_TC_SRC_HSPDM_HSPDM0_ERR (0x0908U)
/** Alias (User Manual Name) for OSEE_TC_SRC_HSPDM_HSPDM0_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_HSPDM_HSPDM0_ERR.
*/
#define OSEE_TC_SRC_HSPDM0ERR (OSEE_TC_SRC_HSPDM_HSPDM0_ERR)

/** \brief 970, Radar Interface 0 Error Service Request */
#define OSEE_TC_SRC_RIF_RIF0_ERR (0x0970U)
/** Alias (User Manual Name) for OSEE_TC_SRC_RIF_RIF0_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_RIF_RIF0_ERR.
*/
#define OSEE_TC_SRC_RIF0ERR (OSEE_TC_SRC_RIF_RIF0_ERR)

/** \brief 974, Radar Interface 0 Service Request */
#define OSEE_TC_SRC_RIF_RIF0_INT (0x0974U)
/** Alias (User Manual Name) for OSEE_TC_SRC_RIF_RIF0_INT.
* To use register names with standard convention, please use OSEE_TC_SRC_RIF_RIF0_INT.
*/
#define OSEE_TC_SRC_RIF0INT (OSEE_TC_SRC_RIF_RIF0_INT)

/** \brief 978, Radar Interface 1 Error Service Request */
#define OSEE_TC_SRC_RIF_RIF1_ERR (0x0978U)
/** Alias (User Manual Name) for OSEE_TC_SRC_RIF_RIF1_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_RIF_RIF1_ERR.
*/
#define OSEE_TC_SRC_RIF1ERR (OSEE_TC_SRC_RIF_RIF1_ERR)

/** \brief 97C, Radar Interface 1 Service Request */
#define OSEE_TC_SRC_RIF_RIF1_INT (0x097CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_RIF_RIF1_INT.
* To use register names with standard convention, please use OSEE_TC_SRC_RIF_RIF1_INT.
*/
#define OSEE_TC_SRC_RIF1INT (OSEE_TC_SRC_RIF_RIF1_INT)

/** \brief 980, SPU 0 Service Request */
#define OSEE_TC_SRC_SPU_SPU0_INT (0x0980U)
/** Alias (User Manual Name) for OSEE_TC_SRC_SPU_SPU0_INT.
* To use register names with standard convention, please use OSEE_TC_SRC_SPU_SPU0_INT.
*/
#define OSEE_TC_SRC_SPU0INT (OSEE_TC_SRC_SPU_SPU0_INT)

/** \brief 984, SPU 0 Error Service Request */
#define OSEE_TC_SRC_SPU_SPU0_ERR (0x0984U)
/** Alias (User Manual Name) for OSEE_TC_SRC_SPU_SPU0_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_SPU_SPU0_ERR.
*/
#define OSEE_TC_SRC_SPU0ERR (OSEE_TC_SRC_SPU_SPU0_ERR)

/** \brief 988, SPU 1 Service Request */
#define OSEE_TC_SRC_SPU_SPU1_INT (0x0988U)
/** Alias (User Manual Name) for OSEE_TC_SRC_SPU_SPU1_INT.
* To use register names with standard convention, please use OSEE_TC_SRC_SPU_SPU1_INT.
*/
#define OSEE_TC_SRC_SPU1INT (OSEE_TC_SRC_SPU_SPU1_INT)

/** \brief 98C, SPU 1 Error Service Request */
#define OSEE_TC_SRC_SPU_SPU1_ERR (0x098CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_SPU_SPU1_ERR.
* To use register names with standard convention, please use OSEE_TC_SRC_SPU_SPU1_ERR.
*/
#define OSEE_TC_SRC_SPU1ERR (OSEE_TC_SRC_SPU_SPU1_ERR)

/** \brief 990, General Purpose Group 0 Service Request 0 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR0 (0x0990U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR0.
*/
#define OSEE_TC_SRC_GPSR00 (OSEE_TC_SRC_GPSR_GPSR0_SR0)

/** \brief 994, General Purpose Group 0 Service Request 1 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR1 (0x0994U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR1.
*/
#define OSEE_TC_SRC_GPSR01 (OSEE_TC_SRC_GPSR_GPSR0_SR1)

/** \brief 998, General Purpose Group 0 Service Request 2 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR2 (0x0998U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR2.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR2.
*/
#define OSEE_TC_SRC_GPSR02 (OSEE_TC_SRC_GPSR_GPSR0_SR2)

/** \brief 99C, General Purpose Group 0 Service Request 3 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR3 (0x099CU)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR3.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR3.
*/
#define OSEE_TC_SRC_GPSR03 (OSEE_TC_SRC_GPSR_GPSR0_SR3)

/** \brief 9A0, General Purpose Group 0 Service Request 4 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR4 (0x09A0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR4.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR4.
*/
#define OSEE_TC_SRC_GPSR04 (OSEE_TC_SRC_GPSR_GPSR0_SR4)

/** \brief 9A4, General Purpose Group 0 Service Request 5 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR5 (0x09A4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR5.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR5.
*/
#define OSEE_TC_SRC_GPSR05 (OSEE_TC_SRC_GPSR_GPSR0_SR5)

/** \brief 9A8, General Purpose Group 0 Service Request 6 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR6 (0x09A8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR6.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR6.
*/
#define OSEE_TC_SRC_GPSR06 (OSEE_TC_SRC_GPSR_GPSR0_SR6)

/** \brief 9AC, General Purpose Group 0 Service Request 7 */
#define OSEE_TC_SRC_GPSR_GPSR0_SR7 (0x09ACU)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR0_SR7.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR0_SR7.
*/
#define OSEE_TC_SRC_GPSR07 (OSEE_TC_SRC_GPSR_GPSR0_SR7)

/** \brief 9B0, General Purpose Group 1 Service Request 0 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR0 (0x09B0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR0.
*/
#define OSEE_TC_SRC_GPSR10 (OSEE_TC_SRC_GPSR_GPSR1_SR0)

/** \brief 9B4, General Purpose Group 1 Service Request 1 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR1 (0x09B4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR1.
*/
#define OSEE_TC_SRC_GPSR11 (OSEE_TC_SRC_GPSR_GPSR1_SR1)

/** \brief 9B8, General Purpose Group 1 Service Request 2 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR2 (0x09B8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR2.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR2.
*/
#define OSEE_TC_SRC_GPSR12 (OSEE_TC_SRC_GPSR_GPSR1_SR2)

/** \brief 9BC, General Purpose Group 1 Service Request 3 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR3 (0x09BCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR3.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR3.
*/
#define OSEE_TC_SRC_GPSR13 (OSEE_TC_SRC_GPSR_GPSR1_SR3)

/** \brief 9C0, General Purpose Group 1 Service Request 4 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR4 (0x09C0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR4.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR4.
*/
#define OSEE_TC_SRC_GPSR14 (OSEE_TC_SRC_GPSR_GPSR1_SR4)

/** \brief 9C4, General Purpose Group 1 Service Request 5 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR5 (0x09C4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR5.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR5.
*/
#define OSEE_TC_SRC_GPSR15 (OSEE_TC_SRC_GPSR_GPSR1_SR5)

/** \brief 9C8, General Purpose Group 1 Service Request 6 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR6 (0x09C8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR6.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR6.
*/
#define OSEE_TC_SRC_GPSR16 (OSEE_TC_SRC_GPSR_GPSR1_SR6)

/** \brief 9CC, General Purpose Group 1 Service Request 7 */
#define OSEE_TC_SRC_GPSR_GPSR1_SR7 (0x09CCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR1_SR7.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR1_SR7.
*/
#define OSEE_TC_SRC_GPSR17 (OSEE_TC_SRC_GPSR_GPSR1_SR7)

/** \brief 9D0, General Purpose Group 2 Service Request 0 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR0 (0x09D0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR0.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR0.
*/
#define OSEE_TC_SRC_GPSR20 (OSEE_TC_SRC_GPSR_GPSR2_SR0)

/** \brief 9D4, General Purpose Group 2 Service Request 1 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR1 (0x09D4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR1.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR1.
*/
#define OSEE_TC_SRC_GPSR21 (OSEE_TC_SRC_GPSR_GPSR2_SR1)

/** \brief 9D8, General Purpose Group 2 Service Request 2 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR2 (0x09D8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR2.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR2.
*/
#define OSEE_TC_SRC_GPSR22 (OSEE_TC_SRC_GPSR_GPSR2_SR2)

/** \brief 9DC, General Purpose Group 2 Service Request 3 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR3 (0x09DCU)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR3.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR3.
*/
#define OSEE_TC_SRC_GPSR23 (OSEE_TC_SRC_GPSR_GPSR2_SR3)

/** \brief 9E0, General Purpose Group 2 Service Request 4 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR4 (0x09E0U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR4.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR4.
*/
#define OSEE_TC_SRC_GPSR24 (OSEE_TC_SRC_GPSR_GPSR2_SR4)

/** \brief 9E4, General Purpose Group 2 Service Request 5 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR5 (0x09E4U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR5.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR5.
*/
#define OSEE_TC_SRC_GPSR25 (OSEE_TC_SRC_GPSR_GPSR2_SR5)

/** \brief 9E8, General Purpose Group 2 Service Request 6 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR6 (0x09E8U)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR6.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR6.
*/
#define OSEE_TC_SRC_GPSR26 (OSEE_TC_SRC_GPSR_GPSR2_SR6)

/** \brief 9EC, General Purpose Group 2 Service Request 7 */
#define OSEE_TC_SRC_GPSR_GPSR2_SR7 (0x09ECU)
/** Alias (User Manual Name) for OSEE_TC_SRC_GPSR_GPSR2_SR7.
* To use register names with standard convention, please use OSEE_TC_SRC_GPSR_GPSR2_SR7.
*/
#define OSEE_TC_SRC_GPSR27 (OSEE_TC_SRC_GPSR_GPSR2_SR7)


/******************************************************************************/

/******************************************************************************/

#endif /* OSEE_TC_SRC_H */
