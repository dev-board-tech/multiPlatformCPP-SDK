/*
 * i2c.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: John Smith
 */

#include <string.h>
#include <stdio.h>
#include <api/i2c.h>
#include "i2c.h"
#include <driver/i2c.h>
#include <sys/core_init.h>

extern CfgI2c i2cCfg[];

TWI_t* I2C_BASE_PTRS[] =
{
#ifdef TWIC
		&TWIC,
#else
		NULL,
#endif
#ifdef TWID
		&TWID,
#else
		NULL,
#endif
#ifdef TWIE
		&TWIE,
#else
		NULL,
#endif
#ifdef TWIF
		&TWIF,
#else
		NULL,
#endif
		};

//#####################################################
/**
 * @brief  Initializes peripherals used by the I2C EEPROM driver.
 * @param  None
 * @retval None
 */
GI::Dev::I2c::I2c(ioSettings *cfg)
{
	memset(this, 0, sizeof(*this));
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

	this->cfg = cfg;
	CfgI2c *int_cfg = (CfgI2c *)cfg->cfg;

	unsigned int baud = (FCPU / (int_cfg->speed * 2)) -5;
	if(baud > 255)
		baud = 255;
	((TWI_t*)udata)->MASTER.BAUD = baud;
	((TWI_t*)udata)->MASTER.CTRLA = TWI_MASTER_ENABLE_bm;
}
/*#####################################################*/
GI::Dev::I2c::~I2c()
{
	//I2C_Deinit((I2C_Type *)udata);
}

SysErr GI::Dev::I2c::WR(unsigned char addr, unsigned char *buff_send,
		unsigned int TransmitBytes, unsigned char *buff_receive,
		unsigned int ReceiveBytes)
{
	//TWI_t *pI2Cx = (TWI_t *)udata;
	uint8_t u8ErrorStatus = 0;
	if (!noSendWriteOnRead)
	{
	}
	if (!ReceiveBytes)
	{
		 return (SysErr)u8ErrorStatus;
	}
	else
	{
		return (SysErr)u8ErrorStatus;
	}
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

