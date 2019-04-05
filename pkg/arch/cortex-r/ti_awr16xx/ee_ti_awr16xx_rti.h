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

/** \file   ee_ti_awr16xx_rti.h
 *  \brief  TI RTI minimal driver
 *
 *  \author Errico Guidieri
 *  \date   2019
 */

#ifndef OSEE_TI_AWR16XX_RTI_H
#define OSEE_TI_AWR16XX_RTI_H

#include "ee_cfg.h"
#include "ee_arch_override.h"

#include "ee_compiler.h"
#include "ee_utils.h"
#include "ee_platform_types.h"

#if (!defined(OSEE_HAS_SYSTEM_TIMER))
extern void osEE_ti_awr16xx_rti_init(void);
#endif /* !OSEE_HAS_SYSTEM_TIMER */

enum ti_rti_frc {
  TI_RTI_FRC_0,
  TI_RTI_FRC_1
};

OsEE_reg osEE_ti_awr16xx_get_frc(enum ti_rti_frc);

#endif /* OSEE_TI_AWR16XX_RTI_H */
