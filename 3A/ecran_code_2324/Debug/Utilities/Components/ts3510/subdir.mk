################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/ts3510/ts3510.c 

OBJS += \
./Utilities/Components/ts3510/ts3510.o 

C_DEPS += \
./Utilities/Components/ts3510/ts3510.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/ts3510/%.o Utilities/Components/ts3510/%.su Utilities/Components/ts3510/%.cyclo: ../Utilities/Components/ts3510/%.c Utilities/Components/ts3510/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/core" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/HAL_Driver/Inc" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/Utilities/STM32746G-Discovery" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/device" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/inc" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utilities-2f-Components-2f-ts3510

clean-Utilities-2f-Components-2f-ts3510:
	-$(RM) ./Utilities/Components/ts3510/ts3510.cyclo ./Utilities/Components/ts3510/ts3510.d ./Utilities/Components/ts3510/ts3510.o ./Utilities/Components/ts3510/ts3510.su

.PHONY: clean-Utilities-2f-Components-2f-ts3510

