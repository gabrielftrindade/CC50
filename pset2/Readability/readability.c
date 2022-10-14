#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");

    int letters = 0;
    int words = 1;
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (toupper(text[i]) >= 'A' && toupper(text[i]) <= 'Z')
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    // printf("letters: %i\n", letters);
    // printf("words: %i\n", words);
    // printf("sentences: %i\n", sentences);

    float L = ((float) letters / (float) words) * 100.0;
    // printf("L: %f\n", L);
    float S = ((float) sentences / (float) words) * 100.0;
    // printf("S: %f\n", S);

    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    int grade = round(index);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}