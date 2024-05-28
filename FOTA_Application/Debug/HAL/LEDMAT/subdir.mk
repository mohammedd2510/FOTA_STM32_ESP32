################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LEDMAT/LEDMAT_LCFG.c \
../HAL/LEDMAT/LEDMAT_font.c \
../HAL/LEDMAT/LEDMAT_program.c 

OBJS += \
./HAL/LEDMAT/LEDMAT_LCFG.o \
./HAL/LEDMAT/LEDMAT_font.o \
./HAL/LEDMAT/LEDMAT_program.o 

C_DEPS += \
./HAL/LEDMAT/LEDMAT_LCFG.d \
./HAL/LEDMAT/LEDMAT_font.d \
./HAL/LEDMAT/LEDMAT_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/LEDMAT/%.o HAL/LEDMAT/%.su HAL/LEDMAT/%.cyclo: ../HAL/LEDMAT/%.c HAL/LEDMAT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-LEDMAT

clean-HAL-2f-LEDMAT:
	-$(RM) ./HAL/LEDMAT/LEDMAT_LCFG.cyclo ./HAL/LEDMAT/LEDMAT_LCFG.d ./HAL/LEDMAT/LEDMAT_LCFG.o ./HAL/LEDMAT/LEDMAT_LCFG.su ./HAL/LEDMAT/LEDMAT_font.cyclo ./HAL/LEDMAT/LEDMAT_font.d ./HAL/LEDMAT/LEDMAT_font.o ./HAL/LEDMAT/LEDMAT_font.su ./HAL/LEDMAT/LEDMAT_program.cyclo ./HAL/LEDMAT/LEDMAT_program.d ./HAL/LEDMAT/LEDMAT_program.o ./HAL/LEDMAT/LEDMAT_program.su

.PHONY: clean-HAL-2f-LEDMAT

