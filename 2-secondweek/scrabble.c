#include <stdio.h>
#include <string.h>
#include <ctype.h>

int score(char word[50]);

int main(void) 
{
    char firstWord[50];
    char secondWord[50];

    printf("Player 1: ");
    scanf("%s", firstWord);

    printf("Player 2: ");
    scanf("%s", secondWord);

    int firstScore = score(firstWord);
    int secondScore = score(secondWord);

    if (firstScore > secondScore) {
        printf("Player 1 wins!\n");
    } else if (firstScore < secondScore) {
        printf("Player 2 wins!\n");
    } else {
        printf("Tie!\n");
    }

    return 0;
}

int score(char word[50]) {
    int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int score = 0;

    for (int i = 0, n = strlen(word); i < n; i++) {
        if (isalpha(word[i])) {
            score += points[toupper(word[i]) - 'A'];
        }
    }

    return score;
}