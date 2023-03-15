#include "Transition.h"


Transition::Transition(IState* fromState, 
        IState* targetState, 
        bool (*triggerFunc)(),
        void (*exitFunc)()) {
    this->fromState = fromState;
    this->targetState = targetState;
    this->triggerFunc = triggerFunc;
    this->exitFunc = exitFunc;
}


bool Transition::isTriggered() {
    if (triggerFunc == nullptr) {
        return false;
    }
    return (*triggerFunc)();
}


IState* Transition::getFromState() {
    return fromState;
}


IState* Transition::getTargetState() {
    return targetState;
}


void Transition::onExit() {
    if (exitFunc != nullptr) {
        (*exitFunc)();
    }
}
