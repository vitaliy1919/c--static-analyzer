//
// Created by vitdmit on 2/23/19.
//

#ifndef LEXER_TOKEM_H
#define LEXER_TOKEM_H

#include <string>
#include <ostream>
#include <sstream>
enum class TokenTypes {
    Number,
    Operator,
    StringLiteral,
    ReservedWord
};

#include <string>
#include <iostream>

using std::string;
class Token {

public:
    const string ANSI_RESET = "\u001B[0m";
    const string ANSI_BLACK = "\u001B[30m";
    const string ANSI_RED = "\u001B[31m";
    const string ANSI_GREEN = "\u001B[32m";
    const string ANSI_YELLOW = "\u001B[33m";
    const string ANSI_BLUE = "\u001B[34m";
    const string ANSI_PURPLE = "\u001B[35m";
    const string ANSI_CYAN = "\u001B[36m";
    const string ANSI_WHITE = "\u001B[37m";
    int row;
    int t_start;
    int t_end;
    std::string value;
    TokenTypes type;
    Token() {}

    friend std::ostream &operator<<(std::ostream &os, const Token &token) {
        os << "row: " << token.row << " t_start: " << token.t_start << " t_end: " << token.t_end << " value: "
           << token.value << " type: ";
        return os;
    }

    friend std::string toString(const Token &token) {
        std::stringstream os;
         os << "row: " << token.row << " t_start: " << token.t_start << " t_end: " << token.t_end << " value: "
           << token.value;
        return os.str();
    }

    void printColored() {
        switch (type) {
            case TokenTypes::Number:
                std::cout<<ANSI_RED;
                break;
            case TokenTypes::Operator:
                std::cout <<ANSI_YELLOW;
                break;
            case TokenTypes::ReservedWord:
                std::cout << ANSI_CYAN;
                break;
            case TokenTypes::StringLiteral:
                std::cout << ANSI_GREEN;
                break;
        }
        std::cout<<value << ANSI_RESET;
    }

    Token(int row, int start, int t_end, std::string value = ""): row(row), t_start(start), t_end(t_end), value(value) {
    }
};


#endif //LEXER_TOKEM_H
