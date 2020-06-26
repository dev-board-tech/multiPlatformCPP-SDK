/*
 * st7789v_gpio.cpp
 *
 *  Created on: Jan 29, 2018
 *      Author: Work
 */

#include "st7789v_gpio.h"

#include <api/dev_request.h>
#include <api/gpio.h>
#include <sys/core_init.h>

GI::Device::Display::St7789vGpio::St7789vGpio(LCD_TIMINGS *timings, char *dataPins, char *writePin, char *readPin, char *rsPin, char *csPin, char *resetPin, char *backlightPin)
{
	if(!timings)
		return;
    GI::Dev::DevRequest::request(resetPin, &RESET);
    GI::Dev::DevRequest::request(rsPin, &RS);
    GI::Dev::DevRequest::request(csPin, &CS);
    GI::Dev::DevRequest::request(writePin, &WRITE);
    GI::Dev::DevRequest::request(readPin, &READ);
    GI::Dev::DevRequest::request(dataPins, &DATA);
    GI::Dev::DevRequest::request(backlightPin, &backlight);
    if(!RS || !CS || !WRITE || !DATA)
    {
        return;
    }
    DATA->setMode(CfgGpio::GPIO_OUT_PUSH_PULL, 0x000000FF);
    LcdTimings = timings;
    reset();
    GI::Device::Display::St7789vGpio::_setOrientation(this, LcdTimings->orientation);
    //cacheClean_Ptr = &GI::Dev::St7789vGpio::_cacheClean;
    drawPixel_Ptr = &GI::Device::Display::St7789vGpio::_drawPixel;
    drawRectangle_Ptr = &GI::Device::Display::St7789vGpio::_drawRectangle;
    drawHLine_Ptr = &GI::Device::Display::St7789vGpio::_drawHLine;
    drawVLine_Ptr = &GI::Device::Display::St7789vGpio::_drawVLine;
    clear_Ptr = &GI::Device::Display::St7789vGpio::_clear;
    setBacklight_Ptr = &GI::Device::Display::St7789vGpio::_setBacklight;
    GI::Device::Display::St7789vGpio::_clear(this, 0xFFFF0F0F);
    driverHandler_Ptr = (void *)this;
}

GI::Device::Display::St7789vGpio::~St7789vGpio()
{

}

void GI::Device::Display::St7789vGpio::wrCmd(unsigned char cmd)
{
	volatile u32 cnt = FCPU / 5000000;
	while(cnt--);
	RS->setOut(0);
	CS->setOut(0);
	DATA->setOut(cmd);
	WRITE->setOut(0);
	WRITE->setOut(1);
	RS->setOut(1);
	cnt = FCPU / 5000000;
	while(cnt--);
}

void GI::Device::Display::St7789vGpio::wrData(unsigned char data)
{
#if GPIO_OPTIMIZED_FUNCTIONS == true
	void *GPIORW = WRITE->baseAddr;
	void *GPIODAT = DATA->baseAddr;
	unsigned char PINRW = WRITE->pinNr;
	DATA->setOut(GPIODAT, DATA->multiPinMask, (ui)data);
	WRITE->setOut(GPIORW, PINRW, false);
	WRITE->setOut(GPIORW, PINRW, true);
#else
	DATA->setOut(data);
	WRITE->setOut(0);
	WRITE->setOut(1);
#endif
}


void GI::Device::Display::St7789vGpio::reset()
{
	if(!this)
		return;
	CS->setOut(1);
	RS->setOut(1);
	RESET->setOut(0);

	volatile u32 cnt = FCPU / 100000;
	while(cnt--);
	RESET->setOut(1);
	cnt = FCPU / 1000000;
	while(cnt--);

    wrCmd(0x01);                     // SW reset
 	CS->setOut(1);
	cnt = FCPU / 100000;
	while(cnt--);
    wrCmd(0x28);                     // display off
 	CS->setOut(1);

    wrCmd(0x11);
 	CS->setOut(1);


    /* Start Initial Sequence ----------------------------------------------------*/
 	cnt = FCPU / 100;
 	while(cnt--);

 	wrCmd(0x36);
 	wrData(0x00);

	wrCmd(0x3a);
	wrData(0x05);  //65k
	//--------------------------------ST7789V Frame rate setting----------------------------------//
	wrCmd(0xb2);
	wrData(0x0c);
	wrData(0x0c);
	wrData(0x00);
	wrData(0x33);
	wrData(0x33);

	wrCmd(0xb7);
	wrData(0x70);

	//---------------------------------ST7789V Power setting--------------------------------------//
	wrCmd(0xbb);
	wrData(0x1B);//VCOM

	wrCmd(0xc0);
	wrData(0x2c);

	wrCmd(0xc2);
	wrData(0x01);

	wrCmd(0xc3);
	wrData(0x0B);

	wrCmd(0xc4);
	wrData(0x27);

	wrCmd(0xc6);
	wrData(0x0f);

	wrCmd(0xd0);
	wrData(0xa4);
	wrData(0xA1);
	//--------------------------------ST7789V gamma setting---------------------------------------//
	wrCmd(0xe0);
	wrData(0xD0);
	wrData(0x06);
	wrData(0x0B);
	wrData(0x09);
	wrData(0x08);
	wrData(0x30);
	wrData(0x30);
	wrData(0x5B);
	wrData(0x4B);
	wrData(0x18);
	wrData(0x14);
	wrData(0x14);
	wrData(0x2C);
	wrData(0x32);

	wrCmd(0xe1);
	wrData(0xD0);
	wrData(0x05);
	wrData(0x0A);
	wrData(0x0A);
	wrData(0x07);
	wrData(0x28);
	wrData(0x32);
	wrData(0x2C);
	wrData(0x49);
	wrData(0x18);
	wrData(0x13);
	wrData(0x13);
	wrData(0x2C);
	wrData(0x33);

	wrCmd(0x21); // Display inversion ON
	CS->setOut(1);
	setArea(0, 0, LcdTimings->X, LcdTimings->Y);

	wrCmd(0x29); //display on
	CS->setOut(1);
	wrCmd(0x2c);
	CS->setOut(1);

 	cnt = FCPU / 5000;
 	while(cnt--);
   // wrCmd(0xB8);                     // COLMOD_PIXEL_FORMAT_SET
    //wrData(0x07);                 // 16 bit pixel
 	//CS->setOut(1);

 }
//#######################################################################################
void GI::Device::Display::St7789vGpio::setArea(si x0, si y0, si x1, si y1)
{
	if(!this)
		return;
    wrCmd(0x2A);                       // entry mode
    wrData(x0 >> 8);
    wrData(x0);
    wrData(x1 >> 8);
    wrData(x1);
    CS->setOut(1);
    wrCmd(0x2B);                       // entry mode
    wrData(y0 >> 8);
    wrData(y0);
    wrData(y1 >> 8);
    wrData(y1);
    CS->setOut(1);
}
//#######################################################################################
void GI::Device::Display::St7789vGpio::setCursor(si x, si y)
{
	if(!this)
		return;
	setArea(x, y, x, y);
}
//#######################################################################################
bool GI::Device::Display::St7789vGpio::_setOrientation(void *driverHandlerPtr, LCD_ORIENTATION orientation)
{
	if(!driverHandlerPtr)
		return false;
	bool Tmp = false;
	GI::Device::Display::St7789vGpio *driverHandler = (GI::Device::Display::St7789vGpio *)driverHandlerPtr;
	driverHandler->wrCmd(0x36);                     // MEMORY_ACCESS_CONTROL
	switch(orientation)
	{
		case LCD_ORIENTATION_PORTRAIT:
			driverHandler->wrData(0x18);
			//lcd_rw_cmd(0x36, 0x48); //MY=1 MX=0 MV=1 ML=0 BGR=1
			Tmp = true;
			break;

		case LCD_ORIENTATION_LANDSCAPE:
			driverHandler->wrData(0xB8);
			//lcd_rw_cmd(0x36, 0x28); //MY=0 MX=0 MV=0 ML=0 BGR=1
			Tmp = true;
			break;

		case LCD_ORIENTATION_PORTRAIT_FLIP:
			driverHandler->wrData(0xC8);
			//lcd_rw_cmd(0x36, 0x88); //MY=0 MX=1 MV=1 ML=0 BGR=1
			Tmp = true;
			break;

		case LCD_ORIENTATION_LANDSCAPE_FLIP:
			driverHandler->wrData(0x78);
			//lcd_rw_cmd(0x36, 0xE8); //MY=1 MX=0 MV=1 ML=0 BGR=1
			Tmp = true;
			break;
	}
	driverHandler->CS->setOut(1);
	driverHandler->sClipRegion.sXMin = 0;
	driverHandler->sClipRegion.sYMin = 0;
	driverHandler->sClipRegion.sXMax = driverHandler->LcdTimings->X;
	driverHandler->sClipRegion.sYMax = driverHandler->LcdTimings->Y;
	driverHandler->setArea(0, 0, driverHandler->LcdTimings->X,driverHandler->LcdTimings->Y);
	return Tmp;
}
//#######################################################################################
void GI::Device::Display::St7789vGpio::sendPixels(u32 PixelsNumber, u32 color)
{
	if(!this)
		return;
	if(PixelsNumber > (u32)(((u32)LcdTimings->Y * (u32)LcdTimings->X) << 1))
		return;
	unsigned char R = color >> 16,G = color >> 8,B = color;
	unsigned short _color = ((unsigned)(((R)>>3)&0b11111) | (((G)<<3)&0b11111100000) | (((B)<<8)&0b1111100000000000));
	//u32 cnt = 0;
#if GPIO_OPTIMIZED_FUNCTIONS == true
	void *GPIORW = WRITE->baseAddr;
	void *GPIODAT = DATA->baseAddr;
	unsigned char PINRW = WRITE->pinNr;
#endif
	while(PixelsNumber--)
	{
#if GPIO_OPTIMIZED_FUNCTIONS == true
		DATA->setOut(GPIODAT, DATA->multiPinMask, (ui)_color >> 8);
		WRITE->setOut(GPIORW, PINRW, false);
		WRITE->setOut(GPIORW, PINRW, true);
		DATA->setOut(GPIODAT, DATA->multiPinMask, (ui)_color);
		WRITE->setOut(GPIORW, PINRW, false);
		WRITE->setOut(GPIORW, PINRW, true);
#else
		DATA->setOut(_color >> 8);
		WRITE->setOut(0);
		WRITE->setOut(1);
		DATA->setOut(_color);
		WRITE->setOut(0);
		WRITE->setOut(1);
#endif
	}
 	CS->setOut(1);
}
//#######################################################################################
SysErr GI::Device::Display::St7789vGpio::_setBacklight(void *driverHandlerPtr, unsigned char value)
{
	if(!driverHandlerPtr)
		return SYS_ERR_INVALID_HANDLER;
	GI::Device::Display::St7789vGpio *driverHandler = (GI::Device::Display::St7789vGpio *)driverHandlerPtr;
	driverHandler->err = SYS_ERR_OK;
	if (driverHandler->backlight)
	{
		if (value)
			driverHandler->backlight->setOut(1);
		else
			driverHandler->backlight->setOut(0);
		return SYS_ERR_OK;
	}
	driverHandler->err = SYS_ERR_NOT_INITIALIZED;
	return SYS_ERR_NOT_INITIALIZED;
}
/*//#######################################################################################
void GI::Dev::St7789vGpio::_cacheClean(void *driverHandlerPtr, si x_start, si y_start,
		si x_len, si y_len)
{

}*/
//#######################################################################################
void GI::Device::Display::St7789vGpio::_drawPixel(void *driverHandlerPtr, si X, si Y, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7789vGpio *driverHandler = (GI::Device::Display::St7789vGpio *)driverHandlerPtr;
	//lcd_cursor(X_Coordonate,Y_Coordonate);
	if(X < driverHandler->sClipRegion.sXMin || X >= driverHandler->sClipRegion.sXMax || Y < driverHandler->sClipRegion.sYMin || Y >= driverHandler->sClipRegion.sYMax)
		return;
	if(X >= driverHandler->LcdTimings->X || X < 0 || Y >= driverHandler->LcdTimings->Y || Y < 0)
		return;

	driverHandler->setArea(X, Y, X, Y);
	driverHandler->wrCmd(0x2C);
	driverHandler->sendPixels(1, color);
}
//#######################################################################################
void GI::Device::Display::St7789vGpio::_drawRectangle(void *driverHandlerPtr, si x_start, si y_start, ui x_len, ui y_len, bool fill, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7789vGpio *driverHandler = (GI::Device::Display::St7789vGpio *)driverHandlerPtr;
	si x_end = x_start + x_len ,y_end = y_start + y_len;
	if(x_start >= driverHandler->sClipRegion.sXMax || y_start >= driverHandler->sClipRegion.sYMax || x_end < driverHandler->sClipRegion.sXMin || y_end < driverHandler->sClipRegion.sYMin)
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
		if(y_end > driverHandler->sClipRegion.sYMax)
			y_end = driverHandler->sClipRegion.sYMax;
		driverHandler->setArea(_x_start, LineCnt, _x_end - 1, y_end - 1);
		driverHandler->wrCmd(0x2C);
		driverHandler->sendPixels(((_x_end - 1 - _x_start) * (y_end - LineCnt)) + (y_end - LineCnt), color);
	}
	else
	{
		register int _x_end = x_end;
		int _x_start = x_start;
		if(_x_end >= driverHandler->sClipRegion.sXMax)
			_x_end = driverHandler->sClipRegion.sXMax;
		if(_x_start < driverHandler->sClipRegion.sXMin)
			_x_start = driverHandler->sClipRegion.sXMin;
		if(y_start >= driverHandler->sClipRegion.sYMin)
		{
			driverHandler->setArea(_x_start, y_start, _x_end - 1, y_start);
			driverHandler->wrCmd(0x2C);
			driverHandler->sendPixels((_x_end - _x_start) + 1, color);
		}

		if(y_end <= driverHandler->sClipRegion.sYMax)
		{
			driverHandler->setArea(_x_start, y_end - 1, _x_end - 1, y_end - 1);
			driverHandler->wrCmd(0x2C);
			driverHandler->sendPixels((_x_end - _x_start) + 1, color);
		}

		int _y_end = y_end;
		if(_y_end >= driverHandler->sClipRegion.sYMax)
			_y_end = driverHandler->sClipRegion.sYMax;
		int _y_start = y_start;
		if(_y_start < driverHandler->sClipRegion.sYMin)
			_y_start = driverHandler->sClipRegion.sYMin;
		if(x_start >= driverHandler->sClipRegion.sXMin)
		{
			driverHandler->setArea(x_start,_y_start, x_start, y_end - 1);
			driverHandler->wrCmd(0x2C);
			driverHandler->sendPixels((y_end - _y_start) + 1, color);
		}

		if(x_end <= driverHandler->sClipRegion.sXMax)
		{
			driverHandler->setArea(x_end - 1,_y_start, x_end - 1, y_end - 1);
			driverHandler->wrCmd(0x2C);
			driverHandler->sendPixels((y_end - _y_start) + 1, color);
		}
	}
}
//#######################################################################################
void GI::Device::Display::St7789vGpio::_drawHLine(void *driverHandlerPtr, si X1, ui X2, si Y, unsigned char width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7789vGpio *driverHandler = (GI::Device::Display::St7789vGpio *)driverHandlerPtr;
	if(width == 1 && (Y < driverHandler->sClipRegion.sYMin || Y >= driverHandler->sClipRegion.sYMax))
		return;
	register int X1_Tmp = X1, X2_Tmp = X1 + X2;
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

	if(X2_Tmp - X1_Tmp > 0)
	{
		//register int _Y_ = Y - Half_width1;
		driverHandler->setArea(X1_Tmp, Y - Half_width1, X2_Tmp, (Y + Half_width2) - 1);
		driverHandler->wrCmd(0x2C);
		driverHandler->sendPixels((X2_Tmp - X1_Tmp) * width , color);
	}
}
//#######################################################################################
void GI::Device::Display::St7789vGpio::_drawVLine(void *driverHandlerPtr, si Y1, ui Y2, si X, unsigned char width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7789vGpio *driverHandler = (GI::Device::Display::St7789vGpio *)driverHandlerPtr;
	if(width == 1 && (X < driverHandler->sClipRegion.sXMin || X >= driverHandler->sClipRegion.sXMax))
		return;
	register int Y1_Tmp = Y1, Y2_Tmp = Y1 + Y2;
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
	int Half_width2 = width - Half_width1;
	if(Y2_Tmp - Y1_Tmp > 0)
	{
		//register int _Y_ = Y - Half_width1;
		driverHandler->setArea(X - Half_width1, Y1_Tmp, (X + Half_width2) - 1, Y2_Tmp);
		driverHandler->wrCmd(0x2C);
		driverHandler->sendPixels((Y2_Tmp - Y1_Tmp) * width , color);
	}
}
//#######################################################################################
void GI::Device::Display::St7789vGpio::_clear(void *driverHandlerPtr, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::St7789vGpio *driverHandler = (GI::Device::Display::St7789vGpio *)driverHandlerPtr;
	driverHandler->_drawRectangle(driverHandlerPtr, 0, 0, driverHandler->LcdTimings->X, driverHandler->LcdTimings->Y, true, color);
}
//#######################################################################################

