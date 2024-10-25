#include <iostream>

using namespace std;

class Tweet{
    private:
        //string text; //holds text of tweet
        int sentiment_score; //holds score recorded for the tweet
       // string sentiment_class; 
    public:
        void setSentimentScore(int sentiment_score){
            this->sentiment_score=sentiment_score;
        }
        int getSentimentScore(){
            return sentiment_score;
        }
};
