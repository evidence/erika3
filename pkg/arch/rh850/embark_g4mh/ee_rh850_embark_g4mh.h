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

/** \file   ee_rh850_embark_g4mh.h
 *  \brief  OS features Integration file with Embark G4MH Software Library
 *
 *  \author Errico Guidieri
 *  \date   2018
 */
#ifndef OSEE_RH850_EMBARK_E2X_H
#define OSEE_RH850_EMBARK_E2X_H

#include "ee_platform_types.h"
#include "ee_platform_types.h"
#include "ee_compiler.h"
#include "ee_utils.h"
#include "ee_api.h"
#include <r_intc.h>

typedef struct {
  intc_cfg_t const  * p_intc_cfg_array;
  uint16_t            intc_cfg_num;
} OSEE_CONST OsEE_rh850_embark_g4mh_intc_cfg;

extern void osEE_rh850_isr2_embark_g4mh_wrapper(TaskType tid);

#if (defined(OSEE_HAS_SYSTEM_TIMER))
#define OSEE_RH850_DEVICE_18  (18U)
#define OSEE_RH850_DEVICE_19  (19U)

#if (OSEE_SYSTEM_TIMER_CORE0_DEVICE != OSEE_RH850_DEVICE_18) &&\
    (OSEE_SYSTEM_TIMER_CORE0_DEVICE != OSEE_RH850_DEVICE_19)
#error Unknown device for System Timer
#endif /* OSEE_SYSTEM_TIMER_CORE0_DEVICE */

extern void osEE_rh850_system_timer_handler_wrapper(void);
#endif /* OSEE_HAS_SYSTEM_TIMER */

#endif /* !OSEE_RH850_EMBARK_G4MH_H */
