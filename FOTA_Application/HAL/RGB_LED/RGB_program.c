/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  RGB_program.c
 *        Author: Mohamed Osama
 *		   Date:  Mar 31, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "RGB_interface.h"
#include "RGB_private.h"

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
static void RGB_init_led(port_index_t RGB_LedPort, pin_index_t RGB_LedPin)
{
	switch (RGB_LedPort) {
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
	  GPIO_voidSetPinMode(RGB_LedPort,RGB_LedPin,GPIO_OUTPUT_PIN_MODE);
	  GPIO_voidSetPinOutputMode(RGB_LedPort,RGB_LedPin,GPIO_OUTPUT_PIN_PUSH_PULL);
	  GPIO_voidSetPinOutputSpeed(RGB_LedPort,RGB_LedPin,GPIO_OUTPUT_PIN_LOW_SPEED);
	  GPIO_voidSetPinValue(RGB_LedPort,RGB_LedPin,GPIO_HIGH);
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void RGB_voidInit(RGB_Config_t* REF_RGBObj)
{
	RGB_init_led(REF_RGBObj->RGB_Red_Port, REF_RGBObj->RGB_Red_Pin);
	RGB_init_led(REF_RGBObj->RGB_Green_Port, REF_RGBObj->RGB_Green_Pin);
	RGB_init_led(REF_RGBObj->RGB_Blue_Port, REF_RGBObj->RGB_Blue_Pin);
}
void RGB_voidSetColor(RGB_Config_t* REF_RGBObj, u8 RGB_color)
{
	GPIO_voidSetPinValue(REF_RGBObj->RGB_Red_Port, REF_RGBObj->RGB_Red_Pin, !(RGB_color>>2 & 0x01));
	REF_RGBObj->RGB_Red_State = !(RGB_color>>2 & 0x01);
	GPIO_voidSetPinValue(REF_RGBObj->RGB_Green_Port, REF_RGBObj->RGB_Green_Pin, !(RGB_color>>1 & 0x01));
	REF_RGBObj->RGB_Green_State = !(RGB_color>>1 & 0x01);
	GPIO_voidSetPinValue(REF_RGBObj->RGB_Blue_Port, REF_RGBObj->RGB_Blue_Pin, !(RGB_color>>0 & 0x01));
	REF_RGBObj->RGB_Blue_State = !(RGB_color>>0 & 0x01);
}
void RGB_voidLedOn(RGB_Config_t* REF_RGBObj , RGB_Leds_t RGP_Led)
{
	switch(RGP_Led)
	{
	case RGB_RED_LED:
		GPIO_voidSetPinValue(REF_RGBObj->RGB_Red_Port, REF_RGBObj->RGB_Red_Pin, RGB_LED_ON);
		REF_RGBObj->RGB_Red_State = RGB_LED_ON;
		break;
	case RGB_GREEN_LED:
		GPIO_voidSetPinValue(REF_RGBObj->RGB_Green_Port, REF_RGBObj->RGB_Green_Pin, RGB_LED_ON);
		REF_RGBObj->RGB_Green_State = RGB_LED_ON;
		break;
	case RGB_BLUE_LED:
		GPIO_voidSetPinValue(REF_RGBObj->RGB_Blue_Port, REF_RGBObj->RGB_Blue_Pin, RGB_LED_ON);
		REF_RGBObj->RGB_Blue_State = RGB_LED_ON;
		break;
	}
}
void RGB_voidLedOff( RGB_Config_t* REF_RGBObj , RGB_Leds_t RGP_Led)
{
	switch(RGP_Led)
		{
		case RGB_RED_LED:
			GPIO_voidSetPinValue(REF_RGBObj->RGB_Red_Port, REF_RGBObj->RGB_Red_Pin, RGB_LED_OFF);
			REF_RGBObj->RGB_Red_State = RGB_LED_OFF;
			break;
		case RGB_GREEN_LED:
			GPIO_voidSetPinValue(REF_RGBObj->RGB_Green_Port, REF_RGBObj->RGB_Green_Pin, RGB_LED_OFF);
			REF_RGBObj->RGB_Green_State = RGB_LED_OFF;
			break;
		case RGB_BLUE_LED:
			GPIO_voidSetPinValue(REF_RGBObj->RGB_Blue_Port, REF_RGBObj->RGB_Blue_Pin, RGB_LED_OFF);
			REF_RGBObj->RGB_Blue_State = RGB_LED_OFF;
			break;
		}
}
void RGB_voidLedToggle(RGB_Config_t* REF_RGBObj , RGB_Leds_t RGP_Led)
{
	switch(RGP_Led)
			{
			case RGB_RED_LED:
				if(REF_RGBObj->RGB_Red_State == RGB_LED_ON)
				{
					GPIO_voidSetPinValue(REF_RGBObj->RGB_Red_Port, REF_RGBObj->RGB_Red_Pin, RGB_LED_OFF);
					REF_RGBObj->RGB_Red_State = RGB_LED_OFF;
				}
				else if (REF_RGBObj->RGB_Red_State == RGB_LED_OFF)
				{
					GPIO_voidSetPinValue(REF_RGBObj->RGB_Red_Port, REF_RGBObj->RGB_Red_Pin, RGB_LED_ON);
					REF_RGBObj->RGB_Red_State = RGB_LED_ON;
				}
				break;
			case RGB_GREEN_LED:
				if(REF_RGBObj->RGB_Green_State == RGB_LED_ON)
				{
					GPIO_voidSetPinValue(REF_RGBObj->RGB_Green_Port, REF_RGBObj->RGB_Green_Pin, RGB_LED_OFF);
					REF_RGBObj->RGB_Green_State = RGB_LED_OFF;
				}
				else if (REF_RGBObj->RGB_Green_State == RGB_LED_OFF)
				{
					GPIO_voidSetPinValue(REF_RGBObj->RGB_Green_Port, REF_RGBObj->RGB_Green_Pin, RGB_LED_ON);
					REF_RGBObj->RGB_Green_State = RGB_LED_ON;
				}
				break;
			case RGB_BLUE_LED:
				if(REF_RGBObj->RGB_Blue_State == RGB_LED_ON)
				{
					GPIO_voidSetPinValue(REF_RGBObj->RGB_Blue_Port, REF_RGBObj->RGB_Blue_Pin, RGB_LED_OFF);
					REF_RGBObj->RGB_Blue_State = RGB_LED_OFF;
				}
				else if (REF_RGBObj->RGB_Blue_State == RGB_LED_OFF)
				{
					GPIO_voidSetPinValue(REF_RGBObj->RGB_Blue_Port, REF_RGBObj->RGB_Blue_Pin, RGB_LED_ON);
					REF_RGBObj->RGB_Blue_State = RGB_LED_ON;
				}
				break;
			}
}
/**********************************************************************************************************************
 *  END OF FILE: RGB_program.c
 *********************************************************************************************************************/
