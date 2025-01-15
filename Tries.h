//
// Created by Yonil on 1/13/2025.
//

#ifndef TRIES_H
#define TRIES_H
#include <list>
#include <string>

#include "Node.h"


class Tries {
private:
    Node* root;
    Node* findEndOfWord(const std::string& word) const;
    void preOrder(const Node* node, std::list<int>& results, int& visitedNodes, int maxResults) const;
    void printNodeRecursive(const Node* node, const std::string& prefix) const;

public:
    Tries();
    ~Tries();
    void insert(std::string word, int index);
    std::list<int> search(const std::string &word);
    void printTrie() const;
    void deleteWord(const std::string &word);
};



#endif //TRIES_H
