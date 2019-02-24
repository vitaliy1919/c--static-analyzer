//
// Created by vitdmit on 2/24/19.
//

#include "ReservedWordsFiniteMachine.h"

Token * ReservedWordsFiniteMachine::getToken() {
    return Token();
}

State ReservedWordsFiniteMachine::processString(std::string str, int &i, int row) {
    return Ended;
}

State ReservedWordsFiniteMachine::handleInput(char symbol) {
    return Ended;
}
