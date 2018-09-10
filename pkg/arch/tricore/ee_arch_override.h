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

/** \file   ee_arch_override.h
 *  \brief  Override default settings used in the architecture.
 *
 *  This files is used to define a set of defines which some how override
 *  the default architecture behavior.
 *  \author Errico Guidieri
 *  \date 2018
 */

#ifndef OSEE_ARCH_OVERRIDE_H
#define OSEE_ARCH_OVERRIDE_H

/*==============================================================================
                                Stack
 =============================================================================*/
/*
 * TriCore has 2 word alignment requirement for the stack
 */
#define   OSEE_STACK_ALIGN_SIZE         (8U)

/*==============================================================================
                    Arch dependent Configuration Switches
 =============================================================================*/

/* Used to override default definition of osEE_hal_get_msb,
   in ee_std_change_context.h that is not inlined */
#define OSEE_GET_MSB_INLINE OSEE_STATIC_INLINE

/* Used to override default definition of osEE_hal_change_context_from_isr2,
   in ee_std_change_context.h that is not inlined.
   In any case all the TASK termination functionality have to be override
   to take in account TriCore special CSA behavior. */
#define OSEE_ISR2_INLINE OSEE_STATIC_INLINE

/* Override Terminate Activation Kernel Callback (CB).
   Actually I TriCore porting cannot use the CB, so NULL is used as override
   value. */
#define OSEE_KERNEL_TERMINATE_ACTIVATION_CB NULL


#endif  /* !OSEE_ARCH_OVERRIDE_H */
