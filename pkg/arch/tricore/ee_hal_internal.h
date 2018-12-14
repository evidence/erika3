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

/** \file   ee_hal_internal.h
 *  \brief  HAL internal.
 *
 *  This files contains all HAL Internals for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#ifndef OSEE_HAL_INTERNAL_H
#define OSEE_HAL_INTERNAL_H

/*=============================================================================
                                  Inclusions
 ============================================================================*/
#include "ee_cfg.h"
#include "ee_platform_types.h"
#include "ee_utils.h"
#include "ee_compiler.h"
#include "ee_hal.h"
#include "ee_tc_csfr.h"
#include "ee_hal_internal_types.h"
#include "ee_std_change_context.h"
#include "ee_kernel_types.h"
#include "ee_get_kernel_and_core.h"
#if (!defined(OSEE_TRICORE_ILLD))
#include "ee_tc_system.h"
#endif
#include "ee_hal_mc.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/*=============================================================================
                          Stack utilities
 ============================================================================*/
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_set_SP(OsEE_stack * sp)
{
  __asm__ volatile ("mov.aa %%SP, %0" : : "a"(sp) : "memory");
}

/*=============================================================================
                          ERIKA's Context utilities
 ============================================================================*/

/* Used to clean bits [6:0] corresponding to PSW.CDC (call depth counter) */
#define OSEE_TC_PSW_CDC_CLEAN_MASK     (0xFFFFFF80U)

OSEE_STATIC_INLINE OsEE_addr OSEE_ALWAYS_INLINE osEE_tc_get_RA(void)
{
  OsEE_addr ra;
  /* gets the current return address */
  __asm__ volatile ("mov.aa %0, %%a11" : "=a"(ra) : : "memory");
  return ra;
}


/* The type of the parameter ra generates an explicit MISRA violation.
   - Changing ra to a pointer to a void (*)(void) function generates 
     another MISRA violation, because the return function programmed 
     in the context has type void(*)(const struct OsEE_TDB_tag*).
   - Changing ra to type void(*)(const struct OsEE_TDB_tag*) is not 
     the best option, because we would need to change the OsEE_CTX ra 
     member to something which is in general not of that type (the return
     address is a pointer to a code location.
   Therefore, we chose to use OsEE_addr, which is not the best option,
   but it minimizes the MISRA violation to a single documented point.
*/
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_set_RA(OsEE_addr ra)
{
  /* sets the return address */
  __asm__ volatile ("mov.aa %%a11, %0" : : "a"(ra) : "memory");
}

/*=============================================================================
                        CSA handling utilities
 ============================================================================*/

/** Convert context link to context pointer
 * \param[in] l_csa link to context save area
 * \return csa address pointer
 */
OSEE_STATIC_INLINE OsEE_csa * OSEE_ALWAYS_INLINE
  osEE_tc_csa_link_to_pointer(OsEE_csa_link l_csa)
{
  OsEE_reg tmp_csa_addr;
  tmp_csa_addr = ((OsEE_reg)l_csa.bits.pcxs << 28U) |
    ((OsEE_reg)l_csa.bits.pcxo << 6U);
  return (OsEE_csa *)(tmp_csa_addr);
}

/* Returns the first CSA in the Free Context List */
OSEE_STATIC_INLINE OsEE_csa_link OSEE_ALWAYS_INLINE osEE_tc_csa_get_fcx(void)
{
  OsEE_csa_link head;
  head.reg = osEE_tc_get_csfr(OSEE_CSFR_FCX);
  return head;
}

/* Set the first CSA in the Free Context List */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_csa_set_fcx(OsEE_csa_link l_csa)
{
  osEE_tc_set_csfr(OSEE_CSFR_FCX, l_csa.reg);
}

/* Returns the first CSA in the Previous Context List */
OSEE_STATIC_INLINE OsEE_csa_link OSEE_ALWAYS_INLINE osEE_tc_csa_get_pcxi(void)
{
  OsEE_csa_link head;
  head.reg = osEE_tc_get_csfr(OSEE_CSFR_PCXI);
  return head;
}

/* Set the first CSA in the Previous Context List */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_csa_set_pcxi(OsEE_csa_link l_csa)
{
  osEE_tc_set_csfr(OSEE_CSFR_PCXI, l_csa.reg);
}

/* Returns the link work of a given CSA 'at' */
OSEE_STATIC_INLINE OsEE_csa_link OSEE_ALWAYS_INLINE
  osEE_tc_csa_get_next(OsEE_csa_link l_csa_at)
{
  OsEE_csa_link     l_next;
  const OsEE_csa * const  p_csa = osEE_tc_csa_link_to_pointer(l_csa_at);
  if (p_csa != NULL) {
    l_next = p_csa->l_next;
  } else {
    l_next.reg = 0U;
  }
  return l_next;
}

/* Sets the link word of a given CSA 'at' to 'link' */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_csa_set_next(OsEE_csa_link l_csa_at, OsEE_csa_link l_next)
{
  OsEE_csa * const  p_csa = osEE_tc_csa_link_to_pointer(l_csa_at);
  if (p_csa != NULL) {
    p_csa->l_next = l_next;
  }
}

/*=============================================================================
                        Interrupt handling utilities
 ============================================================================*/
/* Functions to Access ICR register */
OSEE_STATIC_INLINE OsEE_icr OSEE_ALWAYS_INLINE osEE_tc_get_icr(void)
{
  OsEE_icr icr;
  icr.reg = osEE_tc_get_csfr(OSEE_CSFR_ICR);
  return icr;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_set_icr(OsEE_icr icr)
{
  osEE_tc_set_csfr(OSEE_CSFR_ICR, icr.reg);
}

OSEE_STATIC_INLINE OsEE_bool OSEE_ALWAYS_INLINE osEE_hal_is_enabledIRQ(void)
{
  return (osEE_tc_get_icr().bits.ie != 0U)? OSEE_TRUE: OSEE_FALSE;
}

/* Disable Interrupts */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_hal_disableIRQ(void)
{
    __asm__ volatile ("disable" : : : "memory");
}

/* Enable Interrupts */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_hal_enableIRQ(void)
{
  __asm__ volatile ("enable" : : : "memory");
}

/* Suspend/Resume Interrupts */
OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE osEE_hal_suspendIRQ(void)
{
  OsEE_icr icr = osEE_tc_get_icr();
  osEE_hal_disableIRQ();
  return icr.reg;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_hal_resumeIRQ(OsEE_reg flags)
{
  OsEE_icr icr;
  icr.reg = flags;
  osEE_tc_set_icr(icr);
}

OSEE_STATIC_INLINE FUNC(uint8_t, OS_CODE) OSEE_ALWAYS_INLINE
OSEE_ISR2_VIRT_TO_HW_PRIO(TaskPrio virt_prio)
{
  return (uint8_t) (((virt_prio) & (~OSEE_ISR2_PRIO_BIT)) + 1U) ;
}

#define OSEE_ISR2_MAX_HW_PRIO\
  OSEE_ISR2_VIRT_TO_HW_PRIO(OSEE_ISR2_MAX_PRIO)

/* We always use virtual priorities */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_hal_set_ipl(TaskPrio virt_prio)
{
  OsEE_icr icr  = osEE_tc_get_icr();
  icr.bits.ccpn = (virt_prio < OSEE_ISR2_PRIO_BIT)?
    ((uint8_t)OSEE_ISR_UNMASKED):
    ((uint8_t)OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio));

  osEE_tc_set_icr(icr);
}

OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE
  osEE_hal_prepare_ipl(OsEE_reg flags, TaskPrio virt_prio)
{
  OsEE_reg ret_flags;
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    ret_flags = OSEE_B_SET(flags, 8U, 0U, OSEE_ISR_UNMASKED);
  } else {
    ret_flags =
      OSEE_B_SET(flags, 8U, 0U, OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio));
  }
  return ret_flags;
}

#if (defined(OSEE_RQ_MULTIQUEUE))
OSEE_STATIC_INLINE MemSize OSEE_ALWAYS_INLINE
  osEE_hal_get_msb(OsEE_rq_mask mask)
{
#if (OSEE_RQ_PRIO_NUM <= 32U)
  int32_t nbits = 31 - __builtin_clz(mask);
  return (MemSize)(nbits);
#elif (OSEE_RQ_PRIO_NUM <= 64U)
  int32_t nbits = 63 - __builtin_clzll(mask);
  return (MemSize)(nbits);
#else
#error TriCore ISA cannot handle a bitmask long OSEE_RQ_PRIO_NUM
#endif
}
#endif /* OSEE_RQ_MULTIQUEUE */

/*=============================================================================
                    HAL For Primitives Atomicity
 ============================================================================*/

/* Called as _first_ function of a primitive that can be called from within
 * an IRQ and from within a task. */
OSEE_STATIC_INLINE OsEE_reg OSEE_ALWAYS_INLINE
  osEE_hal_begin_nested_primitive(void)
{
  OsEE_icr icr = osEE_tc_get_icr();

  if (icr.bits.ccpn < OSEE_ISR2_MAX_HW_PRIO) {
    OsEE_icr icr_temp = icr;
    /* Set new CCPN value */
    icr_temp.bits.ccpn = OSEE_ISR2_MAX_HW_PRIO;
    osEE_tc_set_icr(icr_temp);
  }

  return icr.reg;
}

/* Called as _last_ function of a primitive that can be called from
 * within an IRQ or a task. */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_hal_end_nested_primitive(OsEE_reg flags)
{
  OsEE_icr icr = osEE_tc_get_icr();
  if (icr.reg != flags) {
    icr.reg = flags;
    osEE_tc_set_icr(icr);
  }
}

/*=============================================================================
                Services Requests Node (SRN) Utility Macros
 ============================================================================*/
#define OSEE_TC_SRC_BASE                  (0xF0038000U)

#define OSEE_TC_SRC_REG(off)\
  (*(OsEE_reg volatile *)(OSEE_TC_SRC_BASE + (off)))

#if (!defined(OSEE_TC_2G))
#define OSEE_TC_SRN_TOS_MASK              ((OsEE_reg)(0x3U))
#else
#define OSEE_TC_SRN_TOS_MASK              ((OsEE_reg)(0x7U))
#endif /* !OSEE_TC_2G */

#define OSEE_TC_SRN_PRIORITY(intvec)      (((OsEE_reg)(intvec)) & \
  (OsEE_reg)0x7FU)
#define OSEE_TC_SRN_ENABLE                ((OsEE_reg)1U << 10U)
#define OSEE_TC_SRN_TYPE_OF_SERVICE(tos)  (((OsEE_reg)(tos) & \
  OSEE_TC_SRN_TOS_MASK) << 11U)
#define OSEE_TC_SRN_CLEAR_REQUEST         ((OsEE_reg)1U << 25U)
#define OSEE_TC_SRN_SET_REQUEST           ((OsEE_reg)1U << 26U)
#define OSEE_TC_SRN_STICKY_CLEAR          ((OsEE_reg)1U << 30U)

#if (!defined(OSEE_TC_2G))
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_conf_src(CoreIdType tos, OsEE_reg src_offset, OsEE_prio prio) {
/*
 *  Service Request Configuration
 *  [0..7] SRPN = Priority
 *  [10] Service Request enable
 *  [11..12] Type Of Service (means which CPU or DMA will handle it)
 */
  OSEE_TC_SRC_REG(src_offset) = OSEE_TC_SRN_TYPE_OF_SERVICE(tos) |
      OSEE_TC_SRN_ENABLE | OSEE_TC_SRN_PRIORITY(prio);
}
#else
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_tc_conf_src(CoreIdType tos, OsEE_reg src_offset, OsEE_prio prio) {
/*
 *  Service Request Configuration
 *  [0..7] SRPN = Priority
 *  [10] Service Request enable
 *  [11..13] Type Of Service (means which CPU or DMA will handle it)
 */
 /* TOS Rule for TC3nX */
 /* Type of Service Control
    The TOS bit field configuration maps a Service Request to an Interrupt
    Service Provider:
    0H CPU0 service is initiated
    1H DMA service is initiated
    2H CPU1 service is initiated
    3H CPU2 service is initiated
    4H CPU3 service is initiated
    5H CPU4 service is initiated
    6H CPU5 service is initiated
    7H PDMA service is initiated

    Note: In products where PDMA or CPUx is not implemented, the related TOS
      encoding will not be used and treated as RESERVED.
 */
#if (!defined(OSEE_SINGLECORE))
  OsEE_reg tos_num;
  if ((tos == OS_CORE_ID_0)
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
    || (tos == OS_CORE_ID_6)
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */
  ) {
    tos_num = (OsEE_reg)tos;
  } else {
    tos_num = (OsEE_reg)tos + 1U;
  }
#else
  OsEE_reg const tos_num = (OsEE_reg)OS_CORE_ID_0;
  /* Touch unused parameter */
  (void)tos;
#endif /* !OSEE_SINGLECORE */

  OSEE_TC_SRC_REG(src_offset) = OSEE_TC_SRN_TYPE_OF_SERVICE(tos_num) |
    OSEE_TC_SRN_ENABLE | OSEE_TC_SRN_PRIORITY(prio);
}
#endif /* !OSEE_TC_2G */

/*=============================================================================
                              Start-up and ISR2
 ============================================================================*/
#if (defined(OSEE_HAS_SYSTEM_TIMER))
extern void osEE_tc_initialize_system_timer(OsEE_TDB * p_tdb);
#endif /* OSEE_HAS_SYSTEM_TIMER */

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_HAL_INTERNAL_H */
