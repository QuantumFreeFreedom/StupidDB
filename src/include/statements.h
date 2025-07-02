#ifndef STATEMENT
#define STATEMENT

typedef enum{
    STMT_INSERT,
    STMT_SELECT,
    STMT_CREATE
} StatementType;

typedef enum{
    INT,
    STRING
} VarTypes;

typedef struct{
    char* tableName; //this simple database only has 1 db so I dont need to worry about the database name
   
    char** colNames;
    VarTypes* types;
} InsertSTMT;

/**
 * I don't really care about allowing all the SQL functionality (I AM MAKING THIS FOR FUN)
 * so I will onlly allow WHERE conditions
 */
typedef struct{

} Condition;

typedef struct {
    char* to_select;
    char* table_select;
    
    Condition* condition;
} SelectSTMT;

typedef struct{
    StatementType* type;

    // Since we will have different kinds of structs for
    // different statements I will have to use a void pointer
    void* stmt_data; 
} Statement ;

#endif