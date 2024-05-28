################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SERVICES/FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./SERVICES/FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./SERVICES/FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
SERVICES/FreeRTOS/Source/portable/MemMang/%.o SERVICES/FreeRTOS/Source/portable/MemMang/%.su SERVICES/FreeRTOS/Source/portable/MemMang/%.cyclo: ../SERVICES/FreeRTOS/Source/portable/MemMang/%.c SERVICES/FreeRTOS/Source/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SERVICES-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang

clean-SERVICES-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang:
	-$(RM) ./SERVICES/FreeRTOS/Source/portable/MemMang/heap_4.cyclo ./SERVICES/FreeRTOS/Source/portable/MemMang/heap_4.d ./SERVICES/FreeRTOS/Source/portable/MemMang/heap_4.o ./SERVICES/FreeRTOS/Source/portable/MemMang/heap_4.su

.PHONY: clean-SERVICES-2f-FreeRTOS-2f-Source-2f-portable-2f-MemMang

