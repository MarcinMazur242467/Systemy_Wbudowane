################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include MCU/src/subdir.mk
-include CMSIS/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MiniDemo1768.axf

# Tool invocations
MiniDemo1768.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\mp3\MiniDemo1769\MCU\src" -L"C:\mp3\MiniDemo1769\CMSIS\src" -Xlinker --gc-sections -Xlinker -Map=MiniDemo1768.map -mcpu=cortex-m3 -mthumb -T "MiniDemo1769_Debug.ld" -o "MiniDemo1768.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) MiniDemo1768.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size MiniDemo1768.axf; # arm-none-eabi-objdump -h -S MiniDemo1768.axf >MiniDemo1768.lss
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
