#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(char text[1000]);
int count_words(char text[1000]);
int count_sentences(char text[1000]);
int compute_grade_level(int letters, int words, int sentences);

int main(void)
{
    char text[1000];
    printf("Text: ");
    scanf("%[^\n]", text);

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    int gradeLevel = compute_grade_level(letters, words, sentences);
 
    if (gradeLevel < 1) {
        printf("Before Grade 1\n");
    } else if (gradeLevel > 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %i\n", gradeLevel);
    }
}

int count_letters(char text[1000])
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    return letters;
}

int count_words(char text[1000])
{
    int words = 0;
    for (int i = 0, n = strlen(text); i < n + 1; i++)
    {
        if (isspace(text[i]) || text[i] == '\0')
        {
            words++;
        }
    }

    return words;
}

int count_sentences(char text[1000])
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}

int compute_grade_level(int letters, int words, int sentences)
{
    printf("letters: %i\n", letters);
    printf("words: %i\n", words);
    printf("sentences: %i\n", sentences);
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;

    return round(0.0588 * L - 0.296 * S - 15.8);
}