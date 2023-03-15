#pragma once 


class IState;


class ITransition {
    public:
        virtual bool isTriggered() = 0;
        virtual IState* getFromState() = 0;
        virtual IState* getTargetState() = 0;
        virtual void onExit() = 0;
};