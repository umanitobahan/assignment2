#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

struct DUNGEON{
	char title[500];
	char array[1000][1000];
	int rows;
	int cols;
	int steps;
};

typedef struct DUNGEON Dungeon;

FILE *loadFile(char *name);
void readFile(FILE *file);
Dungeon *createDungeon();

int main(int argc, char *argv[]){
	FILE *file = NULL;
	file = loadFile(argv[1]);
  	assert(file != NULL);
	if(file != NULL){
		readFile(file);
	}

	return EXIT_SUCCESS;
}

FILE *	loadFile(char *name){
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
	Dungeon *newDungeon = NULL;
	newDungeon = createDungeon();
	assert(newDungeon != NULL);
	fscanf(file, "%d %d %d", &(newDungeon->rows), &(newDungeon->cols), &(newDungeon->steps));
	printf("%d%d%d\n",newDungeon->rows, newDungeon->cols, newDungeon->steps);
	
}

Dungeon *createDungeon(){
	Dungeon *newDungeon = NULL;
	newDungeon = malloc(sizeof(Dungeon));
	assert(newDungeon != NULL);
	if(newDungeon == NULL){
		printf("alloc failed");
	}
	return newDungeon;
}
