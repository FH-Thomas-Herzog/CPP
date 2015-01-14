################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Directory.cpp \
../File.cpp \
../FileSystem.cpp \
../FsNode.cpp \
../IntNode.cpp \
../Node.cpp \
../Tree.cpp 

OBJS += \
./Directory.o \
./File.o \
./FileSystem.o \
./FsNode.o \
./IntNode.o \
./Node.o \
./Tree.o 

CPP_DEPS += \
./Directory.d \
./File.d \
./FileSystem.d \
./FsNode.d \
./IntNode.d \
./Node.d \
./Tree.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/mnt/hgfs/cchet/Documents/Git Repositories/Github/FH-Hagenberg/CPP/Semester 3/2014-15_minilib/eclipseWorkspace/MiniLib" -I"/mnt/hgfs/cchet/Documents/Git Repositories/Github/FH-Hagenberg/CPP/resources/boost" -I"/mnt/hgfs/cchet/Documents/Git Repositories/Github/FH-Hagenberg/CPP/resources/cute" -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags gtk+-2.0` -I../MiniLib -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


