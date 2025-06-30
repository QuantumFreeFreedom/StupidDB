#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Input{
    char* content;
    size_t length;
};

struct Input* getInput()
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

    struct Input* inpt = malloc(sizeof(struct Input));

    if(inpt == NULL)
    {
        perror("Failed to allocate memory for input struct");
        free(inpt);
        exit(EXIT_FAILURE);
    }

    inpt->length = len;
    inpt->content = text;

    return inpt;
}

int main(int argc, char *argv[]) {

    printf("Welcome to SupidDB \n \n");
    
    while(true)
    {
        printf("StupidDB > ");
        struct Input* inpt = getInput();

        if(strcmp(inpt->content, ".exit") == 0)
        {
            printf("Exiting...");
            return EXIT_SUCCESS;
        }
        else{
            printf("Command does not exist: %s\n", inpt->content);
        }
    }

    return EXIT_SUCCESS;
}
