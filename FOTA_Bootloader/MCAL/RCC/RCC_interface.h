#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#include"LIB/BIT_MATH.h"
#include"LIB/STD_TYPES.h"

#define RCC_HSI 0
#define RCC_HSE 1
#define RCC_PLL 2

#define RCC_AHB  0
#define RCC_APB1 1
#define RCC_APB2 2

#define RCC_AHB_GPIOAEN   0
#define RCC_AHB_GPIOBEN   1
#define RCC_AHB_GPIOCEN   2
#define RCC_AHB_GPIODEN   3
#define RCC_AHB_GPIOEEN   4
#define RCC_AHB_GPIOHEN   7
#define RCC_AHB_CRCEN     12
#define RCC_AHB_DMA1EN    21
#define RCC_AHB_DMA2EN    22

#define RCC_APB1_TIM2EN    0
#define RCC_APB1_TIM3EN    1
#define RCC_APB1_TIM4EN    2
#define RCC_APB1_TIM5EN    3
#define RCC_APB1_WWDGEN    11
#define RCC_APB1_SPI2EN    14
#define RCC_APB1_SPI3EN    15
#define RCC_APB1_USART2EN  17
#define RCC_APB1_I2C1EN    21
#define RCC_APB1_I2C2EN    22
#define RCC_APB1_I2C3EN    23
#define RCC_APB1_PWREN     28

#define RCC_APB2_TIM1EN      0
#define RCC_APB2_USART1EN    4
#define RCC_APB2_USART6EN    5
#define RCC_APB2_ADC1EN      8
#define RCC_APB2_SDIOEN      11
#define RCC_APB2_SPI1EN      12
#define RCC_APB2_SPI4EN      13
#define RCC_APB2_SYSCFGEN    14
#define RCC_APB2_TIM9EN      16
#define RCC_APB2_TIM10EN     17
#define RCC_APB2_TIM11EN     18

void RCC_voidEnableClockSource(u8 Copy_u8ClockSoucre);
void RCC_voidDisableClockSource(u8 Copy_u8ClockSoucre);
void RCC_voidInit(void);
void RCC_voidEnablePeripheralClock (u8 Copy_u8BusName, u8 Copy_u8PeripheralName);
void RCC_voidDisablePeripheralClock (u8 Copy_u8BusName, u8 Copy_u8PeripheralName);

#endif
