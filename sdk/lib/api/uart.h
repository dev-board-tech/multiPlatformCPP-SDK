/*
 *  api/uart.h
 */

#ifndef UART_DEF_H_
#define UART_DEF_H_

#include <stdbool.h>
#include <api/gpio.h>
#include <api/lcd_def.h>
#include <interface/uart.h>
#include <include/global.h>
#include <lib/gfx/string.h>
#include <lib/string.h>
#include <api/std.h>
#include <api/init_def.h>
/*#####################################################*/
typedef struct
{
	char name[12];
	unsigned int tx;
	unsigned int rx;
	unsigned long speed;
	enum wordLen_e{
#if (UART_HAVE_WORD_LEN_5BITS == 1)
		WORD_LEN_5,
#endif
#if (UART_HAVE_WORD_LEN_6BITS == 1)
		WORD_LEN_6,
#endif
#if (UART_HAVE_WORD_LEN_7BITS == 1)
		WORD_LEN_7,
#endif
		WORD_LEN_8,
#if (UART_HAVE_WORD_LEN_9BITS == 1)
		WORD_LEN_9,
#endif
	}wordLen;
	enum stopBits_e{
		STOP_BITS_ONE,
#if (UART_HAVE_STOP_BITS_ONE_AND_HALF == 1)
		STOP_BITS_ONE_AND_HALF,
#endif
		STOP_BITS_TWO,
	}stopBits;
	enum parity_e{
		PAR_NONE,
		PAR_ODD,
		PAR_EVEN,
		PAR_MASK,
		PAR_ZERO,
		PAR_ONE
	}parity;
	enum uartMode_e
	{
		MODE_ASYNC = 0,
#if (UART_HAVE_MODE_SYNCHRONOUS == 1)
		MODE_SYNC,
#endif
#if (UART_HAVE_MODE_IR == 1)
		MODE_IR,
#endif
#if (UART_HAVE_MODE_SPI == 1)
		MODE_SPI,
#endif
	}uartMode;
} CfgUart;
/*#####################################################*/
namespace GI
{
namespace Dev
{
class Uart
{
public:
	Uart(ioSettings *cfg);
	~Uart();
	void putChar(unsigned char byteTx);
	unsigned char getChar();
	bool putCharNb(unsigned char byteTx);
	signed short getCharNb();
	void printF(const char *pcString, ...);
	void printF(GI::string *string, ...);
	//void printF(GI::Screen::String *string, ...);
	int print(const char *pcString);
	int print(GI::string *string);
	//int print(GI::Screen::String *string);
	int write(char *data, unsigned int len);

	SysErr setSpeed(unsigned long baudRate);
	SysErr setWordLen(CfgUart::wordLen_e wLen);
	SysErr setStopBits(CfgUart::stopBits_e sBits);
	SysErr setParBits(CfgUart::parity_e pBits);
	SysErr getSpeed(unsigned long *baudRate);
	SysErr getWordLen(CfgUart::wordLen_e *wLen);
	SysErr getStopBits(CfgUart::stopBits_e *sBits);
	SysErr getParBits(CfgUart::parity_e *pBits);
	SysErr err;
	ioSettings *cfg;

	void (*charReceive_Callback)(char data);
	void *udata;
private:

	bool isVirtual;
	unsigned char unitNr;
	unsigned int BaseAddr;
};
}
}
/*#####################################################*/

/*#####################################################*/
#endif /* UART_DEF_H_ */
/*#####################################################*/
