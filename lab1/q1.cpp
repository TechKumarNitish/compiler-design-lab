#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <cctype>
#include <map>

using namespace std;

bool isKeyword(const string &word);
bool isOperator(const char ch);
bool isPunctuation(const char ch);
bool isIdentifier(const string &word);
bool isNumber(const string &word);


const unordered_set<string> keywords = {"int", "float", "if", "else", "return"};

const unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>', '!'};


const unordered_set<char> punctuations = {',', ';', '(', ')', '{', '}'};

int main() {
    int numLines;
    cout << "Enter number of lines: ";
    cin >> numLines;
    cin.ignore(); 

    vector<string> lines(numLines);
    cout << "Enter the code:\n";
    for (int i = 0; i < numLines; ++i) {
        getline(cin, lines[i]);
    }

    vector<string> keywordsFound;
    vector<string> identifiers;
    vector<string> constants;
    vector<char> operatorsFound;
    vector<char> punctuationsFound;

    int tokenCount = 0;

    for (const string &line : lines) {
        stringstream ss(line);
        string token;

        while (ss >> token) {

            if (isKeyword(token)) {
                keywordsFound.push_back(token);
            } else if (isNumber(token)) {
                constants.push_back(token);
            } else if (isIdentifier(token)) {
                identifiers.push_back(token);
            } else {
                // Check for individual characters
                for (char ch : token) {
                    if (isOperator(ch)) {
                        operatorsFound.push_back(ch);
                    } else if (isPunctuation(ch)) {
                        punctuationsFound.push_back(ch);
                    }
                }
            }
        }
    }

    // Print results
    cout << "Keywords: " << keywordsFound.size() << " (";
    for (size_t i = 0; i < keywordsFound.size(); ++i) {
        if (i > 0) cout << " ";
        cout << keywordsFound[i];
    }
    cout << ")\n";

    cout << "Operators: " << operatorsFound.size() << "\n";

    cout << "Constants: " << constants.size() << " (";
    for (size_t i = 0; i < constants.size(); ++i) {
        if (i > 0) cout << " ";
        cout << constants[i];
    }
    cout << ")\n";

    cout << "Punctuations: " << punctuationsFound.size() << " (";
    for (size_t i = 0; i < punctuationsFound.size(); ++i) {
        if (i > 0) cout << " ";
        cout << punctuationsFound[i];
    }
    cout << ")\n";

    cout << "Identifiers: " << identifiers.size() << " (";
    for (size_t i = 0; i < identifiers.size(); ++i) {
        if (i > 0) cout << " ";
        cout << identifiers[i];
    }
    cout << ")\n";

    cout << "Tokens: " << keywordsFound.size() + operatorsFound.size() + constants.size() + punctuationsFound.size() + identifiers.size() << "\n";

    return 0;
}

bool isKeyword(const string &word) {
    return keywords.find(word) != keywords.end();
}

bool isOperator(const char ch) {
    return operators.find(ch) != operators.end();
}

bool isPunctuation(const char ch) {
    return punctuations.find(ch) != punctuations.end();
}

bool isIdentifier(const string &word) {
    if (isKeyword(word) || isNumber(word)) return false;
    if (!isalpha(word[0]) && word[0] != '_') return false;

    for (char ch : word) {
        if (!isalnum(ch) && ch != '_') return false;
    }
    return true;
}

bool isNumber(const string &word) {
    bool hasDecimal = false;
    for (size_t i = 0; i < word.length(); ++i) {
        if (word[i] == '.') {
            if (hasDecimal) return false; 
            hasDecimal = true;
        } else if (!isdigit(word[i])) {
            return false;
        }
    }
    return true;
}