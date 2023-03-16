#include <iostream>
#include "../interface/dataLinkLayerProcess.h"
#include "../interface/globals.h"

#define BAUD_RATE 9600
#define MAX_WAITING_TIME 3.5 * 8 * BAUD_RATE
#define MAX_DISTANCE_TIME 1.5 * 8 * BAUD_RATE


void runModbusStart() {
    std::cout << "runModbusStart" << std::endl;
}


void runModbusIdle() {
    std::cout << "runModbusIdle" << std::endl;
}


void runHandleNewByte() {
    std::cout << "runHandleNewByte" << std::endl;
}


void runFrameChecking() {
    std::cout << "runFrameChecking" << std::endl;
}


void runValidRequest() {
    std::cout << "runValidRequest" << std::endl;
}


void runInvalidRequest() {
    std::cout << "runInvalidRequest" << std::endl;
}


void runDiscardFrame() {
    std::cout << "runDiscardFrame" << std::endl;
}


void runTransmitResponse() {
    std::cout << "runTransmitResponse" << std::endl;
}


void resetTimer() {
    std::cout << "resetTimer" << std::endl;
}


void raiseFrameReceivedFlag() {
    std::cout << "raiseFrameReceivedFlag" << std::endl;
}


bool checkReceiveNewByte() {
    return receiveByte;
}


bool checkReceiveNewByteWithTimeLessThan3_5Chars() {
    return checkReceiveNewByte() && timeValue < MAX_WAITING_TIME;
}


bool checkReceiveNewByteWithTimeLessThan1_5Chars() {
    return checkReceiveNewByte() && timeValue < MAX_DISTANCE_TIME;
}


bool checkTimeMoreThan1_5Chars() {
    return timeValue > MAX_DISTANCE_TIME;
}


bool checkTimeMoreThan3_5Chars() {
    return timeValue > MAX_WAITING_TIME;
}


bool isFrameValid() {
    return validFrame;
}


bool isFrameInvalid() {
    return !validFrame;
}


bool haveSentFrame() {
    return needToSendFrame;
}


bool sentAllFrame() {
    return sentFrameComplete;
}


bool checkNotSendAllFrame() {
    return !sentFrameComplete;
}


bool checkTimerMoreThan3_5CharsAndFrameIsOK() {
    return checkTimeMoreThan3_5Chars() && isFrameValid();
}


bool checkTimerMoreThan3_5CharsAndFrameIsNOK() {
    return checkTimeMoreThan3_5Chars() && isFrameInvalid();
}