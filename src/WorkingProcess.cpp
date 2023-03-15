#include <iostream>
#include "WorkingProcess.h"
#include "globals.h"


void emergencyStop() {
    std::cout << "emergencyStop" << std::endl;
}


void runNormalIdle() {
    working = false;
    std::cout << "runNormalIdle" << std::endl;
}

void runNormalWaiting() {
    std::cout << "runNormalWaiting" << std::endl;
}


void runBraking() {
    std::cout << "runBraking" << std::endl;
}


void reduceSetpoint() {
    working = false;
    std::cout << "reduceSetpoint" << std::endl;
}


void delay1s() {
    std::cout << "delay1s" << std::endl;
}


void runTorqueMode() {
    working = true;
    std::cout << "runTorqueMode" << std::endl;
}


void runVelocityMode() {
    working = true;
    std::cout << "runVelocityMode" << std::endl;
}


bool checkIsError() {
    // std::cout << "checkIsError" << std::endl;
    return error;
}


bool checkNotError() {
    // std::cout << "checkNotError" << std::endl;
    return !error;
}


bool checkStartButtonPressed() {
    // std::cout << "checkStartButtonPressed" << std::endl;
    return startButtonPressed;
}


bool checkStartButtonReleasedAndWorking() {
    // std::cout << "checkStartButtonReleasedAndWorking" << startButtonPressed << working << std::endl;
    return !startButtonPressed && working;
}


bool checkStartButtonReleasedAndNotWorking() {
    // std::cout << "checkStartButtonReleasedAndNotWorking" << std::endl;
    return !startButtonPressed && !working;
}


bool isMotorStop() {
    // std::cout << "isMotorStop" << std::endl;
    return motorStop && !startButtonPressed;
}


bool isMotorNotStop() {
    // std::cout << "isMotorNotStop" << std::endl;
    return !motorStop && !startButtonPressed;
}


bool isMotorInTorqueMode() {
    // std::cout << "isMotorInTorqueMode" << std::endl;
    return motorInTorqueMode;
}


bool isMotorInVelocityMode() {
    // std::cout << "isMotorInVelocityMode" << std::endl;
    return !motorInTorqueMode;
}
