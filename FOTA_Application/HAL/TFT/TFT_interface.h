/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TFT_interface.h
 *        Author: Mohamed Osama
 *		   Date:  Apr 23, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef HAL_TFT_TFT_INTERFACE_H_
#define HAL_TFT_TFT_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "MCAL/SPI/SPI_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "TFT_Font.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define TFT_WIDTH  128
#define TFT_HEIGHT 160

// Color definitions
#define	TFT_BLACK   0x0000
#define	TFT_BLUE    0x001F
#define	TFT_RED     0xF800
#define	TFT_GREEN   0x07E0
#define TFT_CYAN    0x07FF
#define TFT_MAGENTA 0xF81F
#define TFT_YELLOW  0xFFE0
#define TFT_WHITE   0xFFFF
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
	SPI_Config_t TFT_SPI_Config;
	port_index_t TFT_RESET_Port;
	pin_index_t  TFT_RESET_Pin;
	port_index_t TFT_DC_Port;
	pin_index_t  TFT_DC_Pin;
	u8 TFT_InitColor;
	u8 TFT_Row_Loc;
	u8 TFT_Col_Loc;
}TFT_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void TFT_voidInit(TFT_t* TFT_Config);
void TFT_voidSetWindow(TFT_t* TFT_Config ,u8 Copy_u8X0, u8 Copy_u8X1, u8 Copy_u8Y0, u8 Copy_u8Y1);
void TFT_voidDisplayImagePos(TFT_t* TFT_Config,u8 Copy_u8RowStart, u8 Copy_u8RowEnd, u8 Copy_u8ColStart,u8 Copy_u8ColEnd, const u16 * Copy_pu8Image);
void TFT_voidDisplayFullImage(TFT_t* TFT_Config,const u16 * Copy_pu8Image);
void TFT_WriteCharPosWithBgColor(TFT_t* TFT_Config,u16 Row, u16 Col, char ch, u16 color, u16 bgcolor);
void TFT_WriteStringPosWithBgColor(TFT_t* TFT_Config,u16 Row, u16 Col, char*str, u16 color, u16 bgcolor);
void TFT_WriteCharWithBgColor(TFT_t* TFT_Config,char ch, u16 color, u16 bgcolor);
void TFT_WriteStringWithBgColor(TFT_t* TFT_Config, char*str, u16 color, u16 bgcolor);

void TFT_WriteCharPos(TFT_t* TFT_Config,u16 Row, u16 Col, char ch, u16 color);
void TFT_WriteStringPos(TFT_t* TFT_Config,u16 Row, u16 Col, char*str, u16 color);
void TFT_WriteChar(TFT_t* TFT_Config,char ch, u16 color);
void TFT_WriteString(TFT_t* TFT_Config, char*str, u16 color);
void TFT_FillScreen(TFT_t* TFT_Config, u16 color);

void TFT_ClearScreen(TFT_t* TFT_Config);

void TFT_SetCursor(TFT_t* TFT_Config , u8 Row, u8 Col);

#endif /* HAL_TFT_TFT_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: TFT_interface.h
 *********************************************************************************************************************/

