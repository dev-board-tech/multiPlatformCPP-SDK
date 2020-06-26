/*
 * CLK.c
 *
 *  Created on: Sep 24, 2013
 *      Author: B46911
 */
#include <avr/io.h>
#include "core_init.h"
#include <sys/systime.h>
/**********************************************************************************************
* External objects
**********************************************************************************************/


/**********************************************************************************************
* Global variables
**********************************************************************************************/
unsigned long FCPU = CORE_CLOCK_DEFAULT;

/**********************************************************************************************
* Constants and macros
**********************************************************************************************/


/**********************************************************************************************
* Local types
**********************************************************************************************/


/**********************************************************************************************
* Local function prototypes
*********************************************************************************************/


/**********************************************************************************************
* Local variables
**********************************************************************************************/


/**********************************************************************************************
* Local functions
**********************************************************************************************/


static void SystemClock_Config(unsigned long int_osc_freq, unsigned long ext_osc_freq, unsigned long core_freq)
{

}

/**********************************************************************************************
* Global functions
**********************************************************************************************/

GI::Sys::Clock::Clock()
{
	
}

GI::Sys::Clock::~Clock()
{
	
}

void GI::Sys::Clock::setClk(unsigned long fCpu)
{
	
}
