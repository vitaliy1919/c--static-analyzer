//
// Created by vitdmit on 2/23/19.
//

#ifndef LEXER_TOKEM_H
#define LEXER_TOKEM_H

#include <string>
#include <iostream>

#include <sstream>
enum class TokenTypes {
    Number,
    Operator,
    StringLiteral,
    CharLiteral,
    ReservedWord,
    Comment,
    PunctuationMark,
    Indentifier,
    Preprocessor
};


using std::string;
class Token {

public:
    const string ANSI_RESET = "\e[0m";
    const string ANSI_BLACK = "\e[30m";
    const string ANSI_RED = "\e[31m";
    const string ANSI_GREEN = "\e[32m";
    const string ANSI_YELLOW = "\e[33m";
    const string ANSI_BLUE = "\e[34m";
    const string ANSI_PURPLE = "\e[35m";
    const string ANSI_CYAN = "\e[36m";
    const string ANSI_WHITE = "\e[37m";
    const string ANSI_BOLD = "\e[1m";
    const string ANSI_UNDERLINE = "\e[4m";
    const string ANSI_ITALIC = "\e[3m";

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
       //std::cout<<ANSI_BOLD<<"test"<<ANSI_RESET;
        switch (type) {
            case TokenTypes::Number:
                std::cout<<ANSI_RED;
                break;
            case TokenTypes::Operator:
                std::cout <<ANSI_YELLOW;
                break;
            case TokenTypes::CharLiteral:
                std::cout <<ANSI_BOLD<<ANSI_PURPLE;
                break;
            case TokenTypes::ReservedWord:
                std::cout << ANSI_BOLD << ANSI_BLUE;
                break;
            case TokenTypes::StringLiteral:
                std::cout << ANSI_BLUE;
                break;
            case TokenTypes::Comment:
                std::cout << ANSI_GREEN;
                break;
            case TokenTypes ::PunctuationMark:
                std::cout << ANSI_PURPLE;
                break;
            case TokenTypes ::Indentifier:
                std::cout << ANSI_CYAN;
                break;
            case TokenTypes::Preprocessor:
                std::cout << ANSI_BOLD << ANSI_GREEN;
                break;
        }
        std::cout<<value << ANSI_RESET;
    }

    Token(int row, int start, int t_end, const std::string& value = ""): row(row), t_start(start), t_end(t_end), value(value) {
    }

    virtual ~Token() {}

};


#endif //LEXER_TOKEM_H
