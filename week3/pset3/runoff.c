#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        printf("Voter number %i\n", i+1);
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    // Printf current voters preferences
    for (int i=0; i < voter_count; i++){
        printf("Voter %i\n", i+1);
        for (int j=0; j < candidate_count; j++){
            printf("%i-th preference: %s\n", j+1, candidates[preferences[i][j]].name);
        }
    }

    while (true)
    {
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);


        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }

    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Checking current candidate id and validity of candidate name
    bool validname = false;
    int candidate_idx;
    for (int i=0; i < candidate_count; i++){
        if (strcmp(name, candidates[i].name) == 0){
            validname = true;
            candidate_idx = i;
            break;
        }
    }

    // If candidate name is not valid return false
    if (!validname){
        return false;
    }

    // Populate the preferences array, storing candidate index into preferences[voter][th_preference]
    preferences[voter][rank] = candidate_idx;

    return true;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Count number of votes of candidate which selected as first preference
    for (int i=0; i < voter_count; i++){
        // printf("voter %d\n", i+1);
        for (int j=0; j < candidate_count; j++){
                if (!candidates[preferences[i][j]].eliminated){
                    candidates[preferences[i][j]].votes += 1;
                    break;
                }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // In order to win, votes need to top vote_thres
    int vote_thres = voter_count / 2;

    // Check if any candidate's vote is more than vote_thres
    for (int i=0; i < candidate_count; i++){
        if (candidates[i].votes > vote_thres) {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}


// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_votes = MAX_VOTERS;

    // Check for minimum votes less than min_votes
    for (int i = 0; i < candidate_count; i++){
        if (candidates[i].votes < min_votes && !candidates[i].eliminated){
            min_votes = candidates[i].votes;
        }
    }

    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Check whether each candidate's vote equal min
    for (int i = 0; i < candidate_count; i++){
        if (candidates[i].votes != min  && !candidates[i].eliminated){
            return false;
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Eliminate candidate with score same as min
    for (int i = 0; i < candidate_count; i++){
        if (candidates[i].votes == min){
            candidates[i].eliminated =  true;
        }
    }

    return;
}
