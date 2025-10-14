// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// word counter
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    node *n = table[index];
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int sum = 0;
    while (*word)
    {
        sum += tolower(*word++);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
        return false;

    // Read each word in the file
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(source);
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        // Add each word to the hash table
        int index = hash(word);

        n->next = table[index];
        table[index] = n;

        word_count++;
    }
    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            node *temp = n;
            n = n->next;
            free(temp);
        }
        table[i] = NULL;
    }
    word_count = 0;
    return true;
}
