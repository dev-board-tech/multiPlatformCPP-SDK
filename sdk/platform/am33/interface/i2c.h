/*
 * twi_interface.h
 *
 *  Created on: Dec 3, 2012
 *      Author: XxXx
 */
/*#####################################################*/
#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_
/*#####################################################*/
#include <stdbool.h>
#include "api/i2c.h"
#include "../aintc/aintc_twi.h"
#include "../pinmux/pin_mux_twi.h"
#include "../clk/clk_twi.h"
#include "../driver/hsi2c.h"
/*#####################################################*/
#define TWI_USE_INTERRUPTS  false
#define TWI_INT_PRIORITY  0
#define TWI_INTERFACE_COUNT 3
/*#####################################################*/
#ifdef HEADER_INCLUDE_C_FILES
#include "twi_interface.c"
#endif
/*#####################################################*/
#endif /* TWI_INTERFACE_H_ */
/*#####################################################*/
