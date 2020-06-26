/*
 *  lib/gfx/keyboard.h
 */

#ifndef VKBD_QWERTY_H_
#define VKBD_QWERTY_H_
//#######################################################################################
#include <stdbool.h>
#include "controls_definition.h"
#include "string.h"
#include "button.h"
#include "api/timer.h"
//#include "window_def.h"
//#######################################################################################
typedef enum
{
	Kbd_Qwerty_LittleLetters = 0x0,
	Kbd_Qwerty_BigLetters,
	Kbd_Qwerty_Numeric,
}kbdQwertyType_t;

typedef enum
{
	kbd_qwerty_ctrl = 128,
	kbd_qwerty_left = 256,
	kbd_qwerty_right = 257,
	kbd_qwerty_up = 258,
	kbd_qwerty_dn = 259,
}kbd_qwerty_spectial_response_t;

namespace GI
{
namespace Screen
{
namespace Gfx
{
class KbdQwerty {
public:
    KbdQwerty(void *parentWindowHandler);
    KbdQwerty(GI::Display::Display *ScreenDisplay);
	~KbdQwerty();
	void idle(tControlCommandData* control_comand);
	void idle();

	struct
	{
		s32 X;
		s32 Y;
	}Position;
	struct
	{
		s32 X;
		s32 Y;
	}Size;
	tFont *pFont;
	controls_color_struct_t Color;
	struct
	{
		struct
		{
			void* CallbackData;
			void* CallbackReturnData;
			void*(*CallBack)(void*, u32);
		}OnMove;
		struct
		{
			void* CallbackData;
			void* CallbackReturnData;
			void*(*CallBack)(void*, u32);
		}OnUp;
		struct
		{
			void* CallbackData;
			void* CallbackReturnData;
			void*(*CallBack)(void*, u32);
		}OnDown;
		bool CursorUp;
		bool CursorDown;
		bool CursorMove;
	}Events;
	struct
	{
		struct
		{
			bool Initiated;
		}Control;
		struct
		{
			s32 X;
			s32 Y;
		}Position;
		struct
		{
			s32 X;
			s32 Y;
		}PositionOffset;
		struct
		{
			s32 X;
			s32 Y;
		}Size;
		bool OldStateVisible;
		bool OldStateEnabled;
		bool NeedEntireRefresh;
		bool NeedEntireRepaint;
		bool CursorDownInsideBox;
		bool IsChildren;
		bool NoPaintBackGround;
		kbdQwertyType_t oldKeboardType;
		kbdQwertyType_t keboardType;
		CursorState OldStateCursor;
		GI::Display::Display *pDisplay;
		GI::Screen::Gfx::Button *Keys[38];
		void *parentWindowHandler;
		bool parentWindowStateEnabled;
	}Internals;
	bool Visible;
	bool Enabled;
	u32 Return;
	u32 kbd_border_size;
	u32 key_space_size;

private:
	void paint(void *pDisplay, s32 x_start, s32 y_start, s32 x_len, s32 y_len, tControlCommandData* control_comand, bool refrash);

};
}
}
}
//#######################################################################################
#ifdef USE_VISUAL_STUDIO
#include "keyboard.cpp"
#endif
//#######################################################################################
#endif /* BUTON_H_ */
