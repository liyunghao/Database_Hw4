#ifndef DB_UTIL_H
#define DB_UTIL_H
#include "Command.h"
#include "Table.h"

typedef struct State {
    int saved_stdout;
} State_t;
typedef struct pair {
    int *idxList;
    int listLen;
} Pair_t;
typedef struct tuple {
    int *idxList1;
    int *idxList2;
    int listLen;
} Tuple_t;
State_t* new_State();
void print_prompt(State_t *state);
void print_user(User_t *user, SelectArgs_t *sel_args);
void print_like(Like_t *like, SelectArgs_t *sel_args);
void print_aggre(Table_t *table, int *idxList, size_t idxListLen, Command_t *cmd);
void print_users(Table_t *table, int *idxList, size_t idxListLen, Command_t *cmd);
void print_likes(Table_t *table, int *idxList, size_t idxListLen, Command_t *cmd);
int parse_input(char *input, Command_t *cmd);
void handle_builtin_cmd(Table_t *table, Command_t *cmd, State_t *state);
Pair_t where_users(Table_t *table, Command_t *cmd);
void updater(Table_t *table, int *idxList, size_t idxListLen, Command_t *cmd);
void deleter(Table_t *table, int *idxList, size_t idxListLen, Command_t *cmd);
int handle_query_cmd(Table_t *table, Command_t *cmd);
int handle_insert_cmd(Table_t *table, Command_t *cmd);
int handle_select_cmd(Table_t *table, Command_t *cmd);
int handle_update_cmd(Table_t *table, Command_t *cmd);
int handle_delete_cmd(Table_t *table, Command_t *cmd);
void print_help_msg();

#endif
