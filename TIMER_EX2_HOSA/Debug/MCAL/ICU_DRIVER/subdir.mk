################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/ICU_DRIVER/ICU.c 

OBJS += \
./MCAL/ICU_DRIVER/ICU.o 

C_DEPS += \
./MCAL/ICU_DRIVER/ICU.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/ICU_DRIVER/%.o: ../MCAL/ICU_DRIVER/%.c MCAL/ICU_DRIVER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


