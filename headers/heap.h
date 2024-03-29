#include <stdio.h>
#include <stdlib.h>

typedef struct Result {
    int id;
    double score;
} Result;

typedef struct Heap {
    Result * results;
    int length;
    int capacity;
} Heap;

void HeapCreate( Heap ** , int );
void HeapDestroy( Heap * );

int HeapRightChild(int );
int HeapLeftChild(int );
int HeapParent(int );

void HeapSwap(Heap *,int, int);

void HeapInsert(Heap *, int , double );
Result * HeapTop(Heap *);
void HeapPrint(Heap *);

int HeapSearch(Heap *, int );
void HeapBuild(Heap *);
void HeapHeapify(Heap *,int);