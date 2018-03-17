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
int TrieTf(Trie *, char *, int);
void TrieDf(List * , char *);
int TrieInsert(Trie *, char *, int);
ListNode * TrieSearchWord(Trie *, char *);
void TriePrint(List *);