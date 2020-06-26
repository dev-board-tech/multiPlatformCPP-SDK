/*
 *  lib/gfx/controls_definition.h
 */

#ifndef CONTROLS_DEFINITION_H_
#define CONTROLS_DEFINITION_H_
/*#####################################################*/
#ifdef __AVR_XMEGA__
#include <avr/pgmspace.h>
#endif
#include <stdbool.h>
#include <string.h>
#include "sys/cache.h"
#include "api/lcd_def.h"
#include <api/timer.h>
#include "gfxdef.h"
/*#####################################################*/
#define FONT_FMT_UNCOMPRESSED   0x00
#define ABSENT_CHAR_REPLACEMENT '.'
/*#####################################################*/
/*#if (__SIZEOF_INT__ == 4)
//#if 4 == sizeof(u32)
#define ReturnCommand_gp  (unsigned)(29)
#define ReturnCommand_gm  (unsigned)(0x07 << ReturnCommand_gp)
#define ReturnCommand_NoCommand  (unsigned)(0x00<<ReturnCommand_gp)
#define ReturnCommand_GoUp  (unsigned)(0x01<<ReturnCommand_gp)
#define ReturnCommand_GoDn  (unsigned)(0x02<<ReturnCommand_gp)
#define ReturnCommand_GoLeft  (unsigned)(0x03<<ReturnCommand_gp)
#define ReturnCommand_GoRight  (unsigned)(0x04<<ReturnCommand_gp)
#define ReturnCommand_MaxValue  (unsigned)(0x08)
#else
#define ReturnCommand_gp  (unsigned)(13)
#define ReturnCommand_gm  (unsigned)(0x07 << ReturnCommand_gp)
#define ReturnCommand_NoCommand  (unsigned)(0x00<<ReturnCommand_gp)
#define ReturnCommand_GoUp  (unsigned)(0x01<<ReturnCommand_gp)
#define ReturnCommand_GoDn  (unsigned)(0x02<<ReturnCommand_gp)
#define ReturnCommand_GoLeft  (unsigned)(0x03<<ReturnCommand_gp)
#define ReturnCommand_GoRight  (unsigned)(0x04<<ReturnCommand_gp)
#define ReturnCommand_MaxValue  (unsigned)(0x08)
#endif*/
/*#####################################################*/
#define BORDER_LINE_ONE_LIGHT		2
#define BORDER_LINE_TWO_LIGHT		1.5
#define BORDER_LINE_ONE_DARK		3
#define BORDER_LINE_TWO_DARK		2
/*#####################################################*/
typedef u32 colors;

typedef struct
{
	u32 Control_Color_Enabled_Ink_Pull;
	u32 Control_Color_Enabled_Ink_Push;
	u32 Control_Color_Enabled_Buton_Pull;
	u32 Control_Color_Enabled_Buton_Push;
	u32 Control_Color_Enabled_Border_Pull;
	u32 Control_Color_Enabled_Border_Push;
	u32 Control_Color_Enabled_BackGround;
	u32 Control_Color_Enabled_TextBackGround;
	u32 Control_Color_Enabled_WindowBorder;
	u32 Control_Color_Enabled_WindowHeader;

	u32 Control_Color_Disabled_Ink_Pull;
	//u32 Control_Color_Disabled_Ink_Push;
	u32 Control_Color_Disabled_Buton_Pull;
	//u32 Control_Color_Disabled_Buton_Push;
	u32 Control_Color_Disabled_Border_Pull;
	//u32 Control_Color_Disabled_Border_Push;
	u32 Control_Color_Disabled_BackGround;
	u32 Control_Color_Disabled_WindowBorder;
	u32 Control_Color_Disabled_WindowHeader;
	u32 Scren;
	tFont* DefaultFont;
}controlscolor;
/*#####################################################*/
typedef enum
{
	Control_Nop,
	Control_Refresh,
	Control_Entire_Refresh,
	Control_Entire_Repaint,
}ControlCommands;
/*#####################################################*/
typedef enum
{
	Cursor_NoAction = 0,
	Cursor_Up = 1,
	Cursor_Down = 2,
	Cursor_Move = 3,
	mouseNop = 0,
	mouseRelease = 1,
	mousePress = 2,
	mouseMove = 3,
}CursorState;
/*#####################################################*/
typedef struct
{
	s32 X;
	s32 Y;
	s32 xOnLeftMousPress;
	s32 yOnLeftMousPress;
	s32 xOffset;
	s32 yOffset;
	s32 X2;
	s32 Y2;
	s32 X3;
	s32 Y3;
	s32 X4;
	s32 Y4;
	s32 X5;
	s32 Y5;
	CursorState Cursor;
	CursorState Cursor2;
	CursorState Cursor3;
	CursorState Cursor4;
	CursorState Cursor5;
	u32 Data;
	void* Settings;
	bool CursorCoordonateUsed;
	bool WindowRefresh;
	ControlCommands Comand;
}tControlCommandData;
/*#####################################################*/
typedef struct
{
	struct
	{
		u32 Ink;
		u32 Buton;
		u32 Border;
		u32 BackGround;
		double ScalerOnDisabled;
	}Disabled;
	struct
	{
		struct
		{
			u32 Push;
			u32 Pull;
		}Ink;
		struct
		{
			u32 Push;
			u32 Pull;
		}Buton;
		struct
		{
			u32 Push;
			u32 Pull;
		}Border;
		u32 TextBackGround;
		u32 BackGround;
		double ScalerOnDisabled;
	}Enabled;
	u32 Scren;
}controls_color_struct_t;
/*#####################################################*/
/*typedef struct
{
	Align TextAlign;
	String_t *Text;
	bool WordWrap;
	tFont* Font;
}controls_caption_t;*/
/*#####################################################*/
/*#####################################################*/
/*#####################################################*/
/*#####################################################*/
extern controlscolor controls_color;
/*#####################################################*/
typedef struct
{
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
	struct
	{
		u32 Background;
		u32 Scren;
	}Color;
	bool Visible;
	bool Enabled;
	struct
	{
		u32 ItemsNumber;
		void** List;
	}Children;
	struct
	{
		struct
		{
			bool Initiated;
		}Control;
	}Internals;
}tPanel;
/*#####################################################*/
u32 controlls_change_color(u32 color, double value);
bool screen_copy(void *pDisplayTo, void *pDisplayFrom, bool put_cursor, s32 X, s32 Y, u32 color);
void TouchPaintPoint(void *pDisplay, s32 X, s32 Y, u32 color);
void put_circle(void *pDisplay, s32 x, s32 y, s32 _radius, u8 fill, u32 color);
void put_line(void *pDisplay, s32 X1, s32 Y1, s32 X2, s32 Y2, u8 width, u32 color);
void put_elipse(void *pDisplay, s32 xc,s32 yc,s32 _rx,s32 _ry, u8 Fill, u32 color);
void put_triangle(void *pDisplay, s32  Ax,s32  Ay,s32  Bx,s32  By,s32  Cx,s32  Cy, u8 Fill, u32 color);


/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "controls_definition.cpp"
#endif
/*#####################################################*/
#endif /* CONTROLS_DEFINITION_H_ */
/*#####################################################*/
