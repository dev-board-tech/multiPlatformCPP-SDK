/*
 *  lib/gfx/buton.h
 */

#ifndef BUTON_H_
#define BUTON_H_
//#######################################################################################
#include <stdbool.h>
#include <lib/gfx/string.h>
#include "controls_definition.h"
#include <api/timer.h>
#include "gfxdef.h"
//#######################################################################################
namespace GI {
namespace Screen {
namespace Gfx {
class Button {
public:
    Button(void *parentWindowHandler);
    Button(GI::Display::Display *ScreenDisplay);
	~Button();
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
			Color::ARGB text;
		}disabled;
		struct {
			struct {
				Color::ARGB border;
				Color::ARGB back;
				Color::ARGB text;
			}push;
			struct {
				Color::ARGB border;
				Color::ARGB back;
				Color::ARGB text;
			}pull;
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
		bool ContinuouslyPushTimerDisabled;
		CursorState OldStateCursor;
		GI::Sys::Timer ContinuouslyPushTimer;
		GI::Display::Display *pDisplay;
		void *parentWindowHandler;
		bool parentWindowStateEnabled;
		GI::Screen::Gfx::String *Caption;
	}Internals;
	bool Visible;
	bool Enabled;
	CursorState StateChangedOn;

private:
	void paint(void *pDisplay, s32 x_start, s32 y_start, s32 x_len, s32 y_len, tControlCommandData* control_comand);

};
}
}
}
//#######################################################################################
#ifdef USE_VISUAL_STUDIO
#include "button.cpp"
#endif
//#######################################################################################
#endif /* BUTON_H_ */
