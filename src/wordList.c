#include "../headers/wordList.h"

void WordListCreate(WordList ** wordList ) {

    (*wordList) = malloc( sizeof(WordList) );
    (*wordList)->length = 0;
    (*wordList)->head = NULL;

}

void WordListDestroy(WordList * wordList ) {


    WordNode * node = NULL;
    while ( wordList->length ) {

        node = wordList->head;
        wordList->head = wordList->head->next;
        wordList->length--;

        free(node);

    }

    free(wordList);

}

int WordListSearch(WordList * wordList , char * word ) {

    if ( wordList->length == 0 ) {
        return -1;
    }

    WordNode * currentNode = wordList->head;
    for ( int i = 0; i < wordList->length; i++ ) {
        if ( strcmp(currentNode->word,word) == 0 ) {
            return i;
        }
        currentNode = currentNode->next;
    }
    return -1;

}

int WordListInsert( WordList * wordList, char * w) {

    WordNode * wordNode;
    wordNode = malloc(sizeof(WordNode));
    wordNode->word = w;
    if ( wordList->length == 0 ) {
        wordList->head = wordNode;
    } else {
        wordNode->next = wordList->head;
        wordList->head = wordNode;
    }
    wordList->length++;
    return 0;

}

void WordListPrint( WordList * wordList ) {

    if ( wordList->length == 0 ) {
        printf("List is empty...\n");
    }
    printf(" +----------- Our list is -----------+ \n");
    WordNode * currentNode = wordList->head;
    for ( int i = 0; i < wordList->length; i++ ) {
        printf("%s    |", currentNode->word );
        currentNode = currentNode->next;
    }
    printf("\n");

}

char * WordListGetWord( WordList * wordList, int index ) {

    if ( wordList->length == 0 ) {
        return NULL;
    }

    WordNode * node = wordList->head;
    for ( int i = 0; i < index; i++ ) {
        node = node->next;
    }
    return node->word;

}


// int main ( void ) {

//     WordList * wordList;
//     WordListCreate(&wordList);

//     char word1[] = "Hello";
//     char word2[] = "Fox";
//     char word3[] = "Lazy";
//     char word4[] = "Cpp";
//     char word5[] = "search";
//     char word6[] = "/df";

//     WordListInsert(wordList,word1);
//     WordListInsert(wordList,word2);
//     WordListInsert(wordList,word3);
//     WordListInsert(wordList,word6);
//     WordListInsert(wordList,word5);

//     printf("Searching for word \"%s\"...\n", word2);
//     if ( WordListSearch(wordList,word2) != -1 ) {
//         printf("Word found!\n");
//     } else {
//         printf("Word not found\n");
//     }
//     printf("Searching for word \"%s\"...\n", word5);
//     if ( WordListSearch(wordList,word5) != -1 ) {
//         printf("Word found!\n");
//     } else {
//         printf("Word not found\n");
//     }


//     WordListPrint(wordList);

//     WordListDestroy(wordList);

// }