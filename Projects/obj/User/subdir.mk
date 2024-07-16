################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/SmartCartRTOS/User/HX77.c \
F:/SmartCartRTOS/User/L610.c \
F:/SmartCartRTOS/User/allshow.c \
F:/SmartCartRTOS/User/ch32v30x_it.c \
F:/SmartCartRTOS/User/freertos_demo.c \
F:/SmartCartRTOS/User/main.c \
F:/SmartCartRTOS/User/pages.c \
F:/SmartCartRTOS/User/system_ch32v30x.c 

OBJS += \
./User/HX77.o \
./User/L610.o \
./User/allshow.o \
./User/ch32v30x_it.o \
./User/freertos_demo.o \
./User/main.o \
./User/pages.o \
./User/system_ch32v30x.o 

C_DEPS += \
./User/HX77.d \
./User/L610.d \
./User/allshow.d \
./User/ch32v30x_it.d \
./User/freertos_demo.d \
./User/main.d \
./User/pages.d \
./User/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
User/HX77.o: F:/SmartCartRTOS/User/HX77.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
User/L610.o: F:/SmartCartRTOS/User/L610.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
User/allshow.o: F:/SmartCartRTOS/User/allshow.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
User/ch32v30x_it.o: F:/SmartCartRTOS/User/ch32v30x_it.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
User/freertos_demo.o: F:/SmartCartRTOS/User/freertos_demo.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
User/main.o: F:/SmartCartRTOS/User/main.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
User/pages.o: F:/SmartCartRTOS/User/pages.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
User/system_ch32v30x.o: F:/SmartCartRTOS/User/system_ch32v30x.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

