################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/RGB_LED/RGB_Lcfg.c \
../HAL/RGB_LED/RGB_program.c 

OBJS += \
./HAL/RGB_LED/RGB_Lcfg.o \
./HAL/RGB_LED/RGB_program.o 

C_DEPS += \
./HAL/RGB_LED/RGB_Lcfg.d \
./HAL/RGB_LED/RGB_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/RGB_LED/%.o HAL/RGB_LED/%.su HAL/RGB_LED/%.cyclo: ../HAL/RGB_LED/%.c HAL/RGB_LED/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-RGB_LED

clean-HAL-2f-RGB_LED:
	-$(RM) ./HAL/RGB_LED/RGB_Lcfg.cyclo ./HAL/RGB_LED/RGB_Lcfg.d ./HAL/RGB_LED/RGB_Lcfg.o ./HAL/RGB_LED/RGB_Lcfg.su ./HAL/RGB_LED/RGB_program.cyclo ./HAL/RGB_LED/RGB_program.d ./HAL/RGB_LED/RGB_program.o ./HAL/RGB_LED/RGB_program.su

.PHONY: clean-HAL-2f-RGB_LED

