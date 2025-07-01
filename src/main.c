#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/input.h"
#include "include/meta.h"


int main(int argc, char *argv[]) {

    printf("Welcome to SupidDB \n \n");
    
    while(true)
    {
        printf("StupidDB > ");
        Input* inpt = getInput();

        if(inpt->content[0] == '.')
        {
            meta_init(inpt);
        }
        else{
            
        }

        free(inpt);
    }

    return EXIT_SUCCESS;
}


