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

/** \file	ee_hal.h
 *  \brief	HAL support visible to the application.
 *
 *  This files contains all HAL for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \author	Errico Guidieri
 *  \author	Giuseppe Serano
 *  \date	2018
 */

#ifndef OSEE_HAL_H
#define	OSEE_HAL_H

/*==============================================================================
                          HAL Types and structures
 =============================================================================*/
#include "ee_cfg.h"
#include "ee_utils.h"
#include "ee_compiler.h"
#include "ee_platform_types.h"
#include "ee_api_types.h"

#if	(!defined(__GNUC__))
#error	Unsupported compiler!
#endif	/* !__GNUC__ */

#if (defined(__cplusplus))
extern "C" {
#endif

/*==============================================================================
                            Array Utilities
 =============================================================================*/

#if	(!defined(OSEE_FILL_PATTERN))
/** Fill Pattern Used for Stack Monitoring */
#define	OSEE_FILL_PATTERN	(0xA5A5A5A5U)
#endif	/* !OSEE_FILL_PATTERN */

/** Fill Pattern Used for Stack Monitoring.
  * Uses Range Designated Initializers
  * \param [in] array The array to be filled.
  */
#define	OSEE_FILL_ARRAY(array) = {				\
	[0 ... (sizeof(array)/sizeof((array)[0U]) - 1U)] =	\
	OSEE_FILL_PATTERN					\
}

/*==============================================================================
                 Utility Macros for debugging and tracing purposes
 =============================================================================*/

/*==============================================================================
                 Utility Functions
 =============================================================================*/

/**
 *  \brief Returns the current stack pointer.
 *  
 *  Returns the current stack pointer.
 *  
 *  \return Returns an address which is the current value of the stack pointer.
 */
OSEE_STATIC_INLINE FUNC(OsEE_addr, OS_CODE) OSEE_ALWAYS_INLINE
osEE_get_SP (
void
) {
  VAR(OsEE_addr, AUTOMATIC) temp;
  OSEE_GET_SP(temp);
  return temp;
}

/**
 *  \brief Returns the current core ID.
 *  
 *  Returns the current core ID. Always 0 on single cores.
 *  
 *  \return Returns the current core ID.
 */
OSEE_STATIC_INLINE FUNC(CoreIdType, OS_CODE) OSEE_ALWAYS_INLINE
osEE_get_curr_core_id (
  void
) {
  return (CoreIdType)0U;
}

#if (defined(__cplusplus))
}
#endif

#endif	/* !OSEE_HAL_H */
