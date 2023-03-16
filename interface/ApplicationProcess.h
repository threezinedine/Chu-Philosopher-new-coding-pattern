#pragma once


void runApplicationIdle();
void runApplicatinCheckingRequest();
void runApplicationHandleRequest();
void runApplicationFormatReply();
void runApplicationFormatErrorReply();


bool checkReceiveNewRequest();
bool checkFrameIsOK();
bool checkFrameIsNOK();
bool checkHandlingError();
bool checkUnicastRequest();
bool checkBroadcastRequest();
bool checkSendingComplete();