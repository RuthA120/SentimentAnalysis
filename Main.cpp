#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include "SentimentAnalyzer.cpp"
#include <unordered_set>

using namespace std;

void readTestSentiments(unordered_map<int, int>& sentimenttweets, string fileName){
    ifstream file;
    file.open(fileName);

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
    vector<Tweet*> tweets;
    unordered_map<int, int> sentimentTweets;
    SentimentAnalyzer analyzer;
    readUserFile(tweets, "TestDataset.csv");
    readTestSentiments(sentimentTweets, "TestDatasetSentiment.csv");

    double correct = 0.0;
    double total = tweets.size();
    ofstream myFile;
    myFile.open("Output.txt");

    for(int i=0; i<tweets.size(); i++){
        double score = analyzer.analyzeTweetSentiment(tweets.at(i));
        Tweet* testtweet;

        if(score >= 0){ //creating test tweet object
            testtweet = new Tweet(tweets.at(i)->id, tweets.at(i)->date, tweets.at(i)->query, tweets.at(i)->user, tweets.at(i)->text);
            testtweet->sentiment_score=4;
        }
        else{ //creating test tweet object
            testtweet = new Tweet(tweets.at(i)->id, tweets.at(i)->date, tweets.at(i)->query, tweets.at(i)->user, tweets.at(i)->text);
            testtweet->sentiment_score=0;
        }

        auto it = sentimentTweets.find(tweets.at(i)->id);
        if (it != sentimentTweets.end() && it->second == testtweet->sentiment_score){
            correct++;
        } 
        else { // output to file if incorrect
            myFile << "Incorrect: " << tweets.at(i)->text << ", " << testtweet->sentiment_score << "\n";
        }

    }

    myFile.close();

    cout << "Accuracy: " << (correct/tweets.size())*100 << "%" << endl;

    return 0;
}