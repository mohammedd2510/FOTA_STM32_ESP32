/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IR_program.c
 *        Author: Mohamed Osama
 *		   Date:  Mar 31, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "IR_interface.h"
#include "IR_private.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static pCallBackNotification IR_callback = NULL;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
static volatile u32 IR_ReceivedData = ZERO_INIT;
static volatile u8  IR_ReceivedFlag = ZERO_INIT;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void IR_voidInit (IR_Config_t *Copy_IR_Config , pCallBackNotification IR_CallbackNotification)
{
	MEXTI_CONFIG_t IR_EXTI_Config;
	IR_EXTI_Config.MEXTI_Mode = MEXTI_INTERRUPT_MODE;
	IR_EXTI_Config.MEXTI_SenseSignal = Copy_IR_Config->IR_Trigger_Mode;
	IR_EXTI_Config.MEXTI_Line = Copy_IR_Config->IR_Pin;
    IR_EXTI_Config.MEXTI_Port = Copy_IR_Config->IR_Port;
	MEXTI_voidInit(&IR_EXTI_Config,IR_EXTI_Handler);
	switch (Copy_IR_Config->IR_Port)
	{
	    case GPIO_PORTA:
	      RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOAEN);
	      break;
	    case GPIO_PORTB:
	      RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOBEN);
	      break;
	    case GPIO_PORTC:
	      RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOCEN);
	      break;
	    default:
	      break;
	  }
	  GPIO_voidSetPinMode(Copy_IR_Config->IR_Port,Copy_IR_Config->IR_Pin,GPIO_INPUT_PIN_MODE);
	  GPIO_voidSetPinPullUpDownResistor(Copy_IR_Config->IR_Port,Copy_IR_Config->IR_Pin,GPIO_INPUT_PIN_FLOAT);
	  IR_callback = IR_CallbackNotification;
}

u8 IR_u8GetReceivedStatus(void)
{
	u8 Local_IR_ReceivedFlag = IR_ReceivedFlag;
	if(IR_ReceivedFlag == IR_RECEIVED_DATA_STATUS)
	{
		IR_ReceivedFlag = IR_NOT_RECEIVED_DATA_STATUS;
	}
	return Local_IR_ReceivedFlag;
}

u32  IR_u32GetReceivedData(void)
{
	return IR_ReceivedData;
}

static void IR_EXTI_Handler()
{
	static u8 IR_Status_Flag = IR_START_SIGNAL_STARTED;
	static s8 IR_BitCounter = IR_BIT_COUNT_INIT;
	u32 IR_ElapsedTime = ZERO_INIT;
	if(IR_Status_Flag == IR_START_SIGNAL_STARTED)
	{
		IR_Status_Flag = IR_START_SIGNAL_ENDED;
		TIM_SetPreload(&TIM2_Cfg,IR_START_SIGNAL_RANGE_HIGH);
	}
	else if (IR_Status_Flag == IR_START_SIGNAL_ENDED)
	{
		IR_ElapsedTime = TIM_GetElapsedTime(&TIM2_Cfg);
		if(IR_ElapsedTime >= IR_START_SIGNAL_RANGE_LOW && IR_ElapsedTime <= IR_START_SIGNAL_RANGE_HIGH)
		{
			IR_Status_Flag = IR_GETTING_DATA;
		}
		else if(IR_ElapsedTime >=IR_REPEAT_SIGNAL_RANGE_LOW  && IR_ElapsedTime <= IR_REPEAT_SIGNAL_RANGE_HIGH){
			IR_callback();
		}
		TIM_SetPreload(&TIM2_Cfg,IR_START_SIGNAL_RANGE_HIGH);
	}
	else if (IR_Status_Flag == IR_GETTING_DATA)
	{
		IR_ElapsedTime = TIM_GetElapsedTime(&TIM2_Cfg);
		if(IR_ElapsedTime >= IR_LOW_LEVEL_SIGNAL_RANGE_LOW && IR_ElapsedTime <= IR_LOW_LEVEL_SIGNAL_RANGE_HIGH)
		{
			CLR_BIT(IR_ReceivedData,IR_BitCounter);
		}
		else if (IR_ElapsedTime >= IR_HIGH_LEVEL_SIGNAL_RANGE_LOW && IR_ElapsedTime <= IR_HIGH_LEVEL_SIGNAL_RANGE_HIGH)
		{
			SET_BIT(IR_ReceivedData,IR_BitCounter);
		}
		IR_BitCounter--;
		if(IR_BitCounter == IR_BIT_COUNT_END) IR_Status_Flag = IR_END_OF_FRAME_DETECTED;
		TIM_SetPreload(&TIM2_Cfg,IR_START_SIGNAL_RANGE_HIGH);
	}
	else if(IR_Status_Flag == IR_END_OF_FRAME_DETECTED)
	{
		IR_BitCounter = IR_BIT_COUNT_INIT;
		IR_Status_Flag =  IR_START_SIGNAL_STARTED;
		if(IR_callback != NULL){
			IR_callback();
		}
		else
		{
			IR_ReceivedFlag = IR_RECEIVED_DATA_STATUS;
		}

	}

}

/**********************************************************************************************************************
 *  END OF FILE: IR_program.c
 *********************************************************************************************************************/
