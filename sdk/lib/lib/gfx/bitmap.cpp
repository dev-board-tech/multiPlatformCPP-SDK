/*
 *  lib/gfx/bitmap.cpp
 */

#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

Bitmap::Bitmap(s32 width, s32 height)
{
    if(!this)
		return;
	memset(this, 0, sizeof(*this));
	if(width <= 0 || height <= 0)
		return;
	buff = (Color::ARGB *)calloc(1, sizeof(Color::ARGB) * width * height);
	if(buff)
	{
		this->width = width;
		this->height = height;
	}
}
Bitmap::~Bitmap()
{
	if(buff)
		free(buff);
}

SysErr Bitmap::resetWindow()
{
    window.Position.X = this->width;
    window.Size.X = 0;
    window.Size.Y = 0;
    return SYS_ERR_OK;
}

SysErr Bitmap::enlargeWindow(GI::rectangle window)
{
    if(window.Position.X < this->window.Position.X)
        this->window.Position.X = window.Position.X;
    if(window.Position.Y < this->window.Position.Y)
        this->window.Position.Y = window.Position.Y;
    if(window.Size.X > this->window.Size.X)
        this->window.Size.X = window.Size.X;
    if(window.Size.Y > this->window.Size.Y)
        this->window.Size.Y = window.Size.Y;
    return SYS_ERR_OK;
}

SysErr Bitmap::setWindow(GI::rectangle window)
{
    this->window = window;
    return SYS_ERR_OK;
}

SysErr Bitmap::setPixel(s32 x, s32 y, Color::ARGB color)
{
	if(x < 0 || x >= width || y < 0 || y >= height)
		return SYS_ERR_OUT_OF_RANGE;
	if(!buff)
		return SYS_ERR_BUFF_NOT_ALLOCATED;
	buff[(x * width) + y] = color;
	return SYS_ERR_OK;
}

SysErr resize(s32 width, s32 height)
{
    return SYS_ERR_NOT_IMPLEMENTED;
}

SysErr copy(Bitmap bitmapFrom)
{
    return SYS_ERR_NOT_IMPLEMENTED;
}



