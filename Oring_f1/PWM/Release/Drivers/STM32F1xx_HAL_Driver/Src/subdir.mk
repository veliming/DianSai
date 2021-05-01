################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sram.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c \
../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.c 

OBJS += \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sram.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.o \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.o 

C_DEPS += \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sram.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.d \
./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sram.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sram.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sram.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

