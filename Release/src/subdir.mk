################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Particle.cpp \
../src/SDLBasic.cpp \
../src/Screen.cpp \
../src/Swarm.cpp 

OBJS += \
./src/Particle.o \
./src/SDLBasic.o \
./src/Screen.o \
./src/Swarm.o 

CPP_DEPS += \
./src/Particle.d \
./src/SDLBasic.d \
./src/Screen.d \
./src/Swarm.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/SDL2 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


