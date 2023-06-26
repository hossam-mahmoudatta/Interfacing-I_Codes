################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/USART_DRIVER/subdir.mk
-include MCAL/TIMER_DRIVER/subdir.mk
-include MCAL/SPI_DRIVER/subdir.mk
-include MCAL/ICU_DRIVER/subdir.mk
-include MCAL/I2C_DRIVER/subdir.mk
-include MCAL/GPIO_DRIVER/subdir.mk
-include MCAL/EXT_INTERRUPT_DRIVER/subdir.mk
-include MCAL/ADC_DRIVER/subdir.mk
-include ECUAL/SEVEN-SEGMENT_DRIVER/subdir.mk
-include ECUAL/LM35_DRIVER/subdir.mk
-include ECUAL/LED_DRIVER/subdir.mk
-include ECUAL/LCD_DRIVER/subdir.mk
-include ECUAL/KEYPAD_DRIVER/subdir.mk
-include ECUAL/EEPROM_DRIVER/subdir.mk
-include ECUAL/BUTTON_DRIVER/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := TIMER_EX2_HOSA
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
TIMER_EX2_HOSA.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: main-build

# Main-build Target
main-build: TIMER_EX2_HOSA.elf secondary-outputs

# Tool invocations
TIMER_EX2_HOSA.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,TIMER_EX2_HOSA.map -mmcu=atmega16 -o "TIMER_EX2_HOSA.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

TIMER_EX2_HOSA.lss: TIMER_EX2_HOSA.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S TIMER_EX2_HOSA.elf  >"TIMER_EX2_HOSA.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: TIMER_EX2_HOSA.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 TIMER_EX2_HOSA.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) TIMER_EX2_HOSA.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents main-build

-include ../makefile.targets
