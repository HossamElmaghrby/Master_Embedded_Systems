################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Keypad/Keypad.c 

OBJS += \
./HAL/Keypad/Keypad.o 

C_DEPS += \
./HAL/Keypad/Keypad.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Keypad/Keypad.o: ../HAL/Keypad/Keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mastring Embedded System(online)/Codes/Unit14_Mastering_ARM_CortexM3_4/Session3/ARM_Course/HAL" -I"D:/Mastring Embedded System(online)/Codes/Unit14_Mastering_ARM_CortexM3_4/Session3/ARM_Course/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Keypad/Keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

