#pragma once

union FloatRegister {
    float floatValue;
    uint16_t registers[2];
};

// variables for unit controll
bool error = false;
bool startButtonPressed = false;
bool working = false;
bool motorStop = false;
bool motorInTorqueMode = true;

uint16_t setpointInPercentage;

FloatRegister velocityMax;
FloatRegister velocityMin;

FloatRegister torqueMax;
FloatRegister torqueMin;

FloatRegister currentModeP;
FloatRegister currentModeI;
FloatRegister currentModeD;

FloatRegister voltageModeP;
FloatRegister voltageModeI;
FloatRegister voltageModeD;

// modbus datalink
bool receiveByte = false;
int timeValue = 0;
bool validFrame = false;
bool invalidFrame = false;
bool sentFrameComplete = false;
bool needToSendFrame = false;
bool notSendAllFrame = false;

// interface 
bool isUserMode = false;
bool isEngineerMode = false;
bool isManufacturerMode = false;


// modbus definition
#define ERROR &error
#define WORKING &working
#define MODE &motorInTorqueMode
#define IS_USER_MODE &isUserMode
#define IS_ENGINEER_MODE &isEngineerMode
#define IS_MANUFACTURER_MODE &isManufacturerMode


bool inputs[] = {
    MODE,
    IS_USER_MODE,
    IS_ENGINEER_MODE,
    IS_MANUFACTURER_MODE,
    WORKING,
};

bool coils[] = {
    ERROR,
};


bool inputRegistersManufactureMode[] = {
};


bool holdingRegistersManufactureMode[] = {
    &setpointInPercentage,
    &velocityMax.registers[0],
    &velocityMax.registers[1],
    &velocityMin.registers[0],
    &velocityMin.registers[1],
    &currentModeP.registers[0],
    &currentModeP.registers[1],
    &currentModeI.registers[0],
    &currentModeI.registers[1],
    &currentModeD.registers[0],
    &currentModeD.registers[1],
    &voltageModeP.registers[0],
    &voltageModeP.registers[1],
    &voltageModeI.registers[0],
    &voltageModeI.registers[1],
    &voltageModeD.registers[0],
    &voltageModeD.registers[1],
};