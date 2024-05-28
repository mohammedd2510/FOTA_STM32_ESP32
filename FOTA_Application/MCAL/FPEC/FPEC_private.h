/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  FPEC_private.h
 *        Author: Mohamed Osama
 *		   Date:  May 9, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef MCAL_FPEC_FPEC_PRIVATE_H_
#define MCAL_FPEC_FPEC_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define FPEC_BASE_ADDRESS  (0x40023C00)
#define FPEC    ((volatile FPEC_t*)(FPEC_BASE_ADDRESS))

#define FLASH_KEY1    0x45670123
#define FLASH_KEY2    0xCDEF89AB
#define FLASH_LOCK_BIT_POS 31

#define OPTKEY1  	  0x08192A3B
#define OPTKEY2 	  0x4C5D6E7F
#define OPT_LOCK_BIT_POS 0
#define OPT_START_BIT_POS 1
#define MAX_SECTOR    5

#define SECTOR_ERASE_ACTIVE_BIT_POS 2
#define MASS_ERASE_ACTIVE_BIT_POS 1
#define FLASH_PROGRAMMING_ACTIVE_BIT_POS 0
#define FLASH_OPERATION_START_BIT_POS 16
#define FLASH_BSY_FLAG_BIT_POS 16
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 OPTCR;
}FPEC_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static void FLASH_UNLOCK();
static void FLASH_LOCK();
static void OB_UNLOCK();
static void OB_LOCK();
static void OB_LAUNCH();
static void ERASE_SECTOR(u32 Copy_u32Sector);
static void WAIT_END_OF_OPERATION();

static void FLASH_PROGRAM_BYTE(u32 Addr,u8 Data);
static void FLASH_PROGRAM_HALFWORD(u32 Addr,u16 Data);
static void FLASH_PROGRAM_WORD(u32 Addr,u32 Data);


#endif /* MCAL_FPEC_FPEC_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: FPEC_private.h
 *********************************************************************************************************************/

