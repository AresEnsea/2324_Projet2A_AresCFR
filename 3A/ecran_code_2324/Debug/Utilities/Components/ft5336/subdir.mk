################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/ft5336/ft5336.c 

OBJS += \
./Utilities/Components/ft5336/ft5336.o 

C_DEPS += \
./Utilities/Components/ft5336/ft5336.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/ft5336/%.o Utilities/Components/ft5336/%.su Utilities/Components/ft5336/%.cyclo: ../Utilities/Components/ft5336/%.c Utilities/Components/ft5336/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/core" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/HAL_Driver/Inc" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/Utilities/STM32746G-Discovery" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/CMSIS/device" -I"C:/Users/louis/Desktop/2324_Projet2A_AresCFR/3A/ecran_code_2324/inc" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utilities-2f-Components-2f-ft5336

clean-Utilities-2f-Components-2f-ft5336:
	-$(RM) ./Utilities/Components/ft5336/ft5336.cyclo ./Utilities/Components/ft5336/ft5336.d ./Utilities/Components/ft5336/ft5336.o ./Utilities/Components/ft5336/ft5336.su

.PHONY: clean-Utilities-2f-Components-2f-ft5336

