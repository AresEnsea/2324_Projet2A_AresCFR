################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/extra/libs/bmp/lv_bmp.c 

OBJS += \
./lvgl/src/extra/libs/bmp/lv_bmp.o 

C_DEPS += \
./lvgl/src/extra/libs/bmp/lv_bmp.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/extra/libs/bmp/%.o lvgl/src/extra/libs/bmp/%.su lvgl/src/extra/libs/bmp/%.cyclo: ../lvgl/src/extra/libs/bmp/%.c lvgl/src/extra/libs/bmp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324" -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/core" -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324/HAL_Driver/Inc" -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324/Utilities/STM32746G-Discovery" -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/device" -I"C:/Workspace/Git_folders/2324_Projet2A_AresCFR/3A/ecran_code_2324/inc" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-extra-2f-libs-2f-bmp

clean-lvgl-2f-src-2f-extra-2f-libs-2f-bmp:
	-$(RM) ./lvgl/src/extra/libs/bmp/lv_bmp.cyclo ./lvgl/src/extra/libs/bmp/lv_bmp.d ./lvgl/src/extra/libs/bmp/lv_bmp.o ./lvgl/src/extra/libs/bmp/lv_bmp.su

.PHONY: clean-lvgl-2f-src-2f-extra-2f-libs-2f-bmp

