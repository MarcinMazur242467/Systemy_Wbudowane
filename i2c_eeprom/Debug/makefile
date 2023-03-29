################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := i2c_eeprom
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: i2c_eeprom.axf

# Tool invocations
i2c_eeprom.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Studia\Systemy_Wbudowane\Lib_CMSISv1p30_LPC17xx\Debug" -L"C:\Studia\Systemy_Wbudowane\Lib_EaBaseBoard\Debug" -L"C:\Studia\Systemy_Wbudowane\Lib_MCU\Debug" -Xlinker --gc-sections -Xlinker -Map=i2c_eeprom.map -mcpu=cortex-m3 -mthumb -T i2c_eeprom_Debug.ld -o "i2c_eeprom.axf" $(OBJS) $(USER_OBJS) $(LIBS) -lCMSISv1p30_LPC17xx -lLib_EaBaseBoard -lLib_MCU
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) i2c_eeprom.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size i2c_eeprom.axf; # arm-none-eabi-objdump -h -S i2c_eeprom.axf >i2c_eeprom.lss
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
