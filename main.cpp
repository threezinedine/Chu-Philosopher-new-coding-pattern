#include <iostream>
#include "IState.h"
#include "State.h"
#include "ITransition.h"
#include "Transition.h"
#include "WorkingProcess.h"
#include "InterfaceProcess.h"


int main() {
    // define the working process.
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

    // define the modbus receiver process
    IState* modbusReceiverProcess = new State("Modbus Receiver Process", nullptr, nullptr);

    IState* receive_StartState = new State("Start", nullptr, nullptr);
    IState* receive_IdleState = new State("Idle", nullptr, nullptr);
    IState* receive_HandleNewBytesState = new State("Handle New Bytes", nullptr, nullptr);
    IState* endHandlingState = new State("Frame Checking", nullptr, nullptr);

    IState* endHandling_FrameCheckingState = new State("Frame Checking", nullptr, nullptr);
    IState* endHandling_ValidFrameState = new State("Valid Frame", nullptr, nullptr);
    IState* endHandling_InvalidFrameState = new State("Invalid Frame", nullptr, nullptr);

    // define the modbus transmit process
    IState* modbusTransmitProcess = new State("Modbus Transmit Process", nullptr, nullptr);
    IState* transmit_IdleState = new State("Idle", nullptr, nullptr);
    IState* transmit_sendState = new State("Transmit", nullptr, nullptr);

    // define the modbus frame handling process
    IState* modbusFrameHandlingProcess = new State("Modbus Frame Handling", nullptr, nullptr);
    IState* handling_IdleState = new State("Idle", nullptr, nullptr);
    IState* handling_CheckingState = new State("Checking", nullptr, nullptr);
    IState* handling_HandleState = new State("Handle", nullptr, nullptr);
    IState* handling_NormalResponseState = new State("Normal Response", nullptr, nullptr);
    IState* handling_ErrorResponseState = new State("Error Response", nullptr, nullptr);


    // define the interface process
    IState* interfaceProcess = new State("Interface Process", nullptr, nullptr);
    IState* interface_NoAddressState = new State("No Address", nullptr, interface_runNoAddress);
    IState* interface_TimingState = new State("Timing", interface_onEnterTiming, nullptr);
    IState* interface_AddressState = new State("Address", nullptr, nullptr);

    IState* address_NormalState = new State("Have Address Normal", nullptr, address_runNormalMode);
    IState* address_ManufactureState = new State("Have Address Manufacture", nullptr, address_runFactoryMode);
    IState* address_EngineerMode = new State("Have Address Engineer Mode", nullptr, address_runEngineerMode);

    ITransition* interface_NoAddress2AddressState = new Transition(
            interface_NoAddressState, interface_AddressState, interface_checkHaveAddress, nullptr);
    ITransition* interface_Timing2NoAdress = new Transition(
            interface_TimingState, interface_NoAddressState, 
            interface_isHardResetButtonReleasedAndTimerMoreThan3, nullptr);
    ITransition* interface_Timing2Address = new Transition(
            interface_TimingState, interface_AddressState, 
            interface_isHardResetButtonReleasedAndTimerLessThan3, nullptr);
    ITransition* interface_Address2Timing = new Transition(
            interface_AddressState, interface_TimingState, 
            interface_isHardResetButtonPressed, nullptr);
    ITransition* address_Normal2Factory = new Transition(
            address_NormalState, address_ManufactureState, 
            address_isFactoryMode, nullptr);
    ITransition* address_Normal2Engineer = new Transition(
            address_NormalState, address_EngineerMode, 
            address_isEngineerMode, nullptr);
    ITransition* address_Factory2Normal = new Transition(
            address_ManufactureState, address_NormalState, 
            address_isNormalMode, nullptr);
    ITransition* address_Engineer2Normal = new Transition(
            address_EngineerMode, address_NormalState, 
            address_isNormalMode, nullptr);
    ITransition* address_Engineer2Factory = new Transition(
            address_EngineerMode, address_ManufactureState, 
            address_isFactoryMode, nullptr);
}