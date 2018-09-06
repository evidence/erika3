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

/** @file	ee_dspic33ev_ic.v
 *  @brief	Microchip dsPIC33EV MCU Interrupt Controller Driver Sources.
 *  @author	Giuseppe Serano
 *  @date	2018
 */ 

#include "ee_internal.h"

#if	defined(OSEE_API_DYNAMIC)

FUNC(void, OS_CODE) osEE_dspic33_pic24_ic_set_int_src(
  VAR(OsEE_isr_src_id, AUTOMATIC)	src,
  VAR(OsEE_reg, AUTOMATIC)		prio,
  VAR(OsEE_bool, AUTOMATIC)		en
) {

  switch (src)
  {

    case OSEE_DSPIC33_PIC24_INT0_ISR_ID:
      IPC0bits.INT0IP = prio;	/* Set Priority Level. */
      IFS0bits.INT0IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.INT0IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_IC1_ISR_ID:
      IPC0bits.IC1IP = prio;	/* Set Priority Level. */
      IFS0bits.IC1IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.IC1IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_OC1_ISR_ID:
      IPC0bits.OC1IP = prio;	/* Set Priority Level. */
      IFS0bits.OC1IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.OC1IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_T1_ISR_ID:
      IPC0bits.T1IP = prio;	/* Set Priority Level. */
      IFS0bits.T1IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.T1IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_DMA0_ISR_ID:
      IPC1bits.DMA0IP = prio;	/* Set Priority Level. */
      IFS0bits.DMA0IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.DMA0IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_IC2_ISR_ID:
      IPC1bits.IC2IP = prio;	/* Set Priority Level. */
      IFS0bits.IC2IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.IC2IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_OC2_ISR_ID:
      IPC1bits.OC2IP = prio;	/* Set Priority Level. */
      IFS0bits.OC2IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.OC2IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_T2_ISR_ID:
      IPC1bits.T2IP = prio;	/* Set Priority Level. */
      IFS0bits.T2IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.T2IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_T3_ISR_ID:
      IPC2bits.T3IP = prio;	/* Set Priority Level. */
      IFS0bits.T3IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.T3IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_SPI1E_ISR_ID:
      IPC2bits.SPI1EIP = prio;	/* Set Priority Level. */
      IFS0bits.SPI1EIF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.SPI1EIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_SPI1_ISR_ID:
      IPC2bits.SPI1IP = prio;	/* Set Priority Level. */
      IFS0bits.SPI1IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.SPI1IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_U1RX_ISR_ID:
      IPC2bits.U1RXIP = prio;	/* Set Priority Level. */
      IFS0bits.U1RXIF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.U1RXIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_U1TX_ISR_ID:
      IPC3bits.U1TXIP = prio;	/* Set Priority Level. */
      IFS0bits.U1TXIF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.U1TXIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_AD1_ISR_ID:
      IPC3bits.AD1IP = prio;	/* Set Priority Level. */
      IFS0bits.AD1IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.AD1IE = en;	/* Enableinterrupt. */
      break;
    
    case OSEE_DSPIC33_PIC24_DMA1_ISR_ID:
      IPC3bits.DMA1IP = prio;	/* Set Priority Level. */
      IFS0bits.DMA1IF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.DMA1IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_NVM_ISR_ID:
      IPC3bits.NVMIP = prio;	/* Set Priority Level. */
      IFS0bits.NVMIF = 0U;	/* Clear Interrupt Flag. */
      IEC0bits.NVMIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_SI2C1_ISR_ID:
      IPC4bits.SI2C1IP = prio;	/* Set Priority Level. */
      IFS1bits.SI2C1IF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.SI2C1IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_MI2C1_ISR_ID:
      IPC4bits.MI2C1IP = prio;	/* Set Priority Level. */
      IFS1bits.MI2C1IF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.MI2C1IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_CMP1_ISR_ID:
      IPC4bits.CMIP = prio;	/* Set Priority Level. */
      IFS1bits.CMIF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.CMIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_CN_ISR_ID:
      IPC4bits.CNIP = prio;	/* Set Priority Level. */
      IFS1bits.CNIF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.CNIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_INT1_ISR_ID:
      IPC5bits.INT1IP = prio;	/* Set Priority Level. */
      IFS1bits.INT1IF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.INT1IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_DMA2_ISR_ID:
      IPC6bits.DMA2IP = prio;	/* Set Priority Level. */
      IFS1bits.DMA2IF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.DMA2IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_OC3_ISR_ID:
      IPC6bits.OC3IP = prio;	/* Set Priority Level. */
      IFS1bits.OC3IF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.OC3IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_OC4_ISR_ID:
      IPC6bits.OC4IP = prio;	/* Set Priority Level. */
      IFS1bits.OC4IF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.OC4IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_T4_ISR_ID:
      IPC6bits.T4IP = prio;	/* Set Priority Level. */
      IFS1bits.T4IF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.T4IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_T5_ISR_ID:
      IPC7bits.T5IP = prio;	/* Set Priority Level. */
      IFS1bits.T5IF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.T5IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_INT2_ISR_ID:
      IPC7bits.INT2IP = prio;	/* Set Priority Level. */
      IFS1bits.INT2IF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.INT2IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_U2RX_ISR_ID:
      IPC7bits.U2RXIP = prio;	/* Set Priority Level. */
      IFS1bits.U2RXIF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.U2RXIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_U2TX_ISR_ID:
      IPC7bits.U2TXIP = prio;	/* Set Priority Level. */
      IFS1bits.U2TXIF = 0U;	/* Clear Interrupt Flag. */
      IEC1bits.U2TXIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_SPI2E_ISR_ID:
      IPC8bits.SPI2EIP = prio;	/* Set Priority Level. */
      IFS2bits.SPI2EIF = 0U;	/* Clear Interrupt Flag. */
      IEC2bits.SPI2EIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_SPI2_ISR_ID:
      IPC8bits.SPI2IP = prio;	/* Set Priority Level. */
      IFS2bits.SPI2IF = 0U;	/* Clear Interrupt Flag. */
      IEC2bits.SPI2IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_C1RX_ISR_ID:
      IPC8bits.C1RXIP = prio;	/* Set Priority Level. */
      IFS2bits.C1RXIF = 0U;	/* Clear Interrupt Flag. */
      IEC2bits.C1RXIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_C1_ISR_ID:
      IPC8bits.C1IP = prio;	/* Set Priority Level. */
      IFS2bits.C1IF = 0U;	/* Clear Interrupt Flag. */
      IEC2bits.C1IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_DMA3_ISR_ID:
      IPC9bits.DMA3IP = prio;	/* Set Priority Level. */
      IFS2bits.DMA3IF = 0U;	/* Clear Interrupt Flag. */
      IEC2bits.DMA3IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_IC3_ISR_ID:
      IPC9bits.IC3IP = prio;	/* Set Priority Level. */
      IFS2bits.IC3IF = 0U;	/* Clear Interrupt Flag. */
      IEC2bits.IC3IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_IC4_ISR_ID:
      IPC9bits.IC4IP = prio;	/* Set Priority Level. */
      IFS2bits.IC4IF = 0U;	/* Clear Interrupt Flag. */
      IEC2bits.IC4IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_PSEM_ISR_ID:
      IPC14bits.PSEMIP = prio;	/* Set Priority Level. */
      IFS3bits.PSEMIF = 0U;	/* Clear Interrupt Flag. */
      IEC3bits.PSEMIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_U1E_ISR_ID:
      IPC16bits.U1EIP = prio;	/* Set Priority Level. */
      IFS4bits.U1EIF = 0U;	/* Clear Interrupt Flag. */
      IEC4bits.U1EIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_U2E_ISR_ID:
      IPC16bits.U2EIP = prio;	/* Set Priority Level. */
      IFS4bits.U2EIF = 0U;	/* Clear Interrupt Flag. */
      IEC4bits.U2EIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_C1TX_ISR_ID:
      IPC17bits.C1TXIP = prio;	/* Set Priority Level. */
      IFS4bits.C1TXIF = 0U;	/* Clear Interrupt Flag. */
      IEC4bits.C1TXIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_CTMU_ISR_ID:
      IPC19bits.CTMUIP = prio;	/* Set Priority Level. */
      IFS4bits.CTMUIF = 0U;	/* Clear Interrupt Flag. */
      IEC4bits.CTMUIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_PWM1_ISR_ID:
      IPC23bits.PWM1IP = prio;	/* Set Priority Level. */
      IFS5bits.PWM1IF = 0U;	/* Clear Interrupt Flag. */
      IEC5bits.PWM1IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_PWM2_ISR_ID:
      IPC23bits.PWM2IP = prio;	/* Set Priority Level. */
      IFS5bits.PWM2IF = 0U;	/* Clear Interrupt Flag. */
      IEC5bits.PWM2IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_PWM3_ISR_ID:
      IPC24bits.PWM3IP = prio;	/* Set Priority Level. */
      IFS6bits.PWM3IF = 0U;	/* Clear Interrupt Flag. */
      IEC6bits.PWM3IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_ICD_ISR_ID:
      IPC35bits.ICDIP = prio;	/* Set Priority Level. */
      IFS8bits.ICDIF = 0U;	/* Clear Interrupt Flag. */
      IEC8bits.ICDIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_I2C1_ISR_ID:
      IPC43bits.I2C1BCIP = prio;	/* Set Priority Level. */
      IFS10bits.I2C1BCIF = 0U;	/* Clear Interrupt Flag. */
      IEC10bits.I2C1BCIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_SENT1ERR_ISR_ID:
      IPC45bits.SENT1EIP = prio;	/* Set Priority Level. */
      IFS11bits.SENT1EIF = 0U;	/* Clear Interrupt Flag. */
      IEC11bits.SENT1EIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_SENT1_ISR_ID:
      IPC45bits.SENT1IP = prio;	/* Set Priority Level. */
      IFS11bits.SENT1IF = 0U;	/* Clear Interrupt Flag. */
      IEC11bits.SENT1IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_SENT2ERR_ISR_ID:
      IPC46bits.SENT2EIP = prio;	/* Set Priority Level. */
      IFS11bits.SENT2EIF = 0U;	/* Clear Interrupt Flag. */
      IEC11bits.SENT2EIE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_SENT2_ISR_ID:
      IPC46bits.SENT2IP = prio;	/* Set Priority Level. */
      IFS11bits.SENT2IF = 0U;	/* Clear Interrupt Flag. */
      IEC11bits.SENT2IE = en;	/* Enableinterrupt. */
      break;

    case OSEE_DSPIC33_PIC24_ECCSBE_ISR_ID:
      IPC46bits.ECCSBEIP = prio;	/* Set Priority Level. */
      IFS11bits.ECCSBEIF = 0U;	/* Clear Interrupt Flag. */
      IEC11bits.ECCSBEIE = en;	/* Enableinterrupt. */
      break;

    default:
      break;

  }

}	/* osEE_dspic33_pic24_ic_set_int_src() */

#if	0	/* [GS]: Not used for now! */

FUNC(void, OS_CODE) osEE_dspic33_pic24_ic_clr_int_src(
  VAR(OsEE_isr_src_id, AUTOMATIC)	src
) {

  switch (src)
  {

    case OSEE_DSPIC33_PIC24_OSCFAIL_ISR_ID:
      INTCON1bits.OSCFAIL = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_ADDRERR_ISR_ID:
      INTCON1bits.ADDRERR = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_SGHT_ISR_ID:
      INTCON2bits.SWTRAP = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_STKERR_ISR_ID:
      INTCON1bits.STKERR = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_MATHERR_ISR_ID:
      INTCON1bits.MATHERR = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_DMACERR_ISR_ID:
      INTCON1bits.DMACERR = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_INT0_ISR_ID:
      IFS0bits.INT0IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_IC1_ISR_ID:
      IFS0bits.IC1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_OC1_ISR_ID:
      IFS0bits.OC1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_T1_ISR_ID:
      IFS0bits.T1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_DMA0_ISR_ID:
      IFS0bits.DMA0IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_IC2_ISR_ID:
      IFS0bits.IC2IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_OC2_ISR_ID:
      IFS0bits.OC2IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_T2_ISR_ID:
      IFS0bits.T2IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_T3_ISR_ID:
      IFS0bits.T3IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_SPI1E_ISR_ID:
      IFS0bits.SPI1EIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_SPI1_ISR_ID:
      IFS0bits.SPI1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_U1RX_ISR_ID:
      IFS0bits.U1RXIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_U1TX_ISR_ID:
      IFS0bits.U1TXIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_AD1_ISR_ID:
      IFS0bits.AD1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_DMA1_ISR_ID:
      IFS0bits.DMA1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_NVM_ISR_ID:
      IFS0bits.NVMIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_SI2C1_ISR_ID:
      IFS1bits.SI2C1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_MI2C1_ISR_ID:
      IFS1bits.MI2C1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_CMP1_ISR_ID:
      IFS1bits.CMIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_CN_ISR_ID:
      IFS1bits.CNIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_INT1_ISR_ID:
      IFS1bits.INT1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_DMA2_ISR_ID:
      IFS1bits.DMA2IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_OC3_ISR_ID:
      IFS1bits.OC3IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_OC4_ISR_ID:
      IFS1bits.OC4IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_T4_ISR_ID:
      IFS1bits.T4IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_T5_ISR_ID:
      IFS1bits.T5IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_INT2_ISR_ID:
      IFS1bits.INT2IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_U2RX_ISR_ID:
      IFS1bits.U2RXIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_U2TX_ISR_ID:
      IFS1bits.U2TXIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_SPI2E_ISR_ID:
      IFS2bits.SPI2EIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_SPI2_ISR_ID:
      IFS2bits.SPI2IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_C1RX_ISR_ID:
      IFS2bits.C1RXIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_C1_ISR_ID:
      IFS2bits.C1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_DMA3_ISR_ID:
      IFS2bits.DMA3IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_IC3_ISR_ID:
      IFS2bits.IC3IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_IC4_ISR_ID:
      IFS2bits.IC4IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_PSEM_ISR_ID:
      IFS3bits.PSEMIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_U1E_ISR_ID:
      IFS4bits.U1EIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_U2E_ISR_ID:
      IFS4bits.U2EIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_C1TX_ISR_ID:
      IFS4bits.C1TXIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_CTMU_ISR_ID:
      IFS4bits.CTMUIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_PWM1_ISR_ID:
      IFS5bits.PWM1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_PWM2_ISR_ID:
      IFS5bits.PWM2IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_PWM3_ISR_ID:
      IFS6bits.PWM3IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_ICD_ISR_ID:
      IFS8bits.ICDIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_I2C1_ISR_ID:
      IFS10bits.I2C1BCIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_SENT1ERR_ISR_ID:
      IFS11bits.SENT1EIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_SENT1_ISR_ID:
      IFS11bits.SENT1IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_SENT2ERR_ISR_ID:
      IFS11bits.SENT2EIF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_SENT2_ISR_ID:
      IFS11bits.SENT2IF = 0U;	/* Clear Interrupt Flag. */
      break;

    case OSEE_DSPIC33_PIC24_ECCSBE_ISR_ID:
      IFS11bits.ECCSBEIF = 0U;	/* Clear Interrupt Flag. */
      break;

    default:
      break;

  }

}	/* osEE_dspic33_pic24_ic_clr_int_src() */

#endif	/* 0 - [GS]: Not used for now! */

#endif	/* !OSEE_API_DYNAMIC */
