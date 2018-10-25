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

/** \file   ee_compiler_wr_diab.h
 *  \brief  Common Wind River Diab Compilers Definitions.
 *
 *  This file contains all the common compiler-dependent definitions for
 *  Common Wind River Diab Compiler.
 *
 *  \note This file \b MUST contain only \c defines, because it is also
 *        included by the \c .S files. \n
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

/*
 * Compiler dependent interface
 */
#ifndef OSEE_COMPILER_WR_DIAB_H
#define OSEE_COMPILER_WR_DIAB_H

#include "ee_arch_compiler_wr_diab.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#if (!defined(OSEE_INLINE)) && (!defined(OSEE_STATIC_INLINE))
#if (defined(OSEE_NO_INLINE))
#define OSEE_INLINE
#define OSEE_STATIC_INLINE  static
#elif (defined(__STRICT_ANSI__))
/*
                          WindRiver Keywords
  -Xdialect-strict-ansi or -Xstrict-ansi options disable certain keywords...
  The way to solve these problems is to put "__" at the beginning and end of
  each problematical keyword... */
#define OSEE_INLINE         __inline__
#define OSEE_STATIC_INLINE  static __inline__
#else
#define OSEE_INLINE         inline
#define OSEE_STATIC_INLINE  static inline
#endif /* OSEE_NO_INLINE || __STRICT_ANSI__ */
#endif /* !OSEE_INLINE && !OSEE_STATIC_INLINE */

#if (!defined(OSEE_ALWAYS_INLINE))
#define OSEE_ALWAYS_INLINE      __attribute__((always_inline))
#endif /* !OSEE_ALWAYS_INLINE */
#define OSEE_NEVER_INLINE       __attribute__((noinline))
#define OSEE_NORETURN           __attribute__((noreturn))
#define OSEE_COMPILER_ALIGN(a)  __attribute__((aligned(a)))
#define OSEE_COMPILER_KEEP
#define OSEE_COMPILER_IRQ       __interrupt__

#if (!defined(OSEE_INIT))
/* Arbitrary priority chosen to 10, under investigation */
#define OSEE_INIT               __attribute__((constructor(10)))
#endif /* !OSEE_INIT */

/** \brief  Enforce NOT code reordering at compile level. */
#define OSEE_BARRIER() __scheduling_barrier(void);

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_COMPILER_WR_DIAB_H */
