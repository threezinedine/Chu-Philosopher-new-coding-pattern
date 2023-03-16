#include <iostream>

#include "constants.h"
#include "interface/IState.h"
#include "interface/State.h"
#include "interface/ITransition.h"
#include "interface/Transition.h"
#include "interface/WorkingProcess.h"
#include "interface/InterfaceProcess.h"
#include "interface/dataLinkLayerProcess.h"
#include "interface/ApplicationProcess.h"


int main() {
	motorSpeed.floatValue = 0;

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
	ITransition* datalink_ReceiveWholeFrame2Idle_OK = new Transition(datalink_receiveWholeFrameState, 
										datalink_IdleState, 
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
	modbusDataLinkProcess->addTransition(datalink_ReceiveWholeFrame2Idle_OK);
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

    // define the modbus frame handling process
    IState* modbusFrameHandlingProcess = new State("Modbus Frame Handling", nullptr, nullptr);
    IState* handling_IdleState = new State("Idle", nullptr, runApplicationIdle);
    IState* handling_CheckingState = new State("Checking", nullptr, runApplicatinCheckingRequest);
    IState* handling_HandleState = new State("Handle", nullptr, runApplicationHandleRequest);
    IState* handling_NormalResponseState = new State("Normal Response", nullptr, runApplicationFormatReply);
    IState* handling_ErrorResponseState = new State("Error Response", nullptr, runApplicationFormatErrorReply);

	ITransition* handling_Idle2Checking = new Transition(handling_IdleState, 
										handling_CheckingState, 
										checkReceiveNewRequest, nullptr);
	ITransition* handling_Checking2Handle = new Transition(handling_CheckingState, 
										handling_HandleState, 
										checkFrameIsOK, nullptr);
	ITransition* handling_Checking2ErrorResponse = new Transition(handling_CheckingState, 
										handling_ErrorResponseState, 
										checkFrameIsNOK, nullptr);
	ITransition* handling_Handle2NormalResponse = new Transition(handling_HandleState, 
										handling_NormalResponseState, 
										checkUnicastRequest, nullptr);
	ITransition* handling_Handle2Idle = new Transition(handling_HandleState, 
										handling_IdleState, 
										checkBroadcastRequest, nullptr);
	ITransition* handling_Handle2ErrorResponse = new Transition(handling_HandleState, 
										handling_ErrorResponseState, 
										checkHandlingError, nullptr);
	ITransition* handling_ErrorResponse2Idle = new Transition(handling_ErrorResponseState, 
										handling_IdleState, 
										checkSendingComplete, nullptr);
	ITransition* handling_NormalResponse2Idle = new Transition(handling_NormalResponseState, 
										handling_IdleState, 
										checkSendingComplete, nullptr);

	modbusFrameHandlingProcess->addState(handling_CheckingState);
	modbusFrameHandlingProcess->addState(handling_HandleState);
	modbusFrameHandlingProcess->addState(handling_NormalResponseState);
	modbusFrameHandlingProcess->addState(handling_ErrorResponseState);
	modbusFrameHandlingProcess->setInitalState(handling_IdleState);

	modbusFrameHandlingProcess->addTransition(handling_Idle2Checking);
	modbusFrameHandlingProcess->addTransition(handling_Checking2Handle);
	modbusFrameHandlingProcess->addTransition(handling_Checking2ErrorResponse);
	modbusFrameHandlingProcess->addTransition(handling_Handle2NormalResponse);
	modbusFrameHandlingProcess->addTransition(handling_Handle2Idle);
	modbusFrameHandlingProcess->addTransition(handling_Handle2ErrorResponse);
	modbusFrameHandlingProcess->addTransition(handling_ErrorResponse2Idle);
	modbusFrameHandlingProcess->addTransition(handling_NormalResponse2Idle);


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

	while (true) {
		interfaceProcess->run();
		modbusFrameHandlingProcess->run();
		workingProcess->run();
		modbusDataLinkProcess->run();
	}

	return 0;
}