//
// Created by vitdmit on 2/24/19.
//

#ifndef LEXER_TRIE_H
#define LEXER_TRIE_H

#include <unordered_map>
#include <queue>
#include <utility>
#include <fstream>

template <typename Key, typename Value>
class mapE: public std::unordered_map<Key, Value> {
public:
    bool in(const Key& key) {

        return this->find(key) != this->end();
    }
};
// trie node
struct TrieNode
{
    mapE<char, TrieNode*> children;

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

class Trie {
    TrieNode *root_ = nullptr;
    TrieNode* iter_ = nullptr;
public:
    void insert(std::string key) {
        if (root_ == nullptr)
            root_ = new TrieNode();
        TrieNode *iter = root_;
        for (int i = 0; i < key.size(); i++) {
            if (!iter->children.in(key[i])) {
                iter->children[key[i]] = new TrieNode();
            }
            iter = iter->children[key[i]];
        }
        iter->isEndOfWord = true;
    }

    void printToFile(std::string fileName) {
        std::queue<std::pair<TrieNode*, std::string>> nodes;
        nodes.push(std::make_pair(root_, ""));
        std::ofstream file("out.txt");
        file << "digraph {\n";
        std::hash<std::string> str;
        while (!nodes.empty()) {
            auto top = nodes.front();
            nodes.pop();
            file << "\tLabel"<<str(top.second)<<"[label=\""<<top.second<<"\"]\n";
            auto& letters = top.first->children;
            for (auto iter = letters.begin(); iter != letters.end(); ++iter) {
                std::string a = top.second;
                a += iter->first;
                file <<"\tLabel"<< str(top.second)<<"->Label"<<str(a) << std::endl;
                nodes.push(make_pair(iter->second, a));
            }
        }
        file << "}" << std::endl;
        file.close();
    }

    short searchByLetter(char letter) {
        if (iter_ == nullptr)
            iter_ = root_;
        auto letters = iter_->children;
        if (!letters.in(letter)) {
            iter_ = root_;
            return -1;
        }
        iter_ = letters[letter];

        if (letters[letter]->isEndOfWord) {
            //iter_ = root_;
            return 1;
        }
        return 0;
    }

    bool findMaxSubstring(std::string str, int& i) {
        TrieNode *iter = root_;
        bool flag = false;
        int cur_max = -1;
        do {
            auto &letters = iter->children;
            if (letters.in(str[i])) {
                iter = letters[str[i]];
                if (iter->isEndOfWord)
                    cur_max = i;
            } else
                flag = true;
        } while (!flag);
        if (cur_max != -1)
            i = cur_max;
        return cur_max != -1;
    }
};

#endif //LEXER_TRIE_H
