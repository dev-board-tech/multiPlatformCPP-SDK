#ifndef __STM32F769I_DISCO__
#define __STM32F769I_DISCO__

#if defined(STM32F769I_DISCO)

#include "ffconf.h"
#include "lwipopts.h"
#include <api/uart.h>
#include <api/spi.h>
#include <api/i2c.h>
#include <api/gpio.h>

/*
 * Processor choose
 */
//#define STM32F722xx
//#define STM32F723xx
//#define STM32F732xx
//#define STM32F733xx
//#define STM32F756xx
//#define STM32F746xx
//#define STM32F745xx
//#define STM32F765xx
//#define STM32F767xx
#define STM32F769xx
//#define STM32F777xx
//#define STM32F779xx
/*
 * !Processor choose
 */

/*
 * Processor clock selection.
 *
 * If EXTERNAL_CLOCK_VALUE id !0 the reference clock will be EXTERNAL_CLOCK_VALUE.
 * If HSE_VALUE value is 0 the reference clock will be the HSI_VALUE.
 */

#define HSE_VALUE						((uint32_t)25000000)	/*!< Value of the External oscillator in Hz*/
#define LSE_VALUE  						((uint32_t)32768)		/*!< Value of the External Low Speed oscillator in Hz */
#define EXTERNAL_CLOCK_VALUE    		((uint32_t)25000000)	/*!< Value of the External clock in Hz*/
#define CORE_CLOCK_DEFAULT				((uint32_t)216000000)	/*!< Value of the Processor default clock in Hz*/
//#define DATA_IN_ExtSDRAM
/*
 * Processor clock selection.
 */

/*
 * Debug interface setup.
 */
//#define STD_OUT_PATH			"UART:0"
//#define STD_OUT_PATH			"SCREEN<Terminal>"
//#define STD_IN_PATH				"UART:0"
//#define STD_ERR_PATH			"UART:0"
/*
 * !Debug interface setup.
 */

/*
 * Screen settings
 */

#define SCREENS_COUNT					1
#define SCREEN_CONFIG_1					lcd_OTM8009A_PORTRAIT
#define USED_SCREEN_CONTROLLER_1		IntScreen
#define USE_SCREEN_TYPE_DSI				1
#define OTHER_SCREEN_1_PARAMS			(NULL)

/*
 * !Screen settings
 */
/*
 * Touch screen settings
 */

#define TOUCH_SCREEN_ENABLE				true
#define CAP_TOUCHSCREEN_I2C_UNIT		"i2c-3"
#define CAP_TOUCHSCREEN_IRQ_PIN			"touchirq"
#define USED_TOUCHSCREEN_1				Ft5x06

/*
 * !Touch screen settings
 */

/*
 * USB settings
 */

#define USE_USB_DEV
#define USE_USB_HS
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
 * Eth http server settings
 */
#define USE_RMII_INTERFACE					true
#define LWIP_DEBUG_EN						false

/*
 * MmcSd settings
 */

#define MMCSD_INTERFACE_COUNT				1
#define USED_MMCSD_CONTROLLER_1             IntMmcSd
#define OTHER_MMCSD_1_PARAMS                (char *)"mmcsdcd", (char *)"led-1"

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
