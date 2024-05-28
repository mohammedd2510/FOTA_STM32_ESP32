/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  FPEC_interface.h
 *        Author: Mohamed Osama
 *		   Date:  May 9, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef MCAL_FPEC_FPEC_INTERFACE_H_
#define MCAL_FPEC_FPEC_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/** @defgroup FLASHE_WRP_State FLASH WRP State
  * @{
  */
#define FPEC_OB_WRPSTATE_DISABLE       0x00000000U  /*!< Disable the write protection of the desired bank 1 sectors */
#define FPEC_OB_WRPSTATE_ENABLE        0x00000001U  /*!< Enable the write protection of the desired bank 1 sectors  */
/**
  * @}
  */

/** @defgroup FLASH_Option_Type FLASH Option Type
  * @{
  */
#define FPEC_OPTIONBYTE_WRP        0x00000001U  /*!< WRP option byte configuration  */
#define FPEC_OPTIONBYTE_RDP        0x00000002U  /*!< RDP option byte configuration  */

/**
  * @}
  */

/** @defgroup FLASH_Option_Bytes_Read_Protection FLASH Option Bytes Read Protection
  * @{
  */
#define FPEC_OB_RDP_LEVEL_0   ((u8)0xAA)
#define FPEC_OB_RDP_LEVEL_1   ((u8)0x55)

/**
  * @}
  */

#define FPEC_FLASH_SECTOR_0     0U /*!< Sector Number 0   */
#define FPEC_FLASH_SECTOR_1     1U /*!< Sector Number 1   */
#define FPEC_FLASH_SECTOR_2     2U /*!< Sector Number 2   */
#define FPEC_FLASH_SECTOR_3     3U /*!< Sector Number 3   */
#define FPEC_FLASH_SECTOR_4     4U /*!< Sector Number 4   */
#define FPEC_FLASH_SECTOR_5     5U /*!< Sector Number 5   */

#define FPEC_FLASH_TYPEPROGRAM_BYTE        0x00000000U  /*!< Program byte (8-bit) at a specified address           */
#define FPEC_FLASH_TYPEPROGRAM_HALFWORD    0x00000001U  /*!< Program a half-word (16-bit) at a specified address   */
#define FPEC_FLASH_TYPEPROGRAM_WORD        0x00000002U  /*!< Program a word (32-bit) at a specified address        */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
	    u32 FPEC_OptionType;   /*!< Option byte to be configured.
	                              This parameter can be a value of @ref FLASH_Option_Type */

	    u32 FPEC_WRPState;     /*!< Write protection activation or deactivation.
	                              This parameter can be a value of @ref FLASH_WRP_State */

	    u32 FPEC_WRPSector;         /*!< Specifies the sector(s) to be write protected.
	                              The value of this parameter depend on device used within the same series */

	   u32 FPEC_RDPLevel;     /*!< Set the read protection level.
	                              This parameter can be a value of @ref FLASHE_Option_Bytes_Read_Protection */
}FPEC_OB_Config_T;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void FPEC_MassErase(void);
void FPEC_EraseSectors(u32 Copy_u32Sector, u32 Copy_u32NbSectors);
void FPEC_OBGetConfig(FPEC_OB_Config_T* Copy_pFPECConfig);
void FPEC_OBProgram(FPEC_OB_Config_T* Copy_pFPECConfig);
void FPEC_FLASH_Program_Bytes(u32 Copy_u32Address, u8* Copy_u8Data,u8 Copy_u8ProgramSize,u32 Copy_u32Length);
 
#endif /* MCAL_FPEC_FPEC_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: FPEC_interface.h
 *********************************************************************************************************************/

