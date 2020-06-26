/*
 * lps25hb.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: Work
 */

#include "lps25hb.h"

/*@todo: "Need to fix read temperature and pressure"*/

GI::Device::Sensor::Lps25hb::Lps25hb(char *hwPath, unsigned char sa)
{
    hwIo = new GI::IO(hwPath);
    this->sa = sa;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    if(setTempAvarage(LPS25HB_TEMP_AVARAGE_8) ||
    setPressAvarage(LPS25HB_PRESS_AVARAGE_16) ||
    setUpdateMode(LPS25HB_UPDATE_MODE_CONTINUOUS) ||
    setDataRate(LPS25HB_ODR_1HZ) ||
    setPowerDown(LPS25HB_PWR_DOWN_FALSE))
		err = SYS_ERR_UNKNOWN;
	else
		err = SYS_ERR_OK;
}

GI::Device::Sensor::Lps25hb::~Lps25hb()
{
    setPowerDown(LPS25HB_PWR_DOWN_TRUE);
}

SysErr GI::Device::Sensor::Lps25hb::probe()
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LPS25HB_WHO_AM_I, 1)) != SYS_ERR_OK)
    	return err;
    if(tmp != 0xBD)
    	return SYS_ERR_INVALID_DEVICE;
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Lps25hb::getRefPress(signed long *ref_press)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp[3];
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, tmp, LPS25HB_REF_P_XL, 3)) != SYS_ERR_OK)
    	return err;
    *ref_press = tmp[0] + (tmp[1] << 8) + ((unsigned long)tmp[2] << 16) + (tmp[2] & 0x80) ? 0xFF000000 : 0x00000000;
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Lps25hb::setRefPress(signed long ref_press)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp[3];
    tmp[0] = ref_press;
    tmp[1] = ref_press >> 8;
    tmp[2] = ref_press >> 16;
    return GI::Sensor::Common::writeRegs(hwIo, tmp, LPS25HB_REF_P_XL, 3);
}

SysErr GI::Device::Sensor::Lps25hb::setTempAvarage(GI::Device::Sensor::Lps25hb::temp_avarage_e temp_avarage)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LPS25HB_RES_CONF, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LPS25HB_TEMP_AVARAGE_MASK;
    tmp |= ((char)temp_avarage << 2) & LPS25HB_TEMP_AVARAGE_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LPS25HB_RES_CONF, 1);
}

SysErr GI::Device::Sensor::Lps25hb::setPressAvarage(GI::Device::Sensor::Lps25hb::press_avarage_e press_avarage)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LPS25HB_RES_CONF, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LPS25HB_PRESS_AVARAGE_MASK;
    tmp |= ((char)press_avarage) & LPS25HB_PRESS_AVARAGE_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LPS25HB_RES_CONF, 1);
}

SysErr GI::Device::Sensor::Lps25hb::setPowerDown(GI::Device::Sensor::Lps25hb::power_down_e power_down)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LPS25HB_CTRL_REG1, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LPS25HB_PWR_DOWN_MASK;
    tmp |= ((char)power_down << 7) & LPS25HB_PWR_DOWN_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LPS25HB_CTRL_REG1, 1);
}

SysErr GI::Device::Sensor::Lps25hb::setDataRate(GI::Device::Sensor::Lps25hb::data_rate_e data_rate)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LPS25HB_CTRL_REG1, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LPS25HB_ODR_MASK;
    tmp |= ((char)data_rate << 4) & LPS25HB_ODR_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LPS25HB_CTRL_REG1, 1);
}

SysErr GI::Device::Sensor::Lps25hb::setUpdateMode(GI::Device::Sensor::Lps25hb::update_mode_e update_mode)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LPS25HB_CTRL_REG1, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~LPS25HB_UPDATE_MODE_MASK;
    tmp |= ((char)update_mode << 2) & LPS25HB_UPDATE_MODE_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LPS25HB_CTRL_REG1, 1);
}

SysErr GI::Device::Sensor::Lps25hb::startOneShot()
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LPS25HB_CTRL_REG2, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~1;
    tmp |= 1;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, LPS25HB_CTRL_REG2, 1);
}

SysErr GI::Device::Sensor::Lps25hb::getTempDataReady(bool *status)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LPS25HB_STATUS_REG, 1)) != SYS_ERR_OK)
    	return err;
    if(tmp & 1)
    	*status = true;
    else
    	*status = false;
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Lps25hb::getPressDataReady(bool *status)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, LPS25HB_STATUS_REG, 1)) != SYS_ERR_OK)
    	return err;
    if(tmp & 2)
    	*status = true;
    else
    	*status = false;
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Lps25hb::readTemp(float *temperature)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp[2];
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, tmp, LPS25HB_STATUS_REG, 1)) != SYS_ERR_OK)
    	return err;
    if(~tmp[0] & (1 << 0))
    	return SYS_ERR_DATA_NOT_READY;
    if((err = GI::Sensor::Common::readRegs(hwIo, tmp, LPS25HB_TEMP_OUT_L, 1)) != SYS_ERR_OK)
    	return err;
    if((err = GI::Sensor::Common::readRegs(hwIo, tmp + 1, LPS25HB_TEMP_OUT_H, 1)) != SYS_ERR_OK)
    	return err;
    signed short tmpTemp = tmp[0] | (tmp[1] << 8);
    *temperature = 42.5f + (float)(tmpTemp) / 480.0;
    return SYS_ERR_OK;
}

SysErr GI::Device::Sensor::Lps25hb::readPress(float *pressure)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = LPS25HB_I2CADDR + sa;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp1;
    unsigned char tmp2;
    unsigned char tmp3;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp1, LPS25HB_STATUS_REG, 1)) != SYS_ERR_OK)
    	return err;
    if(~tmp1 & (1 << 1))
    	return SYS_ERR_DATA_NOT_READY;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp1, LPS25HB_PRESS_OUT_XL, 1)) != SYS_ERR_OK)
    	return err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp2, LPS25HB_PRESS_OUT_L, 1)) != SYS_ERR_OK)
    	return err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp3, LPS25HB_PRESS_OUT_H, 1)) != SYS_ERR_OK)
    	return err;
    *pressure = (tmp1 + (tmp2 << 8) + ((unsigned long)tmp3 << 16)) / 4096.0/* + ((tmp[2] & 0x80) ? 0xFF000000 : 0x00000000)*/;
    return SYS_ERR_OK;
}
