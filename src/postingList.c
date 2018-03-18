#include "../headers/postingList.h"


void PlCreate( PostingList ** postingList, char * w ) {
    // Used to create a posting list, also saves
    // the full word for use later

    (*postingList) = malloc(sizeof(PostingList));
    (*postingList)->length = 0;
    (*postingList)->count = 0;
    (*postingList)->head = NULL;
    (*postingList)->word = malloc( sizeof(char) * strlen(w) + 1);
    strcpy((*postingList)->word,w);
    
}

void PlDestroy( PostingList * postingList ) {
    // Used to destroy the posting list and
    // all its contents

    Posting * currentPosting = NULL;
    while ( postingList->length ) {
        currentPosting = postingList->head;
        postingList->head = postingList->head->next;
        postingList->length--;

        free(currentPosting);
    }

    free(postingList->word);
    free(postingList);

}

void PlInsert( PostingList * postingList, int d) {
    // Used to Insert an id in the posting list
    // if id already in, then just increase its
    // count accordingly

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
    postingList->count++;

}

Posting * PlSearch( PostingList * postingList, int d ) {
    // Searches a posting list for a specific id, returns
    // the found Posting or NULL if not found

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
    // Prints out the posting list in stdout
    // Used for debugging reassons

    if ( postingList->length == 0 ) {
        printf("List is empty...\n");
    }
    Posting * currentPosting = postingList->head;
    for ( int i = 0; i < postingList->length; i++ ) {
        printf("%5d,%d    |", currentPosting->id, currentPosting->count );
        currentPosting = currentPosting->next;
    }
    printf("\n");

}

int PlSum( PostingList * postingList ) {
    // Return the total occurances of a word in our
    // text or -1 if not found, used in /df

    if ( postingList == NULL ) {
        return -1;
    }
    return postingList->count;

}

Posting * PlGetPosting( PostingList * postingList, int index ) {
    // Returns a specific posting we specified with index

    if ( postingList->length == 0 ) {
        return NULL;
    }
    Posting * posting = postingList->head;
    for ( int i = 0; i < index; i++ ) {
        posting = posting->next;
    }
    return posting;

}