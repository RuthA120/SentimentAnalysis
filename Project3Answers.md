# Assignment 2: Answers
Names: Ruth Assefa, Tiffany Nguyen

## UML Diagram
![UML Diagram](UML_Diagram.pdf)


## Answers

1. How do you train the model and how do you classify a new tweet? Give a short description of the main steps.

    > I trained my model by breaking down or tokenizing each tweet into individual words. These words are then compared to multiple vocabulary datasets that gives a sentiment score to the specific word. If the word is not found in the vocabulary dataset then it isn't given a score. I also trained it by creating a set of negator and frustration words. If the word being compared belongs to either one of the sets, then the sentiment score decreases. 

2. How long did your code take for training and what is the time complexity of your training implementation (Big-Oh notation)? Remember that training includes reading the tweets, breaking it into words, counting, ... Explain why you get this complexity (e.g., what does `N` stand for and how do your data structures/algorithms affect the complexity).

   > The time complexity of the training implementation was O(N*M). N stands for the number of tweets and M is the average number of words per tweet. I came to this conclusion because each tweet is trained individually. For example, each tweet is being tokenized invidually, and each tweet is individually searched in the sentiment vocab lookup. 

3. How long did your code take for classification and what is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

   > The time complexity for the classification implementation was O(N*M). N stands for the number of tweets and M is the average number of words per tweet. It is the same reasoning as the training implementation time complexity: each tweet is being checked individually and each word within the tweet has multiple operations applied to it.

4. What accuracy did your algorithm achieve on the provides training and test data? 

   > My overall accuracy is 72.130%.

5. What were the changes that you made that improved the accuracy the most?
   
   > One change I created was not simply just relying on the vocabulary datasets. I managed to expand my model and use negator and frustration words to improve the accuracy. I also changed how the overall sentiment score was averaged.

6. How do you know that you use proper memory management? I.e., how do you know that you do not have a memory leak?

   > I made sure my program had proper memory management by dynamically allocated the class objects in the main file and I also used a deconstructor to properly prevent memory leaks. By following these practices, my program is ensured to have effective memory management.

6. What was the most challenging part of the assignment?

   > The most challenging part of the assignment was determining how I should average the overall sentiment score. I had to decide if I should decrease the overall score by using weight adjustments or decreasing the score by a certain number of points.