################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Directory.cpp \
../FSNode.cpp \
../File.cpp \
../FileSystem.cpp \
../Node.cpp \
../Tree.cpp \
../main.cpp 

OBJS += \
./Directory.o \
./FSNode.o \
./File.o \
./FileSystem.o \
./Node.o \
./Tree.o \
./main.o 

CPP_DEPS += \
./Directory.d \
./FSNode.d \
./File.d \
./FileSystem.d \
./Node.d \
./Tree.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags gtk+-2.0` -I../MiniLib -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


