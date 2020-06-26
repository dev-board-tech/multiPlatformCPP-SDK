/*
 * ssd1331.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: Work
 */

#include "ssd1331.h"

extern u32 FCPU;

GI::Device::Display::Ssd1331::Ssd1331(LCD_TIMINGS *timings, char *spiPath, char *resetPin, char *dcPin, char *pmodEnPin, char *vccEnPin)
{
    if(!spiPath || !dcPin)
    	return;
    u32 ctl = CfgGpio::GPIO_OUT_PUSH_PULL;
    this->pmodEnPin = new GI::IO(pmodEnPin);
    this->pmodEnPin->ctl(GI::IO::IO_CTL_SET_MODE, &ctl);
    this->vccEnPin = new GI::IO(vccEnPin);
    this->vccEnPin->ctl(GI::IO::IO_CTL_SET_MODE, &ctl);
    this->resetPin = new GI::IO(resetPin);
    this->resetPin->ctl(GI::IO::IO_CTL_SET_MODE, &ctl);
    this->cdPin = new GI::IO(dcPin);
    this->cdPin->ctl(GI::IO::IO_CTL_SET_MODE, &ctl);
    this->spiDevice = new GI::IO(spiPath);
    if(!this->spiDevice || !this->resetPin || !this->cdPin)
    {
        return;
    }
    LcdTimings = timings;
	setOn_Ptr = &GI::Device::Display::Ssd1331::_setOn;
	setOff_Ptr = &GI::Device::Display::Ssd1331::_setOff;
    //cacheClean_Ptr = &GI::Dev::Ssd1331::_cacheClean;
    drawPixel_Ptr = &GI::Device::Display::Ssd1331::_drawPixel;
    drawRectangle_Ptr = &GI::Device::Display::Ssd1331::_drawRectangle;
    drawHLine_Ptr = &GI::Device::Display::Ssd1331::_drawHLine;
    drawVLine_Ptr = &GI::Device::Display::Ssd1331::_drawVLine;
    clear_Ptr = &GI::Device::Display::Ssd1331::_clear;
	refresh_Ptr = &GI::Device::Display::Ssd1331::_refresh;
	sClipRegion.sXMin = 0;
	sClipRegion.sYMin = 0;
	sClipRegion.sXMax = LcdTimings->X;
	sClipRegion.sYMax = LcdTimings->Y;
    driverHandler_Ptr = (void *)this;
    reset();
}

GI::Device::Display::Ssd1331::~Ssd1331()
{

}

void GI::Device::Display::Ssd1331::reset()
{
	resetPin->write(false);
	GI::Sys::Timer::delay(2);
	cdPin->write(false);
	resetPin->write(true);
	vccEnPin->write(false);
	pmodEnPin->write(true);
	GI::Sys::Timer::delay(20);
	resetPin->write(false);
	GI::Sys::Timer::delay(2);
	resetPin->write(true);
	GI::Sys::Timer::delay(2);
	unsigned char cmds[5];
	/* The (un)lock commands register and the byte value to set the register to unlock command mode */
	cmds[0] = 0xFD;
	cmds[1] = 0x12;
	spiDevice->write(cmds, 2);
	/* Turn off the display with a one byte command */
	cmds[0] = SSD1331_CMD_DISPLAYOFF;
	spiDevice->write(cmds, 1);
	/* The driver remap and color depth command and the single byte value */
	cmds[0] = SSD1331_CMD_SETREMAP;
	cmds[1] = 0x72;//RGB = 0x72, BGR = 0x76
	spiDevice->write(cmds, 2);
	/* The set display start line command and the single byte value for the top line */
	cmds[0] = SSD1331_CMD_SETDISPLAYSTARTLINE;
	cmds[1] = 0x00;
	spiDevice->write(cmds, 2);
	/* The  command and the single byte value for no vertical offset */
	cmds[0] = SSD1331_CMD_SETDISPLAYOFFSET;
	cmds[1] = 0x00;
	spiDevice->write(cmds, 2);
	/* A single byte value for a normal display */
	cmds[0] = SSD1331_CMD_NORMALDISPLAY;
	spiDevice->write(cmds, 1);
	/* The multiplex ratio command and the single byte value */
	cmds[0] = SSD1331_CMD_SETMULTIPLEXRATIO;
	cmds[1] = 0x3F;
	spiDevice->write(cmds, 2);
	/* The master configuration command and the required single byte value of 0x8E */
	cmds[0] = SSD1331_CMD_SETMASTERCONFIGURE;
	cmds[1] = 0x8E;
	spiDevice->write(cmds, 2);
	/* The power saving mode command and the single byte value */
	cmds[0] = SSD1331_CMD_POWERSAVEMODE;
	cmds[1] = 0x0B;
	spiDevice->write(cmds, 2);
	/* The set phase length command and the single byte value */
	cmds[0] = SSD1331_CMD_PHASEPERIODADJUSTMENT;
	cmds[1] = 0x31;
	spiDevice->write(cmds, 2);
	/* The Clock ratio and oscillator frequency command and the single byte value */
	cmds[0] = SSD1331_CMD_DISPLAYCLOCKDIV;
	cmds[1] = 0xF0;
	spiDevice->write(cmds, 2);
	/* The color A 2nd precharge speed command and the single byte value*/
	cmds[0] = SSD1331_CMD_SETPRECHARGESPEEDA;
	cmds[1] = 0x64;
	spiDevice->write(cmds, 2);
	/* The color B 2nd precharge speed command and the single byte value*/
	cmds[0] = SSD1331_CMD_SETPRECHARGESPEEDB;
	cmds[1] = 0x78;
	spiDevice->write(cmds, 2);
	/* The color C 2nd precharge speed command and the single byte value */
	cmds[0] = SSD1331_CMD_SETPRECHARGESPEEDC;
	cmds[1] = 0x64;
	spiDevice->write(cmds, 2);
	/* The set precharge voltage command and the single byte value */
	cmds[0] = SSD1331_CMD_SETPRECHARGEVOLTAGE;
	cmds[1] = 0x3A;
	spiDevice->write(cmds, 2);
	/* The VCOMH Deselect level command and the single byte value */
	cmds[0] = SSD1331_CMD_SETVVOLTAGE;
	cmds[1] = 0x3E;
	spiDevice->write(cmds, 2);
	/* The set master current attenuation factor command and the single byte value */
	cmds[0] = SSD1331_CMD_MASTERCURRENTCONTROL;
	cmds[1] = 0x06;
	spiDevice->write(cmds, 2);
	/* The Color A contrast command and the single byte value */
	cmds[0] = SSD1331_CMD_SETCONTRASTA;
	cmds[1] = 0x91;
	spiDevice->write(cmds, 2);
	/* The Color B contrast command and the single byte value */
	cmds[0] = SSD1331_CMD_SETCONTRASTB;
	cmds[1] = 0x50;
	spiDevice->write(cmds, 2);
	/* The Color C contrast command and the single byte value */
	cmds[0] = SSD1331_CMD_SETCONTRASTC;
	cmds[1] = 0x7D;
	spiDevice->write(cmds, 2);
	/* The disable scrolling command */
	cmds[0] = SSD1331_CMD_CLEARWINDOW;
	spiDevice->write(cmds, 1);
	GI::Sys::Timer::delay(2);
	cmds[0] = SSD1331_CMD_CLEARWINDOW;
	cmds[1] = 0x00;
	cmds[2] = 0x00;
	cmds[3] = LcdTimings->X - 1;
	cmds[4] = LcdTimings->Y - 1;
	spiDevice->write(cmds, 5);
	vccEnPin->write(true);
	GI::Sys::Timer::delay(100);
	/* Turn on the display with a one byte command */
	cmds[0] = SSD1331_CMD_DISPLAYON;
	spiDevice->write(cmds, 1);
	GI::Sys::Timer::delay(2);
	/* The clear command and the five bytes representing the area to clear */
	cmds[0] = SSD1331_CMD_CLEARWINDOW; 		// Enter the “clear mode”
	cmds[1] = 0x00;					// Set the starting column coordinates
	cmds[2] = 0x00;					// Set the starting row coordinates
	cmds[3] = LcdTimings->X - 1;	// Set the finishing column coordinates;
	cmds[4] = LcdTimings->Y - 1;	// Set the finishing row coordinates;
	spiDevice->write(cmds, 5);
	GI::Sys::Timer::delay(5);
	//_setLuminosity(this, 0);
}

void GI::Device::Display::Ssd1331::wrCmd(unsigned char cmd)
{
	cdPin->write(false);
	spiDevice->write(&cmd, 1);
}

void GI::Device::Display::Ssd1331::wrCmd(unsigned char *cmd, unsigned char len)
{
	cdPin->write(false);
	spiDevice->write(cmd, len);
}

void GI::Device::Display::Ssd1331::wrData(unsigned char *cmd, unsigned char len)
{
	cdPin->write(true);
	spiDevice->write(cmd, len);
}

void GI::Device::Display::Ssd1331::wrPixels(unsigned short color, unsigned short len)
{
	cdPin->write(true);
	u8 data[2];
	data[0] = color;
	data[1] = color >> 8;
	u16 cnt = len;
	while(--cnt)
		spiDevice->write(data, 2);
}

void GI::Device::Display::Ssd1331::_refresh(void *driverHandlerPtr)
{
	/*GI::Device::Display::Ssd1331 *driverHandler = (GI::Device::Display::Ssd1331 *)driverHandlerPtr;
	//driverHandler->setOff();
	driverHandler->wrCmd(0x40, 1);
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
	}*/
	/*driverHandler->wrCmd(0x21);
	driverHandler->wrCmd(0x00);
	driverHandler->wrCmd(X);
	driverHandler->wrCmd(0x22);
	driverHandler->wrCmd(0x00);
	driverHandler->wrCmd(Y);
	driverHandler->cdPin->write(true);
	driverHandler->spiDevice->write(driverHandler->buff, 512);
	driverHandler->setOn();*/
}

void GI::Device::Display::Ssd1331::_setOn(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1331 *driverHandler = (GI::Device::Display::Ssd1331 *)driverHandlerPtr;
	driverHandler->wrCmd(0xAF);
}

void GI::Device::Display::Ssd1331::_setOff(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1331 *driverHandler = (GI::Device::Display::Ssd1331 *)driverHandlerPtr;
	driverHandler->wrCmd(0xAE);
}

bool GI::Device::Display::Ssd1331::_setOrientation(void *driverHandlerPtr, LCD_ORIENTATION orientation)
{
	//GI::Device::Display::Ssd1331 *driverHandler = (GI::Device::Display::Ssd1331 *)driverHandlerPtr;
	return false;
}

/*void GI::Dev::Ug2832hsweg04::_cacheClean(void *driverHandlerPtr, si x_start, si y_start, si x_len, si y_len)
{
	GI::Device::Display::Ssd1331 *driverHandler = (GI::Device::Display::Ssd1331 *)driverHandlerPtr;
	driverHandler->_refresh(driverHandlerPtr);
}*/

void GI::Device::Display::Ssd1331::_drawPixel(void *driverHandlerPtr, si X_Coordonate, si Y_Coordonate, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1331 *driverHandler = (GI::Device::Display::Ssd1331 *)driverHandlerPtr;
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
	switch ((unsigned char)driverHandler->LcdTimings->orientation)
	{
	case LCD_ORIENTATION_LANDSCAPE_FLIP:
		_X_Coordonate = driverHandler->LcdTimings->X - X_Coordonate - 1;
		_Y_Coordonate = driverHandler->LcdTimings->Y - Y_Coordonate - 1;
		break;
	case LCD_ORIENTATION_PORTRAIT:
		_X_Coordonate = driverHandler->LcdTimings->Y - Y_Coordonate - 1;
		_Y_Coordonate = X_Coordonate;
		break;
	case LCD_ORIENTATION_PORTRAIT_FLIP:
		_X_Coordonate = Y_Coordonate;
		_Y_Coordonate = driverHandler->LcdTimings->X - X_Coordonate - 1;
		break;
	}

	u8 cmds[8];
	cmds[0] = SSD1331_CMD_DRAWLINE;	//draw rectangle
	cmds[1] = _X_Coordonate;					// start column
	cmds[2] = _Y_Coordonate;					// start row
	cmds[3] = _X_Coordonate;					// end column
	cmds[4] = _Y_Coordonate;					//end row

	cmds[5] = (u32)color >> 16;	//R
	cmds[6] = color >> 8;	//G
	cmds[7] = color;	//B
	driverHandler->wrCmd(cmds, 8);
}

void GI::Device::Display::Ssd1331::_drawRectangle(void *driverHandlerPtr, si x_start, si y_start, ui x_len, ui y_len, bool fill, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1331 *driverHandler = (GI::Device::Display::Ssd1331 *)driverHandlerPtr;
	si x_end = x_start + x_len ,y_end = y_start + y_len;
	if(x_start >= driverHandler->sClipRegion.sXMax ||
		y_start >= driverHandler->sClipRegion.sYMax ||
			x_end < driverHandler->sClipRegion.sXMin ||
				y_end < driverHandler->sClipRegion.sYMin)
					return;
	if(y_start < driverHandler->sClipRegion.sYMin)
		y_start = driverHandler->sClipRegion.sYMin;
	if(x_start < driverHandler->sClipRegion.sXMin)
		x_start = driverHandler->sClipRegion.sXMin;
	if(x_end > driverHandler->sClipRegion.sXMax - 1)
		x_end = driverHandler->sClipRegion.sXMax - 1;
	if(y_end > driverHandler->sClipRegion.sYMax - 1)
		y_end = driverHandler->sClipRegion.sYMax - 1;
	u8 cmds[13];
	cmds[0] = SSD1331_CMD_FILLWINDOW;	//draw rectangle
	if(fill)
		cmds[1] = SSD1331_ENABLE_FILL;	//draw rectangle
	else
		cmds[1] = SSD1331_DISABLE_FILL;	//draw rectangle
	driverHandler->wrCmd(cmds, 2);
	cmds[0] = SSD1331_CMD_DRAWRECTANGLE;	//draw rectangle
	cmds[1] = x_start;					// start column
	cmds[2] = y_start;					// start row
	cmds[3] = x_end;					// end column
	cmds[4] = y_end;					//end row

	cmds[5] = (u32)color >> 16;	//R
	cmds[6] = color >> 8;	//G
	cmds[7] = color;	//B
	cmds[8] = (u32)color >> 16;	//R
	cmds[9] = color >> 8;	//G
	cmds[10] = color;	//B
	driverHandler->wrCmd(cmds, 13);
	volatile u32 cntDelay = (FCPU / 10000000) * (y_end - y_start) * (x_end - x_start);
	while(cntDelay--);
	//_refresh(driverHandler);
}

void GI::Device::Display::Ssd1331::_drawHLine(void *driverHandlerPtr, si X1, ui X2, si Y, unsigned char width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1331 *driverHandler = (GI::Device::Display::Ssd1331 *)driverHandlerPtr;
	int X1_Tmp = X1, X2_Tmp = X1 + X2;
	if(X1_Tmp < (int)driverHandler->sClipRegion.sXMin)
		X1_Tmp = (int)driverHandler->sClipRegion.sXMin;
	if(X1_Tmp >= (int)driverHandler->sClipRegion.sXMax)
		X1_Tmp = (int)driverHandler->sClipRegion.sXMax - 1;
	if(X2_Tmp < (int)driverHandler->sClipRegion.sXMin)
		X2_Tmp = (int)driverHandler->sClipRegion.sXMin;
	if(X2_Tmp >= (int)driverHandler->sClipRegion.sXMax)
		X2_Tmp = (int)driverHandler->sClipRegion.sXMax - 1;
	if(Y < (int)driverHandler->sClipRegion.sYMin)
		Y = (int)driverHandler->sClipRegion.sYMin;
	if(Y >= (int)driverHandler->sClipRegion.sYMax)
		Y = (int)driverHandler->sClipRegion.sYMax - 1;
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

void GI::Device::Display::Ssd1331::_drawVLine(void *driverHandlerPtr, si Y1, ui Y2, si X, unsigned char width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1331 *driverHandler = (GI::Device::Display::Ssd1331 *)driverHandlerPtr;
	int Y1_Tmp = Y1, Y2_Tmp = Y1 + Y2;
	if(X <= (int)driverHandler->sClipRegion.sXMin)
		X = (int)driverHandler->sClipRegion.sXMin;
	if(X >= (int)driverHandler->sClipRegion.sXMax)
		X = (int)driverHandler->sClipRegion.sXMax - 1;
	if(Y1_Tmp < (int)driverHandler->sClipRegion.sYMin)
		Y1_Tmp = (int)driverHandler->sClipRegion.sYMin;
	if(Y1_Tmp >= (int)driverHandler->sClipRegion.sYMax)
		Y1_Tmp = (int)driverHandler->sClipRegion.sYMax - 1;
	if(Y2_Tmp < (int)driverHandler->sClipRegion.sYMin)
		Y2_Tmp = (int)driverHandler->sClipRegion.sYMin;
	if(Y2_Tmp >= (int)driverHandler->sClipRegion.sYMax)
		Y2_Tmp = (int)driverHandler->sClipRegion.sYMax - 1;
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

void GI::Device::Display::Ssd1331::_clear(void *driverHandlerPtr, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1331 *driverHandler = (GI::Device::Display::Ssd1331 *)driverHandlerPtr;
	_drawRectangle(driverHandlerPtr, 0, 0, driverHandler->LcdTimings->X - 1, driverHandler->LcdTimings->Y - 1, 1, color);
}

void GI::Device::Display::Ssd1331::_setLuminosity(void *driverHandlerPtr, unsigned char luminosity)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::Ssd1331 *driverHandler = (GI::Device::Display::Ssd1331 *)driverHandlerPtr;
	/* Contrast control */
	driverHandler->wrCmd(0x81);
	driverHandler->wrCmd(luminosity);
}


