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

/** \file   ee_avr8_compiler.h
 *  \brief  AVR8 GCC Compiler Definitions.
 *
 *  This file contains all the compiler-dependent definitions for
 *  GNU GCC Compiler for AVR8 Architecture.
 *
 *  \note This file \b MUST contain only \c #defines, because it is also
 *        included by the \c .S files. \n
 *
 *  \note   TO BE DOCUMENTED!!!
 *
 *  \author Giuseppe Serano
 *  \date   2016
 */

#if (!defined(OSEE_AVR8_COMPILER_H))
#define OSEE_AVR8_COMPILER_H

/*
 * Compiler dependent interface
 */
#include "ee_cfg.h"
#include "ee_compiler.h"
#include "ee_utils.h"

#define OSEE_PREPROC_VAR_VALUE(v) #v "=" OSEE_S(v)

/** @def  OSEE_RETURN()
 *
 *  Returns from a function. This should be the last command executed before
 *  leaving a function defined with the EE_NAKED attribute.
 *
 *  This macro actually compiles into a single line of assembly, so there is
 *   no function call overhead.
 */

#define OSEE_RETURN() __asm__ __volatile__ ("ret" ::)

/** @def  OSEE_NAKED
 *
 *  The function is created with no prologue or epilogue code.
 *
 *  The user code is responsible for preservation of the machine state including
 *  the SREG register, as well as placing a EE_return() at the end of the
 *  function.

 *   Use this attribute in the attributes parameter of the function.
 */
#define OSEE_NAKED  __attribute__((naked))

#endif  /* !__INCLUDE_EE_AVR8_COMPILER_H__ */

