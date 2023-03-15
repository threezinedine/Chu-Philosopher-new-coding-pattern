#include <iostream>
#include "WorkingProcess.h"
#include "State.h"
#include "Transition.h"

bool error = false;
bool startButtonPressed = false;
bool working = false;
bool motorStop = false;
bool motorInTorqueMode = true;

// these functions below are just used for testing
void runWorkingProcess(IState* process, int time) {
    for (int i = 0; i < time; i++) {
        process->run();
        std::cout << "---------------------------" << std::endl;
    }
}

void displayAction(std::string message) {
    std::cout << "+++++++++++++++++++++" << std::endl;
    std::cout << message << std::endl;
    std::cout << "+++++++++++++++++++++" << std::endl;
}
// these functions above are just used for testing


int main(void) {
    IState* workingProcess = new State("Working Process", nullptr, nullptr);

    IState* normalState = new State("Normal", nullptr, nullptr);
    IState* errorState = new State("Error", emergencyStop, nullptr);

    IState* normal_IdleState = new State("Normal-Idle", nullptr, runNormalIdle);
    IState* normal_BrakingState = new State("Normal-Braking", reduceSetpoint, delay1s);
    IState* normal_WatingState = new State("Normal-Waiting", runNormalWaiting, nullptr);
    IState* normal_WorkingState = new State("Normal-Working", nullptr, nullptr);

    IState* working_TorqueState = new State("Working-Torque", nullptr, runTorqueMode);
    IState* working_VelocityState = new State("Working-Velocity", nullptr, runVelocityMode);

    ITransition* normal2Error = new Transition(normalState, errorState, checkIsError, nullptr);
    ITransition* error2Normal = new Transition(errorState, normalState, checkNotError, nullptr);

    ITransition* normal_Idle2Wating = new Transition(normal_IdleState, normal_WatingState, checkStartButtonPressed, nullptr);
    ITransition* normal_Wating2Working = new Transition(normal_WatingState, normal_WorkingState, checkStartButtonReleasedAndNotWorking, nullptr);
    ITransition* normal_Wating2Braking = new Transition(normal_WatingState, normal_BrakingState, checkStartButtonReleasedAndWorking, nullptr);
    ITransition* normal_Working2Waiting = new Transition(normal_WorkingState, normal_WatingState, checkStartButtonPressed, nullptr);
    ITransition* normal_Braking2Idle = new Transition(normal_BrakingState, normal_IdleState, isMotorStop, nullptr);
    ITransition* normal_Braking2Braking = new Transition(normal_BrakingState, normal_BrakingState, isMotorNotStop, nullptr);
    ITransition* normal_Braking2Waiting = new Transition(normal_BrakingState, normal_WatingState, checkStartButtonPressed, nullptr);

    ITransition* working_Torque2Velocity = new Transition(working_TorqueState, working_VelocityState, isMotorInVelocityMode, nullptr);
    ITransition* working_Velocity2Torque = new Transition(working_VelocityState, working_TorqueState, isMotorInTorqueMode, nullptr);

    workingProcess->addState(normalState);
    workingProcess->addState(errorState);
    workingProcess->setInitalState(normalState);
    workingProcess->addTransition(normal2Error);
    workingProcess->addTransition(error2Normal);


    normalState->addState(normal_IdleState);
    normalState->addState(normal_BrakingState);
    normalState->addState(normal_WatingState);
    normalState->addState(normal_WorkingState);
    normalState->setInitalState(normal_IdleState);
    normalState->addTransition(normal_Idle2Wating);
    normalState->addTransition(normal_Wating2Working);
    normalState->addTransition(normal_Wating2Braking);
    normalState->addTransition(normal_Working2Waiting);
    normalState->addTransition(normal_Braking2Idle);
    normalState->addTransition(normal_Braking2Braking);
    normalState->addTransition(normal_Braking2Waiting);


    normal_WorkingState->addState(working_TorqueState);
    normal_WorkingState->addState(working_VelocityState);
    normal_WorkingState->setInitalState(working_TorqueState);
    normal_WorkingState->addTransition(working_Torque2Velocity);
    normal_WorkingState->addTransition(working_Velocity2Torque);


    workingProcess->onEnter();
    std::cout << "***************************" << std::endl;
    std::cout << "***************************" << std::endl;
    runWorkingProcess(workingProcess, 5);

    startButtonPressed = true;
    displayAction("Press Button");
    runWorkingProcess(workingProcess, 5);

    startButtonPressed = false;
    displayAction("Release Button");
    runWorkingProcess(workingProcess, 5);

    motorInTorqueMode = false;
    displayAction("Move To velocity mode");
    runWorkingProcess(workingProcess, 5);

    motorInTorqueMode = true;
    displayAction("Move To Torque mode");
    runWorkingProcess(workingProcess, 5);

    startButtonPressed = true;
    displayAction("Press Button");
    runWorkingProcess(workingProcess, 5);

    startButtonPressed = false;
    displayAction("Release Button");
    runWorkingProcess(workingProcess, 5);

    startButtonPressed = true;
    displayAction("Press Button");
    runWorkingProcess(workingProcess, 5);

    startButtonPressed = false;
    displayAction("Release Button");
    runWorkingProcess(workingProcess, 5);

    startButtonPressed = true;
    displayAction("Press Button");
    runWorkingProcess(workingProcess, 5);

    startButtonPressed = false;
    displayAction("Release Button");
    runWorkingProcess(workingProcess, 5);

    motorStop = true;
    displayAction("Motor Stops");
    runWorkingProcess(workingProcess, 5);

    startButtonPressed = true;
    displayAction("Press Button");
    runWorkingProcess(workingProcess, 5);

    startButtonPressed = false;
    displayAction("Release Button");
    runWorkingProcess(workingProcess, 5);

    error = true;
    displayAction("Error Occurs");
    runWorkingProcess(workingProcess, 10);

    startButtonPressed = true;
    displayAction("Press Button");
    runWorkingProcess(workingProcess, 5);

    startButtonPressed = false;
    displayAction("Release Button");
    runWorkingProcess(workingProcess, 5);

    error = false;
    displayAction("Error Fixed");
    runWorkingProcess(workingProcess, 5);

    std::cout << "After run" << std::endl;

    delete workingProcess;
    delete normalState;
    delete errorState;
    delete normal_IdleState;
    delete normal_BrakingState;
    delete normal_WatingState;
    delete normal_WorkingState;
    delete working_TorqueState;
    delete working_VelocityState;
    delete normal2Error;
    delete error2Normal;
    delete normal_Idle2Wating;
    delete normal_Wating2Working;
    delete normal_Wating2Braking;
    delete normal_Working2Waiting;
    delete normal_Braking2Idle;
    delete normal_Braking2Braking;
    delete working_Torque2Velocity;
    delete working_Velocity2Torque;

    return 0;
}


