################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include FreeRTOS/portable/MemMang/subdir.mk
-include FreeRTOS/portable/ARM_CM4F/subdir.mk
-include FreeRTOS/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
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

BUILD_ARTIFACT_NAME := Embedded_OS_Lab1_P76091234
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Embedded_OS_Lab1_P76091234.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Embedded_OS_Lab1_P76091234.list \

OBJCOPY_BIN += \
Embedded_OS_Lab1_P76091234.bin \


# All Target
all: main-build

# Main-build Target
main-build: Embedded_OS_Lab1_P76091234.elf secondary-outputs

# Tool invocations
Embedded_OS_Lab1_P76091234.elf: $(OBJS) $(USER_OBJS) /home/tsen65409/STM32CubeIDE/workspace_1.5.1/Embedded_OS_Lab1_P76091234/STM32F407VGTX_FLASH.ld
	arm-none-eabi-gcc -o "Embedded_OS_Lab1_P76091234.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/tsen65409/STM32CubeIDE/workspace_1.5.1/Embedded_OS_Lab1_P76091234/STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Embedded_OS_Lab1_P76091234.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Embedded_OS_Lab1_P76091234.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Embedded_OS_Lab1_P76091234.list"
	@echo 'Finished building: $@'
	@echo ' '

Embedded_OS_Lab1_P76091234.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Embedded_OS_Lab1_P76091234.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
