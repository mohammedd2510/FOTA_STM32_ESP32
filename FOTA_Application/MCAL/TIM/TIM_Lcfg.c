/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TIM_Lcfg.c
 *        Author: Mohamed Osama
 *		   Date:  May 20, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TIM_Lcfg.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
TIM_Config_t TIM2_Cfg ={
		.TIM_Direction = TIM_DOWN_COUNTER,
		.TIM_Instance = TIM2,
		.TIM_Mode = TIM_NORMAL_MODE,
		.TIM_Preload = 0xFFFF,
		.TIM_Prescaler = 84,
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
 *  END OF FILE: TIM_Lcfg.c
 *********************************************************************************************************************/
