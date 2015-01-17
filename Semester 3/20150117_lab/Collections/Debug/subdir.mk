################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../List.cpp \
../Node.cpp \
../main.cpp 

OBJS += \
./List.o \
./Node.o \
./main.o 

CPP_DEPS += \
./List.d \
./Node.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/mnt/hgfs/cchet/Documents/Git Repositories/Github/FH-Hagenberg/CPP/Semester 3/20150117_lab/MiniLib" -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags gtk+-2.0` -I../MiniLib -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


