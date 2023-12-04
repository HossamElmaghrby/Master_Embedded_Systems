################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/GPIO.c 

OBJS += \
./MCAL/GPIO.o 

C_DEPS += \
./MCAL/GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/GPIO.o: ../MCAL/GPIO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"E:/Mastring Embedded System(online)/Codes/Unit7_MCU_Essential_peripherals/Lesson3/Section_lab/HAL" -I"E:/Mastring Embedded System(online)/Codes/Unit7_MCU_Essential_peripherals/Lesson3/Section_lab/MCAL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/GPIO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

