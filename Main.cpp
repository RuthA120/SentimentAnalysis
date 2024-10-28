#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include "Tweet.cpp"
#include "Tokenizer.cpp"
#include "SentimentClassifier.cpp"
#include "SentimentLexicon.cpp"
#include <unordered_set>

using namespace std;

void readUserFile(vector<Tweet*>& tweets, string fileName){
    Tokenizer* tokenizer;
    ifstream file;
    file.open(fileName);

    string line="";
    getline(file, line); //ignoring header line
    line="";
    while(getline(file, line)){
        //Sentiment,id,Date,Query,User,Tweet
        string date;
        string query; 
        string user;

        int id;
        string text; //holds text of tweet
        int sentiment_score; //holds score recorded for the tweet
        string sentiment_class; 

        string tempString="";
    
        stringstream inputString(line);

        //getting sentiment score
        getline(inputString, tempString, ',');
        sentiment_score = atoi(tempString.c_str()); //converting from string to int

        //getting ID
        getline(inputString, tempString, ',');
        id = atoi(tempString.c_str()); //converting from string to int

        //getting name
        getline(inputString, date, ',');
        getline(inputString, query, ',');
        getline(inputString, user, ',');
        getline(inputString, text);

        // Tokenize the tweet text using the Tokenizer class
        const char* delimiters = " ,.!?\"';:"; //pointing to string with multiple characters/delimeters
        
        vector<string> words = tokenizer->tokenize(text, delimiters); // Tokenize tweet text

        Tweet* tweet = new Tweet(sentiment_score, id, date, query, user, text);
        tweets.push_back(tweet);

    }
    
    file.close();
}

int main(){
    vector<Tweet*> tweets;
    vector<Tweet*> testTweets;
    readUserFile(tweets, "TrainingDataset.csv");

    unordered_map<string, int> vocabAFINN = SentimentLexicon::loadAFINN("AFINNSentiment.txt");
    unordered_map<string, int> vocabVader = SentimentLexicon::loadVader("vader_lexicon.txt");
    double accuracy = 0.0;
    double correct = 0.0;
    double total = tweets.size();
    ofstream myFile;
    myFile.open("Output.txt");

    for(int i=0; i<tweets.size(); i++){
        int score = SentimentClassifier::analyzeTweetSentiment(tweets.at(i)->text, vocabAFINN, vocabVader);

        Tweet* testtweet;
        if(score >= 0){
            testtweet = new Tweet(4, tweets.at(i)->id, tweets.at(i)->date, tweets.at(i)->query, tweets.at(i)->user, tweets.at(i)->text);
        }
        else{
            testtweet = new Tweet(0, tweets.at(i)->id, tweets.at(i)->date, tweets.at(i)->query, tweets.at(i)->user, tweets.at(i)->text);
        }

        if(tweets.at(i)->sentiment_score == testtweet->sentiment_score){
            correct++;
        }
        else{

            myFile << "Incorrect: " << tweets.at(i)->text << ", " << testtweet->sentiment_score << "\n";
        }

    }

    myFile.close();
    cout << "Accuracy: " << correct/total << endl;



    return 0;
}