#include <iostream>
#include "SentimentLexicon.cpp"
#include "Tweet.cpp"
#include "Tokenizer.cpp"
#include <cctype>
using namespace std;

//Average sentence length: 13 words

class SentimentAnalyzer{ //this class will be used to execute all functions needed to detect accuracy
    private:
        SentimentLexicon* lexicon;
    public:
        double analyzeTweetSentiment(Tweet* tweet);

        SentimentAnalyzer(){
            lexicon = new SentimentLexicon();
            lexicon->loadAFINN();
            lexicon->loadVader();
        }
};


double SentimentAnalyzer::analyzeTweetSentiment(Tweet* tweet){
    Tokenizer tokenizer;
    const char* delimiters = " ,.!?\"';:";
    vector<string> tokens = tokenizer.tokenize(tweet->getText(), delimiters);

    int totalScore = 0;
    double wordTotal = 0;
    int uppercaseCount = 0;
    int letterCount = 0;

    for (string word : tokens) {
        // Count uppercase letters in the original word
        for (char c : word) {
            if (isalpha(c)) {
                letterCount++;
                if (isupper(c)) {
                    uppercaseCount++;
                }
            }
        }

        // Convert word to lowercase for sentiment analysis
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        double afinnScore = lexicon->getAFINNSentiment(word);
        if(afinnScore < 0 && word.size() >= 6){
            afinnScore -= 2;
        }

        double vaderScore = lexicon->getVADERSentiment(word);
        if(vaderScore < 0 && word.size() >= 6){
            vaderScore -= 2;
        }

        wordTotal++;
        totalScore += (afinnScore * 4) + (vaderScore * 2);
    }

    // Check uppercase letter proportion
    double uppercaseProportion = (letterCount > 0) ? (double)uppercaseCount / letterCount : 0;
    if (uppercaseProportion > 0.3) { // Deduct if >30% of letters are uppercase
        totalScore -= 5; // Adjust this deduction value as needed
    }

    return (wordTotal > 0) ? totalScore / wordTotal : 0;
}