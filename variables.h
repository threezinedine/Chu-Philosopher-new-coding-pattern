#pragma once
#include <cstdint>

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
uint16_t currentValueInPercentage;

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

// manufacture
FloatRegister manufactorVelocityMax;
FloatRegister manufactorTorqueMax;

FloatRegister manufactorCurrentModePMax;
FloatRegister manufactorCurrentModePMin;
FloatRegister manufactorCurrentModeIMax;
FloatRegister manufactorCurrentModeIMin;
FloatRegister manufactorCurrentModeDMax;
FloatRegister manufactorCurrentModeDMin;

FloatRegister manufactorVoltageModePMax;
FloatRegister manufactorVoltageModePMin;
FloatRegister manufactorVoltageModeIMax;
FloatRegister manufactorVoltageModeIMin;
FloatRegister manufactorVoltageModeDMax;
FloatRegister manufactorVoltageModeDMin;

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


bool* inputs[] = {
    MODE,
    WORKING,
};

bool* coils[] = {
    ERROR,
};


uint16_t* inputRegistersManufactureMode[] = {
    &manufactorTorqueMax.registers[0],
    &manufactorTorqueMax.registers[1],
    &manufactorVelocityMax.registers[0],
    &manufactorVelocityMax.registers[1],
    &manufactorCurrentModePMax.registers[0],
    &manufactorCurrentModePMax.registers[1],
    &manufactorCurrentModePMin.registers[0],
    &manufactorCurrentModePMin.registers[1],
    &manufactorCurrentModeIMax.registers[0],
    &manufactorCurrentModeIMax.registers[1],
    &manufactorCurrentModeIMin.registers[0],
    &manufactorCurrentModeIMin.registers[1],
    &manufactorCurrentModeDMax.registers[0],
    &manufactorCurrentModeDMax.registers[1],
    &manufactorCurrentModeDMin.registers[0],
    &manufactorCurrentModeDMin.registers[1],
    &manufactorVoltageModePMax.registers[0],
    &manufactorVoltageModePMax.registers[1],
    &manufactorVoltageModePMin.registers[0],
    &manufactorVoltageModePMin.registers[1],
    &manufactorVoltageModeIMax.registers[0],
    &manufactorVoltageModeIMax.registers[1],
    &manufactorVoltageModeIMin.registers[0],
    &manufactorVoltageModeIMin.registers[1],
    &manufactorVoltageModeDMax.registers[0],
    &manufactorVoltageModeDMax.registers[1],
};


uint16_t* holdingRegistersManufactureMode[] = {
    &setpointInPercentage,
    &currentValueInPercentage,
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