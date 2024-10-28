#include <iostream>
#include <unordered_map>
#include <sstream>
#include <unordered_set>
#include <fstream>
#include <unordered_map>

using namespace std;


class SentimentLexicon{
    public: 
        static unordered_map<string, int> loadAFINN(string fileName){
            unordered_map<string, int> vocabulary;
            ifstream file(fileName);
            string line;

            while(getline(file, line)){
                istringstream iss(line);
                string word;
                int score;

                if(iss >> word >> score){
                    vocabulary[word] = score;
                }
            }

            file.close();
            return vocabulary;
        }

        static unordered_map<string, int> loadVader(string fileName){
            unordered_map<string, int> vocabulary;
            ifstream file(fileName);
            string line;

            while(getline(file, line)){
                istringstream iss(line);
                string word;
                int score;

                if(iss >> word >> score){
                    vocabulary[word] = score;
                }

                string ignore;
                
            }

            file.close();
            return vocabulary;
        }

        

};