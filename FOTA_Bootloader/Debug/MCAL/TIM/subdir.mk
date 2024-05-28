################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/TIM/TIM_Lcfg.c \
../MCAL/TIM/TIM_program.c 

OBJS += \
./MCAL/TIM/TIM_Lcfg.o \
./MCAL/TIM/TIM_program.o 

C_DEPS += \
./MCAL/TIM/TIM_Lcfg.d \
./MCAL/TIM/TIM_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/TIM/%.o MCAL/TIM/%.su MCAL/TIM/%.cyclo: ../MCAL/TIM/%.c MCAL/TIM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-TIM

clean-MCAL-2f-TIM:
	-$(RM) ./MCAL/TIM/TIM_Lcfg.cyclo ./MCAL/TIM/TIM_Lcfg.d ./MCAL/TIM/TIM_Lcfg.o ./MCAL/TIM/TIM_Lcfg.su ./MCAL/TIM/TIM_program.cyclo ./MCAL/TIM/TIM_program.d ./MCAL/TIM/TIM_program.o ./MCAL/TIM/TIM_program.su

.PHONY: clean-MCAL-2f-TIM

