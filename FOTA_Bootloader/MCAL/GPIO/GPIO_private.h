/*********************************************
 * Author:				Mohamed Osama
 * Creation Data:		29 Feb, 2024
 * Version:				v1.0
 * Compiler:			GNU ARM-GCC
 * Controller:			STM32F401CCU6
 * Layer:				MCAL
 ********************************************/
/*********************************************
 * Version	    Date			 Author            Description
 *  v1.0	  29 Feb, 2024	   Mohamed Osama      Initial Creation
 *********************************************/
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#define GPIOA_BASE_ADDRESS (0x40020000)
#define GPIOB_BASE_ADDRESS (0x40020400)
#define GPIOC_BASE_ADDRESS (0x40020800)

/*********************************GPIOA Registers******************************/
#define GPIOA_MODER (*((volatile u32 *)(GPIOA_BASE_ADDRESS + 0X00)))
#define GPIOA_OTYPER (*((volatile u32 *)(GPIOA_BASE_ADDRESS + 0X04)))
#define GPIOA_OSPEEDR (*((volatile u32 *)(GPIOA_BASE_ADDRESS + 0X08)))
#define GPIOA_PUPDR (*((volatile u32 *)(GPIOA_BASE_ADDRESS + 0X0C)))
#define GPIOA_IDR (*((volatile u32 *)(GPIOA_BASE_ADDRESS + 0X10)))
#define GPIOA_ODR (*((volatile u32 *)(GPIOA_BASE_ADDRESS + 0X14)))
#define GPIOA_BSRR (*((volatile u32 *)(GPIOA_BASE_ADDRESS + 0X18)))
#define GPIOA_LCKR (*((volatile u32 *)(GPIOA_BASE_ADDRESS + 0X1C)))
#define GPIOA_AFRL (*((volatile u32 *)(GPIOA_BASE_ADDRESS + 0X20)))
#define GPIOA_AFRH (*((volatile u32 *)(GPIOA_BASE_ADDRESS + 0X24)))

/*********************************GPIOB Registers******************************/
#define GPIOB_MODER (*((volatile u32 *)(GPIOB_BASE_ADDRESS + 0X00)))
#define GPIOB_OTYPER (*((volatile u32 *)(GPIOB_BASE_ADDRESS + 0X04)))
#define GPIOB_OSPEEDR (*((volatile u32 *)(GPIOB_BASE_ADDRESS + 0X08)))
#define GPIOB_PUPDR (*((volatile u32 *)(GPIOB_BASE_ADDRESS + 0X0C)))
#define GPIOB_IDR (*((volatile u32 *)(GPIOB_BASE_ADDRESS + 0X10)))
#define GPIOB_ODR (*((volatile u32 *)(GPIOB_BASE_ADDRESS + 0X14)))
#define GPIOB_BSRR (*((volatile u32 *)(GPIOB_BASE_ADDRESS + 0X18)))
#define GPIOB_LCKR (*((volatile u32 *)(GPIOB_BASE_ADDRESS + 0X1C)))
#define GPIOB_AFRL (*((volatile u32 *)(GPIOB_BASE_ADDRESS + 0X20)))
#define GPIOB_AFRH (*((volatile u32 *)(GPIOB_BASE_ADDRESS + 0X24)))

/*********************************GPIOC Registers******************************/
#define GPIOC_MODER (*((volatile u32 *)(GPIOC_BASE_ADDRESS + 0X00)))
#define GPIOC_OTYPER (*((volatile u32 *)(GPIOC_BASE_ADDRESS + 0X04)))
#define GPIOC_OSPEEDR (*((volatile u32 *)(GPIOC_BASE_ADDRESS + 0X08)))
#define GPIOC_PUPDR (*((volatile u32 *)(GPIOC_BASE_ADDRESS + 0X0C)))
#define GPIOC_IDR (*((volatile u32 *)(GPIOC_BASE_ADDRESS + 0X10)))
#define GPIOC_ODR (*((volatile u32 *)(GPIOC_BASE_ADDRESS + 0X14)))
#define GPIOC_BSRR (*((volatile u32 *)(GPIOC_BASE_ADDRESS + 0X18)))
#define GPIOC_LCKR (*((volatile u32 *)(GPIOC_BASE_ADDRESS + 0X1C)))
#define GPIOC_AFRL (*((volatile u32 *)(GPIOC_BASE_ADDRESS + 0X20)))
#define GPIOC_AFRH (*((volatile u32 *)(GPIOC_BASE_ADDRESS + 0X24)))

/**********Clear Masks********/
#define GPIO_MODER_CLEAR_MASK (0X03)
#define GPIO_MODER_PIN_BITS (0x02)

#define GPIO_OTYPER_CLEAR_MASK (0X01)

#define GPIO_OSPEEDR_CLEAR_MASK (0X03)
#define GPIO_OSPEEDR_PIN_BITS (0x02)

#define GPIO_AF_CLEAR_MASK (0X0F)
#define GPIO_AF_PIN_BITS (0x04)

#define GPIO_SET_BIT_POS 0x01
#define GPIO_RESET_BIT_POS 0X01 << 16

#define GPIO_PUPDR_CLEAR_MASK (0X03)
#define GPIO_PUPDR_PIN_BITS (0x02)

#define GPIO_LCKK_MASK (1 << 16)

#define GPIO_ODR_HIGH 0XFFFF
#define GPIO_ODR_LOW 0XFFFF

#define GPIO_PORT_LOCKED 0XFFFF

#endif
