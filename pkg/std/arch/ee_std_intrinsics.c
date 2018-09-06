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

/** \file   ee_std_intrinsics.c
 *  \brief  Emulation of architectures intrinsics
 *
 *  This files contains the emulation in C of some architecture intrinsics
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2016
 */

#include "ee_internal.h"

#define OSEE_LU_MASK  ((uint8_t)-1)
#define OSEE_LU_NULL  OSEE_LU_MASK

/* this function returns the index of the most significant bit of the mask parameter.
   Example: if the mask value is 0x0100, the function returns 9 */
OSEE_GET_MSB_INLINE FUNC(MemSize, OS_CODE)
  osEE_hal_get_msb
(
  VAR(OsEE_rq_mask, AUTOMATIC) mask
)
{
  static CONST(uint8_t, OS_CONST) osEE_msb_8bit_lookup[256U] = {
    OSEE_LU_NULL, 0U, 1U, 1U, 2U, 2U, 2U, 2U,
              3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U,
              4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U,
              4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U,

              5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U,
              5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U,
              5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U,
              5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U,

              6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
              6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
              6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
              6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,

              6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
              6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
              6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
              6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,

              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,

              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,

              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,

              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
              7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
  };

#if (OSEE_RQ_PRIO_NUM > 16U)
  typedef OsEE_sreg VAR(OsEE_signed_index, TYPEDEF);

  VAR(OsEE_signed_index,  AUTOMATIC) i;

  /* the functions looks at the MSB 8 bit at a time. However, since
     the number of "real" bits that can be used in a configuration may
     be lower than the size of the OEE_rq_mask, then mask_8bit_size
     contains the number of 8-bit cycles that we have to perform in
     oredr to find the MSB (the hypothesis here is that the bits
     higher than OSEE_RQ_PRIO_NUM are 0 */

#if ((OSEE_RQ_PRIO_NUM & 0x7U) == 0U)
  CONST(OsEE_reg,         AUTOMATIC) mask_8bit_size = (OSEE_RQ_PRIO_NUM / 8U);
#else
  CONST(OsEE_reg,         AUTOMATIC) mask_8bit_size = (((OSEE_RQ_PRIO_NUM & (~0x7U)) + 8U) / 8U);
#endif

  VAR(MemSize,            AUTOMATIC) msb = (mask_8bit_size * 8U) - 1U;

  /* N.B. (x << 3U) == (x * 8U) */
  for (i = (OsEE_signed_index)((mask_8bit_size - 1U) << 3U); i >= 0; (i -= 8)) {
    CONST(uint8_t, AUTOMATIC) lu_i =
      (uint8_t)((mask & (((OsEE_rq_mask)OSEE_LU_MASK) << ((uint8_t)i))) >> ((uint8_t)i));
    CONST(uint8_t, AUTOMATIC) msb_tmp = osEE_msb_8bit_lookup[lu_i];

    if (msb_tmp != OSEE_LU_NULL) {
      CONST(uint8_t, AUTOMATIC) msb_tmp2 = ((uint8_t)7U) - msb_tmp;
      msb -= (MemSize)msb_tmp2; /* MISRA 10.8 */
      break;
    } else {
      msb -= 8U;
    }
  }
  return msb;
#elif (OSEE_RQ_PRIO_NUM > 8U)
  VAR(uint8_t, AUTOMATIC)
    msb = osEE_msb_8bit_lookup[(mask & 0xFF00U) >> 8];

  if (msb == OSEE_LU_NULL) {
    msb = osEE_msb_8bit_lookup[mask];
  } else {
    msb += (uint8_t)8U;
  }
  return msb;
#else
  return osEE_msb_8bit_lookup[mask];
#endif
}

