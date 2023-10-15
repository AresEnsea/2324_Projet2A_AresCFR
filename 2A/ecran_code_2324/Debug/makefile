################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include lvgl/tests/unity/subdir.mk
-include lvgl/tests/src/test_fonts/subdir.mk
-include lvgl/tests/src/test_cases/subdir.mk
-include lvgl/tests/src/subdir.mk
-include lvgl/src/widgets/subdir.mk
-include lvgl/src/misc/subdir.mk
-include lvgl/src/hal/subdir.mk
-include lvgl/src/font/subdir.mk
-include lvgl/src/extra/widgets/win/subdir.mk
-include lvgl/src/extra/widgets/tileview/subdir.mk
-include lvgl/src/extra/widgets/tabview/subdir.mk
-include lvgl/src/extra/widgets/spinner/subdir.mk
-include lvgl/src/extra/widgets/spinbox/subdir.mk
-include lvgl/src/extra/widgets/span/subdir.mk
-include lvgl/src/extra/widgets/msgbox/subdir.mk
-include lvgl/src/extra/widgets/meter/subdir.mk
-include lvgl/src/extra/widgets/menu/subdir.mk
-include lvgl/src/extra/widgets/list/subdir.mk
-include lvgl/src/extra/widgets/led/subdir.mk
-include lvgl/src/extra/widgets/keyboard/subdir.mk
-include lvgl/src/extra/widgets/imgbtn/subdir.mk
-include lvgl/src/extra/widgets/colorwheel/subdir.mk
-include lvgl/src/extra/widgets/chart/subdir.mk
-include lvgl/src/extra/widgets/calendar/subdir.mk
-include lvgl/src/extra/widgets/animimg/subdir.mk
-include lvgl/src/extra/themes/mono/subdir.mk
-include lvgl/src/extra/themes/default/subdir.mk
-include lvgl/src/extra/themes/basic/subdir.mk
-include lvgl/src/extra/others/snapshot/subdir.mk
-include lvgl/src/extra/others/monkey/subdir.mk
-include lvgl/src/extra/others/gridnav/subdir.mk
-include lvgl/src/extra/libs/sjpg/subdir.mk
-include lvgl/src/extra/libs/rlottie/subdir.mk
-include lvgl/src/extra/libs/qrcode/subdir.mk
-include lvgl/src/extra/libs/png/subdir.mk
-include lvgl/src/extra/libs/gif/subdir.mk
-include lvgl/src/extra/libs/fsdrv/subdir.mk
-include lvgl/src/extra/libs/freetype/subdir.mk
-include lvgl/src/extra/libs/ffmpeg/subdir.mk
-include lvgl/src/extra/libs/bmp/subdir.mk
-include lvgl/src/extra/layouts/grid/subdir.mk
-include lvgl/src/extra/layouts/flex/subdir.mk
-include lvgl/src/extra/subdir.mk
-include lvgl/src/draw/sw/subdir.mk
-include lvgl/src/draw/stm32_dma2d/subdir.mk
-include lvgl/src/draw/sdl/subdir.mk
-include lvgl/src/draw/nxp_vglite/subdir.mk
-include lvgl/src/draw/nxp_pxp/subdir.mk
-include lvgl/src/draw/subdir.mk
-include lvgl/src/core/subdir.mk
-include lvgl/env_support/rt-thread/subdir.mk
-include hal_stm_lvgl/touchpad/subdir.mk
-include hal_stm_lvgl/tft/subdir.mk
-include Utilities/STM32746G-Discovery/subdir.mk
-include Utilities/Components/wm8994/subdir.mk
-include Utilities/Components/ts3510/subdir.mk
-include Utilities/Components/stmpe811/subdir.mk
-include Utilities/Components/st7789h2/subdir.mk
-include Utilities/Components/st7735/subdir.mk
-include Utilities/Components/s5k5cag/subdir.mk
-include Utilities/Components/ov9655/subdir.mk
-include Utilities/Components/otm8009a/subdir.mk
-include Utilities/Components/mfxstm32l152/subdir.mk
-include Utilities/Components/ft6x06/subdir.mk
-include Utilities/Components/ft5336/subdir.mk
-include Utilities/Components/exc7200/subdir.mk
-include Utilities/Components/adv7533/subdir.mk
-include Image/subdir.mk
-include HAL_Driver/Src/Legacy/subdir.mk
-include HAL_Driver/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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


BUILD_ARTIFACT_NAME := ecran_code_2324
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ecran_code_2324.elf \

MAP_FILES += \
ecran_code_2324.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ecran_code_2324.list \

OBJCOPY_BIN += \
ecran_code_2324.bin \


# All Target
all: main-build

# Main-build Target
main-build: ecran_code_2324.elf secondary-outputs

# Tool invocations
ecran_code_2324.elf ecran_code_2324.map: $(OBJS) $(USER_OBJS) /home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/LinkerScript.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "ecran_code_2324.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/LinkerScript.ld" --specs=nosys.specs -Wl,-Map="ecran_code_2324.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ecran_code_2324.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ecran_code_2324.list"
	@echo 'Finished building: $@'
	@echo ' '

ecran_code_2324.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ecran_code_2324.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout ecran_code_2324.bin ecran_code_2324.elf ecran_code_2324.list ecran_code_2324.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
