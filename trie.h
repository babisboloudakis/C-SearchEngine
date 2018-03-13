#include "list.h"

// typedef struct TrieNode { 
//     void * isFinal;
//     List children;
// } TrieNode;

typedef struct Trie {
    List * children;
} Trie;




// Functions on Trie
int TrieCreate(Trie **);
int TrieDestroy(Trie *);
int TrieInsert();
TrieNode * TrieSearch();
void TriePrint();