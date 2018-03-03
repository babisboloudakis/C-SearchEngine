// Linked list data structure
// used to store children of a node
// in a Trie date structure

typedef struct ListNode {
    struct ListNode * next;
    char data; 
} ListNode;

typedef struct List {
    int length;
    ListNode * head;
} List;

void ListCreate(List **);
void ListDestroy(List *);
int ListInsert(List *, char );
int ListSearch(List *, char );
void ListPrint(List *);
