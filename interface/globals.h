#pragma once 

// unit control
extern bool error;
extern bool startButtonPressed;
extern bool working;
extern bool motorStop;
extern bool motorInTorqueMode;


// modbus datalink
extern bool receiveByte;
extern int timeValue;
extern bool validFrame;
extern bool invalidFrame;
extern bool sentFrameComplete;
extern bool needToSendFrame;
extern bool notSendAllFrame;