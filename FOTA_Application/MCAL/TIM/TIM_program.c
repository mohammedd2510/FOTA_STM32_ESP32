/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TIM_program.c
 *        Author: Mohamed Osama
 *		   Date:  May 20, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TIM_interface.h"
#include "TIM_private.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static pCallBackNotification TIMx_UP_INT_Callback[TIMERS_NUM];
static pCallBackNotification TIMx_CC_INT_Callback[TIMERS_NUM];

static u8 TIM_SingleInterval_FLAG[TIMERS_NUM];
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static void TIM_RCC_ENABLE(volatile TIM_t* TIM_Instance);
static void TIM_GPIO_INIT(volatile TIM_t* TIM_Instance);
static void TIM_Update_INT_Init(const TIM_Config_t* TIM_Config);
static void TIM_Capture_Compare_INT_Init(const TIM_Config_t* TIM_Config);
static void TIM_PWM_INIT(const TIM_Config_t* TIM_Config);
static void TIM_IC_INIT(const TIM_Config_t* TIM_Config);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
static void TIM_RCC_ENABLE(volatile TIM_t* TIM_Instance)
{
	if(TIM_Instance == TIM1)
	{
		RCC_voidEnablePeripheralClock(RCC_APB2, RCC_APB2_TIM1EN);
	}
	else if(TIM_Instance == TIM2)
	{
		RCC_voidEnablePeripheralClock(RCC_APB1, RCC_APB1_TIM2EN);
	}
	else if(TIM_Instance == TIM3)
	{
		RCC_voidEnablePeripheralClock(RCC_APB1, RCC_APB1_TIM3EN);
	}
	else if(TIM_Instance == TIM4)
	{
		RCC_voidEnablePeripheralClock(RCC_APB1, RCC_APB1_TIM4EN);
	}
	else if(TIM_Instance == TIM5)
	{
		RCC_voidEnablePeripheralClock(RCC_APB1, RCC_APB1_TIM5EN);
	}
	else if(TIM_Instance == TIM9)
	{
		RCC_voidEnablePeripheralClock(RCC_APB2, RCC_APB2_TIM9EN);
	}
	else if(TIM_Instance == TIM10)
	{
		RCC_voidEnablePeripheralClock(RCC_APB2, RCC_APB2_TIM10EN);
	}
	else if(TIM_Instance == TIM11)
	{
		RCC_voidEnablePeripheralClock(RCC_APB2, RCC_APB2_TIM11EN);
	}
}
static void TIM_GPIO_INIT(volatile TIM_t* TIM_Instance)
{
	RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOAEN);
	RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOBEN);
	if(TIM_Instance == TIM1)
	{
		GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN8, GPIO_ALTERNATE_FUNCTION_PIN_MODE);
		GPIO_voidSetPinAlternateFunction(GPIO_PORTA, GPIO_PIN8, 1);
	}
	else if(TIM_Instance == TIM2)
	{
		GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN5, GPIO_ALTERNATE_FUNCTION_PIN_MODE);
		GPIO_voidSetPinAlternateFunction(GPIO_PORTA, GPIO_PIN5, 1);
	}
	else if(TIM_Instance == TIM3)
	{
		GPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN4, GPIO_ALTERNATE_FUNCTION_PIN_MODE);
		GPIO_voidSetPinAlternateFunction(GPIO_PORTB, GPIO_PIN4, 2);
	}
	else if(TIM_Instance == TIM4)
	{
		GPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN6, GPIO_ALTERNATE_FUNCTION_PIN_MODE);
		GPIO_voidSetPinAlternateFunction(GPIO_PORTB, GPIO_PIN6, 2);
	}
	else if(TIM_Instance == TIM5)
	{
		GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN0, GPIO_ALTERNATE_FUNCTION_PIN_MODE);
		GPIO_voidSetPinAlternateFunction(GPIO_PORTA, GPIO_PIN0, 2);
	}
	else if(TIM_Instance == TIM9)
	{
		GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN2, GPIO_ALTERNATE_FUNCTION_PIN_MODE);
		GPIO_voidSetPinAlternateFunction(GPIO_PORTA, GPIO_PIN2, 3);
	}
	else if(TIM_Instance == TIM10)
	{
		GPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN8, GPIO_ALTERNATE_FUNCTION_PIN_MODE);
		GPIO_voidSetPinAlternateFunction(GPIO_PORTB, GPIO_PIN8, 2);
	}
	else if(TIM_Instance == TIM11)
	{
		GPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN9, GPIO_ALTERNATE_FUNCTION_PIN_MODE);
		GPIO_voidSetPinAlternateFunction(GPIO_PORTB, GPIO_PIN9, 2);
	}
}
static void TIM_Update_INT_Init(const TIM_Config_t* TIM_Config)
{
	if(TIM_Config->TIM_Instance == TIM1)
	{
		MNVIC_voidEnableIRQ(TIM1_UP_TIM10_IRQn);
		TIMx_UP_INT_Callback[TIM1_CALLBACK] = TIM_Config->UP_Callback;
		TIM1->DIER |= TIM_UIE;
	}
	else if(TIM_Config->TIM_Instance == TIM2)
	{
		MNVIC_voidEnableIRQ(TIM2_IRQn);
		TIMx_UP_INT_Callback[TIM2_CALLBACK] = TIM_Config->UP_Callback;
		TIM2->DIER |= TIM_UIE;
	}
	else if(TIM_Config->TIM_Instance == TIM3)
	{
		MNVIC_voidEnableIRQ(TIM3_IRQn);
		TIMx_UP_INT_Callback[TIM3_CALLBACK] = TIM_Config->UP_Callback;
		TIM3->DIER |= TIM_UIE;
	}
	else if(TIM_Config->TIM_Instance == TIM4)
	{
		MNVIC_voidEnableIRQ(TIM4_IRQn);
		TIMx_UP_INT_Callback[TIM4_CALLBACK] = TIM_Config->UP_Callback;
		TIM4->DIER |= TIM_UIE;
	}
	else if(TIM_Config->TIM_Instance == TIM5)
	{
		MNVIC_voidEnableIRQ(TIM5_IRQn);
		TIMx_UP_INT_Callback[TIM5_CALLBACK] = TIM_Config->UP_Callback;
		TIM5->DIER |= TIM_UIE;
	}
	else if(TIM_Config->TIM_Instance == TIM9)
	{
		MNVIC_voidEnableIRQ(TIM1_BRK_TIM9_IRQn);
		TIMx_UP_INT_Callback[TIM9_CALLBACK] = TIM_Config->UP_Callback;
		TIM9->DIER |= TIM_UIE;
	}
	else if(TIM_Config->TIM_Instance == TIM10)
	{
		MNVIC_voidEnableIRQ(TIM1_UP_TIM10_IRQn);
		TIMx_UP_INT_Callback[TIM10_CALLBACK] = TIM_Config->UP_Callback;
		TIM10->DIER |= TIM_UIE;
	}
	else if(TIM_Config->TIM_Instance == TIM11)
	{
		MNVIC_voidEnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
		TIMx_UP_INT_Callback[TIM11_CALLBACK] = TIM_Config->UP_Callback;
		TIM11->DIER |= TIM_UIE;
	}

}
static void TIM_Capture_Compare_INT_Init(const TIM_Config_t* TIM_Config)
{
	if(TIM_Config->TIM_Instance == TIM1)
	{
		MNVIC_voidEnableIRQ(TIM1_CC_IRQn);
		TIMx_CC_INT_Callback[TIM1_CALLBACK] = TIM_Config->CC_Callback;
		TIM1->DIER |= TIM_CC1IE;
	}
	else if(TIM_Config->TIM_Instance == TIM2)
	{
		MNVIC_voidEnableIRQ(TIM2_IRQn);
		TIMx_CC_INT_Callback[TIM2_CALLBACK] = TIM_Config->CC_Callback;
		TIM2->DIER |= TIM_CC1IE;

	}
	else if(TIM_Config->TIM_Instance == TIM3)
	{
		MNVIC_voidEnableIRQ(TIM3_IRQn);
		TIMx_CC_INT_Callback[TIM3_CALLBACK] = TIM_Config->CC_Callback;
		TIM3->DIER |= TIM_CC1IE;
	}
	else if(TIM_Config->TIM_Instance == TIM4)
	{
		MNVIC_voidEnableIRQ(TIM4_IRQn);
		TIMx_CC_INT_Callback[TIM4_CALLBACK] = TIM_Config->CC_Callback;
		TIM4->DIER |= TIM_CC1IE;
	}
	else if(TIM_Config->TIM_Instance == TIM5)
	{
		MNVIC_voidEnableIRQ(TIM5_IRQn);
		TIMx_CC_INT_Callback[TIM5_CALLBACK] = TIM_Config->CC_Callback;
		TIM5->DIER |= TIM_CC1IE;
	}
	else if(TIM_Config->TIM_Instance == TIM9)
	{
		MNVIC_voidEnableIRQ(TIM1_BRK_TIM9_IRQn);
		TIMx_CC_INT_Callback[TIM9_CALLBACK] = TIM_Config->CC_Callback;
		TIM9->DIER |= TIM_CC1IE;
	}
	else if(TIM_Config->TIM_Instance == TIM10)
	{
		MNVIC_voidEnableIRQ(TIM1_UP_TIM10_IRQn);
		TIMx_CC_INT_Callback[TIM10_CALLBACK] = TIM_Config->CC_Callback;
		TIM10->DIER |= TIM_CC1IE;
	}
	else if(TIM_Config->TIM_Instance == TIM11)
	{
		MNVIC_voidEnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
		TIMx_CC_INT_Callback[TIM11_CALLBACK] = TIM_Config->CC_Callback;
		TIM11->DIER |= TIM_CC1IE;
	}
}
static void TIM_PWM_INIT(const TIM_Config_t* TIM_Config)
{
	TIM_Config->TIM_Instance->CCMR1 = TIM_PWM_MODE_ENABLE;
	TIM_Config->TIM_Instance->CCER = TIM_OUTPUT_MODE_ENABLE;
	if(TIM_Config->TIM_Instance == TIM1)
	{
		TIM_Config->TIM_Instance->BDTR = TIM_OC_PIN_ENABLE;
	}
	TIM_Config->TIM_Instance->CCR1 =(u32)(((TIM_Config->TIM_PWM_DutyCycle)/100.0)*TIM_Config->TIM_Preload);
}
static void TIM_IC_INIT(const TIM_Config_t* TIM_Config)
{
	TIM_Config->TIM_Instance->CCMR1 = TIM_IC_MODE;
	switch(TIM_Config->TIM_IC_Mode)
	{
	case TIM_IC_RISING_EDGE:
		TIM_Config->TIM_Instance->CCER= TIM_IC_RISING_EDGE_ENABLE;
		break;
	case TIM_IC_FALLING_EDGE:
		TIM_Config->TIM_Instance->CCER= TIM_IC_FALLING_EDGE_ENABLE;
		break;
	case TIM_IC_BOTH_EDGES:
		TIM_Config->TIM_Instance->CCER= TIM_IC_BOTH_EDGES_ENABLE;
		break;
	}
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void TIM_Init(const TIM_Config_t* TIM_Config)
{
	TIM_RCC_ENABLE(TIM_Config->TIM_Instance);
	CLR_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
	if(TIM_Config->TIM_Mode != TIM_NORMAL_MODE)
	{
		TIM_GPIO_INIT(TIM_Config->TIM_Instance);
	}
	if (TIM_Config->CAPTURE_COMPARE_INT_ENABLE == INTERRUPT_ENABLED)
	{
		TIM_Capture_Compare_INT_Init(TIM_Config);
	}
	TIM_Config->TIM_Instance->ARR = TIM_Config->TIM_Preload;
	TIM_Config->TIM_Instance->PSC = TIM_Config->TIM_Prescaler;
	TIM_Config->TIM_Instance->RCR = TIM_Config->TIM_RepetitionCounter;
	if(TIM_Config->TIM_Direction == TIM_UP_COUNTER)
	{
		CLR_BIT(TIM_Config->TIM_Instance->CR1,TIM_DIR_BIT_POS);
	}
	else
	{
		SET_BIT(TIM_Config->TIM_Instance->CR1,TIM_DIR_BIT_POS);
	}
	if(TIM_Config->TIM_Mode == TIM_PWM_MODE)
	{
		TIM_PWM_INIT(TIM_Config);
	}
	else if (TIM_Config->TIM_Mode == TIM_INPUT_CAPTURE_MODE)
	{
		TIM_IC_INIT(TIM_Config);
	}
	SET_BIT(TIM_Config->TIM_Instance->CR1,TIM_ARPE_BIT_POS);
	SET_BIT(TIM_Config->TIM_Instance->CR1,TIM_URS_BIT_POS);
	SET_BIT(TIM_Config->TIM_Instance->EGR,TIM_UG_BIT_POS);
	SET_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
}
void TIM_DeInit(const TIM_Config_t* TIM_Config)
{
	SET_BIT(TIM_Config->TIM_Instance->EGR,TIM_UG_BIT_POS);
	CLR_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
	TIM_Config->TIM_Instance->DIER &= ~TIM_UIE;
}
void TIM_Reset(const TIM_Config_t* TIM_Config)
{
	SET_BIT(TIM_Config->TIM_Instance->EGR,TIM_UG_BIT_POS);
}
u32 TIM_GetElapsedTime(const TIM_Config_t* TIM_Config)
{
	u32 ElapsedTime =0;
	if(TIM_Config->TIM_Direction ==TIM_UP_COUNTER)
	{
		ElapsedTime = TIM_Config->TIM_Instance->CNT;
	}
	else if(TIM_Config->TIM_Direction == TIM_DOWN_COUNTER){
		ElapsedTime = TIM_Config->TIM_Preload - TIM_Config->TIM_Instance->CNT;
	}
	return ElapsedTime;
}
void TIM_SingleInterval(TIM_Config_t* TIM_Config , u32 preload , pCallBackNotification callback)
{
	CLR_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
	TIM_Config->TIM_Instance->ARR = preload;
	SET_BIT(TIM_Config->TIM_Instance->EGR,TIM_UG_BIT_POS);
	TIM_Config->UP_Callback = callback;
	TIM_Update_INT_Init(TIM_Config);
	SET_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
	if(TIM_Config->TIM_Instance == TIM1){
		TIM_SingleInterval_FLAG[TIM1_CALLBACK] = TIM_SINGLE_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM2)
	{
		TIM_SingleInterval_FLAG[TIM2_CALLBACK] = TIM_SINGLE_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM3){
		TIM_SingleInterval_FLAG[TIM3_CALLBACK] = TIM_SINGLE_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM4){
		TIM_SingleInterval_FLAG[TIM4_CALLBACK] = TIM_SINGLE_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM5){
		TIM_SingleInterval_FLAG[TIM5_CALLBACK] = TIM_SINGLE_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM9){
		TIM_SingleInterval_FLAG[TIM9_CALLBACK] = TIM_SINGLE_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM10){
		TIM_SingleInterval_FLAG[TIM10_CALLBACK] = TIM_SINGLE_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM11){
		TIM_SingleInterval_FLAG[TIM11_CALLBACK] = TIM_SINGLE_INTERVAL_MODE;
	}
}
void TIM_PeriodicInterval(TIM_Config_t* TIM_Config , u32 preload , pCallBackNotification callback)
{
	CLR_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
	TIM_Config->TIM_Instance->ARR = preload;
	SET_BIT(TIM_Config->TIM_Instance->EGR,TIM_UG_BIT_POS);
	TIM_Config->UP_Callback = callback;
	TIM_Update_INT_Init(TIM_Config);
	SET_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
	if(TIM_Config->TIM_Instance == TIM1){
		TIM_SingleInterval_FLAG[TIM1_CALLBACK] = TIM_PERIODIC_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM2)
	{
		TIM_SingleInterval_FLAG[TIM2_CALLBACK] = TIM_PERIODIC_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM3){
		TIM_SingleInterval_FLAG[TIM3_CALLBACK] = TIM_PERIODIC_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM4){
		TIM_SingleInterval_FLAG[TIM4_CALLBACK] = TIM_PERIODIC_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM5){
		TIM_SingleInterval_FLAG[TIM5_CALLBACK] = TIM_PERIODIC_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM9){
		TIM_SingleInterval_FLAG[TIM9_CALLBACK] = TIM_PERIODIC_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM10){
		TIM_SingleInterval_FLAG[TIM10_CALLBACK] = TIM_PERIODIC_INTERVAL_MODE;
	}
	else if(TIM_Config->TIM_Instance == TIM11){
		TIM_SingleInterval_FLAG[TIM11_CALLBACK] = TIM_PERIODIC_INTERVAL_MODE;
	}
}
void TIM_Set_DutyCycle(const TIM_Config_t* TIM_Config , u16 DutyCycle)
{
	CLR_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
	TIM_Config->TIM_Instance->CCR1 = (u32)(((DutyCycle)/100.0)*TIM_Config->TIM_Preload);
	SET_BIT(TIM_Config->TIM_Instance->EGR,TIM_UG_BIT_POS);
	SET_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);

}
void TIM_Change_CaptureMode(TIM_Config_t* TIM_Config , u8 CaptureMode)
{
	CLR_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
	TIM_Config->TIM_IC_Mode = CaptureMode;
	TIM_IC_INIT(TIM_Config);
	SET_BIT(TIM_Config->TIM_Instance->EGR,TIM_UG_BIT_POS);
	SET_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
}
void TIM_SetPreload(TIM_Config_t* TIM_Config , u32 preload)
{
	CLR_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
	TIM_Config->TIM_Preload = preload;
	TIM_Config->TIM_Instance->ARR = preload;
	SET_BIT(TIM_Config->TIM_Instance->EGR,TIM_UG_BIT_POS);
	SET_BIT(TIM_Config->TIM_Instance->CR1,TIM_CEN_BIT_POS);
}
u32 TIM_GetInputCapture(const TIM_Config_t* TIM_Config)
{
	return TIM_Config->TIM_Instance->CCR1;
}
/*************************ISRs*********************************************/

void TIM1_UP_TIM10_IRQHandler(void)
{
	/* TIM1 Update interrupt and TIM10 global interrupt  */
	if(GET_BIT(TIM1->SR,TIM_UIF_BIT_POS) == INTERRUPT_ACTIVE)
	{
		CLR_BIT(TIM1->SR,TIM_UIF_BIT_POS);
		if(TIM_SingleInterval_FLAG[TIM1_CALLBACK] == TIM_SINGLE_INTERVAL_MODE)
		{
			CLR_BIT(TIM1->CR1,TIM_CEN_BIT_POS);
			SET_BIT(TIM1->EGR,TIM_UG_BIT_POS);
			CLR_BIT(TIM1->DIER,TIM_UIE_BIT_POS);
		}
		if(TIMx_UP_INT_Callback[TIM1_CALLBACK] != NULL)
		{
			TIMx_UP_INT_Callback[TIM1_CALLBACK]();
		}
	}
	if(GET_BIT(TIM10->SR,TIM_UIF_BIT_POS) == INTERRUPT_ACTIVE)
	{
		CLR_BIT(TIM10->SR,TIM_UIF_BIT_POS);
		if(TIM_SingleInterval_FLAG[TIM10_CALLBACK] == TIM_SINGLE_INTERVAL_MODE)
		{
			CLR_BIT(TIM10->CR1,TIM_CEN_BIT_POS);
			SET_BIT(TIM10->EGR,TIM_UG_BIT_POS);
			CLR_BIT(TIM10->DIER,TIM_UIE_BIT_POS);
		}
		if(TIMx_UP_INT_Callback[TIM10_CALLBACK] != NULL)
		{
			TIMx_UP_INT_Callback[TIM10_CALLBACK]();
		}
	}
	if(GET_BIT(TIM10->SR,TIM_CC1IF_BIT_POS) == INTERRUPT_ACTIVE)
	{
		CLR_BIT(TIM10->SR,TIM_CC1IF_BIT_POS);
		if(TIMx_CC_INT_Callback[TIM10_CALLBACK] != NULL)
		{
			TIMx_CC_INT_Callback[TIM10_CALLBACK]();
		}
	}
}
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
	/* TIM1 Trigger and Commutation interrupts and TIM11 global interrupt              */
	if(GET_BIT(TIM11->SR,TIM_UIF_BIT_POS) == INTERRUPT_ACTIVE)
	{
		CLR_BIT(TIM11->SR,TIM_UIF_BIT_POS);
		if(TIM_SingleInterval_FLAG[TIM11_CALLBACK] == TIM_SINGLE_INTERVAL_MODE)
		{
			CLR_BIT(TIM11->CR1,TIM_CEN_BIT_POS);
			SET_BIT(TIM11->EGR,TIM_UG_BIT_POS);
			CLR_BIT(TIM11->DIER,TIM_UIE_BIT_POS);
		}
		if(TIMx_UP_INT_Callback[TIM11_CALLBACK] != NULL)
		{
			TIMx_UP_INT_Callback[TIM11_CALLBACK]();
		}
	}
	if(GET_BIT(TIM11->SR,TIM_CC1IF_BIT_POS) == INTERRUPT_ACTIVE)
	{
		CLR_BIT(TIM11->SR,TIM_CC1IF_BIT_POS);
		if(TIMx_CC_INT_Callback[TIM11_CALLBACK] != NULL)
		{
			TIMx_CC_INT_Callback[TIM11_CALLBACK]();
		}
	}
}
void TIM1_BRK_TIM9_IRQHandler(void){
	if(GET_BIT(TIM9->SR,TIM_UIF_BIT_POS) == INTERRUPT_ACTIVE){
		CLR_BIT(TIM9->SR,TIM_UIF_BIT_POS);
		if(TIM_SingleInterval_FLAG[TIM9_CALLBACK] == TIM_SINGLE_INTERVAL_MODE)
		{
			CLR_BIT(TIM9->CR1,TIM_CEN_BIT_POS);
			SET_BIT(TIM9->EGR,TIM_UG_BIT_POS);
			CLR_BIT(TIM9->DIER,TIM_UIE_BIT_POS);
		}
		if(TIMx_UP_INT_Callback[TIM9_CALLBACK] != NULL){
			TIMx_UP_INT_Callback[TIM9_CALLBACK]();
		}
	}
	if(GET_BIT(TIM9->SR,TIM_CC1IF_BIT_POS) == INTERRUPT_ACTIVE){
		CLR_BIT(TIM9->SR,TIM_CC1IF_BIT_POS);
		if(TIMx_CC_INT_Callback[TIM9_CALLBACK] != NULL){
			TIMx_CC_INT_Callback[TIM9_CALLBACK]();
		}
	}
}
void TIM1_CC_IRQHandler(void)
{
	CLR_BIT(TIM1->SR,TIM_CC1IF_BIT_POS);
	if(TIMx_CC_INT_Callback[TIM1_CALLBACK] != NULL)
	{
		TIMx_CC_INT_Callback[TIM1_CALLBACK]();
	}
}

void TIM2_IRQHandler(void){
	if(GET_BIT(TIM2->SR,TIM_UIF_BIT_POS) == INTERRUPT_ACTIVE){
		CLR_BIT(TIM2->SR,TIM_UIF_BIT_POS);
		if(TIM_SingleInterval_FLAG[TIM2_CALLBACK] == TIM_SINGLE_INTERVAL_MODE)
		{
			CLR_BIT(TIM2->CR1,TIM_CEN_BIT_POS);
			SET_BIT(TIM2->EGR,TIM_UG_BIT_POS);
			CLR_BIT(TIM2->DIER,TIM_UIE_BIT_POS);
		}
		if(TIMx_UP_INT_Callback[TIM2_CALLBACK] != NULL){
			TIMx_UP_INT_Callback[TIM2_CALLBACK]();
		}
	}
	if(GET_BIT(TIM2->SR,TIM_CC1IF_BIT_POS) == INTERRUPT_ACTIVE){
		CLR_BIT(TIM2->SR,TIM_CC1IF_BIT_POS);
		if(TIMx_CC_INT_Callback[TIM2_CALLBACK] != NULL){
			TIMx_CC_INT_Callback[TIM2_CALLBACK]();
		}
	}
}
void TIM3_IRQHandler(void)
{
	if(GET_BIT(TIM3->SR,TIM_UIF_BIT_POS) == INTERRUPT_ACTIVE)
	{
		CLR_BIT(TIM3->SR,TIM_UIF_BIT_POS);
		if(TIM_SingleInterval_FLAG[TIM3_CALLBACK] == TIM_SINGLE_INTERVAL_MODE)
		{
			CLR_BIT(TIM3->CR1,TIM_CEN_BIT_POS);
			SET_BIT(TIM3->EGR,TIM_UG_BIT_POS);
			CLR_BIT(TIM3->DIER,TIM_UIE_BIT_POS);
		}
		if(TIMx_UP_INT_Callback[TIM3_CALLBACK] != NULL)
		{
			TIMx_UP_INT_Callback[TIM3_CALLBACK]();
		}
	}
	if(GET_BIT(TIM3->SR,TIM_CC1IF_BIT_POS) == INTERRUPT_ACTIVE)
	{
		CLR_BIT(TIM3->SR,TIM_CC1IF_BIT_POS);
		if(TIMx_CC_INT_Callback[TIM3_CALLBACK] != NULL)
		{
			TIMx_CC_INT_Callback[TIM3_CALLBACK]();
		}
	}
}
void TIM4_IRQHandler(void)
{
	if(GET_BIT(TIM4->SR,TIM_UIF_BIT_POS) == INTERRUPT_ACTIVE){
		CLR_BIT(TIM4->SR,TIM_UIF_BIT_POS);
		if(TIM_SingleInterval_FLAG[TIM4_CALLBACK] == TIM_SINGLE_INTERVAL_MODE)
		{
			CLR_BIT(TIM4->CR1,TIM_CEN_BIT_POS);
			SET_BIT(TIM4->EGR,TIM_UG_BIT_POS);
			CLR_BIT(TIM4->DIER,TIM_UIE_BIT_POS);
		}
		if(TIMx_UP_INT_Callback[TIM4_CALLBACK] != NULL){
			TIMx_UP_INT_Callback[TIM4_CALLBACK]();
		}
	}
	if(GET_BIT(TIM4->SR,TIM_CC1IF_BIT_POS) == INTERRUPT_ACTIVE){
		CLR_BIT(TIM4->SR,TIM_CC1IF_BIT_POS);
		if(TIMx_CC_INT_Callback[TIM4_CALLBACK] != NULL){
			TIMx_CC_INT_Callback[TIM4_CALLBACK]();
		}
	}
}
void TIM5_IRQHandler(void)
{
	if(GET_BIT(TIM5->SR,TIM_UIF_BIT_POS) == INTERRUPT_ACTIVE){
		CLR_BIT(TIM5->SR,TIM_UIF_BIT_POS);
		if(TIM_SingleInterval_FLAG[TIM5_CALLBACK] == TIM_SINGLE_INTERVAL_MODE)
		{
			CLR_BIT(TIM5->CR1,TIM_CEN_BIT_POS);
			SET_BIT(TIM5->EGR,TIM_UG_BIT_POS);
			CLR_BIT(TIM5->DIER,TIM_UIE_BIT_POS);
		}
		if(TIMx_UP_INT_Callback[TIM5_CALLBACK] != NULL){
			TIMx_UP_INT_Callback[TIM5_CALLBACK]();
		}
	}
	if(GET_BIT(TIM5->SR,TIM_CC1IF_BIT_POS) == INTERRUPT_ACTIVE){
		CLR_BIT(TIM5->SR,TIM_CC1IF_BIT_POS);
		if(TIMx_CC_INT_Callback[TIM5_CALLBACK] != NULL){
			TIMx_CC_INT_Callback[TIM5_CALLBACK]();
		}
	}
}

/**********************************************************************************************************************
 *  END OF FILE: TIM_program.c
 *********************************************************************************************************************/
