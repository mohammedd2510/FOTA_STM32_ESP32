/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IR_interface.h
 *        Author: Mohamed Osama
 *		   Date:  Mar 31, 2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef HAL_IR_RECEIVER_IR_INTERFACE_H_
#define HAL_IR_RECEIVER_IR_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/TIM/TIM_Lcfg.h"
#include"MCAL/EXTI/EXTI_interface.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/******************* MP3 Remote IR_CODES *******************/
#define IR_CH_PERV_BUTTON 	    0xFFA25D
#define IR_CH_BUTTON 			0xFF629D
#define IR_CH_NEXT_BUTTON	    0xFFE21D
#define IR_PREV_BUTTON			0xFF22DD
#define IR_NEXT_BUTTON			0xFF02FD
#define IR_PLAY_PAUSE_BUTTON	0xFFC23D
#define IR_VOLUME_DOWN_BUTTON	0xFFE01F
#define IR_VOLUME_UP_BUTTON		0xFFA857
#define IR_EQ_BUTTON			0xFF906F
#define IR_0_BUTTON				0xFF6897
#define IR_100_PLUS_BUTTON		0xFF9867
#define IR_200_PLUS_BUTTON		0xFFB04F
#define IR_1_BUTTON				0xFF30CF
#define IR_2_BUTTON				0xFF18E7
#define IR_3_BUTTON				0xFF7A85
#define IR_4_BUTTON				0xFF10EF
#define IR_5_BUTTON				0xFF38C7
#define IR_6_BUTTON				0xFF5AA5
#define IR_7_BUTTON				0xFF42BD
#define IR_8_BUTTON				0xFF4AB5
#define IR_9_BUTTON				0xFF52AD
/*****************************************************/

/******************* TV Remote IR_CODES *******************/
#define IR_TV_REMOTE_UP_ARROW 		0x22d9708f
#define IR_TV_REMOTE_DOWN_ARROW 	0x22d950af
#define IR_TV_REMOTE_LEFT_ARROW 	0x22d958a7
#define IR_TV_REMOTE_RIGHT_ARROW 	0x22d948b7
#define IR_TV_REMOTE_OK          	0x22d9609f
#define IR_TV_REMOTE_EXIT        	0x22d9c837
#define IR_TV_REMOTE_MENU        	0x22d9f807
#define IR_TV_REMOTE_POWER       	0x22d9d02f
#define IR_TV_REMOTE_0           	0x22d930cf
#define IR_TV_REMOTE_1           	0x22d9d827
#define IR_TV_REMOTE_2           	0x22d9f00f
#define IR_TV_REMOTE_3           	0x22d9c03f
#define IR_TV_REMOTE_4           	0x22d99867
#define IR_TV_REMOTE_5           	0x22d98877
#define IR_TV_REMOTE_6           	0x22d9807f
#define IR_TV_REMOTE_7           	0x22d9906f
#define IR_TV_REMOTE_8           	0x22d9b847
#define IR_TV_REMOTE_9           	0x22d9b04f
#define IR_TV_REMOTE_RADIO       	0x22d918e7
#define IR_TV_REMOTE_MUTE        	0x22d9e817
#define IR_TV_REMOTE_GROUP       	0x22d97887
#define IR_TV_REMOTE_INFO        	0x22d908f7
#define IR_TV_REMOTE_EPG         	0x22d910ef
#define IR_TV_REMOTE_LANG        	0x22d938c7
#define IR_TV_REMOTE_CHANNEL_UP  	0x22d9a857
#define IR_TV_REMOTE_CHANNEL_DOWN 	0x22d928d7
#define IR_TV_REMOTE_VOLUME_UP    	0x22d948b7
#define IR_TV_REMOTE_VOLUME_DOWN  	0x22d958a7
#define IR_TV_REMOTE_RED_BUTTON   	0x22d900ff
#define IR_TV_REMOTE_GREEN_BUTTON 	0x22d940bf
#define IR_TV_REMOTE_BLUE_BUTTON  	0x22d920df
#define IR_TV_REMOTE_YELLOW_BUTTON 	0x22d9a05f
#define IR_TV_REMOTE_COLOR        	0x22d96897
#define IR_TV_REMOTE_ZOOM         	0x22d9e01f
#define IR_TV_REMOTE_PAUSE        	0x22d902fd
#define IR_TV_REMOTE_P_N          	0x22d9827d

/***********************************************/


#define IR_RECEIVED_DATA_STATUS	 1
#define IR_NOT_RECEIVED_DATA_STATUS 0
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct{
	u8 IR_Port;
	u8 IR_Pin;
	u8 IR_Trigger_Mode;

}IR_Config_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void IR_voidInit (IR_Config_t *Copy_IR_Config , pCallBackNotification IR_CallbackNotification);

u8 IR_u8GetReceivedStatus(void);

u32  IR_u32GetReceivedData(void);
 
#endif /* HAL_IR_RECEIVER_IR_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: IR_interface.h
 *********************************************************************************************************************/

