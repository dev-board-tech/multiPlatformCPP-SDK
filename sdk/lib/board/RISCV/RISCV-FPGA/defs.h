#ifndef __RiscV_FPGA__
#define __RiscV_FPGA__

#if defined(RiscV_FPGA)

#include <include/global.h>
#include "ffconf.h"
#include "lwipopts.h"
#include "xio.h"
#include <io_defs.h>

/*
 * Processor clock selection.
 *
 * If EXTERNAL_CLOCK_VALUE id !0 the reference clock will be EXTERNAL_CLOCK_VALUE.
 * If HSE_VALUE value is 0 the reference clock will be the HSI_VALUE.
 */

#define EXTERNAL_CLOCK_VALUE    		((unsigned long)0000000)	/*!< Value of the External clock in Hz*/
#define CORE_CLOCK_DEFAULT				CPU_FREQ	/*!< Value of the Processor default clock in Hz*/

/*
 * Processor clock selection.
 */

/*
 * Debug interface setup.
 */
//#define STD_OUT_PATH			"uart-0"/* Is output is directed to serial port you need to provide the path of port */
//#define STD_OUT_PATH			"SCREEN<Terminal>"/* If output is directed to screen, need a screen name to be displayed on caption. */
//#define STD_IN_PATH				"UART:0"
//#define STD_ERR_PATH			"UART:0"
/*
 * !Debug interface setup.
 */

/*
 * Screen settings
 */

#define SCREENS_COUNT					1
#define SCREEN_CONFIG_1					lcd_fpga_1440_900_60_display_106_00_mhz
#define USED_SCREEN_CONTROLLER_1		IntScreen
#define OTHER_SCREEN_1_PARAMS			&FPGA_GFX_ACCELA

/*
 * !Screen settings
 */
/*
 * Touch screen settings
 */

#define TOUCH_SCREEN_ENABLE				false
#define CAP_TOUCHSCREEN_I2C_UNIT		"i2c-0"
#define CAP_TOUCHSCREEN_IRQ_PIN			"touchirq"
//#define USED_TOUCHSCREEN				Stmpe811

/*
 * !Touch screen settings
 */

/*
 * USB settings
 */

#define USE_USB_DEV
//#define USE_USB_HS
//#define USE_USB_FS
/* #define USE_USB_HS_IN_FS */

/*
 * !USB settings
 */

/*
 * Used fonts
 */
#define USE_FONT_CMSS14B
//#define USE_ALL_FONTS
/*
 * !Used fonts
 */

/*
 * Eth general settings
 */
#define LWIP_DEBUG_EN						false
#define MAX_DHCP_TRIES  					4

/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_ADDR0							(unsigned char) 192
#define IP_ADDR1							(unsigned char) 168
#define IP_ADDR2							(unsigned char) 0
#define IP_ADDR3							(unsigned char) 10

/*NETMASK*/
#define NETMASK_ADDR0						(unsigned char) 255
#define NETMASK_ADDR1						(unsigned char) 255
#define NETMASK_ADDR2						(unsigned char) 255
#define NETMASK_ADDR3						(unsigned char) 0

/*Gateway Address*/
#define GW_ADDR0							(unsigned char) 192
#define GW_ADDR1							(unsigned char) 168
#define GW_ADDR2							(unsigned char) 0
#define GW_ADDR3							(unsigned char) 1

/*
 * !Eth general settings
 */

/*
 * MmcSd settings
 */

#define MMCSD_INTERFACE_COUNT				0
#define USED_MMCSD_CONTROLLER_1             MmcSd_Spi
#define OTHER_MMCSD_1_PARAMS                (char *)"spi-0.1", (char *)NULL, (char *)"led-1"

/*
 * !MmcSd settings
 */

/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "defs.cpp"
#endif
/*#####################################################*/


#endif/*!FRDM_KEAZ*/
#endif
