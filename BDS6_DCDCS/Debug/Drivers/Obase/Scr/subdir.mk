################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Obase/Scr/obase.c 

OBJS += \
./Drivers/Obase/Scr/obase.o 

C_DEPS += \
./Drivers/Obase/Scr/obase.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Obase/Scr/%.o: ../Drivers/Obase/Scr/%.c Drivers/Obase/Scr/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/DSP/Include -I../Drivers/ADS8688/Inc -I../Drivers/LCDandTOUCH/Inc -I../Drivers/Obase/Inc -I../Drivers/LCD5110/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Obase-2f-Scr

clean-Drivers-2f-Obase-2f-Scr:
	-$(RM) ./Drivers/Obase/Scr/obase.d ./Drivers/Obase/Scr/obase.o

.PHONY: clean-Drivers-2f-Obase-2f-Scr

