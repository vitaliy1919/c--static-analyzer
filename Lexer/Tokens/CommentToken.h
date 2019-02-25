//
// Created by i503709 on 2/25/19.
//

#ifndef LEXER_STRINGTOKEN_H
#define LEXER_STRINGTOKEN_H

#include "Token.h"

class CommentToken: public Token {
public:
    int row_end;


};
#endif //LEXER_STRINGTOKEN_H
