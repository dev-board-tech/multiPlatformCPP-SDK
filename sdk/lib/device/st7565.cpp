/*
 * st7565.cpp
 */

#include "st7565.h"
#include <api/dev_request.h>
#include <api/gpio.h>
#include <sys/core_init.h>

#if __AVR_XMEGA__
#include <avr/pgmspace.h>
const unsigned char SSD1306_BIT_MASK_TABLE [] PROGMEM = {
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000
};
#endif

GI::Device::Display::St7565::St7565(LCD_TIMINGS *timings, char *spiPath)
{
	if(!spiPath || !timings)
		return;
    GI::Dev::DevRequest::request((char *)"lcd-rst", &RESET);
    GI::Dev::DevRequest::request((char *)"lcd-cd", &CD);
    GI::Dev::DevRequest::request((char *)spiPath, &spiDevice);
    if(!spiDevice || !RESET || !CD)
    {
        return;
    }
    LcdTimings = timings;
    setOn_Ptr = &GI::Device::Display::St7565::_setOn;
    setOff_Ptr = &GI::Device::Display::St7565::_setOff;
    //cacheClean_Ptr = &GI::Device::Display::St7565::_cacheClean;
    drawPixel_Ptr = &GI::Device::Display::St7565::_drawPixel;
    drawRectangle_Ptr = &GI::Device::Display::St7565::_drawRectangle;
    drawHLine_Ptr = &GI::Device::Display::St7565::_drawHLine;
    drawVLine_Ptr = &GI::Device::Display::St7565::_drawVLine;
    clear_Ptr = &GI::Device::Display::St7565::_clear;
    refresh_Ptr = &GI::Device::Display::St7565::_refresh;
    sClipRegion.sXMin = 0;
    sClipRegion.sYMin = 0;
    sClipRegion.sXMax = LcdTimings->X;
    sClipRegion.sYMax = LcdTimings->Y;
    driverHandler_Ptr = (void *)this;
    reset();
    //GI::Dev::St7565::_setOrientation(this, LcdTimings->orientation);
    //GI::Dev::St7565::_clear(this, 0xFFFF0F0F);
}

GI::Device::Display::St7565::~St7565()
{

}

void GI::Device::Display::St7565::reset()
{
    RESET->setOut(0);
    GI::Sys::Timer::delay(2);
    RESET->setOut(1);
    GI::Sys::Timer::delay(100);
    /* Display start line 0 */
    wrCmd(0x40);
    /* ADC normal */
    wrCmd(0xA0);
    /* Reverse COM0~COM63 */
    wrCmd(0xC8);
    /* Display norma */
    wrCmd(0xA6);
    /* Set bias 1/9 (Duty 1/65) */
    wrCmd(0xA2);
    /* Booster, Regulator and Follower on */
    wrCmd(0x2F);
    /* Set internal Booster to 4x */
    wrCmd(0xF8);
    wrCmd(0x00);
    /* Contrast set */
    wrCmd(0x27);
    wrCmd(0x81);
    wrCmd(0x10);
    /* No indicator */
    wrCmd(0xAC);
    wrCmd(0x00);
    /* Display on */
    wrCmd(0xAF);
    GI::Sys::Timer::delay(2);
    memset(buff, 0x00, 1024);
    _refresh(this);
    //_setLuminosity(this, 0);
}

void GI::Device::Display::St7565::wrCmd(unsigned char cmd)
{
    CD->setOut(0);
    spiDevice->writeBytes(&cmd, 1);
}

void GI::Device::Display::St7565::_refresh(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7565 *driverHandler = (GI::Device::Display::St7565 *)driverHandlerPtr;
    ui cnt_addr = 0;
    for(; cnt_addr < 1024; cnt_addr += 128)
    {

        driverHandler->wrCmd(0xB0 | (cnt_addr >> 7));
        driverHandler->wrCmd(0x10);
        driverHandler->wrCmd(0x00);
        driverHandler->CD->setOut(1);
        driverHandler->spiDevice->writeBytes(driverHandler->buff + cnt_addr, 128);
    }
    driverHandler->setOn();
}

void GI::Device::Display::St7565::_setOn(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7565 *driverHandler = (GI::Device::Display::St7565 *)driverHandlerPtr;
    driverHandler->wrCmd(0xAF);
}

void GI::Device::Display::St7565::_setOff(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7565 *driverHandler = (GI::Device::Display::St7565 *)driverHandlerPtr;
    driverHandler->wrCmd(0xAE);
}

bool GI::Device::Display::St7565::_setOrientation(void *driverHandlerPtr, LCD_ORIENTATION orientation)
{
    //GI::Device::Display::St7565 *driverHandler = (GI::Device::Display::St7565 *)driverHandlerPtr;
    return false;
}

void GI::Device::Display::St7565::_cacheClean(void *driverHandlerPtr, si x_start, si y_start, si x_len, si y_len)
{

}

void GI::Device::Display::St7565::_drawPixel(void *driverHandlerPtr, si X_Coordonate, si Y_Coordonate, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7565 *driverHandler = (GI::Device::Display::St7565 *)driverHandlerPtr;
    /* Check if outside the window */
    if(X_Coordonate < driverHandler->sClipRegion.sXMin ||
        X_Coordonate >= driverHandler->sClipRegion.sXMax ||
            Y_Coordonate < driverHandler->sClipRegion.sYMin ||
                Y_Coordonate >= driverHandler->sClipRegion.sYMax)
                    return;
    /* Check if outside the display */
    if(X_Coordonate >= driverHandler->LcdTimings->X ||
        X_Coordonate < 0 ||
            Y_Coordonate >= driverHandler->LcdTimings->Y ||
                Y_Coordonate < 0)
                    return;
    si _X_Coordonate = X_Coordonate;
    si _Y_Coordonate = Y_Coordonate;
    si X_Limit = driverHandler->LcdTimings->X;
    switch ((unsigned char)driverHandler->LcdTimings->orientation)
    {
    case LCD_ORIENTATION_LANDSCAPE_FLIP:
        _X_Coordonate = driverHandler->LcdTimings->X - X_Coordonate - 1;
        _Y_Coordonate = driverHandler->LcdTimings->Y - Y_Coordonate - 1;
        break;
    case LCD_ORIENTATION_PORTRAIT:
        _X_Coordonate = driverHandler->LcdTimings->Y - Y_Coordonate - 1;
        _Y_Coordonate = X_Coordonate;
        X_Limit = driverHandler->LcdTimings->Y;
        break;
    case LCD_ORIENTATION_PORTRAIT_FLIP:
        _X_Coordonate = Y_Coordonate;
        _Y_Coordonate = driverHandler->LcdTimings->X - X_Coordonate - 1;
        X_Limit = driverHandler->LcdTimings->Y;
        break;
    }
    unsigned char *tmp_buff = driverHandler->buff + (((_Y_Coordonate >> 3) * X_Limit) + (_X_Coordonate % X_Limit));
#if __AVR_XMEGA__
    if (color)
        *tmp_buff |= pgm_read_byte(&SSD1306_BIT_MASK_TABLE[_Y_Coordonate & 0x07]);
    else
        *tmp_buff &= ~pgm_read_byte(&SSD1306_BIT_MASK_TABLE[_Y_Coordonate & 0x07]);
#else
    if (color)
        *tmp_buff |= 1 << (_Y_Coordonate & 0x07);
    else
        *tmp_buff &= ~(1 << (_Y_Coordonate & 0x07));
#endif
}

void GI::Device::Display::St7565::_drawRectangle(void *driverHandlerPtr, si x_start, si y_start, ui x_len, ui y_len, bool fill, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7565 *driverHandler = (GI::Device::Display::St7565 *)driverHandlerPtr;
    si x_end = x_start + x_len ,y_end = y_start + y_len;
    if(x_start >= driverHandler->sClipRegion.sXMax ||
        y_start >= driverHandler->sClipRegion.sYMax ||
            x_end < driverHandler->sClipRegion.sXMin ||
                y_end < driverHandler->sClipRegion.sYMin)
                    return;
    register si LineCnt = y_start;
    if(fill)
    {
        if(LineCnt < driverHandler->sClipRegion.sYMin)
            LineCnt = driverHandler->sClipRegion.sYMin;
        si _x_start = x_start;
        if(_x_start < driverHandler->sClipRegion.sXMin)
            _x_start = driverHandler->sClipRegion.sXMin;
        si _x_end = x_end;
        if(_x_end > driverHandler->sClipRegion.sXMax)
            _x_end = driverHandler->sClipRegion.sXMax;
        si width_to_refresh = (_x_end - _x_start);
        if((width_to_refresh + _x_start) > driverHandler->sClipRegion.sXMax)
            width_to_refresh = (driverHandler->sClipRegion.sXMax - _x_start);
        for( ; LineCnt < y_end; LineCnt++)
        {
            if(LineCnt >= driverHandler->sClipRegion.sYMax)
                return;
            register int x = _x_start;
            for( ; x < _x_end ; x++)
            {
                _drawPixel(driverHandlerPtr, x, LineCnt, color);
            }
        }
        //_refresh(driverHandler);
        return;
    }
    int _x_end = x_end;
    int _x_start = x_start;
    if(_x_end > driverHandler->sClipRegion.sXMax) _x_end = driverHandler->sClipRegion.sXMax;
    if(_x_start < driverHandler->sClipRegion.sXMin) _x_start = driverHandler->sClipRegion.sXMin;
    if(y_start >= driverHandler->sClipRegion.sYMin)
    {
        for(LineCnt = _x_start ; LineCnt < _x_end ; LineCnt++)
        {
            _drawPixel(driverHandler, LineCnt, y_start, color);
            //ScreenBuff[LineCnt + (driverHandler->Width * y_start)] = _color;
        }
    }

    if(y_end <= driverHandler->sClipRegion.sYMax)
    {
        for(LineCnt = _x_start ; LineCnt < _x_end ; LineCnt++)
        {
            _drawPixel(driverHandler, LineCnt, y_end - 1, color);
            //ScreenBuff[LineCnt + (driverHandler->Width * (y_end - 1))] = _color;
        }
    }

    int _y_end = y_end;
    if(_y_end > driverHandler->sClipRegion.sYMax) _y_end = driverHandler->sClipRegion.sYMax;
    int _y_start = y_start;
    if(_y_start < driverHandler->sClipRegion.sYMin) _y_start = driverHandler->sClipRegion.sYMin;
    if(x_start >= driverHandler->sClipRegion.sXMin)
    {
        for(LineCnt = _y_start ; LineCnt < _y_end ; LineCnt++)
        {
            _drawPixel(driverHandler, x_start, LineCnt, color);
            //ScreenBuff[x_start + (driverHandler->Width * LineCnt)] = _color;
        }
    }

    if(x_end <= driverHandler->sClipRegion.sXMax)
    {
        for(LineCnt = _y_start ; LineCnt < _y_end ; LineCnt++)
        {
            _drawPixel(driverHandler, (x_end - 1), LineCnt, color);
            //ScreenBuff[(x_end - 1) + (driverHandler->Width * LineCnt)] = _color;
        }
    }
    //_refresh(driverHandler);
}

void GI::Device::Display::St7565::_drawHLine(void *driverHandlerPtr, si X1, ui X2, si Y, unsigned char width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7565 *driverHandler = (GI::Device::Display::St7565 *)driverHandlerPtr;
    int X1_Tmp = X1, X2_Tmp = X1 + X2;
    if(X1_Tmp <= (int)driverHandler->sClipRegion.sXMin)
        X1_Tmp = (int)driverHandler->sClipRegion.sXMin;
    if(X1_Tmp >= (int)driverHandler->sClipRegion.sXMax)
        X1_Tmp = (int)driverHandler->sClipRegion.sXMax;
    if(X2_Tmp <= (int)driverHandler->sClipRegion.sXMin)
        X2_Tmp = (int)driverHandler->sClipRegion.sXMin;
    if(X2_Tmp >= (int)driverHandler->sClipRegion.sXMax)
        X2_Tmp = (int)driverHandler->sClipRegion.sXMax;
    if(Y < (int)driverHandler->sClipRegion.sYMin)
        Y = (int)driverHandler->sClipRegion.sYMin;
    if(Y >= (int)driverHandler->sClipRegion.sYMax)
        Y = (int)driverHandler->sClipRegion.sYMax;
    int Half_width1 = (width>>1);
    int Half_width2 = width-Half_width1;
    for(;X1_Tmp < X2_Tmp; X1_Tmp++)
    {
        int _Y_ = Y - Half_width1;
        for(; _Y_ < Y + Half_width2; _Y_++)
            _drawPixel(driverHandler,(ui)(X1_Tmp),(ui)(_Y_), color);
    }
    //_refresh(driverHandler);
}

void GI::Device::Display::St7565::_drawVLine(void *driverHandlerPtr, si Y1, ui Y2, si X, unsigned char width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7565 *driverHandler = (GI::Device::Display::St7565 *)driverHandlerPtr;
    int Y1_Tmp = Y1, Y2_Tmp = Y1 + Y2;
    if(X <= (int)driverHandler->sClipRegion.sXMin)
        X = (int)driverHandler->sClipRegion.sXMin;
    if(X >= (int)driverHandler->sClipRegion.sXMax)
        X = (int)driverHandler->sClipRegion.sXMax;
    if(Y1_Tmp <= (int)driverHandler->sClipRegion.sYMin)
        Y1_Tmp = (int)driverHandler->sClipRegion.sYMin;
    if(Y1_Tmp >= (int)driverHandler->sClipRegion.sYMax)
        Y1_Tmp = (int)driverHandler->sClipRegion.sYMax;
    if(Y2_Tmp <= (int)driverHandler->sClipRegion.sYMin)
        Y2_Tmp = (int)driverHandler->sClipRegion.sYMin;
    if(Y2_Tmp >= (int)driverHandler->sClipRegion.sYMax)
        Y2_Tmp = (int)driverHandler->sClipRegion.sYMax;
    int Half_width1 = (width>>1);
    int Half_width2 = width-Half_width1;
    for(;Y1_Tmp < Y2_Tmp; Y1_Tmp++)
    {
        int _X_ = X - Half_width1;
        for(; _X_ < X + Half_width2; _X_++)
            _drawPixel(driverHandler,(ui)(_X_),(ui)(Y1_Tmp), color);
    }
    //_refresh(driverHandler);
}

void GI::Device::Display::St7565::_clear(void *driverHandlerPtr, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7565 *driverHandler = (GI::Device::Display::St7565 *)driverHandlerPtr;
    _drawRectangle(driverHandlerPtr, 0, 0, driverHandler->LcdTimings->X, driverHandler->LcdTimings->Y, 1, color);
}

void GI::Device::Display::St7565::_setLuminosity(void *driverHandlerPtr, unsigned char luminosity)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7565 *driverHandler = (GI::Device::Display::St7565 *)driverHandlerPtr;
    /* Contrast control */
    driverHandler->wrCmd(0x81);
    driverHandler->wrCmd(luminosity);
}



