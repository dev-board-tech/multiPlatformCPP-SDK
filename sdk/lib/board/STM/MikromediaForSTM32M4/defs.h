#ifndef __MikromediaForSTM32M4__
#define __MikromediaForSTM32M4__

#if defined(MikromediaForSTM32M4)

#include "ffconf.h"
#include "lwipopts.h"
#include <api/lcd_def.h>

/*
 * Processor choose
 */
//#define STM32F405xx
//#define STM32F415xx
#define STM32F407xx
//#define STM32F417xx
//#define STM32F427xx
//#define STM32F437xx
//#define STM32F429xx
//#define STM32F439xx
//#define STM32F401xC
//#define STM32F401xE
//#define STM32F410Tx
//#define STM32F410Cx
//#define STM32F410Rx
//#define STM32F411xE
//#define STM32F446xx
//#define STM32F469xx
//#define STM32F479xx

/*
 * !Processor choose
 */

/*
 * Processor clock selection.
 *
 * If EXTERNAL_CLOCK_VALUE id !0 the reference clock will be EXTERNAL_CLOCK_VALUE.
 * If HSE_VALUE value is 0 the reference clock will be the HSI_VALUE.
 */

#define HSE_VALUE						((uint32_t)0000000)	/*!< Value of the External oscillator in Hz*/
#define LSE_VALUE  						((uint32_t)32768)		/*!< Value of the External Low Speed oscillator in Hz */
#define EXTERNAL_CLOCK_VALUE    		((uint32_t)0000000)	/*!< Value of the External clock in Hz*/
#define CORE_CLOCK_DEFAULT				((uint32_t)168000000)	/*!< Value of the Processor default clock in Hz*/
#define USE_EXT_RAM						false
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
#define SCREEN_CONFIG_1					lcd_MI0283_PORTRAIT
#define USED_SCREEN_CONTROLLER_1		Ili9341Gpio//St7789vGpio
#define USE_SCREEN_TYPE_DSI				0
#define OTHER_SCREEN_1_PARAMS			(char *)"mi0283-dat", (char *)"mi0283-wr", (char *)"mi0283-rd", (char *)"mi0283-rs", (char *)"mi0283-cs", (char *)"mi0283-rst", NULL

/*
 * !Screen settings
 */
/*
 * Touch screen settings
 */

#define TOUCH_SCREEN_ENABLE				false
#define CAP_TOUCHSCREEN_I2C_UNIT		"i2c-0"
#define CAP_TOUCHSCREEN_IRQ_PIN			"touchirq"
//#define USED_TOUCHSCREEN_1			Mi0283Gpio

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

#define MMCSD_INTERFACE_COUNT				1
#define USED_MMCSD_CONTROLLER_1             MmcSd_Spi
#define OTHER_MMCSD_1_PARAMS                (char *)"spi-2.0", (char *)"mmcsdcd", (char *)"led-1"

/*
 * !MmcSd settings
 */

/*
 * Thread settings
 */

#define USE_DRIVER_SEMAPHORE			true

/*
 * !Thread settings
 */




#endif/*!STM32F769I_DISCO*/
#endif