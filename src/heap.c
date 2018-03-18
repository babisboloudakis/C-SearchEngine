#include "../headers/heap.h"

void HeapCreate( Heap ** heap, int size ) {

    (*heap) = malloc( sizeof(Heap) );
    (*heap)->length = 0;
    (*heap)->results = malloc( sizeof(Result) * size);
    (*heap)->capacity = size;

    for ( int i = 0; i < size; i++ ) {
        (*heap)->results[i].id = -1;
        (*heap)->results[i].score = -1; 
    }
}

void HeapDestroy( Heap * heap) {
    free(heap->results);
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
    heap->results[index2].score = temp.score;

}

void HeapInsert( Heap * heap, int d, double s ) {
    int index = 0;
    if ( ( index = HeapSearch(heap,d) ) != -1 ) {
        heap->results[index].score += s;
        } else {
        heap->results[heap->length].id = d; 
        heap->results[heap->length].score = s;
        heap->length++;
    }

}


void HeapPrint( Heap * heap ) {
    for ( int i = 0; i < heap->length; i++ ) {
        printf("   %f , %d   \n", heap->results[i].score, heap->results[i].id );
    } 
}

void HeapHeapify(Heap * heap, int index ) {
    int largest = index;
    if ( heap->results[HeapLeftChild(index)].score > heap->results[largest].score && HeapLeftChild(index) < heap->length ) {
        largest = HeapLeftChild(index);
    } 
    if ( heap->results[HeapRightChild(index)].score > heap->results[largest].score && HeapRightChild(index) < heap->length ) {
        largest = HeapRightChild(index);
    } 
    if ( largest != index ) {
        HeapSwap(heap,largest,index);
        HeapHeapify(heap, largest);
    }
}

void HeapBuild(Heap * heap) {
    for ( int i = HeapParent(heap->length -1); i >= 0; i-- ) {
        HeapHeapify(heap,i);
    }
} 

int HeapSearch(Heap * heap, int d ) {
    for ( int i = 0; i < heap->length -1; i++ ) {
        if ( heap->results[i].id == d ) {
            return i;
        }
    }
    return -1;
}

Result * HeapTop(Heap * heap ) {

    HeapBuild(heap);

    double sco = heap->results[0].score;
    int i = heap->results[0].id;

    Result * temp = malloc(sizeof(Result));
    temp->id = i;
    temp->score = sco;

    heap->results[0].id = heap->results[heap->length-1].id;
    heap->results[0].score = heap->results[heap->length-1].score;
    heap->results[heap->length-1].id = -1;
    heap->results[heap->length-1].score = -1;
    heap->length--;

    return temp;
}


// int main ( void ) {
//     Heap * heap;
//     HeapCreate(&heap,11);

//     HeapInsert(heap,0,1);
//     HeapInsert(heap,1,16);
//     HeapInsert(heap,2,5);
//     HeapInsert(heap,3,30);
//     HeapInsert(heap,4,27);
//     HeapInsert(heap,5,17);
//     HeapInsert(heap,6,20);
//     HeapInsert(heap,7,2);
//     HeapInsert(heap,8,57);
//     HeapInsert(heap,9,3);
//     HeapInsert(heap,10,90);
//     HeapInsert(heap,6,100);
//     HeapInsert(heap,0,534.21);

    
//     printf("%f\n\n", HeapTop(heap));


//     HeapDestroy(heap);
// }