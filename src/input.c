#include "include/input.h"
#include <stdio.h>
#include <stdlib.h>

Input* getInput()
{
    char* text = NULL;
    size_t len = 0;
    ssize_t read;

    if((read = getline(&text, &len, stdin)) == -1) // reads the input and catches any error
    {
        exit(EXIT_FAILURE);
    }

    //removes the newline if it exists
    if (read > 0 && text[read - 1] == '\n') {
        text[read - 1] = '\0';
        read--;
    }

    Input* inpt = malloc(sizeof( Input));

    if(inpt == NULL)
    {
        perror("Failed to allocate memory for input struct");
        free(inpt);
        exit(EXIT_FAILURE);
    }

    inpt->length = read;
    inpt->content = text;

    return inpt;
}