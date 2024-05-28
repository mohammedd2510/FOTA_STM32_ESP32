/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:   Bootloader_Host.h
 *        Author: Mohamed Osama
 *		   Date:   5/27/2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef BOOTLOADER_HOST_H
#define BOOTLOADER_HOST_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "mqtt.h"
#include "Fire_Base.h"
#include <stdio.h>
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define CBL_GET_VER_CMD              0x10
#define CBL_GET_CID_CMD              0x12
#define CBL_GET_RDP_STATUS_CMD       0x13
#define CBL_FLASH_ERASE_CMD          0x15
#define CBL_MEM_WRITE_CMD            0x16
#define CBL_GO_TO_MAIN_APP_CMD       0x18

#define JUMP_FAILED                  0x00
#define JUMP_SUCCESSFUL              0x01

#define FLASH_PAYLOAD_WRITE_FAILED    0x00
#define FLASH_PAYLOAD_WRITE_PASSED    0x01

#define BL_HOST_BUFFER_TX_LENGTH 200
#define BL_HOST_BUFFER_RX_LENGTH 50

#define CBL_SEND_NACK                0xAB
#define CBL_SEND_ACK                 0xCD
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern uint8_t BL_Host_Buffer[BL_HOST_BUFFER_TX_LENGTH];
extern uint8_t BL_Host_Receive_Buffer[BL_HOST_BUFFER_RX_LENGTH]; 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void BL_Host_Get_Version(void);

void BL_Host_Get_Chip_ID(void);

void BL_Host_Get_RDP(void);

void BL_Host_Erase_Application(void);

void BL_Host_Jump_To_Application(void);

void BL_Host_Flash_Application(void);
 
#endif /* BOOTLOADER_HOST_H */

/**********************************************************************************************************************
 *  END OF FILE: Bootloader_Host.h
 *********************************************************************************************************************/

