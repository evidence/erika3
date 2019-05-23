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

/** \file   ee_mmwave_osal.c
 *  \brief  OSAL implementation for mmWave SDK library
 *
 *  \author Errico Guidieri
 *  \date   2019
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <ti/drivers/osal/MemoryP.h>
#include <ti/drivers/osal/HwiP.h>
#include <ti/drivers/osal/DebugP.h>

#include "ee_internal.h"
#include "ee_mmwave_osal_vim.h"
#include "ee_ti_awr16xx_rti.h"

#if (defined(OSEE_CORTEX_R_HAS_ISR1_TO_CONF))
extern OsEE_isr1_db osEE_isr1_db_instance;
#endif /* OSEE_CORTEX_R_HAS_ISR1_TO_CONF */

/* Assembly Function declared here for now */
extern void osEE_cortex_r_switch_to_system_mode(void);

static OsEE_bool volatile vim_initStatus;

#if (defined(OSEE_DEBUG))
#define OSEE_INT_VECTORS_STORAGE
#else
#define OSEE_INT_VECTORS_STORAGE static
#endif /* OSEE_DEBUG */

/* I save this in RAM allowing mmWave to registers interrupts a Run Time */
OSEE_INT_VECTORS_STORAGE OsEE_cortex_r_hnd_type
  osEE_cortex_r_int_vectors[OSEE_CORTEX_R_VIM_CHANNELS];

OSEE_INT_VECTORS_STORAGE OsEE_isr_channel
  osEE_cortex_r_int_channel[OSEE_CORTEX_R_VIM_CHANNELS];

/*
 *  ======== HwiP_DispatchEntry ========
 */
typedef struct HwiP_DispatchEntry {
    HwiP_Fxn          entry;
    uintptr_t         arg;
    OsEE_vim_irq_type vim_type;
    OsEE_isr_src_id   intNum;
} HwiP_DispatchEntry;

HwiP_DispatchEntry HwiP_dispatchTable[OSEE_CORTEX_R_VIM_CHANNELS];


static __inline OsEE_reg osEE_reg_write_read_back(OsEE_reg volatile * p_reg,
  OsEE_reg regVal)
{
  OsEE_reg regWr;
  /* Write the new value on the register */
  *p_reg = regVal;
  /* Read it back  */
  regWr = *p_reg;
  /* Bit compare the two values: 0 means equals */
  return regVal ^ regWr;
}

static StatusType osEE_ti_awr16xx_set_channel_hnd
(
  CONSTP2VAR(OsEE_cortex_r_hnd_type, AUTOMATIC, OS_APPL_DATA) p_hnd,
  VAR(ISRSource,  AUTOMATIC)                                  channel_id
)
{
  StatusType  ev;
  if (p_hnd == NULL) {
    ev = E_OS_PARAM_POINTER;
  } else if (channel_id >= OSEE_CORTEX_R_VIM_CHANNELS) {
    ev = E_OS_ID;
  } else
#if (defined(OSEE_HAS_CHECKS))
  if ((p_hnd->cat == OSEE_ISR_CAT_2) && (p_hnd->hnd.tid == INVALID_TASK)) {
    ev = E_OS_NOFUNC;
  } else
  if ((p_hnd->cat != OSEE_ISR_CAT_2) && (p_hnd->hnd.p_hnd_func == NULL)) {
    ev = E_OS_NOFUNC;
  } else
#endif /* OSEE_HAS_CHECKS */
  {
    osEE_cortex_r_int_vectors[channel_id]= *p_hnd;

    ev = E_OK;
  }

  return ev;
}

static void osEE_ti_awr16xx_hnd_req_and_ch
(
  OsEE_isr_src_id           request,
  OsEE_isr_channel          channel,
  OsEE_cortex_r_hnd_type  * p_hnd_to_conf
)
{
  OsEE_cortex_r_hnd_type * p_hnd;

  DebugP_assert(request < OSEE_CORTEX_R_VIM_CHANNELS);
  DebugP_assert(channel < OSEE_CORTEX_R_VIM_CHANNELS);

  p_hnd = &osEE_cortex_r_int_vectors[channel];

  /* Before initialization disable and clear the channel & request */
  osEE_vim_disable_interrupt(channel);
  osEE_vim_clear_interrupt(channel);

  if (channel != request) {
    osEE_vim_disable_interrupt((OsEE_isr_channel)request);
    osEE_vim_clear_interrupt((OsEE_isr_channel)request);
  }

  /* Remap previous set ISR1/TRAP on higher priority
     "request" channel, if possible...  */
  if ((p_hnd->cat != OSEE_ISR_CAT_2) && (p_hnd->hnd.p_hnd_func != NULL)) {
    /* Swap previous HwiP entry from channel to request */
    HwiP_DispatchEntry const * p_dispatch_entry = &HwiP_dispatchTable[channel];

    if (channel > request) {
      /* Map the number to the interrupt handler */
      osEE_vim_channel_map(p_dispatch_entry->intNum,
        (OsEE_isr_channel)request);

#if 0
      HwiP_dispatchTable[request].entry     = p_dispatch_entry->entry;
      HwiP_dispatchTable[request].arg       = p_dispatch_entry->arg;
      HwiP_dispatchTable[request].vim_type  = p_dispatch_entry->vim_type;
      HwiP_dispatchTable[request].intNum    = p_dispatch_entry->intNum;
#endif  /* 0 */

      HwiP_dispatchTable[request] = *p_dispatch_entry;

      osEE_ti_awr16xx_set_channel_hnd(p_hnd, (OsEE_isr_channel)request);
      osEE_cortex_r_int_channel[p_dispatch_entry->intNum] =
        (OsEE_isr_channel)request;

      /* If the previous channel is enabled, enable the new "request"
         channel */
      if (osEE_vim_is_enabled_interrupt(channel)) {
        osEE_vim_enable_interrupt(request, p_dispatch_entry->vim_type);
      }
    } else {
      /* Assert False */
      DebugP_assert(0);
    }
  } else if (channel != request) {
    /* In any case swap request with channel otherwise, double
       interrupt mapping. */
    osEE_vim_channel_map((OsEE_isr_src_id)channel, (OsEE_isr_channel)request);
  }

  /* Configure and enable the new ISR */
  (*p_hnd) = *p_hnd_to_conf;

  osEE_cortex_r_int_channel[request] = channel;

  osEE_vim_channel_map(request, channel);
}

OsEE_bool osEE_cpu_startos(void) {
  /* TODO ISR Mapping */
  OsEE_KDB *  const p_kdb    = osEE_get_kernel();
  size_t      const tdb_size = (size_t)p_kdb->tdb_array_size - 1U;
  size_t            i;

  if (vim_initStatus == OSEE_FALSE) {
    /* ERIKA's initialization need to be executed in supervisor mode too */
    osEE_cortex_r_switch_to_system_mode();
    osEE_vim_init();
  }

  /* Disable all software interrupts AT reset at least SW0 is enabled and
     active */
  osEE_vim_disable_sw_int((OsEE_isr_channel)-1);
#if (!defined(OSEE_HAS_SYSTEM_TIMER))
  /* This will reset RTI interrupts */
  osEE_ti_awr16xx_rti_init();
#endif /* !OSEE_HAS_SYSTEM_TIMER */

  for (i = 0U; i < tdb_size; ++i) {
    /* ISR2 initialization */
    OsEE_TDB  * const p_tdb = (*p_kdb->p_tdb_ptr_array)[i];
    if (p_tdb->task_type == OSEE_TASK_TYPE_ISR2) {
      OsEE_isr_src_id  const request = p_tdb->hdb.isr2_src;
      OsEE_isr_channel const channel =
        OSEE_ISR2_VIRT_TO_HW_PRIO(p_tdb->ready_prio);
      OsEE_cortex_r_hnd_type hnd_to_conf;

      hnd_to_conf.cat     = OSEE_ISR_CAT_2;
      hnd_to_conf.hnd.tid = p_tdb->tid;

      osEE_ti_awr16xx_hnd_req_and_ch(request, channel, &hnd_to_conf);

#if (defined(OSEE_HAS_SYSTEM_TIMER))
      if (p_tdb->task_func == &osEE_cortex_r_system_timer_handler) {
        osEE_cortex_r_initialize_system_timer(p_tdb);
      }
#endif /* OSEE_HAS_SYSTEM_TIMER */

      osEE_vim_enable_interrupt(channel, OSEE_VIM_SYS_IRQ);
    }
  }
#if (defined(OSEE_CORTEX_R_HAS_ISR1_TO_CONF))
  {
    MemSize const isr1_num = osEE_isr1_db_instance.isr1_num;

    for (i = 0U; i < isr1_num; ++i) {
      OsEE_isr_src_id  const request =
        (*osEE_isr1_db_instance.p_isr1_src_array)[i].isr1_src;
      OsEE_isr_channel const channel = OSEE_CORTEX_R_VIM_CHANNELS -
        (*osEE_isr1_db_instance.p_isr1_src_array)[i].isr_prio;
      OsEE_cortex_r_hnd_type hnd_to_conf;

      hnd_to_conf.cat             = OSEE_ISR_CAT_1;
      hnd_to_conf.hnd.p_hnd_func  =
        (*osEE_isr1_db_instance.p_isr1_src_array)[i].p_hnd_func;

      osEE_ti_awr16xx_hnd_req_and_ch(request, channel, &hnd_to_conf);

      osEE_vim_enable_interrupt(channel, OSEE_VIM_SYS_IRQ);
    }
  }
#endif /* OSEE_CORTEX_R_HAS_ISR1_TO_CONF */


  return osEE_std_cpu_startos();
}

FUNC(void, OS_CODE)
  osEE_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
)
{
  CONSTP2VAR(OsEE_HCB, AUTOMATIC, OS_APPL_DATA)
    p_fromt_hcb = p_from->hdb.p_hcb;
  OsEE_isr_channel const channel =
    osEE_cortex_r_int_channel[p_from->hdb.isr2_src];

  /* Clear the channel */
  osEE_vim_clear_interrupt(channel);

  /* Restore previous interrupt enabled masks */
  OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET0) =
    p_fromt_hcb->mask_set0;
  OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET1) =
    p_fromt_hcb->mask_set1;
  OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET2) =
    p_fromt_hcb->mask_set2;
  OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET3) =
    p_fromt_hcb->mask_set3;

  /*
   * Perform DSB to complete ongoing VIM register writes
   */
  __asm volatile (" dsb");

  osEE_change_context_from_task_end(p_from, p_to);
}

#if (defined(DebugP_ASSERT_ENABLED))
/*
 *  ======== _DebugP_assert ========
 */
void _DebugP_assert(int expression, const char *file, int line)
{
  if (expression == 0) {
    printf("ASSERT ERROR: file %s[line:%d]\n\r", file, line);
    for(;;);
  }
}
#endif /* DebugP_ASSERT_ENABLED */

/*
 *  ======== MemoryP_ctrlAlloc ========
 */
void* MemoryP_ctrlAlloc(uint32_t size, uint8_t alignment)
{
  size_t corr_align;
  if ((size_t)alignment < sizeof(void *)) {
    corr_align = sizeof(void *);
  } else {
    if (alignment & (alignment - 1U) == 0U) {
      corr_align = alignment;
    } else {
      corr_align = (size_t)1U << (32U - __clz((uint32_t)alignment));
    }
  }

  return memalign(size, corr_align);
}

/*
 *  ======== MemoryP_ctrlFree ========
 */
void MemoryP_ctrlFree(void* ptr, uint32_t size)
{
    /* Free the memory to the appropriate heap: */
    free(ptr);
}

/*
 *  ======== MemoryP_dataAlloc ========
 */
void* MemoryP_dataAlloc(uint32_t size, uint8_t alignment)
{
  size_t corr_align;
  if ((size_t)alignment < sizeof(void *)) {
    corr_align = sizeof(void *);
  } else {
    if (alignment & (alignment - 1U) == 0U) {
      corr_align = alignment;
    } else {
      corr_align = (size_t)1U << (32U - __clz((uint32_t)alignment));
    }
  }

  return memalign(size, corr_align);
}

/*
 *  ======== MemoryP_dataFree ========
 */
void MemoryP_dataFree(void* ptr, uint32_t size)
{
  /* Free the memory to the appropriate heap: */
  free(ptr);
}

/*
 *  ======== HwiP_dispatch ========
 */
void HwiP_dispatch(void) {
  /* Used Only As Tag To understand what to do in IRQ dispatcher */
}

/*
 *  ======== HwiP_clearInterrupt ========
 */
void HwiP_clearInterrupt(int32_t interruptNum) {
  OsEE_isr_channel const channel = osEE_cortex_r_int_channel[interruptNum];
  if (channel != 0) {
      osEE_vim_clear_interrupt(channel);
  }
}

/*
 *  ======== HwiP_disable ========
 */
uintptr_t HwiP_disable(void)
{
  return (uintptr_t)osEE_hal_suspendIRQ();
}

/*
 *  ======== HwiP_disableInterrupt ========
 */
void HwiP_disableInterrupt(int32_t interruptNum)
{
  OsEE_isr_channel const channel = osEE_cortex_r_int_channel[interruptNum];
  if (channel != 0) {
      osEE_vim_disable_interrupt(channel);
  }
}

/*
 *  ======== HwiP_restore ========
 */
void HwiP_restore(uintptr_t key)
{
  osEE_hal_resumeIRQ((OsEE_reg) key);
}

/*
 *  ======== HwiP_Params_init ========
 */
void HwiP_Params_init(HwiP_Params *params)
{
  params->name = NULL;
  params->arg = 0;
  params->enableInt = true;
  /* Priority is given by the channel number, lower is the channel
     number higher is the priority */
  params->priority = OSEE_CORTEX_R_VIM_CHANNELS;
  params->type = HwiP_Type_IRQ;
}

HwiP_Handle HwiP_create(int32_t interruptNum, HwiP_Fxn hwiFxn,
                        HwiP_Params *params)
{
  OsEE_isr_channel        channel = 0;
  OsEE_cortex_r_hnd_type  hnd_type;
  OsEE_vim_irq_type       type;

  if (vim_initStatus == OSEE_FALSE) {
    /* mmWave initialization need to be executed in supervisor mode */
    osEE_cortex_r_switch_to_system_mode();
    /* Initialize vim module if not done already */
    osEE_vim_init();
  }

  if (params->type == HwiP_Type_IRQ) {
    hnd_type.cat  = OSEE_ISR_CAT_1;
    type          = OSEE_VIM_SYS_IRQ;
  } else {
    hnd_type.cat  = OSEE_ISR_TRAP;
    type          = OSEE_VIM_SYS_FIQ;
  }

  /* The priority of an interrupt is tied to which channel is tied to */
  if (params->priority < OSEE_CORTEX_R_VIM_CHANNELS) {
    channel = params->priority;
  } else {
    /* Channel eq. to interrupt number */
    channel = interruptNum;
  }

  /* Map the interrupt number to the interrupt handler */
  osEE_vim_channel_map(interruptNum, channel);

  HwiP_dispatchTable[channel].entry     = hwiFxn;
  HwiP_dispatchTable[channel].arg       = params->arg;
  HwiP_dispatchTable[channel].vim_type  = type;
  HwiP_dispatchTable[channel].intNum    = interruptNum;

  hnd_type.hnd.p_hnd_func = HwiP_dispatch;

  osEE_ti_awr16xx_set_channel_hnd(&hnd_type, channel);
  osEE_cortex_r_int_channel[interruptNum] = channel;

  if (params->enableInt) {
    osEE_vim_enable_interrupt(channel, type);
  }

  return((HwiP_Handle)interruptNum);
}

/*=============================================================================
                                VIM Stuff
 ============================================================================*/
/**
 *  @fn void vimInit(void)
 *  @brief Initializes VIM module
 *
 *  This function initializes VIM registers
 */
void osEE_vim_init(void) {
  if (vim_initStatus == OSEE_FALSE) {
    OsEE_reg regWrFailStatus = 0U;

    {
      size_t i;
      /* Initialize the RAM Map Channel->Int Source with reset status, that is
         Int Source mapped on corresponding channel + Clear stale IRQ status.
      */
      for (i = 0U; i < OSEE_CORTEX_R_VIM_CHANNELS; ++i) {
        osEE_vim_disable_interrupt(i);
        osEE_vim_clear_interrupt(i);
        osEE_cortex_r_int_channel[i] = i;
      }
    }

    /* Set IRQ/FIQ priorities */
    regWrFailStatus |= osEE_reg_write_read_back(
                          OSEE_CORTEX_R_VIM_ADDR(OSEE_CORTEX_R_VIM_FIRQPR0),
                          OSEE_CORTEX_R_VIM_FIRQPR0_CFGVAL);

    regWrFailStatus |= osEE_reg_write_read_back(
                          OSEE_CORTEX_R_VIM_ADDR(OSEE_CORTEX_R_VIM_FIRQPR1),
                          OSEE_CORTEX_R_VIM_FIRQPR1_CFGVAL);

    regWrFailStatus |= osEE_reg_write_read_back(
                        OSEE_CORTEX_R_VIM_ADDR(OSEE_CORTEX_R_VIM_FIRQPR2),
                        OSEE_CORTEX_R_VIM_FIRQPR2_CFGVAL);

    regWrFailStatus |= osEE_reg_write_read_back(
                        OSEE_CORTEX_R_VIM_ADDR(OSEE_CORTEX_R_VIM_FIRQPR3),
                        OSEE_CORTEX_R_VIM_FIRQPR3_CFGVAL);

    /* Clear Pending Interrupts */
    OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_INTREQ0) = (0xFFFFFFFFU);
    OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_INTREQ1) = (0xFFFFFFFFU);
    OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_INTREQ2) = (0xFFFFFFFFU);
    OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_INTREQ3) = (0xFFFFFFFFU);

    /* Enable Interrupts */
    OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET0) =
      OSEE_CORTEX_R_VIM_REQMASKSET0_CFGVAL;
    OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET1) =
      OSEE_CORTEX_R_VIM_REQMASKSET1_CFGVAL;
    OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET2) =
      OSEE_CORTEX_R_VIM_REQMASKSET2_CFGVAL;
    OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET3) =
      OSEE_CORTEX_R_VIM_REQMASKSET3_CFGVAL;

    /* Set Capture Event Sources */
    regWrFailStatus |= osEE_reg_write_read_back(
                        OSEE_CORTEX_R_VIM_ADDR(OSEE_CORTEX_R_VIM_CAPEVT),
                        OSEE_CORTEX_R_VIM_CAPEVT_CFGVAL);

    DebugP_assert(0U == regWrFailStatus);

    osEE_vim_wakeup_config(0x0U);

    vim_initStatus = OSEE_TRUE;
  }
}

void osEE_vim_clear_interrupt(OsEE_isr_channel channel) {
  OsEE_reg  chRegIndex;
  OsEE_reg  chRegOffset;

  /* Channel Reg Id = channel / 32U */
  chRegIndex  = (OsEE_reg)channel >> 5U;
  /* Channel Offset in Reg = channel % 32U */
  chRegOffset = channel - (chRegIndex << 5U);
  /* INTREQx is OSEE_CORTEX_R_VIM_INTREQ0 address + (chRegIndex * 4) */
  OSEE_CORTEX_R_VIM_ADDR(OSEE_CORTEX_R_VIM_INTREQ0)[chRegIndex] =
    (OsEE_reg)1U << chRegOffset;
}


/**
 *  @fn void vimChannelMap(uint32_t request, uint32_t channel)
 *  @brief Map selected interrupt request to the selected channel
*
*    @param[in] request: Interrupt request number 2..127
*    @param[in] channel: VIM Channel number 2..127
*
*   This function will map selected interrupt request to the selected channel.
*
*/
void osEE_vim_channel_map(OsEE_isr_src_id request, OsEE_isr_channel channel)
{
  OsEE_reg chRegId, chRegOffset;
  OsEE_reg regWrFailStatus, regVal;

  /* Find the register to configure */
  chRegId     = (OsEE_reg)channel >> 2U;
  /* Find the offset of the type    */
  chRegOffset = (OsEE_reg)channel - (chRegId << 2U);
  /* Reverse the offset, since the lowest channel is mapped on the MSB */
  chRegOffset = ((OsEE_reg)3U - chRegOffset);
  /* Find the bit location offset * 8 => offset << 3U */
  chRegOffset = chRegOffset << 3U;

  /* Mapping the required interrupt request to the required channel */
  regVal = OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_CHANCTRL(chRegId));

  regVal &= ~((OsEE_reg)0xFFU << chRegOffset);
  regVal |= ((OsEE_reg)request << chRegOffset);
  regWrFailStatus = osEE_reg_write_read_back(
                   OSEE_CORTEX_R_VIM_ADDR(OSEE_CORTEX_R_VIM_CHANCTRL(chRegId)),
                   regVal);

  /* Raise a fatal error if any of above register writes and comparison
     failed */
  DebugP_assert(0U == regWrFailStatus);
}

/**
 *  @fn void osEE_vim_wakeup_config(uint32_t channel)
 *  @brief This function enables the wakeup mask of channel
 *
 *  @param[in] channel: Interrupt channel number
 *
 *   This function enables the wakeup mask of channel
 *
 */
void osEE_vim_wakeup_config(OsEE_isr_channel channel) {
  OsEE_reg  chRegIndex, chSlotIndex;
  OsEE_reg  chanRegVal;
  OsEE_reg  regWrFailStatus;

  /* Find the register to configure */
  chRegIndex  = (OsEE_reg)channel >> 5U;
  /* Find the offset of the channel */
  chSlotIndex = (OsEE_reg)channel - ((OsEE_reg)chRegIndex << 5U);

  /*
   * Enable the wakeup VIM channel
   */
  chanRegVal = ((OsEE_reg)0x1UL << chSlotIndex);

  if (chRegIndex == 0U) {
    chanRegVal =
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_WAKEMASKSET0) | chanRegVal;
    regWrFailStatus = osEE_reg_write_read_back(
                        OSEE_CORTEX_R_VIM_ADDR(OSEE_CORTEX_R_VIM_WAKEMASKSET0),
                        chanRegVal);
  } else if (chRegIndex == 1U) {
    chanRegVal =
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_WAKEMASKSET1) | chanRegVal;
    regWrFailStatus = osEE_reg_write_read_back(
                        OSEE_CORTEX_R_VIM_ADDR(OSEE_CORTEX_R_VIM_WAKEMASKSET1),
                        chanRegVal);
  } else if(chRegIndex == 2U) {
    chanRegVal =
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_WAKEMASKSET2) | chanRegVal;
    regWrFailStatus = osEE_reg_write_read_back(
                        OSEE_CORTEX_R_VIM_ADDR(OSEE_CORTEX_R_VIM_WAKEMASKSET2),
                        chanRegVal);
  } else {
    chanRegVal =
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_WAKEMASKSET3) | chanRegVal;
    regWrFailStatus = osEE_reg_write_read_back(
                        OSEE_CORTEX_R_VIM_ADDR(OSEE_CORTEX_R_VIM_WAKEMASKSET3),
                        chanRegVal);
  }

  /* Raise a fatal error if any of above register writes and comparison failed */
  DebugP_assert(0U == regWrFailStatus);
}

/** @fn void vimEnableInterrupt(uint32_t channel, uint32_t inttype)
 *  @brief Enable interrupt for the the selected channel
 *
 *  @param[in] channel: VIM Channel number 2..127
 *  @param[in] type: Interrupt type
 *                      - OSEE_VIM_SYS_IRQ: channel will be enabled as IRQ
 *                      - OSEE_VIM_SYS_FIQ: channel will be enabled as FIQ
 *
 *   This function will enable interrupt for the selected channel.
 *
 */
void osEE_vim_enable_interrupt(OsEE_isr_channel channel, OsEE_vim_irq_type type)
{
  OsEE_reg regWrFailStatus;
  if (channel < OSEE_CORTEX_R_VIM_CHANNELS) {
    OsEE_reg regMask, regFIRQPRoff;

    if (channel >= 96U) {
      regMask = (OsEE_reg)1U << (channel - 96U);
      regFIRQPRoff = OSEE_CORTEX_R_VIM_FIRQPR3;
    } else if (channel >= 64U) {
      regMask = (OsEE_reg)1U << (channel - 64U);
      regFIRQPRoff = OSEE_CORTEX_R_VIM_FIRQPR2;
    } else if (channel >= 32U) {
      regMask = (OsEE_reg)1U << (channel - 32U);
      regFIRQPRoff = OSEE_CORTEX_R_VIM_FIRQPR1;
    } else if (channel >= 2U) {
      regMask = (OsEE_reg)1U << channel;
      regFIRQPRoff = OSEE_CORTEX_R_VIM_FIRQPR0;
    } else {
      regFIRQPRoff = 0U;
    }

    if (regFIRQPRoff != 0U) {
      OsEE_reg const  delta_from_firqpr_to_set =
        (OSEE_CORTEX_R_VIM_REQMASKSET0 - OSEE_CORTEX_R_VIM_FIRQPR0);

      OsEE_reg        regVal = OSEE_CORTEX_R_VIM_REG(regFIRQPRoff);

      if (type == OSEE_VIM_SYS_IRQ) {
        regVal &= (~regMask);
      } else {
        regVal |= regMask;
      }

      regWrFailStatus = osEE_reg_write_read_back(
        OSEE_CORTEX_R_VIM_ADDR(regFIRQPRoff),
        regVal);

      OSEE_CORTEX_R_VIM_REG(regFIRQPRoff + delta_from_firqpr_to_set)
        = regMask;
    } else {
      regWrFailStatus = 0U;
    }
  } else {
    regWrFailStatus = 0U;
  }

  /* Raise a fatal error if any of above register writes and comparison failed */
  DebugP_assert(0U == regWrFailStatus);
}

/**
 *  @fn void osEE_vim_is_enabled_interrupt(OsEE_isr_channel channel)
 *  @brief Disable interrupt for the the selected channel
 *
 *  @param[in] channel: VIM Channel number 2..127
 *
 *  This function will disable interrupt for the selected channel.
 *
 */
OsEE_bool osEE_vim_is_enabled_interrupt(OsEE_isr_channel channel) {
  OsEE_bool enabled;

  if (channel < OSEE_CORTEX_R_VIM_CHANNELS) {
    if (channel >= 96U) {
      enabled = ((OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET3) =
        ((OsEE_reg)1U << (channel - 96U))) != 0U);
    } else if (channel >= 64U) {
      enabled = ((OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET2) =
        ((OsEE_reg)1U << (channel- 64U))) != 0U);
    } else if (channel >= 32U) {
      enabled = ((OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET1) &
        ((OsEE_reg)1U << (channel - 32U))) != 0U);
    } else {
      enabled = ((OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET0) &
        ((OsEE_reg)1U << channel)) != 0U);
    }
  } else {
    enabled = OSEE_FALSE;
  }

  return enabled;
}

/**
 *  @fn void osEE_vim_disable_interrupt(OsEE_isr_channel channel)
 *  @brief Disable interrupt for the the selected channel
 *
 *  @param[in] channel: VIM Channel number 2..127
 *
 *  This function will disable interrupt for the selected channel.
 *
 */
void osEE_vim_disable_interrupt(OsEE_isr_channel channel) {
  if (channel < OSEE_CORTEX_R_VIM_CHANNELS) {
    if (channel >= 96U) {
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR3) =
        (OsEE_reg)1U << (channel - 96U);
    } else if (channel >= 64U) {
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR2) =
        (OsEE_reg)1U << (channel- 64U);
    } else if (channel >= 32U) {
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR1) =
        (OsEE_reg)1U << (channel - 32U);
    } else if (channel >= 2U) {
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR0) =
        (OsEE_reg)1U << channel;
    } else {
      /* Nothing TODO */
    }
  } else {
    /* Nothing TODO */
  }
}

/** @fn void osEE_cortex_r_irq_hnd(void)
 *  @brief This is C function of IRQ Interrupt dispatch handler
 *
 *
 */
/* .startup section is an arm 32 bit section I force the following function to
    be generated as arm 32 bit instruction section instead of */
#pragma CODE_STATE(osEE_cortex_r_irq_hnd, 32)
#pragma CODE_SECTION(osEE_cortex_r_irq_hnd, ".startup");
void osEE_cortex_r_irq_hnd(void) {
  /*
   * Get IRQ channel index number from VIM
   */
  OsEE_reg channel =
    (OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_IRQINDEX) & 0xFFU);

  if (channel > 0U) {
    /* Stack VIM REQENASET[0,1,2,3] Registers for later restore */
    OsEE_reg const prev_REQMASKSET0 =
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET0);
    OsEE_reg const prev_REQMASKSET1 =
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET1);
    OsEE_reg const prev_REQMASKSET2 =
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET2);
    OsEE_reg const prev_REQMASKSET3 =
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET3);

    OsEE_reg chRegIndex, chRegBit, chClearMask;
    /* Normalize the channel from [0..127] */
    channel -= 1U;

   /*
    * Resolve the registers set
    */
    /* Find the ID of register to configure (channel /32U) */
    chRegIndex  = channel >> 5U;
    /* Find the Bit offset for the interrupt (channel % 32U) */
    chRegBit = channel - (uint32_t)((uint8_t)chRegIndex << 5U);
    /* Initial Clear Mask for the ID register */
    chClearMask = 0xFFFFFFFFU ^ (((OsEE_reg)0x1U << chRegBit) - 1U);

    /* Mask out lower priority IRQ's and the current IRQ itself,
       keep FIQ's enabled.

       This because as soon as I read the IRQINDEX the
       Interrupt bit have been acknowledged already,
       so low level interrupts and the same source it self can preempt
       this instance of execution

       EG: This interrupt vector sucks at levels that I never
           thought be possible, they made everything wrong... */
    if (chRegIndex == 0U) {
      chClearMask &= (~OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_FIRQPR0));
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR0) = chClearMask;
    } else {
      /* Nothing To Do */
    }

    if (chRegIndex < 1U) {
      chClearMask =
        0xFFFFFFFFU && (~OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_FIRQPR1));
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR1) = chClearMask;
    } else if (chRegIndex == 1U) {
      chClearMask &= (~OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_FIRQPR1));
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR1) = chClearMask;
    } else {
      /* Nothing To Do */
    }

    if (chRegIndex < 2U) {
      chClearMask =
        0xFFFFFFFFU && (~OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_FIRQPR2));
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR2) = chClearMask;
    } else if (chRegIndex == 2U) {
      chClearMask &= (~OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_FIRQPR2));
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR2) = chClearMask;
    } else {
      /* Nothing To Do */
    }

    if (chRegIndex < 3U) {
      chClearMask =
        0xFFFFFFFFU && (~OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_FIRQPR3));
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR3) = chClearMask;
    } else if (chRegIndex == 3U) {
      chClearMask &= (~OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_FIRQPR3));
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR3) = chClearMask;
    } else {
      /* Nothing To Do */
    }

#if (defined(OSEE_CORTEX_R_VIM_HAS_4_REGSET))
    if (chRegIndex < 4U) {
      chClearMask =
        0xFFFFFFFFU && (~OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_FIRQPR4));
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR4) = chClearMask;
    } else if (chRegIndex == 4U) {
      chClearMask &= (~OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_FIRQPR4));
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKCLR4) = chClearMask;
    } else {
      /* Nothing To Do */
    }
#endif /* OSEE_CORTEX_R_VIM_HAS_4_REGSET */
    /*
     * Perform DSB to complete ongoing VIM register writes
     */
    __asm volatile (" dsb");

    /* Schedule ISR e VIM registers restore */
    {
      OsEE_cortex_r_hnd_type OSEE_CONST * const p_hnd =
        &osEE_cortex_r_int_vectors[channel];

      if (p_hnd->cat == OSEE_ISR_CAT_2) {
        TaskType const tid = p_hnd->hnd.tid;
        if (tid != INVALID_TASK) {
          /* Implement here osEE_activate_isr2 since I need to save REQENASET */
          CONSTP2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)
            p_kdb = osEE_get_kernel();
          CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
            p_act_tdb = (*p_kdb->p_tdb_ptr_array)[tid];
          CONSTP2VAR(OsEE_HCB, AUTOMATIC, OS_APPL_DATA)
            p_act_hcb = p_act_tdb->hdb.p_hcb;
#if (defined(OSEE_HAS_STACK_MONITORING))
          osEE_stack_monitoring(osEE_get_curr_core());
#endif /* OSEE_HAS_STACK_MONITORING */

          /* Mark the TASK as Activated */
          ++p_act_tdb->p_tcb->current_num_of_act;

          /* VIM save REQENASET[0,1,2,3] */
          p_act_hcb->mask_set0 = prev_REQMASKSET0;
          p_act_hcb->mask_set1 = prev_REQMASKSET1;
          p_act_hcb->mask_set2 = prev_REQMASKSET2;
          p_act_hcb->mask_set3 = prev_REQMASKSET3;

          osEE_scheduler_task_set_running(p_kdb, p_act_tdb, NULL);
        }
      } else {
        OsEE_void_cb p_hnd_func = p_hnd->hnd.p_hnd_func;
        if (p_hnd_func != NULL) {
          if (p_hnd_func == HwiP_dispatch) {
            HwiP_DispatchEntry * const p_hwi = &HwiP_dispatchTable[channel];
            if (p_hwi->entry != NULL) {
              (p_hwi->entry)(p_hwi->arg);
            }
          } else {
            p_hnd_func();
          }
        }
        /* Clear the channel */
        osEE_vim_clear_interrupt(channel);
      }

      /* VIM restore REQENASET[0,1,2,3] */
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET0) = prev_REQMASKSET0;
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET1) = prev_REQMASKSET1;
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET2) = prev_REQMASKSET2;
      OSEE_CORTEX_R_VIM_REG(OSEE_CORTEX_R_VIM_REQMASKSET3) = prev_REQMASKSET3;

#if 0
      /*
       * Perform DSB to complete ongoing VIM register writes
       */
      __asm volatile (" dsb");
#endif /* 0 */
    }
  } else {
    /* Phantom Interrupt */;
  }
}

/** @fn void osEE_vim_trigger_soft_int(OsEE_isr_channel channel,
*         uint8 sw_int_data)
*   @brief Trigger Software interrupt for given channel
*
*   @param[in] channel: vim interrupt channel
*   @param[in] sw_int_data: system software interrupt data
*
*   This function will trigger software interrupt with assigning interrupt
*   data to it.
*
*/

#define TI_RCM_REG_P   ((RCMRegs*)SOC_XWR16XX_MSS_RCM_BASE_ADDRESS)

void osEE_vim_trigger_soft_int(OsEE_isr_channel channel, uint8_t sw_int_data)
{
  OsEE_reg regVal;

  /* I cannot use osEE_reg_write_read_back since the interrupt can happen
     before I actually I read back */
  switch (channel) {
    case SOC_XWR16XX_MSS_SYS_SW0_INT:
      regVal = TI_RCM_REG_P->SWIRQA;
      regVal |= (0xADU << 8U) | (OsEE_reg)sw_int_data;
      TI_RCM_REG_P->SWIRQA = regVal;
      regVal = TI_RCM_REG_P->SWIRQA;
    break;
    case SOC_XWR16XX_MSS_SYS_SW2_INT:
      regVal = TI_RCM_REG_P->SWIRQB;
      regVal |= (0xADU << 8U) | (OsEE_reg)sw_int_data;
      TI_RCM_REG_P->SWIRQB = regVal;
      regVal = TI_RCM_REG_P->SWIRQB;
    break;
    case SOC_XWR16XX_MSS_SYS_SW4_INT:
      regVal = TI_RCM_REG_P->SWIRQC;
      regVal |= (0xADU << 8U) | (OsEE_reg)sw_int_data;
      TI_RCM_REG_P->SWIRQC = regVal;
      regVal = TI_RCM_REG_P->SWIRQC;
    break;
    case SOC_XWR16XX_MSS_SYS_SW1_INT:
      regVal = TI_RCM_REG_P->SWIRQA;
      regVal |= (0xADU << 24U) | (OsEE_reg)sw_int_data;
      TI_RCM_REG_P->SWIRQA = regVal;
      regVal = TI_RCM_REG_P->SWIRQA;
    break;
    case SOC_XWR16XX_MSS_SYS_SW3_INT:
      regVal = TI_RCM_REG_P->SWIRQB;
      regVal |= (0xADU << 24U) | (OsEE_reg)sw_int_data;
      TI_RCM_REG_P->SWIRQB = regVal;
      regVal = TI_RCM_REG_P->SWIRQB;
    break;
    case SOC_XWR16XX_MSS_SYS_SW5_INT:
      regVal = TI_RCM_REG_P->SWIRQC;
      regVal |= (0xADU << 24U) | (OsEE_reg)sw_int_data;
      TI_RCM_REG_P->SWIRQC = regVal;
      regVal = TI_RCM_REG_P->SWIRQC;
    break;
    default:
    break;
  }
}


/** @fn uint8 osEE_vim_get_sw_int_data(OsEE_isr_channel channel)
*   @brief Get Software interrupt data for given SW Vim Channel
*
*    @param[in] channel: vim interrupt channel
*   This function will ret Software interrupt data for given SW Vim Channel
*
*/
uint8_t osEE_vim_get_sw_int_data(OsEE_isr_channel channel) {
  uint8_t sw_int_data;

  switch (channel) {
    case SOC_XWR16XX_MSS_SYS_SW0_INT:
      sw_int_data = (uint8_t)OSEE_B_GET(TI_RCM_REG_P->SWIRQA, 8U, 0U);
    break;
    case SOC_XWR16XX_MSS_SYS_SW2_INT:
      sw_int_data = (uint8_t)OSEE_B_GET(TI_RCM_REG_P->SWIRQB, 8U, 0U);
    break;
    case SOC_XWR16XX_MSS_SYS_SW4_INT:
      sw_int_data = (uint8_t)OSEE_B_GET(TI_RCM_REG_P->SWIRQC,8U, 0U);
    break;
    case SOC_XWR16XX_MSS_SYS_SW1_INT:
      sw_int_data = (uint8_t)OSEE_B_GET(TI_RCM_REG_P->SWIRQA, 8U, 0U);
    break;
    case SOC_XWR16XX_MSS_SYS_SW3_INT:
      sw_int_data = (uint8_t)(OSEE_B_GET(TI_RCM_REG_P->SWIRQB, 8U, 16U) >> 16U);
    break;
    case SOC_XWR16XX_MSS_SYS_SW5_INT:
      sw_int_data = (uint8_t)(OSEE_B_GET(TI_RCM_REG_P->SWIRQC, 8U, 16U) >> 16);
    break;
    default:
      sw_int_data = 0U;
    break;
  }

  return sw_int_data;
}

/** @fn void osEE_vim_disable_sw_int(OsEE_isr_channel channel)
*   @brief Mask Software interrupt for given channel
*
*   @param[in] channel: vim interrupt channel
*   This function will mask Software interrupt and its data value for given
*   channel
*
*/
void osEE_vim_disable_sw_int(OsEE_isr_channel channel) {
  switch (channel) {
    case SOC_XWR16XX_MSS_SYS_SW0_INT:
      TI_RCM_REG_P->SWIRQA &= 0xFFFF0000U;
    break;
    case SOC_XWR16XX_MSS_SYS_SW2_INT:
      TI_RCM_REG_P->SWIRQB &= 0xFFFF0000U;
    break;
    case SOC_XWR16XX_MSS_SYS_SW4_INT:
      TI_RCM_REG_P->SWIRQC &= 0xFFFF0000U;
    break;
    case SOC_XWR16XX_MSS_SYS_SW1_INT:
      TI_RCM_REG_P->SWIRQA &= 0x0000FFFFU;
    break;
    case SOC_XWR16XX_MSS_SYS_SW3_INT:
      TI_RCM_REG_P->SWIRQB &= 0x0000FFFFU;
    break;
    case SOC_XWR16XX_MSS_SYS_SW5_INT:
      TI_RCM_REG_P->SWIRQC &= 0x0000FFFFU;
    break;
    default:
      /* Disable All Software interrupts */
      TI_RCM_REG_P->SWIRQA = 0x0U;
      TI_RCM_REG_P->SWIRQB = 0x0U;
      TI_RCM_REG_P->SWIRQC = 0x0U;
    break;
  }
}

#pragma CODE_STATE(osEE_cortex_r_fiq_hnd, 32)
#pragma CODE_SECTION(osEE_cortex_r_fiq_hnd, ".startup");
void osEE_cortex_r_fiq_hnd(void) {
  /* TODO */
}

void osEE_vim_phantom_interrupt(void) {
  /* Empty Handler */
}
