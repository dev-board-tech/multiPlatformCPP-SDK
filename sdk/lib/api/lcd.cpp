/*
 * lcd.cpp
 */

#include "lcd_def.h"
#include <include/global.h>
#include <lib/gfx/gfxdef.h>
//#######################################################################################
SysErr GI::Display::Display::setOrientation(LCD_ORIENTATION orientation)
{
	if(setOrientation_Ptr)
		setOrientation_Ptr(driverHandler_Ptr, orientation);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::setOn()
{
	if(setOn_Ptr)
		setOn_Ptr(driverHandler_Ptr);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::setOff()
{
	if(setOff_Ptr)
		setOff_Ptr(driverHandler_Ptr);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::setBacklight(u8 value)
{
	if(setBacklight_Ptr)
		setBacklight_Ptr(driverHandler_Ptr, value);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::copyScreen(void *pDisplayFrom, bool put_cursor,
			s32 X, s32 Y, u32 color)
{
	if(copyScreen_Ptr)
		copyScreen_Ptr(driverHandler_Ptr, pDisplayFrom, put_cursor, X, Y, color);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
/*//#######################################################################################
SysErr GI::Display::Display::cacheClean(s32 x_start, s32 y_start,
			s32 x_len, s32 y_len)
{
	if(cacheClean_Ptr)
		cacheClean_Ptr(driverHandler_Ptr, x_start, y_start, x_len, y_len);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}*/
//#######################################################################################
SysErr GI::Display::Display::drawRectangle(si x_start, si y_start,
			ui x_len, ui y_len, bool fill, u32 color)
{
	if(drawRectangle_Ptr && x_len && y_len)
		drawRectangle_Ptr(driverHandler_Ptr, x_start, y_start, x_len, y_len, fill, color);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::drawRectangle(si x_start, si y_start,
		ui x_len, ui y_len, bool fill, u32 color, ui cornerRadius)
{
	if(!x_len || !y_len)
		return SYS_ERR_OK;
	if(cornerRadius == 0)
	{
		return drawRectangle(x_start, y_start,x_len, y_len, fill, color);
	}
	ui radius = cornerRadius;
	ui __x_size = x_len, __y_size = y_len;
	if(radius >= (__x_size >> 1)) {
		radius = (__x_size >> 1) - 1;
	}
	if(radius >= (__y_size >> 1)) {
		radius = (__y_size >> 1) - 1;
	}
	if((~radius & 0x1) && radius)
		radius--;

	si a, b, P;
	u32 _color = color;

	a = 0;
	b = radius;
	P = 1 - radius;
	si Tmp1;
	si Tmp2;
	si Tmp3;
	si Tmp4;
	si Tmp5;
	si Tmp6;
	si Tmp7;
	si Tmp8;
	si _Tmp5 = 5, _Tmp7 = 0;

	do
	{
		Tmp1 = ((x_start + __x_size + a) - radius);
		Tmp2 = ((x_start + radius) - a);
		Tmp3 = ((x_start + __x_size + b) - radius);
		Tmp4 = ((x_start + radius) - b);
		Tmp5 = ((y_start + __y_size + a) - radius);
		Tmp6 = ((y_start + radius) - a);
		Tmp7 = ((y_start + __y_size + b) - radius);
		Tmp8 = ((y_start + radius) - b);
		if(fill)
		{

			if(_Tmp7 != Tmp7 && (Tmp1 - Tmp2) > 0)
			{
				drawHLine(Tmp2, Tmp1 - Tmp2, Tmp7 - 1, 1, color);
				drawHLine(Tmp2, Tmp1 - Tmp2, Tmp8, 1, color);
			}
			if(_Tmp5 != Tmp5 && (Tmp3 - Tmp4) > 0)
			{
				drawHLine(Tmp4, Tmp3 - Tmp4, Tmp5 - 1, 1, color);
				drawHLine(Tmp4, Tmp3 - Tmp4, Tmp6, 1, color);
			}
		}
		else
		{
			drawPixel(Tmp1 - 1, Tmp7 - 1, _color);
			drawPixel(Tmp2, Tmp7 - 1, _color);
			drawPixel(Tmp3 - 1, Tmp5 - 1, _color);
			drawPixel(Tmp3 - 1, Tmp6, _color);
			drawPixel(Tmp4, Tmp5 - 1, _color);
			drawPixel(Tmp1 - 1, Tmp8, _color);
			drawPixel(Tmp2, Tmp8, _color);
			drawPixel(Tmp4, Tmp6, _color);
		}
		_Tmp5 = Tmp5;
		_Tmp7 = Tmp7;

		if(P < 0)
			P += 3 + 2 * a++;
		else
			P += 5 + 2 * (a++ - b--);
	} while(a <= b);
	if(!fill)
	{
		if(x_len > (radius << 1)) {
			drawHLine(x_start + radius + 1, x_len - (radius << 1), y_start, 1, color);
			drawHLine(x_start + radius + 1, x_len - (radius << 1), (y_start + y_len) - 1, 1, color);
		}
		if(y_len > (radius << 1)) {
			drawVLine(y_start + radius + 1, y_len - (radius << 1), x_start, 1, color);
			drawVLine(y_start + radius + 1, y_len - (radius << 1), (x_start + x_len) - 1, 1, color);
		}
	} else {
		if(y_len > (radius << 1)) {
			drawRectangle( x_start, y_start + radius + 1, x_len, y_len - (radius << 1), true, color);
		}
	}
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::drawPixel(s32 X, s32 Y, u32 color)
{
	if(drawPixel_Ptr)
		drawPixel_Ptr(driverHandler_Ptr, X, Y, color);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::copyRectangle16Bit(u16 *rgb_buffer,
			ui x1, ui y1, ui width,
			ui height)
{
	if(copyRectangle16Bit_Ptr)
		copyRectangle16Bit_Ptr(driverHandler_Ptr, rgb_buffer, x1, y1, width, height);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::copyRectangle24Bit(u8 *rgb_buffer,
			ui x1, ui y1, ui width,
			ui height)
{
	if(copyRectangle24Bit_Ptr)
		copyRectangle24Bit_Ptr(driverHandler_Ptr, rgb_buffer, x1, y1, width, height);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::copyRectangle32Bit(u8 *rgb_buffer,
			ui x1, ui y1, ui width,
			ui height)
{
	if(copyRectangle32Bit_Ptr)
		copyRectangle32Bit_Ptr(driverHandler_Ptr, rgb_buffer, x1, y1, width, height);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::drawHLine(si X1, ui X2,
			si Y, u8 width, u32 color)
{
	if(drawHLine_Ptr)
		drawHLine_Ptr(driverHandler_Ptr, X1, X2, Y, width, color);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::drawVLine(si Y1, ui Y2,
			si X, u8 width, u32 color)
{
	if(drawVLine_Ptr)
		drawVLine_Ptr(driverHandler_Ptr, Y1, Y2, X, width, color);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::clear(u32 color)
{
	if(clear_Ptr)
		clear_Ptr(driverHandler_Ptr, color);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::setLuminosity(u8 luminosity)
{
	if(setLuminosity_Ptr)
		setLuminosity_Ptr(driverHandler_Ptr, luminosity);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::drawTouchPoint(s32 X, s32 Y, u32 color)
{
	if(drawTouchPoint_Ptr)
	{
		drawTouchPoint_Ptr(driverHandler_Ptr, X, Y, color);
		return SYS_ERR_OK;
	}
	drawHLine(X - 7, 6, Y, 1, color);
	drawHLine(X + 2, 6, Y, 1, color);
	drawVLine(Y - 7, 6, X, 1, color);
	drawVLine(Y + 2, 6, X, 1, color);
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::drawCircle(si x, si y, ui _radius, bool fill, u32 color)
{
	if(drawCircle_Ptr)
	{
		drawCircle_Ptr(driverHandler_Ptr, x, y, _radius, fill, color);
		return SYS_ERR_OK;
	}
	ui radius = _radius;
	if (radius < 0)
		radius = ~radius;
	si a, b, P;

	a = 0;
	b = radius;
	P = 1 - radius;
	si Tmp1;
	si Tmp2;
	si Tmp3;
	si Tmp4;
	si Tmp5;
	si Tmp6;
	si Tmp7;
	si Tmp8;
	si _Tmp5 = 5, _Tmp7 = 0;

	do
	{
		Tmp1 = x + a;
		Tmp2 = x - a;
		Tmp3 = x + b;
		Tmp4 = x - b;
		Tmp5 = y + a;
		Tmp6 = y - a;
		Tmp7 = y + b;
		Tmp8 = y - b;
		if (fill)
		{

			if (_Tmp7 != Tmp7)
			{
				drawHLine(Tmp2, Tmp1 - Tmp2, Tmp7, 1, color);
				drawHLine(Tmp2, Tmp1 - Tmp2, Tmp8, 1, color);
			}
			if (_Tmp5 != Tmp5)
			{
				drawHLine(Tmp4, Tmp3 - Tmp4, Tmp5, 1, color);
				drawHLine(Tmp4, Tmp3 - Tmp4, Tmp6, 1, color);
			}
			_Tmp5 = Tmp5;
			_Tmp7 = Tmp7;
		}
		else
		{
			drawPixel(Tmp1, Tmp7, color);
			drawPixel(Tmp3, Tmp5, color);
			drawPixel(Tmp2, Tmp7, color);
			drawPixel(Tmp4, Tmp5, color);
			drawPixel(Tmp3, Tmp6, color);
			drawPixel(Tmp1, Tmp8, color);
			drawPixel(Tmp2, Tmp8, color);
			drawPixel(Tmp4, Tmp6, color);
		}

		if (P < 0)
			P += 3 + 2 * a++;
		else
			P += 5 + 2 * (a++ - b--);
	} while (a <= b);
	//refresh();
	return SYS_ERR_OK;
}
//#######################################################################################
SysErr GI::Display::Display::drawLine(si X1, si Y1, si X2, si Y2, u8 width, u32 color)
{
	if(drawLine_Ptr)
	{
		drawLine_Ptr(driverHandler_Ptr, X1, Y1, X2, Y2, width, color);
		return SYS_ERR_OK;
	}
	if (width == 1)
	{
		si currentX, currentY, Xinc, Yinc, Dx, Dy, TwoDx, TwoDy,
				twoDxAccumulatedError, twoDyAccumulatedError;
		Dx = (X2 - X1);
		Dy = (Y2 - Y1);
		TwoDx = Dx + Dx;
		TwoDy = Dy + Dy;
		currentX = X1;
		currentY = Y1;
		Xinc = 1;
		Yinc = 1;
		if (Dx < 0)
		{
			Xinc = -1;
			Dx = -Dx;
			TwoDx = -TwoDx;
		}
		if (Dy < 0)
		{
			Yinc = -1;
			Dy = -Dy;
			TwoDy = -TwoDy;
		}
		drawPixel(X1, Y1, color);
		if ((Dx != 0) || (Dy != 0))
		{
			if (Dy <= Dx)
			{
				twoDxAccumulatedError = 0;
				do
				{
					currentX += Xinc;
					twoDxAccumulatedError += TwoDy;
					if (twoDxAccumulatedError > Dx)
					{
						currentY += Yinc;
						twoDxAccumulatedError -= TwoDx;
					}
					drawPixel(currentX, currentY, color);
				} while (currentX != X2);
			}
			else
			{
				twoDyAccumulatedError = 0;
				do
				{
					currentY += Yinc;
					twoDyAccumulatedError += TwoDx;
					if (twoDyAccumulatedError > Dy)
					{
						currentX += Xinc;
						twoDyAccumulatedError -= TwoDy;
					}
					drawPixel(currentX, currentY, color);
				} while (currentY != Y2);
			}
		}
	}
	else
	{
		s32 half_width;
		s32 half_width_square;
		si dy, dx;
		si addx = 1, addy = 1, j;
		si P, diff;
		s32 c1, c2;

		si i = 0;
		half_width = width >> 1;
		half_width_square = half_width;
		dx = X2 - X1;
		dy = Y2 - Y1;
		if(dx < 0) {
			dx = -dx;
			half_width_square = half_width * half_width;
		}
		if(dy < 0) {
			dy = -dy;
			half_width_square = half_width * half_width;
		}

		c1 = -(dx * X1 + dy * Y1);
		c2 = -(dx * X2 + dy * Y2);

		if (X1 > X2)
		{
			s32 temp;
			temp = c1;
			c1 = c2;
			c2 = temp;
			addx = -1;
		}
		if (Y1 > Y2)
		{
			s32 temp;
			temp = c1;
			c1 = c2;
			c2 = temp;
			addy = -1;
		}

		if (dx >= dy)
		{
			P = 2 * dy - dx;
			diff = P - dx;

			for (i = 0; i <= dx; ++i)
			{
#ifdef Use_FastDrawBar
				lcd_func.screen_draw_vertical_line(pContext,Y1+ (-half_width), Y1+ (half_width+width % 2), X1, 1);
#else
				for (j = -half_width; j < half_width + width % 2; ++j)
				{
					s32 temp;

					temp = dx * X1 + dy * (Y1 + j); // Use more RAM to increase speed
					if (temp + c1 >= -half_width_square && temp + c2 <= half_width_square)
						drawPixel(X1, Y1 + j, color);
				}
#endif
				if (P < 0)
				{
					P += 2 * dy;
					X1 += addx;
				}
				else
				{
					P += diff;
					X1 += addx;
					Y1 += addy;
				}
			}
		}
		else
		{
			P = 2 * dx - dy;
			diff = P - dy;

			for (i = 0; i <= dy; ++i)
			{
				if (P < 0)
				{
					P += 2 * dx;
					Y1 += addy;
				}
				else
				{
					P += diff;
					X1 += addx;
					Y1 += addy;
				}
#ifdef Use_FastDrawBar
				lcd_func.put_horizontal_line(pContext,(X1+(-half_width)), (X1+(half_width+width % 2)), Y1, 1);
#else
				for (j = -half_width; j < half_width + width % 2; ++j)
				{
					si temp;

					temp = dx * X1 + dy * (Y1 + j); // Use more RAM to increase speed
					if (temp + c1 >= 0 && temp + c2 <= 0)
						drawPixel(X1 + j, Y1, color);
				}
#endif
			}
		}
	}
	return SYS_ERR_OK;
}

//#######################################################################################
static void elipseplot(GI::Display::Display *pDisplay, si xc, si yc,
		si x, si y, bool Fill, u32 color)
{
	si Tmp1 = xc + x;
	si Tmp2 = xc - x;
	si Tmp3 = yc + y;
	si Tmp4 = yc - y;

	if (Fill)
	{
		pDisplay->drawHLine(Tmp2, Tmp1 - Tmp2, Tmp3, 1, color);
		pDisplay->drawHLine(Tmp2, Tmp1 - Tmp2, Tmp4, 1, color);
	}
	else
	{
		pDisplay->drawPixel((u32) (Tmp1), (u32) (Tmp3), color);
		pDisplay->drawPixel((u32) (Tmp2), (u32) (Tmp3), color);
		pDisplay->drawPixel((u32) (Tmp1), (u32) (Tmp4), color);
		pDisplay->drawPixel((u32) (Tmp2), (u32) (Tmp4), color);
	}
}
//----------------------------------------------------------------------------------------
SysErr GI::Display::Display::drawElipse(si x,si y,ui rx,ui ry, bool fill, u32 color)
{
	if(drawElipse_Ptr)
	{
		drawElipse_Ptr(driverHandler_Ptr, x, y, rx, ry, fill, color);
		return SYS_ERR_OK;
	}
	ui _rx = rx;
	if (_rx < 0)
		_rx = 0xFFFFFFFF - _rx;
	ui _ry = ry;
	if (_ry < 0)
		_ry = 0xFFFFFFFF - _ry;
	si rx2 = _rx * _rx;
	si ry2 = _ry * _ry;
	si tory2 = 2 * ry2;
	si torx2 = 2 * rx2;
	si p;
	si _x = 0;
	si _y = _ry;
	si py = torx2 * _y;
	si px = 0;
	elipseplot(this, x, y, _x, _y, fill, color);
	p = /*round(*/ry2 - (rx2 * _ry) + (0.25 * rx2)/*)*/;
	while (px < py)
	{
		_x++;
		px += tory2;
		if (p < 0)
			p += ry2 + px;
		else
		{
			_y--;
			py -= torx2;
			p += ry2 + px - py;
		}
		elipseplot(this, x, y, _x, _y, fill, color);
	}
	p = /*round(*/ry2 * (_x + 0.5) * (_x + 0.5) + rx2 * (_y - 1) * (_y - 1)
			- rx2 * ry2/*)*/;
	while (_y > 0)
	{
		_y--;
		py -= torx2;
		if (p > 0)
			p += rx2 - py;
		else
		{
			_x++;
			px += tory2;
			p += rx2 - py + px;
		}
		elipseplot(this, x, y, _x, _y, fill, color);
	}
	return SYS_ERR_OK;
}

//#######################################################################################
/*
 *  the coordinates of vertices are (A.x,A.y), (B.x,B.y), (C.x,C.y); we assume that A.y<=B.y<=C.y (you should sort them first)
 * dx1,dx2,dx3 are deltas used in interpolation
 * horizline draws horizontal segment with coordinates (S.x,Y), (E.x,Y)
 * S.x, E.x are left and right x-coordinates of the segment we have to draw
 * S=A means that S.x=A.x; S.y=A.y;
 */

static void triangle_swap_nibble(si* a, si *b)
{
	si t = *a;
	*a = *b;
	*b = t;
}

SysErr GI::Display::Display::drawTriangle(si  ax,si  ay,si  bx,si  by,si  cx,si  cy, bool fill, u32 color)
{
	if(drawTriangle_Ptr)
	{
		drawTriangle_Ptr(driverHandler_Ptr, ax, ay, bx, by, cx, cy, fill, color);
		return SYS_ERR_OK;
	}
	if(!fill) {
		drawLine(ax, ay, bx, by, 1, color);
		drawLine(ax, ay, cx, cy, 1, color);
		drawLine(bx, by, cx, cy, 1, color);
		return SYS_ERR_OK;
	}
	s32 dx1, dx2, dx3;
	s32 sx, ex;
	s32 sy, ey;

	if (ay > by)
	{
		triangle_swap_nibble(&ay, &by);
		triangle_swap_nibble(&ax, &bx);
	}
	if (ay > cy)
	{
		triangle_swap_nibble(&ay, &cy);
		triangle_swap_nibble(&ax, &cx);
	}
	if (by > cy)
	{
		triangle_swap_nibble(&by, &cy);
		triangle_swap_nibble(&bx, &cx);
	}
	if (by - ay > 0)
		dx1 = ((s32) (bx - ax) << 16) / (by - ay);
	else
		dx1 = 0;
	if (cy - ay > 0)
		dx2 = ((s32) (cx - ax) << 16) / (cy - ay);
	else
		dx2 = 0;
	if (cy - by > 0)
		dx3 = ((s32) (cx - bx) << 16) / (cy - by);
	else
		dx3 = 0;

	ex = sx = (s32) ax << 16;
	ey = sy = ay;

	if (dx1 > dx2)
	{
		while (sy <= by)
		{
			drawLine(sx >> 16, sy++, ex >> 16, ey++, 1, color);
			sx += dx2;
			ex += dx1;
		}
		ex = (s32) bx << 16;
		ey = by;
		while (sy <= cy)
		{
			drawLine(sx >> 16, sy++, ex >> 16, ey++, 1, color);
			sx += dx2;
			ex += dx3;
		}
	}
	else
	{
		while (sy <= by)
		{
			drawLine(sx >> 16, sy++, ex >> 16, ey++, 1, color);
			sx += dx1;
			ex += dx2;
		}
		sx = (s32) bx << 16;
		sy = by;
		while (sy <= cy)
		{
			drawLine(sx >> 16, sy++, ex >> 16, ey++, 1, color);
			sx += dx3;
			ex += dx2;
		}
	}
	return SYS_ERR_OK;
}
//#######################################################################################
#ifdef __AVR_XMEGA__
#include <avr/pgmspace.h>
extern const u8 CharTable6x8[];
#else
extern const u8 CharTable6x8[];
#endif
int GI::Display::Display::drawString(GI::string *string, si X, si Y, tRectangle *box, bool WordWrap, u32 foreColor, u32 inkColor)
{
	return drawString(string->buff, X, Y, box, WordWrap, foreColor, inkColor);
}


int GI::Display::Display::drawString(char *string, si X, si Y, tRectangle *box, bool wordWrap, u32 foreColor, u32 inkColor)
{
	tRectangle int_box;
	if(box)
	{
		int_box.sXMin = box->sXMin;
		int_box.sXMax = box->sXMax;
		int_box.sYMin = box->sYMin;
		int_box.sYMax = box->sYMax;
	}
	else
	{
		int_box.sXMin = 0;
		int_box.sXMax = LcdTimings->X;
		int_box.sYMin = 0;
		int_box.sYMax = LcdTimings->Y;
	}
	char *pcString = string;
	bool WordWrap = wordWrap;
	//s32 _SelStart = properties->_SelStart;
	//s32 _SelLen = properties->_SelLen;

	s8 chWidth = 0;
	s8 chHeight = 0;
	s32 CharPtr;
	s8 Tmp = 0;
	s32 Cursor_X = X;
	s32 Cursor_Y = Y;
	bool ulVisible = true;
	s32 CharCnt = 0;
	bool ulOpaque = false;
#ifdef __AVR_XMEGA__
	chWidth = pgm_read_byte(&CharTable6x8[2]);
	chHeight = pgm_read_byte(&CharTable6x8[3]);
#else
	chWidth = CharTable6x8[2];
	chHeight = CharTable6x8[3];
#endif
	do
	{
		u8 Char = *pcString;
		if (Char == 0)
		{
			//refresh();
			return CharCnt - 1;
		}
#ifdef __AVR_XMEGA__
		CharPtr = ((Char - pgm_read_byte(&CharTable6x8[4])) * chWidth) + pgm_read_byte(&CharTable6x8[0]);
		if(Char < pgm_read_byte(&CharTable6x8[4]) || Char > pgm_read_byte(&CharTable6x8[5]))
#else
		CharPtr = ((Char - CharTable6x8[4]) * chWidth) + CharTable6x8[0];
		if (Char < CharTable6x8[4] || Char > CharTable6x8[5])
#endif
		{
			//chWidth_Tmp = chWidth;
			chWidth = 0;
		}
		else
		{
			u8 Temp;
			/* if CompactWriting is true search the character for free cols from right to left and clear them */
			if (!terminalMode)
			{
				for (Tmp = 1; Tmp < chWidth; Tmp++)
				{
#ifdef __AVR_XMEGA__
					Temp = pgm_read_byte(&CharTable6x8[Tmp + CharPtr]);
#else
					Temp = CharTable6x8[Tmp + CharPtr];
#endif
					if (Temp == 0)
						break;
				}
				Tmp++;
			}
			else
			{
				Tmp = chWidth;
			}
			if (Cursor_X + Tmp >= int_box.sXMin
					&& Cursor_X < int_box.sXMax + Tmp
					&& Cursor_Y + chHeight >= int_box.sYMin
					&& Cursor_Y < int_box.sYMax + chHeight)
			{
				if (ulVisible)
				{
					s32 XX = 0;
					s32 YY = 0;
					for (XX = 0; XX < Tmp; XX++)
					{
#ifdef __AVR_XMEGA__
						Temp = pgm_read_byte(&CharTable6x8[XX + CharPtr]);
#else
						Temp = CharTable6x8[XX + CharPtr];
#endif
						for (YY = 0; YY < chHeight; YY++)
						{
							if (Temp & 0x1)
							{
								drawPixel(XX + Cursor_X,
										YY + Cursor_Y, inkColor);
							}
							else
							{
								if (ulOpaque)
									drawPixel(XX + Cursor_X,
											YY + Cursor_Y, foreColor);
							}
							Temp = Temp >> 1;
						}
					}
				}
			}
		}
		//if(Tmp < chWidth) Tmp++;
		switch (Char)
		{
		case '\r':
			Cursor_X = X;
			pcString++;
			break;
		case '\n':
			Cursor_Y += chHeight;
			pcString++;
			break;
			//case 9:
			//case 11:
			////s16 TabCursor = (ScreenStruct->Cursor_X/((chWidth_Tmp>>1)*4)*(chWidth_Tmp>>1))*4;
			//Tmp = (((Cursor_X/(chWidth_Tmp<<2))*(chWidth_Tmp<<2))-Cursor_X) + (chWidth_Tmp<<2);
		default:
			Cursor_X += Tmp;
			/*if((ScreenStruct->Cursor_X + chWidth > ScreenStruct->Width) && ScreenStruct->WorldWrap == True)
			 {
			 ScreenStruct->CharWidth = Tmp;
			 ScreenStruct->CharHeight = chHeight;
			 return EOF;
			 }*/
			if ((Cursor_X + chWidth > int_box.sXMax)
					&& WordWrap == true)
			{
				Cursor_Y += chHeight;
				Cursor_X = X;
			}
			pcString++;
		}
		CharCnt++;
	} while (1);
}
//#######################################################################################
SysErr GI::Display::Display::refresh()
{
	if(refresh_Ptr)
		refresh_Ptr(driverHandler_Ptr);
	else
		return SYS_ERR_NOT_IMPLEMENTED;
	return SYS_ERR_OK;
}
//#######################################################################################
