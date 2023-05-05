################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/LED_DRIVER/LED.c 

OBJS += \
./MCAL/LED_DRIVER/LED.o 

C_DEPS += \
./MCAL/LED_DRIVER/LED.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/LED_DRIVER/%.o: ../MCAL/LED_DRIVER/%.c MCAL/LED_DRIVER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


