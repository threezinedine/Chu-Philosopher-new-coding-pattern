#pragma once

void runModbusStart();
void runModbusIdle();
void runHandleNewByte();
void runFrameChecking();
void runValidRequest();
void runInvalidRequest();
void runDiscardFrame();
void runTransmitResponse();
void resetTimer();
void raiseFrameReceivedFlag();

bool checkReceiveNewByte();
bool checkReceiveNewByteWithTimeLessThan3_5Chars();
bool checkReceiveNewByteWithTimeLessThan1_5Chars();
bool checkTimeMoreThan1_5Chars();
bool checkTimeMoreThan3_5Chars();
bool isFrameValid();
bool isFrameInvalid();
bool haveSentFrame();
bool sentAllFrame();
bool checkNotSendAllFrame();
bool checkTimerMoreThan3_5CharsAndFrameIsOK();
bool checkTimerMoreThan3_5CharsAndFrameIsNOK();