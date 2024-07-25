// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>
#include "dictionary.h"

 // Initialize counter
static int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define N 26

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word
    unsigned int hash_result = hash(word);
    // Set up a cursor
    node *cursor;
    //Point cursor at head of list
    cursor = table[hash_result];
    while(cursor != NULL)
    {// If word I am looking for, return true
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // If not the word I am looking for, move the pointer forwards
        cursor = cursor->next;
    }
    // If pointer hits NULL, didn't find it in the list
    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return (toupper(word[0]) - 'A');
    //+(toupper(word[1] - 'A'));
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    // Check if opened correctly
    if(source != NULL)
    {
        // Create buffer
        char word[45];
        // Read each word in the dictionary
        while(fscanf(source, "%s", word) != EOF)
        {
            // Add each word to the hash table
                // Create space for each new node
                node *new_node = malloc(sizeof(node));
                if(new_node != NULL)
                {
                    // Copy the word into the node
                    strcpy(new_node-> word, word);
                    // Hash each word
                    unsigned int index = hash(word);
                    // Insert the new node into the hash table at that value
                    // Set next value of new node to current head of list
                    new_node->next = table[index];
                    // Point head of list to new node
                    table[index] = new_node;
                    //increment counter
                    word_count++;
                }
                else
                {
                    return false;
                }
        }
        fclose(source);
        return true;
        // Close the dictionary file

    }
   else
    {
        printf("This file could not be opened.\n");
        return false;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

   return(word_count);

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor;
    node *tmp;
    int i;
    for(i = 0; i < N; i++)
    {
        cursor = table[i];
        while(cursor != NULL)
        {
            // tmp and cursor point to the same thing
            tmp = cursor;
            //move the cursor forwards
            cursor = cursor->next;
            // free the node tmp is pointing to
            free(tmp);
        }
    }
    return true;
}

