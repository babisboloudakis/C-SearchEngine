#include "./postingList.h"

typedef struct List List;

// List node contains data (char), a posting list pointer
// as well as its children
typedef struct ListNode { 
    struct ListNode * next;
    char data; 
    PostingList * isFinal;
    List * children;
} ListNode;

// Linked list in ascending order used in trie to connect
// sibling nodes
struct List { 
    int length;
    ListNode * head;
};

void ListCreate(List **);
void ListDestroy(List *);
int ListInsert(List *, char );
int ListSearch(List *, char );
void ListPrint(List *);
ListNode * ListGet(List *, int);
 