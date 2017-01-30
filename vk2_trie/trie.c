#include "trie.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Trie* new_trie()
{
    Trie* tr = malloc(sizeof(Trie));
    
    tr->is_word_end = false;
    for (int i = 0; i < ASCII_RANGE; ++i)
        tr->edges[i] = NULL;

    return tr;
}

void delete_trie(Trie* tr)
{
    if (tr == NULL) return;

    for (int i = 0; i < ASCII_RANGE; ++i)
        delete_trie(tr->edges[i]);

    free(tr);
}

void trie_add(Trie* tr, char* word)
{
    if (word[0] != '\n')
    {
        int idx = word[0] - ASCII_LO;

        if (tr->edges[idx] == NULL)
            tr->edges[idx] = new_trie();
        
        trie_add(tr->edges[idx], ++word);
    }
    else tr->is_word_end = true;
}

bool trie_find(Trie* tr, char* word)
{    
    if (strlen(word))
    {
        int idx = word[0] - ASCII_LO;

        if (tr->edges[idx] == NULL) 
            return false;
        
        Trie* next = tr->edges[idx];
        return trie_find(next, ++word);
    }
    
    else return tr->is_word_end;
}
