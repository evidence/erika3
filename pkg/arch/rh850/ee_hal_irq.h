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
 *  \brief  HAL for interrupt vector handling.
 *
 *  \author Errico Guidieri
 *  \date   2018
 */
#ifndef OSEE_HAL_IRQ_H
#define OSEE_HAL_IRQ_H

#include "ee_cfg.h"

/* ISR priority level defines: The value of these macros can be used in
   assembly inline templates, so no parentheses nor unsigned specifiers is
   allowed */
#define OSEE_ISR_UNMASKED (16U)
#define OSEE_ISR_PRI_1    (15U)
#define OSEE_ISR_PRI_2    (14U)
#define OSEE_ISR_PRI_3    (13U)
#define OSEE_ISR_PRI_4    (12U)
#define OSEE_ISR_PRI_5    (11U)
#define OSEE_ISR_PRI_6    (10U)
#define OSEE_ISR_PRI_7    (9U)
#define OSEE_ISR_PRI_8    (8U)
#define OSEE_ISR_PRI_9    (7U)
#define OSEE_ISR_PRI_10   (6U)
#define OSEE_ISR_PRI_11   (5U)
#define OSEE_ISR_PRI_12   (4U)
#define OSEE_ISR_PRI_13   (3U)
#define OSEE_ISR_PRI_14   (2U)
#define OSEE_ISR_PRI_15   (1U)
#define OSEE_ISR_PRI_16   (0U)

#if (!defined(ISR))
#define ISR(f) void f(void)
#endif /* !ISR */

#if (!defined(ISR1))
#define ISR1 void f(void)
#endif /* !ISR1 */

#if (!defined(ISR2))
#define ISR2 ISR
#endif /* !ISR2 */

#if (defined(OSEE_HAS_SYSTEM_TIMER))
extern void osEE_rh850_system_timer_handler(void);
#endif /* OSEE_HAS_SYSTEM_TIMER */

#endif /* OSEE_HAL_IRQ_H */
