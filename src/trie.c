#include "../headers/trie.h"

extern int K;
extern int loops;

int TrieCreate( Trie ** trie ) {
    // Used to create and initialize a trie

    (*trie) = malloc( sizeof(Trie) );
    ListCreate( &((*trie)->children) );
    return 0;

}

int TrieDestroy( Trie * trie ) { 
    // Destroy tree and ALL its contents
    // contents are freed recursively using
    // trieCut
    
    TrieCut(trie->children);
    free(trie);
    return 0;

}

void TrieCut( List * list ) {
    // Used in TrieDestroy, this function frees
    // a list in the tree as well as it contents
    // but before that makes a recursive call
    // on its children

    ListNode * node;
    for ( int i = 0; i < list->length; i++ ) {
        node = ListGet(list,i);
        if ( node->isFinal != NULL ) {
            PlDestroy(node->isFinal);
        }
        TrieCut( node->children );
    }
    ListDestroy( list );
}

int TrieInsert( Trie * trie, char * word, int d ) {
    // Inserts a word in the trie, if the word already
    // exists then it simply increase the counter accordingly
    // on the right PostingList, else it also creates a Posting
    // least which it connects on the leaf node

    List * currentList = trie->children;

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
    return 0;

} 

void TriePrint ( List * list ) {
    // Used for debugging reassons
    // WARNING: ugly output format

    if ( list->length != 0 ) ListPrint(list);
    for ( int i = 0; i < list->length; i++ ) {
        TriePrint( ListGet(list,i)->children );
    }
}


ListNode * TrieSearchWord ( Trie * trie , char * word ) {
    // Used to search the trie for a given word, returns
    // NULL if word not found, if found it returns the leaf
    // node that also contains the pointer to the postingList

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
    // Used in /tf command, just returns the count
    // of a specific word in a specific id

    ListNode * node = TrieSearchWord(trie,word);
    Posting * posting = PlSearch(node->isFinal, id);
    if ( posting == NULL ) return -1;
    return posting->count;

}

void TrieDf( List * list, char * filter ) {
    // Used in the /df command, does the printing
    // itself, also has parameter filter which ignored
    // if NULL, else prints only the given word.
    ListNode * listNode;
    for ( int i = 0; i < list->length; i++ ) {
        
        listNode = ListGet(list,i);
        if ( listNode->isFinal != NULL ) {
            if ( filter == NULL ) {
                if ( ++loops > K ) {
                 break;   
                }
                printf("%s %d\n", listNode->isFinal->word, listNode->isFinal->length);
                
            } else {
                if ( strcmp(filter,listNode->isFinal->word) == 0 ) {
                    printf("%s %d\n", listNode->isFinal->word, listNode->isFinal->length);
                }
            }
        }
        TrieDf(listNode->children,filter);
    }
} 