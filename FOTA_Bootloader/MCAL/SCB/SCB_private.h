/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SCB_private.h
 *        Author: Mohamed Osama
 *		   Date:  Mar 15, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef SCB_PRIVATE_H_
#define SCB_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define SCB_BASE (0xE000ED00UL)
#define SCB ((SCB_Type*)SCB_BASE)


/**
 * @brief System Control Block (SCB) AIRCR Register Bit Positions Macros
 *
 * These macros define the bit positions for specific fields in the AIRCR register of the SCB.
 */

#define SCB_AIRCR_PRIGROUP_POS 8U       /**< Priority Group Bit Position: 8 */
#define SCB_AIRCR_VECTKEY_POS 16U       /**< Vector Key Bit Position: 16 */


/**
 * @brief System Control Block (SCB) AIRCR Register Bit Masks Macros
 *
 * These macros define the bit masks for specific fields in the AIRCR register of the SCB.
 */

#define SCB_AIRCR_PRIGROUP_Msk  (7UL << SCB_AIRCR_PRIGROUP_POS)   /**< Priority Group Bit Mask */
#define SCB_AIRCR_VECTKEY_Msk   (0xFFFFUL << SCB_AIRCR_VECTKEY_POS)   /**< Vector Key Status Bit Mask */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/**
 * @brief Structure representing the System Control Block (SCB) registers.
 */
typedef struct {
    volatile u32 CPUID;   /**< Offset: 0x00 - R   - CPUID Base Register */
    volatile u32 ICSR;    /**< Offset: 0x04 - R/W - Interrupt Control and State Register */
    volatile u32 VTOR;    /**< Offset: 0x08 - R/W - Vector Table Offset Register */
    volatile u32 AIRCR;   /**< Offset: 0x0C - R/W - Application Interrupt and Reset Control Register */
    volatile u32 SCR;     /**< Offset: 0x10 - R/W - System Control Register */
    volatile u32 CCR;     /**< Offset: 0x14 - R/W - Configuration and Control Register */
    volatile u32 SHPR1;   /**< Offset: 0x18 - R/W - System Handler Priority Register 1 */
    volatile u32 SHPR2;   /**< Offset: 0x1C - R/W - System Handler Priority Register 2 */
    volatile u32 SHPR3;   /**< Offset: 0x20 - R/W - System Handler Priority Register 3 */
    volatile u32 SHCRS;   /**< Offset: 0x24 - R/W - System Handler Control and State Register */
    volatile u32 CFSR;    /**< Offset: 0x28 - R/W - Configurable Fault Status Register */
} SCB_Type;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif /* SCB_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: SCB_private.h
 *********************************************************************************************************************/
