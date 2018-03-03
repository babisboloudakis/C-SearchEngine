#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void ListCreate(List ** list) {
    // Used to properly initialize a List

    (*list)->length = 0;
    (*list)->head = NULL;

}


void ListDestroy(List * list) {
    // Used to properly free every node of a given List

    ListNode * currentNode = NULL;
    while ( list->length ) {

        currentNode = list->head;
        list->head = list->head->next;
        list->length--;

        free(currentNode);

    }
}


int ListInsert(List * list, char d ) {
    // Used to insert a given char to a given List

    ListNode * newNode = malloc(sizeof(ListNode));
    newNode->next = list->head;
    newNode->data = d;
    list->head = newNode;
    list->length++;

    return 0;

}


int ListSearch(List * list, char d ) {
    // Used to find if a given character exists in a given list
    // returns -1 if character wasn't found

    if ( list->length == 0 ) {
        return -1;
    }

    ListNode * currentNode = list->head;
    for ( int i = 0; i < list->length; i++ ) {
        if ( currentNode->data == d ) {
            return i;
        }
        currentNode = currentNode->next;
    }
    return -1;
}


void ListPrint(List * list) {
    // Used to graphically show a given List on stdout
    // for debugging reassons
    
    if ( list->length == 0 ) {
        printf("List is empty...\n");
    }
    printf(" +----------- Our list is -----------+ \n");
    ListNode * currentNode = list->head;
    for ( int i = 0; i < list->length; i++ ) {
        printf("%5c    |", currentNode->data );
        currentNode = currentNode->next;
    }
    printf("\n");
}

int main ( void ) {

    List * list;
    ListCreate(&list);

    ListInsert(list,'t');
    ListInsert(list,'r');
    ListInsert(list,'e');
    ListInsert(list,'v');
    ListInsert(list,'d');
    ListInsert(list,'a');

    printf("Searching for \'r\'....\n");
    sleep(1);
    printf("Found in position %d\n", ListSearch(list,'r'));

    printf("Searching for \'w\'....\n");
    sleep(1);
    printf("Found in position %d\n", ListSearch(list,'w'));


    ListPrint(list);

    ListDestroy(list);


}