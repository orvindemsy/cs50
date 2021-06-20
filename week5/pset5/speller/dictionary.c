// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Number of words in dictionary
int n_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hashing the word
    int idx = hash(word);

    // Traverse the linked list in table[idx]
    node *cursor = table[idx];

    while (cursor){
        // case-insensitively compare two words
        if (strcasecmp(word, cursor->word)==0){
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Will return the index of alphabet
    int idx = (int) tolower(word[0]) % 97;

    return idx;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL){
        return false;
    }

    // Initalize hash table
    for (int i=0; i < N; i++)
        table[i] = NULL;

    // Read strings from the file
    char w[LENGTH + 1];

    while(fscanf(dict, "%s", w) != EOF){

        // Create node to store each word
        node *newnode = malloc(sizeof(node));
        if (!newnode){
            return false;
        }

        // Copy word into node-word
        strcpy(newnode->word, w);
        newnode->next = NULL;

        // Hashing
        int idx = hash(newnode->word);

        // Insert node into hash table, consider if existing node exists
        if (!table[idx]){
            table[idx] = newnode;
        }
        else{
            newnode->next = table[idx];
            table[idx] = newnode;
        }

        n_words += 1;

    }

    fclose(dict);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return n_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Two helpers variables
    node *cursor = NULL;
    node *tmp    = NULL;

    // Free each allocated memory in linked list inside hash table
    for (int i=0; i < N; i++){
        cursor = table[i];

        while (cursor){
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
