#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 9

typedef struct
{
    char name[20];
    int votes;
} candidate;

candidate candidates[MAX];

int candidate_count;

bool vote(char name[20]);
void print_winner(void);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
    }

    printf("Number of voters: ");
    int voter_count;
    int ret;
    do {
       ret = scanf("%i", &voter_count);
      if (ret != 1 || voter_count < 1) {
          while (getchar() != '\n');
          printf("Invalid input. Please enter a positive integer:  ");
      }
    } 
    while (ret != 1 || voter_count < 1);

    for (int i = 0; i < voter_count; i++)
    {
        char name[20];
        printf("\nVote: ");
        scanf("%s", name);

        if (!vote(name))
        {
            printf("Invalid vote.");
        }
    }

    print_winner();
}

bool vote(char name[20])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

void print_winner(void)
{
    int max = 0;
    char winner[20];
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max)
        {
            strcpy(winner, candidates[i].name);
            max = candidates[i].votes;
        }
        if (candidates[i].votes == max && strcmp(candidates[i].name, winner) != 0)
        {
            strcat(winner, " and ");
            strcat(winner, candidates[i].name);
        }
    }
 
    printf("\nWinner: %s\n", winner);
}