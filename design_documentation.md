# Design Documentation
## Overview
This project is a simple sentiment analysis system written in C++ that classifies tweets as either positive or negative. It uses custom data structures and follows specific design requirements, including implementing a custom string class (DSString) instead of using C++ standard library strings.

## Classes
**SentimentAnalyzer**
- Central class performing the sentiment analysis on tweets.
- Attributes
  - `lexicon`: Pointer to `SentimentLexicon` object for accessing vocabulary.
  - `tokenizer`: Pointer to `Tokenizer` object for splitting tweet text into tokens.
- Functions
  - `analyzeTweetSentiment`: Analyzes a tweet's sentiment by tokenizing the twee, applying sentiment scores, and handling specific cases like negation or frustration terms to adjust the final score.

**Tweet**
- Represents a tweet with relevant metadata, storing both the tweet's content and sentiment data.
- Attributes
  - `date`: Holds the date of the tweet.
  - `query`: Holds the query name.
  - `user`: Holds user of the tweet.
  - `id`: Holds the ID of the tweet.
  - `text`: Holds the text of a tweet.
  - `sentiment_score`: Holds the score recorded for the tweet.
  - `sentiment_class`: Determines if the tweet is positive or negative (sentiment score).
- Functions
  - `setSentimentScore`: Updates the sentiment score.

**SentimentLexicon**
- Manages vocabulary for sentiment analysis, using predefined lexicons.
- Attributes
  - `AFINN_lexicon`: Holds AFINN vocabulary words and the sentiments, sourced from their respective lexicons.
  - `VADER_lexicon`: Holds VADER vocabulary words and the sentiments, sourced from their respective lexicons.
- Functions
  - `loadAFINN`: Loads the AFINN vocabulary text file.
  - `loadVader`: Loads teh VADER vocabulary text file.
  - `getAFINNSentiment`: Retrieves sentiment scores for vocabulary words in the AFINN file.
  - `getVADERSentiment`: Retrieves sentiment scores for vocaulary words in the VADER file.
  
**Tokenizer**
- Processes the text into tokens (words) to facilitate sentiment analysis.
- Functions
  - `tokenize`: Takes the text and delimiters, breaking the text into individual tokens (words) and returning them in a vector.

**Main**
- Acts as the driver of the program, deals with file reading, sentiment analysis, and the accuracy calculation.
- Functions
  - `readTestSentiments`: Reads test sentiment scores from a file and stores them in a map.
  - `readUserFile`: Reads tweets from a file, creating `Tweet` objects.
  - `main`: Coordinates the analysis process, initializes tweets and sentiment analyzer, processes each tweet for sentiment, compares results with test data, and calculates accuracy.
