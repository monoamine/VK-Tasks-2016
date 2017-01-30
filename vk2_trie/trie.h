#include <stdbool.h>

enum 
{ 
    ASCII_LO = 32, 
    ASCII_HI = 127, 
    ASCII_RANGE = ASCII_HI - ASCII_LO + 1 
};


typedef struct TrieNode Trie;

struct TrieNode
{
    Trie* edges[ASCII_RANGE];
    bool is_word_end;
};

Trie* new_trie();
void  delete_trie(Trie* tr);

void  trie_add(Trie* tr, char* word);
bool  trie_find(Trie* tr, char* word);