/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SCB_program.c
 *        Author: Mohamed Osama
 *		   Date:  Mar 15, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "SCB_private.h"
#include "SCB_interface.h"
#include "SCB_config.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**
 * @brief Set the priority grouping for the System Control Block (SCB).
 *
 * @details This function sets the priority grouping for the SCB, which determines the number of bits allocated
 * 			for preemptive priority and subpriority in the interrupt priority level.
 *
 * @param PriorityGroup The priority grouping value to be set. It should be one of the following macros:
 *                      - SCB_PRIORITYGROUP_0: 0 bits for preemptive priority,  4 bits for subpriority
 *                      - SCB_PRIORITYGROUP_1: 1 bit for  preemptive priority,  3 bits for subpriority
 *                      - SCB_PRIORITYGROUP_2: 2 bits for preemptive priority,  2 bits for subpriority
 *                      - SCB_PRIORITYGROUP_3: 3 bits for preemptive priority,  1 bit for subpriority
 *                      - SCB_PRIORITYGROUP_4: 4 bits for preemptive priority,  0 bits for subpriority
 *
 * @note Changing the priority grouping affects the allocation of priority levels for interrupts.
 *       It is recommended to set the priority grouping early in the system initialization.
 */
void MSCB_voidSetPriorityGrouping()
{
	u32 Register_Value = 0;
	u32 PriorityGroupTemp= (u32)SCB_PRIORITY_GROUP & (u32)0x07;
	Register_Value = SCB->AIRCR ;
	Register_Value &= ~(SCB_AIRCR_PRIGROUP_Msk | SCB_AIRCR_VECTKEY_Msk);
	Register_Value |= ((u32)0x5FA << SCB_AIRCR_VECTKEY_POS) | (PriorityGroupTemp << SCB_AIRCR_PRIGROUP_POS);
	SCB->AIRCR = Register_Value ;
}

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
u32 MSCB_u32GetPriorityGrouping(void)
{
	u32 Register_Value = 0;
	Register_Value = SCB->AIRCR ;
	Register_Value &= SCB_AIRCR_PRIGROUP_Msk;
	Register_Value >>= SCB_AIRCR_PRIGROUP_POS;
	return Register_Value;
}


/**********************************************************************************************************************
 *  END OF FILE: SCB_program.c
 *********************************************************************************************************************/
