/*
 *  lib/gfx/progressbar.h
 */

#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_
//#######################################################################################
#include <stdbool.h>
#include "controls_definition.h"
//#include "window_def.h"
#include <lib/util/converters.h>
#include "string.h"
#include "gfxdef.h"
//#######################################################################################
namespace GI
{
namespace Screen
{
namespace Gfx
{
class ProgressBar {
public:
    ProgressBar(void *parentWindowHandler);
    ProgressBar(GI::Display::Display *ScreenDisplay);
	~ProgressBar();
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
	GI::Screen::Gfx::String *Caption;
	controls_color_struct_t Color;

	struct {
		struct {
			Color::ARGB border;
			Color::ARGB back;
			Color::ARGB progress;
			Color::ARGB text;
		}disabled;
		struct {
			Color::ARGB border;
			Color::ARGB back;
			Color::ARGB progress;
			Color::ARGB text;
		}enabled;
	}color;

	struct
	{
		struct
		{
			void* CallbackData;
			void* CallbackReturnData;
			void*(*CallBack)(void*);
		}OnMove;
		struct
		{
			void* CallbackData;
			void* CallbackReturnData;
			void*(*CallBack)(void*);
		}OnUp;
		struct
		{
			void* CallbackData;
			void* CallbackReturnData;
			void*(*CallBack)(void*);
		}OnDown;
		struct
		{
			void* CallbackData;
			void* CallbackReturnData;
			void*(*CallBack)(void*);
		}OnValueChange;
		bool CursorUp;
		bool CursorDown;
		bool CursorMove;
		bool ValueChanged;
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
		u32 OldValue;
		u32 OldMinimValue;
		u32 OldMaximValue;
		bool OldStateVisible;
		bool OldStateEnabled;
		bool OldStateCheched;
		bool NeedEntireRefresh;
		bool NeedEntireRepaint;
		bool NoPaintBackGround;
		bool CursorDownInsideBox;
		CursorState OldStateCursor;
		GI::Display::Display *pDisplay;
		void *parentWindowHandler;
		bool parentWindowStateEnabled;
		GI::Screen::Gfx::String *Caption;
	}Internals;
	bool Visible;
	bool Enabled;
	u32 Value;
	u32 MinimValue;
	u32 MaximValue;
	CursorState StateChangedOn;

private:
	void paint(void *pDisplay, s32 x_start, s32 y_start, s32 x_len, s32 y_len, tControlCommandData* control_comand);

};
}
}
}
//#######################################################################################
#ifdef USE_VISUAL_STUDIO
#include "progressbar.cpp"
#endif
//#######################################################################################
#endif /* PROGRESSBAR_H_ */
