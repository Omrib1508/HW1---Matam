/////////////////////////////////////////////////////////////////////////
//////////////////////////////father.h //////////////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the function and declarion to the Father
//      process. There are also the include libraries. In this file there
//      is the forest sturct.

#ifndef FATHER_H
#define FATHER_H

//............................Includes.................................//
//.....................................................................//
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>

#include "hard_coded_data.h"

//...........................Structs...................................//
//.....................................................................//
typedef struct forest{
	int size;
	int generations;
	char* str;
	int** forest;
} Forest;

static int up = 0, down = 0, left = 0, right = 0;

//...........................Functions.................................//
//.....................................................................//
void verification(FILE* file, Forest* forest);

char* initialize_str(FILE* file, int size);

int** initialize_table(char* str, int size);

void neighbours(Forest* forest, int i, int j);

void update_forest(Forest* forest);

void iterations(FILE* output, Forest* forest);

int creat_process(char* forest_str);

void print_file(FILE* file, char* str, int size, int fire);

#endif // !FATHER_H
