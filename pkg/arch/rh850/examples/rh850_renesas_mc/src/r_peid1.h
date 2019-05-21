/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 - 2019 Evidence s.r.l.
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
 * <www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
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

/******************************************************************************
 * File Name   : r_peid1.h
 * Device(s)   : RH850/E2x
 * Description : PEID1 API
 *****************************************************************************/


#ifndef R_PEID1_H
#define R_PEID1_H


/*#############################################################################
 # API
 #
 #  R_PEID1_HwInit
 #  R_PEID1_SwInit
 #  R_PEID1_RunBckgrndHook
 #  R_PEID0_Task500ms (C declaration in out/ee_declcfg.h per ERIKA)
 #
 ############################################################################*/

/******************************************************************************
 * Function Name : R_PEID1_HwInit
 * Description   : project hardware initializations (PLL,...)
 * Arguments     : none
 * Return Value  : none
 * Notice   : RAM not initialized, only minimal code here
 *****************************************************************************/
extern void R_PEID1_HwInit(void);

/******************************************************************************
 * Function Name : R_PEID1_SwInit
 * Description   : Project initialization.
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
extern void R_PEID1_SwInit(void);

/******************************************************************************
 * Function Name : R_PEID1_RunBckgrndHook
 * Description   : background tasks
 * Arguments     : none
 * Return Value  : none
 * Notes         : background hook shares PE1 load with ERIKA Kernel,
 *               : in extremne loads situations (no idle time available)
 *               : background hook does not tun. Otherwise is it called
 *               : when PE0 is not busy
 *****************************************************************************/
extern void R_PEID1_RunBckgrndHook(void);



#endif /* R_PEID1_H */

