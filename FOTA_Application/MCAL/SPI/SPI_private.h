/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SPI_private.h
 *        Author: Mohamed Osama
 *		   Date:  Apr 6, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef MCAL_SPI_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/STD_TYPES.h"
#include "MCAL/NVIC/NVIC_interface.h"
#include "MCAL/TIM/TIM_Lcfg.h"
#include "MCAL/GPIO/GPIO_private.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/RCC/RCC_interface.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define SPI1_BASE_ADDRESS	0x40013000
#define SPI2_BASE_ADDRESS	0x40003800
#define SPI3_BASE_ADDRESS	0x40003C00


#define MSPI1		((volatile SPI_t *)(SPI1_BASE_ADDRESS))
#define MSPI2		((volatile SPI_t *)(SPI2_BASE_ADDRESS))
#define MSPI3		((volatile SPI_t *)(SPI3_BASE_ADDRESS))

#define SPI1_NSS_AF		0x05U
#define SPI1_SCK_AF		0x05U
#define SPI1_MISO_AF	0x05U
#define SPI1_MOSI_AF	0x05U

#define SPI2_SCK_AF		0x05U
#define SPI2_NSS_AF		0x05U
#define SPI2_MISO_AF	0x05U
#define SPI2_MOSI_AF	0x05U

#define SPI3_SCK_AF		0x06U
#define SPI3_NSS_AF		0x06U
#define SPI3_MISO_AF	0x06U
#define SPI3_MOSI_AF	0x06U

#define TXIE_BIT_POS	0x07U
#define RXIE_BIT_POS	0x06U

#define TXDMAEN_BIT_POS	0x01U
#define RXDMAEN_BIT_POS	0x00U

#define SPI_EN_BIT_POS	0x06U

#define SPI_BSY_BIT_POS	0x07U
#define SPI_TXE_BIT_POS	0x01U

#define SPI_BUSY 0x01
#define SPI_NOT_BUSY 0x00

#define SPI_TIMEOUT 0x01
#define SPI_NO_TIMEOUT 0x00
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define GET_SPI1_TXE_FLAG()  GET_BIT(MSPI1->SR,1)
#define GET_SPI1_RXNE_FLAG()  GET_BIT(MSPI1->SR,0)

#define GET_SPI2_TXE_FLAG()  GET_BIT(MSPI2->SR,1)
#define GET_SPI2_RXNE_FLAG()  GET_BIT(MSPI2->SR,0)

#define GET_SPI3_TXE_FLAG()  GET_BIT(MSPI3->SR,1)
#define GET_SPI3_RXNE_FLAG()  GET_BIT(MSPI3->SR,0)
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 CRCPR;
	volatile u32 RXCRCR;
	volatile u32 TXCRCR;
	volatile u32 I2SCFGR;
	volatile u32 I2SPR;
}SPI_t;



/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
static void MSPI_GPIOInit(const SPI_Config_t* SPIConfig);

#if (SPI1_TX_INT_ENABLE || SPI2_TX_INT_ENABLE || SPI3_TX_INT_ENABLE ) ||(SPI1_RX_INT_ENABLE || SPI2_RX_INT_ENABLE || SPI3_RX_INT_ENABLE)==(INTERRUPT_ENABLED)
static void MSPI_InterruptInit(const SPI_Config_t* SPIConfig);
#endif



static void MSPIx_voidClockEnable(const SPI_Config_t* SPIConfig);

static void SPI_Timeout_Handler(void);

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif /* MCAL_SPI_SPI_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: SPI_private.h
 *********************************************************************************************************************/

