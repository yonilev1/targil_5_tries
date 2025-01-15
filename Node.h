//
// Created by Yonil on 1/13/2025.
//

#ifndef NODE_H
#define NODE_H
#include <list>
#include <map>
#include <memory>

class Node {
private:
    bool endOfString;
    std::list <int> indexesOfString;
    std::map<char, Node*> suns;
public:
    Node();
    ~Node();
    void markEndOfString();
    void unMarkEndOfString();
    bool isEndOfString() const;
    void addIndex(int index);
    const std::list<int>& getIndexesOfString() const;
    void addSun(char ch);
    const std::map<char, Node*>& getSuns() const;
    Node* getChild(char ch) const;
    void printNode(const std::string& prefix = "") const;
};



#endif //NODE_H
