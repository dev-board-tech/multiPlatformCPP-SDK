/*
 * core_init.c
 *
 *  Created on: Aug 3, 2012
 *      Author: XxXx
 */

#include "core_init.h"
//#include "api/cache_api.h"
//#include "api/gpio_api.h"
#include "driver/interrupt.h"
#include "mmu.h"
#include "cache.h"
#include "clk/clk_core.h"
#include "driver/hw/hw_types.h"
#include "driver/hw/hw_cm_per.h"
#include "driver/hw/hw_cm_dpll.h"
#include "driver/hw/hw_cm_wkup.h"
#include "driver/hw/soc_AM335x.h"
#include "driver/hw/hw_control_AM335x.h"
#include "driver/armv7a/cpu.h"
//#include "startup.c"

unsigned long FCPU = 1000000000;

inline void VfpEnable(void)
{
	asm("    MRC p15, #0, r1, c1, c0, #2\n\t" // r1 = Access Control Register
		    "    ORR r1, r1, #(0xf << 20)\n\t" // enable full access for p10,11
		    "    MCR p15, #0, r1, c1, c0, #2\n\t" // Access Control Register = r1
		    "    MOV r1, #0\n\t"
		    "    MCR p15, #0, r1, c7, c5, #4\n\t" // flush prefetch buffer because of FMXR below
		    "    MOV r0,#0x40000000\n\t"
		    "    FMXR FPEXC, r0\n\t"); // FPEXC = r0
}



inline void _core_init(void)
{
	//VfpEnable();
	//CPUSwitchToUserMode();
	MMUConfigAndEnable();
	//CacheEnable(CACHE_ICACHE);
	CacheEnable(CACHE_ALL);
	//EnableNeon();
	CP15BranchPredictionEnable();
	L3L4_init();
	//NeonEnable();

    /* Enable IRQ for ARM (in CPSR)*/
    IntMasterIRQEnable();
    IntAINTCInit();
    //STimer_Init();
}

