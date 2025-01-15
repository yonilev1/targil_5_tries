#include "Book.h"
#include <algorithm>
#include <string>
#include <regex>
#include <list>
#include "Tries.h"

using namespace std;

// Constructor: Reads the content of the file, processes it, and initializes the Trie.
Book::Book(const string& filepath) {
    // Open the file at the specified filepath
    ifstream file(filepath);

    // Check if the file is successfully opened
    if (file.is_open()) {
        // Read the entire content of the file into a stringstream
        stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str(); // Store the content
        file.close();

        // Transform the content to lowercase
        transform(content.begin(), content.end(), content.begin(), ::tolower);

        // Replace consecutive whitespaces with a single space using regular expressions
        regex pattern("\\s+"); // Matches one or more whitespace characters
        content = regex_replace(content, pattern, " ");

        // Insert content into the Trie
        processContent();
    } else {
        // If the file fails to open, throw an exception
        throw invalid_argument("Unable to open file");
    }
}

// Cleans a string by keeping only alphanumeric characters and spaces.
std::string Book::cleanString(const std::string& str) {
    std::string cleaned;
    for (char c : str) {
        if (isalnum(c) || isspace(c)) {
            cleaned += c;
        }
    }
    return cleaned;
}

// Splits the text into triplets (trios) of consecutive words and tracks their starting positions.
vector<pair<vector<string>, int>> Book::generateTrio(const string& text) {
    vector<pair<vector<string>, int>> result; // Stores triplets and their positions
    vector<string> words; // Holds the words of the text
    string word;
    int position = 0;

    istringstream stream(text);
    while (stream >> word) {
        words.push_back(word); // Extract words from the text
    }

    // Generate triplets from the words
    for (size_t i = 0; i + 3 <= words.size(); ++i) {
        vector<string> trio = {cleanString(words[i]), cleanString(words[i + 1]), cleanString(words[i + 2])};
        result.emplace_back(trio, position);

        // Log generated trio for debugging
        std::cout << "Generated trio: [" << trio[0] << ", " << trio[1] << ", " << trio[2]
                  << "], position: " << position << std::endl;

        // Update the starting position for the next trio
        position += words[i].length() + 1;
    }
    return result;
}

// Processes the content by generating trios and inserting them into the Trie.
void Book::processContent() {
    vector<pair<vector<string>, int>> myTrios = generateTrio(content); // Generate trios

    for (auto pair : myTrios) {
        // Combine the trio into a single string and insert into the Trie
        string combinedWords = pair.first[0] + " " + pair.first[1] + " " + pair.first[2];
        tries.insert(combinedWords, pair.second);

        // Log inserted trio for debugging
        std::cout << "Inserted into Trie: \"" << combinedWords << "\", at position: " << pair.second << std::endl;
    }
}

// Searches for a query in the Trie and prints sentences containing the query.
void Book::searchAndPrint(const string& query) {
    list<int> locations = tries.search(query); // Search for the query in the Trie

    if (locations.empty()) {
        cout << "No results" << endl; // Print a message if no results are found
        return;
    }

    cout << "Sentences matching the prefix:" << endl;

    for (int location : locations) {
        string sentence = extractSentence(location); // Extract the sentence around the location
        cout << sentence << endl; // Print the sentence
    }
}

// Extracts a sentence around a given location in the content.
string Book::extractSentence(int location) {
    if (location < 0 || location >= content.size()) {
        throw std::out_of_range("Location is out of bounds"); // Validate the location
    }

    // Find the start of the sentence
    int startPos = location;
    int wordCount = 0;
    while (startPos > 0 && wordCount < 5 && content[startPos] != '.') {
        if (isspace(content[startPos])) {
            wordCount++;
        }
        startPos--;
    }
    if (content[startPos] == '.') {
        startPos++;
    }

    // Find the end of the sentence
    int endPos = location;
    wordCount = 0;
    while (endPos < content.size() && wordCount < 10 && content[endPos] != '.') {
        if (isspace(content[endPos])) {
            wordCount++;
        }
        endPos++;
    }

    // Construct the sentence with markers for the query's location
    string sentence;
    if (startPos > 0) {
        sentence += "...";
    }
    sentence += content.substr(startPos, location - startPos);
    sentence += "*"; // Mark the location
    sentence += content.substr(location, endPos - location);
    if (endPos < content.size()) {
        sentence += "...";
    }

    return sentence;
}

// Removes all occurrences of a query from the Trie.
void Book::censorQuery(const string& query) {
    tries.deleteWord(query); // Mark the query as non-end-of-word in the Trie
}
