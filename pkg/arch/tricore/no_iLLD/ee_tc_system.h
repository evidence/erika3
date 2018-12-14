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

/** \file   ee_tc_system.h
 *  \brief  PLL configuration and System Timer Implementation, to be used in
            Erika's standalone configuration (no iLLD integration)
 *  \author Errico Guidieri
 *  \date   2017
 */
#ifndef OSEE_TC_SYSTEM_H
#define OSEE_TC_SYSTEM_H

#include "ee_cfg.h"
#include "ee_utils.h"
#include "ee_platform_types.h"
#include "ee_hal.h"
#include "ee_tc_csfr.h"
#include "ee_hal_internal_types.h"
#include "ee_tc_src.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/*******************************************************************************
                            Frequencies References
 ******************************************************************************/
/* PLL Frequencies Bound Defines */
#define OSEE_TC_CLOCK_MIN           20000000U
#if (defined(OSEE_TC_TC29X))
#define OSEE_TC_CLOCK_MAX          300000000U /* 300Mhz for TC29x MCU */
#else
#define OSEE_TC_CLOCK_MAX          200000000U /* 200Mhz for other MCUs */
#endif

#if (!defined(OSEE_TC_BOARD_FOSC))
#define OSEE_TC_BOARD_FOSC 20000000U
#endif /* !OSEE_TC_BOARD_FOSC */

/* Configure EVR (backup clock) frequency */
#if (!defined(OSEE_TC_EVR_OSC_FREQUENCY))
#define OSEE_TC_EVR_OSC_FREQUENCY 100000000U
#endif /* !OSEE_TC_EVR_OSC_FREQUENCY */

#if (defined(OSEE_BYPASS_CLOCK_CONFIGURATION))
#if (!defined(OSEE_CPU_CLOCK))
#define OSEE_CPU_CLOCK  OSEE_TC_EVR_OSC_FREQUENCY
#endif /* !OSEE_CPU_CLOCK */
#else
#if (!defined(OSEE_CPU_CLOCK))
#define OSEE_CPU_CLOCK  OSEE_TC_CLOCK_MAX
#endif /* !OSEE_CPU_CLOCK */
#endif /* OSEE_BYPASS_CLOCK_CONFIGURATION */

/*******************************************************************************
                         Typedef for system support
 ******************************************************************************/

typedef uint8_t OsEE_tc_isr_hw_prio;

/*******************************************************************************
                              Ports Support
 ******************************************************************************/
/* Defines to populate Ports registers */
/*  Input - No input pull device connected, tri-state mode
    (same as 0x03U) */
#define OSEE_TC_INPUT_TRISTATE         0x00U
/*  Input - Pull-Down device connected */
#define OSEE_TC_INPUT_PULL_DOWN        0x01U
/*  Input - Pull-Up device connected. RESET Default */
#define OSEE_TC_INPUT_PULL_UP          0x02U

/*  Output - Push-pull General-purpose output */
#define OSEE_TC_OUTPUT_PUSH_PULL_GP    0x10U
/*  Output - Push-pull Alternate output function 1 */
#define OSEE_TC_OUTPUT_PUSH_PULL_ALT1  0x11U
/*  Output - Push-pull Alternate output function 2 */
#define OSEE_TC_OUTPUT_PUSH_PULL_ALT2  0x12U
/*  Output - Push-pull Alternate output function 3 */
#define OSEE_TC_OUTPUT_PUSH_PULL_ALT3  0x13U
/*  Output - Push-pull Alternate output function 4 */
#define OSEE_TC_OUTPUT_PUSH_PULL_ALT4  0x14U
/*  Output - Push-pull Alternate output function 5 */
#define OSEE_TC_OUTPUT_PUSH_PULL_ALT5  0x15U
/*  Output - Push-pull Alternate output function 6 */
#define OSEE_TC_OUTPUT_PUSH_PULL_ALT6  0x16U
/*  Output - Push-pull Alternate output function 7 */
#define OSEE_TC_OUTPUT_PUSH_PULL_ALT7  0x17U

/*  Output - Open-drain General-purpose output */
#define OSEE_TC_OUTPUT_OPEN_DRAIN_GP   0x24U
/*  Output - Open-drain Alternate output function 1 */
#define OSEE_TC_OUTPUT_OPEN_DRAIN_ALT1 0x25U
/*  Output - Open-drain Alternate output function 2 */
#define OSEE_TC_OUTPUT_OPEN_DRAIN_ALT2 0x26U
/*  Output - Open-drain Alternate output function 3 */
#define OSEE_TC_OUTPUT_OPEN_DRAIN_ALT3 0x27U
/*  Output - Open-drain Alternate output function 4 */
#define OSEE_TC_OUTPUT_OPEN_DRAIN_ALT4 0x28U
/*  Output - Open-drain Alternate output function 5 */
#define OSEE_TC_OUTPUT_OPEN_DRAIN_ALT5 0x29U
/*  Output - Open-drain Alternate output function 6 */
#define OSEE_TC_OUTPUT_OPEN_DRAIN_ALT6 0x30U
/*  Output - Open-drain Alternate output function 7 */
#define OSEE_TC_OUTPUT_OPEN_DRAIN_ALT7 0x31U

/******************************************************************************
                            SCU Watchdogs Handling
 *****************************************************************************/

/** \brief CPU WDT Control Register 0 */
typedef struct OsEE_tc_SCU_WDTCPU_CON0_bits_tag
{
/** \brief [0:0] End-of-Initialization Control Bit (rwh) */
  unsigned int endinit  : 1;
/** \brief [1:1] Lock Bit to Control Access to WDTxCON0 (rwh) */
  unsigned int lck      : 1;
/** \brief [15:2] User-Definable Password Field for Access to WDTxCON0 (rwh) */
  unsigned int pw       : 14;
/** \brief [31:16] Reload Value for the WDT (also Time Check Value) (rw) */
  unsigned int rel      : 16;
} OsEE_tc_SCU_WDTCPU_CON0_bits;

/** \brief  Safety WDT Control Register 0 */
typedef OsEE_tc_SCU_WDTCPU_CON0_bits OsEE_tc_SCU_WDTS_CON0_bits;

/** \brief  CPU WDT Control Register 1 */
typedef struct OsEE_tc_SCU_WDTCPU_CON1_bits_tag
{
/** \brief \internal Reserved */
  unsigned int      : 2;
/** \brief [2:2] Input Frequency Request Control (rw) */
  unsigned int ir0  : 1;
/** \brief [3:3] Disable Request Control Bit (rw) */
  unsigned int dr   : 1;
/** \brief \internal Reserved */
  unsigned int      : 1;
/** \brief [5:5] Input Frequency Request Control (rw) */
  unsigned int ir1  : 1;
/** \brief [6:6] Unlock Restriction Request Control Bit (rw) */
  unsigned int ur   : 1;
/** \brief [7:7] Password Auto-sequence Request Bit (rw) */
  unsigned int par  : 1;
/** \brief [8:8] Counter Check Request Bit (rw) */
  unsigned int tcr  : 1;
/** \brief [15:9] Timer Check Tolerance Request (rw) */
  unsigned int tctr : 7;
/** \brief \internal Reserved */
  unsigned int      : 16;
} OsEE_tc_SCU_WDTCPU_CON1_bits;

/** \brief  Safety WDT Control Register 1 */
typedef struct OsEE_tc_SCU_WDTS_CON1_bits_tag
{
/** \brief [0:0] Clear Internal Reset Flag (rwh) */
  unsigned int clrif  : 1;
/** \brief \internal Reserved */
  unsigned int        : 1;
/** \brief [2:2] Input Frequency Request Control (rw) */
  unsigned int ir0    : 1;
/** \brief [3:3] Disable Request Control Bit (rw) */
  unsigned int dr     : 1;
/** \brief \internal Reserved */
  unsigned int        : 1;
/** \brief [5:5] Input Frequency Request Control (rw) */
  unsigned int ir1    : 1;
/** \brief [6:6] Unlock Restriction Request Control Bit (rw) */
  unsigned int ur     : 1;
/** \brief [7:7] Password Auto-sequence Request Bit (rw) */
  unsigned int par    : 1;
/** \brief [8:8] Counter Check Request Bit (rw) */
  unsigned int tcr    : 1;
/** \brief [15:9] Timer Check Tolerance Request (rw) */
  unsigned int tctr   : 7;
/** \brief \internal Reserved */
  unsigned int        : 16;
} OsEE_tc_SCU_WDTS_CON1_bits;

/** \brief  CPU WDT Status Register */
typedef struct OsEE_tc_SCU_WDTCPU_SR_bits_tag
{
/** \brief [0:0] Watchdog Access Error Status Flag (rh) */
  unsigned int ae   : 1;
/** \brief [1:1] Watchdog Overflow Error Status Flag (rh) */
  unsigned int oe   : 1;
/** \brief [2:2] Watchdog Input Clock Status (rh) */
  unsigned int is0  : 1;
/** \brief [3:3] Watchdog Enable/Disable Status Flag (rh) */
  unsigned int ds   : 1;
/** \brief [4:4] Watchdog Time-Out Mode Flag (rh) */
  unsigned int to   : 1;
/** \brief [5:5] Watchdog Input Clock Status (rh) */
  unsigned int is1  : 1;
/** \brief [6:6] SMU Unlock Restriction Status Flag (rh) */
  unsigned int us   : 1;
/** \brief [7:7] Password Auto-sequence Status Flag (rh) */
  unsigned int pas  : 1;
/** \brief [8:8] Timer Check Status Flag (rh) */
  unsigned int tcs  : 1;
/** \brief [15:9] Timer Check Tolerance (rh) */
  unsigned int tct  : 7;
/** \brief [31:16] Timer Value (rh) */
  unsigned int tim  : 16;
} OsEE_tc_SCU_WDTCPU_SR_bits;

/** \brief  Safety WDT Status Register */
typedef OsEE_tc_SCU_WDTCPU_SR_bits OsEE_tc_SCU_WDTS_SR_bits;

/** \brief  CPU WDT Control Register 0 */
typedef union OsEE_tc_SCU_WDTCPU_CON0_tag
{
/** \brief Register access */
  OsEE_reg                      reg;
/** \brief Bitfield access */
  OsEE_tc_SCU_WDTCPU_CON0_bits  bits;
} OsEE_tc_SCU_WDTCPU_CON0;

/** \\brief  CPU WDT Control Register 1 */
typedef union OsEE_tc_SCU_WDTCPU_CON1_tag
{
/** \brief  Register access */
  OsEE_reg                      reg;
/** \brief  Bitfield access */
  OsEE_tc_SCU_WDTCPU_CON1_bits  bits;
} OsEE_tc_SCU_WDTCPU_CON1;

/** \brief  CPU WDT Status Register */
typedef union OsEE_tc_SCU_WDTCPU_SR_tag
{
/** \brief  Register access */
  OsEE_reg                    reg;
/** \brief  Bitfield access */
  OsEE_tc_SCU_WDTCPU_SR_bits  bits;
} OsEE_tc_SCU_WDTCPU_SR;

/** \brief  Safety WDT Control Register 0 */
typedef union OsEE_tc_SCU_WDTS_CON0_tag
{
/** \brief  Register access */
  OsEE_reg                    reg;
/** \brief  Bitfield access */
  OsEE_tc_SCU_WDTS_CON0_bits  bits;
} OsEE_tc_SCU_WDTS_CON0;

/** \brief  Safety WDT Control Register 1 */
typedef union OsEE_tc_SCU_WDTS_CON1_tag
{
/** \brief  Register access */
  OsEE_reg                    reg;
/** \brief  Bitfield access */
  OsEE_tc_SCU_WDTS_CON1_bits  bits;
} OsEE_tc_SCU_WDTS_CON1;

/** \brief  Safety WDT Status Register */
typedef union OsEE_tc_SCU_WDTS_SR_tag
{
/** \brief  Register access */
  OsEE_reg                  reg;
/** \brief  Bitfield access */
  OsEE_tc_SCU_WDTS_SR_bits  bits;
} OsEE_tc_SCU_WDTS_SR;

/** \brief  CPU watchdog */
typedef struct OsEE_tc_SCU_WDTCPU_tag
{
/** \brief  CPU WDT Control Register 0, offset 0 */
  OsEE_tc_SCU_WDTCPU_CON0 con0;
/** \brief  CPU WDT Control Register 1, offset 4 */
  OsEE_tc_SCU_WDTCPU_CON1 con1;
/** \brief  CPU WDT Status Register, offset 8 */
  OsEE_tc_SCU_WDTCPU_SR   sr;
} OsEE_tc_SCU_WDTCPU;

/** \brief  Safety watchdog */
typedef struct OsEE_tc_SCU_WDTS_tag
{
/** \brief  Safety WDT Control Register 0, offset 0 */
  OsEE_tc_SCU_WDTS_CON0 con0;
/** \brief  Safety WDT Control Register 1, offset 4 */
  OsEE_tc_SCU_WDTS_CON1 con1;
/** \brief  Safety WDT Status Register, offset 8 */
  OsEE_tc_SCU_WDTS_SR   sr;
} OsEE_tc_SCU_WDTS;

/** \brief Base address of SCU module */
#define OSEE_TC_SCU_BASE_ADDRESS  (0xF0036000U)
#if (!defined(OSEE_TC_2G))
/** \brief Numer of CPU Watchdogs */
#define OSEE_TC_SCU_WDTCPU_NUM    (3U)
/** \brief Safety Watchdog offset in SCU module */
#define OSEE_TC_SCU_WDTS_OFFSET   (0x000000F0U)
/** \brief CPU Watchdogs offset in SCU module */
#define OSEE_TC_SCU_WDTCPU_OFFSET (0x00000100U)
#else
#define OSEE_TC_SCU_WDTCPU_NUM    (6U)
/** \brief Safety Watchdog offset in SCU module */
#define OSEE_TC_SCU_WDTS_OFFSET   (0x000002A8U)
/** \brief CPU Watchdogs offset in SCU module */
#define OSEE_TC_SCU_WDTCPU_OFFSET (0x0000024CU)
#endif /* !OSEE_TC_2G */

/** \brief SCU Safety Watchdog Access Macro */
#define OSEE_TC_SCU_WDTS\
  (*((OsEE_tc_SCU_WDTS volatile *)\
      (OSEE_TC_SCU_BASE_ADDRESS + OSEE_TC_SCU_WDTS_OFFSET)\
    )\
  )

/** \brief SCU CPU Watchdogs Access Macro */
#define OSEE_TC_SCU_WDTCPU\
  (*((OsEE_tc_SCU_WDTCPU volatile (*)[OSEE_TC_SCU_WDTCPU_NUM])\
      (OSEE_TC_SCU_BASE_ADDRESS + OSEE_TC_SCU_WDTCPU_OFFSET)\
    )\
  )


OSEE_STATIC_INLINE uint16_t OSEE_ALWAYS_INLINE
  osEE_tc_get_cpu_wdt_pw(OsEE_reg core_index)
{
  /* Read Password from CON0 register
   * !!! NOTE: !!! when read bottom six bit of password are inverted so we have
   * to toggle them before returning password */
  uint16_t pw = OSEE_TC_SCU_WDTCPU[core_index].con0.bits.pw;
  uint16_t pw_toggled = pw ^ ((uint16_t)0x003FU);
  return (uint16_t)pw_toggled;
}

OSEE_STATIC_INLINE uint16_t OSEE_ALWAYS_INLINE
  osEE_tc_get_safety_wdt_pw(void)
{
  /* Read Password from CON0 register
   * !!! NOTE: !!! when read bottom six bit of password are inverted so we have
   * to toggle them before returning password */
  uint16_t pw = OSEE_TC_SCU_WDTS.con0.bits.pw;
  uint16_t pw_toggled = pw ^ ((uint16_t)0x003FU);
  return (uint16_t)pw_toggled;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
 osEE_tc_clear_cpu_endinit(OsEE_reg core_index, uint16_t pw)
{
/* Prepare a "reference" to the CPU watchdog */
  OsEE_tc_SCU_WDTCPU volatile * const
    p_cpu_wdt = &OSEE_TC_SCU_WDTCPU[core_index];

/* Read Config_0 register */
  OsEE_tc_SCU_WDTCPU_CON0
    cpu_wdt_con0 = p_cpu_wdt->con0;

/* If locked unlock it */
  if (cpu_wdt_con0.bits.lck != 0U) {
/* see Table 1 (Pass.word Access Bit Pattern Requirements) */
    cpu_wdt_con0.bits.endinit = 1U;
    cpu_wdt_con0.bits.lck     = 0U;
    cpu_wdt_con0.bits.pw      = pw;

/* Password ready. Store it to WDT_CON0 to unprotect the register */
    p_cpu_wdt->con0.reg = cpu_wdt_con0.reg;
  }

/* Clear ENDINT and set LCK bit in Config_0 register */
  cpu_wdt_con0.bits.endinit = 0U;
  cpu_wdt_con0.bits.lck     = 1U;
  p_cpu_wdt->con0.reg       = cpu_wdt_con0.reg;

/* Read back ENDINIT and wait until it has been cleared */
  while (p_cpu_wdt->con0.bits.endinit == 1U) {
    ;
  }
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_set_cpu_endinit(OsEE_reg core_index, uint16_t pw)
{
/* Prepare a "reference" to the CPU watchdog */
  OsEE_tc_SCU_WDTCPU volatile * const
    p_cpu_wdt = &OSEE_TC_SCU_WDTCPU[core_index];

/* Read Config_0 register */
  OsEE_tc_SCU_WDTCPU_CON0
    cpu_wdt_con0 = p_cpu_wdt->con0;

/* If locked unlock it */
  if (cpu_wdt_con0.bits.lck != 0U) {
/* see Table 1 (Pass.word Access Bit Pattern Requirements) */
    cpu_wdt_con0.bits.endinit = 1U;
    cpu_wdt_con0.bits.lck     = 0U;
    cpu_wdt_con0.bits.pw      = pw;

/* Password ready. Store it to WDT_CON0 to unprotect the register */
    p_cpu_wdt->con0.reg = cpu_wdt_con0.reg;
  }

/* Set ENDINT and set LCK bit in Config_0 register */
  cpu_wdt_con0.bits.endinit = 1U;
  cpu_wdt_con0.bits.lck     = 1U;
  p_cpu_wdt->con0.reg       = cpu_wdt_con0.reg;

/* Read back ENDINIT and wait until it has been set */
  while (p_cpu_wdt->con0.bits.endinit == 0U) {
    ;
  }
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_disable_cpu_wdt(OsEE_reg core_index, uint16_t pw)
{
  osEE_tc_clear_cpu_endinit(core_index, pw);
/* Set "Disable Request bit" on CPU_WDT[core_index].CON1 */
  OSEE_TC_SCU_WDTCPU[core_index].con1.bits.dr = 1U;
  osEE_tc_set_cpu_endinit(core_index, pw);
}

#if 0
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_enable_cpu_wdt(OsEE_reg core_index, uint16_t pw)
{
  osEE_tc_clear_cpu_endinit(core_index, pw);
/* Reset "Disable Request bit" on CPU_WDT[core_index].CON1 */
  OSEE_TC_SCU_WDTCPU[core_index].con1.bits.dr = 0U;
  osEE_tc_set_cpu_endinit(core_index, pw);
}
#endif

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_clear_safety_endinit(uint16_t pw)
{
/* Read Config_0 register */
  OsEE_tc_SCU_WDTS_CON0
    safety_wdt_con0 = OSEE_TC_SCU_WDTS.con0;

/* If locked unlock it */
  if (safety_wdt_con0.bits.lck != 0U) {
/* see Table 1 (Pass.word Access Bit Pattern Requirements) */
    safety_wdt_con0.bits.endinit = 1U;
    safety_wdt_con0.bits.lck     = 0U;
    safety_wdt_con0.bits.pw      = pw;

/* Password ready. Store it to WDT_CON0 to unprotect the register */
    OSEE_TC_SCU_WDTS.con0.reg = safety_wdt_con0.reg;
  }

/* Clear ENDINT and set LCK bit in Config_0 register */
  safety_wdt_con0.bits.endinit = 0U;
  safety_wdt_con0.bits.lck     = 1U;
  OSEE_TC_SCU_WDTS.con0.reg    = safety_wdt_con0.reg;

/* Read back ENDINIT and wait until it has been cleared */
  while (OSEE_TC_SCU_WDTS.con0.bits.endinit == 1U) {
    ;
  }
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_set_safety_endinit(uint16_t pw)
{
/* Read Config_0 register */
  OsEE_tc_SCU_WDTS_CON0
    safety_wdt_con0 = OSEE_TC_SCU_WDTS.con0;

/* If locked unlock it */
  if (safety_wdt_con0.bits.lck != 0U) {
/* see Table 1 (Pass.word Access Bit Pattern Requirements) */
    safety_wdt_con0.bits.endinit = 1U;
    safety_wdt_con0.bits.lck     = 0U;
    safety_wdt_con0.bits.pw      = pw;

/* Password ready. Store it to WDT_CON0 to unprotect the register */
    OSEE_TC_SCU_WDTS.con0.reg = safety_wdt_con0.reg;
  }


/* Set ENDINT and set LCK bit in Config_0 register */
  safety_wdt_con0.bits.endinit = 1U;
  safety_wdt_con0.bits.lck     = 1U;
  OSEE_TC_SCU_WDTS.con0.reg   = safety_wdt_con0.reg;

/* Read back ENDINIT and wait until it has been cleared */
  while (OSEE_TC_SCU_WDTS.con0.bits.endinit == 0U) {
    ;
  }
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_disable_safety_wdt(uint16_t pw)
{
  osEE_tc_clear_safety_endinit(pw);
/* Set "Disable Request bit" on CPU_WDTS.CON1 */
  OSEE_TC_SCU_WDTS.con1.bits.dr = 1U;
  osEE_tc_set_safety_endinit(pw);
}

#if 0
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_enable_safety_wdt(uint16_t pw)
{
  osEE_tc_clear_safety_endinit(pw);
/* Reset "Disable Request bit" on CPU_WDTS.CON1 */
  OSEE_TC_SCU_WDTS.con1.bits.dr = 0U;
  osEE_tc_set_safety_endinit(pw);
}
#endif

/******************************************************************************
          Initialization Utility Functions Declaration and Definition
 *****************************************************************************/

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_set_pcache(OsEE_bool enable)
{
  uint16_t cpu_wdt_pw;
  OsEE_core_id  const core_id = osEE_get_curr_core_id();
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
  OsEE_reg      const core_index = (core_id != OS_CORE_ID_6)?
    (OsEE_reg)core_id: 5U;
#else
  OsEE_reg      const core_index = (OsEE_reg)core_id;
#endif
/* PCON0[1:1](.PCBYP mask) Program Cache Bypass (rw).
   PCBYP is the only not reserved bit in PCON0. */
  OsEE_reg const pcon0 = (enable)? 0x0U: 0x2U;
  if (enable) {
    /* Step 1: Initiate invalidation of current pcache contents if any.
       (i.e. PCON1[0:0](.PCINV) = 1 Program Cache Invalidate */
    osEE_tc_set_csfr(OSEE_CSFR_PCON1, 0x1U);
  }

/* CPU WDT Password */
  cpu_wdt_pw = osEE_tc_get_cpu_wdt_pw(core_index);

/* PCACHE enable steps */
/* Step 2: Set PCBYP to 0 if cache is enabled */
  osEE_tc_clear_cpu_endinit(core_index, cpu_wdt_pw);
  osEE_tc_set_csfr(OSEE_CSFR_PCON0, pcon0);
  osEE_tc_set_cpu_endinit(core_index, cpu_wdt_pw);
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_set_dcache(OsEE_bool enable)
{
  uint16_t cpu_wdt_pw;
  OsEE_core_id  const core_id = osEE_get_curr_core_id();
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
  OsEE_reg      const core_index = (core_id != OS_CORE_ID_6)?
    (OsEE_reg)core_id: 5U;
#else
  OsEE_reg      const core_index = (OsEE_reg)core_id;
#endif


/* DCON0[1:1](.DCBYP mask) Data Cache Bypass (rw).
   DCBYP is the only not reserved bit in DCON0. */
  OsEE_reg const dcon0 = (enable)? 0x0U: 0x2U;

/* CPU WDT Password */
  cpu_wdt_pw = osEE_tc_get_cpu_wdt_pw(core_index);

/* DCACHE enable steps */
/* Step 2: Set DCBYP to 0 if cache is enabled */
  osEE_tc_clear_cpu_endinit(core_index, cpu_wdt_pw);
  osEE_tc_set_csfr(OSEE_CSFR_DCON0, dcon0);
  osEE_tc_set_cpu_endinit(core_index, cpu_wdt_pw);
}

/**
 * \brief Setup the context save area linked list. This MUST be
 *        inline because you cannot make a real function call before
 *        initialize CSAs lists
 * \param [in] p_csa_begin  Start address for the CSA area to be initialized
 * \param [in] p_csa_end    End address for the CSA area to be initialized
 *
 */

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_csa_init_inline
(
  OsEE_csa       * const p_csa_begin,
  OsEE_csa const * const p_csa_end
)
{
/* Nr of CSAs in area. Best solution, even though is a MISRA deviation, since
   pointers subtraction handles OsEE_csa size and p_csa_end/p_csa_begin
   are the extremes of an array constructed in linker script
   (condition under where C language specification allows pointer subtraction).
 */
  size_t const no_of_csas = (size_t)(p_csa_end - p_csa_begin);

/* Previous Context Pointer (CSA Link Word) */
  OsEE_reg pcxi_val = 0U;
/*
  This variable hold the number of CSA that I have to leave free to
  handle FCD trap.
  3 are needed by this trap and 3 more are needed for
  potential nested asynchronous trap.
  To handle a trap 3 CSA are needed because class trap handler entry
  call TNI switch routine that call TNI sub-handler.
  TODO: Give the possibility to configure this parameter.
*/
  OsEE_reg fcd_needed_csa = 6U;
/* Cycle Index */
  size_t i;

/*
  IMPORTANT:
  I initialize the Free Context List in reverse order.
  So I will end with a list that will grow toward bigger addresses.
 */
  for (i = no_of_csas; i > 0U; --i) {
/* CSA PCXI segment */
    OsEE_reg   pcxi_s;
/* CSA PCXI offset */
    OsEE_reg   pcxi_o;
/* Get current CSA pointer */
    OsEE_csa * const p_csa = &p_csa_begin[(i - 1U)];

/* Store in current CSA previous pointer (null in last CSA. i.e. First time!) */
    p_csa->l_next.reg = pcxi_val;
/* Current CSA segment */
    pcxi_s  = (((OsEE_reg)p_csa >> 28U) & 0xFU) << 16U;
/* Evaluate CSA Segment Offset */
    pcxi_o  = (((OsEE_reg)p_csa >> 6U) & 0xFFFFU);
/* Compose pcxi_s and pcxi_o in the pcxi_val to be stored in next CSA */
    pcxi_val = pcxi_s | pcxi_o;

/* Check if you have to populate LCX that point to the 'almost empty'
   position */
    --fcd_needed_csa;
    if (fcd_needed_csa == 0U) {
/* After having stored the LCX, I would have to have a 32 bit wrap around to
   override the previous value and in a 32-bit address space is not possible. */
      osEE_tc_set_csfr(OSEE_CSFR_LCX, pcxi_val);
    }
  }
/* Initialize the HEAD of Free Context List */
  osEE_tc_set_csfr(OSEE_CSFR_FCX, pcxi_val);
}

/******************************************************************************
                          System Timer Support (STM)
 *****************************************************************************/

#if (!defined(OSEE_TC_2G))
#define OSEE_TC_STM_BASE            (0xF0000000U)
#else
#define OSEE_TC_STM_BASE            (0xF0001000U)
#endif /* !OSEE_TC_2G */

#define OSEE_TC_STM_CORE_OFFSET(c)  (((((OsEE_reg)(c))) & 0x3U) * 0x100U)

#define OSEE_TC_STM_ADDR(c, regoffset)\
  (OSEE_TC_STM_BASE + OSEE_TC_STM_CORE_OFFSET(c) + ((regoffset) & 0xFFU))
  
#define OSEE_TC_STM_REG(c, regoffset)\
  (*(OsEE_reg volatile *)OSEE_TC_STM_ADDR(c, regoffset))

#if (!defined(OSEE_TC_2G))
#define OSEE_TC_SRC_STM_OFF         (0x0490U)
#else
#define OSEE_TC_SRC_STM_OFF         (0x0300U)
#endif /* !OSEE_TC_2G */

#define OSEE_TC_STM_SRC_OFFSET(c, sr)\
  (OSEE_TC_SRC_STM_OFF +\
    ((((OsEE_reg)(c)) & 0x3U) * 8U) + (((sr) & 0x1U) * 4U))

/** \brief Clock Control Register */
#define OSEE_TC_STM_CLC_OFF     (0x00U)
/** \brief Module Identification Register */
#define OSEE_TC_STM_ID_OFF      (0x08U)
/** \brief Timer Register 0 */
#define OSEE_TC_STM_TIM0_OFF    (0x10U)
/** \brief Timer Register 1 */
#define OSEE_TC_STM_TIM1_OFF    (0x14U)
/** \brief Timer Register 2 */
#define OSEE_TC_STM_TIM2_OFF    (0x18U)
/** \brief Timer Register 3 */
#define OSEE_TC_STM_TIM3_OFF    (0x1CU)
/** \brief Timer Register 4 */
#define OSEE_TC_STM_TIM4_OFF    (0x20U)
/** \brief Timer Register 5 */
#define OSEE_TC_STM_TIM5_OFF    (0x24U)
/** \brief Timer Register 6 */
#define OSEE_TC_STM_TIM6_OFF    (0x28U)
/** \brief Timer Capture Register */
#define OSEE_TC_STM_CAP_OFF     (0x2CU)
/** \brief Compare Register 0 */
#define OSEE_TC_STM_CMP0_OFF    (0x30U)
/** \brief Compare Register 1 */
#define OSEE_TC_STM_CMP1_OFF    (0x34U)
/** \brief Compare Match Control Register */
#define OSEE_TC_STM_CMCON_OFF   (0x38U)
/** \brief Interrupt Control Register */
#define OSEE_TC_STM_ICR_OFF     (0x3CU)
/** \brief Interrupt Set/Clear Register */
#define OSEE_TC_STM_ISCR_OFF    (0x40U)
/** \brief Timer Register 0 Second View */
#define OSEE_TC_STM_TIM0SV_OFF  (0x50U)
/** \brief Timer Capture Register Second View */
#define OSEE_TC_STM_CAPSV_OFF   (0x54U)
/** \brief OCDS Control and Status */
#define OSEE_TC_STM_OCS_OFF     (0xE8U)
/** \brief Kernel Reset Status Clear Register */
#define OSEE_TC_STM_KRSTCLR_OFF (0xECU)
/** \brief Kernel Reset Register 1 */
#define OSEE_TC_STM_KRST1_OFF   (0xF0U)
/** \brief Kernel Reset Register 0 */
#define OSEE_TC_STM_KRST0_OFF   (0xF4U)
/** \brief Access Enable Register 1 */
#define OSEE_TC_STM_ACCEN1_OFF  (0xF8U)
/** \brief Access Enable Register 0 */
#define OSEE_TC_STM_ACCEN0_OFF  (0xFCU)

/** \brief  Compare Match Control Register */
typedef struct OsEE_tc_STM_CMCON_bits_tag
{
/** \brief [4:0] Compare Register Size for CMP0 (rw) */
  unsigned int msize0   : 5;
/** \brief \internal Reserved */
  unsigned int          : 3;
/** \brief [12:8] Start Bit Location for CMP0 (rw) */
  unsigned int mstart0  : 5;
/** \brief \internal Reserved */
  unsigned int          : 3;
/** \brief [20:16] Compare Register Size for CMP1 (rw) */
  unsigned int msize1   : 5;
/** \brief \internal Reserved */
  unsigned int          : 3;
/** \brief [28:24] Start Bit Location for CMP1 (rw) */
  unsigned int mstart1  : 5;
/** \brief \internal Reserved */
  unsigned int          : 3;
} OsEE_tc_STM_CMCON_bits;

typedef union OsEE_tc_STM_CMCON_tag {
  OsEE_reg                reg;
  OsEE_tc_STM_CMCON_bits  bits;
} OsEE_tc_STM_CMCON;

#define OSEE_TC_STM_CMCON(c)\
  (*(OsEE_tc_STM_CMCON volatile *)\
    OSEE_TC_STM_ADDR(c, OSEE_TC_STM_CMCON_OFF)\
  )

/** \\brief  Interrupt Control Register */
typedef struct OsEE_tc_STM_ICR_bits_tag
{
/** \brief [0:0] Compare Register CMP0 Interrupt Enable Control (rw) */
  unsigned int cmp0en : 1;
/** \brief [1:1] Compare Register CMP0 Interrupt Request Flag (rh) */
  unsigned int cmp0ir : 1;
/** \brief [2:2] Compare Register CMP0 Interrupt Output Selection (rw) */
  unsigned int cmp0os : 1;
/** \brief \internal Reserved */
  unsigned int        : 1;
/** \brief [4:4] Compare Register CMP1 Interrupt Enable Control (rw) */
  unsigned int cmp1en : 1;
/** \brief [5:5] Compare Register CMP1 Interrupt Request Flag (rh) */
  unsigned int cmp1ir : 1;
/** \brief [6:6] Compare Register CMP1 Interrupt Output Selection (rw) */
  unsigned int cmp1os : 1;
/** \brief \internal Reserved */
  unsigned int        : 25;
} OsEE_tc_STM_ICR_bits;

typedef union OsEE_tc_STM_ICR_tag {
  OsEE_reg                reg;
  OsEE_tc_STM_ICR_bits  bits;
} OsEE_tc_STM_ICR;

#define OSEE_TC_STM_ICR(c)\
  (*(OsEE_tc_STM_ICR volatile *)\
    OSEE_TC_STM_ADDR(c, OSEE_TC_STM_ICR_OFF)\
  )

/**
  * @brief  Used to read lower word of STM peripheral 64 bit counter.
  *         To guarantee coherency lower word must be read before than upper
  *         word.
 */
OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE
  osEE_tc_stm_get_time_lower_word(OsEE_reg stm_id)
{
  return OSEE_TC_STM_REG(stm_id, OSEE_TC_STM_TIM0_OFF);
}

/**
  * @brief  Used to read upper word of STM peripheral 64 bit counter.
  *         To guarantee coherency lower word must be read before than upper
  *         word.
  */
OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE
  osEE_tc_stm_get_time_upper_word(OsEE_reg stm_id)
{
  return OSEE_TC_STM_REG(stm_id, OSEE_TC_STM_CAP_OFF);
}

/** @brief Mask for STM OCDS suspension: SUS := 2, SUS_P := 1 */
#define OSEE_TC_STM_OCS_SUS_CTRL_MASK\
  ((((OsEE_reg)1U) << 28U) | (((OsEE_reg)2U) << 24U))

/**
  * @brief  Used to set STM suspension when OCDS take control
  */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_stm_ocds_suspend_control(OsEE_reg stm_id)
{
  OSEE_TC_STM_REG(stm_id, OSEE_TC_STM_OCS_OFF) =
    OSEE_TC_STM_OCS_SUS_CTRL_MASK;
}

/**
  * @brief  Used as bounded busy wait.
  * @param  usec the number of microseconds you want to wait
  */
void osEE_tc_delay(OsEE_reg usec);

/* Legit Devices for System Timer Defines. */
/* N.B:
 * For the system timer we will use STM periperal. This periferal
 * is composed by a 64 bit upper cunter in free-run, two compare
 * registers (32 bit with offset and mask-length configurable),
 * and two services (read: interrupt sources). Each Compare
 * register can be tied to both service, and that would mean
 * 4 STM meaningfull configuration, but only two independent.
 * For semplicity i fix a degrees of freedom tying compare register
 * with corrisponding service number. So the configuration will be
 * easyer, still having two independent services source.
 *
 * (Check the documentention for more information)
 */

/* Valid system timer devices */
#define OSEE_TC_STM_SR0 1
#define OSEE_TC_STM_SR1 2

/** @brief Initialize a global variable with STM frequency. */
extern void osEE_tc_stm_set_clockpersec(void);

#if (defined(OSEE_SINGLECORE))
#if (!defined(OSEE_SYSTEM_TIMER_DEVICE)) ||\
  (OSEE_SYSTEM_TIMER_DEVICE != OSEE_TC_STM_SR0)
/**
  *  @brief Programs STM compare register 0 to trigger an IRQ after
  *         usec microseconds
  *  @param usec microseconds after you want get an IRQ on intvec
  *  @param intvec Interrupt Vector Table entry that will handle STM interrupt.
  *         With intvec == 0, the correponding service request node is left
  *         unprogrammed or resetted.
  */
void osEE_tc_stm_set_sr0(OsEE_reg usec, OsEE_tc_isr_hw_prio intvec);

/**
  *  @brief Change previous programmed STM compare register 0 to trigger next
            IRQ after usec microseconds
  *  @param usec microseconds after you want get an IRQ on intvec
  */
void osEE_tc_stm_set_sr0_next_match(OsEE_reg usec);
#endif /* OSEE_SYSTEM_TIMER_DEVICE != OSEE_TC_STM_SR0 */
#if (!defined(OSEE_SYSTEM_TIMER_DEVICE)) ||\
  (OSEE_SYSTEM_TIMER_DEVICE != OSEE_TC_STM_SR1)
/**
  *  @brief Programs STM compare register 1 to trigger an IRQ after
  *         usec microseconds
  *  @param usec microseconds after you want get an IRQ on intvec
  *  @param intvec Interrupt Vector Table entry that will handle STM interrupt.
  *         With intvec == 0, the correponding service request node is left
  *         unprogrammed or resetted.
  */
void osEE_tc_stm_set_sr1(OsEE_reg usec, OsEE_tc_isr_hw_prio intvec);

/**
  * @brief  Change previous programmed STM compare register 1 to trigger next
  *         IRQ after usec microseconds
  * @param  usec microseconds after you want get an IRQ on intvec
  */
void osEE_tc_stm_set_sr1_next_match(OsEE_reg usec);
#endif /* OSEE_SYSTEM_TIMER_DEVICE != OSEE_TC_STM_SR1 */
#else /* OSEE_SINGLECORE */
#if ((!defined(OSEE_SYSTEM_TIMER_CORE0_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE0_DEVICE != OSEE_TC_STM_SR0)) && \
    ((!defined(OSEE_SYSTEM_TIMER_CORE1_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE1_DEVICE != OSEE_TC_STM_SR0)) && \
    ((!defined(OSEE_SYSTEM_TIMER_CORE2_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE2_DEVICE != OSEE_TC_STM_SR0)) && \
    ((!defined(OSEE_SYSTEM_TIMER_CORE3_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE3_DEVICE != OSEE_TC_STM_SR0)) && \
    ((!defined(OSEE_SYSTEM_TIMER_CORE4_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE4_DEVICE != OSEE_TC_STM_SR0)) && \
    ((!defined(OSEE_SYSTEM_TIMER_CORE6_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE6_DEVICE != OSEE_TC_STM_SR0))
/**
  *  @brief Programs STM compare register 0 to trigger an IRQ after
  *         usec microseconds
  *  @param usec microseconds after you want get an IRQ on intvec
  *  @param intvec Interrupt Vector Table entry that will handle STM interrupt.
  *         With intvec == 0, the correponding service request node is left
  *         unprogrammed or resetted.
  */
void osEE_tc_stm_set_sr0(OsEE_reg usec, OsEE_tc_isr_hw_prio intvec);

/**
  *  @brief Change previous programmed STM compare register 0 to trigger next
            IRQ after usec microseconds
  *  @param usec microseconds after you want get an IRQ on intvec
  */
void osEE_tc_stm_set_sr0_next_match(OsEE_reg usec);
#endif
#if ((!defined(OSEE_SYSTEM_TIMER_CORE0_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE0_DEVICE != OSEE_TC_STM_SR1)) && \
    ((!defined(OSEE_SYSTEM_TIMER_CORE1_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE1_DEVICE != OSEE_TC_STM_SR1)) && \
    ((!defined(OSEE_SYSTEM_TIMER_CORE2_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE2_DEVICE != OSEE_TC_STM_SR1)) && \
    ((!defined(OSEE_SYSTEM_TIMER_CORE3_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE3_DEVICE != OSEE_TC_STM_SR1)) && \
    ((!defined(OSEE_SYSTEM_TIMER_CORE4_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE4_DEVICE != OSEE_TC_STM_SR1)) && \
    ((!defined(OSEE_SYSTEM_TIMER_CORE6_DEVICE)) ||            \
      (OSEE_SYSTEM_TIMER_CORE6_DEVICE != OSEE_TC_STM_SR1))
/**
  *  @brief Programs STM compare register 1 to trigger an IRQ after
  *         usec microseconds
  *  @param usec microseconds after you want get an IRQ on intvec
  *  @param intvec Interrupt Vector Table entry that will handle STM interrupt.
  *         With intvec == 0, the correponding service request node is left
  *         unprogrammed or resetted.
  */
void osEE_tc_stm_set_sr1(OsEE_reg usec, OsEE_tc_isr_hw_prio intvec);

/**
  * @brief  Change previous programmed STM compare register 1 to trigger next
  *         IRQ after usec microseconds
  * @param  usec microseconds after you want get an IRQ on intvec
  */
void osEE_tc_stm_set_sr1_next_match(OsEE_reg usec);
#endif
#endif /* OSEE_SINGLECORE */

/* STM fSOURCE PLL divider */
#if (!defined(OSEE_TC_STMDIV_VALUE))
/* Write at 300 MHz on STM registers fails, so is a MUST to slow down fSTM. */
#if (OSEE_CPU_CLOCK >= 300000000U)
#define OSEE_TC_STMDIV_VALUE  (2U)
#else
#define OSEE_TC_STMDIV_VALUE  (1U)
#endif
#endif /* OSEE_TC_STMDIV_VALUE */

/******************************************************************************
                              SCU Support
 *****************************************************************************/
/** \brief SCU Module Address */
#define OSEE_TC_SCU_BASE (0xF0036000U)
/** \brief Evaluate a Register Address */
#define OSEE_TC_SCU_REG_ADDR(offset)  (OSEE_TC_SCU_BASE + (offset))
/** \brief Access a SCU register as 32-bit variable */
#define OSEE_TC_SCU_REG(offset)\
  (*(OsEE_reg volatile *)OSEE_TC_SCU_REG_ADDR(offset))

/** \brief SCU offset 0x10, OSC Control Register */
#define OSEE_TC_SCU_OSCCON_OFF      (0x10U)
/** \brief SCU offset 0x14, PLL Status Register */
#define OSEE_TC_SCU_PLLSTAT_OFF     (0x14U)
/** \brief SCU offset 0x18, PLL Configuration 0 Register */
#define OSEE_TC_SCU_PLLCON0_OFF     (0x18U)
/** \brief SCU offset 0x1C, PLL Configuration 1 Register */
#define OSEE_TC_SCU_PLLCON1_OFF     (0x1CU)
/** \brief SCU offset 0x20, PLL Configuration 2 Register */
#define OSEE_TC_SCU_PLLCON2_OFF     (0x20U)
/** \brief SCU offset 0x24, PLL_ERAY Status Register */
#define OSEE_TC_SCU_PLLERAYSTAT_OFF (0x24U)
/** \brief SCU offset 0x28, PLL_ERAY Configuration 0 Register */
#define OSEE_TC_SCU_PLLERAYCON0_OFF (0x28U)
/** \brief SCU offset 0x2C, PLL_ERAY Configuration 1 Register */
#define OSEE_TC_SCU_PLLERAYCON1_OFF (0x2CU)
/** \brief SCU offset 0x30, CCU Clock Control Register 0 */
#define OSEE_TC_SCU_CCUCON0_OFF     (0x30U)
/** \brief SCU offset 0x34, CCU Clock Control Register 1 */
#define OSEE_TC_SCU_CCUCON1_OFF     (0x34U)

/** \brief SCU offset 0x40, CCU Clock Control Register 2 */
#define OSEE_TC_SCU_CCUCON2_OFF     (0x40U)
/** \brief SCU offset 0x44, CCU Clock Control Register 3 */
#define OSEE_TC_SCU_CCUCON3_OFF     (0x44U)
/** \brief SCU offset 0x48, CCU Clock Control Register 4 */
#define OSEE_TC_SCU_CCUCON4_OFF     (0x48U)
/** \brief SCU offset 0x4C, CCU Clock Control Register 5 */
#define OSEE_TC_SCU_CCUCON5_OFF     (0x4CU)

/** \brief SCU offset 0x80, CCU Clock Control Register 6 */
#define OSEE_TC_SCU_CCUCON6_OFF     (0x80U)
/** \brief SCU offset 0x84, CCU Clock Control Register 7 */
#define OSEE_TC_SCU_CCUCON7_OFF     (0x84U)
/** \brief SCU offset 0x88, CCU Clock Control Register 8 */
#define OSEE_TC_SCU_CCUCON8_OFF     (0x88U)
/** \brief SCU offset 0x8C, CCU Clock Control Register 9 */
#define OSEE_TC_SCU_CCUCON9_OFF     (0x8CU)

#if (!defined(OSEE_TC_2G))
/** \brief  OSC Control Register */
typedef struct
{
/** \brief \internal Reserved */
  unsigned int          : 1;
/** \brief [1:1] Oscillator for PLL Valid Low Status Bit (rh) */
  unsigned int plllv    : 1;
/** \brief [2:2] Oscillator Watchdog Reset (w) */
  unsigned int oscres   : 1;
/** \brief [4:3] Oscillator Gain Selection (rw) */
  unsigned int gainsel  : 2;
/** \brief [6:5] Oscillator Mode (rw) */
  unsigned int mode     : 2;
/** \brief [7:7] Shaper Bypass (rw) */
  unsigned int shby     : 1;
/** \brief [8:8] Oscillator for PLL Valid High Status Bit (rh) */
  unsigned int pllhv    : 1;
/** \brief \internal Reserved */
  unsigned int          : 1;
/** \brief [10:10] XTAL1 Data Value (rh) */
  unsigned int x1d      : 1;
/** \brief [11:11] XTAL1 Data Enable (rw) */
  unsigned int x1den    : 1;
/** \brief \internal Reserved */
  unsigned int          : 4;
/** \brief [20:16] OSC Frequency Value (rw) */
  unsigned int oscval   : 5;
/** \brief \internal Reserved */
  unsigned int          : 2;
/** \brief [23:23] Amplitude Regulation Enable (rw) */
  unsigned int apren    : 1;
/** \brief [24:24] Capacitance 0 Enable (rw) */
  unsigned int cap0en   : 1;
/** \brief [25:25] Capacitance 1 Enable (rw) */
  unsigned int cap1en   : 1;
/** \brief [26:26] Capacitance 2 Enable (rw) */
  unsigned int cap2en   : 1;
/** \brief [27:27] Capacitance 3 Enable (rw) */
  unsigned int cap3en   : 1;
/**< \brief \internal Reserved */
  unsigned int          : 4;
} OsEE_tc_SCU_OSCCON_bits;

/** \brief  PLL Status Register */
typedef struct
{
/** \brief [0:0] VCO Bypass Status (rh) */
  unsigned int vcobyst  : 1;
/** \brief \internal Reserved */
  unsigned int          : 1;
/** \brief [2:2] PLL VCO Lock Status (rh) */
  unsigned int vcolock  : 1;
/** \brief [3:3] Input Clock Disconnect Select Status (rh) */
  unsigned int findis   : 1;
/** \brief [4:4] K1 Divider Ready Status (rh) */
  unsigned int k1rdy    : 1;
/** \brief [5:5] K2 Divider Ready Status (rh) */
  unsigned int k2rdy    : 1;
/** \brief \internal Reserved */
  unsigned int          : 1;
/** \brief [7:7] Modulation Run (rh) */
  unsigned int modrun   : 1;
/** \brief \internal Reserved */
  unsigned int          : 24;
} OsEE_tc_SCU_PLLSTAT_bits;

typedef union {
  OsEE_reg                  reg;
  OsEE_tc_SCU_PLLSTAT_bits  bits;
} OsEE_tc_SCU_PLLSTAT;

#define OSEE_TC_SCU_PLLSTAT\
  (*(OsEE_tc_SCU_PLLSTAT volatile *)\
    OSEE_TC_SCU_REG_ADDR(OSEE_TC_SCU_PLLSTAT_OFF)\
  )

/** \brief  PLL Configuration 0 Register */
typedef struct
{
/** \brief [0:0] VCO Bypass (rw) */
  unsigned int vcobyp     : 1;
/** \brief [1:1] VCO Power Saving Mode (rw) */
  unsigned int vcopwd     : 1;
/** \brief [2:2] Modulation Enable (rw) */
  unsigned int moden      : 1;
/** \brief \internal Reserved */
  unsigned int            : 1;
/** \brief [4:4] Set Status Bit PLLSTAT.FINDIS (w) */
  unsigned int setfindis  : 1;
/** \brief [5:5] Clear Status Bit PLLSTAT.FINDIS (w) */
  unsigned int clrfindis  : 1;
/** \brief [6:6] Oscillator Disconnect Disable (rw) */
  unsigned int oscdisdis  : 1;
/** \brief \internal Reserved */
  unsigned int            : 2;
/** \brief [15:9] N-Divider Value (rw) */
  unsigned int ndiv       : 7;
/** \brief [16:16] PLL Power Saving Mode (rw) */
  unsigned int pllpwd     : 1;
/** \brief \internal Reserved */
  unsigned int            : 1;
/** \brief [18:18] Restart VCO Lock Detection (w) */
  unsigned int resld      : 1;
/** \brief \internal Reserved */
  unsigned int            : 5;
/**< \brief [27:24] P-Divider Value (rw) */
  unsigned int pdiv       : 4;
/** \brief \internal Reserved */
  unsigned int            : 4;
} OsEE_tc_SCU_PLLCON0_bits;

typedef union {
  OsEE_reg                  reg;
  OsEE_tc_SCU_PLLCON0_bits  bits;
} OsEE_tc_SCU_PLLCON0;

#define OSEE_TC_SCU_PLLCON0\
  (*(OsEE_tc_SCU_PLLCON0 volatile *)\
    OSEE_TC_SCU_REG_ADDR(OSEE_TC_SCU_PLLCON0_OFF)\
  )

/** \brief  PLL Configuration 1 Register */
typedef struct
{
/** \brief [6:0] K2-Divider Value (rw) */
  unsigned int k2div  : 7;
/** \brief \internal Reserved */
  unsigned int        : 1;
/** \brief [14:8] K3-Divider Value (rw) */
  unsigned int k3div  : 7;
/** \brief \internal Reserved */
  unsigned int        : 1;
/** \brief [22:16] K1-Divider Value (rw) */
  unsigned int k1div  : 7;
/** \brief \internal Reserved */
  unsigned int        : 9;
} OsEE_tc_SCU_PLLCON1_bits;

typedef union {
  OsEE_reg                  reg;
  OsEE_tc_SCU_PLLCON1_bits  bits;
} OsEE_tc_SCU_PLLCON1;

#define OSEE_TC_SCU_PLLCON1\
  (*(OsEE_tc_SCU_PLLCON1 volatile *)\
    OSEE_TC_SCU_REG_ADDR(OSEE_TC_SCU_PLLCON1_OFF)\
  )

/** \brief  CCU Clock Control Register 0 */
typedef struct
{
/** \brief [3:0] Baud1 Divider Reload Value (rw) */
  unsigned int baud1div   : 4;
/** \brief [7:4] Baud2 Divider Reload Value (rw) */
  unsigned int baud2div   : 4;
/** \brief [11:8] SRI Divider Reload Value (rw) */
  unsigned int sridiv     : 4;
/** \brief [15:12] Low Power Divider Reload Value (rw) */
  unsigned int lpdiv      : 4;
/** \brief [19:16] SPB Divider Reload Value (rw) */
  unsigned int spbdiv     : 4;
/** \brief [21:20] FSI2 Divider Reload Value (rw) */
  unsigned int fsi2div    : 2;
/** \brief \internal Reserved */
  unsigned int            : 2;
/** \brief [25:24] FSI Divider Reload Value (rw) */
  unsigned int fsidiv     : 2;
/** \brief [27:26] ADC Clock Selection (rw) */
  unsigned int adcclksel  : 2;
/** \brief [29:28] Clock Selection (rw) */
  unsigned int clksel     : 2;
/** \brief [30:30] Update Request (w) */
  unsigned int up         : 1;
/** \brief [31:31] Lock Status (rh) */
  unsigned int lck        : 1;
} OsEE_tc_SCU_CCUCON0_bits;

/*  Baud1 Divider Reload Value. 0001B fBAUD1 = fsource. Bits [0:3] */
#define OSEE_TC_SCU_CCUCON0_BAUD1DIV(baud1)\
  (((OsEE_reg)(baud1)) & (OsEE_reg)0xFU)
/*  Baud2 Divider Reload Value. 0001B fBAUD2 = fsource. Bits[4:7] */
#define OSEE_TC_SCU_CCUCON0_BAUD2DIV(baud2)\
  ((((OsEE_reg)(baud2)) & (OsEE_reg)0xF) << 4U)
/*  SRI Divider Reload Value 0001B fSRI = fsource. Bits [8:11] */
#define OSEE_TC_SCU_CCUCON0_SRI(sri)\
  ((((OsEE_reg)(sri)) & (OsEE_reg)0xFU) << 8U)
/*  Low Power Divider Reload Value 0001B fSRI, fSPB, and fBBB = fsource/30;
    fMAX = fsource/15. Bits [15:12] */
#define OSEE_TC_SCU_CCUCON0_LPDIV(lpdiv)\
  ((((OsEE_reg)(lpdiv)) & (OsEE_reg)0xFU) << 12U)
/*  SPB Divider Reload Value 0001B Reserved 0010B fSPB = fsource/2.
    Bits [16:19] */
#define OSEE_TC_SCU_CCUCON0_SPB(spb)\
  (((((OsEE_reg)(spb)) & (OsEE_reg)0xFU) == 1U)?\
    ((OsEE_reg)0x2U << 16U):\
    ((((OsEE_reg)(spb)) & (OsEE_reg)0xFU) << 16U))
/*  FSI2 Divider Reload Value 10B fFSI2 = fSRI / 2 for SRIDIV = 0001B
    or 0010B, else fFSI2 = fSRI. Bits [20:21] */
#define OSEE_TC_SCU_CCUCON0_FSI2(fsi2)\
  ((((OsEE_reg)(fsi2)) & (OsEE_reg)0x3U) << 20U)
/*  FSI Divider Reload Value 10B fFSI = fSRI / 2 for SRIDIV = 0001B
    or 0010B, else fFSI = fSR. Bits [24:25] */
#define OSEE_TC_SCU_CCUCON0_FSI(fsi)\
  ((((OsEE_reg)(fsi)) & (OsEE_reg)0x3U) << 24U)
/*  ADC Clock Selection This bit field defines the clock source that is
    used for the clock fADC of the ADCs. Bits[26:27]*/
#define OSEE_TC_SCU_CCUCON0_ADC(adc)\
  ((((OsEE_reg)(adc)) & (OsEE_reg)0x3U) << 26U)
/*  Clock Selection: fERAY and fFSI. 1B fPLL is used as clock source fsource.
    Bits [28:29] */
#define OSEE_TC_SCU_CCUCON0_CLKSEL(clk)\
  ((((OsEE_reg)(clk)) & (OsEE_reg)0x1U) << 28U)

/** \brief  CCU Clock Control Register 1 */
typedef struct
{
/** \brief [3:0] MultiCAN Divider Reload Value (rw) */
  unsigned int candiv     : 4;
/** \brief [7:4] ERAY Divider Reload Value (rw) */
  unsigned int eraydiv    : 4;
/** \brief [11:8] STM Divider Reload Value (rw) */
  unsigned int stmdiv     : 4;
/** \brief [15:12] GTM Divider Reload Value (rw) */
  unsigned int gtmdiv     : 4;
/** \brief [19:16] Ethernet Divider Reload Value (rw) */
  unsigned int ethdiv     : 4;
/** \brief [23:20] ASCLIN Fast Divider Reload Value (rw) */
  unsigned int asclinfdiv : 4;
/** \brief [27:24] ASCLIN Slow Divider Reload Value (rw) */
  unsigned int asclinsdiv : 4;
/** \brief [29:28] Input Selection (rw) */
  unsigned int insel      : 2;
/** \brief [30:30] Update Request (w) */
  unsigned int up         : 1;
/** \brief [31:31] Lock Status (rh) */
  unsigned int lck        : 1;
} OsEE_tc_SCU_CCUCON1_bits;

/* STM Divider Reload Value. 0001B fSTM = fsource. Bits[8:11] */
#define OSEE_TC_SCU_CCUCON1_STMDIV(stm)\
  ((((OsEE_reg)(stm)) & (OsEE_reg)0x3U) << 8U)
/* GTM Divider Reload Value. 0001B fGTM = fsource. Bits[12:15] */
#define OSEE_TC_SCU_CCUCON1_GTMDIV(gtm)\
  ((((OsEE_reg)(gtm)) & (OsEE_reg)0x3U) << 12U)
/* Input Selection source for the PLL and PLL_ERAY. 01B fOSC0
   is used as clock source. Bits [28:29] */
#define OSEE_TC_SCU_CCUCON1_INSEL(in)\
  ((((OsEE_reg)(in)) & (OsEE_reg)0x1U) << 28U)

/*  CCU0 Init Value */
#if (!defined(OSEE_TC_SCU_CCUCON0_INIT))
#define OSEE_TC_SCU_CCUCON0_INIT\
  (OSEE_TC_SCU_CCUCON0_BAUD1DIV(1U) |\
    OSEE_TC_SCU_CCUCON0_SRI(1U) | OSEE_TC_SCU_CCUCON0_SPB(2U) |\
    OSEE_TC_SCU_CCUCON0_FSI2(2U) | OSEE_TC_SCU_CCUCON0_FSI(2U) |\
    OSEE_TC_SCU_CCUCON0_CLKSEL(1U) /* | OSEE_TC_SCU_CCUCON0_BAUD2DIV(1U) */)
#endif /* !OSEE_TC_SCU_CCUCON0_INIT */

/*  CCU1 Init Value */
#if (!defined(OSEE_TC_SCU_CCUCON1_INIT))
#define OSEE_TC_SCU_CCUCON1_INIT\
  (OSEE_TC_SCU_CCUCON1_STMDIV(OSEE_TC_STMDIV_VALUE) |\
    OSEE_TC_SCU_CCUCON1_GTMDIV(1U) | OSEE_TC_SCU_CCUCON1_INSEL(1U))
#endif /* !OSEE_TC_SCU_CCUCON1_INIT */

/*  CCUCONX bit 30  This bit defined the update for the CCU.
    Please note that setting this bit request a CCU
    update based on all three registers,
    so only one UP bit have to be set.

    1B A new complete parameter set is transferred
    to the CCU. All three registers CCUCON0, 1
    and 5 content is taken by CCU. */
#define OSEE_TC_SCU_CCUCONX_UP ((OsEE_reg)1U << 30U)
#else

/** \brief OSC Control Register */
typedef struct
{
  /** \brief [0:0] \internal Reserved */
  unsigned int          :1;
  /** \brief [1:1] Oscillator for PLL Valid Low Status Bit - PLLLV (rh) */
  unsigned int plllv    :1;
  /** \brief [2:2] Oscillator Watchdog Reset - OSCRES (w) */
  unsigned int oscres   :1;
  /** \brief [3:4] Oscillator Gain Selection - GAINSEL (rw) */
  unsigned int gainsel  :2;
  /** \brief [5:6] Oscillator Mode - MODE (rw) */
  unsigned int mode     :2;
  /** \brief [7:7] Shaper Bypass - SHBY (rw) */
  unsigned int shby     :1;
  /** \brief [8:8] Oscillator for PLL Valid High Status Bit - PLLHV (rh) */
  unsigned int pllhv    :1;
  /** \brief [9:9] Hysteresis Enable (rw) */
  unsigned int hysen    :1;
  /** \brief [10:11] Hysteresis Control (rw) */
  unsigned int hysctl   :2;
  /** \brief [12:13] Amplitude Control (rw) */
  unsigned int ampctl   :2;
  /** \brief [14:15] \internal Reserved */
  unsigned int          :2;
  /** \brief [16:20] OSC Frequency Value - OSCVAL (rw) */
  unsigned int oscval   :5;
  /** \brief [21:22] \internal Reserved */
  unsigned int          :2;
  /** \brief [23:23] Amplitude Regulation Enable - APREN (rw) */
  unsigned int apren    :1;
  /** \brief [24:24] Capacitance 0 Enable - CAP0EN (rw) */
  unsigned int cap0en   :1;
  /** \brief [25:25] Capacitance 1 Enable - CAP1EN (rw) */
  unsigned int cap1en   :1;
  /** \brief [26:26] Capacitance 2 Enable - CAP2EN (rw) */
  unsigned int cap2en   :1;
  /** \brief [27:27] Capacitance 3 Enable - CAP3EN (rw) */
  unsigned int cap3en   :1;
  /** \brief [31:28] \internal Reserved */
  unsigned int          :4;
} OsEE_tc_SCU_OSCCON_bits;

/** \brief System PLL Configuration 0 Register */
typedef struct
{
  /** \brief [1:0] \internal Reserved */
  unsigned int          :2;
  /** \brief [2:2] Modulation Enable - MODEN (rw) */
  unsigned int moden    :1;
  /** \brief [3:8] \internal Reserved */
  unsigned int          :6;
  /** \brief [9:15] N-Divider Value - NDIV (rw) */
  unsigned int ndiv     :7;
  /** \brief [16:16] System PLL Power Saving Mode - PLLPWD (rw) */
  unsigned int pllpwd   :1;
  /** \brief [17:17] \internal Reserved */
  unsigned int          :1;
  /** \brief [18:18] Restart DCO Lock Detection - RESLD (w) */
  unsigned int resld    :1;
  /** \brief [19:23] \internal Reserved */
  unsigned int          :5;
  /** \brief [24:26] P-Divider Value - PDIV (rw) */
  unsigned int pdiv     :3;
  /** \brief [29:27] \internal Reserved */
  unsigned int          :3;
  /** \brief [30:31] Input Selection - INSEL (rw) */
  unsigned int insel    :2;
} OsEE_tc_SYSPLLCON0_bits;

/*  Input Selection
    This bit field defines as clock source for the two PLLs
    (System PLL and Peripheral PLL).
 */
#define OSEE_TC_SCU_SYSPLLCON_INSEL_BACKUP  (0x0U)
#define OSEE_TC_SCU_SYSPLLCON_INSEL_FOSC0   (0x1U)
#define OSEE_TC_SCU_SYSPLLCON_INSEL_SYSCLK  (0x2U)

typedef union {
  OsEE_reg                reg;
  OsEE_tc_SYSPLLCON0_bits bits;
} OsEE_tc_SYSPLLCON0;

#define OSEE_TC_SCU_SYSPLLCON0\
  (*(OsEE_tc_SYSPLLCON0 volatile *)\
    OSEE_TC_SCU_REG_ADDR(OSEE_TC_SCU_PLLCON0_OFF)\
  )

/** \brief System PLL Configuration 1 Register */
typedef struct
{
  /** \brief [0:2] K2-Divider Value - K2DIV (rw) */
  unsigned int k2div  :3;
  /** \brief [3:31] \internal Reserved */
  unsigned int        :29;
} OsEE_tc_SYSPLLCON1_bits;

typedef union {
  OsEE_reg                reg;
  OsEE_tc_SYSPLLCON1_bits bits;
} OsEE_tc_SYSPLLCON1;

#define OSEE_TC_SCU_SYSPLLCON1\
  (*(OsEE_tc_SYSPLLCON1 volatile *)\
    OSEE_TC_SCU_REG_ADDR(OSEE_TC_SCU_PLLCON1_OFF)\
  )

/** \brief System PLL Status Register */
typedef struct
{
  /** \brief [0:0] \internal Reserved */
  unsigned int          :1;
  /** \brief [1:1] System PLL Power-saving Mode Status - PWDSTAT (rh) */
  unsigned int  pwdstat :1;
  /** \brief [2:2] System PLL Lock Status - LOCK (rh) */
  unsigned int  lock    :1;
  /** \brief [3:4] \internal Reserved */
  unsigned int          :2;
  /** \brief [5:5] K2 Divider Ready Status - K2RDY (rh) */
  unsigned int  k2rdy   :1;
  /** \brief [6:6] \internal Reserved */
  unsigned int          :1;
  /** \brief [7:7] Modulation Run - MODRUN (rh) */
  unsigned int  modrun  :1;
  /** \brief [8:31] \internal Reserved */
  unsigned int          :24;
} OsEE_tc_SCU_SYSPLLSTAT_bits;

typedef union {
  OsEE_reg                    reg;
  OsEE_tc_SCU_SYSPLLSTAT_bits bits;
} OsEE_tc_SCU_SYSPLLSTAT;

#define OSEE_TC_SCU_SYSPLLSTAT\
  (*(OsEE_tc_SCU_SYSPLLSTAT volatile *)\
    OSEE_TC_SCU_REG_ADDR(OSEE_TC_SCU_PLLSTAT_OFF)\
  )

/** \brief Peripheral PLL Status Register */
typedef struct
{
  /** \brief [0:0] \internal Reserved */
  unsigned int          :1;
  /** \brief [1:1] Peripheral PLL Power-saving Mode Status - PWDSTAT (rh) */
  unsigned int pwdstat  :1;
  /** \brief [2:2] Peripheral PLL Lock Status - LOCK (rh) */
  unsigned int lock     :1;
  /** \brief [3:3] \internal Reserved */
  unsigned int          :1;
  /** \brief [4:4] K3 Divider Ready Status - K3RDY (rh) */
  unsigned int k3rdy    :1;
  /** \brief [5:5] K2 Divider Ready Status - K2RDY (rh) */
  unsigned int k2rdy    :1;
  /** \brief [6:6] \internal Reserved */
  unsigned int          :1;
  /** \brief [7:31] \internal Reserved */
  unsigned int          :25;
} OsEE_tc_SCU_PERPLLSTAT_bits;

typedef union {
  OsEE_reg                    reg;
  OsEE_tc_SCU_PERPLLSTAT_bits bits;
} OsEE_tc_SCU_PERPLLSTAT;

#define OSEE_TC_SCU_PERPLLSTAT\
  (*(OsEE_tc_SCU_PERPLLSTAT volatile *)\
    OSEE_TC_SCU_REG_ADDR(OSEE_TC_SCU_PLLERAYSTAT_OFF)\
  )

/** \brief Peripheral PLL Configuration 0 Register */
typedef struct
{
  /** \brief [0:0] Divider Bypass - DIVBY (rw) */
  unsigned int divby    :1;
  /** \brief [1:8] \internal Reserved */
  unsigned int          :8;
  /** \brief [9:15] N-Divider Value - NDIV (rw) */
  unsigned int ndiv     :7;
  /** \brief [16:16] Peripheral PLL Power Saving Mode - PLLPWD (rw) */
  unsigned int pllwd    :1;
  /** \brief [17:17] \internal Reserved */
  unsigned int          :1;
  /** \brief [18:18] Restart DCO Lock Detection - RESLD (w) */
  unsigned int resld    :1;
  /** \brief [19:23] \internal Reserved */
  unsigned int          :5;
  /** \brief [24:26] P-Divider Value - PDIV (rw) */
  unsigned int pdiv     :3;
  /** \brief [31:27] \internal Reserved */
  unsigned int          :5;
} OsEE_tc_SCU_PERPLLCON0_bits;

/** \brief Peripheral PLL Configuration 1 Register */
typedef struct
{
  /** \brief [0:2] K2-Divider Value - K2DIV (rw) */
  unsigned int k2div    :3;
  /** \brief [3:7] \internal Reserved */
  unsigned int          :5;
  /** \brief [10:8] K3-Divider Value - K3DIV (rw) */
  unsigned int k3div    :3;
  /** \brief [11:31] \internal Reserved */
  unsigned int          :21;
} OsEE_tc_SCU_PERPLLCON1_bits;

/** \brief CCU Clock Control Register 0 */
typedef struct
{
  /** \brief [0:3] STM Divider Reload Value - STMDIV (rw) */
  unsigned int stmdiv   :4;
  /** \brief [4:7] GTM Divider Reload Value - GTMDIV (rw) */
  unsigned int gtmdiv   :4;
  /** \brief [8:11] SRI Divider Reload Value - SRIDIV (rw) */
  unsigned int sridiv   :4;
  /** \brief [12:14] Low Power Divider Reload Value - LPDIV (rw) */
  unsigned int lpdiv    :3;
  /** \brief [15:15] \internal Reserved */
  unsigned int          :1;
  /** \brief [16:19] SPB Divider Reload Value - SPBDIV (rw) */
  unsigned int spbdiv   :4;
  /** \brief [20:23] BBB Divider Reload Value - BBBDIV (rw) */
  unsigned int bbbdiv   :4;
  /** \brief [24:25] FSI Divider Reload Value - FSIDIV (rw) */
  unsigned int fsidiv   :2;
  /** \brief [26:27] FSI2 Divider Reload Value - FSI2DIV (rw) */
  unsigned int fsi2div  :2;
  /** \brief [28:29] Clock Selection for Source - CLKSEL (rwh) */
  unsigned int clksel   :2;
  /** \brief [30:30] Update Request - UP (w) */
  unsigned int up       :1;
  /** \brief [31:31] Lock Status - LCK (rh) */
  unsigned int lck      :1;
}  OsEE_tc_SCU_CCUCON0_bits;

/** \brief CCU Clock Control Register 1 */
typedef struct
{
  /** \brief [0:3] MCAN Divider Reload Value - MCANDIV (rw) */
  unsigned int mcandiv    :4;
  /** \brief [4:5] Clock Selection for MCAN - CLKSELMCAN (rw) */
  unsigned int clkselmcan :2;
  /** \brief [6:6] \internal Reserved */
  unsigned int            :1;
  /** \brief [7:7] Divider Disable for fPLL1 - PLL1DIVDIS (rw) */
  unsigned int pll1divdis :1;
  /** \brief [8:11] I2C Divider Reload Value - I2CDIV (rw) */
  unsigned int i2cdiv     :4;
  /** \brief [12:15] \internal Reserved */
  unsigned int            :4;
  /** \brief [16:19] MSC Divider Reload Value - MSCDIV (rw) */
  unsigned int mscdiv     :4;
  /** \brief [20:21] Clock Selection for MSC - CLKSELMSC (rw) */
  unsigned int clkselmsc  :2;
  /** \brief [22:23] \internal Reserved */
  unsigned int            :2;
  /** \brief [24:27] QSPI Divider Reload Value - QSPIDIV (rw) */
  unsigned int qspidiv    :4;
  /** \brief [28:29] Clock Selection for QSPI - CLKSELQSPI (rw) */
  unsigned int clkselqspi :2;
  /** \brief [30:30] \internal Reserved */
  unsigned int            :1;
  /** \brief [31:31] Lock Status - LCK (rh) */
  unsigned int lck        :1;
} OsEE_tc_SCU_CCUCON1_bits;
#endif  /* !OSEE_TC_2G */

typedef union {
  OsEE_reg                reg;
  OsEE_tc_SCU_OSCCON_bits bits;
} OsEE_tc_SCU_OSCCON;

/* Command to reset Watchdog Oscillator. Bits[2] */
#define OSEE_TC_SCU_OSCCON_OSCRES ((OsEE_reg)1U << 2U)
/* Default Reset Value for OSCCCON.GAIN Should not be Changed. Bits[3:4] */
#define OSEE_TC_SCU_OSCCON_GAINSEL ((OsEE_reg)3U << 3U)
/* Extern Cristall is 00 mode so this define doesn't change the OSSCON
   Value. Bits[5:6] */
#define OSEE_TC_SCU_OSCCON_MODE(mode)\
  ((((OsEE_reg)(mode)) & (OsEE_reg)0x3U) << 5U)
/* OSCVAL  defines the divider value that generates  the reference clock
 *  that is supervised by the oscillator watchdog.
 *  We want a reference frequency of 2.5
 *  fOSC / (OSCVAL + 1) ~ 2.5Mhz  => OSCVAL = (fOSC / 2.5Mhz) - 1 */
/* TriCore 2G:
 * OSC Frequency Value
 * This bit field defines the divider value that generates the reference clock
 * that is supervised by the oscillator watchdog.
 * fOSCREF = OSCCON.OSCVAL + 1 + 16 MHz. */
#define OSEE_TC_SCU_OSCCON_OSCVAL(oscval)\
  ((((OsEE_reg)(oscval)) & (OsEE_reg)0xFU) << 16U)

#define OSEE_TC_SCU_OSCCON\
  (*(OsEE_tc_SCU_OSCCON volatile *)\
    OSEE_TC_SCU_REG_ADDR(OSEE_TC_SCU_OSCCON_OFF)\
  )

typedef union {
  OsEE_reg                  reg;
  OsEE_tc_SCU_CCUCON0_bits  bits;
} OsEE_tc_SCU_CCUCON0;

#define OSEE_TC_SCU_CCUCON0\
  (*(OsEE_tc_SCU_CCUCON0 volatile *)\
    OSEE_TC_SCU_REG_ADDR(OSEE_TC_SCU_CCUCON0_OFF)\
  )

typedef union {
  OsEE_reg                  reg;
  OsEE_tc_SCU_CCUCON1_bits  bits;
} OsEE_tc_SCU_CCUCON1;

#define OSEE_TC_SCU_CCUCON1\
  (*(OsEE_tc_SCU_CCUCON1 volatile *)\
    OSEE_TC_SCU_REG_ADDR(OSEE_TC_SCU_CCUCON1_OFF)\
  )

/** @brief  Return fSOURCE in HZ. **/
OsEE_reg osEE_tc_get_fsource(void);

#if (!defined(OSEE_TC_2G))
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_conf_clock_ctrl(void) {
/* N.B The following initialization order is not casual */
/* Core Divisors */
#if (defined(OSEE_TC_SCU_CCUCON6_INIT))
  OSEE_TC_SCU_REG(OSEE_TC_SCU_CCUCON6_OFF) = OSEE_TC_SCU_CCUCON6_INIT;
#endif /* OSEE_TC_SCU_CCUCON6_INIT */
#if (defined(OSEE_TC_SCU_CCUCON7_INIT))
  OSEE_TC_SCU_REG(OSEE_TC_SCU_CCUCON7_OFF) = OSEE_TC_SCU_CCUCON7_INIT;
#endif /* OSEE_TC_SCU_CCUCON7_INIT */
#if (defined(OSEE_TC_SCU_CCUCON8_INIT))
  OSEE_TC_SCU_REG(OSEE_TC_SCU_CCUCON8_OFF) = OSEE_TC_SCU_CCUCON8_INIT;
#endif /* OSEE_TC_SCU_CCUCON8_INIT */

/* BUS Divisors */
/* Configure CCUCON0 */
  OSEE_TC_SCU_CCUCON0.reg = OSEE_TC_SCU_CCUCON0_INIT;
#if (defined(OSEE_TC_SCU_CCUCON5_INIT))
  OSEE_TC_SCU_REG(OSEE_TC_SCU_CCUCON5_OFF) = OSEE_TC_SCU_CCUCON5_INIT;
#endif /* OSEE_TC_SCU_CCUCON5_INIT */
/* Configure CCUCON1 and Update CCU 0, 1 & 5. Forced INSEL to 1 even for
   external configuration, otherwise PLL initialization won't work. */
  OSEE_TC_SCU_CCUCON1.reg = OSEE_TC_SCU_CCUCON1_INIT |
    OSEE_TC_SCU_CCUCON1_INSEL(1U) | OSEE_TC_SCU_CCUCONX_UP;

#if (defined(OSEE_TC_SCU_CCUCON2_INIT))
  /* CCU2 has it's own update bit */
  OSEE_TC_SCU_REG(OSEE_TC_SCU_CCUCON2_OFF) =
    OSEE_TC_SCU_CCUCON2_INIT | OSEE_TC_SCU_CCUCONX_UP;
#endif /* OSEE_TC_SCU_CCUCON2_INIT */
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_conf_osc_ctrl(void)
{
  /*
   * Default System Oscillator Configuration
   * MODE:    0   -> External Crystal
   */
  OSEE_TC_SCU_OSCCON.reg = OSEE_TC_SCU_OSCCON_OSCRES |
    OSEE_TC_SCU_OSCCON_GAINSEL | OSEE_TC_SCU_OSCCON_MODE(0U) |
    OSEE_TC_SCU_OSCCON_OSCVAL((OSEE_TC_BOARD_FOSC / 2500000U) - 1U);

  while (OSEE_TC_SCU_OSCCON.bits.plllv == 0U) {
    ; /* Oscillator not too low */
  }

  while (OSEE_TC_SCU_OSCCON.bits.pllhv == 0U) {
    ; /* Oscillator not too high */
  }
}

/** @brief  Set PLL frequency (fSOURCE). This function accept fpll HZ **/
void osEE_tc_set_pll_fsource(OsEE_reg fpll);

/** \brief Macro to get the STM divider */
#define OSEE_SCU_HW_FSTM_DIV (OSEE_TC_SCU_CCUCON1.bits.stmdiv)

#else

/** \brief Macro to get the STM divider */
#define OSEE_SCU_HW_FSTM_DIV (OSEE_TC_SCU_CCUCON0.bits.stmdiv)

/** \brief Structure definition for the BMHD
 *    Based on BMI and start address respective CRC and Inverted CRC values has
 *    to be calculated and updated.
 *    CRC-32 polynomial as defined in the IEEE 802.3 standard is used to
 *    generate the CRC value. The CRC algorithm treats input data as a
 *    stream of bits.
 *    Eg. To calculate the CRC data has to given in big-endian order.
 *
 *    For the below values:
 *
 *    bmi    = 0x00FE
 *    bmhdid = 0xB359
 *    stad   = 0xA0002020
 *
 * CRC calculation:
 *    Input        = 0xB35900FEA0002020
 *    CRC value    = 0x9F93511A
 *    CRC Inverted = 0x606CAEE5
 */
typedef struct
{
/** \brief 0x000: Boot Mode Index (BMI)*/
  uint16_t  bmi;
/** \brief 0x002: Boot Mode Header ID (CODE) = B359H*/
  uint16_t  bmhdid;
/** \brief 0x004: User Code start address*/
  uint32_t  stad;
/** \brief 0x008: Check Result for the BMI Header (offset 000H - 007H)*/
  uint32_t  crc;
/** \brief 0x00C: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
  uint32_t  crcInv;
/** \brief 0x010: Reserved area (60 words) till the offset 0x100*/
  uint32_t  reserved0[60];
/** \brief 0x100: Password protection (8 words) till the offset 0x120 */
  uint32_t  pw[8];
/** \brief 0x120: Reserved area (52 words) till the offset 0x1F0*/
  uint32_t  reserved1[52];
/** \brief 0x1F0: 32-bit CODE, (always same)*/
  uint32_t  confirmation;
} OsEE_tc_ssw_bmhd;

#endif /* !OSEE_TC_2G */

#if (defined(__cplusplus))
}
#endif

#endif /* OSEE_TC_SYSTEM_H */
