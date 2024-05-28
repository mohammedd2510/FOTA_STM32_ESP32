/*********************************************
 * Author:				      Mohamed Osama
 * Creation Data:	  	  29 Feb, 2024
 * Version:				      v1.0
 * Compiler:			      GNU ARM-GCC
 * Controller:			    STM32F401CCU6
 * Layer:				        MCAL
 ********************************************/
/*********************************************
 * Version	    Date			       Author            Description
 *  v1.0	    29 Feb, 2024	   Mohamed Osama      Initial Creation
 *********************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

// Library Inclusion
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

// Macros Definitions
#define GPIO_INPUT_PORT_MODE 0x00
#define GPIO_OUTPUT_PORT_MODE 0x55555555
#define GPIO_ALTERNATE_FUNCTION_PORT_MODE 0xAAAAAAAA
#define GPIO_ANALOG_PORT_MODE 0XFFFFFFFF

#define GPIO_OUTPUT_PORT_PUSH_PULL 0X00
#define GPIO_OUTPUT_PORT_OPEN_DRAIN 0XFFFF

#define GPIO_OUTPUT_PORT_LOW_SPEED 0x00
#define GPIO_OUTPUT_PORT_MEDIUM_SPEED 0x55555555
#define GPIO_OUTPUT_PORT_HIGH_SPEED 0xAAAAAAAA
#define GPIO_OUTPUT_PORT_VERY_HIGH_SPEED 0XFFFFFFFF

#define GPIO_INPUT_PORT_FLOAT 0x00
#define GPIO_INPUT_PORT_PULL_UP 0x55555555
#define GPIO_INPUT_PORT_PULL_DOWN 0XFFFFFFFF

// Enums Definitions
typedef enum {
  GPIO_PIN0 = 0,
  GPIO_PIN1,
  GPIO_PIN2,
  GPIO_PIN3,
  GPIO_PIN4,
  GPIO_PIN5,
  GPIO_PIN6,
  GPIO_PIN7,
  GPIO_PIN8,
  GPIO_PIN9,
  GPIO_PIN10,
  GPIO_PIN11,
  GPIO_PIN12,
  GPIO_PIN13,
  GPIO_PIN14,
  GPIO_PIN15,
} pin_index_t;

typedef enum {
  GPIO_PORTA = 0,
  GPIO_PORTB,
  GPIO_PORTC,
} port_index_t;

typedef enum {
  GPIO_INPUT_PIN_MODE = 0,
  GPIO_OUTPUT_PIN_MODE,
  GPIO_ALTERNATE_FUNCTION_PIN_MODE,
  GPIO_ANALOG_PIN_MODE
} gpio_pin_mode_t;

typedef enum {
  GPIO_OUTPUT_PIN_PUSH_PULL = 0,
  GPIO_OUTPUT_PIN_OPEN_DRAIN,
} output_pin_mode_t;

typedef enum {
  GPIO_OUTPUT_PIN_LOW_SPEED = 0,
  GPIO_OUTPUT_PIN_MEDIUM_SPEED,
  GPIO_OUTPUT_PIN_HIGH_SPEED,
  GPIO_OUTPUT_PIN_VERY_HIGH_SPEED
} output_pin_speed_mode_t;

typedef enum {
  GPIO_INPUT_PIN_FLOAT = 0,
  GPIO_INPUT_PIN_PULL_UP,
  GPIO_INPUT_PIN_PULL_DOWN
} input_pin_mode_t;

typedef enum { GPIO_LOW = 0, GPIO_HIGH } gpio_logic_t;

// Software Interfaces
void GPIO_voidSetPinMode(port_index_t Copy_PortIndex, pin_index_t Copy_PinIndex,
                         gpio_pin_mode_t Copy_GPIOPinMode);
void GPIO_voidSetPinOutputMode(port_index_t Copy_PortIndex,
                               pin_index_t Copy_PinIndex,
                               output_pin_mode_t Copy_OutputPinMode);
void GPIO_voidSetPinOutputSpeed(port_index_t Copy_PortIndex,
                                pin_index_t Copy_PinIndex,
                                output_pin_speed_mode_t Copy_OutputPinSpeed);
void GPIO_voidSetPinValue(port_index_t Copy_PortIndex,
                          pin_index_t Copy_PinIndex,
                          gpio_logic_t Copy_GPIOLogic);
void GPIO_voidSetPinPullUpDownResistor(port_index_t Copy_PortIndex,
                                       pin_index_t Copy_PinIndex,
                                       input_pin_mode_t Copy_InputPinMode);
u8 GPIO_u8GetPinValue(port_index_t Copy_PortIndex, pin_index_t Copy_PinIndex);

void GPIO_voidLockPin(port_index_t Copy_PortIndex, pin_index_t Copy_PinIndex);

void GPIO_voidSetPinAlternateFunction(port_index_t Copy_PortIndex, pin_index_t Copy_PinIndex, u8 Copy_u8AlternateFunction);

void GPIO_voidSetPortMode(port_index_t Copy_PortIndex, u32 Copy_u32GPIOPortMode);
void GPIO_voidSetPortOutputMode(port_index_t Copy_PortIndex,
                                u32 Copy_u32OutputPortMode);
void GPIO_voidSetPortOutputSpeed(port_index_t Copy_PortIndex,
                                 u32 Copy_u32OutputPortSpeed);
void GPIO_voidSetPortValue(port_index_t Copy_PortIndex, gpio_logic_t GPIOLogic);
void GPIO_voidSetPortPullUpDownResistor(port_index_t Copy_PortIndex,
                                        u32 Copy_u32InputPortMode);
u32 GPIO_u32GetPortValue(port_index_t Copy_PortIndex);

void GPIO_voidLockPort(port_index_t Copy_PortIndex);

#endif
