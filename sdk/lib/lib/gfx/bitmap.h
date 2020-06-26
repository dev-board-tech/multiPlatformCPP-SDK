/*
 *  lib/gfx/bitmap.h
 */

#ifndef LIB_LIB_GFX_BITMAP_H_
#define LIB_LIB_GFX_BITMAP_H_

#include <include/global.h>
#include "gfxdef.h"

class Bitmap {
public:
	Bitmap(s32 width, s32 height);
	~Bitmap();
    SysErr resetWindow();
    SysErr enlargeWindow(GI::rectangle window);
    SysErr setWindow(GI::rectangle window);
	SysErr setPixel(s32 x, s32 y, Color::ARGB color);
    SysErr resize(s32 width, s32 height);
    SysErr copy(Bitmap bitmapFrom);

private:
	Color::ARGB *buff;
	s32 width;
	s32 height;
    GI::rectangle window;
};

/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "bitmap.cpp"
#endif
/*#####################################################*/
#endif /* LIB_LIB_GFX_BITMAP_H_ */
