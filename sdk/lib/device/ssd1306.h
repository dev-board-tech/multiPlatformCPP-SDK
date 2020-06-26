/*
 * ssd1306.h
 */

#ifndef LIB_DEVICE_UG2832HSWEG04_H_
#define LIB_DEVICE_UG2832HSWEG04_H_

#include <api/dev_request.h>
#include <api/lcd_def.h>
#include <api/gpio.h>
#include <api/spi.h>
/*#####################################################*/

namespace GI {
namespace Device {
namespace Display {
class Ssd1306 : public GI::Display::Display {
public:
	Ssd1306(LCD_TIMINGS *timings, char *spiPath, char *cdPin, char *rstPin=NULL);
    ~Ssd1306();

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

    GI::Dev::Gpio *RESET;
    GI::Dev::Gpio *CD;
    GI::Dev::Spi *spiDevice;
private:
    unsigned char buff[512];

};
}
}
}
/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "ssd1306.cpp"
#endif
/*#####################################################*/
#endif /* LIB_DEVICE_UG2832HSWEG04_H_ */
