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

StatementType getStmtType(char* stmt, size_t* pos, size_t length)
{
    StatementType stmtType = STMT_INVALID;

    unsigned short maxTokenLen = 5;
    char* firstToken = malloc(maxTokenLen*sizeof(char)); // drop is 4 characters and we need a null terminator \0
    unsigned short firstTokenlen = 0;
    
    do {
        firstToken[firstTokenlen] = stmt[*pos];
        
        // Resize firstToken if the first token isn't DROP
        if(firstTokenlen == maxTokenLen - 1)
        {
            maxTokenLen++;
            char* tmp = realloc(firstToken, maxTokenLen*sizeof(char));
            
            if(tmp == NULL)
            {
                printf("Failed to realloc the firstToken on compiler.c. \n");
                free(firstToken);
                return STMT_INVALID;
            }

            firstToken = tmp;
        }

        if(*pos+1 == length) // prevent accessing out of bounds
        {
            return STMT_INVALID;
        }

        firstTokenlen++;
        (*pos)++;

        if(firstTokenlen == maxTokenLen)
        {
            return STMT_INVALID;
        }
        
    }while (stmt[*pos] != ' ');

    firstToken[++firstTokenlen] = '\0';

    if(strcmp(firstToken, "DROP") == 0)
    {
        free(firstToken);
        return STMT_DROP;
    }

    if(strcmp(firstToken, "SELECT") == 0)
    {
        free(firstToken);
        return STMT_SELECT;
    }

    if(strcmp(firstToken, "CREATE") == 0)
    {
        free(firstToken);
        return STMT_CREATE;
    }

    if(strcmp(firstToken, "INSERT") == 0)
    {
        free(firstToken);
        return STMT_INSERT;
    }

    if(strcmp(firstToken, "DELETE") == 0)
    {
        free(firstToken);
        return STMT_DELETE;
    }

    return STMT_INVALID;
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

    stmt->type = getStmtType(inpt->content, &pos, inpt->length);
    

    // Here we see why the void pointer comes in handy
    switch(stmt->type)
    {
        case STMT_DROP:
        stmt->stmt_data = malloc(sizeof(DropSTMT));
        break;

        case STMT_SELECT:
        stmt->stmt_data = malloc(sizeof(SelectSTMT));
        break;

        case STMT_CREATE:
        stmt->stmt_data = malloc(sizeof(CreateSTMT));
        break;

        case STMT_INSERT:
        stmt->stmt_data = malloc(sizeof(InsertSTMT));
        break;

        case STMT_DELETE:
        stmt->stmt_data = malloc(sizeof(DeleteSTMT));
        break;

        case STMT_INVALID:
        compRet->status = COMPILER_FALIURE;
        compRet->prepared_stmt = stmt;
        return compRet;
    }

    return compRet;
}
