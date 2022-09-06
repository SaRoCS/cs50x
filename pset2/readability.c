#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
//prototype functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //get the text
    string text = get_string("Text: ");
    //count the letters words and sentences
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

    //calculat the average per 100
    float l = 100 / words * letters;
    float s = 100 / words * sentences;
    //find the index
    int index = round(0.0588 * l - 0.296 * s - 15.8);
    //determine and print the grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //go through each char and see if it is a letter
        bool x = isalpha(text[i]);
        //if it is a letter count it
        if (x == true)
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    //words is equal to spaces plus one
    int words = 1;
    //fgo through each char and see if it is a space
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        bool x = isspace(text[i]);
        //if it is count it
        if (x == true)
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    //go through and see if each char is a . ! ?
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //if it is count it
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}

