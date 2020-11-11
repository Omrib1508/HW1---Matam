/////////////////////////////////////////////////////////////////////////
//////////////////////auxiliary_function.h //////////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the function and declarion to the auxiliary
//      function. There are also the include to father.h.

#ifndef AUXILIARY_FUNCTION_H
#define AUXILIARY_FUNCTION_H

//............................Includes.................................//
//.....................................................................//
#include "father.h"

//...........................Functions.................................//
//.....................................................................//
void file_check(FILE* file);

void exit_prog(FILE* input, FILE* output, Forest* forest);

void copy_struct(Forest* forest_to, Forest* forest_from);

//int fire(char* str);
#endif // !AUXILIARY_FUNCTION_H
