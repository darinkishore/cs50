#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


/*
Program Name: Readability
Author: Darin Kishore
Date: Started 7/17/21

Description: Given a string of text, output a readability level
from <1 to >16th grade.

Functions :
analyze_text() : computes letter/word/sent count.
cl_index() : computes cl_index based on global vars.
main() : gets text to analyze, prints to cmdline based on cl_index output.

Global Vars : letter_count, word_count, sentence_count
*/

int letter_count = 0;
int word_count = 0; //avoids loss of precision in cl_index() .
int sentence_count = 0;

void analyze_text(string text);
int cl_index();

int main(void)
{
    string text = get_string("Text: ");
    analyze_text(text);

    int index = cl_index(); //compute coleman_liau index

    if (index < 1) //print matching output for index. takes care of edge cases with specific outputs.
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else printf("Grade %i\n", index);


}

void analyze_text(string local_text) //computes letter, words, and sentence count of string
{
    for (int i = 0, n = strlen(local_text); i < n; i++)
    {
        //Letter count
        if (isalpha(local_text[i]))
        {
            letter_count++;
        }

        //Word Count

        if (i > 0) //prevents not-findable-index errors
        {
            if (
                ((isgraph(local_text[i - 1]) || isblank(local_text[i - 1])) //sequence of chars OR space
                &&
                isgraph(local_text[i])) // followed by char
                &&
                (isblank(local_text[i + 1]) || local_text[i + 1] == '\0') //followed by space OR null.
                )
            {
                word_count++;
            }
        }

        //Sentence count
        if (local_text[i] == '!' || local_text[i] == '?' || local_text[i] == '.')
        {
            sentence_count++;
        }
    }
}


int cl_index() //computes Coleman-Liau index for global letter, sentence, word count.
{
    // avg_x : average x per 100 words.
    float avg_letters = (letter_count / (float)word_count * 100);
    float avg_sentences = (sentence_count / (float)word_count * 100);

    return round((.0588 * avg_letters - .296 * avg_sentences - 15.8));
}