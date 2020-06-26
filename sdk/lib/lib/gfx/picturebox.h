/*
 *  lib/gfx/picturebox.cpp
 */
#ifndef PICTUREBOX_H_
#define PICTUREBOX_H_
//#######################################################################################
#include <stdbool.h>
#include "3d.h"
#include "controls_definition.h"
#include "string.h"
#include "api/timer.h"
#include "gfxdef.h"
//#include "window_def.h"
//#######################################################################################
namespace GI
{
namespace Screen
{
namespace Gfx
{
class Picturebox {
public:
    Picturebox(void *parentWindowHandler);
    Picturebox(GI::Display::Display *ScreenDisplay);
	~Picturebox();
	void idle(tControlCommandData* control_comand);
	void idle();
	void clear();
	void copyRectangle(u32 *src_buff, u32 src_buff_data_offset, tRectangle *_dest_rectangle, tRectangle *_src_rectangle, s32 src_width, s32 src_height);
	void drawPixel(s32 X, s32 Y, u32 color);
	void drawHLine(s32 X1, s32 X2, s32 Y, u8 width, u32 color);
	void drawVLine(s32 Y1, s32 Y2, s32 X, u8 width, u32 color);
	void drawCircle(s32 x, s32 y, s32 radius, u8 fill, u32 color);
	void drawLine(s32 X1, s32 Y1, s32 X2, s32 Y2, u8 width, u32 color);
	void drawElipse(s32 xc,s32 yc,s32 rx,s32 ry, u8 fill, u32 color);
	void drawTriangle(s32  Ax,s32  Ay,s32  Bx,s32  By,s32  Cx,s32  Cy, u8 fill, u32 color);
	void drawString(GI::Screen::Gfx::String *string);
	void draw3dTriangle(_3d_points *Points, s32 X_offset, s32 Y_offset, double X_Angle, double Y_Angle, double Z_Angle, u32 Color);
	void draw3dCube(_3d_points *Points, s32 X_offset, s32 Y_offset, double X_Angle, double Y_Angle, double Z_Angle, u32 Color);


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
			void* CallbackReturnData;
			void*(*CallBack)(GI::Screen::Gfx::Picturebox *, tControlCommandData *);
		}OnMove;
		struct
		{
			void* CallbackReturnData;
			void*(*CallBack)(GI::Screen::Gfx::Picturebox *, tControlCommandData *);
		}OnUp;
		struct
		{
			void* CallbackReturnData;
			void*(*CallBack)(GI::Screen::Gfx::Picturebox *, tControlCommandData *);
		}OnDown;
		struct
		{
			void* CallbackReturnData;
			void*(*CallBack)(GI::Screen::Gfx::Picturebox *, tControlCommandData *);
		}Refresh;
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
		//CursorState OldStateCursor;
		GI::Sys::Timer ContinuouslyPushTimer;
		GI::Display::Display *pDisplay;
		tRectangle PictureWindowLimits;
		void *parentWindowHandler;
		bool parentWindowStateEnabled;
	}Internals;
	bool PaintBackground;
	u32 BackgroundColor;
	bool Visible;
	bool Enabled;

private:
	void paint(void *pDisplay, s32 x_start, s32 y_start, s32 x_len, s32 y_len, tControlCommandData* control_comand);

};
}
}
}
#if _USE_BITMAP_LIBRARY == 1
bool picturebox_put_bitmap(tPictureBox* settings, u8 *file, s32 X, s32 Y, bool use_transparency, bool scale);
bool picturebox_put_fbitmap(tPictureBox* settings, char *path, s32 X, s32 Y, bool use_transparency, bool scale);
#endif
//#######################################################################################
#ifdef USE_VISUAL_STUDIO
#include "picturebox.cpp"
#endif
//#######################################################################################
#endif /* BUTON_H_ */
