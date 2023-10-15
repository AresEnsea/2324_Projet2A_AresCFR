################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/env_support/rt-thread/lv_rt_thread_port.c 

OBJS += \
./lvgl/env_support/rt-thread/lv_rt_thread_port.o 

C_DEPS += \
./lvgl/env_support/rt-thread/lv_rt_thread_port.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/env_support/rt-thread/%.o lvgl/env_support/rt-thread/%.su lvgl/env_support/rt-thread/%.cyclo: ../lvgl/env_support/rt-thread/%.c lvgl/env_support/rt-thread/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/CMSIS/core" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/HAL_Driver/Inc" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/Utilities/STM32746G-Discovery" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/CMSIS/device" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/inc" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-env_support-2f-rt-2d-thread

clean-lvgl-2f-env_support-2f-rt-2d-thread:
	-$(RM) ./lvgl/env_support/rt-thread/lv_rt_thread_port.cyclo ./lvgl/env_support/rt-thread/lv_rt_thread_port.d ./lvgl/env_support/rt-thread/lv_rt_thread_port.o ./lvgl/env_support/rt-thread/lv_rt_thread_port.su

.PHONY: clean-lvgl-2f-env_support-2f-rt-2d-thread

