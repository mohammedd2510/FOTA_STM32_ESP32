/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  EXTI_Lcfg.c
 *        Author: Mohamed Osama
 *		   Date:  Mar 30, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EXTI_Lcfg.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
MEXTI_CONFIG_t EXTI0_CONFIG = {
	.MEXTI_Mode = MEXTI_INTERRUPT_MODE,
	. MEXTI_Line = MEXTI_EXTI0,
	. MEXTI_Port = MEXTI_PORTA,
	.MEXTI_SenseSignal = MEXTI_RISING_EDGE
};
MEXTI_CONFIG_t EXTI1_CONFIG = {
	.MEXTI_Mode = MEXTI_INTERRUPT_MODE,
	. MEXTI_Line = MEXTI_EXTI1,
	. MEXTI_Port = MEXTI_PORTB,
	.MEXTI_SenseSignal = MEXTI_RISING_EDGE
};

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  END OF FILE: EXTI_Lcfg.c
 *********************************************************************************************************************/