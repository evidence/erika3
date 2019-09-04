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
 *
 * This file derives from a modification of the Infineon startup scripts,
 * distributed under the following license:
 *
 * \file IfxCpu_Cstart0.c
 * \brief This file contains the Core startup sequence for Cpu0.
 * \version iLLD_1_0_1_3_0
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */


/** \file   ee_tc_cstart.c
 *  \brief  Start-up sequence, to be used in Erika's
 *          standalone configuration (no iLLD integration)
 *  \author Errico Guidieri
 *  \date   2017
 */

#include "ee_internal.h"
#include <stdlib.h>

/******************************************************************************
                          Default Caches policies
 *****************************************************************************/
#if (!defined(OSEE_TC_DCACHE_ENABLED))
#define OSEE_TC_DCACHE_ENABLED OSEE_TRUE
#endif /* OSEE_TC_DCACHE_ENABLED */

#if (!defined(OSEE_TC_PCACHE_ENABLED))
#define OSEE_TC_PCACHE_ENABLED OSEE_TRUE
#endif /* OSEE_TC_PCACHE_ENABLED */

/******************************************************************************
                           Compilers support 
 *****************************************************************************/

#if (defined(__TASKING__))
/* The following prevent that the compiler do not inline some calls */
#pragma optimize 3

#pragma weak   exit
#pragma extern _Exit
/* prevent profiling information on cstart */
#pragma profiling off
/* preset tradeoff level (for size) */
#pragma tradeoff 4
/* disable runtime error checking for cstart */
#pragma runtime BCM
/* disable MISRA-C checking */
#pragma nomisrac
/* bss clearing not before cinit */
#pragma noclear
/* no external ROM access before bus configuration */
#pragma immediate_in_code

#if (defined(OSEE_TC_CLONE_OS))
/* Disable code cloning for startup code */
#pragma code_core_association default
#endif /* OSEE_TC_CLONE_OS */

/* linker definitions */
/* user stack end */
#define __USTACK0       _lc_ue_ustack_tc0
#define __USTACK1       _lc_ue_ustack_tc1
#define __USTACK2       _lc_ue_ustack_tc2
#define __USTACK3       _lc_ue_ustack_tc3
#define __USTACK4       _lc_ue_ustack_tc4
#define __USTACK6       _lc_ue_ustack_tc5
/* user stack end */
#define __ISTACK0       _lc_ue_istack_tc0
#define __ISTACK1       _lc_ue_istack_tc1
#define __ISTACK2       _lc_ue_istack_tc2
#define __ISTACK3       _lc_ue_istack_tc3
#define __ISTACK4       _lc_ue_istack_tc4
#define __ISTACK6       _lc_ue_istack_tc5
/* trap table */
#define __TRAPTAB0      _lc_u_trap_tab_tc0
#define __TRAPTAB1      _lc_u_trap_tab_tc1
#define __TRAPTAB2      _lc_u_trap_tab_tc2
#define __TRAPTAB3      _lc_u_trap_tab_tc3
#define __TRAPTAB4      _lc_u_trap_tab_tc4
#define __TRAPTAB6      _lc_u_trap_tab_tc5
/* interrupt table */
#define __INTTAB0       _lc_u_int_tab_tc0
#define __INTTAB1       _lc_u_int_tab_tc1
#define __INTTAB2       _lc_u_int_tab_tc2
#define __INTTAB3       _lc_u_int_tab_tc3
#define __INTTAB4       _lc_u_int_tab_tc4
#define __INTTAB6       _lc_u_int_tab_tc5

/* _SMALL_DATA_ centre of A0 addressable area is equal to Hightec GCC */
/* centre of A1 addressable area */
#define _SMALL_DATA2_   _LITERAL_DATA_
/* centre of A8 addressable area */
#define _SMALL_DATA3_   _A8_DATA_
/* centre of A9 addressable area */
#define _SMALL_DATA4_   _A9_DATA_

/* context save areas begin */
#define __CSA0          _lc_ub_csa_tc0
#define __CSA1          _lc_ub_csa_tc1
#define __CSA2          _lc_ub_csa_tc2
#define __CSA3          _lc_ub_csa_tc3
#define __CSA4          _lc_ub_csa_tc4
#define __CSA6          _lc_ub_csa_tc5

/* context save areas end */
#define __CSA0_END      _lc_ue_csa_tc0
#define __CSA1_END      _lc_ue_csa_tc1
#define __CSA2_END      _lc_ue_csa_tc2
#define __CSA3_END      _lc_ue_csa_tc3
#define __CSA4_END      _lc_ue_csa_tc4
#define __CSA6_END      _lc_ue_csa_tc5

/* Start symbol for TASKING linker scripts */
#define _start    _START

/* libc exit function remapping  */
#define OSEE_EXIT exit
#define OSEE_FAR  __far

/* C initialization function for TASKING is inside libc */
#define osEE_tc_C_init _c_init
/* C initialization function declaration */
extern void _c_init(void);
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
extern void _c_init_tc1(void);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
extern void _c_init_tc2(void);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
extern void _c_init_tc3(void);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
extern void _c_init_tc4(void);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */
/* Numeric ID 5 is took by HSM core, how lame :(. */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
extern void _c_init_tc5(void);
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */


#elif defined (__GNUC__)
/* The following prevent that the compiler do not inline some calls */
#pragma GCC optimize ("-O3")

extern void _exit (int status);
/* libc exit function remapping  */
#define OSEE_EXIT _exit
/* GNUC meaningless function or data keyword */
#define OSEE_FAR

/* Actually we use only one interrupt vector with GCC */
#define __TRAPTAB0 __TRAPTAB
#define __TRAPTAB1 __TRAPTAB
#define __TRAPTAB2 __TRAPTAB
#define __TRAPTAB3 __TRAPTAB
#define __TRAPTAB4 __TRAPTAB
#define __TRAPTAB6 __TRAPTAB
#endif

/******************************************************************************
                          main function declaration
 *****************************************************************************/
#if 1
extern int main(void);
#else
extern int main(int argc, char *argv[]);
#endif

/******************************************************************************
                        Start-up Functions Declarations
 *****************************************************************************/
void _start(void);
void osEE_tc_core0_start(void);

#if (defined(__GNUC__))
/******************************************************************************
                      C initialization Functions Declarations
 *****************************************************************************/
typedef union
{
  uint8_t   * p_uc;
  uint16_t  * p_us;
  uint32_t  * p_ui;
  uint64_t  * p_ull;
} OsEE_tc_init_table_entry_ptr;

typedef struct
{
  OsEE_tc_init_table_entry_ptr  block_to_clear;
  uint32_t                      table_entry_length;
} OsEE_tc_clear_table;

typedef struct
{
  OsEE_tc_init_table_entry_ptr  block_src;
  OsEE_tc_init_table_entry_ptr  block_dest;
  uint32_t                      table_entry_length;
} OsEE_tc_copy_table;

static void osEE_tc_apply_clear_table
(
    const OsEE_tc_clear_table * p_clear_table_param
)
{
  const OsEE_tc_clear_table * p_clear_table = p_clear_table_param;
  while (p_clear_table != NULL) {
    OsEE_tc_init_table_entry_ptr  block_to_clear;
    MemSize                       table_entry_length;

/* Get pointer to the block to be cleared */
    block_to_clear = p_clear_table->block_to_clear;

/* Get the lenght of the table entry (in bytes) */
    table_entry_length = p_clear_table->table_entry_length;
    
/* We have finished when length == -1 */
    if (table_entry_length != 0xFFFFFFFFU) {
/* Prepare to clear as much unsigned long long as you can... */
      MemSize ull_cnt = table_entry_length / sizeof(uint64_t);

      while (ull_cnt != 0U) {
        *block_to_clear.p_ull = 0ULL;
        ++block_to_clear.p_ull;
        --ull_cnt;
      }

/*  Clear the remaning bytes */
      if (((table_entry_length) & 0x4U) != 0U) {
        *block_to_clear.p_ui = 0x0U;
        ++block_to_clear.p_ui;
      }

      if (((table_entry_length) & 0x2U) != 0U) {
        *block_to_clear.p_us = 0x0U;
        ++block_to_clear.p_us;
      }

      if (((table_entry_length) & 0x1U) != 0U) {
        *block_to_clear.p_uc = 0x0U;
      }

/* Prepare the table pointer for the next iteration */
      ++p_clear_table;
    } else {
/* Set out condition */
      p_clear_table = NULL;
    }
  }
}

static void osEE_tc_apply_copy_table
(
  const OsEE_tc_copy_table * p_copy_table_param
)
{
  const OsEE_tc_copy_table * p_copy_table = p_copy_table_param;
  while (p_copy_table != NULL) {
    OsEE_tc_init_table_entry_ptr  block_src;
    OsEE_tc_init_table_entry_ptr  block_dest;
    MemSize                       table_entry_length;

/* Get pointer to the data source block */
    block_src = p_copy_table->block_src;

/* Get pointer to the data destination block */
    block_dest = p_copy_table->block_dest;

/* Get the lenght of the table entry (in bytes) */
    table_entry_length = p_copy_table->table_entry_length;
    
/* We have finished when length == -1 */
    if (table_entry_length != 0xFFFFFFFFU) {
/* Prepare to copy as much unsigned long long as you can... */
      MemSize ull_cnt = table_entry_length / sizeof(uint64_t);

      while (ull_cnt != 0U) {
        *block_dest.p_ull = *block_src.p_ull;
        ++block_src.p_ull;
        ++block_dest.p_ull;
        --ull_cnt;
      }

/* Copy the remaning bytes */
      if (((table_entry_length) & 0x4U) != 0U) {
        *block_dest.p_ui = *block_src.p_ui;
        ++block_src.p_ui;
        ++block_dest.p_ui;
      }

      if (((table_entry_length) & 0x2U) != 0U) {
        *block_dest.p_us = *block_src.p_us;
        ++block_src.p_us;
        ++block_dest.p_us;
      }

      if (((table_entry_length) & 0x1U) != 0U) {
        *block_dest.p_uc = *block_src.p_uc;
      }

/* Prepare the table pointer for the next iteration */
      ++p_copy_table;
    } else {
/* Set out condition */
      p_copy_table = NULL;
    }
  }
}

static void osEE_tc_C_init(void) {
/* Clear Table */
  extern OsEE_tc_clear_table __clear_table[];
/* Copy Table */
  extern OsEE_tc_copy_table __copy_table[];

  osEE_tc_apply_clear_table(__clear_table);
  osEE_tc_apply_copy_table(__copy_table);
}

#endif /* __GNUC__ */
/******************************************************************************
                             Boot Mode Headers
 *****************************************************************************/
#if (!defined(OSEE_TC_2G)) && (defined(OSEE_TC_LINK_BMHD))
/* Boot Mode Header 0 sections to inform linker to locate them at 0x80000000 */
#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd0" a
#endif
#if defined(__TASKING__)
#pragma protect on
#pragma section farrom "bmhd0"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd0" R
#endif
/** \brief Boot Mode Header 0
 * Boot mode header at memory location 0c8000 0000.
 */
const uint32_t osEE_tc_bmhd_0[] = {
    0x00000000u,                 /* STADBM first user code at 0x8000 0020h */
    0xb3590070u,                 /* BMI = 0070h BMHDID = B359h */
    0x00000000u,                 /* ChkStart */
    0x00000000u,                 /* ChkEnd */
    0x00000000u,                 /* CRCrange */
    0x00000000u,                 /* !CRCrange */
    0x791eb864u,                 /* CRChead */
    0x86e1479bu                  /* !CRChead */
};

/* Reset the sections defined above */
#if defined(__GNUC__)
#pragma section
#endif
#if defined(__TASKING__)
#pragma protect restore
#pragma section farrom restore
#endif
#if defined(__DCC__)
#pragma section CONST
#endif

/* Boot Mode Header 1 sections to inform linker to locate them at 0x8002 0000 */
#if defined(__GNUC__)
#pragma section
#pragma section ".bmhd1" a
#endif
#if defined(__TASKING__)
#pragma protect on
#pragma section farrom "bmhd1"
#endif
#if defined(__DCC__)
#pragma section CONST ".bmhd1" R
#endif

/** \brief Boot Mode Header 1
 * Boot mode header at memory location 0c8002 0000.
 */
const uint32_t osEE_tc_bmhd_1[] = {
    0x00000000U,                 /* STADBM first user code at 0x8000 0020h */
    0xB3590070U,                 /* BMI = 0070h BMHDID = B359h */
    0x00000000U,                 /* ChkStart */
    0x00000000U,                 /* ChkEnd */
    0x00000000U,                 /* CRCrange */
    0x00000000U,                 /* !CRCrange */
    0x791eb864U,                 /* CRChead */
    0x86e1479bU                  /* !CRChead */
};

/* Reset the sections defined above */
#if defined(__GNUC__)
#pragma section
#endif
#if defined(__TASKING__)
#pragma protect restore
#pragma section farrom restore
#endif
#if defined(__DCC__)
#pragma section CONST
#endif
#endif /* !OSEE_TC_2G  && OSEE_TC_LINK_BMHD */

#if (defined(__GNUC__))
/******************************************************************************
                  Derivative Check + Turn-Off Frame pointer
 *****************************************************************************/
/* Define the Derivate Name as a hexvalue. This value
 * is an Hightec GCC built-in (e.g. TC27x => 0x2700)
 * This name will be used in the Memory description of linker script to
 * to confirm that we are linking with a correct script.
 */
__asm__ (
"\t.global __TRICORE_DERIVATE_NAME__\n"
"\t.type __TRICORE_DERIVATE_NAME__,@object\n"
"\t.set __TRICORE_DERIVATE_NAME__," OSEE_S(__TRICORE_NAME__) "\n"
);

/* The following guarantee that the -fomit-frame-pointer switch is enabled,
   preventing thet the compiler to mess up with the stack, not yet set at the
   start-up */
#pragma GCC optimize ("-O2")
#endif

/******************************************************************************
  Reset vector address, user section to inform linker to locate the code at
  0x8000 0020
 *****************************************************************************/
#if defined(__GNUC__)
#pragma section
#pragma section ".startup" x
#endif
#if defined(__TASKING__)
#pragma protect on
#pragma section code "startup"
#endif
#if defined(__DCC__)
#pragma section CODE ".startup" X
#endif

void _start(void)
{
  /* asm instruction to jump to the core startup */
  osEE_tc_jump_abs(osEE_tc_core0_start);
}

/******************************************************************************
                          Constant Definitions
 ******************************************************************************/
#define OSEE_TC_START_PSW          (0x00000B80U)

#if 0
#define OSEE_TC_START_PSW_ISP      (0x00000980U)
#endif

/* reset the sections defined above, to normal region */
#if defined(__GNUC__)
#pragma section
#endif
#if defined(__TASKING__)
#pragma protect restore
#pragma section code restore
#endif
#if defined(__DCC__)
#pragma section CODE
#endif

/* Linker script defined symbols */
extern OSEE_FAR OsEE_stack __USTACK0[];
extern OSEE_FAR OsEE_stack __ISTACK0[];

extern void __TRAPTAB0(void);
extern void __INTTAB0(void);

extern OSEE_FAR uint8_t _SMALL_DATA_[];
extern OSEE_FAR uint8_t _SMALL_DATA2_[];
extern OSEE_FAR uint8_t _SMALL_DATA3_[];
extern OSEE_FAR uint8_t _SMALL_DATA4_[];

extern OSEE_FAR OsEE_csa __CSA0[];
extern OSEE_FAR OsEE_csa __CSA0_END[];

void osEE_tc_core0_start(void)
{
  OsEE_reg       pcxi;
  uint16_t const cpu_wdt_pw     = osEE_tc_get_cpu_wdt_pw(0U);
  uint16_t const safety_wdt_pw  = osEE_tc_get_safety_wdt_pw();

/* Load User stack pointer */
  osEE_set_SP(__USTACK0);

/* Do a dsync before changing any of the CSFR values, thus any previous
 * background state gets flushed first.
 * Required for applications that jump to the reset address.
 */
  osEE_tc_dsync();

/* Set the PSW to its reset value in case of a warm start, set PSW.IS.
   Global Stack is needed since ERIKA's use the stack to save context for the
   current TASK */
  osEE_tc_set_csfr(OSEE_CSFR_PSW, OSEE_TC_START_PSW);

/* Set the PCXS and PCXO to its reset value in case of a warm start */
  pcxi  = osEE_tc_get_csfr(OSEE_CSFR_PCXI);
  pcxi &= 0xFFF00000U;
  osEE_tc_set_csfr(OSEE_CSFR_PCXI, pcxi);

/* Clear the ENDINIT bit in the WDT_CON0 register */
  osEE_tc_clear_cpu_endinit(0U, cpu_wdt_pw);

/* TODO: Enable/Disable program cache depending on the configuration */
  osEE_tc_set_pcache_wo_endinit(OSEE_TC_PCACHE_ENABLED);

/* TODO: Enable/Disable data cache depending on the configuration */
  osEE_tc_set_dcache_wo_endinit(OSEE_TC_DCACHE_ENABLED);

/* Load Base Address of Trap Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BTV, (OsEE_reg)__TRAPTAB0);

/* Load Base Address of Interrupt Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BIV, (OsEE_reg)__INTTAB0);

/* Load Interrupt Stack Pointer. (Not Used) */
  osEE_tc_set_csfr(OSEE_CSFR_ISP, (OsEE_reg)__ISTACK0);

/* Set the ENDINIT bit in the WDT_CON0 register back */
  osEE_tc_set_cpu_endinit(0U, cpu_wdt_pw);

/* Initialize SDA base pointers */
  osEE_tc_setareg(a0, _SMALL_DATA_);
  osEE_tc_setareg(a1, _SMALL_DATA2_);

/* Initialization of A8 and A9 */
  osEE_tc_setareg(a8, _SMALL_DATA3_);
#if (defined(OSEE_SINGLECORE)) || (defined(OSEE_TC_DISABLE_A9_OPTIMIZATION))
  osEE_tc_setareg(a9, _SMALL_DATA4_);
#else
  osEE_tc_setareg(a9, &osEE_cdb_var_core0);
#endif /* OSEE_SINGLECORE || OSEE_TC_DISABLE_A9_OPTIMIZATION */

/* Setup the context save area linked list for CPU0 */
  osEE_tc_csa_init_inline(__CSA0, __CSA0_END);

/* CPU and safety watchdogs are enabled by default. Disable them here to be
   re-enabled by ERIKA or by the Application */
  osEE_tc_disable_cpu_wdt(0U, cpu_wdt_pw);
  osEE_tc_disable_safety_wdt(safety_wdt_pw);

/* C initialization routine */
  osEE_tc_C_init();

/* Moved PLL configuration here from osEE_cpu_startos, since TriCore AURIX
   environment trying to access to SCU_PLL registers, at the same time that
   another core try to set ENDINIT password on it's own SCU_CPU_WDT
   is a TRAP BUS peripheral fault. */
#if (!defined(OSEE_TRICORE_ILLD)) && (!defined(OSEE_TC_2G))
#if (!defined(OSEE_BYPASS_CLOCK_CONFIGURATION))
/* If a CPU CLOCK frequency is defined configure the SCU registers */
#if (defined(OSEE_CPU_CLOCK))
/* Disable SAFETY ENDINIT Protection */
  osEE_tc_clear_safety_endinit(safety_wdt_pw);
/*===================== Configure CCU Clock Control =========================*/
  osEE_tc_conf_clock_ctrl();
/*===================== Configure Oscillator Control ========================*/
  osEE_tc_conf_osc_ctrl();
/*============================ Configure PLL ================================*/
  osEE_tc_set_pll_fsource(OSEE_CPU_CLOCK);
/* Re-enable SAFETY ENDINIT Protection */
  osEE_tc_set_safety_endinit(safety_wdt_pw);
#endif /* OSEE_CPU_CLOCK */
#endif /* !OSEE_BYPASS_CLOCK_CONFIGURATION */
#endif /* !OSEE_TRICORE_ILLD && !OSEE_TC_2G */

  OSEE_EXIT(main());
}

#if (!defined(OSEE_SINGLECORE))
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
/* Linker script defined symbols */
extern OSEE_FAR OsEE_stack __USTACK1[];
extern OSEE_FAR OsEE_stack __ISTACK1[];

extern void __TRAPTAB1(void);
extern void __INTTAB1(void);

extern OSEE_FAR OsEE_csa __CSA1[];
extern OSEE_FAR OsEE_csa __CSA1_END[];

void osEE_tc_core1_start(void)
{
  OsEE_reg       pcxi;
  uint16_t const cpu_wdt_pw     = osEE_tc_get_cpu_wdt_pw(1U);

/* Load User stack pointer */
  osEE_set_SP(__USTACK1);

/* Do a dsync before changing any of the CSFR values, thus any previous
 * background state gets flushed first.
 * Required for applications that jump to the reset address.
 */
  osEE_tc_dsync();

/* Set the PSW to its reset value in case of a warm start, set PSW.IS.
   Global Stack is needed since ERIKA's use the stack to save context for the
   current TASK */
  osEE_tc_set_csfr(OSEE_CSFR_PSW, OSEE_TC_START_PSW);

/* Set the PCXS and PCXO to its reset value in case of a warm start */
  pcxi  = osEE_tc_get_csfr(OSEE_CSFR_PCXI);
  pcxi &= 0xFFF00000U;
  osEE_tc_set_csfr(OSEE_CSFR_PCXI, pcxi);

/* Clear the ENDINIT bit in the WDT_CON0 register */
  osEE_tc_clear_cpu_endinit(1U, cpu_wdt_pw);

/* TODO: Enable/Disable program cache depending on the configuration */
  osEE_tc_set_pcache_wo_endinit(OSEE_TC_PCACHE_ENABLED);

/* TODO: Enable/Disable data cache depending on the configuration */
  osEE_tc_set_dcache_wo_endinit(OSEE_TC_DCACHE_ENABLED);

/* Load Base Address of Trap Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BTV, (OsEE_reg)__TRAPTAB1);

/* Load Base Address of Interrupt Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BIV, (OsEE_reg)__INTTAB1);

/* Load Interrupt Stack Pointer. (Not Used) */
  osEE_tc_set_csfr(OSEE_CSFR_ISP, (OsEE_reg)__ISTACK1);

/* Set the ENDINIT bit in the WDT_CON0 register back */
  osEE_tc_set_cpu_endinit(1U, cpu_wdt_pw);

/* Initialize SDA base pointers */
  osEE_tc_setareg(a0, _SMALL_DATA_);
  osEE_tc_setareg(a1, _SMALL_DATA2_);

/* Initialization of A8 and A9 */
  osEE_tc_setareg(a8, _SMALL_DATA3_);
#if (defined(OSEE_TC_DISABLE_A9_OPTIMIZATION))
  osEE_tc_setareg(a9, _SMALL_DATA4_);
#else
  osEE_tc_setareg(a9, &osEE_cdb_var_core1);
#endif /* OSEE_TC_DISABLE_A9_OPTIMIZATION */

/* Setup the context save area linked list for CPU0 */
  osEE_tc_csa_init_inline(__CSA1, __CSA1_END);

/* CPU watchdogs are enabled by default. Disable the core1 one here to be
   re-enabled by ERIKA or by the Application */
  osEE_tc_disable_cpu_wdt(1U, cpu_wdt_pw);

#if (defined(__TASKING__))
/* C core 1 private initialization */
  _c_init_tc1();
#endif /* __TASKING__ */

/* Call main function */
  (void)main();

/* TODO: handle main return */
  for (;;) {
    ;
  }
}
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
/* Linker script defined symbols */
extern OSEE_FAR OsEE_stack __USTACK2[];
extern OSEE_FAR OsEE_stack __ISTACK2[];

extern void __TRAPTAB2(void);
extern void __INTTAB2(void);

extern OSEE_FAR OsEE_csa __CSA2[];
extern OSEE_FAR OsEE_csa __CSA2_END[];

void osEE_tc_core2_start(void)
{
  OsEE_reg       pcxi;
  uint16_t const cpu_wdt_pw     = osEE_tc_get_cpu_wdt_pw(2U);

/* Load User stack pointer */
  osEE_set_SP(__USTACK2);

/* Do a dsync before changing any of the CSFR values, thus any previous
 * background state gets flushed first.
 * Required for applications that jump to the reset address.
 */
  osEE_tc_dsync();

/* Set the PSW to its reset value in case of a warm start, set PSW.IS.
   Global Stack is needed since ERIKA's use the stack to save context for the
   current TASK */
  osEE_tc_set_csfr(OSEE_CSFR_PSW, OSEE_TC_START_PSW);

/* Set the PCXS and PCXO to its reset value in case of a warm start */
  pcxi  = osEE_tc_get_csfr(OSEE_CSFR_PCXI);
  pcxi &= 0xFFF00000U;
  osEE_tc_set_csfr(OSEE_CSFR_PCXI, pcxi);

/* Clear the ENDINIT bit in the WDT_CON0 register */
  osEE_tc_clear_cpu_endinit(2U, cpu_wdt_pw);

/* TODO: Enable/Disable program cache depending on the configuration */
  osEE_tc_set_pcache_wo_endinit(OSEE_TC_PCACHE_ENABLED);

/* TODO: Enable/Disable data cache depending on the configuration */
  osEE_tc_set_dcache_wo_endinit(OSEE_TC_DCACHE_ENABLED);

/* Load Base Address of Trap Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BTV, (OsEE_reg)__TRAPTAB2);

/* Load Base Address of Interrupt Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BIV, (OsEE_reg)__INTTAB2);

/* Load Interrupt Stack Pointer. (Not Used) */
  osEE_tc_set_csfr(OSEE_CSFR_ISP, (OsEE_reg)__ISTACK2);

/* Set the ENDINIT bit in the WDT_CON0 register back */
  osEE_tc_set_cpu_endinit(2U, cpu_wdt_pw);

/* Initialize SDA base pointers */
  osEE_tc_setareg(a0, _SMALL_DATA_);
  osEE_tc_setareg(a1, _SMALL_DATA2_);

/* Initialization of A8 and A9 */
  osEE_tc_setareg(a8, _SMALL_DATA3_);
#if (defined(OSEE_TC_DISABLE_A9_OPTIMIZATION))
  osEE_tc_setareg(a9, _SMALL_DATA4_);
#else
  osEE_tc_setareg(a9, &osEE_cdb_var_core2);
#endif /* OSEE_TC_DISABLE_A9_OPTIMIZATION */

/* Setup the context save area linked list for CPU0 */
  osEE_tc_csa_init_inline(__CSA2, __CSA2_END);

/* CPU watchdogs are enabled by default. Disable the core2 one here to be
   re-enabled by ERIKA or by the Application */
  osEE_tc_disable_cpu_wdt(2U, cpu_wdt_pw);

#if (defined(__TASKING__))
/* C core 2 private initialization */
  _c_init_tc2();
#endif /* __TASKING__ */

/* Call main function */
  (void)main();
  
/* TODO: handle main return */
  for (;;) {
    ;
  }
}

#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
/* Linker script defined symbols */
extern OSEE_FAR OsEE_stack __USTACK3[];
extern OSEE_FAR OsEE_stack __ISTACK3[];

extern void __TRAPTAB3(void);
extern void __INTTAB3(void);

extern OSEE_FAR OsEE_csa __CSA3[];
extern OSEE_FAR OsEE_csa __CSA3_END[];

void osEE_tc_core3_start(void)
{
  OsEE_reg       pcxi;
  uint16_t const cpu_wdt_pw     = osEE_tc_get_cpu_wdt_pw(3U);

/* Load User stack pointer */
  osEE_set_SP(__USTACK3);

/* Do a dsync before changing any of the CSFR values, thus any previous
 * background state gets flushed first.
 * Required for applications that jump to the reset address.
 */
  osEE_tc_dsync();

/* Set the PSW to its reset value in case of a warm start, set PSW.IS.
   Global Stack is needed since ERIKA's use the stack to save context for the
   current TASK */
  osEE_tc_set_csfr(OSEE_CSFR_PSW, OSEE_TC_START_PSW);

/* Set the PCXS and PCXO to its reset value in case of a warm start */
  pcxi  = osEE_tc_get_csfr(OSEE_CSFR_PCXI);
  pcxi &= 0xFFF00000U;
  osEE_tc_set_csfr(OSEE_CSFR_PCXI, pcxi);

/* Clear the ENDINIT bit in the WDT_CON0 register */
  osEE_tc_clear_cpu_endinit(3U, cpu_wdt_pw);

/* TODO: Enable/Disable program cache depending on the configuration */
  osEE_tc_set_pcache_wo_endinit(OSEE_TC_PCACHE_ENABLED);

/* TODO: Enable/Disable data cache depending on the configuration */
  osEE_tc_set_dcache_wo_endinit(OSEE_TC_DCACHE_ENABLED);

/* Load Base Address of Trap Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BTV, (OsEE_reg)__TRAPTAB3);

/* Load Base Address of Interrupt Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BIV, (OsEE_reg)__INTTAB3);

/* Load Interrupt Stack Pointer. (Not Used) */
  osEE_tc_set_csfr(OSEE_CSFR_ISP, (OsEE_reg)__ISTACK3);

/* Set the ENDINIT bit in the WDT_CON0 register back */
  osEE_tc_set_cpu_endinit(3U, cpu_wdt_pw);

/* Initialize SDA base pointers */
  osEE_tc_setareg(a0, _SMALL_DATA_);
  osEE_tc_setareg(a1, _SMALL_DATA2_);

/* Initialization of A8 and A9 */
  osEE_tc_setareg(a8, _SMALL_DATA3_);
#if (defined(OSEE_TC_DISABLE_A9_OPTIMIZATION))
  osEE_tc_setareg(a9, _SMALL_DATA4_);
#else
  osEE_tc_setareg(a9, &osEE_cdb_var_core3);
#endif /* OSEE_TC_DISABLE_A9_OPTIMIZATION */

/* Setup the context save area linked list for CPU0 */
  osEE_tc_csa_init_inline(__CSA3, __CSA3_END);

/* CPU watchdogs are enabled by default. Disable the core3 one here to be
   re-enabled by ERIKA or by the Application */
  osEE_tc_disable_cpu_wdt(3U, cpu_wdt_pw);

#if (defined(__TASKING__))
/* C core 3 private initialization */
  _c_init_tc3();
#endif /* __TASKING__ */

/* Call main function */
  (void)main();
  
/* TODO: handle main return */
  for (;;) {
    ;
  }
}
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
/* Linker script defined symbols */
extern OSEE_FAR OsEE_stack __USTACK4[];
extern OSEE_FAR OsEE_stack __ISTACK4[];

extern void __TRAPTAB4(void);
extern void __INTTAB4(void);

extern OSEE_FAR OsEE_csa __CSA4[];
extern OSEE_FAR OsEE_csa __CSA4_END[];

void osEE_tc_core4_start(void)
{
  OsEE_reg       pcxi;
  uint16_t const cpu_wdt_pw     = osEE_tc_get_cpu_wdt_pw(4U);

/* Load User stack pointer */
  osEE_set_SP(__USTACK4);

/* Do a dsync before changing any of the CSFR values, thus any previous
 * background state gets flushed first.
 * Required for applications that jump to the reset address.
 */
  osEE_tc_dsync();

/* Set the PSW to its reset value in case of a warm start, set PSW.IS.
   Global Stack is needed since ERIKA's use the stack to save context for the
   current TASK */
  osEE_tc_set_csfr(OSEE_CSFR_PSW, OSEE_TC_START_PSW);

/* Set the PCXS and PCXO to its reset value in case of a warm start */
  pcxi  = osEE_tc_get_csfr(OSEE_CSFR_PCXI);
  pcxi &= 0xFFF00000U;
  osEE_tc_set_csfr(OSEE_CSFR_PCXI, pcxi);

/* Clear the ENDINIT bit in the WDT_CON0 register */
  osEE_tc_clear_cpu_endinit(4U, cpu_wdt_pw);

/* TODO: Enable/Disable program cache depending on the configuration */
  osEE_tc_set_pcache_wo_endinit(OSEE_TC_PCACHE_ENABLED);

/* TODO: Enable/Disable data cache depending on the configuration */
  osEE_tc_set_dcache_wo_endinit(OSEE_TC_DCACHE_ENABLED);

/* Load Base Address of Trap Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BTV, (OsEE_reg)__TRAPTAB4);

/* Load Base Address of Interrupt Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BIV, (OsEE_reg)__INTTAB4);

/* Load Interrupt Stack Pointer. (Not Used) */
  osEE_tc_set_csfr(OSEE_CSFR_ISP, (OsEE_reg)__ISTACK4);

/* Set the ENDINIT bit in the WDT_CON0 register back */
  osEE_tc_set_cpu_endinit(4U, cpu_wdt_pw);

/* Initialize SDA base pointers */
  osEE_tc_setareg(a0, _SMALL_DATA_);
  osEE_tc_setareg(a1, _SMALL_DATA2_);

/* Initialization of A8 and A9 */
  osEE_tc_setareg(a8, _SMALL_DATA3_);
#if (defined(OSEE_TC_DISABLE_A9_OPTIMIZATION))
  osEE_tc_setareg(a9, _SMALL_DATA4_);
#else
  osEE_tc_setareg(a9, &osEE_cdb_var_core4);
#endif /* OSEE_TC_DISABLE_A9_OPTIMIZATION */

/* Setup the context save area linked list for CPU0 */
  osEE_tc_csa_init_inline(__CSA4, __CSA4_END);

/* CPU watchdogs are enabled by default. Disable the core4 one here to be
   re-enabled by ERIKA or by the Application */
  osEE_tc_disable_cpu_wdt(4U, cpu_wdt_pw);

#if (defined(__TASKING__))
/* C core 4 private initialization */
  _c_init_tc4();
#endif /* __TASKING__ */

/* Call main function */
  (void)main();
  
/* TODO: handle main return */
  for (;;) {
    ;
  }
}
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
/* Linker script defined symbols */
extern OSEE_FAR OsEE_stack __USTACK6[];
extern OSEE_FAR OsEE_stack __ISTACK6[];

extern void __TRAPTAB6(void);
extern void __INTTAB6(void);

extern OSEE_FAR OsEE_csa __CSA6[];
extern OSEE_FAR OsEE_csa __CSA6_END[];

void osEE_tc_core6_start(void)
{
  OsEE_reg       pcxi;
  uint16_t const cpu_wdt_pw     = osEE_tc_get_cpu_wdt_pw(5U);

/* Load User stack pointer */
  osEE_set_SP(__USTACK6);

/* Do a dsync before changing any of the CSFR values, thus any previous
 * background state gets flushed first.
 * Required for applications that jump to the reset address.
 */
  osEE_tc_dsync();

/* Set the PSW to its reset value in case of a warm start, set PSW.IS.
   Global Stack is needed since ERIKA's use the stack to save context for the
   current TASK */
  osEE_tc_set_csfr(OSEE_CSFR_PSW, OSEE_TC_START_PSW);

/* Set the PCXS and PCXO to its reset value in case of a warm start */
  pcxi  = osEE_tc_get_csfr(OSEE_CSFR_PCXI);
  pcxi &= 0xFFF00000U;
  osEE_tc_set_csfr(OSEE_CSFR_PCXI, pcxi);

/* Clear the ENDINIT bit in the WDT_CON0 register */
  osEE_tc_clear_cpu_endinit(5U, cpu_wdt_pw);

/* TODO: Enable/Disable program cache depending on the configuration */
  osEE_tc_set_pcache_wo_endinit(OSEE_TC_PCACHE_ENABLED);

/* TODO: Enable/Disable data cache depending on the configuration */
  osEE_tc_set_dcache_wo_endinit(OSEE_TC_DCACHE_ENABLED);

/* Load Base Address of Trap Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BTV, (OsEE_reg)__TRAPTAB6);

/* Load Base Address of Interrupt Vector Table. */
  osEE_tc_set_csfr(OSEE_CSFR_BIV, (OsEE_reg)__INTTAB6);

/* Load Interrupt Stack Pointer. (Not Used) */
  osEE_tc_set_csfr(OSEE_CSFR_ISP, (OsEE_reg)__ISTACK6);

/* Set the ENDINIT bit in the WDT_CON0 register back */
  osEE_tc_set_cpu_endinit(5U, cpu_wdt_pw);

/* Initialize SDA base pointers */
  osEE_tc_setareg(a0, _SMALL_DATA_);
  osEE_tc_setareg(a1, _SMALL_DATA2_);

/* Initialization of A8 and A9 */
  osEE_tc_setareg(a8, _SMALL_DATA3_);
#if (defined(OSEE_TC_DISABLE_A9_OPTIMIZATION))
  osEE_tc_setareg(a9, _SMALL_DATA4_);
#else
  osEE_tc_setareg(a9, &osEE_cdb_var_core6);
#endif /* OSEE_TC_DISABLE_A9_OPTIMIZATION */

/* Setup the context save area linked list for CPU0 */
  osEE_tc_csa_init_inline(__CSA6, __CSA6_END);

/* CPU watchdogs are enabled by default. Disable the core5 one here to be
   re-enabled by ERIKA or by the Application */
  osEE_tc_disable_cpu_wdt(5U, cpu_wdt_pw);

#if (defined(__TASKING__))
/* C core 6 private initialization */
  _c_init_tc5();
#endif /* __TASKING__ */

/* Call main function */
  (void)main();
  
/* TODO: handle main return */
  for (;;) {
    ;
  }
}
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */
#endif /* !OSEE_SINGLECORE */

#if defined(__GNUC__)
#pragma GCC reset_options
#endif
