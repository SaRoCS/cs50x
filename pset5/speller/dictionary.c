// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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
const unsigned int N = 65536;

//number of words
int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int y = strlen(word);
    char copy[y + 1];
    copy[y] = '\0';
    for (int i = 0; i < y; i++)
    {
        copy[i] = tolower(word[i]);
    }

    int x = hash(copy);
    node *temp = table[x];
    if (temp == NULL)
    {
        return false;
    }

    while (temp != NULL)
    {
        if (strcasecmp(temp -> word, copy) == 0)
        {
            return true;
        }
        temp = temp -> next;
    }
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Source of hash function: stackoverflow.com/questions/14409466/simple-hash-functions
    int hash_index = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_index = word[i] + (hash_index << 6) + (hash_index << 16) - hash_index;
    }
    return hash_index % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open dictionary
    for (int i = 0; i < N; i ++)
    {
        table[i] = NULL;
    }
    FILE *dictionary_p = fopen(dictionary, "r");
    if (dictionary_p == NULL)
    {
        return false;
    }


    char word_dict[LENGTH + 1];


    while (fscanf(dictionary_p, "%s", word_dict) != EOF)
    {
        //make new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node -> word, word_dict);
        new_node -> next = NULL;
        word_count++;

        //hash
        int index = hash(word_dict);

        //insert
        if (table[index] != NULL)
        {
            //other nodes
            new_node -> next = table[index];
        }
        table[index] = new_node;

    }
    fclose(dictionary_p);
    // TODO
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];
        if (temp != NULL)
        {
            while (table[i] != NULL)
            {
                temp = temp -> next;
                free(table[i]);
                table[i] = temp;
            }
            free(temp);
        }
    }

    return true;
}
