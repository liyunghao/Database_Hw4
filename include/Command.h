#ifndef COMMAND_H
#define COMMAND_H

enum { 
    UNRECOG_CMD,
    BUILT_IN_CMD,
    QUERY_CMD,
};

enum {
    INSERT_CMD = 100,
    SELECT_CMD,
    UPDATE_CMD,
    DELETE_CMD,
};

typedef struct {
    char name[256];
    int len;
    unsigned char type;
} CMD_t;

extern CMD_t cmd_list[];

typedef struct SelectArgs {
    char **fields;
    size_t fields_len;
    int offset;
    int limit;
} SelectArgs_t;

typedef struct WhereArgs {
    char **fields;
    size_t fields_len;
    char **operators;
    char **conditions;
    int and;
} WhereArgs_t;

typedef struct UpdateArgs {
    char *fields;
    char *dest;
} UpdateArgs_t;

typedef struct AggreArgs {
    char **type;
    char **fields;
    size_t fields_len;

} AggreArgs_t;
typedef struct JoinArgs {
    char *field;
} JoinArgs_t;
typedef struct Command {
    unsigned char type;
    char **args;
    char *table;
    size_t args_len;
    size_t args_cap;
    SelectArgs_t sel_args;
    WhereArgs_t whe_args;
    UpdateArgs_t up_args;
    AggreArgs_t aggre_args;
    JoinArgs_t join_args;
} Command_t;

Command_t* new_Command();
int add_Arg(Command_t *cmd, const char *arg);
int add_select_field(Command_t *cmd, const char *argument);
int add_where_field(Command_t *cmd, const char *arg1, const char *arg2, const char *arg3);
int add_aggre(Command_t *cmd, char *arg);
void cleanup_Command(Command_t *cmd);

#endif
