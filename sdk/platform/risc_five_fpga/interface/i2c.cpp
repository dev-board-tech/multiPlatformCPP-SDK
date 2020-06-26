/*
 * i2c.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: John Smith
 */

#include <string.h>
#include <stdio.h>
#include "api/i2c.h"
#include "i2c.h"
#include <driver/i2c.h>
#include <io_defs.h>


volatile FPGA_TWI_t* I2C_BASE_PTRS[] =
{
#ifdef FPGA_TWIA
		&FPGA_TWIA,
#else
		NULL,
#endif
#ifdef FPGA_TWIB
		&FPGA_TWIB,
#else
		NULL,
#endif
#ifdef FPGA_TWIC
		&FPGA_TWIC,
#else
		NULL,
#endif
#ifdef FPGA_TWID
		&FPGA_TWID,
#else
		NULL,
#endif
		};
extern unsigned long FCPU;

//#####################################################
/**
 * @brief  Initializes peripherals used by the I2C EEPROM driver.
 * @param  None
 * @retval None
 */
GI::Dev::I2c::I2c(ioSettings *cfg):
		noSendWriteOnRead(false),
		bytesToRead(0),
		cfg(NULL),
		BusyTimeOut(100),
		bytesToWrite(0),
		tCount(0),
		numOfBytes(0),
		rCount(0)
{
	if(cfg->info.ioType != ioSettings::info_s::ioType_I2C)
		return;

	if(strncmp(cfg->info.name, (char *)"i2c-", sizeof("i2c-") - 1))
	{
		err = SYS_ERR_INVALID_PATH;
		return;
	}
	unsigned int dev_nr = 0;
	if(sscanf(cfg->info.name + (sizeof("i2c-") - 1), "%u", &dev_nr) != 1)
	{
		err = SYS_ERR_INVALID_PATH;
		return;
	}
	if(dev_nr >= TWI_INTERFACE_COUNT)
	{
		err = SYS_ERR_INVALID_PATH;
		return;
	}


	udata = (void *) I2C_BASE_PTRS[dev_nr];
	unitNr = dev_nr;

	CfgI2c *int_cfg = (CfgI2c *)cfg->cfg;

	unsigned int baud = (FCPU / (int_cfg->speed * 2)) - 1;
	if(baud > 255)
		baud = 255;
	((FPGA_TWI_t*)udata)->MASTER.BAUD = baud;
	((FPGA_TWI_t*)udata)->MASTER.CTRLA = FPGA_TWI_MASTER_ENABLE_bm;
}
/*#####################################################*/
GI::Dev::I2c::~I2c()
{
	((FPGA_TWI_t*)udata)->MASTER.CTRLA &= ~FPGA_TWI_MASTER_ENABLE_bm;
}

SysErr GI::Dev::I2c::WR(unsigned char addr, unsigned char *buff_send,
		unsigned int TransmitBytes, unsigned char *buff_receive,
		unsigned int ReceiveBytes)
{
	uint8_t u8ErrorStatus = 0;
	unsigned int cnt_bytes;
	if(TransmitBytes)
	{
		((FPGA_TWI_t*)udata)->MASTER.DATA = addr;
		while ((((FPGA_TWI_t*)udata)->MASTER.STATUS & FPGA_TWI_MASTER_WIF_bm) == 0);
		if(((FPGA_TWI_t*)udata)->MASTER.STATUS & FPGA_TWI_MASTER_RXACK_bm)
		{
			((FPGA_TWI_t*)udata)->MASTER.CTRLC = FPGA_TWI_MASTER_CMD_STOP_gc;
			while ((((FPGA_TWI_t*)udata)->MASTER.CTRLC & FPGA_TWI_MASTER_CMD_gm) != 0);
			return SYS_ERR_NAK;
		}
		for(cnt_bytes = 0; cnt_bytes < TransmitBytes; cnt_bytes++)
		{
			((FPGA_TWI_t*)udata)->MASTER.DATA = *buff_send++;
			while ((((FPGA_TWI_t*)udata)->MASTER.STATUS & FPGA_TWI_MASTER_WIF_bm) == 0);
			if(((FPGA_TWI_t*)udata)->MASTER.STATUS & FPGA_TWI_MASTER_RXACK_bm)
			{
				((FPGA_TWI_t*)udata)->MASTER.CTRLC = FPGA_TWI_MASTER_CMD_STOP_gc;
				while ((((FPGA_TWI_t*)udata)->MASTER.CTRLC & FPGA_TWI_MASTER_CMD_gm) != 0);
				return SYS_ERR_NAK;
			}
		}
	}
	if(ReceiveBytes)
	{
		if(TransmitBytes)
		{
			((FPGA_TWI_t*)udata)->MASTER.CTRLC = FPGA_TWI_MASTER_CMD_REPSTART_gc;
			while ((((FPGA_TWI_t*)udata)->MASTER.CTRLC & FPGA_TWI_MASTER_CMD_gm) != 0);
		}
		((FPGA_TWI_t*)udata)->MASTER.DATA = addr | 0x01;
		unsigned char tmp_status;
		while ((((FPGA_TWI_t*)udata)->MASTER.STATUS & FPGA_TWI_MASTER_WIF_bm) == 0);
		if(((FPGA_TWI_t*)udata)->MASTER.STATUS & FPGA_TWI_MASTER_RXACK_bm)
		{
			((FPGA_TWI_t*)udata)->MASTER.CTRLC = FPGA_TWI_MASTER_CMD_STOP_gc;
			while ((((FPGA_TWI_t*)udata)->MASTER.CTRLC & FPGA_TWI_MASTER_CMD_gm) != 0);
			return SYS_ERR_NAK;
		}
		for(cnt_bytes = 0; cnt_bytes < ReceiveBytes; cnt_bytes++)
		{
			unsigned char tmp_status;
			((FPGA_TWI_t*)udata)->MASTER.CTRLC = FPGA_TWI_MASTER_CMD_RECVTRANS_gc | ((cnt_bytes == ReceiveBytes - 1) ? FPGA_TWI_MASTER_ACKACT_bm : 0 );
			while ((((FPGA_TWI_t*)udata)->MASTER.STATUS & FPGA_TWI_MASTER_RIF_bm) == 0);
			*buff_receive++ = ((FPGA_TWI_t*)udata)->MASTER.DATA;
		}
	}
	((FPGA_TWI_t*)udata)->MASTER.CTRLC = FPGA_TWI_MASTER_CMD_STOP_gc;
	while ((((FPGA_TWI_t*)udata)->MASTER.CTRLC & FPGA_TWI_MASTER_CMD_gm) != 0);
	return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::I2c::writeRead(unsigned char addr, unsigned char *buffSend,
		unsigned int lenSend, unsigned char *buffReceive,
		unsigned int lenReceive)
{
	if (!this)
		return SYS_ERR_INVALID_HANDLER;
#if (USE_DRIVER_SEMAPHORE == true)
	while (twi_semaphore[unitNr]);
	twi_semaphore[unitNr] = true;
#endif
	SysErr result = WR(addr << 1, buffSend, lenSend, buffReceive, lenReceive);

#if (USE_DRIVER_SEMAPHORE == true)
	twi_semaphore[unitNr] = false;
#endif
	if (result == SYS_ERR_OK)
		return SYS_ERR_OK;
	else
		return SYS_ERR_NAK;
}
/*#####################################################*/
int GI::Dev::I2c::readBytes(unsigned char addr, unsigned char *buff, unsigned int len)
{
	if (!this)
		return SYS_ERR_INVALID_HANDLER;
#if (USE_DRIVER_SEMAPHORE == true)
	while (twi_semaphore[unitNr])
		;
	twi_semaphore[unitNr] = true;
#endif
	SysErr result = WR(addr << 1, NULL, 0, buff, len);
#if (USE_DRIVER_SEMAPHORE == true)
	twi_semaphore[unitNr] = false;
#endif
	if (result == SYS_ERR_OK)
		return len;
	else
		return SYS_ERR_NAK;
}

/*#####################################################*/
int GI::Dev::I2c::writeBytes(unsigned char addr, unsigned char *buff, unsigned int len)
{
	if (!this)
		return SYS_ERR_INVALID_HANDLER;
#if (USE_DRIVER_SEMAPHORE == true)
	while (twi_semaphore[unitNr])
		;
	twi_semaphore[unitNr] = true;
#endif
	SysErr result = WR(addr << 1, buff, len, NULL, 0);
#if (USE_DRIVER_SEMAPHORE == true)
	twi_semaphore[unitNr] = false;
#endif
	if (result == SYS_ERR_OK)
		return len;
	else
		return SYS_ERR_NAK;
}

/*#####################################################*/

