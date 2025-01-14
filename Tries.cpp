//
// Created by Yonil on 1/13/2025.
//

#include "Tries.h"

#include <iostream>

Tries::Tries(): root(std::make_shared<Node>()) {}

Tries::~Tries() = default;

void Tries::insert(std::string word, int index) {
    auto current = root;
    for(char ch : word) {
        current->addSun(ch);
        current = current->getChild(ch);
    }
    current ->markEndOfString();
    current->addIndex(index);
}

std::shared_ptr<Node> Tries::findEndOfWord(const std::string& word) const {
    auto current = root;
    for(char ch : word) {
        current = current->getChild(ch);
        if(!current) {
            return nullptr;
        }
    }
    return current;
}

void Tries::preOrder(const std::shared_ptr<Node>& node, std::list<int>& results, int& visitedNodes, int maxResults) const {
    if(!node || results.size() >= maxResults) {
        return;
    }
    visitedNodes++;

    if(node->isEndOfString()) {
        for(int index : node->getIndexesOfString()) {
            if(results.size() < maxResults) {
                results.push_back(index);
            }
        }
    }

    for(auto& child : node->getSuns()) {
        preOrder(child.second, results, visitedNodes, maxResults);
    }
}

std::list<int> Tries::search(const std::string& word)  {
    auto startNode = findEndOfWord(word);
    std::list<int> result;
    int visitedNodes = 0;

    if(startNode) {
        preOrder(startNode, result, visitedNodes, 3);
    }

    std::cout << "The search required visiting " << visitedNodes << " nodes" << std::endl;
    return result;
}