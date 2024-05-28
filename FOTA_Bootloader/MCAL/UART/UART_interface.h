/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  UART_interface.h
 *        Author: Mohamed Osama
 *		   Date:  May 9, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/STD_TYPES.h"
#include "LIB/Delay.h"
#include "UART_private.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/** @defgroup UART_PARITY Parity Control
  * @{
  */
#define UART_PARITY_NONE                    0x00000000U                          /*!< Parity control disabled */
#define UART_PARITY_EVEN                    0x400U                      		 /*!< Parity control enabled and Even Parity is selected */
#define UART_PARITY_ODD                     0x600U       					     /*!< Parity control enabled and Odd Parity is selected */
/**
  * @}
  */


/** @defgroup UART_DATAWIDTH Datawidth
  * @{
  */
#define UART_DATAWIDTH_8B                   0x00000000U             /*!< 8 bits word length : Start bit, 8 data bits, n stop bits */
#define UART_DATAWIDTH_9B                    0x1000U                /*!< 9 bits word length : Start bit, 9 data bits, n stop bits */
/**
  * @}
  */


/** @defgroup UART_STOPBITS Stop Bits
  * @{
  */
#define UART_STOPBITS_0_5                   0x1000                    /*!< 0.5 stop bit */
#define UART_STOPBITS_1                     0x00000000U               /*!< 1 stop bit */
#define UART_STOPBITS_1_5                   0x3000       			  /*!< 1.5 stop bits */
#define UART_STOPBITS_2                     0x2000                    /*!< 2 stop bits */
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
	volatile UART_t* UART_Instance;                       /*!< This field defines the UART instance. */

	u32 UART_BaudRate;                           /*!< This field defines expected Usart communication baud rate. */


	u32 UART_DataWidth;                          /*!< Specifies the number of data bits transmitted or received in a frame.*/
										         /*!< This parameter can be a value of @ref UART_DATAWIDTH. */

	u32 UART_StopBits;                           /*!< Specifies the number of stop bits transmitted. */
										           /*!< This parameter can be a value of @ref UART_STOPBITS. */

	u32 UART_Parity;                             /*!< Specifies the parity mode. */
										          /*!< This parameter can be a value of @ref UART_PARITY. */

	u32 UART_TCIE;                      		 /*!< Specifies whether the TC interrupt is enabled or disabled. */

	pCallBackNotification UART_TC_INT_Callback;  /*!< Callback function pointer for TC interrupt. */

	u32 UART_RXNEIE;                   			 /*!< Specifies whether the RXNE interrupt is enabled or disabled. */

	pCallBackNotification UART_RXNE_INT_Callback; /*!< Callback function pointer for RXNE interrupt. */

}UART_InitTypeDef;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void UART_voidInit(const UART_InitTypeDef* UARTConfig);

Std_ReturnType UART_voidTransmit(const UART_InitTypeDef* UARTConfig , u8* Ptr_u8Data , u16 Copy_u16DataSize , u32 Copy_u32Timeout);
Std_ReturnType UART_TransmitByte(const UART_InitTypeDef* UARTConfig , u8 Copy_u8Data , u32 Copy_u32Timeout);

Std_ReturnType UART_ReceiveByte(const UART_InitTypeDef* UARTConfig , u8* Ptr_u8Data , u32 Copy_u32Timeout);
Std_ReturnType UART_voidReceive(const UART_InitTypeDef* UARTConfig , u8* Ptr_u8Data , u16 Copy_u16DataSize , u32 Copy_u32Timeout);
 
#endif /* MCAL_UART_UART_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: UART_interface.h
 *********************************************************************************************************************/

