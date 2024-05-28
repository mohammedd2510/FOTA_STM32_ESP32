################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include SERVICES/FreeRTOS/Source/portable/MemMang/subdir.mk
-include SERVICES/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include SERVICES/FreeRTOS/Source/subdir.mk
-include MCAL/TIM/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/SCB/subdir.mk
-include MCAL/RCC/subdir.mk
-include MCAL/NVIC/subdir.mk
-include MCAL/GPIO/subdir.mk
-include MCAL/FPEC/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/DMA/subdir.mk
-include LIB/subdir.mk
-include HAL/TFT/subdir.mk
-include HAL/SHIFT_REG_16BIT/subdir.mk
-include HAL/RGB_LED/subdir.mk
-include HAL/R2R_DAC/subdir.mk
-include HAL/LEDMAT/subdir.mk
-include HAL/IR_Receiver/subdir.mk
-include APP/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := FOTA_Application
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
FOTA_Application.elf \

MAP_FILES += \
FOTA_Application.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
FOTA_Application.list \

OBJCOPY_HEX += \
FOTA_Application.hex \

OBJCOPY_BIN += \
FOTA_Application.bin \


# All Target
all: main-build

# Main-build Target
main-build: FOTA_Application.elf secondary-outputs

# Tool invocations
FOTA_Application.elf FOTA_Application.map: $(OBJS) $(USER_OBJS) E:\The\ Courses\Embedded\ Systems\ARM\ Interfacing\FOTA\ Project\FOTA_Application\STM32F401CCUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "FOTA_Application.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"E:\The Courses\Embedded Systems\ARM Interfacing\FOTA Project\FOTA_Application\STM32F401CCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="FOTA_Application.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

FOTA_Application.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "FOTA_Application.list"
	@echo 'Finished building: $@'
	@echo ' '

FOTA_Application.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "FOTA_Application.hex"
	@echo 'Finished building: $@'
	@echo ' '

FOTA_Application.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "FOTA_Application.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) FOTA_Application.bin FOTA_Application.elf FOTA_Application.hex FOTA_Application.list FOTA_Application.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
