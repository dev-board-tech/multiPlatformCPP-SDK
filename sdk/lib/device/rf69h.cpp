/*
 * rf69h.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: Work
 */

#include "rf69h.h"

GI::Device::Rf::Rf69h::Rf69h(char *spiPath, char *irqPinPath, center_freq_e centerFreq, u16 networkId, u8 nodeId)
{
	this->spiDevice = new GI::IO(spiPath);
	this->irqPin = new GI::IO(irqPinPath);

	const u8 CONFIG[][2] =
	{
	/* 0x01 */ { RF69_REG_OPMODE, RF69_OPMODE_SEQUENCER_ON | RF69_OPMODE_LISTEN_OFF | RF69_OPMODE_STANDBY },
	/* 0x02 */ { RF69_REG_DATAMODUL, RF69_DATAMODUL_DATAMODE_PACKET | RF69_DATAMODUL_MODULATIONTYPE_FSK | RF69_DATAMODUL_MODULATIONSHAPING_00 }, // no shaping
	/* 0x03 */ { RF69_REG_BITRATEMSB, RF69_BITRATEMSB_55555}, // default: 4.8 KBPS
	/* 0x04 */ { RF69_REG_BITRATELSB, RF69_BITRATELSB_55555},
	/* 0x05 */ { RF69_REG_FDEVMSB, RF69_FDEVMSB_50000}, // default: 5KHz, (FDEV + BitRate / 2 <= 500KHz)
	/* 0x06 */ { RF69_REG_FDEVLSB, RF69_FDEVLSB_50000},

	/* 0x07 */ { RF69_REG_FRFMSB, (u8)(centerFreq >> 16) },
	/* 0x08 */ { RF69_REG_FRFMID, (u8)(centerFreq >> 8) },
	/* 0x09 */ { RF69_REG_FRFLSB, (u8)(centerFreq) },

	// looks like PA1 and PA2 are not implemented on RFM69W, hence the max output power is 13dBm
	// +17dBm and +20dBm are possible on RFM69HW
	// +13dBm formula: Pout = -18 + OutputPower (with PA0 or PA1**)
	// +17dBm formula: Pout = -14 + OutputPower (with PA1 and PA2)**
	// +20dBm formula: Pout = -11 + OutputPower (with PA1 and PA2)** and high power PA settings (section 3.3.7 in datasheet)
	///* 0x11 */ { RF69_REG_PALEVEL, RF69_PALEVEL_PA0_ON | RF69_PALEVEL_PA1_OFF | RF69_PALEVEL_PA2_OFF | RF69_PALEVEL_OUTPUTPOWER_11111},
	///* 0x13 */ { RF69_REG_OCP, RF69_OCP_ON | RF69_OCP_TRIM_95 }, // over current protection (default is 95mA)

	// RXBW defaults are { RF69_REG_RXBW, RF69_RXBW_DCCFREQ_010 | RF69_RXBW_MANT_24 | RF69_RXBW_EXP_5} (RxBw: 10.4KHz)
	/* 0x19 */ { RF69_REG_RXBW, RF69_RXBW_DCCFREQ_010 | RF69_RXBW_MANT_16 | RF69_RXBW_EXP_2 }, // (BitRate < 2 * RxBw)
	//for BR-19200: /* 0x19 */ { RF69_REG_RXBW, RF69_RXBW_DCCFREQ_010 | RF69_RXBW_MANT_24 | RF69_RXBW_EXP_3 },
	/* 0x25 */ { RF69_REG_DIOMAPPING1, RF69_DIOMAPPING1_DIO0_01 }, // DIO0 is the only IRQ we're using
	/* 0x26 */ { RF69_REG_DIOMAPPING2, RF69_DIOMAPPING2_CLKOUT_OFF }, // DIO5 ClkOut disable for power saving
	/* 0x28 */ { RF69_REG_IRQFLAGS2, RF69_IRQFLAGS2_FIFOOVERRUN }, // writing to this bit ensures that the FIFO & status flags are reset
	/* 0x29 */ { RF69_REG_RSSITHRESH, 220 }, // must be set to dBm = (-Sensitivity / 2), default is 0xE4 = 228 so -114dBm
	///* 0x2D */ { RF69_REG_PREAMBLELSB, RF69_PREAMBLESIZE_LSB_VALUE } // default 3 preamble bytes 0xAAAAAA
	/* 0x2E */ { RF69_REG_SYNCCONFIG, RF69_SYNC_ON | RF69_SYNC_FIFOFILL_AUTO | RF69_SYNC_SIZE_2 | RF69_SYNC_TOL_0 },
	/* 0x2F */ { RF69_REG_SYNCVALUE1, (u8)networkId/*0x2D*/ }, // NETWORK ID      // attempt to make this compatible with sync1 byte of RFM12B lib
	/* 0x30 */ { RF69_REG_SYNCVALUE2, (u8)(networkId >> 8) }, // NETWORK ID
	/* 0x37 */ { RF69_REG_PACKETCONFIG1, RF69_PACKET1_FORMAT_VARIABLE | RF69_PACKET1_DCFREE_OFF | RF69_PACKET1_CRC_ON | RF69_PACKET1_CRCAUTOCLEAR_ON | RF69_PACKET1_ADRSFILTERING_OFF },
	/* 0x38 */ { RF69_REG_PAYLOADLENGTH, 66 }, // in variable length mode: the max frame size, not used in TX
	///* 0x39 */ { RF69_REG_NODEADRS, nodeID }, // turned off because we're not using address filtering
	/* 0x3C */ { RF69_REG_FIFOTHRESH, RF69_FIFOTHRESH_TXSTART_FIFONOTEMPTY | RF69_FIFOTHRESH_VALUE }, // TX on FIFO not empty
	/* 0x3D */ { RF69_REG_PACKETCONFIG2, RF69_PACKET2_RXRESTARTDELAY_2BITS | RF69_PACKET2_AUTORXRESTART_ON | RF69_PACKET2_AES_OFF }, // RXRESTARTDELAY must match transmitter PA ramp-down time (bitrate dependent)
	//for BR-19200: /* 0x3D */ { RF69_REG_PACKETCONFIG2, RF69_PACKET2_RXRESTARTDELAY_NONE | RF69_PACKET2_AUTORXRESTART_ON | RF69_PACKET2_AES_OFF }, // RXRESTARTDELAY must match transmitter PA ramp-down time (bitrate dependent)
	/* 0x6F */ { RF69_REG_TESTDAGC, RF69_DAGC_IMPROVED_LOWBETA0 }, // run DAGC continuously in RX mode for Fading Margin Improvement, recommended default for AfcLowBetaOn=0
	{255, 0}
	};
	SysErr err;
	u16 timeout = 1000;
	/* Probe if module is connected */
	u8 tmpCmd[2];
	tmpCmd[0] = RF69_REG_SYNCVALUE1;
	tmpCmd[1] = 0xAA;
	do {
		if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmpCmd[1], tmpCmd[0], 1)) != SYS_ERR_OK)
			return;
		if((err = GI::Sensor::Common::readRegs(spiDevice, &tmpCmd[1], tmpCmd[0], 1)) != SYS_ERR_OK)
			return;
	}while(tmpCmd[1] != 0xAA && timeout--);
	if(timeout == 0)
	{
		delete this->spiDevice;
		delete this->irqPin;
		this->spiDevice = NULL;
		this->irqPin = NULL;
		return;
	}
	timeout = 1000;
	tmpCmd[0] = RF69_REG_SYNCVALUE2;
	tmpCmd[1] = 0x55;
	do {
		if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmpCmd[1], tmpCmd[0], 1)) != SYS_ERR_OK)
			return;
		if((err = GI::Sensor::Common::readRegs(spiDevice, &tmpCmd[1], tmpCmd[0], 1)) != SYS_ERR_OK)
			return;
	}while(tmpCmd[1] != 0x55 && timeout--);

	if(timeout == 0)
	{
		delete this->spiDevice;
		delete this->irqPin;
		this->spiDevice = NULL;
		this->irqPin = NULL;
		return;
	}

	/* Setup the device */
	u8 cnt = 0;
	while(CONFIG[cnt][0] != 255)
	{
		tmpCmd[0] = CONFIG[cnt][0];
		tmpCmd[1] = CONFIG[cnt][1];
		if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmpCmd[1], tmpCmd[0], 1)) != SYS_ERR_OK)
			return;
	}
	address = nodeId;
}

GI::Device::Rf::Rf69h::~Rf69h()
{
	if(!this)
		return;
	u8 tmpCmd[2];
	tmpCmd[0] = RF69_REG_OPMODE;
	tmpCmd[1] = RF69_OPMODE_STANDBY;
	GI::Sensor::Common::writeRegs(spiDevice, &tmpCmd[1], tmpCmd[0], 1);
	if(this->irqPin)
		delete this->irqPin;
	if(this->spiDevice)
		delete this->spiDevice;
}

SysErr GI::Device::Rf::Rf69h::setFreq(u32 freqHz)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	mode_e oldMode = mode;
	SysErr err;
	if (oldMode == RF69_MODE_TX)
	{
		if((err = setMode(RF69_MODE_RX)) != SYS_ERR_OK)
			return err;
	}
	freqHz /= RF69_FSTEP;
	u8 tmp[3];
	tmp[0] = freqHz >> 16;
	tmp[1] = freqHz >> 8;
	tmp[2] = freqHz;
	if((err = GI::Sensor::Common::writeRegs(spiDevice, tmp, RF69_REG_FRFMSB, 3)) != SYS_ERR_OK)
		return err;
	if (oldMode == RF69_MODE_RX)
	{
		if((err = setMode(RF69_MODE_SYNTH)) != SYS_ERR_OK)
			return err;
	}
	if((err = setMode(oldMode)) != SYS_ERR_OK)
		return err;
    return SYS_ERR_OK;
}

SysErr GI::Device::Rf::Rf69h::getFreq(u32 *freqHz)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	u8 tmp[3];
	SysErr err;
	if((err = GI::Sensor::Common::readRegs(spiDevice, tmp, RF69_REG_FRFMSB, 3)) != SYS_ERR_OK)
		return err;
	*freqHz = RF69_FSTEP * (((u32) tmp[0] << 16) + ((u16) tmp[1] << 8) + tmp[0]);
    return SYS_ERR_OK;
}

SysErr GI::Device::Rf::Rf69h::setMode(mode_e newMode)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	u8 tmp = 0;
	SysErr err;
	if((err = GI::Sensor::Common::readRegs(spiDevice, &tmp, RF69_REG_OPMODE, 1)) != SYS_ERR_OK)
		return err;
	switch (newMode) {
	case RF69_MODE_TX:
		tmp = (tmp & 0xE3) | RF69_OPMODE_TRANSMITTER;
		if (isRFM69HW)
			setHighPwrRegs(true);
		break;
	case RF69_MODE_RX:
		tmp = (tmp & 0xE3) | RF69_OPMODE_RECEIVER;
		if (isRFM69HW)
			setHighPwrRegs(false);
		break;
	case RF69_MODE_SYNTH:
		tmp = (tmp & 0xE3) | RF69_OPMODE_SYNTHESIZER;
		break;
	case RF69_MODE_STANDBY:
		tmp = (tmp & 0xE3) | RF69_OPMODE_STANDBY;
		break;
	case RF69_MODE_SLEEP:
		tmp = (tmp & 0xE3) | RF69_OPMODE_SLEEP;
		break;
	default:
		return SYS_ERR_INVALID_COMMAND;
	}
	if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmp, RF69_REG_OPMODE, 1)) != SYS_ERR_OK)
		return err;
	// we are using packet mode, so this check is not really needed
	// but waiting for mode ready is necessary when going from sleep because the FIFO may not be immediately available from previous mode
	do {
		if((err = GI::Sensor::Common::readRegs(spiDevice, &tmp, RF69_REG_IRQFLAGS1, 1)) != SYS_ERR_OK)
			return err;
	}
	while (mode == RF69_MODE_SLEEP && (tmp & RF69_IRQFLAGS1_MODEREADY) == 0x00); // wait for ModeReady

	mode = newMode;
	return SYS_ERR_OK;
}

SysErr GI::Device::Rf::Rf69h::getMode(mode_e *mode)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	return SYS_ERR_NOT_IMPLEMENTED;
}

SysErr GI::Device::Rf::Rf69h::setModeSleep()
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	setMode(RF69_MODE_SLEEP);
	return SYS_ERR_OK;
}

SysErr GI::Device::Rf::Rf69h::setNetworkId(u16 networkId)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	SysErr err;
	u8 tmp[2];
	tmp[0] = networkId;
	tmp[1] = networkId >> 8;
	if((err = GI::Sensor::Common::writeRegs(spiDevice, tmp, RF69_REG_SYNCVALUE1, 2)) != SYS_ERR_OK)
		return err;
	return SYS_ERR_OK;
}

SysErr GI::Device::Rf::Rf69h::setAddress(u8 address)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	SysErr err;
	u8 tmp = address;
	if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmp, RF69_REG_NODEADRS, 1)) != SYS_ERR_OK)
		return err;
	this->address = address;
	return SYS_ERR_OK;
}

SysErr GI::Device::Rf::Rf69h::setPwrLevel(u8 level)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	SysErr err;
	u8 powerLevel = (level > 31 ? 31 : level);
	u8 tmp = 0;
	if((err = GI::Sensor::Common::readRegs(spiDevice, &tmp, RF69_REG_IRQFLAGS1, 1)) != SYS_ERR_OK)
		return err;
	tmp  &= 0xE0;
	tmp |= powerLevel;
	if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmp, RF69_REG_NODEADRS, 1)) != SYS_ERR_OK)
		return err;
	return SYS_ERR_OK;
}

SysErr GI::Device::Rf::Rf69h::canSend()
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	SysErr err;
	s8 rssi;
	if((err = readRssi(&rssi)) != SYS_ERR_OK)
		return err;

	if (mode == RF69_MODE_RX && PAYLOADLEN == 0 && rssi < CSMA_LIMIT) // if signal stronger than -100dBm is detected assume channel activity
	{
		setMode(RF69_MODE_STANDBY);
		return SYS_ERR_OK;
	}
	return SYS_ERR_BUSY;
}







// internal function
SysErr GI::Device::Rf::Rf69h::sendFrame(u8 addr, u8* buff, u8 len, bool requestACK, bool sendACK)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	SysErr err;
	u8 tmp = 0;
	setMode(RF69_MODE_STANDBY); // turn off receiver to prevent reception while filling fifo
	do {
		if((err = GI::Sensor::Common::readRegs(spiDevice, &tmp, RF69_REG_IRQFLAGS1, 1)) != SYS_ERR_OK)
			return err;
	}
	while ((tmp & RF69_IRQFLAGS1_MODEREADY) == 0x00); // wait for ModeReady
	tmp = RF69_DIOMAPPING1_DIO0_00;
	if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmp, RF69_REG_DIOMAPPING1, 1)) != SYS_ERR_OK)
		return err;

	if (len > RF69_MAX_DATA_LEN)
	len = RF69_MAX_DATA_LEN;

	// control byte
	u8 CTLbyte = 0x00;
	if (sendACK)
	CTLbyte = RFM69_CTL_SENDACK;
	else if (requestACK)
	CTLbyte = RFM69_CTL_REQACK;

	u8 tmpBuff[4 + RF69_MAX_DATA_LEN];
	tmpBuff[0] = len + 3;
	tmpBuff[1] = addr;
	tmpBuff[2] = address;
	tmpBuff[3] = CTLbyte;
	memcpy(tmpBuff + 4, buff, len);
	if((err = GI::Sensor::Common::writeRegs(spiDevice, tmpBuff, RF69_REG_FIFO | 0x80, 4 + len)) != SYS_ERR_OK)
		return err;

	// no need to wait for transmit mode to be ready since its handled by the radio
	if((err = setMode(RF69_MODE_TX)) != SYS_ERR_OK)
		return err;

	GI::Sys::Timer timeoutTimer = GI::Sys::Timer(RF69_TX_LIMIT_MS);
	timeoutTimer.enable(true);
	bool intPinState = false;
	do {
		irqPin->read(&intPinState);
	}
	while (intPinState == false && !timeoutTimer.tick()); // wait for DIO0 to turn HIGH signalling transmission finish
	//while (readReg(REG_IRQFLAGS2) & RF_IRQFLAGS2_PACKETSENT == 0x00); // wait for ModeReady
	return setMode(RF69_MODE_STANDBY);
}

SysErr GI::Device::Rf::Rf69h::receiveBegin() {
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	DATALEN = 0;
	SENDERID = 0;
	TARGETID = 0;
	PAYLOADLEN = 0;
	ACK_REQUESTED = 0;
	ACK_RECEIVED = 0;
	RSSI = 0;
	SysErr err;
	u8 tmp = 0;
	if((err = GI::Sensor::Common::readRegs(spiDevice, &tmp, RF69_REG_IRQFLAGS2, 1)) != SYS_ERR_OK)
		return err;
	if (tmp & RF69_IRQFLAGS2_PAYLOADREADY)
	{
		if((err = GI::Sensor::Common::readRegs(spiDevice, &tmp, RF69_REG_PACKETCONFIG2, 1)) != SYS_ERR_OK)
			return err;
		tmp  &= 0xFB;
		tmp |= RF69_PACKET2_RXRESTART;
		if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmp, RF69_REG_PACKETCONFIG2, 1)) != SYS_ERR_OK)
			return err;
	}
	tmp  = RF69_DIOMAPPING1_DIO0_01;
	if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmp, RF69_REG_DIOMAPPING1, 1)) != SYS_ERR_OK)
		return err;
	setMode(RF69_MODE_RX);
	return SYS_ERR_BUSY;
}

SysErr GI::Device::Rf::Rf69h::receiveDone() {
//ATOMIC_BLOCK(ATOMIC_FORCEON)
//{
	// XXX fix -- Need fix
	//noInterrupts(); // re-enabled in unselect() via setMode() or via receiveBegin()
	if (mode == RF69_MODE_RX && PAYLOADLEN > 0)
	{
		setMode(RF69_MODE_STANDBY); // enables interrupts
		return SYS_ERR_OK;
	}
	else if (mode == RF69_MODE_RX) // already in RX no payload yet
	{
		// XXX fix -- Need fix
		//interrupts(); // explicitly re-enable interrupts
		return SYS_ERR_BUSY;
	}
	receiveBegin();
	return SYS_ERR_BUSY;
//}
}

SysErr GI::Device::Rf::Rf69h::setHighPwrRegs(bool onOff)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	SysErr err;
	u8 tmp = onOff ? 0x5D : 0x55;
	if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmp, RF69_REG_TESTPA1, 1)) != SYS_ERR_OK)
		return err;
	tmp = onOff ? 0x7C : 0x70;
	if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmp, RF69_REG_TESTPA2, 1)) != SYS_ERR_OK)
		return err;
	return SYS_ERR_OK;
}


SysErr GI::Device::Rf::Rf69h::readRssi(s8 *rssi, bool forceTrigger)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	*rssi = 0;
	SysErr err;
	u8 tmp = 0;
	if (forceTrigger)
	{
		// RSSI trigger not needed if DAGC is in continuous mode
		tmp = RF69_RSSI_START;
		if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmp, RF69_REG_RSSICONFIG, 1)) != SYS_ERR_OK)
			return err;
		do {
			if((err = GI::Sensor::Common::readRegs(spiDevice, &tmp, RF69_REG_RSSICONFIG, 1)) != SYS_ERR_OK)
				return err;
		}
		while ((tmp & RF69_RSSI_DONE) == 0x00); // wait for RSSI_Ready
	}
	if((err = GI::Sensor::Common::readRegs(spiDevice, &tmp, RF69_REG_RSSIVALUE, 1)) != SYS_ERR_OK)
		return err;
	*rssi = -tmp;
	*rssi >>= 1;
	return SYS_ERR_OK;
}

SysErr GI::Device::Rf::Rf69h::send(u8 address, u8 *buff, u8 len, bool reqAck)
{
	if(!this)
		return SYS_ERR_INVALID_HANDLER;
	SysErr err;
	u8 tmp = 0;
	if((err = GI::Sensor::Common::readRegs(spiDevice, &tmp, RF69_REG_PACKETCONFIG2, 1)) != SYS_ERR_OK)
		return err;
	tmp &= 0xFB;
	tmp |= RF69_PACKET2_RXRESTART;
	if((err = GI::Sensor::Common::writeRegs(spiDevice, &tmp, RF69_REG_PACKETCONFIG2, 1)) != SYS_ERR_OK)
		return err;

	GI::Sys::Timer timeoutTimer = GI::Sys::Timer(RF69_CSMA_LIMIT_MS);
	timeoutTimer.enable(true);
	while(!canSend() && !timeoutTimer.tick())
	{
		receiveDone();
	}
	sendFrame(address, buff, len, reqAck, false);
	return SYS_ERR_OK;
}
