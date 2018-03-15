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
    char * word;
} PostingList;

void PlCreate( PostingList **, char * );
void PlDestroy( PostingList *);
void PlInsert( PostingList * , int);
Posting * PlSearch( PostingList * , int);
int PlSum( PostingList * );
void PlPrint( PostingList * );
