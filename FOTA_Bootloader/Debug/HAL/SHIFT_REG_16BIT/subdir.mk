################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/SHIFT_REG_16BIT/SHIFTREG_Lcfg.c \
../HAL/SHIFT_REG_16BIT/SHIFTREG_program.c 

OBJS += \
./HAL/SHIFT_REG_16BIT/SHIFTREG_Lcfg.o \
./HAL/SHIFT_REG_16BIT/SHIFTREG_program.o 

C_DEPS += \
./HAL/SHIFT_REG_16BIT/SHIFTREG_Lcfg.d \
./HAL/SHIFT_REG_16BIT/SHIFTREG_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/SHIFT_REG_16BIT/%.o HAL/SHIFT_REG_16BIT/%.su HAL/SHIFT_REG_16BIT/%.cyclo: ../HAL/SHIFT_REG_16BIT/%.c HAL/SHIFT_REG_16BIT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-SHIFT_REG_16BIT

clean-HAL-2f-SHIFT_REG_16BIT:
	-$(RM) ./HAL/SHIFT_REG_16BIT/SHIFTREG_Lcfg.cyclo ./HAL/SHIFT_REG_16BIT/SHIFTREG_Lcfg.d ./HAL/SHIFT_REG_16BIT/SHIFTREG_Lcfg.o ./HAL/SHIFT_REG_16BIT/SHIFTREG_Lcfg.su ./HAL/SHIFT_REG_16BIT/SHIFTREG_program.cyclo ./HAL/SHIFT_REG_16BIT/SHIFTREG_program.d ./HAL/SHIFT_REG_16BIT/SHIFTREG_program.o ./HAL/SHIFT_REG_16BIT/SHIFTREG_program.su

.PHONY: clean-HAL-2f-SHIFT_REG_16BIT

