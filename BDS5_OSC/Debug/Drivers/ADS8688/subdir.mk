################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ADS8688/ADS8688.c 

OBJS += \
./Drivers/ADS8688/ADS8688.o 

C_DEPS += \
./Drivers/ADS8688/ADS8688.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ADS8688/ADS8688.o: ../Drivers/ADS8688/ADS8688.c Drivers/ADS8688/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__TARGET_FPU_VFP -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Work-Ele/A-KEIL/BDS5_OSC/Drivers/DSP" -I"D:/Work-Ele/A-KEIL/BDS5_OSC/Drivers/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/ADS8688/ADS8688.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

