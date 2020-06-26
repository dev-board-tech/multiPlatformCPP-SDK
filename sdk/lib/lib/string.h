/*
 * lib/string.h
 */

#ifndef LIB_LIB_STRING_H_
#define LIB_LIB_STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#if defined (__AVR_XMEGA__) || defined (__AVR_MEGA__)
#include <avr/pgmspace.h>
#endif

#include <include/global.h>

#ifdef HAVE_LONG_DOUBLE
#define LDOUBLE long double
#else
#define LDOUBLE double
#endif
#ifdef __AVR_XMEGA__
extern const u8 CharTable6x8[] PROGMEM;
#else
extern const u8 CharTable6x8[];
#endif

namespace GI
{
	class string
	{
	public:
		string();
		//String(char *String);
		//String(GI::String *String);
		string(const char *string, ...);
		string(GI::string *string, ...);
		~string();
		bool equal(char *string);
		bool equal(GI::string *string);
		void toUper();
		void toLower();
		void removeNewLine(GI::string *string);
		void set(char* string);
		void set(GI::string *string);
		void setF(const char *pcString, ...);
		void setF(GI::string *string, ...);
		void append(GI::string *string);
		void append(char* string);
		void append(char Char);
		void appendF(const char *pcString, ...);
		void appendF(GI::string *string, ...);
		void insert(GI::string* string, unsigned int location);
		void insert(char *string, unsigned int location);
		void clone(GI::string* string);
		void clear();
		char *subString(unsigned int position, unsigned int len);
		char *subString(unsigned int position);

		char *buff;
		unsigned int length;
		unsigned int modifyed;
		int error;
		//bool initialized;
		
	private:
		
	};
}

namespace GI
{
	class stringArray
	{
	public:
		stringArray();
		~stringArray();
		SysErr add(GI::string *str);
		SysErr add(char *str);
		SysErr insert(GI::string *str, unsigned int position);
		SysErr insert(char *str, unsigned int position);
		SysErr remove(unsigned int position);
		SysErr toCharStrArray(char ***charArray, unsigned int *itemsCount);
		SysErr freeCharStrArray(char **charArray, unsigned int itemsCount);
		GI::string ** array;
		unsigned int itemsCount;
	};
}

namespace GI
{
	class stringCharArray
	{
	public:
		stringCharArray();
		~stringCharArray();
		stringCharArray(GI::stringArray *strArray);
		stringCharArray(GI::stringArray *strArray, unsigned int offset);
		SysErr convert(GI::stringArray *strArray);
		SysErr convert(GI::stringArray *strArray, unsigned int offset);
		char ** array;
		unsigned int itemsCount;
	};
}
/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "string.cpp"
#endif
/*#####################################################*/

#endif /* LIB_LIB_STRING_H_ */
