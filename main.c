#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DELIMS " \n\t"

char ** textMap;
int maxLines = 0;

void userLoop() { // User interface for commands on search engine

	char buffer[100];
	char * command;
	char * params[10];

	while ( 1 != 0 ) {

		fgets(buffer,100,stdin); //	Read command
		command = strtok(buffer," \n\t");
		// printf("Command is  \" %s \" \n",command);

		//	Read parameters
		int paramCount = -1;
		do {
			paramCount++;
			params[paramCount] = strtok(NULL," \n\t");
			// printf("just got parameter %s\n", params[i]);
		} while ( params[paramCount] != NULL );

		printf("param count is %d\n" , paramCount);

		//	Execute appropriate command
		if ( strcmp(command,"/exit") == 0 ) {
			break;
		} else if ( strcmp(command,"/search") == 0 ) {



			// printf("searching\n");
			// TO BE FUNCTIONED
			char * word, * cparam;
			printf("getting in\n");
			for ( int j = 0; j < paramCount; j++ ) {
				cparam = params[j];
				printf("j is %d \n", j);
				for ( int i = 0; i < maxLines; i++ ) {
					printf("i is %d \n" , i);
					word = strtok(textMap[i], DELIMS);
					if ( strcmp(word,cparam) == 0 ) {
						printf("FOUND %s\n", cparam);
					}
					while ( (word = strtok(NULL,DELIMS)) != NULL ) {
						if ( strcmp(word,cparam) == 0 ) {
							printf("FOUND %s\n", cparam);
						}
					}
				}
			}



		}
	}
}


int main ( int argc, char * argv[] ) {

FILE * fp1, *fp2;

fp1 = fopen(argv[2], "r");
fp2 = fopen(argv[2], "r");

char buffer[100];

//	Calculate number of lines
while( fgets(buffer,100,fp2) != NULL ) maxLines++;
printf("Our line number is %d\n", maxLines);
//Allocate number of lines on Map
textMap = malloc( sizeof(char*) * maxLines); 

//	Calculate size of lines
for ( int currentLine = 0; currentLine < maxLines; currentLine++ ) { 
	fgets(buffer,100,fp1);
	int tempLen = strlen(buffer);
	textMap[currentLine] =  malloc( sizeof(char) * tempLen);
	strcpy(textMap[currentLine],buffer);
}

//Map print
//for ( int i = 0; i < maxLines; i++ ) {
//	printf("Line %s -----------------------------------\n", textMap[i]);
//}



//	Entering user-mode
printf("Loading done...\n");
userLoop();



//De-allocs
for( int currentLine = 0; currentLine < maxLines; currentLine++) { 
	free(textMap[currentLine]);
}
free(textMap);


//Close files
fclose(fp1);
fclose(fp2);


}
