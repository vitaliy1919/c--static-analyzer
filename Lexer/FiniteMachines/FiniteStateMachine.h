//
// Created by vitdmit on 2/22/19.
//

#ifndef LEXER_FINITESTATEMACHINE_H
#define LEXER_FINITESTATEMACHINE_H
#include <string>
#include "../Tokens/Token.h"
#include <memory>
enum class State {
    Running,
    Ended,
    Undefined
};

class FiniteStateMachine {
protected:
    std::shared_ptr<Token> token_;
    std::string current_string_;
    State public_state_ = State::Running;
    int inner_state_;
    virtual State handleInput(char symbol) {
        return State::Ended;
    }

public:
    virtual const std::string &getCurrentString() const;
    virtual std::shared_ptr<Token> getToken() {
        return token_;
    }
    virtual State onInput(char symbol);
    virtual State processString(const string &str, int &i, int row) = 0;

    virtual ~FiniteStateMachine() {}
};


#endif //LEXER_FINITESTATEMACHINE_H
