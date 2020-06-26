/*
 *  lib/gfx/listbox.h
 */

#ifndef LISTBOX_H_
#define LISTBOX_H_
//#######################################################################################
#include <stdbool.h>
#include "scrollbar.h"
#include "scrollbar.h"
#include "controls_definition.h"
#include "string.h"
#include "gfxdef.h"
//#include "window_def.h"
//#######################################################################################
typedef struct
{
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
			Color::ARGB border;
			Color::ARGB back;
			Color::ARGB text;
		}enabled;
	}color;

	bool CursorDownInsideBox;
}listboxItem;


namespace GI
{
namespace Screen
{
namespace Gfx
{
class ListBox {
public:
    ListBox(void *parentWindowHandler);
    ListBox(GI::Display::Display *ScreenDisplay);
	~ListBox();
	void idle(tControlCommandData* control_comand);
	void idle();
	bool insert(char* text, u32 location);
	void add(char* text);
	void clear();
	bool remove(u32 location);

	struct
	{
		s32 X;
		s32 Y;
	}Position;
	struct
	{
		s32 X;
		s32 Y;
		s32 ItemSizeY;
		s32 ScrollSize;
		s32 MinScrollBtnSize;
	}Size;
	GI::Screen::Gfx::String *Caption;
	controls_color_struct_t Color;

	struct {
		struct {
			struct {
				Color::ARGB border;
				Color::ARGB back;
				Color::ARGB text;
			}selected;
			struct {
				Color::ARGB border;
				Color::ARGB back;
				Color::ARGB text;
			}unSelected;
		}disabled;
		struct {
			struct {
				Color::ARGB border;
				Color::ARGB back;
				Color::ARGB text;
			}selected;
			struct {
				Color::ARGB border;
				Color::ARGB back;
				Color::ARGB text;
			}unSelected;
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
			s32 ItemSizeY;
			s32 ScrollSize;
			s32 MinScrollBtnSize;
		}Size;
		bool OldStateVisible;
		bool OldStateEnabled;
		bool NeedEntireRefresh;
		bool NeedEntireRepaint;
		bool CursorDownInsideBox;
		bool IsChildren;
		bool NoPaintBackGround;
		u32 ItemStartOnBox;
		u32 OldItemStartOnBox;
		CursorState OldStateCursor;
		GI::Display::Display *pDisplay;
		GI::Screen::Gfx::ScrollBar* ScrollBar;
		void *parentWindowHandler;
		bool parentWindowStateEnabled;
	}Internals;
	bool Visible;
	bool Enabled;
	bool AlwaisShowScrollbar;
	CursorState StateChangedOn;
	u32 ItemsCount;
	u32 SelectedItem;
	listboxItem **Items;

private:
	bool paint(listboxItem* settings, void *pDisplay, s32 x_start, s32 y_start, tControlCommandData* control_comand, bool Pushed, bool Paint);

};
}
}
}
//#######################################################################################
#ifdef USE_VISUAL_STUDIO
#include "listbox.cpp"
#endif
//#######################################################################################
#endif /* LISTBOX_H_ */
