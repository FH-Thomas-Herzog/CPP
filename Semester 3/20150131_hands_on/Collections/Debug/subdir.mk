################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Bag.cpp \
../BagNode.cpp \
../List.cpp \
../Node.cpp \
../Set.cpp 

OBJS += \
./Bag.o \
./BagNode.o \
./List.o \
./Node.o \
./Set.o 

CPP_DEPS += \
./Bag.d \
./BagNode.d \
./List.d \
./Node.d \
./Set.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/mnt/hgfs/cchet/Documents/Git Repositories/Github/FH-Hagenberg/CPP/Semester 4/20150228_lab_1/MiniLib" -I"/mnt/hgfs/cchet/Documents/Git Repositories/Github/FH-Hagenberg/CPP/Semester 3/20150131_hands_on/Collections/framework/boost" -I"/mnt/hgfs/cchet/Documents/Git Repositories/Github/FH-Hagenberg/CPP/Semester 3/20150131_hands_on/Collections/framework/cute" -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags gtk+-2.0` -I../MiniLib -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


