// C++ implementation of search and insert 
// operations on Trie 
#include <bits/stdc++.h>
#include "FiniteMachines/CommentsFiniteMachine.h"
#include "FiniteMachines/StringLiteralFiniteMachine.h"
#include "FiniteMachines/NumbersFiniteMachine.h"
#include "FiniteMachines/OperatorsStateMachine.h"
#include "FiniteMachines/ReservedWordsFiniteMachine.h"
#include "Utils/trie.h"
#include "Utils/TokenRecognizer.h"
#include "Tokens/PreprocessorToken.h"

using namespace std;
  


// Driver 
int main() {
    std::cout << "\e[1mBold\e[0m non-bold" << std::endl;
    // Input keys (use only 'a' through 'z' 
    // and lower case) 
    string binary_operators[] = {"+", "-", "*", "/", "%", "=", "&", "|", ">", "<", "&", "!", "^", ">>", "<<"};
    string double_operators[] = {"++", "--", "&&", "||", "::"};
    string unary_operators[] = {"(", ")", "~", "->", ".", "?", ":"};
    Trie trie;
    for (int i = 0; i < sizeof(binary_operators) / sizeof(string);i++) {
        trie.insert(binary_operators[i]);
        trie.insert(binary_operators[i] + "=");
    }
    for (int i = 0; i < sizeof(double_operators) / sizeof(string);i++) {
        trie.insert(double_operators[i]);
    }
    for (int i = 0; i < sizeof(unary_operators) / sizeof(string);i++) {
        trie.insert(unary_operators[i]);
    }

    ifstream file("int.txt");
    ofstream tokens_file("tokens.txt");
    string line;
    string cur_string;
//    bool line_comment;
//    bool block_comment_start;
    int row_number = 1;
//    bool match_found = false;
//    while (getline(file, line)) {
//        for (int i = 0; i < line.size(); i++) {
//            int res = trie.searchByLetter(line[i]);
//            if (res == -1 || i == line.size() - 1) {
//                res = trie.searchByLetter(line[i]);
//                if (match_found) {
//                    tokens_file << "(" << row_number<<", "<<i - cur_string.size() + 1 <<"): "<<cur_string << endl;
//                }
//                match_found = false;
//                cur_string.clear();
//            }
//            if (res >= 0) {
//                //cout<<ANSI_RED<<line[i]<<ANSI_RESET;
//                cur_string += line[i];
//            }
//            if (res == 1) {
//                match_found = true;
//            }
//            if (res == -1 || i == line.size() - 1) {
//                if (res== -1)
//                    cout << line[i];
//                if (match_found) {
//                    tokens_file << "(" << row_number<<", "<<i - cur_string.size() + 1 <<"): "<<cur_string << endl;
//                }
//                match_found = false;
//                cur_string.clear();
//            }
//        }
//        cout<<endl;
//        row_number++;
//    }
    file.close();
    trie.printToFile("out.txt");
    cout<<"------------------------------------------"<<endl;
    file.open("int.txt");
    FiniteStateMachine *machine = new NumbersFiniteMachine();
    row_number = 1;
    State state;
    std::shared_ptr<Token> token = nullptr;
    TokenRecognizer tokenRecognizer;
    while (getline(file, line)) {
        int i = 0;
        cout << std::setprecision(6) << row_number <<": ";
        while (i < line.size()) {
            if (tokenRecognizer.isTokenProcessed() && line[i] == ' ') {
                cout << line[i];
                i++;
            } else {
                int start = i;
                try {
                    token = tokenRecognizer.recognizeToken(line, i, row_number);
                    if (tokenRecognizer.isTokenProcessed()) {
                        token->printColored();
                        tokens_file << *token << '\n';
                    } else
                        continue;
                    if (token->type == TokenTypes::Preprocessor) {
                        std::shared_ptr<PreprocessorToken> preToken = std::dynamic_pointer_cast<PreprocessorToken>(token);
                        cout << ' ';
                        for (auto &arg: preToken->args)
                            cout << arg << ' ';
                    }
                } catch (std::runtime_error &e) {
                    for (int j = start; j < i; j++)
                        cout << line[j];
                //    delete token;
                }
                   // cout << e.what() << endl;
            }
        }
        //cout<<"row: " << row_number << endl;
        if (tokenRecognizer.isTokenProcessed())
            cout << '\n';
        row_number++;
    }

//    while (getline(file, line)) {
//        for (int i = 0; i < line.size(); i++) {
//            state = machine->onInput(line[i]);
//            if (state == State::Undefined)
//                cout << line[i];
//            else
//                cout << ANSI_GREEN << line[i] << ANSI_RESET;
//            if (state == State::Ended) {
//                tokens_file << "(" << row_number<<", "<<i - machine->getCurrentString().size() + 1 <<"): "<<machine->getCurrentString() << endl;
//
//            }
//        }
//        state = machine->onInput('\n');
//        if (state == State::Ended) {
//            tokens_file << "(" << row_number<<", "<<line.size() - machine->getCurrentString().size() + 1 <<"): "<<machine->getCurrentString() << endl;
//
//        }
//        row_number++;
//        cout<<'\n';
//    }
    delete machine;
    tokens_file.close();
    file.close();
}
