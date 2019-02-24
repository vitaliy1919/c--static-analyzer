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
using namespace std;
  


// Driver 
int main() {
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
    Token * token = nullptr;
    while (getline(file, line)) {
        int i = 0;
        while (i < line.size()) {
            if (line[i] == ' ') {
                cout << line[i];

                i++;
            } else {
                int start = i;
                try {
                    token = TokenRecognizer::recognizeToken(line, i, row_number);
                    tokens_file << *token << '\n';
                    token->printColored();
                } catch (std::runtime_error &e) {
                    for (int j = start; j < i; j++)
                        cout << line[j];
                   // cout << e.what() << endl;
                }
            }
        }
        //cout<<"row: " << row_number << endl;
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
