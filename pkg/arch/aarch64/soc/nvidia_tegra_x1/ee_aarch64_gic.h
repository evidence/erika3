/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 Evidence s.r.l.
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
 * <https://www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
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

/** \file   ee_aarch64_gic.h
 *  \brief  GIC addresses for NVIDIA Tegrax1
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#if (!defined(OSEE_AARCH64_GIC_H))
#define OSEE_AARCH64_GIC_H

/* GIC base address for NVIDIA TEGRA X1 */
#define OSEE_GIC_BASE     (0x50040000U)
#define OSEE_GICD_OFFSET  (0x1000U)
#define OSEE_GICC_OFFSET  (0x2000U)
#define OSEE_GICH_OFFSET  (0x4000U)
#define OSEE_GICV_OFFSET  (0x6000U)

#define OSEE_GIC_ISR_NUM  (190U)

#endif /* OSEE_AARCH64_GIC_H */
