#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Command.h"
#include "SelectState.h"

void update_state_handler(Command_t *cmd, size_t arg_idx) {
    if (!strncmp(cmd->args[arg_idx], "user", 4) && !strncmp(cmd->args[arg_idx+1], "set", 3)) {
        cmd->table = "user";
        arg_idx += 2;
        cmd->up_args.fields = cmd->args[arg_idx];
        arg_idx += 2;
        cmd->up_args.dest = cmd->args[arg_idx];
        arg_idx++;
        if (arg_idx < cmd->args_len) {
            if (!strncmp(cmd->args[arg_idx], "where", 5)) {
                where_state_handler(cmd, arg_idx+1);
                return;
            }
        } 
        return;
    } else {
        cmd->type = UNRECOG_CMD;
            return;
    }
}
void delete_state_handler(Command_t *cmd, size_t arg_idx) {
    if (!strncmp(cmd->args[arg_idx], "from", 4) && !strncmp(cmd->args[arg_idx+1], "user", 4)) {
        cmd->table = "user";
        arg_idx+=2;
        if (arg_idx < cmd->args_len) {
            if (!strncmp(cmd->args[arg_idx], "where", 5)) {
                where_state_handler(cmd, arg_idx+1);
                return;
            }
        } 
        return;
    } else {
        cmd->type = UNRECOG_CMD;
            return;
    }
}
void field_state_handler(Command_t *cmd, size_t arg_idx) {
    
    while(arg_idx < cmd->args_len) {
        // printf("1\n");
        if (!strncmp(cmd->args[arg_idx], "*", 1)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "count", 5) || !strncmp(cmd->args[arg_idx], "avg", 3) || !strncmp(cmd->args[arg_idx], "sum", 3)) {
            add_aggre(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "id", 2)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "name", 4)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "email", 5)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "age", 3)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "from", 4)) {
            table_state_handler(cmd, arg_idx+1);
            return;
        } else {
            cmd->type = UNRECOG_CMD;
            return;
        }
        arg_idx += 1;
    }
    cmd->type = UNRECOG_CMD;
    return;
}
void where_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len) {
        add_where_field(cmd, cmd->args[arg_idx], cmd->args[arg_idx+1], cmd->args[arg_idx+2]);
        arg_idx += 3;
        if (arg_idx == cmd->args_len) {
            return;
        } else if (arg_idx < cmd->args_len && !strncmp(cmd->args[arg_idx], "and", 3)) {
            cmd->whe_args.and = 1;
            where_state_handler(cmd, arg_idx+1);
            return;
        } else if (arg_idx < cmd->args_len && !strncmp(cmd->args[arg_idx], "or", 2)) {
            where_state_handler(cmd, arg_idx+1);
            return;
        } else if (arg_idx < cmd->args_len && !strncmp(cmd->args[arg_idx], "offset", 6)) {
            offset_state_handler(cmd, arg_idx+1);
            return;
        } else if (!strncmp(cmd->args[arg_idx], "limit", 5)) {
            limit_state_handler(cmd, arg_idx+1);
            return;
        } 
    }
    cmd->type = UNRECOG_CMD;
    return;
}
void join_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len && !strncmp(cmd->args[arg_idx++], "like", 4)) {
        if (arg_idx < cmd->args_len && !strncmp(cmd->args[arg_idx++], "on", 2)) {
            if (cmd->args_len - arg_idx > 2) {
                memcpy(cmd->join_args.field1, cmd->args[arg_idx++], sizeof(char*));
                memcpy(cmd->join_args.operators, cmd->args[arg_idx++], sizeof(char*));
                memcpy(cmd->join_args.field2, cmd->args[arg_idx++], sizeof(char*));
            }
            if (arg_idx < cmd->args_len && !strncmp(cmd->args[arg_idx], "where", 5)) {
                where_state_handler(cmd, arg_idx+1);
            }
        }
    }
    return;
}
void table_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len
            && !strncmp(cmd->args[arg_idx], "user", 4)) {
        arg_idx++;
        cmd->table = "user";
        if (arg_idx == cmd->args_len) {
            return;
        } else if (!strncmp(cmd->args[arg_idx], "join", 4)) {
            cmd->table = "join";
            join_state_handler(cmd, arg_idx+1);
            return;
        } else if (!strncmp(cmd->args[arg_idx], "where", 5)) {
            where_state_handler(cmd, arg_idx+1);
            return;
        } else if (!strncmp(cmd->args[arg_idx], "offset", 6)) {
            offset_state_handler(cmd, arg_idx+1);
            return;
        } else if (!strncmp(cmd->args[arg_idx], "limit", 5)) {
            // printf("1\n")
            limit_state_handler(cmd, arg_idx+1);
            return;
        } 
    } else if (arg_idx < cmd->args_len
            && !strncmp(cmd->args[arg_idx], "like", 4)) {
        arg_idx++;
            cmd->table = "like";
        if (arg_idx == cmd->args_len) {
            return;
        } else if (!strncmp(cmd->args[arg_idx], "where", 5)) {
            where_state_handler(cmd, arg_idx+1);
            return;
        } else if (!strncmp(cmd->args[arg_idx], "offset", 6)) {
            offset_state_handler(cmd, arg_idx+1);
            return;
        } else if (!strncmp(cmd->args[arg_idx], "limit", 5)) {
            // printf("1\n")
            limit_state_handler(cmd, arg_idx+1);
            return;
        } 
    }
    cmd->type = UNRECOG_CMD;
    return;
}

void offset_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len) {
        cmd->sel_args.offset = atoi(cmd->args[arg_idx]);

        arg_idx++;

        if (arg_idx == cmd->args_len) {
            return;
        } else if (arg_idx < cmd->args_len
                && !strncmp(cmd->args[arg_idx], "limit", 5)) {

            limit_state_handler(cmd, arg_idx+1);
            return;
        }
    }
    cmd->type = UNRECOG_CMD;
    return;
}

void limit_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len) {
        cmd->sel_args.limit = atoi(cmd->args[arg_idx]);

        arg_idx++;

        if (arg_idx == cmd->args_len) {
            return;
        }
    }
    cmd->type = UNRECOG_CMD;
    return;
}
