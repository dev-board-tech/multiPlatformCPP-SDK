/*
 * bma250.cpp
 */

#include "bma250.h"

GI::Device::Sensor::Bma250::Bma250(char *hwPath)
{
    hwIo = new GI::IO(hwPath);
    unsigned long addr = BMA250_I2CADDR;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    setRange(BMA250_RANGE_16G);
    setBandwidth(BMA250_BW_7_81HZ);
}

GI::Device::Sensor::Bma250::~Bma250()
{

}

SysErr GI::Device::Sensor::Bma250::writeRegs(unsigned char* pBuffer,
        unsigned char WriteAddr, unsigned short NumByteToWrite)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned char *tmp_buff = (unsigned char *) malloc(NumByteToWrite + 1);
    if (!tmp_buff)
        return SYS_ERR_OUT_OF_MEMORY;
    tmp_buff[0] = WriteAddr;
    memcpy(tmp_buff + 1, pBuffer, NumByteToWrite);
    if (hwIo->write(tmp_buff, NumByteToWrite + 1) != (int)NumByteToWrite + 1)
    {
    	free(tmp_buff);
        return SYS_ERR_UNKNOWN;
    }
	free(tmp_buff);
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Bma250::readRegs(unsigned char* pBuffer,
        unsigned char ReadAddr, unsigned short NumByteToRead)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    ioCtlRwMsgs_t msg;
    ioCtlMsg_t msgs[2];
    msg.nMsgs = 2;
    msg.msgs = msgs;

    msgs[0].buff = &ReadAddr;
    msgs[0].len = 1;
    msgs[0].slaveAddr = hwIo->slaveAddr;
    msgs[1].buff = pBuffer;
    msgs[1].len = NumByteToRead;
    msgs[1].slaveAddr = hwIo->slaveAddr;
    if (hwIo->ctl(GI::IO::IO_CTL_WR, (u32 *) &msg) != SYS_ERR_OK)
        return SYS_ERR_INVALID_HANDLER;
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Bma250::read(signed short *X, signed short *Y, signed short *Z)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned char tmp_buff[6];
    SysErr err = readRegs(tmp_buff, BMA250_X_AXIS_LSB_REG, 6);
    if(err)
        return err;
    signed short X_tmp, Y_tmp, Z_tmp;
    X_tmp = tmp_buff[1] << 8;
    X_tmp |= tmp_buff[0];
    X_tmp >>= 6;
    Y_tmp = tmp_buff[3] << 8;
    Y_tmp |= tmp_buff[2];
    Y_tmp >>= 6;
    Z_tmp = tmp_buff[5] << 8;
    Z_tmp |= tmp_buff[4];
    Z_tmp >>= 6;
    *X = X_tmp;
    *Y = Y_tmp;
    *Z = Z_tmp;
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Bma250::read(float *temp)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned char tmp_temp;
    SysErr err = readRegs(&tmp_temp, BMA250_TEMP_RD_REG, 1);
    if(err)
        return err;
    *temp = (tmp_temp * 0.5) + 24.0;
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Bma250::setRange(GI::Device::Sensor::Bma250::range_e range)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned char tmp = (char)range;
    return writeRegs(&tmp, BMA250_RANGE_SEL_REG, 1);
}

SysErr GI::Device::Sensor::Bma250::setBandwidth(GI::Device::Sensor::Bma250::bandwidth_e bandwidth)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned char tmp = (char)bandwidth;
    return writeRegs(&tmp, BMA250_BW_SEL_REG, 1);
}



