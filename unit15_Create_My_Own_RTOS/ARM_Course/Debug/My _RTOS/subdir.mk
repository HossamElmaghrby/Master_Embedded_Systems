################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../My\ _RTOS/CortexMX_OS_Porting.c \
../My\ _RTOS/MYRTOS_FIFO.c \
../My\ _RTOS/Scheduler.c 

OBJS += \
./My\ _RTOS/CortexMX_OS_Porting.o \
./My\ _RTOS/MYRTOS_FIFO.o \
./My\ _RTOS/Scheduler.o 

C_DEPS += \
./My\ _RTOS/CortexMX_OS_Porting.d \
./My\ _RTOS/MYRTOS_FIFO.d \
./My\ _RTOS/Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
My\ _RTOS/CortexMX_OS_Porting.o: ../My\ _RTOS/CortexMX_OS_Porting.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/My _RTOS/inc" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/CMSIS_V5" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/HAL" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My _RTOS/CortexMX_OS_Porting.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
My\ _RTOS/MYRTOS_FIFO.o: ../My\ _RTOS/MYRTOS_FIFO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/My _RTOS/inc" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/CMSIS_V5" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/HAL" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My _RTOS/MYRTOS_FIFO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
My\ _RTOS/Scheduler.o: ../My\ _RTOS/Scheduler.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/My _RTOS/inc" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/CMSIS_V5" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/HAL" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My _RTOS/Scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

