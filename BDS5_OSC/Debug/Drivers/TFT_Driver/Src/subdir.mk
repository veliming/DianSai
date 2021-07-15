################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/TFT_Driver/Src/cmd_process.c \
../Drivers/TFT_Driver/Src/cmd_queue.c \
../Drivers/TFT_Driver/Src/hmi_driver.c \
../Drivers/TFT_Driver/Src/hmi_user_uart.c 

OBJS += \
./Drivers/TFT_Driver/Src/cmd_process.o \
./Drivers/TFT_Driver/Src/cmd_queue.o \
./Drivers/TFT_Driver/Src/hmi_driver.o \
./Drivers/TFT_Driver/Src/hmi_user_uart.o 

C_DEPS += \
./Drivers/TFT_Driver/Src/cmd_process.d \
./Drivers/TFT_Driver/Src/cmd_queue.d \
./Drivers/TFT_Driver/Src/hmi_driver.d \
./Drivers/TFT_Driver/Src/hmi_user_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/TFT_Driver/Src/cmd_process.o: ../Drivers/TFT_Driver/Src/cmd_process.c Drivers/TFT_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__TARGET_FPU_VFP -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/DSP -I../Drivers/DSP/Include -I../Drivers/ADS8688/Inc -I../Drivers/TFT_Driver/Inc -I../Drivers/LCDandTOUCH/Inc -I../Drivers/Obase/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/TFT_Driver/Src/cmd_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/TFT_Driver/Src/cmd_queue.o: ../Drivers/TFT_Driver/Src/cmd_queue.c Drivers/TFT_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__TARGET_FPU_VFP -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/DSP -I../Drivers/DSP/Include -I../Drivers/ADS8688/Inc -I../Drivers/TFT_Driver/Inc -I../Drivers/LCDandTOUCH/Inc -I../Drivers/Obase/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/TFT_Driver/Src/cmd_queue.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/TFT_Driver/Src/hmi_driver.o: ../Drivers/TFT_Driver/Src/hmi_driver.c Drivers/TFT_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__TARGET_FPU_VFP -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/DSP -I../Drivers/DSP/Include -I../Drivers/ADS8688/Inc -I../Drivers/TFT_Driver/Inc -I../Drivers/LCDandTOUCH/Inc -I../Drivers/Obase/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/TFT_Driver/Src/hmi_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/TFT_Driver/Src/hmi_user_uart.o: ../Drivers/TFT_Driver/Src/hmi_user_uart.c Drivers/TFT_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__TARGET_FPU_VFP -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/DSP -I../Drivers/DSP/Include -I../Drivers/ADS8688/Inc -I../Drivers/TFT_Driver/Inc -I../Drivers/LCDandTOUCH/Inc -I../Drivers/Obase/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/TFT_Driver/Src/hmi_user_uart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

