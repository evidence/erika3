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

/** \file	ee_assert.c
 *  \brief	Assertion Module Implementation.
 *
 *  This files contains the implementation of the Assertion Module.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Paolo Gai
 *  \date	2016
 */
#include "ee_assert.h"

OSEE_TYPEASSERTVALUE OSEE_assert(OSEE_TYPEASSERT id,
           int test,
           OSEE_TYPEASSERT prev)
{
  /* I can use id into an assertion only once */
  if (OSEE_assertions[id] != OSEE_ASSERT_INITVALUE) {
    OSEE_assertions[id] = OSEE_ASSERT_ALREADYUSED;
    return OSEE_ASSERT_ALREADYUSED;
  }

  if (test) {
    if (prev != OSEE_ASSERT_NIL) {
      if (OSEE_assertions[prev] == OSEE_ASSERT_YES) {
  /* test is true and the prev assertion is YES */
  OSEE_assertions[id] = OSEE_ASSERT_YES;
  return OSEE_ASSERT_YES;
      }
      else {
  /* test is true but the prev assertion is != YES */
  OSEE_assertions[id] = OSEE_ASSERT_NO;
  return OSEE_ASSERT_NO;
      }
    } else {
      /* test is true and prev is OSEE_ASSERT_NIL */
      OSEE_assertions[id] = OSEE_ASSERT_YES;
      return OSEE_ASSERT_YES;
    }
  } else {
    /* test is false */
    OSEE_assertions[id] = OSEE_ASSERT_NO;
    return OSEE_ASSERT_NO;
  }
}

OSEE_TYPEASSERTVALUE OSEE_assert_or(OSEE_TYPEASSERT id,
        OSEE_TYPEASSERT prev1,
        OSEE_TYPEASSERT prev2)
{
  /* I can use id into an assertion only once */
  if (OSEE_assertions[id] != OSEE_ASSERT_INITVALUE) {
    OSEE_assertions[id] = OSEE_ASSERT_ALREADYUSED;
    return OSEE_ASSERT_ALREADYUSED;
  }

  if ((OSEE_assertions[prev1] == OSEE_ASSERT_YES) ||
      (OSEE_assertions[prev2] == OSEE_ASSERT_YES)) {
    OSEE_assertions[id] = OSEE_ASSERT_YES;
    return OSEE_ASSERT_YES;
  }
  else {
    OSEE_assertions[id] = OSEE_ASSERT_NO;
    return OSEE_ASSERT_NO;
  }
}

OSEE_TYPEASSERTVALUE OSEE_assert_and(OSEE_TYPEASSERT id,
         OSEE_TYPEASSERT prev1,
         OSEE_TYPEASSERT prev2)
{
  /* I can use id into an assertion only once */
  if (OSEE_assertions[id] != OSEE_ASSERT_INITVALUE) {
    OSEE_assertions[id] = OSEE_ASSERT_ALREADYUSED;
    return OSEE_ASSERT_ALREADYUSED;
  }

  if ((OSEE_assertions[prev1] == OSEE_ASSERT_YES) &&
      (OSEE_assertions[prev2] == OSEE_ASSERT_YES)) {
    OSEE_assertions[id] = OSEE_ASSERT_YES;
    return OSEE_ASSERT_YES;
  }
  else {
    OSEE_assertions[id] = OSEE_ASSERT_NO;
    return OSEE_ASSERT_NO;
  }
}

OSEE_TYPEASSERTVALUE OSEE_assert_range(OSEE_TYPEASSERT id,
           OSEE_TYPEASSERT begin,
           OSEE_TYPEASSERT end)
{
  OSEE_TYPEASSERT i;

  for (i=begin; i<=end; i++) {
    if (OSEE_assertions[i] != OSEE_ASSERT_YES) {
      OSEE_assertions[id] = OSEE_ASSERT_NO;
      return OSEE_ASSERT_NO;
    }
  }

  OSEE_assertions[id] = OSEE_ASSERT_YES;
  return OSEE_ASSERT_YES;
}

OSEE_TYPEASSERTVALUE OSEE_assert_last(void)
{
  return OSEE_assertions[0];
}
