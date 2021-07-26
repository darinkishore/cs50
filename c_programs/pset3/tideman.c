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
    int winner;  //winner INDEX
    int loser;   //loser INDEX
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
void populate_pairs(void);
bool adds_cycle(int win, int lose);
bool isColumnZero(int col);
int compare_to(pair a, pair b);
void quick_sort(pair arr[], int left, int right);
int partition(pair arr[], int left, int right);
void reverse(pair arr[], int start, int end);
bool colAllZeros(int col);

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
        if (strcmp(name, candidates[i]) == 0)
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
    for (int i = 0; i < candidate_count - 1; i++) //loop thru ranks
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int pair_ind = 0;
    for (int i = 0; i < candidate_count; i++) //loop thru ranks, make sure every pref. candidate has a matchup.
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_ind].winner = i;
                pairs[pair_ind].loser = j;
                pair_ind++;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //quicksort implemented because fast and more intuitive conceptually than mergesort.
    //reversing justified b/c speed gains && bigo (log n + n) == bigo(log n)
    quick_sort(pairs, 0, pair_count - 1); //god this was such a pain in the ass
    reverse(pairs, 0, pair_count - 1);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!adds_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (colAllZeros(j))
        {
            printf("%s\n", candidates[j]);
        }
    }
}

bool colAllZeros(int col)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][col])
        {
            return false;
        }
    }
    return true;
}

/****************************************************
method: bool adds_cycle
given winning and losing candidate indices,
recursively visits matchups in locked.

Logic: Maintain a starting candidate (win), and visit
previous candidate matchups. If any of the losers
from each (recursive matchup with our og. winner) lead
back to the winner, then we have a cycle.

OUTPUT: will adding this new pair to locked add a cycle?
*****************************************************/
bool adds_cycle(int win, int lose)
{
    if (win == lose)
    {
        return true;
    }

    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[lose][j])
        {
            if (adds_cycle(win, j))
            {
                return true;
            }
        }
    }

    return false;
}

//QUICKSORT methods all below.

int compare_to(pair a, pair b)
{
    if (preferences[a.winner][a.loser] > preferences[b.winner][b.loser])
    {
        return 1;
    }
    else if (preferences[a.winner][a.loser] < preferences[b.winner][b.loser])
    {
        return -1;
    }
    else return 0;
}

void quick_sort(pair arr[], int left, int right)
{
    //printArray(arr, 5);
    if (left < right) //recursive base case. if false, left right <= left.
    {
        int pivotpos = partition(arr, left, right);
        //printf("pivot: %i\n", pivotpos);
        if (pivotpos >= 0)
        {
            quick_sort(arr, left, pivotpos - 1);
            quick_sort(arr, pivotpos + 1, right);
        }
    }
}

int partition(pair arr[], int left, int right)
{
    pair temp;
    int l = left;
    int r = right;
    int pivot = left;
    while (l < r) //ends with r >= left. ie:swap time.
    {
        while ((compare_to(arr[l],arr[pivot]) < 0 || compare_to(arr[l],arr[pivot]) == 0) && l < right)
        {   //ends with left pointer val > pivot
            l++;
        }
        while ((compare_to(arr[r],arr[pivot]) > 0 || compare_to(arr[r],arr[pivot]) == 0) && r > left)
        {   // ends w right ptr. val < pivot  (arr[r] >= arr[pivot] && r > left)
            r--;
        }
        if (l < r) //prevents swapping when pivot val achieved
        {
            temp = arr[r]; //if left ptr val < pivot & r ptr val > pivot swap
            arr[r] = arr[l];
            arr[l] = temp;
        }
    }
    temp = arr[r];
    arr[r] = arr[pivot];
    arr[pivot] = temp;
    return r;
}

void reverse(pair arr[], int start, int end)
{
    if (start >= end)
    {
        return;
    }

    pair temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;

    reverse(arr, start + 1, end - 1);
}