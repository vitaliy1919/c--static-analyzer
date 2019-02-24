//
// Created by vitdmit on 2/22/19.
//

#include "CommentsFiniteMachine.h"
#include <stdexcept>
State CommentsFiniteMachine::handleInput(char symbol) {
    if (public_state_ != State::Running) {
        current_string_.clear();
        inner_state_ = 0;
        public_state_ = State::Running;
    }
    switch (inner_state_) {
        case 0:
            firstState(symbol);
            break;
        case 1:
            secondState(symbol);
            break;
        case 2:
            thirdState(symbol);
            break;
        case 3:
            fourthState(symbol);
            break;
        case 4:
            fifthState(symbol);
            break;
    }
    if (public_state_ != State::Undefined && (symbol != '\n' || public_state_ != State::Ended))
        current_string_ += symbol;
    return public_state_;
}

State CommentsFiniteMachine::firstState(char symbol) {
    if (symbol == '/') {
        inner_state_ = 1;
        public_state_ = State::Running;
        return public_state_;
    }
    public_state_ = State::Undefined;
    return public_state_;
}

State CommentsFiniteMachine::secondState(char symbol) {
    switch (symbol) {
        case '/':
            inner_state_ = 4;
            break;
        case '*':
            inner_state_ = 2;
            break;
        default:
            public_state_ = State::Undefined;
    }
    return public_state_;
}

State CommentsFiniteMachine::thirdState(char symbol) {
    if (symbol != '*')
        return public_state_;
    inner_state_++;
    return public_state_;
}

void CommentsFiniteMachine::fourthState(char symbol) {
    if (symbol == '/') {
        public_state_ = State::Ended;
    } else {
        public_state_ = State::Undefined;
    }
}

void CommentsFiniteMachine::fifthState(char symbol) {
    if (symbol == '\n')
        public_state_ = State::Ended;
}
