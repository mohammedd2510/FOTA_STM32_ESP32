// Lower Layer Inclusion

// Self Layer Inclusion

// Self Files Inclusion
#include"GPIO_config.h"
#include"GPIO_interface.h"
#include"GPIO_private.h"

void GPIO_voidSetPinMode(port_index_t Copy_PortIndex, pin_index_t Copy_PinIndex,
                         gpio_pin_mode_t Copy_GPIOPinMode) {
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      MODIFY_REG(GPIOA_MODER,
                 GPIO_MODER_CLEAR_MASK << GPIO_MODER_PIN_BITS * Copy_PinIndex,
                 Copy_GPIOPinMode << GPIO_MODER_PIN_BITS * Copy_PinIndex);
      break;
    case GPIO_PORTB:
      MODIFY_REG(GPIOB_MODER,
                 GPIO_MODER_CLEAR_MASK << GPIO_MODER_PIN_BITS * Copy_PinIndex,
                 Copy_GPIOPinMode << GPIO_MODER_PIN_BITS * Copy_PinIndex);
      break;
    case GPIO_PORTC:
      MODIFY_REG(GPIOC_MODER,
                 GPIO_MODER_CLEAR_MASK << GPIO_MODER_PIN_BITS * Copy_PinIndex,
                 Copy_GPIOPinMode << GPIO_MODER_PIN_BITS * Copy_PinIndex);
      break;
    default:
      break;
  }
}
void GPIO_voidSetPinOutputMode(port_index_t Copy_PortIndex,
                               pin_index_t Copy_PinIndex,
                               output_pin_mode_t Copy_OutputPinMode) {
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      MODIFY_REG(GPIOB_OTYPER, GPIO_OTYPER_CLEAR_MASK << Copy_PinIndex,
                 Copy_OutputPinMode << Copy_PinIndex);
      break;
    case GPIO_PORTB:
      MODIFY_REG(GPIOB_OTYPER, GPIO_OTYPER_CLEAR_MASK << Copy_PinIndex,
                 Copy_OutputPinMode << Copy_PinIndex);
      break;
    case GPIO_PORTC:
      MODIFY_REG(GPIOC_OTYPER, GPIO_OTYPER_CLEAR_MASK << Copy_PinIndex,
                 Copy_OutputPinMode << Copy_PinIndex);
      break;
    default:
      break;
  }
}
void GPIO_voidSetPinAlternateFunction(port_index_t Copy_PortIndex, pin_index_t Copy_PinIndex, u8 Copy_u8AlternateFunction)
{
	switch (Copy_PortIndex) {
	    case GPIO_PORTA:
             if(Copy_PinIndex < 8)
             {
            	 MODIFY_REG(GPIOA_AFRL, GPIO_AF_CLEAR_MASK << Copy_PinIndex * GPIO_AF_PIN_BITS,
					  Copy_u8AlternateFunction << Copy_PinIndex * GPIO_AF_PIN_BITS);
             }
             else
             {
            	 MODIFY_REG(GPIOA_AFRH, GPIO_AF_CLEAR_MASK << (Copy_PinIndex-8) * GPIO_AF_PIN_BITS,
            			 Copy_u8AlternateFunction << (Copy_PinIndex-8) * GPIO_AF_PIN_BITS);
             }
	      break;
	    case GPIO_PORTB:
	    	if(Copy_PinIndex < 8)
	    	{
	    		MODIFY_REG(GPIOB_AFRL, GPIO_AF_CLEAR_MASK << Copy_PinIndex * GPIO_AF_PIN_BITS,
	    				Copy_u8AlternateFunction << Copy_PinIndex * GPIO_AF_PIN_BITS);
	    	}
	    	else
	    	{
	    		MODIFY_REG(GPIOB_AFRH, GPIO_AF_CLEAR_MASK << (Copy_PinIndex-8) * GPIO_AF_PIN_BITS,
	    				Copy_u8AlternateFunction << (Copy_PinIndex-8) * GPIO_AF_PIN_BITS);
	    	}
	      break;
	    case GPIO_PORTC:
	    	if(Copy_PinIndex < 8)
	    	{
	    		MODIFY_REG(GPIOC_AFRL, GPIO_AF_CLEAR_MASK << Copy_PinIndex * GPIO_AF_PIN_BITS,
	    				Copy_u8AlternateFunction << Copy_PinIndex * GPIO_AF_PIN_BITS);
	    	}
	    	else
	    	{
	    		MODIFY_REG(GPIOC_AFRH, GPIO_AF_CLEAR_MASK << (Copy_PinIndex-8) * GPIO_AF_PIN_BITS,
	    				Copy_u8AlternateFunction << (Copy_PinIndex-8) * GPIO_AF_PIN_BITS);
	    	}
	      break;
	    default:
	      break;
	  }
}
void GPIO_voidSetPinOutputSpeed(port_index_t Copy_PortIndex,
                                pin_index_t Copy_PinIndex,
                                output_pin_speed_mode_t Copy_OutputPinSpeed) {
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      MODIFY_REG(
          GPIOA_OSPEEDR,
          GPIO_OSPEEDR_CLEAR_MASK << GPIO_OSPEEDR_PIN_BITS * Copy_PinIndex,
          Copy_OutputPinSpeed << GPIO_OSPEEDR_PIN_BITS * Copy_PinIndex);
      break;
    case GPIO_PORTB:
      MODIFY_REG(
          GPIOB_OSPEEDR,
          GPIO_OSPEEDR_CLEAR_MASK << GPIO_OSPEEDR_PIN_BITS * Copy_PinIndex,
          Copy_OutputPinSpeed << GPIO_OSPEEDR_PIN_BITS * Copy_PinIndex);
      break;
    case GPIO_PORTC:
      MODIFY_REG(GPIOC_OSPEEDR,
                 GPIO_MODER_CLEAR_MASK << GPIO_OSPEEDR_PIN_BITS * Copy_PinIndex,
                 Copy_OutputPinSpeed << GPIO_OSPEEDR_PIN_BITS * Copy_PinIndex);
      break;
    default:
      break;
  }
}
void GPIO_voidSetPinValue(port_index_t Copy_PortIndex,
                          pin_index_t Copy_PinIndex,
                          gpio_logic_t Copy_GPIOLogic) {
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      if (Copy_GPIOLogic == GPIO_HIGH) {
        WRITE_REG(GPIOA_BSRR, GPIO_SET_BIT_POS << Copy_PinIndex);
      } else if (Copy_GPIOLogic == GPIO_LOW) {
        WRITE_REG(GPIOA_BSRR, GPIO_RESET_BIT_POS << Copy_PinIndex);
      } else { /* Nothing */
      }
      break;
    case GPIO_PORTB:
      if (Copy_GPIOLogic == GPIO_HIGH) {
        WRITE_REG(GPIOB_BSRR, GPIO_SET_BIT_POS << Copy_PinIndex);
      } else if (Copy_GPIOLogic == GPIO_LOW) {
        WRITE_REG(GPIOB_BSRR, GPIO_RESET_BIT_POS << Copy_PinIndex);
      } else { /* Nothing */
      }
      break;
    case GPIO_PORTC:
      if (Copy_GPIOLogic == GPIO_HIGH) {
        WRITE_REG(GPIOC_BSRR, GPIO_SET_BIT_POS << Copy_PinIndex);
      } else if (Copy_GPIOLogic == GPIO_LOW) {
        WRITE_REG(GPIOC_BSRR, GPIO_RESET_BIT_POS << Copy_PinIndex);
      } else { /* Nothing */
      }
      break;
    default:
      break;
  }
}
void GPIO_voidSetPinPullUpDownResistor(port_index_t Copy_PortIndex,
                                       pin_index_t Copy_PinIndex,
                                       input_pin_mode_t Copy_InputPinMode) {
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      MODIFY_REG(GPIOA_PUPDR,
                 GPIO_PUPDR_CLEAR_MASK << GPIO_PUPDR_PIN_BITS * Copy_PinIndex,
                 Copy_InputPinMode << GPIO_PUPDR_PIN_BITS * Copy_PinIndex);
      break;
    case GPIO_PORTB:
      MODIFY_REG(GPIOB_PUPDR,
                 GPIO_PUPDR_CLEAR_MASK << GPIO_PUPDR_PIN_BITS * Copy_PinIndex,
                 Copy_InputPinMode << GPIO_PUPDR_PIN_BITS * Copy_PinIndex);
      break;
    case GPIO_PORTC:
      MODIFY_REG(GPIOC_PUPDR,
                 GPIO_PUPDR_CLEAR_MASK << GPIO_PUPDR_PIN_BITS * Copy_PinIndex,
                 Copy_InputPinMode << GPIO_PUPDR_PIN_BITS * Copy_PinIndex);
      break;
    default:
      break;
  }
}
u8 GPIO_u8GetPinValue(port_index_t Copy_PortIndex, pin_index_t Copy_PinIndex) {
  u8 Local_u8PinValue = GPIO_LOW;
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      Local_u8PinValue = GET_BIT(GPIOA_IDR, Copy_PinIndex);
      break;
    case GPIO_PORTB:
      Local_u8PinValue = GET_BIT(GPIOB_IDR, Copy_PinIndex);
      break;
    case GPIO_PORTC:
      Local_u8PinValue = GET_BIT(GPIOC_IDR, Copy_PinIndex);
      break;
    default:
      break;
  }
  return Local_u8PinValue;
}

void GPIO_voidLockPin(port_index_t Copy_PortIndex, pin_index_t Copy_PinIndex) {
  u32 Local_u32LCKRDummyRead = 0;
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      WRITE_REG(GPIOA_LCKR, GPIO_LCKK_MASK | (1 << Copy_PinIndex));
      WRITE_REG(GPIOA_LCKR, (1 << Copy_PinIndex));
      WRITE_REG(GPIOA_LCKR, GPIO_LCKK_MASK | (1 << Copy_PinIndex));
      Local_u32LCKRDummyRead = READ_REG(GPIOA_LCKR);
      break;
    case GPIO_PORTB:
      WRITE_REG(GPIOB_LCKR, GPIO_LCKK_MASK | (1 << Copy_PinIndex));
      WRITE_REG(GPIOB_LCKR, (1 << Copy_PinIndex));
      WRITE_REG(GPIOB_LCKR, GPIO_LCKK_MASK | (1 << Copy_PinIndex));
      Local_u32LCKRDummyRead = READ_REG(GPIOB_LCKR);
      break;
    case GPIO_PORTC:
      WRITE_REG(GPIOC_LCKR, GPIO_LCKK_MASK | (1 << Copy_PinIndex));
      WRITE_REG(GPIOC_LCKR, (1 << Copy_PinIndex));
      WRITE_REG(GPIOC_LCKR, GPIO_LCKK_MASK | (1 << Copy_PinIndex));
      Local_u32LCKRDummyRead = READ_REG(GPIOC_LCKR);
      break;
    default:
      break;
  }
}

void GPIO_voidSetPortMode(port_index_t Copy_PortIndex, u32 Copy_u32GPIOPortMode) {
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      WRITE_REG(GPIOA_MODER, Copy_u32GPIOPortMode);
      break;
    case GPIO_PORTB:
      WRITE_REG(GPIOB_MODER, Copy_u32GPIOPortMode);
      break;
    case GPIO_PORTC:
      WRITE_REG(GPIOC_MODER, Copy_u32GPIOPortMode);
      break;
    default:
      break;
  }
}
void GPIO_voidSetPortOutputMode(port_index_t Copy_PortIndex,
                                u32 Copy_u32OutputPortMode) {
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      WRITE_REG(GPIOA_OTYPER, Copy_u32OutputPortMode);
      break;
    case GPIO_PORTB:
      WRITE_REG(GPIOB_OTYPER, Copy_u32OutputPortMode);
      break;
    case GPIO_PORTC:
      WRITE_REG(GPIOC_OTYPER, Copy_u32OutputPortMode);
      break;
    default:
      break;
  }
}
void GPIO_voidSetPortOutputSpeed(port_index_t Copy_PortIndex,
                                 u32 Copy_u32OutputPortSpeed) {
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      WRITE_REG(GPIOA_OSPEEDR, Copy_u32OutputPortSpeed);
      break;
    case GPIO_PORTB:
      WRITE_REG(GPIOB_OSPEEDR, Copy_u32OutputPortSpeed);
      break;
    case GPIO_PORTC:
      WRITE_REG(GPIOC_OSPEEDR, Copy_u32OutputPortSpeed);
      break;
    default:
      break;
  }
}
void GPIO_voidSetPortValue(port_index_t Copy_PortIndex,
                           gpio_logic_t Copy_GPIOLogic) {
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      if (Copy_GPIOLogic == GPIO_HIGH) {
        WRITE_REG(GPIOA_ODR, GPIO_ODR_HIGH);
      } else if (Copy_GPIOLogic == GPIO_LOW) {
        WRITE_REG(GPIOA_ODR, GPIO_ODR_LOW);
      } else { /* Nothing */
      }
      break;
    case GPIO_PORTB:
      if (Copy_GPIOLogic == GPIO_HIGH) {
        WRITE_REG(GPIOB_ODR, GPIO_ODR_HIGH);
      } else if (Copy_GPIOLogic == GPIO_LOW) {
        WRITE_REG(GPIOB_ODR, GPIO_ODR_LOW);
      } else { /* Nothing */
      }
      break;
    case GPIO_PORTC:
      if (Copy_GPIOLogic == GPIO_HIGH) {
        WRITE_REG(GPIOC_ODR, GPIO_ODR_HIGH);
      } else if (Copy_GPIOLogic == GPIO_LOW) {
        WRITE_REG(GPIOC_ODR, GPIO_ODR_LOW);
      } else { /* Nothing */
      }
      break;
    default:
      break;
  }
}
void GPIO_voidSetPortPullUpDownResistor(port_index_t Copy_PortIndex,
                                        u32 Copy_u32InputPortMode) {
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      WRITE_REG(GPIOA_PUPDR, Copy_u32InputPortMode);
      break;
    case GPIO_PORTB:
      WRITE_REG(GPIOB_PUPDR, Copy_u32InputPortMode);
      break;
    case GPIO_PORTC:
      WRITE_REG(GPIOC_PUPDR, Copy_u32InputPortMode);
      break;
    default:
      break;
  }
}
u32 GPIO_u32GetPortValue(port_index_t Copy_PortIndex) {
  u8 Local_u32PortValue = 0x00;
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      Local_u32PortValue = READ_REG(GPIOA_IDR);
      break;
    case GPIO_PORTB:
      Local_u32PortValue = READ_REG(GPIOB_IDR);
      break;
    case GPIO_PORTC:
      Local_u32PortValue = READ_REG(GPIOC_IDR);
      break;
    default:
      break;
  }
  return Local_u32PortValue;
}

void GPIO_voidLockPort(port_index_t Copy_PortIndex) {
  u32 Local_u32LCKRDummyRead = 0;
  switch (Copy_PortIndex) {
    case GPIO_PORTA:
      WRITE_REG(GPIOA_LCKR, GPIO_LCKK_MASK | GPIO_PORT_LOCKED);
      WRITE_REG(GPIOA_LCKR, GPIO_PORT_LOCKED);
      WRITE_REG(GPIOA_LCKR, GPIO_LCKK_MASK | GPIO_PORT_LOCKED);
      Local_u32LCKRDummyRead = READ_REG(GPIOA_LCKR);
      break;
    case GPIO_PORTB:
      WRITE_REG(GPIOB_LCKR, GPIO_LCKK_MASK | GPIO_PORT_LOCKED);
      WRITE_REG(GPIOB_LCKR, GPIO_PORT_LOCKED);
      WRITE_REG(GPIOB_LCKR, GPIO_LCKK_MASK | GPIO_PORT_LOCKED);
      Local_u32LCKRDummyRead = READ_REG(GPIOB_LCKR);
      break;
    case GPIO_PORTC:
      WRITE_REG(GPIOC_LCKR, GPIO_LCKK_MASK | GPIO_PORT_LOCKED);
      WRITE_REG(GPIOC_LCKR, GPIO_PORT_LOCKED);
      WRITE_REG(GPIOC_LCKR, GPIO_LCKK_MASK | GPIO_PORT_LOCKED);
      Local_u32LCKRDummyRead = READ_REG(GPIOC_LCKR);
      break;
    default:
      break;
  }
}
