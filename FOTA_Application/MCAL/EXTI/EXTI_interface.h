/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  EXTI_interface.h
 *        Author: Mohamed Osama
 *		   Date:  Mar 29, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum {
	MEXTI_INTERRUPT_MODE = 0,
	MEXTI_EVENT_MODE
} MEXTT_MODE_t;

typedef enum{
	MEXTI_PORTA = 0,
	MEXTI_PORTB,
	MEXTI_PORTC,
}MEXTI_PORT_t; ;

typedef enum {
	MEXTI_EXTI0 = 0,
    MEXTI_EXTI1,
    MEXTI_EXTI2,
    MEXTI_EXTI3,
    MEXTI_EXTI4,
    MEXTI_EXTI5,
    MEXTI_EXTI6,
    MEXTI_EXTI7,
    MEXTI_EXTI8,
    MEXTI_EXTI9,
    MEXTI_EXTI10,
    MEXTI_EXTI11,
    MEXTI_EXTI12,
    MEXTI_EXTI13,
    MEXTI_EXTI14,
    MEXTI_EXTI15
} MEXTI_INTERRUPT_LINE_t;

typedef enum {
    MEXTI_RISING_EDGE = 0,
    MEXTI_FALLING_EDGE,
    MEXTI_ONCHANGE
}MEXTI_INTERRUPT_SENSE_SIGNAL_t;

typedef struct{
	MEXTI_PORT_t MEXTI_Port;
	MEXTI_INTERRUPT_LINE_t MEXTI_Line;
	MEXTI_INTERRUPT_SENSE_SIGNAL_t MEXTI_SenseSignal;
	MEXTT_MODE_t MEXTI_Mode;
}MEXTI_CONFIG_t;
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void MEXTI_voidInit(MEXTI_CONFIG_t* Copy_tEXTIConfig ,void (*pCallBackFunction)(void));
void MEXTI_voidEnableInterrupt(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine);
void MEXTI_voidDisableInterrupt(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine);
void MEXTI_voidChangeSenseMode(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine, MEXTI_INTERRUPT_SENSE_SIGNAL_t Copy_tSenseSignal);
void MEXTI_voidSetCallBack(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine, void (*pCallBackFunction)(void));
void MEXTI_voidClearPendingFlag(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine);
void MEXTI_voidGetPendingFlag(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine);

#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: EXTI_interface.h
 *********************************************************************************************************************/

