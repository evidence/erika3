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

#include "uart-driver.h"
#include <inmate.h>
/******************************************************************************
 * Macros
 *****************************************************************************/
/*#define UART_SET_BAUDRATE*/ /* Enable this for baudrate set in DLL, DLM */

#define UART_MAX_NUMBER (4)

/* Devices base addresses */
#define UART_A_BASE	(uint64_t*)(0x70006000)
#define UART_B_BASE	(uint64_t*)(0x70006040)
#define UART_C_BASE	(uint64_t*)(0x70006200)
#define UART_D_BASE	(uint64_t*)(0x70006300)

/* Devices IRQ */
#define UART_A_IRQ	(36)
#define UART_B_IRQ	(37)
#define UART_C_IRQ	(46)
#define UART_D_IRQ	(90)
#define IRQ_BASE	(32)

/* Registers offset */
#define UART_TX		0x0
#define UART_RX		0x0
#define UART_DLL	0x0
#define UART_DLM	0x4
#define UART_IER	(UART_DLM)
#define UART_FCR	0x8
#define UART_MCR	0x10  
#define UART_LCR	0xc
#define UART_LSR	0x14
#define UART_RX_FIFO_CFG    0x24
#define UART_CONT_STAT_REG  0X2c

/* Flags */
#define UART_LCR_8N1		0x03
#define UART_LCR_DLAB		0x80
#define UART_LSR_THRE		0x20
#define UART_RX_TRIG_VAL	0x1
#define UART_RX_TRIG_ENBL	0x80
/* Fifo masks*/
#define UART_FIFO_EN     (1)
/* Setting the bit 0 of IER Register enables  Receive Data Interrupt*/
#define UART_IE_RHR      (1)
#define UART_IE_EORD     (1 << 5)
/* UART RX DATA Flag is bit 0 of LSR */
#define UART_RX_DATA     (1)

/* Divisor values */
#define UART_DIV_9600	(156)
#define UART_DIV_38400	(39)
#define UART_DIV_115200	(13)
#define UART_DIV_VALUES	(3)

#if 0 
#define UART1_CLOCK_REGISTER  (0x60006000 + 0x32c)
#define UART1_CLOCK_ENABLE    (1 << 23)
#endif

/******************************************************************************
 * Types
 *****************************************************************************/
typedef struct {
        /* System info */
        uint64_t *base;
        uint32_t irq;
	void (*isr)(void);
        /* User info */
        UART_callback_t callback;
} UART_dev_t;

/******************************************************************************
 * Utility
 *****************************************************************************/
static bool uart_is_busy(uint64_t *base);
static void uart_write_char(uint64_t *base, char c);
static void uart_read( UART_id_t id );

/* Defining ISR */
static void UART_ISR_UART_A(void);
static void UART_ISR_UART_B(void);
static void UART_ISR_UART_C(void);
static void UART_ISR_UART_D(void);

/******************************************************************************
 * Internal structures
 *****************************************************************************/
static UART_dev_t devices[UART_MAX_NUMBER] = {
				/* UART A */
				{
					.base = UART_A_BASE,
					.irq = UART_A_IRQ,
					.isr = UART_ISR_UART_A,
					.callback = NULL,
				},
				/* UART B */
				{
					.base = UART_B_BASE,
					.irq = UART_B_IRQ,
					.isr = UART_ISR_UART_B,
					.callback = NULL,

				},
				/* UART C*/
				{		
					.base = UART_C_BASE,
					.irq = UART_C_IRQ,
					.isr = UART_ISR_UART_C,
					.callback = NULL,

				},
				/* UART D*/
				{
					.base = UART_D_BASE,
					.irq = UART_D_IRQ,
					.isr = UART_ISR_UART_D,
					.callback = NULL,
				}

			};

#ifdef UART_SET_BAUDRATE
/* Divider map */
static uint32_t divider_values[UART_DIV_VALUES] = {UART_DIV_9600, UART_DIV_38400,
							 UART_DIV_115200};
#endif

/******************************************************************************
 * Static functions
 *****************************************************************************/
/* Defining ISR */
static void UART_ISR_UART_A(void)
{
	uart_read(UART_A);
}

static void UART_ISR_UART_B(void)
{
	uart_read(UART_B);

}

static void UART_ISR_UART_C(void)
{
	uart_read(UART_C);
}

static void UART_ISR_UART_D(void)
{
	uart_read(UART_D);

}


static bool uart_is_busy(uint64_t *base)
{
  return !(osEE_mmio_read32((uint64_t)base + UART_LSR) & UART_LSR_THRE);
}

static void uart_write_char(uint64_t *base, char c)
{
  osEE_mmio_write32((uint64_t)base + UART_TX, c);
}

static void uart_read( UART_id_t id ){
	if( id >= 0 && id < UART_MAX_NUMBER ){
		/* getting chars */
		UART_dev_t *device = devices + id;
		while((osEE_mmio_read32((uint64_t) device->base + UART_LSR) & UART_RX_DATA) ){
        		char recv = (char) osEE_mmio_read32((uint64_t) device->base + UART_RX)
									 & 0x000000FF;
		
			/* Calling callback */
			if(device->callback)
				device->callback(recv);
  		}		

	}
}


/******************************************************************************
 * API
 *****************************************************************************/
uint8_t UART_init( UART_id_t id, 
#ifdef UART_SET_BAUDRATE
	__attribute_((unused))
#endif
				UART_baudrate_t baudrate)
{
	uint8_t result = 0;
	if((id >= 0) && (id < UART_MAX_NUMBER)){
		UART_dev_t *dev = devices +id;
		uint64_t base = (uint64_t) dev->base;
#ifdef UART_SET_BAUDRATE
		uint32_t divider = divider_values[UART_BAUD_9600];
#endif

		/*Setting MCR in order to disable loopback mode*/
  		osEE_mmio_write32(base + UART_MCR, 0);
 		/*Setting FCR in order to enable FIFO mode and disable DMA mode*/
		osEE_mmio_write32(base + UART_FCR, UART_FIFO_EN);
  		/* Enabling the interrut on Rx data */
  		osEE_mmio_write32(base + UART_LCR, 0);
  		osEE_mmio_write32(base + UART_IER, UART_IE_RHR);
		/* Enabling and configuring the RX Fifo trigger level*/
  		osEE_mmio_write32(base + UART_RX_FIFO_CFG, UART_RX_TRIG_VAL | UART_RX_TRIG_ENBL);

#ifdef UART_SET_BAUDRATE		
		if( baudrate >= 0 || baudrate < UART_DIV_VALUES)
			/*setting default baudrate */
			divider = divider_values[baudrate];

		/*Setting LCR for DLM acess*/
  		osEE_mmio_write32(base + UART_LCR, UART_LCR_DLAB);
  		/*Setting DLL with divider*/
		osEE_mmio_write32(base + UART_DLL, divider);
  		osEE_mmio_write32(base + UART_DLM, 0);
  		/*Setting LCR for 8n1 mode*/
#endif
  		osEE_mmio_write32(base + UART_LCR, UART_LCR_8N1);

		TaskType isr_uart_id;
		/* Setting the handler */
		CreateTask( &isr_uart_id, OSEE_TASK_TYPE_ISR2, dev->isr ,1U, 1U, 1U, OSEE_SYSTEM_STACK );
		/* Tie ISR2 With IRQ */
		SetISR2Source(isr_uart_id, dev->irq + IRQ_BASE);

		result = 1;
	}

	return result;
}

uint32_t UART_write( UART_id_t id, const void * buffer, uint32_t size)
{
	uint32_t written = 0;
	if(( id >= 0 && id < UART_MAX_NUMBER) && (buffer != NULL) && (size > 0)){
		UART_dev_t *device = devices + id;
		uint64_t *base = device->base;
		uint32_t to_be_written = size;
		char *char_buffer = (char *)buffer;
		while(to_be_written){
#if 1 
			while(uart_is_busy(base))
				;
#endif
			uart_write_char(base, char_buffer[written++]);
			to_be_written--;
		}
	}
	return written;
}

void UART_set_callback( UART_id_t id, UART_callback_t rx_callback)
{
	if(( id >= 0 && id < UART_MAX_NUMBER) && (rx_callback != NULL)){
		UART_dev_t *device = devices + id;
                device->callback = rx_callback;
	}
	return;
}


