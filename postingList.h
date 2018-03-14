#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Posting {
    int id;
    int count;
    struct Posting * next;
} Posting;


typedef struct PostingList {
    int length;
    Posting * head;
} PostingList;

void PlCreate( PostingList ** );
void PlDestroy( PostingList *);
void PlInsert( PostingList * , int);
Posting * PlSearch( PostingList * , int);
void PlPrint( PostingList * );
