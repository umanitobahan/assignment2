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
	int move;
};

typedef struct DUNGEON Dungeon;

FILE *loadFile(char *name);
void readFile(Dungeon *newDungeon, FILE * const file);
void printDungeon(Dungeon const * const newDungeon);

int main(int argc, char *argv[]){
	FILE *file = NULL;
	Dungeon newDungeon;

	file = loadFile(argv[1]);
  	assert(file != NULL);
	if(file != NULL){
		readFile(&newDungeon, file);
	}
	printDungeon(&newDungeon);
	#ifdef NDEBUG
		printf("Debug is off\n");
	#endif
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

void readFile(Dungeon *newDungeon, FILE * const file){
        assert(file != NULL);
	assert(newDungeon != NULL);
	if(file != NULL && newDungeon != NULL){
		int position = 0;
		char ch = '\0';
		ch = fgetc(file);
		if(ch == '*'){
			newDungeon->title[position++] = ch;
			ch = fgetc(file);
			while(ch != '*'){
				newDungeon->title[position++] = ch;
				ch = fgetc(file);
			}
			newDungeon->title[position++] = ch;
			newDungeon->title[position] = '\0';
			while(ch != '\n'){
 				ch = fgetc(file);
			}
		}
		fscanf(file, "%d%d%d", &(newDungeon->rows), &(newDungeon->cols), &(newDungeon->steps));
		newDungeon->move = 0;
		ch = fgetc(file);
		while(ch != '\n'){
			ch = fgetc(file);
		}
		for(int r=1; r<=newDungeon->rows; r++){
			for(int c=1; c<=newDungeon->cols; c++){
				ch = fgetc(file);
				newDungeon->array[r][c] = ch;		
			}
			while(ch != '\n'){
				ch = fgetc(file);
			}
		}
		newDungeon->array[0][0] = '+';
		newDungeon->array[0][newDungeon->cols+1] = '+';
		newDungeon->array[newDungeon->rows+1][0] = '+';
		newDungeon->array[newDungeon->rows+1][newDungeon->cols+1] = '+';
		for(int c=1; c<=newDungeon->cols; c++){
			newDungeon->array[0][c] = '-';
			newDungeon->array[newDungeon->rows+1][c] = '-';
		}
		for(int r=1; r<=newDungeon->rows; r++){
			newDungeon->array[r][0] = '|';
			newDungeon->array[r][newDungeon->cols+1] = '|';
		}
	}

}

void printDungeon(Dungeon const * const newDungeon){
	assert(newDungeon != NULL);
	if(newDungeon != NULL){
		printf("%s\n", newDungeon->title);
		printf("Move %d:\n",newDungeon->move);
		for(int r=0; r<=newDungeon->rows+1; r++){
                        for(int c=0; c<=newDungeon->cols+1; c++){
                                printf("%c", newDungeon->array[r][c]);
                        }
                        printf("\n");
                }

	}
}
