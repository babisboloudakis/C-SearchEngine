#include "list.h"

// Trie data structure, used to store
// the first level of siblings
typedef struct Trie {
    List * children;
} Trie;


// Functions on Trie
int TrieCreate(Trie **);
int TrieDestroy(Trie *);
void TrieCut(List *);
int TrieTf(Trie *, char *, int);
void TrieDf(List * , char *);
int TrieInsert(Trie *, char *, int);
ListNode * TrieSearchWord(Trie *, char *);
void TriePrint(List *);