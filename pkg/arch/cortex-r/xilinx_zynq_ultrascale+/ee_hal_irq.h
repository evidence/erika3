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

/** \file   ee_hal_irq.h
 *  \brief  HAL for (external) interrupt vector handling.
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#if (!defined(OSEE_HAL_IRQ_H))
#define OSEE_HAL_IRQ_H

#include "ee_cfg.h"
#include "ee_platform_types.h"
#include "ee_utils.h"
#include "ee_compiler.h"
#include "ee_hal.h"
#include "ee_hal_internal_types.h"
#include "ee_std_change_context.h"
#include "ee_kernel_types.h"

/* XIL BSP definitions */
#include "xparameters.h"

/* ERIKA's ISR2 Wrapper */
extern void osEE_cortex_r_irq_hnd(OsEE_ISR_CTX * p_isr_ctx);

/* The Interrupt Controller uses a certain amount of the 8 available bits to
   handle interrupt priorities. These bits are always the most significants of
   the priority byte. So if the GIC handle 32 priorities, it uses the 5 msb.
   This means that the logic virtual ISR priority value have to be left-shifted
   of 3 positions. */
#if (!defined(OSEE_ARMV7_GIC_PRIO_SHIFT))
#define OSEE_ARMV7_GIC_PRIO_SHIFT (0x3U)
#endif /* OSEE_ARMV7_GIC_PRIO_SHIFT */

#if (!defined(OSEE_ISR2_MAX_PRIO))
#define OSEE_ISR2_MAX_PRIO ((TaskPrio)(OSEE_ISR2_PRIO_BIT + 0x3U))
#endif /* OSEE_ISR2_MAX_PRIO */

#define OSEE_ARMV7_GIC_REQUIRE_CS

#endif /* OSEE_HAL_IRQ_H */
