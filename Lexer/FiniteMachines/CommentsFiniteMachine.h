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
    std::string cur_line;
    bool isFirstLine = true;
    bool isLastLine = false;
protected:

    virtual State handleInput(char symbol) override;
public:
    CommentsFiniteMachine() {
        inner_state_ = 0;
    }

    State processString(const string &str, int &i, int row) override;

    void setIsLastLine(bool isLastLine);

};


#endif //LEXER_COMMENTSFINITEMACHINE_H
