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
void TrieHatch(List *);

int TrieInsert(Trie *, char *);
void TrieSearchWord(Trie *, char *);
void TriePrint(List *);