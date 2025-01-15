// Node.cpp
// This file contains the implementation of the Node class used in the Trie.

#include "Node.h"  // Includes the header file for the Node class.
#include <iostream>
#include <list>

// Constructor: Initializes the node with endOfString set to false.
Node::Node() : endOfString{false} {}

// Destructor: Default destructor for the Node class.
Node::~Node() = default;

// Marks the node as the end of a string.
void Node::markEndOfString() {
    this->endOfString = true;
}

// Unmarks the node as the end of a string.
void Node::unMarkEndOfString() {
    this->endOfString = false;
}

// Returns true if the node marks the end of a string.
bool Node::isEndOfString() const {
    return this->endOfString;
}

// Adds an index to the node.
void Node::addIndex(const int index) {
    this->indexesOfString.push_back(index);
}

// Returns the list of indexes associated with the node.
const std::list<int> &Node::getIndexesOfString() const {
    return this->indexesOfString;
}

// Adds a child node for the given character if it does not already exist.
void Node::addSun(char ch) {
    if (suns.find(ch) == suns.end()) {
        suns[ch] = new Node();
    }
}

// Returns the map of child nodes.
const std::map<char, Node*>& Node::getSuns() const {
    return suns;
}

// Returns the child node associated with the given character.
Node* Node::getChild(char ch) const {
    auto it = suns.find(ch);
    return (it != suns.end()) ? it->second : nullptr;
}

// Prints the node's details, including its children and indexes.
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

    // Recursively print children nodes.
    for (const auto& pair : suns) {
        pair.second->printNode(prefix + "  ");
    }
}