// Lower Layer Inclusion

// Self Layer Inclusion

// Self Files Inclusion
#include"RCC_config.h"
#include"RCC_interface.h"
#include"RCC_private.h"
#include "MCAL/FPEC/FPEC_private.h"
/******** Local Functions Declaration **********/
static void RCC_void_HSI_Init(void);
static void RCC_void_HSE_Init(void);
static void RCC_void_PLL_Init(void);
static void RCC_void_AHB1Prescaler_Init(void);
static void RCC_void_APB1Prescaler_Init(void);
static void RCC_void_APB2Prescaler_Init(void);
/************************************************/

/******* Local Functions Implementation ********/
static void RCC_void_HSI_Init(void)
{
    SET_BIT(RCC_CR,RCC_CR_HSION_Pos);  // Enable HSI
    CLR_BIT(RCC_CR,RCC_CR_HSEON_Pos); // Disable HSE  
    CLR_BIT(RCC_CR,RCC_CR_PLLON_Pos); // Disable PLL
    // Polling (Busy Wait)
    while (GET_BIT(RCC_CR,RCC_CR_HSIRDY_Pos) == 0);
    CLR_BIT(RCC_CFGR,RCC_CFGR_SW0_Pos);
    CLR_BIT(RCC_CFGR,RCC_CFGR_SW1_Pos);    
}
static void RCC_void_HSE_Init(void)
{
    SET_BIT(RCC_CR,RCC_CR_HSEON_Pos); // Enable HSE
    CLR_BIT(RCC_CR,RCC_CR_HSION_Pos);  // Disable HSI
    CLR_BIT(RCC_CR,RCC_CR_PLLON_Pos); // Disable PLL
    while (GET_BIT(RCC_CR,RCC_CR_HSERDY_Pos) == 0);
    SET_BIT(RCC_CFGR,RCC_CFGR_SW0_Pos);
    CLR_BIT(RCC_CFGR,RCC_CFGR_SW1_Pos);
}
static void RCC_void_PLL_Init(void)
{
    /**Must Disable PLL & PLLI2S FIRST**/
    CLR_BIT(RCC_CR,RCC_CR_PLLON_Pos);
    CLR_BIT(RCC_CR,RCC_CR_PLLI2SON_Pos);
    /**RCC_PLLN_CFG**/
    RCC_PLLCFGR &=~(RCC_PLLN_MASK);
    RCC_PLLCFGR |=(RCC_PLLN_VALUE<<RCC_PLLCFGR_PLLN_Pos);
    /** RCC_PLLM_CFG**/
    RCC_PLLCFGR &=~(RCC_PLLM_MASK);
    RCC_PLLCFGR |=(RCC_PLLM_VALUE<<RCC_PLLCFGR_PLLM0_Pos);
    /** RCC_PLLP_CFG**/
    RCC_PLLCFGR &=~(RCC_PLLP_MASK);
    RCC_PLLCFGR |= RCC_PLLP_VALUE;
    /* Enabling RCC_PLL_CLK */
    #if RCC_CLK_PLL_SRC == RCC_CLK_HSI
        CLR_BIT(RCC_PLLCFGR,RCC_PLLCFGR_PLLSRC_Pos);
    #elif RCC_CLK_PLL_SRC == RCC_CLK_HSE
        SET_BIT(RCC_PLLCFGR,RCC_PLLCFGR_PLLSRC_Pos);
    #else
    #endif
    SET_BIT(RCC_CR,RCC_CR_HSEON_Pos); // Disable HSE
    SET_BIT(RCC_CR,RCC_CR_PLLON_Pos); // Enable PLL
    FPEC->ACR = 0x02;
    CLR_BIT(RCC_CFGR,RCC_CFGR_SW0_Pos);
    SET_BIT(RCC_CFGR,RCC_CFGR_SW1_Pos); 
}
static void RCC_void_AHB1Prescaler_Init(void)
{
    #if   RCC_AHB_PRESCALER == RCC_AHB_DIV_1
        RCC_CFGR &= ~(RCC_AHB_PRESCALER_MASK);
        RCC_CFGR |= RCC_AHB_DIV_1;
    #elif RCC_AHB_PRESCALER == RCC_AHB_DIV_2
        RCC_CFGR &= ~(RCC_AHB_PRESCALER_MASK);
        RCC_CFGR |= RCC_AHB_DIV_2;
    #elif RCC_AHB_PRESCALER == RCC_AHB_DIV_4
        RCC_CFGR &= ~(RCC_AHB_PRESCALER_MASK);
        RCC_CFGR |= RCC_AHB_DIV_4;
    #elif RCC_AHB_PRESCALER == RCC_AHB_DIV_8
        RCC_CFGR &= ~(RCC_AHB_PRESCALER_MASK);
        RCC_CFGR |= RCC_AHB_DIV_8;
    #elif RCC_AHB_PRESCALER == RCC_AHB_DIV_16
        RCC_CFGR &= ~(RCC_AHB_PRESCALER_MASK);
        RCC_CFGR |= RCC_AHB_DIV_16;
    #elif RCC_AHB_PRESCALER == RCC_AHB_DIV_64
        RCC_CFGR &= ~(RCC_AHB_PRESCALER_MASK);
        RCC_CFGR |= RCC_AHB_DIV_64;
    #elif RCC_AHB_PRESCALER == RCC_AHB_DIV_128
        RCC_CFGR &= ~(RCC_AHB_PRESCALER_MASK);
        RCC_CFGR |= RCC_AHB_DIV_128;
    #elif RCC_AHB_PRESCALER == RCC_AHB_DIV_256
        RCC_CFGR &= ~(RCC_AHB_PRESCALER_MASK);
        RCC_CFGR |= RCC_AHB_DIV_256;
    #elif RCC_AHB_PRESCALER == RCC_AHB_DIV_512
        RCC_CFGR &= ~(RCC_AHB_PRESCALER_MASK);
        RCC_CFGR |= RCC_AHB_DIV_512;
    #endif
}
static void RCC_void_APB1Prescaler_Init(void)
{
    #if RCC_APB1_PRESCALER == RCC_APB1_DIV_1
        RCC_CFGR &= ~(RCC_APB1_PRESCALER_MASK);
        RCC_CFGR |= RCC_APB1_DIV_1;
    #elif RCC_APB1_PRESCALER == RCC_APB1_DIV_2
        RCC_CFGR &= ~(RCC_APB1_PRESCALER_MASK);
        RCC_CFGR |= RCC_APB1_DIV_2;
    #elif RCC_APB1_PRESCALER == RCC_APB1_DIV_4
        RCC_CFGR &= ~(RCC_APB1_PRESCALER_MASK);
        RCC_CFGR |= RCC_APB1_DIV_4;
    #elif RCC_APB1_PRESCALER == RCC_APB1_DIV_8
        RCC_CFGR &= ~(RCC_APB1_PRESCALER_MASK);
        RCC_CFGR |= RCC_APB1_DIV_8;
    #elif RCC_APB1_PRESCALER == RCC_APB1_DIV_16
        RCC_CFGR &= ~(RCC_APB1_PRESCALER_MASK);
        RCC_CFGR |= RCC_APB1_DIV_16;
    #endif
}
static void RCC_void_APB2Prescaler_Init(void)
{
    #if (RCC_APB2_PRESCALER == RCC_APB2_DIV_1)
        RCC_CFGR &= ~(RCC_APB2_PRESCALER_MASK);
        RCC_CFGR |= RCC_APB2_DIV_1;
    #elif (RCC_APB2_PRESCALER == RCC_APB2_DIV_2)
        RCC_CFGR &= ~(RCC_APB2_PRESCALER_MASK);
        RCC_CFGR |= RCC_APB2_DIV_2;
    #elif (RCC_APB2_PRESCALER == RCC_APB2_DIV_4)
        RCC_CFGR &= ~(RCC_APB2_PRESCALER_MASK);
        RCC_CFGR |= RCC_APB2_DIV_4;
    #elif (RCC_APB2_PRESCALER == RCC_APB2_DIV_8)
        RCC_CFGR &= ~(RCC_APB2_PRESCALER_MASK);
        RCC_CFGR |= RCC_APB2_DIV_8;
    #elif (RCC_APB2_PRESCALER == RCC_APB2_DIV_16)
        RCC_CFGR &= ~(RCC_APB2_PRESCALER_MASK);
        RCC_CFGR |= RCC_APB2_DIV_16;
    #endif
}
/**********************************************  */
void RCC_voidInit(void)
{
    RCC_void_AHB1Prescaler_Init();
    RCC_void_APB1Prescaler_Init();
    RCC_void_APB2Prescaler_Init();
    #if RCC_CLOCK_SOURCE == RCC_CLK_HSI
        RCC_void_HSI_Init();        
    #elif RCC_CLOCK_SOURCE == RCC_CLK_HSE
        RCC_void_HSE_Init();
    #elif RCC_CLOCK_SOURCE == RCC_CLK_PLL
        RCC_void_PLL_Init();
    #else
        #error "RCC_ClOCK_SOURCE_Configuration_Error"
    #endif
}
void RCC_voidEnableClockSource(u8 Copy_u8ClockSoucre)
{
    if(Copy_u8ClockSoucre == RCC_HSI)
    {
        SET_BIT(RCC_CR,RCC_CR_HSION_Pos);  // Enable HSI
    }
    else if(Copy_u8ClockSoucre == RCC_HSE)
    {
        SET_BIT(RCC_CR,RCC_CR_HSEON_Pos); // Enable HSE
    }
    else if(Copy_u8ClockSoucre == RCC_PLL)
    {
        SET_BIT(RCC_CR,RCC_CR_PLLON_Pos); // Enable PLL
    }
    else
    {
        // Error
    }
}
void RCC_voidDisableClockSource(u8 Copy_u8ClockSoucre)
{
    if(Copy_u8ClockSoucre == RCC_HSI)
    {
        CLR_BIT(RCC_CR,RCC_CR_HSION_Pos);
    }
    else if(Copy_u8ClockSoucre == RCC_HSE)
    {
        CLR_BIT(RCC_CR,RCC_CR_HSEON_Pos);
    }
    else if(Copy_u8ClockSoucre == RCC_PLL)
    {
        CLR_BIT(RCC_CR,RCC_CR_PLLON_Pos);
    }
    else
    {
        // Error
    }
}
void RCC_voidEnablePeripheralClock (u8 Copy_u8BusName, u8 Copy_u8PeripheralName){
    switch (Copy_u8BusName)
    {
        case RCC_AHB:
        /* code */
        SET_BIT(RCC_AHB1ENR,Copy_u8PeripheralName);
        break;
        case RCC_APB1:
        /* code */
        SET_BIT(RCC_APB1ENR,Copy_u8PeripheralName);
        break;
        case RCC_APB2:
        SET_BIT(RCC_APB2ENR,Copy_u8PeripheralName);
        /* code */
        break;  
    default:
        // Error
        break;
    }
}
void RCC_voidDisablePeripheralClock (u8 Copy_u8BusName, u8 Copy_u8PeripheralName)
{
    switch (Copy_u8BusName)
    {
        case RCC_AHB:
        /* code */
        CLR_BIT(RCC_AHB1ENR,Copy_u8PeripheralName);
        break;
        case RCC_APB1:
        /* code */
        CLR_BIT(RCC_APB1ENR,Copy_u8PeripheralName);
        break;
        case RCC_APB2:
        CLR_BIT(RCC_APB2ENR,Copy_u8PeripheralName);
        /* code */
        break;  
    default:
        // Error
        break;
    }
}
