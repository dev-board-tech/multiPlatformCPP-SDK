/*
 * defs.cpp
 */
#if defined(RiscV_FPGA)

#if __AVR_XMEGA__
#include <avr/pgmspace.h>
#endif

#include "defs.h"
#include <stdio.h>

#include <api/gpio.h>
#include <api/spi.h>
#include <api/i2c.h>
#include <api/uart.h>

ioSetCfgGpio(push_0, 		"phbtn-0",		pin_mux_convert_to_pin(IOA,  0),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(push_1, 		"phbtn-1",		pin_mux_convert_to_pin(IOA,  1),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(push_2, 		"phbtn-2",		pin_mux_convert_to_pin(IOA,  2),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(push_3, 		"phbtn-3",		pin_mux_convert_to_pin(IOA,  3),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(push_4, 		"phbtn-4",		pin_mux_convert_to_pin(IOA,  4),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(sw_0, 			"hbtn-0",		pin_mux_convert_to_pin(IOB,  0),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(sw_1, 			"hbtn-1",		pin_mux_convert_to_pin(IOB,  1),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(sw_2, 			"hbtn-2",		pin_mux_convert_to_pin(IOB,  2),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(sw_3, 			"hbtn-3",		pin_mux_convert_to_pin(IOB,  3),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(sw_4, 			"hbtn-4",		pin_mux_convert_to_pin(IOB,  4),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(sw_5, 			"hbtn-5",		pin_mux_convert_to_pin(IOB,  5),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(sw_6, 			"hbtn-6",		pin_mux_convert_to_pin(IOB,  6),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(sw_7, 			"hbtn-7",		pin_mux_convert_to_pin(IOB,  7),CfgGpio::GPIO_IN_FLOATING,		false,	false,	0);
ioSetCfgGpio(led_0, 		"led-0",		pin_mux_convert_to_pin(IOC,  0),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	0);
ioSetCfgGpio(led_1, 		"led-1",		pin_mux_convert_to_pin(IOC,  1),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	0);
ioSetCfgGpio(led_2, 		"led-2",		pin_mux_convert_to_pin(IOC,  2),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	0);
ioSetCfgGpio(led_3, 		"led-3",		pin_mux_convert_to_pin(IOC,  3),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	0);
ioSetCfgGpio(led_4, 		"led-4",		pin_mux_convert_to_pin(IOC,  4),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	0);
ioSetCfgGpio(led_5, 		"led-5",		pin_mux_convert_to_pin(IOC,  5),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	0);
ioSetCfgGpio(led_6, 		"led-6",		pin_mux_convert_to_pin(IOC,  6),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	0);
ioSetCfgGpio(led_7, 		"led-7",		pin_mux_convert_to_pin(IOC,  7),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	0);

ioSetCfgGpio(ug2832_dc, 	"oled-dc",		pin_mux_convert_to_pin(IOG,  0),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	0);
ioSetCfgGpio(ug2832_rst, 	"oled-res",		pin_mux_convert_to_pin(IOG,  1),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	1);
ioSetCfgGpio(ug2832_vbat, 	"oled-vba",		pin_mux_convert_to_pin(IOG,  2),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	0);
ioSetCfgGpio(ug2832_vdd, 	"oled-vdd",		pin_mux_convert_to_pin(IOG,  3),CfgGpio::GPIO_OUT_PUSH_PULL, 	false,	false,	0);

ioSetCfgUart(uart_0, "uart-0", pin_mux_convert_to_pin(IOA, 0)	, pin_mux_convert_to_pin(IOA, 0)	, 115200	, CfgUart::WORD_LEN_8	, CfgUart::STOP_BITS_ONE	, CfgUart::PAR_NONE	, CfgUart::MODE_ASYNC);

ioSetCfgI2c(i2c_0, "i2c-0", pin_mux_convert_to_pin(IOA, 0), pin_mux_convert_to_pin(IOA, 0), 400000);

ioSetCfgSpi(spi_0_0, "spi-0.0", pin_mux_convert_to_pin(IOA,  0), pin_mux_convert_to_pin(IOA,  0), pin_mux_convert_to_pin(IOA,  0), pin_mux_convert_to_pin(IOA, 0), CfgSpi::spiMode0, 15000000, false);

ioSetCfgEnd(ioTableEnd);

ioSettings *ioSetCfg[] = {
	&push_0,
	&push_1,
	&push_2,
	&push_3,
	&push_4,
	&sw_0,
	&sw_1,
	&sw_2,
	&sw_3,
	&sw_4,
	&sw_5,
	&sw_6,
	&sw_7,
	&led_0,
	&led_1,
	&led_2,
	&led_3,
	&led_4,
	&led_5,
	&led_6,
	&led_7,
	&ug2832_dc,
	&ug2832_rst,
	&ug2832_vbat,
	&ug2832_vdd,
	&uart_0,
	&i2c_0,
	&spi_0_0,
	&ioTableEnd,
	(ioSettings *)-1/* This is an artifice to force linker to put this structure ito .data section, to be sure that this will be initiated before the call of init() function. */
};

#endif/*!FRDM_KEAZ*/
