/*
 * newString.h
 *
 *  Created on: Jul 20, 2019
 *      Author: Work
 */

#ifndef LIB_LIB_GFX_NEWSTRING_H_
#define LIB_LIB_GFX_NEWSTRING_H_

#include "include/global.h"
#include <lib/gfx/newGfxStructs.h>
#include <api/lcd_def.h>

#define FONT_FMT_UNCOMPRESSED   0x00
#define ABSENT_CHAR_REPLACEMENT '.'

#if (__SIZEOF_INT__ == 4)
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
#endif

namespace GI {
namespace Gfx {
	class string
	{
	public:
		string();
		string(char *string);
		string(GI::Gfx::string *string, u32 position, u32 len);
		string(GI::string *string, u32 position, u32 len);
		string(char *string, u32 position, u32 len);
		~string();
		void idle();
		bool equal(GI::Gfx::string *string);
		bool equal(GI::string *string);
		bool equal(char *string);
		void toUper();
		void toLower();
		void removeNewLine(GI::Gfx::string *string);
		void setText(char* string);
		void setText(GI::Gfx::string *string);
		void setText(GI::string *string);
		void setText(const char *pcString, ...);
		void setText(GI::string *string, ...);
		void setText(GI::Gfx::string *string, ...);
		void append(char* string);
		void append(GI::Gfx::string *string);
		void append(GI::string *string);
		void append(char Char);
		void appendF(const char *pcString, ...);
		void appendF(GI::string *string, ...);
		void appendF(GI::Gfx::string *string, ...);
		void insert(GI::string* string, u32 location);
		void insert(GI::Gfx::string* string, u32 location);
		void insert(char *string, u32 location);
		void clone(GI::Gfx::string* string);
		void clear();
		void subString(GI::Gfx::string *string, u32 position, u32 len);
		void subString(GI::string *string, u32 position, u32 len);
		void subString(char *string, u32 position, u32 len);

		//#######################################################################################
		u8 getFontHeight()
		{
			return read_data_byte(pFont->ucHeight);
		}
		void getStrSelect(s32 *Start, s32 *SelStartReturn, s32 *SelLenReturn, s32 _XPush, s32 _YPush, s32 _XPull, s32 _YPull, s32 lX, s32 lY, u32 *return_command);
		u32 getStrWidth();
		u32 getStrRowsNr();
		StringProperties_t getStrProp();
		s32 drawString();
		s32 drawStringTiny();
		s32 getStrPropTiny();



		char *buff;

		tRectangle window;
		GI::Display::Display *pDisplay;
		tFont *pFont;
		s32 length;
		Color::ARGB foreColor;
		Color::ARGB backColor;
		bool opaque;
		bool visible;
		bool wordWrap;
		s32 x;
		s32 y;
		s32 selStart;
		s32 selLen;
		GI::textAllign textAlign;
		bool isModifyed;
		int error;
		bool terminalMode;
	};
}
}


#endif /* LIB_LIB_GFX_NEWSTRING_H_ */
