#include "trie.h"

int TrieCreate( Trie ** trie ) {

    (*trie) = malloc( sizeof(Trie) );
    ListCreate( &((*trie)->children) );
    return 0;

}

int TrieDestroy( Trie * trie ) { 

    // Destroy tree

    free(trie);

    return 0;

}

int TrieInsert( Trie * trie, char * word ) {

    List * currentList = trie->children;
    ListNode * currentNode = NULL;
    
    char letter;
    int length = strlen(word);

    for ( int i = 0; i < length; i++ ) {
        letter = word[i];
        if ( ListSearch(currentList,letter) == -1 ) {
            ListInsert(currentList,letter);
        }
        currentList = ListSearch(currentList,letter);
    }
    return 0;

}

int main ( void ) {

}