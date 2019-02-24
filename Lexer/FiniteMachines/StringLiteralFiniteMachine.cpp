//
// Created by vitdmit on 2/23/19.
//

#include "StringLiteralFiniteMachine.h"

State StringLiteralFiniteMachine::handleInput(char symb) {
    if (public_state_ != State::Running) {
        inner_state_ = START;
        public_state_ = State::Running;
    }

    switch (inner_state_) {
        case START:
            startState(symb);
            break;
        case CONSUMING_STRING:
            consumingStringState(symb);
            break;
        case SPECIAL_SYMBOL:
            consumingSpecialSymbolState(symb);
            break;
        default:
            break;
    }

    if (public_state_ != State::Undefined)
        current_string_ += symb;
    return public_state_;
}

State StringLiteralFiniteMachine::processString(std::string str, int &i, int row) {
    State state;
    token_ = new Token();
    token_->row = row;
    token_->type = TokenTypes::StringLiteral;
    token_->t_start = i;
    do {
        if (i < str.length())
            state = handleInput(str[i]);
        else
            state = handleInput('\n');

        if (public_state_ != State::Undefined)
            token_->value += str[i];

        i++;
    } while (public_state_ != State::Undefined && public_state_ != State ::Ended);
    token_->t_end = i;
    return public_state_;
}

void StringLiteralFiniteMachine::startState(char symb) {
    if (symb == '\"') {
        inner_state_ = CONSUMING_STRING;
    } else {
        public_state_ = State ::Undefined;
    }
}

void StringLiteralFiniteMachine::consumingStringState(char symb) {
    if (symb == '\\') {
        inner_state_ = SPECIAL_SYMBOL;
    } else if (symb == '\"') {
        public_state_ = State::Ended;
    }

}

void StringLiteralFiniteMachine::consumingSpecialSymbolState(char symb) {
    inner_state_ = CONSUMING_STRING;
}

