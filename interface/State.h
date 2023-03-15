#pragma once 

#include "IState.h"
#include <unordered_map>
#include <vector>


class State: public IState {
    public:
        State();
        State(std::string name, void (*enterFunc)() = nullptr, void (*runFunc)() = nullptr);
        void run();
        void onEnter();
        void addState(IState* state);
        void addTransition(ITransition* transition);
        void setInitalState(IState* state);
        void next();
    private:
        IState* currentState;
        IState* initialState = nullptr;
        std::unordered_map<IState*, std::vector<ITransition*>> transitions;
        void (*enterFunc)();
        void (*runFunc)();
        std::string name;
};