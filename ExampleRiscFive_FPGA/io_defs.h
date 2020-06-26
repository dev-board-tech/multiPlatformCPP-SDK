/*
 * io_addrs.h
 *
 * Created: 8/4/2018 22:10:54
 *  Author: Iulian Gheorghiu
 */ 


#ifndef IO_DEFS_H_
#define IO_DEFS_H_

#include "board/RISCV/RISCV-FPGA/xio.h"

#define CPU_FREQ				(72000000)

/* Specify number of UART's and capability */
#define UART_INTERFACE_COUNT				1
#define UART_HAVE_STOP_BITS_ONE_AND_HALF	0
#define UART_HAVE_WORD_LEN_5BITS			1
#define UART_HAVE_WORD_LEN_6BITS			1
#define UART_HAVE_WORD_LEN_7BITS			1
#define UART_HAVE_WORD_LEN_9BITS			1

/* Specify number of SPI's and and number of channels per SPI interface */
#define SPI_INTERFACE_COUNT					1
#define SPI_CHANNELS_PER_INTERFACE_COUNT	4
/* Specify number of TWI's */
#define TWI_INTERFACE_COUNT					1
/* Specify number of SCREEN's to be automatically initialized */
#define SCREEN_INTERFACE_COUNT				1


#define FPGA_RTC				(*(FPGA_RTC_t *) 0x4000)  /* Port */
#define FPGA_UARTA				(*(FPGA_USART_t *) 0x4010)  /* Uart */
#define FPGA_SPIA				(*(FPGA_SPI_t *) 0x4018)  /* SPI */
#define FPGA_TWIA				(*(FPGA_TWI_t *) 0x4020)  /* TWI */
#define FPGA_PORTA				(*(FPGA_PORT_t *) 0x4040)  /* Push buttons Port */
#define FPGA_PORTB				(*(FPGA_PORT_t *) 0x4080)  /* Switch Port */
#define FPGA_PORTC				(*(FPGA_PORT_t *) 0x40C0)  /* LED's Port */
#define FPGA_PORTD				(*(FPGA_PORT_t *) 0x4100)  /* PMOD A Port */
#define FPGA_PORTE				(*(FPGA_PORT_t *) 0x4140)  /* PMOD B Port */
#define FPGA_PORTF				(*(FPGA_PORT_t *) 0x4180)  /* PMOD C Port */
#define FPGA_PORTG				(*(FPGA_PORT_t *) 0x41C0)  /* Onboard OLED display Port */
#define FPGA_GFX_ACCELA			(*(FPGA_GFX_ACCEL_t *) 0x4400)  /*  */




#endif /* IO_ADDRS_H_ */
