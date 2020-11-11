/////////////////////////////////////////////////////////////////////////
//////////////////////// auxiliary_function.c ///////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the helper functions which help the Father
//      process. This functions are more generals then the one in 
//      father.c

//............................Includes.................................//
//.....................................................................//
#include "father.h"
#include "hard_coded_data.h"

extern int errno;


//...........................Functions.................................//
//.....................................................................//
/*
* Function:        file_check
* description:     check if file open correctlly
* input:           file
* output:          none
*/
void file_check(FILE* file){
	int				errnum;
	
	if (!file) {
		errnum = errno;
		fprintf(stderr, "Value of errno: %d\n", errno);
		perror("Error printed by perror");
		fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
		
		exit(EXIT_FAILURE);
	}
}

/*
* Function:        exit_prog
* description:     this function close the program, close the file and free memory
* input:           input file, output file, forest srtruct
* output:          none
*/
void exit_prog(FILE* input, FILE* output, Forest* forest){
	
	fclose(input);
	fclose(output);

	free(forest->str);
	for (int i = 0; i < forest->size; i++) {free(forest->forest[i]);}
	free(forest->forest);
}

/*
* Function:        copy_struct
* description:     this function duplicate one struct to the other one
* input:           destination forest sturct, from forest sturct
* output:          none
*/
void copy_struct(Forest* forest_to, Forest* forest_from) {
	forest_to->size = forest_from->size;
	forest_to->generations = forest_from->generations;
	
	forest_to->str = (char*)malloc(((forest_from->size * forest_from->size) + END_STRING) * sizeof(char));
	if (!forest_to->str) {
		printf("Error: memory doesn't allocote correctly\n");
		exit(EXIT_FAILURE);
	}
	strcpy(forest_to->str, forest_from->str);
	

	forest_to->forest = (int**)malloc(forest_from->size * sizeof(int*));
	if (!forest_to->forest) {
		printf("Error: memory doesn't allocote correctly\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < forest_from->size; i++) {
		forest_to->forest[i] = (int*)malloc(forest_from->size * sizeof(int));
	}

	for (int i = 0; i < forest_from->size; i++) {
		for (int j = 0; j < forest_from->size; j++) {
			forest_to->forest[i][j] = forest_from->forest[i][j];
		}
	}
}

// calculate num of fire
/*
int fire(char* str) {
	int len, burned_trees = 0;
	
	len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (str[i] == 'F') {
			burned_trees++;
		}
	}
	return burned_trees;
}*/
