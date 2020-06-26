#include "screen.h"

GI::Device::Display::IntScreen::IntScreen(LCD_TIMINGS *timings, FPGA_GFX_ACCEL_t *lcdDev)
{
	if(!timings || !lcdDev)
		return;
	this->lcdDev = lcdDev;
	LcdTimings = timings;
	setOn_Ptr = &GI::Device::Display::IntScreen::_setOn;
	setOff_Ptr = &GI::Device::Display::IntScreen::_setOff;
	drawPixel_Ptr = &GI::Device::Display::IntScreen::_drawPixel;
	drawRectangle_Ptr = &GI::Device::Display::IntScreen::_drawRectangle;
	drawHLine_Ptr = &GI::Device::Display::IntScreen::_drawHLine;
	drawVLine_Ptr = &GI::Device::Display::IntScreen::_drawVLine;
	clear_Ptr = &GI::Device::Display::IntScreen::_clear;
	//refresh_Ptr = &GI::Device::Display::IntScreen::_refresh;
	sClipRegion.sXMin = 0;
	sClipRegion.sYMin = 0;
	sClipRegion.sXMax = LcdTimings->X;
	sClipRegion.sYMax = LcdTimings->Y;
	driverHandler_Ptr = (void *)this;
	lcdDev->LCD.LCD_V_BACK_PORCH = LcdTimings->vbp;
	lcdDev->LCD.LCD_V_FRONT_PORCH = LcdTimings->vfp;
	lcdDev->LCD.LCD_H_BACK_PORCH = LcdTimings->hbp;
	lcdDev->LCD.LCD_H_FRONT_PORCH = LcdTimings->hfp;
	lcdDev->LCD.LCD_V_PULSE_WIDTH = LcdTimings->vsw;
	lcdDev->LCD.LCD_H_PULSE_WIDTH = LcdTimings->hsw;
	lcdDev->LCD.LCD_PIXEL_SIZE = LcdTimings->bus_size;
}

GI::Device::Display::IntScreen::~IntScreen()
{

}

void GI::Device::Display::IntScreen::_setOn(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::IntScreen *driverHandler = (GI::Device::Display::IntScreen *)driverHandlerPtr;
	driverHandler->lcdDev->LCD.LCD_CTRL |= EN_bm;
}

void GI::Device::Display::IntScreen::_setOff(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::IntScreen *driverHandler = (GI::Device::Display::IntScreen *)driverHandlerPtr;
	driverHandler->lcdDev->LCD.LCD_CTRL &= ~EN_bm;
}

bool GI::Device::Display::IntScreen::_setOrientation(void *driverHandlerPtr, LCD_ORIENTATION orientation)
{
	//GI::Device::Display::IntScreen *driverHandler = (GI::Device::Display::IntScreen *)driverHandlerPtr;
	return false;
}

void GI::Device::Display::IntScreen::_drawPixel(void *driverHandlerPtr, si X_Coordonate, si Y_Coordonate, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::IntScreen *driverHandler = (GI::Device::Display::IntScreen *)driverHandlerPtr;
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
	switch ((u8)driverHandler->LcdTimings->orientation)
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
	do
	{
	} while (driverHandler->lcdDev->GFX_ACCEL_CMD != 0);
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN = _X_Coordonate;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN = _Y_Coordonate;
	driverHandler->lcdDev->GFX_ACCEL_COLOR = color;
	driverHandler->lcdDev->GFX_ACCEL_CMD = GFX_ACCEL_CMD_PIXEL_LOAD;
}

void GI::Device::Display::IntScreen::_drawRectangle(void *driverHandlerPtr, si x_start, si y_start, ui x_len, ui y_len, bool fill, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::IntScreen *driverHandler = (GI::Device::Display::IntScreen *)driverHandlerPtr;
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
	do
	{
	} while (driverHandler->lcdDev->GFX_ACCEL_CMD);
	if(fill)
	{
		driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN = x_start;
		driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MAX = (x_start + x_len);
		driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN = y_start;
		driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MAX = (y_start + y_len);
		driverHandler->lcdDev->GFX_ACCEL_COLOR = color;
		driverHandler->lcdDev->GFX_ACCEL_CMD = GFX_ACCEL_CMD_FILL_RECT;
	}
	else
	{
		int _x_end = x_end;
		int _x_start = x_start;
		if(_x_end > driverHandler->sClipRegion.sXMax)
			_x_end = driverHandler->sClipRegion.sXMax;
		if(_x_start < driverHandler->sClipRegion.sXMin)
			_x_start = driverHandler->sClipRegion.sXMin;
		if(y_start >= driverHandler->sClipRegion.sYMin)
		{
			_drawHLine(driverHandler, _x_start, _x_end, y_start, 1, color);
		}

		if(y_end <= driverHandler->sClipRegion.sYMax)
		{
			_drawHLine(driverHandler, _x_start, _x_end, y_end - 1, 1, color);
		}

		int _y_end = y_end;
		if(_y_end > driverHandler->sClipRegion.sYMax)
			_y_end = driverHandler->sClipRegion.sYMax;
		int _y_start = y_start;
		if(_y_start < driverHandler->sClipRegion.sYMin)
			_y_start = driverHandler->sClipRegion.sYMin;
		if(x_start >= driverHandler->sClipRegion.sXMin)
		{
			_drawVLine(driverHandler, _y_start, _y_end, x_start, 1, color);
		}

		if(x_end <= driverHandler->sClipRegion.sXMax)
		{
			_drawVLine(driverHandler, _y_start, _y_end, x_end - 1, 1, color);
		}
	}
}

void GI::Device::Display::IntScreen::_drawHLine(void *driverHandlerPtr, si X1, ui X2, si Y, u8 width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::IntScreen *driverHandler = (GI::Device::Display::IntScreen *)driverHandlerPtr;
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
	do
	{
	} while (driverHandler->lcdDev->GFX_ACCEL_CMD);
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN = X1_Tmp;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MAX = X2_Tmp;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN = (Y - Half_width1);
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MAX = (Y + Half_width2);
	driverHandler->lcdDev->GFX_ACCEL_COLOR = color;
	driverHandler->lcdDev->GFX_ACCEL_CMD = GFX_ACCEL_CMD_FILL_RECT;
}

void GI::Device::Display::IntScreen::_drawVLine(void *driverHandlerPtr, si Y1, ui Y2, si X, u8 width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::IntScreen *driverHandler = (GI::Device::Display::IntScreen *)driverHandlerPtr;
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
	do
	{
	} while (driverHandler->lcdDev->GFX_ACCEL_CMD);
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN = X - Half_width1;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MAX = X + Half_width2;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN = Y1_Tmp;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MAX = Y2_Tmp;
	driverHandler->lcdDev->GFX_ACCEL_COLOR = color;
	driverHandler->lcdDev->GFX_ACCEL_CMD = GFX_ACCEL_CMD_FILL_RECT;
}

void GI::Device::Display::IntScreen::_clear(void *driverHandlerPtr, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::IntScreen *driverHandler = (GI::Device::Display::IntScreen *)driverHandlerPtr;
	_drawRectangle(driverHandlerPtr, 0, 0, driverHandler->LcdTimings->X - 1, driverHandler->LcdTimings->Y - 1, 1, color);
}

