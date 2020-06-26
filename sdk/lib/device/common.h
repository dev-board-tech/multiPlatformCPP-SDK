/*
 * common.h
 *
 *  Created on: Jan 22, 2018
 *      Author: Work
 */

#ifndef LIB_DEVICE_COMMON_H_
#define LIB_DEVICE_COMMON_H_
/*#####################################################*/
#include <include/global.h>
#include <api/io_handle.h>
/*#####################################################*/
namespace GI {
namespace Sensor {
class Common
{
public:
	static SysErr writeRegs(GI::IO *io, unsigned char* pBuffer,
	        unsigned char WriteAddr, unsigned short NumByteToWrite);
	static SysErr readRegs(GI::IO *io, unsigned char* pBuffer,
	        unsigned char ReadAddr, unsigned short NumByteToRead);
};
}
}
/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "common.cpp"
#endif
/*#####################################################*/
#endif /* LIB_DEVICE_COMMON_H_ */
