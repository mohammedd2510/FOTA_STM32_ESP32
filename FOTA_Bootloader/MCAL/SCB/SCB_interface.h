/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SCB_interface.h
 *        Author: Mohamed Osama
 *		   Date:  Mar 15, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef SCB_INTERFACE_H_
#define SCB_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/**
 * @brief System Control Block (SCB) Priority Group Macros
 *
 * These macros define the priority group values for the SCB register.
 * The priority group determines the number of bits allocated for preemptive priority
 * and subpriority in the interrupt priority level.
 */

#define SCB_PRIORITYGROUP_0 	0x00000007UL /**< Priority Group 0: 0 bits for preemptive priority, 4 bits for subpriority */
#define SCB_PRIORITYGROUP_1 	0x00000006UL /**< Priority Group 1: 1 bits for preemptive priority, 3 bits for subpriority */
#define SCB_PRIORITYGROUP_2 	0x00000005UL /**< Priority Group 2: 2 bits for preemptive priority, 2 bits for subpriority */
#define SCB_PRIORITYGROUP_3 	0x00000004UL /**< Priority Group 3: 3 bits for preemptive priority, 1 bit for subpriority */
#define SCB_PRIORITYGROUP_4 	0x00000003UL /**< Priority Group 4: 4 bits for preemptive priority, 0 bits for subpriority */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**
 * @brief Set the priority grouping for the System Control Block (SCB).
 *
 * @details This function sets the priority grouping for the SCB, which determines the number of bits allocated
 * 			for preemptive priority and subpriority in the interrupt priority level.
 *
 * @note Changing the priority grouping affects the allocation of priority levels for interrupts.
 *       It is recommended to set the priority grouping early in the system initialization.
 */
void MSCB_voidSetPriorityGrouping(void);


/**
 * @brief Get the current priority grouping for the System Control Block (SCB).
 *
 * @details The priority grouping determines the number of bits allocated for preemptive priority and subpriority
 *          in the interrupt priority level. The returned value can be used for configuring interrupt priorities
 *          or determining the number of priority levels available.
 *
 * @param None.
 *
 * @return The current priority grouping value.
 *         - Possible values:
 *           - SCB_PRIORITYGROUP0: 0 bits for preemptive priority, 4 bits for subpriority.
 *           - SCB_PRIORITYGROUP1: 1 bit for preemptive priority, 3 bits for subpriority.
 *           - SCB_PRIORITYGROUP2: 2 bits for preemptive priority, 2 bits for subpriority.
 *           - SCB_PRIORITYGROUP3: 3 bits for preemptive priority, 1 bit for subpriority.
 *           - SCB_PRIORITYGROUP4: 4 bits for preemptive priority, 0 bits for subpriority.
 *
 * @note The priority grouping value obtained from this function can be used for various purposes, such as
 *       configuring interrupt priorities or determining the number of priority levels available.
 */
u32 MSCB_u32GetPriorityGrouping(void);
 
#endif /* SCB_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: SCB_interface.h
 *********************************************************************************************************************/
