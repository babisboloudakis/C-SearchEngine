// Linked list data structure
// used to store children of a node
// in a Trie date structure

typedef struct List List;

typedef struct ListNode {
    struct ListNode * next;
    char data; 
    void * isFinal;
    List * children;
} ListNode;

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
