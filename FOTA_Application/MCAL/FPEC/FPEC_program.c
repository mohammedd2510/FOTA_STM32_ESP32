/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  FPEC_program.c
 *        Author: Mohamed Osama
 *		   Date:  May 9, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "FPEC_private.h"
#include "FPEC_interface.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
static void FLASH_UNLOCK()
{
	FPEC->KEYR = FLASH_KEY1;
	FPEC->KEYR = FLASH_KEY2;
}
static void FLASH_LOCK()
{
	WAIT_END_OF_OPERATION();
	SET_BIT(FPEC->CR,FLASH_LOCK_BIT_POS);
}
static void OB_UNLOCK()
{
	FPEC->OPTKEYR = OPTKEY1;
	FPEC->OPTKEYR = OPTKEY2;
}
static void OB_LOCK()
{
	WAIT_END_OF_OPERATION();
	SET_BIT(FPEC->OPTCR,OPT_LOCK_BIT_POS);
}
static void OB_LAUNCH()
{
	WAIT_END_OF_OPERATION();
	SET_BIT(FPEC->OPTCR,OPT_START_BIT_POS);
}
static void ERASE_SECTOR(u32 Copy_u32Sector)
{
	WAIT_END_OF_OPERATION();
	if(Copy_u32Sector > 5){
		Copy_u32Sector = 5;
	}
	SET_BIT(FPEC->CR ,SECTOR_ERASE_ACTIVE_BIT_POS);
	MODIFY_REG(FPEC->CR,0xF<<3,Copy_u32Sector<<3);
	SET_BIT(FPEC->CR,FLASH_OPERATION_START_BIT_POS);
	WAIT_END_OF_OPERATION();
}
static void WAIT_END_OF_OPERATION()
{
	while(GET_BIT(FPEC->SR,FLASH_BSY_FLAG_BIT_POS) == 1);
}

static void FLASH_PROGRAM_BYTE(u32 Addr,u8 Data)
{
	WAIT_END_OF_OPERATION();
	SET_BIT(FPEC->CR,FLASH_PROGRAMMING_ACTIVE_BIT_POS);
	*((volatile u8*)Addr) = Data;
	WAIT_END_OF_OPERATION();
}
static void FLASH_PROGRAM_HALFWORD(u32 Addr,u16 Data)
{
	WAIT_END_OF_OPERATION();
	SET_BIT(FPEC->CR,FLASH_PROGRAMMING_ACTIVE_BIT_POS);
	*((volatile u16*)Addr) = Data;
	WAIT_END_OF_OPERATION();
}
static void FLASH_PROGRAM_WORD(u32 Addr,u32 Data)
{
	WAIT_END_OF_OPERATION();
	SET_BIT(FPEC->CR,FLASH_PROGRAMMING_ACTIVE_BIT_POS);
	*((volatile u32*)Addr) = Data;
	WAIT_END_OF_OPERATION();
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void FPEC_MassErase(void)
{
	FLASH_UNLOCK();
	WAIT_END_OF_OPERATION();
	SET_BIT(FPEC->CR ,MASS_ERASE_ACTIVE_BIT_POS);
	SET_BIT(FPEC->CR,FLASH_OPERATION_START_BIT_POS);
	WAIT_END_OF_OPERATION();
	CLR_BIT(FPEC->CR ,MASS_ERASE_ACTIVE_BIT_POS);
	FLASH_LOCK();

}
void FPEC_EraseSectors(u32 Copy_u32Sector, u32 Copy_u32NbSectors)
{
	FLASH_UNLOCK();
	for(; Copy_u32Sector <Copy_u32NbSectors;Copy_u32Sector++)
	{
		ERASE_SECTOR(Copy_u32Sector);
	}
	CLR_BIT(FPEC->CR ,SECTOR_ERASE_ACTIVE_BIT_POS);
	FLASH_LOCK();
}
void FPEC_OBGetConfig(FPEC_OB_Config_T* Copy_pFPECConfig)
{
	switch(Copy_pFPECConfig->FPEC_OptionType)
	{
		case FPEC_OPTIONBYTE_WRP:
				Copy_pFPECConfig->FPEC_WRPSector = ((FPEC->OPTCR >>16)&0x3F);
				break;

		case FPEC_OPTIONBYTE_RDP:
			Copy_pFPECConfig->FPEC_RDPLevel =((FPEC->OPTCR >>8)&0xFF);
				break;
	}
}
void FPEC_OBProgram(FPEC_OB_Config_T* Copy_pFPECConfig)
{
	OB_UNLOCK();
	switch(Copy_pFPECConfig->FPEC_OptionType)
	{
		case FPEC_OPTIONBYTE_WRP:
			if(Copy_pFPECConfig->FPEC_WRPState == FPEC_OB_WRPSTATE_ENABLE)
			{
				MODIFY_REG(FPEC->OPTCR,0x3F<<16,((u8)(~(Copy_pFPECConfig->FPEC_WRPSector))&0x3F)<<16);
			}
			else
			{
				FPEC->OPTCR|=((Copy_pFPECConfig->FPEC_WRPSector)<<16);
			}
			break;
		case FPEC_OPTIONBYTE_RDP:
			MODIFY_REG(FPEC->OPTCR,0xFF<<8,Copy_pFPECConfig->FPEC_RDPLevel <<8);
			break;
	}
	OB_LAUNCH();
	WAIT_END_OF_OPERATION();
	OB_LOCK();
}
void FPEC_FLASH_Program_Bytes(u32 Copy_u32Address, u8* Copy_u8Data,u8 Copy_u8ProgramSize,u32 Copy_u32Length)
{

	u32 Local_u32Counter = ZERO_INIT;
	FLASH_UNLOCK();
	MODIFY_REG(FPEC->CR,0x3<<8,Copy_u8ProgramSize<<8);
	for(Local_u32Counter=ZERO_INIT; Local_u32Counter<Copy_u32Length; Local_u32Counter++)
		{
			switch (Copy_u8ProgramSize)
			{
				case FPEC_FLASH_TYPEPROGRAM_BYTE:
					FLASH_PROGRAM_BYTE(Copy_u32Address, (u8)(*(((u8*)Copy_u8Data)+Local_u32Counter)));
					Copy_u32Address+=1;
					break;
				case FPEC_FLASH_TYPEPROGRAM_HALFWORD:
					FLASH_PROGRAM_HALFWORD(Copy_u32Address, (u16)(*(((u16*)Copy_u8Data)+Local_u32Counter)));
					Copy_u32Address+=2;
					break;
				case FPEC_FLASH_TYPEPROGRAM_WORD:
					FLASH_PROGRAM_WORD(Copy_u32Address, (u32)(*(((u32*)Copy_u8Data)+Local_u32Counter)));
					Copy_u32Address+=4;
					break;
			}
		}

	FLASH_LOCK();
}


/**********************************************************************************************************************
 *  END OF FILE: FPEC_program.c
 *********************************************************************************************************************/
