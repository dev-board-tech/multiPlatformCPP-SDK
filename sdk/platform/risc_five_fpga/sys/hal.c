/*
 * sysdelay.c
 *
 * Created: 2/8/2013 10:53:14 PM
 *  Author: Iulian Gheorghiu
 */
#include <stdint.h>
#include "hal.h"
#include "io_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
// Macro for weak symbol aliasing
//
//*****************************************************************************
extern int IRQHandler_RTC(unsigned int int_nr);
extern int (* const intVectors[])(unsigned int);

ISR(IRQHandler)
{
	asm volatile
	(
		"addi sp, sp, -33*4" "\n\t"
		"sw	x1,2*4(sp)" "\n\t"
		"sw	x2,3*4(sp)" "\n\t"
		"sw	x3,4*4(sp)" "\n\t"
		"sw	x4,5*4(sp)" "\n\t"
		"sw	x5,6*4(sp)" "\n\t"
		"sw	x6,7*4(sp)" "\n\t"
		"sw	x7,8*4(sp)" "\n\t"
		"sw	x8,9*4(sp)" "\n\t"
		"sw	x9,10*4(sp)" "\n\t"
		"sw	x10,11*4(sp)" "\n\t"
		"sw	x11,12*4(sp)" "\n\t"
		"sw	x12,13*4(sp)" "\n\t"
		"sw	x13,14*4(sp)" "\n\t"
		"sw	x14,15*4(sp)" "\n\t"
		"sw	x15,16*4(sp)" "\n\t"
		"sw	x16,17*4(sp)" "\n\t"
		"sw	x17,18*4(sp)" "\n\t"
		"sw	x18,19*4(sp)" "\n\t"
		"sw	x19,20*4(sp)" "\n\t"
		"sw	x20,21*4(sp)" "\n\t"
		"sw	x21,22*4(sp)" "\n\t"
		"sw	x22,23*4(sp)" "\n\t"
		"sw	x23,24*4(sp)" "\n\t"
		"sw	x24,25*4(sp)" "\n\t"
		"sw	x25,26*4(sp)" "\n\t"
		"sw	x26,27*4(sp)" "\n\t"
		"sw	x27,28*4(sp)" "\n\t"
		"sw	x28,29*4(sp)" "\n\t"
		"sw x29,30*4(sp)" "\n\t"
		"sw	x30,31*4(sp)" "\n\t"
		"sw	x31,32*4(sp)" "\n\t"
		"sw	x0,1*4(sp)" "\n\t"	/* Store Interrupt number*/
		"sw	x0,0*4(sp)" "\n\t"	/* Store return address*/
		/*"xor t0, t0, t0" "\n\t"
		"xor t1, t1, t1" "\n\t"
		"xor t2, t2, t2" "\n\t"
		"xor s0, s0, s0" "\n\t"
		"xor s1, s1, s1" "\n\t"
		"xor a0, a0, a0" "\n\t"
		"xor a1, a1, a1" "\n\t"
		"xor a2, a2, a2" "\n\t"
		"xor a3, a3, a3" "\n\t"
		"xor a4, a4, a4" "\n\t"
		"xor a5, a5, a5" "\n\t"
		"xor a6, a6, a6" "\n\t"
		"xor a7, a7, a7" "\n\t"
		"xor s2, s2, s2" "\n\t"
		"xor s3, s3, s3" "\n\t"
		"xor a0, a0, a0" "\n\t"
		"xor s4, s4, s4" "\n\t"
		"xor s5, s5, s5" "\n\t"
		"xor s6, s6, s6" "\n\t"
		"xor s7, s7, s7" "\n\t"
		"xor s8, s8, s8" "\n\t"
		"xor s9, s9, s9" "\n\t"
		"xor s10, s10, s10" "\n\t"
		"xor s11, s11, s11" "\n\t"
		"xor t3, t3, t3" "\n\t"
		"xor t4, t4, t4" "\n\t"
		"xor t5, t5, t5" "\n\t"
		"xor t6, t6, t6" "\n\t"*/
	);
	int interrupt_nr;
	__asm__ __volatile__ (
		"lw %0, 1*4(sp)"
	: "=r" (interrupt_nr)
	:);

	if(interrupt_nr)
	{
		int (*int_to_call)(unsigned int) = intVectors[interrupt_nr - 1];
		int_to_call(interrupt_nr);
	}
	else
	{
		IRQHandler_RTC(interrupt_nr);
	}
	asm volatile
	(
		"lw	x1,2*4(sp)" "\n\t"
		"lw	x2,3*4(sp)" "\n\t"
		"lw	x3,4*4(sp)" "\n\t"
		"lw	x4,5*4(sp)" "\n\t"
		"lw	x5,6*4(sp)" "\n\t"
		"lw	x6,7*4(sp)" "\n\t"
		"lw	x7,8*4(sp)" "\n\t"
		"lw	x8,9*4(sp)" "\n\t"
		"lw	x9,10*4(sp)" "\n\t"
		"lw	x10,11*4(sp)" "\n\t"
		"lw	x11,12*4(sp)" "\n\t"
		"lw	x12,13*4(sp)" "\n\t"
		"lw	x13,14*4(sp)" "\n\t"
		"lw	x14,15*4(sp)" "\n\t"
		"lw	x15,16*4(sp)" "\n\t"
		"lw	x16,17*4(sp)" "\n\t"
		"lw	x17,18*4(sp)" "\n\t"
		"lw	x18,19*4(sp)" "\n\t"
		"lw	x19,20*4(sp)" "\n\t"
		"lw	x20,21*4(sp)" "\n\t"
		"lw	x21,22*4(sp)" "\n\t"
		"lw	x22,23*4(sp)" "\n\t"
		"lw	x23,24*4(sp)" "\n\t"
		"lw	x24,25*4(sp)" "\n\t"
		"lw	x25,26*4(sp)" "\n\t"
		"lw	x26,27*4(sp)" "\n\t"
		"lw	x27,28*4(sp)" "\n\t"
		"lw	x28,29*4(sp)" "\n\t"
		"lw x29,30*4(sp)" "\n\t"
		"lw	x30,31*4(sp)" "\n\t"
		"lw	x31,32*4(sp)" "\n\t"
		"lw	x0,0*4(sp)" "\n\t"	/* Load return address*/
		"addi sp, sp, 33*4" "\n\t"
		"mret" "\n\t"			/* Execute return from interrupt*/
	)
;
}
#ifdef __cplusplus
}
#endif



/*------------------------------------------------------------------------------
 *
 */
/*------------------------------------------------------------------------------
 * RISC-V interrupt handler for external interrupts.
 */
/*__attribute__ ((section(".vectors"), used))
void vector_table()
{
	asm volatile ("j _entry");
	asm volatile ("j IRQHandler");
}*/

/*------------------------------------------------------------------------------
 * Disable all interrupts.
 */
void __disable_irq(void)
{
	REG_MSTATUS = (REG_MSTATUS & ~REG_MSTATUS_MIE_bm);
	//clear_csr(mstatus, MSTATUS_MPIE);
    //clear_csr(mstatus, MSTATUS_MIE);
}

/*------------------------------------------------------------------------------
 * Enabler all interrupts.
 */
void __enable_irq(void)
{
	REG_MSTATUS = (REG_MSTATUS | REG_MSTATUS_MIE_bm);
    //set_csr(mstatus, MSTATUS_MIE);
}

#ifdef __cplusplus
}
#endif
