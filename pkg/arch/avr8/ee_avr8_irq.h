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

/** \file	ee_avr8_irq.h
 *  \brief	AVR8 IRQs.
 *
 *  This files contains the interfaces of the IRQs support for AVR8 Architecture
 *  available in Erika Enterprise.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Giuseppe Serano
 *  \date	2016
 */
#if (!defined(OSEE_AVR8_IRQ_H))
#define OSEE_AVR8_IRQ_H

/* I need base API */
#include "ee_compiler.h"

/* Macro to declare ISR1: always valid */
#define DeclareIsr1(f)  void f ( void )

/* Macro to define ISR1: always valid */
#define ISR1(f) void OSEE_COMPILER_KEEP f ( void )

/* Macro to declare ISR2: always valid */
#define DeclareIsr2(f)  void f ( void )

/* Macro to define ISR2: always valid */
#define ISR2(f) void OSEE_COMPILER_KEEP f ( void )

/*==============================================================================
                  ISR IDs in Dynamic A.P.I.s Environment
 =============================================================================*/
#if (defined(OSEE_API_DYNAMIC))

/* INT0 interrupt vector */
#define OSEE_AVR8_INT0_ISR_ID 0x00U

/* INT1 interrupt vector */
#define OSEE_AVR8_INT1_ISR_ID 0x01U

#if (defined(__AVR_ATmega128__)) || (defined(__AVR_ATmega1281__))
/* INT2 interrupt vector */
#define OSEE_AVR8_INT2_ISR_ID 0x02U

/* INT3 interrupt vector */
#define OSEE_AVR8_INT3_ISR_ID 0x03U

/* INT4 interrupt vector */
#define OSEE_AVR8_INT4_ISR_ID 0x04U

/* INT5 interrupt vector */
#define OSEE_AVR8_INT5_ISR_ID 0x05U

/* INT6 interrupt vector */
#define OSEE_AVR8_INT6_ISR_ID 0x06U

/* INT7 interrupt vector */
#define OSEE_AVR8_INT7_ISR_ID 0x07U
#endif  /* __AVR_ATmega128__ || __AVR_ATmega1281__ */

#if (                            \
  defined(__AVR_ATmega328__)  || \
  defined(__AVR_ATmega328P__) || \
  defined(__AVR_ATmega1281__)    \
)
/* PCINT0 interrupt vector */
#define OSEE_AVR8_PCINT0_ISR_ID 0x08U

/* PCINT1 interrupt vector */
#define OSEE_AVR8_PCINT1_ISR_ID 0x09U

/* PCINT2 interrupt vector */
#define OSEE_AVR8_PCINT2_ISR_ID 0x0AU

/* WDT interrupt vector */
#define OSEE_AVR8_WDT_ISR_ID    0x0BU
#endif  /* __AVR_ATmega328__ || __AVR_ATmega328P__ || __AVR_ATmega1281__ */

#if (defined(__AVR_ATmega128__))
/* TIMER2_COMP interrupt vector */
#define OSEE_AVR8_TIMER2_COMP_ISR_ID  0x0CU
#endif  /* __AVR_ATmega128__ */

#if (                            \
  defined(__AVR_ATmega328__)  || \
  defined(__AVR_ATmega328P__) || \
  defined(__AVR_ATmega1281__)    \
)
/* TIMER2_COMPA interrupt vector */
#define OSEE_AVR8_TIMER2_COMPA_ISR_ID 0x0DU

/* TIMER2_COMPB interrupt vector */
#define OSEE_AVR8_TIMER2_COMPB_ISR_ID 0x0EU
#endif  /* __AVR_ATmega328__ || __AVR_ATmega328P__ || __AVR_ATmega1281__ */

/* TIMER2_OVF interrupt vector */
#define OSEE_AVR8_TIMER2_OVF_ISR_ID   0x0FU

/* TIMER1_CAPT interrupt vector */
#define OSEE_AVR8_TIMER1_CAPT_ISR_ID  0x10U

/* TIMER1_COMPA interrupt vector */
#define OSEE_AVR8_TIMER1_COMPA_ISR_ID 0x11U

/* TIMER1_COMPB interrupt vector */
#define OSEE_AVR8_TIMER1_COMPB_ISR_ID 0x12U

#if (defined(__AVR_ATmega128__)) || (defined(__AVR_ATmega1281__))
/* TIMER1_COMPC interrupt vector */
#define OSEE_AVR8_TIMER1_COMPC_ISR_ID 0x13U
#endif  /* __AVR_ATmega128__ || __AVR_ATmega1281__ */

/* TIMER1_OVF interrupt vector */
#define OSEE_AVR8_TIMER1_OVF_ISR_ID   0x14U

#if (defined(__AVR_ATmega128__))
/* TIMER0_COMP interrupt vector */
#define OSEE_AVR8_TIMER0_COMP_ISR_ID  0x15U
#endif  /* __AVR_ATmega128__ */

#if (                            \
  defined(__AVR_ATmega328__)  || \
  defined(__AVR_ATmega328P__) || \
  defined(__AVR_ATmega1281__)    \
)
/* TIMER2_COMPA interrupt vector */
#define OSEE_AVR8_TIMER0_COMPA_ISR_ID 0x16U

/* TIMER0_COMPB interrupt vector */
#define OSEE_AVR8_TIMER0_COMPB_ISR_ID 0x17U
#endif  /* __AVR_ATmega328__ || __AVR_ATmega328P__ || __AVR_ATmega1281__ */

/* TIMER0_OVF interrupt vector */
#define OSEE_AVR8_TIMER0_OVF_ISR_ID   0x18U

/* SPI_STC interrupt vector */
#define OSEE_AVR8_SPI_STC_ISR_ID      0x19U

#if (defined(__AVR_ATmega128__)) || (defined(__AVR_ATmega1281__))
/* USART0_RX interrupt vector */
#define OSEE_AVR8_USART0_RX_ISR_ID    0x1AU

/* USART0_UDRE interrupt vector */
#define OSEE_AVR8_USART0_UDRE_ISR_ID  0x1BU

/* USART0_TX interrupt vector */
#define OSEE_AVR8_USART0_TX_ISR_ID    0x1CU
#endif  /* __AVR_ATmega128__ || __AVR_ATmega1281__ */

#if (defined(__AVR_ATmega328__)) || (defined(__AVR_ATmega328P__))
/* USART_RX interrupt vector */
#define OSEE_AVR8_USART_RX_ISR_ID     0x1DU

/* USART_UDRE interrupt vector */
#define OSEE_AVR8_USART_UDRE_ISR_ID   0x1EU

/* USART_TX interrupt vector */
#define OSEE_AVR8_USART_TX_ISR_ID     0x0FU
#endif  /* __AVR_ATmega328__ || __AVR_ATmega328P__ */

/* ADC interrupt vector */
#define OSEE_AVR8_ADC_ISR_ID          0x1FU

/* EE_READY interrupt vector */
#define OSEE_AVR8_EE_READY_ISR_ID     0x20U

/* ANALOG_COMP interrupt vector */
#define OSEE_AVR8_ANALOG_COMP_ISR_ID  0x21U

#if (defined(__AVR_ATmega128__)) || (defined(__AVR_ATmega1281__))
/* TIMER3_CAPT interrupt vector */
#define OSEE_AVR8_TIMER3_CAPT_ISR_ID  0x22U

/* TIMER3_COMPA interrupt vector */
#define OSEE_AVR8_TIMER3_COMPA_ISR_ID 0x23U

/* TIMER3_COMPB interrupt vector */
#define OSEE_AVR8_TIMER3_COMPB_ISR_ID 0x24U

/* TIMER3_COMPC interrupt vector */
#define OSEE_AVR8_TIMER3_COMPC_ISR_ID 0x25U

/* TIMER3_OVF interrupt vector */
#define OSEE_AVR8_TIMER3_OVF_ISR_ID   0x26U

/* USART1_RX interrupt vector */
#define OSEE_AVR8_USART1_RX_ISR_ID    0x27U

/* USART1_UDRE interrupt vector */
#define OSEE_AVR8_USART1_UDRE_ISR_ID  0x28U

/* USART1_TX interrupt vector */
#define OSEE_AVR8_USART1_TX_ISR_ID    0x29U
#endif  /* __AVR_ATmega128__ || __AVR_ATmega1281__ */

/* TWI interrupt vector */
#define OSEE_AVR8_TWI_ISR_ID          0x2AU

/* SPM_READY interrupt vector */
#define OSEE_AVR8_SPM_READY_ISR_ID    0x2BU

#if (defined(__AVR_ATmega1281__))
/* TIMER4_CAPT interrupt vector */
#define OSEE_AVR8_TIMER4_CAPT_ISR_ID  0x2CU

/* TIMER4_COMPA interrupt vector */
#define OSEE_AVR8_TIMER4_COMPA_ISR_ID 0x2DU

/* TIMER4_COMPB interrupt vector */
#define OSEE_AVR8_TIMER4_COMPB_ISR_ID 0x2EU

/* TIMER4_COMPC interrupt vector */
#define OSEE_AVR8_TIMER4_COMPC_ISR_ID 0x2FU

/* TIMER4_OVF interrupt vector */
#define OSEE_AVR8_TIMER4_OVF_ISR_ID   0x30U

/* TIMER5_CAPT interrupt vector */
#define OSEE_AVR8_TIMER5_CAPT_ISR_ID  0x31U

/* TIMER5_COMPA interrupt vector */
#define OSEE_AVR8_TIMER5_COMPA_ISR_ID 0x32U

/* TIMER5_COMPB interrupt vector */
#define OSEE_AVR8_TIMER5_COMPB_ISR_ID 0x33U

/* TIMER5_COMPC interrupt vector */
#define OSEE_AVR8_TIMER5_COMPC_ISR_ID 0x34U

/* TIMER5_OVF interrupt vector */
#define OSEE_AVR8_TIMER5_OVF_ISR_ID   0x35U

/* USART2_RX interrupt vector */
#define OSEE_AVR8_USART2_RX_ISR_ID    0x36U

/* USART2_UDRE interrupt vector */
#define OSEE_AVR8_USART2_UDRE_ISR_ID  0x37U

/* USART2_TX interrupt vector */
#define OSEE_AVR8_USART2_TX_ISR_ID    0x38U

/* USART3_RX interrupt vector */
#define OSEE_AVR8_USART3_RX_ISR_ID    0x39U

/* USART3_UDRE interrupt vector */
#define OSEE_AVR8_USART3_UDRE_ISR_ID  0x3AU

/* USART3_TX interrupt vector */
#define OSEE_AVR8_USART3_TX_ISR_ID    0x3BU
#endif  /* __AVR_ATmega1281__ */

#endif  /* OSEE_API_DYNAMIC */

#endif  /* !OSEE_AVR8_IRQ_H */
