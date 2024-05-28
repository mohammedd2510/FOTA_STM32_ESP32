################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/SCB/SCB_program.c 

OBJS += \
./MCAL/SCB/SCB_program.o 

C_DEPS += \
./MCAL/SCB/SCB_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/SCB/%.o MCAL/SCB/%.su MCAL/SCB/%.cyclo: ../MCAL/SCB/%.c MCAL/SCB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-SCB

clean-MCAL-2f-SCB:
	-$(RM) ./MCAL/SCB/SCB_program.cyclo ./MCAL/SCB/SCB_program.d ./MCAL/SCB/SCB_program.o ./MCAL/SCB/SCB_program.su

.PHONY: clean-MCAL-2f-SCB

