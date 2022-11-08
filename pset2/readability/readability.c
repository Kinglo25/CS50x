#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int find_nb_letters(string text)
{
    int i = 0, letters = 0;

    while (text[i])
    {
        if (isalpha(text[i]))
            letters++;
        i++;
    }
    return (letters);
}

int find_nb_words(string text)
{
    int i = 0, spaces = 0, words = 0;

    while (text[i])
    {
        if (isspace(text[i]))
            spaces++;
        i++;
    }
    words = spaces + 1;
    return (words);
}

int find_nb_senteces(string text)
{
    int i = 0, sentences = 0;

    while (text[i])
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
            sentences++;
        i++;
    }
    return (sentences);
}

int main(void)
{
    float index = 0, letters = 0, words = 0, sentences = 0;
    //L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
    float l = 0, s = 0;
    string  text;

    do
    {
        text = get_string("Text: ");
    }
    while (text == 0);
    //Finds # of letters, words and sentences in the given text
    letters = find_nb_letters(text);
    words = find_nb_words(text);
    sentences = find_nb_senteces(text);
    //Finds l and s
    l = letters / words * 100;
    s = sentences / words * 100;
    index = round(0.0588 * l - 0.296 * s - 15.8);
    if (index < 1)
        printf("Before Grade 1\n");
    else if (index > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", (int)index);
    return (0);
}