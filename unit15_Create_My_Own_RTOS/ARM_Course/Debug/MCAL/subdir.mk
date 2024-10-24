################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/stm32f103x6_EXTI_Driver.c \
../MCAL/stm32f103x6_GPIO_Driver.c \
../MCAL/stm32f103x6_RCC_Driver.c 

OBJS += \
./MCAL/stm32f103x6_EXTI_Driver.o \
./MCAL/stm32f103x6_GPIO_Driver.o \
./MCAL/stm32f103x6_RCC_Driver.o 

C_DEPS += \
./MCAL/stm32f103x6_EXTI_Driver.d \
./MCAL/stm32f103x6_GPIO_Driver.d \
./MCAL/stm32f103x6_RCC_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/stm32f103x6_EXTI_Driver.o: ../MCAL/stm32f103x6_EXTI_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/My _RTOS/inc" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/CMSIS_V5" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/HAL" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/stm32f103x6_EXTI_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/stm32f103x6_GPIO_Driver.o: ../MCAL/stm32f103x6_GPIO_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/My _RTOS/inc" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/CMSIS_V5" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/HAL" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/stm32f103x6_GPIO_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/stm32f103x6_RCC_Driver.o: ../MCAL/stm32f103x6_RCC_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/My _RTOS/inc" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/CMSIS_V5" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/HAL" -I"D:/Mastring Embedded System(online)/Codes/Unit15_Create_My_Own_RTOS/ARM_Course/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/stm32f103x6_RCC_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

