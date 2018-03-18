#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Posting node used in PostingLists
typedef struct Posting { 
    int id;
    int count;
    struct Posting * next;
} Posting;

// Posting list is a list of tupples(id,count)
// for a specific word.
typedef struct PostingList {
    int length;
    int count;
    Posting * head;
    char * word;
} PostingList;


void PlCreate( PostingList **, char * );
void PlDestroy( PostingList *);
void PlInsert( PostingList * , int);
Posting * PlSearch( PostingList * , int);
int PlSum( PostingList * );
void PlPrint( PostingList * );
Posting * PlGetPosting( PostingList * , int );
