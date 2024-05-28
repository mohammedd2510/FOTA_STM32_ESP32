################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/EXTI/EXTI_Lcfg.c \
../MCAL/EXTI/EXTI_program.c 

OBJS += \
./MCAL/EXTI/EXTI_Lcfg.o \
./MCAL/EXTI/EXTI_program.o 

C_DEPS += \
./MCAL/EXTI/EXTI_Lcfg.d \
./MCAL/EXTI/EXTI_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/EXTI/%.o MCAL/EXTI/%.su MCAL/EXTI/%.cyclo: ../MCAL/EXTI/%.c MCAL/EXTI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-EXTI

clean-MCAL-2f-EXTI:
	-$(RM) ./MCAL/EXTI/EXTI_Lcfg.cyclo ./MCAL/EXTI/EXTI_Lcfg.d ./MCAL/EXTI/EXTI_Lcfg.o ./MCAL/EXTI/EXTI_Lcfg.su ./MCAL/EXTI/EXTI_program.cyclo ./MCAL/EXTI/EXTI_program.d ./MCAL/EXTI/EXTI_program.o ./MCAL/EXTI/EXTI_program.su

.PHONY: clean-MCAL-2f-EXTI

