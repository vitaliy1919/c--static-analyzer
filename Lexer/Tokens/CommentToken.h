//
// Created by i503709 on 2/25/19.
//

#ifndef LEXER_STRINGTOKEN_H
#define LEXER_STRINGTOKEN_H

#include <vector>
#include "Token.h"

class CommentToken: public Token {
public:
    int row_end;
    std::vector<std::string> lines;

};
#endif //LEXER_STRINGTOKEN_H
