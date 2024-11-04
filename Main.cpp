#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <iomanip>
#include "SentimentAnalyzer.cpp"
#include <unordered_set>

using namespace std;

void readTestSentiments(unordered_map<int, int>& sentimenttweets, string fileName){
    ifstream file; //used to open file
    file.open(fileName);
    if (!file.is_open()) {
        cout << "Error opening file " << fileName << endl;
        return;
    }

    string line="";
    getline(file, line); //ignoring header line
    line="";
    while(getline(file, line)){
        string date;
        string query; 
        string user;

        int id;
        string text; //holds text of tweet
        int sentiment_score; //holds score recorded for the tweet

        string tempString="";
    
        stringstream inputString(line);

        //getting sentiment score
        getline(inputString, tempString, ',');
        sentiment_score = atoi(tempString.c_str()); //converting from string to int

        //getting ID
        getline(inputString, tempString);
        id = atoi(tempString.c_str()); //converting from string to int

        sentimenttweets[id] = sentiment_score;
    }
    
    file.close();
}

void readUserFile(vector<Tweet*>& tweets, string fileName){
    ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        cout << "Error opening file " << fileName << endl;
        return;
    }

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

        //getting ID
        getline(inputString, tempString, ',');
        id = atoi(tempString.c_str()); //converting from string to int

        //getting name
        getline(inputString, date, ',');
        getline(inputString, query, ',');
        getline(inputString, user, ',');
        getline(inputString, text);
        

        Tweet* tweet = new Tweet(id, date, query, user, text);
        tweets.push_back(tweet);
    }
    
    file.close();
}

int main(){
    vector<Tweet*> tweets; //holds tweets that are going to be analyzed
    unordered_map<int, int> sentimentTweets; //holds ID's and sentiment scores of test dataset

    vector<Tweet*> incorrectTweets;
    
    SentimentAnalyzer* analyzer = new SentimentAnalyzer(); //used to access analyzer functions

    readUserFile(tweets, "TestDataset.csv"); //reading files
    readTestSentiments(sentimentTweets, "TestDatasetSentiment.csv");

    double correct = 0.0; //checking number of correct tweets
    double total = tweets.size(); //number of total tweets]
    ofstream classifierResult; //prints each tweet's given sentiment and id 
    ofstream accuracy; //prints accuracy and compares ground truth and model sentiment score

    classifierResult.open("ClassifierResults.txt");
    accuracy.open("AccuracyFile.txt");

    if (!classifierResult.is_open() || !accuracy.is_open()) {
        cout << "Error opening output files" << endl;
        return 1;
    }

    for(int i=0; i<tweets.size(); i++){
        double score = analyzer->analyzeTweetSentiment(tweets.at(i));
        Tweet* testtweet;

        if(score >= 0){ //creating test tweet object
            testtweet = new Tweet(tweets.at(i)->id, tweets.at(i)->date, tweets.at(i)->query, tweets.at(i)->user, tweets.at(i)->text);
            testtweet->sentiment_score=4;
        }
        else{ //creating test tweet object
            testtweet = new Tweet(tweets.at(i)->id, tweets.at(i)->date, tweets.at(i)->query, tweets.at(i)->user, tweets.at(i)->text);
            testtweet->sentiment_score=0;
        }

        classifierResult << testtweet->sentiment_score << ", " << testtweet->id << endl; //prints model sentiment score and tweet's id

        auto it = sentimentTweets.find(tweets.at(i)->id);
        if (it != sentimentTweets.end() && it->second == testtweet->sentiment_score){ //comparing with test vector to see if correct
            correct++;
        }
        else{
            incorrectTweets.push_back(testtweet);
        } 
    }

    accuracy << fixed << setprecision(3) << (correct/tweets.size())*100 << endl; //printing accuracy into file

    for(int i=0; i<incorrectTweets.size(); i++){ //printing all incorrect tweets into file
        auto it = sentimentTweets.find(incorrectTweets.at(i)->id);
        accuracy << incorrectTweets.at(i)->sentiment_score << ", " << it->second << ", " << incorrectTweets.at(i)->id << endl;
    }

    cout << "Accuracy: " << fixed << setprecision(3) << (correct/tweets.size())*100 << "%" << endl; //printing accuracy to terminal

    accuracy.close(); //closing files
    classifierResult.close();

    for (auto& tweet : tweets) {
        delete tweet;
    }
    for (auto& incorrectTweet : incorrectTweets) {
        delete incorrectTweet;
    }
    delete analyzer;

    return 0;
}