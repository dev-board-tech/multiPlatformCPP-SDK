/*
 * st7789v_gpio.h
 *
 *  Created on: Jan 29, 2018
 *      Author: Work
 */

#ifndef LIB_DEVICE_ST7789V_GPIO_H_
#define LIB_DEVICE_ST7789V_GPIO_H_

#include <api/dev_request.h>
#include <api/lcd_def.h>
#include <api/gpio.h>

namespace GI {
namespace Device {
namespace Display {
class St7789vGpio : public GI::Display::Display {
public:
	St7789vGpio(LCD_TIMINGS *timings, char *dataPins, char *writePin, char *readPin, char *rsPin, char *csPin, char *resetPin, char *backlightPin);
    ~St7789vGpio();

    void reset();
    static bool _setOrientation(void *driverHandlerPtr, LCD_ORIENTATION orientation);
    static SysErr _setBacklight(void *driverHandlerPtr, unsigned char value);
    //static void _cacheClean(void *driverHandlerPtr, si x_start, si y_start, si x_len, si y_len);
    static void _drawPixel(void *driverHandlerPtr, si X_Coordonate, si Y_Coordonate, u32 Color16);
    static void _drawRectangle(void *driverHandlerPtr, si x_start, si y_start, ui x_len, ui y_len, bool fill, u32 color);
    static void _drawHLine(void *driverHandlerPtr, si X1, ui X2, si Y, unsigned char width, u32 color);
    static void _drawVLine(void *driverHandlerPtr, si Y1, ui Y2, si X, unsigned char width, u32 color);
    static void _clear(void *driverHandlerPtr, u32 color);

    void wrCmd(unsigned char cmd);
    void wrData(unsigned char data);
    void setArea(si x0, si y0, si x1, si y1);
    void setCursor(si x, si y);
    void sendPixels(u32 PixelsNumber, u32 color);

    GI::Dev::Gpio *DATA;
    GI::Dev::Gpio *RESET;
    GI::Dev::Gpio *RS;
    GI::Dev::Gpio *CS;
    GI::Dev::Gpio *WRITE;
    GI::Dev::Gpio *READ;
    GI::Dev::Gpio *BACKLIGHT;
private:


};
}
}
}
/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "st7789v_gpio.cpp"
#endif
/*#####################################################*/
#endif /* LIB_DEVICE_ST7789V_GPIO_H_ */
