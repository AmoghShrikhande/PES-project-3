################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../dma/sources/adc.c \
../dma/sources/dma.c \
../dma/sources/main.c \
../dma/sources/uart.c 

OBJS += \
./dma/sources/adc.o \
./dma/sources/dma.o \
./dma/sources/main.o \
./dma/sources/uart.o 

C_DEPS += \
./dma/sources/adc.d \
./dma/sources/dma.d \
./dma/sources/main.d \
./dma/sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
dma/sources/%.o: ../dma/sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -DCPU_MKL25Z128VFM4 -DCPU_MKL25Z128VFM4_cm0plus -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


