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

/** \file   ee_mmwave_osal_vim.h
 *  \brief  ARM Vector Interrupt Module Support, this is part of OSAL
 *          implementation of th OSAL for mmWave SDK
 *
 *  \author Errico Guidieri
 *  \date   2019
 */

#ifndef OSEE_MMWAVE_OSAL_VIM_H
#define OSEE_MMWAVE_OSAL_VIM_H

#include "ee_ti_awr16xx_internal_types.h"
/* For RCM i will delegate at mmWave */
#include <ti/drivers/soc/include/reg_rcm.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VIM General Configuration */
#if (!defined(OSEE_CORTEX_R_VIM_CHANNELS))
/* TI AWR16XX num of channels */
#define   OSEE_CORTEX_R_VIM_CHANNELS (128)
#elif (OSEE_CORTEX_R_VIM_CHANNELS > (160U)
/* 160 channels is the maximum supported  */
#undef  OSEE_CORTEX_R_VIM_CHANNELS
#define OSEE_CORTEX_R_VIM_CHANNELS  (160U)
#endif /* !OSEE_CORTEX_R_VIM_CHANNELS */

typedef enum {
  OSEE_VIM_SYS_IRQ,
  OSEE_VIM_SYS_FIQ
} OsEE_vim_irq_type;

#define  OSEE_CORTEX_R_VIM_IRQINDEX       (0x00U)
#define  OSEE_CORTEX_R_VIM_FIQINDEX       (0x04U)
#define  OSEE_CORTEX_R_VIM_FIRQPR0        (0x10U)
#define  OSEE_CORTEX_R_VIM_FIRQPR1        (0x14U)
#define  OSEE_CORTEX_R_VIM_FIRQPR2        (0x18U)
#define  OSEE_CORTEX_R_VIM_FIRQPR3        (0x1CU)
#define  OSEE_CORTEX_R_VIM_INTREQ0        (0x20U)
#define  OSEE_CORTEX_R_VIM_INTREQ1        (0x24U)
#define  OSEE_CORTEX_R_VIM_INTREQ2        (0x28U)
#define  OSEE_CORTEX_R_VIM_INTREQ3        (0x2CU)
#define  OSEE_CORTEX_R_VIM_REQMASKSET0    (0x30U)
#define  OSEE_CORTEX_R_VIM_REQMASKSET1    (0x34U)
#define  OSEE_CORTEX_R_VIM_REQMASKSET2    (0x38U)
#define  OSEE_CORTEX_R_VIM_REQMASKSET3    (0x3CU)
#define  OSEE_CORTEX_R_VIM_REQMASKCLR0    (0x40U)
#define  OSEE_CORTEX_R_VIM_REQMASKCLR1    (0x44U)
#define  OSEE_CORTEX_R_VIM_REQMASKCLR2    (0x48U)
#define  OSEE_CORTEX_R_VIM_REQMASKCLR3    (0x4CU)
#define  OSEE_CORTEX_R_VIM_WAKEMASKSET0   (0x50U)
#define  OSEE_CORTEX_R_VIM_WAKEMASKSET1   (0x54U)
#define  OSEE_CORTEX_R_VIM_WAKEMASKSET2   (0x58U)
#define  OSEE_CORTEX_R_VIM_WAKEMASKSET3   (0x5CU)
#define  OSEE_CORTEX_R_VIM_WAKEMASKCLR0   (0x60U)
#define  OSEE_CORTEX_R_VIM_WAKEMASKCLR1   (0x64U)
#define  OSEE_CORTEX_R_VIM_WAKEMASKCLR2   (0x68U)
#define  OSEE_CORTEX_R_VIM_WAKEMASKCLR3   (0x6CU)
#define  OSEE_CORTEX_R_VIM_IRQVECREG      (0x70U)
#define  OSEE_CORTEX_R_VIM_FIQVECREG      (0x74U)
#define  OSEE_CORTEX_R_VIM_CAPEVT         (0x78U)
/* 160 Channels available the following assure that we don't overflow them */
#define  OSEE_CORTEX_R_VIM_CHANCTRL(n)\
  ((OsEE_reg)0x80U +\
    (((OsEE_reg)(n) < ((OsEE_reg)(OSEE_CORTEX_R_VIM_CHANNELS >> 2U) + 1U))?\
      (OsEE_reg)((n) << 2U): (OsEE_reg)0U))

#if (!defined(OSEE_CORTEX_R_VIM_MODULE_BASEADDR))
/* VIM configuration space base address is wrong in reference manual
   and in code composer register view (wonderful). */
#define OSEE_CORTEX_R_VIM_MODULE_BASEADDR (0xFFFFFE00U)
#endif /* !OSEE_CORTEX_R_VIM_MODULE_BASEADDR */

#define OSEE_CORTEX_R_VIM_ADDR(offset)\
  ((OsEE_reg volatile *)(OSEE_CORTEX_R_VIM_MODULE_BASEADDR + (offset)))

#define OSEE_CORTEX_R_VIM_REG(offset)\
  (*OSEE_CORTEX_R_VIM_ADDR(offset))

#if (!defined(OSEE_CORTEX_R_VIM_RAM))
#define OSEE_CORTEX_R_VIM_RAM  ((OsEE_void_cb volatile *)0xFFF82000U)
#endif /* !OSEE_CORTEX_R_VIM_RAM */
#define OSEE_CORTEX_R_VIM_RAMPARLOC_REG (*(volatile uint32_t *)0xFFF82400U)

/* Configuration registers initial value */
#define OSEE_CORTEX_R_VIM_FIRQPR0_CFGVAL      (0x3U)
#define OSEE_CORTEX_R_VIM_FIRQPR1_CFGVAL      (0x0U)
#define OSEE_CORTEX_R_VIM_FIRQPR2_CFGVAL      (0x0U)
#define OSEE_CORTEX_R_VIM_FIRQPR3_CFGVAL      (0x0U)

#define OSEE_CORTEX_R_VIM_REQMASKSET0_CFGVAL  (0x3U)
#define OSEE_CORTEX_R_VIM_REQMASKSET1_CFGVAL  (0x0U)
#define OSEE_CORTEX_R_VIM_REQMASKSET2_CFGVAL  (0x0U)
#define OSEE_CORTEX_R_VIM_REQMASKSET3_CFGVAL  (0x0U)

#define OSEE_CORTEX_R_VIM_WAKEMASKSET0_CFGVAL (0xFFFFFFFFU)
#define OSEE_CORTEX_R_VIM_WAKEMASKSET1_CFGVAL (0xFFFFFFFFU)
#define OSEE_CORTEX_R_VIM_WAKEMASKSET2_CFGVAL (0xFFFFFFFFU)
#define OSEE_CORTEX_R_VIM_WAKEMASKSET3_CFGVAL (0xFFFFFFFFU)
/* Bit interesting 0 and 16 */
#define OSEE_CORTEX_R_VIM_CAPEVT_CFGVAL       (0x0U)

#define OSEE_CORTEX_R_VIM_CHANCTRL0_CFGVAL    (0x00010203U)
#define OSEE_CORTEX_R_VIM_CHANCTRL1_CFGVAL    (0x04050607U)
#define OSEE_CORTEX_R_VIM_CHANCTRL2_CFGVAL    (0x08090A0BU)
#define OSEE_CORTEX_R_VIM_CHANCTRL3_CFGVAL    (0x0C0D0E0FU)
#define OSEE_CORTEX_R_VIM_CHANCTRL4_CFGVAL    (0x10111213U)
#define OSEE_CORTEX_R_VIM_CHANCTRL5_CFGVAL    (0x14151617U)
#define OSEE_CORTEX_R_VIM_CHANCTRL6_CFGVAL    (0x18191A1BU)
#define OSEE_CORTEX_R_VIM_CHANCTRL7_CFGVAL    (0x1C1D1E1FU)
#define OSEE_CORTEX_R_VIM_CHANCTRL8_CFGVAL    (0x20212223U)
#define OSEE_CORTEX_R_VIM_CHANCTRL9_CFGVAL    (0x24252627U)
#define OSEE_CORTEX_R_VIM_CHANCTRL10_CFGVAL   (0x28292A2BU)
#define OSEE_CORTEX_R_VIM_CHANCTRL11_CFGVAL   (0x2C2D2E2FU)
#define OSEE_CORTEX_R_VIM_CHANCTRL12_CFGVAL   (0x30313233U)
#define OSEE_CORTEX_R_VIM_CHANCTRL13_CFGVAL   (0x34353637U)
#define OSEE_CORTEX_R_VIM_CHANCTRL14_CFGVAL   (0x38393A3BU)
#define OSEE_CORTEX_R_VIM_CHANCTRL15_CFGVAL   (0x3C3D3E3FU)
#define OSEE_CORTEX_R_VIM_CHANCTRL16_CFGVAL   (0x40414243U)
#define OSEE_CORTEX_R_VIM_CHANCTRL17_CFGVAL   (0x44454647U)
#define OSEE_CORTEX_R_VIM_CHANCTRL18_CFGVAL   (0x48494A4BU)
#define OSEE_CORTEX_R_VIM_CHANCTRL19_CFGVAL   (0x4C4D4E4FU)
#define OSEE_CORTEX_R_VIM_CHANCTRL20_CFGVAL   (0x50515253U)
#define OSEE_CORTEX_R_VIM_CHANCTRL21_CFGVAL   (0x54555657U)
#define OSEE_CORTEX_R_VIM_CHANCTRL22_CFGVAL   (0x58595A5BU)
#define OSEE_CORTEX_R_VIM_CHANCTRL23_CFGVAL   (0x5C5D5E5FU)
#define OSEE_CORTEX_R_VIM_CHANCTRL24_CFGVAL   (0x60616263U)
#define OSEE_CORTEX_R_VIM_CHANCTRL25_CFGVAL   (0x64656667U)
#define OSEE_CORTEX_R_VIM_CHANCTRL26_CFGVAL   (0x68696A6BU)
#define OSEE_CORTEX_R_VIM_CHANCTRL27_CFGVAL   (0x6C6D6E6FU)
#define OSEE_CORTEX_R_VIM_CHANCTRL28_CFGVAL   (0x70717273U)
#define OSEE_CORTEX_R_VIM_CHANCTRL29_CFGVAL   (0x74757677U)
#define OSEE_CORTEX_R_VIM_CHANCTRL30_CFGVAL   (0x78797A7BU)
#define OSEE_CORTEX_R_VIM_CHANCTRL31_CFGVAL   (0x7C7D7E7FU)

#if 0
/**
 * \defgroup VIM VIM
 * \brief Vectored Interrupt Manager
 *
 * The vectored interrupt manager (VIM) provides hardware assistance for
 * prioritizing and controlling the many interrupt sources present on a device.
 * Interrupts are caused by events outside of the normal flow of
 * program execution.
 *
 */
#endif /* 0 */
/* VIM Interface functions */
extern void osEE_vim_init(void);

extern void
  osEE_vim_channel_map(OsEE_isr_src_id request, OsEE_isr_channel channel);
extern void
  osEE_vim_enable_interrupt(OsEE_isr_channel channel, OsEE_vim_irq_type type);

extern OsEE_bool osEE_vim_is_enabled_interrupt(OsEE_isr_channel channel);
extern void osEE_vim_disable_interrupt(OsEE_isr_channel channel);
extern void osEE_vim_clear_interrupt(OsEE_isr_channel channel);

extern void osEE_vim_wakeup_config(OsEE_isr_channel channel);
extern void osEE_vim_phantom_interrupt(void);

#if 0
void vimTriggerSoftInt(uint32_t channel, uint8_t swIntData);
uint8_t vimGetSwIntData(uint32_t channel);
void vimDisableSoftInt(RCMRegs *rcmBaseAddr,uint32_t channel);
void vimGetConfigValue(vim_config_reg_t *config_reg, uint8_t type);
void vimParityErrorHandler(void);
void vimWakeupConfigClr(uint32_t channel);
t_isrFuncPTR vimGetIsrAddress(uint32_t channel);

void vimCaptureOnEvent(uint32_t interrupt_used);
void vimIntClear(uint32_t intPriority);
#endif /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* OSEE_MMWAVE_OSAL_VIM_H */

