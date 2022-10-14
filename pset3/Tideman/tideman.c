#include <cs50.h>
#include <stdio.h>
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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
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
        candidates[i] = argv[i + 1];
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
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

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
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // ga bi ma
    // 0  1  2
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                preferences[i][j] += 0;
            }
            else
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (ranks[k] == i)
                    {
                        preferences[i][j] += 1;
                        k = candidate_count + 1;
                    } else if (ranks[k] == j)
                    {
                        preferences[i][j] += 0;
                        k = candidate_count + 1;
                    }
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 1; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                } else if (preferences[i][j] < preferences[j][i])
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
    int max[2];
    pair aux;
    for (int i = 0; i < pair_count - 1; i++)
    {
        int auxWin = pairs[i].winner;
        int auxLos = pairs[i].loser;
        int dif = preferences[auxWin][auxLos] - preferences[auxLos][auxWin];
        max[0] = i;
        max[1] = dif;
        for (int j = (i+1); j < pair_count; j++)
        {
            int auxWin2 = pairs[j].winner;
            int auxLos2 = pairs[j].loser;
            int dif2 = preferences[auxWin2][auxLos2] - preferences[auxLos2][auxWin2];

            if (max[1] < dif2)
            {
                max[0] = j;
                max[1] = dif2;
            }
        }

        if (max[1] > dif)
        {
            aux = pairs[max[0]];
            pairs[max[0]] = pairs[i];
            pairs[i] = aux;
        }
    }
    return;
}
// Lock pairs into the candidate graph in order, without creating cycles
bool cycled(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true && cycled(winner, i))
        {
            return true;
        }
    }

    return false;
}

void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!cycled(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int result[candidate_count];
    for (int t = 0; t < candidate_count; t++)
    {
        result[t] = 0;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                result[j] += 1;
            }
        }
    }
    for (int k = 0; k < candidate_count; k++)
    {
        if (result[k] == 0)
        {
            printf("%s\n", candidates[k]);
            k = candidate_count + 1;
        }
    }
    return;
}

