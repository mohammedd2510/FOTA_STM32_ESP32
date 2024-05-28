/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  bootloader.c
 *        Author: Mohamed Osama
 *		   Date:  May 26, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "bootloader.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static u8 BL_Host_Buffer[BL_HOST_BUFFER_RX_LENGTH];


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static void Bootloader_Get_Version(u8 *Host_Buffer);
static void Bootloader_Get_Chip_Identification_Number(u8 *Host_Buffer);
static void Bootloader_Read_Protection_Level(u8 *Host_Buffer);
static void Bootloader_Erase_Application(u8 *Host_Buffer);
static void Bootloader_Flash_Application(u8 *Host_Buffer);
static void Bootloader_Jump_To_Application(u8 *Host_Buffer);

static u8 Bootloader_CRC_Verify(u8 *pData , u32 Data_Len , u32 Host_CRC);
static void Bootloader_Send_ACK(u8 Replay_Len);
static void Bootloader_Send_NACK(void);
static void Bootloader_Send_Data_To_Host(u8 *Host_Buffer , u32 Host_Buffer_Len);
static u8 Host_Address_Verification(u32 Jump_Address);
static u8 CBL_STM32F401CCx_Get_RDP_Level(void);
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
static void Bootloader_Send_ACK(u8 Replay_Len)
{
	u8 Ack_Value[2] = {0};
	Ack_Value[0] = CBL_SEND_ACK;
	Ack_Value[1] = Replay_Len;
	Bootloader_Send_Data_To_Host((u8*)Ack_Value , 2 );
}
static void Bootloader_Send_NACK(void)
{
	u8 Ack_Value = CBL_SEND_NACK;
	Bootloader_Send_Data_To_Host(&Ack_Value , 1);
}
static u8 Bootloader_CRC_Verify(u8 *pData , u32 Data_Len , u32 Host_CRC)
{
	u8 CRC_Status = CRC_VERIFICATION_FAILED;
	u32 MCU_CRC_Calculated = 0;
	u8 Data_Counter = 0;
	u32 Data_Buffer = 0;
	/* Calculate CRC32 */
	for(Data_Counter = 0 ; Data_Counter < Data_Len ; Data_Counter++)
	{
		Data_Buffer = (u32)pData[Data_Counter];
		MCU_CRC_Calculated = CRC_Accumulate(&Data_Buffer , 1);
	}
	/* Reset The CRC Caclulation Unit */
	CRC_DR_RESET();

	/* Compare the host CRC32 with the calculated CRC32 */
	if(Host_CRC == MCU_CRC_Calculated){
		CRC_Status = CRC_VERIFICATION_PASSED;
	}
	else if (Host_CRC != MCU_CRC_Calculated){
		CRC_Status = CRC_VERIFICATION_FAILED;
	}
	return CRC_Status;
}

static u8 CBL_STM32F401CCx_Get_RDP_Level(void){
	FPEC_OB_Config_T FLASH_OBProgram;
	FLASH_OBProgram.FPEC_OptionType = FPEC_OPTIONBYTE_RDP;
	/* Get the Option byte configuration */
	FPEC_OBGetConfig(&FLASH_OBProgram);

	return (u8)(FLASH_OBProgram.FPEC_RDPLevel);
}

static void Bootloader_Send_Data_To_Host(u8 *Host_Buffer , u32 Host_Buffer_Len)
{
	UART_voidTransmit(BL_HOST_COMMUNICATION_UART , Host_Buffer , Host_Buffer_Len , HAL_MAX_DELAY);
}
static u8 Host_Address_Verification(u32 Jump_Address){
	u8 Address_Verification = ADDRESS_IS_INVALID;
	if((Jump_Address >= SRAM_BASE) && (Jump_Address <= STM32F401CCx_SRAM_END)){
		Address_Verification = ADDRESS_IS_VALID;
	}
	else if((Jump_Address >= FLASH_BASE) && (Jump_Address <= STM32F401CCx_FLASH_END)){
		Address_Verification = ADDRESS_IS_VALID;
	}
	else{
		Address_Verification = ADDRESS_IS_INVALID;
	}
	return Address_Verification;
}
static void Bootloader_Get_Version(u8 *Host_Buffer)
{
	u8 BL_Version[4] = { CBL_VENDOR_ID, CBL_SW_MAJOR_VERSION, CBL_SW_MINOR_VERSION, CBL_SW_PATCH_VERSION };
	u16 Host_CMD_Packet_Len = 0;
	u32 Host_CRC32 = 0;

	/* Extract the CRC32 and Packet length from the host buffer */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;
	Host_CRC32 = *((u32*)((Host_Buffer+Host_CMD_Packet_Len)-CRC_TYPE_SIZE_BYTE));

	/*********** CRC Verification *************/
	if(Bootloader_CRC_Verify(Host_Buffer,Host_CMD_Packet_Len - 4, Host_CRC32) == CRC_VERIFICATION_PASSED)
	{
		Bootloader_Send_ACK(4);
		Bootloader_Send_Data_To_Host((u8*)BL_Version ,4);
	}
	else
	{
		Bootloader_Send_NACK();
	}
}
static void Bootloader_Get_Chip_Identification_Number(u8 *Host_Buffer)
{
	u16 Host_CMD_Packet_Len = 0;
	u32 Host_CRC32 = 0;
	u16 MCU_Identification_Number = 0;
	/* Extract the CRC32 and Packet length from the host buffer */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;
	Host_CRC32 = *((u32*)((Host_Buffer+Host_CMD_Packet_Len)-CRC_TYPE_SIZE_BYTE));

	MCU_Identification_Number =(u16)(IDCODE_REG & 0x000000FFF);
	/*********** CRC Verification *************/
	if(Bootloader_CRC_Verify(Host_Buffer,Host_CMD_Packet_Len - 4, Host_CRC32) == CRC_VERIFICATION_PASSED)
	{
		Bootloader_Send_ACK(2);
		Bootloader_Send_Data_To_Host((u8 *)(&MCU_Identification_Number), 2);
	}
	else
	{
		Bootloader_Send_NACK();
	}
}
static void Bootloader_Read_Protection_Level(u8 *Host_Buffer)
{
	u16 Host_CMD_Packet_Len = 0;
	u32 Host_CRC32 = 0;
	u8 RDP_Level = 0;

	/* Extract the CRC32 and Packet length from the host buffer */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;
	Host_CRC32 = *((u32*)((Host_Buffer+Host_CMD_Packet_Len)-CRC_TYPE_SIZE_BYTE));

	/*********** CRC Verification *************/
	if(Bootloader_CRC_Verify(Host_Buffer,Host_CMD_Packet_Len - 4, Host_CRC32) == CRC_VERIFICATION_PASSED)
	{
		Bootloader_Send_ACK(1);
		/* Read Protection Level */
		RDP_Level = CBL_STM32F401CCx_Get_RDP_Level();
		/* Report Valid Protection Level */
		Bootloader_Send_Data_To_Host((u8 *)&RDP_Level, 1);
	}
	else
	{
		Bootloader_Send_NACK();
	}
}
static void Bootloader_Erase_Application(u8 *Host_Buffer){
	u16 Host_CMD_Packet_Len = 0;
	u32 Host_CRC32 = 0;
	u8 Erase_Status = SUCCESSFUL_ERASE;

	/* Extract the CRC32 and Packet length from the host buffer */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;
	Host_CRC32 = *((u32*)((Host_Buffer+Host_CMD_Packet_Len)-CRC_TYPE_SIZE_BYTE));

	/*********** CRC Verification *************/
	if(Bootloader_CRC_Verify(Host_Buffer,Host_CMD_Packet_Len - 4, Host_CRC32) == CRC_VERIFICATION_PASSED)
	{
		Bootloader_Send_ACK(1);
		/* Perform Mass erase or sector erase of the user flash */
		FPEC_EraseSectors(APPLICATION_SECTOR_NUMBER, FLASH_MAX_SECTOR_NUMBER-APPLICATION_SECTOR_NUMBER);
		Bootloader_Send_Data_To_Host((u8 *)&Erase_Status, 1);
	}
	else
	{
		Bootloader_Send_NACK();
	}
}
static void Bootloader_Flash_Application(u8 *Host_Buffer)
{
	u16 Host_CMD_Packet_Len = 0;
	u32 Host_CRC32 = 0;
	u32 HOST_Address = 0;
	u8 Payload_Len = 0;
	u8 Address_Verification = ADDRESS_IS_INVALID;

	/* Extract the CRC32 and Packet length from the host buffer */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;
	Host_CRC32 = *((u32*)((Host_Buffer+Host_CMD_Packet_Len)-CRC_TYPE_SIZE_BYTE));

	/*********** CRC Verification *************/
	if(Bootloader_CRC_Verify(Host_Buffer,Host_CMD_Packet_Len - 4, Host_CRC32) == CRC_VERIFICATION_PASSED)
	{
		Bootloader_Send_ACK(1);
		/* Extract the start address from the Host packet */
		HOST_Address = *((u32 *)(&Host_Buffer[2]));
		/* Extract the payload length from the Host packet */
		Payload_Len = Host_Buffer[6];
		/* Verify the Extracted address to be valid address */
		Address_Verification = Host_Address_Verification(HOST_Address);
		if(ADDRESS_IS_VALID == Address_Verification)
		{
			/* Write the payload to the Flash memory */
			FPEC_FLASH_Program_Bytes(HOST_Address,(u8 *)&Host_Buffer[7], Payload_Len , FPEC_FLASH_TYPEPROGRAM_BYTE);
			Bootloader_Send_Data_To_Host((u8 *)&Address_Verification, 1);
		}
		else
		{
			/* Report address verification failed */
			Bootloader_Send_Data_To_Host((u8 *)&Address_Verification, 1);
		}
	}
	else
	{
		Bootloader_Send_NACK();
	}
}
static void Bootloader_Jump_To_Application(u8 *Host_Buffer)
{
	u16 Host_CMD_Packet_Len = 0;
	u32 Host_CRC32 = 0;
	u32 MainAppAddr = 0;
	pMainApp ResetHandler_Address = NULL;
	u8 Jump_Status = JUMP_FAILED;
	/* Extract the CRC32 and Packet length from the host buffer */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;
	Host_CRC32 = *((u32*)((Host_Buffer+Host_CMD_Packet_Len)-CRC_TYPE_SIZE_BYTE));

	/*********** CRC Verification *************/
	if(Bootloader_CRC_Verify(Host_Buffer,Host_CMD_Packet_Len - 4, Host_CRC32) == CRC_VERIFICATION_PASSED)
	{
		Bootloader_Send_ACK(1);
		/* Reset Handler definition function of our main application */
		 MainAppAddr = *((volatile u32 *)(FLASH_SECTOR1_BASE_ADDRESS + 4));
		 if(MainAppAddr !=0XFFFFFFFF)
		 {
			 Jump_Status = JUMP_SUCCESSFUL;
			 Bootloader_Send_Data_To_Host((u8 *)&Jump_Status, 1);
			 SCB->VTOR = FLASH_SECTOR1_BASE_ADDRESS;
			 /* Fetch the reset handler address of the user application */
			 ResetHandler_Address = (pMainApp)(MainAppAddr);
			 /* Jump to Application Reset Handler */
			 ResetHandler_Address();
		 }
		 else
		 {
			 Bootloader_Send_Data_To_Host((u8 *)&Jump_Status, 1);
		 }
	}
	else
	{
		Bootloader_Send_NACK();
	}
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
BL_Status BL_UART_Fetch_Host_Command(void)
{

	BL_Status ret = BL_OK;
	Std_ReturnType HAL_Status = STD_NOK;
	u8 Data_Length = 0;
	memset(BL_Host_Buffer,0,BL_HOST_BUFFER_RX_LENGTH);
	HAL_Status = UART_voidReceive(BL_HOST_COMMUNICATION_UART,BL_Host_Buffer,1,HAL_MAX_DELAY);
	if (HAL_Status != STD_OK)
	{
		ret = BL_NACK;
	}
	else
	{
		Data_Length = BL_Host_Buffer[0];
		HAL_Status = UART_voidReceive(BL_HOST_COMMUNICATION_UART,&BL_Host_Buffer[1],Data_Length,HAL_MAX_DELAY);
		if (HAL_Status != STD_OK)
		{
			ret = BL_NACK;
		}
		else{
			switch(BL_Host_Buffer[1]){
				case CBL_GET_VER_CMD:
					Bootloader_Get_Version(BL_Host_Buffer);
					break;
				case CBL_GET_CID_CMD:
					Bootloader_Get_Chip_Identification_Number(BL_Host_Buffer);
					break;
						case CBL_GET_RDP_STATUS_CMD:
					Bootloader_Read_Protection_Level(BL_Host_Buffer);
					break;
				case CBL_FLASH_ERASE_CMD:
					Bootloader_Erase_Application(BL_Host_Buffer);
					break;
				case CBL_MEM_WRITE_CMD:
					Bootloader_Flash_Application(BL_Host_Buffer);
					break;
				case CBL_GO_TO_MAIN_APP_CMD:
					Bootloader_Jump_To_Application(BL_Host_Buffer);
					break;
				default:
					break;
			}
		}
	}

	return ret;
}



/**********************************************************************************************************************
 *  END OF FILE: bootloader.c
 *********************************************************************************************************************/
