/*
 * lib/gfx/string.cpp
 */

#include <stdio.h>
#include "string.h"

/*#####################################################*/
#ifdef __AVR_XMEGA__
const u8 CharTable6x8[] PROGMEM =
#else
extern const u8 CharTable6x8[] =
#endif
{
	6                          ,0          ,6          ,8          ,32            ,128,
	/*  OffsetOfBeginingCharTable  ,0=Y-X|1=X-X,X-Dimension,Y-Dimension,BeginAsciiChar,EndAsciiChar*/
	0x00,0x00,0x00,0x00,0x00,0x00,
	0x5F,0x00,0x00,0x00,0x00,0x00,//   !		32,33
	0x07,0x00,0x07,0x00,0x00,0x00,
	0x14,0x7F,0x14,0x7F,0x14,0x00,// " #		34,35
	0x24,0x2A,0x7F,0x2A,0x12,0x00,
	0x23,0x13,0x08,0x64,0x62,0x00,// 0x %		36,37
	0x36,0x49,0x55,0x22,0x50,0x00,
	0x05,0x03,0x00,0x00,0x00,0x00,// & '		38,39
	0x1C,0x22,0x41,0x00,0x00,0x00,
	0x41,0x22,0x1C,0x00,0x00,0x00,// ( )		40,41
	0x08,0x2A,0x1C,0x2A,0x08,0x00,
	0x08,0x08,0x3E,0x08,0x08,0x00,// * +		42,43
	0x50,0x30,0x00,0x00,0x00,0x00,
	0x08,0x08,0x08,0x00,0x00,0x00,// , -		44,45
	0x30,0x30,0x00,0x00,0x00,0x00,
	0x20,0x10,0x08,0x04,0x02,0x00,// . /		46,47
	0x3E,0x51,0x49,0x45,0x3E,0x00,
	0x42,0x7F,0x40,0x00,0x00,0x00,// 0 1		48,49
	0x42,0x61,0x51,0x49,0x46,0x00,
	0x21,0x41,0x45,0x4B,0x31,0x00,// 2 3		50,51
	0x18,0x14,0x12,0x7F,0x10,0x00,
	0x27,0x45,0x45,0x45,0x39,0x00,// 4 5		52,53
	0x3C,0x4A,0x49,0x49,0x30,0x00,
	0x01,0x71,0x09,0x05,0x03,0x00,// 6 7		54,55
	0x36,0x49,0x49,0x49,0x36,0x00,
	0x06,0x49,0x49,0x29,0x1E,0x00,// 8 9		56,57
	0x36,0x00,0x00,0x00,0x00,0x00,
	0x56,0x36,0x00,0x00,0x00,0x00,// : ;		58,59
	0x08,0x14,0x22,0x41,0x00,0x00,
	0x14,0x14,0x14,0x00,0x00,0x00,// < =		60,61
	0x41,0x22,0x14,0x08,0x00,0x00,
	0x02,0x01,0x51,0x09,0x06,0x00,// > ?		62,63
	0x32,0x49,0x79,0x41,0x3E,0x00,
	0x7E,0x11,0x11,0x7E,0x00,0x00,// @ A		64,65
	0x7F,0x49,0x49,0x36,0x00,0x00,
	0x3E,0x41,0x41,0x22,0x00,0x00,// B C		66,67
	0x7F,0x41,0x22,0x1C,0x00,0x00,
	0x7F,0x49,0x49,0x41,0x00,0x00,// D E		68,69
	0x7F,0x09,0x09,0x01,0x00,0x00,
	0x3E,0x41,0x51,0x32,0x00,0x00,// F G		70,71
	0x7F,0x08,0x08,0x7F,0x00,0x00,
	0x41,0x7F,0x41,0x00,0x00,0x00,// H I		72,73
	0x20,0x40,0x41,0x3F,0x01,0x00,
	0x7F,0x08,0x14,0x22,0x41,0x00,// J K		74,75
	0x7F,0x40,0x40,0x00,0x00,0x00,
	0x7F,0x02,0x04,0x02,0x7F,0x00,// L M		76,77
	0x7F,0x04,0x08,0x10,0x7F,0x00,
	0x3E,0x41,0x41,0x3E,0x00,0x00,// N O		78,79
	0x7F,0x09,0x09,0x06,0x00,0x00,
	0x3E,0x41,0x51,0x21,0x5E,0x00,// P Q		80,81
	0x7F,0x19,0x29,0x46,0x00,0x00,
	0x46,0x49,0x49,0x31,0x00,0x00,// R S		82,83
	0x01,0x7F,0x01,0x00,0x00,0x00,
	0x3F,0x40,0x40,0x3F,0x00,0x00,// T U		84,85
	0x1F,0x20,0x40,0x20,0x1F,0x00,
	0x7F,0x20,0x18,0x20,0x7F,0x00,// V W		86,87
	0x63,0x14,0x08,0x14,0x63,0x00,
	0x03,0x04,0x78,0x04,0x03,0x00,// X Y		88,89
	0x61,0x51,0x49,0x45,0x43,0x00,
	0x7F,0x41,0x41,0x00,0x00,0x00,// Z [		90,91
	0x02,0x04,0x08,0x10,0x20,0x00,
	0x41,0x41,0x7F,0x00,0x00,0x00,// \ ]		92,93
	0x04,0x02,0x01,0x02,0x04,0x00,
	0x40,0x40,0x40,0x00,0x00,0x00,// ^ _		94,95
	0x01,0x02,0x04,0x00,0x00,0x00,
	0x20,0x54,0x54,0x78,0x00,0x00,// ` a		96,97
	0x7F,0x48,0x44,0x38,0x00,0x00,
	0x38,0x44,0x44,0x00,0x00,0x00,// b c		98,99
	0x38,0x44,0x48,0x7F,0x00,0x00,
	0x38,0x54,0x54,0x18,0x00,0x00,// d e		100,101
	0x08,0x7E,0x09,0x01,0x00,0x00,
	0x08,0x14,0x54,0x3C,0x00,0x00,// f g		102,103
	0x7F,0x08,0x04,0x78,0x00,0x00,
	0x44,0x7D,0x40,0x00,0x00,0x00,// h i		104,105
	0x20,0x40,0x44,0x3D,0x00,0x00,
	0x7F,0x10,0x28,0x44,0x00,0x00,// j k		106,107
	0x41,0x7F,0x40,0x00,0x00,0x00,
	0x7C,0x04,0x18,0x04,0x78,0x00,// l m		108,109
	0x7C,0x08,0x04,0x78,0x00,0x00,
	0x38,0x44,0x44,0x38,0x00,0x00,// n o		110,111
	0x7C,0x14,0x14,0x08,0x00,0x00,
	0x08,0x14,0x18,0x7C,0x00,0x00,// p q		112,113
	0x7C,0x08,0x04,0x08,0x00,0x00,
	0x48,0x54,0x54,0x20,0x00,0x00,// r s		114,115
	0x04,0x3F,0x44,0x40,0x00,0x00,
	0x3C,0x40,0x20,0x7C,0x00,0x00,// t u		116,117
	0x1C,0x20,0x40,0x20,0x1C,0x00,
	0x3C,0x40,0x30,0x40,0x3C,0x00,// v w		118,119
	0x44,0x28,0x10,0x28,0x44,0x00,
	0x0C,0x50,0x50,0x3C,0x00,0x00,// x y		120,121
	0x44,0x64,0x54,0x4C,0x44,0x00,
	0x08,0x36,0x41,0x00,0x00,0x00,// z {		122,123
	0x7F,0x00,0x00,0x00,0x00,0x00,
	0x41,0x36,0x08,0x00,0x00,0x00,// | }		124,125
	0x08,0x2A,0x1C,0x08,0x00,0x00,
	0x08,0x1C,0x2A,0x08,0x00,0x00,// -> <-	126,127
	0x14,0x36,0x77,0x36,0x14,0x00 };//			128

GI::Screen::Gfx::String::String(GI::Display::Display *pDisplay) :
				buff(NULL), pFont((tFont*) &g_sFontCmss14b), length(0), foreground_color(0), background_color(
				0), ulOpaque(true), ulVisible(true), wordWrap(true), lX(0), lY(
				0), _SelStart(0), _SelLen(0), textAlign(alignLeft), modifyed(0), error(
				SYS_ERR_OK), terminalMode(false)
{
	this->Capsule.sXMin = 0;
	this->Capsule.sXMax = pDisplay->LcdTimings->X;
	this->Capsule.sYMin = 0;
	this->Capsule.sYMax = pDisplay->LcdTimings->Y;
	this->pDisplay = pDisplay;
	buff = (char *) malloc(1);
	if (buff)
	{
		error = SYS_ERR_OK;

	}
}

GI::Screen::Gfx::String::String(GI::Display::Display *pDisplay, char *String) :
		buff(NULL), pFont((tFont*) &g_sFontCmss14b), length(0), foreground_color(0), background_color(
				0), ulOpaque(true), ulVisible(true), wordWrap(true), lX(0), lY(
				0), _SelStart(0), _SelLen(0), textAlign(alignLeft), modifyed(0), error(
				SYS_ERR_OK), terminalMode(false)
{
	this->Capsule.sXMin = 0;
	this->Capsule.sXMax = pDisplay->LcdTimings->X;
	this->Capsule.sYMin = 0;
	this->Capsule.sYMax = pDisplay->LcdTimings->Y;
	this->pDisplay = pDisplay;
	u32 len = strlen(String);
	buff = (char *) malloc(len + 1);
	if (buff)
	{
		strcpy((char *) buff, (const char *) String);
		length = len;
		error = SYS_ERR_OK;
		modifyed++;
	}
}

GI::Screen::Gfx::String::~String()
{
	if(!this)
		return;
	if (buff)
		free((void *) buff);
}

bool GI::Screen::Gfx::String::equal(GI::Screen::Gfx::String *string)
{
	if(!this)
		return false;
	if(!string)
		return false;
	if(!buff)
		return false;
	  if((modifyed != string->modifyed) ||
		//(strcmp(buff, string.buff) == 0)   ? false :
		(pFont != string->pFont) ||
		(length != string->length) ||
		//(foreground_color != string->foreground_color) ||
		(ulOpaque != string->ulOpaque) ||
		(ulVisible != string->ulVisible) ||
		(wordWrap != string->wordWrap) ||
		(lX != string->lX) ||
		(lY != string->lY) ||
		(_SelStart != string->_SelStart) ||
		(_SelLen != string->_SelLen) ||
		(textAlign != string->textAlign) ||
		(pDisplay != string->pDisplay))
		  return false;
	  return true;
}

bool GI::Screen::Gfx::String::equal(char *string)
{
	if(!this)
		return false;
	if(!string)
		return false;
	if(strcmp(buff, string))
		return false;
	return true;
}

void GI::Screen::Gfx::String::toUper()
{
	if(!this)
		return;
	if(!buff)
		return;
	u32 TmpCnt = length;
	char* Str = buff;
	do{
		*Str = (char)toupper((int)*Str);
		Str++;
	}while(--TmpCnt);
	error = SYS_ERR_OK;
	modifyed++;
}

void GI::Screen::Gfx::String::toLower()
{
	if(!this)
		return;
	if(!buff)
		return;
	u32 TmpCnt = length;
	char* Str = buff;
	do{
		*Str = (char)tolower((int)*Str);
		Str++;
	}while(--TmpCnt);
	error = SYS_ERR_OK;
	modifyed++;
}

void GI::Screen::Gfx::String::removeNewLine(GI::Screen::Gfx::String *string)
{
	if(!this)
		return;
	if(!string)
		return;
	if(!buff)
		return;
	char *_item = buff;
	char *tmp_str1 = buff;
	char *tmp_str2 = buff;
	while (*_item != 0)
	{
		if (*_item == '\n' || *_item == '\r')
			_item++;
		else
			*tmp_str1++ = *_item++;
	}
	*tmp_str1 = 0;
	length = tmp_str1 - tmp_str2;
	buff = (char *) realloc(tmp_str2, (tmp_str1 - tmp_str2) + 1);
	error = SYS_ERR_OK;
	modifyed++;
}

void GI::Screen::Gfx::String::setText(char* string)
{
	if(!this)
		return;
	if(!string)
		return;
	if(!buff)
		return;
	u32 LenSrc = strlen(string);
	char *Return;
	Return = (char *) realloc(buff, LenSrc + 1);
	*Return = 0;
	if (!Return)
		return;
	strcat(Return, string);
	buff = Return;
	length = LenSrc;
	modifyed++;
	error = SYS_ERR_OK;
}

void GI::Screen::Gfx::String::setText(GI::Screen::Gfx::String *string)
{
	if(!this)
		return;
	if(!string)
		return;
	if(!buff)
		return;
	u32 LenSrc = string->length;
	char *Return;
	Return = (char *) realloc(buff, LenSrc + 1);
	*Return = 0;
	if (!Return)
		return;
	strcat(Return, string->buff);
	buff = Return;
	length = LenSrc;
	modifyed++;
	error = SYS_ERR_OK;
}

void GI::Screen::Gfx::String::setText(GI::string *string)
{
	if(!this)
		return;
	if(!string)
		return;
	if(!buff)
		return;
	u32 LenSrc = string->length;
	char *Return;
	Return = (char *) realloc(buff, LenSrc + 1);
	*Return = 0;
	if (!Return)
		return;
	strcat(Return, string->buff);
	buff = Return;
	length = LenSrc;
	modifyed++;
	error = SYS_ERR_OK;
}

void GI::Screen::Gfx::String::append(char* string)
{
	if(!this)
		return;
	if(!string)
		return;
	if(!buff)
		return;
	u32 LenSrc = strlen(string);
	u32 LenDest = length;
	char *Return = (char *)realloc(buff, LenDest + LenSrc + 1);
	//char *Return = (char *)realloc(dest, LenDest + LenSrc + 1);
	if(!Return)
		return;
	strcat(Return, string);
	buff = Return;
	length = LenDest + LenSrc;
	modifyed++;
	error = SYS_ERR_OK;
}

void GI::Screen::Gfx::String::append(GI::Screen::Gfx::String *string)
{
	if(!this)
		return;
	if(!string)
		return;
	if(!buff)
		return;
	u32 LenSrc = string->length;
	u32 LenDest = length;
	char *Return = (char *)realloc(buff, LenDest + LenSrc + 1);
	//char *Return = (char *)realloc(dest, LenDest + LenSrc + 1);
	if(!Return)
		return;
	strcat(Return, string->buff);
	buff = Return;
	length = LenDest + LenSrc;
	modifyed++;
	error = SYS_ERR_OK;
}

void GI::Screen::Gfx::String::append(GI::string *string)
{
	if(!this)
		return;
	if(!string)
		return;
	if(!buff)
		return;
	u32 LenSrc = string->length;
	u32 LenDest = length;
	char *Return = (char *)realloc(buff, LenDest + LenSrc + 1);
	//char *Return = (char *)realloc(dest, LenDest + LenSrc + 1);
	if(!Return)
		return;
	strcat(Return, string->buff);
	buff = Return;
	length = LenDest + LenSrc;
	modifyed++;
	error = SYS_ERR_OK;
}

void GI::Screen::Gfx::String::append(char Char)
{
	if(!this)
		return;
	if(!buff)
		return;
	u32 LenSrc = 1;
	u32 LenDest = length;
	char *Return = (char *) realloc(buff, LenDest + LenSrc + 1);
	//char *Return = (char *)realloc(dest, LenDest + LenSrc + 1);
	if (!Return)
		return;
	char buff_char[2];
	buff_char[0] = Char;
	buff_char[1] = '\0';
	strcat(Return, buff_char);
	buff = Return;
	length = LenDest + LenSrc;
	modifyed = true;
	error = SYS_ERR_OK;
}

void GI::Screen::Gfx::String::insert(GI::Screen::Gfx::String* string, u32 location)
{
	if(!this)
		return;
	if(!string)
		return;
	if(!buff)
		return;
	u32 LenSrc = string->length;
	if(location > LenSrc)
		return;
	if(!buff)
	{
		return;
	}

	char *Return = (char *)realloc(buff, length + LenSrc + 1);
	if(!Return)
		return;
	u32 LenDest = length + location;
	char *Tmp = (char *)malloc((length - location) +1);
	if(!Tmp)
		return;
	strcpy(Tmp, buff + location);
	strcpy(Return + location, string->buff);
	strcat(Return, Tmp);
	free(Tmp);
	buff = Return;
	length = LenDest + LenSrc;
	error = SYS_ERR_OK;
	modifyed++;
}

void GI::Screen::Gfx::String::insert(GI::string* string, u32 location)
{
	if(!this)
		return;
	if(!string)
		return;
	if(!buff)
		return;
	u32 LenSrc = string->length;
	if(location > LenSrc)
		return;
	if(!buff)
	{
		return;
	}

	char *Return = (char *)realloc(buff, length + LenSrc + 1);
	if(!Return)
		return;
	u32 LenDest = length + location;
	char *Tmp = (char *)malloc((length - location) +1);
	if(!Tmp)
		return;
	strcpy(Tmp, buff + location);
	strcpy(Return + location, string->buff);
	strcat(Return, Tmp);
	free(Tmp);
	buff = Return;
	length = LenDest + LenSrc;
	error = SYS_ERR_OK;
	modifyed++;
}

void GI::Screen::Gfx::String::insert(char *string, u32 location)
{
	if(!this)
		return;
	if(!string)
		return;
	if(!buff)
		return;
	u32 LenSrc = strlen(string);
	if(location > LenSrc)
		return;

	char *Return = (char *)realloc(buff, length + LenSrc + 1);
	if(!Return)
		return;
	u32 LenDest = length + location;
	char *Tmp = (char *)malloc((length - location) +1);
	if(!Tmp)
		return;
	strcpy(Tmp, buff + location);
	strcpy(Return + location, string);
	strcat(Return, Tmp);
	free(Tmp);
	buff = Return;
	length = LenDest + LenSrc;
	error = SYS_ERR_OK;
	modifyed++;
}

void GI::Screen::Gfx::String::clone(GI::Screen::Gfx::String* string)
{
	if(!this)
		return;
	if (!string)
		return;
	if(!buff)
		return;
	u32 LenSrc = string->length;
	char *Return = (char *) realloc(string->buff, LenSrc + 1);
	//char *Return = (char *)realloc(dest, LenDest + LenSrc + 1);
	if (!Return)
		return;
	strcpy(Return, string->buff);
	buff = Return;
	error = SYS_ERR_OK;
    modifyed = string->modifyed;
	pFont = string->pFont;
    length = string->length;
    foreground_color = string->foreground_color;
    ulOpaque = string->ulOpaque;
	ulVisible = string->ulVisible;
	wordWrap = string->wordWrap;
	lX = string->lX;
	lY = string->lY;
	_SelStart = string->_SelStart;
	_SelLen = string->_SelLen;
	textAlign = string->textAlign;
	pDisplay = string->pDisplay;
}

void GI::Screen::Gfx::String::clear()
{
	if(!this)
		return;
	if(!buff)
		return;
	char *Return = (char *) realloc(buff, 1);
	*Return = 0;
	length = 0;
	buff = Return;
	error = SYS_ERR_OK;
	modifyed++;
}

char *GI::Screen::Gfx::String::subString(u32 position, u32 len)
{
	if(!this)
		return NULL;
	if(!buff)
		return NULL;
	if (position + len >= (u32) length)
		return NULL;
	char *Return = (char *) calloc(1, len + 1);
	if (!Return)
		return NULL;
	*Return = 0;
	strncpy(Return, buff + position, len);
	return Return;
}

void GI::Screen::Gfx::String::getStrSelect(
		s32 *Start, s32 *SelStartReturn,
		s32 *SelLenReturn, s32 _XPush, s32 _YPush,
		s32 _XPull, s32 _YPull, s32 lX, s32 lY,
		u32 *return_command)
{
	if(!this)
		return;
	GI::Display::Display* LcdStruct = (GI::Display::Display *) pDisplay;
	char *pcString = buff;
	s32 lLength = -1;
	if (LcdStruct->sClipRegion.sXMin > _XPull)
	{
		*return_command = ReturnCommand_GoLeft;
		u32 tmp = LcdStruct->sClipRegion.sXMin - _XPull;
		if (tmp > ReturnCommand_MaxValue)
			tmp = ReturnCommand_MaxValue;
		*return_command |= tmp;
	}
	if (LcdStruct->sClipRegion.sXMax < _XPull)
	{
		*return_command = ReturnCommand_GoRight;
		u32 tmp = _XPull - LcdStruct->sClipRegion.sXMax;
		if (tmp > ReturnCommand_MaxValue)
			tmp = ReturnCommand_MaxValue;
		*return_command |= tmp;
	}
	if (LcdStruct->sClipRegion.sYMin > _YPull)
	{
		*return_command = ReturnCommand_GoUp;
		u32 tmp = LcdStruct->sClipRegion.sYMin - _YPull;
		if (tmp > ReturnCommand_MaxValue)
			tmp = ReturnCommand_MaxValue;
		*return_command |= tmp;
	}
	if (LcdStruct->sClipRegion.sYMax < _YPull)
	{
		*return_command = ReturnCommand_GoDn;
		u32 tmp = _YPull - LcdStruct->sClipRegion.sYMax;
		if (tmp > ReturnCommand_MaxValue)
			tmp = ReturnCommand_MaxValue;
		*return_command |= tmp;
	}
	if (*return_command)
		return;

	s32 StringColsHeight_Pixels = lY;
	//s32 CharHeight_Pixels = 0;

	const u16 *pusOffset;
	const u8 *pucData;
	//s32 lRows;
	volatile s32 StringLengthOfEveryRow = lX;

	//
	// Get some pointers to relevant information in the font to make things
	// easier, and give the compiler a hint about extraneous loads that it can
	// avoid.
	//
#ifdef __AVR_XMEGA__
	pusOffset = (const u16 *)pFont + 2;
	pucData = (const u8 *)&pFont->pucData + 2;
#else
	pusOffset = pFont->pusOffset;
	pucData = pFont->pucData;
#endif

	s32 XPush = _XPush;
	s32 YPush = _YPush;
	s32 XPull = _XPull;
	s32 YPull = _YPull;

	/*if(XPush > XPull)
	 {
	 s32 Tmp = XPull;
	 XPull = XPush;
	 XPush = Tmp;
	 }
	 if(YPush > YPull)
	 {
	 s32 Tmp = YPull;
	 YPull = YPush;
	 YPush = Tmp;
	 }*/

	s32 CharCount = 0;

	bool StartSelected = false;
	bool LenSelected = false;

	//
	// Loop through the characters in the string.
	//
	for (; *pcString && lLength; pcString++, lLength--)
	{
		if (*Start
				< 0&& XPush < StringLengthOfEveryRow + (read_data_byte(pucData[read_data_word(pusOffset[*pcString - ' ']) + 1]) >> 1) && YPush < StringColsHeight_Pixels + read_data_byte(pFont->ucHeight) && StartSelected == false)
		{
			*SelStartReturn = CharCount;
			*Start = CharCount;
			StartSelected = true;
		}
		if (*Start
				>= 0&& XPull < StringLengthOfEveryRow + (read_data_byte(pucData[read_data_word(pusOffset[*pcString - ' ']) + 1]) >> 1) && YPull < StringColsHeight_Pixels + read_data_byte(pFont->ucHeight) && LenSelected == false)
		{
			*SelLenReturn = CharCount - *SelStartReturn;
			LenSelected = true;
			return;
		}

		CharCount += 1;
		//
		// Get a pointer to the font data for the next character from the
		// string.  If there is not a glyph for the next character, replace it
		// with a ".".
		//
		if (((StringLengthOfEveryRow - LcdStruct->sClipRegion.sXMin) + read_data_byte(pucData[read_data_word(pusOffset[*pcString - ' '] ) + 1])
				>= (LcdStruct->sClipRegion.sXMax - LcdStruct->sClipRegion.sXMin) && wordWrap == true))
		{
			//pucData = 0;

			StringLengthOfEveryRow = lX;
			StringColsHeight_Pixels += read_data_byte(pFont->ucHeight);
		}
		if (*pcString == '\r')
		{
			//pucData = 0;

			StringLengthOfEveryRow = lX;
			StringColsHeight_Pixels += read_data_byte(pFont->ucHeight);
		}
		else if (*pcString == '\n')
		{
			//pucData = 0;
			StringLengthOfEveryRow += read_data_byte(pucData[read_data_word(pusOffset[ABSENT_CHAR_REPLACEMENT - ' ']) + 1]);
		}
		else
		{
			if ((*pcString >= ' ') && (*pcString) <= '~')
			{
				//
				// Add the width of this character as drawn with the given font.
				//
				StringLengthOfEveryRow += read_data_byte(pucData[read_data_word(pusOffset[*pcString - ' '] ) + 1]);
			}
			else
			{
				//
				// This character does not exist in the font so replace it with
				// a '.' instead.  This matches the approach taken in Grput_string
				// and ensures that the width returned here represents the
				// rendered dimension of the string.
				//
				StringLengthOfEveryRow += read_data_byte(pucData[read_data_word(pusOffset[ABSENT_CHAR_REPLACEMENT - ' ']) + 1]);
			}
		}
	}

	if (*Start >= 0&& *pcString == 0 && YPull < StringColsHeight_Pixels + read_data_byte(pFont->ucHeight) && LenSelected == false)
	{
		*SelLenReturn = CharCount - *SelStartReturn;
		LenSelected = true;
	}

}

s32 GI::Screen::Gfx::String::getStrWidth()
{
	if(!this)
		return 0;
	//tDisplay* LcdStruct = (tDisplay *) pDisplay;
	char *pcString = buff;
	const u16 *pusOffset;
	const u8 *pucData;
	s32 lWidth;
	int lLength = -1;

	//
	// Check the arguments.
	//
	if (!pFont)
		return 0;
	if (!pcString)
		return 0;

	//
	// Get some pointers to relevant information in the font to make things
	// easier, and give the compiler a hint about extraneous loads that it can
	// avoid.
	//
#ifdef __AVR_XMEGA__
	pusOffset = (const u16 *)pFont + 2;
	pucData = (const u8 *)&pFont->pucData + 2;
#else
	pusOffset = pFont->pusOffset;
	pucData = pFont->pucData;
#endif

	//
	// Loop through the characters in the string.
	//
	for (lWidth = 0; *pcString && lLength; pcString++, lLength--)
	{
		//
		// Get a pointer to the font data for the next character from the
		// string.  If there is not a glyph for the next character, replace it
		// with a ".".
		//
		if (*pcString == '\n')
		{
			//pucData = 0;
			lWidth += read_data_byte(pucData[read_data_word(pusOffset[ABSENT_CHAR_REPLACEMENT - ' ']) + 1]);
		}
		if ((*pcString >= ' ') && (*pcString <= '~'))
		{
			//
			// Add the width of this character as drawn with the given font.
			//
			lWidth += read_data_byte(pucData[read_data_word(pusOffset[*pcString - ' '] ) + 1]);
		}
		else
		{
			//
			// This character does not exist in the font so replace it with
			// a '.' instead.  This matches the approach taken in Grput_string
			// and ensures that the width returned here represents the
			// rendered dimension of the string.
			//
			lWidth += read_data_byte(pucData[read_data_word(pusOffset[ABSENT_CHAR_REPLACEMENT - ' ']) + 1]);
		}
	}

	//
	// Return the width of the string.
	//
	return (lWidth);
}

s32 GI::Screen::Gfx::String::getStrRowsNr()
{
	if(!this)
		return 0;
	char *pcString = buff;
	int lLength = -1;
	//const u16 *pusOffset;
	//const u8 *pucData;
	s32 lRows;

	//
	// Check the arguments.
	//
	if (!pcString)
		return 0;

	//
	// Get some pointers to relevant information in the font to make things
	// easier, and give the compiler a hint about extraneous loads that it can
	// avoid.
	//
	//
	// Loop through the characters in the string.
	//
	for (; *pcString && lLength; pcString++, lLength--)
	{
		//
		// Get a pointer to the font data for the next character from the
		// string.  If there is not a glyph for the next character, replace it
		// with a ".".
		//
		if (*pcString == '\r')
		{
			lRows++;
			//pcString++;
		}
	}
	//
	// Return the number of Rows of the string.
	//
	return (lRows);
}

StringProperties_t GI::Screen::Gfx::String::getStrProp()
{
	StringProperties_t StringReturnProperties;
	memset(&StringReturnProperties, 0, sizeof(StringReturnProperties));
	if(!this)
		return StringReturnProperties;
	s32 lLength = -1;
	char *pcString = buff;
	bool WordWrap = wordWrap;
	GI::Display::Display* LcdStruct = (GI::Display::Display *) pDisplay;

	volatile s32 FirstRowLength_Pixels = 0;
	volatile s32 FirstRowLength_Chars = 0;
	volatile s32 StringLengthWithSpecialChars_Chars = 0;
	volatile s32 StringLengthWithOutSpecialChars_Chars = 0;
	volatile s32 StringRowsMaxLength_Pixels = 0;
	//s32 StringColsHeight_Pixels = 0;
	volatile s32 StringColsHeight_Rows = 0;
	//s32 CharHeight_Pixels = 0;

	volatile u8 EndOfFirstRow = false;

	//u16 *pusOffset;
	//u8 *pucData;
	//s32 lRows;
	volatile s32 StringLengthOfEveryRow = 0;

	//
	// Check the arguments.
	//
	//if(pDisplay) return;

	//
	// Get some pointers to relevant information in the font to make things
	// easier, and give the compiler a hint about extraneous loads that it can
	// avoid.
	//
#ifdef __AVR_XMEGA__
	const u16 *pusOffset = (const u16 *)pFont + 2;
	const u8 *pucData = (const u8 *)&pFont->pucData + 2;
#else
	const u16 *pusOffset = pFont->pusOffset;
	const u8 *pucData = pFont->pucData;
#endif

	StringReturnProperties.FirstRowLength_Pixels = 0;
	StringReturnProperties.FirstRowLength_Chars = 0;
	//
	// Loop through the characters in the string.
	//
	for (; *pcString && lLength; pcString++, lLength--)
	{
		//
		// Get a pointer to the font data for the next character from the
		// string.  If there is not a glyph for the next character, replace it
		// with a ".".
		//
		if ((StringLengthOfEveryRow + read_data_byte(pucData[read_data_word(pusOffset[*pcString - ' '] ) + 1])
				>= (LcdStruct->sClipRegion.sXMax - LcdStruct->sClipRegion.sXMin) && WordWrap == true))
		{
			//pucData = 0;

			if (EndOfFirstRow == false)
			{
				StringReturnProperties.FirstRowLength_Pixels =
						FirstRowLength_Pixels;
				StringReturnProperties.FirstRowLength_Chars =
						FirstRowLength_Chars;
			}
			EndOfFirstRow = true;
			StringColsHeight_Rows++;
			//tringLengthWithOutSpecialChars_Chars--;
			//StringLengthWithSpecialChars_Chars++;
			if (StringLengthOfEveryRow > StringRowsMaxLength_Pixels)
			{
				StringRowsMaxLength_Pixels = StringLengthOfEveryRow;
			}
			StringLengthOfEveryRow = 0;
			//FirstRowLength_Chars--;
			//FirstRowLength_Pixels -= pucData[pusOffset[ABSENT_CHAR_REPLACEMENT - ' '] + 1];
		}
		if (*pcString == '\r')
		{
			//pucData = 0;

			if (EndOfFirstRow == false)
			{
				StringReturnProperties.FirstRowLength_Pixels =
						FirstRowLength_Pixels;
				StringReturnProperties.FirstRowLength_Chars =
						FirstRowLength_Chars;
			}
			EndOfFirstRow = true;
			StringColsHeight_Rows++;
			//StringLengthWithOutSpecialChars_Chars--;
			StringLengthWithSpecialChars_Chars++;
			if (StringLengthOfEveryRow > StringRowsMaxLength_Pixels)
			{
				StringRowsMaxLength_Pixels = StringLengthOfEveryRow;
			}
			StringLengthOfEveryRow = 0;
			//FirstRowLength_Chars--;
			//FirstRowLength_Pixels -= pucData[pusOffset[ABSENT_CHAR_REPLACEMENT - ' '] + 1];
		}
		else if (*pcString == '\n')
		{
			//pucData = 0;
			u8 CharLen = read_data_byte(pucData[read_data_word(pusOffset[ABSENT_CHAR_REPLACEMENT - ' ']) + 1]);
			FirstRowLength_Pixels += CharLen;
			StringLengthOfEveryRow += CharLen;
			FirstRowLength_Chars++;
			StringLengthWithOutSpecialChars_Chars++;
			StringLengthWithSpecialChars_Chars++;
		}
		else
		{
			if ((*pcString >= ' ') && (*pcString <= '~'))
			{
				//
				// Add the width of this character as drawn with the given font.
				//
				u8 CharLen = read_data_byte(pucData[read_data_word(pusOffset[*pcString - ' ']
												) + 1]);
				FirstRowLength_Pixels += CharLen;
				StringLengthOfEveryRow += CharLen;
				FirstRowLength_Chars++;
				StringLengthWithOutSpecialChars_Chars++;
				StringLengthWithSpecialChars_Chars++;
			}
			else
			{
				//
				// This character does not exist in the font so replace it with
				// a '.' instead.  This matches the approach taken in Grput_string
				// and ensures that the width returned here represents the
				// rendered dimension of the string.
				//
				u8 CharLen = read_data_byte(pucData[read_data_word(pusOffset[ABSENT_CHAR_REPLACEMENT - ' ']) + 1]);
				FirstRowLength_Pixels += CharLen;
				StringLengthOfEveryRow += CharLen;
				FirstRowLength_Chars++;
				StringLengthWithOutSpecialChars_Chars++;
				StringLengthWithSpecialChars_Chars++;
			}
		}
	}

	if (StringLengthWithSpecialChars_Chars)
		StringColsHeight_Rows++;

	if (StringLengthOfEveryRow > StringRowsMaxLength_Pixels)
		StringRowsMaxLength_Pixels = StringLengthOfEveryRow;
	StringReturnProperties.CharHeight_Pixels = read_data_byte(pFont->ucHeight);
	StringReturnProperties.StringColsHeight_Pixels = StringColsHeight_Rows * read_data_byte(pFont->ucHeight);
	StringReturnProperties.StringColsHeight_Rows = StringColsHeight_Rows;
	StringReturnProperties.StringLengthWithOutSpecialChars_Chars = StringLengthWithOutSpecialChars_Chars;
	StringReturnProperties.StringLengthWithSpecialChars_Chars = StringLengthWithSpecialChars_Chars;
	StringReturnProperties.StringRowsMaxLength_Pixels = StringRowsMaxLength_Pixels;
	//
	// Return the number of Rows of the string.
	//
	return (StringReturnProperties);
}

static u8 _NumLeadingZeros(u32 x)
{
	register u8 count = 0;    //sizeof(x)*8;

	while (x)
	{
		if (!(x & 0xFF000000))
		{
			count = count + 8;
			x = x << 8;
		}
		else
		{
			while (!(x & 0x80000000))
			{
				x = x << 1;
				count++;
			}
			break;
		}
	}

	return count;
}

s32 GI::Screen::Gfx::String::drawString()
{
	if(!this)
		return 0;
	GI::Display::Display* LcdStruct = (GI::Display::Display *) pDisplay;
	char *pcString = buff;
	bool WordWrap = wordWrap;
	int lLength = -1;

	s32 lIdx, lX0, lY0, lCount, lOff, lOn, lBit;
	s32 lXBackup = lX;
	const u16 *pusOffset;
	const u8 *pucData;

	bool _ulOpaque = ulOpaque;

	s32 SelStart = _SelStart;
	s32 SelLen = _SelLen;

	if (SelLen < 0)
	{
		SelStart -= 0 - SelLen;
		SelLen = 0 - SelLen;
	}

#ifdef __AVR_XMEGA__
	pusOffset = (const u16 *)pFont + 2;
	pucData = (const u8 *)&pFont->pucData + 2;
#else
	pusOffset = pFont->pusOffset;
	pucData = pFont->pucData;
#endif

	//
	// Check the arguments.
	//
	if (!pDisplay || !pFont || !pcString)
		return 0;

	s32 CharCount = 0;
	s32 ChCount = 0;

	//
	// Copy the drawing context into a local structure that can be modified.
	//
	//
	// Loop through the characters in the string.
	//
	while (*pcString && lLength--)
	{
		ChCount++;
		if (SelLen)
		{
			if (CharCount >= SelStart && CharCount < SelStart + SelLen)
				_ulOpaque = true;
			else
				_ulOpaque = false;
			CharCount++;
		}

		//
		// Stop drawing the string if the right edge of the clipping region has
		// been exceeded.
		//
		/*if(lX > sCon.sClipRegion.sXMax)
		 {
		 break;
		 }*/

		//
		// Get a pointer to the font data for the next character from the
		// string.  If there is not a glyph for the next character, replace it
		// with a ".".
		//
		if (*pcString == '\r')
		{
			lX = lXBackup;
			pucData = 0;
			pcString++;
		}
		else if (*pcString == '\n')
		{
			lY += read_data_byte(pFont->ucHeight);
			pucData = 0;
			pcString++;
		}
		else
		{
			if ((*pcString >= ' ') && (*pcString <= '~'))
			{
#ifdef __AVR_XMEGA__
				pucData = ((const u8 *)&pFont->pucData + 2 + read_data_word(pusOffset[*pcString++ - ' ']));
#else
				pucData = (pFont->pucData + read_data_word(pusOffset[*pcString++ - ' ']));
#endif
			}
			else
			{
#ifdef __AVR_XMEGA__
				pucData = ((const u8 *)&pFont->pucData + 2 + read_data_word(pusOffset[ABSENT_CHAR_REPLACEMENT - ' ']));
#else
				pucData = (pFont->pucData + read_data_word(pusOffset[ABSENT_CHAR_REPLACEMENT - ' ']));
#endif
				pcString++;
			}

			if (lX + read_data_byte(pucData[1]) >= LcdStruct->sClipRegion.sXMax&& WordWrap == true)
			{
				lX = lXBackup;
				lY += read_data_byte(pFont->ucHeight);
			}
			else
			//
			// See if the entire character is to the left of the clipping region.
			//
			if ((lX + read_data_byte(pucData[1])) < LcdStruct->sClipRegion.sXMin)
			{
				//
				// Increment the X coordinate by the width of the character.
				//
				lX += read_data_byte(pucData[1]);

				//
				// Go to the next character in the string.
				//
				continue;
			}

			//
			// Loop through the bytes in the encoded data for this glyph.
			//
			for (lIdx = 2, lX0 = 0, lBit = 0, lY0 = 0; lIdx < read_data_byte(pucData[0]);)
			{
				//
				// See if the bottom of the clipping region has been exceeded.
				//
				if ((lY + lY0) > LcdStruct->sClipRegion.sYMax)
				{
					//
					// Stop drawing this character.
					//
					break;
				}

				//
				// See if the font is uncompressed.
				//
				if (read_data_byte(pFont->ucFormat) == FONT_FMT_UNCOMPRESSED)
				{
					//
					// Count the number of off pixels from this position in the
					// glyph image.
					//
					for (lOff = 0; lIdx < read_data_byte(pucData[0]);)
					{
						//
						// Get the number of zero pixels at this position.
						//
						lCount = _NumLeadingZeros(read_data_byte(pucData[lIdx])<< (24 + lBit));

						//
						// If there were more than 8, then it is a "false" result
						// since it counted beyond the end of the current byte.
						// Therefore, simply limit it to the number of pixels
						// remaining in this byte.
						//
						if(lCount > 8)
						{
							lCount = 8 - lBit;
						}

						//
						// Increment the number of off pixels.
						//
						lOff += lCount;

						//
						// Increment the bit position within the byte.
						//
						lBit += lCount;

						//
						// See if the end of the byte has been reached.
						//
						if(lBit == 8)
						{
							//
							// Advance to the next byte and continue counting off
							// pixels.
							//
							lBit = 0;
							lIdx++;
						}
						else
						{
							//
							// Since the end of the byte was not reached, there
							// must be an on pixel.  Therefore, stop counting off
							// pixels.
							//
							break;
						}
					}

					//
					// Count the number of on pixels from this position in the
					// glyph image.
					//
					for(lOn = 0; lIdx < read_data_byte(pucData[0]); )
					{
						//
						// Get the number of one pixels at this location (by
						// inverting the data and counting the number of zeros).
						//
						lCount = _NumLeadingZeros(~(read_data_byte(pucData[lIdx]) << (24 + lBit)));

						//
						// If there were more than 8, then it is a "false" result
						// since it counted beyond the end of the current byte.
						// Therefore, simply limit it to the number of pixels
						// remaining in this byte.
						//
						if(lCount > 8)
						{
							lCount = 8 - lBit;
						}

						//
						// Increment the number of on pixels.
						//
						lOn += lCount;

						//
						// Increment the bit position within the byte.
						//
						lBit += lCount;

						//
						// See if the end of the byte has been reached.
						//
						if(lBit == 8)
						{
							//
							// Advance to the next byte and continue counting on
							// pixels.
							//
							lBit = 0;
							lIdx++;
						}
						else
						{
							//
							// Since the end of the byte was not reached, there
							// must be an off pixel.  Therefore, stop counting on
							// pixels.
							//
							break;
						}
					}
				}

				//
				// Otherwise, the font is compressed with a pixel RLE scheme.
				//
				else
				{
					//
					// See if this is a byte that encodes some on and off pixels.
					//
					if(read_data_byte(pucData[lIdx]))
					{
						//
						// Extract the number of off pixels.
						//
						lOff = (read_data_byte(pucData[lIdx]) >> 4) & 15;

						//
						// Extract the number of on pixels.
						//
						lOn = read_data_byte(pucData[lIdx]) & 15;

						//
						// Skip past this encoded byte.
						//
						lIdx++;
					}

					//
					// Otherwise, see if this is a repeated on pixel byte.
					//
					else if(read_data_byte(pucData[lIdx + 1]) & 0x80)
					{
						//
						// There are no off pixels in this encoding.
						//
						lOff = 0;

						//
						// Extract the number of on pixels.
						//
						lOn = (read_data_byte(pucData[lIdx + 1]) & 0x7f) * 8;

						//
						// Skip past these two encoded bytes.
						//
						lIdx += 2;
					}

					//
					// Otherwise, this is a repeated off pixel byte.
					//
					else
					{
						//
						// Extract the number of off pixels.
						//
						lOff = read_data_byte(pucData[lIdx + 1]) * 8;

						//
						// There are no on pixels in this encoding.
						//
						lOn = 0;

						//
						// Skip past these two encoded bytes.
						//
						lIdx += 2;
					}
				}

				//
				// Loop while there are any off pixels.
				//
				while (lOff)
				{
					//
					// See if the bottom of the clipping region has been exceeded.
					//
					if ((lY + lY0) > LcdStruct->sClipRegion.sYMax)
					{
						//
						// Ignore the remainder of the on pixels.
						//
						break;
					}

					//
					// See if there is more than one on pixel that will fit onto
					// the current row.
					//
					if ((lOff > 1) && ((lX0 + 1) < read_data_byte(pucData[1])))
					{
						//
						// Determine the number of on pixels that will fit on this
						// row.
						//
						lCount = (((lX0 + lOff) > read_data_byte(pucData[1])) ? read_data_byte(pucData[1])- lX0 : lOff);

						//
						// If this row is within the clipping region, draw a
						// horizontal line that corresponds to the sequence of on
						// pixels.
						//
						if(((lY + lY0) >= LcdStruct->sClipRegion.sYMin) && _ulOpaque)
						{
							if(ulVisible == true)
								LcdStruct->drawHLine(lX + lX0, lCount, lY + lY0, 1, background_color);
						}

						//
						// Decrement the count of on pixels by the number on this
						// row.
						//
						lOff -= lCount;

						//
						// Increment the X offset by the number of on pixels.
						//
						lX0 += lCount;
					}

					//
					// Otherwise, there is only a single on pixel that can be
					// drawn.
					//
					else
					{
						//
						// If this pixel is within the clipping region, then draw
						// it.
						//
						if(((lX + lX0) >= LcdStruct->sClipRegion.sXMin) &&
							((lX + lX0) <= LcdStruct->sClipRegion.sXMax) &&
							((lY + lY0) >= LcdStruct->sClipRegion.sYMin) && _ulOpaque == true)
						{
#if (__SIZEOF_INT__ == 2)
							if(ulVisible == true)
								LcdStruct->drawPixel(lX + lX0, lY + lY0, background_color);
#else
							if(ulVisible == true)
								LcdStruct->drawPixel(lX + lX0, lY + lY0, background_color<<8);
#endif
						}

						//
						// Decrement the count of on pixels.
						//
						lOff--;

						//
						// Increment the X offset.
						//
						lX0++;
					}

					//
					// See if the X offset has reached the right side of the
					// character glyph.
					//
					if (lX0 == read_data_byte(pucData[1]))
					{
						//
						// Increment the Y offset.
						//
						lY0++;

						//
						// Reset the X offset to the left side of the character
						// glyph.
						//
						lX0 = 0;
					}
				}

				//
				// Loop while there are any on pixels.
				//
				while (lOn)
				{
					//
					// See if the bottom of the clipping region has been exceeded.
					//
					if ((lY + lY0) > LcdStruct->sClipRegion.sYMax)
					{
						//
						// Ignore the remainder of the on pixels.
						//
						break;
					}

					//
					// See if there is more than one on pixel that will fit onto
					// the current row.
					//
					if ((lOn > 1) && ((lX0 + 1) < read_data_byte(pucData[1])))
					{
						//
						// Determine the number of on pixels that will fit on this
						// row.
						//
						lCount = (((lX0 + lOn) > read_data_byte(pucData[1])) ? read_data_byte(pucData[1])- lX0 : lOn);

						//
						// If this row is within the clipping region, draw a
						// horizontal line that corresponds to the sequence of on
						// pixels.
						//
						if((lY + lY0) >= LcdStruct->sClipRegion.sYMin)
						{
							if(ulVisible == true)
								LcdStruct->drawHLine(lX + lX0, lCount, lY + lY0, 1, foreground_color);
						}

						//
						// Decrement the count of on pixels by the number on this
						// row.
						//
						lOn -= lCount;

						//
						// Increment the X offset by the number of on pixels.
						//
						lX0 += lCount;
					}

					//
					// Otherwise, there is only a single on pixel that can be
					// drawn.
					//
					else
					{
						//
						// If this pixel is within the clipping region, then draw
						// it.
						//
						if(((lX + lX0) >= LcdStruct->sClipRegion.sXMin) &&
							((lX + lX0) <= LcdStruct->sClipRegion.sXMax) &&
							((lY + lY0) >= LcdStruct->sClipRegion.sYMin))
						{
#if (__SIZEOF_INT__ == 2)
							if(ulVisible == true)
								LcdStruct->drawPixel(lX + lX0, lY + lY0, foreground_color);
#else
							if(ulVisible == true)
								LcdStruct->drawPixel(lX + lX0, lY + lY0, foreground_color<<8);
#endif
						}

						//
						// Decrement the count of on pixels.
						//
						lOn--;

						//
						// Increment the X offset.
						//
						lX0++;
					}

					//
					// See if the X offset has reached the right side of the
					// character glyph.
					//
					if (lX0 == read_data_byte(pucData[1]))
					{
						//
						// Increment the Y offset.
						//
						lY0++;

						//
						// Reset the X offset to the left side of the character
						// glyph.
						//
						lX0 = 0;
					}
				}
			}

			//
			// Increment the X coordinate by the width of the character.
			//
			lX += read_data_byte(pucData[1]);
		}
	}
	return ChCount;
}

s32 GI::Screen::Gfx::String::drawStringTiny()
{
	if(!this)
		return 0;
	GI::Display::Display* LcdStruct = (GI::Display::Display *) pDisplay;
	//tFont *pFont = properties->pFont;
	char *pcString = buff;
	bool WordWrap = wordWrap;
	//s32 _SelStart = properties->_SelStart;
	//s32 _SelLen = properties->_SelLen;

	//struct Display_Struct* ScreenStruct = (struct Display_Struct*)ScreenFile->udata;
	s8 chWidth = 0;
	//s8 chWidth_Tmp = 0;
	s8 chHeight = 0;
	s32 CharPtr;
	s8 Tmp = 0;
	s32 Cursor_X = lX;
	s32 Cursor_Y = lY;
	s32 CharCnt = 0;
#ifdef __AVR_XMEGA__
	chWidth = pgm_read_byte(&CharTable6x8[2]);
	chHeight = pgm_read_byte(&CharTable6x8[3]);
#else
	chWidth = CharTable6x8[2];
	chHeight = CharTable6x8[3];
#endif
	do
	{
		u8 Char = *pcString;
		if (Char == 0)
			return CharCnt - 1;
#ifdef __AVR_XMEGA__
		CharPtr = ((Char - pgm_read_byte(&CharTable6x8[4])) * chWidth) + pgm_read_byte(&CharTable6x8[0]);
		if(Char < pgm_read_byte(&CharTable6x8[4]) || Char > pgm_read_byte(&CharTable6x8[5]))
#else
		CharPtr = ((Char - CharTable6x8[4]) * chWidth) + CharTable6x8[0];
		if (Char < CharTable6x8[4] || Char > CharTable6x8[5])
#endif
		{
			//chWidth_Tmp = chWidth;
			chWidth = 0;
		}
		else
		{
			u8 Temp;
			if (!terminalMode)
			{
				for (Tmp = 1; Tmp < chWidth; Tmp++)
				{
#ifdef __AVR_XMEGA__
					Temp = pgm_read_byte(&CharTable6x8[Tmp + CharPtr]);
#else
					Temp = CharTable6x8[Tmp + CharPtr];
#endif
					if (Temp == 0)
						break;
				}
				Tmp++;
			}
			else
			{
				Tmp = chWidth;
			}
			if (Cursor_X + Tmp >= LcdStruct->sClipRegion.sXMin
					&& Cursor_X < LcdStruct->sClipRegion.sXMax + Tmp
					&& Cursor_Y + chHeight >= LcdStruct->sClipRegion.sYMin
					&& Cursor_Y < LcdStruct->sClipRegion.sYMax + chHeight)
			{
				if (ulVisible)
				{
					s32 XX = 0;
					s32 YY = 0;
					for (XX = 0; XX < Tmp; XX++)
					{
#ifdef __AVR_XMEGA__
						Temp = pgm_read_byte(&CharTable6x8[XX + CharPtr]);
#else
						Temp = CharTable6x8[XX + CharPtr];
#endif
						for (YY = 0; YY < chHeight; YY++)
						{
							if (Temp & 0x1)
							{
								LcdStruct->drawPixel(XX + Cursor_X,
										YY + Cursor_Y, foreground_color);
							}
							else
							{
								if (ulOpaque)
									LcdStruct->drawPixel(XX + Cursor_X,
											YY + Cursor_Y, background_color);
							}
							Temp = Temp >> 1;
						}
					}
				}
			}
		}
		//if(Tmp < chWidth) Tmp++;
		switch (Char)
		{
		case '\r':
			Cursor_X = lX;
			pcString++;
			break;
		case '\n':
			Cursor_Y += chHeight;
			pcString++;
			break;
			//case 9:
			//case 11:
			////signed short TabCursor = (ScreenStruct->Cursor_X/((chWidth_Tmp>>1)*4)*(chWidth_Tmp>>1))*4;
			//Tmp = (((Cursor_X/(chWidth_Tmp<<2))*(chWidth_Tmp<<2))-Cursor_X) + (chWidth_Tmp<<2);
		default:
			Cursor_X += Tmp;
			/*if((ScreenStruct->Cursor_X + chWidth > ScreenStruct->Width) && ScreenStruct->WorldWrap == True)
			 {
			 ScreenStruct->CharWidth = Tmp;
			 ScreenStruct->CharHeight = chHeight;
			 return EOF;
			 }*/
			if ((Cursor_X + chWidth > LcdStruct->sClipRegion.sXMax)
					&& WordWrap == true)
			{
				Cursor_Y += chHeight;
				Cursor_X = lX;
			}
			pcString++;
		}
		CharCnt++;
	} while (1);
}

s32 GI::Screen::Gfx::String::getStrPropTiny()
{
	if(!this)
		return 0;
	//GScreen::Window *pDisplay = pDisplay;
	char *pcString = buff;
	//bool WordWrap = wordWrap;
	//tDisplay* LcdStruct = (tDisplay *) pDisplay;
	s8 chWidth = 0;
	//s8 chWidth_Tmp = 0;
	s32 CharPtr;
	s32 Cursor_X = 0;
	s32 CharCnt = 0;
#ifdef __AVR_XMEGA__
	chWidth = pgm_read_byte(&CharTable6x8[2]);
#else
	chWidth = CharTable6x8[2];
#endif
	do
	{
		s8 Tmp = 0;
		u8 Char = *pcString;
		if (Char == 0)
			return Cursor_X;
#ifdef __AVR_XMEGA__
		CharPtr = ((Char - pgm_read_byte(&CharTable6x8[4])) * chWidth) + pgm_read_byte(&CharTable6x8[0]);
		if(Char < pgm_read_byte(&CharTable6x8[4]) || Char > pgm_read_byte(&CharTable6x8[5]))
#else
		CharPtr = ((Char - CharTable6x8[4]) * chWidth) + CharTable6x8[0];
		if (Char < CharTable6x8[4] || Char > CharTable6x8[5])
#endif
		{
			//chWidth_Tmp = chWidth;
			chWidth = 0;
		}
		else
		{
			u8 Temp;
			if (!terminalMode)
			{
				for (Tmp = 1; Tmp < chWidth; Tmp++)
				{
#ifdef __AVR_XMEGA__
					Temp = pgm_read_byte(&CharTable6x8[Tmp + CharPtr]);
#else
					Temp = CharTable6x8[Tmp + CharPtr];
#endif
					if (Temp == 0)
						break;
				}
				Tmp++;
			}
			else
			{
				Tmp = chWidth;
			}
		}
		Cursor_X += Tmp;
		pcString++;
		CharCnt++;
	} while (1);
}

void GI::Screen::Gfx::String::appendF(const char *pcString, ...)
{
	if(!this)
		return;
	va_list args;
	va_start (args, pcString);
	char buff[1];
	s32 len = vsnprintf(buff, 0, pcString, args);
	va_end (args);
	if(len > 0)
	{
		char *tmp_str = (char *)malloc(len + 1);
		if(tmp_str)
		{
			va_start (args, pcString);
			vsnprintf(tmp_str, len + 1, pcString, args);
			va_end (args);
			append(tmp_str);
			free(tmp_str);
		}
	}
}

void GI::Screen::Gfx::String::appendF(GI::string *string, ...)
{
	if(!this)
		return;
	va_list args;
	char *pcString = string->buff;
	va_start (args, pcString);
	char buff[1];
	s32 len = vsnprintf(buff, 0, pcString, args);
	va_end (args);
	if(len > 0)
	{
		char *tmp_str = (char *)malloc(len + 1);
		if(tmp_str)
		{
			va_start (args, pcString);
			vsnprintf(tmp_str, len + 1, pcString, args);
			va_end (args);
			append(tmp_str);
			free(tmp_str);
		}
	}
}

void GI::Screen::Gfx::String::appendF(GI::Screen::Gfx::String *string, ...)
{
	if(!this)
		return;
	va_list args;
	char *pcString = string->buff;
	va_start (args, pcString);
	char buff[1];
	s32 len = vsnprintf(buff, 0, pcString, args);
	va_end (args);
	if(len > 0)
	{
		char *tmp_str = (char *)malloc(len + 1);
		if(tmp_str)
		{
			va_start (args, pcString);
			vsnprintf(tmp_str, len + 1, pcString, args);
			va_end (args);
			append(tmp_str);
			free(tmp_str);
		}
	}
}


void GI::Screen::Gfx::String::setTextF(const char *pcString, ...)
{
	if(!this)
		return;
	clear();
	va_list args;
	va_start (args, pcString);
	char buff[1];
	s32 len = vsnprintf(buff, 0, pcString, args);
	va_end (args);
	if(len > 0)
	{
		char *tmp_str = (char *)malloc(len + 1);
		if(tmp_str)
		{
			va_start (args, pcString);
			vsnprintf(tmp_str, len + 1, pcString, args);
			va_end (args);
			setText(tmp_str);
			free(tmp_str);
		}
	}
}

void GI::Screen::Gfx::String::setTextF(GI::string *string, ...)
{
	if(!this)
		return;
	clear();
	va_list args;
	char *pcString = string->buff;
	va_start (args, pcString);
	char buff[1];
	s32 len = vsnprintf(buff, 0, pcString, args);
	va_end (args);
	if(len > 0)
	{
		char *tmp_str = (char *)malloc(len + 1);
		if(tmp_str)
		{
			va_start (args, pcString);
			vsnprintf(tmp_str, len + 1, pcString, args);
			va_end (args);
			setText(tmp_str);
			free(tmp_str);
		}
	}
}

void GI::Screen::Gfx::String::setTextF(GI::Screen::Gfx::String *string, ...)
{
	if(!this)
		return;
	clear();
	va_list args;
	char *pcString = string->buff;
	va_start (args, pcString);
	char buff[1];
	s32 len = vsnprintf(buff, 0, pcString, args);
	va_end (args);
	if(len > 0)
	{
		char *tmp_str = (char *)malloc(len + 1);
		if(tmp_str)
		{
			va_start (args, pcString);
			vsnprintf(tmp_str, len + 1, pcString, args);
			va_end (args);
			setText(tmp_str);
			free(tmp_str);
		}
	}
}
