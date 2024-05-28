/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  RGB_interface.h
 *        Author: Mohamed Osama
 *		   Date:  Mar 31, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef HAL_RGB_LED_RGB_INTERFACE_H_
#define HAL_RGB_LED_RGB_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/RCC/RCC_interface.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define RGB_BLACK_COLOR    0b000
#define RGB_RED_COLOR 	   0b100
#define RGB_GREEN_COLOR    0b010
#define RGB_BLUE_COLOR     0b001
#define RGB_YELLOW_COLOR   0b110
#define RGB_WHITE_COLOR    0b111
#define RGB_PURPLE_COLOR   0b101
#define RGB_CYAN_COLOR     0b011

#define RGB_LED_ON	0x00
#define RGB_LED_OFF 0X01

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
	RGB_RED_LED,
	RGB_GREEN_LED,
	RGB_BLUE_LED,
}RGB_Leds_t;
typedef struct
{
	pin_index_t  RGB_Red_Pin;
	port_index_t RGB_Red_Port;
	gpio_logic_t RGB_Red_State;
	pin_index_t  RGB_Green_Pin;
	port_index_t RGB_Green_Port;
	gpio_logic_t RGB_Green_State;
	pin_index_t  RGB_Blue_Pin;
	port_index_t RGB_Blue_Port;
	gpio_logic_t RGB_Blue_State;
}RGB_Config_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void RGB_voidInit(RGB_Config_t* REF_RGBObj);
void RGB_voidSetColor(RGB_Config_t* REF_RGBObj, u8 RGB_color);
void RGB_voidLedOn(RGB_Config_t* REF_RGBObj , RGB_Leds_t RGP_Led);
void RGB_voidLedOff(RGB_Config_t* REF_RGBObj , RGB_Leds_t RGP_Led);
void RGB_voidLedToggle(RGB_Config_t* REF_RGBObj , RGB_Leds_t RGP_Led);
 
#endif /* HAL_RGB_LED_RGB_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: RGB_interface.h
 *********************************************************************************************************************/

