#include "../headers/list.h"

void ListCreate(List ** list) {
    // Used to properly initialize a List
    (*list) = malloc( sizeof(List) );
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

    free(list);

}

int ListInsert(List * list, char d ) {

    // Used to insert a given char to a given List
    // in ascending order
    ListNode * newNode = malloc(sizeof(ListNode));
    ListNode * currentNode = list->head;

    if ( currentNode == NULL ) {
        list->head = newNode;
        newNode->next = NULL;
    } 
    else if ( currentNode->data > d ) {
        list->head = newNode;
        newNode->next = currentNode;
    }
    else {
        ListNode * prevNode = currentNode;
        while ( 1 ) {

            if ( currentNode->next == NULL ) {
                break;
            }
            if ( currentNode->next->data > d ) {
                break;
            } else {
                currentNode = currentNode->next;
            }

        }
        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }
    newNode->data = d;
    list->length++;
    newNode->isFinal = NULL;
    ListCreate( &(newNode->children) );

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


ListNode * ListGet( List * list, int index ) {
    // Used to return a specific node of a given list
    if ( list->length == 0 ) {
        return NULL;
    }

    ListNode * currentNode = list->head;
    for ( int i = 0; i < index; i++ ) {
        currentNode = currentNode->next;
    }
    return currentNode;
}