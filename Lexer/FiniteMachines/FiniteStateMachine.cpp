//
// Created by vitdmit on 2/22/19.
//

#include "FiniteStateMachine.h"
#include "../Tokens/Token.h"

State FiniteStateMachine::onInput(char symbol) {
            return handleInput(symbol);
    }

const std::string &FiniteStateMachine::getCurrentString() const {
    return current_string_;
}


