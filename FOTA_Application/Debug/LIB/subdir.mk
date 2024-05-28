################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIB/syscalls.c \
../LIB/sysmem.c 

OBJS += \
./LIB/syscalls.o \
./LIB/sysmem.o 

C_DEPS += \
./LIB/syscalls.d \
./LIB/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
LIB/%.o LIB/%.su LIB/%.cyclo: ../LIB/%.c LIB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LIB

clean-LIB:
	-$(RM) ./LIB/syscalls.cyclo ./LIB/syscalls.d ./LIB/syscalls.o ./LIB/syscalls.su ./LIB/sysmem.cyclo ./LIB/sysmem.d ./LIB/sysmem.o ./LIB/sysmem.su

.PHONY: clean-LIB

