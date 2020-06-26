/*
 * rf69h.h
 *
 *  Created on: Jan 25, 2018
 *      Author: Work
 */

#ifndef RF69H_H_
#define RF69H_H_
/*#####################################################*/
#include <include/global.h>
#include <api/io_handle.h>
#include <api/timer.h>
#include "common.h"
/*#####################################################*/
/*
 * Derinitions writed by:
 * Copyright Felix Rusu (2015), felix@lowpowerlab.com
 * http://lowpowerlab.com/
 */
#define RF69_REG_FIFO          0x00
#define RF69_REG_OPMODE        0x01
#define RF69_REG_DATAMODUL     0x02
#define RF69_REG_BITRATEMSB    0x03
#define RF69_REG_BITRATELSB    0x04
#define RF69_REG_FDEVMSB       0x05
#define RF69_REG_FDEVLSB       0x06
#define RF69_REG_FRFMSB        0x07
#define RF69_REG_FRFMID        0x08
#define RF69_REG_FRFLSB        0x09
#define RF69_REG_OSC1          0x0A
#define RF69_REG_AFCCTRL       0x0B
#define RF69_REG_LOWBAT        0x0C
#define RF69_REG_LISTEN1       0x0D
#define RF69_REG_LISTEN2       0x0E
#define RF69_REG_LISTEN3       0x0F
#define RF69_REG_VERSION       0x10
#define RF69_REG_PALEVEL       0x11
#define RF69_REG_PARAMP        0x12
#define RF69_REG_OCP           0x13
#define RF69_REG_AGCREF        0x14  // not present on RFM69/SX1231
#define RF69_REG_AGCTHRESH1    0x15  // not present on RFM69/SX1231
#define RF69_REG_AGCTHRESH2    0x16  // not present on RFM69/SX1231
#define RF69_REG_AGCTHRESH3    0x17  // not present on RFM69/SX1231
#define RF69_REG_LNA           0x18
#define RF69_REG_RXBW          0x19
#define RF69_REG_AFCBW         0x1A
#define RF69_REG_OOKPEAK       0x1B
#define RF69_REG_OOKAVG        0x1C
#define RF69_REG_OOKFIX        0x1D
#define RF69_REG_AFCFEI        0x1E
#define RF69_REG_AFCMSB        0x1F
#define RF69_REG_AFCLSB        0x20
#define RF69_REG_FEIMSB        0x21
#define RF69_REG_FEILSB        0x22
#define RF69_REG_RSSICONFIG    0x23
#define RF69_REG_RSSIVALUE     0x24
#define RF69_REG_DIOMAPPING1   0x25
#define RF69_REG_DIOMAPPING2   0x26
#define RF69_REG_IRQFLAGS1     0x27
#define RF69_REG_IRQFLAGS2     0x28
#define RF69_REG_RSSITHRESH    0x29
#define RF69_REG_RXTIMEOUT1    0x2A
#define RF69_REG_RXTIMEOUT2    0x2B
#define REG_PREAMBLEMSB   0x2C
#define RF69_REG_PREAMBLELSB   0x2D
#define RF69_REG_SYNCCONFIG    0x2E
#define RF69_REG_SYNCVALUE1    0x2F
#define RF69_REG_SYNCVALUE2    0x30
#define RF69_REG_SYNCVALUE3    0x31
#define RF69_REG_SYNCVALUE4    0x32
#define RF69_REG_SYNCVALUE5    0x33
#define RF69_REG_SYNCVALUE6    0x34
#define RF69_REG_SYNCVALUE7    0x35
#define RF69_REG_SYNCVALUE8    0x36
#define RF69_REG_PACKETCONFIG1 0x37
#define RF69_REG_PAYLOADLENGTH 0x38
#define RF69_REG_NODEADRS      0x39
#define RF69_REG_BROADCASTADRS 0x3A
#define RF69_REG_AUTOMODES     0x3B
#define RF69_REG_FIFOTHRESH    0x3C
#define RF69_REG_PACKETCONFIG2 0x3D
#define RF69_REG_AESKEY1       0x3E
#define RF69_REG_AESKEY2       0x3F
#define RF69_REG_AESKEY3       0x40
#define RF69_REG_AESKEY4       0x41
#define RF69_REG_AESKEY5       0x42
#define RF69_REG_AESKEY6       0x43
#define RF69_REG_AESKEY7       0x44
#define RF69_REG_AESKEY8       0x45
#define RF69_REG_AESKEY9       0x46
#define RF69_REG_AESKEY10      0x47
#define RF69_REG_AESKEY11      0x48
#define RF69_REG_AESKEY12      0x49
#define RF69_REG_AESKEY13      0x4A
#define RF69_REG_AESKEY14      0x4B
#define RF69_REG_AESKEY15      0x4C
#define RF69_REG_AESKEY16      0x4D
#define RF69_REG_TEMP1         0x4E
#define RF69_REG_TEMP2         0x4F
#define RF69_REG_TESTLNA       0x58
#define RF69_REG_TESTPA1       0x5A  // only present on RFM69HW/SX1231H
#define RF69_REG_TESTPA2       0x5C  // only present on RFM69HW/SX1231H
#define RF69_REG_TESTDAGC      0x6F

//******************************************************
// RF69/SX1231 bit control definition
//******************************************************

// RegOpMode
#define RF69_OPMODE_SEQUENCER_OFF       0x80
#define RF69_OPMODE_SEQUENCER_ON        0x00  // Default

#define RF69_OPMODE_LISTEN_ON           0x40
#define RF69_OPMODE_LISTEN_OFF          0x00  // Default

#define RF69_OPMODE_LISTENABORT         0x20

#define RF69_OPMODE_SLEEP               0x00
#define RF69_OPMODE_STANDBY             0x04  // Default
#define RF69_OPMODE_SYNTHESIZER         0x08
#define RF69_OPMODE_TRANSMITTER         0x0C
#define RF69_OPMODE_RECEIVER            0x10


// RegDataModul
#define RF69_DATAMODUL_DATAMODE_PACKET            0x00  // Default
#define RF69_DATAMODUL_DATAMODE_CONTINUOUS        0x40
#define RF69_DATAMODUL_DATAMODE_CONTINUOUSNOBSYNC 0x60

#define RF69_DATAMODUL_MODULATIONTYPE_FSK         0x00  // Default
#define RF69_DATAMODUL_MODULATIONTYPE_OOK         0x08

#define RF69_DATAMODUL_MODULATIONSHAPING_00       0x00  // Default
#define RF69_DATAMODUL_MODULATIONSHAPING_01       0x01
#define RF69_DATAMODUL_MODULATIONSHAPING_10       0x02
#define RF69_DATAMODUL_MODULATIONSHAPING_11       0x03


// RegBitRate (bits/sec) example bit rates
#define RF69_BITRATEMSB_1200            0x68
#define RF69_BITRATELSB_1200            0x2B
#define RF69_BITRATEMSB_2400            0x34
#define RF69_BITRATELSB_2400            0x15
#define RF69_BITRATEMSB_4800            0x1A  // Default
#define RF69_BITRATELSB_4800            0x0B  // Default
#define RF69_BITRATEMSB_9600            0x0D
#define RF69_BITRATELSB_9600            0x05
#define RF69_BITRATEMSB_19200           0x06
#define RF69_BITRATELSB_19200           0x83
#define RF69_BITRATEMSB_38400           0x03
#define RF69_BITRATELSB_38400           0x41

#define RF69_BITRATEMSB_38323           0x03
#define RF69_BITRATELSB_38323           0x43

#define RF69_BITRATEMSB_34482           0x03
#define RF69_BITRATELSB_34482           0xA0

#define RF69_BITRATEMSB_76800           0x01
#define RF69_BITRATELSB_76800           0xA1
#define RF69_BITRATEMSB_153600          0x00
#define RF69_BITRATELSB_153600          0xD0
#define RF69_BITRATEMSB_57600           0x02
#define RF69_BITRATELSB_57600           0x2C
#define RF69_BITRATEMSB_115200          0x01
#define RF69_BITRATELSB_115200          0x16
#define RF69_BITRATEMSB_12500           0x0A
#define RF69_BITRATELSB_12500           0x00
#define RF69_BITRATEMSB_25000           0x05
#define RF69_BITRATELSB_25000           0x00
#define RF69_BITRATEMSB_50000           0x02
#define RF69_BITRATELSB_50000           0x80
#define RF69_BITRATEMSB_100000          0x01
#define RF69_BITRATELSB_100000          0x40
#define RF69_BITRATEMSB_150000          0x00
#define RF69_BITRATELSB_150000          0xD5
#define RF69_BITRATEMSB_200000          0x00
#define RF69_BITRATELSB_200000          0xA0
#define RF69_BITRATEMSB_250000          0x00
#define RF69_BITRATELSB_250000          0x80
#define RF69_BITRATEMSB_300000          0x00
#define RF69_BITRATELSB_300000          0x6B
#define RF69_BITRATEMSB_32768           0x03
#define RF69_BITRATELSB_32768           0xD1
// custom bit rates
#define RF69_BITRATEMSB_55555           0x02
#define RF69_BITRATELSB_55555           0x40
#define RF69_BITRATEMSB_200KBPS         0x00
#define RF69_BITRATELSB_200KBPS         0xa0


// RegFdev - frequency deviation (Hz)
#define RF69_FDEVMSB_2000             0x00
#define RF69_FDEVLSB_2000             0x21
#define RF69_FDEVMSB_5000             0x00  // Default
#define RF69_FDEVLSB_5000             0x52  // Default
#define RF69_FDEVMSB_7500             0x00
#define RF69_FDEVLSB_7500             0x7B
#define RF69_FDEVMSB_10000            0x00
#define RF69_FDEVLSB_10000            0xA4
#define RF69_FDEVMSB_15000            0x00
#define RF69_FDEVLSB_15000            0xF6
#define RF69_FDEVMSB_20000            0x01
#define RF69_FDEVLSB_20000            0x48
#define RF69_FDEVMSB_25000            0x01
#define RF69_FDEVLSB_25000            0x9A
#define RF69_FDEVMSB_30000            0x01
#define RF69_FDEVLSB_30000            0xEC
#define RF69_FDEVMSB_35000            0x02
#define RF69_FDEVLSB_35000            0x3D
#define RF69_FDEVMSB_40000            0x02
#define RF69_FDEVLSB_40000            0x8F
#define RF69_FDEVMSB_45000            0x02
#define RF69_FDEVLSB_45000            0xE1
#define RF69_FDEVMSB_50000            0x03
#define RF69_FDEVLSB_50000            0x33
#define RF69_FDEVMSB_55000            0x03
#define RF69_FDEVLSB_55000            0x85
#define RF69_FDEVMSB_60000            0x03
#define RF69_FDEVLSB_60000            0xD7
#define RF69_FDEVMSB_65000            0x04
#define RF69_FDEVLSB_65000            0x29
#define RF69_FDEVMSB_70000            0x04
#define RF69_FDEVLSB_70000            0x7B
#define RF69_FDEVMSB_75000            0x04
#define RF69_FDEVLSB_75000            0xCD
#define RF69_FDEVMSB_80000            0x05
#define RF69_FDEVLSB_80000            0x1F
#define RF69_FDEVMSB_85000            0x05
#define RF69_FDEVLSB_85000            0x71
#define RF69_FDEVMSB_90000            0x05
#define RF69_FDEVLSB_90000            0xC3
#define RF69_FDEVMSB_95000            0x06
#define RF69_FDEVLSB_95000            0x14
#define RF69_FDEVMSB_100000           0x06
#define RF69_FDEVLSB_100000           0x66
#define RF69_FDEVMSB_110000           0x07
#define RF69_FDEVLSB_110000           0x0A
#define RF69_FDEVMSB_120000           0x07
#define RF69_FDEVLSB_120000           0xAE
#define RF69_FDEVMSB_130000           0x08
#define RF69_FDEVLSB_130000           0x52
#define RF69_FDEVMSB_140000           0x08
#define RF69_FDEVLSB_140000           0xF6
#define RF69_FDEVMSB_150000           0x09
#define RF69_FDEVLSB_150000           0x9A
#define RF69_FDEVMSB_160000           0x0A
#define RF69_FDEVLSB_160000           0x3D
#define RF69_FDEVMSB_170000           0x0A
#define RF69_FDEVLSB_170000           0xE1
#define RF69_FDEVMSB_180000           0x0B
#define RF69_FDEVLSB_180000           0x85
#define RF69_FDEVMSB_190000           0x0C
#define RF69_FDEVLSB_190000           0x29
#define RF69_FDEVMSB_200000           0x0C
#define RF69_FDEVLSB_200000           0xCD
#define RF69_FDEVMSB_210000           0x0D
#define RF69_FDEVLSB_210000           0x71
#define RF69_FDEVMSB_220000           0x0E
#define RF69_FDEVLSB_220000           0x14
#define RF69_FDEVMSB_230000           0x0E
#define RF69_FDEVLSB_230000           0xB8
#define RF69_FDEVMSB_240000           0x0F
#define RF69_FDEVLSB_240000           0x5C
#define RF69_FDEVMSB_250000           0x10
#define RF69_FDEVLSB_250000           0x00
#define RF69_FDEVMSB_260000           0x10
#define RF69_FDEVLSB_260000           0xA4
#define RF69_FDEVMSB_270000           0x11
#define RF69_FDEVLSB_270000           0x48
#define RF69_FDEVMSB_280000           0x11
#define RF69_FDEVLSB_280000           0xEC
#define RF69_FDEVMSB_290000           0x12
#define RF69_FDEVLSB_290000           0x8F
#define RF69_FDEVMSB_300000           0x13
#define RF69_FDEVLSB_300000           0x33


// RegOsc1
#define RF69_OSC1_RCCAL_START       0x80
#define RF69_OSC1_RCCAL_DONE        0x40


// RegAfcCtrl
#define RF69_AFCCTRL_LOWBETA_OFF    0x00  // Default
#define RF69_AFCCTRL_LOWBETA_ON     0x20


// RegLowBat
#define RF69_LOWBAT_MONITOR         0x10
#define RF69_LOWBAT_ON              0x08
#define RF69_LOWBAT_OFF             0x00  // Default

#define RF69_LOWBAT_TRIM_1695       0x00
#define RF69_LOWBAT_TRIM_1764       0x01
#define RF69_LOWBAT_TRIM_1835       0x02  // Default
#define RF69_LOWBAT_TRIM_1905       0x03
#define RF69_LOWBAT_TRIM_1976       0x04
#define RF69_LOWBAT_TRIM_2045       0x05
#define RF69_LOWBAT_TRIM_2116       0x06
#define RF69_LOWBAT_TRIM_2185       0x07


// RegListen1
#define RF69_LISTEN1_RESOL_64       0x50
#define RF69_LISTEN1_RESOL_4100     0xA0  // Default
#define RF69_LISTEN1_RESOL_262000   0xF0

#define RF69_LISTEN1_RESOL_IDLE_64     0x40
#define RF69_LISTEN1_RESOL_IDLE_4100   0x80  // Default
#define RF69_LISTEN1_RESOL_IDLE_262000 0xC0

#define RF69_LISTEN1_RESOL_RX_64       0x10
#define RF69_LISTEN1_RESOL_RX_4100     0x20  // Default
#define RF69_LISTEN1_RESOL_RX_262000   0x30

#define RF69_LISTEN1_CRITERIA_RSSI          0x00  // Default
#define RF69_LISTEN1_CRITERIA_RSSIANDSYNC   0x08

#define RF69_LISTEN1_END_00                 0x00
#define RF69_LISTEN1_END_01                 0x02  // Default
#define RF69_LISTEN1_END_10                 0x04


// RegListen2
#define RF69_LISTEN2_COEFIDLE_VALUE         0xF5 // Default


// RegListen3
#define RF69_LISTEN3_COEFRX_VALUE           0x20 // Default


// RegVersion
#define RF69_VERSION_VER        0x24  // Default


// RegPaLevel
#define RF69_PALEVEL_PA0_ON     0x80  // Default
#define RF69_PALEVEL_PA0_OFF    0x00
#define RF69_PALEVEL_PA1_ON     0x40
#define RF69_PALEVEL_PA1_OFF    0x00  // Default
#define RF69_PALEVEL_PA2_ON     0x20
#define RF69_PALEVEL_PA2_OFF    0x00  // Default

#define RF69_PALEVEL_OUTPUTPOWER_00000      0x00
#define RF69_PALEVEL_OUTPUTPOWER_00001      0x01
#define RF69_PALEVEL_OUTPUTPOWER_00010      0x02
#define RF69_PALEVEL_OUTPUTPOWER_00011      0x03
#define RF69_PALEVEL_OUTPUTPOWER_00100      0x04
#define RF69_PALEVEL_OUTPUTPOWER_00101      0x05
#define RF69_PALEVEL_OUTPUTPOWER_00110      0x06
#define RF69_PALEVEL_OUTPUTPOWER_00111      0x07
#define RF69_PALEVEL_OUTPUTPOWER_01000      0x08
#define RF69_PALEVEL_OUTPUTPOWER_01001      0x09
#define RF69_PALEVEL_OUTPUTPOWER_01010      0x0A
#define RF69_PALEVEL_OUTPUTPOWER_01011      0x0B
#define RF69_PALEVEL_OUTPUTPOWER_01100      0x0C
#define RF69_PALEVEL_OUTPUTPOWER_01101      0x0D
#define RF69_PALEVEL_OUTPUTPOWER_01110      0x0E
#define RF69_PALEVEL_OUTPUTPOWER_01111      0x0F
#define RF69_PALEVEL_OUTPUTPOWER_10000      0x10
#define RF69_PALEVEL_OUTPUTPOWER_10001      0x11
#define RF69_PALEVEL_OUTPUTPOWER_10010      0x12
#define RF69_PALEVEL_OUTPUTPOWER_10011      0x13
#define RF69_PALEVEL_OUTPUTPOWER_10100      0x14
#define RF69_PALEVEL_OUTPUTPOWER_10101      0x15
#define RF69_PALEVEL_OUTPUTPOWER_10110      0x16
#define RF69_PALEVEL_OUTPUTPOWER_10111      0x17
#define RF69_PALEVEL_OUTPUTPOWER_11000      0x18
#define RF69_PALEVEL_OUTPUTPOWER_11001      0x19
#define RF69_PALEVEL_OUTPUTPOWER_11010      0x1A
#define RF69_PALEVEL_OUTPUTPOWER_11011      0x1B
#define RF69_PALEVEL_OUTPUTPOWER_11100      0x1C
#define RF69_PALEVEL_OUTPUTPOWER_11101      0x1D
#define RF69_PALEVEL_OUTPUTPOWER_11110      0x1E
#define RF69_PALEVEL_OUTPUTPOWER_11111      0x1F  // Default


// RegPaRamp
#define RF69_PARAMP_3400            0x00
#define RF69_PARAMP_2000            0x01
#define RF69_PARAMP_1000            0x02
#define RF69_PARAMP_500             0x03
#define RF69_PARAMP_250             0x04
#define RF69_PARAMP_125             0x05
#define RF69_PARAMP_100             0x06
#define RF69_PARAMP_62              0x07
#define RF69_PARAMP_50              0x08
#define RF69_PARAMP_40              0x09  // Default
#define RF69_PARAMP_31              0x0A
#define RF69_PARAMP_25              0x0B
#define RF69_PARAMP_20              0x0C
#define RF69_PARAMP_15              0x0D
#define RF69_PARAMP_12              0x0E
#define RF69_PARAMP_10              0x0F


// RegOcp
#define RF69_OCP_OFF                0x0F
#define RF69_OCP_ON                 0x1A  // Default

#define RF69_OCP_TRIM_45            0x00
#define RF69_OCP_TRIM_50            0x01
#define RF69_OCP_TRIM_55            0x02
#define RF69_OCP_TRIM_60            0x03
#define RF69_OCP_TRIM_65            0x04
#define RF69_OCP_TRIM_70            0x05
#define RF69_OCP_TRIM_75            0x06
#define RF69_OCP_TRIM_80            0x07
#define RF69_OCP_TRIM_85            0x08
#define RF69_OCP_TRIM_90            0x09
#define RF69_OCP_TRIM_95            0x0A  // Default
#define RF69_OCP_TRIM_100           0x0B
#define RF69_OCP_TRIM_105           0x0C
#define RF69_OCP_TRIM_110           0x0D
#define RF69_OCP_TRIM_115           0x0E
#define RF69_OCP_TRIM_120           0x0F


// RegAgcRef - not present on RFM69/SX1231
#define RF69_AGCREF_AUTO_ON         0x40  // Default
#define RF69_AGCREF_AUTO_OFF        0x00

#define RF69_AGCREF_LEVEL_MINUS80   0x00  // Default
#define RF69_AGCREF_LEVEL_MINUS81   0x01
#define RF69_AGCREF_LEVEL_MINUS82   0x02
#define RF69_AGCREF_LEVEL_MINUS83   0x03
#define RF69_AGCREF_LEVEL_MINUS84   0x04
#define RF69_AGCREF_LEVEL_MINUS85   0x05
#define RF69_AGCREF_LEVEL_MINUS86   0x06
#define RF69_AGCREF_LEVEL_MINUS87   0x07
#define RF69_AGCREF_LEVEL_MINUS88   0x08
#define RF69_AGCREF_LEVEL_MINUS89   0x09
#define RF69_AGCREF_LEVEL_MINUS90   0x0A
#define RF69_AGCREF_LEVEL_MINUS91   0x0B
#define RF69_AGCREF_LEVEL_MINUS92   0x0C
#define RF69_AGCREF_LEVEL_MINUS93   0x0D
#define RF69_AGCREF_LEVEL_MINUS94   0x0E
#define RF69_AGCREF_LEVEL_MINUS95   0x0F
#define RF69_AGCREF_LEVEL_MINUS96   0x10
#define RF69_AGCREF_LEVEL_MINUS97   0x11
#define RF69_AGCREF_LEVEL_MINUS98   0x12
#define RF69_AGCREF_LEVEL_MINUS99   0x13
#define RF69_AGCREF_LEVEL_MINUS100  0x14
#define RF69_AGCREF_LEVEL_MINUS101  0x15
#define RF69_AGCREF_LEVEL_MINUS102  0x16
#define RF69_AGCREF_LEVEL_MINUS103  0x17
#define RF69_AGCREF_LEVEL_MINUS104  0x18
#define RF69_AGCREF_LEVEL_MINUS105  0x19
#define RF69_AGCREF_LEVEL_MINUS106  0x1A
#define RF69_AGCREF_LEVEL_MINUS107  0x1B
#define RF69_AGCREF_LEVEL_MINUS108  0x1C
#define RF69_AGCREF_LEVEL_MINUS109  0x1D
#define RF69_AGCREF_LEVEL_MINUS110  0x1E
#define RF69_AGCREF_LEVEL_MINUS111  0x1F
#define RF69_AGCREF_LEVEL_MINUS112  0x20
#define RF69_AGCREF_LEVEL_MINUS113  0x21
#define RF69_AGCREF_LEVEL_MINUS114  0x22
#define RF69_AGCREF_LEVEL_MINUS115  0x23
#define RF69_AGCREF_LEVEL_MINUS116  0x24
#define RF69_AGCREF_LEVEL_MINUS117  0x25
#define RF69_AGCREF_LEVEL_MINUS118  0x26
#define RF69_AGCREF_LEVEL_MINUS119  0x27
#define RF69_AGCREF_LEVEL_MINUS120  0x28
#define RF69_AGCREF_LEVEL_MINUS121  0x29
#define RF69_AGCREF_LEVEL_MINUS122  0x2A
#define RF69_AGCREF_LEVEL_MINUS123  0x2B
#define RF69_AGCREF_LEVEL_MINUS124  0x2C
#define RF69_AGCREF_LEVEL_MINUS125  0x2D
#define RF69_AGCREF_LEVEL_MINUS126  0x2E
#define RF69_AGCREF_LEVEL_MINUS127  0x2F
#define RF69_AGCREF_LEVEL_MINUS128  0x30
#define RF69_AGCREF_LEVEL_MINUS129  0x31
#define RF69_AGCREF_LEVEL_MINUS130  0x32
#define RF69_AGCREF_LEVEL_MINUS131  0x33
#define RF69_AGCREF_LEVEL_MINUS132  0x34
#define RF69_AGCREF_LEVEL_MINUS133  0x35
#define RF69_AGCREF_LEVEL_MINUS134  0x36
#define RF69_AGCREF_LEVEL_MINUS135  0x37
#define RF69_AGCREF_LEVEL_MINUS136  0x38
#define RF69_AGCREF_LEVEL_MINUS137  0x39
#define RF69_AGCREF_LEVEL_MINUS138  0x3A
#define RF69_AGCREF_LEVEL_MINUS139  0x3B
#define RF69_AGCREF_LEVEL_MINUS140  0x3C
#define RF69_AGCREF_LEVEL_MINUS141  0x3D
#define RF69_AGCREF_LEVEL_MINUS142  0x3E
#define RF69_AGCREF_LEVEL_MINUS143  0x3F


// RegAgcThresh1 - not present on RFM69/SX1231
#define RF69_AGCTHRESH1_SNRMARGIN_000   0x00
#define RF69_AGCTHRESH1_SNRMARGIN_001   0x20
#define RF69_AGCTHRESH1_SNRMARGIN_010   0x40
#define RF69_AGCTHRESH1_SNRMARGIN_011   0x60
#define RF69_AGCTHRESH1_SNRMARGIN_100   0x80
#define RF69_AGCTHRESH1_SNRMARGIN_101   0xA0  // Default
#define RF69_AGCTHRESH1_SNRMARGIN_110   0xC0
#define RF69_AGCTHRESH1_SNRMARGIN_111   0xE0

#define RF69_AGCTHRESH1_STEP1_0         0x00
#define RF69_AGCTHRESH1_STEP1_1         0x01
#define RF69_AGCTHRESH1_STEP1_2         0x02
#define RF69_AGCTHRESH1_STEP1_3         0x03
#define RF69_AGCTHRESH1_STEP1_4         0x04
#define RF69_AGCTHRESH1_STEP1_5         0x05
#define RF69_AGCTHRESH1_STEP1_6         0x06
#define RF69_AGCTHRESH1_STEP1_7         0x07
#define RF69_AGCTHRESH1_STEP1_8         0x08
#define RF69_AGCTHRESH1_STEP1_9         0x09
#define RF69_AGCTHRESH1_STEP1_10        0x0A
#define RF69_AGCTHRESH1_STEP1_11        0x0B
#define RF69_AGCTHRESH1_STEP1_12        0x0C
#define RF69_AGCTHRESH1_STEP1_13        0x0D
#define RF69_AGCTHRESH1_STEP1_14        0x0E
#define RF69_AGCTHRESH1_STEP1_15        0x0F
#define RF69_AGCTHRESH1_STEP1_16        0x10  // Default
#define RF69_AGCTHRESH1_STEP1_17        0x11
#define RF69_AGCTHRESH1_STEP1_18        0x12
#define RF69_AGCTHRESH1_STEP1_19        0x13
#define RF69_AGCTHRESH1_STEP1_20        0x14
#define RF69_AGCTHRESH1_STEP1_21        0x15
#define RF69_AGCTHRESH1_STEP1_22        0x16
#define RF69_AGCTHRESH1_STEP1_23        0x17
#define RF69_AGCTHRESH1_STEP1_24        0x18
#define RF69_AGCTHRESH1_STEP1_25        0x19
#define RF69_AGCTHRESH1_STEP1_26        0x1A
#define RF69_AGCTHRESH1_STEP1_27        0x1B
#define RF69_AGCTHRESH1_STEP1_28        0x1C
#define RF69_AGCTHRESH1_STEP1_29        0x1D
#define RF69_AGCTHRESH1_STEP1_30        0x1E
#define RF69_AGCTHRESH1_STEP1_31        0x1F


// RegAgcThresh2 - not present on RFM69/SX1231
#define RF69_AGCTHRESH2_STEP2_0         0x00
#define RF69_AGCTHRESH2_STEP2_1         0x10
#define RF69_AGCTHRESH2_STEP2_2         0x20
#define RF69_AGCTHRESH2_STEP2_3         0x30  // XXX wrong -- Default
#define RF69_AGCTHRESH2_STEP2_4         0x40
#define RF69_AGCTHRESH2_STEP2_5         0x50
#define RF69_AGCTHRESH2_STEP2_6         0x60
#define RF69_AGCTHRESH2_STEP2_7         0x70  // default
#define RF69_AGCTHRESH2_STEP2_8         0x80
#define RF69_AGCTHRESH2_STEP2_9         0x90
#define RF69_AGCTHRESH2_STEP2_10        0xA0
#define RF69_AGCTHRESH2_STEP2_11        0xB0
#define RF69_AGCTHRESH2_STEP2_12        0xC0
#define RF69_AGCTHRESH2_STEP2_13        0xD0
#define RF69_AGCTHRESH2_STEP2_14        0xE0
#define RF69_AGCTHRESH2_STEP2_15        0xF0

#define RF69_AGCTHRESH2_STEP3_0         0x00
#define RF69_AGCTHRESH2_STEP3_1         0x01
#define RF69_AGCTHRESH2_STEP3_2         0x02
#define RF69_AGCTHRESH2_STEP3_3         0x03
#define RF69_AGCTHRESH2_STEP3_4         0x04
#define RF69_AGCTHRESH2_STEP3_5         0x05
#define RF69_AGCTHRESH2_STEP3_6         0x06
#define RF69_AGCTHRESH2_STEP3_7         0x07
#define RF69_AGCTHRESH2_STEP3_8         0x08
#define RF69_AGCTHRESH2_STEP3_9         0x09
#define RF69_AGCTHRESH2_STEP3_10        0x0A
#define RF69_AGCTHRESH2_STEP3_11        0x0B  // Default
#define RF69_AGCTHRESH2_STEP3_12        0x0C
#define RF69_AGCTHRESH2_STEP3_13        0x0D
#define RF69_AGCTHRESH2_STEP3_14        0x0E
#define RF69_AGCTHRESH2_STEP3_15        0x0F


// RegAgcThresh3 - not present on RFM69/SX1231
#define RF69_AGCTHRESH3_STEP4_0         0x00
#define RF69_AGCTHRESH3_STEP4_1         0x10
#define RF69_AGCTHRESH3_STEP4_2         0x20
#define RF69_AGCTHRESH3_STEP4_3         0x30
#define RF69_AGCTHRESH3_STEP4_4         0x40
#define RF69_AGCTHRESH3_STEP4_5         0x50
#define RF69_AGCTHRESH3_STEP4_6         0x60
#define RF69_AGCTHRESH3_STEP4_7         0x70
#define RF69_AGCTHRESH3_STEP4_8         0x80
#define RF69_AGCTHRESH3_STEP4_9         0x90  // Default
#define RF69_AGCTHRESH3_STEP4_10        0xA0
#define RF69_AGCTHRESH3_STEP4_11        0xB0
#define RF69_AGCTHRESH3_STEP4_12        0xC0
#define RF69_AGCTHRESH3_STEP4_13        0xD0
#define RF69_AGCTHRESH3_STEP4_14        0xE0
#define RF69_AGCTHRESH3_STEP4_15        0xF0

#define RF69_AGCTHRESH3_STEP5_0         0x00
#define RF69_AGCTHRESH3_STEP5_1         0x01
#define RF69_AGCTHRESH3_STEP5_2         0x02
#define RF69_AGCTHRESH3_STEP5_3         0x03
#define RF69_AGCTHRESH3_STEP5_4         0x04
#define RF69_AGCTHRESH3_STEP5_5         0x05
#define RF69_AGCTHRESH3_STEP5_6         0x06
#define RF69_AGCTHRESH3_STEP5_7         0x07
#define RF69_AGCTHRES33_STEP5_8         0x08
#define RF69_AGCTHRESH3_STEP5_9         0x09
#define RF69_AGCTHRESH3_STEP5_10        0x0A
#define RF69_AGCTHRESH3_STEP5_11        0x0B  // Default
#define RF69_AGCTHRESH3_STEP5_12        0x0C
#define RF69_AGCTHRESH3_STEP5_13        0x0D
#define RF69_AGCTHRESH3_STEP5_14        0x0E
#define RF69_AGCTHRESH3_STEP5_15        0x0F


// RegLna
#define RF69_LNA_ZIN_50                 0x00  // Reset value
#define RF69_LNA_ZIN_200                0x80  // Recommended default

#define RF69_LNA_LOWPOWER_OFF           0x00  // Default
#define RF69_LNA_LOWPOWER_ON            0x40

#define RF69_LNA_CURRENTGAIN            0x08

#define RF69_LNA_GAINSELECT_AUTO        0x00  // Default
#define RF69_LNA_GAINSELECT_MAX         0x01
#define RF69_LNA_GAINSELECT_MAXMINUS6   0x02
#define RF69_LNA_GAINSELECT_MAXMINUS12  0x03
#define RF69_LNA_GAINSELECT_MAXMINUS24  0x04
#define RF69_LNA_GAINSELECT_MAXMINUS36  0x05
#define RF69_LNA_GAINSELECT_MAXMINUS48  0x06


// RegRxBw
#define RF69_RXBW_DCCFREQ_000           0x00
#define RF69_RXBW_DCCFREQ_001           0x20
#define RF69_RXBW_DCCFREQ_010           0x40  // Recommended default
#define RF69_RXBW_DCCFREQ_011           0x60
#define RF69_RXBW_DCCFREQ_100           0x80  // Reset value
#define RF69_RXBW_DCCFREQ_101           0xA0
#define RF69_RXBW_DCCFREQ_110           0xC0
#define RF69_RXBW_DCCFREQ_111           0xE0

#define RF69_RXBW_MANT_16               0x00  // Reset value
#define RF69_RXBW_MANT_20               0x08
#define RF69_RXBW_MANT_24               0x10  // Recommended default

#define RF69_RXBW_EXP_0                 0x00
#define RF69_RXBW_EXP_1                 0x01
#define RF69_RXBW_EXP_2                 0x02
#define RF69_RXBW_EXP_3                 0x03
#define RF69_RXBW_EXP_4                 0x04
#define RF69_RXBW_EXP_5                 0x05  // Recommended default
#define RF69_RXBW_EXP_6                 0x06  // Reset value
#define RF69_RXBW_EXP_7                 0x07


// RegAfcBw
#define RF69_AFCBW_DCCFREQAFC_000       0x00
#define RF69_AFCBW_DCCFREQAFC_001       0x20
#define RF69_AFCBW_DCCFREQAFC_010       0x40
#define RF69_AFCBW_DCCFREQAFC_011       0x60
#define RF69_AFCBW_DCCFREQAFC_100       0x80  // Default
#define RF69_AFCBW_DCCFREQAFC_101       0xA0
#define RF69_AFCBW_DCCFREQAFC_110       0xC0
#define RF69_AFCBW_DCCFREQAFC_111       0xE0

#define RF69_AFCBW_MANTAFC_16           0x00
#define RF69_AFCBW_MANTAFC_20           0x08  // Default
#define RF69_AFCBW_MANTAFC_24           0x10

#define RF69_AFCBW_EXPAFC_0             0x00
#define RF69_AFCBW_EXPAFC_1             0x01
#define RF69_AFCBW_EXPAFC_2             0x02  // Reset value
#define RF69_AFCBW_EXPAFC_3             0x03  // Recommended default
#define RF69_AFCBW_EXPAFC_4             0x04
#define RF69_AFCBW_EXPAFC_5             0x05
#define RF69_AFCBW_EXPAFC_6             0x06
#define RF69_AFCBW_EXPAFC_7             0x07


// RegOokPeak
#define RF69_OOKPEAK_THRESHTYPE_FIXED       0x00
#define RF69_OOKPEAK_THRESHTYPE_PEAK        0x40  // Default
#define RF69_OOKPEAK_THRESHTYPE_AVERAGE     0x80

#define RF69_OOKPEAK_PEAKTHRESHSTEP_000     0x00  // Default
#define RF69_OOKPEAK_PEAKTHRESHSTEP_001     0x08
#define RF69_OOKPEAK_PEAKTHRESHSTEP_010     0x10
#define RF69_OOKPEAK_PEAKTHRESHSTEP_011     0x18
#define RF69_OOKPEAK_PEAKTHRESHSTEP_100     0x20
#define RF69_OOKPEAK_PEAKTHRESHSTEP_101     0x28
#define RF69_OOKPEAK_PEAKTHRESHSTEP_110     0x30
#define RF69_OOKPEAK_PEAKTHRESHSTEP_111     0x38

#define RF69_OOKPEAK_PEAKTHRESHDEC_000      0x00  // Default
#define RF69_OOKPEAK_PEAKTHRESHDEC_001      0x01
#define RF69_OOKPEAK_PEAKTHRESHDEC_010      0x02
#define RF69_OOKPEAK_PEAKTHRESHDEC_011      0x03
#define RF69_OOKPEAK_PEAKTHRESHDEC_100      0x04
#define RF69_OOKPEAK_PEAKTHRESHDEC_101      0x05
#define RF69_OOKPEAK_PEAKTHRESHDEC_110      0x06
#define RF69_OOKPEAK_PEAKTHRESHDEC_111      0x07


// RegOokAvg
#define RF69_OOKAVG_AVERAGETHRESHFILT_00    0x00
#define RF69_OOKAVG_AVERAGETHRESHFILT_01    0x40
#define RF69_OOKAVG_AVERAGETHRESHFILT_10    0x80  // Default
#define RF69_OOKAVG_AVERAGETHRESHFILT_11    0xC0


// RegOokFix
#define RF69_OOKFIX_FIXEDTHRESH_VALUE       0x06  // Default


// RegAfcFei
#define RF69_AFCFEI_FEI_DONE                0x40
#define RF69_AFCFEI_FEI_START               0x20
#define RF69_AFCFEI_AFC_DONE                0x10
#define RF69_AFCFEI_AFCAUTOCLEAR_ON         0x08
#define RF69_AFCFEI_AFCAUTOCLEAR_OFF        0x00  // Default

#define RF69_AFCFEI_AFCAUTO_ON              0x04
#define RF69_AFCFEI_AFCAUTO_OFF             0x00  // Default

#define RF69_AFCFEI_AFC_CLEAR               0x02
#define RF69_AFCFEI_AFC_START               0x01


// RegRssiConfig
#define RF69_RSSI_FASTRX_ON                 0x08  // not present on RFM69/SX1231
#define RF69_RSSI_FASTRX_OFF                0x00  // Default

#define RF69_RSSI_DONE                      0x02
#define RF69_RSSI_START                     0x01


// RegDioMapping1
#define RF69_DIOMAPPING1_DIO0_00            0x00  // Default
#define RF69_DIOMAPPING1_DIO0_01            0x40
#define RF69_DIOMAPPING1_DIO0_10            0x80
#define RF69_DIOMAPPING1_DIO0_11            0xC0

#define RF69_DIOMAPPING1_DIO1_00            0x00  // Default
#define RF69_DIOMAPPING1_DIO1_01            0x10
#define RF69_DIOMAPPING1_DIO1_10            0x20
#define RF69_DIOMAPPING1_DIO1_11            0x30

#define RF69_DIOMAPPING1_DIO2_00            0x00  // Default
#define RF69_DIOMAPPING1_DIO2_01            0x04
#define RF69_DIOMAPPING1_DIO2_10            0x08
#define RF69_DIOMAPPING1_DIO2_11            0x0C

#define RF69_DIOMAPPING1_DIO3_00            0x00  // Default
#define RF69_DIOMAPPING1_DIO3_01            0x01
#define RF69_DIOMAPPING1_DIO3_10            0x02
#define RF69_DIOMAPPING1_DIO3_11            0x03


// RegDioMapping2
#define RF69_DIOMAPPING2_DIO4_00            0x00  // Default
#define RF69_DIOMAPPING2_DIO4_01            0x40
#define RF69_DIOMAPPING2_DIO4_10            0x80
#define RF69_DIOMAPPING2_DIO4_11            0xC0

#define RF69_DIOMAPPING2_DIO5_00            0x00  // Default
#define RF69_DIOMAPPING2_DIO5_01            0x10
#define RF69_DIOMAPPING2_DIO5_10            0x20
#define RF69_DIOMAPPING2_DIO5_11            0x30

#define RF69_DIOMAPPING2_CLKOUT_32MHZ       0x00
#define RF69_DIOMAPPING2_CLKOUT_16MHZ       0x01
#define RF69_DIOMAPPING2_CLKOUT_8MHZ        0x02
#define RF69_DIOMAPPING2_CLKOUT_4MHZ        0x03
#define RF69_DIOMAPPING2_CLKOUT_2MHZ        0x04
#define RF69_DIOMAPPING2_CLKOUT_1MHZ        0x05  // Reset value
#define RF69_DIOMAPPING2_CLKOUT_RC          0x06
#define RF69_DIOMAPPING2_CLKOUT_OFF         0x07  // Recommended default


// RegIrqFlags1
#define RF69_IRQFLAGS1_MODEREADY            0x80
#define RF69_IRQFLAGS1_RXREADY              0x40
#define RF69_IRQFLAGS1_TXREADY              0x20
#define RF69_IRQFLAGS1_PLLLOCK              0x10
#define RF69_IRQFLAGS1_RSSI                 0x08
#define RF69_IRQFLAGS1_TIMEOUT              0x04
#define RF69_IRQFLAGS1_AUTOMODE             0x02
#define RF69_IRQFLAGS1_SYNCADDRESSMATCH     0x01


// RegIrqFlags2
#define RF69_IRQFLAGS2_FIFOFULL             0x80
#define RF69_IRQFLAGS2_FIFONOTEMPTY         0x40
#define RF69_IRQFLAGS2_FIFOLEVEL            0x20
#define RF69_IRQFLAGS2_FIFOOVERRUN          0x10
#define RF69_IRQFLAGS2_PACKETSENT           0x08
#define RF69_IRQFLAGS2_PAYLOADREADY         0x04
#define RF69_IRQFLAGS2_CRCOK                0x02
#define RF69_IRQFLAGS2_LOWBAT               0x01  // not present on RFM69/SX1231


// RegRssiThresh
#define RF69_RSSITHRESH_VALUE               0xE4  // Default


// RegRxTimeout1
#define RF69_RXTIMEOUT1_RXSTART_VALUE       0x00  // Default


// RegRxTimeout2
#define RF69_RXTIMEOUT2_RSSITHRESH_VALUE    0x00  // Default


// RegPreamble
#define RF69_PREAMBLESIZE_MSB_VALUE         0x00  // Default
#define RF69_PREAMBLESIZE_LSB_VALUE         0x03  // Default


// RegSyncConfig
#define RF69_SYNC_ON                0x80  // Default
#define RF69_SYNC_OFF               0x00

#define RF69_SYNC_FIFOFILL_AUTO     0x00  // Default -- when sync interrupt occurs
#define RF69_SYNC_FIFOFILL_MANUAL   0x40

#define RF69_SYNC_SIZE_1            0x00
#define RF69_SYNC_SIZE_2            0x08
#define RF69_SYNC_SIZE_3            0x10
#define RF69_SYNC_SIZE_4            0x18  // Default
#define RF69_SYNC_SIZE_5            0x20
#define RF69_SYNC_SIZE_6            0x28
#define RF69_SYNC_SIZE_7            0x30
#define RF69_SYNC_SIZE_8            0x38

#define RF69_SYNC_TOL_0             0x00  // Default
#define RF69_SYNC_TOL_1             0x01
#define RF69_SYNC_TOL_2             0x02
#define RF69_SYNC_TOL_3             0x03
#define RF69_SYNC_TOL_4             0x04
#define RF69_SYNC_TOL_5             0x05
#define RF69_SYNC_TOL_6             0x06
#define RF69_SYNC_TOL_7             0x07


// RegSyncValue1-8
#define RF69_SYNC_BYTE1_VALUE       0x00  // Default
#define RF69_SYNC_BYTE2_VALUE       0x00  // Default
#define RF69_SYNC_BYTE3_VALUE       0x00  // Default
#define RF69_SYNC_BYTE4_VALUE       0x00  // Default
#define RF69_SYNC_BYTE5_VALUE       0x00  // Default
#define RF69_SYNC_BYTE6_VALUE       0x00  // Default
#define RF69_SYNC_BYTE7_VALUE       0x00  // Default
#define RF69_SYNC_BYTE8_VALUE       0x00  // Default


// RegPacketConfig1
#define RF69_PACKET1_FORMAT_FIXED       0x00  // Default
#define RF69_PACKET1_FORMAT_VARIABLE    0x80

#define RF69_PACKET1_DCFREE_OFF         0x00  // Default
#define RF69_PACKET1_DCFREE_MANCHESTER  0x20
#define RF69_PACKET1_DCFREE_WHITENING   0x40

#define RF69_PACKET1_CRC_ON             0x10  // Default
#define RF69_PACKET1_CRC_OFF            0x00

#define RF69_PACKET1_CRCAUTOCLEAR_ON    0x00  // Default
#define RF69_PACKET1_CRCAUTOCLEAR_OFF   0x08

#define RF69_PACKET1_ADRSFILTERING_OFF            0x00  // Default
#define RF69_PACKET1_ADRSFILTERING_NODE           0x02
#define RF69_PACKET1_ADRSFILTERING_NODEBROADCAST  0x04


// RegPayloadLength
#define RF69_PAYLOADLENGTH_VALUE          0x40  // Default


// RegBroadcastAdrs
#define RF69_BROADCASTADDRESS_VALUE       0x00


// RegAutoModes
#define RF69_AUTOMODES_ENTER_OFF                0x00  // Default
#define RF69_AUTOMODES_ENTER_FIFONOTEMPTY       0x20
#define RF69_AUTOMODES_ENTER_FIFOLEVEL          0x40
#define RF69_AUTOMODES_ENTER_CRCOK              0x60
#define RF69_AUTOMODES_ENTER_PAYLOADREADY       0x80
#define RF69_AUTOMODES_ENTER_SYNCADRSMATCH      0xA0
#define RF69_AUTOMODES_ENTER_PACKETSENT         0xC0
#define RF69_AUTOMODES_ENTER_FIFOEMPTY          0xE0

#define RF69_AUTOMODES_EXIT_OFF                 0x00  // Default
#define RF69_AUTOMODES_EXIT_FIFOEMPTY           0x04
#define RF69_AUTOMODES_EXIT_FIFOLEVEL           0x08
#define RF69_AUTOMODES_EXIT_CRCOK               0x0C
#define RF69_AUTOMODES_EXIT_PAYLOADREADY        0x10
#define RF69_AUTOMODES_EXIT_SYNCADRSMATCH       0x14
#define RF69_AUTOMODES_EXIT_PACKETSENT          0x18
#define RF69_AUTOMODES_EXIT_RXTIMEOUT           0x1C

#define RF69_AUTOMODES_INTERMEDIATE_SLEEP       0x00  // Default
#define RF69_AUTOMODES_INTERMEDIATE_STANDBY     0x01
#define RF69_AUTOMODES_INTERMEDIATE_RECEIVER    0x02
#define RF69_AUTOMODES_INTERMEDIATE_TRANSMITTER 0x03


// RegFifoThresh
#define RF69_FIFOTHRESH_TXSTART_FIFOTHRESH      0x00  // Reset value
#define RF69_FIFOTHRESH_TXSTART_FIFONOTEMPTY    0x80  // Recommended default

#define RF69_FIFOTHRESH_VALUE                   0x0F  // Default


// RegPacketConfig2
#define RF69_PACKET2_RXRESTARTDELAY_1BIT        0x00  // Default
#define RF69_PACKET2_RXRESTARTDELAY_2BITS       0x10
#define RF69_PACKET2_RXRESTARTDELAY_4BITS       0x20
#define RF69_PACKET2_RXRESTARTDELAY_8BITS       0x30
#define RF69_PACKET2_RXRESTARTDELAY_16BITS      0x40
#define RF69_PACKET2_RXRESTARTDELAY_32BITS      0x50
#define RF69_PACKET2_RXRESTARTDELAY_64BITS      0x60
#define RF69_PACKET2_RXRESTARTDELAY_128BITS     0x70
#define RF69_PACKET2_RXRESTARTDELAY_256BITS     0x80
#define RF69_PACKET2_RXRESTARTDELAY_512BITS     0x90
#define RF69_PACKET2_RXRESTARTDELAY_1024BITS    0xA0
#define RF69_PACKET2_RXRESTARTDELAY_2048BITS    0xB0
#define RF69_PACKET2_RXRESTARTDELAY_NONE        0xC0
#define RF69_PACKET2_RXRESTART                  0x04

#define RF69_PACKET2_AUTORXRESTART_ON           0x02  // Default
#define RF69_PACKET2_AUTORXRESTART_OFF          0x00

#define RF69_PACKET2_AES_ON                     0x01
#define RF69_PACKET2_AES_OFF                    0x00  // Default


// RegAesKey1-16
#define RF69_AESKEY1_VALUE            0x00  // Default
#define RF69_AESKEY2_VALUE            0x00  // Default
#define RF69_AESKEY3_VALUE            0x00  // Default
#define RF69_AESKEY4_VALUE            0x00  // Default
#define RF69_AESKEY5_VALUE            0x00  // Default
#define RF69_AESKEY6_VALUE            0x00  // Default
#define RF69_AESKEY7_VALUE            0x00  // Default
#define RF69_AESKEY8_VALUE            0x00  // Default
#define RF69_AESKEY9_VALUE            0x00  // Default
#define RF69_AESKEY10_VALUE           0x00  // Default
#define RF69_AESKEY11_VALUE           0x00  // Default
#define RF69_AESKEY12_VALUE           0x00  // Default
#define RF69_AESKEY13_VALUE           0x00  // Default
#define RF69_AESKEY14_VALUE           0x00  // Default
#define RF69_AESKEY15_VALUE           0x00  // Default
#define RF69_AESKEY16_VALUE           0x00  // Default


// RegTemp1
#define RF69_TEMP1_MEAS_START         0x08
#define RF69_TEMP1_MEAS_RUNNING       0x04
// not present on RFM69/SX1231
#define RF69_TEMP1_ADCLOWPOWER_ON     0x01  // Default
#define RF69_TEMP1_ADCLOWPOWER_OFF    0x00


// RegTestLna
#define RF69_TESTLNA_NORMAL           0x1B
#define RF69_TESTLNA_HIGH_SENSITIVITY 0x2D


// RegTestDagc
#define RF69_DAGC_NORMAL              0x00  // Reset value
#define RF69_DAGC_IMPROVED_LOWBETA1   0x20
#define RF69_DAGC_IMPROVED_LOWBETA0 0x30 // Recommended default
/*-----------------------------------------------------*/
#define RF69_MAX_DATA_LEN       61 // to take advantage of the built in AES/CRC we want to limit the frame size to the internal FIFO size (66 bytes - 3 bytes overhead - 2 bytes crc)
#define RF69_SPI_CS             SS // SS is the SPI slave select pin, for instance D10 on ATmega328

#define CSMA_LIMIT              -90 // upper RX signal sensitivity threshold in dBm for carrier sense access


#define null                  0
#define COURSE_TEMP_COEF    -90 // puts the temperature reading in the ballpark, user can fine tune the returned value
#define RF69_BROADCAST_ADDR 255
#define RF69_CSMA_LIMIT_MS 1000
#define RF69_TX_LIMIT_MS   1000
#define RF69_FSTEP  61.03515625 // == FXOSC / 2^19 = 32MHz / 2^19 (p13 in datasheet)

// TWS: define CTLbyte bits
#define RFM69_CTL_SENDACK   0x80
#define RFM69_CTL_REQACK    0x40

/*#####################################################*/
namespace GI {
namespace Device {
namespace Rf {
class Rf69h {
public:
	enum center_freq_e {
		// RegFrf (MHz) - carrier frequency
		// 315Mhz band
		RFM69_FRFMSB_314 = 0x4E8000,
		RFM69_FRFMSB_315 = 0x4EC000,
		RFM69_FRFMSB_316 = 0x4F0000,
		// 433mhz band
		RFM69_FRFMSB_433 = 0x6C4000,
		RFM69_FRFMSB_434 = 0x6C8000,
		RFM69_FRFMSB_435 = 0x6CC000,
		// 868Mhz band
		RFM69_FRFMSB_863 = 0xD7C000,
		RFM69_FRFMSB_864 = 0xD80000,
		RFM69_FRFMSB_865 = 0xD84000,
		RFM69_FRFMSB_866 = 0xD88000,
		RFM69_FRFMSB_867 = 0xD8C000,
		RFM69_FRFMSB_868 = 0xD90000,
		RFM69_FRFMSB_869 = 0xD94000,
		RFM69_FRFMSB_870 = 0xD98000,
		// 915Mhz band
		RFM69_FRFMSB_902 = 0xE18000,
		RFM69_FRFMSB_903 = 0xE1C000,
		RFM69_FRFMSB_904 = 0xE20000,
		RFM69_FRFMSB_905 = 0xE24000,
		RFM69_FRFMSB_906 = 0xE28000,
		RFM69_FRFMSB_907 = 0xE2C000,
		RFM69_FRFMSB_908 = 0xE30000,
		RFM69_FRFMSB_909 = 0xE34000,
		RFM69_FRFMSB_910 = 0xE38000,
		RFM69_FRFMSB_911 = 0xE3C000,
		RFM69_FRFMSB_912 = 0xE40000,
		RFM69_FRFMSB_913 = 0xE44000,
		RFM69_FRFMSB_914 = 0xE48000,
		RFM69_FRFMSB_915 = 0xE4C000,  // Default
		RFM69_FRFMSB_916 = 0xE50000,
		RFM69_FRFMSB_917 = 0xE54000,
		RFM69_FRFMSB_918 = 0xE58000,
		RFM69_FRFMSB_919 = 0xE5C000,
		RFM69_FRFMSB_920 = 0xE60000,
		RFM69_FRFMSB_921 = 0xE64000,
		RFM69_FRFMSB_922 = 0xE68000,
		RFM69_FRFMSB_923 = 0xE6C000,
		RFM69_FRFMSB_924 = 0xE70000,
		RFM69_FRFMSB_925 = 0xE74000,
		RFM69_FRFMSB_926 = 0xE78000,
		RFM69_FRFMSB_927 = 0xE7C000,
		RFM69_FRFMSB_928 = 0xE80000,
	};

	enum mode_e {
		RF69_MODE_SLEEP = 0, // XTAL OFF
		RF69_MODE_STANDBY = 1, // XTAL ON
		RF69_MODE_SYNTH = 2, // PLL ON
		RF69_MODE_RX = 3, // RX MODE
		RF69_MODE_TX = 4, // TX MODE
	};
	Rf69h(char *spiPath, char *irqPinPath, center_freq_e centerFreq, u16 networkId, u8 nodeId);
	~Rf69h();
	SysErr setFreq(u32 freqHz);
	SysErr getFreq(u32 *freqHz);
	SysErr setMode(mode_e newMode);
	SysErr getMode(mode_e *mode);
	SysErr setModeSleep();
	SysErr setNetworkId(u16 networkId);
	SysErr setAddress(u8 address);
	SysErr setPwrLevel(u8 level);
	SysErr canSend();


	SysErr sendFrame(u8 addr, u8* buff, u8 len, bool requestACK, bool sendACK);
	SysErr receiveBegin();
	SysErr receiveDone();
	SysErr setHighPwrRegs(bool onOff);
	SysErr readRssi(s8 *rssi, bool forceTrigger = false);
	SysErr send(u8 address, u8 *buff, u8 len, bool reqAck);
private:
    GI::IO *spiDevice;
    GI::IO *irqPin;
    mode_e mode;
    bool isRFM69HW;
    volatile u8 DATA[RF69_MAX_DATA_LEN];
    volatile u8 DATALEN;
    volatile u8 SENDERID;
    volatile u8 TARGETID;     // should match _address
    volatile u8 PAYLOADLEN;
    volatile u8 ACK_REQUESTED;
    volatile u8 ACK_RECEIVED; // should be polled immediately after sending a packet with ACK request
    volatile s8 RSSI;          // most accurate RSSI during reception (closest to the reception)
    volatile bool inISR;
    volatile u8 address;

};
}
}
}
/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "rf69h.cpp"
#endif
/*#####################################################*/
#endif /* RF69H_H_ */
