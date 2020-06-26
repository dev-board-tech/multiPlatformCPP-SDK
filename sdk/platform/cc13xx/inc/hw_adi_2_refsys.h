/******************************************************************************
*  Filename:       hw_adi_2_refsys_h
*  Revised:        2015-11-12 13:07:02 +0100 (Thu, 12 Nov 2015)
*  Revision:       45056
*
* Copyright (c) 2015, Texas Instruments Incorporated
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1) Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2) Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* 3) Neither the name of the ORGANIZATION nor the names of its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/

#ifndef __HW_ADI_2_REFSYS_H__
#define __HW_ADI_2_REFSYS_H__

//*****************************************************************************
//
// This section defines the register offsets of
// ADI_2_REFSYS component
//
//*****************************************************************************
// Internal
#define ADI_2_REFSYS_O_REFSYSCTL0                                   0x00000000

// Internal
#define ADI_2_REFSYS_O_SOCLDOCTL0                                   0x00000002

// Internal
#define ADI_2_REFSYS_O_SOCLDOCTL1                                   0x00000003

// Internal
#define ADI_2_REFSYS_O_SOCLDOCTL2                                   0x00000004

// Internal
#define ADI_2_REFSYS_O_SOCLDOCTL3                                   0x00000005

// Internal
#define ADI_2_REFSYS_O_SOCLDOCTL4                                   0x00000006

// Internal
#define ADI_2_REFSYS_O_SOCLDOCTL5                                   0x00000007

// HPOSC Control 0
#define ADI_2_REFSYS_O_HPOSCCTL0                                    0x0000000A

// HPOSC Control 1
#define ADI_2_REFSYS_O_HPOSCCTL1                                    0x0000000B

// HPOSC Control 2
#define ADI_2_REFSYS_O_HPOSCCTL2                                    0x0000000C

//*****************************************************************************
//
// Register: ADI_2_REFSYS_O_REFSYSCTL0
//
//*****************************************************************************
// Field:   [4:0] TRIM_IREF
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_REFSYSCTL0_TRIM_IREF_W                                  5
#define ADI_2_REFSYS_REFSYSCTL0_TRIM_IREF_M                         0x0000001F
#define ADI_2_REFSYS_REFSYSCTL0_TRIM_IREF_S                                  0

//*****************************************************************************
//
// Register: ADI_2_REFSYS_O_SOCLDOCTL0
//
//*****************************************************************************
// Field:   [7:4] VTRIM_UDIG
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL0_VTRIM_UDIG_W                                 4
#define ADI_2_REFSYS_SOCLDOCTL0_VTRIM_UDIG_M                        0x000000F0
#define ADI_2_REFSYS_SOCLDOCTL0_VTRIM_UDIG_S                                 4

// Field:   [3:0] VTRIM_BOD
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL0_VTRIM_BOD_W                                  4
#define ADI_2_REFSYS_SOCLDOCTL0_VTRIM_BOD_M                         0x0000000F
#define ADI_2_REFSYS_SOCLDOCTL0_VTRIM_BOD_S                                  0

//*****************************************************************************
//
// Register: ADI_2_REFSYS_O_SOCLDOCTL1
//
//*****************************************************************************
// Field:   [7:4] VTRIM_COARSE
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL1_VTRIM_COARSE_W                               4
#define ADI_2_REFSYS_SOCLDOCTL1_VTRIM_COARSE_M                      0x000000F0
#define ADI_2_REFSYS_SOCLDOCTL1_VTRIM_COARSE_S                               4

// Field:   [3:0] VTRIM_DIG
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL1_VTRIM_DIG_W                                  4
#define ADI_2_REFSYS_SOCLDOCTL1_VTRIM_DIG_M                         0x0000000F
#define ADI_2_REFSYS_SOCLDOCTL1_VTRIM_DIG_S                                  0

//*****************************************************************************
//
// Register: ADI_2_REFSYS_O_SOCLDOCTL2
//
//*****************************************************************************
// Field:   [2:0] VTRIM_DELTA
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL2_VTRIM_DELTA_W                                3
#define ADI_2_REFSYS_SOCLDOCTL2_VTRIM_DELTA_M                       0x00000007
#define ADI_2_REFSYS_SOCLDOCTL2_VTRIM_DELTA_S                                0

//*****************************************************************************
//
// Register: ADI_2_REFSYS_O_SOCLDOCTL3
//
//*****************************************************************************
// Field:   [7:6] ITRIM_DIGLDO_LOAD
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_DIGLDO_LOAD_W                          2
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_DIGLDO_LOAD_M                 0x000000C0
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_DIGLDO_LOAD_S                          6

// Field:   [5:3] ITRIM_DIGLDO
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// BIAS_120P                Internal. Only to be used through TI provided API.
// BIAS_100P                Internal. Only to be used through TI provided API.
// BIAS_80P                 Internal. Only to be used through TI provided API.
// BIAS_60P                 Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_DIGLDO_W                               3
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_DIGLDO_M                      0x00000038
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_DIGLDO_S                               3
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_DIGLDO_BIAS_120P              0x00000038
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_DIGLDO_BIAS_100P              0x00000028
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_DIGLDO_BIAS_80P               0x00000018
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_DIGLDO_BIAS_60P               0x00000000

// Field:   [2:0] ITRIM_UDIGLDO
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_UDIGLDO_W                              3
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_UDIGLDO_M                     0x00000007
#define ADI_2_REFSYS_SOCLDOCTL3_ITRIM_UDIGLDO_S                              0

//*****************************************************************************
//
// Register: ADI_2_REFSYS_O_SOCLDOCTL4
//
//*****************************************************************************
// Field:   [6:5] UDIG_ITEST_EN
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL4_UDIG_ITEST_EN_W                              2
#define ADI_2_REFSYS_SOCLDOCTL4_UDIG_ITEST_EN_M                     0x00000060
#define ADI_2_REFSYS_SOCLDOCTL4_UDIG_ITEST_EN_S                              5

// Field:   [4:2] DIG_ITEST_EN
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL4_DIG_ITEST_EN_W                               3
#define ADI_2_REFSYS_SOCLDOCTL4_DIG_ITEST_EN_M                      0x0000001C
#define ADI_2_REFSYS_SOCLDOCTL4_DIG_ITEST_EN_S                               2

// Field:     [1] BIAS_DIS
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL4_BIAS_DIS                            0x00000002
#define ADI_2_REFSYS_SOCLDOCTL4_BIAS_DIS_BITN                                1
#define ADI_2_REFSYS_SOCLDOCTL4_BIAS_DIS_M                          0x00000002
#define ADI_2_REFSYS_SOCLDOCTL4_BIAS_DIS_S                                   1

// Field:     [0] UDIG_LDO_EN
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// EN                       Internal. Only to be used through TI provided API.
// DIS                      Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL4_UDIG_LDO_EN                         0x00000001
#define ADI_2_REFSYS_SOCLDOCTL4_UDIG_LDO_EN_BITN                             0
#define ADI_2_REFSYS_SOCLDOCTL4_UDIG_LDO_EN_M                       0x00000001
#define ADI_2_REFSYS_SOCLDOCTL4_UDIG_LDO_EN_S                                0
#define ADI_2_REFSYS_SOCLDOCTL4_UDIG_LDO_EN_EN                      0x00000001
#define ADI_2_REFSYS_SOCLDOCTL4_UDIG_LDO_EN_DIS                     0x00000000

//*****************************************************************************
//
// Register: ADI_2_REFSYS_O_SOCLDOCTL5
//
//*****************************************************************************
// Field:     [3] IMON_ITEST_EN
//
// Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL5_IMON_ITEST_EN                       0x00000008
#define ADI_2_REFSYS_SOCLDOCTL5_IMON_ITEST_EN_BITN                           3
#define ADI_2_REFSYS_SOCLDOCTL5_IMON_ITEST_EN_M                     0x00000008
#define ADI_2_REFSYS_SOCLDOCTL5_IMON_ITEST_EN_S                              3

// Field:   [2:0] TESTSEL
//
// Internal. Only to be used through TI provided API.
// ENUMs:
// VDD_AON                  Internal. Only to be used through TI provided API.
// VREF_AMP                 Internal. Only to be used through TI provided API.
// ITEST                    Internal. Only to be used through TI provided API.
// NC                       Internal. Only to be used through TI provided API.
#define ADI_2_REFSYS_SOCLDOCTL5_TESTSEL_W                                    3
#define ADI_2_REFSYS_SOCLDOCTL5_TESTSEL_M                           0x00000007
#define ADI_2_REFSYS_SOCLDOCTL5_TESTSEL_S                                    0
#define ADI_2_REFSYS_SOCLDOCTL5_TESTSEL_VDD_AON                     0x00000004
#define ADI_2_REFSYS_SOCLDOCTL5_TESTSEL_VREF_AMP                    0x00000002
#define ADI_2_REFSYS_SOCLDOCTL5_TESTSEL_ITEST                       0x00000001
#define ADI_2_REFSYS_SOCLDOCTL5_TESTSEL_NC                          0x00000000

//*****************************************************************************
//
// Register: ADI_2_REFSYS_O_HPOSCCTL0
//
//*****************************************************************************
// Field:     [7] FILTER_EN
//
// Enable HPOSC Bias filter
//
// Enable 1 kHz low pass filter in the HPOSC bias.
#define ADI_2_REFSYS_HPOSCCTL0_FILTER_EN                            0x00000080
#define ADI_2_REFSYS_HPOSCCTL0_FILTER_EN_BITN                                7
#define ADI_2_REFSYS_HPOSCCTL0_FILTER_EN_M                          0x00000080
#define ADI_2_REFSYS_HPOSCCTL0_FILTER_EN_S                                   7

// Field:   [6:5] BIAS_RECHARGE_DLY
//
// When HPOSCCTL2.BIAS_HOLD_MODE_EN = 1, low-power sample and hold mode for
// HPOSC bias is enabled. This field sets the recharge delay for this sample
// and hold mode by counting number of 48 MHz clock edges.
// ENUMs:
// MIN_DLY_X8               5461 us
// MIN_DLY_X4               2731 us
// MIN_DLY_X2               1365 us
// MIN_DLY_X1               682 us
#define ADI_2_REFSYS_HPOSCCTL0_BIAS_RECHARGE_DLY_W                           2
#define ADI_2_REFSYS_HPOSCCTL0_BIAS_RECHARGE_DLY_M                  0x00000060
#define ADI_2_REFSYS_HPOSCCTL0_BIAS_RECHARGE_DLY_S                           5
#define ADI_2_REFSYS_HPOSCCTL0_BIAS_RECHARGE_DLY_MIN_DLY_X8         0x00000060
#define ADI_2_REFSYS_HPOSCCTL0_BIAS_RECHARGE_DLY_MIN_DLY_X4         0x00000040
#define ADI_2_REFSYS_HPOSCCTL0_BIAS_RECHARGE_DLY_MIN_DLY_X2         0x00000020
#define ADI_2_REFSYS_HPOSCCTL0_BIAS_RECHARGE_DLY_MIN_DLY_X1         0x00000000

// Field:   [4:3] TUNE_CAP
//
// Cap to shift HPOSC center frequency.
// ENUMs:
// SHIFT_M108               -108 ppm shift
// SHIFT_M70                -70 ppm shift
// SHIFT_M35                -35 ppm shift
// SHIFT_0                  0 ppm shift
#define ADI_2_REFSYS_HPOSCCTL0_TUNE_CAP_W                                    2
#define ADI_2_REFSYS_HPOSCCTL0_TUNE_CAP_M                           0x00000018
#define ADI_2_REFSYS_HPOSCCTL0_TUNE_CAP_S                                    3
#define ADI_2_REFSYS_HPOSCCTL0_TUNE_CAP_SHIFT_M108                  0x00000018
#define ADI_2_REFSYS_HPOSCCTL0_TUNE_CAP_SHIFT_M70                   0x00000010
#define ADI_2_REFSYS_HPOSCCTL0_TUNE_CAP_SHIFT_M35                   0x00000008
#define ADI_2_REFSYS_HPOSCCTL0_TUNE_CAP_SHIFT_0                     0x00000000

// Field:   [2:1] SERIES_CAP
//
// Cap to set HPOSC into proper mode.  Set 1 time in factory.
//
// 00:  1.4 pF Cs1/Cs2
// 01: 1.1 pF Cs1/Cs2
// 10: 2.1 pF Cs1/Cs2
// 11:  1.8 pF Cs1/Cs2
#define ADI_2_REFSYS_HPOSCCTL0_SERIES_CAP_W                                  2
#define ADI_2_REFSYS_HPOSCCTL0_SERIES_CAP_M                         0x00000006
#define ADI_2_REFSYS_HPOSCCTL0_SERIES_CAP_S                                  1

// Field:     [0] DIV3_BYPASS
//
// Bypass for divide by 3 in divider.
// ENUMs:
// HPOSC_2520MHZ            Divide by 17.5 for use with 2520 MHz HPOSC
// HPOSC_840MHZ             Divide by 52.5 for use with 840 MHz HPOSC
#define ADI_2_REFSYS_HPOSCCTL0_DIV3_BYPASS                          0x00000001
#define ADI_2_REFSYS_HPOSCCTL0_DIV3_BYPASS_BITN                              0
#define ADI_2_REFSYS_HPOSCCTL0_DIV3_BYPASS_M                        0x00000001
#define ADI_2_REFSYS_HPOSCCTL0_DIV3_BYPASS_S                                 0
#define ADI_2_REFSYS_HPOSCCTL0_DIV3_BYPASS_HPOSC_2520MHZ            0x00000001
#define ADI_2_REFSYS_HPOSCCTL0_DIV3_BYPASS_HPOSC_840MHZ             0x00000000

//*****************************************************************************
//
// Register: ADI_2_REFSYS_O_HPOSCCTL1
//
//*****************************************************************************
// Field:     [5] BIAS_DIS
//
// Disable dummy bias current.
//
// 0: Dummy bias current on (Default)
// 1: Dummy bias current off
#define ADI_2_REFSYS_HPOSCCTL1_BIAS_DIS                             0x00000020
#define ADI_2_REFSYS_HPOSCCTL1_BIAS_DIS_BITN                                 5
#define ADI_2_REFSYS_HPOSCCTL1_BIAS_DIS_M                           0x00000020
#define ADI_2_REFSYS_HPOSCCTL1_BIAS_DIS_S                                    5

// Field:     [4] PWRDET_EN
//
// Enable signal for HPOSC power detector.
//
// 0:  HPOSC power detector disabled.
// 1:  HPOSC power detector enabled.
//
// When enabled, Power detector VMAX and VMIN referred to in
// HPOSCCTL2.ATEST_SEL can be selected.
#define ADI_2_REFSYS_HPOSCCTL1_PWRDET_EN                            0x00000010
#define ADI_2_REFSYS_HPOSCCTL1_PWRDET_EN_BITN                                4
#define ADI_2_REFSYS_HPOSCCTL1_PWRDET_EN_M                          0x00000010
#define ADI_2_REFSYS_HPOSCCTL1_PWRDET_EN_S                                   4

// Field:   [3:0] BIAS_RES_SET
//
// Adjust the HPOSC bias resistor to set the current in the HPOSC core. Two's
// complement encoding.
//
// 0x8: Highest resistance, lowest current
// 0x0: Default
// 0x7: Lowest resistance, maximum current
#define ADI_2_REFSYS_HPOSCCTL1_BIAS_RES_SET_W                                4
#define ADI_2_REFSYS_HPOSCCTL1_BIAS_RES_SET_M                       0x0000000F
#define ADI_2_REFSYS_HPOSCCTL1_BIAS_RES_SET_S                                0

//*****************************************************************************
//
// Register: ADI_2_REFSYS_O_HPOSCCTL2
//
//*****************************************************************************
// Field:     [7] BIAS_HOLD_MODE_EN
//
// Enable signal for bias sample and hold mode.  Should give some power savings
// at expense of increased phase noise or spurs.
//
// 0: Disabled hold mode
// 1: Enabled hold mode
#define ADI_2_REFSYS_HPOSCCTL2_BIAS_HOLD_MODE_EN                    0x00000080
#define ADI_2_REFSYS_HPOSCCTL2_BIAS_HOLD_MODE_EN_BITN                        7
#define ADI_2_REFSYS_HPOSCCTL2_BIAS_HOLD_MODE_EN_M                  0x00000080
#define ADI_2_REFSYS_HPOSCCTL2_BIAS_HOLD_MODE_EN_S                           7

// Field:     [6] TESTMUX_EN
//
// Enable signal for HPOSC test mux.
//
// 0:  HPOSC test mux disabled.
// 1:  HPOSC test mux enabled.
#define ADI_2_REFSYS_HPOSCCTL2_TESTMUX_EN                           0x00000040
#define ADI_2_REFSYS_HPOSCCTL2_TESTMUX_EN_BITN                               6
#define ADI_2_REFSYS_HPOSCCTL2_TESTMUX_EN_M                         0x00000040
#define ADI_2_REFSYS_HPOSCCTL2_TESTMUX_EN_S                                  6

// Field:   [5:4] ATEST_SEL
//
// ATEST Selection Control
//
// 00:  Output test bias current
// 01:  Former connction for HPOSC BGAP.  Not currently used.
// 10:  Power detector VMAX
// 11: Power detector VMIN
//
// Must also set TESTMUX_EN high to get test outputs.
#define ADI_2_REFSYS_HPOSCCTL2_ATEST_SEL_W                                   2
#define ADI_2_REFSYS_HPOSCCTL2_ATEST_SEL_M                          0x00000030
#define ADI_2_REFSYS_HPOSCCTL2_ATEST_SEL_S                                   4

// Field:   [3:0] CURRMIRR_RATIO
//
// Set current mirror ratio in HPOSC.  Controls amount of current flowing in
// HPOSC oscillator core.  May need to increase from nominal if nominal setting
// does not result in oscillation. Two's complement encoding.
//
// 0x8:  Minimum current (~0 uA)
// 0x9:  50 uA
// 0x0:  400 uA
// 0x7:  Maximum current (~750 uA)
#define ADI_2_REFSYS_HPOSCCTL2_CURRMIRR_RATIO_W                              4
#define ADI_2_REFSYS_HPOSCCTL2_CURRMIRR_RATIO_M                     0x0000000F
#define ADI_2_REFSYS_HPOSCCTL2_CURRMIRR_RATIO_S                              0


#endif // __ADI_2_REFSYS__
