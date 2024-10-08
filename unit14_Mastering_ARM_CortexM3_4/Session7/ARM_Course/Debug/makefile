################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include MCAL/subdir.mk
-include HAL/Seven_segment/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/Keypad/subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ARM_Course.axf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ARM_Course.list \

OBJCOPY_BIN += \
ARM_Course.bin \


# All Target
all: ARM_Course.axf secondary-outputs

# Tool invocations
ARM_Course.axf: $(OBJS) $(USER_OBJS) D:\Mastring\ Embedded\ System(online)\Codes\Unit14_Mastering_ARM_CortexM3_4\Session7\ARM_Course\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "ARM_Course.axf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Mastring Embedded System(online)\Codes\Unit14_Mastering_ARM_CortexM3_4\Session7\ARM_Course\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ARM_Course.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ARM_Course.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ARM_Course.list"
	@echo 'Finished building: $@'
	@echo ' '

ARM_Course.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ARM_Course.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
