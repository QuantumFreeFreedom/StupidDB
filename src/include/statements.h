#ifndef STATEMENT
#define STATEMENT

#include <stdlib.h>

#include <stdbool.h>

typedef enum{
    STMT_INSERT,
    STMT_SELECT,
    STMT_CREATE,
    STMT_DELETE
} StatementType;

typedef enum{
    INT,
    STRING
} VarTypes;

typedef enum {
    GREATER, // >
    LESSER, // <
    EQUAL // =
} Operators;

/**
 * I don't really care about allowing all the SQL functionality (I AM MAKING THIS FOR FUN)
 * so I will onlly allow WHERE conditions
 */
typedef struct{
    bool isLeftCol; // Defines if the left value is a column or not
    char* leftVal;
    char* rightVal;
    Operators op;
} Condition;

/**
 * *SELECT STATEMENT
 */
typedef struct {
    char* to_select;
    char* table_select;
    Condition* condition;
} SelectSTMT;

/**
 * *CREATE STATEMENT
 */
typedef struct{
    size_t PK_index;
    char* tableName; //this simple database only has 1 db so I dont need to worry about the database name
    char** colNames;
    VarTypes* types;
} CreateSTMT;

/**
 * *DELETE STATEMENT
 */
typedef struct {
    Condition* condition;
} DeleteSTMT;

/**
 * *INSERT STATEMENT
 */
typedef struct {
    char* table;
    char** cols;
    char** vals;
} InsertSTMT;

typedef struct{
    StatementType* type;

    // Since we will have different kinds of structs for
    // different statements I will have to use a void pointer
    void* stmt_data; 
} Statement ;

#endif