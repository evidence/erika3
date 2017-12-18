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

/** \file  ee_assert.h
 *  \brief  Assertion Module Interface.
 *
 *  This files contains the interface of the Assertion Module.
 *
 *  EE Test Assertions
 *  ------------------
 *
 *  This component provides a set of macros/functions which allow to
 *  simplify the debug of a generic EE component using an automatic
 *  tool. The paradigm of the testing is a "black box" testing. That
 *  is, assertions are inserted into the code OUTSIDE the component
 *  code, and the test will test the behavior of the system seen by an
 *  external observer.
 *
 *  To debug a component, a set of test cases have to be produced and
 *  verified.
 *
 * E ach test case is composed by:
 *
 *  - a set of tasks, resources, ..., with their properties and init values
 *
 *  - a sequence of calls, ISRs and assertions that constitute a
 *    typical execution of the test case
 *
 *  \b Definition:  The test case is said to be successful if a run
 *        of the application respects the sequence.
 *
 *  To check if a test case is successful, the automatic tool runs the
 *  test case. When the test case ends (i.e., it stops at a predefined
 *  breackpoint), the debugger (or the user) have to check that the
 *  final assertion is verified. If it is verified, the test is passed.
 *
 *  Implementation details
 *  ----------------------
 *
 *  Assertion internal structure:
 *
 *  Assertion Data
 *
 *  - Assertions are identified by an identifier (index in an array).
 *    Index 0 is reserved for the final result that says if the
 *    test case is successful or not.
 *
 *  - The data structure for an assertion is an array of integers
 *    filled with 0s. The array contains a structure with a field
 *    "value" that is 0 if the assertion has not yet been evaluated,
 *    \c ASSERT_NO if the assertion has failed, \c ASSERT_YES if the
 *    assertion was successful.
 *
 *  Assertion functions
 *  -------------------
 *
 *  - Assertions can run with interrupts enabled. Please notice that if a
 *    preemption by an interrupt or another task occurs during the execution of
 *    an assertion, and the preempting task/interrupt modifies the same
 *    assertion, the check for a double use of an assertion may fail.
 *
 *  - The assertion functions should not work as a normal
 *    primitive. Every assertion basically should work with a dedicated
 *    entry in the array. That is, there can not exist two assertions with
 *    the same identifier.
 *
 *  - Assertions can rely on other assertion identifiers to implement
 *    precedence constraints. It is guaranteed that an assertion function
 *    will read the value field only once, to avoid problems due to the
 *    fact that assertion runs with interrupts enabled.
 *
 *  Types that have to be defined in types.h
 *
 *  - \c EE_TYPEASSERT is the type used for the assertion index.
 *    MUST BE SIGNED!!!
 *
 *  - \c EE_TYPEASSERTVALUE contains at least 3 values:
 *    \c 0, \c EE_ASSERT_NO, \c EE_ASSERT_YES
 *    The type \c EE_INT8 should work for most architectures.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Paolo Gai
 *  \date  2016
 */

#ifndef	OSEE_ASSERT_ASSERT_H
#define	OSEE_ASSERT_ASSERT_H

#include "ee.h"


/* types.h */
#ifndef EE_TYPEASSERT
#define EE_TYPEASSERT OsEE_reg
#endif

#ifndef EE_TYPEASSERTVALUE
#define EE_TYPEASSERTVALUE uint8_t
#endif




/* this is an invalid value for the index */
#define EE_ASSERT_NIL      ((EE_TYPEASSERT)(-1))

/* these are the results of each assertion test */
#define EE_ASSERT_INITVALUE   ((EE_TYPEASSERTVALUE)0)
#define EE_ASSERT_YES         ((EE_TYPEASSERTVALUE)1)
#define EE_ASSERT_NO          ((EE_TYPEASSERTVALUE)2)
#define EE_ASSERT_ALREADYUSED ((EE_TYPEASSERTVALUE)3)

/* If MemMap.h support is enabled (i.e. because memory protection): use it */
#ifdef EE_SUPPORT_MEMMAP_H
#define API_START_SEC_VAR_NOINIT
#define API_START_SEC_CODE
#include "MemMap.h"
#endif /* EE_SUPPORT_MEMMAP_H */

#if (defined(ASSERT_LENGTH))
/* the assertion array */
extern EE_TYPEASSERTVALUE EE_assertions[ASSERT_LENGTH];
#else
extern EE_TYPEASSERTVALUE EE_assertions[];
#endif

/* This is the simplest assertion that can be made:
 *
 * the assertion "id" become YES if the test is true and the prev
 * assertion is YES.
 *
 * If no PREVious assertion has to be checked, the prev parameter
 * should be EE_ASSERT_NIL.
 *
 * The return value is either YES or NO depending on the result.
 */
#ifndef __PRIVATE_ASSERT__
EE_TYPEASSERTVALUE EE_assert(EE_TYPEASSERT id,
           int test,
           EE_TYPEASSERT prev);
#endif

/* These are a simple or/and assertion:
 *
 * the assertion "id" become YES if the prev1 or/and prev2
 * assertions are YES.
 */
#ifndef __PRIVATE_ASSERT_OR__
EE_TYPEASSERTVALUE EE_assert_or(EE_TYPEASSERT id,
        EE_TYPEASSERT prev1,
        EE_TYPEASSERT prev2);
#endif

#ifndef __PRIVATE_ASSERT_AND__
EE_TYPEASSERTVALUE EE_assert_and(EE_TYPEASSERT id,
         EE_TYPEASSERT prev1,
         EE_TYPEASSERT prev2);
#endif

/* This is a range assertion, typically used as last assertion.
 *
 * the assertion "id" become YES if ALL the assertions between begin
 * and end are YES.
 */

#ifndef __PRIVATE_ASSERT_RANGE__
EE_TYPEASSERTVALUE EE_assert_range(EE_TYPEASSERT id,
           EE_TYPEASSERT begin,
           EE_TYPEASSERT end);
#endif

/* This is the last assertion. It simply does nothing, and must be
 * included in all the examples with the purpose of setting a
 * breakpoint there.
 */
#ifndef __PRIVATE_ASSERT_LAST__
EE_TYPEASSERTVALUE EE_assert_last(void);
#endif

/* If MemMap.h support is enabled (i.e. because memory protection): use it */
#ifdef EE_SUPPORT_MEMMAP_H
#define API_STOP_SEC_VAR_NOINIT
#define API_STOP_SEC_CODE
#include "MemMap.h"
#endif /* EE_SUPPORT_MEMMAP_H */

#endif	/* OSEE_ASSERT_ASSERT_H */
