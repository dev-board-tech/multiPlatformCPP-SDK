/*
 * uart.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: John Smith
 */

#include <string.h>
#include <api/uart.h>
#include <api/init.h>
#include "uart.h"
#include <driver/uart.h>
#include <io_defs.h>

#define USE_UART_TX_INTERRUPT	true

#if (USE_DRIVER_SEMAPHORE == true)
volatile bool uart_semaphore[UART_INTERFACE_COUNT];
#endif
extern unsigned long FCPU;

static volatile unsigned char *nonblockingTxBuffPtr[8];
static volatile unsigned int bytesLeft[8];

FPGA_USART_t* UART_BASE_PTRS[] =
{
#ifdef FPGA_UARTA
		&FPGA_UARTA,
#else
		NULL,
#endif
#ifdef FPGA_UARTB
		&FPGA_UARTB,
#else
		NULL,
#endif
#ifdef FPGA_UARTC
		&FPGA_UARTC,
#else
		NULL,
#endif
#ifdef FPGA_UARTD
		&FPGA_UARTD,
#else
		NULL,
#endif
#ifdef FPGA_UARTE
		&FPGA_UARTE,
#else
		NULL,
#endif
#ifdef FPGA_UARTF
		&FPGA_UARTF,
#else
		NULL,
#endif
#ifdef FPGA_UARTG
		&FPGA_UARTG,
#else
		NULL,
#endif
#ifdef FPGA_UARTH
		&FPGA_UARTH
#else
		NULL,
#endif
		};

/*#####################################################*/
GI::Dev::Uart::Uart(ioSettings *cfg)
{
	if(cfg->info.ioType != ioSettings::info_s::ioType_UART)
	return;

	if(strncmp(cfg->info.name, (char *)"uart-", sizeof("uart-") - 1))
	{
		err = SYS_ERR_INVALID_PATH;
		return;
	}
	if(!strncmp(cfg->info.name, (char *)"uart-", sizeof("uart-") - 1))
	{
		unsigned char dev_nr = cfg->info.name[sizeof("uart-") - 1] - '0';
		if(dev_nr >= UART_INTERFACE_COUNT)
		{
			err = SYS_ERR_INVALID_PATH;
			return;
		}
		memset(this, 0, sizeof(*this));
		unitNr = dev_nr;
	}
	else
	{
		err = SYS_ERR_INVALID_PARAM;
		return;
	}

	this->cfg = cfg;
	CfgUart *int_cfg = (CfgUart *)cfg->cfg;

	udata = (void *)UART_BASE_PTRS[unitNr];

	unsigned int ubrr = (FCPU / (int_cfg->speed * 8)) -1;
	if(ubrr < 4095)
		ubrr = 4095;
	((FPGA_USART_t*)udata)->BAUDCTRLA = (unsigned char)ubrr;
	((FPGA_USART_t*)udata)->BAUDCTRLB = (unsigned char)((ubrr>>8) & 0x0F);
	unsigned char tmp = 0;
	if(int_cfg->wordLen == CfgUart::WORD_LEN_5)
		tmp = FPGA_USART_CHSIZE_5BIT_gc;
	else if(int_cfg->wordLen == CfgUart::WORD_LEN_6)
		tmp = FPGA_USART_CHSIZE_6BIT_gc;
	else if(int_cfg->wordLen == CfgUart::WORD_LEN_7)
		tmp = FPGA_USART_CHSIZE_7BIT_gc;
	else if(int_cfg->wordLen == CfgUart::WORD_LEN_8)
		tmp = FPGA_USART_CHSIZE_8BIT_gc;
	else if(int_cfg->wordLen == CfgUart::WORD_LEN_9)
		tmp = FPGA_USART_CHSIZE_9BIT_gc;
	else
		tmp = FPGA_USART_CHSIZE_8BIT_gc;
		
	if(int_cfg->parity == CfgUart::PAR_EVEN)
		tmp |= FPGA_USART_PMODE_EVEN_gc;
	else if(int_cfg->parity == CfgUart::PAR_ODD)
		tmp |= FPGA_USART_PMODE_ODD_gc;
		
#if UART_HAVE_MODE_SYNCHRONOUS == 1
	if(int_cfg->uartMode == CfgUart::MODE_SYNC)
	{
		tmp |= FPGA_USART_CMODE_SYNCHRONOUS_gc;
	}
#endif

	if(int_cfg->stopBits == CfgUart::STOP_BITS_TWO)
		tmp |= FPGA_USART_SBMODE_bm;
	((FPGA_USART_t*)udata)->CTRLC = tmp;
	tmp = FPGA_USART_CLK2X_bm;
	if(int_cfg->rx)
		tmp |= FPGA_USART_RXEN_bm;
	if(int_cfg->tx)
		tmp |= FPGA_USART_TXEN_bm;
	((FPGA_USART_t*)udata)->CTRLB = tmp;
#if USE_UART_TX_INTERRUPT == true
	((FPGA_USART_t*)udata)->CTRLA = FPGA_USART_TXCINTLVL_LO_gc;
#endif
}
/*#####################################################*/
GI::Dev::Uart::~Uart()
{

}
/*#####################################################*/
/*#####################################################*/
SysErr GI::Dev::Uart::setSpeed(unsigned long baudRate)
{
	if(!this || !udata)
		return SYS_ERR_INVALID_HANDLER;
	CfgUart *int_cfg = (CfgUart *)cfg->cfg;
	unsigned int ubrr = ((FCPU / 8) / baudRate) -1;
	((FPGA_USART_t*)udata)->BAUDCTRLA = (unsigned char)ubrr;
	((FPGA_USART_t*)udata)->BAUDCTRLB = (unsigned char)((ubrr>>8) & 0x0F);
	return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::Uart::setWordLen(CfgUart::wordLen_e wLen)
{
	if(!this || !udata)
		return SYS_ERR_INVALID_HANDLER;
	unsigned char tmp = ((FPGA_USART_t*)udata)->CTRLC & ~FPGA_USART_CHSIZE_gm;
	CfgUart *int_cfg = (CfgUart *)cfg->cfg;
	if(int_cfg->wordLen == CfgUart::WORD_LEN_5)
		tmp = FPGA_USART_CHSIZE_5BIT_gc;
	else if(int_cfg->wordLen == CfgUart::WORD_LEN_6)
		tmp = FPGA_USART_CHSIZE_6BIT_gc;
	else if(int_cfg->wordLen == CfgUart::WORD_LEN_7)
		tmp = FPGA_USART_CHSIZE_7BIT_gc;
	else if(int_cfg->wordLen == CfgUart::WORD_LEN_8)
		tmp = FPGA_USART_CHSIZE_8BIT_gc;
	else if(int_cfg->wordLen == CfgUart::WORD_LEN_9)
		tmp = FPGA_USART_CHSIZE_9BIT_gc;
	else
		tmp = FPGA_USART_CHSIZE_8BIT_gc;
	((FPGA_USART_t*)udata)->CTRLC = tmp;
	return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::Uart::setStopBits(CfgUart::stopBits_e sBits)
{
	if(!this || !udata)
		return SYS_ERR_INVALID_HANDLER;
	unsigned char tmp = ((FPGA_USART_t*)udata)->CTRLC & ~FPGA_USART_SBMODE_bm;
	CfgUart *int_cfg = (CfgUart *)cfg->cfg;
	if(int_cfg->stopBits == CfgUart::STOP_BITS_TWO)
		tmp |= FPGA_USART_SBMODE_bm;
	((FPGA_USART_t*)udata)->CTRLC = tmp;
	return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::Uart::setParBits(CfgUart::parity_e pBits)
{
	if(!this || !udata)
		return SYS_ERR_INVALID_HANDLER;
	unsigned char tmp = ((FPGA_USART_t*)udata)->CTRLC & ~FPGA_USART_PMODE_gm;
	CfgUart *int_cfg = (CfgUart *)cfg->cfg;
	if(int_cfg->parity == CfgUart::PAR_EVEN)
		tmp |= FPGA_USART_PMODE_EVEN_gc;
	else if(int_cfg->parity == CfgUart::PAR_ODD)
		tmp |= FPGA_USART_PMODE_ODD_gc;
	((FPGA_USART_t*)udata)->CTRLC = tmp;
	return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::Uart::getSpeed(unsigned long *baudRate)
{
	if(!this || !udata)
		return SYS_ERR_INVALID_HANDLER;
	*baudRate = (FCPU / 8) / ((((FPGA_USART_t*)udata)->BAUDCTRLB << 8) | ((FPGA_USART_t*)udata)->BAUDCTRLA);
	return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::Uart::getWordLen(CfgUart::wordLen_e *wLen)
{
	if(!this || !udata)
		return SYS_ERR_INVALID_HANDLER;
	//unsigned char tmp = ((USART_t*)udata)->CTRLC & USART_CHSIZE_gm;
	CfgUart *int_cfg = (CfgUart *)cfg->cfg;
	/*if(int_cfg->wordLen == USART_CHSIZE_5BIT_gc)
		*wLen = CfgUart::WORD_LEN_5;
	else if(int_cfg->wordLen == USART_CHSIZE_6BIT_gc)
		*wLen = CfgUart::WORD_LEN_6;
	else if(int_cfg->wordLen == USART_CHSIZE_7BIT_gc)
		*wLen = CfgUart::WORD_LEN_7;
	else if(int_cfg->wordLen == USART_CHSIZE_8BIT_gc)
		*wLen = CfgUart::WORD_LEN_8;
	else if(int_cfg->wordLen == USART_CHSIZE_9BIT_gc)
		*wLen = CfgUart::WORD_LEN_9;
	else
		*wLen = CfgUart::WORD_LEN_8;*/
	*wLen = int_cfg->wordLen;
	return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::Uart::getStopBits(CfgUart::stopBits_e *sBits)
{
	if(!this || !udata)
		return SYS_ERR_INVALID_HANDLER;
	//unsigned char tmp = ((USART_t*)udata)->CTRLC & USART_SBMODE_bm;
	CfgUart *int_cfg = (CfgUart *)cfg->cfg;
	if(int_cfg->stopBits == FPGA_USART_SBMODE_bm)
		*sBits = CfgUart::STOP_BITS_TWO;
	else
		*sBits = CfgUart::STOP_BITS_ONE;
	return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::Uart::getParBits(CfgUart::parity_e *pBits)
{
	if(!this || !udata)
		return SYS_ERR_INVALID_HANDLER;
	//unsigned char tmp = ((USART_t*)udata)->CTRLC & ~USART_PMODE_gm;
	CfgUart *int_cfg = (CfgUart *)cfg->cfg;
	/*if(int_cfg->parity == USART_PMODE_EVEN_gc)
		*pBits = CfgUart::PAR_EVEN;
	else if(int_cfg->parity == USART_PMODE_ODD_gc)
		*pBits = CfgUart::PAR_ODD;
	else if(int_cfg->parity == USART_PMODE_DISABLED_gc)
		*pBits = CfgUart::PAR_NONE;
	else
		*pBits = CfgUart::PAR_NONE;*/
	*pBits = int_cfg->parity;
	return SYS_ERR_OK;
}
/*#####################################################*/
void GI::Dev::Uart::putChar(unsigned char byteTx)
{
#if (USE_DRIVER_SEMAPHORE == true)
	while (uart_semaphore[unitNr]);
	uart_semaphore[unitNr] = true;
#endif
	/*if(isVirtual)
	{
		while(((GI::Dev::UsbDCdc *)udata)->tx(&byteTx, 1) != 1);
	}
	else*/
	{
		while (!(((FPGA_USART_t*)udata)->STATUS & (FPGA_USART_DREIF_bm)));
		/* Put data into buffer, sends the data */
		((FPGA_USART_t*)udata)->DATA = byteTx;
	}
#if (USE_DRIVER_SEMAPHORE == true)
	uart_semaphore[unitNr] = false;
#endif
}
/*#####################################################*/
unsigned char GI::Dev::Uart::getChar()
{
	unsigned char data = 0;
#if (USE_DRIVER_SEMAPHORE == true)
	while (uart_semaphore[unitNr]);
	uart_semaphore[unitNr] = true;
#endif
	/*if(isVirtual)
		while(((GI::Dev::UsbDCdc *)udata)->rx(&data) == 0);
	else*/
	{
		while ((((FPGA_USART_t*)udata)->STATUS & (FPGA_USART_RXCIF_bm)) == 0)
		data = ((FPGA_USART_t*)udata)->DATA;
	}
#if (USE_DRIVER_SEMAPHORE == true)
	uart_semaphore[unitNr] = false;
#endif
	return data;
}
/*#####################################################*/
bool GI::Dev::Uart::putCharNb(unsigned char byteTx)
{
#if (USE_DRIVER_SEMAPHORE == true)
	while (uart_semaphore[unitNr])
		;
	uart_semaphore[unitNr] = true;
#endif
	if (!(((FPGA_USART_t*)udata)->STATUS & FPGA_USART_DREIF_bm))
	{
#if (USE_DRIVER_SEMAPHORE == true)
			uart_semaphore[unitNr] = false;
#endif
		return false;
	}
	((FPGA_USART_t*)udata)->DATA = byteTx;
#if (USE_DRIVER_SEMAPHORE == true)
	uart_semaphore[unitNr] = false;
#endif
	return true;
}
/*#####################################################*/
signed short GI::Dev::Uart::getCharNb()
{
	signed short data = 0;
#if (USE_DRIVER_SEMAPHORE == true)
	while (uart_semaphore[unitNr])
		;
	uart_semaphore[unitNr] = true;
#endif
	if ((((FPGA_USART_t*)udata)->STATUS & (FPGA_USART_RXCIF_bm)) == 0)
	{
#if (USE_DRIVER_SEMAPHORE == true)
			uart_semaphore[unitNr] = false;
#endif
		return -1;	 //UARTCharPutNonBlocking((USART_TypeDef*)BaseAddr, byteTx);
	}
	data = ((FPGA_USART_t*)udata)->DATA;
#if (USE_DRIVER_SEMAPHORE == true)
	uart_semaphore[unitNr] = false;
#endif
	return data;
}
/*#####################################################*/
void GI::Dev::Uart::printF(const char *pcString, ...)
{
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
			vsnprintf(tmp_str, len, pcString, args);
			va_end (args);
			print(tmp_str);
			free(tmp_str);
		}
	}
}
/*#####################################################*/
void GI::Dev::Uart::printF(GI::string *string, ...)
{
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
			vsnprintf(tmp_str, len, pcString, args);
			va_end (args);
			print(tmp_str);
			free(tmp_str);
		}
	}
}
/*#####################################################*/
int GI::Dev::Uart::print(const char *pcString)
{
	if(!this)
		return 0;
	unsigned int count = 0;

	while('\0' != *pcString)
	{
		putChar((char)*pcString);
		pcString++;
		count++;

	}
	return count;
}
/*#####################################################*/
int GI::Dev::Uart::print(GI::string *string)
{
	if(!this)
		return 0;
	unsigned int count = 0;
	char *pcString = string->buff;
	while('\0' != *pcString)
	{
		putChar((char)*pcString);
		pcString++;
		count++;

	}
	return count;
}
/*#####################################################*/
/*int GI::Dev::Uart::print(GI::Screen::String *string)
{
	if(!this)
		return 0;
	unsigned int count = 0;
	char *pcString = string->buff;
	while('\0' != *pcString)
	{
		putChar((char)*pcString);
		pcString++;
		count++;

	}
	return count;
}*/
/*#####################################################*/
int GI::Dev::Uart::write(char *data, unsigned int len)
{
#if USE_UART_TX_INTERRUPT == true
	if(!bytesLeft[this->unitNr])
	{
		nonblockingTxBuffPtr[this->unitNr] = (volatile unsigned char *)data;
		bytesLeft[this->unitNr] = len - 1;
		((FPGA_USART_t*)udata)->DATA = *nonblockingTxBuffPtr[this->unitNr]++;
		return len;
	}
	else
		return 0;
#else
	unsigned int len_cnt = len;
	while(len_cnt--)
	{
		putChar(*data++);
	}
	return len - len_cnt;
#endif
	return len;
}
/*#####################################################*/
void uartTx(volatile unsigned char *buff, FPGA_USART_t *instance, volatile unsigned int bytesLeft)
{
	if(buff)
	{
		instance->DATA = *buff;
	}
}
/*#####################################################*/
#if 0
#if USE_UART_TX_INTERRUPT == true
#ifdef FPGA_UARTA
ISR(UART_A_TXC_vect)
{
	if(!bytesLeft[0])
	{
		nonblockingTxBuffPtr[0] = NULL;
		return;
	}
	uartTx(nonblockingTxBuffPtr[0], &FPGA_UARTA, bytesLeft[0]);
	nonblockingTxBuffPtr[0]++;
	bytesLeft[0]--;
}
#endif

#ifdef FPGA_UARTB
ISR(UART_B_TXC_vect)
{
	if(!bytesLeft[1])
	{
		nonblockingTxBuffPtr[1] = NULL;
		return;
	}
	uartTx(nonblockingTxBuffPtr[1], &FPGA_UARTB, bytesLeft[1]);
	nonblockingTxBuffPtr[1]++;
	bytesLeft[1]--;
}
#endif

#ifdef FPGA_UARTC
ISR(UART_C_TXC_vect)
{
	if(!bytesLeft[2])
	{
		nonblockingTxBuffPtr[2] = NULL;
		return;
	}
	uartTx(nonblockingTxBuffPtr[2], &FPGA_UARTC, bytesLeft[2]);
	nonblockingTxBuffPtr[2]++;
	bytesLeft[2]--;
}
#endif

#ifdef FPGA_UARTD
ISR(UART_D_TXC_vect)
{
	if(!bytesLeft[3])
	{
		nonblockingTxBuffPtr[3] = NULL;
		return;
	}
	uartTx(nonblockingTxBuffPtr[3], &FPGA_UARTD, bytesLeft[3]);
	nonblockingTxBuffPtr[3]++;
	bytesLeft[3]--;
}
#endif

#ifdef FPGA_UARTE
ISR(UART_E_TXC_vect)
{
	if(!bytesLeft[4])
	{
		nonblockingTxBuffPtr[4] = NULL;
		return;
	}
	uartTx(nonblockingTxBuffPtr[4], &FPGA_UARTE, bytesLeft[4]);
	nonblockingTxBuffPtr[4]++;
	bytesLeft[4]--;
}
#endif

#ifdef FPGA_UARTF
ISR(UART_F_TXC_vect)
{
	if(!bytesLeft[5])
	{
		nonblockingTxBuffPtr[5] = NULL;
		return;
	}
	uartTx(nonblockingTxBuffPtr[5], &FPGA_UARTF, bytesLeft[5]);
	nonblockingTxBuffPtr[5]++;
	bytesLeft[5]--;
}
#endif

#ifdef FPGA_UARTG
ISR(UART_G_TXC_vect)
{
	if(!bytesLeft[6])
	{
		nonblockingTxBuffPtr[6] = NULL;
		return;
	}
	uartTx(nonblockingTxBuffPtr[6], &FPGA_UARTG, bytesLeft[6]);
	nonblockingTxBuffPtr[6]++;
	bytesLeft[6]--;
}
#endif

#ifdef FPGA_UARTH
ISR(UART_H_TXC_vect)
{
	if(!bytesLeft[7])
	{
		nonblockingTxBuffPtr[7] = NULL;
		return;
	}
	uartTx(nonblockingTxBuffPtr[7], &FPGA_UARTH, bytesLeft[7]);
	nonblockingTxBuffPtr[7]++;
	bytesLeft[7]--;
}
#endif
#endif
#endif
