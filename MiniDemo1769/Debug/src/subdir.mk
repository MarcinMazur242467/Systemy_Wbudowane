################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc17.c \
../src/irq.c \
../src/main.c 

C_DEPS += \
./src/cr_startup_lpc17.d \
./src/irq.d \
./src/main.d 

OBJS += \
./src/cr_startup_lpc17.o \
./src/irq.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"C:\Studia\Systemy_Wbudowane\MiniDemo1769\CMSIS\inc" -I"C:\Studia\Systemy_Wbudowane\MiniDemo1769\MCU\inc" -O0 -g3 -c -fmessage-length=0 -fno-builtin -ffunction-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/cr_startup_lpc17.d ./src/cr_startup_lpc17.o ./src/irq.d ./src/irq.o ./src/main.d ./src/main.o

.PHONY: clean-src

