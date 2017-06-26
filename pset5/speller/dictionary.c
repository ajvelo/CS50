/*
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

typedef struct trie
{
    bool word;
    struct trie* children[27];
}trie;

trie* root;

unsigned int wordCount;

// Function that frees a node from the heap.
void freenode(trie* node)
{
    size_t n = sizeof node->children / sizeof node->children[0];
    for (size_t i = 0; i < n; i++)
    {
        if (node->children[i])
        {
            freenode(node->children[i]);
        }
    }

    free(node);
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    trie* node = root;
    
    size_t n = strlen(word);

    for (int i=0; i < n; i++)
    {
        char c = tolower((unsigned char) word[i]);

        if (c == '\'')
        {
            c = 'z' + 1;
        }

        struct trie* current = node->children[c-'a'];

        if (current == NULL)
        {
            return false;
        }
        else
        {
            node = current;
        }
    }

    return node->word;
    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* d = fopen(dictionary, "r");
    if (d == NULL)
    {
        return false;
    }

    root = calloc(1, sizeof(*root));

    trie* node = root;
    
    int c = tolower(fgetc(d));

    while (c != EOF)
    {
        if (c == '\n')
        {
            if (node != root)
            {
                wordCount++;

                node->word = true;

                node = root;                
            }
        }
        else
        {
            if (c == '\'')
            {
                c = 'z' + 1;;
            }

            struct trie* current = node->children[c-'a'];
            if (current == NULL)
            {
                node->children[c-'a'] = calloc(1, sizeof(*root));

                node = node->children[c-'a'];
            }
            else
            {
                node = current;
            }

        }
        
        c = tolower(fgetc(d));
        
    }
    
    fclose(d);

    return root;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    freenode(root);
    return true;
}