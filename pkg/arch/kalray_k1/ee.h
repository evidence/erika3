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

/** \file  ee.h
 *  \brief  Main Collector.
 *
 *  This files is the main collector in Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \author  Giuseppe Serano
 *  \date  2016
 */

#if (!defined(OSEE_H))
#define OSEE_H

#if (defined(__cplusplus))
extern "C" {
#endif

#include "ee_cfg.h"
#include "ee_platform_types.h"
#include "ee_k1_vbsp.h"
#include "ee_utils.h"
#include "ee_hal.h"
#include "ee_api.h"
#include "ee_api_k1.h"
#if (defined(OSEE_ASSERT))
#include "ee_assert.h"
#endif  /* OSEE_ASSERT */
#include "ee_k1_irq.h"

#if (!defined(OSEE_SINGLECORE)) && (defined(OSEE_API_EXTENSION))
#include "ee_api_k1.h"
#endif /* !OSEE_SINGLECORE && OSEE_API_EXTENSION_ */

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_H */
