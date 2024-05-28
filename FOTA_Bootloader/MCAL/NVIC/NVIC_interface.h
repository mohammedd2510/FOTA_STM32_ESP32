/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NVIC_interface.h
 *        Author: Mohamed Osama
 *		   Date:  Mar 15, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum {
	// Core Exceptions
	 NonMaskableInt_IRQn     = -14,  // Non-Maskable Interrupt
	 MemoryManagement_IRQn   = -12,  // Memory Management Interrupt
	 BusFault_IRQn           = -11,  // Bus Fault Interrupt
	 UsageFault_IRQn         = -10,  // Usage Fault Interrupt
	 SVCall_IRQn             = -5,   // Supervisor Call Interrupt
	 DebugMonitor_IRQn       = -4,   // Debug Monitor Interrupt
	 PendSV_IRQn             = -2,   // PendSV Interrupt
	 SysTick_IRQn            = -1,   // SysTick Interrupt
	// STM32-specific interrupts
    WWDG_IRQn                   = 0,    // Window Watchdog interrupt
    EXTI16_PVD_IRQn             = 1,    // EXTI Line 16 interrupt / PVD through EXTI line detection interrupt
    EXTI21_TAMP_STAMP_IRQn      = 2,    // EXTI Line 21 interrupt / Tamper and TimeStamp interrupts through the EXTI line
    EXTI22_RTC_WKUP_IRQn        = 3,    // EXTI Line 22 interrupt / RTC Wakeup interrupt through the EXTI line
    FLASH_IRQn                  = 4,    // Flash global interrupt
    RCC_IRQn                    = 5,    // RCC global interrupt
    EXTI0_IRQn                  = 6,    // EXTI Line 0 interrupt
    EXTI1_IRQn                  = 7,    // EXTI Line 1 interrupt
    EXTI2_IRQn                  = 8,    // EXTI Line 2 interrupt
    EXTI3_IRQn                  = 9,    // EXTI Line 3 interrupt
    EXTI4_IRQn                  = 10,   // EXTI Line 4 interrupt
    DMA1_Stream0_IRQn           = 11,   // DMA1 Stream 0 global interrupt
    DMA1_Stream1_IRQn           = 12,   // DMA1 Stream 1 global interrupt
    DMA1_Stream2_IRQn           = 13,   // DMA1 Stream 2 global interrupt
    DMA1_Stream3_IRQn           = 14,   // DMA1 Stream 3 global interrupt
    DMA1_Stream4_IRQn           = 15,   // DMA1 Stream 4 global interrupt
    DMA1_Stream5_IRQn           = 16,   // DMA1 Stream 5 global interrupt
    DMA1_Stream6_IRQn           = 17,   // DMA1 Stream 6 global interrupt
    ADC_IRQn                    = 18,   // ADC1 global interrupt
    EXTI9_5_IRQn                = 23,   // EXTI Line [9:5] interrupts
    TIM1_BRK_TIM9_IRQn          = 24,   // TIM1 Break interrupt and TIM9 global interrupt
    TIM1_UP_TIM10_IRQn          = 25,   // TIM1 Update interrupt and TIM10 global interrupt
    TIM1_TRG_COM_TIM11_IRQn     = 26,   // TIM1 Trigger and Commutation interrupts and TIM11 global interrupt
    TIM1_CC_IRQn                = 27,   // TIM1 Capture Compare interrupt
    TIM2_IRQn                   = 28,   // TIM2 global interrupt
    TIM3_IRQn                   = 29,   // TIM3 global interrupt
    TIM4_IRQn                   = 30,   // TIM4 global interrupt
    I2C1_EV_IRQn                = 31,   // I2C1 event interrupt
    I2C1_ER_IRQn                = 32,   // I2C1 error interrupt
    I2C2_EV_IRQn                = 33,   // I2C2 event interrupt
    I2C2_ER_IRQn                = 34,   // I2C2 error interrupt
    SPI1_IRQn                   = 35,   // SPI1 global interrupt
    SPI2_IRQn                   = 36,   // SPI2 global interrupt
    USART1_IRQn                 = 37,   // USART1 global interrupt
    USART2_IRQn                 = 38,   // USART2 global interrupt
    EXTI15_10_IRQn              = 40,   // EXTI Line [15:10] interrupts
    EXTI17_RTC_Alarm_IRQn       = 41,   // EXTI Line 17 interrupt / RTC Alarms (A and B) through EXTI line interrupt
    EXTI18_OTG_FS_WKUP_IRQn     = 42,   // EXTI Line 18 interrupt / USB On-The-Go FS Wakeup through EXTI line interrupt
    DMA1_Stream7_IRQn           = 47,   // DMA1 Stream 7 global interrupt
    SDIO_IRQn                   = 49,   // SDIO global interrupt
    TIM5_IRQn                   = 50,   // TIM5 global interrupt
    SPI3_IRQn                   = 51,   // SPI3 global interrupt
    DMA2_Stream0_IRQn           = 56,   // DMA2 Stream 0 global interrupt
    DMA2_Stream1_IRQn           = 57,   // DMA2 Stream 1 global interrupt
    DMA2_Stream2_IRQn           = 58,   // DMA2 Stream 2 global interrupt
    DMA2_Stream3_IRQn           = 59,   // DMA2 Stream 3 global interrupt
    DMA2_Stream4_IRQn           = 60,   // DMA2 Stream 4 global interrupt
    OTG_FS_IRQn                 = 67,   // USB On The Go FS global interrupt
    DMA2_Stream5_IRQn= 68,   // DMA2 Stream 5 global interrupt
    DMA2_Stream6_IRQn           = 69,   // DMA2 Stream 6 global interrupt
    DMA2_Stream7_IRQn           = 70,   // DMA2 Stream 7 global interrupt
    USART6_IRQn                 = 71,   // USART6 global interrupt
    I2C3_EV_IRQn                = 72,   // I2C3 event interrupt
    I2C3_ER_IRQn                = 73,   // I2C3 error interrupt
    FPU_IRQn                    = 81,   // FPU global interrupt
    SPI4_IRQn                   = 84    // SPI4 global interrupt
}IRQn_Type;

typedef enum
{
	MNVIC_INT_DISABLE =  0,
	MNVIC_INT_ENABLE,
}NVIC_INT_CTRL_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void MNVIC_voidInit(void);

/**
 * @brief Enables a specific interrupt in the NVIC.
 * @details This function enables the interrupt specified by the IRQn parameter in the NVIC
 * @param IRQn The interrupt number to be enabled.
 * @note IRQn must not be Negative.
 */
void MNVIC_voidEnableIRQ(IRQn_Type IRQn);
/** @brief Disables a specific interrupt in the NVIC.
 *  @details This function disables the interrupt specified by the IRQn parameter in the NVIC
 *  @param IRQn The interrupt number to be disabled.
 *  @note IRQn must not be Negative.
 */
void MNVIC_voidDisableIRQ(IRQn_Type IRQn);

/** @brief Sets a specific interrupt as pending in the NVIC.
 *  @details This function sets the specified interrupt as pending in the NVIC
 *  @param IRQn The interrupt number to be set as pending.
 *  @note IRQn must not be Negative.
 */
void MNVIC_voidPeripheralInterruptControl(IRQn_Type IRQn ,NVIC_INT_CTRL_t Copy_tInterruptState);

void MNVIC_voidSetPendingIRQ(IRQn_Type IRQn);

/** @brief Clears the pending status of a specific interrupt in the NVIC.
 *  @details This function clears the pending status of the specified interrupt in the NVIC
 *  @param IRQn The interrupt number for which the pending status should be cleared.
 *  @note IRQn must not be Negative.
 */
void MNVIC_voidClearPendingIRQ(IRQn_Type IRQn);

/** @brief Retrieves the active status of a specific interrupt in the NVIC.
 *  @details This function retrieves the active status of the specified interrupt in the NVIC (Nested Vectored Interrupt Controller).
 *  @param IRQn The interrupt number for which the active status should be retrieved.
 *  @return The active status of the specified interrupt. It returns a 1 value if the interrupt is active, and zero otherwise.
 *  @note IRQn must not be Negative
 */
u32 MNVIC_u32GetActiveIRQ(IRQn_Type IRQn);

/**
 * @brief Set the priority of a specific interrupt.
 *
 * @details This function allows setting the priority of a specific interrupt identified by its IRQn_Type.
 *          The priority value determines the relative importance of the interrupt compared to other interrupts.
 *
 * @param IRQn     The interrupt number for which the priority is to be set.
 * @param Priority The priority value to be assigned to the interrupt.
 *                 - The valid range of priority values depends on the specific MicroController.
 *                 - A lower numerical value represents a higher priority.
 *
 * @return None.
 *
 * @note The priority value assigned to an interrupt determines its relative importance compared to other interrupts.
 *       The valid range of priority values may vary depending on the specific MicroController.
 */
void MNVIC_voidSetPriority(IRQn_Type IRQn, u32 Priority);

/**
 * @brief Get the priority of a specific interrupt.
 *
 * @details This function retrieves the priority of a specific interrupt identified by its IRQn_Type.
 *          The priority value indicates the relative importance of the interrupt compared to other interrupts.
 *
 * @param IRQn The interrupt number for which the priority is to be retrieved.
 *
 * @return The priority value of the specified interrupt.
 *         - The priority value represents the relative importance of the interrupt.
 *         - The valid range of priority values depends on the specific MicroController.
 *         - A lower numerical value indicates a higher priority.
 *
 * @note The priority value of an interrupt indicates its relative importance compared to other interrupts.
 *       The valid range of priority values may vary depending on the specific MicroController.
 */
u32 MNVIC_u32GetPriority(IRQn_Type IRQn);

/**
 * @brief Generate a Software Generated Interrupt (SGI) for a specific interrupt request line.
 *
 * @details This function generates a Software Generated Interrupt (SGI) for a specific interrupt request line identified by its IRQn_Type.
 *          An SGI can be used to trigger an interrupt handler for a specific interrupt request line manually.
 *
 * @param IRQn The interrupt request line for which the SGI needs to be generated.
 *
 * @return None.
 *
 * @note This function does not return a value.
 *       The specific implementation details of the generateSGI function may vary depending on the system.
 */
void MNVIC_voidGenerateSGI(IRQn_Type IRQn);
 
#endif /* NVIC_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: NVIC_interface.h
 *********************************************************************************************************************/

