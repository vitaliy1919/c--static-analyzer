//
// Created by vitdmit on 2/23/19.
//

#ifndef LEXER_TOKEM_H
#define LEXER_TOKEM_H

#include <string>
#include <ostream>

class Token {

public:
    int row;
    int t_start;
    int t_end;
    std::string value;
    Token() {}

    friend std::ostream &operator<<(std::ostream &os, const Token &token) {
        os << "row: " << token.row << " t_start: " << token.t_start << " t_end: " << token.t_end << " value: "
           << token.value;
        return os;
    }

    Token(int row, int start, int t_end, std::string value = ""): row(row), t_start(start), t_end(t_end), value(value) {
    }
};


#endif //LEXER_TOKEM_H
