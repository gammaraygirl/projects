//The Coleman-Liau index of a text is designed to output that (U.S.) grade level that is needed to understand some text. The formula is
//index = 0.0588 * L - 0.296 * S - 15.8
//where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.

#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string);
int count_words(string);
int count_sentences(string);
float coleman_liau(int,int,int);
void grade_index(float);

int main(void)
{
    //Prompt user for some text
    //Check if the string is empty
    string text;
    do {
        text = get_string("Please enter the text: \n");
    } while(text[0] == '\0');

    //Compute the number of letters, sentences, and words
    int num_letters = count_letters(text);
    int num_words = count_words(text);
    int num_sentences = count_sentences(text);
    //Run the Coleman-Liau algorithm: index = 0.0588 * L - 0.296 * S - 15.8
    float index = coleman_liau(num_letters, num_words, num_sentences);
    //Print the reading level
    grade_index(index);
    //checks
    //printf("%d\n", num_letters);
    //printf("%d\n", num_words);
    //printf(%f\n, index);


}

int count_letters(string s)
{
  int a = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))
        {
            a ++;
        }
    }
    return a;
}

int count_words(string s)
{
    int b = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (((s[i]) != ' ') && (s[i+1] == ' ' || (i == n - 1))) //if character i is a space and the next one is not a space, increment b
        {
            b ++;
        }
    }
    return b;
}

int count_sentences(string s)
{
    int c = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            c++;
        }
    }
    return c;
}

//Coleman-Liau algorithm: index = 0.0588 * L - 0.296 * S - 15.8
float coleman_liau(int l, int w, int s)
{
    float index = round(0.0588 * (((float)l/(float)w)*100) - 0.296 * (((float)s/(float)w)*100) - 15.8);
    return index;
}

//Score the index
void grade_index(float g)
{
    if (g < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (g > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int)g );
    }
}
