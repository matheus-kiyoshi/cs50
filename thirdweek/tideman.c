#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

typedef struct
{
    char name[20];
} candidate;

// Array of candidates
candidate candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char name[], int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool has_cycle(int winner, int loser);
void lock_pairs(void);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name, argv[i + 1]);
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count;
    printf("Number of voters: ");
    int ret;
    printf("Height: ");
    do {
       ret = scanf("%i", &voter_count);
      if (ret != 1 || voter_count < 0) {
          while (getchar() != '\n');
          printf("Invalid input. Please enter a positive number of voters:  ");
      }
    } 
    while (ret != 1 || voter_count < 0);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[20];
            printf("Rank %i: ", j + 1);
            scanf("%s", name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, char name[], int ranks[])
{
    if (rank < candidate_count)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (strcmp(candidates[i].name, name) == 0)
            {
                ranks[rank] = i;
                return true;
            }
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i != j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else 
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int max = 0;
    int max_index = 0;
    pair temp;
    for (int i = 0; i < pair_count; i++)
    {
        // find actual max
        max = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        max_index = i;
        for (int j = i; j < pair_count; j++)
        {
            // compare if next is bigger than actual max
            if (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner] > max)
            {
                // if yes, next number is the new max
                max = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
                max_index = j;
            }
        }
        temp = pairs[i];
        pairs[i] = pairs[max_index];
        pairs[max_index] = temp;
    }
    return;
}

bool has_cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)
        {
            return has_cycle(winner, i);
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int winner;
    int loser;
    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;
        if (!has_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner;
    int loser;
    bool is_winner;
    for (int i = 0; i < candidate_count; i++)
    {
        winner = i;
        is_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            loser = j;
            if (locked[loser][winner] == true)
            {
                is_winner = false;
            }
        }
        if (is_winner == true)
        {
            printf("%s\n", candidates[winner].name);
        }
    }
    return;
}
