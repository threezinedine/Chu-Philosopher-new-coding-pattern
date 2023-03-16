#include <iostream>
#include "../interface/globals.h"
#include "../interface/ApplicationProcess.h"


void runApplicationIdle() {
    std::cout << "runApplicationIdle" << std::endl;
}


void runApplicatinCheckingRequest() {
    std::cout << "runApplicatinCheckingRequest" << std::endl;
}


void runApplicationHandleRequest() {
    std::cout << "runApplicationHandleRequest" << std::endl;
}


void runApplicationFormatReply() {
    std::cout << "runApplicationFormatReply" << std::endl;
}


void runApplicationFormatErrorReply() {
    std::cout << "runFormatErrorReply" << std::endl;
}


bool checkReceiveNewRequest() {
    return true;
}


bool checkFrameIsOK() {
    return true;
}


bool checkFrameIsNOK() {
    return true;
}


bool checkHandlingError() {
    return true;
}


bool checkUnicastRequest() {
    return true;
}


bool checkBroadcastRequest() {
    return true;
}


bool checkSendingComplete() {
    return true;
}


