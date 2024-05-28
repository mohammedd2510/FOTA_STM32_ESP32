/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TFT_program.c
 *        Author: Mohamed Osama
 *		   Date:  Apr 23, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TFT_interface.h"
#include "TFT_private.h"

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
static void TFT_GPIO_PinsInit(port_index_t port, pin_index_t pin)
{
	switch (port)
			{
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
	GPIO_voidSetPinMode(port,pin,GPIO_OUTPUT_PIN_MODE);
}

static void TFT_ResetSequence(TFT_t* TFT_Config)
{
	GPIO_voidSetPinValue(TFT_Config->TFT_RESET_Port,TFT_Config->TFT_RESET_Pin, GPIO_HIGH);
	Delay_us(100);
	GPIO_voidSetPinValue(TFT_Config->TFT_RESET_Port,TFT_Config->TFT_RESET_Pin, GPIO_LOW);
	Delay_us(1);
	GPIO_voidSetPinValue(TFT_Config->TFT_RESET_Port,TFT_Config->TFT_RESET_Pin, GPIO_HIGH);
	Delay_us(100);
	GPIO_voidSetPinValue(TFT_Config->TFT_RESET_Port,TFT_Config->TFT_RESET_Pin, GPIO_LOW);
	Delay_us(100);
	GPIO_voidSetPinValue(TFT_Config->TFT_RESET_Port,TFT_Config->TFT_RESET_Pin, GPIO_HIGH);
	Delay_ms(120);
}
static void TFT_voidSendCommand(TFT_t* TFT_Config, u8 Command)
{
	GPIO_voidSetPinValue(TFT_Config->TFT_DC_Port,TFT_Config->TFT_DC_Pin, GPIO_LOW);
	MSPI_TransmitByte(&TFT_Config->TFT_SPI_Config, Command , 1000);
}
static void TFT_voidSendData(TFT_t* TFT_Config, u8 Data){
	GPIO_voidSetPinValue(TFT_Config->TFT_DC_Port,TFT_Config->TFT_DC_Pin, GPIO_HIGH);
	MSPI_TransmitByte(&TFT_Config->TFT_SPI_Config, Data , 1000);
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void TFT_voidInit(TFT_t* TFT_Config)
{
	TFT_GPIO_PinsInit(TFT_Config->TFT_RESET_Port, TFT_Config->TFT_RESET_Pin);
	TFT_GPIO_PinsInit(TFT_Config->TFT_DC_Port, TFT_Config->TFT_DC_Pin);
	MSPI_voidInit(&TFT_Config->TFT_SPI_Config);
	TFT_ResetSequence(TFT_Config);
	TFT_voidSendCommand(TFT_Config,SLPOUT_CMD);
	Delay_ms(150);
	TFT_voidSendCommand(TFT_Config,COLMOD_CMD);
	TFT_voidSendData(TFT_Config,RGB565_COLOR_MODE);
	TFT_voidSendCommand(TFT_Config,INVON_CMD);
	TFT_voidSendCommand(TFT_Config,MADCTL_CMD);
	TFT_voidSendData(TFT_Config,TOP_TO_BOTTOM_MODE);
	TFT_FillScreen(TFT_Config,TFT_Config->TFT_InitColor);
	TFT_voidSendCommand(TFT_Config,DISPON_CMD);
	TFT_Config->TFT_Row_Loc = 0;
	TFT_Config->TFT_Col_Loc = 0;
}

void TFT_voidSetWindow(TFT_t* TFT_Config ,u8 Copy_u8X0, u8 Copy_u8X1, u8 Copy_u8Y0, u8 Copy_u8Y1)
{
    // Send Set X Addresses Command
    TFT_voidSendCommand(TFT_Config,CASET_CMD);
    TFT_voidSendData(TFT_Config,0);
    TFT_voidSendData(TFT_Config , Copy_u8X0);
    TFT_voidSendData(TFT_Config , 0);
    TFT_voidSendData(TFT_Config,Copy_u8X1);
    // Send Set Y Addresses Command
    TFT_voidSendCommand(TFT_Config,RASET_CMD);
    TFT_voidSendData(TFT_Config,0);
    TFT_voidSendData(TFT_Config,Copy_u8Y0);
    TFT_voidSendData(TFT_Config,0);
    TFT_voidSendData(TFT_Config,Copy_u8Y1);
    TFT_voidSendCommand(TFT_Config,RAM_WR_CMD);
}

void TFT_voidDisplayImagePos(TFT_t* TFT_Config,u8 Copy_u8RowStart, u8 Copy_u8RowEnd, u8 Copy_u8ColStart,u8 Copy_u8ColEnd, const u16 * Copy_pu8Image)
{
	u16 Height = (Copy_u8RowEnd - Copy_u8RowStart)+1;
	u16 Width = (Copy_u8ColEnd - Copy_u8ColStart)+1;
    TFT_voidSetWindow(TFT_Config,Copy_u8ColStart,Copy_u8ColEnd,Copy_u8RowStart,Copy_u8RowEnd);
    GPIO_voidSetPinValue(TFT_Config->TFT_DC_Port,TFT_Config->TFT_DC_Pin, GPIO_HIGH);
    MSPI_DMA_Transmit(&TFT_Config->TFT_SPI_Config, Copy_pu8Image, Height*Width*2);
}
void TFT_voidDisplayFullImage(TFT_t* TFT_Config,const u16 * Copy_pu8Image)
{
	TFT_voidSetWindow(TFT_Config,0,TFT_WIDTH-1,0,TFT_HEIGHT-1);
	GPIO_voidSetPinValue(TFT_Config->TFT_DC_Port,TFT_Config->TFT_DC_Pin, GPIO_HIGH);
	MSPI_DMA_Transmit(&TFT_Config->TFT_SPI_Config, Copy_pu8Image,TFT_WIDTH*TFT_HEIGHT*2);
}

void TFT_WriteCharPosWithBgColor(TFT_t* TFT_Config,u16 Row, u16 Col, char ch, u16 color, u16 bgcolor)
{
	u16 Local_RowCounter = ZERO_INIT;
	u16 Local_ColCounter = ZERO_INIT;
	u16 FontRowData = ZERO_INIT;
	if(Row*TFT_FONT_HEIGHT + TFT_FONT_HEIGHT > TFT_HEIGHT || Col*TFT_FONT_WIDTH + TFT_FONT_WIDTH > TFT_WIDTH)
	{
		return;
	}
	else
	{
		TFT_Config->TFT_Col_Loc = Col*TFT_FONT_WIDTH + TFT_FONT_WIDTH;
		TFT_voidSetWindow(TFT_Config, Col*TFT_FONT_WIDTH, Col*TFT_FONT_WIDTH + TFT_FONT_WIDTH - 1, Row*TFT_FONT_HEIGHT, Row*TFT_FONT_HEIGHT + TFT_FONT_HEIGHT - 1);
		for(Local_RowCounter = ZERO_INIT; Local_RowCounter < TFT_FONT_HEIGHT; Local_RowCounter++)
		{
			FontRowData = (TFT_FONT[(ch - 32)*TFT_FONT_HEIGHT + Local_RowCounter] );
			for(Local_ColCounter = ZERO_INIT; Local_ColCounter < TFT_FONT_WIDTH; Local_ColCounter++)
			{
				if((FontRowData << Local_ColCounter)& 0X8000)
				{
					TFT_voidSendData(TFT_Config, color>>8);
					TFT_voidSendData(TFT_Config,(u8)color);
				}
				else
				{
					TFT_voidSendData(TFT_Config,bgcolor>>8);
					TFT_voidSendData(TFT_Config,(u8)bgcolor);
				}
			}
		}
	}
}
void TFT_WriteStringPosWithBgColor(TFT_t* TFT_Config,u16 Row, u16 Col, char*str, u16 color, u16 bgcolor)
{
	u8 RowCounter = Row;
	u8 ColCounter = Col;
	while(*str)
	{
		if(ColCounter + TFT_FONT_WIDTH > TFT_WIDTH)
		{
			ColCounter =0;
			RowCounter++;

			if(*str == ' ')
			{
				str++;
				continue;
			}
		}
		if(RowCounter + TFT_FONT_HEIGHT > TFT_HEIGHT)
		{
			break;
		}
		TFT_WriteCharPosWithBgColor(TFT_Config,RowCounter,ColCounter,*str,color,bgcolor);
		ColCounter++;
		str++;
	}
}

void TFT_WriteCharWithBgColor(TFT_t* TFT_Config,char ch, u16 color, u16 bgcolor)
{
	u16 Local_RowCounter = ZERO_INIT;
	u16 Local_ColCounter = ZERO_INIT;
	u16 FontRowData = ZERO_INIT;
	if(TFT_Config->TFT_Row_Loc + TFT_FONT_HEIGHT > TFT_HEIGHT || TFT_Config->TFT_Col_Loc + TFT_FONT_WIDTH > TFT_WIDTH)
	{
		return;
	}
	else
	{
		TFT_voidSetWindow(TFT_Config, TFT_Config->TFT_Col_Loc, TFT_Config->TFT_Col_Loc + TFT_FONT_WIDTH - 1, TFT_Config->TFT_Row_Loc,TFT_Config->TFT_Row_Loc + TFT_FONT_HEIGHT - 1);
		TFT_Config->TFT_Col_Loc += TFT_FONT_WIDTH;
		for(Local_RowCounter = ZERO_INIT; Local_RowCounter < TFT_FONT_HEIGHT; Local_RowCounter++)
		{
			FontRowData = (TFT_FONT[(ch - 32)*TFT_FONT_HEIGHT + Local_RowCounter] );
			for(Local_ColCounter = ZERO_INIT; Local_ColCounter < TFT_FONT_WIDTH; Local_ColCounter++)
			{
				if((FontRowData << Local_ColCounter)& 0X8000)
				{
					TFT_voidSendData(TFT_Config, color>>8);
					TFT_voidSendData(TFT_Config,(u8)color);
				}
				else
				{
					TFT_voidSendData(TFT_Config,bgcolor>>8);
					TFT_voidSendData(TFT_Config,(u8)bgcolor);
				}
			}
		}
	}
}
void TFT_WriteStringWithBgColor(TFT_t* TFT_Config, char*str, u16 color, u16 bgcolor)
{
	while(*str)
		{
			if(TFT_Config->TFT_Col_Loc + TFT_FONT_WIDTH > TFT_WIDTH)
			{
				TFT_Config->TFT_Col_Loc =0;
				TFT_Config->TFT_Row_Loc+= TFT_FONT_HEIGHT;

				if(*str == ' ')
				{
					str++;
					continue;
				}
			}
			if(TFT_Config->TFT_Row_Loc + TFT_FONT_HEIGHT > TFT_HEIGHT)
			{
				break;
			}
			TFT_WriteCharWithBgColor(TFT_Config,*str,color,bgcolor);
			str++;
		}
}
void TFT_WriteCharPos(TFT_t* TFT_Config,u16 Row, u16 Col, char ch, u16 color)
{
	u16 Local_RowCounter = ZERO_INIT;
		u16 Local_ColCounter = ZERO_INIT;
		u16 FontRowData = ZERO_INIT;
		if(Row*TFT_FONT_HEIGHT + TFT_FONT_HEIGHT > TFT_HEIGHT || Col*TFT_FONT_WIDTH + TFT_FONT_WIDTH > TFT_WIDTH)
		{
			return;
		}
		else
		{
			TFT_Config->TFT_Col_Loc = Col + TFT_FONT_WIDTH;
			TFT_voidSetWindow(TFT_Config, Col*TFT_FONT_WIDTH, Col*TFT_FONT_WIDTH + TFT_FONT_WIDTH - 1, Row*TFT_FONT_HEIGHT, Row*TFT_FONT_HEIGHT + TFT_FONT_HEIGHT - 1);
			for(Local_RowCounter = ZERO_INIT; Local_RowCounter < TFT_FONT_HEIGHT; Local_RowCounter++)
			{
				FontRowData = (TFT_FONT[(ch - 32)*TFT_FONT_HEIGHT + Local_RowCounter] );
				for(Local_ColCounter = ZERO_INIT; Local_ColCounter < TFT_FONT_WIDTH; Local_ColCounter++)
				{
					if((FontRowData << Local_ColCounter)& 0X8000)
					{
						TFT_voidSendData(TFT_Config, color>>8);
						TFT_voidSendData(TFT_Config,(u8)color);
					}
					else
					{
						TFT_voidSendData(TFT_Config,TFT_Config->TFT_InitColor>>8);
						TFT_voidSendData(TFT_Config,(u8)TFT_Config->TFT_InitColor);
					}
				}
			}
		}
}
void TFT_WriteStringPos(TFT_t* TFT_Config,u16 Row, u16 Col, char*str, u16 color)
{
	u8 RowCounter = Row;
	u8 ColCounter = Col;
	while(*str)
	{
		if(ColCounter + TFT_FONT_WIDTH > TFT_WIDTH)
		{
			ColCounter =0;
			RowCounter++;
			if(*str == ' ')
			{
				str++;
				continue;
			}
		}
		if(RowCounter + TFT_FONT_HEIGHT > TFT_HEIGHT)
		{
			break;
		}
		TFT_WriteCharPos(TFT_Config,RowCounter,ColCounter,*str,color);
		ColCounter++;
		str++;
	}
}
void TFT_WriteChar(TFT_t* TFT_Config,char ch, u16 color)
{
	u16 Local_RowCounter = ZERO_INIT;
	u16 Local_ColCounter = ZERO_INIT;
	u16 FontRowData = ZERO_INIT;
	if(TFT_Config->TFT_Row_Loc + TFT_FONT_HEIGHT > TFT_HEIGHT || TFT_Config->TFT_Col_Loc + TFT_FONT_WIDTH > TFT_WIDTH)
	{
		return;
	}
	else
	{
		TFT_voidSetWindow(TFT_Config, TFT_Config->TFT_Col_Loc, TFT_Config->TFT_Col_Loc + TFT_FONT_WIDTH - 1, TFT_Config->TFT_Row_Loc,TFT_Config->TFT_Row_Loc + TFT_FONT_HEIGHT - 1);
		TFT_Config->TFT_Col_Loc += TFT_FONT_WIDTH;
		for(Local_RowCounter = ZERO_INIT; Local_RowCounter < TFT_FONT_HEIGHT; Local_RowCounter++)
		{
			FontRowData = (TFT_FONT[(ch - 32)*TFT_FONT_HEIGHT + Local_RowCounter] );
			for(Local_ColCounter = ZERO_INIT; Local_ColCounter < TFT_FONT_WIDTH; Local_ColCounter++)
			{
				if((FontRowData << Local_ColCounter)& 0X8000)
				{
					TFT_voidSendData(TFT_Config, color>>8);
					TFT_voidSendData(TFT_Config,(u8)color);
				}
				else
				{
					TFT_voidSendData(TFT_Config,TFT_Config->TFT_InitColor>>8);
					TFT_voidSendData(TFT_Config,(u8)TFT_Config->TFT_InitColor);
				}
			}
		}
	}
}
void TFT_WriteString(TFT_t* TFT_Config, char*str, u16 color)
{
	while(*str)
	{
		if(TFT_Config->TFT_Col_Loc + TFT_FONT_WIDTH > TFT_WIDTH)
		{
			TFT_Config->TFT_Col_Loc =0;
			TFT_Config->TFT_Row_Loc+= TFT_FONT_HEIGHT;
			if(*str == ' ')
			{
				str++;
				continue;
			}
		}
		if(TFT_Config->TFT_Row_Loc + TFT_FONT_HEIGHT > TFT_HEIGHT)
		{
			break;
		}
		TFT_WriteChar(TFT_Config,*str,color);
		str++;
	}
}

void TFT_FillScreen(TFT_t* TFT_Config, u16 color)
{
	u16 Local_RowCounter = ZERO_INIT;
	u16 Local_ColCounter = ZERO_INIT;
	u8 color_arr[2]={color>>8,(u8)color};
	TFT_voidSetWindow(TFT_Config,0,TFT_WIDTH-1,0,TFT_HEIGHT-1);
	GPIO_voidSetPinValue(TFT_Config->TFT_DC_Port,TFT_Config->TFT_DC_Pin, GPIO_HIGH);
	for(Local_RowCounter = ZERO_INIT; Local_RowCounter < TFT_HEIGHT; Local_RowCounter++)
	{
		for(Local_ColCounter = ZERO_INIT; Local_ColCounter < TFT_WIDTH; Local_ColCounter++)
		{
			MSPI_DMA_Transmit(&TFT_Config->TFT_SPI_Config, color_arr,2);
		}
	}
}

void TFT_ClearScreen(TFT_t* TFT_Config)
{
	TFT_Config->TFT_Col_Loc = ZERO_INIT;
	TFT_Config->TFT_Row_Loc = ZERO_INIT;
	TFT_FillScreen(TFT_Config, TFT_Config->TFT_InitColor);
}

void TFT_SetCursor(TFT_t* TFT_Config , u8 Row, u8 Col){
	TFT_Config->TFT_Row_Loc = Row * TFT_FONT_HEIGHT;
	TFT_Config->TFT_Col_Loc = Col * TFT_FONT_WIDTH;
}
/**********************************************************************************************************************
 *  END OF FILE: TFT_program.c
 *********************************************************************************************************************/
