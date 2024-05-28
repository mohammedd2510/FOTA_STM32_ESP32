/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SPI_program.c
 *        Author: Mohamed Osama
 *		   Date:  Apr 6, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
#if SPI1_TX_INT_ENABLE == INTERRUPT_ENABLED
static pCallBackNotification SPI1_TX_INT_Callback = NULL;
#endif

#if SPI1_RX_INT_ENABLE == INTERRUPT_ENABLED
static pCallBackNotification SPI1_RX_INT_Callback = NULL;
#endif


#if SPI2_TX_INT_ENABLE == INTERRUPT_ENABLED
static pCallBackNotification SPI2_TX_INT_Callback = NULL;
#endif

#if SPI2_RX_INT_ENABLE == INTERRUPT_ENABLED
static pCallBackNotification SPI2_RX_INT_Callback = NULL;
#endif


#if SPI3_TX_INT_ENABLE == INTERRUPT_ENABLED
static pCallBackNotification SPI3_TX_INT_Callback = NULL;
#endif

#if SPI3_RX_INT_ENABLE == INTERRUPT_ENABLED
static pCallBackNotification SPI3_RX_INT_Callback = NULL;
#endif


static volatile SPI_t* SPIx[3] = {MSPI1, MSPI2, MSPI3};

static u8 SPI_Timeout_Flag = 0;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
static void MSPI_GPIOInit(const SPI_Config_t* SPIConfig)
{
	switch (SPIConfig->SPI_Instance)
		{
			case SPI1_INSTANCE:
				RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOAEN);
				GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN4, GPIO_ALTERNATE_FUNCTION_PIN_MODE); // SPI1_NSS_PIN
				GPIO_voidSetPinAlternateFunction(GPIO_PORTA,GPIO_PIN4,SPI1_NSS_AF);

				GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN5, GPIO_ALTERNATE_FUNCTION_PIN_MODE); // SPI1_SCK_PIN
				GPIO_voidSetPinAlternateFunction(GPIO_PORTA,GPIO_PIN5,SPI1_SCK_AF);

			//	GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN6, GPIO_ALTERNATE_FUNCTION_PIN_MODE); // SPI1_MISO_PIN
			//	GPIO_voidSetPinAlternateFunction(GPIO_PORTA,GPIO_PIN6,SPI1_MISO_AF);

				GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN7, GPIO_ALTERNATE_FUNCTION_PIN_MODE); // SPI1_MOSI_PIN
				GPIO_voidSetPinAlternateFunction(GPIO_PORTA,GPIO_PIN7,SPI1_MOSI_AF);

				break;
			case SPI2_INSTANCE:
				RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOBEN);
				GPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN10, GPIO_ALTERNATE_FUNCTION_PIN_MODE); // SP2_SCK_PIN
				GPIO_voidSetPinAlternateFunction(GPIO_PORTB, GPIO_PIN10, SPI2_SCK_AF);

		//		GPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN12, GPIO_ALTERNATE_FUNCTION_PIN_MODE); // SPI2_NSS_PIN
		//		GPIO_voidSetPinAlternateFunction(GPIO_PORTB, GPIO_PIN12, SPI2_NSS_AF);

		//		GPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN14, GPIO_ALTERNATE_FUNCTION_PIN_MODE); // SPI2_MISO_PIN
		//		GPIO_voidSetPinAlternateFunction(GPIO_PORTB, GPIO_PIN14, SPI2_MISO_AF);

				GPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN15, GPIO_ALTERNATE_FUNCTION_PIN_MODE); // SPI2_MOSI_PIN
				GPIO_voidSetPinAlternateFunction(GPIO_PORTB, GPIO_PIN15, SPI2_MOSI_AF);

				break;
			case SPI3_INSTANCE:
				RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOAEN);
				RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOBEN);

		//		GPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN10, GPIO_ALTERNATE_FUNCTION_PIN_MODE); // SPI3_NSS_PIN
		//		GPIO_voidSetPinAlternateFunction(GPIO_PORTA, GPIO_PIN10, SPI3_NSS_AF);

				GPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN3, GPIO_ALTERNATE_FUNCTION_PIN_MODE);  // SPI3_SCK_PIN
				GPIO_voidSetPinAlternateFunction(GPIO_PORTB, GPIO_PIN3, SPI3_SCK_AF);

		//		GPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN4, GPIO_ALTERNATE_FUNCTION_PIN_MODE);  // SPI3_MISO_PIN
		//		GPIO_voidSetPinAlternateFunction(GPIO_PORTB, GPIO_PIN4, SPI3_MISO_AF);

				GPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN5, GPIO_ALTERNATE_FUNCTION_PIN_MODE);  // SPI3_MOSI_PIN
				GPIO_voidSetPinAlternateFunction(GPIO_PORTB, GPIO_PIN5, SPI3_MOSI_AF);

				break;
		}
}
#if (SPI1_TX_INT_ENABLE || SPI2_TX_INT_ENABLE || SPI3_TX_INT_ENABLE ) ||(SPI1_RX_INT_ENABLE || SPI2_RX_INT_ENABLE || SPI3_RX_INT_ENABLE)==(INTERRUPT_ENABLED)
	static void MSPI_InterruptInit(const SPI_Config_t* SPIConfig)
	{
		switch (SPIConfig->SPI_Instance)
				{
					case SPI1_INSTANCE:
	#if(SPI1_TX_INT_ENABLE) ==(INTERRUPT_ENABLED)
						SET_BIT(MSPI1->CR2,TXIE_BIT_POS);
						MNVIC_voidEnableIRQ(SPI1_IRQn);
	#endif
	#if(SPI1_RX_INT_ENABLE) ==(INTERRUPT_ENABLED)
						SET_BIT(MSPI1->CR2,RXIE_BIT_POS);
						MNVIC_voidEnableIRQ(SPI1_IRQn);
	#endif
						break;
					case SPI2_INSTANCE:
	#if(SPI2_TX_INT_ENABLE) ==(INTERRUPT_ENABLED)
						SET_BIT(MSPI2->CR2,TXIE_BIT_POS);
						MNVIC_voidEnableIRQ(SPI2_IRQn);
	#endif
	#if(SPI2_RX_INT_ENABLE) ==(INTERRUPT_ENABLED)
						SET_BIT(MSPI2->CR2,RXIE_BIT_POS);
						MNVIC_voidEnableIRQ(SPI2_IRQn);
	#endif
						break;
					case SPI3_INSTANCE:
	#if(SPI3_TX_INT_ENABLE) ==(INTERRUPT_ENABLED)
						SET_BIT(MSPI3->CR2,TXIE_BIT_POS);
						MNVIC_voidEnableIRQ(SPI3_IRQn);
	#endif
	#if(SPI3_RX_INT_ENABLE) ==(INTERRUPT_ENABLED)
						SET_BIT(MSPI3->CR2,RXIE_BIT_POS);
						MNVIC_voidEnableIRQ(SPI3_IRQn);
	#endif
						break;
				}
	}
#endif
static void SPI_Timeout_Handler(void)
{
	SPI_Timeout_Flag=SPI_TIMEOUT;
}


static void MSPIx_voidClockEnable(const SPI_Config_t* SPIConfig){
	switch (SPIConfig->SPI_Instance){
	case SPI1_INSTANCE:
		RCC_voidEnablePeripheralClock(RCC_APB2,RCC_APB2_SPI1EN);
		break;
	case SPI2_INSTANCE:
		RCC_voidEnablePeripheralClock(RCC_APB1,RCC_APB1_SPI2EN);
		break;
	case SPI3_INSTANCE:
		RCC_voidEnablePeripheralClock(RCC_APB1,RCC_APB1_SPI3EN);
		break;
	}
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void MSPI_voidInit(const SPI_Config_t* SPIConfig)
{
	MSPI_GPIOInit(SPIConfig);
	MSPIx_voidClockEnable(SPIConfig);
#if (SPI1_TX_INT_ENABLE || SPI2_TX_INT_ENABLE || SPI3_TX_INT_ENABLE ) ||(SPI1_RX_INT_ENABLE || SPI2_RX_INT_ENABLE || SPI3_RX_INT_ENABLE)==(INTERRUPT_ENABLED)
	MSPI_InterruptInit(SPIConfig);
#endif
	SPIx[SPIConfig->SPI_Instance]->CR1 =SPIConfig->SPI_Mode | SPIConfig->SPI_CLKPolarity | SPIConfig->SPI_CLKPhase
			| SPIConfig->SPI_FirstBit | SPIConfig->SPI_BaudRatePrescaler;
	SET_BIT(SPIx[SPIConfig->SPI_Instance]->CR2,SSOE_BIT_POS);
	SET_BIT(SPIx[SPIConfig->SPI_Instance]->CR1, SPI_EN_BIT_POS);
}

#if (SPI1_TX_INT_ENABLE || SPI2_TX_INT_ENABLE || SPI3_TX_INT_ENABLE )==(INTERRUPT_ENABLED)
void MSPI_voidSetTXCallback(SPI_Config_t* SPIConfig , const pCallBackNotification CallbackFunction)
{
	switch (SPIConfig->SPI_Instance)
					{
						case SPI1_INSTANCE:
		#if(SPI1_TX_INT_ENABLE) ==(INTERRUPT_ENABLED)
							SPI1_TX_INT_Callback = CallbackFunction;
		#endif
							break;
						case SPI2_INSTANCE:
		#if(SPI2_TX_INT_ENABLE) ==(INTERRUPT_ENABLED)
							SPI2_TX_INT_Callback = CallbackFunction;
		#endif
							break;
						case SPI3_INSTANCE:
		#if(SPI3_TX_INT_ENABLE) ==(INTERRUPT_ENABLED)
							SPI3_TX_INT_Callback = CallbackFunction;
		#endif
							break;
					}
}
#endif

#if (SPI1_RX_INT_ENABLE || SPI2_RX_INT_ENABLE || SPI3_RX_INT_ENABLE )==(INTERRUPT_ENABLED)
void MSPI_voidSetRXCallback(SPI_Config_t* SPIConfig , const pCallBackNotification CallbackFunction)
{
	switch (SPIConfig->SPI_Instance)
						{
							case SPI1_INSTANCE:
			#if(SPI1_RX_INT_ENABLE) ==(INTERRUPT_ENABLED)
								SPI1_RX_INT_Callback = CallbackFunction;
			#endif
								break;
							case SPI2_INSTANCE:
			#if(SPI2_RX_INT_ENABLE) ==(INTERRUPT_ENABLED)
								SPI2_RX_INT_Callback = CallbackFunction;
			#endif
								break;
							case SPI3_INSTANCE:
			#if(SPI3_RX_INT_ENABLE) ==(INTERRUPT_ENABLED)
								SPI3_RX_INT_Callback = CallbackFunction;
			#endif
								break;
						}
}
#endif

Std_ReturnType MSPI_TransmitByte(SPI_Config_t* SPIConfig , u8 Copy_u8Data , u32 Copy_u32Timeout)
{
	Std_ReturnType Local_u8ErrorState = STD_OK;
    u8 Local_u8DummyReceieve = 0;
    TIM_SingleInterval(&TIM2_Cfg, Copy_u32Timeout*1000, SPI_Timeout_Handler);
    SPIx[SPIConfig->SPI_Instance]->DR = Copy_u8Data;
    while((GET_BIT(SPIx[SPIConfig->SPI_Instance]->SR,SPI_BSY_BIT_POS) == SPI_BUSY) && (SPI_Timeout_Flag != SPI_TIMEOUT));
    if(SPI_Timeout_Flag == SPI_TIMEOUT)
    {
    	Local_u8ErrorState = STD_TIMEOUT;
    	SPI_Timeout_Flag = SPI_NO_TIMEOUT;
    }
    else
    {
    	TIM_DeInit(&TIM2_Cfg);
    	Local_u8DummyReceieve = SPIx[SPIConfig->SPI_Instance]->DR;
    }
	return Local_u8ErrorState;
}
Std_ReturnType MSPI_ReceiveByte(SPI_Config_t* SPIConfig , u8* Ptr_u8Data , u32 Copy_u32Timeout)
{
	Std_ReturnType Local_u8ErrorState = STD_OK;
    u8 Local_u8DummyTransmit = 0;
    TIM_SingleInterval(&TIM2_Cfg, Copy_u32Timeout*1000, SPI_Timeout_Handler);
	SPIx[SPIConfig->SPI_Instance]->DR = Local_u8DummyTransmit;
	while((GET_BIT(SPIx[SPIConfig->SPI_Instance]->SR,SPI_BSY_BIT_POS) == SPI_BUSY) && (SPI_Timeout_Flag != SPI_TIMEOUT));
	if(SPI_Timeout_Flag == SPI_TIMEOUT)
	{
		Local_u8ErrorState = STD_TIMEOUT;
		SPI_Timeout_Flag = SPI_NO_TIMEOUT;
	}
	else {
		TIM_DeInit(&TIM2_Cfg);
		*Ptr_u8Data = SPIx[SPIConfig->SPI_Instance]->DR;
	}
	return Local_u8ErrorState;
}
Std_ReturnType MSPI_TransmitReceiveByte(SPI_Config_t* SPIConfig ,u8 Copy_u8Data, u8* Ptr_u8Data , u32 Copy_u32Timeout)
{
	Std_ReturnType Local_u8ErrorState = STD_OK;
	TIM_SingleInterval(&TIM2_Cfg, Copy_u32Timeout*1000, SPI_Timeout_Handler);
	SPIx[SPIConfig->SPI_Instance]->DR = Copy_u8Data;
	while((GET_BIT(SPIx[SPIConfig->SPI_Instance]->SR,SPI_BSY_BIT_POS) == SPI_BUSY) && (SPI_Timeout_Flag != SPI_TIMEOUT));
	if(SPI_Timeout_Flag == SPI_TIMEOUT)
	{
		Local_u8ErrorState = STD_TIMEOUT;
		SPI_Timeout_Flag = SPI_NO_TIMEOUT;
	}
	else
	{
		TIM_DeInit(&TIM2_Cfg);
		*Ptr_u8Data = SPIx[SPIConfig->SPI_Instance]->DR;
	}
	return Local_u8ErrorState;
}

Std_ReturnType MSPI_Transmit(SPI_Config_t* SPIConfig , u8* Ptr_u8Data , u16 Copy_u16DataSize , u32 Copy_u32Timeout)
{
	Std_ReturnType Local_u8ErrorState = STD_OK;
	u8 Local_u8Counter = 0;
	if(SPIConfig == NULL || Ptr_u8Data == NULL)
	{
		Local_u8ErrorState = STD_NOK;
	}
	else
	{
		for(Local_u8Counter = 0 ; Local_u8Counter < Copy_u16DataSize ; Local_u8Counter++)
		{
			Local_u8ErrorState = MSPI_TransmitByte(SPIConfig, Ptr_u8Data[Local_u8Counter], Copy_u32Timeout);
			if(Local_u8ErrorState != STD_OK)
			{
				break;
			}
		}
	}
	return Local_u8ErrorState;
}
Std_ReturnType MSPI_Receive(SPI_Config_t* SPIConfig , u8* Ptr_u8Data , u16 Copy_u16DataSize , u32 Copy_u32Timeout)
{
	Std_ReturnType Local_u8ErrorState = STD_OK;
	u8 Local_u8Counter = 0;
	if(SPIConfig == NULL || Ptr_u8Data == NULL)
	{
		Local_u8ErrorState = STD_NOK;
	}
	else
	{
		for(Local_u8Counter = 0 ; Local_u8Counter < Copy_u16DataSize ; Local_u8Counter++)
		{
			Local_u8ErrorState = MSPI_ReceiveByte(SPIConfig, &Ptr_u8Data[Local_u8Counter], Copy_u32Timeout);
			if(Local_u8ErrorState != STD_OK)
			{
				break;
			}
		}
	}
	return Local_u8ErrorState;
}
Std_ReturnType MSPI_TransmitReceive(SPI_Config_t* SPIConfig , u8 *pTxData, u8 *pRxData , u16 Copy_u16DataSize , u32 Copy_u32Timeout)
{
	Std_ReturnType Local_u8ErrorState = STD_OK;
	u8 Local_u8Counter = 0;
	if(SPIConfig == NULL || pTxData == NULL || pRxData == NULL)
	{
		Local_u8ErrorState = STD_NOK;
	}
	else
	{
		for(Local_u8Counter = 0 ; Local_u8Counter < Copy_u16DataSize ; Local_u8Counter++)
		{
			Local_u8ErrorState = MSPI_TransmitReceiveByte(SPIConfig,pTxData[Local_u8Counter] ,&pRxData[Local_u8Counter], Copy_u32Timeout);
			if(Local_u8ErrorState != STD_OK)
			{
				break;
			}
		}
	}
	return Local_u8ErrorState;
}

void MSPI_DMA_Transmit(SPI_Config_t* SPIConfig , u8* Ptr_u8Data , u16 Copy_u16DataSize)
{
	MDMA_voidInit(&SPIConfig->SPI_TX_DMA_Config);
	MDMA_voidStart(&SPIConfig->SPI_TX_DMA_Config, &SPIx[SPIConfig->SPI_Instance]->DR,(u32*)Ptr_u8Data, Copy_u16DataSize);
	SET_BIT(SPIx[SPIConfig->SPI_Instance]->CR2, TXDMAEN_BIT_POS);
}
void MSPI_DMA_Receive(SPI_Config_t* SPIConfig , u8* Ptr_u8Data , u16 Copy_u16DataSize)
{
	MDMA_voidInit(&SPIConfig->SPI_RX_DMA_Config);
	MDMA_voidStart(&SPIConfig->SPI_RX_DMA_Config, &SPIx[SPIConfig->SPI_Instance]->DR, (u32*)Ptr_u8Data, Copy_u16DataSize);
	SET_BIT(SPIx[SPIConfig->SPI_Instance]->CR2, RXDMAEN_BIT_POS);
}
void MSPI_DMA_TransmitReceive(SPI_Config_t* SPIConfig , u8 *pTxData, u8 *pRxData , u16 Copy_u16DataSize)
{
	MDMA_voidInit(&SPIConfig->SPI_TX_DMA_Config);
	MDMA_voidInit(&SPIConfig->SPI_RX_DMA_Config);
	MDMA_voidStart(&SPIConfig->SPI_TX_DMA_Config, &SPIx[SPIConfig->SPI_Instance]->DR,(u32*)pTxData, Copy_u16DataSize);
	MDMA_voidStart(&SPIConfig->SPI_RX_DMA_Config, &SPIx[SPIConfig->SPI_Instance]->DR,(u32*)pRxData, Copy_u16DataSize);
	SET_BIT(SPIx[SPIConfig->SPI_Instance]->CR2, TXDMAEN_BIT_POS);
	SET_BIT(SPIx[SPIConfig->SPI_Instance]->CR2, RXDMAEN_BIT_POS);
}
/*************************************************************SPI IRQ HANDLERS******************************************************************/
void SPI1_IRQHandler(void)
{
#if(SPI1_TX_INT_ENABLE) ==(INTERRUPT_ENABLED)
	if(GET_SPI1_TXE_FLAG() == INTERRUPT_ACTIVE)
	{
		if(SPI1_TX_INT_Callback != NULL)
		{
			SPI1_TX_INT_Callback();
		}
	}
#endif

#if(SPI1_RX_INT_ENABLE) ==(INTERRUPT_ENABLED)
	if(GET_SPI1_RXNE_FLAG() == INTERRUPT_ACTIVE)
	{
		if(SPI1_RX_INT_Callback != NULL)
		{
			SPI1_RX_INT_Callback();
		}
	}
#endif
}
void SPI2_IRQHandler(void)
{
#if(SPI2_TX_INT_ENABLE) ==(INTERRUPT_ENABLED)
	if(GET_SPI2_TXE_FLAG() == INTERRUPT_ACTIVE)
	{
		if(SPI2_TX_INT_Callback != NULL)
		{
			SPI2_TX_INT_Callback();
		}
	}
#endif

#if(SPI2_RX_INT_ENABLE) ==(INTERRUPT_ENABLED)
	if(GET_SPI2_RXNE_FLAG() == INTERRUPT_ACTIVE)
	{
		if(SPI2_RX_INT_Callback != NULL)
		{
			SPI2_RX_INT_Callback();
		}
	}
#endif
}
void SPI3_IRQHandler(void)
{
#if(SPI3_TX_INT_ENABLE) ==(INTERRUPT_ENABLED)
	if(GET_SPI3_TXE_FLAG() == INTERRUPT_ACTIVE)
	{
		if(SPI3_TX_INT_Callback != NULL)
		{
			SPI3_TX_INT_Callback();
		}
	}
#endif

#if(SPI3_RX_INT_ENABLE) ==(INTERRUPT_ENABLED)
	if(GET_SPI3_RXNE_FLAG() == INTERRUPT_ACTIVE)
	{
		if(SPI3_RX_INT_Callback != NULL)
		{
			SPI3_RX_INT_Callback();
		}
	}
#endif
}
/**********************************************************************************************************************
 *  END OF FILE: SPI_program.c
 *********************************************************************************************************************/
