################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CuteTests/src/Test.cpp \
../CuteTests/src/Trees.cpp 

OBJS += \
./CuteTests/src/Test.o \
./CuteTests/src/Trees.o 

CPP_DEPS += \
./CuteTests/src/Test.d \
./CuteTests/src/Trees.d 


# Each subdirectory must supply rules for building sources it contributes
CuteTests/src/%.o: ../CuteTests/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/mnt/hgfs/cchet/Documents/Git Repositories/Github/FH-Hagenberg/CPP/Semester 3/2014-15_minilib/eclipseWorkspace/MiniLib" -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags gtk+-2.0` -I../MiniLib -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


