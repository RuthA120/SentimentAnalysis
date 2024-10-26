#include <iostream>
#include <sstream>
#include <fstream>
#include "Tweet.cpp"

using namespace std;

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

        Tweet* tweet = new Tweet(sentiment_score, id, date, query, user, text);
        tweets.push_back(tweet);
    }
    
    file.close();
}

int main(){
    vector<Tweet*> tweets;
    readUserFile(tweets, "TrainingDataset.csv");



    return 0;
}