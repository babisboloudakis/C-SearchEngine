#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/trie.h"
#include "../headers/wordList.h"
#include "../headers/heap.h"

#define DELIMS " \n\t"
#define BUFFERSIZE 50000
#define SCOREB 0.75
#define SCOREK 1.2

char ** textMap;
int * documentWordCount;
Trie * trie;
Heap * heap;
int maxLines = 0;
int averageWords = 0;

double CalculateScore(WordList * wordList) {

	double documentScore = 0;
	double numerator = 0;
	double idf = 0;
	double denominator = 0;
	for ( int i = 0; i < wordList->length; i++ ) {

		ListNode * listNode = TrieSearchWord(trie,WordListGetWord(wordList,i));
		if ( listNode == NULL ) continue;
		int f = 0;
		Posting * posting = NULL;
		for ( int j = 0; j < listNode->isFinal->length; j++ ) {
			posting = PlGetPosting(listNode->isFinal,j);
			f = posting->count;
			idf = log10(	(maxLines - listNode->isFinal->length + 0.5) / (listNode->isFinal->length + 0.5)	);
			numerator = f * (SCOREK + 1) * idf;
			denominator = f + SCOREK * ( 1 - SCOREB + SCOREB * documentWordCount[posting->id] / averageWords);
			documentScore = numerator/denominator;
			HeapInsert(heap,posting->id, documentScore);
		}
		

	}

	return documentScore;

}

void searchQuery(WordList * wordList ) {

	// int documentsInQuery = 0;
	// for ( int i = 0; i < wordList->length; i++) {
	// 	ListNode * listNode = TrieSearchWord(trie,WordListGetWord(wordList,i));
	// 	if ( listNode == NULL ) continue;
	// 	documentsInQuery += listNode->isFinal->count;
	// }
	HeapCreate(&heap,maxLines);

	//Calculate score
	double score = CalculateScore(wordList);

	Result * result;
	char * underline;
	int strSize = 0;
	char buffer[BUFFERSIZE];
	char * temp, * temp2;
	while( ( result = HeapTop(heap) ) != NULL ) {
		// Get top result and find every word in it

		// Create a clone of the top document
		temp = textMap[result->id];
		underline = malloc( sizeof(char) * ( strlen(temp) + 1 ) );
		strcpy(underline,temp);

		// Replace every word from arguments found in document clone
		// with ^
		for ( int arg = 0; arg < wordList->length; arg++ ) {
			while ( ( temp2 = strstr(underline, WordListGetWord(wordList,arg)) ) != NULL ) {
				for ( int i = 0; i < strlen(WordListGetWord(wordList,arg)); i++ ) {
					temp2[i] = '^';
				}
			}
		}
		// Any other stuff replaced with SPACE
		for ( int i = 0; i < strlen(underline); i++ ) {
				if ( underline[i] != '^' ) {
					underline[i] = ' ';

				}
		}
		// for ( int i = 0; i < strlen(temp); i++ ) {
		// 	if ( underline[i] == '\n' ) break;
		// 	putchar(temp[i]);
		// }
		// putchar('\n');
		// for ( int i = 0; i < strlen(underline); i++ ) {
		// 	if ( underline[i] == '\n' ) break;
		// 	putchar(underline[i]);
		// }
		// 		putchar('\n');
		printf("%f\n", score);
		printf("%s\n", temp);
		printf("%s\n", underline);

		free(underline);
		free(result);
	}

	HeapDestroy(heap);


}


void userLoop() {
	 // User interface for commands on search engine

	char buffer[BUFFERSIZE];
	char * temp;
	char * command;
	WordList * parameters;

	while ( 1 != 0 ) { // only user can terminate with /exit 

		WordListCreate(&parameters);
		fgets(buffer,BUFFERSIZE,stdin); //	Read command
		command = strtok(buffer," \n\t");

		//	Read parameters
		int paramCount = -1;
		do {
			paramCount++;
			temp = strtok(NULL,DELIMS);
			if ( temp == NULL ) break;
			WordListInsert(parameters, temp);
		} while ( temp != NULL );
		
		//	Execute appropriate command
		if ( strcmp(command,"/exit") == 0 ) {
			WordListDestroy(parameters);
			break;
		} else if ( strcmp(command,"/search") == 0 ) {
			if ( parameters->length == 0 ) {
				printf("Wrong format: /search arg1 arg2 ... arg10\n");
			} else {
				searchQuery(parameters);
			}
		} else if ( strcmp(command,"/df") == 0 ) {
			if ( parameters->length == 0 ) {
				TrieDf(trie->children,NULL);
			} else {
				TrieDf(trie->children,WordListGetWord(parameters,parameters->length-1));
			}
		} else if ( strcmp(command,"/tf") == 0 ) {
			if ( parameters->length != 2 ) {
				printf("Wrong format:/tf id word\n");
			} else {
				int id = atoi(WordListGetWord(parameters,parameters->length-1));
				char * word = WordListGetWord(parameters,parameters->length - 2);
				if ( TrieTf(trie,word,id) == -1 ) {
					printf("%d %s not found.\n",id,word);
				} else {
					printf("%d %s %d\n",id, word, TrieTf(trie,word,id));
				}
			}
		} else {
			printf("Unknown command, available commands are: \n");
			printf("/search arg1 arg2 ... arg10\n");
			printf("/df (filter)\n");
			printf("/tf id word\n");
		}
		WordListDestroy(parameters);
	}

}


int main ( int argc, char * argv[] ) {

	if ( argc < 3 ) {
		printf("Invalid arguments: Please exectue the program like this\n");
		printf("/main -i \"input file\" (-k K)\n");
		return -1;
	}

	FILE * fp1, *fp2;

	fp1 = fopen(argv[2], "r");
	fp2 = fopen(argv[2], "r");

	char buffer[BUFFERSIZE];

	// Calculate number of lines
	int expectedId = 0;
	while( fgets(buffer,BUFFERSIZE,fp2) != NULL ) {
		maxLines++;
		if ( atoi(buffer) != expectedId++ ) {
			printf("Invalid input file: text ids not in order \n");
			printf("Expected %d, got %d\n", --expectedId, atoi(buffer));
			return -2;
		}
	} 
	//Allocate number of lines on Map
	textMap = malloc( sizeof(char*) * maxLines); 
	documentWordCount = malloc ( sizeof(int) * maxLines);
	for ( int i = 0; i < maxLines; i++) documentWordCount[i] = 0;
	TrieCreate(&trie);

	printf("Loading ...\n");
	char * word;
	int id;
	//	Calculate size of lines and insert on trie and map
	for ( int currentLine = 0; currentLine < maxLines; currentLine++ ) { 
		memset(buffer,0,BUFFERSIZE);
		fgets(buffer,BUFFERSIZE,fp1);

		int tempLen = strlen(buffer);
		textMap[currentLine] =  malloc( sizeof(char) * tempLen + 1);
		strcpy(textMap[currentLine],buffer);

		id = atoi(strtok(buffer,DELIMS));
		while (  ( word = strtok(NULL,DELIMS) ) != NULL ) {
			TrieInsert(trie,word, id);
			// used for scoring
			averageWords++;
			documentWordCount[currentLine]++;
		}
	}
	averageWords /= maxLines;

	// Map print
	// for ( int i = 0; i < maxLines; i++ ) {
	// 	printf("Line %s \n", textMap[i]);
	// }

	//	Entering user-mode
	printf("Done!\n");
	userLoop();

	//De-allocs
	for( int currentLine = 0; currentLine < maxLines; currentLine++) { 
		free(textMap[currentLine]);
	}
	free(textMap);
	free(documentWordCount);
	TrieDestroy(trie);

	//Close files
	fclose(fp1);
	fclose(fp2);


}
