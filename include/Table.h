#ifndef TABLE_H
#define TABLE_H
#include <stdlib.h>
#include <stdio.h>
#include "User.h"
#include "Like.h"

#define INIT_TABLE_SIZE 10000
#define EXT_LEN 500

typedef struct Table {
    size_t capacity;
    size_t user_len;
    size_t like_len;
    User_t *users;
    Like_t *likes;
    unsigned char *cache_map;
    FILE *fp;
    char *file_name;
} Table_t;

Table_t *new_Table(char *file_name);
int add_User(Table_t *table, User_t *user);
int add_Like(Table_t *table, Like_t *like);
int archive_user_table(Table_t *table);
int archive_like_table(Table_t *table);
int load_user_table(Table_t *table, char *file_name);
//int load_user_table(Table_t *table, char *file_name);
User_t* get_User(Table_t *table, size_t idx);
Like_t* get_Like(Table_t *table, size_t idx);

#endif
