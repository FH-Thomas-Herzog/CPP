################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DrawApp.cpp \
../DrawWin.cpp \
../Line.cpp \
../Oval.cpp \
../Rectangle.cpp \
../Shape.cpp \
../main.cpp 

OBJS += \
./DrawApp.o \
./DrawWin.o \
./Line.o \
./Oval.o \
./Rectangle.o \
./Shape.o \
./main.o 

CPP_DEPS += \
./DrawApp.d \
./DrawWin.d \
./Line.d \
./Oval.d \
./Rectangle.d \
./Shape.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/include/gtk-2.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/atk-1.0 -I/usr/include/harfbuzz -I"/mnt/hgfs/cchet/Documents/Git Repositories/Github/FH-Hagenberg/CPP/Semester 3/20150124_lab/MiniLib" -I"/mnt/hgfs/cchet/Documents/Git Repositories/Github/FH-Hagenberg/CPP/Semester 3/20150124_lab/WindowApplication" -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags gtk+-2.0` -I../MiniLib -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


