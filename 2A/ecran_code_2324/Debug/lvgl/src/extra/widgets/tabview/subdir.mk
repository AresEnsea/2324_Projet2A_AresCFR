################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/extra/widgets/tabview/lv_tabview.c 

OBJS += \
./lvgl/src/extra/widgets/tabview/lv_tabview.o 

C_DEPS += \
./lvgl/src/extra/widgets/tabview/lv_tabview.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/extra/widgets/tabview/%.o lvgl/src/extra/widgets/tabview/%.su lvgl/src/extra/widgets/tabview/%.cyclo: ../lvgl/src/extra/widgets/tabview/%.c lvgl/src/extra/widgets/tabview/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/CMSIS/core" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/HAL_Driver/Inc" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/Utilities/STM32746G-Discovery" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/CMSIS/device" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/inc" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-extra-2f-widgets-2f-tabview

clean-lvgl-2f-src-2f-extra-2f-widgets-2f-tabview:
	-$(RM) ./lvgl/src/extra/widgets/tabview/lv_tabview.cyclo ./lvgl/src/extra/widgets/tabview/lv_tabview.d ./lvgl/src/extra/widgets/tabview/lv_tabview.o ./lvgl/src/extra/widgets/tabview/lv_tabview.su

.PHONY: clean-lvgl-2f-src-2f-extra-2f-widgets-2f-tabview

