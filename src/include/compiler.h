#ifndef COMPILER
#define COMPILER

#include "input.h"
#include "statements.h"

typedef enum{
    COMPILER_SUCCESS,
    COMPILER_FALIURE
} CompilerStatus;

typedef struct{
    Statement* prepared_stmt;
    CompilerStatus status;
} CompilerReturn;

CompilerReturn* prepare(Input* inpt);

CompilerStatus write_bytecode(Statement* stmt);

#endif