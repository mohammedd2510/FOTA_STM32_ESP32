/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SHIFTREG_program.c
 *        Author: Mohamed Osama
 *		   Date:  Apr 18, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "HAL\SHIFT_REG_16BIT\SHIFTREG_interface.h"
#include "HAL\SHIFT_REG_16BIT\SHIFTREG_private.h"

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
static void SHIFTREG_voidPinInit(port_index_t port_index, pin_index_t pin_index)
{
	switch (port_index) {
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
		  GPIO_voidSetPinMode(port_index,pin_index,GPIO_OUTPUT_PIN_MODE);
		  GPIO_voidSetPinOutputMode(port_index,pin_index,GPIO_OUTPUT_PIN_PUSH_PULL);
		  GPIO_voidSetPinOutputSpeed(port_index,pin_index,GPIO_OUTPUT_PIN_LOW_SPEED);
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void SHIFTREG_voidInit(SHIFTREG_t *ptrSHIFTREG)
{
		SHIFTREG_voidPinInit(ptrSHIFTREG->ShiftReg_DataSerial_Port,ptrSHIFTREG->ShiftReg_DataSerial_Pin);
		SHIFTREG_voidPinInit(ptrSHIFTREG->ShiftReg_StorageClk_Port,ptrSHIFTREG->ShiftReg_StorageClk_Pin);
		SHIFTREG_voidPinInit(ptrSHIFTREG->ShiftReg_ShiftClk_Port,ptrSHIFTREG->ShiftReg_ShiftClk_Pin);
}

void SHIFTREG_voidSetBufferData(SHIFTREG_t *ptrSHIFTREG,u16 Copy_u16BufferData){
	ptrSHIFTREG->ShiftReg_Data = Copy_u16BufferData;
}

void SHIFTREG_voidClearBuffer(SHIFTREG_t *ptrSHIFTREG)
{
	ptrSHIFTREG->ShiftReg_Data = 0;

}
void SHIFTREG_voidLatchData(SHIFTREG_t *ptrSHIFTREG)
{
	u8 Local_u8Counter = 0;
	for(Local_u8Counter=0;Local_u8Counter<16;Local_u8Counter++)
	{
		GPIO_voidSetPinValue(ptrSHIFTREG->ShiftReg_DataSerial_Port,ptrSHIFTREG->ShiftReg_DataSerial_Pin,GET_BIT(ptrSHIFTREG->ShiftReg_Data,(15-Local_u8Counter)));

		GPIO_voidSetPinValue(ptrSHIFTREG->ShiftReg_ShiftClk_Port,ptrSHIFTREG->ShiftReg_ShiftClk_Pin,GPIO_HIGH);
		GPIO_voidSetPinValue(ptrSHIFTREG->ShiftReg_ShiftClk_Port,ptrSHIFTREG->ShiftReg_ShiftClk_Pin,GPIO_LOW);
	}
	GPIO_voidSetPinValue(ptrSHIFTREG->ShiftReg_StorageClk_Port,ptrSHIFTREG->ShiftReg_StorageClk_Pin,GPIO_HIGH);
	GPIO_voidSetPinValue(ptrSHIFTREG->ShiftReg_StorageClk_Port,ptrSHIFTREG->ShiftReg_StorageClk_Pin,GPIO_LOW);
}

/**********************************************************************************************************************
 *  END OF FILE: SHIFTREG_program.c
 *********************************************************************************************************************/
