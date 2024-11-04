#include <iostream>

using namespace std;

class Tweet{
    public:
        string date; //holds date of tweet
        string query;  //holds query name
        string user; //holds user of tweet
        int id; //holds id of tweet
        string text; //holds text of tweet
        int sentiment_score; //holds score recorded for the tweet
        string sentiment_class;  //determines if tweet is positive or negative
        
        Tweet(int id, string date, string query, string user, string text){ //this constructor is used to create objects from the test dataset
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

        Tweet(int id, int sentiment_score){ //this constructor is used to create objects from the test dataset sentiment file
            this->id = id;
            this->sentiment_score=sentiment_score;
            if(sentiment_score==4){ //assigning class based on score
                this->sentiment_class="Positive";
            }
            else{ //assigning class based on score
                this->sentiment_class="Negative";
            }
        }

        void setSentimentScore(int sentiment_score){ //setting score for tweet
            this->sentiment_score=sentiment_score;
        }
};
