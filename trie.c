#include "trie.h"

int TrieCreate( Trie ** trie ) {

    (*trie) = malloc( sizeof(Trie) );
    ListCreate( &((*trie)->children) );
    return 0;

}

int TrieDestroy( Trie * trie ) { 

    // Destroy tree
    
    free(trie);
    TrieHatch(trie->children);
    return 0;

}

void TrieHatch( List * list ) {
    // if ( list->length != 0 ) ListPrint(list);
    for ( int i = 0; i < list->length; i++ ) {
        TrieHatch( ListGet(list,i)->children );
    }
    ListDestroy( list );
}

int TrieInsert( Trie * trie, char * word ) {

    List * currentList = trie->children;
    // ListNode * currentNode = NULL;

    char letter;
    int length = strlen(word);

    for ( int i = 0; i < length; i++ ) {
        letter = word[i];
        if ( ListSearch(currentList,letter) == -1 ) {
            ListInsert(currentList,letter);
        }
        currentList = ListGet(currentList, ListSearch(currentList,letter))->children;
    }
    return 0;

} 

void TriePrint ( List * list ) {
    if ( list->length != 0 ) ListPrint(list);
    for ( int i = 0; i < list->length; i++ ) {
        TriePrint( ListGet(list,i)->children );
    }
}

void TrieSearchWord ( Trie * trie , char * word ) {

    List * currentList = trie->children;
    // ListNode * currentNode = NULL;

    char letter;
    int length = strlen(word);

    for ( int i = 0; i < length; i++ ) {
        letter = word[i];
        if ( ListSearch(currentList,letter) == -1 ) {
            printf("WORD NOT FOUND\n");
            return;
        }
        printf("found %c\n", letter);
        currentList = ListGet(currentList, ListSearch(currentList,letter))->children;
    }
    printf("FOUND WORD %s\n" , word );
    return ;
}

int main ( void ) {

    Trie * trie;
    TrieCreate(&trie);

    char word1[] = "world";
    char word2[] = "war";
    char word3[] = "two";
    char word4[] = "what";
    char word5[] = "whale";
    char word6[] = "three";
    char word7[] = "race";
    char word8[] = "grace";

    TrieInsert(trie,word1);
    TrieInsert(trie,word2);
    TrieInsert(trie,word3);
    TrieInsert(trie,word8);
    TrieInsert(trie,word5);
    TrieInsert(trie,word6);

    TriePrint(trie->children);

    TrieSearchWord(trie, word3);
    TrieSearchWord(trie, word4);
    TrieSearchWord(trie, word7);

    TrieDestroy(trie);
}