/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TIM_private.h
 *        Author: Mohamed Osama
 *		   Date:  May 20, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef TIM_TIM_PRIVATE_H_
#define TIM_TIM_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/NVIC/NVIC_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define TIM1_BASE_ADDRESS	0x40010000

#define TIM2_BASE_ADDRESS	0x40000000
#define TIM3_BASE_ADDRESS	0x40000400
#define TIM4_BASE_ADDRESS	0x40000800
#define TIM5_BASE_ADDRESS	0x40000C00

#define TIM9_BASE_ADDRESS   0x40014000
#define TIM10_BASE_ADDRESS  0x40014400
#define TIM11_BASE_ADDRESS  0x40014800

#define TIM1 ((volatile TIM_t*)(TIM1_BASE_ADDRESS))
#define TIM2 ((volatile TIM_t*)(TIM2_BASE_ADDRESS))
#define TIM3 ((volatile TIM_t*)(TIM3_BASE_ADDRESS))
#define TIM4 ((volatile TIM_t*)(TIM4_BASE_ADDRESS))
#define TIM5 ((volatile TIM_t*)(TIM5_BASE_ADDRESS))
#define TIM9 ((volatile TIM_t*)(TIM9_BASE_ADDRESS))
#define TIM10 ((volatile TIM_t*)(TIM10_BASE_ADDRESS))
#define TIM11 ((volatile TIM_t*)(TIM11_BASE_ADDRESS))


#define TIM_UIE  (1<<0)
#define TIM_CC1IE (1<<1)
#define TIM_CEN_BIT_POS  0
#define TIM_DIR_BIT_POS  4
#define TIM_ARPE_BIT_POS 7
#define TIM_URS_BIT_POS  2
#define TIM_UG_BIT_POS   0

#define TIM_PWM_MODE_ENABLE   120
#define TIM_IC_MODE 1

#define TIM_OUTPUT_MODE_ENABLE 3
#define TIM_OC_PIN_ENABLE    ((1<<15)|(1<<11)|(1<<10))

#define TIM_IC_RISING_EDGE_ENABLE (1<<0)
#define TIM_IC_FALLING_EDGE_ENABLE (3)
#define TIM_IC_BOTH_EDGES_ENABLE   (11)

#define TIM_SINGLE_INTERVAL_MODE   1
#define TIM_PERIODIC_INTERVAL_MODE 0

#define TIM_UIF_BIT_POS 0
#define TIM_UIE_BIT_POS 0
#define TIM_CC1IF_BIT_POS 1

#define TIMERS_NUM 8
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
 TIM1_CALLBACK,
 TIM2_CALLBACK,
 TIM3_CALLBACK,
 TIM4_CALLBACK,
 TIM5_CALLBACK,
 TIM9_CALLBACK,
 TIM10_CALLBACK,
 TIM11_CALLBACK
}TIM_CALLBACK_t;



typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR1;
	volatile u32 CCMR2;
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 RCR;
	volatile u32 CCR1;
	volatile u32 CCR2;
	volatile u32 CCR3;
	volatile u32 CCR4;
	volatile u32 BDTR;
	volatile u32 DCR;
	volatile u32 DMAR;
}TIM_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif /* TIM_TIM_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: TIM_private.h
 *********************************************************************************************************************/

