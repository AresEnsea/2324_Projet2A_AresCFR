################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/tests/src/test_cases/_test_template.c \
../lvgl/tests/src/test_cases/test_arc.c \
../lvgl/tests/src/test_cases/test_bar.c \
../lvgl/tests/src/test_cases/test_checkbox.c \
../lvgl/tests/src/test_cases/test_config.c \
../lvgl/tests/src/test_cases/test_demo_stress.c \
../lvgl/tests/src/test_cases/test_demo_widgets.c \
../lvgl/tests/src/test_cases/test_dropdown.c \
../lvgl/tests/src/test_cases/test_event.c \
../lvgl/tests/src/test_cases/test_font_loader.c \
../lvgl/tests/src/test_cases/test_obj_tree.c \
../lvgl/tests/src/test_cases/test_snapshot.c \
../lvgl/tests/src/test_cases/test_style.c \
../lvgl/tests/src/test_cases/test_switch.c \
../lvgl/tests/src/test_cases/test_txt.c 

OBJS += \
./lvgl/tests/src/test_cases/_test_template.o \
./lvgl/tests/src/test_cases/test_arc.o \
./lvgl/tests/src/test_cases/test_bar.o \
./lvgl/tests/src/test_cases/test_checkbox.o \
./lvgl/tests/src/test_cases/test_config.o \
./lvgl/tests/src/test_cases/test_demo_stress.o \
./lvgl/tests/src/test_cases/test_demo_widgets.o \
./lvgl/tests/src/test_cases/test_dropdown.o \
./lvgl/tests/src/test_cases/test_event.o \
./lvgl/tests/src/test_cases/test_font_loader.o \
./lvgl/tests/src/test_cases/test_obj_tree.o \
./lvgl/tests/src/test_cases/test_snapshot.o \
./lvgl/tests/src/test_cases/test_style.o \
./lvgl/tests/src/test_cases/test_switch.o \
./lvgl/tests/src/test_cases/test_txt.o 

C_DEPS += \
./lvgl/tests/src/test_cases/_test_template.d \
./lvgl/tests/src/test_cases/test_arc.d \
./lvgl/tests/src/test_cases/test_bar.d \
./lvgl/tests/src/test_cases/test_checkbox.d \
./lvgl/tests/src/test_cases/test_config.d \
./lvgl/tests/src/test_cases/test_demo_stress.d \
./lvgl/tests/src/test_cases/test_demo_widgets.d \
./lvgl/tests/src/test_cases/test_dropdown.d \
./lvgl/tests/src/test_cases/test_event.d \
./lvgl/tests/src/test_cases/test_font_loader.d \
./lvgl/tests/src/test_cases/test_obj_tree.d \
./lvgl/tests/src/test_cases/test_snapshot.d \
./lvgl/tests/src/test_cases/test_style.d \
./lvgl/tests/src/test_cases/test_switch.d \
./lvgl/tests/src/test_cases/test_txt.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/tests/src/test_cases/%.o lvgl/tests/src/test_cases/%.su lvgl/tests/src/test_cases/%.cyclo: ../lvgl/tests/src/test_cases/%.c lvgl/tests/src/test_cases/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/core" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/HAL_Driver/Inc" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/Utilities/STM32746G-Discovery" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/device" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/inc" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-tests-2f-src-2f-test_cases

clean-lvgl-2f-tests-2f-src-2f-test_cases:
	-$(RM) ./lvgl/tests/src/test_cases/_test_template.cyclo ./lvgl/tests/src/test_cases/_test_template.d ./lvgl/tests/src/test_cases/_test_template.o ./lvgl/tests/src/test_cases/_test_template.su ./lvgl/tests/src/test_cases/test_arc.cyclo ./lvgl/tests/src/test_cases/test_arc.d ./lvgl/tests/src/test_cases/test_arc.o ./lvgl/tests/src/test_cases/test_arc.su ./lvgl/tests/src/test_cases/test_bar.cyclo ./lvgl/tests/src/test_cases/test_bar.d ./lvgl/tests/src/test_cases/test_bar.o ./lvgl/tests/src/test_cases/test_bar.su ./lvgl/tests/src/test_cases/test_checkbox.cyclo ./lvgl/tests/src/test_cases/test_checkbox.d ./lvgl/tests/src/test_cases/test_checkbox.o ./lvgl/tests/src/test_cases/test_checkbox.su ./lvgl/tests/src/test_cases/test_config.cyclo ./lvgl/tests/src/test_cases/test_config.d ./lvgl/tests/src/test_cases/test_config.o ./lvgl/tests/src/test_cases/test_config.su ./lvgl/tests/src/test_cases/test_demo_stress.cyclo ./lvgl/tests/src/test_cases/test_demo_stress.d ./lvgl/tests/src/test_cases/test_demo_stress.o ./lvgl/tests/src/test_cases/test_demo_stress.su ./lvgl/tests/src/test_cases/test_demo_widgets.cyclo ./lvgl/tests/src/test_cases/test_demo_widgets.d ./lvgl/tests/src/test_cases/test_demo_widgets.o ./lvgl/tests/src/test_cases/test_demo_widgets.su ./lvgl/tests/src/test_cases/test_dropdown.cyclo ./lvgl/tests/src/test_cases/test_dropdown.d ./lvgl/tests/src/test_cases/test_dropdown.o ./lvgl/tests/src/test_cases/test_dropdown.su ./lvgl/tests/src/test_cases/test_event.cyclo ./lvgl/tests/src/test_cases/test_event.d ./lvgl/tests/src/test_cases/test_event.o ./lvgl/tests/src/test_cases/test_event.su ./lvgl/tests/src/test_cases/test_font_loader.cyclo ./lvgl/tests/src/test_cases/test_font_loader.d ./lvgl/tests/src/test_cases/test_font_loader.o ./lvgl/tests/src/test_cases/test_font_loader.su ./lvgl/tests/src/test_cases/test_obj_tree.cyclo ./lvgl/tests/src/test_cases/test_obj_tree.d ./lvgl/tests/src/test_cases/test_obj_tree.o ./lvgl/tests/src/test_cases/test_obj_tree.su ./lvgl/tests/src/test_cases/test_snapshot.cyclo ./lvgl/tests/src/test_cases/test_snapshot.d ./lvgl/tests/src/test_cases/test_snapshot.o ./lvgl/tests/src/test_cases/test_snapshot.su ./lvgl/tests/src/test_cases/test_style.cyclo ./lvgl/tests/src/test_cases/test_style.d ./lvgl/tests/src/test_cases/test_style.o ./lvgl/tests/src/test_cases/test_style.su ./lvgl/tests/src/test_cases/test_switch.cyclo ./lvgl/tests/src/test_cases/test_switch.d ./lvgl/tests/src/test_cases/test_switch.o ./lvgl/tests/src/test_cases/test_switch.su ./lvgl/tests/src/test_cases/test_txt.cyclo ./lvgl/tests/src/test_cases/test_txt.d ./lvgl/tests/src/test_cases/test_txt.o ./lvgl/tests/src/test_cases/test_txt.su

.PHONY: clean-lvgl-2f-tests-2f-src-2f-test_cases

