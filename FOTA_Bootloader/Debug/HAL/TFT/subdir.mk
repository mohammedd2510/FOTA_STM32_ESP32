################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/TFT/TFT_Font.c \
../HAL/TFT/TFT_Lcfg.c \
../HAL/TFT/TFT_program.c 

OBJS += \
./HAL/TFT/TFT_Font.o \
./HAL/TFT/TFT_Lcfg.o \
./HAL/TFT/TFT_program.o 

C_DEPS += \
./HAL/TFT/TFT_Font.d \
./HAL/TFT/TFT_Lcfg.d \
./HAL/TFT/TFT_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/TFT/%.o HAL/TFT/%.su HAL/TFT/%.cyclo: ../HAL/TFT/%.c HAL/TFT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-TFT

clean-HAL-2f-TFT:
	-$(RM) ./HAL/TFT/TFT_Font.cyclo ./HAL/TFT/TFT_Font.d ./HAL/TFT/TFT_Font.o ./HAL/TFT/TFT_Font.su ./HAL/TFT/TFT_Lcfg.cyclo ./HAL/TFT/TFT_Lcfg.d ./HAL/TFT/TFT_Lcfg.o ./HAL/TFT/TFT_Lcfg.su ./HAL/TFT/TFT_program.cyclo ./HAL/TFT/TFT_program.d ./HAL/TFT/TFT_program.o ./HAL/TFT/TFT_program.su

.PHONY: clean-HAL-2f-TFT

