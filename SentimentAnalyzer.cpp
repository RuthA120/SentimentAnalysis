#include <iostream>
#include <algorithm>
#include "SentimentLexicon.cpp"
#include "Tweet.cpp"
#include "Tokenizer.cpp"
#include <cctype>
using namespace std;

class SentimentAnalyzer{ //this class will be used to execute all functions needed to detect accuracy
    private:
        SentimentLexicon* lexicon; //used to access functions from lexicon class
        Tokenizer* tokenizer; //used to access function from tokenizer class
    public:
        double analyzeTweetSentiment(Tweet* tweet); //determining if tweet negative or not

        SentimentAnalyzer(){ //when object is created --> load vocab words
            lexicon = new SentimentLexicon();
            tokenizer = new Tokenizer();
            lexicon->loadAFINN();
            lexicon->loadVader();
        }
};


double SentimentAnalyzer::analyzeTweetSentiment(Tweet* tweet){
    const char* delimiters = " ,.!?\"';:-/*";
    vector<string> tokens = tokenizer->tokenize(tweet->text, delimiters);

    int totalScore = 0; //this int holds the total sentiment score for a tweet
    bool isNegated = false; //bool for if the word is negator word or not
    bool isFrustration = false; //bool for if the word is a frustration term or not
    bool isWord = false; //bool for if the word prior is a negator word

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

    unordered_set<string> frustrationTerms; //frustration terms
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

    for (size_t i = 0; i < tokens.size(); i++){ //looping through all of the tokens
        string word = tokens[i]; //getting word from vector
        transform(word.begin(), word.end(), word.begin(), ::tolower); //lowering all letters in word so then it can properly be matched to vocab lists

        double afinnScore = lexicon->getAFINNSentiment(word); //getting sentiment score for word in AFINN list
        double vaderScore = lexicon->getVADERSentiment(word); //getting sentiment score for word in VADER list

        if (negators.count(word)){ //checking to see is a negator word
            isNegated = true; //if it is mark as true
            isWord = true;
        }

        if (frustrationTerms.count(word)){ //checking to see is a frustration word
            isFrustration = true;
        }

        if (isNegated && !isWord){ //if prior word was a negator term --> execute
            afinnScore = afinnScore * -1.5; //decrease score by times -1.5
            vaderScore = vaderScore * -0.5; //decrease score by times -0.5
            if(afinnScore == 0){ //if current afinn score is zero --> -3
                afinnScore = -3;
            } 
            else if(vaderScore == 0){ //if current vader score is zero --> -3
                vaderScore = -3;
            }
            isNegated = false;
        }

        if (afinnScore < 0 && word.size() >= 7){ //if current afinnscore is less than 1 and the word size is greater than 7 letters
            afinnScore -= word.size() / 2.0; //subtract afinnscore by word size divided by 2 
        }
        if (vaderScore < 0 && word.size() >= 7){ //if current vaderscore is less than 1 and the word size is greater than 7 letters
            vaderScore -= word.size() / 2.0; //subtract vaderscore by word size divided by 2 
        }

        if(isFrustration){ //if word is a frustration term
            afinnScore = afinnScore - 3; //if true --> decrease scores by -3
            vaderScore = vaderScore - 3;
            isFrustration = false;
        }

        totalScore += (afinnScore * 4) + (vaderScore * 2); //calculate vocab scores with weights and add to total score

        isWord = false; //change bool to false
    }

    return totalScore;
}