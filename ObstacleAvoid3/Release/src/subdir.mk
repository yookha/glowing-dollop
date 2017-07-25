################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ConfigurationManager.cpp \
../src/LocalizationManager.cpp \
../src/Map.cpp \
../src/Node.cpp \
../src/Particle.cpp \
../src/PathPlanner.cpp \
../src/PointType.cpp \
../src/Robot.cpp \
../src/main.cpp 

OBJS += \
./src/ConfigurationManager.o \
./src/LocalizationManager.o \
./src/Map.o \
./src/Node.o \
./src/Particle.o \
./src/PathPlanner.o \
./src/PointType.o \
./src/Robot.o \
./src/main.o 

CPP_DEPS += \
./src/ConfigurationManager.d \
./src/LocalizationManager.d \
./src/Map.d \
./src/Node.d \
./src/Particle.d \
./src/PathPlanner.d \
./src/PointType.d \
./src/Robot.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


