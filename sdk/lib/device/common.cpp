/*
 * common.cpp
 *
 *  Created on: Jan 22, 2018
 *      Author: Work
 */

#include "common.h"

SysErr GI::Sensor::Common::writeRegs(GI::IO *io, unsigned char* pBuffer,
        unsigned char WriteAddr, unsigned short NumByteToWrite)
{
	if(!io)
		return SYS_ERR_INVALID_HANDLER;
    unsigned char *tmp_buff = (unsigned char *) malloc(NumByteToWrite + 1);
    if (!tmp_buff)
        return SYS_ERR_OUT_OF_MEMORY;
    tmp_buff[0] = WriteAddr;
    memcpy(tmp_buff + 1, pBuffer, NumByteToWrite);
    if (io->write(tmp_buff, NumByteToWrite + 1) != (int)NumByteToWrite + 1)
    {
    	free(tmp_buff);
        return SYS_ERR_UNKNOWN;
    }
	free(tmp_buff);
    return SYS_ERR_OK;
}

SysErr GI::Sensor::Common::readRegs(GI::IO *io, unsigned char* pBuffer,
        unsigned char ReadAddr, unsigned short NumByteToRead)
{
	if(!io)
		return SYS_ERR_INVALID_HANDLER;
    ioCtlRwMsgs_t msg;
    ioCtlMsg_t msgs[2];
    msg.nMsgs = 2;
    msg.msgs = msgs;

    msgs[0].buff = &ReadAddr;
    msgs[0].len = 1;
    msgs[0].slaveAddr = io->slaveAddr;
    msgs[1].buff = pBuffer;
    msgs[1].len = NumByteToRead;
    msgs[1].slaveAddr = io->slaveAddr;
    if (io->ctl(GI::IO::IO_CTL_WR, (u32 *) &msg) != SYS_ERR_OK)
        return SYS_ERR_INVALID_HANDLER;
    return SYS_ERR_OK;
}




