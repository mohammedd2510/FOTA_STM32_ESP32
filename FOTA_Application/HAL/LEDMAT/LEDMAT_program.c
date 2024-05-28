/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  LEDMAT_program.c
 *        Author: Mohamed Osama
 *		   Date:  Mar 22, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "HAL/LEDMAT/LEDMAT_interface.h"
#include "HAL/LEDMAT/LEDMAT_private.h"
#include"LIB/Delay.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/




/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static u8 LEDMAT_Delay_Flag = LEDMAT_DELAY_NOT_COMPLETED;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
static void LEDMAT_Timer_CallBack_Handler(void)
{
	LEDMAT_Delay_Flag = LEDMAT_DELAY_COMPLETED;
}
static void voidDisableAllRows(ledmat_t* ledmat_obj)
{
	u8 Local_RowsCounter = ZERO_INIT;
	for(Local_RowsCounter = ZERO_INIT; Local_RowsCounter<LED_MATRIX_ROW_NUM; Local_RowsCounter++)
	{
#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
		GPIO_voidSetPinValue(ledmat_obj->row[Local_RowsCounter].port, ledmat_obj->row[Local_RowsCounter].pin,GPIO_LOW);
	}
#else
		CLR_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data , ledmat_obj->row[Local_RowsCounter].ShiftRegPin);
	}
		SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
#endif

}
static void voidDisableAllColumns(ledmat_t* ledmat_obj)
{
	u8 Local_ColumnsCounter = ZERO_INIT;
	for(Local_ColumnsCounter = ZERO_INIT; Local_ColumnsCounter<LED_MATRIX_COL_NUM; Local_ColumnsCounter++)
	{
#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
		GPIO_voidSetPinValue(ledmat_obj->col[Local_ColumnsCounter].port, ledmat_obj->col[Local_ColumnsCounter].pin,GPIO_HIGH);
	}
#else
		SET_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data , ledmat_obj->col[Local_ColumnsCounter].ShiftRegPin);
	}
		SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
#endif
}

static void voidUpdateScreen_WithDelay(ledmat_t* ledmat_obj, u32 time_ms)
{
	u8 Local_RowsCounter = ZERO_INIT;
	u8 Local_ColumnsCounter = ZERO_INIT;
	gpio_logic_t Local_col_pin_logic = GPIO_HIGH;
	voidDisableAllRows(ledmat_obj);
	TIM_SingleInterval(&TIM2_Cfg, time_ms*1000, LEDMAT_Timer_CallBack_Handler);
	while(LEDMAT_Delay_Flag == LEDMAT_DELAY_NOT_COMPLETED)
	{
		for(Local_RowsCounter = ZERO_INIT; Local_RowsCounter<LED_MATRIX_ROW_NUM; Local_RowsCounter++)
		{
			voidDisableAllColumns(ledmat_obj);
			#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
			GPIO_voidSetPinValue(ledmat_obj->row[Local_RowsCounter].port, ledmat_obj->row[Local_RowsCounter].pin,GPIO_HIGH);
			#else
			SET_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->row[Local_RowsCounter].ShiftRegPin);
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			#endif
			for(Local_ColumnsCounter = ZERO_INIT; Local_ColumnsCounter<LED_MATRIX_COL_NUM; Local_ColumnsCounter++)
			{
				Local_col_pin_logic= !(ledmat_obj->LedMatrix_Buffer[Local_RowsCounter]>>Local_ColumnsCounter &0x01);
				#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
				GPIO_voidSetPinValue(ledmat_obj->col[Local_ColumnsCounter].port, ledmat_obj->col[Local_ColumnsCounter].pin,Local_col_pin_logic);
				Frame_delay();
				#else
				if(Local_col_pin_logic == GPIO_HIGH){
					SET_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->col[Local_ColumnsCounter].ShiftRegPin);
				}
				else if(Local_col_pin_logic == GPIO_LOW){
					CLR_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->col[Local_ColumnsCounter].ShiftRegPin);
				}

				#endif
			}
			#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
			GPIO_voidSetPinValue(ledmat_obj->row[Local_RowsCounter].port, ledmat_obj->row[Local_RowsCounter].pin,GPIO_LOW);
			#else
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			CLR_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->row[Local_RowsCounter].ShiftRegPin);
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			#endif
		}
	}
	LEDMAT_Delay_Flag = LEDMAT_DELAY_NOT_COMPLETED;
}

static void voidUpdateScreen_WithDelay_WithStopFlag(ledmat_t* ledmat_obj, u32 time_ms , u8* StopFlag)
{
	u8 Local_RowsCounter = ZERO_INIT;
	u8 Local_ColumnsCounter = ZERO_INIT;
	gpio_logic_t Local_col_pin_logic = GPIO_HIGH;
	voidDisableAllRows(ledmat_obj);
	TIM_SingleInterval(&TIM2_Cfg, time_ms*1000, LEDMAT_Timer_CallBack_Handler);
	while(LEDMAT_Delay_Flag == LEDMAT_DELAY_NOT_COMPLETED)
	{
		for(Local_RowsCounter = ZERO_INIT; Local_RowsCounter<LED_MATRIX_ROW_NUM; Local_RowsCounter++)
		{
			voidDisableAllColumns(ledmat_obj);
			#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
			GPIO_voidSetPinValue(ledmat_obj->row[Local_RowsCounter].port, ledmat_obj->row[Local_RowsCounter].pin,GPIO_HIGH);
			#else
			SET_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->row[Local_RowsCounter].ShiftRegPin);
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			#endif
			for(Local_ColumnsCounter = ZERO_INIT; Local_ColumnsCounter<LED_MATRIX_COL_NUM; Local_ColumnsCounter++)
			{
				Local_col_pin_logic= !(ledmat_obj->LedMatrix_Buffer[Local_RowsCounter]>>Local_ColumnsCounter &0x01);
				#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
				GPIO_voidSetPinValue(ledmat_obj->col[Local_ColumnsCounter].port, ledmat_obj->col[Local_ColumnsCounter].pin,Local_col_pin_logic);
				Frame_delay();
				#else
				if(Local_col_pin_logic == GPIO_HIGH){
					SET_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->col[Local_ColumnsCounter].ShiftRegPin);
				}
				else if(Local_col_pin_logic == GPIO_LOW){
					CLR_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->col[Local_ColumnsCounter].ShiftRegPin);
				}

				#endif
			}
			#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
			GPIO_voidSetPinValue(ledmat_obj->row[Local_RowsCounter].port, ledmat_obj->row[Local_RowsCounter].pin,GPIO_LOW);
			#else
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			CLR_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->row[Local_RowsCounter].ShiftRegPin);
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			#endif
		if(*StopFlag == 1)
		{
			voidDisableAllColumns(ledmat_obj);
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			return;
		}
		}
	}
	LEDMAT_Delay_Flag = LEDMAT_DELAY_NOT_COMPLETED;
}
static void voidClearLEDMATBuffer(ledmat_t* ledmat_obj){
	memset(ledmat_obj->LedMatrix_Buffer,0,LED_MATRIX_ROW_NUM);
}
static void voidScrollLeft(ledmat_t* ledmat_obj)
{
	u8 Local_RowsCounter = ZERO_INIT;
	for(Local_RowsCounter = ZERO_INIT; Local_RowsCounter<LED_MATRIX_ROW_NUM; Local_RowsCounter++)
	{
		ledmat_obj->LedMatrix_Buffer[Local_RowsCounter] >>= 1;
	}
}
static void voidScrollRight(ledmat_t* ledmat_obj)
{
	u8 Local_RowsCounter = ZERO_INIT;
	for(Local_RowsCounter = ZERO_INIT; Local_RowsCounter<LED_MATRIX_ROW_NUM; Local_RowsCounter++)
	{
		ledmat_obj->LedMatrix_Buffer[Local_RowsCounter] <<= 1;
	}
}
static void Frame_delay(){
 u8 Local_u8DelayCounter = ZERO_INIT;
 	for(Local_u8DelayCounter=ZERO_INIT;Local_u8DelayCounter<10;Local_u8DelayCounter++);
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void HLEDMAT_voidInit(ledmat_t* ledmat_obj)
{
#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
	u8 Local_RowsCounter = ZERO_INIT;
	u8 Local_ColumnsCounter = ZERO_INIT;
	for(Local_RowsCounter = ZERO_INIT; Local_RowsCounter<LED_MATRIX_ROW_NUM; Local_RowsCounter++)
	{
		switch (ledmat_obj->row[Local_RowsCounter].port) {
		    case GPIO_PORTA:
		      RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOAEN);
		      break;
		    case GPIO_PORTB:
		      RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOBEN);
		      break;
		    case GPIO_PORTC:
		      RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOCEN);
		      break;
		    default:
		      break;
		  }
		  GPIO_voidSetPinMode(ledmat_obj->row[Local_RowsCounter].port,ledmat_obj->row[Local_RowsCounter].pin,GPIO_OUTPUT_PIN_MODE);
		  GPIO_voidSetPinOutputMode(ledmat_obj->row[Local_RowsCounter].port,ledmat_obj->row[Local_RowsCounter].pin,GPIO_OUTPUT_PIN_PUSH_PULL);
		  GPIO_voidSetPinOutputSpeed(ledmat_obj->row[Local_RowsCounter].port,ledmat_obj->row[Local_RowsCounter].pin,GPIO_OUTPUT_PIN_LOW_SPEED);
		  GPIO_voidSetPinValue(ledmat_obj->row[Local_RowsCounter].port,ledmat_obj->row[Local_RowsCounter].pin,ledmat_obj->row[Local_RowsCounter].state);
	}
	for(Local_ColumnsCounter = ZERO_INIT; Local_ColumnsCounter<LED_MATRIX_COL_NUM; Local_ColumnsCounter++)
		{
			switch (ledmat_obj->col[Local_ColumnsCounter].port) {
			    case GPIO_PORTA:
			      RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOAEN);
			      break;
			    case GPIO_PORTB:
			      RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOBEN);
			      break;
			    case GPIO_PORTC:
			      RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOCEN);
			      break;
			    default:
			      break;
			  }
			  GPIO_voidSetPinMode(ledmat_obj->col[Local_ColumnsCounter].port,ledmat_obj->col[Local_ColumnsCounter].pin,GPIO_OUTPUT_PIN_MODE);
			  GPIO_voidSetPinOutputMode(ledmat_obj->col[Local_ColumnsCounter].port,ledmat_obj->col[Local_ColumnsCounter].pin,GPIO_OUTPUT_PIN_PUSH_PULL);
			  GPIO_voidSetPinOutputSpeed(ledmat_obj->col[Local_ColumnsCounter].port,ledmat_obj->col[Local_ColumnsCounter].pin,GPIO_OUTPUT_PIN_LOW_SPEED);
			  GPIO_voidSetPinValue(ledmat_obj->col[Local_ColumnsCounter].port,ledmat_obj->col[Local_ColumnsCounter].pin,ledmat_obj->col[Local_ColumnsCounter].state);
		}
#else
SHIFTREG_voidInit(ledmat_obj->ptrShiftRegCfg);
#endif
}


void HLEDMAT_voidDisplayFrame(ledmat_t* ledmat_obj,u8* Copy_pu8FrameData)
{
	u8 Local_RowsCounter = ZERO_INIT;
	u8 Local_ColumnsCounter = ZERO_INIT;
	gpio_logic_t Local_col_pin_logic = GPIO_HIGH;
	voidDisableAllRows(ledmat_obj);
	memcpy(ledmat_obj->LedMatrix_Buffer,Copy_pu8FrameData,LED_MATRIX_COL_NUM);
	for(Local_RowsCounter = ZERO_INIT; Local_RowsCounter<LED_MATRIX_ROW_NUM; Local_RowsCounter++)
		{
			voidDisableAllColumns(ledmat_obj);
			#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
			GPIO_voidSetPinValue(ledmat_obj->row[Local_RowsCounter].port, ledmat_obj->row[Local_RowsCounter].pin,GPIO_HIGH);
			#else
			SET_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->row[Local_RowsCounter].ShiftRegPin);
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			#endif
			for(Local_ColumnsCounter = ZERO_INIT; Local_ColumnsCounter<LED_MATRIX_COL_NUM; Local_ColumnsCounter++)
				{

					Local_col_pin_logic= !(ledmat_obj->LedMatrix_Buffer[Local_RowsCounter]>>Local_ColumnsCounter &0x01);
					#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
					GPIO_voidSetPinValue(ledmat_obj->col[Local_ColumnsCounter].port, ledmat_obj->col[Local_ColumnsCounter].pin,Local_col_pin_logic);
					Frame_delay();
					#else
					if(Local_col_pin_logic == GPIO_HIGH){
						SET_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->col[Local_ColumnsCounter].ShiftRegPin);
					}
					else if(Local_col_pin_logic == GPIO_LOW){
						CLR_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->col[Local_ColumnsCounter].ShiftRegPin);
					}
					#endif
				}
			#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
			GPIO_voidSetPinValue(ledmat_obj->row[Local_RowsCounter].port, ledmat_obj->row[Local_RowsCounter].pin,GPIO_LOW);
			#else
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			CLR_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->row[Local_RowsCounter].ShiftRegPin);
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			#endif
		}
}
void HLEDMAT_voidDisplayFrameWithDelay(ledmat_t* ledmat_obj,u8* Copy_pu8FrameData , u32 time_ms)
{
	u8 Local_RowsCounter = ZERO_INIT;
	u8 Local_ColumnsCounter = ZERO_INIT;
	gpio_logic_t Local_col_pin_logic = GPIO_HIGH;
	voidDisableAllRows(ledmat_obj);
	memcpy(ledmat_obj->LedMatrix_Buffer,Copy_pu8FrameData,LED_MATRIX_COL_NUM);
	TIM_SingleInterval(&TIM2_Cfg, time_ms*1000, LEDMAT_Timer_CallBack_Handler);
	while(LEDMAT_Delay_Flag == LEDMAT_DELAY_NOT_COMPLETED)
	{
		for(Local_RowsCounter = ZERO_INIT; Local_RowsCounter<LED_MATRIX_ROW_NUM; Local_RowsCounter++)
		{
			voidDisableAllColumns(ledmat_obj);
			#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
			GPIO_voidSetPinValue(ledmat_obj->row[Local_RowsCounter].port, ledmat_obj->row[Local_RowsCounter].pin,GPIO_HIGH);
			#else
			SET_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->row[Local_RowsCounter].ShiftRegPin);
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			#endif
			for(Local_ColumnsCounter = ZERO_INIT; Local_ColumnsCounter<LED_MATRIX_COL_NUM; Local_ColumnsCounter++)
			{
				Local_col_pin_logic= !(ledmat_obj->LedMatrix_Buffer[Local_RowsCounter]>>Local_ColumnsCounter &0x01);
				#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
				GPIO_voidSetPinValue(ledmat_obj->col[Local_ColumnsCounter].port, ledmat_obj->col[Local_ColumnsCounter].pin,Local_col_pin_logic);
				Frame_delay();
				#else
				if(Local_col_pin_logic == GPIO_HIGH){
					SET_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->col[Local_ColumnsCounter].ShiftRegPin);
				}
				else if(Local_col_pin_logic == GPIO_LOW){
					CLR_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->col[Local_ColumnsCounter].ShiftRegPin);
				}
				#endif
			}
			#if LEDMAT_SHIFTREG_MODE == SHIFTREG_MODE_DISABLED
			GPIO_voidSetPinValue(ledmat_obj->row[Local_RowsCounter].port, ledmat_obj->row[Local_RowsCounter].pin,GPIO_LOW);
			#else
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			CLR_BIT(ledmat_obj->ptrShiftRegCfg->ShiftReg_Data,ledmat_obj->row[Local_RowsCounter].ShiftRegPin);
			SHIFTREG_voidLatchData(ledmat_obj->ptrShiftRegCfg);
			#endif
		}
	}
	LEDMAT_Delay_Flag = LEDMAT_DELAY_NOT_COMPLETED;
}
void HLEDMAT_voidDisplayChar(ledmat_t* ledmat_obj,u8 Copy_u8Chr)
{
 HLEDMAT_voidDisplayFrame(ledmat_obj,&Chr_font[Copy_u8Chr-FONT_START]);
}

void HLEDMAT_voidDisplayString(ledmat_t* ledmat_obj,u8* Copy_pu8Str,u32 time_ms)
{
	while(*Copy_pu8Str){
		TIM_SingleInterval(&TIM2_Cfg, time_ms*1000, LEDMAT_Timer_CallBack_Handler);
		while(LEDMAT_Delay_Flag == LEDMAT_DELAY_NOT_COMPLETED)
		{
		HLEDMAT_voidDisplayChar(ledmat_obj, *Copy_pu8Str);
		}
		LEDMAT_Delay_Flag =LEDMAT_DELAY_NOT_COMPLETED;
		Copy_pu8Str++;
	}
}
void HLEDMAT_voidDisplayScrollingString(ledmat_t* ledmat_obj,u8* Copy_pu8Str,u32 Copy_u32TimeMs)
{
	u8 Local_u8ColumnCounter = ZERO_INIT;
	u8 Local_u8RowCounter = ZERO_INIT;
	voidClearLEDMATBuffer(ledmat_obj);
	while(*Copy_pu8Str)
	{
		for (Local_u8ColumnCounter = ZERO_INIT; Local_u8ColumnCounter <LED_MATRIX_COL_NUM;Local_u8ColumnCounter++)
			{
				for (Local_u8RowCounter = ZERO_INIT;Local_u8RowCounter<LED_MATRIX_ROW_NUM;Local_u8RowCounter++)
				{
						ledmat_obj->LedMatrix_Buffer[Local_u8RowCounter] |= ((Chr_font[*Copy_pu8Str-FONT_START][Local_u8RowCounter]>>Local_u8ColumnCounter&0x01)<<7);
				}
				voidUpdateScreen_WithDelay(ledmat_obj,Copy_u32TimeMs);
				voidScrollLeft(ledmat_obj);
			}
		Copy_pu8Str++;
	}
	for(Local_u8ColumnCounter =0; Local_u8ColumnCounter<LED_MATRIX_COL_NUM;Local_u8ColumnCounter++)
	{
		voidScrollLeft(ledmat_obj);
		voidUpdateScreen_WithDelay(ledmat_obj,Copy_u32TimeMs);
	}
}
void HLEDMAT_voidDisplayScrollingString_WithStopFlag(ledmat_t* ledmat_obj,u8* Copy_pu8Str,u32 Copy_u32TimeMs , u8* StopFlag)
{
	u8 Local_u8ColumnCounter = ZERO_INIT;
	u8 Local_u8RowCounter = ZERO_INIT;
	voidClearLEDMATBuffer(ledmat_obj);
	while(*Copy_pu8Str)
	{
		for (Local_u8ColumnCounter = ZERO_INIT; Local_u8ColumnCounter <LED_MATRIX_COL_NUM;Local_u8ColumnCounter++)
			{
				for (Local_u8RowCounter = ZERO_INIT;Local_u8RowCounter<LED_MATRIX_ROW_NUM;Local_u8RowCounter++)
				{
						ledmat_obj->LedMatrix_Buffer[Local_u8RowCounter] |= ((Chr_font[*Copy_pu8Str-FONT_START][Local_u8RowCounter]>>Local_u8ColumnCounter&0x01)<<7);
				}
				voidUpdateScreen_WithDelay_WithStopFlag(ledmat_obj,Copy_u32TimeMs,StopFlag);
				if(*StopFlag == 1){
					return;
				}
				voidScrollLeft(ledmat_obj);
			}
		Copy_pu8Str++;
	}
	for(Local_u8ColumnCounter =0; Local_u8ColumnCounter<LED_MATRIX_COL_NUM;Local_u8ColumnCounter++)
	{
		voidScrollLeft(ledmat_obj);
		voidUpdateScreen_WithDelay_WithStopFlag(ledmat_obj,Copy_u32TimeMs,StopFlag);
		if(*StopFlag == 1){
							return;
						}
	}
}
void HLEDMAT_voidScrollFrameRight(ledmat_t* ledmat_obj,u32 time_ms)
{
	voidScrollRight(ledmat_obj);
	voidUpdateScreen_WithDelay(ledmat_obj, time_ms);
}

void HLEDMAT_voidScrollFrameLeft(ledmat_t* ledmat_obj,u32 time_ms)
{
	voidScrollLeft(ledmat_obj);
	voidUpdateScreen_WithDelay(ledmat_obj, time_ms);
}
/**********************************************************************************************************************
 *  END OF FILE: LEDMAT_program.c
 *********************************************************************************************************************/
