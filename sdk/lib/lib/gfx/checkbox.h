/*
 *  lib/gfx/checkbox.h
 */

#ifndef CHECKBOX_H_
#define CHECKBOX_H_
//#######################################################################################
#include <stdbool.h>
#include "string.h"
#include "controls_definition.h"
//#include "window_def.h"
#include "gfxdef.h"
//#######################################################################################
//#######################################################################################
namespace GI
{
namespace Screen
{
namespace Gfx
{
class CheckBox {
public:
	CheckBox(void *parentWindowHandler);
	CheckBox(GI::Display::Display *ScreenDisplay);
	~CheckBox();
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
			struct {
				Color::ARGB border;
				Color::ARGB back;
				Color::ARGB check;
				Color::ARGB ink;
			}checked;
			struct {
				Color::ARGB border;
				Color::ARGB back;
				Color::ARGB check;
				Color::ARGB ink;
			}unChecked;
		}disabled;
		struct {
			struct {
				struct {
					Color::ARGB border;
					Color::ARGB back;
					Color::ARGB check;
					Color::ARGB ink;
				}checked;
				struct {
					Color::ARGB border;
					Color::ARGB back;
					Color::ARGB check;
					Color::ARGB ink;
				}unChecked;
			}push;
			struct {
				struct {
					Color::ARGB border;
					Color::ARGB back;
					Color::ARGB check;
					Color::ARGB ink;
				}checked;
				struct {
					Color::ARGB border;
					Color::ARGB back;
					Color::ARGB check;
					Color::ARGB ink;
				}unChecked;
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
		struct
		{
			void* CallbackData;
			void* CallbackReturnData;
			void*(*CallBack)(void*);
		}OnCheched;
		struct
		{
			void* CallbackData;
			void* CallbackReturnData;
			void*(*CallBack)(void*);
		}OnUnCheched;
		bool CursorUp;
		bool CursorDown;
		bool CursorMove;
		bool Checked;
		bool UnChecked;
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
		bool OldStateCheched;
		bool NeedEntireRefresh;
		bool NeedEntireRepaint;
		bool CursorDownInsideBox;
		bool NoPaintBackGround;
		CursorState OldStateCursor;
		GI::Display::Display *pDisplay;
		void *parentWindowHandler;
		bool parentWindowStateEnabled;
		GI::Screen::Gfx::String *Caption;
	}Internals;
	enum
	{
		normal = 0,
		radio_btn
	}Style;
	bool Visible;
	bool Enabled;
	bool Cheched;
	CursorState StateChangedOn;

private:
	void paint(void *pDisplay, s32 x_start, s32 y_start, s32 x_len, s32 y_len, tControlCommandData* control_comand);

};
}
}
}
//#######################################################################################
#ifdef USE_VISUAL_STUDIO
#include "checkbox.cpp"
#endif
//#######################################################################################
#endif /* CHECKBOX_H_ */
