/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SPI_interface.h
 *        Author: Mohamed Osama
 *		   Date:  Apr 6, 2024
 *  Description:  Single Master Slave Full Duplex SPI Version
 *  
 *********************************************************************************************************************/
#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include"LIB/Delay.h"
#include "MCAL/DMA/DMA_interface.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/** @defgroup SPI_Mode SPI Mode
  * @{
  */
#define SPI_MODE_SLAVE                  (0x00000000U)
#define SPI_MODE_MASTER					(0x00000001U << 2)
/**
  * @}
  */

/** @defgroup SPI_Instance SPI Instance
 *
 */
#define SPI1_INSTANCE            (0x00000000U)
#define SPI2_INSTANCE            (0x00000001U)
#define SPI3_INSTANCE            (0x00000002U)
/**
 *
 */

/** @defgroup SPI_BaudRatePrescaler SPI Baud Rate Prescaler
 *
 */
#define SPI_BAUDRATEPRESCALER_2   (0x00000000U << 3)
#define SPI_BAUDRATEPRESCALER_4   (0x00000001U << 3)
#define SPI_BAUDRATEPRESCALER_8   (0x00000002U << 3)
#define SPI_BAUDRATEPRESCALER_16  (0x00000003U << 3)
#define SPI_BAUDRATEPRESCALER_32  (0x00000004U << 3)
#define SPI_BAUDRATEPRESCALER_64  (0x00000005U << 3)
#define SPI_BAUDRATEPRESCALER_128 (0x00000006U << 3)
#define SPI_BAUDRATEPRESCALER_256 (0x00000007U << 3)
/**
 *
 */

/** @defgroup SPI_FirstBit SPI First Bit
 *
 */
#define SPI_MSB_FIRST              (0x00000000U << 7)
#define SPI_LSB_FIRST              (0x00000001U << 7)
/**
 *
 */

/** @defgroup SPI_Clock_Polarity SPI Clock Polarity
 *
 */
#define SPI_POLARITY_LOW           (0x00000000U << 1)
#define SPI_POLARITY_HIGH          (0x00000001U << 1)
/**
 *
 */

/** @defgroup SPI_Clock_Phase SPI Clock Phase
 *
 */
#define SPI_PHASE_FIRST_EDGE            (0x00000000U << 0)
#define SPI_PHASE_SECOND_EDGE           (0x00000001U << 0)
/**
 *
 */

#define SSOE_BIT_POS                0x02U
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
	u8 SPI_Instance;
	u8 SPI_Mode;
	u8 SPI_CLKPolarity;
	u8 SPI_CLKPhase;
	u8 SPI_FirstBit;
	u8 SPI_BaudRatePrescaler;
#if (SPI1_TX_INT_ENABLE || SPI2_TX_INT_ENABLE || SPI3_TX_INT_ENABLE )==(INTERRUPT_ENABLED)
	pCallBackNotification SPI_TX_INT_Callback;
#endif
#if (SPI1_RX_INT_ENABLE || SPI2_RX_INT_ENABLE || SPI3_RX_INT_ENABLE )==(INTERRUPT_ENABLED)
	pCallBackNotification SPI_RX_INT_Callback;
#endif
	DMA_Config_t SPI_TX_DMA_Config;
	DMA_Config_t SPI_RX_DMA_Config;
}SPI_Config_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void MSPI_voidInit(const SPI_Config_t* SPIConfig);

#if (SPI1_TX_INT_ENABLE || SPI2_TX_INT_ENABLE || SPI3_TX_INT_ENABLE )==(INTERRUPT_ENABLED)
void MSPI_voidSetTXCallback(SPI_Config_t* SPIConfig , const pCallBackNotification CallbackFunction);
#endif

#if (SPI1_RX_INT_ENABLE || SPI2_RX_INT_ENABLE || SPI3_RX_INT_ENABLE )==(INTERRUPT_ENABLED)
void MSPI_voidSetRXCallback(SPI_Config_t* SPIConfig , const pCallBackNotification CallbackFunction);
#endif

Std_ReturnType MSPI_Transmit(SPI_Config_t* SPIConfig , u8* Ptr_u8Data , u16 Copy_u16DataSize , u32 Copy_u32Timeout);
Std_ReturnType MSPI_Receive(SPI_Config_t* SPIConfig , u8* Ptr_u8Data , u16 Copy_u16DataSize , u32 Copy_u32Timeout);
Std_ReturnType MSPI_TransmitReceive(SPI_Config_t* SPIConfig , u8 *pTxData, u8 *pRxData , u16 Copy_u16DataSize , u32 Copy_u32Timeout);

Std_ReturnType MSPI_TransmitByte(SPI_Config_t* SPIConfig , u8 Copy_u8Data , u32 Copy_u32Timeout);
Std_ReturnType MSPI_ReceiveByte(SPI_Config_t* SPIConfig , u8* Ptr_u8Data , u32 Copy_u32Timeout);
Std_ReturnType MSPI_TransmitReceiveByte(SPI_Config_t* SPIConfig ,u8 Copy_u8Data, u8* Ptr_u8Data , u32 Copy_u32Timeout);

void MSPI_DMA_Transmit(SPI_Config_t* SPIConfig , u8* Ptr_u8Data , u16 Copy_u16DataSize);
void MSPI_DMA_Receive(SPI_Config_t* SPIConfig , u8* Ptr_u8Data , u16 Copy_u16DataSize);
void MSPI_DMA_TransmitReceive(SPI_Config_t* SPIConfig , u8 *pTxData, u8 *pRxData , u16 Copy_u16DataSize);
 
#endif /* MCAL_SPI_SPI_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: SPI_interface.h
 *********************************************************************************************************************/

