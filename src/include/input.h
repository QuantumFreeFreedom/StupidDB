#ifndef INPUT
#define INPUT

#include <stdlib.h>

typedef struct{
    char* content;
    size_t length;
} Input;

Input* getInput();

#endif