/*
 *  lib/gfx/scrollbar.h
 */

#ifndef SCROLLBAR_H_
#define SCROLLBAR_H_

#include <stdbool.h>
#include "controls_definition.h"
#include "button.h"
#include "string.h"
#include "gfxdef.h"

//#######################################################################################
namespace GI
{
namespace Screen
{
namespace Gfx
{
class ScrollBar {
public:
    ScrollBar(void *parentWindowHandler);
    ScrollBar(GI::Display::Display *ScreenDisplay);
	~ScrollBar();
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
		s32 MinBtnSize;
	}Size;
	controls_color_struct_t Color;

	struct {
		struct {
			Color::ARGB border;
			Color::ARGB back;
		}disabled;
		struct {
			Color::ARGB border;
			Color::ARGB back;
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
		}OnValueChanged;
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
			s32 MinBtnSize;
		}Size;
		bool CursorDownInsideBox;
		bool OldStateVisible;
		bool OldStateEnabled;
		bool NeedEntireRefresh;
		bool NeedEntireRepaint;
		bool NoPaintBackGround;
		bool IsChildren;
		s32 OldMinimum;
		s32 OldMaximum;
		s32 OldValue;
		s32 CoordonateOfTouchDown;
		s32 CoordonateOfButtonDown;
		//s32 OffsetButtonCoord;
		CursorState OldStateCursor;
		GI::Screen::Gfx::Button *BtnSettings;
		GI::Screen::Gfx::Button *BtnUpSettings;
		GI::Screen::Gfx::Button *BtnDnSettings;
		GI::Display::Display *pDisplay;
		void *parentWindowHandler;
		bool parentWindowStateEnabled;
	}Internals;
	bool Visible;
	bool Enabled;
	s32 Minimum;
	s32 Maximum;
	s32 Value;
	CursorState StateChangedOn;

private:
	void paint(void *pDisplay, s32 x_start, s32 y_start, s32 x_len, s32 y_len, tControlCommandData* control_comand);

};
}
}
}
//#######################################################################################
#ifdef USE_VISUAL_STUDIO
#include "scrollbar.cpp"
#endif
#endif /* SCROLLBAR_H_ */
