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

int TrieInsert( Trie * trie, char * word, int d ) {

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

    ListNode * node = TrieSearchWord(trie,word);
            printf("asasas %p\n\n", node->isFinal);

    if ( node->isFinal == NULL ) {
        printf("creating...\n");
        PlCreate(&(node->isFinal));
    }
    PlInsert(node->isFinal,d);
    PlPrint(node->isFinal);
    return 0;

} 

void TriePrint ( List * list ) {
    if ( list->length != 0 ) ListPrint(list);
    for ( int i = 0; i < list->length; i++ ) {
        TriePrint( ListGet(list,i)->children );
    }
}

ListNode * TrieSearchWord ( Trie * trie , char * word ) {

    List * currentList = trie->children;

    char letter;
    int length = strlen(word);

    for ( int i = 0; i < length; i++ ) {
        letter = word[i];
        if ( ListSearch(currentList,letter) == -1 ) {
            printf("WORD NOT FOUND\n");
            return NULL;
        }
        printf("found %c\n", letter);
        if ( i == length - 1 ) break;
        printf("DONT SHOW ME\n");
        currentList = ListGet(currentList, ListSearch(currentList,letter))->children;
    }
    ListNode * node = ListGet(currentList, ListSearch(currentList,letter));
    printf("FOUND WORD %s\n" , word );
    printf("letter %p \n\n", node);
    return node;

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

    TrieInsert(trie,word1,0);
    TrieInsert(trie,word1,2);
    TrieInsert(trie,word1,0);
    TrieInsert(trie,word1,1);
    TrieInsert(trie,word1,0);
    TrieInsert(trie,word1,3);
    TrieInsert(trie,word2,0);
    TrieInsert(trie,word2,3);
    TrieInsert(trie,word2,3);
    TrieInsert(trie,word2,3);



    // TriePrint(trie->children);

    // TrieSearchWord(trie, word3);
    // TrieSearchWord(trie, word4);
    // TrieSearchWord(trie, word8);

    // TrieDestroy(trie);
}