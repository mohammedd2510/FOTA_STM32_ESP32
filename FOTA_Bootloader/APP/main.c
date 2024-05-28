/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */


#include"main.h"
#include"bootloader.h"

BL_Status Status = BL_NACK;

int main(void)
{

	UART_voidInit(BL_HOST_COMMUNICATION_UART);
	CRC_voidInit();

	for(;;){
		Status = BL_UART_Fetch_Host_Command();
	}
}




