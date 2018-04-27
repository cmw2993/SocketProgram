################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Dir.cpp \
../Error.cpp \
../LogFile.cpp \
../Pages.cpp \
../Project4.cpp \
../Server.cpp \
../Status.cpp 

OBJS += \
./Dir.o \
./Error.o \
./LogFile.o \
./Pages.o \
./Project4.o \
./Server.o \
./Status.o 

CPP_DEPS += \
./Dir.d \
./Error.d \
./LogFile.d \
./Pages.d \
./Project4.d \
./Server.d \
./Status.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<" -std=gnu++14
	@echo 'Finished building: $<'
	@echo ' '


