#include <iostream>

using namespace std;

class Tweet{
    private:
    public:
        string date;
        string query; 
        string user;
        int id;
        string text; //holds text of tweet
        int sentiment_score; //holds score recorded for the tweet
        string sentiment_class; 
        
        Tweet(int id, string date, string query, string user, string text){
            this->date = date;
            this->query = query;
            this->id = id;
            this->text = text;
            if(sentiment_score==4){
                this->sentiment_class="Positive";
            }
            else{
                this->sentiment_class="Negative";
            }
        }

        Tweet(int id, int sentiment_score){
            this->id = id;
            this->sentiment_score=sentiment_score;
            if(sentiment_score==4){
                this->sentiment_class="Positive";
            }
            else{
                this->sentiment_class="Negative";
            }
        }

        void setTweet(string text){
            this->text=text;
        }

        void setSentimentScore(int sentiment_score){
            this->sentiment_score=sentiment_score;
        }

        int getSentimentScore(){
            return sentiment_score;
        }

        string getSentimentClass(){
            return sentiment_class;
        }

        string getText(){
            return text;
        }
};
