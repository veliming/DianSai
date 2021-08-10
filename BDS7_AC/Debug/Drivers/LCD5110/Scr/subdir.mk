################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LCD5110/Scr/lcd5510.c 

OBJS += \
./Drivers/LCD5110/Scr/lcd5510.o 

C_DEPS += \
./Drivers/LCD5110/Scr/lcd5510.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LCD5110/Scr/%.o: ../Drivers/LCD5110/Scr/%.c Drivers/LCD5110/Scr/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/DSP/Include -I../Drivers/ADS8688/Inc -I../Drivers/LCDandTOUCH/Inc -I../Drivers/Obase/Inc -I../Drivers/LCD5110/Inc -I../Drivers/output/Inc -I../Drivers/TFT_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

