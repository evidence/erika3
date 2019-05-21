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

/*******************************************************************************
 * File Name   : r_boot_cfg.c
 * Device(s)   : RH850/E2x
 * Description : project core start-up configuration,
 *             : provided by Evidence (Errico Gudieri, 2018)
 ******************************************************************************/


#include <r_prj.h>


/*##############################################################################
 # local defines
 ##############################################################################*/

/*******************************************************************************
 * BOOT entry casting
 ******************************************************************************/
#define BOOT_ADDR_UNDEFINED    ((boot_code_t)0x0)


/*##############################################################################
 # local configurations
 ##############################################################################*/

/*******************************************************************************
 * PE configuration
 ******************************************************************************/
static const boot_pe_cfg_t pe[] =
{
  {/* PE0 */
    R_PEID0_HwInit,
    BOOT_ADDR_UNDEFINED,  /* Hard coded to compiler specific for PE0 */
    BOOT_ADDR_UNDEFINED,  /* Has to be started from main() */
    g_peid0_RefTblEiPrjCfg,
    g_peid0_DirVecEiPrjCfg,
    g_peid0_FePrjCfg,
    g_peid0_SysCallPrjCfg
  },
  {/* PE1 */
    R_PEID1_HwInit,
    R_PEID1_SwInit,
    BOOT_ADDR_UNDEFINED,
    g_peid1_RefTblEiPrjCfg,
    g_peid1_DirVecEiPrjCfg,
    g_peid1_FePrjCfg,
    g_peid1_SysCallPrjCfg
  },
  {/* PE2 */
    R_PEID2_HwInit,
    R_PEID2_SwInit,
    BOOT_ADDR_UNDEFINED,
    g_peid2_RefTblEiPrjCfg,
    g_peid2_DirVecEiPrjCfg,
    g_peid2_FePrjCfg,
    g_peid2_SysCallPrjCfg
  },
  {/* PE3 */
    R_PEID3_HwInit,
    R_PEID3_SwInit,
    BOOT_ADDR_UNDEFINED,
    g_peid3_RefTblEiPrjCfg,
    g_peid3_DirVecEiPrjCfg,
    g_peid3_FePrjCfg,
    g_peid3_SysCallPrjCfg
  },
  {/* PE4 */
    R_PEID4_HwInit,
    R_PEID4_SwInit,
    BOOT_ADDR_UNDEFINED,
    g_peid4_RefTblEiPrjCfg,
    g_peid4_DirVecEiPrjCfg,
    g_peid4_FePrjCfg,
    g_peid4_SysCallPrjCfg
  },
  {/* PE5 */
    R_PEID5_HwInit,
    R_PEID5_SwInit,
    BOOT_ADDR_UNDEFINED,
    g_peid5_RefTblEiPrjCfg,
    g_peid5_DirVecEiPrjCfg,
    g_peid5_FePrjCfg,
    g_peid5_SysCallPrjCfg
  }
};


/*##############################################################################
 # global configurations
 ##############################################################################*/

/*******************************************************************************
 * Project multi-core configuration
 ******************************************************************************/
const boot_cfg_t g_boot_PrjCfg =
{
  sizeof(boot_pe_cfg_t),
  sizeof(pe)/sizeof(pe[0]),
  pe
};
