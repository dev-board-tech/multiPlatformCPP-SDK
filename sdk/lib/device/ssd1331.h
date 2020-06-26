/*
 * ssd1331.h
 *
 *  Created on: Jan 24, 2018
 *      Author: Work
 */

#ifndef LIB_DEVICE_SSD1331_H_
#define LIB_DEVICE_SSD1331_H_
/*#####################################################*/
#include <api/lcd_def.h>
#include <include/global.h>
#include <api/io_handle.h>
#include <api/timer.h>
/*#####################################################*/

#define SSD1331_CMD_DRAWLINE						0x21
#define SSD1331_CMD_DRAWRECTANGLE					0x22
#define SSD1331_CMD_COPYWINDOW						0x23
#define SSD1331_CMD_DIMWINDOW						0x24
#define SSD1331_CMD_CLEARWINDOW						0x25
#define SSD1331_CMD_FILLWINDOW						0x26
    #define SSD1331_DISABLE_FILL		0x00
    #define SSD1331_ENABLE_FILL			0x01
#define SSD1331_CMD_CONTINUOUSSCROLLINGSETUP		0x27
#define SSD1331_CMD_DEACTIVESCROLLING				0x2E
#define SSD1331_CMD_ACTIVESCROLLING					0x2F

#define SSD1331_CMD_SETCOLUMNADDRESS				0x15
#define SSD1331_CMD_SETROWADDRESS					0x75
#define SSD1331_CMD_SETCONTRASTA					0x81
#define SSD1331_CMD_SETCONTRASTB					0x82
#define SSD1331_CMD_SETCONTRASTC					0x83
#define SSD1331_CMD_MASTERCURRENTCONTROL			0x87
#define SSD1331_CMD_SETPRECHARGESPEEDA				0x8A
#define SSD1331_CMD_SETPRECHARGESPEEDB				0x8B
#define SSD1331_CMD_SETPRECHARGESPEEDC				0x8C
#define SSD1331_CMD_SETREMAP						0xA0
#define SSD1331_CMD_SETDISPLAYSTARTLINE				0xA1
#define SSD1331_CMD_SETDISPLAYOFFSET				0xA2
#define SSD1331_CMD_NORMALDISPLAY					0xA4
#define SSD1331_CMD_ENTIREDISPLAYON					0xA5
#define SSD1331_CMD_ENTIREDISPLAYOFF				0xA6
#define SSD1331_CMD_INVERSEDISPLAY					0xA7
#define SSD1331_CMD_SETMULTIPLEXRATIO				0xA8
#define SSD1331_CMD_DIMMODESETTING					0xAB
#define SSD1331_CMD_SETMASTERCONFIGURE				0xAD
#define SSD1331_CMD_DIMMODEDISPLAYON				0xAC
#define SSD1331_CMD_DISPLAYOFF						0xAE
#define SSD1331_CMD_DISPLAYON						0xAF
#define SSD1331_CMD_POWERSAVEMODE					0xB0
#define SSD1331_CMD_PHASEPERIODADJUSTMENT			0xB1
#define SSD1331_CMD_DISPLAYCLOCKDIV					0xB3
#define SSD1331_CMD_SETGRAySCALETABLE				0xB8
#define SSD1331_CMD_ENABLELINEARGRAYSCALETABLE		0xB9
#define SSD1331_CMD_SETPRECHARGEVOLTAGE				0xBB
#define SSD1331_CMD_SETVVOLTAGE						0xBE
/*#####################################################*/
namespace GI {
	namespace Device {
		namespace Display {
			class Ssd1331 : public GI::Display::Display {
			public:
				Ssd1331(LCD_TIMINGS *timings, char *spiPath, char *resetPin, char *dcPin, char *pmodEnPin=NULL, char *vccEnPin=NULL);
				~Ssd1331();

				void reset();
				static void _setOn(void *driverHandlerPtr);
				static void _setOff(void *driverHandlerPtr);
				static bool _setOrientation(void *driverHandlerPtr, LCD_ORIENTATION orientation);
				//static void _cacheClean(void *driverHandlerPtr, si x_start, si y_start, si x_len, si y_len);
				static void _drawPixel(void *driverHandlerPtr, si X_Coordonate, si Y_Coordonate, u32 color);
				static void _drawRectangle(void *driverHandlerPtr, si x_start, si y_start, ui x_len, ui y_len, bool fill, u32 color);
				static void _drawHLine(void *driverHandlerPtr, si X1, ui X2, si Y, unsigned char width, u32 color);
				static void _drawVLine(void *driverHandlerPtr, si Y1, ui Y2, si X, unsigned char width, u32 color);
				static void _clear(void *driverHandlerPtr, u32 color);
				static void _setLuminosity(void *driverHandlerPtr, unsigned char luminosity);
				static void _refresh(void *driverHandlerPtr);

				void wrCmd(unsigned char cmd);
				void wrCmd(unsigned char *cmd, unsigned char len);
				void wrData(unsigned char *cmd, unsigned char len);
				void wrPixels(unsigned short color, unsigned short len);

				GI::IO *vccEnPin;
				GI::IO *pmodEnPin;
				GI::IO *resetPin;
				GI::IO *cdPin;
				GI::IO *spiDevice;
			};
		}
	}
}
/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "ssd1306.cpp"
#endif
/*#####################################################*/
#endif /* LIB_DEVICE_SSD1331_H_ */
