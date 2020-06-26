
#include "io_defs.h"
/*------------------------------------------------------------------------------
 *
 */
//*****************************************************************************
//
//! This is the code that gets called when the processor receives an unexpected
//! interrupt. This simply enters an infinite loop, preserving the system state
//! for examination by a debugger.
//
//*****************************************************************************
int IntDefaultHandler(unsigned int reason)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}

int IRQHandler_1(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_2(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_3(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_4(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_5(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_6(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_7(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_8(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_9(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_10(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_11(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_12(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_13(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_14(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_15(unsigned int) WEAK_ALIAS(IntDefaultHandler);
int IRQHandler_16(unsigned int) WEAK_ALIAS(IntDefaultHandler);


int (* const intVectors[])(unsigned int) =
{
	IRQHandler_1,
	IRQHandler_2,
	IRQHandler_3,
	IRQHandler_4,
	IRQHandler_5,
	IRQHandler_6,
	IRQHandler_7,
	IRQHandler_8,
	IRQHandler_9,
	IRQHandler_10,
	IRQHandler_11,
	IRQHandler_12,
	IRQHandler_13,
	IRQHandler_14,
	IRQHandler_15,
	IRQHandler_16,
};

