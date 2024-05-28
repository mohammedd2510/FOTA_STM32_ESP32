#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

#define RCC_BASE_ADDRESS    (0x40023800)
#define RCC_CR              (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X00)))
#define RCC_PLLCFGR         (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X04)))
#define RCC_CFGR            (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X08)))
#define RCC_CIR             (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X0C)))
#define RCC_AHB1RSTR        (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X10)))
#define RCC_AHB2RSTR        (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X14)))
#define RCC_APB1RSTR        (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X20)))
#define RCC_APB2RSTR        (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X24)))
#define RCC_AHB1ENR         (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X30)))
#define RCC_AHB2ENR         (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X34)))
#define RCC_APB1ENR         (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X40)))
#define RCC_APB2ENR         (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X44)))
#define RCC_AHB1LPENR       (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X50)))
#define RCC_AHB2LPENR       (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X54)))
#define RCC_APB1LPENR       (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X60)))
#define RCC_APB2LPENR       (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X64)))
#define RCC_BDCR            (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X70)))
#define RCC_CSR             (*((volatile u32 *)(RCC_BASE_ADDRESS + 0X74)))
#define RCC_SSCGR           (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x80)))
#define RCC_PLLI2SCFGR      (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x84)))
#define RCC_DCKCFGR         (*((volatile u32 *)(RCC_BASE_ADDRESS + 0x8C)))

#define RCC_CR_PLLI2SRDY_Pos   27
#define RCC_CR_PLLI2SON_Pos    26
#define RCC_CR_PLLRDY_Pos      25
#define RCC_CR_PLLON_Pos       24
#define RCC_CR_CSSON_Pos       19
#define RCC_CR_HSEBYP_Pos      18
#define RCC_CR_HSERDY_Pos      17
#define RCC_CR_HSEON_Pos       16
#define RCC_CR_HSICAL_Pos      8
#define RCC_CR_HSITRIM_Pos     3
#define RCC_CR_HSIRDY_Pos      1
#define RCC_CR_HSION_Pos       0

#define RCC_CFGR_SW1_Pos           1
#define RCC_CFGR_SW0_Pos           0

#define RCC_PLLCFGR_PLLQ3_Pos     27
#define RCC_PLLCFGR_PLLQ2_Pos     26
#define RCC_PLLCFGR_PLLQ1_Pos     25
#define RCC_PLLCFGR_PLLQ0_Pos     24
#define RCC_PLLCFGR_PLLSRC_Pos    22
#define RCC_PLLCFGR_PLLP1_Pos     17
#define RCC_PLLCFGR_PLLP0_Pos     16
#define RCC_PLLCFGR_PLLN_Pos      6
#define RCC_PLLCFGR_PLLM5_Pos     5
#define RCC_PLLCFGR_PLLM4_Pos     4
#define RCC_PLLCFGR_PLLM3_Pos     3
#define RCC_PLLCFGR_PLLM2_Pos     2
#define RCC_PLLCFGR_PLLM1_Pos     1
#define RCC_PLLCFGR_PLLM0_Pos     0

#define RCC_AHB_DIV_1     (0X00 << 4)
#define RCC_AHB_DIV_2     (0X08 << 4)
#define RCC_AHB_DIV_4     (0X09 << 4)
#define RCC_AHB_DIV_8     (0X0A << 4)
#define RCC_AHB_DIV_16    (0X0B << 4)
#define RCC_AHB_DIV_64    (0X0C << 4)
#define RCC_AHB_DIV_128   (0X0D << 4)
#define RCC_AHB_DIV_256   (0X0E << 4)
#define RCC_AHB_DIV_512   (0X0F << 4)

#define RCC_APB1_DIV_1     (0X00 << 10)
#define RCC_APB1_DIV_2     (0X04 << 10)
#define RCC_APB1_DIV_4     (0X05 << 10)
#define RCC_APB1_DIV_8     (0X06 << 10)
#define RCC_APB1_DIV_16    (0X07 << 10)


#define RCC_APB2_DIV_1     (0X00 << 13)
#define RCC_APB2_DIV_2     (0X04 << 13)
#define RCC_APB2_DIV_4     (0X05 << 13)
#define RCC_APB2_DIV_8     (0X06 << 13)
#define RCC_APB2_DIV_16    (0X07 << 13)

#define RCC_AHB_PRESCALER_MASK (0x0F<<4)
#define RCC_APB1_PRESCALER_MASK (0x07<<10)
#define RCC_APB2_PRESCALER_MASK (0x07<<13)

#define RCC_CLK_HSI 0
#define RCC_CLK_HSE 1
#define RCC_CLK_PLL 2

#define RCC_PLLN_MASK (0x1FF<<6)
#define RCC_PLLM_MASK (0x3F<<0)
#define RCC_PLLP_MASK (0x03<<16)

#define RCC_PLLP_DIV_2     (0X00 << 16)
#define RCC_PLLP_DIV_4     (0X01 << 16)
#define RCC_PLLP_DIV_6     (0X02 << 16)
#define RCC_PLLP_DIV_8     (0X03 << 16)


#endif