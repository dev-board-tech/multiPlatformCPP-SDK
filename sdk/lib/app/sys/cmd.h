/*
 * app/sys/cmd.h
 */

#ifndef LIB_APP_SYS_CMD_H_
#define LIB_APP_SYS_CMD_H_

#ifdef __AVR_XMEGA__
#endif
#include <lib/string.h>
#include <api/io_handle.h>
#include <include/global.h>
#include <api/gpio.h>
#include <lib/buffers/ring_buff.h>

class Cmd
{
public:
	Cmd(char *inPath, char *outPath, char *errPath);
	~Cmd();
	SysErr idle();
	SysErr parse(char data);
	SysErr ls(int argc, char *argv[]);
	SysErr cd(int argc, char *argv[]);
	SysErr cat(int argc, char *argv[]);

	void printError(int error);
private:
	GI::string *input;
	GI::string *path;
	GI::IO *inPath;
	GI::IO *outPath;
	GI::IO *errPath;

	SysErr cdInt(GI::string *_path, GI::string *input);
	SysErr hystoryAdd(GI::string *input);
	SysErr hystoryUp(GI::string *out);
	SysErr hystoryDn(GI::string *out);

	unsigned int hystoryPtr;
	bool escape_received;
	unsigned char escape_second_char;
	GI::Buff::RingBuff *outFifo;
	short charPopFromFifo;
};

#if __AVR_XMEGA__
#include <avr/pgmspace.h>
extern PGM_P fs_err_table[];
#else
extern const char *fs_err_table[];
#endif
/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "cat.cpp"
#include "cd.cpp"
#include "cmd.cpp"
#include "ls.cpp"
#endif
/*#####################################################*/

#endif /* LIB_APP_SYS_CMD_H_ */
