#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <cctype>

using namespace std;

class Tokenizer{
    public:
    // This method will take a string and delimiters and return a list of words (tokens)
    
    vector<string> tokenize(string& text, const char* delimiters) {
        vector<string> tokens; // This will hold our tokens (words)
        // Allocate a char array (C-style string) and copy the text into it
        char* cstr = new char[text.length() + 1]; 
        strcpy(cstr, text.c_str()); // Copy the content of the string

        // Start tokenizing
        char* token = strtok(cstr, delimiters); // Get the first token
        while (token != nullptr) { // While we have tokens
            tokens.push_back(token); // Add the token to our list
            token = strtok(nullptr, delimiters); // Get the next token
        }

        delete[] cstr; // Clean up the allocated memory
        return tokens; // Return the list of tokens
    }
};