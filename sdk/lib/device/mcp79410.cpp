/*
 * mcp79410.cpp
 */

#include <stdlib.h>
#include <stdint.h>
#include "mcp79410.h"

GI::Device::Rtc::Mcp79410::Mcp79410(char *hwPath)
{
    hwIo = new GI::IO(hwPath);
    unsigned long addr = MCP73871_RTC;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    timeStr = new GI::string();
    unsigned char tmp_buff[4];
    if (readRegs(MCP73871_RTC_SecReg, tmp_buff, 4) == SYS_ERR_OK
            && (tmp_buff[0] & MCP73871_St_bm) == 0)
    {
        tmp_buff[0] |= MCP73871_St_bm;
        tmp_buff[3] |= MCP73871_VBatEn_bm;
        writeRegs(MCP73871_RTC_SecReg, tmp_buff, 4);
    }
}

GI::Device::Rtc::Mcp79410::~Mcp79410()
{
	if(!this)
		return;
    delete timeStr;
}

SysErr GI::Device::Rtc::Mcp79410::readRegs(unsigned char ReadAddr, unsigned char *pBuffer,
        							unsigned char NumByteToRead)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	hwIo->slaveAddr = MCP73871_RTC;
	return GI::Sensor::Common::readRegs(hwIo, pBuffer, ReadAddr, NumByteToRead);
}

SysErr GI::Device::Rtc::Mcp79410::writeRegs(unsigned char WriteAddr, unsigned char *pBuffer,
        							unsigned char NumByteToWrite)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	hwIo->slaveAddr = MCP73871_RTC;
    return GI::Sensor::Common::writeRegs(hwIo, pBuffer, WriteAddr, NumByteToWrite);
}

SysErr GI::Device::Rtc::Mcp79410::readRam(unsigned char ReadAddr, unsigned char *pBuffer,
        							unsigned char NumByteToRead)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	hwIo->slaveAddr = MCP73871_SRAM;
    return GI::Sensor::Common::readRegs(hwIo, pBuffer, ReadAddr + MCP73871_Sram_Start, NumByteToRead);
}

SysErr GI::Device::Rtc::Mcp79410::writeRam(unsigned char WriteAddr, unsigned char *pBuffer,
        							unsigned char NumByteToWrite)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	hwIo->slaveAddr = MCP73871_SRAM;
    return GI::Sensor::Common::writeRegs(hwIo, pBuffer, WriteAddr + MCP73871_Sram_Start, NumByteToWrite);
}

SysErr GI::Device::Rtc::Mcp79410::readEep(unsigned char ReadAddr, unsigned char *pBuffer,
									unsigned char NumByteToRead)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	hwIo->slaveAddr = MCP73871_EEP;
    return GI::Sensor::Common::readRegs(hwIo, pBuffer, ReadAddr + MCP73871_Eep_Start, NumByteToRead);
}

SysErr GI::Device::Rtc::Mcp79410::writeEep(unsigned char WriteAddr, unsigned char *pBuffer,
									unsigned char NumByteToWrite)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	hwIo->slaveAddr = MCP73871_EEP;
    return GI::Sensor::Common::writeRegs(hwIo, pBuffer, WriteAddr + MCP73871_Eep_Start, NumByteToWrite);
}

SysErr GI::Device::Rtc::Mcp79410::checkEepReady()
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned char tmp;
    return readEep(0, &tmp, 1);
}

unsigned char GI::Device::Rtc::Mcp79410::byteToBcd(unsigned char byte)
{
    uint8_t Tmp = 0;
    while (byte > 9)
        Tmp++;
    return ((Tmp << 4) | byte);
}

unsigned char GI::Device::Rtc::Mcp79410::bcdToByte(unsigned char bcd)
{
    return ((((bcd >> 4) & 0x0F) * 10) + (bcd & 0x0F));
}

SysErr GI::Device::Rtc::Mcp79410::writeRtc(unsigned char reg, unsigned char time)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned char tmp_reg = 0;
    SysErr err = SYS_ERR_OK;
    if ((err = readRegs(reg, &tmp_reg, 1)) != SYS_ERR_OK)
        return err;
    switch (reg)
    {
    case MCP73871_RTC_SecReg:
        tmp_reg = (tmp_reg & ~(MCP73871_Seconds_gm | MCP73871_10Seconds_gm))
                | (byteToBcd(time) & (MCP73871_Seconds_gm | MCP73871_10Seconds_gm));
        break;
    case MCP73871_RTC_MinReg:
        tmp_reg = (tmp_reg & ~(MCP73871_Minutes_gm | MCP73871_10Minutes_gm))
                | (byteToBcd(time) & (MCP73871_Minutes_gm | MCP73871_10Minutes_gm));
        break;
    case MCP73871_RTC_HourReg:
        tmp_reg = (tmp_reg & ~(MCP73871_Hours_gm | MCP73871_10Hours_gm))
                | (byteToBcd(time) & (MCP73871_Hours_gm | MCP73871_10Hours_gm));
        break;
    case MCP73871_RTC_DateReg:
        tmp_reg = (tmp_reg & ~(MCP73871_Date_gm | MCP73871_10Date_gm))
                | (byteToBcd(time) & (MCP73871_Date_gm | MCP73871_10Date_gm));
        break;
    case MCP73871_RTC_MonthReg:
        tmp_reg = (tmp_reg & ~(MCP73871_Month_gm | MCP73871_10Month_bm))
                | (byteToBcd(time) & (MCP73871_Month_gm | MCP73871_10Month_bm));
        break;
    case MCP73871_RTC_YearReg:
        tmp_reg = (tmp_reg & ~(MCP73871_Year_gm | MCP73871_10Year_gm))
                | (byteToBcd(time) & (MCP73871_Year_gm | MCP73871_10Year_gm));
        break;
    }
    if ((err = writeRegs(reg, &tmp_reg, 1)) != SYS_ERR_OK)
        return err;
    return err;
}

SysErr GI::Device::Rtc::Mcp79410::readRtc(unsigned char reg, unsigned char *time)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned char tmp_reg = 0;
    SysErr err = SYS_ERR_OK;
    if ((err = readRegs(reg, &tmp_reg, 1)) != SYS_ERR_OK)
        return err;
    switch (reg)
    {
    case MCP73871_RTC_SecReg:
        *time = bcdToByte(tmp_reg & (MCP73871_Seconds_gm | MCP73871_10Seconds_gm));
        break;
    case MCP73871_RTC_MinReg:
        *time = bcdToByte(tmp_reg & (MCP73871_Minutes_gm | MCP73871_10Minutes_gm));
        break;
    case MCP73871_RTC_HourReg:
        *time = bcdToByte(tmp_reg & (MCP73871_Hours_gm | MCP73871_10Hours_gm));
        break;
    case MCP73871_RTC_DateReg:
        *time = bcdToByte(tmp_reg & (MCP73871_Date_gm | MCP73871_10Date_gm));
        break;
    case MCP73871_RTC_MonthReg:
        *time = bcdToByte(tmp_reg & (MCP73871_Month_gm | MCP73871_10Month_bm));
        break;
    case MCP73871_RTC_YearReg:
        *time = bcdToByte(tmp_reg & (MCP73871_Year_gm | MCP73871_10Year_gm));
        break;
    }
    return err;
}
/*
 * Format can be "%02d:%02d:%02d-%02d:%02d:%04d" result = 01:01:01-01:01:2017 = Hour:Min:Sec-Day:Month:Year.
 * If a NULL is provided the result will be in the UP format.
 */
GI::string *GI::Device::Rtc::Mcp79410::readTime(char *format)
{
	if(!this)
		return NULL;
    if(!timeStr)
    {
    	return timeStr;
    }
	unsigned char tmp_buff[7];
    timeStr->clear();
    if (readRegs(MCP73871_RTC_SecReg, tmp_buff, 7) != SYS_ERR_OK)
    {
        return timeStr;
    }

    unsigned int sec = bcdToByte(tmp_buff[0] & (MCP73871_Seconds_gm | MCP73871_10Seconds_gm));
    unsigned int min = bcdToByte(tmp_buff[1] & (MCP73871_Minutes_gm | MCP73871_10Minutes_gm));
    unsigned int hour = bcdToByte(tmp_buff[2] & (MCP73871_Hours_gm | MCP73871_10Hours_gm));
    unsigned int date = bcdToByte(tmp_buff[4] & (MCP73871_Date_gm | MCP73871_10Date_gm));
    unsigned int month = bcdToByte(tmp_buff[5] & (MCP73871_Month_gm | MCP73871_10Month_bm));
    unsigned int year = bcdToByte(tmp_buff[6] & (MCP73871_Year_gm | MCP73871_10Year_gm));
    if(format)
        timeStr->setF(format, hour, min, sec, date, month, year);
    else
        timeStr->setF("%02d:%02d:%02d-%02d:%02d:%04d", hour, min, sec, date, month, year);
    return timeStr;
}
