#
# Auto-Generated file. Do not edit!
#

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../ls1x-drv/useful/fls.c \
../ls1x-drv/useful/aligned_malloc.c

OBJS += \
./ls1x-drv/useful/fls.o \
./ls1x-drv/useful/aligned_malloc.o

C_DEPS += \
./ls1x-drv/useful/fls.d \
./ls1x-drv/useful/aligned_malloc.d

# Each subdirectory must supply rules for building sources it contributes
ls1x-drv/useful/%.o: ../ls1x-drv/useful/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	D:/Softwares/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1B -DOS_NONE  -O0 -g -Wall -c -fmessage-length=0 -pipe -I"../" -I"../include" -I"../core/include" -I"../core/mips" -I"../ls1x-drv/include" -I"../src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

