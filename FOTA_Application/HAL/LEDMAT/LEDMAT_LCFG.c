/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  LEDMAT_LCFG.c
 *        Author: Mohamed Osama
 *		   Date:  Mar 24, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include"HAL/LEDMAT/LEDMAT_Lcfg.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#if (LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED)
ledmat_t ledmat_obj =
{
		.row[0].port = GPIO_PORTB,
		.row[0].pin = GPIO_PIN0,
		.row[0].state = GPIO_LOW,
		.row[1].port = GPIO_PORTB,
		.row[1].pin = GPIO_PIN1,
		.row[1].state = GPIO_LOW,
		.row[2].port = GPIO_PORTB,
		.row[2].pin = GPIO_PIN2,
		.row[2].state = GPIO_LOW,
		.row[3].port = GPIO_PORTB,
		.row[3].pin = GPIO_PIN3,
		.row[3].state = GPIO_LOW,
		.row[4].port = GPIO_PORTB,
		.row[4].pin = GPIO_PIN4,
		.row[4].state = GPIO_LOW,
		.row[5].port = GPIO_PORTB,
		.row[5].pin = GPIO_PIN5,
		.row[5].state = GPIO_LOW,
		.row[6].port = GPIO_PORTB,
		.row[6].pin = GPIO_PIN6,
		.row[6].state = GPIO_LOW,
		.row[7].port = GPIO_PORTB,
		.row[7].pin = GPIO_PIN7,
		.row[7].state = GPIO_LOW,
		.col[0].port = GPIO_PORTA,
		.col[0].pin = GPIO_PIN0,
		.col[0].state = GPIO_LOW,
		.col[1].port = GPIO_PORTA,
		.col[1].pin = GPIO_PIN1,
		.col[1].state = GPIO_LOW,
		.col[2].port = GPIO_PORTA,
		.col[2].pin = GPIO_PIN2,
		.col[2].state = GPIO_LOW,
		.col[3].port = GPIO_PORTA,
		.col[3].pin = GPIO_PIN3,
		.col[3].state = GPIO_LOW,
		.col[4].port = GPIO_PORTA,
		.col[4].pin = GPIO_PIN4,
		.col[4].state = GPIO_LOW,
		.col[5].port = GPIO_PORTA,
		.col[5].pin = GPIO_PIN5,
		.col[5].state = GPIO_LOW,
		.col[6].port = GPIO_PORTA,
		.col[6].pin = GPIO_PIN6,
		.col[6].state = GPIO_LOW,
		.col[7].port = GPIO_PORTA,
		.col[7].pin = GPIO_PIN7,
		.col[7].state = GPIO_LOW,
};
#else
ledmat_t ledmat_obj =
{
		.row[0].ShiftRegPin = SHIFT_REG_Q0,
		.row[1].ShiftRegPin = SHIFT_REG_Q1,
		.row[2].ShiftRegPin = SHIFT_REG_Q2,
		.row[3].ShiftRegPin = SHIFT_REG_Q3,
		.row[4].ShiftRegPin = SHIFT_REG_Q4,
		.row[5].ShiftRegPin = SHIFT_REG_Q5,
		.row[6].ShiftRegPin = SHIFT_REG_Q6,
		.row[7].ShiftRegPin = SHIFT_REG_Q7,
		.col[0].ShiftRegPin = SHIFT_REG_Q8,
		.col[1].ShiftRegPin = SHIFT_REG_Q9,
		.col[2].ShiftRegPin = SHIFT_REG_Q10,
		.col[3].ShiftRegPin = SHIFT_REG_Q11,
		.col[4].ShiftRegPin = SHIFT_REG_Q12,
		.col[5].ShiftRegPin = SHIFT_REG_Q13,
		.col[6].ShiftRegPin = SHIFT_REG_Q14,
		.col[7].ShiftRegPin = SHIFT_REG_Q15,
		.ptrShiftRegCfg = &SHIFTREG_Config
};

#endif



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
 *  END OF FILE: LEDMAT_LCFG.c
 *********************************************************************************************************************/
