//
// Created by vitdmit on 2/22/19.
//

#ifndef LEXER_FINITESTATEMACHINE_H
#define LEXER_FINITESTATEMACHINE_H
#include <string>
#include "../Tokens/Token.h"

enum class State {
    Running,
    Ended,
    Undefined
};

class FiniteStateMachine {
protected:
    Token *token_;
    std::string current_string_;
    State public_state_ = State::Running;
    int inner_state_;
    virtual State handleInput(char symbol) = 0;

public:
    virtual const std::string &getCurrentString() const;
    virtual Token* getToken() = 0;
    virtual State onInput(char symbol);
    virtual State processString(std::string str, int& i, int row) = 0;

};


#endif //LEXER_FINITESTATEMACHINE_H
