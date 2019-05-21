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

/** \file   ee_s_barrier.c
 *  \brief  Software barrier implementation, preferred over hardware barr since
 *          I want to know which cores has been the last to leave the barrier.
 *
 *  \author Errico Gudieri
 *  \date   2018
 */

#ifndef R_SYNCH_H
#define R_SYNCH_H


/*#############################################################################
 # API
 #
 #  R_SYNCH_InitBarrier
 #  R_SYNCH_ManageBarrier
 #  R_SYNCH_SetPeActive
 #  R_SYNCH_GetPeValid
 #  R_SYNCH_SetPeValid
 #  R_SYNCH_GetPeStatus
 #  R_SYNHC_SetPeStatus
 #
 ############################################################################*/

/******************************************************************************
 * Function Name : R_SYNCH_InitBarrier
 * Description   : initialize mutual exclusion between PEs
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
extern void R_SYNCH_InitBarrier(void);

/******************************************************************************
 * Function Name : R_SYNC_ManageBarrier
 * Description   : manage mutual exclusion between PEs
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
extern OsEE_bool R_SYNCH_ManageBarrier(void);

/******************************************************************************
 * Function Name : R_SYNC_SetPeActive
 * Description   : update local mask of active Processor Elements (PEs)
 * Arguments     : mask   = PE to add
 * Return Value  : none
 *****************************************************************************/
extern void R_SYNCH_SetPeActive(CoreMaskType mask);

/******************************************************************************
 * Function Name : R_SYNCH_GetPeValid
 * Description   : check if requested PE is valid
 * Arguments     : core   = PE
 * Return Value  : is PE valid
 *****************************************************************************/
extern OsEE_bool R_SYNCH_GetPeValid(CoreNumType core);

/******************************************************************************
 * Function Name : R_SYNCH_SetPeValid
 * Description   : configure PE valid flag as requested
 * Arguments     : core   = PE
 *         : valid    = valid/invalid
 * Return Value  : none
 *****************************************************************************/
extern void R_SYNCH_SetPeValid(CoreNumType core, OsEE_bool valid);

/******************************************************************************
 * Function Name : R_SYNC_GetPeStatus
 * Description   : return PE structure status
 * Arguments     : core   = PE
 * Return Value  : PE structure status
 *****************************************************************************/
extern StatusType R_SYNCH_GetPeStatus(CoreNumType core);

/******************************************************************************
 * Function Name : R_SYNC_SetPeStatus
 * Description   : return PE structure status
 * Arguments     : core   = PE
 *         : ev   = status
 * Return Value  : PE structure status
 *****************************************************************************/
extern void R_SYNCH_SetPeStatus(CoreNumType core, StatusType ev);


#endif /* R_SYNCH_H */
