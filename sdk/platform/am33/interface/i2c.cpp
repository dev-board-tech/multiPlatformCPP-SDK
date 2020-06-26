/*
 * twi_interface.c
 *
 *  Created on: Dec 3, 2012
 *      Author: XxXx
 */
/*#####################################################*/
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "i2c.h"
#include "api/i2c.h"
#include "api/timer.h"
#include "aintc/aintc_twi.h"
#include "sys/twi_definition.h"
#include "pinmux/pin_mux_twi.h"
#include "clk/clk_twi.h"
#include "driver/hsi2c.h"

extern Twi_Int_Service_t Twi_Int_Service;

extern CfgI2c i2cCfg[];

i2c_t* I2C_BASE_PTRS[] =
{
    &I2C0,
    &I2C1,
    &I2C2,
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
    //I2C_ConfigType  sI2C_Config = {0};

    TWIModuleClkConfig(dev_nr);
    //if(TwiStruct == NULL) return NULL;
    //if(TwiStruct->UseInterrupt)I2CAINTCConfigure(TwiStruct);
    switch(dev_nr)
    {
    case 0:
        //Twi_Int_Service.Twi0 = int_cfg;
        pin_mux_twi0_sda(int_cfg->sda);
        pin_mux_twi0_scl(int_cfg->scl);
        break;
    case 1:
        //Twi_Int_Service.Twi1 = int_cfg;
        pin_mux_twi1_sda(int_cfg->sda);
        pin_mux_twi1_scl(int_cfg->scl);
        break;
    case 2:
        //Twi_Int_Service.Twi2 = int_cfg;
        pin_mux_twi2_sda(int_cfg->sda);
        pin_mux_twi2_scl(int_cfg->scl);
        break;
    }
    //I2CPinMuxSetup(TwiStruct->TwiNr);
    /* Put i2c in reset/disabled state */
    I2CMasterDisable((unsigned int)udata);

    //if(TwiStruct->UseInterrupt) I2CSoftReset(TwiStruct->BaseAddr);
    /* Disable auto Idle functionality */
    I2CAutoIdleDisable((unsigned int)udata);

    /* Configure i2c bus speed to 100khz */
    I2CMasterInitExpClk((unsigned int)udata, 48000000, 12000000, int_cfg->speed);

    /* Bring I2C out of reset */
    I2CMasterEnable((unsigned int)udata);
    while(!I2CSystemStatusGet((unsigned int)udata));
    err = SYS_ERR_OK;
}
/*#####################################################*/
GI::Dev::I2c::~I2c()
{
    if(!this)
        return;
    I2CMasterDisable((unsigned int)udata);
    TWIModuleClkUnConfig(unitNr);
    I2CAINTCUnConfigure(unitNr);
/*    switch(unitNr)
    {
    case 0:
        Twi_Int_Service.Twi0 = NULL;
        break;
    case 1:
        Twi_Int_Service.Twi1 = NULL;
        break;
    case 2:
        Twi_Int_Service.Twi2 = NULL;
        break;
    }*/
}
/*#####################################################*/
SysErr GI::Dev::I2c::WR(unsigned char addr, unsigned char *buff_send,
        unsigned int TransmitBytes, unsigned char *buff_receive,
        unsigned int ReceiveBytes)
{
    if(!this)
        return SYS_ERR_INVALID_HANDLER;
    /* Set i2c slave address */

    GI::Sys::Timer TimerBusyTimeout = GI::Sys::Timer(5);
    TimerBusyTimeout.enable(true);
    while(I2CMasterBusy((unsigned int)udata))
      {
          if(TimerBusyTimeout.tick()) {
                /*
                I2C_TypeDef I2CxBack;
                I2CxBack.CR1 = I2Cx->CR1;
                I2CxBack.CR2 = I2Cx->CR2;
                I2CxBack.OAR1 = I2Cx->OAR1;
                I2CxBack.OAR2 = I2Cx->OAR2;
                I2CxBack.CCR = I2Cx->CCR;
                I2CxBack.TRISE = I2Cx->TRISE;
                I2C_SoftwareResetCmd(sEE_I2C[TwiStruct->TwiNr], ENABLE);
                I2C_SoftwareResetCmd(sEE_I2C[TwiStruct->TwiNr], DISABLE);
                I2Cx->TRISE = I2CxBack.TRISE;
                I2Cx->CCR = I2CxBack.CCR;
                I2Cx->OAR2 = I2CxBack.OAR2;
                I2Cx->OAR1 = I2CxBack.OAR1;
                I2Cx->CR2 = I2CxBack.CR2;
                I2Cx->CR1 = I2CxBack.CR1;
                }
                */
                break;
            }
      }
    I2CMasterSlaveAddrSet((unsigned int)udata, addr);
    tCount = 0;
    rCount = 0;

    I2CSetDataCount((unsigned int)udata, TransmitBytes);

    CleanUpInterrupts(unitNr);

    I2CMasterControl((unsigned int)udata, I2C_CFG_MST_TX);

    I2CMasterStart((unsigned int)udata);

    TimerBusyTimeout.enable(true);
    while(I2CMasterBusBusy((unsigned int)udata) == 0) {
          if(TimerBusyTimeout.tick()) {
                return SYS_ERR_TIMEOUT;
          }
    }

    TimerBusyTimeout.enable(true);
    while((I2C_INT_TRANSMIT_READY == (I2CMasterIntRawStatus((unsigned int)udata) & I2C_INT_TRANSMIT_READY))
           && TransmitBytes--)
    {
        I2CMasterDataPut((unsigned int)udata, buff_send[tCount++]);

        I2CMasterIntClearEx((unsigned int)udata, I2C_INT_TRANSMIT_READY);
          if(TimerBusyTimeout.tick()) {
                return SYS_ERR_TIMEOUT;
          }
    }
    TimerBusyTimeout.enable(true);
    while(0 == (I2CMasterIntRawStatus((unsigned int)udata) & I2C_INT_ADRR_READY_ACESS)) {
          if(TimerBusyTimeout.tick()) {
                return SYS_ERR_TIMEOUT;
          }
    }

    I2CSetDataCount((unsigned int)udata, ReceiveBytes);

    CleanUpInterrupts(unitNr);

    I2CMasterControl((unsigned int)udata, I2C_CFG_MST_RX);

    I2CMasterStart((unsigned int)udata);

    TimerBusyTimeout.enable(true);
    while(I2CMasterBusBusy((unsigned int)udata) == 0) {
          if(TimerBusyTimeout.tick()) {
                return SYS_ERR_TIMEOUT;
          }
    }

    while((ReceiveBytes--))
    {
        TimerBusyTimeout.enable(true);
        while(0 == (I2CMasterIntRawStatus((unsigned int)udata) & I2C_INT_RECV_READY)) {
          if(TimerBusyTimeout.tick()) {
                return SYS_ERR_TIMEOUT;
          }
        }

        buff_receive[rCount++] = I2CMasterDataGet((unsigned int)udata);

        I2CMasterIntClearEx((unsigned int)udata, I2C_INT_RECV_READY);
    }

    I2CMasterStop((unsigned int)udata);

    TimerBusyTimeout.enable(true);
    while(0 == (I2CMasterIntRawStatus((unsigned int)udata) & I2C_INT_STOP_CONDITION)) {
          if(TimerBusyTimeout.tick()) {
                return SYS_ERR_TIMEOUT;
          }
    }

    I2CMasterIntClearEx((unsigned int)udata, I2C_INT_STOP_CONDITION);

    return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::I2c::writeRead(unsigned char addr, unsigned char *buffSend,
        unsigned int lenSend, unsigned char *buffReceive,
        unsigned int lenReceive)
{
    if(!this)
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
    if(!this)
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
    if(!this)
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


