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

/** \file   ee_compiler.h
 *  \brief  Common Utilities.
 *
 *  This files contains all common utilities available in Erika Enterprise.
 *
 *  \note Those utilities must be abstracted in order to become platform
 *        and compiler independend. \n
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */

#if (!defined(OSEE_UTILS_H))
#define OSEE_UTILS_H

#include "ee_compiler.h"

/*==============================================================================
                              Useful Generic Macros
 =============================================================================*/

/*==============================================================================
                           String Manipulation Macros
 =============================================================================*/

#if (!defined(OSEE_STRING_JOIN))
#define OSEE_STRING_JOIN(a,b)  a##b
#endif /* !OSEE_STRING_JOIN */

#if (!defined(OSEE_STRING))
#define OSEE_STRING(s)         #s
#endif /* !OSEE_STRING */

/* String manipulation macros with one more step indirection to let argument
   macro explode */
#if (!defined(OSEE_EVAL))
#define OSEE_EVAL(e)           e
#endif /* !OSEE_EVAL */

#if (!defined(OSEE_S))
#define OSEE_S(m)             OSEE_STRING(m)
#endif /* !OSEE_S */

#if (!defined(OSEE_S_J))
#define OSEE_S_J(s1,s2)       OSEE_STRING_JOIN(s1,s2)
#endif /* !OSEE_S_J */

/*==============================================================================
                                Run Assertion
 =============================================================================*/
#if (!defined(OSEE_RUN_ASSERT))
#if (defined(OSEE_ENABLE_RUN_ASSERT))
/* TODO: Add some kind of assertion libs */
#if (defined(__STDC_VERSION_)) && (__STDC_VERSION__ >= 199901L)
  /* C99 */
#define OSEE_RUN_ASSERT(cond,MSG) \
  (void)OSEE_S_J(OSEE_S_J(OSEE_S_J(OSEE_S_J(OSEE_S_J(OSEE_S_J(__FILE__,"-"),
    __LINE__),":"),__func__),"="),MSG)
#else
#define OSEE_RUN_ASSERT(cond,MSG) \
  (void)OSEE_S_J(OSEE_S_J(OSEE_S_J(OSEE_S_J(__FILE__,"-"),__LINE__),"="),MSG)
#endif
#else
#define OSEE_RUN_ASSERT(cond,MSG)
#endif /* OSEE_RUN_ENABLE_ASSERT */
#endif /* !OSEE_RUN_ASSERT */

/*==============================================================================
                                 Static Assertion
 =============================================================================*/
#if (!defined(OSEE_STATIC_ASSERT))
#if (defined(OSEE_ENABLE_STATIC_ASSERT))
#define OSEE_STATIC_ASSERT(cond,MSG) \
  typedef char OSEE_S_J(OsEE_static_assertion_,MSG)[(cond)?1:-1];
#else
#define OSEE_STATIC_ASSERT(cond,MSG)
#endif /* OSEE_ENABLE_STATIC_ASSERT */
#endif /* !OSEE_STATIC_ASSERT */

/*==============================================================================
                                 Boolean Macros
 =============================================================================*/

#if (!defined(OSEE_M_TRUE))
#define OSEE_M_TRUE (0==0)
#endif /* !OSEE_M_TRUE */

#if (!defined(OSEE_M_FALSE))
#define OSEE_M_FALSE (0!=0)
#endif /* !OSEE_M_FALSE */

/*==============================================================================
                               Integers Macros
 =============================================================================*/

#if (!defined(OSEE_INTEGER_DEFINES_SUFFIX))
#define OSEE_INTEGER_DEFINES_SUFFIX U
#endif /* !OSEE_INTEGER_DEFINES_SUFFIX */

#if (!defined(OSEE_ZERO))
#define OSEE_ZERO         OSEE_S_J(0, OSEE_INTEGER_DEFINES_SUFFIX)
#endif /* !OSEE_ZERO */

#if (!defined(OSEE_ONE))
#define OSEE_ONE          OSEE_S_J(1, OSEE_INTEGER_DEFINES_SUFFIX)
#endif /* !OSEE_ONE */

#if (!defined(OSEE_KILO))
#define OSEE_KILO         OSEE_S_J(1000, OSEE_INTEGER_DEFINES_SUFFIX)
#endif /* !OSEE_KILO */

#if (!defined(OSEE_MEGA))
#define OSEE_MEGA         OSEE_S_J(1000000, OSEE_INTEGER_DEFINES_SUFFIX)
#endif /* !OSEE_MEGA */

#if (!defined(OSEE_GIGA))
#define OSEE_GIGA         OSEE_S_J(1000000000, OSEE_INTEGER_DEFINES_SUFFIX)
#endif /* !OSEE_GIGA */

/*==============================================================================
                              Bitmasking Macros
 =============================================================================*/

#if (!defined(OSEE_BIT))
/* \brief Single bit bitmask generator. */
#define OSEE_BIT(type,bit)     (((type)1) << (bit))
#endif /* !OSEE_BIT */

#if (!defined(OSEE_ONES))
/* \brief Generate a Single bit bitmask generator. */
#define OSEE_ONES(num)         ((1U << (num)) - 1U)
#endif /* !OSEE_ONES */

#if (!defined(OSEE_B_MASK))
#define OSEE_B_MASK(length, lower_bit)      (OSEE_ONES(length) << (lower_bit))
#endif /* !OSEE_B_MASK */

#if (!defined(OSEE_B_GET))
#define OSEE_B_GET(x, length, lower_bit)    \
  ((x) & OSEE_B_MASK(length, lower_bit))
#endif /* !OSEE_B_GET */

#if (!defined(OSEE_B_CLEAR))
#define OSEE_B_CLEAR(x, length, lower_bit)  \
  ((x) & (~OSEE_B_MASK(length, lower_bit)))
#endif /* OSEE_B_CLEAR */

#if (!defined(OSEE_B_SET))
#define OSEE_B_SET(x, length, lower_bit, v) \
  (OSEE_B_CLEAR(x,length,lower_bit) |\
    (((v) & OSEE_ONES(length)) << (lower_bit))\
  )
#endif /* !OSEE_B_SET*/

/* Range Bitmasks. r is a bit range with this syntax h:l.
   It is a trick that uses ternary operator */
#if (!defined(OSEE_DISABLE_R_MACROS))
#if (!defined(OSEE_R_LOW))
#define OSEE_R_LOW(r)     (0?r)
#endif /* !OSEE_R_LOW */

#if (!defined(OSEE_R_HIGH))
#define OSEE_R_HIGH(r)    (1?r)
#endif /* !OSEE_R_HIGH */

#if (!defined(OSEE_R_LENGTH))
#define OSEE_R_LENGTH(r)  (OSEE_R_HIGH(r) - OSEE_R_LOW(r) + 1U)
#endif /* !OSEE_R_LENGTH */

#if (!defined(OSEE_R_MASK))
#define OSEE_R_MASK(r)    OSEE_B_MASK(OSEE_R_LENGTH(r), OSEE_R_LOW(r))
#endif /* !OSEE_R_MASK */

#if (!defined(OSEE_R_GET))
#define OSEE_R_GET(x,r)   OSEE_B_GET(x, OSEE_R_LENGTH(r), OSEE_R_LOW(r))
#endif /* !OSEE_R_GET */

#if (!defined(OSEE_R_CLEAR))
#define OSEE_R_CLEAR(x,r) OSEE_B_CLEAR(x, OSEE_R_LENGTH(r), OSEE_R_LOW(r))
#endif /* !OSEE_R_CLEAR */

#if (!defined(OSEE_R_SET))
#define OSEE_R_SET(x,r,v) OSEE_B_SET(x, OSEE_R_LENGTH(r), OSEE_R_LOW(r), v)
#endif /* !OSEE_R_SET */
#endif /* !OSEE_DISABLE_R_MACROS */

/*==============================================================================
                                 Array Macros
 =============================================================================*/

#if (!defined(OSEE_ARRAY_ELEMENT_COUNT))
/** \brief Utility macro that Count the number of element for an Array */
#define OSEE_ARRAY_ELEMENT_COUNT(ar) \
  ((sizeof(ar)/sizeof(0[ar])) / (!(sizeof(ar) % sizeof(0[ar]))))
#endif /* !OSEE_ARRAY_ELEMENT_COUNT */

/*==============================================================================
                             Stack Alignment Macros
 =============================================================================*/

#if (!defined(OSEE_STACK_ALIGN_SIZE))
#define OSEE_STACK_ALIGN_SIZE   (sizeof(OsEE_stack))
#endif /* !OSEE_STACK_ALIGN_SIZE */

#if (!defined(OSEE_STACK_ALIGN))
#define OSEE_STACK_ALIGN        (~(OSEE_STACK_ALIGN_SIZE - 1U))
#endif /* !OSEE_STACK_ALIGN */

#if (!defined(OSEE_STACK_ALIGN_INDEX))
#define OSEE_STACK_ALIGN_INDEX \
  (~((OSEE_STACK_ALIGN_SIZE/sizeof(OsEE_stack)) -1U))
#endif /* OSEE_STACK_ALIGN_INDEX */

#if (!defined(OSEE_STACK_WORD_LENGHT))
/** \brief Used to initialize stack arrays with the right size. */
#define OSEE_STACK_WORD_LENGHT(size)\
  (((size) + OSEE_STACK_ALIGN_SIZE - 1U) / sizeof(OsEE_stack))
#endif /* !OSEE_STACK_WORD_LENGHT */

#if (!defined(OSEE_STACK_TOS))
#define OSEE_STACK_TOS(stack) \
  ((OsEE_addr)&stack[((sizeof(stack)/sizeof(stack[0])) - 1U) & \
    OSEE_STACK_ALIGN_INDEX])
#endif /* OSEE_STACK_TOS */

#if (!defined(OSEE_STACK_BOS))
#define OSEE_STACK_BOS(stack)   ((OsEE_addr)&stack[0U])
#endif /* !OSEE_STACK_BOS */

#if (!defined(OSEE_GUARD_AREA))
#define OSEE_STACK_GUARD_AREA   (OSEE_STACK_ALIGN_SIZE)
#endif /* !OSEE_GUARD_AREA */

#if (!defined(OSEE_GET_STACK_POINTER))
#define OSEE_GET_STACK_POINTER(pool)\
  ((OsEE_stack *)((char *)(pool) - (ptrdiff_t)(((OSEE_STACK_GUARD_AREA) + \
      (OSEE_STACK_ALIGN_SIZE - 1U)) & OSEE_STACK_ALIGN)))
#endif /* !OSEE_GET_STACK_POINTER */

#if (!defined(OSEE_ADJUST_POOL_BASE))
#define OSEE_ADJUST_POOL_BASE(pool, size)\
  ((pool) - (ptrdiff_t)(size))
#endif /* !OSEE_ADJUST_POOL_BASE */

/*==============================================================================
                             Time to Ticks Utilities
 =============================================================================*/
#if (!defined(OSEE_MILLI_TO_TICKS))
/** \brief Utility macro that convert an amount of ms in number of ticks of a
           given fequency */
#define OSEE_MILLI_TO_TICKS(X_MS, REF_FREQ_HZ)  \
  ((X_MS) * ((REF_FREQ_HZ) / OSEE_KILO))
#endif /* !OSEE_MILLI_TO_TICKS */

#if (!defined(OSEE_MICRO_TO_TICKS))
/** \brief Utility macro that convert an amount of us in number of ticks of a
           given frequency */
#define OSEE_MICRO_TO_TICKS(X_US, REF_FREQ_HZ)                \
  (((X_US) / OSEE_KILO)?                                      \
      OSEE_MILLI_TO_TICKS(((X_US) / OSEE_KILO), REF_FREQ_HZ): \
      (OSEE_MILLI_TO_TICKS(X_US, REF_FREQ_HZ) / OSEE_KILO))
#endif /* !OSEE_MICRO_TO_TICKS */

#if (!defined(OSEE_NANO_TO_TICKS))
/** \brief Utility macro that convert an amount of ns in number of ticks of a
           given frequency */
#define OSEE_NANO_TO_TICKS(X_NS, REF_FREQ_HZ)                 \
  (((X_NS) / OSEE_KILO)?                                      \
      OSEE_MICRO_TO_TICKS(((X_NS) / OSEE_KILO), REF_FREQ_HZ): \
      (OSEE_MICRO_TO_TICKS(X_NS, REF_FREQ_HZ) / OSEE_KILO))
#endif /* !OSEE_NANO_TO_TICKS */

#if (!defined(OSEE_TICKS_TO_NANO))
/** \brief Utility macro that convert an amount of ticks in equivalent ns
           given a frequency */
#define OSEE_TICKS_TO_NANO(TICKS, REF_FREQ_HZ)            \
  (((TICKS) / OSEE_KILO)?                                 \
    ((TICKS) * OSEE_KILO) / ((REF_FREQ_HZ) / OSEE_MEGA):  \
    ((TICKS) * OSEE_MEGA) / ((REF_FREQ_HZ) / OSEE_KILO))
#endif /* !OSEE_TICKS_TO_NANO */

#if (!defined(OSEE_TICKS_TO_MICRO))
/** \brief Utility macro that convert an amount of ticks in equivalent us
           given a frequency */
#define OSEE_TICKS_TO_MICRO(TICKS, REF_FREQ_HZ)  \
  (OSEE_TICKS_TO_NANO(TICKS, REF_FREQ_HZ) / OSEE_KILO)
#endif /* !OSEE_TICKS_TO_MICRO */

#endif /* !OSEE_UTILS_H */
