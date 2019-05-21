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

/** \file   r_boot_cfg.c
 *  \brief  project core start-up configuration
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

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
  { /* PE0 */
    R_PRJ_HwInit,
    BOOT_ADDR_UNDEFINED,  /* hard coded to compiler specific for PE0 */
    BOOT_ADDR_UNDEFINED,  /* has to be started from main() */
    g_g4mh_RefTblEiPrjCfg,
    g_g4mh_DirVecEiPrjCfg,
    g_g4mh_FePrjCfg,
    g_g4mh_SysCallPrjCfg
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

