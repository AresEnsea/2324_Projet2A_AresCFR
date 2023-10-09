################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Prod/Src/avoidance.c \
../Prod/Src/bezier.c \
../Prod/Src/control.c \
../Prod/Src/drv8825.c \
../Prod/Src/lidar.c \
../Prod/Src/lidarReading.c \
../Prod/Src/odometry.c \
../Prod/Src/propulsion.c \
../Prod/Src/serial.c \
../Prod/Src/strategy.c \
../Prod/Src/symetry.c \
../Prod/Src/vector2.c 

OBJS += \
./Prod/Src/avoidance.o \
./Prod/Src/bezier.o \
./Prod/Src/control.o \
./Prod/Src/drv8825.o \
./Prod/Src/lidar.o \
./Prod/Src/lidarReading.o \
./Prod/Src/odometry.o \
./Prod/Src/propulsion.o \
./Prod/Src/serial.o \
./Prod/Src/strategy.o \
./Prod/Src/symetry.o \
./Prod/Src/vector2.o 

C_DEPS += \
./Prod/Src/avoidance.d \
./Prod/Src/bezier.d \
./Prod/Src/control.d \
./Prod/Src/drv8825.d \
./Prod/Src/lidar.d \
./Prod/Src/lidarReading.d \
./Prod/Src/odometry.d \
./Prod/Src/propulsion.d \
./Prod/Src/serial.d \
./Prod/Src/strategy.d \
./Prod/Src/symetry.d \
./Prod/Src/vector2.d 


# Each subdirectory must supply rules for building sources it contributes
Prod/Src/%.o Prod/Src/%.su Prod/Src/%.cyclo: ../Prod/Src/%.c Prod/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Prod/Inc -I../Prod/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Prod-2f-Src

clean-Prod-2f-Src:
	-$(RM) ./Prod/Src/avoidance.cyclo ./Prod/Src/avoidance.d ./Prod/Src/avoidance.o ./Prod/Src/avoidance.su ./Prod/Src/bezier.cyclo ./Prod/Src/bezier.d ./Prod/Src/bezier.o ./Prod/Src/bezier.su ./Prod/Src/control.cyclo ./Prod/Src/control.d ./Prod/Src/control.o ./Prod/Src/control.su ./Prod/Src/drv8825.cyclo ./Prod/Src/drv8825.d ./Prod/Src/drv8825.o ./Prod/Src/drv8825.su ./Prod/Src/lidar.cyclo ./Prod/Src/lidar.d ./Prod/Src/lidar.o ./Prod/Src/lidar.su ./Prod/Src/lidarReading.cyclo ./Prod/Src/lidarReading.d ./Prod/Src/lidarReading.o ./Prod/Src/lidarReading.su ./Prod/Src/odometry.cyclo ./Prod/Src/odometry.d ./Prod/Src/odometry.o ./Prod/Src/odometry.su ./Prod/Src/propulsion.cyclo ./Prod/Src/propulsion.d ./Prod/Src/propulsion.o ./Prod/Src/propulsion.su ./Prod/Src/serial.cyclo ./Prod/Src/serial.d ./Prod/Src/serial.o ./Prod/Src/serial.su ./Prod/Src/strategy.cyclo ./Prod/Src/strategy.d ./Prod/Src/strategy.o ./Prod/Src/strategy.su ./Prod/Src/symetry.cyclo ./Prod/Src/symetry.d ./Prod/Src/symetry.o ./Prod/Src/symetry.su ./Prod/Src/vector2.cyclo ./Prod/Src/vector2.d ./Prod/Src/vector2.o ./Prod/Src/vector2.su

.PHONY: clean-Prod-2f-Src

