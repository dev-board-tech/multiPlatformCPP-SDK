/*
 * util.h
 */

#ifndef LIB_LIB_GFX_UTIL_H_
#define LIB_LIB_GFX_UTIL_H_


#include <api/cursor_ctl_def.h>
#include "api/lcd_def.h"
#include <lib/gfx/string.h>
#include "gfxdef.h"

namespace GI
{
namespace Screen
{
	class Util {
	public:
		static void clipLimit(tRectangle *limited, tRectangle *limits);
		static bool insideBox(s32 x_start, s32 y_start, s32 x_len, s32 y_len, s32 x_point, s32 y_point);
	};
}
}

/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "util.cpp"
#endif
/*#####################################################*/
#endif /* LIB_LIB_GFX_UTIL_H_ */
