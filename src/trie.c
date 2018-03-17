#include "../headers/trie.h"

int TrieCreate( Trie ** trie ) {

    (*trie) = malloc( sizeof(Trie) );
    ListCreate( &((*trie)->children) );
    return 0;

}

int TrieDestroy( Trie * trie ) { 

    // Destroy tree
    
    TrieHatch(trie->children);
    free(trie);
    return 0;

}

void TrieHatch( List * list ) {
    // if ( list->length != 0 ) ListPrint(list);
    ListNode * node;
    for ( int i = 0; i < list->length; i++ ) {
        node = ListGet(list,i);
        if ( node->isFinal != NULL ) {
            PlDestroy(node->isFinal);
        }
        TrieHatch( node->children );
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

    if ( node->isFinal == NULL ) {
        PlCreate(&(node->isFinal), word);
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
            return NULL;
        }
        if ( i == length - 1 ) break;
        currentList = ListGet(currentList, ListSearch(currentList,letter))->children;
    }
    ListNode * node = ListGet(currentList, ListSearch(currentList,letter));
    return node;

}

int TrieTf(Trie * trie, char * word, int id ) {

    ListNode * node = TrieSearchWord(trie,word);
    Posting * posting = PlSearch(node->isFinal, id);
    if ( posting == NULL ) return -1;
    return posting->count;

}

void TrieDf( List * list, char * filter ) {
    ListNode * listNode;
    for ( int i = 0; i < list->length; i++ ) {
        
        listNode = ListGet(list,i);
        if ( listNode->isFinal != NULL ) {
            if ( filter == NULL ) {
                printf("%s %d\n", listNode->isFinal->word, PlSum(listNode->isFinal));
            } else {
                if ( strcmp(filter,listNode->isFinal->word) == 0 ) {
                    printf("%s %d\n", listNode->isFinal->word, PlSum(listNode->isFinal));
                }
            }
        }
        TrieDf(listNode->children,filter);
    }
} 


// int main ( void ) {

//     Trie * trie;
//     TrieCreate(&trie);

//     char word1[] = "world";
//     char word2[] = "argh";
//     char word3[] = "two";
//     char word4[] = "what";
//     char word5[] = "whale";
//     char word6[] = "three";
//     char word7[] = "race";
//     char word8[] = "grace";

//     TrieInsert(trie,word1,0);
//     TrieInsert(trie,word1,2);
//     TrieInsert(trie,word1,0);
//     TrieInsert(trie,word1,1);
//     TrieInsert(trie,word1,0);
//     TrieInsert(trie,word1,3);
//     TrieInsert(trie,word2,0);
//     TrieInsert(trie,word2,3);
//     TrieInsert(trie,word2,3);
//     TrieInsert(trie,word2,3);
//     TrieInsert(trie,word3,1);
//     TrieInsert(trie,word3,2);
//     TrieInsert(trie,word4,1);
//     TrieInsert(trie,word4,1);
//     TrieInsert(trie,word8,0);

//     char buffer[50];
//     TrieDf(trie->children);
//     // printf("%d %s %d\n", 0, word1, TrieTf(trie,word1,0));
//     // printf("%d %s %d\n", 0, word2, TrieTf(trie,word2,0));
//     // printf("%d %s %d\n", 3, word2, TrieTf(trie,word2,3));

//     // TriePrint(trie->children);

//     // TrieSearchWord(trie, word3);
//     // TrieSearchWord(trie, word4);
//     // TrieSearchWord(trie, word8);

//     // TrieDestroy(trie);
// }