################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc17.c \
../src/irq.c \
../src/main.c 

OBJS += \
./src/cr_startup_lpc17.o \
./src/irq.o \
./src/main.o 

C_DEPS += \
./src/cr_startup_lpc17.d \
./src/irq.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"C:\mp3\MiniDemo1769\CMSIS\inc" -I"C:\mp3\MiniDemo1769\MCU\inc" -O0 -g3 -c -fmessage-length=0 -fno-builtin -ffunction-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


