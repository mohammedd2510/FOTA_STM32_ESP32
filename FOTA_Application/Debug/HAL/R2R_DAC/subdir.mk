################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/R2R_DAC/R2RDAC_Lcfg.c \
../HAL/R2R_DAC/R2RDAC_program.c 

OBJS += \
./HAL/R2R_DAC/R2RDAC_Lcfg.o \
./HAL/R2R_DAC/R2RDAC_program.o 

C_DEPS += \
./HAL/R2R_DAC/R2RDAC_Lcfg.d \
./HAL/R2R_DAC/R2RDAC_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/R2R_DAC/%.o HAL/R2R_DAC/%.su HAL/R2R_DAC/%.cyclo: ../HAL/R2R_DAC/%.c HAL/R2R_DAC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-R2R_DAC

clean-HAL-2f-R2R_DAC:
	-$(RM) ./HAL/R2R_DAC/R2RDAC_Lcfg.cyclo ./HAL/R2R_DAC/R2RDAC_Lcfg.d ./HAL/R2R_DAC/R2RDAC_Lcfg.o ./HAL/R2R_DAC/R2RDAC_Lcfg.su ./HAL/R2R_DAC/R2RDAC_program.cyclo ./HAL/R2R_DAC/R2RDAC_program.d ./HAL/R2R_DAC/R2RDAC_program.o ./HAL/R2R_DAC/R2RDAC_program.su

.PHONY: clean-HAL-2f-R2R_DAC

