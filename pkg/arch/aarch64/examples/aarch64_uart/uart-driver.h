#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "ee_internal.h"

/******************************************************************************
 * Types
 *****************************************************************************/
typedef enum {
	UART_A = 0,
	UART_B,
	UART_C,
	UART_D,
	MAX_UART_ID
} UART_id_t;

typedef enum{
	UART_BAUD_9600 = 0,
	UART_BAUD_38400,
	UART_BAUD_115200,
	MAX_UART_BAUD 
}UART_baudrate_t;

typedef void (*UART_callback_t)(char);

/******************************************************************************
 * API
 *****************************************************************************/
uint8_t UART_init( UART_id_t id, UART_baudrate_t baudrate);
uint32_t UART_write( UART_id_t id, const void * buffer, uint32_t size);
void UART_set_callback( UART_id_t id, UART_callback_t rx_callback); 

#endif /* UART_DRIVER_H*/

