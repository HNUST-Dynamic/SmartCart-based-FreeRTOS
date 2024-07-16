################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/SmartCartRTOS/Drivers/BSP/LED/led.c 

OBJS += \
./Drivers/BSP/LED/led.o 

C_DEPS += \
./Drivers/BSP/LED/led.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/LED/led.o: F:/SmartCartRTOS/Drivers/BSP/LED/led.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

