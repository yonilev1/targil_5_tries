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
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> findEndOfWord(const std::string& word) const;
    void preOrder(const std::shared_ptr<Node>& node, std::list<int>& results, int& visitedNodes, int maxResults) const;
public:
    Tries();
    ~Tries();
    void insert(std::string word, int index);
    std::list<int> search(const std::string &word);
};



#endif //TRIES_H
