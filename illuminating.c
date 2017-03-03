#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

struct DUNGEON{
	char title[500];
	char array[1000][1000];
	int steps;
};

typedef struct DUNGEON Dungeon;

FILE *loadFile(char *name);
void readFile(FILE *file);


main(int argc, char *argv[]){
	FILE *file = NULL;
	file = loadFile(argv[1]);
	readFile(file);
	return EXIT_SUCCESS;
}

FILE *loadFile(char *name){
	FILE *file = NULL;
	assert(name != NULL);
	if(name != NULL){
		file = fopen(name, "r");
		assert(file != NULL);
	}
	
	if(file == NULL){
		printf("Open file failed");
	}

	return file;
}

void readFile(FILE *file){
	int position = 0;
	char ch = '\0';
	Dungeon *newDungeon = NULL;
	assert(file != NULL);
	if(file != NULL){
		ch = fgetc(file);
		while( ch != EOF){
			if(ch == '*'){
					
			}	
		}
	}

}
