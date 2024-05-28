/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DMA_interface.h
 *        Author: Mohamed Osama
 *		   Date:  Apr 22, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef MCAL_DMA_DMA_INTERFACE_H_
#define MCAL_DMA_DMA_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "DMA_private.h"
#include"DMA_cfg.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/** @defgroup DMA_Channel_selection DMA Channel selection
  * @brief    DMA channel selection
  * @{
  */
#define DMA_CHANNEL0                 0x00000000U    /*!< DMA Channel 0 */
#define DMA_CHANNEL1                 0x02000000U    /*!< DMA Channel 1 */
#define DMA_CHANNEL2                 0x04000000U    /*!< DMA Channel 2 */
#define DMA_CHANNEL3                 0x06000000U    /*!< DMA Channel 3 */
#define DMA_CHANNEL4                 0x08000000U    /*!< DMA Channel 4 */
#define DMA_CHANNEL5                 0x0A000000U    /*!< DMA Channel 5 */
#define DMA_CHANNEL6                 0x0C000000U    /*!< DMA Channel 6 */
#define DMA_CHANNEL7                 0x0E000000U    /*!< DMA Channel 7 */

/**
  * @}
  */

/** @defgroup DMA_Stream_selection DMA Stream selection
 *
 */
#define DMA_STREAM_0                  0x00U    /*!< DMA Stream 0 */
#define DMA_STREAM_1                  0x01U    /*!< DMA Stream 1 */
#define DMA_STREAM_2                  0x02U    /*!< DMA Stream 2 */
#define DMA_STREAM_3                  0x03U    /*!< DMA Stream 3 */
#define DMA_STREAM_4                  0x04U    /*!< DMA Stream 4 */
#define DMA_STREAM_5                  0x05U    /*!< DMA Stream 5 */
#define DMA_STREAM_6                  0x06U    /*!< DMA Stream 6 */
#define DMA_STREAM_7                  0x07U    /*!< DMA Stream 7 */

/**
 * @}
 */

/** @defgroup DMA_Data_transfer_direction DMA Data transfer direction
 *
 */
#define DMA_PERIPHERAL_TO_MEMORY      0x00000000U    /*!< Peripheral to Memory */
#define DMA_MEMORY_TO_PERIPHERAL      0x00000040U    /*!< Memory to Peripheral */
#define DMA_MEMORY_TO_MEMORY          0x00000080U    /*!< Memory to Memory */

/**
 * @}
 */

/** @defgroup DMA_Peripheral_incremented_mode DMA Peripheral incremented mode
 *
 */
#define DMA_PERIPHERAL_INCREMENT      0x00000200U    /*!< Peripheral increment mode */
#define DMA_PERIPHERAL_NO_INCREMENT   0x00000000U    /*!< Peripheral no increment mode */

/**
 * @}
 */

/** @defgroup DMA_Memory_incremented_mode DMA Memory incremented mode
 *
 */
#define DMA_MEMORY_INCREMENT          0x00000400U    /*!< Memory increment mode */
#define DMA_MEMORY_NO_INCREMENT       0x00000000U    /*!< Memory no increment mode */

/**
 * @}
 */

/** @defgroup DMA_Peripheral_data_size DMA Peripheral data size
 *
 */
#define DMA_PERIPHERAL_8BITS          0x00000000U    /*!< Peripheral 8 bits */
#define DMA_PERIPHERAL_16BITS         0x00000800U    /*!< Peripheral 16 bits */
#define DMA_PERIPHERAL_32BITS         0x00001000U    /*!< Peripheral 32 bits */

/**
 * @}
 */

/** @defgroup DMA_Memory_data_size DMA Memory data size
 *
 */
#define DMA_MEMORY_8BITS              0x00000000U    /*!< Memory 8 bits */
#define DMA_MEMORY_16BITS             0x00002000U    /*!< Memory 16 bits */
#define DMA_MEMORY_32BITS             0x00004000U    /*!< Memory 32 bits */

/**
 * @}
 */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
	DMA_t* Instance;           /*!< Specifies the DMA Instance.*/

	u32 Stream;               /*!< Specifies the stream. This parameter can be a value of @ref DMA_Stream_selection */

	u32 Channel;              /*!< Specifies the channel used for the specified stream.
	                                 This parameter can be a value of @ref DMA_Channel_selection
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 */
    u32 Direction;            /*!< Specifies if the data will be transferred from memory to peripheral,
	                                 from memory to memory or from peripheral to memory.
	                                 This parameter can be a value of @ref DMA_Data_transfer_direction              */

    u32 PeriphInc;            /*!< Specifies whether the Peripheral address register should be incremented or not.
	                                 This parameter can be a value of @ref DMA_Peripheral_incremented_mode          */

    u32 MemInc;               /*!< Specifies whether the memory address register should be incremented or not.
	                                 This parameter can be a value of @ref DMA_Memory_incremented_mode              */

    u32 PeriphDataSize;  /*!< Specifies the Peripheral data width.
	                                 This parameter can be a value of @ref DMA_Peripheral_data_size                 */

    u32 MemDataSize;     /*!< Specifies the Memory data width.
	                                 This parameter can be a value of @ref DMA_Memory_data_size   */


  u8 DMA_TC_InterruptEnable; /*!<  DMA Transfer complete interrupt Enable                        */

 pCallBackNotification DMA_TC_Callback; /*!< DMA Transfer complete callback function pointer   */

}DMA_Config_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void MDMA_voidInit(DMA_Config_t* DMA_Config);
void MDMA_voidStart(DMA_Config_t* DMA_Config , u32* PeriphAddr , u32* MemAddr , u32 DataLength);
 
#endif /* MCAL_DMA_DMA_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: DMA_interface.h
 *********************************************************************************************************************/

