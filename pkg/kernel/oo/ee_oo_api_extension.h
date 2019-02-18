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

/** \file  ee_oo_api_extension.h
 *  \brief  OSEK Kernel Extended APIs.
 *
 *  This files contains all OSEK Kernel Extended APIs in Erika Enterprise.
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */

#ifndef OSEE_API_EXTENSION_H
#define OSEE_API_EXTENSION_H

#include "ee_cfg.h"

#if (defined(OSEE_API_EXTENSION))

#include "ee_api_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/* Semaphore forward declaration */
struct OsEE_sem_tag;

/**
 *  Pointer to a Semaphore data structure.
 *  \ingroup primitives-sem
 */
typedef P2VAR(struct OsEE_sem_tag, TYPEDEF, OS_APPL_DATA) SemRefType;

#if (!defined(OSEE_COUNT_TYPE))
/** Internal type for the semaphore counter */
#define OSEE_COUNT_TYPE               VAR(OsEE_reg, TYPEDEF)
#endif /* !OSEE_COUNT_TYPE */
/**
 *  Type for the semaphore counter
 *  \ingroup primitives-sem
 */
typedef OSEE_COUNT_TYPE               CountType;

#if (defined(OSEE_API_DYNAMIC))

/**
 *  \brief Initialize a Semaphore at runtime
 *  \ingroup primitives-sem
 *  
 *  This macro can be used to initialize a semaphore at runtime. It
 *  receives as a parameter the init value of the semaphore counter.
 * 
 *  Conformance Classes: ECC1, ECC2
 *  
 *  \param [out] pSem The semaphore being initialized. 
 *  \param [in] count The counter value for the semaphore being initialized.
 */
FUNC(void, OS_CODE)
  InitSem
(
  VAR(SemRefType, AUTOMATIC)  pSem,
  VAR(CountType, AUTOMATIC)   count
);
#endif /* OSEE_API_DYNAMIC */

/**
 *  \brief Semaphore blocking wait.
 *  \ingroup primitives-sem
 *  
 *  If the semaphore counter is greater than 0, then the counter is
 *  decremented by one. If the counter has a value of 0, then the
 *  calling (running) task blocks. 
 *
 *  This function can only be called by extended tasks in conformance
 *  classes ECC1 and ECC2.
 *
 *  Conformance Classes: ECC1, ECC2
 *  
 *  \param [in] Sem The semaphore used by the primitive.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_CALLEVEL (Extended) The primitive was called at interrupt
 *            level.
 *          - E_OS_RESOURCE (Extended) The calling task occupies resources.
 *          - E_OS_ACCESS (Extended) The calling task is not an extended task.
 */
FUNC(StatusType, OS_CODE)
  WaitSem
(
  VAR(SemRefType, AUTOMATIC) Sem
);

/**
 *  \brief Post on a semaphore
 *  \ingroup primitives-sem
 *  
 *  This primitive unblocks a task eventually blocked on the
 *  semaphore. If there are no tasks blocked on the semaphore, then
 *  the semaphore counter is incremented by one.
 *
 *  Conformance Classes: ECC1, ECC2
 *  
 *  \param [in] Sem The semaphore used by the primitive.
 *  \return The function returns a StatusType.
 *          - E_OK No error.
 *          - E_OS_VALUE The semaphore has not been incremented because
 *            its counter was equal to the semaphore maximum value
 *            EE_MAX_SEM_COUNTER.
 */
FUNC(StatusType, OS_CODE)
  PostSem
(
  VAR(SemRefType, AUTOMATIC) Sem
);

#if (defined(__cplusplus))
}
#endif

#endif /* OSEE_API_EXTENSION */

#endif /* !OSEE_API_EXTENSION_H_ */
