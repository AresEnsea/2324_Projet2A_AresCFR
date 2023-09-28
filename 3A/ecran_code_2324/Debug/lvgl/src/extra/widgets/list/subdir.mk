################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/extra/widgets/list/lv_list.c 

OBJS += \
./lvgl/src/extra/widgets/list/lv_list.o 

C_DEPS += \
./lvgl/src/extra/widgets/list/lv_list.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/extra/widgets/list/%.o lvgl/src/extra/widgets/list/%.su lvgl/src/extra/widgets/list/%.cyclo: ../lvgl/src/extra/widgets/list/%.c lvgl/src/extra/widgets/list/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/core" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/HAL_Driver/Inc" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/Utilities/STM32746G-Discovery" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/device" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/inc" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-extra-2f-widgets-2f-list

clean-lvgl-2f-src-2f-extra-2f-widgets-2f-list:
	-$(RM) ./lvgl/src/extra/widgets/list/lv_list.cyclo ./lvgl/src/extra/widgets/list/lv_list.d ./lvgl/src/extra/widgets/list/lv_list.o ./lvgl/src/extra/widgets/list/lv_list.su

.PHONY: clean-lvgl-2f-src-2f-extra-2f-widgets-2f-list

