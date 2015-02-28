################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Entry.cpp \
../IndexV1.cpp \
../IndexV2.cpp \
../IndexV3.cpp \
../IndexV4.cpp \
../IndexV5.cpp \
../main.cpp \
../utils.cpp 

OBJS += \
./Entry.o \
./IndexV1.o \
./IndexV2.o \
./IndexV3.o \
./IndexV4.o \
./IndexV5.o \
./main.o \
./utils.o 

CPP_DEPS += \
./Entry.d \
./IndexV1.d \
./IndexV2.d \
./IndexV3.d \
./IndexV4.d \
./IndexV5.d \
./main.d \
./utils.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/mnt/hgfs/cchet/Documents/Git Repositories/Github/FH-Hagenberg/CPP/Semester 4/20150228_lab_1/MiniLib" -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags gtk+-2.0` -I../MiniLib -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


