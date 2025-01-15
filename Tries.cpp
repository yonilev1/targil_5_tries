// Tries.cpp
// This file contains the implementation of the Tries class, which implements the Trie data structure.

#include "Tries.h"  // Includes the header file for the Tries class.
#include <iostream>

// Constructor: Initializes the root node as an empty Node.
Tries::Tries() : root(new Node()) {}

// Destructor: Default destructor for the Tries class.
Tries::~Tries() = default;

// Inserts a word into the Trie. For each character in the word, the function adds the character
// to the current node's child and moves down to the next child. After inserting all characters,
// the node is marked as the end of the string, and the index is added to the list of indexes at that node.
void Tries::insert(std::string word, int index) {
    auto current = root;
    for(char ch : word) {
        current->addSun(ch);
        current = current->getChild(ch);
    }
    current->markEndOfString();
    current->addIndex(index);
}

// Finds the node that marks the end of the given word in the Trie. If the word is found, the node
// is returned; otherwise, nullptr is returned.
Node* Tries::findEndOfWord(const std::string& word) const {
    auto current = root;
    for(char ch : word) {
        current = current->getChild(ch);
        if(!current) {
            return nullptr;
        }
    }
    return current;
}

// Pre-order traversal of the Trie. The function visits each node and collects the indexes of strings
// that end at that node. It stops when the desired number of results (maxResults) is collected.
void Tries::preOrder(const Node* node, std::list<int>& results, int& visitedNodes, int maxResults) const {

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

    // Recursively visit child nodes.
    for(auto& child : node->getSuns()) {
        preOrder(child.second, results, visitedNodes, maxResults);
    }
}

// Searches for a word in the Trie. If the word exists, it collects up to 3 indexes where the word is found
// and returns them as a list.
std::list<int> Tries::search(const std::string& word)  {
    auto startNode = findEndOfWord(word);
    std::list<int> result;
    int visitedNodes = 0;

    if(startNode) {
        preOrder(startNode, result, visitedNodes, 3);
    }

    // Output the number of nodes visited during the search.
    std::cout << "The search required visiting " << visitedNodes << " nodes" << std::endl;
    return result;
}

// Deletes a word from the Trie. The function calls search until the word is found, then removes the end
// of string marker for that word.
void Tries::deleteWord(const std::string &word) {
    while(!search(word).empty()) {
        auto endNode = findEndOfWord(word);
        endNode->unMarkEndOfString();
    }
}

// Prints the entire Trie by calling a recursive function that traverses the Trie and prints details of each node.
void Tries::printTrie() const {
    if (!root) {
        std::cout << "Trie is empty.\n";
        return;
    }
    std::cout << "Printing Trie:\n";
    printNodeRecursive(root, "");
}

// Recursively prints details of a node and its children. The details include whether the node marks the
// end of a string and the indexes stored at that node.
void Tries::printNodeRecursive(const Node* node, const std::string& prefix) const {
    if (!node) {
        return;
    }

    // Print current node details
    std::cout << prefix << "Node: endOfString=" << (node->isEndOfString() ? "true" : "false") << ", indexes={";
    for (int index : node->getIndexesOfString()) {
        std::cout << index << " ";
    }
    std::cout << "}, children={";
    for (const auto& child : node->getSuns()) {
        std::cout << child.first << " ";
    }
    std::cout << "}\n";

    // Recursive call for each child
    for (const auto& child : node->getSuns()) {
        printNodeRecursive(child.second, prefix + "  ");
    }
}