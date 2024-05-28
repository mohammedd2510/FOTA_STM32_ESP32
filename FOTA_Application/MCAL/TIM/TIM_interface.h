/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TIM_interface.h
 *        Author: Mohamed Osama
 *		   Date:  May 20, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef TIM_TIM_INTERFACE_H_
#define TIM_TIM_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "TIM_private.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/** @defgroup TIM_Mode
  * @{
  */

	#define TIM_NORMAL_MODE 			0x00
	#define TIM_INPUT_CAPTURE_MODE 		0x01
	#define TIM_PWM_MODE				0X02
/**
  * @}
  */

/** @defgroup TIM_IC_Mode
  * @{
  */

	#define TIM_IC_RISING_EDGE 			0x00
	#define TIM_IC_FALLING_EDGE			0x01
	#define TIM_IC_BOTH_EDGES			0X02
/**
  * @}
  */

/** @defgroup TIM_Direction
  * @{
  */

	#define TIM_UP_COUNTER 			0x00
	#define TIM_DOWN_COUNTER		0x01
/**
  * @}
  */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
	volatile TIM_t* TIM_Instance;
	u16 TIM_Prescaler;
	u8  TIM_Direction;
	u32 TIM_Preload;
	u16 TIM_RepetitionCounter;
	u8  TIM_Mode;
	u8  TIM_IC_Mode;
	u8  TIM_PWM_DutyCycle;
	u8  CAPTURE_COMPARE_INT_ENABLE;
	pCallBackNotification UP_Callback;
	pCallBackNotification CC_Callback;
}TIM_Config_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void TIM_Init(const TIM_Config_t* TIM_Config);
void TIM_DeInit(const TIM_Config_t* TIM_Config);
void TIM_Reset(const TIM_Config_t* TIM_Config);
u32 TIM_GetElapsedTime(const TIM_Config_t* TIM_Config);
void TIM_SetPreload(TIM_Config_t* TIM_Config , u32 preload);
void TIM_SingleInterval(TIM_Config_t* TIM_Config , u32 preload , pCallBackNotification callback);
void TIM_PeriodicInterval(TIM_Config_t* TIM_Config , u32 preload , pCallBackNotification callback);
void TIM_Set_DutyCycle(const TIM_Config_t* TIM_Config , u16 DutyCycle);
void TIM_Change_CaptureMode(TIM_Config_t* TIM_Config , u8 CaptureMode);
u32 TIM_GetInputCapture(const TIM_Config_t* TIM_Config);
 
#endif /* TIM_TIM_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: TIM_interface.h
 *********************************************************************************************************************/

