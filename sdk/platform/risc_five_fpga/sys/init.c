/*
 * sysdelay.c
 *
 * Created: 2/8/2018 10:53:14 PM
 *  Author: Iulian Gheorghiu
 */


#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "io_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

unsigned long FCPU = CPU_FREQ;

extern uint32_t     __data_load_addr__;
extern uint32_t     __data_start__;
extern uint32_t     __data_end__;

extern uint32_t     __bss_start;
extern uint32_t     __bss_end;


static void copy_section(uint32_t * p_load, uint32_t * p_vma, uint32_t * p_vma_end)
{
    while(p_vma < p_vma_end)
    {
        *p_vma = *p_load;
        ++p_load;
        ++p_vma;
    }
}

static void zero_section(uint32_t * start, uint32_t * end)
{
    uint32_t * p_zero = start;

    while(p_zero < end)
    {
        *p_zero = 0;
        ++p_zero;
    }
}

void _begin(void)
{
    copy_section(&__data_load_addr__, &__data_start__, &__data_end__);
    zero_section(&__bss_start, &__bss_end);
    __enable_irq();
    asm volatile ("j _start");
}

#ifdef __cplusplus
}
#endif
