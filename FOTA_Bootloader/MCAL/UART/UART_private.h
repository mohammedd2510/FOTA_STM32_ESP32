/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  UART_private.h
 *        Author: Mohamed Osama
 *		   Date:  May 9, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/RCC/RCC_config.h"
#include "MCAL/NVIC/NVIC_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/SYSTICK/SYSTICK_interface.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define USART1 ((volatile UART_t*)0x40011000)
#define USART2 ((volatile UART_t*)0x40004400)
#define USART6 ((volatile UART_t*)0x40011400)

#define UART_TE_BIT_POS 0x00000003U
#define UART_RE_BIT_POS 0x00000002U
#define UART_UE_BIT_POS 13U

#define USART_TCIE_BIT_POS 6
#define USART_RXNEIE_BIT_POS 5

#define USART_TC_BIT_POS 6
#define USART_RXNE_BIT_POS 5

#define USART1_TX_AF 7
#define USART1_RX_AF 7

#define USART2_TX_AF 7
#define USART2_RX_AF 7

#define USART6_TX_AF 8
#define USART6_RX_AF 8

#define USART_TRANSFER_NOT_COMPLETED 0x00
#define USART_RECIEVE_BUFFER_EMPTY  0x00

#define USART_TIMEOUT 0x01
#define USART_NO_TIMEOUT 0x00
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

#define GET_UART1_TC_FLAG() (GET_BIT(USART1->USART_SR, USART_TC_BIT_POS))
#define CLEAR_UART1_TC_FLAG() (CLR_BIT(USART1->USART_SR, USART_TC_BIT_POS))

#define GET_UART1_RXNE_FLAG() (GET_BIT(USART1->USART_SR, USART_RXNE_BIT_POS))
#define CLEAR_UART1_RXNE_FLAG() (CLR_BIT(USART1->USART_SR, USART_RXNE_BIT_POS))

#define GET_UART2_TC_FLAG() (GET_BIT(USART2->USART_SR, USART_TC_BIT_POS))
#define CLEAR_UART2_TC_FLAG() (CLR_BIT(USART2->USART_SR, USART_TC_BIT_POS))

#define GET_UART2_RXNE_FLAG() (GET_BIT(USART2->USART_SR, USART_RXNE_BIT_POS))
#define CLEAR_UART2_RXNE_FLAG() (CLR_BIT(USART2->USART_SR, USART_RXNE_BIT_POS))

#define GET_UART6_TC_FLAG()  (GET_BIT(USART6->USART_SR, USART_TC_BIT_POS))
#define CLEAR_UART6_TC_FLAG()  (CLR_BIT(USART6->USART_SR, USART_TC_BIT_POS))

#define GET_UART6_RXNE_FLAG()  (GET_BIT(USART6->USART_SR, USART_RXNE_BIT_POS))
#define CLEAR_UART6_RXNE_FLAG()  (CLR_BIT(USART6->USART_SR, USART_RXNE_BIT_POS))


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef struct
{
	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_GTPR;
}UART_t;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*********************************************************************************************************************/


 
#endif /* MCAL_UART_UART_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: UART_private.h
 *********************************************************************************************************************/

