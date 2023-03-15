#include <iostream>
#include "ITransition.h"
#include "IState.h"
#include "State.h"


State::State() {
    currentState = nullptr;
    enterFunc = nullptr;
    runFunc = nullptr;
}


State::State(std::string name, void (*enterFunc)(), void (*runFunc)()) {
    currentState = nullptr;
    this->enterFunc = enterFunc;
    this->runFunc = runFunc;
    this->name = name;
}


void State::run() {
    // std::cout << "Start of run of " << name << std::endl;
    if (runFunc != nullptr) {
        runFunc();
    }
    if (currentState != nullptr) {
        currentState->run();
        next();
    }
    // std::cout << "End of run of " << name << std::endl;
}


void State::onEnter() {
    // std::cout << "Start of on Enter of " << name << std::endl;
    if (initialState != nullptr) {
        currentState = initialState;
        currentState->onEnter();
    }

    if (enterFunc != nullptr) {
        enterFunc();
    }
    // std::cout << "End of on Enter of " << name << std::endl;
}


void State::addState(IState* state) {
    if (initialState == nullptr) {
        initialState = state;
    }

    transitions[state] = std::vector<ITransition*>();
}


void State::addTransition(ITransition* transition) {
    transitions[transition->getFromState()].push_back(transition);
}


void State::setInitalState(IState* state) {
    initialState = state;
}


void State::next() {
    // std::cout << "Start of next of " << name<< std::endl;
    std::vector<ITransition*> trans = transitions[currentState];
    for (int i=0; i<trans.size(); i++) {
        if (trans.at(i)->isTriggered()) {
            trans.at(i)->onExit();
            currentState = trans.at(i)->getTargetState();
            currentState->onEnter();
            break;
        }
    }
    // std::cout << "End of next of " << name<< std::endl;
}