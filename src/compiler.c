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
    unsigned short maxTokenLen = 5;
    char* firstToken = malloc(maxTokenLen*sizeof(char)); // drop is 4 characters and we need a null terminator \0
    unsigned short firstTokenlen = 0;
    
    do {
        firstToken[firstTokenlen] = stmt[*pos];
        
        // Resize firstToken if the first token isn't DROP
        if(firstTokenlen == maxTokenLen - 1)
        {
            maxTokenLen = 7;
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
            free(firstToken);
            return STMT_INVALID;
        }

        firstTokenlen++;
        (*pos)++;

        if(firstTokenlen == maxTokenLen)
        {
            free(firstToken);
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

    free(firstToken);
    return STMT_INVALID;
}

void skipSpaces(char* text, size_t *pos, size_t length)
{
    if(*pos == length - 1)
    {
        return;
    }

    while(text[*pos] == ' ' && *pos != length - 1)
    {
        (*pos)++;
    }
}

CompilerStatus ConstructDrop(Statement* stmt, size_t* pos, Input* inpt)
{
    int tableNameLen = 11;
    int tbNamePos = 0;
    char* tableName = malloc(tableNameLen*sizeof(char));

    while(inpt->content[*pos] != ';' && *pos != inpt->length-1)
    {
        if(tbNamePos == tableNameLen - 1)
        {
            tableNameLen += 10;
            char* tmp = realloc(tableName, tableNameLen*sizeof(char));

            if(tmp == NULL)
            {
                free(tmp);
                printf("failed to realloc tableName on ConstructDrop");
                return COMPILER_FALIURE;
            }

            tableName = tmp;
        }

        if(inpt->content[*pos] == ' ') // Make sure only one table name was meantioned
        {
            skipSpaces(inpt->content, pos, inpt->length);

            if(inpt->content[*pos] != ';')
            {
                printf("Please only include one table when dropping");
                return COMPILER_FALIURE;
            }

            break;
        }
        tableName[tbNamePos] = inpt->content[*pos];
        tbNamePos++;
        (*pos)++;
    }

    tableName[tableNameLen] = '\0';

    DropSTMT* drop = (DropSTMT*)stmt->stmt_data;
    drop->tableName = tableName;

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

    skipSpaces(inpt->content, &pos, inpt->length);
    stmt->type = getStmtType(inpt->content, &pos, inpt->length);

    skipSpaces(inpt->content, &pos, inpt->length);

    // Here we see why the void pointer comes in handy
    switch(stmt->type)
    {
        case STMT_DROP:
        stmt->stmt_data = malloc(sizeof(DropSTMT));
        compRet->status = ConstructDrop(stmt, &pos, inpt);
        compRet->prepared_stmt = stmt;
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
