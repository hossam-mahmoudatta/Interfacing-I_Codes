################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/SPI_DRIVER/SPI.c 

OBJS += \
./MCAL/SPI_DRIVER/SPI.o 

C_DEPS += \
./MCAL/SPI_DRIVER/SPI.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/SPI_DRIVER/%.o: ../MCAL/SPI_DRIVER/%.c MCAL/SPI_DRIVER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


