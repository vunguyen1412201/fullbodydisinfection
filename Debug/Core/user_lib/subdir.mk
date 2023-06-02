################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/user_lib/DFPLAYER.c \
../Core/user_lib/MLX90614.c \
../Core/user_lib/lcd_i2c.c 

OBJS += \
./Core/user_lib/DFPLAYER.o \
./Core/user_lib/MLX90614.o \
./Core/user_lib/lcd_i2c.o 

C_DEPS += \
./Core/user_lib/DFPLAYER.d \
./Core/user_lib/MLX90614.d \
./Core/user_lib/lcd_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Core/user_lib/%.o Core/user_lib/%.su Core/user_lib/%.cyclo: ../Core/user_lib/%.c Core/user_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-user_lib

clean-Core-2f-user_lib:
	-$(RM) ./Core/user_lib/DFPLAYER.cyclo ./Core/user_lib/DFPLAYER.d ./Core/user_lib/DFPLAYER.o ./Core/user_lib/DFPLAYER.su ./Core/user_lib/MLX90614.cyclo ./Core/user_lib/MLX90614.d ./Core/user_lib/MLX90614.o ./Core/user_lib/MLX90614.su ./Core/user_lib/lcd_i2c.cyclo ./Core/user_lib/lcd_i2c.d ./Core/user_lib/lcd_i2c.o ./Core/user_lib/lcd_i2c.su

.PHONY: clean-Core-2f-user_lib

