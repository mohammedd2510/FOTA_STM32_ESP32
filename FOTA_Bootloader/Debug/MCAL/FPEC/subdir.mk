################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/FPEC/FPEC_program.c 

OBJS += \
./MCAL/FPEC/FPEC_program.o 

C_DEPS += \
./MCAL/FPEC/FPEC_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/FPEC/%.o MCAL/FPEC/%.su MCAL/FPEC/%.cyclo: ../MCAL/FPEC/%.c MCAL/FPEC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Bootloader" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-FPEC

clean-MCAL-2f-FPEC:
	-$(RM) ./MCAL/FPEC/FPEC_program.cyclo ./MCAL/FPEC/FPEC_program.d ./MCAL/FPEC/FPEC_program.o ./MCAL/FPEC/FPEC_program.su

.PHONY: clean-MCAL-2f-FPEC

