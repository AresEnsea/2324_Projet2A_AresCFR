################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal_stm_lvgl/tft/tft.c 

OBJS += \
./hal_stm_lvgl/tft/tft.o 

C_DEPS += \
./hal_stm_lvgl/tft/tft.d 


# Each subdirectory must supply rules for building sources it contributes
hal_stm_lvgl/tft/%.o hal_stm_lvgl/tft/%.su hal_stm_lvgl/tft/%.cyclo: ../hal_stm_lvgl/tft/%.c hal_stm_lvgl/tft/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324" -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/core" -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324/HAL_Driver/Inc" -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324/Utilities/STM32746G-Discovery" -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/device" -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324/inc" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-hal_stm_lvgl-2f-tft

clean-hal_stm_lvgl-2f-tft:
	-$(RM) ./hal_stm_lvgl/tft/tft.cyclo ./hal_stm_lvgl/tft/tft.d ./hal_stm_lvgl/tft/tft.o ./hal_stm_lvgl/tft/tft.su

.PHONY: clean-hal_stm_lvgl-2f-tft

