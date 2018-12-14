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
 * This file derives from a modification of the Infineon Configuration of Ssw 
 * boot mode header, distributed under the following license:
 * \file IfxCpu_SswBmhd.c
 * \brief This file contains the Bmhd for Aurix Plus.
 * \ingroup
 *
 * \version iLLD_Demos_1_0_1_8_0
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
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
 */
/** \file   ee_tc_ssw_bmhd.c
 *  \brief  Contains Boot Header Mode configuration for TC3n families
 *  \author Errico Guidieri
 *  \date   2018
 */
/******************************************************************************
                                      Includes                          
******************************************************************************/
#include "ee_internal.h"

/*******************************************************************************
**                      Type definitions                                     **
*******************************************************************************/


/*******************************************************************************
**                              BMHD constants                                **
*******************************************************************************/

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_0_orig" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_0_orig"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_0_orig" far-absolute R
#endif

const OsEE_tc_ssw_bmhd osEE_tc_bmhd_0_orig =
{
  0x00FE,     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
  0xB359,     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
  0xA0002020,   /**< \brief 0x004: .stad: User Code start address*/
  0x9F93511A,   /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
  0x606CAEE5,   /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x010: Reserved (0x010 - 0x01F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x020: Reserved (0x020 - 0x02F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x030: Reserved (0x030 - 0x03F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x040: Reserved (0x040 - 0x04F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x050: Reserved (0x050 - 0x05F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x060: Reserved (0x060 - 0x06F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x070: Reserved (0x070 - 0x07F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x080: Reserved (0x080 - 0x08F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x090: Reserved (0x090 - 0x09F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0A0: Reserved (0x0A0 - 0x0AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0B0: Reserved (0x0B0 - 0x0BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0C0: Reserved (0x0C0 - 0x0CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0D0: Reserved (0x0D0 - 0x0DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0E0: Reserved (0x0E0 - 0x0EF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x0F0: Reserved (0x0F0 - 0x0FF) */
  },
  {
    0x00000000,   /**< \brief 0x100: PW0: Password protection word 0 (lsw) */
    0x00000000,   /**< \brief 0x104: PW1: Password protection word 1 */
    0x00000000,   /**< \brief 0x108: PW2: Password protection word 2 */
    0x00000000,   /**< \brief 0x10C: PW3: Password protection word 3 */
    0x00000000,   /**< \brief 0x110: PW4: Password protection word 4 */
    0x00000000,   /**< \brief 0x114: PW5: Password protection word 5 */
    0x00000000,   /**< \brief 0x118: PW6: Password protection word 6 */
    0x00000000,   /**< \brief 0x11C: PW7: Password protection word 7 (msw) */
  },
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x120: Reserved (0x120 - 0x12F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x130: Reserved (0x130 - 0x13F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x140: Reserved (0x140 - 0x14F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x150: Reserved (0x150 - 0x15F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x160: Reserved (0x160 - 0x16F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x170: Reserved (0x170 - 0x17F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x180: Reserved (0x180 - 0x18F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x190: Reserved (0x190 - 0x19F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1A0: Reserved (0x1A0 - 0x1AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1B0: Reserved (0x1B0 - 0x1BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1C0: Reserved (0x1C0 - 0x1CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1D0: Reserved (0x1D0 - 0x1DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x1E0: Reserved (0x1E0 - 0x1EF) */
  },
  0x43211234    /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_0_copy" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_0_copy"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_0_copy" far-absolute R
#endif
const OsEE_tc_ssw_bmhd osEE_tc_bmhd_0_copy =
{
  0x00FE,     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
  0xB359,     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
  0xA0002020,   /**< \brief 0x004: .stad: User Code start address*/
  0x9F93511A,   /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
  0x606CAEE5,   /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x010: Reserved (0x010 - 0x01F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x020: Reserved (0x020 - 0x02F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x030: Reserved (0x030 - 0x03F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x040: Reserved (0x040 - 0x04F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x050: Reserved (0x050 - 0x05F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x060: Reserved (0x060 - 0x06F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x070: Reserved (0x070 - 0x07F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x080: Reserved (0x080 - 0x08F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x090: Reserved (0x090 - 0x09F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0A0: Reserved (0x0A0 - 0x0AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0B0: Reserved (0x0B0 - 0x0BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0C0: Reserved (0x0C0 - 0x0CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0D0: Reserved (0x0D0 - 0x0DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0E0: Reserved (0x0E0 - 0x0EF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x0F0: Reserved (0x0F0 - 0x0FF) */
  },
  {
    0x00000000,   /**< \brief 0x100: PW0: Password protection word 0 (lsw) */
    0x00000000,   /**< \brief 0x104: PW1: Password protection word 1 */
    0x00000000,   /**< \brief 0x108: PW2: Password protection word 2 */
    0x00000000,   /**< \brief 0x10C: PW3: Password protection word 3 */
    0x00000000,   /**< \brief 0x110: PW4: Password protection word 4 */
    0x00000000,   /**< \brief 0x114: PW5: Password protection word 5 */
    0x00000000,   /**< \brief 0x118: PW6: Password protection word 6 */
    0x00000000,   /**< \brief 0x11C: PW7: Password protection word 7 (msw) */
  },
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x120: Reserved (0x120 - 0x12F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x130: Reserved (0x130 - 0x13F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x140: Reserved (0x140 - 0x14F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x150: Reserved (0x150 - 0x15F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x160: Reserved (0x160 - 0x16F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x170: Reserved (0x170 - 0x17F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x180: Reserved (0x180 - 0x18F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x190: Reserved (0x190 - 0x19F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1A0: Reserved (0x1A0 - 0x1AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1B0: Reserved (0x1B0 - 0x1BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1C0: Reserved (0x1C0 - 0x1CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1D0: Reserved (0x1D0 - 0x1DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1E0: Reserved (0x1E0 - 0x1EF) */
  },
  0x43211234    /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_1_orig" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_1_orig"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_1_orig" far-absolute R
#endif
const OsEE_tc_ssw_bmhd osEE_tc_bmhd_1_orig =
{
  0x00FE,     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
  0xB359,     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
  0xA0002020,   /**< \brief 0x004: .stad: User Code start address*/
  0x9F93511A,   /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
  0x606CAEE5,   /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x010: Reserved (0x010 - 0x01F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x020: Reserved (0x020 - 0x02F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x030: Reserved (0x030 - 0x03F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x040: Reserved (0x040 - 0x04F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x050: Reserved (0x050 - 0x05F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x060: Reserved (0x060 - 0x06F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x070: Reserved (0x070 - 0x07F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x080: Reserved (0x080 - 0x08F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x090: Reserved (0x090 - 0x09F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0A0: Reserved (0x0A0 - 0x0AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0B0: Reserved (0x0B0 - 0x0BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0C0: Reserved (0x0C0 - 0x0CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0D0: Reserved (0x0D0 - 0x0DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0E0: Reserved (0x0E0 - 0x0EF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x0F0: Reserved (0x0F0 - 0x0FF) */
  },
  {
    0x00000000,   /**< \brief 0x100: PW0: Password protection word 0 (lsw) */
    0x00000000,   /**< \brief 0x104: PW1: Password protection word 1 */
    0x00000000,   /**< \brief 0x108: PW2: Password protection word 2 */
    0x00000000,   /**< \brief 0x10C: PW3: Password protection word 3 */
    0x00000000,   /**< \brief 0x110: PW4: Password protection word 4 */
    0x00000000,   /**< \brief 0x114: PW5: Password protection word 5 */
    0x00000000,   /**< \brief 0x118: PW6: Password protection word 6 */
    0x00000000,   /**< \brief 0x11C: PW7: Password protection word 7 (msw) */
  },
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x120: Reserved (0x120 - 0x12F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x130: Reserved (0x130 - 0x13F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x140: Reserved (0x140 - 0x14F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x150: Reserved (0x150 - 0x15F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x160: Reserved (0x160 - 0x16F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x170: Reserved (0x170 - 0x17F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x180: Reserved (0x180 - 0x18F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x190: Reserved (0x190 - 0x19F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1A0: Reserved (0x1A0 - 0x1AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1B0: Reserved (0x1B0 - 0x1BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1C0: Reserved (0x1C0 - 0x1CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1D0: Reserved (0x1D0 - 0x1DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x1E0: Reserved (0x1E0 - 0x1EF) */
  },
  0x43211234    /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_1_copy" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_1_copy"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_1_copy" far-absolute R
#endif
const OsEE_tc_ssw_bmhd osEE_tc_bmhd_1_copy=
{
  0x00FE,     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
  0xB359,     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
  0xA0002020,   /**< \brief 0x004: .stad: User Code start address*/
  0x9F93511A,   /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
  0x606CAEE5,   /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x010: Reserved (0x010 - 0x01F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x020: Reserved (0x020 - 0x02F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x030: Reserved (0x030 - 0x03F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x040: Reserved (0x040 - 0x04F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x050: Reserved (0x050 - 0x05F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x060: Reserved (0x060 - 0x06F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x070: Reserved (0x070 - 0x07F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x080: Reserved (0x080 - 0x08F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x090: Reserved (0x090 - 0x09F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0A0: Reserved (0x0A0 - 0x0AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0B0: Reserved (0x0B0 - 0x0BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0C0: Reserved (0x0C0 - 0x0CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0D0: Reserved (0x0D0 - 0x0DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0E0: Reserved (0x0E0 - 0x0EF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x0F0: Reserved (0x0F0 - 0x0FF) */
  },
  {
    0x00000000,   /**< \brief 0x100: PW0: Password protection word 0 (lsw) */
    0x00000000,   /**< \brief 0x104: PW1: Password protection word 1 */
    0x00000000,   /**< \brief 0x108: PW2: Password protection word 2 */
    0x00000000,   /**< \brief 0x10C: PW3: Password protection word 3 */
    0x00000000,   /**< \brief 0x110: PW4: Password protection word 4 */
    0x00000000,   /**< \brief 0x114: PW5: Password protection word 5 */
    0x00000000,   /**< \brief 0x118: PW6: Password protection word 6 */
    0x00000000,   /**< \brief 0x11C: PW7: Password protection word 7 (msw) */
  },
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x120: Reserved (0x120 - 0x12F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x130: Reserved (0x130 - 0x13F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x140: Reserved (0x140 - 0x14F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x150: Reserved (0x150 - 0x15F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x160: Reserved (0x160 - 0x16F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x170: Reserved (0x170 - 0x17F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x180: Reserved (0x180 - 0x18F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x190: Reserved (0x190 - 0x19F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1A0: Reserved (0x1A0 - 0x1AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1B0: Reserved (0x1B0 - 0x1BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1C0: Reserved (0x1C0 - 0x1CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1D0: Reserved (0x1D0 - 0x1DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1E0: Reserved (0x1E0 - 0x1EF) */
  },
  0x43211234    /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_2_orig" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_2_orig"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_2_orig" far-absolute R
#endif
const OsEE_tc_ssw_bmhd osEE_tc_bmhd_2_orig=
{
  0x00FE,     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
  0xB359,     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
  0xA0002020,   /**< \brief 0x004: .stad: User Code start address*/
  0x9F93511A,   /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
  0x606CAEE5,   /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x010: Reserved (0x010 - 0x01F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x020: Reserved (0x020 - 0x02F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x030: Reserved (0x030 - 0x03F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x040: Reserved (0x040 - 0x04F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x050: Reserved (0x050 - 0x05F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x060: Reserved (0x060 - 0x06F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x070: Reserved (0x070 - 0x07F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x080: Reserved (0x080 - 0x08F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x090: Reserved (0x090 - 0x09F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0A0: Reserved (0x0A0 - 0x0AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0B0: Reserved (0x0B0 - 0x0BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0C0: Reserved (0x0C0 - 0x0CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0D0: Reserved (0x0D0 - 0x0DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0E0: Reserved (0x0E0 - 0x0EF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x0F0: Reserved (0x0F0 - 0x0FF) */
  },
  {
    0x00000000,   /**< \brief 0x100: PW0: Password protection word 0 (lsw) */
    0x00000000,   /**< \brief 0x104: PW1: Password protection word 1 */
    0x00000000,   /**< \brief 0x108: PW2: Password protection word 2 */
    0x00000000,   /**< \brief 0x10C: PW3: Password protection word 3 */
    0x00000000,   /**< \brief 0x110: PW4: Password protection word 4 */
    0x00000000,   /**< \brief 0x114: PW5: Password protection word 5 */
    0x00000000,   /**< \brief 0x118: PW6: Password protection word 6 */
    0x00000000,   /**< \brief 0x11C: PW7: Password protection word 7 (msw) */
  },
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x120: Reserved (0x120 - 0x12F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x130: Reserved (0x130 - 0x13F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x140: Reserved (0x140 - 0x14F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x150: Reserved (0x150 - 0x15F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x160: Reserved (0x160 - 0x16F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x170: Reserved (0x170 - 0x17F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x180: Reserved (0x180 - 0x18F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x190: Reserved (0x190 - 0x19F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1A0: Reserved (0x1A0 - 0x1AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1B0: Reserved (0x1B0 - 0x1BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1C0: Reserved (0x1C0 - 0x1CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1D0: Reserved (0x1D0 - 0x1DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x1E0: Reserved (0x1E0 - 0x1EF) */
  },
  0x43211234    /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_2_copy" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_2_copy"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_2_copy" far-absolute R
#endif
const OsEE_tc_ssw_bmhd osEE_tc_bmhd_2_copy =
{
  0x00FE,     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
  0xB359,     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
  0xA0002020,   /**< \brief 0x004: .stad: User Code start address*/
  0x9F93511A,   /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
  0x606CAEE5,   /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x010: Reserved (0x010 - 0x01F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x020: Reserved (0x020 - 0x02F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x030: Reserved (0x030 - 0x03F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x040: Reserved (0x040 - 0x04F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x050: Reserved (0x050 - 0x05F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x060: Reserved (0x060 - 0x06F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x070: Reserved (0x070 - 0x07F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x080: Reserved (0x080 - 0x08F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x090: Reserved (0x090 - 0x09F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0A0: Reserved (0x0A0 - 0x0AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0B0: Reserved (0x0B0 - 0x0BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0C0: Reserved (0x0C0 - 0x0CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0D0: Reserved (0x0D0 - 0x0DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0E0: Reserved (0x0E0 - 0x0EF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x0F0: Reserved (0x0F0 - 0x0FF) */
  },
  {
    0x00000000,   /**< \brief 0x100: PW0: Password protection word 0 (lsw) */
    0x00000000,   /**< \brief 0x104: PW1: Password protection word 1 */
    0x00000000,   /**< \brief 0x108: PW2: Password protection word 2 */
    0x00000000,   /**< \brief 0x10C: PW3: Password protection word 3 */
    0x00000000,   /**< \brief 0x110: PW4: Password protection word 4 */
    0x00000000,   /**< \brief 0x114: PW5: Password protection word 5 */
    0x00000000,   /**< \brief 0x118: PW6: Password protection word 6 */
    0x00000000,   /**< \brief 0x11C: PW7: Password protection word 7 (msw) */
  },
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x120: Reserved (0x120 - 0x12F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x130: Reserved (0x130 - 0x13F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x140: Reserved (0x140 - 0x14F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x150: Reserved (0x150 - 0x15F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x160: Reserved (0x160 - 0x16F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x170: Reserved (0x170 - 0x17F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x180: Reserved (0x180 - 0x18F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x190: Reserved (0x190 - 0x19F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1A0: Reserved (0x1A0 - 0x1AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1B0: Reserved (0x1B0 - 0x1BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1C0: Reserved (0x1C0 - 0x1CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1D0: Reserved (0x1D0 - 0x1DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1E0: Reserved (0x1E0 - 0x1EF) */
  },
  0x43211234    /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_3_orig" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_3_orig"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_3_orig" far-absolute R
#endif
const OsEE_tc_ssw_bmhd osEE_tc_bmhd_3_orig =
{
  0x00FE,     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
  0xB359,     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
  0xA0002020,   /**< \brief 0x004: .stad: User Code start address*/
  0x9F93511A,   /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
  0x606CAEE5,   /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x010: Reserved (0x010 - 0x01F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x020: Reserved (0x020 - 0x02F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x030: Reserved (0x030 - 0x03F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x040: Reserved (0x040 - 0x04F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x050: Reserved (0x050 - 0x05F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x060: Reserved (0x060 - 0x06F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x070: Reserved (0x070 - 0x07F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x080: Reserved (0x080 - 0x08F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x090: Reserved (0x090 - 0x09F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0A0: Reserved (0x0A0 - 0x0AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0B0: Reserved (0x0B0 - 0x0BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0C0: Reserved (0x0C0 - 0x0CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0D0: Reserved (0x0D0 - 0x0DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0E0: Reserved (0x0E0 - 0x0EF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x0F0: Reserved (0x0F0 - 0x0FF) */
  },
  {
    0x00000000,   /**< \brief 0x100: PW0: Password protection word 0 (lsw) */
    0x00000000,   /**< \brief 0x104: PW1: Password protection word 1 */
    0x00000000,   /**< \brief 0x108: PW2: Password protection word 2 */
    0x00000000,   /**< \brief 0x10C: PW3: Password protection word 3 */
    0x00000000,   /**< \brief 0x110: PW4: Password protection word 4 */
    0x00000000,   /**< \brief 0x114: PW5: Password protection word 5 */
    0x00000000,   /**< \brief 0x118: PW6: Password protection word 6 */
    0x00000000,   /**< \brief 0x11C: PW7: Password protection word 7 (msw) */
  },
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x120: Reserved (0x120 - 0x12F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x130: Reserved (0x130 - 0x13F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x140: Reserved (0x140 - 0x14F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x150: Reserved (0x150 - 0x15F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x160: Reserved (0x160 - 0x16F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x170: Reserved (0x170 - 0x17F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x180: Reserved (0x180 - 0x18F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x190: Reserved (0x190 - 0x19F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1A0: Reserved (0x1A0 - 0x1AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1B0: Reserved (0x1B0 - 0x1BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1C0: Reserved (0x1C0 - 0x1CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1D0: Reserved (0x1D0 - 0x1DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x1E0: Reserved (0x1E0 - 0x1EF) */
  },
  0x43211234    /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd_3_copy" a
#endif
#if defined(__TASKING__)
#pragma section farrom "bmhd_3_copy"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd_3_copy" far-absolute R
#endif
const OsEE_tc_ssw_bmhd osEE_tc_bmhd_3_copy =
{
  0x00FE,     /**< \brief 0x000: .bmi: Boot Mode Index (BMI)*/
  0xB359,     /**< \brief 0x002: .bmhdid: Boot Mode Header ID (CODE) = B359H*/
  0xA0002020,   /**< \brief 0x004: .stad: User Code start address*/
  0x9F93511A,   /**< \brief 0x008: .crc: Check Result for the BMI Header (offset 000H - 007H)*/
  0x606CAEE5,   /**< \brief 0x00C: .crcInv: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x010: Reserved (0x010 - 0x01F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x020: Reserved (0x020 - 0x02F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x030: Reserved (0x030 - 0x03F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x040: Reserved (0x040 - 0x04F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x050: Reserved (0x050 - 0x05F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x060: Reserved (0x060 - 0x06F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x070: Reserved (0x070 - 0x07F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x080: Reserved (0x080 - 0x08F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x090: Reserved (0x090 - 0x09F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0A0: Reserved (0x0A0 - 0x0AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0B0: Reserved (0x0B0 - 0x0BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0C0: Reserved (0x0C0 - 0x0CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0D0: Reserved (0x0D0 - 0x0DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x0E0: Reserved (0x0E0 - 0x0EF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000  /**< \brief 0x0F0: Reserved (0x0F0 - 0x0FF) */
  },
  {
    0x00000000,   /**< \brief 0x100: PW0: Password protection word 0 (lsw) */
    0x00000000,   /**< \brief 0x104: PW1: Password protection word 1 */
    0x00000000,   /**< \brief 0x108: PW2: Password protection word 2 */
    0x00000000,   /**< \brief 0x10C: PW3: Password protection word 3 */
    0x00000000,   /**< \brief 0x110: PW4: Password protection word 4 */
    0x00000000,   /**< \brief 0x114: PW5: Password protection word 5 */
    0x00000000,   /**< \brief 0x118: PW6: Password protection word 6 */
    0x00000000,   /**< \brief 0x11C: PW7: Password protection word 7 (msw) */
  },
  {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x120: Reserved (0x120 - 0x12F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x130: Reserved (0x130 - 0x13F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x140: Reserved (0x140 - 0x14F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x150: Reserved (0x150 - 0x15F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x160: Reserved (0x160 - 0x16F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x170: Reserved (0x170 - 0x17F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x180: Reserved (0x180 - 0x18F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x190: Reserved (0x190 - 0x19F) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1A0: Reserved (0x1A0 - 0x1AF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1B0: Reserved (0x1B0 - 0x1BF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1C0: Reserved (0x1C0 - 0x1CF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1D0: Reserved (0x1D0 - 0x1DF) */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, /**< \brief 0x1E0: Reserved (0x1E0 - 0x1EF) */
  },
  0x43211234    /**< \brief 0x1F0: .confirmation: 32-bit CODE, (always same)*/
};

#if defined(__GNUC__)
#pragma section
#endif
