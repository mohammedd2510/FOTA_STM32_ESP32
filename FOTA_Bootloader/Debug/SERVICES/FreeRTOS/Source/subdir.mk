################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SERVICES/FreeRTOS/Source/croutine.c \
../SERVICES/FreeRTOS/Source/event_groups.c \
../SERVICES/FreeRTOS/Source/list.c \
../SERVICES/FreeRTOS/Source/queue.c \
../SERVICES/FreeRTOS/Source/stream_buffer.c \
../SERVICES/FreeRTOS/Source/tasks.c \
../SERVICES/FreeRTOS/Source/timers.c 

OBJS += \
./SERVICES/FreeRTOS/Source/croutine.o \
./SERVICES/FreeRTOS/Source/event_groups.o \
./SERVICES/FreeRTOS/Source/list.o \
./SERVICES/FreeRTOS/Source/queue.o \
./SERVICES/FreeRTOS/Source/stream_buffer.o \
./SERVICES/FreeRTOS/Source/tasks.o \
./SERVICES/FreeRTOS/Source/timers.o 

C_DEPS += \
./SERVICES/FreeRTOS/Source/croutine.d \
./SERVICES/FreeRTOS/Source/event_groups.d \
./SERVICES/FreeRTOS/Source/list.d \
./SERVICES/FreeRTOS/Source/queue.d \
./SERVICES/FreeRTOS/Source/stream_buffer.d \
./SERVICES/FreeRTOS/Source/tasks.d \
./SERVICES/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
SERVICES/FreeRTOS/Source/%.o SERVICES/FreeRTOS/Source/%.su SERVICES/FreeRTOS/Source/%.cyclo: ../SERVICES/FreeRTOS/Source/%.c SERVICES/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/include" -I"E:/The Courses/Embedded Systems/ARM Interfacing/Test_FreeRtos/SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SERVICES-2f-FreeRTOS-2f-Source

clean-SERVICES-2f-FreeRTOS-2f-Source:
	-$(RM) ./SERVICES/FreeRTOS/Source/croutine.cyclo ./SERVICES/FreeRTOS/Source/croutine.d ./SERVICES/FreeRTOS/Source/croutine.o ./SERVICES/FreeRTOS/Source/croutine.su ./SERVICES/FreeRTOS/Source/event_groups.cyclo ./SERVICES/FreeRTOS/Source/event_groups.d ./SERVICES/FreeRTOS/Source/event_groups.o ./SERVICES/FreeRTOS/Source/event_groups.su ./SERVICES/FreeRTOS/Source/list.cyclo ./SERVICES/FreeRTOS/Source/list.d ./SERVICES/FreeRTOS/Source/list.o ./SERVICES/FreeRTOS/Source/list.su ./SERVICES/FreeRTOS/Source/queue.cyclo ./SERVICES/FreeRTOS/Source/queue.d ./SERVICES/FreeRTOS/Source/queue.o ./SERVICES/FreeRTOS/Source/queue.su ./SERVICES/FreeRTOS/Source/stream_buffer.cyclo ./SERVICES/FreeRTOS/Source/stream_buffer.d ./SERVICES/FreeRTOS/Source/stream_buffer.o ./SERVICES/FreeRTOS/Source/stream_buffer.su ./SERVICES/FreeRTOS/Source/tasks.cyclo ./SERVICES/FreeRTOS/Source/tasks.d ./SERVICES/FreeRTOS/Source/tasks.o ./SERVICES/FreeRTOS/Source/tasks.su ./SERVICES/FreeRTOS/Source/timers.cyclo ./SERVICES/FreeRTOS/Source/timers.d ./SERVICES/FreeRTOS/Source/timers.o ./SERVICES/FreeRTOS/Source/timers.su

.PHONY: clean-SERVICES-2f-FreeRTOS-2f-Source

