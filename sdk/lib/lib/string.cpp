/*
 * lib/string.cpp
 */

#include "string.h"


GI::string::string()
{
	memset(this, 0, sizeof(*this));
	buff = (char *) calloc(1, 1);
	if (buff)
	{
		error = SYS_ERR_OK;
	}
	else
	{
		error = SYS_ERR_OUT_OF_MEMORY;
	}
}

/*GI::String::String(char *String)
{
	memset(this, 0, sizeof(*this));
	unsigned int len = strlen(String);
	buff = (char *) malloc(len + 1);
	if (buff)
	{
		strcpy((char *) buff, (const char *) String);
		length = len;
		error = SYS_ERR_OK;
		modifyed++;
	}
}

GI::String::String(GI::String *String)
{
	memset(this, 0, sizeof(*this));
	unsigned int len = String->length;
	buff = (char *) malloc(len + 1);
	if (buff)
	{
		strcpy((char *) buff, (const char *) String->buff);
		length = len;
		error = SYS_ERR_OK;
		modifyed++;
	}
}*/

GI::string::string(const char *String, ...)
{
	memset(this, 0, sizeof(*this));
	va_list args;
	va_start (args, String);
	char tmp_buff[1];
	s32 len = vsnprintf(tmp_buff, 0, String, args);
	va_end (args);
	buff = (char *)malloc(len + 1);
	if(buff)
	{
		va_start (args, String);
		vsnprintf(buff, len + 1, String, args);
		va_end (args);
		length = len;
		modifyed++;
	}
	else
	{
		error = SYS_ERR_OUT_OF_MEMORY;
	}
}

GI::string::string(GI::string *String, ...)
{
	memset(this, 0, sizeof(*this));
	va_list args;
	char *pcString = String->buff;
	va_start (args, pcString);
	char tmp_buff[1];
	s32 len = vsnprintf(tmp_buff, 0, pcString, args);
	va_end (args);
	buff = (char *)malloc(len + 1);
	if(buff)
	{
		va_start (args, pcString);
		vsnprintf(buff, len + 1, pcString, args);
		va_end (args);
		length = len;
		modifyed++;
	}
	else
	{
		error = SYS_ERR_OUT_OF_MEMORY;
	}
}




GI::string::~string()
{
	if(!this)
		return;
	if (buff)
		free((void *) buff);
	memset(this, 0, sizeof(*this));
}

bool GI::string::equal(GI::string *string)
{
	if(!this)
		return false;
	if(!string)
		return false;
	if((modifyed != string->modifyed) ||
	//(strcmp(buff, string.buff) == 0)   ? false :
		(length != string->length))
		return false;
	return true;
}

bool GI::string::equal(char *string)
{
	if(!this)
		return false;
	if(!string)
		return false;
	if(strcmp(buff, string))
		return false;
	return true;
}

void GI::string::toUper()
{
	if(!this)
		return;
	unsigned int TmpCnt = length;
	char* Str = buff;
	do{
		*Str = (char)toupper((int)*Str);
		Str++;
	}while(--TmpCnt);
	error = SYS_ERR_OK;
	modifyed++;
}

void GI::string::toLower()
{
	if(!this)
		return;
	unsigned int TmpCnt = length;
	char* Str = buff;
	do{
		*Str = (char)tolower((int)*Str);
		Str++;
	}while(--TmpCnt);
	error = SYS_ERR_OK;
	modifyed++;
}

void GI::string::removeNewLine(GI::string *string)
{
	if(!this)
		return;
	if(!string)
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

void GI::string::set(char* string)
{
	if(!this)
		return;
	if (!string)
		return;
	unsigned int LenSrc = strlen(string);
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

void GI::string::set(GI::string *string)
{
	if(!this)
		return;
	if (!string)
		return;
	unsigned int LenSrc = string->length;
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

void GI::string::setF(const char *pcString, ...)
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
            set(tmp_str);
            free(tmp_str);
        }
    }
}

void GI::string::setF(GI::string *string, ...)
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
            set(tmp_str);
            free(tmp_str);
        }
    }
}


void GI::string::append(GI::string *string)
{
	if(!this)
		return;
	if(!buff || !string)
		return;
	unsigned int LenSrc = string->length;
	unsigned int LenDest = length;
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

void GI::string::append(char* string)
{
	if(!this)
		return;
	if(!buff || !string)
		return;
	unsigned int LenSrc = strlen(string);
	unsigned int LenDest = length;
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

void GI::string::append(char Char)
{
	if(!this)
		return;
	signed int LenSrc = (Char == 0x08 || Char == 0x7F) ? -1 : 1;
	if(!length && LenSrc == -1)
		return;
	unsigned int LenDest = length;
	char *Return = (char *) realloc(buff, LenDest + LenSrc + 1);
	//char *Return = (char *)realloc(dest, LenDest + LenSrc + 1);
	if (!Return)
		return;
	char buff_char[2];
	if(LenSrc != -1)
	{
		buff_char[0] = Char;
		buff_char[1] = '\0';
		strcat(Return, buff_char);
	}
	Return[LenDest + LenSrc] = '\0';
	buff = Return;
	length = LenDest + LenSrc;
	modifyed = true;
	error = SYS_ERR_OK;
}

void GI::string::appendF(const char *pcString, ...)
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

void GI::string::appendF(GI::string *string, ...)
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

void GI::string::insert(GI::string* string, unsigned int location)
{
	if(!this)
		return;
	if(!string)
		return;
	unsigned int LenSrc = string->length;
	if(location > LenSrc)
		return;
	if(!buff)
	{
		return;
	}

	char *Return = (char *)realloc(buff, length + LenSrc + 1);
	if(!Return)
		return;
	unsigned int LenDest = length + location;
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

void GI::string::insert(char *string, unsigned int location)
{
	if(!this)
		return;
	if(!string)
		return;
	unsigned int LenSrc = strlen(string);
	if(location > LenSrc)
		return;
	if(!buff)
	{
		return;
	}

	char *Return = (char *)realloc(buff, length + LenSrc + 1);
	if(!Return)
		return;
	unsigned int LenDest = length + location;
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

void GI::string::clone(GI::string* string)
{
	if(!this)
		return;
	if (!string)
		return;
	unsigned int LenSrc = string->length;
	char *Return = (char *) realloc(string->buff, LenSrc + 1);
	//char *Return = (char *)realloc(dest, LenDest + LenSrc + 1);
	if (!Return)
		return;
	strcpy(Return, string->buff);
	buff = Return;
	error = SYS_ERR_OK;
    modifyed = string->modifyed;
    length = string->length;
}

void GI::string::clear()
{
	if(!this)
		return;
	char *Return = (char *) realloc(buff, 1);
	*Return = 0;
	length = 0;
	buff = Return;
	error = SYS_ERR_OK;
	modifyed++;
}
char *GI::string::subString(unsigned int position, unsigned int len)
{
	if(!this)
		return NULL;
	if (!buff)
		return NULL;
	if (position + len >= (unsigned int) length)
		return NULL;
	char *Return = (char *) malloc(len + 1);
	if (!Return)
		return NULL;
	*Return = 0;
	strncpy(Return, buff + position, len);
	Return[len] = '\0';
	return Return;
}

char *GI::string::subString(unsigned int position)
{
	if(!this)
		return NULL;
	if (!buff)
		return NULL;
	if (position >= (unsigned int) length)
		return NULL;
	char *Return = (char *) malloc((length - position) + 1);
	if (!Return)
		return NULL;
	*Return = 0;
	strcpy(Return, buff + position);
	return Return;
}

GI::stringArray::stringArray()
{
	memset(this, 0, sizeof(*this));
	array = (GI::string **)calloc(1, sizeof(GI::string *));
}

GI::stringArray::~stringArray()
{
	if(!this)
		return;
	if(!array)
		return;
	while(itemsCount)
	{
		delete array[itemsCount - 1];
		itemsCount--;
	}
	free(array);
	array = NULL;
}

SysErr GI::stringArray::add(GI::string *str)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	if(!str)
		return SYS_ERR_INVALID_PARAM;
	if(!array)
		return SYS_ERR_UNKNOWN;
	GI::string * tmp_str = new GI::string(str);
	if(!tmp_str)
		return SYS_ERR_OUT_OF_MEMORY;
	GI::string **tmp_array = (GI::string **)realloc(array, sizeof(GI::string *) * (itemsCount + 1));
	if(!tmp_array)
	{
		delete tmp_str;
		return SYS_ERR_OUT_OF_MEMORY;
	}
	tmp_str->set(str);
	tmp_array[itemsCount] = tmp_str;
	array = tmp_array;
	itemsCount++;
	return SYS_ERR_OK;
}

SysErr GI::stringArray::add(char *str)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	if(!str)
		return SYS_ERR_INVALID_PARAM;
	if(!array)
		return SYS_ERR_UNKNOWN;
	GI::string * tmp_str = new GI::string(str);
	if(!tmp_str)
		return SYS_ERR_OUT_OF_MEMORY;
	GI::string **tmp_array = (GI::string **)realloc(array, sizeof(GI::string *) * (itemsCount + 1));
	if(!tmp_array)
		return SYS_ERR_OUT_OF_MEMORY;
	tmp_array[itemsCount] = tmp_str;
	array = tmp_array;
	itemsCount++;
	return SYS_ERR_OK;
}

SysErr GI::stringArray::insert(GI::string *str, unsigned int position)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	if(!str)
		return SYS_ERR_INVALID_PARAM;
	if(!array)
		return SYS_ERR_UNKNOWN;
	if(itemsCount == 0 && position == 0)
	{
		return add(str);
	}
	GI::string * tmp_str = new GI::string(str);
	if(!tmp_str)
		return SYS_ERR_OUT_OF_MEMORY;
	GI::string **tmp_array = (GI::string **)realloc(array, sizeof(GI::string *) * (itemsCount + 1));
	if(!tmp_array)
	{
		delete tmp_str;
		return SYS_ERR_OUT_OF_MEMORY;
	}
	//memmove(tmp_array + (sizeof(GI::String *) * (position + 1)), tmp_array + (sizeof(GI::String *) * position), sizeof(GI::String *) * (itemsCount - position));
	unsigned long cnt = itemsCount - position;
	for(; cnt > 0; cnt--)
	{
		tmp_array[cnt + position] = tmp_array[(cnt - 1) + position];
	}
	tmp_array[position] = tmp_str;
	array = tmp_array;
	itemsCount++;
	return SYS_ERR_OK;
}

SysErr GI::stringArray::insert(char *str, unsigned int position)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	if(!str)
		return SYS_ERR_INVALID_PARAM;
	if(!array)
		return SYS_ERR_UNKNOWN;
	if(itemsCount == 0 && position == 0)
	{
		return add(str);
	}
	GI::string * tmp_str = new GI::string(str);
	if(!tmp_str)
		return SYS_ERR_OUT_OF_MEMORY;
	GI::string **tmp_array = (GI::string **)realloc(array, sizeof(GI::string *) * (itemsCount + 1));
	if(!tmp_array)
		return SYS_ERR_OUT_OF_MEMORY;
	memmove(tmp_array + (sizeof(GI::string *) * (position + 1)), tmp_array + (sizeof(GI::string *) * position), sizeof(GI::string *) * (itemsCount - position));
	tmp_array[itemsCount] = tmp_str;
	array = tmp_array;
	itemsCount++;
	return SYS_ERR_OK;
}

SysErr GI::stringArray::remove(unsigned int position)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	if(!array)
		return SYS_ERR_UNKNOWN;
	if(position >= itemsCount)
		return SYS_ERR_OUT_OF_RANGE;
	delete array[position];
	memmove(array + (sizeof(GI::string *) * position), array + (sizeof(GI::string *) * (position + 1)), sizeof(GI::string *) * (itemsCount - position - 1));
	GI::string **tmp_array = (GI::string **)realloc(array, sizeof(GI::string *) * (itemsCount - 1));
	array = tmp_array;
	itemsCount--;
	if(!tmp_array)
		return SYS_ERR_OUT_OF_MEMORY;
	return SYS_ERR_OK;
}

GI::stringCharArray::stringCharArray()
{
	memset(this, 0, sizeof(*this));
	array = (char **)calloc(1, sizeof(char *));
}

GI::stringCharArray::stringCharArray(GI::stringArray *strArray)
{
	memset(this, 0, sizeof(*this));
	char **char_array = (char **)malloc(sizeof(char *) * strArray->itemsCount);
	if(!char_array)
		return;
	unsigned int cnt = 0;
	for(; cnt < strArray->itemsCount; cnt++)
	{
		char *item_str = (char *)malloc(strArray->array[cnt]->length + 1);
		if(!item_str)
			break;
		strcpy(item_str, strArray->array[cnt]->buff);
		char_array[cnt] = item_str;
	}
	itemsCount = strArray->itemsCount;
	array = char_array;
}

GI::stringCharArray::stringCharArray(GI::stringArray *strArray, unsigned int offset)
{
	memset(this, 0, sizeof(*this));
	if(offset > strArray->itemsCount)
		return;
	char **char_array = (char **)malloc(sizeof(char *) * strArray->itemsCount - offset);
	if(!char_array)
		return;
	unsigned int cnt = offset;
	unsigned int dest_cnt = 0;
	for(; cnt < strArray->itemsCount; cnt++)
	{
		char *item_str = (char *)malloc(strArray->array[cnt]->length + 1);
		if(!item_str)
			break;
		strcpy(item_str, strArray->array[cnt]->buff);
		char_array[dest_cnt++] = item_str;
	}
	itemsCount = strArray->itemsCount - offset;
	array = char_array;
}

GI::stringCharArray::~stringCharArray()
{
	if(!this)
		return;
	if(!array)
		return;
	while(itemsCount)
	{
		free((void *)array[itemsCount - 1]);
		itemsCount--;
	}
	free(array);
}


SysErr GI::stringCharArray::convert(GI::stringArray *strArray)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	char **char_array = (char **)realloc(array, sizeof(char *) * strArray->itemsCount);
	if(!char_array)
		return SYS_ERR_OUT_OF_MEMORY;
	unsigned int cnt = 0;
	for(; cnt < strArray->itemsCount; cnt++)
	{
		char *item_str = (char *)malloc(strArray->array[cnt]->length + 1);
		if(!item_str)
			break;
		strcpy(item_str, strArray->array[cnt]->buff);
		char_array[cnt] = item_str;
	}
	itemsCount = strArray->itemsCount;
	array = char_array;
	if(cnt == strArray->itemsCount)
		return SYS_ERR_OUT_OF_MEMORY;
	return SYS_ERR_OK;
}

SysErr GI::stringCharArray::convert(GI::stringArray *strArray, unsigned int offset)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	if(offset >= strArray->itemsCount)
		return SYS_ERR_OUT_OF_RANGE;
	char **char_array = (char **)malloc(sizeof(char *) * strArray->itemsCount - offset);
	if(!char_array)
		return SYS_ERR_OUT_OF_MEMORY;
	unsigned int cnt = offset;
	unsigned int dest_cnt = 0;
	for(; cnt < strArray->itemsCount; cnt++)
	{
		char *item_str = (char *)malloc(strArray->array[cnt]->length + 1);
		if(!item_str)
			break;
		strcpy(item_str, strArray->array[cnt]->buff);
		char_array[dest_cnt++] = item_str;
	}
	itemsCount = strArray->itemsCount;
	array = char_array;
	return SYS_ERR_OK;
}



