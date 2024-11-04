#include <iostream>
#include <unordered_map>
#include <sstream>
#include <unordered_set>
#include <fstream>
#include <unordered_map>

using namespace std;


class SentimentLexicon{ //this class contains all of the vocabulary needed for the ana
    private:
        unordered_map<string, int> AFINN_lexicon; //holds AFINN vocab words and the sentiments
        unordered_map<string, int> VADER_lexicon; //holds VADER vocab words and the sentiments

    public:
        void loadAFINN(){ //loading AFINN vocab text file
            ifstream file("AFINNSentiment.txt");
            string line;

            while(getline(file, line)){
                istringstream iss(line);
                string word;
                int score;

                if(iss >> word >> score){ //adding each word and its score into unordered_map
                    AFINN_lexicon[word] = score;
                }
            }

            file.close();
        }

        void loadVader(){ //loading VADER vocab text file
            ifstream file("vader_lexicon.txt");
            string line;

            while(getline(file, line)){
                istringstream iss(line);
                string word;
                int score;
                if(iss >> word >> score){ //adding each word and its score into unordered_map
                    VADER_lexicon[word] = score;
                }
            }

            file.close();
        }


        double getAFINNSentiment(string word){ //getting sentiment for vocab word in AFINN file
            double afinnScore = AFINN_lexicon.count(word) ? AFINN_lexicon[word] : 0;
            return afinnScore;
        }

        double getVADERSentiment(string word){ //getting sentiment for vocab word in VADER file
            double afinnScore = VADER_lexicon.count(word) ? VADER_lexicon[word] : 0;
            return afinnScore;
        }
};