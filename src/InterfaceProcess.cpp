#include "InterfaceProcess.h"


bool interface_checkHaveAddress() {
    return false;
}


bool interface_isHardResetButtonPressed() {
    return false;
}


bool interface_isHardResetButtonReleasedAndTimerLessThan3() {
    return false;
}


bool interface_isHardResetButtonReleasedAndTimerMoreThan3() {
    return false;
}


bool address_isNormalMode() {
    return false;
}


bool address_isEngineerMode() {
    return false;
}


bool address_isFactoryMode() {
    return false;
}


void interface_runNoAddress() {
}

void interface_onEnterTiming() {
}


void address_runNormalMode() {
}


void address_runEngineerMode() {
}


void address_runFactoryMode() {
}

