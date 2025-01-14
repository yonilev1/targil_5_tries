//
// Created by Yonil on 1/13/2025.
//

#include "Node.h"

#include <iostream>
#include <list>

Node::Node(): endOfString{false} {}

Node::~Node() = default;

void Node::markEndOfString() {
    this->endOfString = true;
}

bool Node::isEndOfString() const{
    return this->endOfString;
}

void Node::addIndex(const int index) {
    this->indexesOfString.push_back(index);
}

const std::list<int> &Node::getIndexesOfString() const{
    return this->indexesOfString;
}

void Node::addSun(char ch) {
    if (suns.find(ch) == suns.end()) {
        suns[ch] = std::make_shared<Node>();
    }
}

const std::map<char, std::shared_ptr<Node>>& Node::getSuns() const {
    return suns;
}

std::shared_ptr<Node> Node::getChild(char ch) const {
    auto it = suns.find(ch);
    return (it != suns.end()) ? it->second : nullptr;
}

void Node::printNode(const std::string& prefix) const {
    std::cout << prefix << "Node: endOfString=" << endOfString << ", indexes={";
    for (int index : indexesOfString) {
        std::cout << index << " ";
    }
    std::cout << "}, children={";
    for (const auto& pair : suns) {
        std::cout << pair.first << " ";
    }
    std::cout << "}\n";

    for (const auto& pair : suns) {
        pair.second->printNode(prefix + "  ");
    }

}

