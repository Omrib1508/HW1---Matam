/////////////////////////////////////////////////////////////////////////
/////////////////////////////// father.c ////////////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the function bodies. All this functions are
//      helping to build the Father process, and olso create the son 
//      process.

//............................Includes.................................//
//.....................................................................//
#include "auxiliary_function.h"
#include "father.h"
#include "hard_coded_data.h"

//...........................Functions.................................//
//.....................................................................//
/*
* Function:        verification
* description:     check if file code is good and initailize forest sturct
* input:           input file, forest struct
* output:          none
*/
void verification(FILE *file, Forest* forest) {
	char			line[LINE_LENGTH];

	fgets(line, LINE_LENGTH, file);
	forest->size = (int)strtol(line, NULL, 10);
	if (forest->size < 1){
		printf("Error: invaild size of matrix\n");
		exit(EXIT_FAILURE);
	}
	
	fgets(line, LINE_LENGTH, file);
	forest->generations = strtol(line, NULL, 10);
	if (forest->generations < 1) {
		printf("Error: invaild generations\n");
		exit(1);
	}

	forest->str = initialize_str(file, forest->size);
	forest->forest = initialize_table(forest->str, forest->size);
}

/*
* Function:        initialize
* description:     the function initialize the forest string
* input:           input file, forest size
* output:          forest string
*/
char* initialize_str(FILE* file, int size) {
	int				i=0 , j=0, index=0;
	char*			forest_str = NULL;
	char			letter;

	
	forest_str = (char*)malloc(((size * size) + END_STRING) * sizeof(char));
	if (!forest_str) {
		printf("Error: memory doesn't allocote correctly\n");
		exit(EXIT_FAILURE);
	}

	while (i < size) {
		index = (i * size) + j;
		letter = fgetc(file);

		switch (letter) {
		case ',':
			continue;

		case '\n':
			if (j != size) 
				goto print_error;
			i++;
			j = 0;
			break;

		case 'F':
			forest_str[index] = letter;
			j++;
			break;

		case 'G':
			forest_str[index] = letter;
			j++;
			break;

		case 'T':
			forest_str[index] = letter;
			j++;
			break;

		case EOF:
			if (j != size)
				goto print_error;
			forest_str[index] = '\0';
			return forest_str;

		}
	}

	return forest_str;

print_error:
	printf("Error: Forest is not writing correct\n");
	free(forest_str);
	return NULL;
}

/*
* Function:        initialize_table
* description:     the function initialize the forest matrix
* input:           string of forest, forest size
* output:          forest matrix
*/
int** initialize_table(char* str, int size) {
	int**				table;
	int					index;

	table = (int**) malloc(size * sizeof(int*));
	if (!table) {
		printf("Error: memory doesn't allocote correctly\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < size; i++) {
		table[i] = (int*)malloc(size * sizeof(int));
	}
	

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			index = (i * size) + j;
			switch (str[index]) {
			case 'F':		table[i][j] = F;		break;
			case 'G':		table[i][j] = G;		break;
			case 'T':		table[i][j] = T;		break;
			}
		}
	}

	// check if matrix got moved to table[][]//
	/*
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d, ", table[i][j]);
			if (j == size - 1) {
				printf("\n");
			}
		}
	}*/
	return table;
}

/*
* Function:        neighbours
* description:     the function check if table[i][j] has neighbour
* input:           forest struct, forest table row no., forest table col no. 
* output:          none
*/
void neighbours(Forest* forest, int i, int j) {
	if (i == 0) {
		if (j == (forest->size) - 1){
			down = 1;
			left = 1;
		}
		else if (j == 0){
			right = 1;
			down = 1;
		}
		else{
			right = 1;
			down = 1;
			left = 1;
		}
	}
	else if (i == (forest->size) - 1){
		if (j == (forest->size) - 1){
			up = 1;
			left = 1;
		}
		else if (j == 0){
			up = 1;
			right = 1;
		}
		else{
			up = 1;
			right = 1;
			left = 1;
		}
	}

	else if ((j == 0) && (i < (forest->size - 1)) && (i > 0)){
		right = 1;
		down = 1;
		up = 1;
	}

	else if ((j == (forest->size - 1)) && (i < (forest->size - 1)) && (i > 0)){
		left = 1;
		up = 1;
		down = 1;
	}

	else{
		up = 1;
		down = 1;
		left = 1;
		right = 1;
	}

}


/*
* Function:        update_forest
* description:     the function update forest after process
* input:           forest matrix, forest size
* output:          none
*/

void update_forest(Forest* forest) {
	int neighbour_ground = 0, index = 0;
	Forest* bis = NULL;

	bis = (Forest*)malloc(sizeof(Forest));
	if (!bis) {
		printf("Error: memory doesn't allocote correctly\n");
		exit(EXIT_FAILURE);
	}
	copy_struct(bis, forest);

	// print the forest matrix after update
	/*
	printf("%s\n\n", bis->str);
	for (int i = 0; i < forest->size; i++) {
		for (int j = 0; j < forest->size; j++) {
			printf("%c,", (char)bis->forest[i][j]);
			if (j == forest->size - 1) {
				printf("\n");
			}
		}
	}
	printf("\n");*/

	for (int i = 0; i < forest->size; i++) {
		for (int j = 0; j < forest->size; j++) {
			down = 0;
			up = 0;
			left = 0;
			right = 0;
			switch (forest->forest[i][j]) {
			case F:
				neighbours(forest, i, j);
				if (left == 1 && (forest->forest[i][j - 1] == T)) {
					bis->forest[i][j - 1] = F;
				}
				if (right == 1 && (forest->forest[i][j + 1] == T)) {
					bis->forest[i][j + 1] = F;
				}
				if (up == 1 && (forest->forest[i - 1][j] == T)) {
					bis->forest[i - 1][j] = F;
				}
				if (down == 1 && (forest->forest[i + 1][j] == T)) {
					bis->forest[i + 1][j] = F;
				}
				bis->forest[i][j] = G;
				break;

			case G:
				neighbours(forest, i, j);
				if (right == 1){
					if (forest->forest[i][j + 1] == T){
						neighbour_ground++;
					}
				}
				if (left == 1){
					if (forest->forest[i][j - 1] == T){
						neighbour_ground++;
					}
				}
				if (up == 1){
					if (forest->forest[i - 1][j] == T){
						neighbour_ground++;
					}
				}
				if (down == 1){
					if (forest->forest[i + 1][j] == T){
						neighbour_ground++;
					}
				}
				if (up == 1 && right == 1 ) {
					if (forest->forest[i - 1][j + 1] == T) {
						neighbour_ground++;
					}
				}
				if (down == 1 && right == 1) {
					if (forest->forest[i + 1][j + 1] == T) {
						neighbour_ground++;
					}
				}
				if (up == 1 && left == 1) {
					if (forest->forest[i - 1][j - 1] == T) {
						neighbour_ground++;
					}
				}
				if (down == 1 && left == 1) {
					if (forest->forest[i + 1][j - 1] == T) {
						neighbour_ground++;
					}
				}
				if (neighbour_ground > 1){
					bis->forest[i][j] = T;
				}
				neighbour_ground = 0;
				break;
			}
		}
	}
	// print the forest matrix after update
	/*
	for (int i = 0; i < forest->size; i++) {
		for (int j = 0; j < forest->size; j++) {
			printf("%c,", (char)bis->forest[i][j]);
			if (j == forest->size - 1) {
				printf("\n");
			}
		}
	}*/
	
	for (int i = 0; i < forest->size; i++) {
		for (int j = 0; j < forest->size; j++) {
			index = (i * bis->size) + j;
			bis->str[index] = bis->forest[i][j];
		}
	}

	copy_struct(forest, bis);
	free(bis);
}

/*
* Function:        iteration
* description:     the function do the forest iterations and open son process
* input:           forest matrix, forest size
* output:          none
*/
void iterations(FILE* output, Forest* forest) {
	int				burned_trees;
	int				iter = 0;

	do {
		//burned_trees = fire(forest->str);   ** checking without process
		
		burned_trees = creat_process(forest->str);
		if (burned_trees < 0) {
			printf("Error: counting fire was failed\n");
			exit_prog(NULL, output, forest);
		}

		print_file(output, forest->str, forest->size, burned_trees);
		update_forest(forest);

	} while (iter++ < forest->generations - 1);

}


/*
* Function:        creat_process
* description:     the function create son process and active it
* input:           forest matrix, forest size
* output:          none
*/
int creat_process(char* forest_str)
{
	int					len;
	PROCESS_INFORMATION procinfo;
	STARTUPINFO			startinfo = { sizeof(STARTUPINFO) };
	char				*str;
	DWORD				waitcode;
	DWORD				exitcode;
	BOOL				retVal;
	TCHAR				*command = NULL;

	/* Making command line for son */
	len = strlen(forest_str) + strlen("Son.exe") + 2;
	str = (char*)malloc(len * sizeof(char));
	if (!str) {
		printf("Error: memory doesn't allocote correctly\n");
		exit(EXIT_FAILURE);
	}
	sprintf(str, "Son.exe %s", forest_str);

	/* Check sizof TCHAR */
	switch (sizeof(TCHAR)) {
	case 1:
		command = str;
		break;
	case 2:
		command = (char*)malloc(2 * len);
		if (!command) {
			printf("Error: memory doesn't allocote correctly\n");
			exit(1);
		}
		mbstowcs(command, str, len);
		break;
	}

	/*  Start the child process. */
	retVal = CreateProcess(NULL,                  /* No module name (use command line).        */
		command,               /* Command line.                             */
		NULL,                  /* Process handle not inheritable.           */
		NULL,                  /* Thread handle not inheritable.            */
		FALSE,                 /* Set handle inheritance to FALSE.          */
		NORMAL_PRIORITY_CLASS, /* creation/priority flags.                  */
		NULL,                  /* Use parent's environment block.           */
		NULL,                  /* Use parent's starting directory.          */
		&startinfo,            /* Pointer to STARTUPINFO structure.         */
		&procinfo);            /* Pointer to PROCESS_INFORMATION structure. */

	/* Wait for son process to end */
	if (retVal == 0) {
		printf("failed: WinError 0x%X\n", GetLastError());
		printf("Process Creation Failed!\n");
		return (FAIL_PROCESS);
	}

	/* Get waitcode of son process */
	waitcode = WaitForSingleObject(procinfo.hProcess, TIMEOUT_IN_MILLISECONDS);
	if (waitcode != WAIT_OBJECT_0) {
		printf("son process failed, terminat process. the waitcode is 0x%x\n", waitcode);
		TerminateProcess(procinfo.hProcess, BRUTAL_TERMINATION_CODE);
		retVal = false;
		Sleep(10);
		waitcode = WaitForSingleObject(procinfo.hProcess, TIMEOUT_IN_MILLISECONDS);
	}

	/* Get exit code from son process */
	GetExitCodeProcess(procinfo.hProcess, &exitcode);

	/* Release handles */
	CloseHandle(procinfo.hProcess);
	CloseHandle(procinfo.hThread);
	free(str);
	if (sizeof(TCHAR) == 2) {
		free(command);
	}

	// had brutal termination
	return (int)exitcode;
}



/*
* Function:        print_file
* description:     the function print to output file
* input:           output file, forest matrix, forest size, number of burend trees
* output:          none
*/
void print_file(FILE* file, char* str, int size, int fire) {
	fprintf(file, "%s - %d\n", str, fire);
	printf("%s - %d\n", str, fire);
}
