//
// Created by vitdmit on 2/23/19.
//

#include <iostream>
#include "NumbersFiniteMachine.h"
#include "../Utils/string-utils.h"
const std::string &NumbersFiniteMachine::getCurrentString() const {
    return FiniteStateMachine::getCurrentString();
}

Token* NumbersFiniteMachine::getToken() {
    return token_;
}


State NumbersFiniteMachine::processString(std::string str, int &i, int row) {

    State state;
    token_ = new Token();
    token_->row = row;
    token_->t_start = i;
    do {
        if (i < str.length())
            state = handleInput(str[i]);
        else
            state = handleInput('\n');

        if (public_state_ != State::Undefined && !token_omit_symbol_)
            token_->value += str[i];

        i++;
    } while (public_state_ != State::Undefined && public_state_ != State ::Ended);
    token_->t_end = i;
    return public_state_;
}

State NumbersFiniteMachine::handleInput(char symbol) {
    //std::cout << symbol;
    if (public_state_ == State::Undefined || public_state_ == State::Ended) {
        public_state_ = State::Running;
        current_state_ = NumberStates::StartState;
    }
    token_omit_symbol_ = false;
    if (symbol == '\'') {
        token_omit_symbol_ = true;
        return public_state_;
    }
    token_omit_symbol_ = isTerminateSymbol(symbol);
    switch (current_state_) {
        case NumberStates::StartState:
            startState(symbol);
            break;
        case NumberStates::DigitSequenceState:
            digitSequenceState(symbol);
            break;
        case NumberStates::LongRemainderState:
            longRemainderState(symbol);
            break;
        case NumberStates::DotState:
            dotState(symbol);
            break;
        case NumberStates::RemainderSequenceState:
            remainderSequenceState(symbol);
            break;
        case NumberStates ::ExponentState:
            exponentState(symbol);
            break;
        case NumberStates::ExponentDigitSequenceState:
            exponentDigitsState(symbol);
            break;


        case NumberStates::ZeroSymbolState:
            zeroSymbolState(symbol);
            break;
        case NumberStates::BinDigitSequenceState:
            binDigitSequenceState(symbol);
            break;
        case NumberStates::OctDigitSequenceState:
            octDigitSequenceState(symbol);
            break;
        case NumberStates::HexDigitSequenceState:
            hexDigitSequenceState(symbol);
            break;
        case NumberStates::HexDotState:
            hexDotState(symbol);
            break;
    }
    return public_state_;
}

void NumbersFiniteMachine::startState(char symbol) {
    if (symbol >= '1' && symbol <= '9')
        current_state_ = NumberStates::DigitSequenceState;
    else if (symbol == '0') {
        current_state_ = NumberStates::ZeroSymbolState;
    } else if (symbol == '.') {
        current_state_ = NumberStates ::DotState;
    } else
        public_state_ = State::Undefined;

}

void NumbersFiniteMachine::digitSequenceState(char symbol) {
    if (symbol == '.')
        current_state_ = NumberStates::DotState;
    else if (tolower(symbol) == 'e') {
        current_state_ = NumberStates::ExponentState;
    } else if (isTerminateSymbol(symbol) || (tolower(symbol) == 'u')) {
        public_state_ = State::Ended;
    } else if (tolower(symbol) == 'l') {
        current_state_ = NumberStates::LongRemainderState;
    } else if (!isDecDigit(symbol))
        public_state_ = State::Undefined;
}

void NumbersFiniteMachine::dotState(char symbol) {
    if (isTerminateSymbol(symbol) || tolower(symbol) == 'f' || tolower(symbol) == 'l') {
        public_state_ = State::Ended;
    } else if (tolower(symbol) == 'e')
        current_state_ = NumberStates::ExponentState;
    else if (isDecDigit(symbol))
        current_state_ = NumberStates::RemainderSequenceState;
    else
        public_state_ = State::Undefined;
}

void NumbersFiniteMachine::longRemainderState(char symbol) {
    if (isTerminateSymbol(symbol) || tolower(symbol) == 'l') {
        public_state_ = State::Ended;
    } else
        public_state_ = State::Undefined;
}

void NumbersFiniteMachine::exponentState(char symbol) {
    if (isDecDigit(symbol) || symbol == '-' || symbol == '+')
        current_state_ = NumberStates::ExponentDigitSequenceState;
    else
        public_state_ = State::Undefined;
}

void NumbersFiniteMachine::exponentDigitsState(char symbol) {
    if (isTerminateSymbol(symbol) || tolower(symbol) == 'f' || tolower(symbol) == 'l') {
        public_state_ = State::Ended;
    } else if (!isDecDigit(symbol)){
        public_state_ = State::Undefined;
    }
}


void NumbersFiniteMachine::remainderSequenceState(char symbol) {
    if (isTerminateSymbol(symbol) || tolower(symbol) == 'l' || tolower(symbol) == 'f') {
        public_state_ = State::Ended;
    } else if (tolower(symbol) == 'e') {
        current_state_ = NumberStates::ExponentState;
    } else if (!isDecDigit(symbol)){
        public_state_ = State::Undefined;
    }
}

void NumbersFiniteMachine::zeroSymbolState(char symbol) {
    if (isTerminateSymbol(symbol) || tolower(symbol) == 'l')
        public_state_ = State::Ended;
    else if (symbol == '.') {
        current_state_ = NumberStates::DotState;
    } else if (tolower(symbol) =='b')
        current_state_ = NumberStates::BinDigitSequenceState;
    else if (tolower(symbol) == 'x')
        current_state_ = NumberStates::HexDigitSequenceState;
    else if (isOctDigit(symbol))
        current_state_ = NumberStates::OctDigitSequenceState;
    else
        public_state_ = State::Undefined;

}

void NumbersFiniteMachine::binDigitSequenceState(char symbol) {
    if (isTerminateSymbol(symbol) || tolower(symbol) == 'u')
        public_state_ = State::Ended;
    else if (tolower(symbol) == 'l')
        current_state_ = NumberStates::LongRemainderState;
    else if (!isBinDigit(symbol))
        public_state_ = State::Undefined;
}

void NumbersFiniteMachine::octDigitSequenceState(char symbol) {
    if (isTerminateSymbol(symbol) || tolower(symbol) == 'u')
        public_state_ = State::Ended;
    else if (tolower(symbol) == 'l')
        current_state_ = NumberStates::LongRemainderState;
    else if (!isOctDigit(symbol))
        public_state_ = State::Undefined;
}

void NumbersFiniteMachine::hexDigitSequenceState(char symbol) {
    if (tolower(symbol) == 'p')
        current_state_ = NumberStates::ExponentState;
    else if (symbol == '.')
        current_state_ = NumberStates::HexDotState;
    else if (isTerminateSymbol(symbol) || tolower(symbol) == 'u')
        public_state_ = State::Ended;
    else if (tolower(symbol) == 'l')
        current_state_ = NumberStates::LongRemainderState;
    else if (!isHexDigit(symbol))
        public_state_ = State::Undefined;
}

void NumbersFiniteMachine::hexDotState(char symbol) {
    if (isTerminateSymbol(symbol)) {
        public_state_ = State::Ended;
    } else if (tolower(symbol) == 'p')
        current_state_ = NumberStates::ExponentState;
    else if (!isHexDigit(symbol))
        public_state_ = State::Undefined;
}
