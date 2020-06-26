/*
 * aintc_uart.h
 *
 *  Created on: Dec 1, 2012
 *      Author: XxXx
 */
/*#####################################################*/
#ifndef AINTC_UART_H_
#define AINTC_UART_H_
/*#####################################################*/
#include "api/uart.h"
/*#####################################################*/
typedef struct
{
	Uart_t* Uart0;
	Uart_t* Uart1;
	Uart_t* Uart2;
	Uart_t* Uart3;
	Uart_t* Uart4;
	Uart_t* Uart5;
}Uart_Int_Service_t;
/*#####################################################*/
void UARTAINTCConfigure(Uart_t* _UartStruct);
void UARTAINTCUnConfigure(Uart_t* UartStruct);
/*#####################################################*/
#ifdef HEADER_INCLUDE_C_FILES
#include "aintc_uart.c"
#endif
/*#####################################################*/
extern Uart_Int_Service_t Uart_Int_Service;
/*#####################################################*/
#endif /* AINTC_UART_H_ */
