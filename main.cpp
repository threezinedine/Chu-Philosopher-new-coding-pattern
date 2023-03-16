#include <iostream>

#include "constants.h"
#include "interface/IState.h"
#include "interface/State.h"
#include "interface/ITransition.h"
#include "interface/Transition.h"
#include "interface/WorkingProcess.h"
#include "interface/InterfaceProcess.h"
#include "interface/modbus.h"


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
    IState* modbusDataLinkProcess = new State("Modbus Data Link Process", nullptr, nullptr);

    IState* datalink_StartState = new State("Start", resetTimer, nullptr);
    IState* datalink_IdleState = new State("Idle", nullptr, runModbusIdle);
    IState* datalink_HandleNewBytesState = new State("Handle New Bytes", runHandleNewByte, nullptr);
    IState* datalink_receiveWholeFrameState = new State("Frame Checking", nullptr, nullptr);
    IState* datalink_transmitDataState = new State("Transmit", runTransmitResponse, nullptr);
	IState* datalink_processData = new State("Process Data", runProcessData, nullptr);

    IState* receiveWholeFrame_FrameCheckingState = new State("Frame Checking", runFrameChecking, nullptr);
    IState* receiveWholeFrame_ValidFrameState = new State("Valid Frame", nullptr, runValidRequest);
    IState* receiveWholeFrame_InvalidFrameState = new State("Invalid Frame", runDiscardFrame, runInvalidRequest);

    ITransition* datalink_Start2Idle = new Transition(datalink_StartState, 
                                        datalink_IdleState, checkTimeMoreThan3_5Chars, nullptr);
	ITransition* datalink_Start2Start = new Transition(datalink_StartState, 
										datalink_StartState, 
										checkReceiveNewByteWithTimeLessThan1_5Chars, nullptr);
	ITransition* datalink_Idle2HandleNewBytes = new Transition(datalink_IdleState, 
										datalink_HandleNewBytesState, 
										checkReceiveNewByte, nullptr);
	ITransition* datalink_Idle2Transmit = new Transition(datalink_IdleState, 
										datalink_transmitDataState, 
										haveSentFrame, nullptr);
	ITransition* datalink_HandleNewBytes2HandleNewBytes = new Transition(datalink_HandleNewBytesState, 
										datalink_HandleNewBytesState, 
										checkReceiveNewByteWithTimeLessThan1_5Chars, nullptr);
	ITransition* datalink_HandleNewBytes2ReceiveWholeFrame = new Transition(datalink_HandleNewBytesState, 
										datalink_receiveWholeFrameState, 
										checkTimeMoreThan1_5Chars, nullptr);
	ITransition* datalink_ReceiveWholeFrame2ProcessData = new Transition(datalink_receiveWholeFrameState, 
										datalink_processData, 
										checkTimerMoreThan3_5CharsAndFrameIsOK, nullptr);
	ITransition* datalink_ReceiveWholeFrame2Idle_NOK = new Transition(datalink_receiveWholeFrameState, 
										datalink_IdleState, 
										checkTimerMoreThan3_5CharsAndFrameIsNOK, nullptr);
	ITransition* datalink_Transmit2Idle = new Transition(datalink_transmitDataState, 
										datalink_IdleState, 
										sentAllFrame, nullptr);
	ITransition* datalink_Transmit2Transmit = new Transition(datalink_transmitDataState, 
										datalink_transmitDataState, 
										checkNotSendAllFrame, nullptr);

	ITransition* receiveWholeFrame_FrameChecking2ValidFrame = new Transition(receiveWholeFrame_FrameCheckingState, 
										receiveWholeFrame_ValidFrameState, 
										isFrameValid, nullptr);
	ITransition* receiveWholeFrame_FrameChecking2InvalidFrame = new Transition(receiveWholeFrame_FrameCheckingState, 
										receiveWholeFrame_InvalidFrameState, 
										isFrameInvalid, nullptr);
	ITransition* receiveWholeFrame_ValidFrame2InvalidFrame = new Transition(receiveWholeFrame_ValidFrameState, 
										receiveWholeFrame_InvalidFrameState, 
										checkReceiveNewByte, nullptr);
	ITransition* receiveWholeFrame_InvalidFrame2InvalidFrame = new Transition(receiveWholeFrame_InvalidFrameState, 
										receiveWholeFrame_InvalidFrameState, 
										checkReceiveNewByte, nullptr);

	modbusDataLinkProcess->addState(datalink_StartState);
	modbusDataLinkProcess->addState(datalink_IdleState);
	modbusDataLinkProcess->addState(datalink_HandleNewBytesState);
	modbusDataLinkProcess->addState(datalink_receiveWholeFrameState);
	modbusDataLinkProcess->addState(datalink_transmitDataState);
	modbusDataLinkProcess->setInitalState(datalink_StartState);
	modbusDataLinkProcess->addTransition(datalink_Start2Idle);
	modbusDataLinkProcess->addTransition(datalink_Start2Start);
	modbusDataLinkProcess->addTransition(datalink_Idle2HandleNewBytes);
	modbusDataLinkProcess->addTransition(datalink_Idle2Transmit);
	modbusDataLinkProcess->addTransition(datalink_HandleNewBytes2HandleNewBytes);
	modbusDataLinkProcess->addTransition(datalink_HandleNewBytes2ReceiveWholeFrame);
	modbusDataLinkProcess->addTransition(datalink_ReceiveWholeFrame2ProcessData);
	modbusDataLinkProcess->addTransition(datalink_ReceiveWholeFrame2Idle_NOK);
	modbusDataLinkProcess->addTransition(datalink_Transmit2Idle);

	datalink_receiveWholeFrameState->addState(receiveWholeFrame_FrameCheckingState);
	datalink_receiveWholeFrameState->addState(receiveWholeFrame_ValidFrameState);
	datalink_receiveWholeFrameState->addState(receiveWholeFrame_InvalidFrameState);
	datalink_receiveWholeFrameState->setInitalState(receiveWholeFrame_FrameCheckingState);
	datalink_receiveWholeFrameState->addTransition(receiveWholeFrame_FrameChecking2ValidFrame);
	datalink_receiveWholeFrameState->addTransition(receiveWholeFrame_FrameChecking2InvalidFrame);
	datalink_receiveWholeFrameState->addTransition(receiveWholeFrame_ValidFrame2InvalidFrame);
	datalink_receiveWholeFrameState->addTransition(receiveWholeFrame_InvalidFrame2InvalidFrame);

    // define the interface process
    IState* interfaceProcess = new State("Interface Process", nullptr, nullptr);
    IState* interface_NoAddressState = new State("No Address", nullptr, interface_runNoAddress);
    IState* interface_TimingState = new State("Timing", interface_onEnterTiming, nullptr);
    IState* interface_AddressState = new State("Address", nullptr, nullptr);

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

	while (true) {
		interfaceProcess->run();
		workingProcess->run();
		modbusDataLinkProcess->run();
	}

	return 0;
}