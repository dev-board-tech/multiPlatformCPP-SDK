/*
 * io_addrs.h
 *
 * Created: 8/4/2018 22:10:54
 *  Author: Work
 */ 


#ifndef IO_DEFS_H_
#define IO_DEFS_H_

#include <board/ATMEL/Xmega-FPGA/xio.h>

#define CPU_FREQ				(100000000)

#define UART_INTERFACE_COUNT	1
#define SPI_INTERFACE_COUNT		1
#define SPI_CHANNELS_PER_INTERFACE_COUNT	4
#define TWI_INTERFACE_COUNT		1


#define FPGA_RTC				(*(FPGA_RTC_t *) 0x0040)  /* Port */
#define FPGA_PORTA				(*(FPGA_PORT_t *) 0x0060)  /* Push buttons Port */
#define FPGA_PORTB				(*(FPGA_PORT_t *) 0x0080)  /* Switch Port */
#define FPGA_PORTC				(*(FPGA_PORT_t *) 0x00A0)  /* LED's Port */
#define FPGA_PORTD				(*(FPGA_PORT_t *) 0x00C0)  /* PMOD A Port */
#define FPGA_PORTE				(*(FPGA_PORT_t *) 0x00E0)  /* PMOD B Port */
#define FPGA_PORTF				(*(FPGA_PORT_t *) 0x0100)  /* PMOD C Port */
#define FPGA_PORTG				(*(FPGA_PORT_t *) 0x0120)  /* Onboard OLED display Port */
#define FPGA_GFX_ACCELA			(*(FPGA_GFX_ACCEL_t *) 0x0300)  /*  */
#define FPGA_UARTA				(*(FPGA_USART_t *) 0x0400)  /*  */
#define FPGA_SPIA				(*(FPGA_SPI_t *) 0x0600)  /*  */
#define FPGA_TWIA				(*(FPGA_TWI_t *) 0x0800)  /*  */

#define RST_vect				_VECTOR(0)
#define RTC_vect				_VECTOR(1)
#define PORTA_vect				_VECTOR(2)
#define PORTB_vect				_VECTOR(3)
#define PORTC_vect				_VECTOR(4)
#define PORTD_vect				_VECTOR(5)
#define PORTE_vect				_VECTOR(6)
#define PORTF_vect				_VECTOR(7)
#define SPI_A_vect				_VECTOR(8)
#define UART_A_RXC_vect			_VECTOR(9)
#define UART_A_TXC_vect			_VECTOR(10)
#define UART_A_DRE_vect			_VECTOR(11)



#endif /* IO_ADDRS_H_ */