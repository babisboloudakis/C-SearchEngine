#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ( int argc, char * argv[] ) {

FILE * fp1, *fp2;

fp1 = fopen(argv[2], "r");
fp2 = fopen(argv[2], "r");

char ** textMap;

int maxLines = 0;
char buffer[100];

//Calculate number of lines
while( fgets(buffer,100,fp2) != NULL ) maxLines++;
printf("Our line number is %d\n", maxLines);
//Allocate number of lines on Map
textMap = malloc( sizeof(char*) * maxLines); 

//Calculate size of lines
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



//De-allocs
for( int currentLine = 0; currentLine < maxLines; currentLine++) { 
	free(textMap[currentLine]);
}
free(textMap);


//Close files
fclose(fp1);
fclose(fp2);


}
