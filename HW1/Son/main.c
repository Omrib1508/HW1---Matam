/////////////////////////////////////////////////////////////////////////
///////////////////////////////// main.c ////////////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This main.c file of the son process is incharge of reading the
//      forest string and calculate how much burning trees there are.

//............................Includes.................................//
//.....................................................................//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG 2
#define LINE_LENGTH 1000
#define FAIL_PROCESS -1


//...........................Functions.................................//
//.....................................................................//
/*
* Function:        main
* description:     the main function does the son process
* input:           number of arguments, array of argument 
* output:          number of trees that was burn in process
*/
int main(int argc, char* argv[]) {
	int burned_trees = 0, len = 0;
	FILE* file;
	
	if (argc != ARG) {
		printf("Error: invalid number of arguments(%d instead of %d)\n", (argc - 1), ARG);
		return FAIL_PROCESS;
	}
	else {
		len = strlen(argv[ARG - 1]);
		for (int i = 0; i < len; i++) {
			if (argv[ARG - 1][i] == 'F') {
				burned_trees++;
			}
		}
		return burned_trees;
	}
}