/*********************************************
 * Author:				Mohamed Osama
 * Creation Data:		29 Feb, 2024
 * Version:				v1.0
 * Compiler:			GNU ARM-GCC
 * Controller:			STM32F401CCU6
 * Layer:				MCAL
 ********************************************/
/*********************************************
 * Version	    Date			 Author            Description
 *  v1.0	  29 Feb, 2024	   Mohamed Osama      Initial Creation
 *********************************************/
#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

#include"LIB/STD_TYPES.h"


/* Memory Mapping of Core Hardware */

#define SysTick_BASE 	(0xE000E010UL)  // Base address of the SysTick peripheral
#define SysTick			((SysTick_Type*)SysTick_BASE)  // Pointer to the SysTick peripheral registers

/**
  * @brief  SysTick Control and Status Register Structure
  *
  * This structure represents the SysTick Control and Status Register (SysTick_Type).
  * It contains the following members:
  *
  * @note   The structure fields represent the register offsets and access types.
  *
  * @ingroup SysTick
  */
typedef struct
{
	volatile u32 CTRL;   /*!< Offset: 0x00 (R/W)  SysTick Control and Status Register */

	volatile u32 LOAD;   /*!< Offset: 0x04 (R/W)  SysTick Reload Value Register */

	volatile u32 VAL;    /*!< Offset: 0x08 (R/W)  SysTick Current Value Register */

	volatile u32 CALIB;  /*!< Offset: 0x0C (R/ )  SysTick Calibration Value Register */
} SysTick_Type;


/**
  * @brief  Initializes the SysTick timer with the specified number of ticks.
  * @details This function initializes the SysTick timer with the provided number of ticks.
  *          The SysTick timer is a 24-bit down counter that generates an interrupt when it reaches zero.
  * @param  SysTick_Ticks: The number of ticks to be loaded into the SysTick timer.
  * @return 0 if the initialization is successful, 1 if it fails.
  */


#define SYSTICK_AHB_DIV_1 1
#define SYSTICK_AHB_DIV_8 8
#define SYSTICK_ENABLE 0
#define SYSTICK_DISABLE 1

/* SysTick Control / Status Register Definitions */
#define SysTick_CTRL_ENABLE_Pos 			0U   /**< Position of the ENABLE bit in the SysTick Control and Status Register */
#define SysTick_CTRL_ENABLE_Msk 		   (1U << SysTick_CTRL_ENABLE_Pos)   /**< Mask for the ENABLE bit in the SysTick Control and Status Register */

#define SysTick_CTRL_TICKINT_Pos 			1U   /**< Position of the TICKINT bit in the SysTick Control and Status Register */
#define SysTick_CTRL_TICKINT_Msk 		   (1U << SysTick_CTRL_TICKINT_Pos)   /**< Mask for the TICKINT bit in the SysTick Control and Status Register */

#define SysTick_CTRL_CLKSOURCE_Pos 			2U   /**< Position of the CLKSOURCE bit in the SysTick Control and Status Register */
#define SysTick_CTRL_CLKSOURCE_Msk 		   (1U << SysTick_CTRL_CLKSOURCE_Pos)   /**< Mask for the CLKSOURCE bit in the SysTick Control and Status Register */

#define SysTick_CTRL_COUNTFLAG_Pos 			16U   /**< Position of the COUNTFLAG bit in the SysTick Control and Status Register */
#define SysTick_CTRL_COUNTFLAG_Msk 		   (1U << SysTick_CTRL_COUNTFLAG_Pos)   /**< Mask for the COUNTFLAG bit in the SysTick Control and Status Register */

/* SysTick Reload Register Definitions */
#define SysTick_LOAD_RELOAD_Pos 			 0U   /**< Position of the RELOAD value in the SysTick Reload Value Register */
#define SysTick_LOAD_RELOAD_Msk 		   (0xFFFFFFUL << SysTick_LOAD_RELOAD_Pos)   /**< Mask for the RELOAD value in the SysTick Reload Value Register */
/****************************************************/
#define SysTick_SingleInterval_Mode			0U
#define SysTick_PeriodicInterval_Mode		1U

#endif
