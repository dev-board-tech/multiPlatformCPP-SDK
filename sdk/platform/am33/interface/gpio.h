/*
 * gpio_interface.h
 *
 *  Created on: Dec 2, 2012
 *      Author: XxXx
 */
/*#####################################################*/
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_
/*#####################################################*/
#include <stdbool.h>
#include "api/gpio.h"
#include "clk/clk_gpio.h"
#include "pinmux/pin_mux_gpio.h"
#include "driver/gpio_v2.h"
/*#####################################################*/

#define HAVE_GPIO_IN_FLOATING
#define HAVE_GPIO_IN_PULL_DOWN
#define HAVE_GPIO_IN_PULL_UP
#define HAVE_GPIO_OUT_PUSH_PULL

#define _GPIO_FAST_SET_PIN(base_addr, pin)\
		HWREG(base_addr + GPIO_SETDATAOUT) = 1 << (pin % 32)

#define _GPIO_FAST_CLEAR_PIN(base_addr, pin)\
		HWREG(base_addr + GPIO_CLEARDATAOUT) = 1 << (pin % 32)

#define _GPIO_FAST_WRITE_MULTI_PIN(base_addr, mask, pin_mask)\
		HWREG(base_addr + GPIO_DATAOUT) = (HWREG(base_addr + GPIO_DATAOUT) & ~mask) | ((pin_mask) & mask)



#define dir_in	GPIO_DIR_INPUT
#define dir_out	GPIO_DIR_OUTPUT

/*#####################################################*/
#ifdef HEADER_INCLUDE_C_FILES
#include "gpio.cpp"
#endif
/*#####################################################*/
#endif /* GPIO_INTERFACE_H_ */
/*#####################################################*/
