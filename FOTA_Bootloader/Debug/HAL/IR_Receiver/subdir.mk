################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/IR_Receiver/IR_Lcfg.c \
../HAL/IR_Receiver/IR_program.c 

OBJS += \
./HAL/IR_Receiver/IR_Lcfg.o \
./HAL/IR_Receiver/IR_program.o 

C_DEPS += \
./HAL/IR_Receiver/IR_Lcfg.d \
./HAL/IR_Receiver/IR_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/IR_Receiver/%.o HAL/IR_Receiver/%.su HAL/IR_Receiver/%.cyclo: ../HAL/IR_Receiver/%.c HAL/IR_Receiver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-IR_Receiver

clean-HAL-2f-IR_Receiver:
	-$(RM) ./HAL/IR_Receiver/IR_Lcfg.cyclo ./HAL/IR_Receiver/IR_Lcfg.d ./HAL/IR_Receiver/IR_Lcfg.o ./HAL/IR_Receiver/IR_Lcfg.su ./HAL/IR_Receiver/IR_program.cyclo ./HAL/IR_Receiver/IR_program.d ./HAL/IR_Receiver/IR_program.o ./HAL/IR_Receiver/IR_program.su

.PHONY: clean-HAL-2f-IR_Receiver

