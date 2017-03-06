#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

struct DUNGEON{
	char title[500];
	char array[1000][1000];
	char operate[500];
	int rows;
	int cols;
	int steps;
	int move;
};

typedef struct DUNGEON Dungeon;

FILE *loadFile(char *name);
void readFile(Dungeon *newDungeon, FILE * const file);
void printDungeon(Dungeon const * const newDungeon);
void validateDungeon(Dungeon const * const newDungeon);
void playDungeon(int m, Dungeon *newDungeon);

int main(int argc, char *argv[]){
	FILE *file = NULL;
	Dungeon newDungeon;
	int move = 0;

	file = loadFile(argv[1]);
  	assert(file != NULL);
	if(file != NULL){
		readFile(&newDungeon, file);
		validateDungeon(&newDungeon);
		printDungeon(&newDungeon);
		//while(move <= newDungeon.steps){
			playDungeon(move, &newDungeon);
		//}
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
			  	if(ch == '@'){
					newDungeon->array[r][c] = '%';
				}
				if(ch == '.'){
					newDungeon->array[r][c] = ',';
				}
				if(ch == '~'){
					newDungeon->array[r][c] = '!';
				}
				if(ch == ' '){
					newDungeon->array[r][c] = ' ';
				}
			}
			while(ch != '\n'){
				ch = fgetc(file);
			}
		}
		assert(ch == '\n');
		for(position=0; position<newDungeon->steps; position++){
			ch = fgetc(file);
			newDungeon->operate[position] = ch;
		}
		newDungeon->operate[position] = '\0';
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
	validateDungeon(newDungeon);
}

void printDungeon(Dungeon const * const newDungeon){
	assert(newDungeon != NULL);
	validateDungeon(newDungeon);
	if(newDungeon != NULL){
		printf("%s\n", newDungeon->title);
		printf("Move %d:\n",newDungeon->move);
		for(int r=0; r<=newDungeon->rows+1; r++){
                        for(int c=0; c<=newDungeon->cols+1; c++){
                                printf("%c", newDungeon->array[r][c]);
                        }
                        printf("\n");
                }
	for(int i=0; i<newDungeon->steps; i++){
		printf("%c", newDungeon->operate[i]);
	}
	printf("\n");
	}
}

void validateDungeon(Dungeon const * const newDungeon){
	assert(newDungeon != NULL);
	assert(newDungeon->title != NULL);
	assert(newDungeon->title[strlen(newDungeon->title)] == '\0');
	assert(newDungeon->array != NULL);
	assert(newDungeon->operate != NULL);
}

void playDungeon(int m, Dungeon *newDungeon){
	assert(newDungeon != NULL);
	validateDungeon(newDungeon);
	int distance = 0;
	float range1 = sqrt(2);
	float range2 = sqrt(8);
	float range3 = 3.0;
	int mr = 0;
	int mc = 0;
	if(newDungeon != NULL){
		for(int i=0; i<newDungeon->steps; i++){
			if(newDungeon->operate[i] == 'v'){
				for(int r=1; r<=newDungeon->rows; r++){
					for(int c=1; c<=newDungeon->cols; c++){
						if(newDungeon->array[r][c] == '%'){
							mr = r;
							mc = c;
								
							}
						}
					}
				if(newDungeon->array[mr+1][mc] == '-' || newDungeon->array[mr+1][mc] == '!'){
					}
				if(newDungeon->array[mr+1][mc] != '-' && newDungeon->array[mr+1][mc] != '!'){
					newDungeon->array[mr][mc] = ',';
					newDungeon->array[mr+1][mc] = '%';
					newDungeon->move = newDungeon->move+1;
				}
				for(int newr=1; newr<=newDungeon->rows; newr++){
					for(int newc=1; newc<=newDungeon->cols; newc++){
						distance = sqrt(pow((newc-mc), 2)+pow((newr-(mr+1)),2));
						if(distance == 0){
						}
						if(distance>0 && distance <= range1 && newDungeon->array[newr][newc] != '!'){
							newDungeon->array[newr][newc] = '#';		
						}
						if(distance > range1 && distance <= range2 && newDungeon->array[newr][newc] != '!'){
							newDungeon->array[newr][newc] = '=';
						}
						if(distance > range2 && distance <= range3 && newDungeon->array[newr][newc] != '!'){
							newDungeon->array[newr][newc] = '-';
						}
						if(distance > range3){
							if(newDungeon->array[newr][newc] == '#' || newDungeon->array[newr][newc] == '=' || newDungeon->array[newr][newc] == '-'){
								newDungeon->array[newr][newc] = ',';
							}
						} 
					}
				}
				printDungeon(newDungeon);	
			}

			if(newDungeon->operate[i] == '^'){
				for(int r=1; r<=newDungeon->rows; r++){
                                        for(int c=1; c<=newDungeon->cols; c++){
                                                if(newDungeon->array[r][c] == '%'){
                                                        mr = r;
                                                        mc = c;

                                                }
                                        }
				}
				if(newDungeon->array[mr-1][mc] == '-' || newDungeon->array[mr-1][mc] == '!'){
				}
                                if(newDungeon->array[mr-1][mc] != '-' && newDungeon->array[mr+1][mc] != '!'){
                                        newDungeon->array[mr][mc] = ',';
                                        newDungeon->array[mr-1][mc] = '%';
                                        newDungeon->move = newDungeon->move+1;
                                }
                                printDungeon(newDungeon);
			        
			}

			if(newDungeon->operate[i] == '>'){
				for(int r=1; r<=newDungeon->rows; r++){
                                        for(int c=1; c<=newDungeon->cols; c++){
                                                if(newDungeon->array[r][c] == '%'){
                                                        mr = r;
                                                        mc = c;

                                                        }
                                                }
                                        }
				if(newDungeon->array[mr][mc+1] == '|' || newDungeon->array[mr][mc+1] == '!'){
				}
                                if(newDungeon->array[mr][mc+1] != '|' && newDungeon->array[mr][mc+1] != '!'){
                                        newDungeon->array[mr][mc] = ',';
                                        newDungeon->array[mr][mc+1] = '%';
                                        newDungeon->move = newDungeon->move+1;
                                }
                                printDungeon(newDungeon);
			}

			if(newDungeon->operate[i] == '<'){
				for(int r=1; r<=newDungeon->rows; r++){
                                        for(int c=1; c<=newDungeon->cols; c++){
                                                if(newDungeon->array[r][c] == '%'){
                                                        mr = r;
                                                        mc = c;

                                                        }
                                                }
                                        }
				if(newDungeon->array[mr][mc-1] == '|' || newDungeon->array[mr][mc-1] == '!'){
				}
                                if(newDungeon->array[mr][mc-1] != '|' && newDungeon->array[mr][mc-1] != '!'){
                                        newDungeon->array[mr][mc] = ',';
                                        newDungeon->array[mr][mc-1] = '%';
                                        newDungeon->move = newDungeon->move+1;
                                }
                                printDungeon(newDungeon);
			}
	
		}	
	}
}
