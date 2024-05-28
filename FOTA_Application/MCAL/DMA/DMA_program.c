/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DMA_program.c
 *        Author: Mohamed Osama
 *		   Date:  Apr 22, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include"MCAL/DMA/DMA_private.h"
#include"MCAL/DMA/DMA_interface.h"
#include"MCAL/DMA/DMA_cfg.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static pCallBackNotification DMA1_TCx_Callback[8] ={ NULL};
static pCallBackNotification DMA2_TCx_Callback[8] ={ NULL};
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static void DMA_ClearTCInterruptFlag(DMA_Config_t* DMA_Config);
static void DMA_Interrupt_Init(DMA_Config_t* DMA_Config);
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************
*********************************************************************************************************************/
static void DMA_ClearTCInterruptFlag(DMA_Config_t* DMA_Config)
{
	if(DMA_Config->Stream == DMA_STREAM_0)
	{
		SET_BIT(DMA_Config->Instance->LIFCR ,DMA_CTCIF0_BIT_POS);
	}
	else if (DMA_Config->Stream == DMA_STREAM_1)
	{
		SET_BIT(DMA_Config->Instance->LIFCR ,DMA_CTCIF1_BIT_POS);
	}
	else if (DMA_Config->Stream == DMA_STREAM_2)
	{
		SET_BIT(DMA_Config->Instance->LIFCR ,DMA_CTCIF2_BIT_POS);
	}
	else if (DMA_Config->Stream == DMA_STREAM_3)
	{
		SET_BIT(DMA_Config->Instance->LIFCR ,DMA_CTCIF3_BIT_POS);
	}
	else if (DMA_Config->Stream == DMA_STREAM_4)
	{
		SET_BIT(DMA_Config->Instance->HIFCR ,DMA_CTCIF4_BIT_POS);
	}
	else if (DMA_Config->Stream == DMA_STREAM_5)
	{
		SET_BIT(DMA_Config->Instance->HIFCR ,DMA_CTCIF5_BIT_POS);
	}
	else if (DMA_Config->Stream == DMA_STREAM_6)
	{
		SET_BIT(DMA_Config->Instance->HIFCR ,DMA_CTCIF6_BIT_POS);
	}
	else if (DMA_Config->Stream == DMA_STREAM_7)
	{
		SET_BIT(DMA_Config->Instance->HIFCR ,DMA_CTCIF7_BIT_POS);
	}
}
static void DMA_Interrupt_Init(DMA_Config_t* DMA_Config)
{
	if(DMA_Config->Instance ==  DMA1)
	{
		if(DMA_Config->Stream <=6)
		{
			MNVIC_voidEnableIRQ(DMA_Config->Stream + 11);
		}
		else if (DMA_Config->Stream == 7 )
		{
			MNVIC_voidEnableIRQ(DMA1_Stream7_IRQn);
		}
		DMA1_TCx_Callback[DMA_Config->Stream] = DMA_Config->DMA_TC_Callback;
	}
	else if (DMA_Config->Instance == DMA2)
	{
		if(DMA_Config->Stream <=4)
		{
			MNVIC_voidEnableIRQ(DMA_Config->Stream + 56);
		}
		else if ((DMA_Config->Stream > 4) && (DMA_Config->Stream <= 7 ))
		{
			MNVIC_voidEnableIRQ(DMA_Config->Stream + 68);
		}
		DMA2_TCx_Callback[DMA_Config->Stream] = DMA_Config->DMA_TC_Callback;
	}
	else
	{
		/* Nothing */
	}
	SET_BIT(DMA_Config->Instance->DMA_Sx[DMA_Config->Stream].CR,DMA_TCIE_BIT_POS);
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void MDMA_voidInit(DMA_Config_t* DMA_Config)
{
	/* Enable DMA Clock */
	if(DMA_Config->Instance ==  DMA1)
	{
		RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_DMA1EN);
	}
	else if (DMA_Config->Instance == DMA2)
	{
		RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_DMA2EN);
	}
	else
	{
		/* Nothing */
	}
	/* Clear DMA stream pervious configuration */
	DMA_Config->Instance->DMA_Sx[DMA_Config->Stream].CR =0;
	/* Clear DMA TC interrupt Flag */
	DMA_ClearTCInterruptFlag(DMA_Config);
	/* Configure DMA Stream */
	DMA_Config->Instance->DMA_Sx[DMA_Config->Stream].CR =
			((DMA_Config->Channel) |
			(DMA_Config->Direction) |
			(DMA_Config->PeriphInc) |
			(DMA_Config->MemInc) |
			(DMA_Config->PeriphDataSize) |
			(DMA_Config->MemDataSize) );
	if(DMA_Config->DMA_TC_InterruptEnable == INTERRUPT_ENABLED)
	{
		DMA_Interrupt_Init(DMA_Config);
	}
}
void MDMA_voidStart(DMA_Config_t* DMA_Config , u32* PeriphAddr , u32* MemAddr , u32 DataLength)
{
	CLR_BIT(DMA_Config->Instance->DMA_Sx[DMA_Config->Stream].CR ,DMA_STREAM_ENABLE_BIT_POS);
	DMA_Config->Instance->DMA_Sx[DMA_Config->Stream].NDTR = DataLength;
	DMA_Config->Instance->DMA_Sx[DMA_Config->Stream].PAR = (u32)PeriphAddr;
	DMA_Config->Instance->DMA_Sx[DMA_Config->Stream].M0AR = (u32)MemAddr;
	SET_BIT(DMA_Config->Instance->DMA_Sx[DMA_Config->Stream].CR ,DMA_STREAM_ENABLE_BIT_POS);
}

/************************************* DMA1 ISRs************************************************/
void DMA1_Stream0_IRQHandler(void)
{
	SET_BIT(DMA1->LIFCR ,DMA_CTCIF0_BIT_POS);
	if(DMA1_TCx_Callback[0] != NULL)
	{
		DMA1_TCx_Callback[0]();
	}
}
void DMA1_Stream1_IRQHandler(void){
	SET_BIT(DMA1->LIFCR ,DMA_CTCIF1_BIT_POS);
	if(DMA1_TCx_Callback[1] != NULL)
	{
		DMA1_TCx_Callback[1]();
	}
}
void DMA1_Stream2_IRQHandler(void){
	SET_BIT(DMA1->LIFCR ,DMA_CTCIF2_BIT_POS);
	if(DMA1_TCx_Callback[2] != NULL)
	{
		DMA1_TCx_Callback[2]();
	}
}
void DMA1_Stream3_IRQHandler(void)
{
	SET_BIT(DMA1->LIFCR ,DMA_CTCIF3_BIT_POS);
	if(DMA1_TCx_Callback[3] != NULL)
	{
		DMA1_TCx_Callback[3]();
	}
}
void DMA1_Stream4_IRQHandler(void){
	SET_BIT(DMA1->HIFCR ,DMA_CTCIF4_BIT_POS);
	if(DMA1_TCx_Callback[4] != NULL)
	{
		DMA1_TCx_Callback[4]();
	}
}
void DMA1_Stream5_IRQHandler(void){
	SET_BIT(DMA1->HIFCR ,DMA_CTCIF5_BIT_POS);
	if(DMA1_TCx_Callback[5] != NULL)
	{
		DMA1_TCx_Callback[5]();
	}
}
void DMA1_Stream6_IRQHandler(void){
	SET_BIT(DMA1->HIFCR ,DMA_CTCIF6_BIT_POS);
	if(DMA1_TCx_Callback[6] != NULL)
	{
		DMA1_TCx_Callback[6]();
	}
}
void DMA1_Stream7_IRQHandler(void){
	SET_BIT(DMA1->HIFCR ,DMA_CTCIF7_BIT_POS);
	if(DMA1_TCx_Callback[7] != NULL)
	{
		DMA1_TCx_Callback[7]();
	}
}

/************************************* DMA2 ISRs************************************************/
void DMA2_Stream0_IRQHandler(void)
{
	SET_BIT(DMA2->LIFCR ,DMA_CTCIF0_BIT_POS);
	if(DMA2_TCx_Callback[0] != NULL)
	{
		DMA2_TCx_Callback[0]();
	}
}
void DMA2_Stream1_IRQHandler(void){
	SET_BIT(DMA2->LIFCR ,DMA_CTCIF1_BIT_POS);
	if(DMA2_TCx_Callback[1] != NULL)
	{
		DMA2_TCx_Callback[1]();
	}
}
void DMA2_Stream2_IRQHandler(void){
	SET_BIT(DMA2->LIFCR ,DMA_CTCIF2_BIT_POS);
	if(DMA2_TCx_Callback[2] != NULL)
	{
		DMA2_TCx_Callback[2]();
	}
}
void DMA2_Stream3_IRQHandler(void)
{
	SET_BIT(DMA2->LIFCR ,DMA_CTCIF3_BIT_POS);
	if(DMA2_TCx_Callback[3] != NULL)
	{
		DMA2_TCx_Callback[3]();
	}
}
void DMA2_Stream4_IRQHandler(void){
	SET_BIT(DMA2->HIFCR ,DMA_CTCIF4_BIT_POS);
	if(DMA2_TCx_Callback[4] != NULL)
	{
		DMA2_TCx_Callback[4]();
	}
}
void DMA2_Stream5_IRQHandler(void){
	SET_BIT(DMA2->HIFCR ,DMA_CTCIF5_BIT_POS);
	if(DMA2_TCx_Callback[5] != NULL)
	{
		DMA2_TCx_Callback[5]();
	}
}
void DMA2_Stream6_IRQHandler(void){
	SET_BIT(DMA2->HIFCR ,DMA_CTCIF6_BIT_POS);
	if(DMA2_TCx_Callback[6] != NULL)
	{
		DMA2_TCx_Callback[6]();
	}
}
void DMA2_Stream7_IRQHandler(void){
	SET_BIT(DMA2->HIFCR ,DMA_CTCIF7_BIT_POS);
	if(DMA2_TCx_Callback[7] != NULL)
	{
		DMA2_TCx_Callback[7]();
	}
}
/**********************************************************************************************************************
 *  END OF FILE: DMA_program.c
 *********************************************************************************************************************/
