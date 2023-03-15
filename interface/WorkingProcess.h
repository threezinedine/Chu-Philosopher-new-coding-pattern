#pragma once

#include "State.h"
#include "Transition.h"


void emergencyStop();
void runNormalIdle();
void runNormalWaiting();
void reduceSetpoint();
void delay1s();
void runTorqueMode();
void runVelocityMode();
void runBraking();

bool checkIsError();
bool checkNotError();
bool checkStartButtonPressed();
bool checkStartButtonReleasedAndWorking();
bool checkStartButtonReleasedAndNotWorking();
bool isMotorStop();
bool isMotorNotStop();
bool isMotorInTorqueMode();
bool isMotorInVelocityMode();


// IState* workingProcess = new State(nullptr, nullptr);

// IState* normalState = new State(nullptr, nullptr);
// IState* errorState = new State(emergencyStop, nullptr);

// IState* normal_IdleState = new State(nullptr, runNormalIdle);
// IState* normal_BrakingState = new State(reduceSetpoint, delay1s);
// IState* normal_WatingState = new State(nullptr, nullptr);
// IState* normal_WorkingState = new State(nullptr, nullptr);

// IState* working_TorqueState = new State(nullptr, runTorqueMode);
// IState* working_VelocityState = new State(nullptr, runVelocityMode);

// ITransition* normal2Error = new Transition(normalState, errorState, checkIsError, nullptr);
// ITransition* error2Normal = new Transition(errorState, normalState, checkNotError, nullptr);

// ITransition* normal_Idle2Wating = new Transition(normal_IdleState, normal_WatingState, nullptr, nullptr);
// ITransition* normal_Wating2Working = new Transition(normal_WatingState, normal_WorkingState, checkStartButtonReleasedAndNotWorking, nullptr);
// ITransition* normal_Wating2Braking = new Transition(normal_WatingState, normal_BrakingState, checkStartButtonReleasedAndWorking, nullptr);
// ITransition* normal_Working2Waiting = new Transition(normal_WorkingState, normal_WatingState, checkStartButtonPressed, nullptr);
// ITransition* normal_Braking2Idle = new Transition(normal_BrakingState, normal_IdleState, isMotorStop, nullptr);
// ITransition* normal_Braking2Braking = new Transition(normal_BrakingState, normal_BrakingState, isMotorNotStop, nullptr);

// ITransition* working_Torque2Velocity = new Transition(working_TorqueState, working_VelocityState, isMotorInVelocityMode, nullptr);
// ITransition* working_Velocity2Torque = new Transition(working_VelocityState, working_TorqueState, isMotorInTorqueMode, nullptr);


// workingProcess->addState(normalState);
// workingProcess->addState(errorState);
// workingProcess->setInitalState(normalState);
// workingProcess->addTransition(normal2Error);
// workingProcess->addTransition(error2Normal);


// normalState->addState(normal_IdleState);
// normalState->addState(normal_BrakingState);
// normalState->addState(normal_WatingState);
// normalState->addState(normal_WorkingState);
// normalState->setInitalState(normal_IdleState);
// normalState->addTransition(normal_Idle2Wating);
// normalState->addTransition(normal_Wating2Working);
// normalState->addTransition(normal_Wating2Braking);
// normalState->addTransition(normal_Working2Waiting);
// normalState->addTransition(normal_Braking2Idle);
// normalState->addTransition(normal_Braking2Braking);


// normal_WorkingState->addState(working_TorqueState);
// normal_WorkingState->addState(working_VelocityState);
// normal_WorkingState->setInitalState(working_TorqueState);
// normal_WorkingState->addTransition(working_Torque2Velocity);
// normal_WorkingState->addTransition(working_Velocity2Torque);

