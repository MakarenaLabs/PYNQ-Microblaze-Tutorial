################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
main.elf.size \


# All Target
all: main.elf secondary-outputs

# Tool invocations
main.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze gcc linker'
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L/home/pynq/workspace_vitis_ide/microblaze/export/microblaze/sw/microblaze/standalone_domain/bsplib/lib -mlittle-endian -mcpu=v11.0 -mxl-soft-mul -Wl,--no-relax -Wl,--gc-sections -o "main.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

main.elf.size: main.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size main.elf  |tee "main.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

main.bin: main.elf
	@echo 'Invoking: MicroBlaze Bin Gen'
	mb-objcopy -O binary main.elf main.bin
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(S_UPPER_DEPS)$(C_DEPS)$(ELFSIZE) main.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) main.bin

.PHONY: all clean dependents

-include ../makefile.targets
