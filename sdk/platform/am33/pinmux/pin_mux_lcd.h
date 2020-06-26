/*
 * pin_mux_lcd.h
 *
 *  Created on: Aug 15, 2012
 *      Author: Iulian Gheorghiu morgoth2600@gmail.com
 */
/**********************************************/
#ifndef PIN_MUX_LCD_H_
#define PIN_MUX_LCD_H_
#include "driver/hw/soc_AM335x.h"
#include "driver/hw/hw_control_AM335x.h"
#include "driver/hw/hw_types.h"
/**********************************************/
unsigned int pin_mux_lcd_LCD3_beaglebone(void);
unsigned int pin_mux_lcd_AT070TN92_beaglebone(void);
unsigned int LCDPinMuxSetup(unsigned int lcd_bus_size);
/**********************************************/
#ifdef HEADER_INCLUDE_C_FILES
#include "pin_mux_lcd.c"
#endif
/**********************************************/
/**********************************************/
#endif /* PIN_MUX_LCD_H_ */
/**********************************************/
