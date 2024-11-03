#include <iostream>
#include <algorithm>
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
    const char* delimiters = " ,.!?\"';:-/*";
    vector<string> tokens = tokenizer.tokenize(tweet->getText(), delimiters);

    int totalScore = 0;
    double wordTotal = 0;
    bool isNegated = false;
    bool isFrustration = false;
    bool isWord = false;

    unordered_set<string> negators; //negator words -- these will be used 
    negators.insert("not");
    negators.insert("no");
    negators.insert("never");
    negators.insert("wasn't");
    negators.insert("wasnt");
    negators.insert("didn't");
    negators.insert("didnt");
    negators.insert("don't");
    negators.insert("dont");
    negators.insert("won't");
    negators.insert("wont");
    negators.insert("havent");
    negators.insert("shouldn't");
    negators.insert("shouldnt");
    negators.insert("wouldn't");
    negators.insert("wouldnt");
    negators.insert("haven't");
    negators.insert("nor");
    negators.insert("none");
    negators.insert("nowhere");
    negators.insert("neither");
    negators.insert("nothing");
    negators.insert("nobody");

    unordered_set<string> frustrationTerms;
    frustrationTerms.insert("ugh");
    frustrationTerms.insert("meh");
    frustrationTerms.insert("meh");
    frustrationTerms.insert("why");
    frustrationTerms.insert("whatever");
    frustrationTerms.insert("frustrated");
    frustrationTerms.insert("anymore");
    frustrationTerms.insert("annoy");
    frustrationTerms.insert("annoyed");
    frustrationTerms.insert("sigh");
    frustrationTerms.insert("wish");
    frustrationTerms.insert("bored");
    frustrationTerms.insert("miss");
    frustrationTerms.insert("need");
    frustrationTerms.insert("want");

    for (size_t i = 0; i < tokens.size(); ++i) {
        string word = tokens[i];
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        double afinnScore = lexicon->getAFINNSentiment(word);
        double vaderScore = lexicon->getVADERSentiment(word);

        // Check for negation
        if (negators.count(word)) {
            isNegated = true;
            isWord = true;
        }

        // Check for frustration and dissatisfaction
        if (frustrationTerms.count(word)) {
            isFrustration = true;
        }

        if (isNegated && !isWord) {
            afinnScore = -afinnScore * 1.5;
            vaderScore = -vaderScore * 0.5;
            if (afinnScore == 0) {
                afinnScore = -3;
            } 
            else if (vaderScore == 0) {
                vaderScore = -3;
            }
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
            afinnScore = afinnScore - 3;
            vaderScore = vaderScore - 3;
            isFrustration = false;
        }

        // Calculate total score with updated weights
        wordTotal++;
        totalScore += (afinnScore * 4) + (vaderScore * 2);

        isWord = false;
    }

    return totalScore;
}