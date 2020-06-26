/*
 *  lib/device/tps65217.c
 *
 *  Copyright (C) 2013  Iulian Gheorghiu <morgoth.creator@gmail.com>
 *
 *  This file is part of Multiplatform SDK.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#if 0
#include "sys/plat_properties.h"
//#if (defined USE_TPS65217) || (defined beaglebone)
#include "tps65217.h"
#include "../api/twi_api.h"
#include "include/hw/hw_tps65217.h"
#include "include/hw/hw_types.h"
#include <api/dev_request.h>
/*#####################################################*/
GI::Device::Pmic::Tps65217(char *i2cPath)
{
    hwIo = new GI::IO(hwPath);
    unsigned long addr = TPS65217_PMIC;
    hwIo->ctl(GI::IO::IO_CTL_SET_SLAVE_ADDR, &addr);
    unsigned char pmic_status = 0;
    unsigned char pmic_status = 0;

    read(TwiStruct, STATUS, &pmic_status);

    /* Increase USB current limit to 1300mA */
    write(TwiStruct, PROT_LEVEL_NONE, POWER_PATH, USB_INPUT_CUR_LIMIT_1300MA,
                       USB_INPUT_CUR_LIMIT_MASK);

    /* Set DCDC2 (MPU) voltage to 1.275V */
    v_core_update(TwiStruct, DEFDCDC2, DCDC_VOLT_SEL_1275MV);

    /* Set LDO3, LDO4 output voltage to 3.3V */
    write(TwiStruct, PROT_LEVEL_2, DEFLS1, LDO_VOLTAGE_OUT_3_3, LDO_MASK);


    write(TwiStruct, PROT_LEVEL_2, DEFLS2, LDO_VOLTAGE_OUT_3_3, LDO_MASK);
}
GI::Device::Pmic::~Tps65217()
{

}


GI::Sys::Pmic::readRegs(unsigned char ReadAddr, unsigned char *pBuffer,
                                    unsigned char NumByteToRead)
{
    if(!this)
        return SYS_ERR_INVALID_HANDLER;
    hwIo->slaveAddr = TPS65217_PMIC;
    return GI::Sensor::Common::readRegs(hwIo, pBuffer, ReadAddr, NumByteToRead);
}

GI::Sys::Pmic::writeRegs(unsigned char WriteAddr, unsigned char *pBuffer,
                                    unsigned char NumByteToWrite)
{
    if(!this)
        return SYS_ERR_INVALID_HANDLER;
    hwIo->slaveAddr = TPS65217_PMIC;
    return GI::Sensor::Common::writeRegs(hwIo, pBuffer, WriteAddr, NumByteToWrite);
}
/*#####################################################*/
/**
 * tps65217_reg_read() - Generic function that can read a TPS65217 register
 * @regOffset:          Source register address
 * @src_val:          Address of destination variable
 */
SysErr GI::Device::Pmic::Tps65217::read(unsigned char regOffset, unsigned char* dest)
{
    if(!this)
        return;
    /* Configure PMIC slave address */
	return readRegs(regOffset, dest, 1);
}
/*#####################################################*/
/**
 *  tps65217_reg_write() - Generic function that can write a TPS65217 PMIC
 *                         register or bit field regardless of protection
 *                         level.
 *
 *  @prot_level:        Register password protection.
 *                      use PROT_LEVEL_NONE, PROT_LEVEL_1, or PROT_LEVEL_2
 *  @regOffset:         Register address to write.
 *  @dest_val:          Value to write.
 *  @mask:              Bit mask (8 bits) to be applied.  Function will only
 *                      change bits that are set in the bit mask.
 *
 *  @return:            None.
 */
SysErr GI::Device::Pmic::Tps65217::write(unsigned char port_level, unsigned char regOffset,
                        unsigned char dest_val, unsigned char mask)
{
    if(!this)
        return;
    unsigned char read_val = 0;
    unsigned xor_reg = 0;
    unsigned char buff_send[2];

    if(mask != MASK_ALL_BITS)
    {
        readRegs(regOffset, &read_val, 1);
        read_val &= (~mask);
        read_val |= (dest_val & mask);
        dest_val = read_val;
    }

    if(port_level > 0)
    {
         xor_reg = regOffset ^ PASSWORD_UNLOCK;

         buff_send[0] = PASSWORD;
         buff_send[1] = xor_reg;
         writeRegs(regOffset, buff_send, 2);
    }

    buff_send[0] = regOffset;
    buff_send[1] = dest_val;
    writeRegs(regOffset, buff_send, 2);

    if(port_level == PROT_LEVEL_2)
    {
        buff_send[0] = PASSWORD;
        buff_send[1] = xor_reg;
        writeRegs(regOffset, buff_send, 2);

        buff_send[0] = regOffset;
        buff_send[1] = dest_val;
        writeRegs(regOffset, buff_send, 2);
    }
}
/*#####################################################*/
/**
 *  tps65217_voltage_update() - Controls output voltage setting for the DCDC1,
 *       DCDC2, or DCDC3 control registers in the PMIC.
 *
 *  @dc_cntrl_reg:      DCDC Control Register address.
 *                      Must be DEFDCDC1, DEFDCDC2, or DEFDCDC3.
 *  @volt_sel:          Register value to set.  See PMIC TRM for value set.
 *
 *  @return:            None.
 */
void v_core_update(unsigned char dc_cntrl_reg, unsigned char volt_sel)
{
    if(!this)
        return;
    /* set voltage level */
	write(TwiStruct, PROT_LEVEL_2, dc_cntrl_reg, volt_sel, MASK_ALL_BITS);

    /* set GO bit to initiate voltage transition */
	write(TwiStruct, PROT_LEVEL_2, DEFSLEW, DCDC_GO, DCDC_GO);
}
/*#####################################################*/
SysError wled_enable()
{
    if(!this)
        return;
    SysError status;
	if((status = write(TwiStruct, PROT_LEVEL_NONE, WLEDCTRL1, WLED_CURENT_SYNK_ENABLE_BITMASK | WLED_PWM_DIMMING_FREQ_200, 0xFF)) != SYS_ERR_OK)
	    return status;
	return write(TwiStruct, PROT_LEVEL_NONE, WLEDCTRL2, 80, 0xFF);
}
/*#####################################################*/
SysError wled_level( unsigned char level)
{
    if(!this)
        return;
	if(level > 100)
	    level = 100;
	return write(TwiStruct, PROT_LEVEL_NONE, WLEDCTRL2, level, 0xFF );
}
/*#####################################################*/
#endif


