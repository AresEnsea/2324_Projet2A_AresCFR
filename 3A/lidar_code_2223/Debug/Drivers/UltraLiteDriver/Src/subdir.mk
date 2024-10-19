################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UltraLiteDriver/Src/VL53L1X_api.c \
../Drivers/UltraLiteDriver/Src/VL53L1X_calibration.c \
../Drivers/UltraLiteDriver/Src/platform.c \
../Drivers/UltraLiteDriver/Src/platform_specific.c 

OBJS += \
./Drivers/UltraLiteDriver/Src/VL53L1X_api.o \
./Drivers/UltraLiteDriver/Src/VL53L1X_calibration.o \
./Drivers/UltraLiteDriver/Src/platform.o \
./Drivers/UltraLiteDriver/Src/platform_specific.o 

C_DEPS += \
./Drivers/UltraLiteDriver/Src/VL53L1X_api.d \
./Drivers/UltraLiteDriver/Src/VL53L1X_calibration.d \
./Drivers/UltraLiteDriver/Src/platform.d \
./Drivers/UltraLiteDriver/Src/platform_specific.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UltraLiteDriver/Src/%.o Drivers/UltraLiteDriver/Src/%.su Drivers/UltraLiteDriver/Src/%.cyclo: ../Drivers/UltraLiteDriver/Src/%.c Drivers/UltraLiteDriver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Core/Inc -I"D:/Oldone/louis/Desktop/2324_Projet2A_AresCFR/3A/lidar_code_2223/Core/Startup" -I"D:/Oldone/louis/Desktop/2324_Projet2A_AresCFR/3A/lidar_code_2223/Drivers/UltraLiteDriver/Inc" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-UltraLiteDriver-2f-Src

clean-Drivers-2f-UltraLiteDriver-2f-Src:
	-$(RM) ./Drivers/UltraLiteDriver/Src/VL53L1X_api.cyclo ./Drivers/UltraLiteDriver/Src/VL53L1X_api.d ./Drivers/UltraLiteDriver/Src/VL53L1X_api.o ./Drivers/UltraLiteDriver/Src/VL53L1X_api.su ./Drivers/UltraLiteDriver/Src/VL53L1X_calibration.cyclo ./Drivers/UltraLiteDriver/Src/VL53L1X_calibration.d ./Drivers/UltraLiteDriver/Src/VL53L1X_calibration.o ./Drivers/UltraLiteDriver/Src/VL53L1X_calibration.su ./Drivers/UltraLiteDriver/Src/platform.cyclo ./Drivers/UltraLiteDriver/Src/platform.d ./Drivers/UltraLiteDriver/Src/platform.o ./Drivers/UltraLiteDriver/Src/platform.su ./Drivers/UltraLiteDriver/Src/platform_specific.cyclo ./Drivers/UltraLiteDriver/Src/platform_specific.d ./Drivers/UltraLiteDriver/Src/platform_specific.o ./Drivers/UltraLiteDriver/Src/platform_specific.su

.PHONY: clean-Drivers-2f-UltraLiteDriver-2f-Src

