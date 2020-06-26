/*
 * lib/gfx/item.h
 */

#ifndef LIB_LIB_GFX_ITEM_H_
#define LIB_LIB_GFX_ITEM_H_

#include <lib/gfx/string.h>
#include "controls_definition.h"

namespace GI
{
namespace Screen
{
namespace Gfx
{
class Item {
public:
	Item(s8* text, u32 location);

	struct
	{
		s32 X;
		s32 Y;
	}Size;
	GI::Screen::Gfx::String *Caption;
	controls_color_struct_t Color;
	bool CursorDownInsideBox;

};
}
}
}

/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "item.cpp"
#endif
/*#####################################################*/
#endif /* LIB_LIB_GFX_ITEM_H_ */
