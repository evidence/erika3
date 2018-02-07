/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2017 Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * See LICENSE file.
 * ###*E*### */

/** \file   ee_arch_compiler_gcc.h
 *  \brief  Common GCC Compilers Definitions.
 *
 *  This file contains all the common compiler-dependent architectural
 *  definitions for GNU GCC Compiler.
 *
 *  \note This file \b MUST contain only \c defines, because it is also
 *        included by the \c .S files. \n
 *
 *  \note   TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

/*
 * Compiler dependent interface
 */
#if (!defined(OSEE_ARCH_COMPILER_GCC_H))
#define OSEE_ARCH_COMPILER_GCC_H

#define OSEE_INIT       __attribute__((constructor))

#endif /* !OSEE_ARCH_COMPILER_GCC_H */
