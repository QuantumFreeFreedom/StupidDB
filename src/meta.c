/*
Este ficheiro serve para lidar com "meta statements" (commandos que não são sql)
*/

#include "include/meta.h"
#include "include/input.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

MetaType execute_meta(Input *statement)
{
    if(statement == NULL)
    {
        return META_UNRECOGNIZED_COMMAND;
    }

    if(strcmp(statement->content, ".exit") == 0)
    {
        printf("Exiting...");
        free(statement);
        exit(EXIT_SUCCESS);
    }

    return META_UNRECOGNIZED_COMMAND;
}

void meta_init(Input *statement)
{
    if(execute_meta(statement) != META_COMMAND)
    {
        printf("Unrecognized command: %s \n", statement->content);
    }
}