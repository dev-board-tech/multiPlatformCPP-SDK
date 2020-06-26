/*
 * device/mi0283_gpio.cpp
 */

#include "ili9341_gpio.h"
#include <api/dev_request.h>
#include <api/gpio.h>
#include <sys/core_init.h>

GI::Device::Display::Ili9341Gpio::Ili9341Gpio(LCD_TIMINGS *timings, char *dataPins, char *writePin, char *readPin, char *rsPin, char *csPin, char *resetPin, char *backlightPin)
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
    GI::Device::Display::Ili9341Gpio::_setOrientation(this, LcdTimings->orientation);
    //cacheClean_Ptr = &GI::Dev::Ili9341Gpio::_cacheClean;
    drawPixel_Ptr = &GI::Device::Display::Ili9341Gpio::_drawPixel;
    drawRectangle_Ptr = &GI::Device::Display::Ili9341Gpio::_drawRectangle;
    drawHLine_Ptr = &GI::Device::Display::Ili9341Gpio::_drawHLine;
    drawVLine_Ptr = &GI::Device::Display::Ili9341Gpio::_drawVLine;
    clear_Ptr = &GI::Device::Display::Ili9341Gpio::_clear;
    setBacklight_Ptr = &GI::Device::Display::Ili9341Gpio::_setBacklight;
    GI::Device::Display::Ili9341Gpio::_clear(this, 0xFFFF0F0F);
    driverHandler_Ptr = (void *)this;
}

GI::Device::Display::Ili9341Gpio::~Ili9341Gpio()
{

}

void GI::Device::Display::Ili9341Gpio::wrCmd(unsigned char cmd)
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

void GI::Device::Display::Ili9341Gpio::wrData(unsigned char data)
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

void GI::Device::Display::Ili9341Gpio::reset()
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

    wrCmd(0xCF);
    wrData(0x00);
    wrData(0x83);
    wrData(0x30);
 	CS->setOut(1);

    wrCmd(0xED);
    wrData(0x64);
    wrData(0x03);
    wrData(0x12);
    wrData(0x81);
 	CS->setOut(1);

    wrCmd(0xE8);
    wrData(0x85);
    wrData(0x01);
    wrData(0x79);
 	CS->setOut(1);

    wrCmd(0xCB);
    wrData(0x39);
    wrData(0x2C);
    wrData(0x00);
    wrData(0x34);
    wrData(0x02);
 	CS->setOut(1);

    wrCmd(0xF7);
    wrData(0x20);
 	CS->setOut(1);

    wrCmd(0xEA);
    wrData(0x00);
    wrData(0x00);
 	CS->setOut(1);

    wrCmd(0xC0);                     // POWER_CONTROL_1
    wrData(0x26);
    wrData(0x06);
 	CS->setOut(1);

    wrCmd(0xC1);                     // POWER_CONTROL_2
    wrData(0x11);
 	CS->setOut(1);

    wrCmd(0xC5);                     // VCOM_CONTROL_1
    wrData(0x35);
    wrData(0x3E);
 	CS->setOut(1);

    wrCmd(0xC7);                     // VCOM_CONTROL_2
    wrData(0xBE);
 	CS->setOut(1);

    //wrCmd(0x36);                     // MEMORY_ACCESS_CONTROL
    //wrData(0x48);
 	//CS->setOut(1);

    wrCmd(0x3A);                     // COLMOD_PIXEL_FORMAT_SET
    wrData(0x55);                 // 16 bit pixel
 	CS->setOut(1);

    //wrCmd(0x17);                     //0x0005=65k, 0x0006=262k
    //wrData(0x05);
 	//CS->setOut(1);

    wrCmd(0xB1);                     // Frame Rate
    wrData(0x00);
    wrData(0x1B);
 	CS->setOut(1);

    wrCmd(0xF2);                     // Gamma Function Disable
    wrData(0x08);
 	CS->setOut(1);

    wrCmd(0x26);
    wrData(0x01);                 // gamma set for curve 01/2/04/08
 	CS->setOut(1);

    wrCmd(0xE0);                     // positive gamma correction
    wrData(0x1F);
    wrData(0x1A);
    wrData(0x18);
    wrData(0x0A);
    wrData(0x0F);
    wrData(0x06);
    wrData(0x45);
    wrData(0x87);
    wrData(0x32);
    wrData(0x0A);
    wrData(0x07);
    wrData(0x02);
    wrData(0x07);
    wrData(0x05);
    wrData(0x00);
 	CS->setOut(1);

    wrCmd(0xE1);                     // negativ gamma correction
    wrData(0x00);
    wrData(0x25);
    wrData(0x27);
    wrData(0x05);
    wrData(0x10);
    wrData(0x09);
    wrData(0x3A);
    wrData(0x78);
    wrData(0x4D);
    wrData(0x05);
    wrData(0x18);
    wrData(0x0D);
    wrData(0x38);
    wrData(0x3A);
    wrData(0x1F);
 	CS->setOut(1);

 	//setArea(0, 0, _LcdTimings->X, _LcdTimings->Y);

     //WindowMax ();

     //wrCmd(0x34);                     // tearing effect off
     //_cs = 1;

    //wrCmd(0x35);                     // tearing effect on
 	//CS->setOut(1);
     //_cs = 1;

    wrCmd(0xB7);                       // entry mode
    wrData(0x07);
 	CS->setOut(1);

    wrCmd(0xB6);                       // display function control
    wrData(0x0A);
    wrData(0x82);
    wrData(0x27);
    wrData(0x04);
 	CS->setOut(1);

    wrCmd(0x11);                     // sleep out
 	CS->setOut(1);

 	cnt = FCPU / 1000;
 	while(cnt--);

    wrCmd(0x29);                     // display on
 	CS->setOut(1);

 	cnt = FCPU / 5000;
 	while(cnt--);
   // wrCmd(0xB8);                     // COLMOD_PIXEL_FORMAT_SET
    //wrData(0x07);                 // 16 bit pixel
 	//CS->setOut(1);

 }
//#######################################################################################
void GI::Device::Display::Ili9341Gpio::setArea(si x0, si y0, si x1, si y1)
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
void GI::Device::Display::Ili9341Gpio::setCursor(si x, si y)
{
	if(!this)
		return;
	setArea(x, y, x, y);
}
//#######################################################################################
bool GI::Device::Display::Ili9341Gpio::_setOrientation(void *driverHandlerPtr, LCD_ORIENTATION orientation)
{
	if(!driverHandlerPtr)
		return false;
	bool Tmp = false;
	GI::Device::Display::Ili9341Gpio *driverHandler = (GI::Device::Display::Ili9341Gpio *)driverHandlerPtr;
	driverHandler->wrCmd(0x36);                     // MEMORY_ACCESS_CONTROL
	switch(orientation)
	{
		case LCD_ORIENTATION_PORTRAIT:
			driverHandler->wrData(0x48);
			//lcd_rw_cmd(0x36, 0x48); //MY=1 MX=0 MV=1 ML=0 BGR=1
			Tmp = true;
			break;

		case LCD_ORIENTATION_LANDSCAPE:
			driverHandler->wrData(0x28);
			//lcd_rw_cmd(0x36, 0x28); //MY=0 MX=0 MV=0 ML=0 BGR=1
			Tmp = true;
			break;

		case LCD_ORIENTATION_PORTRAIT_FLIP:
			driverHandler->wrData(0x88);
			//lcd_rw_cmd(0x36, 0x88); //MY=0 MX=1 MV=1 ML=0 BGR=1
			Tmp = true;
			break;

		case LCD_ORIENTATION_LANDSCAPE_FLIP:
			driverHandler->wrData(0xE8);
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
void GI::Device::Display::Ili9341Gpio::sendPixels(u32 PixelsNumber, u32 color)
{
	if(!this)
		return;
	if(PixelsNumber > (u32)(((u32)LcdTimings->Y * (u32)LcdTimings->X) << 1))
		return;
	unsigned char R = color >> 16,G = color >> 8,B = color;
	unsigned short _color = ((unsigned)(((R)>>3)&0b11111) | (((G)<<3)&0b11111100000) | (((B)<<8)&0b1111100000000000));
	//u32 cnt = 0;
	while(PixelsNumber--)
	{
#if GPIO_OPTIMIZED_FUNCTIONS == true
		void *GPIORW = WRITE->baseAddr;
		void *GPIODAT = DATA->baseAddr;
		unsigned char PINRW = WRITE->pinNr;
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
SysErr GI::Device::Display::Ili9341Gpio::_setBacklight(void *driverHandlerPtr, unsigned char value)
{
	if(!driverHandlerPtr)
		return SYS_ERR_INVALID_HANDLER;
	GI::Device::Display::Ili9341Gpio *driverHandler = (GI::Device::Display::Ili9341Gpio *)driverHandlerPtr;
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
void GI::Dev::Ili9341Gpio::_cacheClean(void *driverHandlerPtr, si x_start, si y_start,
		si x_len, si y_len)
{

}*/
//#######################################################################################
void GI::Device::Display::Ili9341Gpio::_drawPixel(void *driverHandlerPtr, si X, si Y, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ili9341Gpio *driverHandler = (GI::Device::Display::Ili9341Gpio *)driverHandlerPtr;
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
void GI::Device::Display::Ili9341Gpio::_drawRectangle(void *driverHandlerPtr, si x_start, si y_start, ui x_len, ui y_len, bool fill, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ili9341Gpio *driverHandler = (GI::Device::Display::Ili9341Gpio *)driverHandlerPtr;
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
void GI::Device::Display::Ili9341Gpio::_drawHLine(void *driverHandlerPtr, si X1, ui X2, si Y, unsigned char width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ili9341Gpio *driverHandler = (GI::Device::Display::Ili9341Gpio *)driverHandlerPtr;
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
void GI::Device::Display::Ili9341Gpio::_drawVLine(void *driverHandlerPtr, si Y1, ui Y2, si X, unsigned char width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ili9341Gpio *driverHandler = (GI::Device::Display::Ili9341Gpio *)driverHandlerPtr;
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
void GI::Device::Display::Ili9341Gpio::_clear(void *driverHandlerPtr, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ili9341Gpio *driverHandler = (GI::Device::Display::Ili9341Gpio *)driverHandlerPtr;
	driverHandler->_drawRectangle(driverHandlerPtr, 0, 0, driverHandler->LcdTimings->X, driverHandler->LcdTimings->Y, true, color);
}
//#######################################################################################
