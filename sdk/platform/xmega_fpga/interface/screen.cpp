#include "screen.h"

extern u32 FCPU;

GI::Device::Display::LcdFpga::LcdFpga(LCD_TIMINGS *timings, FPGA_GFX_ACCEL_t *lcdDev)
{
	memset(this, 0, sizeof(*this));
	if(!timings || !lcdDev)
		return;
	this->lcdDev = lcdDev;
	LcdTimings = timings;
	setOn_Ptr = &GI::Device::Display::LcdFpga::_setOn;
	setOff_Ptr = &GI::Device::Display::LcdFpga::_setOff;
	drawPixel_Ptr = &GI::Device::Display::LcdFpga::_drawPixel;
	drawRectangle_Ptr = &GI::Device::Display::LcdFpga::_drawRectangle;
	drawHLine_Ptr = &GI::Device::Display::LcdFpga::_drawHLine;
	drawVLine_Ptr = &GI::Device::Display::LcdFpga::_drawVLine;
	clear_Ptr = &GI::Device::Display::LcdFpga::_clear;
	//refresh_Ptr = &GI::Device::Display::LcdFpga::_refresh;
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

GI::Device::Display::LcdFpga::~LcdFpga()
{

}

void GI::Device::Display::LcdFpga::_setOn(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::LcdFpga *driverHandler = (GI::Device::Display::LcdFpga *)driverHandlerPtr;
	driverHandler->lcdDev->LCD.LCD_CTRL |= EN_bm;
}

void GI::Device::Display::LcdFpga::_setOff(void *driverHandlerPtr)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::LcdFpga *driverHandler = (GI::Device::Display::LcdFpga *)driverHandlerPtr;
	driverHandler->lcdDev->LCD.LCD_CTRL &= ~EN_bm;
}

bool GI::Device::Display::LcdFpga::_setOrientation(void *driverHandlerPtr, LCD_ORIENTATION orientation)
{
	//GI::Device::Display::LcdFpga *driverHandler = (GI::Device::Display::LcdFpga *)driverHandlerPtr;
	return false;
}

void GI::Device::Display::LcdFpga::_drawPixel(void *driverHandlerPtr, si X_Coordonate, si Y_Coordonate, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::LcdFpga *driverHandler = (GI::Device::Display::LcdFpga *)driverHandlerPtr;
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
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN_H = _X_Coordonate >> 8;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN_L = _X_Coordonate;
	//driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MAX_H = (X_Coordonate + 1) >> 8;
	//driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MAX_L = (X_Coordonate + 1);
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN_H = _Y_Coordonate >> 8;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN_L = _Y_Coordonate;
	//driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MAX_H = (Y_Coordonate + 1) >> 8;
	//driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MAX_L = (Y_Coordonate + 1);
	driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_2 = color >> 16;
	driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_1 = color >> 8;
	driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_0 = color;
	driverHandler->lcdDev->GFX_ACCEL_CMD = GFX_ACCEL_CMD_PIXEL_LOAD;
}

void GI::Device::Display::LcdFpga::_drawRectangle(void *driverHandlerPtr, si x_start, si y_start, ui x_len, ui y_len, bool fill, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::LcdFpga *driverHandler = (GI::Device::Display::LcdFpga *)driverHandlerPtr;
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
		driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN_H = x_start >> 8;
		driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN_L = x_start;
		driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MAX_H = (x_start + x_len) >> 8;
		driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MAX_L = (x_start + x_len);
		driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN_H = y_start >> 8;
		driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN_L = y_start;
		driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MAX_H = (y_start + y_len) >> 8;
		driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MAX_L = (y_start + y_len);
		driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_2 = color >> 16;
		driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_1 = color >> 8;
		driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_0 = color;
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
			/*for(LineCnt = _x_start ; LineCnt < _x_end ; LineCnt++)
			{
				_drawPixel(driverHandler, LineCnt, y_start, color);
				//ScreenBuff[LineCnt + (driverHandler->Width * y_start)] = _color;
			}*/
		}

		if(y_end <= driverHandler->sClipRegion.sYMax)
		{
			_drawHLine(driverHandler, _x_start, _x_end, y_end - 1, 1, color);
			/*for(LineCnt = _x_start ; LineCnt < _x_end ; LineCnt++)
			{
				_drawPixel(driverHandler, LineCnt, y_end - 1, color);
				//ScreenBuff[LineCnt + (driverHandler->Width * (y_end - 1))] = _color;
			}*/
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
			/*for(LineCnt = _y_start ; LineCnt < _y_end ; LineCnt++)
			{
				_drawPixel(driverHandler, x_start, LineCnt, color);
				//ScreenBuff[x_start + (driverHandler->Width * LineCnt)] = _color;
			}*/
		}

		if(x_end <= driverHandler->sClipRegion.sXMax)
		{
			_drawVLine(driverHandler, _y_start, _y_end, x_end - 1, 1, color);
			/*for(LineCnt = _y_start ; LineCnt < _y_end ; LineCnt++)
			{
				_drawPixel(driverHandler, (x_end - 1), LineCnt, color);
				//ScreenBuff[(x_end - 1) + (driverHandler->Width * LineCnt)] = _color;
			}*/
		}
	}
}

void GI::Device::Display::LcdFpga::_drawHLine(void *driverHandlerPtr, si X1, ui X2, si Y, u8 width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::LcdFpga *driverHandler = (GI::Device::Display::LcdFpga *)driverHandlerPtr;
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
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN_H = X1_Tmp >> 8;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN_L = X1_Tmp;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MAX_H = X2_Tmp >> 8;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MAX_L = X2_Tmp;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN_H = (Y - Half_width1) >> 8;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN_L = (Y - Half_width1);
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MAX_H = (Y + Half_width2) >> 8;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MAX_L = (Y + Half_width2);
	driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_2 = color >> 16;
	driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_1 = color >> 8;
	driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_0 = color;
	driverHandler->lcdDev->GFX_ACCEL_CMD = GFX_ACCEL_CMD_FILL_RECT;
}

void GI::Device::Display::LcdFpga::_drawVLine(void *driverHandlerPtr, si Y1, ui Y2, si X, u8 width, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::LcdFpga *driverHandler = (GI::Device::Display::LcdFpga *)driverHandlerPtr;
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
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN_H = Half_width1 >> 8;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MIN_L = Half_width1;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MAX_H = Half_width2 >> 8;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_X_MAX_L = Half_width2;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN_H = Y1_Tmp >> 8;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MIN_L = Y1_Tmp;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MAX_H = Y2_Tmp >> 8;
	driverHandler->lcdDev->GFX_ACCEL_CLIP_Y_MAX_L = Y2_Tmp;
	driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_2 = color >> 16;
	driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_1 = color >> 8;
	driverHandler->lcdDev->GFX_ACCEL_COLOR_BYTE_0 = color;
	driverHandler->lcdDev->GFX_ACCEL_CMD = GFX_ACCEL_CMD_FILL_RECT;
}

void GI::Device::Display::LcdFpga::_clear(void *driverHandlerPtr, u32 color)
{
	if(!driverHandlerPtr)
		return;
	GI::Device::Display::LcdFpga *driverHandler = (GI::Device::Display::LcdFpga *)driverHandlerPtr;
	_drawRectangle(driverHandlerPtr, 0, 0, driverHandler->LcdTimings->X - 1, driverHandler->LcdTimings->Y - 1, 1, color);
}

