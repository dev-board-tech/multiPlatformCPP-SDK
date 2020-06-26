
#ifndef _SCREEN_H_
#define _SCREEN_H_
/*#####################################################*/
#include "api/lcd_def.h"
#include <include/global.h>
#include <api/io_handle.h>
#include <api/timer.h>
/*#####################################################*/

/*#####################################################*/
namespace GI {
	namespace Device {
		namespace Display {
			class IntScreen : public GI::Display::Display {
				public:
				IntScreen(LCD_TIMINGS *timings, FPGA_GFX_ACCEL_t *lcdDev);
				~IntScreen();

				static void _setOn(void *driverHandlerPtr);
				static void _setOff(void *driverHandlerPtr);
				static bool _setOrientation(void *driverHandlerPtr, LCD_ORIENTATION orientation);
				//static void _cacheClean(void *driverHandlerPtr, si x_start, si y_start, si x_len, si y_len);
				static void _drawPixel(void *driverHandlerPtr, si X_Coordonate, si Y_Coordonate, u32 color);
				static void _drawRectangle(void *driverHandlerPtr, si x_start, si y_start, ui x_len, ui y_len, bool fill, u32 color);
				static void _drawHLine(void *driverHandlerPtr, si X1, ui X2, si Y, u8 width, u32 color);
				static void _drawVLine(void *driverHandlerPtr, si Y1, ui Y2, si X, u8 width, u32 color);
				static void _clear(void *driverHandlerPtr, u32 color);
				static void _setLuminosity(void *driverHandlerPtr, u8 luminosity);
				static void _refresh(void *driverHandlerPtr);

				volatile FPGA_GFX_ACCEL_t *lcdDev;
			};
		}
	}
}
/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "lcd_fpga.cpp"
#endif
/*#####################################################*/
#endif /* LIB_DEVICE_SSD1331_H_ */
