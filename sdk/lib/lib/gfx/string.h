/*
 * lib/gfx/string.h
 */

#ifndef LIB_LIB_GFX_STRING_H_
#define LIB_LIB_GFX_STRING_H_

#if __AVR_XMEGA__
#include <avr/pgmspace.h>
#endif
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <api/lcd_def.h>
#include "resource/fonts.h"
#include <lib/string.h>
#include "gfxdef.h"

#define FONT_FMT_UNCOMPRESSED   0x00
#define ABSENT_CHAR_REPLACEMENT '.'

/*#####################################################*/
#define RGB_TO_UINT(R,G,B) ((R)<<16) | ((G)<<8) | ((B))

/*#####################################################*/

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
namespace Screen {
namespace Gfx {
	class String
	{
	public:
		String(GI::Display::Display *pDisplay);
		String(GI::Display::Display *pDisplay, char *String);
		~String();
		bool equal(GI::Screen::Gfx::String *string);
		bool equal(char *string);
		void toUper();
		void toLower();
		void removeNewLine(GI::Screen::Gfx::String *string);
		void setText(char* string);
		void setText(GI::Screen::Gfx::String *string);
		void setText(GI::string *string);
		void setTextF(const char *pcString, ...);
		void setTextF(GI::string *string, ...);
		void setTextF(GI::Screen::Gfx::String *string, ...);
		void append(char* string);
		void append(GI::Screen::Gfx::String *string);
		void append(GI::string *string);
		void append(char Char);
		void appendF(const char *pcString, ...);
		void appendF(GI::string *string, ...);
		void appendF(GI::Screen::Gfx::String *string, ...);
		void insert(GI::string* string, u32 location);
		void insert(GI::Screen::Gfx::String* string, u32 location);
		void insert(char *string, u32 location);
		void clone(GI::Screen::Gfx::String* string);
		void clear();
		char *subString(u32 position, u32 len);

		//#######################################################################################
		u8 getFontHeight()
		{
			return read_data_byte(pFont->ucHeight);
		}
		void getStrSelect(s32 *Start, s32 *SelStartReturn, s32 *SelLenReturn, s32 _XPush, s32 _YPush, s32 _XPull, s32 _YPull, s32 lX, s32 lY, u32 *return_command);
		s32 getStrWidth();
		s32 getStrRowsNr();
		StringProperties_t getStrProp();
		s32 drawString();
		s32 drawStringTiny();
		s32 getStrPropTiny();



		char *buff;

		tRectangle Capsule;
		GI::Display::Display *pDisplay;
		tFont *pFont;
		s32 length;
		u32 foreground_color;
		u32 background_color;
		bool ulOpaque;
		bool ulVisible;
		bool wordWrap;
		s32 lX;
		s32 lY;
		s32 _SelStart;
		s32 _SelLen;
		allign textAlign;
		/*
		 * Private variables.
		 */
		u32 modifyed;
		int error;
		bool terminalMode;
		//bool initialized;
	};
}
}
}
/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "string.cpp"
#endif
/*#####################################################*/
#endif /* LIB_LIB_GFX_STRING_H_ */
