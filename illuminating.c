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

main(int argc, char *argv[]){
	FILE *file = NULL;
	file = loadFile(argv[1]);

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
