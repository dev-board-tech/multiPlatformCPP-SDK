/*
 * defs.cpp
 */
#if defined(CC1310LauchPad)

#include "defs.h"
#include <stdio.h>

#include <api/gpio.h>
#include <api/spi.h>
#include <api/i2c.h>
#include <api/uart.h>

/* IO initialization table */
ioSetCfgGpio(led_0,     "led-0",    pin_mux_convert_to_pin(IOA, 6),CfgGpio::GPIO_OUT_PUSH_PULL,    false, false, 0);
ioSetCfgGpio(led_1,     "led-1",    pin_mux_convert_to_pin(IOA, 7),CfgGpio::GPIO_OUT_PUSH_PULL,    false, false, 0);
ioSetCfgGpio(hbtn_0,    "hbtn-0",   pin_mux_convert_to_pin(IOA, 13),CfgGpio::GPIO_IN_PULL_UP,       false, false, 0);
ioSetCfgGpio(hbtn_1,    "hbtn-1",   pin_mux_convert_to_pin(IOA, 14),CfgGpio::GPIO_IN_PULL_UP,       false, false, 0);

//ioSetCfgUart(uart_0,    "uart-0",   pin_mux_convert_to_pin(IOA,  3) , pin_mux_convert_to_pin(IOA, 2)    , 115200    , CfgUart::WORD_LEN_8   , CfgUart::STOP_BITS_ONE    , CfgUart::PAR_NONE , CfgUart::MODE_ASYNC);

//ioSetCfgI2c(i2c_0,      "i2c-0",    pin_mux_convert_to_pin(IOA,  8) , pin_mux_convert_to_pin(IOC, 9), 100000);

ioSetCfgSpi(spi_0_0,    "spi-0.0",  pin_mux_convert_to_pin(IOA, 10) , pin_mux_convert_to_pin(IOA, 9), pin_mux_convert_to_pin(IOA, 8), pin_mux_convert_to_pin(IOA,14), CfgSpi::spiMode0,20000000, false);//LCD

ioSetCfgEnd(ioTableEnd);

ioSettings *ioSetCfg[] = {
        &led_0,
        &led_1,
        &hbtn_0,
        &hbtn_1,
        //&uart_0,
        //&i2c_0,
        &spi_0_0,
        //&spi_0_1,
        //&spi_0_2,
        &ioTableEnd,
        (ioSettings *)-1/* This is an artifice to force linker to put this structure into '.data' section, to be sure that this will be initiated before the call of init() function. */
};

#endif/*!STM32F769I_DISCO*/
