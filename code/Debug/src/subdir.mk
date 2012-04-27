################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Airport.cpp \
../src/LoadData.cpp \
../src/Waypoint.cpp \
../src/main.cpp 

OBJS += \
./src/Airport.o \
./src/LoadData.o \
./src/Waypoint.o \
./src/main.o 

CPP_DEPS += \
./src/Airport.d \
./src/LoadData.d \
./src/Waypoint.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/andre/git/cal-flight-advisor/code/cute" -I"/home/andre/git/cal-flight-advisor/code/include" -I"/home/andre/git/cal-flight-advisor/code/boost" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


