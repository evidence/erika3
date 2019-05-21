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

/** \file   r_prj.h
 *  \brief  project implementation
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

/*******************************************************************************
 * File Name   : r_prj.h
 * Device(s)   : RH850/E2x
 * Description : PRJ API
 ******************************************************************************/


#ifndef R_PRJ_H
#define R_PRJ_H

#include <r_rh850.h>
#include <r_prj_cfg.h>


/*##############################################################################
 # API
 #
 #	R_PRJ_HwInit
 #	R_PRJ_SwInit
 #	R_PRJ_RunBckgrndHook
 #	R_PRJ_FreeTask
 #	R_PRJ_Task5msFirst    (C declaration in out/ee_declcfg.h per ERIKA)
 #	R_PRJ_Task5msSecond   (C declaration in out/ee_declcfg.h per ERIKA)
 #  R_PRJ_Task5msThird	  (C declaration in out/ee_declcfg.h per ERIKA)
 #  R_PRJ_Task5msFourth   (C declaration in out/ee_declcfg.h per ERIKA)
 #  R_PRJ_Task5msFifth    (C declaration in out/ee_declcfg.h per ERIKA)
 #
 ##############################################################################*/

/*******************************************************************************
 * Function Name : R_PRJ_HwInit
 * Description   : project hardware initializations (PLL,...)
 * Arguments     : none
 * Return Value  : none
 * Notice		 : RAM not initialized, only minimal code here
 *******************************************************************************/
extern void R_PRJ_HwInit(void);

/******************************************************************************
 * Function Name : R_PRJ_SwInit
 * Description   : Project initialization.
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
extern void R_PRJ_SwInit(void);

/******************************************************************************
 * Function Name : R_PRJ_RunBckgrndHook
 * Description   : background tasks
 * Arguments     : none
 * Return Value  : none
 * Notes         : background hook shares PE0 load with ERIKA Kernel,
 *               : in extremne loads situations (no idle time available)
 *               : background hook does not tun. Otherwise is it called
 *               : when PE0 is not busy
 *****************************************************************************/
extern void R_PRJ_RunBckgrndHook(void);

/******************************************************************************
 * Function Name : R_PRJ_FreeTask
 * Description   : release of task busy flag
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
extern void R_PRJ_FreeTask(void);


#endif /* R_PRJ_H */

