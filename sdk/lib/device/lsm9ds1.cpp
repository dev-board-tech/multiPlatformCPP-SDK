/*
 * lsm9ds1.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: Work
 */

#include "lsm9ds1.h"

GI::Device::Sensor::Lsm9ds1::Lsm9ds1(char *hwPath, unsigned char sa0, unsigned char sa1)
{
    hwIo = new GI::IO(hwPath);
    this->sa0 = sa0;
    this->sa1 = sa1;
    unsigned long addr = LSM9DS1_ACCEL_GIR_I2CADDR + sa0;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    if(setScale(LSM9DS1_SCALE_2000) ||
    setBandwidth(LSM9DS1_BW_0) ||
    setDataRate(LSM9DS1_ODR_59_5HZ) ||
    setMagPerformance(LSM9DS1_MAG_PERFORMANCE_UHIGH) ||
    setMagDataRate(LSM9DS1_MAG_ODR_80HZ) ||
    setMagTempCompensation(LSM9DS1_MAG_TMP_COMP_ON) ||
    setMagScale(LSM9DS1_MAG_SCALE_4G) ||
    setMagOpMode(LSM9DS1_MAG_OP_MODE_CONTINUOUS))
		err = SYS_ERR_UNKNOWN;
	else
		err = SYS_ERR_OK;
}

GI::Device::Sensor::Lsm9ds1::~Lsm9ds1()
{
    setMagOpMode(LSM9DS1_MAG_OP_MODE_PWR_DOWN);
}

SysErr GI::Device::Sensor::Lsm9ds1::probe()
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_ACCEL_GIR_I2CADDR + sa0;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LSM9DS1_ACCEL_GIR_WHO_AM_I, 1)) != SYS_ERR_OK)
    	return err;
    if(tmp != 0x34)
    	return SYS_ERR_INVALID_DEVICE;
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Lsm9ds1::setScale(GI::Device::Sensor::Lsm9ds1::scale_e scale)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_ACCEL_GIR_I2CADDR + sa0;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LSM9DS1_ACCEL_GIR_CTRL_REG1_G, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LSM9DS1_SCALE_MASK;
    tmp |= ((char)scale << 3) & LSM9DS1_SCALE_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LSM9DS1_ACCEL_GIR_CTRL_REG1_G, 1);
}

SysErr GI::Device::Sensor::Lsm9ds1::setBandwidth(GI::Device::Sensor::Lsm9ds1::bandwidth_e bandwidth)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_ACCEL_GIR_I2CADDR + sa0;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LSM9DS1_ACCEL_GIR_CTRL_REG1_G, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LSM9DS1_BW_MASK;
    tmp |= ((char)bandwidth << 3) & LSM9DS1_BW_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LSM9DS1_ACCEL_GIR_CTRL_REG1_G, 1);
}

SysErr GI::Device::Sensor::Lsm9ds1::setDataRate(GI::Device::Sensor::Lsm9ds1::data_rate_e data_rate)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_ACCEL_GIR_I2CADDR + sa0;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LSM9DS1_ACCEL_GIR_CTRL_REG1_G, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LSM9DS1_ODR_PWR_MASK;
    tmp |= ((char)data_rate << 5) & LSM9DS1_ODR_PWR_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LSM9DS1_ACCEL_GIR_CTRL_REG1_G, 1);
}

SysErr GI::Device::Sensor::Lsm9ds1::readTemp(float *temperature)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_ACCEL_GIR_I2CADDR + sa0;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
	unsigned char tmp[2];
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, tmp, LSM9DS1_ACCEL_GIR_OUT_TEMP_L, 2)) != SYS_ERR_OK)
    	return err;
    signed char tmp1 = (tmp[1] << 4) | (tmp[0] >> 4);
    unsigned char tmp2 = (tmp[0] & 0x0F);
    *temperature = (float)tmp1 + (tmp2 / 16.0) + 25.0;
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Lsm9ds1::readAccel(signed short *X, signed short *Y, signed short *Z)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_ACCEL_GIR_I2CADDR + sa0;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
	unsigned char tmp[6];
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, tmp, LSM9DS1_ACCEL_GIR_OUT_X_L_XL, 6)) != SYS_ERR_OK)
    	return err;
    *X = tmp[0] | (tmp[1] << 8);
    *Y = tmp[2] | (tmp[3] << 8);
    *Z = tmp[4] | (tmp[5] << 8);
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Lsm9ds1::readGyro(signed short *X, signed short *Y, signed short *Z)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_ACCEL_GIR_I2CADDR + sa0;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
	unsigned char tmp[6];
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, tmp, LSM9DS1_ACCEL_GIR_OUT_X_L_G, 6)) != SYS_ERR_OK)
    	return err;
    *X = tmp[0] | (tmp[1] << 8);
    *Y = tmp[2] | (tmp[3] << 8);
    *Z = tmp[4] | (tmp[5] << 8);
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Lsm9ds1::setMagPerformance(GI::Device::Sensor::Lsm9ds1::mag_performance_e performance)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_MAG_I2CADDR + (sa1 << 1);
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LSM9DS1_MAG_CTRL_REG1_M, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LSM9DS1_MAG_PERFORMANCE_MASK;
    tmp |= ((char)performance << 5) & LSM9DS1_MAG_PERFORMANCE_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LSM9DS1_MAG_CTRL_REG1_M, 1);
}

SysErr GI::Device::Sensor::Lsm9ds1::setMagDataRate(GI::Device::Sensor::Lsm9ds1::mag_data_rate_e data_rate)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_MAG_I2CADDR + (sa1 << 1);
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LSM9DS1_MAG_CTRL_REG1_M, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LSM9DS1_MAG_ODR_PWR_MASK;
    tmp |= ((char)data_rate << 2) & LSM9DS1_MAG_ODR_PWR_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LSM9DS1_MAG_CTRL_REG1_M, 1);
}

SysErr GI::Device::Sensor::Lsm9ds1::setMagTempCompensation(GI::Device::Sensor::Lsm9ds1::mag_temp_compensation_e temp_compensation)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_MAG_I2CADDR + (sa1 << 1);
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LSM9DS1_MAG_CTRL_REG1_M, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LSM9DS1_MAG_TMP_COMP_MASK;
    tmp |= ((char)temp_compensation << 7) & LSM9DS1_MAG_TMP_COMP_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LSM9DS1_MAG_CTRL_REG1_M, 1);
}

SysErr GI::Device::Sensor::Lsm9ds1::setMagScale(GI::Device::Sensor::Lsm9ds1::mag_scale_e scale)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_MAG_I2CADDR + (sa1 << 1);
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LSM9DS1_MAG_CTRL_REG2_M, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LSM9DS1_MAG_SCALE_MASK;
    tmp |= ((char)scale << 5) & LSM9DS1_MAG_SCALE_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LSM9DS1_MAG_CTRL_REG2_M, 1);
}

SysErr GI::Device::Sensor::Lsm9ds1::setMagOpMode(GI::Device::Sensor::Lsm9ds1::mag_op_mode_e op_mode)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_MAG_I2CADDR + (sa1 << 1);
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LSM9DS1_MAG_CTRL_REG3_M, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LSM9DS1_MAG_OP_MODE_MASK;
    tmp |= ((char)op_mode) & LSM9DS1_MAG_OP_MODE_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LSM9DS1_MAG_CTRL_REG3_M, 1);
}

SysErr GI::Device::Sensor::Lsm9ds1::setMagOffset(signed short X, signed short Y, signed short Z)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_MAG_I2CADDR + (sa1 << 1);
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
	unsigned char tmp[6];
	tmp[0] = X;
	tmp[1] = X >> 8;
	tmp[0] = Y;
	tmp[1] = Y >> 8;
	tmp[0] = Z;
	tmp[1] = Z >> 8;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, tmp, LSM9DS1_MAG_OUT_X_L_M, 6)) != SYS_ERR_OK)
    	return err;
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Lsm9ds1::readMag(signed short *X, signed short *Y, signed short *Z)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LSM9DS1_MAG_I2CADDR + (sa1 << 1);
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
	unsigned char tmp[6];
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, tmp, LSM9DS1_MAG_OUT_X_L_M, 6)) != SYS_ERR_OK)
    	return err;
    *X = tmp[0] | (tmp[1] << 8);
    *Y = tmp[2] | (tmp[3] << 8);
    *Z = tmp[4] | (tmp[5] << 8);
    return SYS_ERR_OK;
}


