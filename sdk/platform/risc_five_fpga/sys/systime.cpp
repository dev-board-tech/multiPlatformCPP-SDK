/*
 * sysdelay.c
 *
 * Created: 2/8/2013 10:53:14 PM
 *  Author: Iulian Gheorghiu
 */

#include "io_defs.h"
#include <sys/systime.h>
GI::Sys::Systime systime = GI::Sys::Systime();
//extern unsigned long FCPU;
#define _RTC_PERIOD		(CPU_FREQ / 1000)
/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
//volatile unsigned long long TimerTimeoutValue = 1;
volatile unsigned long long STimerCnt = 0;
//#####################################################
GI::Sys::Systime::Systime()
{
	FPGA_RTC.RTC_PERIOD = _RTC_PERIOD;
}

GI::Sys::Systime::~Systime()
{
	FPGA_RTC.RTC_PERIOD = 0;
}
//#####################################################
void GI::Sys::Systime::sysDelay(unsigned long long milliSec)
{
	unsigned long long time_to_tick = STimerCnt + milliSec;
	unsigned long long rtc_cnt_int;
	do
	{
		rtc_cnt_int = STimerCnt;
	} while (time_to_tick > rtc_cnt_int);
}
//#####################################################
#ifdef __cplusplus
 extern "C" {
#endif
int IRQHandler_RTC(unsigned int int_nr)
{
	STimerCnt ++;
	return 0;
}
#ifdef __cplusplus
}
#endif
