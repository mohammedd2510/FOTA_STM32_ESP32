################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/NVIC/NVIC_program.c 

OBJS += \
./MCAL/NVIC/NVIC_program.o 

C_DEPS += \
./MCAL/NVIC/NVIC_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/NVIC/%.o MCAL/NVIC/%.su MCAL/NVIC/%.cyclo: ../MCAL/NVIC/%.c MCAL/NVIC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-NVIC

clean-MCAL-2f-NVIC:
	-$(RM) ./MCAL/NVIC/NVIC_program.cyclo ./MCAL/NVIC/NVIC_program.d ./MCAL/NVIC/NVIC_program.o ./MCAL/NVIC/NVIC_program.su

.PHONY: clean-MCAL-2f-NVIC

