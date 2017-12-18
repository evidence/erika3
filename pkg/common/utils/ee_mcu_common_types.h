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

/** \file   ee_mcu_common_types.h
 *  \brief  Common MCUs Types.
 *
 *  This files contains all common types and symbols for all supported MCUs in
 *  Enterprise MCUs.
 *
 *  \note Those types must be abstracted in order to become platform and
 *        compiler independend. \n
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Giuseppe Serano
 *  \author Errico Guidieri
 *  \date   2016
 */

#ifndef OSEE_MCU_COMMON_TYPES_H
#define OSEE_MCU_COMMON_TYPES_H

#include "ee_utils.h"

/*==============================================================================
                          MCU dependent data types
 =============================================================================*/
#if (defined(OSEE_HAS_MCU_CUSTOM_TYPES_H))
#include "ee_mcu_custom_types.h"
#endif /* OSEE_HAS_MCU_CUSTOM_TYPES_H */

/*==============================================================================
                         MCU independent data types
 =============================================================================*/

/** \brief  Standard Return Type
 *
 *  This type can be used as standard API return type which is shared between
 *  the MCU modules.
 *
 *  The <tt>OSEE_TYPERET</tt> shall normally be used with value <tt>E_OK</tt> or
 *  <tt>E_NOT_OK</tt>. If those return values are not sufficient, MCU modules
 *  specific values can be defined.
 */
#if (!defined(OSEE_TYPERET))
#define OSEE_TYPERET  OsEE_reg
#endif /* !OSEE_TYPERET */

#if (!defined(STATUSTYPEDEFINED))
#define STATUSTYPEDEFINED /**< OSEK compliance */
/* MISRA RULE XX VIOLATION: AUTOSAR standard symbols */
#define E_OK              OSEE_S_J(0x0,OSEE_INTEGER_DEFINES_SUFFIX) /**< OK  */

/** \brief  OSEK compliance
 *
 *  Because <tt>E_OK</tt> is already defined within OSEK, the symbol
 *  <tt>E_OK</tt> has to be shared. To avoid name clashes and redefinition
 *  problems, the symbols have to be defined in the following way
 *  (approved within implementation):<br>
 *  <code>
 *    \#ifndef STATUSTYPEDEFINED<br>
 *    \#define STATUSTYPEDEFINED<br>
 *    \#define E_OK 0x00U<br>
 *    typedef unsigned char StatusType;<br>
 *    \#endif<br>
 *    \#define E_NOT_OK 0x01U<br>
 *  </code>
 */
typedef unsigned char StatusType; /* OSEK compliance */
#endif /* !STATUSTYPEDEFINED */

#if (!defined(E_NOT_OK))
/* MISRA RULE XX VIOLATION: AUTOSAR standard symbols */
#define E_NOT_OK  OSEE_S_J(0x01,OSEE_INTEGER_DEFINES_SUFFIX) /**< NOT OK */
#endif /* !E_NOT_OK */

/** [SWS_Std_00005]
    Name: Std_ReturnType
    Type: uint8
    Range:
      E_OK      -- see 8.2.1, SWS_Std_00006
      E_NOT_OK  -- see 8.2.1, SWS_Std_00006
      0x02-0x3F -- Available to user specific errors

    This type can be used as standard API return type which is shared between
    the RTE and the BSW modules. It shall be defined as follows:
    typedef uint8 Std_ReturnType;
    EG: Some DSP architectures have CHAR_BIT equal to 16. So using unsigned char
        (the smallest unsigned integer usable) is less misleading.
 */
typedef unsigned char Std_ReturnType;

/*
 * The symbols EE_HIGH and EE_LOW shall be defined as follows:
 */
#if (!defined(OSEE_LOW))
#define OSEE_LOW          OSEE_ZERO /**< Physical state 0V */
#endif /* !OSEE_LOW */
#if (!defined(OSEE_HIGH))
#define OSEE_HIGH         OSEE_ONE  /**< Physical state 5V or 3.3V */
#endif /* OSEE_HIGH */

/*
 * The symbols EE_ON and EE_OFF shall be defined as follows:
 */
#if (!defined(OSEE_OFF))
#define OSEE_OFF          OSEE_ZERO /**< OFF */
#endif /* !OSEE_OFF */
#if (!defined(EE_ON))
#define OSEE_ON           OSEE_ONE /**< ON */
#endif /* !OSEE_ON */

/*
 * The symbols EE_ACTIVE and EE_IDLE shall be defined as follows:
 */
#if (!defined(OSEE_IDLE))
#define OSEE_IDLE         OSEE_ZERO /**< Logical state idle */
#endif /* !OSEE_IDLE */
#if (!defined(OSEE_ACTIVE))
#define OSEE_ACTIVE       OSEE_ONE  /**< Logical state active */
#endif /* !OSEE_ACTIVE */

#if (!defined(OSEE_HWREG_PTR))
/** \brief  Harware Register Pointer Type */
#define OSEE_HWREG_PTR  OsEE_reg  volatile *
#endif /* !OSEE_HWREG_PTR */

#if (!defined(OSEE_HWREG_ADDR))
/** \brief  Hardware Register L-Value */
#define OSEE_HWREG_ADDR(x)  ((OSEE_HWREG_PTR)(x))
#endif /* !OSEE_HWREG_ADDR */

#if (!defined(OSEE_HWREG))
/** \brief  Hardware Register R-Value */
#define OSEE_HWREG(x) (*OSEE_HWREG_ADDR(x))
#endif /* !OSEE_HWREG */

#endif  /* OSEE_MCU_COMMON_TYPES_H */
