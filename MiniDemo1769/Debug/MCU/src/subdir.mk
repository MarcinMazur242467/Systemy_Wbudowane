################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCU/src/lpc17xx_clkpwr.c \
../MCU/src/lpc17xx_gpio.c \
../MCU/src/lpc17xx_nvic.c \
../MCU/src/lpc17xx_pinsel.c \
../MCU/src/lpc17xx_systick.c \
../MCU/src/lpc17xx_timer.c 

OBJS += \
./MCU/src/lpc17xx_clkpwr.o \
./MCU/src/lpc17xx_gpio.o \
./MCU/src/lpc17xx_nvic.o \
./MCU/src/lpc17xx_pinsel.o \
./MCU/src/lpc17xx_systick.o \
./MCU/src/lpc17xx_timer.o 

C_DEPS += \
./MCU/src/lpc17xx_clkpwr.d \
./MCU/src/lpc17xx_gpio.d \
./MCU/src/lpc17xx_nvic.d \
./MCU/src/lpc17xx_pinsel.d \
./MCU/src/lpc17xx_systick.d \
./MCU/src/lpc17xx_timer.d 


# Each subdirectory must supply rules for building sources it contributes
MCU/src/%.o: ../MCU/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"C:\mp3\MiniDemo1769\CMSIS\inc" -I"C:\mp3\MiniDemo1769\MCU\inc" -O0 -g3 -c -fmessage-length=0 -fno-builtin -ffunction-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


