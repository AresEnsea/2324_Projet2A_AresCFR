################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp.c \
../lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp_osa.c 

OBJS += \
./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp.o \
./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp_osa.o 

C_DEPS += \
./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp.d \
./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp_osa.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/draw/nxp_pxp/%.o lvgl/src/draw/nxp_pxp/%.su lvgl/src/draw/nxp_pxp/%.cyclo: ../lvgl/src/draw/nxp_pxp/%.c lvgl/src/draw/nxp_pxp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/CMSIS/core" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/HAL_Driver/Inc" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/Utilities/STM32746G-Discovery" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/CMSIS/device" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/inc" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-draw-2f-nxp_pxp

clean-lvgl-2f-src-2f-draw-2f-nxp_pxp:
	-$(RM) ./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp.cyclo ./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp.d ./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp.o ./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp.su ./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp_osa.cyclo ./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp_osa.d ./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp_osa.o ./lvgl/src/draw/nxp_pxp/lv_gpu_nxp_pxp_osa.su

.PHONY: clean-lvgl-2f-src-2f-draw-2f-nxp_pxp

