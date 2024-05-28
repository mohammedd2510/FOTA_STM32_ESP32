################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/SPI/SPI_Lcfg.c \
../MCAL/SPI/SPI_program.c 

OBJS += \
./MCAL/SPI/SPI_Lcfg.o \
./MCAL/SPI/SPI_program.o 

C_DEPS += \
./MCAL/SPI/SPI_Lcfg.d \
./MCAL/SPI/SPI_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/SPI/%.o MCAL/SPI/%.su MCAL/SPI/%.cyclo: ../MCAL/SPI/%.c MCAL/SPI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-SPI

clean-MCAL-2f-SPI:
	-$(RM) ./MCAL/SPI/SPI_Lcfg.cyclo ./MCAL/SPI/SPI_Lcfg.d ./MCAL/SPI/SPI_Lcfg.o ./MCAL/SPI/SPI_Lcfg.su ./MCAL/SPI/SPI_program.cyclo ./MCAL/SPI/SPI_program.d ./MCAL/SPI/SPI_program.o ./MCAL/SPI/SPI_program.su

.PHONY: clean-MCAL-2f-SPI

