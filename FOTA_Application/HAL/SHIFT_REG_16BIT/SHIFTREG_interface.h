/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SHIFTREG_interface.h
 *        Author: Mohamed Osama
 *		   Date:  Apr 18, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef HAL_SHIFT_REG_16BIT_SHIFTREG_INTERFACE_H_
#define HAL_SHIFT_REG_16BIT_SHIFTREG_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "MCAL/GPIO/GPIO_interface.h"
#include "LIB/Delay.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define SHIFTREG_PIN_SET 0x01
#define SHIFTREG_PIN_CLR 0x00

#define SHIFT_REG_Q0	0
#define SHIFT_REG_Q1	1
#define SHIFT_REG_Q2	2
#define SHIFT_REG_Q3	3
#define SHIFT_REG_Q4	4
#define SHIFT_REG_Q5	5
#define SHIFT_REG_Q6	6
#define SHIFT_REG_Q7	7
#define SHIFT_REG_Q8	8
#define SHIFT_REG_Q9	9
#define SHIFT_REG_Q10	10
#define SHIFT_REG_Q11	11
#define SHIFT_REG_Q12	12
#define SHIFT_REG_Q13	13
#define SHIFT_REG_Q14	14
#define SHIFT_REG_Q15	15

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{

	u16 ShiftReg_Data;
	port_index_t ShiftReg_DataSerial_Port;
	pin_index_t  ShiftReg_DataSerial_Pin;
	port_index_t ShiftReg_ShiftClk_Port;
	pin_index_t  ShiftReg_ShiftClk_Pin;
	port_index_t ShiftReg_StorageClk_Port;
	pin_index_t  ShiftReg_StorageClk_Pin;
}SHIFTREG_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void SHIFTREG_voidInit(SHIFTREG_t *ptrSHIFTREG);

void SHIFTREG_voidSetBufferData(SHIFTREG_t *ptrSHIFTREG,u16 Copy_u16BufferData);

void SHIFTREG_voidClearBuffer(SHIFTREG_t *ptrSHIFTREG);

void SHIFTREG_voidLatchData(SHIFTREG_t *ptrSHIFTREG);

#endif /* HAL_SHIFT_REG_16BIT_SHIFTREG_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: SHIFTREG_interface.h
 *********************************************************************************************************************/

