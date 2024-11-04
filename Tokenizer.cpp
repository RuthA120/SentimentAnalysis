#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <cctype>

using namespace std;

class Tokenizer{ //class is used to split up text into individual words
    public:
        vector<string> tokenize(string text, const char* delimiters) {
            vector<string> tokens; //holds tokens in vector

            char* cstr = new char[text.length() + 1]; 
            strcpy(cstr, text.c_str()); //copying string content

            char* token = strtok(cstr, delimiters); //get first token
            while (token != nullptr) { //looping till no tokens
                tokens.push_back(token); //continuously add tokens to vector
                token = strtok(nullptr, delimiters); //get next token
            }

            delete[] cstr; //cleaning up allocated memory
            return tokens; //return all tokens
        }
};