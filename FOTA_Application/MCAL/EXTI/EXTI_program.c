/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  EXTI_program.c
 *        Author: Mohamed Osama
 *		   Date:  Mar 29, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EXTI_private.h"
#include "EXTI_interface.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static void (*EXTI_pNotificationFunction[16])(void) = {NULL};


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void MEXTI_voidInit(MEXTI_CONFIG_t* Copy_tEXTIConfig ,void (*pCallBackFunction)(void)){

	/*Enable EXTI Line mode interrupt or event*/
	switch(Copy_tEXTIConfig->MEXTI_Mode)
	{
		case MEXTI_INTERRUPT_MODE:
			SET_BIT(EXTI->IMR,Copy_tEXTIConfig->MEXTI_Line);
			break;
		case MEXTI_EVENT_MODE:
			SET_BIT(EXTI->EMR,Copy_tEXTIConfig->MEXTI_Line);
			break;
		default:
			break;
	}

	/*Set Notification function*/
	EXTI_pNotificationFunction[Copy_tEXTIConfig->MEXTI_Line] = pCallBackFunction;

	/*Set Sense Signal mode RISING, FALLING, ONCHANGE */
	switch(Copy_tEXTIConfig->MEXTI_SenseSignal){
		case MEXTI_RISING_EDGE:
			SET_BIT(EXTI->RTSR,Copy_tEXTIConfig->MEXTI_Line);
			CLR_BIT(EXTI->FTSR,Copy_tEXTIConfig->MEXTI_Line);
			break;
		case MEXTI_FALLING_EDGE:
			SET_BIT(EXTI->FTSR,Copy_tEXTIConfig->MEXTI_Line);
			CLR_BIT(EXTI->RTSR,Copy_tEXTIConfig->MEXTI_Line);
			break;
		case MEXTI_ONCHANGE:
			SET_BIT(EXTI->RTSR,Copy_tEXTIConfig->MEXTI_Line);
			SET_BIT(EXTI->FTSR,Copy_tEXTIConfig->MEXTI_Line);
			break;
		default:
			break;
	}
	/* Enable SYSCFG Peripheral Clock*/
	RCC_voidEnablePeripheralClock(RCC_APB2, RCC_APB2_SYSCFGEN);
	/*Set EXTI Port PORTA, PORTB, PORTC*/
	if(Copy_tEXTIConfig->MEXTI_Line < 4 && Copy_tEXTIConfig->MEXTI_Line >= 0)
	{
		SYSCFG_EXTICR1 |= (Copy_tEXTIConfig->MEXTI_Port << (Copy_tEXTIConfig->MEXTI_Line*4));

	}
	else if(Copy_tEXTIConfig->MEXTI_Line < 8 && Copy_tEXTIConfig->MEXTI_Line >= 4){
		SYSCFG_EXTICR2 |= (Copy_tEXTIConfig->MEXTI_Port << (Copy_tEXTIConfig->MEXTI_Line*4));
	}
	else if(Copy_tEXTIConfig->MEXTI_Line < 12 && Copy_tEXTIConfig->MEXTI_Line >= 8){
		SYSCFG_EXTICR3 |= (Copy_tEXTIConfig->MEXTI_Port << (Copy_tEXTIConfig->MEXTI_Line*4));
	}
	else if(Copy_tEXTIConfig->MEXTI_Line < 16 && Copy_tEXTIConfig->MEXTI_Line >= 12){
		SYSCFG_EXTICR4 |= (Copy_tEXTIConfig->MEXTI_Port << (Copy_tEXTIConfig->MEXTI_Line*4));
	}

	/*Enable NVIC Mask for EXTI Line*/
	if(Copy_tEXTIConfig->MEXTI_Line <5){
		MNVIC_voidEnableIRQ(EXTI0_IRQn+Copy_tEXTIConfig->MEXTI_Line);
	}
	else if(Copy_tEXTIConfig->MEXTI_Line >= 5 && Copy_tEXTIConfig->MEXTI_Line <= 9){
		MNVIC_voidEnableIRQ(EXTI9_5_IRQn);
	}
	else if(Copy_tEXTIConfig->MEXTI_Line >= 10 && Copy_tEXTIConfig->MEXTI_Line <= 15){
		MNVIC_voidEnableIRQ(EXTI15_10_IRQn);
	}
}
void MEXTI_voidEnableInterrupt(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine){
    SET_BIT(EXTI->IMR,Copy_tInterruptLine);
}
void MEXTI_voidDisableInterrupt(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine){
    CLR_BIT(EXTI->IMR,Copy_tInterruptLine);
}


void MEXTI_voidChangeSenseMode(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine, MEXTI_INTERRUPT_SENSE_SIGNAL_t Copy_tSenseSignal){
    switch(Copy_tSenseSignal){
        case MEXTI_RISING_EDGE:
            SET_BIT(EXTI->RTSR,Copy_tInterruptLine);
            CLR_BIT(EXTI->FTSR,Copy_tInterruptLine);
            break;
        case MEXTI_FALLING_EDGE:
            SET_BIT(EXTI->FTSR,Copy_tInterruptLine);
            CLR_BIT(EXTI->RTSR,Copy_tInterruptLine);
            break;
        case MEXTI_ONCHANGE:
            SET_BIT(EXTI->RTSR,Copy_tInterruptLine);
            SET_BIT(EXTI->FTSR,Copy_tInterruptLine);
            break;
        default:
            break;
    }
}

void MEXTI_voidSetCallBack(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine, void (*pCallBackFunction)(void)){
    EXTI_pNotificationFunction[Copy_tInterruptLine] = pCallBackFunction;
}

void MEXTI_voidClearPendingFlag(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine){
	SET_BIT(EXTI->PR,Copy_tInterruptLine);
}

u8 MEXTI_u8GetPendingFlag(MEXTI_INTERRUPT_LINE_t Copy_tInterruptLine)
{
	return GET_BIT(EXTI->PR,Copy_tInterruptLine);
}


/*********************************************EXTI0_15_IRQHandlers******************************/
void EXTI0_IRQHandler(void){
    if(EXTI_pNotificationFunction[0] != NULL){
        EXTI_pNotificationFunction[0]();
    }
    MEXTI_voidClearPendingFlag(MEXTI_EXTI0);
}

void EXTI1_IRQHandler(void){
    if(EXTI_pNotificationFunction[1] != NULL){
        EXTI_pNotificationFunction[1]();
    }
    MEXTI_voidClearPendingFlag(MEXTI_EXTI1);
}

void EXTI2_IRQHandler(void){
    if(EXTI_pNotificationFunction[2] != NULL){
        EXTI_pNotificationFunction[2]();
    }
    MEXTI_voidClearPendingFlag(MEXTI_EXTI2);
}

void EXTI3_IRQHandler(void){
    if(EXTI_pNotificationFunction[3] != NULL){
        EXTI_pNotificationFunction[3]();
    }
    MEXTI_voidClearPendingFlag(MEXTI_EXTI3);
}

void EXTI4_IRQHandler(void){
    if(EXTI_pNotificationFunction[4] != NULL){
        EXTI_pNotificationFunction[4]();
    }
    MEXTI_voidClearPendingFlag(MEXTI_EXTI4);
}

void EXTI9_5_IRQHandler(void)
{
	if(MEXTI_u8GetPendingFlag(MEXTI_EXTI5))
	{
		if(EXTI_pNotificationFunction[5] != NULL){
			EXTI_pNotificationFunction[5]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_EXTI5);
	}
	else if(MEXTI_u8GetPendingFlag(MEXTI_EXTI6))
	{
		if(EXTI_pNotificationFunction[6] != NULL){
			EXTI_pNotificationFunction[6]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_EXTI6);
	}
	else if(MEXTI_u8GetPendingFlag(MEXTI_EXTI7))
	{
		if(EXTI_pNotificationFunction[7] != NULL){
			EXTI_pNotificationFunction[7]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_EXTI7);
	}
	else if (MEXTI_u8GetPendingFlag(MEXTI_EXTI8))
	{
		if(EXTI_pNotificationFunction[8] != NULL){
			EXTI_pNotificationFunction[8]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_EXTI8);
	}
	else if (MEXTI_u8GetPendingFlag(MEXTI_EXTI9))
	{
		if(EXTI_pNotificationFunction[9] != NULL){
			EXTI_pNotificationFunction[9]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_EXTI9);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if(MEXTI_u8GetPendingFlag(MEXTI_EXTI10))
	{
		if(EXTI_pNotificationFunction[10] != NULL){
			EXTI_pNotificationFunction[10]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_EXTI10);
	}
	else if(MEXTI_u8GetPendingFlag(MEXTI_EXTI11))
	{
		if(EXTI_pNotificationFunction[11] != NULL){
			EXTI_pNotificationFunction[11]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_EXTI11);
	}
	else if(MEXTI_u8GetPendingFlag(MEXTI_EXTI12))
	{
		if(EXTI_pNotificationFunction[12] != NULL){
			EXTI_pNotificationFunction[12]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_EXTI12);
	}
	else if (MEXTI_u8GetPendingFlag(MEXTI_EXTI13))
	{
		if(EXTI_pNotificationFunction[13] != NULL){
			EXTI_pNotificationFunction[13]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_EXTI13);
	}
	else if (MEXTI_u8GetPendingFlag(MEXTI_EXTI14))
	{
		if(EXTI_pNotificationFunction[14] != NULL){
			EXTI_pNotificationFunction[14]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_EXTI14);
	}
	else if (MEXTI_u8GetPendingFlag(MEXTI_EXTI15))
	{
		if(EXTI_pNotificationFunction[15] != NULL){
			EXTI_pNotificationFunction[15]();
		}
		MEXTI_voidClearPendingFlag(MEXTI_EXTI15);
	}
}

/**********************************************************************************************************************
 *  END OF FILE: EXTI_program.c
 *********************************************************************************************************************/
