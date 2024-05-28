/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  LEDMAT_interface.h
 *        Author: Mohamed Osama
 *		   Date:  Mar 22, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef INC_HAL_LEDMAT_LEDMAT_INTERFACE_H_
#define INC_HAL_LEDMAT_LEDMAT_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/TIM/TIM_Lcfg.h"
#include "MCAL/RCC/RCC_interface.h"
#include<string.h>
#include"HAL/LEDMAT/LEDMAT_font.h"
#include"HAL/LEDMAT/LEDMAT_config.h"
#include "HAL/SHIFT_REG_16BIT/SHIFTREG_Lcfg.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define LED_MATRIX_ROW_NUM	8
#define LED_MATRIX_COL_NUM	8

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
#if (LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED)
	port_index_t port;
	pin_index_t  pin ;
	gpio_logic_t state;
#else
    u8 ShiftRegPin;
#endif
}ledmat_column_t;

typedef struct
{
#if (LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED)
	port_index_t port;
	pin_index_t  pin ;
	gpio_logic_t state;
#else
 u8 ShiftRegPin;
#endif
}ledmat_row_t;

typedef struct
{
	ledmat_row_t row[LED_MATRIX_ROW_NUM];
	ledmat_column_t col[LED_MATRIX_COL_NUM];
	u8	LedMatrix_Buffer[8];
#if (LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_ENABLED)
	SHIFTREG_t* ptrShiftRegCfg;
#endif
}ledmat_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
void HLEDMAT_voidInit(ledmat_t* ledmat_obj);

void HLEDMAT_voidDisplayFrame(ledmat_t* ledmat_obj,u8* Copy_pu8FrameData);

void HLEDMAT_voidDisplayFrameWithDelay(ledmat_t* ledmat_obj,u8* Copy_pu8FrameData , u32 time_ms);

void HLEDMAT_voidDisplayChar(ledmat_t* ledmat_obj,u8 Copy_u8Chr);

void HLEDMAT_voidDisplayString(ledmat_t* ledmat_obj,u8* Copy_pu8Str,u32 time_ms);

void HLEDMAT_voidDisplayScrollingString(ledmat_t* ledmat_obj,u8* Copy_pu8Str,u32 time_ms);

void HLEDMAT_voidDisplayScrollingString_WithStopFlag(ledmat_t* ledmat_obj,u8* Copy_pu8Str,u32 Copy_u32TimeMs , u8* StopFlag);

void HLEDMAT_voidScrollFrameRight(ledmat_t* ledmat_obj,u32 time_ms);

void HLEDMAT_voidScrollFrameLeft(ledmat_t* ledmat_obj,u32 time_ms);
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif /* INC_HAL_LEDMAT_LEDMAT_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: LEDMAT_interface.h
 *********************************************************************************************************************/
