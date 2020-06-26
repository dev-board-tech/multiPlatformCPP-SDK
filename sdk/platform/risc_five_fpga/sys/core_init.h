/*
 * core_init.h
 *
 *  Created on: Jan 3, 2017
 *      Author: John Smith
 */

#ifndef CORE_INIT_H_
#define CORE_INIT_H_

#include "board.h"

extern unsigned long FCPU;
extern unsigned long PLL_REF_CLK;

namespace GI
{
namespace Sys
{
	class Clock {
	public:
		Clock();
		~Clock();
		static void setClk(unsigned long fCpu);
};
}
}


#endif /* NXP_KEAZ_SYS_CORE_INIT_H_ */
