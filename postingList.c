#include "postingList.h"



void PlCreate( PostingList ** postingList ) {

    (*postingList) = malloc(sizeof(PostingList));
    (*postingList)->length = 0;
    (*postingList)->head = NULL;
}

void PlDestroy( PostingList * postingList ) {

    Posting * currentPosting = NULL;
    while ( postingList->length ) {
        currentPosting = postingList->head;
        postingList->head = postingList->head->next;
        postingList->length--;

        free(currentPosting);
    }

    free(postingList);

}

void PlInsert( PostingList * postingList, int d) {

    Posting * posting;
    if ( (posting = PlSearch(postingList,d) ) != NULL ) {
        posting->count++;
    } else {

        posting = malloc(sizeof(Posting));
        posting->id = d;
        posting->count = 1;
        if ( postingList->length == 0 ) {
            postingList->head = posting;
        } else {
            posting->next = postingList->head;
            postingList->head = posting;
        }
        postingList->length++;
    }

}

Posting * PlSearch( PostingList * postingList, int d ) {
    if ( postingList->length == 0 ) {
        return NULL;
    }

    Posting * currentPosting = postingList->head;
    for ( int i = 0; i < postingList->length; i++ ) {
        if ( currentPosting->id == d ) {
            return currentPosting;
        }
        currentPosting = currentPosting->next;
    }
    return NULL;
}

void PlPrint( PostingList * postingList ) {

    if ( postingList->length == 0 ) {
        printf("List is empty...\n");
    }
    printf(" +----------- Our Posting list is -----------+ \n");
    Posting * currentPosting = postingList->head;
    for ( int i = 0; i < postingList->length; i++ ) {
        printf("%5d,%d    |", currentPosting->id, currentPosting->count );
        currentPosting = currentPosting->next;
    }
    printf("\n");

}


// int main ( void ) { 

//     PostingList * postingList;

//     PlCreate(&postingList);

//     PlInsert(postingList, 0);
//     PlInsert(postingList, 0);
//     PlInsert(postingList, 1);
//     PlInsert(postingList, 2);
//     PlInsert(postingList, 2);
//     PlInsert(postingList, 2);
//     PlInsert(postingList, 2);
//     PlInsert(postingList, 3);
//     PlInsert(postingList, 5);
//     PlInsert(postingList, 20);
//     PlInsert(postingList, 20);
//     PlInsert(postingList, 20);

//     PlPrint(postingList);


//     PlDestroy(postingList);



// }