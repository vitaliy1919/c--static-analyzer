// C++ implementation of search and insert 
// operations on Trie 
#include <bits/stdc++.h>
#include "FiniteMachines/CommentsFiniteMachine.h"
#include "FiniteMachines/StringLiteralFiniteMachine.h"
#include "FiniteMachines/NumbersFiniteMachine.h"
using namespace std;
  
const int ALPHABET_SIZE = 26; 

const string ANSI_RESET = "\u001B[0m";
const string ANSI_BLACK = "\u001B[30m";
const string ANSI_RED = "\u001B[31m";
const string ANSI_GREEN = "\u001B[32m";
const string ANSI_YELLOW = "\u001B[33m";
const string ANSI_BLUE = "\u001B[34m";
const string ANSI_PURPLE = "\u001B[35m";
const string ANSI_CYAN = "\u001B[36m";
const string ANSI_WHITE = "\u001B[37m";
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
    bool line_comment;
    bool block_comment_start;
    int row_number = 1;
    bool match_found = false;
    while (getline(file, line)) {
        for (int i = 0; i < line.size(); i++) {
            int res = trie.searchByLetter(line[i]);
            if (res == -1 || i == line.size() - 1) {
                res = trie.searchByLetter(line[i]);
                if (match_found) {
                    tokens_file << "(" << row_number<<", "<<i - cur_string.size() + 1 <<"): "<<cur_string << endl;
                }
                match_found = false;
                cur_string.clear();
            }
            if (res >= 0) {
                cout<<ANSI_RED<<line[i]<<ANSI_RESET;
                cur_string += line[i];
            }
            if (res == 1) {
                match_found = true;
            }
            if (res == -1 || i == line.size() - 1) {
                if (res== -1)
                    cout << line[i];
                if (match_found) {
                    tokens_file << "(" << row_number<<", "<<i - cur_string.size() + 1 <<"): "<<cur_string << endl;
                }
                match_found = false;
                cur_string.clear();
            }
        }
        cout<<endl;
        row_number++;
    }
    file.close();
    trie.printToFile("out.txt");
    cout<<"------------------------------------------"<<endl;
    file.open("int.txt");
    FiniteStateMachine *machine = new NumbersFiniteMachine();
    row_number = 1;
    State state;
    while (getline(file, line)) {
        int i = 0;
        while (i < line.size()) {
            if (line[i] == ' ')
                i++;
            else {
                state = machine->processString(line, i, row_number);
                if (state == State::Ended)
                    cout << machine->getToken() << endl;
            }
        }
        //cout<<"row: " << row_number << endl;
        if (row_number == 34)
            int a = 2;
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

}
