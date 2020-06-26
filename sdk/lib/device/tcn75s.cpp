/*
 * tcn75s.cpp
 *
 *  Created on: Jan 22, 2018
 *      Author: Work
 */

#include "tcn75s.h"

GI::Device::Sensor::Tcn75s::Tcn75s(char *hwPath, unsigned char subAddr)
{
	if(!hwPath)
		return;
    hwIo = new GI::IO(hwPath);
    this->subAddr = subAddr;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    setShutDown(TCN75S_SHUT_DOWN_ENABLE);
    setAdcResolution(TCN75S_ADC_RESOLUTION_0_0625GR);
    setOneShot(TCN75S_ONE_SHOT_DISABLE);
}

GI::Device::Sensor::Tcn75s::~Tcn75s()
{

}

SysErr GI::Device::Sensor::Tcn75s::setShutDown(GI::Device::Sensor::Tcn75s::shut_down_e shut_down)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~TCN75S_SHUT_DOWN_MASK;
    tmp |= ((char)shut_down << TCN75S_SHUT_DOWN_POSITION) & TCN75S_SHUT_DOWN_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, 1, 1);
}

SysErr GI::Device::Sensor::Tcn75s::getShutDown(GI::Device::Sensor::Tcn75s::shut_down_e *shut_down)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    *shut_down = (shut_down_e)((tmp & TCN75S_SHUT_DOWN_MASK) >> TCN75S_SHUT_DOWN_POSITION);
    return err;
}

SysErr GI::Device::Sensor::Tcn75s::setCompInt(GI::Device::Sensor::Tcn75s::comp_int_e comp_int)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~TCN75S_COMP_INT_MASK;
    tmp |= ((char)comp_int << TCN75S_COMP_INT_POSITION) & TCN75S_COMP_INT_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, 1, 1);
}

SysErr GI::Device::Sensor::Tcn75s::getCompInt(GI::Device::Sensor::Tcn75s::comp_int_e *comp_int)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    *comp_int = (comp_int_e)((tmp & TCN75S_COMP_INT_MASK) >> TCN75S_COMP_INT_POSITION);
    return err;
}

SysErr GI::Device::Sensor::Tcn75s::setAlertPolarity(GI::Device::Sensor::Tcn75s::alert_polarity_e alert_polarity)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~TCN75S_ALERT_POLARITY_MASK;
    tmp |= ((char)alert_polarity << TCN75S_ALERT_POLARITY_POSITION) & TCN75S_ALERT_POLARITY_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, 1, 1);
}

SysErr GI::Device::Sensor::Tcn75s::getAlertPolarity(GI::Device::Sensor::Tcn75s::alert_polarity_e *alert_polarity)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    *alert_polarity = (alert_polarity_e)((tmp & TCN75S_ALERT_POLARITY_MASK) >> TCN75S_ALERT_POLARITY_POSITION);
    return err;
}

SysErr GI::Device::Sensor::Tcn75s::setFaultQueue(GI::Device::Sensor::Tcn75s::fault_queue_e fault_queue)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~TCN75S_FAULT_QUEUE_MASK;
    tmp |= ((char)fault_queue << TCN75S_FAULT_QUEUE_POSITION) & TCN75S_FAULT_QUEUE_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, 1, 1);
}

SysErr GI::Device::Sensor::Tcn75s::getFaultQueue(GI::Device::Sensor::Tcn75s::fault_queue_e *fault_queue)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    *fault_queue = (fault_queue_e)((tmp & TCN75S_FAULT_QUEUE_MASK) >> TCN75S_FAULT_QUEUE_POSITION);
    return err;
}

SysErr GI::Device::Sensor::Tcn75s::setAdcResolution(GI::Device::Sensor::Tcn75s::adc_resolution_e adc_resolution)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~TCN75S_ADC_RESOLUTION_MASK;
    tmp |= ((char)adc_resolution << TCN75S_ADC_RESOLUTION_POSITION) & TCN75S_ADC_RESOLUTION_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, 1, 1);
}

SysErr GI::Device::Sensor::Tcn75s::getAdcResolution(GI::Device::Sensor::Tcn75s::adc_resolution_e *adc_resolution)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    *adc_resolution = (adc_resolution_e)((tmp & TCN75S_ADC_RESOLUTION_MASK) >> TCN75S_ADC_RESOLUTION_POSITION);
    return err;
}

SysErr GI::Device::Sensor::Tcn75s::setOneShot(GI::Device::Sensor::Tcn75s::one_shot_e one_shot)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    tmp &= ~TCN75S_ONE_SHOT_MASK;
    tmp |= ((char)one_shot << TCN75S_ONE_SHOT_POSITION) & TCN75S_ONE_SHOT_MASK;
    return GI::Sensor::Common::writeRegs(hwIo, &tmp, 1, 1);
}

SysErr GI::Device::Sensor::Tcn75s::getOneShot(GI::Device::Sensor::Tcn75s::one_shot_e *one_shot)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char tmp = 0;
    SysErr err;
    if((err = GI::Sensor::Common::readRegs(hwIo, &tmp, 1, 1)) != SYS_ERR_OK)
    	return err;
    *one_shot = (one_shot_e)((tmp & TCN75S_ONE_SHOT_MASK) >> TCN75S_ONE_SHOT_POSITION);
    return err;
}

SysErr GI::Device::Sensor::Tcn75s::startOneShot()
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	return setOneShot(TCN75S_ONE_SHOT_ENABLE);
}

SysErr GI::Device::Sensor::Tcn75s::readTemp(float *temperature)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
    unsigned long addr = TCN75S_I2CADDR + subAddr;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    SysErr err;
    one_shot_e one_shot;
    if((err = getOneShot(&one_shot)) != SYS_ERR_OK)
    	return err;
    if(one_shot == TCN75S_ONE_SHOT_ENABLE)
    	return SYS_ERR_BUSY;
    unsigned char tmp[2];
    if((err = GI::Sensor::Common::readRegs(hwIo, tmp, 0, 2)) != SYS_ERR_OK)
    	return err;
    *temperature = (float)tmp[0] + ((float)tmp[1] / 256.0);
    return err;
}

