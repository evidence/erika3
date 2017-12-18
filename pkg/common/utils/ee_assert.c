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

#ifndef __PRIVATE_ASSERT__
EE_TYPEASSERTVALUE EE_assert(EE_TYPEASSERT id,
           int test,
           EE_TYPEASSERT prev)
{
  /* I can use id into an assertion only once */
  if (EE_assertions[id] != EE_ASSERT_INITVALUE) {
    EE_assertions[id] = EE_ASSERT_ALREADYUSED;
    return EE_ASSERT_ALREADYUSED;
  }

  if (test) {
    if (prev != EE_ASSERT_NIL) {
      if (EE_assertions[prev] == EE_ASSERT_YES) {
  /* test is true and the prev assertion is YES */
  EE_assertions[id] = EE_ASSERT_YES;
  return EE_ASSERT_YES;
      }
      else {
  /* test is true but the prev assertion is != YES */
  EE_assertions[id] = EE_ASSERT_NO;
  return EE_ASSERT_NO;
      }
    } else {
      /* test is true and prev is EE_ASSERT_NIL */
      EE_assertions[id] = EE_ASSERT_YES;
      return EE_ASSERT_YES;
    }
  } else {
    /* test is false */
    EE_assertions[id] = EE_ASSERT_NO;
    return EE_ASSERT_NO;
  }
}
#endif

#ifndef __PRIVATE_ASSERT_OR__
EE_TYPEASSERTVALUE EE_assert_or(EE_TYPEASSERT id,
        EE_TYPEASSERT prev1,
        EE_TYPEASSERT prev2)
{
  /* I can use id into an assertion only once */
  if (EE_assertions[id] != EE_ASSERT_INITVALUE) {
    EE_assertions[id] = EE_ASSERT_ALREADYUSED;
    return EE_ASSERT_ALREADYUSED;
  }

  if ((EE_assertions[prev1] == EE_ASSERT_YES) ||
      (EE_assertions[prev2] == EE_ASSERT_YES)) {
    EE_assertions[id] = EE_ASSERT_YES;
    return EE_ASSERT_YES;
  }
  else {
    EE_assertions[id] = EE_ASSERT_NO;
    return EE_ASSERT_NO;
  }
}
#endif

#ifndef __PRIVATE_ASSERT_AND__
EE_TYPEASSERTVALUE EE_assert_and(EE_TYPEASSERT id,
         EE_TYPEASSERT prev1,
         EE_TYPEASSERT prev2)
{
  /* I can use id into an assertion only once */
  if (EE_assertions[id] != EE_ASSERT_INITVALUE) {
    EE_assertions[id] = EE_ASSERT_ALREADYUSED;
    return EE_ASSERT_ALREADYUSED;
  }

  if ((EE_assertions[prev1] == EE_ASSERT_YES) &&
      (EE_assertions[prev2] == EE_ASSERT_YES)) {
    EE_assertions[id] = EE_ASSERT_YES;
    return EE_ASSERT_YES;
  }
  else {
    EE_assertions[id] = EE_ASSERT_NO;
    return EE_ASSERT_NO;
  }
}
#endif

#ifndef __PRIVATE_ASSERT_RANGE__
EE_TYPEASSERTVALUE EE_assert_range(EE_TYPEASSERT id,
           EE_TYPEASSERT begin,
           EE_TYPEASSERT end)
{
  EE_TYPEASSERT i;

  for (i=begin; i<=end; i++) {
    if (EE_assertions[i] != EE_ASSERT_YES) {
      EE_assertions[id] = EE_ASSERT_NO;
      return EE_ASSERT_NO;
    }
  }

  EE_assertions[id] = EE_ASSERT_YES;
  return EE_ASSERT_YES;
}
#endif

#ifndef __PRIVATE_ASSERT_ALL__
EE_TYPEASSERTVALUE EE_assert_last(void)
{
  return EE_assertions[0];
}
#endif
