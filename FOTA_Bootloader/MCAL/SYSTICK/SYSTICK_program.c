// Lower Layer Inclusion

// Self Layer Inclusion

// Self Files Inclusion
#include"SYSTICK_config.h"
#include"SYSTICK_interface.h"
#include"SYSTICK_private.h"

/* Global variables*/
volatile PtrFunction SysTick_CallBack = NULL;
volatile u8 SysTick_Mode = SysTick_SingleInterval_Mode;
/********************/

void MSysTick_voidInit(void)
{
		/* Select The Processor Clock */
#if (SYSTICK_CLOCK_SOURCE == SYSTICK_AHB_DIV_1)
		SET_BIT(SysTick->CTRL,SysTick_CTRL_CLKSOURCE_Pos);
#elif (SYSTICK_CLOCK_SOURCE == SYSTICK_AHB_DIV_8)
		CLR_BIT(SysTick->CTRL,SysTick_CTRL_CLKSOURCE_Pos);
#else
#error "Invalid Clock Source"
#endif
		#if(SYSTICK_INT_CTRL == SYSTICK_ENABLE)
    /*Enable SysTick IRQ */
		SET_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Pos);
    #elif(SYSTICK_INT_CTRL == SYSTICK_DISABLE)
    /*Disable SysTick IRQ */
		CLR_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Pos);
    #endif
    #if(SYSTICK_CTRL == SYSTICK_ENABLE)
    /*Enable SysTick Counter*/
    SET_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Pos);
    #elif(SYSTICK_CTRL == SYSTICK_DISABLE)
    /* Disable SysTick Counter */
		CLR_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Pos);
    #endif
}
void MSysTick_voidDeInit(void)
{
	/* Disable SysTick Counter */
	CLR_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Pos);
	/* Reset The SysTick Reload Register */
	SysTick->LOAD = 0;
	/* Reset The SysTick Counter Value*/
	SysTick->VAL = 0;
	/*Disable SysTick IRQ */
	CLR_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Pos);
}
void MSysTick_voidSetBusyWait(u32 Copy_u32Ticks)
{
	/* Set Reload Register to SysTick Ticks */
	  SysTick->LOAD = Copy_u32Ticks;
	  SysTick->VAL = 0;
  /* Wait The COUNTFLAG Returns 1 */
	  while (GET_BIT(SysTick->CTRL,SysTick_CTRL_COUNTFLAG_Pos) == 0);
  /* Reset The SysTick Reload Register */
	SysTick->LOAD = 0;
	/* Reset The SysTick Counter Value*/
	SysTick->VAL = 0;
}
void MSysTick_voidSetIntervalSingle(u32 Copy_u32Ticks,PtrFunction CallBack_Ptr)
{
  if (CallBack_Ptr != NULL)
	{
	  /* Set Reload Register to SysTick Ticks */
	  	SysTick->LOAD = Copy_u32Ticks;
	  	SysTick->VAL = 0;
		/* Copy The User CallBack to Local ptrFunction */
		SysTick_CallBack = CallBack_Ptr;
		/* Set The SysTick Timer to Single Interval Mode */
		SysTick_Mode = SysTick_SingleInterval_Mode;
		/*Enable SysTick IRQ */
		SET_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Pos);
		/* Enable SysTick Counter */
		SET_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Pos);
	}
	else { /* Nothing */}
}

void MSysTick_voidSetIntervalPeriodic(u32 Copy_u32Ticks,PtrFunction CallBack_Ptr)
{
  if (CallBack_Ptr != NULL)
	{
	  	   /* Set Reload Register to SysTick Ticks */
	  	  SysTick->LOAD = Copy_u32Ticks;
	  	  SysTick->VAL = 0;
		/* Copy The User CallBack to Local ptrFunction */
		SysTick_CallBack = CallBack_Ptr;
		/* Set The SysTick Timer to Single Interval Mode */
		SysTick_Mode = SysTick_PeriodicInterval_Mode;
		/*Enable SysTick IRQ */
		SET_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Pos);
		/* Enable SysTick Counter */
		SET_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Pos);
	}
	else { /* Nothing */}  
}

u32 MSysTick_u32GetElapsedTicks(void)
{
  u32 Local_ElapsedTicks = 0;
	/* Copy The SysTick Elapsed Ticks to a Local Variable */
	Local_ElapsedTicks =  (SysTick->LOAD - SysTick->VAL);
	/* Return The Local Variable */
	return Local_ElapsedTicks;
}
u32 MSysTick_u32GetElapsedTime_us(void)
{
	u32 Local_ElapsedTicks = 0;
	u32 Local_ElapsedTime_us = 0;
	/* Copy The SysTick Elapsed Ticks to a Local Variable */
	Local_ElapsedTicks =  (SysTick->LOAD - SysTick->VAL);
	Local_ElapsedTime_us = Local_ElapsedTicks /((u32)((SYSTICK_AHB_CLK/SYSTICK_CLOCK_SOURCE)/1000000.0));
	/* Return The Local Variable */
	return Local_ElapsedTime_us;
}
u32 MSysTick_u32GetRemainingTicks(void)
{
  u32 Local_RemainingTicks = 0;
	/* Copy The SysTick Counter Register to a Local Variable */
	Local_RemainingTicks =  SysTick->VAL;
	/* Return The Local Variable */
	return Local_RemainingTicks;
}

void MSystick_voidResetTimer(void)
{
	SysTick->VAL = 0;
}

void MSystick_voidSetPreloadvalue(u32 Copy_u32Ticks)
{
	SysTick->LOAD = Copy_u32Ticks;
	SysTick->VAL = 0;
}
void SysTick_Handler(void)
{
	if (SysTick_Mode == SysTick_SingleInterval_Mode)
	{
		MSysTick_voidDeInit();
	}
	if(SysTick_CallBack)
	{
		SysTick_CallBack();
	}
}

void MSystick_Delay_ms(u32 time_ms)
{
  u32 Local_ticks = 0;
  Local_ticks = (u32)(((SYSTICK_AHB_CLK/SYSTICK_CLOCK_SOURCE)/1000.0)*time_ms);
  if(Local_ticks>SysTick_LOAD_RELOAD_Msk){
    Local_ticks = SysTick_LOAD_RELOAD_Msk;
  }
   /* Set Reload Register to SysTick Ticks */
  SysTick->LOAD = Local_ticks;
  SysTick->VAL = 0;
  /* Wait The COUNTFLAG Returns 1 */
   while (GET_BIT(SysTick->CTRL,SysTick_CTRL_COUNTFLAG_Pos) == 0);
  /* Reset The SysTick Reload Register */
	SysTick->LOAD = 0;
	/* Reset The SysTick Counter Value*/
	SysTick->VAL = 0;
}

void MSystick_Delay_us(u32 time_us)
{
  u32 Local_ticks = 0;
  Local_ticks = (u32)(((SYSTICK_AHB_CLK/SYSTICK_CLOCK_SOURCE)/1000000.0)*time_us);
  if(Local_ticks>SysTick_LOAD_RELOAD_Msk){
    Local_ticks = SysTick_LOAD_RELOAD_Msk;
  }
  CLR_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Pos);
    /* Set Reload Register to SysTick Ticks */
   SysTick->LOAD = Local_ticks;
   SysTick->VAL = 0;
   SET_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Pos);
  /* Wait The COUNTFLAG Returns 1 */
  while (GET_BIT(SysTick->CTRL,SysTick_CTRL_COUNTFLAG_Pos) == 0);
  /* Reset The SysTick Reload Register */
	SysTick->LOAD = 0;
	/* Reset The SysTick Counter Value*/
	SysTick->VAL = 0;
}
void MSysTick_void_ASYNC_Delay_ms(u32 time_ms,PtrFunction CallBack_Ptr)
{
	u32 Local_ticks = 0;
	if (CallBack_Ptr != NULL)
		{
			Local_ticks = (u32)(((SYSTICK_AHB_CLK/SYSTICK_CLOCK_SOURCE)/1000.0)*time_ms);
			if(Local_ticks>SysTick_LOAD_RELOAD_Msk)
			{
				Local_ticks = SysTick_LOAD_RELOAD_Msk;
			}
		  /* Set Reload Register to SysTick Ticks */
		  	SysTick->LOAD = Local_ticks;
		  	SysTick->VAL = 0;
			/* Copy The User CallBack to Local ptrFunction */
			SysTick_CallBack = CallBack_Ptr;
			/* Set The SysTick Timer to Single Interval Mode */
			SysTick_Mode = SysTick_SingleInterval_Mode;
			/*Enable SysTick IRQ */
			SET_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Pos);
			/* Enable SysTick Counter */
			SET_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Pos);
		}
		else { /* Nothing */}
}
