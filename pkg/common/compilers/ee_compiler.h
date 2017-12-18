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
 *  \brief  Compilers Abstraction File
 *
 *  This files is a collector between all supported compilers in
 *  Erika Enterprise.
 *
 *  \author Errico Guidieri
 *  \date   2016
 */
 
#if (!defined(OSEE_COMPILER_H))
#define OSEE_COMPILER_H

/*==============================================================================
                        INCLUDES Compiler Configuration
 =============================================================================*/

#include "ee_compiler_cfg.h"

/*==============================================================================
                              Compiler Abstraction
 =============================================================================*/

#if (!defined(AUTOMATIC))
/** \brief  Used for the declaration of stack allocated variables
            [SWS_COMPILER_00046] */
#define AUTOMATIC
#endif /* !AUTOMATIC */

#if (!defined(TYPEDEF))
/** \brief Shall be used within type definitions, where no memory qualifier can
    be specified. This can be necessary for defining pointer types, with e.g.
    P2VAR, where the macros require two parameters.
    First parameter can be specified in the type definition
    (distance to the memory location referenced by the pointer), but
    the second one (memory allocation of the pointer itself) cannot be defined
    at this time. Hence, memory class TYPEDEF shall be applied.
    [SWS_COMPILER_00059] */
#define TYPEDEF
#endif /* !TYPEDEF */

#if (!defined(NULL_PTR))
/** \brief Null void pointer [SWS_COMPILER_00051] */
#define NULL_PTR  ((void *)0)
#endif /* !NULL_PTR */

#if (!defined(INLINE))
/** \brief Define compiler abstraction for keyword (c99) inline
           [SWS_COMPILER_00057] */
#define INLINE       OSEE_INLINE
#endif /* !INLINE */

#if (!defined(LOCAL_INLINE))
/** \brief define for abstraction of the keyword inline in functions with
          "static" scope. [SWS_COMPILER_00060] */
#define LOCAL_INLINE  OSEE_STATIC_INLINE
#endif /* !LOCAL_INLINE */

/*==============================================================================
  Default implementation of types and function declaration and definition macros
  This implementation follow the hypothesis that any compiler extension were
  'left' associatiave as all the standard C keywords.
 =============================================================================*/

#if (!defined(VAR))
/** \brief  Macro for the declaration and definition of variables
    \param  vartype   type of the variable
    \param  memclass  classification of the variable itself
 */
#define VAR(vartype, memclass) vartype memclass
#endif /* !VAR */

#if (!defined(CONST))
/** \brief  Macro for the declaration and definition of constants
            [SWS_COMPILER_00023]
    \param  type      type of the constant
    \param  memclass  classification of the constant itself
 */
#define CONST(consttype, memclass) consttype const memclass
#endif /* !CONST */

#if (!defined(P2VAR))
/** \brief  Macro for the declaration and definition of pointers in RAM,
            pointing to variables. [SWS_COMPILER_00006]
    \param  ptrtype   type of the referenced variable memclass
    \param  memclass  classification of the pointer's variable itself
    \param  ptrclass  defines the classification of the pointer's distance */
# define P2VAR(ptrtype, memclass, ptrclass) ptrtype memclass * ptrclass
#endif /* !P2VAR */

#if (!defined(P2CONST))
/** \brief  Macro for the declaration and definition of pointers in RAM pointing
            to constants. [SWS_COMPILER_00013]
    \param  ptrtype   type of the referenced data
    \param  memclass  classification of the pointer's variable itself
    \param  ptrclass  defines the classification of the pointer's distance
 */
#define P2CONST(ptrtype, memclass, ptrclass) ptrtype const memclass * ptrclass
#endif /* !P2CONST */

#if (!defined(CONSTP2VAR))
/** \brief  Macro for the declaration and definition of constant pointers
            accessing variables. [SWS_COMPILER_00031]
    \param  ptrtype   type of the referenced data
    \param  memclass  classification of the pointer's variable itself
    \param  ptrclass  defines the classification of the pointer's distance
 */
#define CONSTP2VAR(ptrtype, memclass, ptrclass)\
  ptrtype memclass * const ptrclass
#endif /* !CONSTP2VAR */

#if (!defined(CONSTP2CONST))
/** \brief  Macro for the declaration and definition of constant pointers
            accessing constants. [SWS_COMPILER_00032]
    \param  ptrtype   type of the referenced data
    \param  memclass  classification of the pointer's variable itself
    \param  ptrclass  defines the classification of the pointer's distance
 */
#define CONSTP2CONST(ptrtype, memclass, ptrclass)\
  ptrtype const memclass *  const ptrclass
#endif /* !CONSTP2CONST */

#if (!defined(P2FUNC))
/** \brief  Macro for the type definition of pointers to functions
            [SWS_COMPILER_00039]
    \param  rettype   return type of the function
    \param  ptrclass  defines the classification of the pointer's distance
    \param  fctname   function name respectivly name of the defined type
 */
#define P2FUNC(rettype, ptrclass, fctname) rettype (* ptrclass fctname)
#endif /* !P2FUNC */

#if (!defined(FUNC))
/** \brief  Macro for the declaration and definition of functions that ensures
            correct syntax of function declarations as required by a specific
            compiler. [SWS_COMPILER_00001]
    \param  rettype   return type of the function
    \param  memclass  classification of the function itself */
#define FUNC(rettype, memclass) rettype memclass
#endif /* !FUNC */

#if (!defined(FUNC_P2VAR))
/** \brief  Macro for the declaration and definition of functions returning a
            pointer to a variable, that ensures correct syntax of function
            declarations. [SWS_COMPILER_00063]
    \param  rettype   return type of the function
    \param  ptrclass  defines the classification of the pointe' distance 
    \param  memclass  classification of the function itself */
#define FUNC_P2VAR(rettype, ptrclass, memclass) rettype * ptrclass memclass
#endif /* !FUNC_P2VAR */

#if (!defined(FUNC_P2CONST))
/** \brief  Macro for the declaration and definition of functions returning a
            pointer to a constant. This shall ensure the correct syntax of
            function declarations as required by a specific compiler
            [SWS_COMPILER_00061].
    \param  rettype   return type of the function
    \param  ptrclass  defines the classification of the pointer's distance 
    \param  memclass  classification of the function itself */
#define FUNC_P2CONST(rettype, ptrclass, memclass) \
  rettype const * ptrclass memclass
#endif /* !FUNC_P2CONST */

/*==============================================================================
  Following Compiler Abstraction Macros are Not AUTOSAR standard but are needed
  in ERIKA's implementation.
 =============================================================================*/

#if (!defined(P2SYM_VAR))
/** \brief  Macro for the type definition of pointers to symbols
            (array or function)

    \param  type      type of the function return or type for the array
    \param  ptrclass  defines the classification of the pointer's distance
    \param  symname   function or array pointer name
                      respectivly name of the defined type
 */
#define P2SYM_VAR(type, ptrclass, ptrname)\
  type (* ptrclass ptrname)

#endif /* !P2SYM_VAR */

#if (!defined(P2SYM_P2VAR))
/** \brief  Macro for the type definition of pointers to symbols
            (array or function) with pointer (return) type

    \param  type      type of the function return or type for the array
    \param  ptrclass  defines the classification of the pointer's distance
    \param  symname   function or array pointer name
                      respectivly name of the defined type
 */
#define P2SYM_P2VAR(type, ptrclass, ptrname)\
  type * (* ptrclass ptrname)
#endif /* !P2SYM_P2VAR */

#if (!defined(P2SYM_CONSTP2VAR))
/** \brief  Macro for the type definition of pointers to symbols
            (array or function) with const pointer (return) type

    \param  type      type of the function return or type for the array
    \param  ptrclass  defines the classification of the pointer's distance
    \param  symname   function or array pointer name
                      respectivly name of the defined type
 */
#define P2SYM_CONSTP2VAR(type, ptrclass, ptrname)\
  type * const (* ptrclass ptrname)
#endif /* !P2SYM_CONSTP2VAR */

#endif /* !OSEE_COMPILER_H */
