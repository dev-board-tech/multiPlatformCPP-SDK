/*
 * gpio_interface.c
 *
 *  Created on: Dec 2, 2012
 *      Author: XxXx
 */
/*#####################################################*/
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "api/gpio.h"
#include "sys/gpio_definition.h"
#include "../pinmux/pin_mux_gpio.h"
#include "../clk/clk_gpio.h"
#include "driver/gpio_v2.h"
#include "driver/hw/hw_control_AM335x.h"
#include "driver/hw/soc_AM335x.h"
#include "driver/hw/hw_cm_wkup.h"
#include "driver/hw/hw_cm_per.h"
#include "driver/hw/hw_types.h"
/*#####################################################*/

_gpio_t *GET_GPIO_PORT_BASE_ADDR[] =
{
    &GPIO0,
    &GPIO1,
    &GPIO2,
    &GPIO3
};


/*#####################################################*/
GI::Dev::Gpio::Gpio(ioSettings *cfg)
{
    memset(this, 0, sizeof(*this));
    if(cfg->info.ioType != ioSettings::info_s::ioType_GPIO)
        return;
    this->cfg = cfg;
    CfgGpio *int_cfg = (CfgGpio *)cfg->cfg;
    if(!int_cfg->multiPin)
    {
        setMode(int_cfg->gpioMode);
        setOut(int_cfg->defValue);
    }
    pinNr = int_cfg->pin % 32;
    baseAddr = (void *)GET_GPIO_PORT_BASE_ADDR[int_cfg->pin >> 5];
    GPIOModuleClkConfig(int_cfg->pin >> 5);
    //GPIOModuleReset(int_cfg->pin >> 5);
    GPIOModuleEnable(int_cfg->pin >> 5);
}

/*#####################################################*/
GI::Dev::Gpio::~Gpio()
{
    if(!this)
        return;
    CfgGpio *int_cfg = (CfgGpio *)cfg->cfg;
    switch (int_cfg->pin >> 5)
    {
    case 0:
        gpio_mux_setup(0, int_cfg->pin % 32, 0, 0, 0, 0, 1);
        break;
    case 1:
        gpio_mux_setup(1, int_cfg->pin % 32, 0, 0, 0, 0, 1);
        break;
    case 2:
        gpio_mux_setup(2, int_cfg->pin % 32, 0, 0, 0, 0, 1);
        break;
    case 3:
        gpio_mux_setup(3, int_cfg->pin % 32, 0, 0, 0, 0, 1);
        break;
    }
}

/*#####################################################*/
/*#####################################################*/
SysErr GI::Dev::Gpio::setOut(unsigned int value)
{
    if(!this)
        return SYS_ERR_INVALID_HANDLER;
    CfgGpio *int_cfg = (CfgGpio *)cfg->cfg;
    _gpio_t *BaseAddr = GET_GPIO_PORT_BASE_ADDR[int_cfg->pin >> 5];
    if (int_cfg->multiPin)
    {
        HWREG((unsigned int)BaseAddr + GPIO_DATAOUT) = (HWREG((unsigned int *)BaseAddr + GPIO_DATAOUT) & ~multiPinMask)
                        | (value & multiPinMask);
    }
    else
    {
        unsigned int state = value;
        if (int_cfg->reverse)
            state = (~state) & 0x01;
        if (state)
            HWREG((unsigned int)BaseAddr + GPIO_SETDATAOUT) = 1 << (int_cfg->pin % 32);
        else
            HWREG((unsigned int)BaseAddr + GPIO_CLEARDATAOUT) = 1 << (int_cfg->pin % 32);
    }
    return SYS_ERR_OK;
}

void GI::Dev::Gpio::setOut(void *baseAddr, unsigned int mask, unsigned int pin_mask)
{
    if(!this)
        return;
    HWREG((unsigned int)baseAddr + GPIO_DATAOUT) = (HWREG((unsigned int)baseAddr + GPIO_DATAOUT) & ~mask) | ((pin_mask) & mask);
}

void GI::Dev::Gpio::setOut(void *baseAddr, unsigned int pin, bool value)
{
    if(!this)
        return;
    if(value)
        HWREG((unsigned int)baseAddr + GPIO_SETDATAOUT) =  1 << pin;
    else
        HWREG((unsigned int)baseAddr + GPIO_CLEARDATAOUT) = 1 << pin;
}

/*#####################################################*/
signed int GI::Dev::Gpio::in()
{
    if(!this)
        return false;
    CfgGpio *int_cfg = (CfgGpio *)cfg->cfg;
    _gpio_t *BaseAddr = GET_GPIO_PORT_BASE_ADDR[int_cfg->pin >> 5];
    if (int_cfg->multiPin)
    {
        return GPIOMultiplePinsRead((unsigned int)BaseAddr + GPIO_DATAIN, multiPinMask);
    }
    else
    {
        if (int_cfg->reverse)
        {
            if(GPIOMultiplePinsRead((unsigned int)BaseAddr, (unsigned short)(1 << (int_cfg->pin % 32))))
                return false;
            else
                return true;
        }
        else
            return GPIOMultiplePinsRead((unsigned int)BaseAddr, (unsigned short)(1 << (int_cfg->pin % 32)));
    }
}
/*#####################################################*/
SysErr GI::Dev::Gpio::getIn(unsigned long *value)
{
    if(!this)
        return SYS_ERR_INVALID_HANDLER;
    *value = (unsigned int)in();
    return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::Gpio::setMode(CfgGpio::gpioMode_e mode)
{
    if(!this)
        return SYS_ERR_INVALID_HANDLER;
    CfgGpio *int_cfg = (CfgGpio *)cfg->cfg;
    if(int_cfg->multiPin)
        return SYS_ERR_INVALID_COMMAND;
    _gpio_t *BaseAddr = GET_GPIO_PORT_BASE_ADDR[int_cfg->pin >> 5];
    multiPinMask = 1 << (int_cfg->pin % 32);
    unsigned char cnt = 0;
    unsigned int tmp = (int_cfg->pin % 32);
    if(int_cfg->multiPin)
    {
        for(; cnt < 32; cnt++)
        {
            if(tmp & 1)
            {
                if(mode != CfgGpio::GPIO_OUT_PUSH_PULL) {
                    gpio_mux_setup((int_cfg->pin >> 5), cnt, 7, 0, 0, 1, 1);
                    GPIODirModeSet((unsigned int)BaseAddr, cnt, GPIO_DIR_INPUT);
                    if(mode != CfgGpio::GPIO_IN_FLOATING) {
                        if(mode == CfgGpio::GPIO_IN_PULL_UP)
                            gpio_mux_setup((int_cfg->pin >> 5), cnt, 7, 1, 1, 1, 1);
                        else
                            gpio_mux_setup((int_cfg->pin >> 5), cnt, 7, 1, 0, 1, 1);
                    }
                }
                else {
                    gpio_mux_setup((int_cfg->pin >> 5), cnt, 7, 0, 0, 0, 1);
                    GPIODirModeSet((unsigned int)BaseAddr, cnt, GPIO_DIR_OUTPUT);
                }
            }
            tmp = tmp >> 1;
        }
    }
    else
    {
        if(mode != CfgGpio::GPIO_OUT_PUSH_PULL) {
            gpio_mux_setup((int_cfg->pin >> 5), (int_cfg->pin % 32), 7, 0, 0, 1, 1);
            GPIODirModeSet((unsigned int)BaseAddr, (int_cfg->pin % 32), GPIO_DIR_INPUT);
            if(mode != CfgGpio::GPIO_IN_FLOATING) {
                if(mode == CfgGpio::GPIO_IN_PULL_UP)
                    gpio_mux_setup((int_cfg->pin >> 5), (int_cfg->pin % 32), 7, 1, 1, 1, 1);
                else
                    gpio_mux_setup((int_cfg->pin >> 5), (int_cfg->pin % 32), 7, 1, 0, 1, 1);
            }
        }
        else {
            gpio_mux_setup((int_cfg->pin >> 5), (int_cfg->pin % 32), 7, 0, 0, 0, 1);
            GPIODirModeSet((unsigned int)BaseAddr, (int_cfg->pin % 32), GPIO_DIR_OUTPUT);
        }
    }
    return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::Gpio::setMode(CfgGpio::gpioMode_e mode, unsigned int mask)
{
    if(!this)
        return SYS_ERR_INVALID_HANDLER;
    CfgGpio *int_cfg = (CfgGpio *)cfg->cfg;
    if(int_cfg->multiPin)
        return SYS_ERR_INVALID_COMMAND;
    _gpio_t *BaseAddr = GET_GPIO_PORT_BASE_ADDR[int_cfg->pin >> 5];
    multiPinMask = mask;
    unsigned char cnt = 0;
    unsigned int tmp = mask;
    if(int_cfg->multiPin)
    {
        for(; cnt < 32; cnt++)
        {
            if(tmp & 1)
            {
                if(mode != CfgGpio::GPIO_OUT_PUSH_PULL) {
                    gpio_mux_setup((int_cfg->pin >> 5), cnt, 7, 0, 0, 1, 1);
                    GPIODirModeSet((unsigned int)BaseAddr, cnt, GPIO_DIR_INPUT);
                    if(mode != CfgGpio::GPIO_IN_FLOATING) {
                        if(mode == CfgGpio::GPIO_IN_PULL_UP)
                            gpio_mux_setup((int_cfg->pin >> 5), cnt, 7, 1, 1, 1, 1);
                        else
                            gpio_mux_setup((int_cfg->pin >> 5), cnt, 7, 1, 0, 1, 1);
                    }
                }
                else {
                    gpio_mux_setup((int_cfg->pin >> 5), cnt, 7, 0, 0, 0, 1);
                    GPIODirModeSet((unsigned int)BaseAddr, cnt, GPIO_DIR_OUTPUT);
                }
            }
            tmp = tmp >> 1;
        }
    }
    else
    {
        if(mode != CfgGpio::GPIO_OUT_PUSH_PULL) {
            gpio_mux_setup((int_cfg->pin >> 5), (int_cfg->pin % 32), 7, 0, 0, 1, 1);
            GPIODirModeSet((unsigned int)BaseAddr, (int_cfg->pin % 32), GPIO_DIR_INPUT);
            if(mode != CfgGpio::GPIO_IN_FLOATING) {
                if(mode == CfgGpio::GPIO_IN_PULL_UP)
                    gpio_mux_setup((int_cfg->pin >> 5), (int_cfg->pin % 32), 7, 1, 1, 1, 1);
                else
                    gpio_mux_setup((int_cfg->pin >> 5), (int_cfg->pin % 32), 7, 1, 0, 1, 1);
            }
        }
        else {
            gpio_mux_setup((int_cfg->pin >> 5), (int_cfg->pin % 32), 7, 0, 0, 0, 1);
            GPIODirModeSet((unsigned int)BaseAddr, (int_cfg->pin % 32), GPIO_DIR_OUTPUT);
        }
    }
    return SYS_ERR_OK;
}
/*#####################################################*/
bool GI::Dev::Gpio::getState()
{
    if(!this)
        return false;
    return lastState;
}
/*#####################################################*/
void GI::Dev::Gpio::idle()
{
    if(!this)
        return;
    if (in() == 0 && lastState == true)
    {
        lastState = false;
        events.stateDown = true;
        events.stateChanged = true;
        if (events.callback.onStateChanged)
            events.callback.onStateChanged(
                    events.callback.onStateChangedHandler, false);
        if (events.callback.onDown)
            events.callback.onDown(
                    events.callback.onDownHandler);
    }
    else if (in() != 0 && lastState == false)
    {
        lastState = true;
        events.stateUp = true;
        events.stateChanged = true;
        if (events.callback.onStateChanged)
            events.callback.onStateChanged(
                    events.callback.onStateChangedHandler, true);
        if (events.callback.onUp)
            events.callback.onUp(
                    events.callback.onUpHandler);
    }
}
/*#####################################################*/
