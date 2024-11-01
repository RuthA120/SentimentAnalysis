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


double SentimentAnalyzer::analyzeTweetSentiment(Tweet* tweet) {
    Tokenizer tokenizer;
    const char* delimiters = " ,.!?\"';:-@/";
    vector<string> tokens = tokenizer.tokenize(tweet->getText(), delimiters);

    int totalScore = 0;
    double wordTotal = 0;
    bool isNegated = false;
    bool isFrustration = false;
    bool isSarcasm = false;
    bool isWord = false;

    // Define and populate negators, frustration indicators, sarcasm indicators, and dissatisfaction terms
    unordered_set<string> negators;
    negators.insert("not");
    negators.insert("no");
    negators.insert("never");
    negators.insert("nor");
    negators.insert("none");
    negators.insert("hardly");
    negators.insert("neither");
    negators.insert("nothing");
    negators.insert("nobody");

    unordered_set<string> frustrationTerms;
    frustrationTerms.insert("ugh");
    frustrationTerms.insert("meh");
    frustrationTerms.insert("wish");
    frustrationTerms.insert("miss");
    frustrationTerms.insert("need");
    frustrationTerms.insert("want");
    frustrationTerms.insert("don't");
    frustrationTerms.insert("dont");
    frustrationTerms.insert("won't");
    frustrationTerms.insert("wont");

    for (size_t i = 0; i < tokens.size(); ++i) {
        string word = tokens[i];
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Check for negation
        if (negators.count(word)) {
            isNegated = true;
            isWord = true;
        }

        // Check for frustration and dissatisfaction
        if (frustrationTerms.count(word)) {
            isFrustration = true;
            isWord = true;
        }

        // Check for sentiment score in lexicon
        double afinnScore = lexicon->getAFINNSentiment(word);
        double vaderScore = lexicon->getVADERSentiment(word);

        // Apply negation and sarcasm adjustments
        if (isNegated && !isWord) {
            afinnScore = -afinnScore * 1.5;
            vaderScore = -vaderScore * 0.5;
            isNegated = false;
        }
        // Long negative words and repeated characters emphasis
        if (afinnScore < 0 && word.size() >= 7) {
            afinnScore -= word.size() / 2.0;
        }
        if (vaderScore < 0 && word.size() >= 7) {
            vaderScore -= word.size() / 2.0;
        }

        // Adjust for frustration terms
        if (isFrustration) {
            afinnScore -= 3;
            vaderScore -= 3;
            isFrustration = false;
        }

        // Calculate total score with updated weights
        wordTotal++;
        totalScore += (afinnScore * 4) + (vaderScore * 2);
        isWord = false;
    }

    return totalScore / wordTotal;
}
