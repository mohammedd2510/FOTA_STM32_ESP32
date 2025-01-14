/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  CRC_private.h
 *        Author: Mohamed Osama
 *		   Date:  May 26, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef CRC_CRC_PRIVATE_H_
#define CRC_CRC_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/STD_TYPES.h"
#include "MCAL/RCC/RCC_interface.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define CRC_BASE_ADDRESS 0x40023000
#define CRC ((CRC_t*)CRC_BASE_ADDRESS)

#define CRC_CR_RESET_Pos    (0U)
#define CRC_CR_RESET_Msk    (0x1UL << CRC_CR_RESET_Pos)                         /*!< 0x00000001 */
#define CRC_CR_RESET        CRC_CR_RESET_Msk                                   /*!< RESET bit */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct{
	volatile u32 DR;
	volatile u32 IDR;
	volatile u32 CR;
}CRC_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif /* CRC_CRC_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: CRC_private.h
 *********************************************************************************************************************/

