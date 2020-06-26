/*
 * gpio.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: Iulian Gheorghiu
 */
#include <string.h>
#include "api/gpio.h"
#include "io_defs.h"

FPGA_PORT_t *GPIO_BASE_PTRS[] =
{
		&FPGA_PORTA
#ifdef FPGA_PORTB
		, &FPGA_PORTB
#else
		, NULL
#endif
#ifdef FPGA_PORTC
		, &FPGA_PORTC
#else
		, NULL
#endif
#ifdef FPGA_PORTD
		, &FPGA_PORTD
#else
		, NULL
#endif
#ifdef FPGA_PORTE
		, &FPGA_PORTE
#else
		, NULL
#endif
#ifdef FPGA_PORTF
		, &FPGA_PORTF
#else
		, NULL
#endif
#ifdef FPGA_PORTG
		, &FPGA_PORTG
#else
		, NULL
#endif
#ifdef FPGA_PORTH
		, &FPGA_PORTH
#else
		, NULL
#endif
#ifdef FPGA_PORTI
		, &FPGA_PORTI
#else
		, NULL
#endif
#ifdef FPGA_PORTJ
		, &FPGA_PORTJ
#else
		, NULL
#endif
#ifdef FPGA_PORTK
		, &FPGA_PORTK
#else
		, NULL
#endif
#ifdef FPGA_PORTL
		,&FPGA_PORTL
#else
		, NULL
#endif
#ifdef FPGA_PORTM
		,&FPGA_PORTM
#else
		, NULL
#endif
#ifdef FPGA_PORTN
		,&FPGA_PORTN
#else
		, NULL
#endif
#ifdef FPGA_PORTO
		,&FPGA_PORTO
#else
		, NULL
#endif
#ifdef FPGA_PORTP
		,&FPGA_PORTP
#else
		, NULL
#endif
#ifdef FPGA_PORTQ
		,&FPGA_PORTQ
#else
		, NULL
#endif
#ifdef FPGA_PORTR
		,&FPGA_PORTR
#else
		, NULL
#endif
};
/*#####################################################*/
GI::Dev::Gpio::Gpio(ioSettings *cfg)
{
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
	baseAddr = (void *)GPIO_BASE_PTRS[int_cfg->pin >> 5];
}

/*#####################################################*/
GI::Dev::Gpio::~Gpio()
{
	setMode(CfgGpio::GPIO_IN_FLOATING, multiPinMask);
}
/*#####################################################*/
SysErr GI::Dev::Gpio::setOut(unsigned int value)
{
	if (!this)
		return SYS_ERR_INVALID_HANDLER;
	CfgGpio *int_cfg = (CfgGpio *)cfg->cfg;
	volatile FPGA_PORT_t *BaseAddr = GPIO_BASE_PTRS[int_cfg->pin >> 5];
	if (int_cfg->multiPin)
	{
		BaseAddr->OUT = (BaseAddr->OUT & ~(int_cfg->pin % 32))
				| (value & (int_cfg->pin % 32));
	}
	else
	{
		unsigned int state = value;
		if (int_cfg->reverse)
			state = (~state) & 0x01;
		if (state)
			BaseAddr->OUTSET = (1 << (int_cfg->pin % 32));
		else
			BaseAddr->OUTCLR = (1 << (int_cfg->pin % 32));
	}
	return SYS_ERR_OK;
}
/*#####################################################*/
signed int GI::Dev::Gpio::in()
{
	if (!this)
		return -1;
	CfgGpio *int_cfg = (CfgGpio *)cfg->cfg;
	volatile FPGA_PORT_t *BaseAddr = GPIO_BASE_PTRS[int_cfg->pin >> 5];
	if (int_cfg->multiPin)
	{
		return BaseAddr->IN & (int_cfg->pin % 32);
	}
	else
	{
		if (int_cfg->reverse)
		{
			if(BaseAddr->IN & (1 << (int_cfg->pin % 32)))
				return false;
			else
				return true;
		}
		else
			return BaseAddr->IN & (1 << (int_cfg->pin % 32));
	}
}
/*#####################################################*/
SysErr GI::Dev::Gpio::getIn(unsigned long *value)
{
	if (!this)
		return SYS_ERR_INVALID_HANDLER;
	*value = (unsigned int)in();
	return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::Gpio::setMode(CfgGpio::gpioMode_e mode)
{
	if (!this)
		return SYS_ERR_INVALID_HANDLER;
	CfgGpio *int_cfg = (CfgGpio *)cfg->cfg;
	volatile FPGA_PORT_t *BaseAddr = GPIO_BASE_PTRS[int_cfg->pin >> 5];

	if(int_cfg->multiPin)
		return SYS_ERR_INVALID_COMMAND;
	multiPinMask = 1 << (int_cfg->pin % 32);
	
	register8_t *ctl_pin = &BaseAddr->PIN0CTRL;
	switch (mode)
	{
	case CfgGpio::GPIO_IN_FLOATING:
		ctl_pin[int_cfg->pin % 32] = FPGA_PORT_OPC_TOTEM_gc;
		BaseAddr->DIRCLR = (1 << (int_cfg->pin % 32));
		break;
	case CfgGpio::GPIO_OUT_PUSH_PULL:
		ctl_pin[int_cfg->pin % 32] = FPGA_PORT_OPC_TOTEM_gc;
		BaseAddr->DIRSET = (1 << (int_cfg->pin % 32));
		break;
	default:
		return SYS_ERR_INVALID_COMMAND;

	}
	return SYS_ERR_OK;
}
/*#####################################################*/
SysErr GI::Dev::Gpio::setMode(CfgGpio::gpioMode_e mode, unsigned int mask)
{
	if (!this)
		return SYS_ERR_INVALID_HANDLER;
	CfgGpio *int_cfg = (CfgGpio *)cfg->cfg;
	if(!int_cfg->multiPin)
		return SYS_ERR_INVALID_COMMAND;
	volatile FPGA_PORT_t *BaseAddr = GPIO_BASE_PTRS[int_cfg->pin >> 5];
    multiPinMask = mask;

    register8_t *ctl_pin = &BaseAddr->PIN0CTRL;
	unsigned int cnt_pins = 0;
	for(; cnt_pins < 32; cnt_pins++)
	{
		if(mask & (1 << (cnt_pins % 32)))
		{
			switch (mode)
			{
			case CfgGpio::GPIO_IN_FLOATING:
				ctl_pin[cnt_pins] = FPGA_PORT_OPC_TOTEM_gc;
				BaseAddr->DIRCLR = (1 << (int_cfg->pin % 32));
				break;
			case CfgGpio::GPIO_OUT_PUSH_PULL:
				ctl_pin[cnt_pins] = FPGA_PORT_OPC_TOTEM_gc;
				BaseAddr->DIRSET = (1 << (int_cfg->pin % 32));
				break;
			default:
				return SYS_ERR_INVALID_COMMAND;
			}
		}
	}
	return SYS_ERR_OK;
}
/*#####################################################*/
bool GI::Dev::Gpio::getState()
{
	return lastState;
}
/*#####################################################*/
void GI::Dev::Gpio::idle()
{
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


