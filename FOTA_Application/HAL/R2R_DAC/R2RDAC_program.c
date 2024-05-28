/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  R2RDAC_program.c
 *        Author: Mohamed Osama
 *		   Date:  Apr 5, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "HAL/R2R_DAC/R2RDAC_interface.h"
#include "HAL/R2R_DAC/R2RDAC_private.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
static void R2RDAC_Bit_init(port_index_t R2RDAC_BitPort, pin_index_t R2RDAC_BitPin)
{
	switch (R2RDAC_BitPort)
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
	  GPIO_voidSetPinMode(R2RDAC_BitPort,R2RDAC_BitPin,GPIO_OUTPUT_PIN_MODE);
	  GPIO_voidSetPinOutputMode(R2RDAC_BitPort,R2RDAC_BitPin,GPIO_OUTPUT_PIN_PUSH_PULL);
	  GPIO_voidSetPinOutputSpeed(R2RDAC_BitPort,R2RDAC_BitPin,GPIO_OUTPUT_PIN_LOW_SPEED);
	  GPIO_voidSetPinValue(R2RDAC_BitPort,R2RDAC_BitPin,GPIO_LOW);
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void R2RDAC_voidInit(R2RDAC_config_t* R2RDAC_Config)
{
	u8 	Local_DAC_BitCounter = ZERO_INIT;
	for(Local_DAC_BitCounter = ZERO_INIT;Local_DAC_BitCounter<R2RDAC_RESOLUTION;Local_DAC_BitCounter++)
	{
		R2RDAC_Bit_init(R2RDAC_Config->R2RDAC_Bit_Port[Local_DAC_BitCounter],R2RDAC_Config->R2RDAC_Bit_Pin[Local_DAC_BitCounter]);
	}

}
void R2RDAC_voidSetSignal(R2RDAC_config_t* R2RDAC_Config,const u8* Copy_pu8Signal , u32 Copy_u32SignalLength)
{
	u32 Local_DAC_Counter = ZERO_INIT;
	u8 	Local_DAC_BitCounter = ZERO_INIT;
	for(Local_DAC_Counter=ZERO_INIT;Local_DAC_Counter<Copy_u32SignalLength;Local_DAC_Counter++)
	{
		for(Local_DAC_BitCounter=ZERO_INIT;Local_DAC_BitCounter<R2RDAC_RESOLUTION;Local_DAC_BitCounter++)
			{
				GPIO_voidSetPinValue
				(
					R2RDAC_Config->R2RDAC_Bit_Port[Local_DAC_BitCounter],
					R2RDAC_Config->R2RDAC_Bit_Pin[Local_DAC_BitCounter],
					GET_BIT(Copy_pu8Signal[Local_DAC_Counter],Local_DAC_BitCounter)
				);
			}
		Delay_us(175);
	}
}


/**********************************************************************************************************************
 *  END OF FILE: R2RDAC_program.c
 *********************************************************************************************************************/
