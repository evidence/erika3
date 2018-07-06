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

#if (!defined(OSEE_HAL_INTERNAL_H))
#define OSEE_HAL_INTERNAL_H
/*==============================================================================
                    Arch dependent Configuration Switches
 =============================================================================*/

/* Used to override default definition of osEE_hal_get_msb,
   in ee_std_change_context.h that is not inlined */
#define OSEE_GET_MSB_INLINE OSEE_STATIC_INLINE


#include "ee_platform_types.h"
#include "ee_utils.h"
#include "ee_hal.h"
#include "ee_hal_internal_types.h"
#include "ee_std_change_context.h"
#include "ee_kernel_types.h"
#if (defined(OSEE_AARCH64_SOC))
#include "ee_aarch64_gic.h"
#endif /* OSEE_AARCH64_SOC */

/*==============================================================================
                          Macros & Inline Functions
 =============================================================================*/

OSEE_STATIC_INLINE void osEE_aarch64_isb( void ) {
  __asm__ volatile ("isb\n\t");
}

OSEE_STATIC_INLINE OsEE_reg osEE_aarch64_DAIF( void ) {
  OsEE_reg daif;
  OSEE_AARCH64_MRS(daif,daif);
  /* __asm__ volatile("mrs %0, daif\n\t" : "=&r"(daif)); */
  return daif;
}

OSEE_STATIC_INLINE OsEE_reg osEE_aarch64_NZCV( void ) {
  OsEE_reg nzcv;
  OSEE_AARCH64_MRS(nzcv,nzcv);
  return nzcv;
}

OSEE_STATIC_INLINE OsEE_reg osEE_aarch64_CurrentEL( void ) {
  OsEE_reg CurrentEL;
  OSEE_AARCH64_MRS(CurrentEL,CurrentEL);
  /* EL is set starting from bit 2 */
  return (CurrentEL >> 2);
}

OSEE_STATIC_INLINE OsEE_reg osEE_aarch64_SPSel( void ) {
  OsEE_reg SPSel;
  OSEE_AARCH64_MRS(SPSel,SPSel);
  return SPSel;
}

#define OSEE_AARCH64_SCTLR_SA0  OSEE_BIT(OsEE_reg,4U)
#define OSEE_AARCH64_SCTLR_SA   OSEE_BIT(OsEE_reg,3U)
#define OSEE_AARCH64_SCTLR_A    OSEE_BIT(OsEE_reg,1U)

OSEE_STATIC_INLINE OsEE_reg osEE_aarch64_SCTLR(void) {
  OsEE_reg sctlr_el1;
  OSEE_AARCH64_MRS(sctlr_el1,sctlr_el1);
  return sctlr_el1;
}

OSEE_STATIC_INLINE void osEE_aarch64_set_SCTLR(OsEE_reg sctlr_el1) {
  OSEE_AARCH64_MSR(sctlr_el1,sctlr_el1);
}

/*==============================================================================
                        Interrupt handling utilities
 =============================================================================*/

#define OSEE_AARCH64_I_DAIF             OSEE_BIT(OsEE_reg,7)
#define OSEE_AARCH64_I_DAIF_NOT_SET(f)  (((f) & OSEE_AARCH64_I_DAIF) == 0U)

OSEE_STATIC_INLINE OsEE_bool osEE_hal_is_enabledIRQ( void )
{
  OsEE_reg flags;
  __asm__ volatile("mrs %0, daif\n\t" : "=&r"(flags));
  return OSEE_AARCH64_I_DAIF_NOT_SET(flags);
}

/* Disable/Enable Interrupts */
OSEE_STATIC_INLINE void osEE_hal_disableIRQ( void )
{
  __asm__ volatile("msr daifset, #2\n\t");
}

OSEE_STATIC_INLINE void osEE_hal_enableIRQ( void )
{
  __asm__ volatile("msr daifclr, #2\n\t");
}

/* Suspend/Resume Interrupts */
OSEE_STATIC_INLINE OsEE_reg osEE_hal_suspendIRQ(void)
{
  OsEE_reg flags;
  __asm__ volatile("mrs %0, daif\n\t" : "=&r"(flags));
  osEE_hal_disableIRQ();
  return flags;
}

OSEE_STATIC_INLINE void osEE_hal_resumeIRQ(OsEE_reg flags)
{
  if (OSEE_AARCH64_I_DAIF_NOT_SET(flags)) {
    osEE_hal_enableIRQ();
  }
}

/* Max number of distinct priorities implemented in this GIC
  (one priority is the TASK level, so Interrupts off this priority won't
   trigger) */
#if (defined(OSEE_GIC_HAS_MAX_NUM_PRIO_DISCOVERY))
extern OsEE_isr_prio osEE_gic_max_num_prio;
#define OSEE_GIC_MAX_NUM_PRIO osEE_gic_max_num_prio
#else
#if (!defined(OSEE_GIC_MAX_NUM_PRIO))
#define OSEE_GIC_MAX_NUM_PRIO (16U)
#endif /* OSEE_GIC_MAX_NUM_PRIO */
#endif /* OSEE_GIC_HAS_MAX_NUM_PRIO_DISCOVERY */

#if (!defined(OSEE_ISR2_MAX_PRIO)) && (defined(OSEE_API_DYNAMIC))
#define OSEE_ISR2_MAX_PRIO  (OSEE_ISR2_PRIO_BIT + OSEE_GIC_MAX_NUM_PRIO/2U +1U)
#endif /* !OSEE_ISR2_MAX_PRIO && OSEE_API_DYNAMIC */

#define OSEE_GIC_PRIO_UNMASKED    (0xFFU)

/* The Interrupt Controller uses a certain amount of the 8 available bits to
   handle interrupt priorities. These bits are always the most significants of
   the priority byte. So if the GIC handles 16 priorities, it uses the 4 msb;
   if it handles 32 priorities, it uses the 5 msb.
   This means that the logic virtual ISR priority value have to be left-shifted
   of 4 or 3 positions respectively, that is 8 - log2(num_prio) =>
   using int of 32 bits  8 - (31 - CLZ(num_prio)) => CLZ(num_prio) - 23.
   Or more simply is like multiply by 16 and 8 respectively that is
   (256 / num_prio).
 */
OSEE_STATIC_INLINE OsEE_isr_prio osEE_isr2_virt_to_hw_prio(TaskPrio virt_prio) {
  OsEE_isr_prio const hw_prio = (OsEE_isr_prio)(
    ((OSEE_GIC_MAX_NUM_PRIO - 1U) - ((virt_prio & (~OSEE_ISR2_PRIO_BIT)) + 1U))
    * (256U/OSEE_GIC_MAX_NUM_PRIO)
    /* << (__builtin_clz(OSEE_GIC_MAX_NUM_PRIO) - 23U) */
  );

  return hw_prio;
}

#if (!defined(OSEE_GIC_BASE))
/* GIC base address for NVIDIA TEGRA X1 */
#define OSEE_GIC_BASE (0x50040000U)
#endif /* !OSEE_GICC_BASE */

#if (!defined(OSEE_GICD_OFFSET))
#define OSEE_GICD_OFFSET      (0x1000U)
#endif /* OSEE_GICD_OFFSET */
#if (!defined(OSEE_GICC_OFFSET))
#define OSEE_GICC_OFFSET      (0x2000U)
#endif /* OSEE_GICC_OFFSET */
#if (!defined(OSEE_GICH_OFFSET))
#define OSEE_GICH_OFFSET      (0x4000U)
#endif /* OSEE_GICH_OFFSET */
#if (!defined(OSEE_GICV_OFFSET))
#define OSEE_GICV_OFFSET      (0x6000U)
#endif /* OSEE_GICV_OFFSET */

/* GICD and GICC base addresses */
#define OSEE_GICD_BASE        (OSEE_GIC_BASE + OSEE_GICD_OFFSET)
#define OSEE_GICC_BASE        (OSEE_GIC_BASE + OSEE_GICC_OFFSET)

#define OSEE_GICD_GROUP0      (0x00U)
#define OSEE_GICD_GROUP1      (0x01U)

/*******************************************************************************
                GIC Distributor interface general definitions
 ******************************************************************************/
/* Constants to categorise interrupts */
#define OSEE_GIC_MIN_SGI_ID   (0U)
#define OSEE_GIC_MIN_PPI_ID   (16U)
#define OSEE_GIC_MIN_SPI_ID   (32U)

/* Constant to indicate a spurious interrupt in all GIC versions */
#define OSEE_GIC_SPURIOUS_ISR (0x3ffU) /* 1023 */

/*******************************************************************************
 * GIC Distributor interface register offsets that are common to GICv3 & GICv2
 ******************************************************************************/
#define OSEE_GICD_CTLR        (0x0000U)
#define OSEE_GICD_TYPER       (0x0004U)
#define OSEE_GICD_IIDR        (0x0008U)
#define OSEE_GICD_IGROUPR     (0x0080U)
#define OSEE_GICD_ISENABLER   (0x0100U)
#define OSEE_GICD_ICENABLER   (0x0180U)
#define OSEE_GICD_ISPENDR     (0x0200U)
#define OSEE_GICD_ICPENDR     (0x0280U)
#define OSEE_GICD_ISACTIVER   (0x0300U)
#define OSEE_GICD_ICACTIVER   (0x0380U)
#define OSEE_GICD_IPRIORITYR  (0x0400U)
#define OSEE_GICD_ITARGETSR   (0x0800U)
#define OSEE_GICD_ICFGR       (0x0C00U)
#define OSEE_GICD_NSACR       (0x0E00U)

/* GICD_CTLR bit definitions */
#define OSEE_GICD_CTLR_ENABLE_G0_SHIFT  (0U)
#define OSEE_GICD_CTLR_ENABLE_G0_MASK   (0x1U)
#define OSEE_GICD_CTLR_ENABLE_G0_BIT    (1U << OSEE_GICD_CTLR_ENABLE_G0_SHIFT)

#define OSEE_GICD_CTLR_ENABLE_G1_SHIFT  (1U)
#define OSEE_GICD_CTLR_ENABLE_G1_MASK   (0x2U)
#define OSEE_GICD_CTLR_ENABLE_G1_BIT    (1U << OSEE_GICD_CTLR_ENABLE_G1_SHIFT)

#define OSEE_GICD_IGROUPR_SHIFT     (5U)
#define OSEE_GICD_ISENABLER_SHIFT   (5U)
#define OSEE_GICD_ICENABLER_SHIFT   OSEE_GICD_ISENABLER_SHIFT
#define OSEE_GICD_ISPENDR_SHIFT     (5U)
#define OSEE_GICD_ICPENDR_SHIFT     OSEE_GICD_ISPENDR_SHIFT
#define OSEE_GICD_ISACTIVER_SHIFT   (5U)
#define OSEE_GICD_ICACTIVER_SHIFT   OSEE_GICD_ISACTIVER_SHIFT
#define OSEE_GICD_ITARGETSR_SHIFT   (2U)
#define OSEE_GICD_ICFGR_SHIFT       (4U)
#define OSEE_GICD_NSACR_SHIFT       (4U)

/* GICD_TYPER shifts and masks */
#define OSEE_GICD_TYPER_IT_LINES_NO_SHIFT (0U)
#define OSEE_GICD_TYPER_IT_LINES_NO_MASK  (0x1FU)

#define OSEE_GIC_TARGET_CPU_MASK          (0xFFU)

/*******************************************************************************
 * GIC Distributor interface register constants that are common to GICv3 & GICv2
 ******************************************************************************/
#define OSEE_GIC_PIDR2_ARCH_REV_SHIFT (4U)
#define OSEE_GIC_PIDR2_ARCH_REV_MASK  (0x0FU)

/* GICv3 revision as reported by the PIDR2 register */
#define OSEE_GIC_ARCH_REV_GICV3       (0x03U)
/* GICv2 revision as reported by the PIDR2 register */
#define OSEE_GIC_ARCH_REV_GICV2       (0x02U)

OSEE_STATIC_INLINE uint32_t osEE_gicd_read_igroupr(ISRSource source_id)
{
  unsigned int n = source_id >> OSEE_GICD_IGROUPR_SHIFT;
  return osEE_mmio_read32(OSEE_GICD_BASE + OSEE_GICD_IGROUPR + (n << 2));
}

OSEE_STATIC_INLINE void
  osEE_gicd_write_igroupr(ISRSource source_id, uint32_t val)
{
  unsigned int n = source_id >> OSEE_GICD_IGROUPR_SHIFT;
  return osEE_mmio_write32(OSEE_GICD_BASE + OSEE_GICD_IGROUPR + (n << 2), val);
}

OSEE_STATIC_INLINE uint32_t osEE_gicd_get_igroupr(ISRSource source_id)
{
  uint32_t bit = source_id & ((1U << OSEE_GICD_IGROUPR_SHIFT) - 1U);
  uint32_t reg = osEE_gicd_read_igroupr(source_id);

  return (reg >> bit) & 0x1U;
}

OSEE_STATIC_INLINE void osEE_gicd_set_igroupr(ISRSource source_id)
{
  uint32_t bit = source_id & ((1U << OSEE_GICD_IGROUPR_SHIFT) - 1U);
  uint32_t reg = osEE_gicd_read_igroupr(source_id);

  osEE_gicd_write_igroupr(source_id, (reg | (1U << bit)));
}

OSEE_STATIC_INLINE void osEE_gic_v2_set_hw_prio(ISRSource source_id,
  uint8_t hw_prio_mask)
{
  osEE_mmio_write8(OSEE_GICD_BASE + OSEE_GICD_IPRIORITYR + source_id,
    hw_prio_mask);
}

OSEE_STATIC_INLINE void osEE_gic_v2_enable_irq(ISRSource source_id) {
  unsigned bit = source_id & ((1U << OSEE_GICD_ISENABLER_SHIFT) - 1U);
  unsigned reg_offset = ((source_id >> OSEE_GICD_ISENABLER_SHIFT) << 2U);
  osEE_mmio_write32(OSEE_GICD_BASE + OSEE_GICD_ISENABLER + reg_offset,
    (1U << bit));
}

OSEE_STATIC_INLINE TaskPrio osEE_gic_v2_read_hw_prio_isr(ISRSource source_id)
{
  return osEE_mmio_read8(OSEE_GICD_BASE + OSEE_GICD_IPRIORITYR + source_id);
}

OSEE_STATIC_INLINE TaskPrio osEE_gic_v2_read_virt_prio_isr(ISRSource source_id)
{
  return (OSEE_GIC_MAX_NUM_PRIO - 1U) -
    (osEE_gic_v2_read_hw_prio_isr(source_id)/(256U/OSEE_GIC_MAX_NUM_PRIO));
}

OSEE_STATIC_INLINE uint32_t osEE_gic_v2_read_isenabler(ISRSource source_id)
{
  unsigned reg_offset = ((source_id >> OSEE_GICD_ISENABLER_SHIFT) << 2U);
  return osEE_mmio_read32(OSEE_GICD_BASE + OSEE_GICD_ISENABLER + reg_offset);
}

OSEE_STATIC_INLINE OsEE_bool osEE_gic_v2_is_enabled_irq(ISRSource source_id)
{
  unsigned const bit = source_id & ((1U << OSEE_GICD_ISENABLER_SHIFT) - 1U);
  uint32_t const isenabler = osEE_gic_v2_read_isenabler(source_id);
  return (OsEE_bool) ((isenabler & (1U << bit)) != 0U);
}

/*******************************************************************************
                      GICD ITARGETSR Helper Functions
 ******************************************************************************/
OSEE_STATIC_INLINE OsEE_core_id osEE_gic_v2_read_itargetsr(ISRSource source_id)
{
  OsEE_reg const addr = OSEE_GICD_BASE + OSEE_GICD_ITARGETSR + source_id;
  return osEE_mmio_read8(addr);
}

OSEE_STATIC_INLINE void osEE_gic_v2_set_itargetsr(ISRSource source_id,
  OsEE_core_id target_cpu)
{
  OsEE_reg const addr = OSEE_GICD_BASE + OSEE_GICD_ITARGETSR + source_id;
  osEE_mmio_write8(addr, target_cpu);
}

OSEE_STATIC_INLINE OsEE_core_id osEE_gic_v2_get_cpuif_mask(void)
{
  return osEE_gic_v2_read_itargetsr(0U);
}

OSEE_STATIC_INLINE uint32_t osEE_gic_v2_read32_itargetsr(ISRSource source_id) {
  unsigned const reg_offset = (source_id >> OSEE_GICD_ITARGETSR_SHIFT) << 2U;
  OsEE_reg const addr = OSEE_GICD_BASE + OSEE_GICD_ITARGETSR + reg_offset;
  return osEE_mmio_read32(addr);
}

OSEE_STATIC_INLINE void osEE_gic_v2_write32_itargetsr(ISRSource source_id) {
   OsEE_core_id const curr_core_mask = osEE_gic_v2_get_cpuif_mask();
  unsigned const reg_offset = (source_id & ~OSEE_GIC_TARGET_CPU_MASK);
  uint32_t const itargetisr_mask =
    (curr_core_mask) << (source_id & OSEE_GIC_TARGET_CPU_MASK);

  osEE_mmio_write32(OSEE_GICD_BASE + OSEE_GICD_ITARGETSR + reg_offset,
    itargetisr_mask);
}

/*******************************************************************************
                          GICC Utilities Functions
 ******************************************************************************/
/* GICC Offsets */
#define OSEE_GICC_CTLR  (0x0000U)
#define OSEE_GICC_PMR   (0x0004U)
#define OSEE_GICC_IAR   (0x000CU)
#define OSEE_GICC_EOIR  (0x0010U)
/* GICC register values */
#define OSEE_GICC_CTLR_GRPEN1   (0x01U)
#define OSEE_GICC_CTLR_DIS_BYPASS_MASK (0x0FU << 5)

OSEE_STATIC_INLINE void osEE_gicd_init(void)
{
  osEE_mmio_write32(OSEE_GICD_BASE + OSEE_GICD_CTLR,
    OSEE_GICD_CTLR_ENABLE_G1_BIT | OSEE_GICD_CTLR_ENABLE_G0_BIT);
}

OSEE_STATIC_INLINE void osEE_gicc_init(void)
{
  uint32_t bypass;

  osEE_mmio_write32(OSEE_GICC_BASE + OSEE_GICC_PMR, OSEE_GIC_PRIO_UNMASKED);

  bypass = osEE_mmio_read32(OSEE_GICC_BASE + OSEE_GICC_CTLR)
           & OSEE_GICC_CTLR_DIS_BYPASS_MASK;

  osEE_mmio_write32(OSEE_GICC_BASE + OSEE_GICC_CTLR,
                    bypass | OSEE_GICC_CTLR_GRPEN1);
}

OSEE_STATIC_INLINE void osEE_gicc_eoi(ISRSource irqn)
{
  osEE_mmio_write32(OSEE_GICC_BASE + OSEE_GICC_EOIR, irqn);
}

OSEE_STATIC_INLINE uint8_t osEE_gicc_read_pmr(void)
{
  return (uint8_t)osEE_mmio_read32(OSEE_GICC_BASE + OSEE_GICC_PMR);
}

OSEE_STATIC_INLINE uint32_t osEE_gicc_read_ack(void)
{
  return osEE_mmio_read32(OSEE_GICC_BASE + OSEE_GICC_IAR);
}

/*==============================================================================
                              IPL Handling
 =============================================================================*/

/* We always use virtual priorities */
OSEE_STATIC_INLINE void osEE_hal_set_ipl(TaskPrio virt_prio) {
#if (defined(OSEE_GIC_PMR_HANDLING))
#if (defined(OSEE_GIC_REQUIRE_CS))
  OsEE_reg const daif_flags = osEE_hal_suspendIRQ();
#endif /* OSEE_GIC_REQUIRE_CS */
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    osEE_mmio_write32(OSEE_GICC_BASE + OSEE_GICC_PMR, OSEE_GIC_PRIO_UNMASKED);
  } else {
    osEE_mmio_write32(OSEE_GICC_BASE + OSEE_GICC_PMR,
      osEE_isr2_virt_to_hw_prio(virt_prio));
  }
#if (defined(OSEE_GIC_REQUIRE_CS))
  osEE_hal_resumeIRQ(daif_flags);
#endif /* OSEE_GIC_REQUIRE_CS */
#endif /* OSEE_GIC_PMR_HANDLING */
}

OSEE_STATIC_INLINE OsEE_reg
  osEE_hal_prepare_ipl(OsEE_reg flags, TaskPrio virt_prio)
{
#if (defined(OSEE_GIC_PMR_HANDLING))
  OsEE_reg ret_flags;
  /* Touch unused parameter */
  (void)flags;
  if (virt_prio < OSEE_ISR2_PRIO_BIT) {
    ret_flags = OSEE_GIC_PRIO_UNMASKED;
  } else {
    ret_flags = osEE_isr2_virt_to_hw_prio(virt_prio);
  }
  return ret_flags;
#else /* OSEE_GIC_PMR_HANDLING */
  return flags;
#endif /* OSEE_GIC_PMR_HANDLING */
}

/*==============================================================================
                          Ready Queue utilities
 =============================================================================*/

#if (defined(OSEE_RQ_MULTIQUEUE))
OSEE_STATIC_INLINE MemSize osEE_hal_get_msb (OsEE_rq_mask mask) {
  MemSize msb;
  MemSize const bits = (MemSize)((sizeof(mask) * CHAR_BIT) - 1U);
  if (mask == 0U) {
    msb = OSEE_RQ_MASK_EMPTY;
  } else if (bits <= 31U) {
    msb = (MemSize)(31 - __builtin_clz(mask));
  } else {
    msb = (MemSize)(63L - __builtin_clzl(mask));
  }
  return msb;
}
#endif /* OSEE_RQ_MULTIQUEUE */

/*==============================================================================
                    HAL For Primitives Synchronization
 =============================================================================*/

/* Called as _first_ function of a primitive that can be called from within
 * an IRQ and from within a task. */
OSEE_STATIC_INLINE OsEE_reg osEE_hal_begin_nested_primitive(void)
{
#if (defined(OSEE_GIC_PMR_HANDLING))
  OsEE_isr_prio const max_isr2_hw_prio =
    osEE_isr2_virt_to_hw_prio(OSEE_ISR2_MAX_PRIO);
  OsEE_isr_prio const flags =
    osEE_mmio_read32(OSEE_GICC_BASE + OSEE_GICC_PMR);

  /* hw prio increase to lower numerical values */
  if (flags > max_isr2_hw_prio) {
#if (defined(OSEE_GIC_REQUIRE_CS))
    OsEE_reg const daif_flags = osEE_hal_suspendIRQ();
#endif /* OSEE_GIC_REQUIRE_CS */
    osEE_mmio_write32(OSEE_GICC_BASE + OSEE_GICC_PMR, max_isr2_hw_prio);
#if (defined(OSEE_GIC_REQUIRE_CS))
    osEE_hal_resumeIRQ(daif_flags);
#endif /* OSEE_GIC_REQUIRE_CS */
  }
  return (OsEE_reg)flags;
#else /* OSEE_GIC_PMR_HANDLING */
  return osEE_hal_suspendIRQ();
#endif /* OSEE_GIC_PMR_HANDLING */
}

/* Called as _last_ function of a primitive that can be called from
 * within an IRQ or a task. */
OSEE_STATIC_INLINE void osEE_hal_end_nested_primitive(OsEE_reg flags)
{
#if (defined(OSEE_GIC_PMR_HANDLING))
  osEE_mmio_write32(OSEE_GICC_BASE + OSEE_GICC_PMR, (OsEE_isr_prio)flags);
#else /* OSEE_GIC_PMR_HANDLING */
  osEE_hal_resumeIRQ(flags);
#endif /* OSEE_GIC_PMR_HANDLING */
}

/*==============================================================================
                              Start-up and ISR2
 =============================================================================*/

/* C initialization function */
void osEE_c_start(void);

/* System Timer init */
#if (defined(OSEE_HAS_SYSTEM_TIMER))
void osEE_aarch64_system_timer_init(void);
#endif /* OSEE_HAS_SYSTEM_TIMER */

/* ERIKA's ISR2 Wrapper */
extern void osEE_aarch64_isr_wrapper(OsEE_ISR_CTX * p_isr_ctx);
/* extern void osEE_aarch64_isr_wrapper ( unsigned int irqn ); */

extern void osEE_aarch64_change_context_from_isr2_end (
  OsEE_TDB * p_to, OsEE_TDB * p_from
);

OSEE_STATIC_INLINE FUNC(void, OS_CODE)
  osEE_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
)
{
  /* Interrupt acknowledge */
  osEE_gicc_eoi(p_from->hdb.isr2_src);
  osEE_aarch64_change_context_from_isr2_end(p_from, p_to);
}

#endif /* !OSEE_HAL_INTERNAL_H */
