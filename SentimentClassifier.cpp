#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <unordered_set>

using namespace std;

class SentimentClassifier{
    public:

    

static int analyzeTweetSentiment(string& tweet, unordered_map<string, int>& afinn, unordered_map<string, int>& vader) {
    istringstream stream(tweet);
    string word;
    int totalScore = 0;

    int tweetLength = tweet.length();

    while (stream >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        int afinnScore = afinn.count(word) ? afinn[word] : 0;

        totalScore += (afinnScore);
    }


    return totalScore;
}

};