################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Prod/Src/vl53l1x_ares_lidar.c 

OBJS += \
./Prod/Src/vl53l1x_ares_lidar.o 

C_DEPS += \
./Prod/Src/vl53l1x_ares_lidar.d 


# Each subdirectory must supply rules for building sources it contributes
Prod/Src/%.o Prod/Src/%.su Prod/Src/%.cyclo: ../Prod/Src/%.c Prod/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Prod/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Prod-2f-Src

clean-Prod-2f-Src:
	-$(RM) ./Prod/Src/vl53l1x_ares_lidar.cyclo ./Prod/Src/vl53l1x_ares_lidar.d ./Prod/Src/vl53l1x_ares_lidar.o ./Prod/Src/vl53l1x_ares_lidar.su

.PHONY: clean-Prod-2f-Src

