/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
***************************************************************************//*!
*
* @file flash.h
*
* @author Freescale
*
* @brief header file for FLASH module utilities (FLASH). 
*
*******************************************************************************
*
* provide APIs for accessing FLASH module (FLASH)
******************************************************************************/

#ifndef FLASH_H_
#define FLASH_H_
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Includes
******************************************************************************/
#include <include/derivative.h>
/******************************************************************************
* Constants
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/

/******************************************************************************
* Uncomment the following line to support programming flash while running code from flash 
*
*//*! @addtogroup flash_stalling_control_enable
* @{
*******************************************************************************/
#define TRUE	1
#define FLASH_ENABLE_STALLING_FLASH_CONTROLLER	/* enable flash stalling control */

/*! @} End of flash_stalling_control_enable                                  */

/******************************************************************************
* Memory Controller Command Completion Status Flag
*
*//*! @addtogroup flash_MGSTAT_list
* @{
*******************************************************************************/

#define FTMRE_FSTAT_MGSTAT0_MASK  (1)						/* FTMRE FSTAT MGSTAT0 MASK */
#define FTMRE_FSTAT_MGSTAT1_MASK  (1<<1)					/* FTMRE FSTAT MGSTAT1 MASK */
/*! @} End of flash_MGSTAT_list                                                */

#define FLASH_SECTOR_SIZE			512						/* FTMRE sector size*/
#define FLASH_START_ADDRESS			0						/* FTMRE start address */
#define EEPROM_START_ADDRESS		0x10000000				/* EEPRON start address*/

/******************************************************************************
* flash and eeprom driver error status
*
*//*! @addtogroup flash_error_list
* @{
*******************************************************************************/
#define FLASH_ERR_BASE				0x3000										/* FTMRE error base */
#define FLASH_ERR_SUCCESS			0											/* FTMRE sucess */
#define FLASH_ERR_INVALID_PARAM		(FLASH_ERR_BASE+1)							/* Invalid parameter error code */
#define EEPROM_ERR_SINGLE_BIT_FAULT	(FLASH_ERR_BASE+2)							/* EEPROM single bit fault error code */
#define EEPROM_ERR_DOUBLE_BIT_FAULT	(FLASH_ERR_BASE+4)							/* EEPROM double bits fault error code */
#define FLASH_ERR_ACCESS			(FLASH_ERR_BASE+8)							/* Flash access error code */
#define FLASH_ERR_PROTECTION		(FLASH_ERR_BASE+0x10)						/* Flash protection error code */
#define FLASH_ERR_MGSTAT0			(FLASH_ERR_BASE+0x11)						/* Flash verification error code */
#define FLASH_ERR_MGSTAT1			(FLASH_ERR_BASE+0x12)						/* Flash non-correctable error code */
#define FLASH_ERR_INIT_CCIF			(FLASH_ERR_BASE+0x14)						/* Flash driver init error with CCIF = 1 */
#define FLASH_ERR_INIT_FDIV			(FLASH_ERR_BASE+0x18)						/* Flash driver init error with wrong FDIV */
/*! @} End of flash_error_list                                                */

/******************************************************************************
* Flash and EEPROM commands
*
*//*! @addtogroup flash_command_list
* @{
*******************************************************************************/
#define FTMRE_CMD_ERASE_VERIFY_ALL						0x01					/* FTMRE erase verify all command */
#define FTMRE_CMD_ERASE_VERIFY_BLOCK					0x02					/* FTMRE erase verify block command */
#define FTMRE_CMD_ERASE_ALL								0x08					/* FTMRE erase all command */
#define FTMRE_CMD_ERASE_BLOCK							0x09					/* FTMRE erase blockcommand */
#define FTMRE_CMD_UNSECURE								0x0B					/* FTMRE unsecure command */
#define FTMRE_CMD_SET_USER_MARGIN						0x0D					/* FTMRE set usermargin command */

#define FLASH_CMD_ERASE_VERIFY_SECTION					0x03					/* FTMRE erase verify section command */
#define FLASH_CMD_READONCE								0x04					/* FTMRE read once command */
#define FLASH_CMD_PROGRAM								0x06					/* FTMRE program command */
#define FLASH_CMD_PROGRAMONCE							0x07					/* FTMRE program once command */
#define FLASH_CMD_ERASE_SECTOR							0x0A					/* FTMRE erase sector command */
#define FLASH_CMD_BACKDOOR_ACCESS						0x0C					/* FTMRE backdoor key access command */
#define FLASH_CMD_SET_USER_MARGIN_LEVEL					0x0D					/* FTMRE set user margin level command */

#define EEPROM_CMD_ERASE_VERIFY_SECTION					0x10					/* EEPROM erase berify section command */
#define EEPROM_CMD_PROGRAM								0x11					/* EEPROM program command */
#define EEPROM_CMD_ERASE_SECTOR 						0x12					/* EEPROM erase sector command */
/*! @} End of flash_command_list                                              */


/******************************************************************************
*
*//*! @addtogroup nvm_api_list
* @{
*******************************************************************************/
/******************************************************************************
* inline function
******************************************************************************/

/*****************************************************************************//*!
  *
  * @brief Command Complete Interrupt Enable.
  *        
  * @param none.
  *
  * @return none.
  *
  * @ Pass/ Fail criteria: none.
*****************************************************************************/
__STATIC_INLINE void FLASH_IntEnable( void )
{
	FTMRE_FCNFG |= FTMRE_FCNFG_CCIE_MASK;
}
/*****************************************************************************//*!
  *
  * @brief Command Complete Interrupt Disable.
  *        
  * @param none.
  *
  * @return none.
  *
  * @ Pass/ Fail criteria: none.
*****************************************************************************/
__STATIC_INLINE void FLASH_IntDisable( void )
{
	FTMRE_FCNFG &= ~FTMRE_FCNFG_CCIE_MASK;
}

/******************************************************************************
* Types
******************************************************************************/


/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/
uint16_t FLASH_Program1LongWord(uint32_t wNVMTargetAddress, uint32_t dwData);
uint16_t FLASH_Program2LongWords(uint32_t wNVMTargetAddress, uint32_t dwData0, uint32_t dwData1);
uint16_t FLASH_ProgramOnce(uint8_t bPhraseIndex, uint8_t *pData8Bytes);
uint16_t FLASH_ReadOnce(uint8_t bPhraseIndex, uint8_t *pData8Bytes);
uint16_t FLASH_EraseSector(uint32_t wNVMTargetAddress);
uint16_t FLASH_EraseVerifySection(uint32_t wNVMTargetAddress, uint16_t uiLongWordCount);
uint16_t FLASH_VerifyBackdoorKey(uint8_t *pbKey);
uint16_t FLASH_SetUserMarginLevel(uint32_t wNVMTargetAddress, uint16_t wMarginLevel, uint8_t bIsEEPROM);
uint16_t FLASH_Program(uint32_t wNVMTargetAddress, uint8_t *pData, uint16_t sizeBytes);

uint16_t FLASH_EraseBlock(uint32_t wNVMTargetAddress, uint8_t bIsEEPROM);
uint16_t FLASH_EraseVerifyBlock(uint32_t wNVMTargetAddress,uint8_t bIsEEPROM);
uint16_t FLASH_EraseAll(void);
uint16_t FLASH_EraseVerifyAll(void);
uint16_t FLASH_Unsecure(void);
uint16_t FLASH_EraseBlock_NoWait(uint32_t wNVMTargetAddress, uint8_t bIsEEPROM);
uint16_t FLASH_CheckErrStatus(void);

void FLASH_LaunchCMD(uint8_t bWaitComplete);

uint16_t EEPROM_Program1Byte(uint32_t wNVMTargetAddress, uint8_t bData);
uint16_t EEPROM_ProgramUpto4Bytes(uint32_t wNVMTargetAddress, uint8_t *pbData, uint8_t bByteCount);
uint16_t EEPROM_Program(uint32_t wNVMTargetAddress, uint8_t *pData, uint16_t sizeBytes);
uint16_t EEPROM_EraseVerifySection(uint32_t wNVMTargetAddress, uint16_t uiByteCount);
uint16_t EEPROM_Program1Byte_NoWait(uint32_t wNVMTargetAddress, uint8_t bData);
uint16_t EEPROM_ProgramUpto4Bytes_NoWait(uint32_t wNVMTargetAddress, uint8_t *pbData, uint8_t bByteCount);
uint16_t EEPROM_EraseSector_NoWait(uint32_t wNVMTargetAddress);
uint16_t EEPROM_EraseSector(uint32_t wNVMTargetAddress);

uint16_t FLASH_Init(uint32_t BusClock);

/*! @} End of nvm_api_list                                              */
/********************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* FLASH_H_ */
