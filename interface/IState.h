#pragma once
#include <iostream>
#include <string>


class ITransition;


class IState {
    public:
        virtual void run() = 0;
        virtual void onEnter() = 0;
        virtual void addTransition(ITransition* transition) = 0;
        virtual void addState(IState* state) = 0;
        virtual void setInitalState(IState* state) = 0;
        virtual void next() = 0;
};