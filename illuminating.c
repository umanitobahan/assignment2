#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

struct DUNGEON{
	char title[500];
	char array[1000][1000];
	int row;
	int col;
	int steps;
};

typedef struct DUNGEON Dungeon;

FILE *loadFile(char *name);
void readFile(FILE *file);
Dungeon * createDungeon();
Dungeon *destroyDungeon(Dungeon * newDungeon);
void validateDungeon(Dungeon const * const newDungeon);
void printDungeon(Dungeon const * const newDungeon);

int main(int argc, char *argv[]){
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
	newDungeon = createDungeon();
	assert(newDungeon != NULL);
	assert(file != NULL);
	if(file != NULL){
		ch = fgetc(file);
		while( ch != EOF){
			if(ch == '*'){
				newDungeon->title[position] = ch;
				position++;
				ch = fgetc(file);
				while(ch != '*'){
						assert(position < 499);	
						newDungeon->title[position] = ch;
						position++;
						ch = fgetc(file);
										
					}
					newDungeon->title[position] = '*';
					position++;
					newDungeon->title[position] = '\0';
					while(ch != '\n'){
							ch = fgetc(file);
						}
					assert(ch == '\n');
					fscanf(file, "%d %d %d", newDungeon->row, newDungeon->col, newDungeon->steps);
				        ch = fgetc(file);
					while(ch != '\n'){
							ch = fgetc(file);
						}
					assert(ch = '\n');
					for(int r=0; r<newDungeon->row; r++){
						for(int c=0; c<newDungeon->col; c++){
								newDungeon->array[r][c] = fgetc(file);
							}
							newDungeon->array[r][newDungeon->col] = '\0';
							while(ch != '\n' || ch != EOF){
								ch = fgetc(file);
							}
						}
				
				}
			printDungeon(newDungeon);
			if(ch != EOF){
				ch = fgetc(file);
				}
			}
		
		}
	}
//	newDungeon = destroyDungeon(newDungeon);



Dungeon * createDungeon(){
	Dungeon *newDungeon = NULL;
	newDungeon = malloc(sizeof(Dungeon));
	assert(newDungeon != NULL);
	validateDungeon(newDungeon);
	return newDungeon;
}

Dungeon * destroyDungeon(Dungeon * newDungeon){
	
}

void validateDungeon(Dungeon const * const newDungeon){
	assert(newDungeon != NULL);
	assert(newDungeon->title != NULL);
	assert(newDungeon->array != NULL);
	assert('\0' == newDungeon->title[strlen(newDungeon->title)]);
}

void printDungeon(Dungeon const * const newDungeon){
	printf("%s\n", newDungeon->title);
	printf("%d  %d  %d  \n", newDungeon->row, newDungeon->col, newDungeon->steps);
	for(int r=0; r<newDungeon->row; r++){
		for(int c=0; c<newDungeon->col; c++){
			printf("%c", newDungeon->array[r][c]);
			}
		printf("\n");
		}
	printf("\n");
}
