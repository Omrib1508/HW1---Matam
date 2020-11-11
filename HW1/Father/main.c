/////////////////////////////////////////////////////////////////////////
///////////////////////////////// main.c ////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#include "auxiliary_function.h"
#include "father.h"

/*
* Function:        main
* description:     the main function does the son process
* input:           number of arguments, array of argument
* output:          number of trees that was burn in process
*/

int main(int argc, char* argv[]) {
	FILE			*input, *output;
	Forest*			forest = NULL;

	forest = (Forest*) malloc(sizeof(Forest));
	if (!forest) {
		printf("Error: memory doesn't allocote correctly\n");
		exit(EXIT_FAILURE);
	}

	if (argc != ARGUMENT) {
		printf("Error: invalid number of arguments(%d instead of %d)\n", (argc - 1), ARGUMENT);
		exit(EXIT_FAILURE);
	}
	else {
		input = fopen(argv[ARGUMENT - 2], "r");
		file_check(input);
		output = fopen(argv[ARGUMENT - 1], "w");
		file_check(output);

		// create forest data structere
		verification(input, forest);

		// process the forest and print
		iterations(output, forest);

		// exit and free memory
		exit_prog(input, output, forest);
	}

	return EXIT_SUCCESS;
}
