//
// Created by vitdmit on 2/24/19.
//

#include "OperatorsStateMachine.h"

Token OperatorsStateMachine::getToken() {
    return Token();
}

State OperatorsStateMachine::processString(std::string str, int &i, int row) {
    bool state = operatorsTrie_.findMaxSubstring(str, i);

}

State OperatorsStateMachine::handleInput(char symbol) {
    return State::Ended;
}

OperatorsStateMachine::OperatorsStateMachine() {
    string binary_operators[] = {"+", "-", "*", "/", "%", "=", "&", "|", ">", "<", "&", "!", "^", ">>", "<<"};
    string double_operators[] = {"++", "--", "&&", "||", "::"};
    string unary_operators[] = {"(", ")", "~", "->", ".", "?", ":"};
    for (int i = 0; i < sizeof(binary_operators) / sizeof(string);i++) {
        operatorsTrie_.insert(binary_operators[i]);
        operatorsTrie_.insert(binary_operators[i] + "=");
    }
    for (int i = 0; i < sizeof(double_operators) / sizeof(string);i++) {
        operatorsTrie_.insert(double_operators[i]);
    }
    for (int i = 0; i < sizeof(unary_operators) / sizeof(string);i++) {
        operatorsTrie_.insert(unary_operators[i]);
    }
}
