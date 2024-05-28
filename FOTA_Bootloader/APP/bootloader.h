/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  bootloader.h
 *        Author: Mohamed Osama
 *		   Date:  May 26, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include <string.h>

#include "MCAL/UART/UART_Lcfg.h"
#include "MCAL/CRC/CRC_interface.h"
#include "MCAL/FPEC/FPEC_interface.h"
#include "MCAL/SCB/SCB_private.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define BL_HOST_COMMUNICATION_UART  &UART1_Cfg


#define HAL_MAX_DELAY       1800000

#define BL_HOST_BUFFER_RX_LENGTH 200

#define CBL_GET_VER_CMD              0x10
#define CBL_GET_CID_CMD              0x12
#define CBL_GET_RDP_STATUS_CMD       0x13
#define CBL_FLASH_ERASE_CMD          0x15
#define CBL_MEM_WRITE_CMD            0x16
#define CBL_GO_TO_MAIN_APP_CMD       0x18


#define CBL_VENDOR_ID 					100
#define CBL_SW_MAJOR_VERSION            1
#define CBL_SW_MINOR_VERSION            2
#define CBL_SW_PATCH_VERSION            0

#define CRC_TYPE_SIZE_BYTE	            4

#define CRC_VERIFICATION_FAILED       0
#define CRC_VERIFICATION_PASSED       1

#define CBL_SEND_NACK                0xAB
#define CBL_SEND_ACK                 0xCD

/* Start address of sector 2 */
#define FLASH_SECTOR1_BASE_ADDRESS   0x08004000U

#define ADDRESS_IS_INVALID           0x00
#define ADDRESS_IS_VALID             0x01

#define JUMP_FAILED                  0x00
#define JUMP_SUCCESSFUL                 0x01

#define STM32F401CCx_SRAM_SIZE         (64 * 1024)
#define STM32F401CCx_FLASH_SIZE        (256 * 1024)
#define STM32F401CCx_SRAM_END          (SRAM_BASE + STM32F401CCx_SRAM_SIZE)
#define STM32F401CCx_FLASH_END         (FLASH_BASE + STM32F401CCx_FLASH_SIZE)

#define SRAM_BASE 	0x20000000U
#define FLASH_BASE 	0x08000000U

/* CBL_FLASH_ERASE_CMD */
#define APPLICATION_SECTOR_NUMBER   1
#define FLASH_MAX_SECTOR_NUMBER  	5


#define SUCCESSFUL_ERASE             0x03


#define CBL_ROP_LEVEL_0              0x00
#define CBL_ROP_LEVEL_1              0x01
#define CBL_ROP_LEVEL_2              0x02


#define IDCODE_REG 			(*((volatile u32*)0xE0042000))
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
	BL_NACK = 0,
	BL_OK,
}BL_Status;

typedef void (*pMainApp)(void);
typedef void (*Jump_Ptr)(void);

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
BL_Status BL_UART_Fetch_Host_Command(void);
 
#endif /* BOOTLOADER_H_ */

/**********************************************************************************************************************
 *  END OF FILE: bootloader.h
 *********************************************************************************************************************/

