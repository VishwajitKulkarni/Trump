################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Card.cpp \
../src/CardManager.cpp \
../src/CommandLineUserInterface.cpp \
../src/GameManager.cpp \
../src/Message.cpp \
../src/Player.cpp \
../src/PlayerSocket.cpp \
../src/RoundManager.cpp \
../src/Server.cpp \
../src/main.cpp 

OBJS += \
./src/Card.o \
./src/CardManager.o \
./src/CommandLineUserInterface.o \
./src/GameManager.o \
./src/Message.o \
./src/Player.o \
./src/PlayerSocket.o \
./src/RoundManager.o \
./src/Server.o \
./src/main.o 

CPP_DEPS += \
./src/Card.d \
./src/CardManager.d \
./src/CommandLineUserInterface.d \
./src/GameManager.d \
./src/Message.d \
./src/Player.d \
./src/PlayerSocket.d \
./src/RoundManager.d \
./src/Server.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/vishwajit/eclipse-workspace/Server_It02V03/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


