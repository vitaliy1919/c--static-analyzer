//
// Created by vitdmit on 2/22/19.
//

#ifndef LEXER_COMMENTSFINITEMACHINE_H
#define LEXER_COMMENTSFINITEMACHINE_H


#include "FiniteStateMachine.h"
class CommentsFiniteMachine: public FiniteStateMachine {
private:
    State firstState(char symbol);
    State secondState(char symbol);
    State thirdState(char symbol);
    void fourthState(char symbol);
    void fifthState(char symbol);
protected:

    virtual State handleInput(char symbol) override;
public:
    CommentsFiniteMachine() {
        inner_state_ = 0;
    }

    State processString(std::string str, int &i, int row) override;


};


#endif //LEXER_COMMENTSFINITEMACHINE_H
