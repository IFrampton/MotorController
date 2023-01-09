################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Model/MemoryStructure.cpp \
../Model/Protection.cpp 

OBJS += \
./Model/MemoryStructure.o \
./Model/Protection.o 

CPP_DEPS += \
./Model/MemoryStructure.d \
./Model/Protection.d 


# Each subdirectory must supply rules for building sources it contributes
Model/%.o: ../Model/%.cpp Model/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_LPC5502JBD64 -DCPU_LPC5502JBD64_cm33 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\GIT\Davis\MotorController\BoardSupport" -I"C:\GIT\Davis\MotorController\Code" -I"C:\GIT\Davis\MotorController\Device" -I"C:\GIT\Davis\MotorController\Model" -I"C:\GIT\Davis\MotorController\CMSIS" -I"C:\GIT\Davis\MotorController\Interface" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


