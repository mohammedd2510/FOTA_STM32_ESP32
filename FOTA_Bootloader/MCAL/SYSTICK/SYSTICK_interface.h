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

#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

// Library Inclusion
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

// Macros Definitions


// Software Interfaces
void MSysTick_voidInit(void);

void MSysTick_voidDeInit(void);

void MSysTick_voidSetBusyWait(u32 Copy_u32Ticks);

void MSysTick_voidSetIntervalSingle(u32 Copy_u32Ticks,PtrFunction CallBack_Ptr);

void MSysTick_voidSetIntervalPeriodic(u32 Copy_u32Ticks,PtrFunction CallBack_Ptr);

u32 MSysTick_u32GetElapsedTicks(void);

u32 MSysTick_u32GetElapsedTime_us(void);

u32 MSysTick_u32GetRemainingTicks(void);

void MSystick_Delay_ms(u32 time_ms);

void MSystick_Delay_us(u32 time_us);

void MSysTick_void_ASYNC_Delay_ms(u32 time_ms,PtrFunction CallBack_Ptr);

void MSystick_voidResetTimer(void);

void MSystick_voidSetPreloadvalue(u32 Copy_u32Ticks);

#endif
