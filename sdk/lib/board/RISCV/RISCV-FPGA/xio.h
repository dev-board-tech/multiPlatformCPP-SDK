/*
 * sysdelay.c
 *
 * Created: 2/8/2013 10:53:14 PM
 *  Author: Iulian Gheorghiu
 */
#ifndef XIO_H_
#define XIO_H_

#include <stdint.h>
#include "sys/hal.h"

typedef volatile uint8_t register8_t;
typedef volatile uint16_t register16_t;
typedef volatile uint32_t register32_t;

/*
--------------------------------------------------------------------------
System registers in IO space
--------------------------------------------------------------------------
*/
#define REG_MSTATUS					(*(register32_t*) (0x300 << 2))	//Machine status register.
#define REG_MIE						(*(register32_t*) (0x304 << 2))	//Machine interrupt-enable register.
#define REG_MSCRATCH				(*(register32_t*) (0x340 << 2))	//Scratch register for machine trap handlers.
#define REG_MEPC					(*(register32_t*) (0x341 << 2))	//Machine exception program counter.
#define REG_MCAUSE					(*(register32_t*) (0x342 << 2))	//Machine trap cause.
#define REG_MBADADDR				(*(register32_t*) (0x343 << 2))	//Machine bad address.

#define REG_MSTATUS_MIE_bp			3
#define REG_MSTATUS_MIE_bm			(1 << REG_MSTATUS_MIE_bp)
#define REG_MSTATUS_HIE_bp			2
#define REG_MSTATUS_HIE_bm			(1 << REG_MSTATUS_HIE_bp)
#define REG_MSTATUS_SIE_bp			1
#define REG_MSTATUS_SIE_bm			(1 << REG_MSTATUS_SIE_bp)
#define REG_MSTATUS_UIE_bp			0
#define REG_MSTATUS_UIE_bm			(1 << REG_MSTATUS_UIE_bp)

/*
--------------------------------------------------------------------------
RTC - Real-Time Clounter
--------------------------------------------------------------------------
*/
typedef struct FPGA_RTC_struct
{
	register32_t RTC_CNT;
	register32_t RTC_PERIOD;
	register32_t RTC_STATUS;
} FPGA_RTC_t;

/*
--------------------------------------------------------------------------
PORT - Port Configuration
--------------------------------------------------------------------------
*/
typedef struct FPGA_PORT_struct
{
	register32_t DIR;  /* I/O Port Data Direction */
	register32_t DIRSET;  /* I/O Port Data Direction Set */
	register32_t DIRCLR;  /* I/O Port Data Direction Clear */
	register32_t DIRTGL;  /* I/O Port Data Direction Toggle */
	register32_t OUT;  /* I/O Port Output */
	register32_t OUTSET;  /* I/O Port Output Set */
	register32_t OUTCLR;  /* I/O Port Output Clear */
	register32_t OUTTGL;  /* I/O Port Output Toggle */
	register32_t IN;  /* I/O port Input */
	register32_t INTCTRL;  /* Interrupt Control Register */
	register32_t INTMASK;  /* Port Interrupt Mask */
	register32_t INTFLAGS;  /* Interrupt Flag Register */
	register8_t PIN0CTRL;  /* Pin 0 Control Register */
	register8_t PIN1CTRL;  /* Pin 1 Control Register */
	register8_t PIN2CTRL;  /* Pin 2 Control Register */
	register8_t PIN3CTRL;  /* Pin 3 Control Register */
	register8_t PIN4CTRL;  /* Pin 4 Control Register */
	register8_t PIN5CTRL;  /* Pin 5 Control Register */
	register8_t PIN6CTRL;  /* Pin 6 Control Register */
	register8_t PIN7CTRL;  /* Pin 7 Control Register */
//	register8_t PIN8CTRL;  /* Pin 0 Control Register */
//	register8_t PIN9CTRL;  /* Pin 1 Control Register */
//	register8_t PIN10CTRL;  /* Pin 2 Control Register */
//	register8_t PIN11CTRL;  /* Pin 3 Control Register */
//	register8_t PIN12CTRL;  /* Pin 4 Control Register */
//	register8_t PIN13CTRL;  /* Pin 5 Control Register */
//	register8_t PIN14CTRL;  /* Pin 6 Control Register */
//	register8_t PIN15CTRL;  /* Pin 7 Control Register */
//	register8_t PIN16CTRL;  /* Pin 0 Control Register */
//	register8_t PIN17CTRL;  /* Pin 1 Control Register */
//	register8_t PIN18CTRL;  /* Pin 2 Control Register */
//	register8_t PIN19CTRL;  /* Pin 3 Control Register */
//	register8_t PIN20CTRL;  /* Pin 4 Control Register */
//	register8_t PIN21CTRL;  /* Pin 5 Control Register */
//	register8_t PIN22CTRL;  /* Pin 6 Control Register */
//	register8_t PIN23CTRL;  /* Pin 7 Control Register */
//	register8_t PIN24CTRL;  /* Pin 0 Control Register */
//	register8_t PIN25CTRL;  /* Pin 1 Control Register */
//	register8_t PIN26CTRL;  /* Pin 2 Control Register */
//	register8_t PIN27CTRL;  /* Pin 3 Control Register */
//	register8_t PIN28CTRL;  /* Pin 4 Control Register */
//	register8_t PIN29CTRL;  /* Pin 5 Control Register */
//	register8_t PIN30CTRL;  /* Pin 6 Control Register */
//	register8_t PIN31CTRL;  /* Pin 7 Control Register */
} FPGA_PORT_t;

/* Output/Pull Configuration */
typedef enum FPGA_PORT_OPC_enum
{
	FPGA_PORT_OPC_TOTEM_gc = (0x00<<3),  /* Totempole */
	FPGA_PORT_OPC_BUSKEEPER_gc = (0x01<<3),  /* Totempole w/ Bus keeper on Input and Output */
	FPGA_PORT_OPC_PULLDOWN_gc = (0x02<<3),  /* Totempole w/ Pull-down on Input */
	FPGA_PORT_OPC_PULLUP_gc = (0x03<<3),  /* Totempole w/ Pull-up on Input */
	FPGA_PORT_OPC_WIREDOR_gc = (0x04<<3),  /* Wired OR */
	FPGA_PORT_OPC_WIREDAND_gc = (0x05<<3),  /* Wired AND */
	FPGA_PORT_OPC_WIREDORPULL_gc = (0x06<<3),  /* Wired OR w/ Pull-down */
	FPGA_PORT_OPC_WIREDANDPULL_gc = (0x07<<3),  /* Wired AND w/ Pull-up */
} FPGA_PORT_OPC_t;

/* Input/Sense Configuration */
typedef enum FPGA_PORT_ISC_enum
{
	FPGA_PORT_ISC_BOTHEDGES_gc = (0x00<<0),  /* Sense Both Edges */
	FPGA_PORT_ISC_RISING_gc = (0x01<<0),  /* Sense Rising Edge */
	FPGA_PORT_ISC_FALLING_gc = (0x02<<0),  /* Sense Falling Edge */
	FPGA_PORT_ISC_LEVEL_gc = (0x03<<0),  /* Sense Level (Transparent For Events) */
	FPGA_PORT_ISC_FORCE_ENABLE_gc = (0x06<<0),  /* Digital Input Buffer Forced Enable */
	FPGA_PORT_ISC_INPUT_DISABLE_gc = (0x07<<0),  /* Disable Digital Input Buffer */
} FPGA_PORT_ISC_t;

/* PORT.PIN0CTRL  bit masks and bit positions */
#define PORT_INVEN_bm  0x40  /* Inverted I/O Enable bit mask. */
#define PORT_INVEN_bp  6  /* Inverted I/O Enable bit position. */

/*
--------------------------------------------------------------------------
TWI - Two wire interface
--------------------------------------------------------------------------
*/
/* Two-Wire Interface */
typedef struct FPGA_TWI_MASTER_struct
{
	register8_t CTRLA;  /* Control Register A */
	register8_t CTRLB;  /* Control Register B */
	register8_t CTRLC;  /* Control Register C */
	register8_t STATUS;  /* Status Register */
	register8_t BAUD;  /* Baurd Rate Control Register */
	register8_t ADDR;  /* Address Register */
	register8_t DATA;  /* Data Register */
} FPGA_TWI_MASTER_t;


/*  */
typedef struct FPGA_TWI_SLAVE_struct
{
	register8_t CTRLA;  /* Control Register A */
	register8_t CTRLB;  /* Control Register B */
	register8_t STATUS;  /* Status Register */
	register8_t ADDR;  /* Address Register */
	register8_t DATA;  /* Data Register */
	register8_t ADDRMASK;  /* Address Mask Register */
} FPGA_TWI_SLAVE_t;


/*  */
typedef struct FPGA_TWI_TIMEOUT_struct
{
	register8_t TOS;  /* Timeout Status Register */
	register8_t TOCONF;  /* Timeout Configuration Register */
} FPGA_TWI_TIMEOUT_t;

/*  */
typedef struct FPGA_TWI_struct
{
	register8_t CTRL;  /* TWI Common Control Register */
	FPGA_TWI_MASTER_t MASTER;  /* TWI master module */
	FPGA_TWI_SLAVE_t SLAVE;  /* TWI slave module */
	FPGA_TWI_TIMEOUT_t TIMEOUT;  /* TWI SMBUS timeout module */
} FPGA_TWI_t;


/* SDA Hold Time */
typedef enum FPGA_TWI_SDAHOLD_enum
{
	FPGA_TWI_SDAHOLD_OFF_gc = (0x00<<4),  /* SDA Hold Time off */
	FPGA_TWI_SDAHOLD_50NS_gc = (0x01<<4),  /* SDA Hold Time 50 ns */
	FPGA_TWI_SDAHOLD_300NS_gc = (0x02<<4),  /* SDA Hold Time 300 ns */
	FPGA_TWI_SDAHOLD_400NS_gc = (0x03<<4),  /* SDA Hold Time 400 ns */
} FPGA_TWI_SDAHOLD_t;

/* Master Interrupt Level */
typedef enum FPGA_TWI_MASTER_INTLVL_enum
{
	FPGA_TWI_MASTER_INTLVL_OFF_gc = (0x00<<6),  /* Interrupt Disabled */
	FPGA_TWI_MASTER_INTLVL_LO_gc = (0x01<<6),  /* Low Level */
	FPGA_TWI_MASTER_INTLVL_MED_gc = (0x02<<6),  /* Medium Level */
	FPGA_TWI_MASTER_INTLVL_HI_gc = (0x03<<6),  /* High Level */
} FPGA_TWI_MASTER_INTLVL_t;

/* Inactive Timeout */
typedef enum FPGA_TWI_MASTER_TIMEOUT_enum
{
	FPGA_TWI_MASTER_TIMEOUT_DISABLED_gc = (0x00<<2),  /* Bus Timeout Disabled */
	FPGA_TWI_MASTER_TIMEOUT_50US_gc = (0x01<<2),  /* 50 Microseconds */
	FPGA_TWI_MASTER_TIMEOUT_100US_gc = (0x02<<2),  /* 100 Microseconds */
	FPGA_TWI_MASTER_TIMEOUT_200US_gc = (0x03<<2),  /* 200 Microseconds */
} FPGA_TWI_MASTER_TIMEOUT_t;

/* Master Command */
typedef enum FPGA_TWI_MASTER_CMD_enum
{
	FPGA_TWI_MASTER_CMD_NOACT_gc = (0x00<<0),  /* No Action */
	FPGA_TWI_MASTER_CMD_REPSTART_gc = (0x01<<0),  /* Issue Repeated Start Condition */
	FPGA_TWI_MASTER_CMD_RECVTRANS_gc = (0x02<<0),  /* Receive or Transmit Data */
	FPGA_TWI_MASTER_CMD_STOP_gc = (0x03<<0),  /* Issue Stop Condition */
} FPGA_TWI_MASTER_CMD_t;

/* Master Bus State */
typedef enum FPGA_TWI_MASTER_BUSSTATE_enum
{
	FPGA_TWI_MASTER_BUSSTATE_UNKNOWN_gc = (0x00<<0),  /* Unknown Bus State */
	FPGA_TWI_MASTER_BUSSTATE_IDLE_gc = (0x01<<0),  /* Bus is Idle */
	FPGA_TWI_MASTER_BUSSTATE_OWNER_gc = (0x02<<0),  /* This Module Controls The Bus */
	FPGA_TWI_MASTER_BUSSTATE_BUSY_gc = (0x03<<0),  /* The Bus is Busy */
} FPGA_TWI_MASTER_BUSSTATE_t;

/* Slave Interrupt Level */
typedef enum FPGA_TWI_SLAVE_INTLVL_enum
{
	FPGA_TWI_SLAVE_INTLVL_OFF_gc = (0x00<<6),  /* Interrupt Disabled */
	FPGA_TWI_SLAVE_INTLVL_LO_gc = (0x01<<6),  /* Low Level */
	FPGA_TWI_SLAVE_INTLVL_MED_gc = (0x02<<6),  /* Medium Level */
	FPGA_TWI_SLAVE_INTLVL_HI_gc = (0x03<<6),  /* High Level */
} FPGA_TWI_SLAVE_INTLVL_t;

/* Slave Command */
typedef enum FPGA_TWI_SLAVE_CMD_enum
{
	FPGA_TWI_SLAVE_CMD_NOACT_gc = (0x00<<0),  /* No Action */
	FPGA_TWI_SLAVE_CMD_COMPTRANS_gc = (0x02<<0),  /* Used To Complete a Transaction */
	FPGA_TWI_SLAVE_CMD_RESPONSE_gc = (0x03<<0),  /* Used in Response to Address/Data Interrupt */
} FPGA_TWI_SLAVE_CMD_t;

/* Master Timeout */
typedef enum FPGA_TWI_MASTER_TTIMEOUT_enum
{
	FPGA_TWI_MASTER_TTIMEOUT_25MS_gc = (0x00<<0),  /* 25 Milliseconds */
	FPGA_TWI_MASTER_TTIMEOUT_24MS_gc = (0x01<<0),  /* 24 Milliseconds */
	FPGA_TWI_MASTER_TTIMEOUT_23MS_gc = (0x02<<0),  /* 23 Milliseconds */
	FPGA_TWI_MASTER_TTIMEOUT_22MS_gc = (0x03<<0),  /* 22 Milliseconds */
	FPGA_TWI_MASTER_TTIMEOUT_26MS_gc = (0x04<<0),  /* 26 Milliseconds */
	FPGA_TWI_MASTER_TTIMEOUT_27MS_gc = (0x05<<0),  /* 27 Milliseconds */
	FPGA_TWI_MASTER_TTIMEOUT_28MS_gc = (0x06<<0),  /* 28 Milliseconds */
	FPGA_TWI_MASTER_TTIMEOUT_29MS_gc = (0x07<<0),  /* 29 Milliseconds */
} FPGA_TWI_MASTER_TTIMEOUT_t;

/* Slave Ttimeout */
typedef enum FPGA_TWI_SLAVE_TTIMEOUT_enum
{
	FPGA_TWI_SLAVE_TTIMEOUT_25MS_gc = (0x00<<5),  /* 25 Milliseconds */
	FPGA_TWI_SLAVE_TTIMEOUT_24MS_gc = (0x01<<5),  /* 24 Milliseconds */
	FPGA_TWI_SLAVE_TTIMEOUT_23MS_gc = (0x02<<5),  /* 23 Milliseconds */
	FPGA_TWI_SLAVE_TTIMEOUT_22MS_gc = (0x03<<5),  /* 22 Milliseconds */
	FPGA_TWI_SLAVE_TTIMEOUT_26MS_gc = (0x04<<5),  /* 26 Milliseconds */
	FPGA_TWI_SLAVE_TTIMEOUT_27MS_gc = (0x05<<5),  /* 27 Milliseconds */
	FPGA_TWI_SLAVE_TTIMEOUT_28MS_gc = (0x06<<5),  /* 28 Milliseconds */
	FPGA_TWI_SLAVE_TTIMEOUT_29MS_gc = (0x07<<5),  /* 29 Milliseconds */
} FPGA_TWI_SLAVE_TTIMEOUT_t;

/* Master/Slave Extend Timeout */
typedef enum FPGA_TWI_MASTER_TMSEXT_enum
{
	FPGA_TWI_MASTER_TMSEXT_10MS25MS_gc = (0x00<<3),  /* Tmext 10ms Tsext 25ms */
	FPGA_TWI_MASTER_TMSEXT_9MS24MS_gc = (0x01<<3),  /* Tmext 9ms  Tsext 24ms */
	FPGA_TWI_MASTER_TMSEXT_11MS26MS_gc = (0x02<<3),  /* Tmext 11ms Tsext 26ms */
	FPGA_TWI_MASTER_TMSEXT_12MS27MS_gc = (0x03<<3),  /* Tmext 12ms Tsext 27ms */
} FPGA_TWI_MASTER_TMSEXT_t;

/* TWI - Two-Wire Interface */
/* TWI.CTRL  bit masks and bit positions */
#define FPGA_TWI_BRIDGEEN_bm  0x80  /* Bridge Enable bit mask. */
#define FPGA_TWI_BRIDGEEN_bp  7  /* Bridge Enable bit position. */

#define FPGA_TWI_SFMPEN_bm  0x40  /* Slave Fast Mode Plus Enable bit mask. */
#define FPGA_TWI_SFMPEN_bp  6  /* Slave Fast Mode Plus Enable bit position. */

#define FPGA_TWI_SSDAHOLD_gm  0x30  /* Slave SDA Hold Time Enable group mask. */
#define FPGA_TWI_SSDAHOLD_gp  4  /* Slave SDA Hold Time Enable group position. */
#define FPGA_TWI_SSDAHOLD0_bm  (1<<4)  /* Slave SDA Hold Time Enable bit 0 mask. */
#define FPGA_TWI_SSDAHOLD0_bp  4  /* Slave SDA Hold Time Enable bit 0 position. */
#define FPGA_TWI_SSDAHOLD1_bm  (1<<5)  /* Slave SDA Hold Time Enable bit 1 mask. */
#define FPGA_TWI_SSDAHOLD1_bp  5  /* Slave SDA Hold Time Enable bit 1 position. */

#define FPGA_TWI_FMPEN_bm  0x08  /* FMPLUS Enable bit mask. */
#define FPGA_TWI_FMPEN_bp  3  /* FMPLUS Enable bit position. */

#define FPGA_TWI_SDAHOLD_gm  0x06  /* SDA Hold Time Enable group mask. */
#define FPGA_TWI_SDAHOLD_gp  1  /* SDA Hold Time Enable group position. */
#define FPGA_TWI_SDAHOLD0_bm  (1<<1)  /* SDA Hold Time Enable bit 0 mask. */
#define FPGA_TWI_SDAHOLD0_bp  1  /* SDA Hold Time Enable bit 0 position. */
#define FPGA_TWI_SDAHOLD1_bm  (1<<2)  /* SDA Hold Time Enable bit 1 mask. */
#define FPGA_TWI_SDAHOLD1_bp  2  /* SDA Hold Time Enable bit 1 position. */

#define FPGA_TWI_EDIEN_bm  0x01  /* External Driver Interface Enable bit mask. */
#define FPGA_TWI_EDIEN_bp  0  /* External Driver Interface Enable bit position. */

/* TWI_MASTER.CTRLA  bit masks and bit positions */
#define FPGA_TWI_MASTER_INTLVL_gm  0xC0  /* Interrupt Level group mask. */
#define FPGA_TWI_MASTER_INTLVL_gp  6  /* Interrupt Level group position. */
#define FPGA_TWI_MASTER_INTLVL0_bm  (1<<6)  /* Interrupt Level bit 0 mask. */
#define FPGA_TWI_MASTER_INTLVL0_bp  6  /* Interrupt Level bit 0 position. */
#define FPGA_TWI_MASTER_INTLVL1_bm  (1<<7)  /* Interrupt Level bit 1 mask. */
#define FPGA_TWI_MASTER_INTLVL1_bp  7  /* Interrupt Level bit 1 position. */

#define FPGA_TWI_MASTER_RIEN_bm  0x20  /* Read Interrupt Enable bit mask. */
#define FPGA_TWI_MASTER_RIEN_bp  5  /* Read Interrupt Enable bit position. */

#define FPGA_TWI_MASTER_WIEN_bm  0x10  /* Write Interrupt Enable bit mask. */
#define FPGA_TWI_MASTER_WIEN_bp  4  /* Write Interrupt Enable bit position. */

#define FPGA_TWI_MASTER_ENABLE_bm  0x08  /* Enable TWI Master bit mask. */
#define FPGA_TWI_MASTER_ENABLE_bp  3  /* Enable TWI Master bit position. */

/* TWI_MASTER.CTRLB  bit masks and bit positions */
#define FPGA_TWI_MASTER_TIMEOUT_gm  0x0C  /* Inactive Bus Timeout group mask. */
#define FPGA_TWI_MASTER_TIMEOUT_gp  2  /* Inactive Bus Timeout group position. */
#define FPGA_TWI_MASTER_TIMEOUT0_bm  (1<<2)  /* Inactive Bus Timeout bit 0 mask. */
#define FPGA_TWI_MASTER_TIMEOUT0_bp  2  /* Inactive Bus Timeout bit 0 position. */
#define FPGA_TWI_MASTER_TIMEOUT1_bm  (1<<3)  /* Inactive Bus Timeout bit 1 mask. */
#define FPGA_TWI_MASTER_TIMEOUT1_bp  3  /* Inactive Bus Timeout bit 1 position. */

#define FPGA_TWI_MASTER_QCEN_bm  0x02  /* Quick Command Enable bit mask. */
#define FPGA_TWI_MASTER_QCEN_bp  1  /* Quick Command Enable bit position. */

#define FPGA_TWI_MASTER_SMEN_bm  0x01  /* Smart Mode Enable bit mask. */
#define FPGA_TWI_MASTER_SMEN_bp  0  /* Smart Mode Enable bit position. */

#define FPGA_TWI_MASTER_TTOUTEN_bm  0x10  /* Ttimeout Enable bit mask. */
#define FPGA_TWI_MASTER_TTOUTEN_bp  4  /* Ttimeout Enable bit position. */

#define FPGA_TWI_MASTER_TSEXTEN_bm  0x20  /* Slave Extend Timeout Enable bit mask. */
#define FPGA_TWI_MASTER_TSEXTEN_bp  5  /* Slave Extend Timeout Enable bit position. */

#define FPGA_TWI_MASTER_TMEXTEN_bm  0x40  /* Master Extend Timeout Enable bit mask. */
#define FPGA_TWI_MASTER_TMEXTEN_bp  6  /* Master Extend Timeout Enable bit position. */

#define FPGA_TWI_MASTER_TOIE_bm  0x80  /* Timeout Interrupt Enable bit mask. */
#define FPGA_TWI_MASTER_TOIE_bp  7  /* Timeout Interrupt Enable bit position. */

/* TWI_MASTER.CTRLC  bit masks and bit positions */
#define FPGA_TWI_MASTER_ACKACT_bm  0x04  /* Acknowledge Action bit mask. */
#define FPGA_TWI_MASTER_ACKACT_bp  2  /* Acknowledge Action bit position. */

#define FPGA_TWI_MASTER_CMD_gm  0x03  /* Command group mask. */
#define FPGA_TWI_MASTER_CMD_gp  0  /* Command group position. */
#define FPGA_TWI_MASTER_CMD0_bm  (1<<0)  /* Command bit 0 mask. */
#define FPGA_TWI_MASTER_CMD0_bp  0  /* Command bit 0 position. */
#define FPGA_TWI_MASTER_CMD1_bm  (1<<1)  /* Command bit 1 mask. */
#define FPGA_TWI_MASTER_CMD1_bp  1  /* Command bit 1 position. */

/* TWI_MASTER.STATUS  bit masks and bit positions */
#define FPGA_TWI_MASTER_RIF_bm  0x80  /* Read Interrupt Flag bit mask. */
#define FPGA_TWI_MASTER_RIF_bp  7  /* Read Interrupt Flag bit position. */

#define FPGA_TWI_MASTER_WIF_bm  0x40  /* Write Interrupt Flag bit mask. */
#define FPGA_TWI_MASTER_WIF_bp  6  /* Write Interrupt Flag bit position. */

#define FPGA_TWI_MASTER_CLKHOLD_bm  0x20  /* Clock Hold bit mask. */
#define FPGA_TWI_MASTER_CLKHOLD_bp  5  /* Clock Hold bit position. */

#define FPGA_TWI_MASTER_RXACK_bm  0x10  /* Received Acknowledge bit mask. */
#define FPGA_TWI_MASTER_RXACK_bp  4  /* Received Acknowledge bit position. */

#define FPGA_TWI_MASTER_ARBLOST_bm  0x08  /* Arbitration Lost bit mask. */
#define FPGA_TWI_MASTER_ARBLOST_bp  3  /* Arbitration Lost bit position. */

#define FPGA_TWI_MASTER_BUSERR_bm  0x04  /* Bus Error bit mask. */
#define FPGA_TWI_MASTER_BUSERR_bp  2  /* Bus Error bit position. */

#define FPGA_TWI_MASTER_BUSSTATE_gm  0x03  /* Bus State group mask. */
#define FPGA_TWI_MASTER_BUSSTATE_gp  0  /* Bus State group position. */
#define FPGA_TWI_MASTER_BUSSTATE0_bm  (1<<0)  /* Bus State bit 0 mask. */
#define FPGA_TWI_MASTER_BUSSTATE0_bp  0  /* Bus State bit 0 position. */
#define FPGA_TWI_MASTER_BUSSTATE1_bm  (1<<1)  /* Bus State bit 1 mask. */
#define FPGA_TWI_MASTER_BUSSTATE1_bp  1  /* Bus State bit 1 position. */

/* TWI_SLAVE.CTRLA  bit masks and bit positions */
#define FPGA_TWI_SLAVE_INTLVL_gm  0xC0  /* Interrupt Level group mask. */
#define FPGA_TWI_SLAVE_INTLVL_gp  6  /* Interrupt Level group position. */
#define FPGA_TWI_SLAVE_INTLVL0_bm  (1<<6)  /* Interrupt Level bit 0 mask. */
#define FPGA_TWI_SLAVE_INTLVL0_bp  6  /* Interrupt Level bit 0 position. */
#define FPGA_TWI_SLAVE_INTLVL1_bm  (1<<7)  /* Interrupt Level bit 1 mask. */
#define FPGA_TWI_SLAVE_INTLVL1_bp  7  /* Interrupt Level bit 1 position. */

#define FPGA_TWI_SLAVE_DIEN_bm  0x20  /* Data Interrupt Enable bit mask. */
#define FPGA_TWI_SLAVE_DIEN_bp  5  /* Data Interrupt Enable bit position. */

#define FPGA_TWI_SLAVE_APIEN_bm  0x10  /* Address/Stop Interrupt Enable bit mask. */
#define FPGA_TWI_SLAVE_APIEN_bp  4  /* Address/Stop Interrupt Enable bit position. */

#define FPGA_TWI_SLAVE_ENABLE_bm  0x08  /* Enable TWI Slave bit mask. */
#define FPGA_TWI_SLAVE_ENABLE_bp  3  /* Enable TWI Slave bit position. */

#define FPGA_TWI_SLAVE_PIEN_bm  0x04  /* Stop Interrupt Enable bit mask. */
#define FPGA_TWI_SLAVE_PIEN_bp  2  /* Stop Interrupt Enable bit position. */

#define FPGA_TWI_SLAVE_PMEN_bm  0x02  /* Promiscuous Mode Enable bit mask. */
#define FPGA_TWI_SLAVE_PMEN_bp  1  /* Promiscuous Mode Enable bit position. */

#define FPGA_TWI_SLAVE_SMEN_bm  0x01  /* Smart Mode Enable bit mask. */
#define FPGA_TWI_SLAVE_SMEN_bp  0  /* Smart Mode Enable bit position. */

/* TWI_SLAVE.CTRLB  bit masks and bit positions */
#define FPGA_TWI_SLAVE_ACKACT_bm  0x04  /* Acknowledge Action bit mask. */
#define FPGA_TWI_SLAVE_ACKACT_bp  2  /* Acknowledge Action bit position. */

#define FPGA_TWI_SLAVE_CMD_gm  0x03  /* Command group mask. */
#define FPGA_TWI_SLAVE_CMD_gp  0  /* Command group position. */
#define FPGA_TWI_SLAVE_CMD0_bm  (1<<0)  /* Command bit 0 mask. */
#define FPGA_TWI_SLAVE_CMD0_bp  0  /* Command bit 0 position. */
#define FPGA_TWI_SLAVE_CMD1_bm  (1<<1)  /* Command bit 1 mask. */
#define FPGA_TWI_SLAVE_CMD1_bp  1  /* Command bit 1 position. */

#define FPGA_TWI_SLAVE_TTOUTEN_bm  0x10  /* Ttimeout Enable bit mask. */
#define FPGA_TWI_SLAVE_TTOUTEN_bp  4  /* Ttimeout Enable bit position. */

#define FPGA_TWI_SLAVE_TOIE_bm  0x80  /* Timeout Interrupt Enable bit mask. */
#define FPGA_TWI_SLAVE_TOIE_bp  7  /* Timeout Interrupt Enable bit position. */

/* TWI_SLAVE.STATUS  bit masks and bit positions */
#define FPGA_TWI_SLAVE_DIF_bm  0x80  /* Data Interrupt Flag bit mask. */
#define FPGA_TWI_SLAVE_DIF_bp  7  /* Data Interrupt Flag bit position. */

#define FPGA_TWI_SLAVE_APIF_bm  0x40  /* Address/Stop Interrupt Flag bit mask. */
#define FPGA_TWI_SLAVE_APIF_bp  6  /* Address/Stop Interrupt Flag bit position. */

#define FPGA_TWI_SLAVE_CLKHOLD_bm  0x20  /* Clock Hold bit mask. */
#define FPGA_TWI_SLAVE_CLKHOLD_bp  5  /* Clock Hold bit position. */

#define FPGA_TWI_SLAVE_RXACK_bm  0x10  /* Received Acknowledge bit mask. */
#define FPGA_TWI_SLAVE_RXACK_bp  4  /* Received Acknowledge bit position. */

#define FPGA_TWI_SLAVE_COLL_bm  0x08  /* Collision bit mask. */
#define FPGA_TWI_SLAVE_COLL_bp  3  /* Collision bit position. */

#define FPGA_TWI_SLAVE_BUSERR_bm  0x04  /* Bus Error bit mask. */
#define FPGA_TWI_SLAVE_BUSERR_bp  2  /* Bus Error bit position. */

#define FPGA_TWI_SLAVE_DIR_bm  0x02  /* Read/Write Direction bit mask. */
#define FPGA_TWI_SLAVE_DIR_bp  1  /* Read/Write Direction bit position. */

#define FPGA_TWI_SLAVE_AP_bm  0x01  /* Slave Address or Stop bit mask. */
#define FPGA_TWI_SLAVE_AP_bp  0  /* Slave Address or Stop bit position. */

/* TWI_SLAVE.ADDRMASK  bit masks and bit positions */
#define FPGA_TWI_SLAVE_ADDRMASK_gm  0xFE  /* Address Mask group mask. */
#define FPGA_TWI_SLAVE_ADDRMASK_gp  1  /* Address Mask group position. */
#define FPGA_TWI_SLAVE_ADDRMASK0_bm  (1<<1)  /* Address Mask bit 0 mask. */
#define FPGA_TWI_SLAVE_ADDRMASK0_bp  1  /* Address Mask bit 0 position. */
#define FPGA_TWI_SLAVE_ADDRMASK1_bm  (1<<2)  /* Address Mask bit 1 mask. */
#define FPGA_TWI_SLAVE_ADDRMASK1_bp  2  /* Address Mask bit 1 position. */
#define FPGA_TWI_SLAVE_ADDRMASK2_bm  (1<<3)  /* Address Mask bit 2 mask. */
#define FPGA_TWI_SLAVE_ADDRMASK2_bp  3  /* Address Mask bit 2 position. */
#define FPGA_TWI_SLAVE_ADDRMASK3_bm  (1<<4)  /* Address Mask bit 3 mask. */
#define FPGA_TWI_SLAVE_ADDRMASK3_bp  4  /* Address Mask bit 3 position. */
#define FPGA_TWI_SLAVE_ADDRMASK4_bm  (1<<5)  /* Address Mask bit 4 mask. */
#define FPGA_TWI_SLAVE_ADDRMASK4_bp  5  /* Address Mask bit 4 position. */
#define FPGA_TWI_SLAVE_ADDRMASK5_bm  (1<<6)  /* Address Mask bit 5 mask. */
#define FPGA_TWI_SLAVE_ADDRMASK5_bp  6  /* Address Mask bit 5 position. */
#define FPGA_TWI_SLAVE_ADDRMASK6_bm  (1<<7)  /* Address Mask bit 6 mask. */
#define FPGA_TWI_SLAVE_ADDRMASK6_bp  7  /* Address Mask bit 6 position. */

#define FPGA_TWI_SLAVE_ADDREN_bm  0x01  /* Address Enable bit mask. */
#define FPGA_TWI_SLAVE_ADDREN_bp  0  /* Address Enable bit position. */

/* TWI_TIMEOUT.TOS  bit masks and bit positions */
#define FPGA_TWI_TIMEOUT_TTOUTMIF_bm  0x01  /* Master Ttimeout Interrupt Flag bit mask. */
#define FPGA_TWI_TIMEOUT_TTOUTMIF_bp  0  /* Master Ttimeout Interrupt Flag bit position. */

#define FPGA_TWI_TIMEOUT_TSEXTIF_bm  0x02  /* Slave Extend Interrupt Flag bit mask. */
#define FPGA_TWI_TIMEOUT_TSEXTIF_bp  1  /* Slave Extend Interrupt Flag bit position. */

#define FPGA_TWI_TIMEOUT_TMEXTIF_bm  0x04  /* Master Extend Interrupt Flag bit mask. */
#define FPGA_TWI_TIMEOUT_TMEXTIF_bp  2  /* Master Extend Interrupt Flag bit position. */

#define FPGA_TWI_TIMEOUT_TTOUTSIF_bm  0x10  /* Slave Ttimeout Interrupt Flag bit mask. */
#define FPGA_TWI_TIMEOUT_TTOUTSIF_bp  4  /* Slave Ttimeout Interrupt Flag bit position. */

/* TWI_TIMEOUT.TOCONF  bit masks and bit positions */
#define FPGA_TWI_TIMEOUT_TTOUTMSEL_gm  0x07  /* Master Ttimeout Select group mask. */
#define FPGA_TWI_TIMEOUT_TTOUTMSEL_gp  0  /* Master Ttimeout Select group position. */
#define FPGA_TWI_TIMEOUT_TTOUTMSEL0_bm  (1<<0)  /* Master Ttimeout Select bit 0 mask. */
#define FPGA_TWI_TIMEOUT_TTOUTMSEL0_bp  0  /* Master Ttimeout Select bit 0 position. */
#define FPGA_TWI_TIMEOUT_TTOUTMSEL1_bm  (1<<1)  /* Master Ttimeout Select bit 1 mask. */
#define FPGA_TWI_TIMEOUT_TTOUTMSEL1_bp  1  /* Master Ttimeout Select bit 1 position. */
#define FPGA_TWI_TIMEOUT_TTOUTMSEL2_bm  (1<<2)  /* Master Ttimeout Select bit 2 mask. */
#define FPGA_TWI_TIMEOUT_TTOUTMSEL2_bp  2  /* Master Ttimeout Select bit 2 position. */

#define FPGA_TWI_TIMEOUT_TMSEXTSEL_gm  0x18  /* Master/Slave Timeout Select group mask. */
#define FPGA_TWI_TIMEOUT_TMSEXTSEL_gp  3  /* Master/Slave Timeout Select group position. */
#define FPGA_TWI_TIMEOUT_TMSEXTSEL0_bm  (1<<3)  /* Master/Slave Timeout Select bit 0 mask. */
#define FPGA_TWI_TIMEOUT_TMSEXTSEL0_bp  3  /* Master/Slave Timeout Select bit 0 position. */
#define FPGA_TWI_TIMEOUT_TMSEXTSEL1_bm  (1<<4)  /* Master/Slave Timeout Select bit 1 mask. */
#define FPGA_TWI_TIMEOUT_TMSEXTSEL1_bp  4  /* Master/Slave Timeout Select bit 1 position. */

#define FPGA_TWI_TIMEOUT_TTOUTSSEL_gm  0xE0  /* Slave Ttimeout Select group mask. */
#define FPGA_TWI_TIMEOUT_TTOUTSSEL_gp  5  /* Slave Ttimeout Select group position. */
#define FPGA_TWI_TIMEOUT_TTOUTSSEL0_bm  (1<<5)  /* Slave Ttimeout Select bit 0 mask. */
#define FPGA_TWI_TIMEOUT_TTOUTSSEL0_bp  5  /* Slave Ttimeout Select bit 0 position. */
#define FPGA_TWI_TIMEOUT_TTOUTSSEL1_bm  (1<<6)  /* Slave Ttimeout Select bit 1 mask. */
#define FPGA_TWI_TIMEOUT_TTOUTSSEL1_bp  6  /* Slave Ttimeout Select bit 1 position. */
#define FPGA_TWI_TIMEOUT_TTOUTSSEL2_bm  (1<<7)  /* Slave Ttimeout Select bit 2 mask. */
#define FPGA_TWI_TIMEOUT_TTOUTSSEL2_bp  7  /* Slave Ttimeout Select bit 2 position. */

/*
--------------------------------------------------------------------------
SPI - Serial Pheripheral Interface
--------------------------------------------------------------------------
*/
/* Serial Peripheral Interface with Buffer Modes */
typedef struct FPGA_SPI_struct
{
	register8_t CTRL;  /* Control Register */
	register8_t INTCTRL;  /* Interrupt Control Register */
	register8_t STATUS;  /* Status Register */
	register8_t DATA;  /* Data Register */
	register8_t CTRLB;  /* Control Register B */
} FPGA_SPI_t;

/* SPI Mode */
typedef enum FPGA_SPI_MODE_enum
{
	FPGA_SPI_MODE_0_gc = (0x00<<2),  /* SPI Mode 0, base clock at "0", sampling on leading edge (rising) & set-up on trailling edge (falling). */
	FPGA_SPI_MODE_1_gc = (0x01<<2),  /* SPI Mode 1, base clock at "0", set-up on leading edge (rising) & sampling on trailling edge (falling). */
	FPGA_SPI_MODE_2_gc = (0x02<<2),  /* SPI Mode 2, base clock at "1", sampling on leading edge (falling) & set-up on trailling edge (rising). */
	FPGA_SPI_MODE_3_gc = (0x03<<2),  /* SPI Mode 3, base clock at "1", set-up on leading edge (falling) & sampling on trailling edge (rising). */
} FPGA_SPI_MODE_t;

/* Prescaler setting */
typedef enum FPGA_SPI_PRESCALER_enum
{
	FPGA_SPI_PRESCALER_DIV4_gc = (0x00<<0),  /* If CLK2X=1 CLKper/2, else (CLK2X=0) CLKper/4. */
	FPGA_SPI_PRESCALER_DIV16_gc = (0x01<<0),  /* If CLK2X=1 CLKper/8, else (CLK2X=0) CLKper/16. */
	FPGA_SPI_PRESCALER_DIV64_gc = (0x02<<0),  /* If CLK2X=1 CLKper/32, else (CLK2X=0) CLKper/64. */
	FPGA_SPI_PRESCALER_DIV128_gc = (0x03<<0),  /* If CLK2X=1 CLKper/64, else (CLK2X=0) CLKper/128. */
} FPGA_SPI_PRESCALER_t;

/* Interrupt level */
typedef enum FPGA_SPI_INTLVL_enum
{
	FPGA_SPI_INTLVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
	FPGA_SPI_INTLVL_LO_gc = (0x01<<0),  /* Low Level */
	FPGA_SPI_INTLVL_MED_gc = (0x02<<0),  /* Medium Level */
	FPGA_SPI_INTLVL_HI_gc = (0x03<<0),  /* High Level */
} FPGA_SPI_INTLVL_t;

/* Buffer Modes */
typedef enum FPGA_SPI_BUFMODE_enum
{
	FPGA_SPI_BUFMODE_OFF_gc = (0x00<<6),  /* SPI Unbuffered Mode */
	FPGA_SPI_BUFMODE_BUFMODE1_gc = (0x02<<6),  /* Buffer Mode 1 (with dummy byte) */
	FPGA_SPI_BUFMODE_BUFMODE2_gc = (0x03<<6),  /* Buffer Mode 2 (no dummy byte) */
} FPGA_SPI_BUFMODE_t;

/* SPI - Serial Peripheral Interface */
/* SPI.CTRL  bit masks and bit positions */
#define FPGA_SPI_CLK2X_bm  0x80  /* Enable Double Speed bit mask. */
#define FPGA_SPI_CLK2X_bp  7  /* Enable Double Speed bit position. */

#define FPGA_SPI_ENABLE_bm  0x40  /* Enable SPI Module bit mask. */
#define FPGA_SPI_ENABLE_bp  6  /* Enable SPI Module bit position. */

#define FPGA_SPI_DORD_bm  0x20  /* Data Order Setting bit mask. */
#define FPGA_SPI_DORD_bp  5  /* Data Order Setting bit position. */

#define FPGA_SPI_MASTER_bm  0x10  /* Master Operation Enable bit mask. */
#define FPGA_SPI_MASTER_bp  4  /* Master Operation Enable bit position. */

#define FPGA_SPI_MODE_gm  0x0C  /* SPI Mode group mask. */
#define FPGA_SPI_MODE_gp  2  /* SPI Mode group position. */
#define FPGA_SPI_MODE0_bm  (1<<2)  /* SPI Mode bit 0 mask. */
#define FPGA_SPI_MODE0_bp  2  /* SPI Mode bit 0 position. */
#define FPGA_FPGA_SPI_MODE1_bm  (1<<3)  /* SPI Mode bit 1 mask. */
#define SPI_MODE1_bp  3  /* SPI Mode bit 1 position. */

#define FPGA_SPI_PRESCALER_gm  0x03  /* Prescaler group mask. */
#define FPGA_SPI_PRESCALER_gp  0  /* Prescaler group position. */
#define FPGA_SPI_PRESCALER0_bm  (1<<0)  /* Prescaler bit 0 mask. */
#define FPGA_SPI_PRESCALER0_bp  0  /* Prescaler bit 0 position. */
#define FPGA_SPI_PRESCALER1_bm  (1<<1)  /* Prescaler bit 1 mask. */
#define FPGA_SPI_PRESCALER1_bp  1  /* Prescaler bit 1 position. */

/* SPI.INTCTRL  bit masks and bit positions */
#define FPGA_SPI_RXCIE_bm  0x80  /* Receive Complete Interrupt Enable (In Buffer Modes Only). bit mask. */
#define FPGA_SPI_RXCIE_bp  7  /* Receive Complete Interrupt Enable (In Buffer Modes Only). bit position. */

#define FPGA_SPI_TXCIE_bm  0x40  /* Transmit Complete Interrupt Enable (In Buffer Modes Only). bit mask. */
#define FPGA_SPI_TXCIE_bp  6  /* Transmit Complete Interrupt Enable (In Buffer Modes Only). bit position. */

#define FPGA_SPI_DREIE_bm  0x20  /* Data Register Empty Interrupt Enable (In Buffer Modes Only). bit mask. */
#define FPGA_SPI_DREIE_bp  5  /* Data Register Empty Interrupt Enable (In Buffer Modes Only). bit position. */

#define FPGA_SPI_SSIE_bm  0x10  /* Slave Select Trigger Interrupt Enable (In Buffer Modes Only). bit mask. */
#define FPGA_SPI_SSIE_bp  4  /* Slave Select Trigger Interrupt Enable (In Buffer Modes Only). bit position. */

#define FPGA_SPI_INTLVL_gm  0x03  /* Interrupt level group mask. */
#define FPGA_SPI_INTLVL_gp  0  /* Interrupt level group position. */
#define FPGA_SPI_INTLVL0_bm  (1<<0)  /* Interrupt level bit 0 mask. */
#define FPGA_SPI_INTLVL0_bp  0  /* Interrupt level bit 0 position. */
#define FPGA_SPI_INTLVL1_bm  (1<<1)  /* Interrupt level bit 1 mask. */
#define FPGA_SPI_INTLVL1_bp  1  /* Interrupt level bit 1 position. */

/* SPI.STATUS  bit masks and bit positions */
#define FPGA_SPI_IF_bm  0x80  /* Interrupt Flag (In Standard Mode Only). bit mask. */
#define FPGA_SPI_IF_bp  7  /* Interrupt Flag (In Standard Mode Only). bit position. */

#define FPGA_SPI_RXCIF_bm  0x80  /* Receive Complete Interrupt Flag (In Buffer Modes Only). bit mask. */
#define FPGA_SPI_RXCIF_bp  7  /* Receive Complete Interrupt Flag (In Buffer Modes Only). bit position. */

#define FPGA_SPI_WRCOL_bm  0x40  /* Write Collision Flag (In Standard Mode Only). bit mask. */
#define FPGA_SPI_WRCOL_bp  6  /* Write Collision Flag (In Standard Mode Only). bit position. */

#define FPGA_SPI_TXCIF_bm  0x40  /* Transmit Complete Interrupt Flag (In Buffer Modes Only). bit mask. */
#define FPGA_SPI_TXCIF_bp  6  /* Transmit Complete Interrupt Flag (In Buffer Modes Only). bit position. */

#define FPGA_SPI_DREIF_bm  0x20  /* Data Register Empty Interrupt Flag (In Buffer Modes Only). bit mask. */
#define FPGA_SPI_DREIF_bp  5  /* Data Register Empty Interrupt Flag (In Buffer Modes Only). bit position. */

#define FPGA_SPI_SSIF_bm  0x10  /* Slave Select Trigger Interrupt Flag (In Buffer Modes Only). bit mask. */
#define FPGA_SPI_SSIF_bp  4  /* Slave Select Trigger Interrupt Flag (In Buffer Modes Only). bit position. */

#define FPGA_SPI_BUFOVF_bm  0x01  /* Buffer Overflow (In Buffer Modes Only). bit mask. */
#define FPGA_SPI_BUFOVF_bp  0  /* Buffer Overflow (In Buffer Modes Only). bit position. */

/* SPI.CTRLB  bit masks and bit positions */
#define FPGA_SPI_BUFMODE_gm  0xC0  /* Buffer Modes group mask. */
#define FPGA_SPI_BUFMODE_gp  6  /* Buffer Modes group position. */
#define FPGA_SPI_BUFMODE0_bm  (1<<6)  /* Buffer Modes bit 0 mask. */
#define FPGA_SPI_BUFMODE0_bp  6  /* Buffer Modes bit 0 position. */
#define FPGA_SPI_BUFMODE1_bm  (1<<7)  /* Buffer Modes bit 1 mask. */
#define FPGA_SPI_BUFMODE1_bp  7  /* Buffer Modes bit 1 position. */

#define FPGA_SPI_SSD_bm  0x04  /* Slave Select Disable bit mask. */
#define FPGA_SPI_SSD_bp  2  /* Slave Select Disable bit position. */


/*
--------------------------------------------------------------------------
USART - Universal Asynchronous Receiver-Transmitter
--------------------------------------------------------------------------
*/

/* Universal Synchronous/Asynchronous Receiver/Transmitter */
typedef struct FPGA_USART_struct
{
	register8_t DATA;  /* Data Register */
	register8_t STATUS;  /* Status Register */
	register8_t CTRLA;  /* Control Register A */
	register8_t CTRLB;  /* Control Register B */
	register8_t CTRLC;  /* Control Register C */
	register8_t CTRLD;  /* Control Register D */
	register8_t BAUDCTRLA;  /* Baud Rate Control Register A */
	register8_t BAUDCTRLB;  /* Baud Rate Control Register B */
} FPGA_USART_t;

/* USART.CTRLA  bit masks and bit positions */
/* Receive Start Interrupt level */
typedef enum FPGA_USART_RXSINTLVL_enum
{
	FPGA_USART_RXSINTLVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
	FPGA_USART_RXSINTLVL_LO_gc = (0x01<<0),  /* Low Level */
	FPGA_USART_RXSINTLVL_MED_gc = (0x02<<0),  /* Medium Level */
	FPGA_USART_RXSINTLVL_HI_gc = (0x03<<0),  /* High Level */
} FPGA_USART_RXSINTLVL_t;

/* Receive Complete Interrupt level */
typedef enum FPGA_USART_RXCINTLVL_enum
{
	FPGA_USART_RXCINTLVL_OFF_gc = (0x00<<4),  /* Interrupt Disabled */
	FPGA_USART_RXCINTLVL_LO_gc = (0x01<<4),  /* Low Level */
	FPGA_USART_RXCINTLVL_MED_gc = (0x02<<4),  /* Medium Level */
	FPGA_USART_RXCINTLVL_HI_gc = (0x03<<4),  /* High Level */
} FPGA_USART_RXCINTLVL_t;

/* Transmit Complete Interrupt level */
typedef enum FPGA_USART_TXCINTLVL_enum
{
	FPGA_USART_TXCINTLVL_OFF_gc = (0x00<<2),  /* Interrupt Disabled */
	FPGA_USART_TXCINTLVL_LO_gc = (0x01<<2),  /* Low Level */
	FPGA_USART_TXCINTLVL_MED_gc = (0x02<<2),  /* Medium Level */
	FPGA_USART_TXCINTLVL_HI_gc = (0x03<<2),  /* High Level */
} FPGA_USART_TXCINTLVL_t;

/* Data Register Empty Interrupt level */
typedef enum FPGA_USART_DREINTLVL_enum
{
	FPGA_USART_DREINTLVL_OFF_gc = (0x00<<0),  /* Interrupt Disabled */
	FPGA_USART_DREINTLVL_LO_gc = (0x01<<0),  /* Low Level */
	FPGA_USART_DREINTLVL_MED_gc = (0x02<<0),  /* Medium Level */
	FPGA_USART_DREINTLVL_HI_gc = (0x03<<0),  /* High Level */
} FPGA_USART_DREINTLVL_t;

/* USART.CTRLB  bit masks and bit positions */
#define FPGA_USART_ONEWIRE_bm  0x80  /* One Wire Mode bit mask. */
#define FPGA_USART_ONEWIRE_bp  7  /* One Wire Mode bit position. */

#define FPGA_USART_SFDEN_bm  0x40  /* Start Frame Detection Enable bit mask. */
#define FPGA_USART_SFDEN_bp  6  /* Start Frame Detection Enable bit position. */

#define FPGA_USART_RXEN_bm  0x10  /* Receiver Enable bit mask. */
#define FPGA_USART_RXEN_bp  4  /* Receiver Enable bit position. */

#define FPGA_USART_TXEN_bm  0x08  /* Transmitter Enable bit mask. */
#define FPGA_USART_TXEN_bp  3  /* Transmitter Enable bit position. */

#define FPGA_USART_CLK2X_bm  0x04  /* Double transmission speed bit mask. */
#define FPGA_USART_CLK2X_bp  2  /* Double transmission speed bit position. */

#define FPGA_USART_MPCM_bm  0x02  /* Multi-processor Communication Mode bit mask. */
#define FPGA_USART_MPCM_bp  1  /* Multi-processor Communication Mode bit position. */

#define FPGA_USART_TXB8_bm  0x01  /* Transmit bit 8 bit mask. */
#define FPGA_USART_TXB8_bp  0  /* Transmit bit 8 bit position. */

/* USART.CTRLC  bit masks and bit positions */
/* Character Size */
typedef enum FPGA_USART_CHSIZE_enum
{
	FPGA_USART_CHSIZE_5BIT_gc = (0x00<<0),  /* Character size: 5 bit */
	FPGA_USART_CHSIZE_6BIT_gc = (0x01<<0),  /* Character size: 6 bit */
	FPGA_USART_CHSIZE_7BIT_gc = (0x02<<0),  /* Character size: 7 bit */
	FPGA_USART_CHSIZE_8BIT_gc = (0x03<<0),  /* Character size: 8 bit */
	FPGA_USART_CHSIZE_9BIT_gc = (0x07<<0),  /* Character size: 9 bit */
} FPGA_USART_CHSIZE_t;

/* Communication Mode */
typedef enum FPGA_USART_CMODE_enum
{
	FPGA_USART_CMODE_ASYNCHRONOUS_gc = (0x00<<6),  /* Asynchronous Mode */
	FPGA_USART_CMODE_SYNCHRONOUS_gc = (0x01<<6),  /* Synchronous Mode */
	FPGA_USART_CMODE_IRDA_gc = (0x02<<6),  /* IrDA Mode */
	FPGA_USART_CMODE_MSPI_gc = (0x03<<6),  /* Master SPI Mode */
} FPGA_USART_CMODE_t;

/* Parity Mode */
typedef enum FPGA_USART_PMODE_enum
{
	FPGA_USART_PMODE_DISABLED_gc = (0x00<<4),  /* No Parity */
	FPGA_USART_PMODE_EVEN_gc = (0x02<<4),  /* Even Parity */
	FPGA_USART_PMODE_ODD_gc = (0x03<<4),  /* Odd Parity */
} FPGA_USART_PMODE_t;

/* Encoding and Decoding Type */
typedef enum FPGA_USART_DECTYPE_enum
{
	FPGA_USART_DECTYPE_DATA_gc = (0x00<<4),  /* DATA Field Encoding */
	FPGA_USART_DECTYPE_SDATA_gc = (0x02<<4),  /* Start and Data Fields Encoding */
	FPGA_USART_DECTYPE_NOTSDATA_gc = (0x03<<4),  /* Start and Data Fields Encoding, with invertion in START field */
} FPGA_USART_DECTYPE_t;

/* XCL LUT Action */
typedef enum FPGA_USART_LUTACT_enum
{
	FPGA_USART_LUTACT_OFF_gc = (0x00<<2),  /* Standard Frame Configuration */
	FPGA_USART_LUTACT_RX_gc = (0x01<<2),  /* Receiver Decoding Enabled */
	FPGA_USART_LUTACT_TX_gc = (0x02<<2),  /* Transmitter Encoding Enabled */
	FPGA_USART_LUTACT_BOTH_gc = (0x03<<2),  /* Both Encoding and Decoding Enabled */
} FPGA_USART_LUTACT_t;

/* XCL Peripheral Counter Action */
typedef enum FPGA_USART_PECACT_enum
{
	FPGA_USART_PECACT_OFF_gc = (0x00<<0),  /* Standard Mode */
	FPGA_USART_PECACT_PEC0_gc = (0x01<<0),  /* Variable Data Lenght in Reception */
	FPGA_USART_PECACT_PEC1_gc = (0x02<<0),  /* Variable Data Lenght in Transmission */
	FPGA_USART_PECACT_PERC01_gc = (0x03<<0),  /* Variable Data Lenght in both Reception and Transmission */
} FPGA_USART_PECACT_t;

/* USART - Universal Asynchronous Receiver-Transmitter */
/* USART.STATUS  bit masks and bit positions */
#define FPGA_USART_RXCIF_bm  0x80  /* Receive Interrupt Flag bit mask. */
#define FPGA_USART_RXCIF_bp  7  /* Receive Interrupt Flag bit position. */

#define FPGA_USART_TXCIF_bm  0x40  /* Transmit Interrupt Flag bit mask. */
#define FPGA_USART_TXCIF_bp  6  /* Transmit Interrupt Flag bit position. */

#define FPGA_USART_DREIF_bm  0x20  /* Data Register Empty Flag bit mask. */
#define FPGA_USART_DREIF_bp  5  /* Data Register Empty Flag bit position. */

#define FPGA_USART_FERR_bm  0x10  /* Frame Error bit mask. */
#define FPGA_USART_FERR_bp  4  /* Frame Error bit position. */

#define FPGA_USART_BUFOVF_bm  0x08  /* Buffer Overflow bit mask. */
#define FPGA_USART_BUFOVF_bp  3  /* Buffer Overflow bit position. */

#define FPGA_USART_PERR_bm  0x04  /* Parity Error bit mask. */
#define FPGA_USART_PERR_bp  2  /* Parity Error bit position. */

#define FPGA_USART_RXSIF_bm  0x02  /* Receive Start Bit Interrupt Flag bit mask. */
#define FPGA_USART_RXSIF_bp  1  /* Receive Start Bit Interrupt Flag bit position. */

#define FPGA_USART_RXB8_bm  0x01  /* Receive Bit 8 bit mask. */
#define FPGA_USART_RXB8_bp  0  /* Receive Bit 8 bit position. */

#define FPGA_USART_DRIF_bm  0x01  /* Data Reception Flag bit mask. */
#define FPGA_USART_DRIF_bp  0  /* Data Reception Flag bit position. */

/* USART.CTRLA  bit masks and bit positions */
#define FPGA_USART_RXSIE_bm  0x80  /* Receive Start Interrupt Enable bit mask. */
#define FPGA_USART_RXSIE_bp  7  /* Receive Start Interrupt Enable bit position. */

#define FPGA_USART_DRIE_bm  0x40  /* Data Reception Interrupt Enable bit mask. */
#define USART_DRIE_bp  6  /* Data Reception Interrupt Enable bit position. */

#define FPGA_USART_RXCINTLVL_gm  0x30  /* Receive Interrupt Level group mask. */
#define FPGA_USART_RXCINTLVL_gp  4  /* Receive Interrupt Level group position. */
#define FPGA_USART_RXCINTLVL0_bm  (1<<4)  /* Receive Interrupt Level bit 0 mask. */
#define FPGA_USART_RXCINTLVL0_bp  4  /* Receive Interrupt Level bit 0 position. */
#define FPGA_USART_RXCINTLVL1_bm  (1<<5)  /* Receive Interrupt Level bit 1 mask. */
#define FPGA_USART_RXCINTLVL1_bp  5  /* Receive Interrupt Level bit 1 position. */

#define FPGA_USART_TXCINTLVL_gm  0x0C  /* Transmit Interrupt Level group mask. */
#define FPGA_USART_TXCINTLVL_gp  2  /* Transmit Interrupt Level group position. */
#define FPGA_USART_TXCINTLVL0_bm  (1<<2)  /* Transmit Interrupt Level bit 0 mask. */
#define FPGA_USART_TXCINTLVL0_bp  2  /* Transmit Interrupt Level bit 0 position. */
#define FPGA_USART_TXCINTLVL1_bm  (1<<3)  /* Transmit Interrupt Level bit 1 mask. */
#define FPGA_USART_TXCINTLVL1_bp  3  /* Transmit Interrupt Level bit 1 position. */

#define FPGA_USART_DREINTLVL_gm  0x03  /* Data Register Empty Interrupt Level group mask. */
#define FPGA_USART_DREINTLVL_gp  0  /* Data Register Empty Interrupt Level group position. */
#define FPGA_USART_DREINTLVL0_bm  (1<<0)  /* Data Register Empty Interrupt Level bit 0 mask. */
#define FPGA_USART_DREINTLVL0_bp  0  /* Data Register Empty Interrupt Level bit 0 position. */
#define FPGA_USART_DREINTLVL1_bm  (1<<1)  /* Data Register Empty Interrupt Level bit 1 mask. */
#define FPGA_USART_DREINTLVL1_bp  1  /* Data Register Empty Interrupt Level bit 1 position. */

/* USART.CTRLB  bit masks and bit positions */
#define FPGA_USART_ONEWIRE_bm  0x80  /* One Wire Mode bit mask. */
#define FPGA_USART_ONEWIRE_bp  7  /* One Wire Mode bit position. */

#define FPGA_USART_SFDEN_bm  0x40  /* Start Frame Detection Enable bit mask. */
#define FPGA_USART_SFDEN_bp  6  /* Start Frame Detection Enable bit position. */

#define FPGA_USART_RXEN_bm  0x10  /* Receiver Enable bit mask. */
#define FPGA_USART_RXEN_bp  4  /* Receiver Enable bit position. */

#define FPGA_USART_TXEN_bm  0x08  /* Transmitter Enable bit mask. */
#define FPGA_USART_TXEN_bp  3  /* Transmitter Enable bit position. */

#define FPGA_USART_CLK2X_bm  0x04  /* Double transmission speed bit mask. */
#define FPGA_USART_CLK2X_bp  2  /* Double transmission speed bit position. */

#define FPGA_USART_MPCM_bm  0x02  /* Multi-processor Communication Mode bit mask. */
#define FPGA_USART_MPCM_bp  1  /* Multi-processor Communication Mode bit position. */

#define FPGA_USART_TXB8_bm  0x01  /* Transmit bit 8 bit mask. */
#define FPGA_USART_TXB8_bp  0  /* Transmit bit 8 bit position. */

/* USART.CTRLC  bit masks and bit positions */
#define FPGA_USART_CMODE_gm  0xC0  /* Communication Mode group mask. */
#define FPGA_USART_CMODE_gp  6  /* Communication Mode group position. */
#define FPGA_USART_CMODE0_bm  (1<<6)  /* Communication Mode bit 0 mask. */
#define FPGA_USART_CMODE0_bp  6  /* Communication Mode bit 0 position. */
#define FPGA_USART_CMODE1_bm  (1<<7)  /* Communication Mode bit 1 mask. */
#define FPGA_USART_CMODE1_bp  7  /* Communication Mode bit 1 position. */

#define FPGA_USART_PMODE_gm  0x30  /* Parity Mode group mask. */
#define FPGA_USART_PMODE_gp  4  /* Parity Mode group position. */
#define FPGA_USART_PMODE0_bm  (1<<4)  /* Parity Mode bit 0 mask. */
#define FPGA_USART_PMODE0_bp  4  /* Parity Mode bit 0 position. */
#define FPGA_USART_PMODE1_bm  (1<<5)  /* Parity Mode bit 1 mask. */
#define FPGA_USART_PMODE1_bp  5  /* Parity Mode bit 1 position. */

#define FPGA_USART_SBMODE_bm  0x08  /* Stop Bit Mode bit mask. */
#define FPGA_USART_SBMODE_bp  3  /* Stop Bit Mode bit position. */

#define FPGA_USART_CHSIZE_gm  0x07  /* Character Size group mask. */
#define FPGA_USART_CHSIZE_gp  0  /* Character Size group position. */
#define FPGA_USART_CHSIZE0_bm  (1<<0)  /* Character Size bit 0 mask. */
#define FPGA_USART_CHSIZE0_bp  0  /* Character Size bit 0 position. */
#define FPGA_USART_CHSIZE1_bm  (1<<1)  /* Character Size bit 1 mask. */
#define FPGA_USART_CHSIZE1_bp  1  /* Character Size bit 1 position. */
#define FPGA_USART_CHSIZE2_bm  (1<<2)  /* Character Size bit 2 mask. */
#define FPGA_USART_CHSIZE2_bp  2  /* Character Size bit 2 position. */

/* USART.CTRLD  bit masks and bit positions */
#define FPGA_USART_DECTYPE_gm  0x30  /* Receive Interrupt Level group mask. */
#define FPGA_USART_DECTYPE_gp  4  /* Receive Interrupt Level group position. */
#define FPGA_USART_DECTYPE0_bm  (1<<4)  /* Receive Interrupt Level bit 0 mask. */
#define FPGA_USART_DECTYPE0_bp  4  /* Receive Interrupt Level bit 0 position. */
#define FPGA_USART_DECTYPE1_bm  (1<<5)  /* Receive Interrupt Level bit 1 mask. */
#define FPGA_USART_DECTYPE1_bp  5  /* Receive Interrupt Level bit 1 position. */

#define FPGA_USART_LUTACT_gm  0x0C  /* Transmit Interrupt Level group mask. */
#define FPGA_USART_LUTACT_gp  2  /* Transmit Interrupt Level group position. */
#define FPGA_USART_LUTACT0_bm  (1<<2)  /* Transmit Interrupt Level bit 0 mask. */
#define FPGA_USART_LUTACT0_bp  2  /* Transmit Interrupt Level bit 0 position. */
#define FPGA_USART_LUTACT1_bm  (1<<3)  /* Transmit Interrupt Level bit 1 mask. */
#define FPGA_USART_LUTACT1_bp  3  /* Transmit Interrupt Level bit 1 position. */

#define FPGA_USART_PECACT_gm  0x03  /* Data Register Empty Interrupt Level group mask. */
#define FPGA_USART_PECACT_gp  0  /* Data Register Empty Interrupt Level group position. */
#define FPGA_USART_PECACT0_bm  (1<<0)  /* Data Register Empty Interrupt Level bit 0 mask. */
#define FPGA_USART_PECACT0_bp  0  /* Data Register Empty Interrupt Level bit 0 position. */
#define FPGA_USART_PECACT1_bm  (1<<1)  /* Data Register Empty Interrupt Level bit 1 mask. */
#define FPGA_USART_PECACT1_bp  1  /* Data Register Empty Interrupt Level bit 1 position. */

/* USART.BAUDCTRLA  bit masks and bit positions */
#define FPGA_USART_BSEL_gm  0xFF  /* Baud Rate Selection Bits [7:0] group mask. */
#define FPGA_USART_BSEL_gp  0  /* Baud Rate Selection Bits [7:0] group position. */
#define FPGA_USART_BSEL0_bm  (1<<0)  /* Baud Rate Selection Bits [7:0] bit 0 mask. */
#define FPGA_USART_BSEL0_bp  0  /* Baud Rate Selection Bits [7:0] bit 0 position. */
#define FPGA_USART_BSEL1_bm  (1<<1)  /* Baud Rate Selection Bits [7:0] bit 1 mask. */
#define FPGA_USART_BSEL1_bp  1  /* Baud Rate Selection Bits [7:0] bit 1 position. */
#define FPGA_USART_BSEL2_bm  (1<<2)  /* Baud Rate Selection Bits [7:0] bit 2 mask. */
#define FPGA_USART_BSEL2_bp  2  /* Baud Rate Selection Bits [7:0] bit 2 position. */
#define FPGA_USART_BSEL3_bm  (1<<3)  /* Baud Rate Selection Bits [7:0] bit 3 mask. */
#define FPGA_USART_BSEL3_bp  3  /* Baud Rate Selection Bits [7:0] bit 3 position. */
#define FPGA_USART_BSEL4_bm  (1<<4)  /* Baud Rate Selection Bits [7:0] bit 4 mask. */
#define FPGA_USART_BSEL4_bp  4  /* Baud Rate Selection Bits [7:0] bit 4 position. */
#define FPGA_USART_BSEL5_bm  (1<<5)  /* Baud Rate Selection Bits [7:0] bit 5 mask. */
#define FPGA_USART_BSEL5_bp  5  /* Baud Rate Selection Bits [7:0] bit 5 position. */
#define FPGA_USART_BSEL6_bm  (1<<6)  /* Baud Rate Selection Bits [7:0] bit 6 mask. */
#define FPGA_USART_BSEL6_bp  6  /* Baud Rate Selection Bits [7:0] bit 6 position. */
#define FPGA_USART_BSEL7_bm  (1<<7)  /* Baud Rate Selection Bits [7:0] bit 7 mask. */
#define FPGA_USART_BSEL7_bp  7  /* Baud Rate Selection Bits [7:0] bit 7 position. */

/* USART.BAUDCTRLB  bit masks and bit positions */
#define FPGA_USART_BSCALE_gm  0xF0  /* Baud Rate Scale group mask. */
#define FPGA_USART_BSCALE_gp  4  /* Baud Rate Scale group position. */
#define FPGA_USART_BSCALE0_bm  (1<<4)  /* Baud Rate Scale bit 0 mask. */
#define FPGA_USART_BSCALE0_bp  4  /* Baud Rate Scale bit 0 position. */
#define FPGA_USART_BSCALE1_bm  (1<<5)  /* Baud Rate Scale bit 1 mask. */
#define FPGA_USART_BSCALE1_bp  5  /* Baud Rate Scale bit 1 position. */
#define FPGA_USART_BSCALE2_bm  (1<<6)  /* Baud Rate Scale bit 2 mask. */
#define FPGA_USART_BSCALE2_bp  6  /* Baud Rate Scale bit 2 position. */
#define FPGA_USART_BSCALE3_bm  (1<<7)  /* Baud Rate Scale bit 3 mask. */
#define FPGA_USART_BSCALE3_bp  7  /* Baud Rate Scale bit 3 position. */

/* USART_BSEL  Predefined. */
/* USART_BSEL  Predefined. */


/*
--------------------------------------------------------------------------
LCD - LCD display Interface
--------------------------------------------------------------------------
*/

/* Universal Synchronous/Asynchronous Receiver/Transmitter */
typedef struct FPGA_LCD_struct
{
	register32_t LCD_CTRL; 				// 0x00
	register32_t LCD_H_RES; 			// 0x04
	register32_t LCD_H_PULSE_WIDTH; 	// 0x08
	register32_t LCD_H_BACK_PORCH; 		// 0x0c
	register32_t LCD_H_FRONT_PORCH; 	// 0x10
	register32_t LCD_V_RES; 			// 0x14
	register32_t LCD_V_PULSE_WIDTH; 	// 0x18
	register32_t LCD_V_BACK_PORCH; 		// 0x1c
	register32_t LCD_V_FRONT_PORCH; 	// 0x20
	register32_t LCD_PIXEL_SIZE; 		// 0x24
	register32_t LCD_BASE_ADDR; 		// 0x28
	register32_t LCD_RESERVED_1; 		// 0x2c
	register32_t LCD_RESERVED_2; 		// 0x30
	register32_t LCD_RESERVED_3; 		// 0x34
	register32_t LCD_RESERVED_4; 		// 0x38
	register32_t LCD_RESERVED_5; 		// 0x3c
} FPGA_LCD_t;

#define EN_bp						0
#define EN_bm						1

#define HSYNK_INVERTED_bp			1
#define HSYNK_INVERTED_bm			2

#define VSYNK_INVERTED_bp			2
#define VSYNK_INVERTED_bm			4

#define DATA_ENABLE_INVERTED_bp		3
#define DATA_ENABLE_INVERTED_bm		8

/*
--------------------------------------------------------------------------
GFX_ACCEL - GFX_ACCEL LCD display 2D accelerator interface
--------------------------------------------------------------------------
*/

typedef struct FPGA_GFX_ACCEL_struct
{
	FPGA_LCD_t LCD; 					// 0x00
	register32_t GFX_ACCEL_CMD; 		// 0x40
	register32_t GFX_ACCEL_CLIP_X_MIN; 	// 0x44
	register32_t GFX_ACCEL_CLIP_X_MAX; 	// 0x48
	register32_t GFX_ACCEL_CLIP_Y_MIN; 	// 0x4c
	register32_t GFX_ACCEL_CLIP_Y_MAX; 	// 0x50
	register32_t GFX_ACCEL_COLOR; 		// 0x54
} FPGA_GFX_ACCEL_t;

#define GFX_ACCEL_CMD_IDLE			0
#define GFX_ACCEL_CMD_VRAM_ACCESS	1
#define GFX_ACCEL_CMD_PIXEL_LOAD	2
#define GFX_ACCEL_CMD_PIXEL			3
#define GFX_ACCEL_CMD_CTRL_ACCESS	4
#define GFX_ACCEL_CMD_FILL_RECT		5
#define GFX_ACCEL_CMD_OFF			253
#define GFX_ACCEL_CMD_ON			254

#endif
