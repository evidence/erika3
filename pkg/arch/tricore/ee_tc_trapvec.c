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
 
 /**
    \file   ee_tc_trapvec.c
    \brief  TriCore trap handlers vector implementation.
    \author Errico Guidieri
    \date   2017
  */
#include "ee_internal.h"

#if (defined(__TASKING__))

#include <stdlib.h>

#if (defined(OSEE_TC_CLONE_OS))
/* Disable code cloning for trap vector */
#pragma code_core_association default
#endif /* OSEE_TC_CLONE_OS */

#if (defined(OSEE_TC_TURN_ON_TRAP_WORKAROUND))
#define OSEE_TC_TRAP_WORKAROUND() __disable()
#else
#define OSEE_TC_TRAP_WORKAROUND() ((void)0)
#endif /* OSEE_TC_TURN_ON_TRAP_WORKAROUND */

#ifdef OSEE_DEBUG
/* halt execution if debug mode enabled */
/* Disable dead assignment warning in this case for this module (tin value) */
#pragma warning 588
#define OSEE_TC_DEFAULT_TRAP_HANDLER(class_trap, trap_number)\
  do {                  \
    (void)trap_number;  \
    osEE_tc_debug();    \
  } while(1)
#else 
/* libc support needed for default handler */
#pragma weak exit
#pragma extern _Exit

/* or exit if debug mode is disabled */
#define OSEE_TC_DEFAULT_TRAP_HANDLER(class_trap, trap_number)\
  exit(class_trap << 4U | trap_number)
#endif /* OSEE_DEBUG */

#if (defined(OSEE_TC_TRAP_MMU_TRAP))
extern void OSEE_TC_TRAP_MMU_TRAP(OsEE_tc_tin   tin);
#endif /* OSEE_TC_TRAP_MMU_TRAP */
#if (defined(OSEE_TC_TRAP_PROT_TRAP))
extern void OSEE_TC_TRAP_PROT_TRAP(OsEE_tc_tin  tin);
#endif /* OSEE_TC_TRAP_PROT_TRAP */
#if (defined(OSEE_TC_TRAP_INST_TRAP))
extern void OSEE_TC_TRAP_INST_TRAP(OsEE_tc_tin  tin);
#endif /* OSEE_TC_TRAP_INST_TRAP */
#if (defined(OSEE_TC_TRAP_CONT_TRAP))
extern void OSEE_TC_TRAP_CONT_TRAP(OsEE_tc_tin  tin);
#endif /* OSEE_TC_TRAP_CONT_TRAP */
#if (defined(OSEE_TC_TRAP_BUS_TRAP))
extern void OSEE_TC_TRAP_BUS_TRAP(OsEE_tc_tin   tin);
#endif /* OSEE_TC_TRAP_BUS_TRAP */
#if (defined(OSEE_TC_TRAP_ASS_TRAP))
extern void OSEE_TC_TRAP_ASS_TRAP(OsEE_tc_tin   tin);
#endif /* OSEE_TC_TRAP_ASS_TRAP */
#if (defined(OSEE_TC_TRAP_SYS_TRAP))
extern void OSEE_TC_TRAP_SYS_TRAP(OsEE_tc_tin   tin);
#endif /* OSEE_TC_TRAP_SYS_TRAP */

extern void osEE_tc_default_trap_handler(OsEE_tc_tin tin);
#if (defined(OSEE_MEMORY_PROTECTION)) && (defined(OSEE_USE_MMU))
extern void osEE_tc_mmu_handler(OsEE_tc_tin tin);
#endif /* OSEE_MEMORY_PROTECTION && OSEE_USE_MMU */
#if (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
extern void osEE_tc_protection_handler(OsEE_tc_tin tin);
#endif /* OSEE_MEMORY_PROTECTION || OSEE_TIMING_PROTECTION */
#if (defined(OSEE_TIMING_PROTECTION))
extern void osEE_tc_bus_handler(OsEE_tc_tin tin);
#endif /* OSEE_TIMING_PROTECTION */

#if (defined(OSEE_TC_TURN_ON_TRAP_WORKAROUND))
#define OSEE_TC_TRAP_WORKAROUND_STR "disable"
#else
#define OSEE_TC_TRAP_WORKAROUND_STR ""
#endif /* OSEE_TC_TURN_ON_TRAP_WORKAROUND */

#if (defined(OSEE_SINGLECORE))
/**
  Skeleton for MMU trap handler (Trap Class 0).
 */
OSEE_TRAP(OSEE_CLASS_TRAPMMU, osEE_tc_trap_mmu)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION)) && (defined(OSEE_USE_MMU))
  osEE_tc_mmu_handler(tin);
#elif (defined(OSEE_TC_TRAP_MMU_TRAP))
  OSEE_TC_TRAP_MMU_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPMMU, tin);
#endif /* OSEE_TC_TRAP_MMU_TRAP */
}

/**
  Skeleton for PROTECTION trap handler (Trap Class 1).
 */
OSEE_TRAP(OSEE_CLASS_TRAPPROT, osEE_tc_trap_protection)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_protection_handler(tin);
#elif (defined(OSEE_TC_TRAP_PROT_TRAP))
  OSEE_TC_TRAP_PROT_TRAP(tin);
#elif defined(OSEE_TIMING_PROTECTION)
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPPROT, tin);
#endif /* OSEE_TC_TRAP_PROT_TRAP */
}

/**
  Skeleton for INSTRUCTION trap handler (Trap Class 2).
 */
OSEE_TRAP(OSEE_CLASS_TRAPINST, osEE_tc_trap_instruction)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_INST_TRAP))
  OSEE_TC_TRAP_INST_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPINST, tin);
#endif /* OSEE_TC_TRAP_INST_TRAP */
}

/** 
  Skeleton for CONTEXT trap handler (Trap Class 3).
 */
OSEE_TRAP(OSEE_CLASS_TRAPCONT, osEE_tc_trap_context)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_CONT_TRAP)
  OSEE_TC_TRAP_CONT_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPCONT, tin);
#endif /* OSEE_TC_TRAP_CONT_TRAP */
}

/**
  Skeleton for BUS trap handler (Trap Class 4).
 */

OSEE_TRAP(OSEE_CLASS_TRAPBUS, osEE_tc_trap_bus)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_bus_handler(tin);
#elif (defined(OSEE_TC_TRAP_BUS_TRAP))
  OSEE_TC_TRAP_BUS_TRAP(tin)
#elif (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_default_trap_handler(tin)
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPBUS, tin);
#endif /* OSEE_TC_TRAP_BUS_TRAP */
}

/**
  Skeleton for ASSERTION trap handler (Trap Class 5).
 */
OSEE_TRAP(OSEE_CLASS_TRAPASS, osEE_tc_trap_assertion)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_ASS_TRAP)
  OSEE_TC_TRAP_ASS_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPASS, tin);
#endif /* OSEE_TC_TRAP_ASS_TRAP */
}

/**
  Skeleton for SYSTEM trap handler (Trapp Class 6).
  TIN Name Sync/Async  H/S      Description
  n   SYS  Synchronous Software System call
  (n=8-bit unsigned immediate constant int the SYSCALL instruction) *
 */
OSEE_TRAP(OSEE_CLASS_TRAPSYS, osEE_tc_trap_system)
{
#if (defined(OSEE_MEMORY_PROTECTION))
__asm("                                     \n\
  "OSEE_TC_TRAP_WORKAROUND_STR"             \n\
  mfcr %d12, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  svlcx                                     \n\
  mfcr %d13, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  j osEE_tc_syscall_handler                 \n\
");
#else
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_SYS_TRAP))
  OSEE_TC_TRAP_SYS_TRAP(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPSYS, tin);
#endif /* OSEE_TC_TRAP_SYS_TRAP */
#endif /* OSEE_MEMORY_PROTECTION*/
}

/**
  Skeleton for NMI trap handler (Trap Class 7).
 */
OSEE_TRAP(OSEE_CLASS_TRAPNMI, osEE_tc_trap_nmi)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_NMI_TRAP))
  OSEE_TC_TRAP_NMI_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPNMI, tin);
#endif /* OSEE_TC_TRAP_NMI_TRAP */
}

#else
/**
  Skeleton for MMU trap handler (Trap Class 0).
 */
OSEE_TRAP(OSEE_CLASS_TRAPMMU, 0, osEE_tc_trap_mmu)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION)) && (defined(OSEE_USE_MMU))
  osEE_tc_mmu_handler(tin);
#elif (defined(OSEE_TC_TRAP_MMU_TRAP))
  OSEE_TC_TRAP_MMU_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPMMU, tin);
#endif /* OSEE_TC_TRAP_MMU_TRAP */
}

/**
  Skeleton for PROTECTION trap handler (Trap Class 1).
 */
OSEE_TRAP(OSEE_CLASS_TRAPPROT, 0, osEE_tc_trap_protection)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_protection_handler(tin);
#elif (defined(OSEE_TC_TRAP_PROT_TRAP))
  OSEE_TC_TRAP_PROT_TRAP(tin);
#elif defined(OSEE_TIMING_PROTECTION)
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPPROT, tin);
#endif /* OSEE_TC_TRAP_PROT_TRAP */
}

/**
  Skeleton for INSTRUCTION trap handler (Trap Class 2).
 */
OSEE_TRAP(OSEE_CLASS_TRAPINST, 0, osEE_tc_trap_instruction)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_INST_TRAP))
  OSEE_TC_TRAP_INST_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPINST, tin);
#endif /* OSEE_TC_TRAP_INST_TRAP */
}

/** 
  Skeleton for CONTEXT trap handler (Trap Class 3).
 */
OSEE_TRAP(OSEE_CLASS_TRAPCONT, 0, osEE_tc_trap_context)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_CONT_TRAP)
  OSEE_TC_TRAP_CONT_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPCONT, tin);
#endif /* OSEE_TC_TRAP_CONT_TRAP */
}

/**
  Skeleton for BUS trap handler (Trap Class 4).
 */

OSEE_TRAP(OSEE_CLASS_TRAPBUS, 0, osEE_tc_trap_bus)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_bus_handler(tin);
#elif (defined(OSEE_TC_TRAP_BUS_TRAP))
  OSEE_TC_TRAP_BUS_TRAP(tin)
#elif (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_default_trap_handler(tin)
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPBUS, tin);
#endif /* OSEE_TC_TRAP_BUS_TRAP */
}

/**
  Skeleton for ASSERTION trap handler (Trap Class 5).
 */
OSEE_TRAP(OSEE_CLASS_TRAPASS, 0, osEE_tc_trap_assertion)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_ASS_TRAP)
  OSEE_TC_TRAP_ASS_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPASS, tin);
#endif /* OSEE_TC_TRAP_ASS_TRAP */
}

/**
  Skeleton for SYSTEM trap handler (Trapp Class 6).
  TIN Name Sync/Async  H/S      Description
  n   SYS  Synchronous Software System call
  (n=8-bit unsigned immediate constant int the SYSCALL instruction) *
 */
OSEE_TRAP(OSEE_CLASS_TRAPSYS, 0, osEE_tc_trap_system)
{
#if (defined(OSEE_MEMORY_PROTECTION))
__asm("                                     \n\
  "OSEE_TC_TRAP_WORKAROUND_STR"             \n\
  mfcr %d12, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  svlcx                                     \n\
  mfcr %d13, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  j osEE_tc_syscall_handler                 \n\
");
#else
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_SYS_TRAP))
  OSEE_TC_TRAP_SYS_TRAP(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPSYS, tin);
#endif /* OSEE_TC_TRAP_SYS_TRAP */
#endif /* OSEE_MEMORY_PROTECTION*/
}

/**
  Skeleton for NMI trap handler (Trap Class 7).
 */
OSEE_TRAP(OSEE_CLASS_TRAPNMI, 0, osEE_tc_trap_nmi)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_NMI_TRAP))
  OSEE_TC_TRAP_NMI_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPNMI, tin);
#endif /* OSEE_TC_TRAP_NMI_TRAP */
}

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
/**
  Skeleton for MMU trap handler (Trap Class 0).
 */
OSEE_TRAP(OSEE_CLASS_TRAPMMU, 1, osEE_tc_trap_mmu)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION)) && (defined(OSEE_USE_MMU))
  osEE_tc_mmu_handler(tin);
#elif (defined(OSEE_TC_TRAP_MMU_TRAP))
  OSEE_TC_TRAP_MMU_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPMMU, tin);
#endif /* OSEE_TC_TRAP_MMU_TRAP */
}

/**
  Skeleton for PROTECTION trap handler (Trap Class 1).
 */
OSEE_TRAP(OSEE_CLASS_TRAPPROT, 1, osEE_tc_trap_protection)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_protection_handler(tin);
#elif (defined(OSEE_TC_TRAP_PROT_TRAP))
  OSEE_TC_TRAP_PROT_TRAP(tin);
#elif defined(OSEE_TIMING_PROTECTION)
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPPROT, tin);
#endif /* OSEE_TC_TRAP_PROT_TRAP */
}

/**
  Skeleton for INSTRUCTION trap handler (Trap Class 2).
 */
OSEE_TRAP(OSEE_CLASS_TRAPINST, 1, osEE_tc_trap_instruction)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_INST_TRAP))
  OSEE_TC_TRAP_INST_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPINST, tin);
#endif /* OSEE_TC_TRAP_INST_TRAP */
}

/** 
  Skeleton for CONTEXT trap handler (Trap Class 3).
 */
OSEE_TRAP(OSEE_CLASS_TRAPCONT, 1, osEE_tc_trap_context)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_CONT_TRAP)
  OSEE_TC_TRAP_CONT_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPCONT, tin);
#endif /* OSEE_TC_TRAP_CONT_TRAP */
}

/**
  Skeleton for BUS trap handler (Trap Class 4).
 */

OSEE_TRAP(OSEE_CLASS_TRAPBUS, 1, osEE_tc_trap_bus)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_bus_handler(tin);
#elif (defined(OSEE_TC_TRAP_BUS_TRAP))
  OSEE_TC_TRAP_BUS_TRAP(tin)
#elif (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_default_trap_handler(tin)
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPBUS, tin);
#endif /* OSEE_TC_TRAP_BUS_TRAP */
}

/**
  Skeleton for ASSERTION trap handler (Trap Class 5).
 */
OSEE_TRAP(OSEE_CLASS_TRAPASS, 1, osEE_tc_trap_assertion)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_ASS_TRAP)
  OSEE_TC_TRAP_ASS_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPASS, tin);
#endif /* OSEE_TC_TRAP_ASS_TRAP */
}

/**
  Skeleton for SYSTEM trap handler (Trapp Class 6).
  TIN Name Sync/Async  H/S      Description
  n   SYS  Synchronous Software System call
  (n=8-bit unsigned immediate constant int the SYSCALL instruction) *
 */
OSEE_TRAP(OSEE_CLASS_TRAPSYS, 1, osEE_tc_trap_system)
{
#if (defined(OSEE_MEMORY_PROTECTION))
__asm("                                     \n\
  "OSEE_TC_TRAP_WORKAROUND_STR"             \n\
  mfcr %d12, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  svlcx                                     \n\
  mfcr %d13, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  j osEE_tc_syscall_handler                 \n\
");
#else
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_SYS_TRAP))
  OSEE_TC_TRAP_SYS_TRAP(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPSYS, tin);
#endif /* OSEE_TC_TRAP_SYS_TRAP */
#endif /* OSEE_MEMORY_PROTECTION*/
}

/**
  Skeleton for NMI trap handler (Trap Class 7).
 */
OSEE_TRAP(OSEE_CLASS_TRAPNMI, 1, osEE_tc_trap_nmi)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_NMI_TRAP))
  OSEE_TC_TRAP_NMI_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPNMI, tin);
#endif /* OSEE_TC_TRAP_NMI_TRAP */
}

#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
/**
  Skeleton for MMU trap handler (Trap Class 0).
 */
OSEE_TRAP(OSEE_CLASS_TRAPMMU, 2, osEE_tc_trap_mmu)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION)) && (defined(OSEE_USE_MMU))
  osEE_tc_mmu_handler(tin);
#elif (defined(OSEE_TC_TRAP_MMU_TRAP))
  OSEE_TC_TRAP_MMU_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPMMU, tin);
#endif /* OSEE_TC_TRAP_MMU_TRAP */
}

/**
  Skeleton for PROTECTION trap handler (Trap Class 1).
 */
OSEE_TRAP(OSEE_CLASS_TRAPPROT, 2, osEE_tc_trap_protection)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_protection_handler(tin);
#elif (defined(OSEE_TC_TRAP_PROT_TRAP))
  OSEE_TC_TRAP_PROT_TRAP(tin);
#elif defined(OSEE_TIMING_PROTECTION)
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPPROT, tin);
#endif /* OSEE_TC_TRAP_PROT_TRAP */
}

/**
  Skeleton for INSTRUCTION trap handler (Trap Class 2).
 */
OSEE_TRAP(OSEE_CLASS_TRAPINST, 2, osEE_tc_trap_instruction)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_INST_TRAP))
  OSEE_TC_TRAP_INST_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPINST, tin);
#endif /* OSEE_TC_TRAP_INST_TRAP */
}

/** 
  Skeleton for CONTEXT trap handler (Trap Class 3).
 */
OSEE_TRAP(OSEE_CLASS_TRAPCONT, 2, osEE_tc_trap_context)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_CONT_TRAP)
  OSEE_TC_TRAP_CONT_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPCONT, tin);
#endif /* OSEE_TC_TRAP_CONT_TRAP */
}

/**
  Skeleton for BUS trap handler (Trap Class 4).
 */

OSEE_TRAP(OSEE_CLASS_TRAPBUS, 2, osEE_tc_trap_bus)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_bus_handler(tin);
#elif (defined(OSEE_TC_TRAP_BUS_TRAP))
  OSEE_TC_TRAP_BUS_TRAP(tin)
#elif (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_default_trap_handler(tin)
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPBUS, tin);
#endif /* OSEE_TC_TRAP_BUS_TRAP */
}

/**
  Skeleton for ASSERTION trap handler (Trap Class 5).
 */
OSEE_TRAP(OSEE_CLASS_TRAPASS, 2, osEE_tc_trap_assertion)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_ASS_TRAP)
  OSEE_TC_TRAP_ASS_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPASS, tin);
#endif /* OSEE_TC_TRAP_ASS_TRAP */
}

/**
  Skeleton for SYSTEM trap handler (Trapp Class 6).
  TIN Name Sync/Async  H/S      Description
  n   SYS  Synchronous Software System call
  (n=8-bit unsigned immediate constant int the SYSCALL instruction) *
 */
OSEE_TRAP(OSEE_CLASS_TRAPSYS, 2, osEE_tc_trap_system)
{
#if (defined(OSEE_MEMORY_PROTECTION))
__asm("                                     \n\
  "OSEE_TC_TRAP_WORKAROUND_STR"             \n\
  mfcr %d12, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  svlcx                                     \n\
  mfcr %d13, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  j osEE_tc_syscall_handler                 \n\
");
#else
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_SYS_TRAP))
  OSEE_TC_TRAP_SYS_TRAP(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPSYS, tin);
#endif /* OSEE_TC_TRAP_SYS_TRAP */
#endif /* OSEE_MEMORY_PROTECTION*/
}

/**
  Skeleton for NMI trap handler (Trap Class 7).
 */
OSEE_TRAP(OSEE_CLASS_TRAPNMI, 2, osEE_tc_trap_nmi)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_NMI_TRAP))
  OSEE_TC_TRAP_NMI_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPNMI, tin);
#endif /* OSEE_TC_TRAP_NMI_TRAP */
}

#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
/**
  Skeleton for MMU trap handler (Trap Class 0).
 */
OSEE_TRAP(OSEE_CLASS_TRAPMMU, 3, osEE_tc_trap_mmu)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION)) && (defined(OSEE_USE_MMU))
  osEE_tc_mmu_handler(tin);
#elif (defined(OSEE_TC_TRAP_MMU_TRAP))
  OSEE_TC_TRAP_MMU_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPMMU, tin);
#endif /* OSEE_TC_TRAP_MMU_TRAP */
}

/**
  Skeleton for PROTECTION trap handler (Trap Class 1).
 */
OSEE_TRAP(OSEE_CLASS_TRAPPROT, 3, osEE_tc_trap_protection)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_protection_handler(tin);
#elif (defined(OSEE_TC_TRAP_PROT_TRAP))
  OSEE_TC_TRAP_PROT_TRAP(tin);
#elif defined(OSEE_TIMING_PROTECTION)
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPPROT, tin);
#endif /* OSEE_TC_TRAP_PROT_TRAP */
}

/**
  Skeleton for INSTRUCTION trap handler (Trap Class 2).
 */
OSEE_TRAP(OSEE_CLASS_TRAPINST, 3, osEE_tc_trap_instruction)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_INST_TRAP))
  OSEE_TC_TRAP_INST_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPINST, tin);
#endif /* OSEE_TC_TRAP_INST_TRAP */
}

/** 
  Skeleton for CONTEXT trap handler (Trap Class 3).
 */
OSEE_TRAP(OSEE_CLASS_TRAPCONT, 3, osEE_tc_trap_context)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_CONT_TRAP)
  OSEE_TC_TRAP_CONT_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPCONT, tin);
#endif /* OSEE_TC_TRAP_CONT_TRAP */
}

/**
  Skeleton for BUS trap handler (Trap Class 4).
 */

OSEE_TRAP(OSEE_CLASS_TRAPBUS, 3, osEE_tc_trap_bus)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_bus_handler(tin);
#elif (defined(OSEE_TC_TRAP_BUS_TRAP))
  OSEE_TC_TRAP_BUS_TRAP(tin)
#elif (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_default_trap_handler(tin)
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPBUS, tin);
#endif /* OSEE_TC_TRAP_BUS_TRAP */
}

/**
  Skeleton for ASSERTION trap handler (Trap Class 5).
 */
OSEE_TRAP(OSEE_CLASS_TRAPASS, 3, osEE_tc_trap_assertion)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_ASS_TRAP)
  OSEE_TC_TRAP_ASS_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPASS, tin);
#endif /* OSEE_TC_TRAP_ASS_TRAP */
}

/**
  Skeleton for SYSTEM trap handler (Trapp Class 6).
  TIN Name Sync/Async  H/S      Description
  n   SYS  Synchronous Software System call
  (n=8-bit unsigned immediate constant int the SYSCALL instruction) *
 */
OSEE_TRAP(OSEE_CLASS_TRAPSYS, 3, osEE_tc_trap_system)
{
#if (defined(OSEE_MEMORY_PROTECTION))
__asm("                                     \n\
  "OSEE_TC_TRAP_WORKAROUND_STR"             \n\
  mfcr %d12, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  svlcx                                     \n\
  mfcr %d13, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  j osEE_tc_syscall_handler                 \n\
");
#else
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_SYS_TRAP))
  OSEE_TC_TRAP_SYS_TRAP(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPSYS, tin);
#endif /* OSEE_TC_TRAP_SYS_TRAP */
#endif /* OSEE_MEMORY_PROTECTION*/
}

/**
  Skeleton for NMI trap handler (Trap Class 7).
 */
OSEE_TRAP(OSEE_CLASS_TRAPNMI, 3, osEE_tc_trap_nmi)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_NMI_TRAP))
  OSEE_TC_TRAP_NMI_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPNMI, tin);
#endif /* OSEE_TC_TRAP_NMI_TRAP */
}

#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
/**
  Skeleton for MMU trap handler (Trap Class 0).
 */
OSEE_TRAP(OSEE_CLASS_TRAPMMU, 4, osEE_tc_trap_mmu)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION)) && (defined(OSEE_USE_MMU))
  osEE_tc_mmu_handler(tin);
#elif (defined(OSEE_TC_TRAP_MMU_TRAP))
  OSEE_TC_TRAP_MMU_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPMMU, tin);
#endif /* OSEE_TC_TRAP_MMU_TRAP */
}

/**
  Skeleton for PROTECTION trap handler (Trap Class 1).
 */
OSEE_TRAP(OSEE_CLASS_TRAPPROT, 4, osEE_tc_trap_protection)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_protection_handler(tin);
#elif (defined(OSEE_TC_TRAP_PROT_TRAP))
  OSEE_TC_TRAP_PROT_TRAP(tin);
#elif defined(OSEE_TIMING_PROTECTION)
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPPROT, tin);
#endif /* OSEE_TC_TRAP_PROT_TRAP */
}

/**
  Skeleton for INSTRUCTION trap handler (Trap Class 2).
 */
OSEE_TRAP(OSEE_CLASS_TRAPINST, 4, osEE_tc_trap_instruction)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_INST_TRAP))
  OSEE_TC_TRAP_INST_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPINST, tin);
#endif /* OSEE_TC_TRAP_INST_TRAP */
}

/** 
  Skeleton for CONTEXT trap handler (Trap Class 3).
 */
OSEE_TRAP(OSEE_CLASS_TRAPCONT, 4, osEE_tc_trap_context)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_CONT_TRAP)
  OSEE_TC_TRAP_CONT_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPCONT, tin);
#endif /* OSEE_TC_TRAP_CONT_TRAP */
}

/**
  Skeleton for BUS trap handler (Trap Class 4).
 */

OSEE_TRAP(OSEE_CLASS_TRAPBUS, 4, osEE_tc_trap_bus)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_bus_handler(tin);
#elif (defined(OSEE_TC_TRAP_BUS_TRAP))
  OSEE_TC_TRAP_BUS_TRAP(tin)
#elif (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_default_trap_handler(tin)
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPBUS, tin);
#endif /* OSEE_TC_TRAP_BUS_TRAP */
}

/**
  Skeleton for ASSERTION trap handler (Trap Class 5).
 */
OSEE_TRAP(OSEE_CLASS_TRAPASS, 4, osEE_tc_trap_assertion)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_ASS_TRAP)
  OSEE_TC_TRAP_ASS_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPASS, tin);
#endif /* OSEE_TC_TRAP_ASS_TRAP */
}

/**
  Skeleton for SYSTEM trap handler (Trapp Class 6).
  TIN Name Sync/Async  H/S      Description
  n   SYS  Synchronous Software System call
  (n=8-bit unsigned immediate constant int the SYSCALL instruction) *
 */
OSEE_TRAP(OSEE_CLASS_TRAPSYS, 4, osEE_tc_trap_system)
{
#if (defined(OSEE_MEMORY_PROTECTION))
__asm("                                     \n\
  "OSEE_TC_TRAP_WORKAROUND_STR"             \n\
  mfcr %d12, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  svlcx                                     \n\
  mfcr %d13, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  j osEE_tc_syscall_handler                 \n\
");
#else
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_SYS_TRAP))
  OSEE_TC_TRAP_SYS_TRAP(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPSYS, tin);
#endif /* OSEE_TC_TRAP_SYS_TRAP */
#endif /* OSEE_MEMORY_PROTECTION*/
}

/**
  Skeleton for NMI trap handler (Trap Class 7).
 */
OSEE_TRAP(OSEE_CLASS_TRAPNMI, 4, osEE_tc_trap_nmi)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_NMI_TRAP))
  OSEE_TC_TRAP_NMI_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPNMI, tin);
#endif /* OSEE_TC_TRAP_NMI_TRAP */
}

#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
/**
  Skeleton for MMU trap handler (Trap Class 0).
 */
OSEE_TRAP(OSEE_CLASS_TRAPMMU, 5, osEE_tc_trap_mmu)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION)) && (defined(OSEE_USE_MMU))
  osEE_tc_mmu_handler(tin);
#elif (defined(OSEE_TC_TRAP_MMU_TRAP))
  OSEE_TC_TRAP_MMU_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPMMU, tin);
#endif /* OSEE_TC_TRAP_MMU_TRAP */
}

/**
  Skeleton for PROTECTION trap handler (Trap Class 1).
 */
OSEE_TRAP(OSEE_CLASS_TRAPPROT, 5, osEE_tc_trap_protection)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_protection_handler(tin);
#elif (defined(OSEE_TC_TRAP_PROT_TRAP))
  OSEE_TC_TRAP_PROT_TRAP(tin);
#elif defined(OSEE_TIMING_PROTECTION)
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPPROT, tin);
#endif /* OSEE_TC_TRAP_PROT_TRAP */
}

/**
  Skeleton for INSTRUCTION trap handler (Trap Class 2).
 */
OSEE_TRAP(OSEE_CLASS_TRAPINST, 5, osEE_tc_trap_instruction)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_INST_TRAP))
  OSEE_TC_TRAP_INST_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPINST, tin);
#endif /* OSEE_TC_TRAP_INST_TRAP */
}

/** 
  Skeleton for CONTEXT trap handler (Trap Class 3).
 */
OSEE_TRAP(OSEE_CLASS_TRAPCONT, 5, osEE_tc_trap_context)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_CONT_TRAP)
  OSEE_TC_TRAP_CONT_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPCONT, tin);
#endif /* OSEE_TC_TRAP_CONT_TRAP */
}

/**
  Skeleton for BUS trap handler (Trap Class 4).
 */

OSEE_TRAP(OSEE_CLASS_TRAPBUS, 5, osEE_tc_trap_bus)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_bus_handler(tin);
#elif (defined(OSEE_TC_TRAP_BUS_TRAP))
  OSEE_TC_TRAP_BUS_TRAP(tin)
#elif (defined(OSEE_MEMORY_PROTECTION))
  osEE_tc_default_trap_handler(tin)
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPBUS, tin);
#endif /* OSEE_TC_TRAP_BUS_TRAP */
}

/**
  Skeleton for ASSERTION trap handler (Trap Class 5).
 */
OSEE_TRAP(OSEE_CLASS_TRAPASS, 5, osEE_tc_trap_assertion)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if defined(OSEE_TC_TRAP_ASS_TRAP)
  OSEE_TC_TRAP_ASS_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPASS, tin);
#endif /* OSEE_TC_TRAP_ASS_TRAP */
}

/**
  Skeleton for SYSTEM trap handler (Trapp Class 6).
  TIN Name Sync/Async  H/S      Description
  n   SYS  Synchronous Software System call
  (n=8-bit unsigned immediate constant int the SYSCALL instruction) *
 */
OSEE_TRAP(OSEE_CLASS_TRAPSYS, 5, osEE_tc_trap_system)
{
#if (defined(OSEE_MEMORY_PROTECTION))
__asm("                                     \n\
  "OSEE_TC_TRAP_WORKAROUND_STR"             \n\
  mfcr %d12, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  svlcx                                     \n\
  mfcr %d13, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  j osEE_tc_syscall_handler                 \n\
");
#else
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_SYS_TRAP))
  OSEE_TC_TRAP_SYS_TRAP(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPSYS, tin);
#endif /* OSEE_TC_TRAP_SYS_TRAP */
#endif /* OSEE_MEMORY_PROTECTION*/
}

/**
  Skeleton for NMI trap handler (Trap Class 7).
 */
OSEE_TRAP(OSEE_CLASS_TRAPNMI, 5, osEE_tc_trap_nmi)
{
  OsEE_tc_tin tin;
  OSEE_TC_TRAP_WORKAROUND();
  tin = osEE_tc_get_tin();
#if (defined(OSEE_TC_TRAP_NMI_TRAP))
  OSEE_TC_TRAP_NMI_TRAP(tin);
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
  osEE_tc_default_trap_handler(tin);
#else
  OSEE_TC_DEFAULT_TRAP_HANDLER(OSEE_CLASS_TRAPNMI, tin);
#endif /* OSEE_TC_TRAP_NMI_TRAP */
}
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */
#endif /* OSEE_SINGLECORE */

#elif (defined(__GNUC__))
#if (defined(OSEE_TC_TURN_ON_TRAP_WORKAROUND))
#define OSEE_TC_TRAP_WORKAROUND() __asm__ ("disable")
#else
#define OSEE_TC_TRAP_WORKAROUND() __asm__ ("")
#endif /* OSEE_TC_TURN_ON_TRAP_WORKAROUND */

#define OSEE_TC_TRAP_DEFINITION2(t,h)       \
  __asm__ (".globl " OSEE_S(t));            \
  __asm__ (OSEE_S(t) ":");                  \
  OSEE_TC_TRAP_WORKAROUND();                \
  __asm__ ("svlcx");                        \
  __asm__ ("movh.a %a15,hi:" OSEE_S(h));    \
  __asm__ ("lea %a15,[%a15]lo:" OSEE_S(h)); \
  __asm__ ("mov %d4,%d15");                 \
  __asm__ ("ji %a15");                      \
  __asm__ (".align 5");

/* Two pre-processor steps to let macros expands */
#define OSEE_TC_TRAP_DEFINITION(t,h) OSEE_TC_TRAP_DEFINITION2(t,h)

#define OSEE_TC_TRAP_DEFINITION_WITH_CALL(t,h)  \
  __asm__ (".globl " OSEE_S(t));                \
  __asm__ (OSEE_S(t) ":");                      \
  OSEE_TC_TRAP_WORKAROUND();                    \
  __asm__ ("svlcx");                            \
  __asm__ ("movh.a %a15,hi:" OSEE_S(h));        \
  __asm__ ("lea %a15,[%a15]lo:" OSEE_S(h))      \
  __asm__ ("mov %d4,%d15");                     \
  __asm__ ("calli %a15");                       \
  __asm__ ("rslcx");                            \
  __asm__ ("rfe");                              \
  __asm__ (".align 5");

#if (defined(OSEE_DEBUG))
#define OSEE_TC_TRAP_DEFAULT(t)   \
  __asm__ (".globl " OSEE_S(t));  \
  __asm__ (OSEE_S(t) ":");        \
  OSEE_TC_TRAP_WORKAROUND();      \
  __asm__ ("debug");              \
  __asm__ ("j " OSEE_S(t));       \
  __asm__ (".align 5");
#else
#define OSEE_TC_TRAP_DEFAULT(t)   \
  __asm__ (".globl " OSEE_S(t));  \
  __asm__ (OSEE_S(t) ":");        \
  OSEE_TC_TRAP_WORKAROUND();      \
  __asm__ ("svlcx");              \
  __asm__ ("call _exit");         \
  __asm__ ("rslcx");              \
  __asm__ ("rfe");                \
  __asm__ (".align 5");
#endif /* OSEE_DEBUG */

__asm__ ("                                  \n\
  .section .traptab_cpu0, \"ax\", @progbits \n\
  .align 8                                  \n\
  .globl _exit                              \n\
  .globl __TRAPTAB                          \n\
__TRAPTAB:                                  \n\
");
#if (defined(OSEE_MEMORY_PROTECTION)) && (defined(OSEE_USE_MMU))
OSEE_TC_TRAP_DEFINITION(osEE_tc_trap_mmu, osEE_tc_mmu_handler)
#elif (defined(OSEE_TC_TRAP_MMU_TRAP))
OSEE_TC_TRAP_DEFINITION(osEE_tc_trap_mmu, OSEE_TC_TRAP_MMU_TRAP)
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
OSEE_TC_TRAP_DEFINITION_WITH_CALL(osEE_tc_trap_mmu,
  osEE_tc_default_trap_handler)
#else
OSEE_TC_TRAP_DEFAULT(osEE_tc_trap_mmu)
#endif /* OSEE_TC_TRAP_MMU_TRAP */

#if (defined(OSEE_MEMORY_PROTECTION))
OSEE_TC_TRAP_DEFINITION(osEE_tc_trap_protection, osEE_tc_protection_handler)
#elif (defined(OSEE_TC_TRAP_PROT_TRAP))
OSEE_TC_TRAP_DEFINITION(osEE_tc_trap_protection, OSEE_TC_TRAP_PROT_TRAP)
#elif (defined(OSEE_TIMING_PROTECTION))
OSEE_TC_TRAP_DEFINITION_WITH_CALL(osEE_tc_trap_protection,
  osEE_tc_default_trap_handler)
#else
OSEE_TC_TRAP_DEFAULT(osEE_tc_trap_protection)
#endif /* OSEE_TC_TRAP_PROT_TRAP */

#if (defined(OSEE_TC_TRAP_INST_TRAP))
OSEE_TC_TRAP_DEFINITION(osEE_tc_trap_instruction, OSEE_TC_TRAP_INST_TRAP)
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
OSEE_TC_TRAP_DEFINITION_WITH_CALL(osEE_tc_trap_instruction,
  osEE_tc_default_trap_handler)
#else
OSEE_TC_TRAP_DEFAULT(osEE_tc_trap_instruction)
#endif /* OSEE_TC_TRAP_INST_TRAP */

#if (defined(OSEE_TC_TRAP_CONT_TRAP))
OSEE_TC_TRAP_DEFINITION(osEE_tc_trap_context, OSEE_TC_TRAP_CONT_TRAP)
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
OSEE_TC_TRAP_DEFINITION_WITH_CALL(osEE_tc_trap_context,
  osEE_tc_default_trap_handler)
#else
OSEE_TC_TRAP_DEFAULT(osEE_tc_trap_context)
#endif /* OSEE_TC_TRAP_CONT_TRAP */

#if (defined(OSEE_TIMING_PROTECTION))
OSEE_TC_TRAP_DEFINITION(osEE_tc_trap_bus, osEE_tc_bus_handler)
#elif (defined(OSEE_TC_TRAP_BUS_TRAP))
OSEE_TC_TRAP_DEFINITION(osEE_tc_trap_bus, osEE_TC_TRAP_BUS_TRAP)
#elif (defined(OSEE_MEMORY_PROTECTION))
OSEE_TC_TRAP_DEFINITION_WITH_CALL(osEE_tc_trap_bus,
  osEE_tc_default_trap_handler)
#else
OSEE_TC_TRAP_DEFAULT(osEE_tc_trap_bus)
#endif /* OSEE_TC_TRAP_BUS_TRAP */

#if (defined(OSEE_TC_TRAP_ASS_TRAP))
OSEE_TC_TRAP_DEFINITION(EE_tc_trap_assertion, OSEE_TC_TRAP_ASS_TRAP)
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
OSEE_TC_TRAP_DEFINITION_WITH_CALL(osEE_tc_trap_assertion,
  osEE_tc_default_trap_handler)
#else
OSEE_TC_TRAP_DEFAULT(osEE_tc_trap_assertion)
#endif /* OSEE_TC_TRAP_ASS_TRAP */

#if (defined(OSEE_MEMORY_PROTECTION))
#if (defined(OSEE_TC_TURN_ON_TRAP_WORKAROUND))
#define OSEE_TC_TRAP_WORKAROUND_STR "disable"
#else
#define OSEE_TC_TRAP_WORKAROUND_STR ""
#endif /* OSEE_TC_TURN_ON_TRAP_WORKAROUND */
/* Generate the call to system call handler in case of memory protection
   active: Save in d12 and d13 two pcxi value for saved Upper/Lower Context
   respectively, used inside osEE_tc_syscall_handler for stack, ISR status
   restoring and for return value. */
__asm__ ("                                  \n\
  .globl osEE_tc_trap_system                \n\
osEE_tc_trap_system:                        \n\
  "OSEE_TC_TRAP_WORKAROUND_STR"             \n\
  mfcr %d12, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  svlcx                                     \n\
  mfcr %d13, " OSEE_S(OSEE_CSFR_PCXI) "     \n\
  j osEE_tc_syscall_handler                 \n\
  .align 5                                  \n\
");
#elif (defined(OSEE_TC_TRAP_SYS_TRAP))
OSEE_TC_TRAP_DEFINITION(osEE_tc_trap_system, OSEE_TC_TRAP_SYS_TRAP)
#elif (defined(OSEE_TIMING_PROTECTION))
OSEE_TC_TRAP_DEFINITION_WITH_CALL(osEE_tc_trap_system,
  osEE_tc_default_trap_handler)
#else
OSEE_TC_TRAP_DEFAULT(osEE_tc_trap_system)
#endif /* OSEE_TC_TRAP_SYS_TRAP */

#if (defined(OSEE_TC_TRAP_NMI_TRAP))
OSEE_TC_TRAP_DEFINITION(osEE_tc_trap_nmi, OSEE_TC_TRAP_NMI_TRAP)
#elif (defined(OSEE_MEMORY_PROTECTION)) || (defined(OSEE_TIMING_PROTECTION))
OSEE_TC_TRAP_DEFINITION_WITH_CALL(osEE_tc_trap_nmi,
  osEE_tc_default_trap_handler)
#else
OSEE_TC_TRAP_DEFAULT(osEE_tc_trap_nmi)
#endif /* OSEE_TC_TRAP_NMI_TRAP */
#endif /* __TASKING__ || __GNUC__ */

