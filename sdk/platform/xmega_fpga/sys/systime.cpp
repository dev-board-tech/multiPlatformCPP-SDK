/*
 * sysdelay.c
 *
 * Created: 2/8/2013 10:53:14 PM
 *  Author: XxXx
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <io_defs.h>
#include <sys/systime.h>
GI::Sys::Systime systime = GI::Sys::Systime();
//extern unsigned long FCPU;
#define RTC_PERIOD		(CPU_FREQ / 1000)
/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
//volatile unsigned long long TimerTimeoutValue = 1;
volatile unsigned long long STimerCnt = 0;
//#####################################################
GI::Sys::Systime::Systime()
{
	asm("sei");
	FPGA_RTC.RTC_PERIOD_BYTE3 = (unsigned char)(RTC_PERIOD >> 24);
	FPGA_RTC.RTC_PERIOD_BYTE2 = (unsigned char)(RTC_PERIOD >> 16);
	FPGA_RTC.RTC_PERIOD_BYTE1 = (unsigned char)(RTC_PERIOD >> 8);
	FPGA_RTC.RTC_PERIOD_BYTE0 = (unsigned char)RTC_PERIOD;
}

GI::Sys::Systime::~Systime()
{
	FPGA_RTC.RTC_PERIOD_BYTE3 = 0;
	FPGA_RTC.RTC_PERIOD_BYTE2 = 0;
	FPGA_RTC.RTC_PERIOD_BYTE1 = 0;
	FPGA_RTC.RTC_PERIOD_BYTE0 = 0;
}
//#####################################################
void GI::Sys::Systime::sysDelay(unsigned long long milliSec)
{
	unsigned long long time_to_tick = STimerCnt + milliSec;
	unsigned long long rtc_cnt_int;
	do
	{
		unsigned char tmp_sreg = FPGA_CPU_SREG;
		asm("cli");
		rtc_cnt_int = STimerCnt;
		FPGA_CPU_SREG = tmp_sreg;
	} while (time_to_tick > rtc_cnt_int);
}
//#####################################################
#ifdef __cplusplus
 extern "C" {
#endif
ISR(RTC_vect)
{
	STimerCnt ++;
	asm("wdr");
}
#ifdef __cplusplus
}
#endif
