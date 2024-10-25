#include <iostream>

using namespace std;

class Tweet{
    private:
        string text; //holds text of tweet
        int sentiment_score; //holds score recorded for the tweet
        string sentiment_class; 
    public:
        void setText(string text){
            this->text=text;
        }
        void setSentimentScore(int sentiment_score){
            this->sentiment_score=sentiment_score;
        }
        int getSentimentScore(){
            return sentiment_score;
        }
        void setSentimentClass(string sentiment_class){
            this->sentiment_class=sentiment_class;
        }
        string getText(){
            return text;
        }
};
