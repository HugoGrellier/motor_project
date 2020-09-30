################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MOTOR_Grellier_Leconte.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
MOTOR_Grellier_Leconte.list \

OBJCOPY_BIN += \
MOTOR_Grellier_Leconte.bin \


# All Target
all: MOTOR_Grellier_Leconte.elf secondary-outputs

# Tool invocations
MOTOR_Grellier_Leconte.elf: $(OBJS) $(USER_OBJS) C:\Users\thibault.leconte\Documents\LeconteThibault\MOTOR_Grellier_Leconte\STM32F401RETX_FLASH.ld
	arm-none-eabi-gcc -o "MOTOR_Grellier_Leconte.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\thibault.leconte\Documents\LeconteThibault\MOTOR_Grellier_Leconte\STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="MOTOR_Grellier_Leconte.map" -Wl,--gc-sections -static -u _printf_float --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

MOTOR_Grellier_Leconte.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "MOTOR_Grellier_Leconte.list"
	@echo 'Finished building: $@'
	@echo ' '

MOTOR_Grellier_Leconte.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "MOTOR_Grellier_Leconte.bin"
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
