/*
 * Ssd1306.cpp
 */

#include "Ssd1306.h"
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


GI::Device::Display::Ssd1306::Ssd1306(LCD_TIMINGS *timings, char *spiPath, char *cdPin, char *rstPin)
{
    GI::Dev::DevRequest::request(rstPin, &RESET);
    GI::Dev::DevRequest::request(cdPin, &CD);
    GI::Dev::DevRequest::request(spiPath, &spiDevice);
    if(!spiDevice || !CD)
    {
        return;
    }
    LcdTimings = timings;
	setOn_Ptr = &GI::Device::Display::Ssd1306::_setOn;
	setOff_Ptr = &GI::Device::Display::Ssd1306::_setOff;
    //cacheClean_Ptr = &GI::Dev::Ssd1306::_cacheClean;
    drawPixel_Ptr = &GI::Device::Display::Ssd1306::_drawPixel;
    drawRectangle_Ptr = &GI::Device::Display::Ssd1306::_drawRectangle;
    drawHLine_Ptr = &GI::Device::Display::Ssd1306::_drawHLine;
    drawVLine_Ptr = &GI::Device::Display::Ssd1306::_drawVLine;
    clear_Ptr = &GI::Device::Display::Ssd1306::_clear;
	refresh_Ptr = &GI::Device::Display::Ssd1306::_refresh;
	sClipRegion.sXMin = 0;
	sClipRegion.sYMin = 0;
	sClipRegion.sXMax = LcdTimings->X;
	sClipRegion.sYMax = LcdTimings->Y;
    driverHandler_Ptr = (void *)this;
    reset();
    //GI::Dev::Ug2832hsweg04::_setOrientation(this, LcdTimings->orientation);
    //GI::Dev::Ug2832hsweg04::_clear(this, 0xFFFF0F0F);
}

GI::Device::Display::Ssd1306::~Ssd1306()
{

}

void GI::Device::Display::Ssd1306::reset()
{
	RESET->setOut(0);
	GI::Sys::Timer::delay(2);
	RESET->setOut(1);
	GI::Sys::Timer::delay(100);
	/* Charge pump enable */
	wrCmd(0x8D);
	wrCmd(0x14);
	/* Set pre-charge period */
	wrCmd(0xD9);
	wrCmd(0xF1);
	/* Contrast control */
	wrCmd(0x81);
	wrCmd(0x8F);
	/* Column inversion disable */
	wrCmd(0xA0);
	/* Scan direction */
	wrCmd(0xC0);
	wrCmd(0xDA);
	/* COM pins configuration */
	wrCmd(0x00);
	/* Addressing mode: horizontal */
	wrCmd(0x20);
	wrCmd(0x0);
	GI::Sys::Timer::delay(2);
	ui cnt = 0;
	for(; cnt < 512; cnt++)
	{
		buff[cnt] = 0x00;
	}
	_refresh(this);
	_setLuminosity(this, 0);
}

void GI::Device::Display::Ssd1306::wrCmd(unsigned char cmd)
{
	CD->setOut(0);
	spiDevice->writeBytes(&cmd, 1);
}

void GI::Device::Display::Ssd1306::_refresh(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1306 *driverHandler = (GI::Device::Display::Ssd1306 *)driverHandlerPtr;
	//driverHandler->setOff();
	driverHandler->wrCmd(0x40);
	unsigned char X;
	unsigned char Y;
	ui Y_res = driverHandler->LcdTimings->Y;
	if(driverHandler->LcdTimings->orientation == LCD_ORIENTATION_PORTRAIT || 
		driverHandler->LcdTimings->orientation == LCD_ORIENTATION_PORTRAIT_FLIP)
	{
		Y_res = driverHandler->LcdTimings->X;
	}
	switch(Y_res)
	{
	case 16:
		X = 0x7F;
		Y = 0x01;
		break;
	case 32:
		X = 0x7F;
		Y = 0x03;
		break;
	case 64:
		X = 0x7F;
		Y = 0x07;
		break;
	default:
		return;
	}
	driverHandler->wrCmd(0x21);
	driverHandler->wrCmd(0x00);
	driverHandler->wrCmd(X);
	driverHandler->wrCmd(0x22);
	driverHandler->wrCmd(0x00);
	driverHandler->wrCmd(Y);
	driverHandler->CD->setOut(1);
	driverHandler->spiDevice->writeBytes(driverHandler->buff, 512);
	driverHandler->setOn();
}

void GI::Device::Display::Ssd1306::_setOn(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1306 *driverHandler = (GI::Device::Display::Ssd1306 *)driverHandlerPtr;
	driverHandler->wrCmd(0xAF);
}

void GI::Device::Display::Ssd1306::_setOff(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1306 *driverHandler = (GI::Device::Display::Ssd1306 *)driverHandlerPtr;
	driverHandler->wrCmd(0xAE);
}

bool GI::Device::Display::Ssd1306::_setOrientation(void *driverHandlerPtr, LCD_ORIENTATION orientation)
{
	//GI::Device::Display::Ug2832hsweg04 *driverHandler = (GI::Device::Display::Ug2832hsweg04 *)driverHandlerPtr;
	return false;
}

/*void GI::Dev::Ug2832hsweg04::_cacheClean(void *driverHandlerPtr, si x_start, si y_start, si x_len, si y_len)
{
	GI::Dev::Ug2832hsweg04 *driverHandler = (GI::Dev::Ug2832hsweg04 *)driverHandlerPtr;
	driverHandler->_refresh(driverHandlerPtr);
}*/

void GI::Device::Display::Ssd1306::_drawPixel(void *driverHandlerPtr, si X_Coordonate, si Y_Coordonate, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1306 *driverHandler = (GI::Device::Display::Ssd1306 *)driverHandlerPtr;
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
	unsigned char *tmp_buff = driverHandler->buff + (((_Y_Coordonate >> 3) * X_Limit) + _X_Coordonate);
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

void GI::Device::Display::Ssd1306::_drawRectangle(void *driverHandlerPtr, si x_start, si y_start, ui x_len, ui y_len, bool fill, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1306 *driverHandler = (GI::Device::Display::Ssd1306 *)driverHandlerPtr;
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

void GI::Device::Display::Ssd1306::_drawHLine(void *driverHandlerPtr, si X1, ui X2, si Y, unsigned char width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1306 *driverHandler = (GI::Device::Display::Ssd1306 *)driverHandlerPtr;
	int X1_Tmp = X1, X2_Tmp = X1 + X2;
	if(X1_Tmp < (int)driverHandler->sClipRegion.sXMin) 
		X1_Tmp = (int)driverHandler->sClipRegion.sXMin;
	if(X1_Tmp >= (int)driverHandler->sClipRegion.sXMax) 
		X1_Tmp = (int)driverHandler->sClipRegion.sXMax;
	if(X2_Tmp < (int)driverHandler->sClipRegion.sXMin) 
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

void GI::Device::Display::Ssd1306::_drawVLine(void *driverHandlerPtr, si Y1, ui Y2, si X, unsigned char width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1306 *driverHandler = (GI::Device::Display::Ssd1306 *)driverHandlerPtr;
	int Y1_Tmp = Y1, Y2_Tmp = Y1 + Y2;
	if(X < (int)driverHandler->sClipRegion.sXMin) 
		X = (int)driverHandler->sClipRegion.sXMin;
	if(X >= (int)driverHandler->sClipRegion.sXMax) 
		X = (int)driverHandler->sClipRegion.sXMax;
	if(Y1_Tmp < (int)driverHandler->sClipRegion.sYMin) 
		Y1_Tmp = (int)driverHandler->sClipRegion.sYMin;
	if(Y1_Tmp >= (int)driverHandler->sClipRegion.sYMax) 
		Y1_Tmp = (int)driverHandler->sClipRegion.sYMax;
	if(Y2_Tmp < (int)driverHandler->sClipRegion.sYMin) 
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

void GI::Device::Display::Ssd1306::_clear(void *driverHandlerPtr, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1306 *driverHandler = (GI::Device::Display::Ssd1306 *)driverHandlerPtr;
	_drawRectangle(driverHandlerPtr, 0, 0, driverHandler->LcdTimings->X, driverHandler->LcdTimings->Y, 1, color);
}

void GI::Device::Display::Ssd1306::_setLuminosity(void *driverHandlerPtr, unsigned char luminosity)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1306 *driverHandler = (GI::Device::Display::Ssd1306 *)driverHandlerPtr;
	/* Contrast control */
	driverHandler->wrCmd(0x81);
	driverHandler->wrCmd(luminosity);
}




