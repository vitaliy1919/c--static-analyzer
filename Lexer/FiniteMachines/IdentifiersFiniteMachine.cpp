//
// Created by i503709 on 2/25/19.
//

#include "IdentifiersFiniteMachine.h"

State IdentifiersFiniteMachine::processString(const string &str, int &i, int row) {
    State state;
    token_ = std::make_shared<Token>();
    token_->row = row;
    token_->t_start = i;
    token_->type = TokenTypes::Indentifier;
    do {
        if (i < str.length())
            state = handleInput(str[i]);
        else
            state = handleInput('\n');

        if (public_state_ != State::Undefined && public_state_ != State::Ended)
            token_->value += str[i];

        i++;
    } while (public_state_ != State::Undefined && public_state_ != State ::Ended);
    i--;
    token_->t_end = i;
    return public_state_;
}

State IdentifiersFiniteMachine::handleInput(char symbol) {
    if (public_state_ != State::Running) {
        current_state_ = IndentifierState::StartState;
        public_state_ = State::Running;
    }

    switch (current_state_) {
        case IndentifierState::StartState:
            startState(symbol);
            break;
        case IndentifierState::ConstumingState:
            consumingState(symbol);
            break;
    }
    return public_state_;
}

void IdentifiersFiniteMachine::startState(char symbol) {
    if (isalpha(symbol))
        current_state_ = IndentifierState::ConstumingState;
    else
        public_state_ = State::Undefined;

}

void IdentifiersFiniteMachine::consumingState(char symbol) {

    if (!isalpha(symbol) && !isdigit(symbol) && symbol != '_')
        public_state_ = State::Ended;
}
