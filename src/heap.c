#include "../headers/heap.h"

void HeapCreate( Heap ** heap, int size ) {

    (*heap) = malloc( sizeof(Heap) );
    (*heap)->length = 0;
    (*heap)->results = malloc( sizeof(Result) * size);
    (*heap)->capacity = size;

    for ( int i = 0; i < size; i++ ) {
        (*heap)->results[i].id = 0;
        (*heap)->results[i].score = -1; 
    }
}

void HeapDestroy( Heap * heap) {
    free(heap);
}

int HeapRightChild( int index ) {
    return 2 * index + 2;
}

int HeapLeftChild( int index ) {
    return 2 * index + 1;
}

int HeapParent( int index ) {
    return ( index % 2 == 0 ) ? index / 2 - 1 : index / 2;
}

void HeapSwap( Heap * heap, int index1 , int index2 ) {

    Result temp;

    temp.id = heap->results[index1].id;
    temp.score = heap->results[index1].score;
    heap->results[index1].id = heap->results[index2].id;
    heap->results[index1].score = heap->results[index2].score;
    heap->results[index2].id = temp.id;
    heap->results[index2].id = temp.score;

}

void HeapInsert( Heap * heap, int d, double s ) {
    printf("Inserting %d %f \n", d, s);
    heap->results[heap->length].id = 2; 
    heap->results[heap->length].score = 2;
    heap->length++;
    printf("%d %f \n\n", heap->results[0].id, heap->results[0].score);
    HeapBubbleUp(heap);
    printf("%d %f \n\n", heap->results[0].id, heap->results[0].score);

}

double HeapTop(Heap * heap ) {


}

void HeapPrint( Heap * heap ) {
    for ( int i = 0; i < heap->length; i++ ) {
        printf("   %f , %d   \n", heap->results[i].score, heap->results[i].id );
    } 
}

void HeapBubbleUp(Heap * heap) {

    int newDoc = heap->length-1;
    int parent = HeapParent(newDoc);
    
    while ( heap->results[newDoc].score > heap->results[parent].score ) {

        HeapSwap(heap,newDoc,parent);
        newDoc = parent;
        parent = HeapParent(newDoc);

    }

}

void HeapBubbleDown(Heap * heap) {

}

int main ( void ) {
    Heap * heap;
    HeapCreate(&heap,6);

    HeapInsert(heap,5,3.23);
    // HeapInsert(heap,1,9.78);
    // HeapInsert(heap,2,1.00);
    // HeapInsert(heap,3,3.14);
    // HeapInsert(heap,4,6.12);
    // HeapInsert(heap,5,2.2);

    HeapPrint(heap);

    HeapDestroy(heap);
}