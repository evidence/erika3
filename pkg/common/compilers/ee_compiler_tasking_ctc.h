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

/** \file   ee_compiler_tasking_ctc.h
 *  \brief  Common TASKING Compilers Definitions.
 *
 *  This file contains all the common compiler-dependent definitions for
 *  GNU GCC Compiler.
 *
 *  \note This file \b MUST contain only \c defines, because it is also
 *        included by the \c .S files. \n
 *
 *
 *  \author Errico Guidieri
 *  \date   2019
 */
#ifndef OSEE_COMPILER_TASKING_CTC_H
#define OSEE_COMPILER_TASKING_CTC_H

#include "ee_arch_compiler_tasking_ctc.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/*=============================================================================
 * TASKING implements the C99 standard pragma operator that let you embed 
 * pragmas inside macros.
 * So where will be possible we'll use pragmas instead that attributes,
 * because more 'standard' and preferred by MISRA-C.
 * (1.7. Pragmas to Control the Compiler)
 * Syntax for _Pragma operator:
 * _Pragma("[label:]pragma-spec pragma-arguments [on|off|default|restore]")
 ============================================================================*/
/* Used for second level macro expansion and token stringification */
#if (!defined(OSEE_PRAGMA))
#define OSEE_PRAGMA(s) _Pragma(#s)

/*
 * I will use label pragmas
 * (1.7. Pragmas to Control the Compiler -  Label Pragmas)
 * for alignment and sections where I should not share code between
 * TASKING and other (GCC) compilers.
 * I do that to minimize the need of "#pragma ... restore" statments.
 */
#define OSEE_PRAGMA_ALIGN(label,align_value)  \
    OSEE_PRAGMA(label:align align_value)
#define OSEE_PRAGMA_SECTION(label,section_name)   \
    OSEE_PRAGMA(label:section all #section_name)
#endif /* !OSEE_PRAGMA */

#if (defined(OSEE_NO_INLINE))
/** Inline functions */
#define OSEE_INLINE
/** Static Inline functions */
#define OSEE_STATIC_INLINE  static
#else
/** Inline functions */
#define OSEE_INLINE         inline
/** Static Inline functions */
#define OSEE_STATIC_INLINE  static inline
#endif /* OSEE_NO_INLINE  */

/** Always Inline functions */
#if (!defined(__cplusplus))
#define OSEE_ALWAYS_INLINE      __attribute__((always_inline))
#else
#define OSEE_ALWAYS_INLINE
#endif /* !__cplusplus */
/** Never Inline functions */
#define OSEE_NEVER_INLINE       __attribute__((noinline))
/** Function does not return */
#define OSEE_NORETURN           __attribute__((noreturn))
/** Minimum alignment for a variable */
#define OSEE_COMPILER_ALIGN(a)  __attribute__((__align(a)))
/** Mark a function as used also if nevere referenced.
 *  Useful for interrupt handlers that are nevere explicitly referenced 
 *  in the code.
 */
#define OSEE_COMPILER_KEEP      __attribute__((used)) __attribute__((protect))

#if (!defined(OSEE_INIT))
/** Default init section */
#define OSEE_INIT               __attribute__((construct))
#endif /* !OSEE_INIT */

#if 0
#define OSEE_COMPILER_WEAK        __attribute__((weak))
#define OSEE_COMPILER_EXPORT      __attribute__((export))
#endif /* 0 */

/* __vector_table is not defined for single-core CPUs... :( */
#if (defined(__CPU_TC22X__)) || (defined(__CPU_TC23X__))
#define OSEE_VECTORS_TABLE(c)
#else
#define OSEE_VECTORS_TABLE(c)  __vector_table(c)
#endif /* __CPU_TC22X__ || __CPU_TC23X__ */

/* This define is needed to enhance equivalence between GCC compiler and
   TASKING compiler so they can share mostly of the code. */
#define __asm__ __asm

/** \brief  Software "memory barrier" (or "memory clobber") to enforce NOT code
            reordering. At compile level.
   www.nongnu.org/avr-libc/user-manual/optimization.html */
#define OSEE_BARRIER() __asm volatile("" : : : "memory")

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_COMPILER_TASKING_CTC_H */

