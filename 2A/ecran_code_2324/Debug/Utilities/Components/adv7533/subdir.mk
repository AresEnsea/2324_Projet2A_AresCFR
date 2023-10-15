################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/adv7533/adv7533.c 

OBJS += \
./Utilities/Components/adv7533/adv7533.o 

C_DEPS += \
./Utilities/Components/adv7533/adv7533.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/adv7533/%.o Utilities/Components/adv7533/%.su Utilities/Components/adv7533/%.cyclo: ../Utilities/Components/adv7533/%.c Utilities/Components/adv7533/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/CMSIS/core" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/HAL_Driver/Inc" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/Utilities/STM32746G-Discovery" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/CMSIS/device" -I"/home/mowibox/Documents/WorkspaceU/Git_Folders/2324_Projet2A_AresCFR/2A/ecran_code_2324/inc" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utilities-2f-Components-2f-adv7533

clean-Utilities-2f-Components-2f-adv7533:
	-$(RM) ./Utilities/Components/adv7533/adv7533.cyclo ./Utilities/Components/adv7533/adv7533.d ./Utilities/Components/adv7533/adv7533.o ./Utilities/Components/adv7533/adv7533.su

.PHONY: clean-Utilities-2f-Components-2f-adv7533

