################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Seven_segment/Seven_segment.c 

OBJS += \
./HAL/Seven_segment/Seven_segment.o 

C_DEPS += \
./HAL/Seven_segment/Seven_segment.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Seven_segment/Seven_segment.o: ../HAL/Seven_segment/Seven_segment.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mastring Embedded System(online)/Codes/Unit14_Mastering_ARM_CortexM3_4/ARM_Course/HAL" -I"D:/Mastring Embedded System(online)/Codes/Unit14_Mastering_ARM_CortexM3_4/ARM_Course/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Seven_segment/Seven_segment.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

