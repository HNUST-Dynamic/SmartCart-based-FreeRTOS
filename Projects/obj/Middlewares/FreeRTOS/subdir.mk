################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/SmartCartRTOS/Middlewares/FreeRTOS/croutine.c \
F:/SmartCartRTOS/Middlewares/FreeRTOS/event_groups.c \
F:/SmartCartRTOS/Middlewares/FreeRTOS/list.c \
F:/SmartCartRTOS/Middlewares/FreeRTOS/queue.c \
F:/SmartCartRTOS/Middlewares/FreeRTOS/stream_buffer.c \
F:/SmartCartRTOS/Middlewares/FreeRTOS/tasks.c \
F:/SmartCartRTOS/Middlewares/FreeRTOS/timers.c 

OBJS += \
./Middlewares/FreeRTOS/croutine.o \
./Middlewares/FreeRTOS/event_groups.o \
./Middlewares/FreeRTOS/list.o \
./Middlewares/FreeRTOS/queue.o \
./Middlewares/FreeRTOS/stream_buffer.o \
./Middlewares/FreeRTOS/tasks.o \
./Middlewares/FreeRTOS/timers.o 

C_DEPS += \
./Middlewares/FreeRTOS/croutine.d \
./Middlewares/FreeRTOS/event_groups.d \
./Middlewares/FreeRTOS/list.d \
./Middlewares/FreeRTOS/queue.d \
./Middlewares/FreeRTOS/stream_buffer.d \
./Middlewares/FreeRTOS/tasks.d \
./Middlewares/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/croutine.o: F:/SmartCartRTOS/Middlewares/FreeRTOS/croutine.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/event_groups.o: F:/SmartCartRTOS/Middlewares/FreeRTOS/event_groups.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/list.o: F:/SmartCartRTOS/Middlewares/FreeRTOS/list.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/queue.o: F:/SmartCartRTOS/Middlewares/FreeRTOS/queue.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/stream_buffer.o: F:/SmartCartRTOS/Middlewares/FreeRTOS/stream_buffer.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/tasks.o: F:/SmartCartRTOS/Middlewares/FreeRTOS/tasks.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/timers.o: F:/SmartCartRTOS/Middlewares/FreeRTOS/timers.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\SmartCartRTOS\User" -I"F:\SmartCartRTOS\Drivers\RISC_V\Core" -I"F:\SmartCartRTOS\Middlewares" -I"F:\SmartCartRTOS\Drivers" -I"F:\SmartCartRTOS\Drivers\CH32V30x_Driver\inc" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\include" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\MemMang" -I"F:\SmartCartRTOS\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

