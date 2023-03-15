#pragma once 


bool interface_checkHaveAddress();
bool interface_isHardResetButtonPressed();
bool interface_isHardResetButtonReleasedAndTimerLessThan3();
bool interface_isHardResetButtonReleasedAndTimerMoreThan3();
bool address_isNormalMode();
bool address_isEngineerMode();
bool address_isFactoryMode();

void interface_runNoAddress();
void interface_onEnterTiming();
void address_runNormalMode();
void address_runEngineerMode();
void address_runFactoryMode();