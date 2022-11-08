// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1523;

// Hash table
node *table[N];

//Size variable
size_t dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int h = hash(word);
    node *head = table[h];

    while (head)
    {
        if (strcasecmp(head->word, word) == 0)
            return true;
        head = head->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // idea from https://skobki.com/en/c-language-dictionary-spell-checker/
    unsigned int h = 0;
    size_t i = 0;

    while(word[i])
    {
        if (isalpha(word[i]))
            h += toupper(word[i]) - 'A';
        i++;
    }
    h *= strlen(word);

    return (h %= N);
}

node *create_node(char *word)
{
    node *new;

    new = malloc(sizeof(node));
    if (new == NULL)
    {
        unload();
        return (NULL);
    }
    strcpy(new->word, word);
    new->next = NULL;

    return (new);
}

void add_node(node *new)
{
    new->next = table[hash(new->word)];
    table[hash(new->word)] = new;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    node *new;
    char word[LENGTH + 1];

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
        return false;

    while(fscanf(dict, "%s", word) != EOF)
    {
        new = create_node(word);
        if (new == NULL)
            return false;
        add_node(new);
        dictionary_size++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return (dictionary_size);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *head;

    for(int i = 0; i < N; i++)
    {
        head = table[i];
        while(head)
        {
            node *tmp = head->next;
            free(head);
            head = tmp;
        }
    }
    return true;
}
