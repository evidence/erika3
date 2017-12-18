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

/** \file  ee_oo_api_extension.h
 *  \brief  OSEK Kernel Extended APIs.
 *
 *  This files contains all OSEK Kernel Extended APIs in Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */

#if (!defined(OSEE_API_EXTENSION_H))
#define OSEE_API_EXTENSION_H

#include "ee_cfg.h"

#if (defined(OSEE_API_EXTENSION))

#define OS_SERVICE_ID_EXTENSION OS_SERVICE_ID_OSEK

#include "ee_api_types.h"

/* Semaphore forward declaration */
struct OsEE_sem_tag;

typedef P2VAR(struct OsEE_sem_tag, TYPEDEF, OS_APPL_DATA) SemRefType;

#if (!defined(OSEE_COUNT_TYPE))
#define OSEE_COUNT_TYPE               VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_COUNT_TYPE */

typedef OSEE_COUNT_TYPE               CountType;

#if (defined(OSEE_API_DYNAMIC))
FUNC(void, OS_CODE)
  InitSem
(
  VAR(SemRefType, AUTOMATIC)  pSem,
  VAR(CountType, AUTOMATIC)   count
);
#endif /* OSEE_API_DYNAMIC */

FUNC(StatusType, OS_CODE)
  WaitSem
(
  VAR(SemRefType, AUTOMATIC) Sem
);

FUNC(StatusType, OS_CODE)
  PostSem
(
  VAR(SemRefType, AUTOMATIC) Sem
);

#endif /* OSEE_API_EXTENSION */

#define OS_SERVICE_ID_EXTENSION OS_SERVICE_ID_OSEK

#endif /* !OSEE_API_EXTENSION_H_ */
