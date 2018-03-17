#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WordNode {
    struct WordNode * next;
    char * word;
} WordNode;

typedef struct WordList {
    int length;
    WordNode * head;
} WordList;

void WordListCreate(WordList **);
void WordListDestroy(WordList *);
int WordListSearch(WordList *, char *);
int WordListInsert(WordList *, char *);
void WordListPrint(WordList *);
char * WordListGetWord(WordList *, int);