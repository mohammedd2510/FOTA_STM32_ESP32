################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/DMA/DMA_Lcfg.c \
../MCAL/DMA/DMA_program.c 

OBJS += \
./MCAL/DMA/DMA_Lcfg.o \
./MCAL/DMA/DMA_program.o 

C_DEPS += \
./MCAL/DMA/DMA_Lcfg.d \
./MCAL/DMA/DMA_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/DMA/%.o MCAL/DMA/%.su MCAL/DMA/%.cyclo: ../MCAL/DMA/%.c MCAL/DMA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/FOTA Project/FOTA_Application/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-DMA

clean-MCAL-2f-DMA:
	-$(RM) ./MCAL/DMA/DMA_Lcfg.cyclo ./MCAL/DMA/DMA_Lcfg.d ./MCAL/DMA/DMA_Lcfg.o ./MCAL/DMA/DMA_Lcfg.su ./MCAL/DMA/DMA_program.cyclo ./MCAL/DMA/DMA_program.d ./MCAL/DMA/DMA_program.o ./MCAL/DMA/DMA_program.su

.PHONY: clean-MCAL-2f-DMA

