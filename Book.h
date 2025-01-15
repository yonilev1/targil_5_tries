#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Tries.h"
using namespace std;

class Book {
private:
    string content;
    Tries tries;
    // TODO: Add a trie attribute
    void processContent();
    vector<pair<vector<string>, int>> generateTrio(const string& text);


public:
    std::string cleanString(const std::string& str);
    Book(const string& filepath);
    string extractSentence(int location);
    void searchAndPrint(const string& query);
    void censorQuery(const string& query);

};
