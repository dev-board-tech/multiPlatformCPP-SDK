/*
 * board.h
 */

#ifndef _BOARD_BOARD_H_
#define _BOARD_BOARD_H_

#if defined(MikromediaForSTM32M4)
#include <board/STM/MikromediaForSTM32M4/defs.h>
#elif defined(STM32F429I_DISCO)
#include <board/STM/STM32F429I-DISCO/defs.h>
#elif defined(STM32F469I_DISCO)
#include <board/STM/STM32F469I-DISCO/defs.h>
#elif defined(STM32F769I_DISCO)
#include <board/STM/STM32F769I-DISCO/defs.h>
#elif defined(SmartRf06)
#include <board/TI/SmartRF06/defs.h>
#elif defined(CC1310LauchPad)
#include <board/TI/CC1310LauchPad/defs.h>
#elif defined(beaglebone)
#include <board/TI/beaglebone/defs.h>
#elif defined(FRDM_KEAZ128)
#include <board/NXP/FRDM-KEAZ128/defs.h>
#elif defined(Xmega_E5_Xplained)
#include <board/ATMEL/Xmega-E5_Xplained/defs.h>
#elif defined(Xmega_FPGA)
#include <board/ATMEL/Xmega-FPGA/defs.h>
#elif defined(RiscV_FPGA)
#include <board/RISCV/RISCV-FPGA/defs.h>
#elif defined(FeatherAdaloggerM0)
#include <board/ATMEL/FeatherAdaloggerM0/defs.h>
#elif defined(mikroXmega)
#include <board/ATMEL/mikroXmega/defs.h>
#endif

#endif /* _BOARD_BOARD_H_ */
