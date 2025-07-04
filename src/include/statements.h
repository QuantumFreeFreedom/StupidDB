#ifndef STATEMENT
#define STATEMENT

#include <stdlib.h>

#include <stdbool.h>

typedef enum{
    STMT_INSERT,
    STMT_SELECT,
    STMT_CREATE,
    STMT_DELETE,
    STMT_DROP,
    STMT_INVALID // used when a valid statement wasn't detected
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

typedef struct{
    char* tableReferenceName;
} ForeignKeyData;

typedef struct{
    bool isPrimary;
    bool allowsNull;
    bool unique;
    bool isForeignKey;
    
    char* colName;

    VarTypes type;

    ForeignKeyData* fk_data;
} Columns;

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
    Columns* cols;
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

/**
 * *DROP STATEMENT
 */
typedef struct{
    char* tableName; // again, this is a single database system.
} DropSTMT;

typedef struct{
    StatementType type;

    // Since we will have different kinds of structs for
    // different statements I will have to use a void pointer
    void* stmt_data; 
} Statement ;

#endif