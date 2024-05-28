################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.o SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.su SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.cyclo: ../SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.c SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SERVICES-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

clean-SERVICES-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.cyclo ./SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d ./SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o ./SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.su

.PHONY: clean-SERVICES-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

