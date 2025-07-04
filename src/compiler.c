#include "include/compiler.h"
#include "include/input.h"
#include "include/statements.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Executes a simple validation on the input, to prevent wasting resources
 * on trash inputs.
 */
CompilerStatus validateInputSimple(CompilerReturn* compRet, Input* inpt, Statement* stmt)
{
    if(inpt == NULL)
    {
        compRet->prepared_stmt = stmt;
        compRet->status = COMPILER_FALIURE;

        printf("Input given was NULL. \n Error happened on compiler.c inside function prepare(Input* inpt).\n inpt == NULL\n");
        return COMPILER_FALIURE;
    }
 
    /**
     * As of writing this the shortest instruction possible (at least for this simple database)
     * is drop, whith 4 characters
     */
    if(inpt->length < 4)
    {
        compRet->prepared_stmt = stmt;
        compRet->status = COMPILER_FALIURE;

        printf("Query given was too short\n");
        return COMPILER_FALIURE;
    }

    return COMPILER_SUCCESS;
}


CompilerReturn* prepare(Input* inpt)
{
    CompilerReturn* compRet = malloc(sizeof(CompilerReturn));
    Statement* stmt = malloc(sizeof(Statement));

    if(validateInputSimple(compRet, inpt, stmt) == COMPILER_FALIURE)
    {
        return compRet;
    }

    size_t pos = 0;

    while(pos != inpt->length-1)
    {

    }

    return compRet;
}
