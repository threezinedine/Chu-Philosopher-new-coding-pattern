#pragma once
#include "ITransition.h"
#include "IState.h"


class Transition: public ITransition {
    public:
        Transition(IState* fromState, 
                IState* targetState, 
                bool (*triggerFunc)(),
                void (*exitFunc)());
        bool isTriggered();
        IState* getFromState();
        IState* getTargetState();
        void onExit();
    private:
        IState* fromState;
        IState* targetState;
        bool (*triggerFunc)();
        void (*exitFunc)();
};